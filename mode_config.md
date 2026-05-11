Perfect. You’ve reached one of the most confusing STM32 topics: **CRL/CRH pin configuration**.

After this clicks, GPIO setup becomes easy.

Think of every STM32 pin as having **4 configuration bits**:

```text id="1g65oq"
CNF1 CNF0 MODE1 MODE0
```

Example for PC13:

```text id="bchfht"
[31:28]
```

4 bits control the whole pin behavior.

---

# 🧠 Big picture

STM32 asks TWO questions for every pin:

---

## Question 1:

```text id="3tw65x"
Input or Output?
```

This is:

```text id="mif6l4"
MODE bits
```

---

## Question 2:

```text id="w4q2ww"
How should pin behave?
```

This is:

```text id="c8t8gw"
CNF bits
```

---

# 🥇 MODE bits

These decide:

```text id="sqrqw3"
input or output speed
```

---

## MODE = 00

```text id="14zwn4"
INPUT MODE
```

Pin listens.

Examples:

* button
* sensor output
* UART RX

---

## MODE = 01

```text id="ztjlwm"
OUTPUT 10 MHz
```

---

## MODE = 10

```text id="jlwm12"
OUTPUT 2 MHz
```

---

## MODE = 11

```text id="jlwm13"
OUTPUT 50 MHz
```

---

# 🧠 Important realization

This is NOT CPU speed.

It means:

```text id="jlwm14"
maximum GPIO switching speed
```

---

## Practical rule

| Use          | Speed     |
| ------------ | --------- |
| LED          | 2 MHz     |
| UART         | 10/50 MHz |
| SPI          | 50 MHz    |
| General GPIO | 2 MHz     |

---

# 🥈 CNF bits in INPUT mode

Only valid when:

```text id="jlwm15"
MODE = 00
```

---

## CNF = 00

### Analog input

Used for:

```text id="jlwm16"
ADC
```

Example:

* potentiometer
* analog temperature sensor

Pin directly goes to ADC hardware.

---

## CNF = 01

### Floating input

Pin:

```text id="jlwm17"
not connected internally
```

It "floats".

Example:

* UART RX

Danger:
noise may trigger random values.

---

## CNF = 10

### Pull-up / Pull-down input

Internal resistor added.

Pin becomes stable.

---

### Pull-up

Default HIGH.

Button to GND:

```text id="jlwm18"
not pressed → HIGH
pressed → LOW
```

---

### Pull-down

Default LOW.

Button to VCC:

```text id="jlwm19"
not pressed → LOW
pressed → HIGH
```

---

## CNF = 11

Reserved

Ignore it.

---

# 🥉 CNF bits in OUTPUT mode

When:

```text id="jlwm20"
MODE > 00
```

---

## CNF = 00

### General purpose Push-Pull

Most common.

Pin actively drives:

```text id="jlwm21"
HIGH and LOW
```

Used for:

* LED
* simple GPIO

---

### Example

Your LED:

```c id="jlwm22"
PC13 output push-pull
```

---

## CNF = 01

### General purpose Open-Drain

Pin can:

```text id="jlwm23"
LOW or FLOAT
```

Used for:

* shared signals
* special logic

Less common.

---

## CNF = 10

### Alternate Function Push-Pull

Peripheral controls pin.

Used for:

```text id="jlwm24"
USART TX
SPI
PWM
```

---

### Example

USART TX on PA9:

Peripheral generates waveform.

You do NOT manually toggle pin.

---

## CNF = 11

### Alternate Function Open-Drain

Used for:

```text id="jlwm25"
I²C
```

Because bus is shared.

---

# 🔥 The cheat sheet

---

## INPUT modes

| MODE | CNF | Meaning      |
| ---- | --: | ------------ |
| 00   |  00 | Analog       |
| 00   |  01 | Floating     |
| 00   |  10 | Pull-up/down |

---

## OUTPUT modes

| MODE | CNF | Meaning         |
| ---- | --: | --------------- |
| 10   |  00 | GPIO push-pull  |
| 10   |  01 | GPIO open-drain |
| 10   |  10 | AF push-pull    |
| 10   |  11 | AF open-drain   |

---

# 🧪 Real examples

---

### LED on PC13

Need:

```text id="jlwm26"
GPIO output push-pull
2 MHz
```

So:

```text id="jlwm27"
MODE = 10
CNF = 00
```

Combined:

```text id="jlwm28"
0010 = 0x2
```

That’s why:

```c id="jlwm29"
GPIOC_CRH |= (0x2 << 20);
```

---

### USART TX

Need:

* peripheral control
* strong HIGH/LOW

So:

```text id="jlwm30"
MODE = 11
CNF = 10
```

Binary:

```text id="jlwm31"
1011 = 0xB
```

---

### I²C SDA/SCL

Need:

* peripheral control
* shared bus

So:

```text id="jlwm32"
MODE = 11
CNF = 11
```

Binary:

```text id="jlwm33"
1111 = 0xF
```

---

### UART RX

Need:

* input
* stable/no pull resistor often

So:

```text id="jlwm34"
MODE = 00
CNF = 01
```

Binary:

```text id="jlwm35"
0100 = 0x4
```

---

# 🧠 Mental shortcut

Ask two questions:

### 1. Input or output?

If peripheral transmits:

```text id="jlwm36"
output
```

If receiving:

```text id="jlwm37"
input
```

---

### 2. Who controls?

```text id="jlwm38"
CPU → GPIO
Peripheral → Alternate Function
```

---

### 3. Shared line?

```text id="jlwm39"
Yes → Open-drain
No → Push-pull
```

---

# 🏁 Final takeaway

STM32 pin config is just:

```text id="jlwm40"
WHO controls it?
(GPIO or peripheral)

HOW electrical output works?
(push-pull/open-drain)

INPUT or OUTPUT?
```

Once those 3 questions become automatic, register configuration becomes easy.
