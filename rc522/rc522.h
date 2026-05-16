#include <stdint.h>
#include "../spi/spi.h"
#include "../core/core.h"

// RC522 Registers
#define CommandReg 0x01
#define ComIEnReg 0x02
#define DivIEnReg 0x03
#define ComIrqReg 0x04
#define DivIrqReg 0x05
#define ErrorReg 0x06
#define Status1Reg 0x07
#define Status2Reg 0x08
#define FIFODataReg 0x09
#define FIFOLevelReg 0x0A
#define ControlReg 0x0C
#define BitFramingReg 0x0D
#define CollReg 0x0E
#define ModeReg 0x11
#define TxControlReg 0x14
#define TxASKReg 0x15
#define TModeReg 0x2A
#define TPrescalerReg 0x2B
#define TReloadRegH 0x2C
#define TReloadRegL 0x2D
#define VersionReg 0x37

#define CommandReg 0x01
#define CommIEnReg 0x02
#define CommIrqReg 0x04
#define ErrorReg 0x06
#define Status2Reg 0x08
#define FIFODataReg 0x09
#define FIFOLevelReg 0x0A
#define ControlReg 0x0C
#define BitFramingReg 0x0D

#define ModeReg 0x11
#define TxControlReg 0x14
#define TxASKReg 0x15

#define CRCResultRegL 0x22
#define CRCResultRegH 0x21

#define PCD_IDLE 0x00
#define PCD_TRANSCEIVE 0x0C

#define PICC_REQIDL 0x26
#define PICC_ANTICOLL 0x93

void rc522_antenna_on(void);
void rc522_init(void);
uint8_t rc522_card_present(void);
uint8_t rc522_transceive(
    uint8_t *send_data,
    uint8_t send_len,
    uint8_t *back_data,
    uint8_t *back_len);
uint8_t rc522_read_uid(uint8_t *uid);