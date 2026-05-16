#include "rc522.h"

void rc522_antenna_on(void)
{
    uint8_t temp;

    temp = rc522_read_register(TxControlReg);

    if (!(temp & 0x03))
    {
        rc522_write_register(TxControlReg, temp | 0x03);
    }
}

void rc522_init(void)
{
    rc522_spi_init();

    // software reset
    rc522_write_register(CommandReg, 0x0F);
    delay_ms(50);

    // timer settings
    rc522_write_register(TModeReg, 0x8D);
    rc522_write_register(TPrescalerReg, 0x3E);
    rc522_write_register(TReloadRegL, 30);
    rc522_write_register(TReloadRegH, 0);

    rc522_write_register(TxASKReg, 0x40);
    rc522_write_register(ModeReg, 0x3D);

    rc522_antenna_on();
}

uint8_t rc522_card_present(void)
{
    uint8_t irq;
    uint8_t error;
    uint8_t fifo_level;

    // stop command
    rc522_write_register(CommandReg, 0x00);

    // clear interrupts
    rc522_write_register(ComIrqReg, 0x7F);

    // flush FIFO
    rc522_write_register(FIFOLevelReg, 0x80);

    // send REQA
    rc522_write_register(FIFODataReg, 0x26);

    // only 7 bits
    rc522_write_register(BitFramingReg, 0x07);

    // transceive
    rc522_write_register(CommandReg, 0x0C);

    // start transmission
    rc522_write_register(BitFramingReg, 0x87);

    // quick poll (only few checks)
    for (int i = 0; i < 25; i++)
    {
        irq = rc522_read_register(ComIrqReg);

        if (irq & 0x20) // RxIRq
        {
            break;
        }

        if (irq & 0x01) // TimerIRq
        {
            return 0;
        }
    }

    error = rc522_read_register(ErrorReg);

    if (error & 0x1B)
    {
        return 0;
    }

    fifo_level =
        rc522_read_register(FIFOLevelReg);

    return (fifo_level == 2);
}

uint8_t rc522_transceive(
    uint8_t *send_data,
    uint8_t send_len,
    uint8_t *back_data,
    uint8_t *back_len)
{
    uint8_t i;

    // stop command
    rc522_write_register(
        CommandReg,
        PCD_IDLE);

    // clear interrupt flags
    rc522_write_register(
        CommIrqReg,
        0x7F);

    // flush FIFO
    rc522_write_register(
        FIFOLevelReg,
        0x80);

    // write data to FIFO
    for (i = 0;
         i < send_len;
         i++)
    {
        rc522_write_register(
            FIFODataReg,
            send_data[i]);
    }

    // start transceive
    rc522_write_register(
        CommandReg,
        PCD_TRANSCEIVE);

    // start transmission
    rc522_write_register(
        BitFramingReg,
        0x80);

    // wait for response
    i = 200;

    while (i--)
    {
        uint8_t irq =
            rc522_read_register(
                CommIrqReg);

        if (irq & 0x30)
        {
            break;
        }
    }

    if (i == 0)
    {
        return 0;
    }

    // check errors
    if (rc522_read_register(
            ErrorReg) &
        0x1B)
    {
        return 0;
    }

    // receive length
    *back_len =
        rc522_read_register(
            FIFOLevelReg);

    // read response
    for (i = 0;
         i < *back_len;
         i++)
    {
        back_data[i] =
            rc522_read_register(
                FIFODataReg);
    }

    return 1;
}

uint8_t rc522_read_uid(
    uint8_t *uid)
{
    uint8_t cmd[2];
    uint8_t response[10];
    uint8_t response_len;

    // anti-collision command
    cmd[0] =
        PICC_ANTICOLL;

    cmd[1] =
        0x20;

    if (!rc522_transceive(
            cmd,
            2,
            response,
            &response_len))
    {
        return 0;
    }

    // UID is first 4 bytes
    uid[0] =
        response[0];

    uid[1] =
        response[1];

    uid[2] =
        response[2];

    uid[3] =
        response[3];

    return 1;
}