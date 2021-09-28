# Lab 1: Rotrekl

Link to your `Digital-electronics-2` GitHub repository:

   [https://github.com/xrotre05/Digital-electronics-2](https://github.com/xrotre05/Digital-electronics-2)


### Blink example

1. What is the meaning of the following binary operators in C?
   * `|`    - Binary OR Operator
   * `&`    - Binary AND Operator
   * `^`    - Binary XOR Operator 
   * `~`    - Binary NOT Operator  
   * `<<`   - Binary Left Shift Operator
   * `>>`   - Binary Right Shift Operator

2. Complete truth table with operators: `|`, `&`, `^`, `~`

| **b** | **a** |**b or a** | **b and a** | **b xor a** | **not b** |
| :-: | :-: | :-: | :-: | :-: | :-: |
| 0 | 0 | 0 | 0 | 0 | 1 |
| 0 | 1 | 1 | 0 | 1 | 1 |
| 1 | 0 | 1 | 0 | 1 | 0 |
| 1 | 1 | 1 | 1 | 0 | 0 |


### Morse code

1. Listing of C code with syntax highlighting which repeats one "dot" and one "comma" on a LED:

```c
#define LED_GREEN   PB5 // AVR pin where green LED is connected
#define SHORT_DELAY 250 // Delay between parts of the same letter   1 unit
#define DELAY       750 // Delay between letters                    3 units
#define LONG_DELAY  1750// Delay between words                      7 units
#define DOT         250 // Delay of dot signal                      1 unit
#define COMMA       750 // Delay of comma signal                    3 units
#ifndef F_CPU           // Preprocessor directive allows for conditional
                        // compilation. The #ifndef means "if not defined".
# define F_CPU 16000000 // CPU frequency in Hz required for delay
#endif

#include <util/delay.h> // Functions for busy-wait delay loops
#include <avr/io.h>     // AVR device-specific IO definitions

int main(void)
{   
    // Set pin as output in Data Direction Register
    // DDRB = DDRB or 0010 0000
    DDRB = DDRB | (1<<LED_GREEN);

    // Set pin LOW in Data Register (LED off)
    // PORTB = PORTB and 1101 1111
    PORTB = PORTB & ~(1<<LED_GREEN);

    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(SHORT_DELAY);

        // Invert LED in Data Register
        // PORTB = PORTB xor 0010 0000
        PORTB = PORTB ^ (1<<LED_GREEN);     //led on
        
        _delay_ms(DOT);                         //dot
       
       PORTB = PORTB ^ (1<<LED_GREEN);     //off
       
       _delay_ms(SHORT_DELAY);
       
       PORTB = PORTB ^ (1<<LED_GREEN);     //on
       
       _delay_ms(COMMA);                       // comma

       PORTB = PORTB ^ (1<<LED_GREEN);     //off
       
       _delay_ms(LONG_DELAY);
    }

    // Will never reach this
    return 0;
}
```


2. Scheme of Morse code application, i.e. connection of AVR device, LED, resistor, and supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values!

   ![Scheme](https://github.com/xrotre05/Digital-electronics-2/blob/main/Labs/01-tools/scheme.PNG)
