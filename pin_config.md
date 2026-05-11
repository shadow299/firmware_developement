This is the right question. Instead of memorizing hex values (`0x2`, `0xB`, `0x8`), think:

```text id="w8o1vm"
"What am I trying to do?"
→ choose configuration
```

I’ll give you a practical cheat sheet for STM32F103.

# 🟢 1. LED / simple GPIO output

Example:

* LED
* relay
* buzzer enable pin

You manually control pin:

```c id="q6x6v8"
GPIOx_ODR |= ...
```

Choose:

```text id="7b7d9y"
General Purpose Output Push-Pull
```

Usually:

```text id="4b1l7f"
2 MHz
```

Config:

```text id="d2e4yv"
MODE = 10
CNF  = 00
= 0x2
```

Example:

```c id="f0v3tm"
GPIOC_CRH |= (0x2 << shift);
```

---

# 🔵 2. Button input

Example:

* push button
* switch

Choose:

```text id="0x9m4u"
Input Pull-up / Pull-down
```

Why?

Because floating inputs become noisy.

Config:

```text id="t0j7w3"
MODE = 00
CNF  = 10
= 0x8
```

Then choose pull-up or pull-down using ODR.

---

### Pull-up

```c id="h1m2xz"
GPIOA_ODR |= (1 << pin);
```

Default HIGH.

---

### Pull-down

```c id="p7f3vk"
GPIOA_ODR &= ~(1 << pin);
```

Default LOW.

---

# 🟡 3. UART TX

Example:

* serial output

Peripheral controls pin.

Need:

* alternate function
* strong HIGH/LOW

Choose:

```text id="8j2y4m"
Alternate Function Push-Pull
```

Usually:

```text id="3y7r1q"
50 MHz
```

Config:

```text id="5k6d2n"
MODE = 11
CNF  = 10
= 0xB
```

Example:

```c id="d7x3va"
GPIOA_CRH |= (0xB << 4);
```

(for PA9)

---

# 🟣 4. UART RX

Example:

* receive serial

Pin receives data only.

Choose:

```text id="1v8k6z"
Floating Input
```

Config:

```text id="u9p2sm"
MODE = 00
CNF  = 01
= 0x4
```

---

# 🔴 5. SPI pins

### MOSI / SCK

Peripheral output.

Choose:

```text id="x5n7jd"
Alternate Function Push-Pull
```

```text id="0n7x2r"
0xB
```

---

### MISO

Input pin.

Choose:

```text id="q4m8zh"
Floating Input
```

```text id="9u1kxo"
0x4
```

---

# 🟤 6. I²C SDA / SCL

Very important:

I²C MUST use:

```text id="4m9d7p"
Alternate Function Open-Drain
```

Why?

Shared bus.

Config:

```text id="p8w6yt"
MODE = 11
CNF  = 11
= 0xF
```

---

# ⚫ 7. ADC input

Example:

* potentiometer
* analog sensor

Choose:

```text id="m7z3rq"
Analog Input
```

Config:

```text id="v4k9pb"
MODE = 00
CNF  = 00
= 0x0
```

---

# 🧠 The cheat sheet

| Operation         | Config             |   Hex |
| ----------------- | ------------------ | ----: |
| LED / GPIO output | GP Push-Pull       | `0x2` |
| Button            | Pull-up/down input | `0x8` |
| UART TX           | AF Push-Pull       | `0xB` |
| UART RX           | Floating input     | `0x4` |
| SPI MOSI/SCK      | AF Push-Pull       | `0xB` |
| SPI MISO          | Floating input     | `0x4` |
| I²C SDA/SCL       | AF Open-Drain      | `0xF` |
| ADC               | Analog input       | `0x0` |

---

# 🧠 Mental shortcut

Ask yourself:

### Is pin sending or receiving?

```text id="i0y7hf"
send → output
receive → input
```

---

### Who controls pin?

```text id="z8s4my"
you → GPIO
peripheral → Alternate Function
```

---

### Shared bus?

```text id="k5f2un"
yes → Open-drain
no → Push-pull
```

These 3 questions usually tell you the correct configuration automatically.

MODE chooses INPUT vs OUTPUT

CNF chooses BEHAVIOR
