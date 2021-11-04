## Preparation tasks (done before the lab at home)

1. Use schematic of the [LCD keypad shield](../../Docs/arduino_shield.pdf) and find out the connection of LCD display. What data and control signals are used? What is the meaning of these signals?

   &nbsp;

   &nbsp;

   &nbsp;

   &nbsp;

   &nbsp;

   &nbsp;

   | **LCD signal(s)** | **AVR pin(s)** | **Description** |
   | :-: | :-: | :-- |
   | RS | PB0 | Register selection signal. Selection between Instruction register (RS=0) and Data register (RS=1) |
   | R/W | GND | Register read or write |
   | E | PB1 | Starts data read/write |
   | D[3:0] | GND | These pins are not used during 4-bit operation |
   | D[7:4] | PD[7:4] | Used for data transfer and receive between the MPU and the HD44780U |

2. What is the ASCII table? What are the codes/values for uppercase letters `A` to `Z`, lowercase letters `a` to `z`, and numbers `0` to `9` in this table?

   | **Char** | **Decimal** | **Hexadecimal** |
   | :-: | :-: | :-: |
   | `A` | 65 | 0x41 |
   | `B` | 66 | 0x42 |
   | ... |  |  |
   | `Y` | 89 | 0x59 |
   | `Z` | 90 | 0x60 |
   | `a` | 97 | 0x61 |
   | `b` | 98 | 0x62 |
   | ... |  |  |
   | `y` | 121 | 0x79 |
   | `z` | 122 | 0x80 |
   | `0` | 48 | 0x30 |
   | `1` | 49 | 0x31 |
   | ... |  |  |
   | `8` | 56 | 0x38 |
   | `9` | 57 | 0x39 |
