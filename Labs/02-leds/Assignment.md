# Lab 2: Rotrekl

Link to your `Digital-electronics-2` GitHub repository:

   [https://github.com/xrotre05/Digital-electronics-2](https://github.com/xrotre05/Digital-electronics-2)


### Active-low and active-high LEDs

1. Complete tables according to the AVR manual.

| **DDRB** | **Description** |
| :-: | :-- |
| 0 | Input pin |
| 1 | Output pin |

| **PORTB** | **Description** |
| :-: | :-- |
| 0 | Output low value |
| 1 | Output High value |

| **DDRB** | **PORTB** | **Direction** | **Internal pull-up resistor** | **Description** |
| :-: | :-: | :-: | :-: | :-- |
| 0 | 0 | Input | no | Tri-state, high-impedance |
| 0 | 1 | Input | Yes | Pxn will source current if ext. pulled low. |
| 1 | 0 | Output | no | Output Low (Sink) |
| 1 | 1 | Output | no | Output High (Source) |

2. Part of the C code listing with syntax highlighting, which blinks alternately with a pair of LEDs; let one LED is connected to port B and the other to port C:

```c
int main(void)
{
    // Green LED at port B
    // Set pin as output in Data Direction Register...
    DDRB = DDRB | (1<<LED_GREEN);
    // ...and turn LED off in Data Register
    PORTB = PORTB & ~(1<<LED_GREEN); 
    // Turn LED on
    PORTB = PORTB ^ (1<<LED_INT); 

    // Configure the second LED at port C
    DDRC = DDRC | (1<<LED_EXT);
    
    PORTC = PORTC | (1<<LED_EXT);

    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(BLINK_DELAY);
        
        // Turns state of both leds 
        PORTB = PORTB ^ (1<<LED_INT); 
        PORTC = PORTC ^ (1<<LED_EXT);
    }

    // Will never reach this
    return 0;
}
```


### Push button

1. Part of the C code listing with syntax highlighting, which toggles LEDs only if push button is pressed. Otherwise, the value of the LEDs does not change. Let the push button is connected to port D:

```c
    // Configure Push button at port D and enable internal pull-up resistor
    DDRD = DDRD & ~(1<<BUTTON);  //set DDRD PD2 to 0
    PORTD = PORTD | (1<<BUTTON); //set PORT PD2 to 1

    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(BLINK_DELAY);

        //loop when PIN PD2 is 0
        if (bit_is_clear(PIND, 2))
        {
        //short delay
        _delay_ms(SHORT_DELAY);
        
        //switch both LEDs
        PORTB = PORTB ^ (1<<LED_INT);
        PORTC = PORTC ^ (1<<LED_EXT);
    }
```


### Knight Rider

1. Scheme of Knight Rider application, i.e. connection of AVR device, five LEDs, resistors, one push button, and supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values!

   ![Knight Rider](https://github.com/xrotre05/Digital-electronics-2/blob/main/Labs/02-leds/Knight_Rider.PNG)
