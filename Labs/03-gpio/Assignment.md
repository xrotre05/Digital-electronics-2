# Lab 3: Rotrekl 

Link to your `Digital-electronics-2` GitHub repository:

   [https://github.com/xrotre05/Digital-electronics-2/](https://github.com/xrotre05/Digital-electronics-2/)


### Data types in C

1. Complete table.

| **Data type** | **Number of bits** | **Range** | **Description** |
| :-: | :-: | :-: | :-- | 
| `uint8_t`  | 8 | 0, 1, ..., 255 | Unsigned 8-bit integer |
| `int8_t`   | 8 | -128, ..., 127 | Signed 8-bit integer |
| `uint16_t` | 16 | 0, ..., 65 535 | Unsigned 16-bit integer |
| `int16_t`  | 16 | -32 768, ..., 32 767 | Signed 16-bit integer |
| `float`    | 32 | -3.4e+38, ..., 3.4e+38 | Single-precision floating-point |
| `void`     | 0 | None | No value |


### GPIO library

1. In your words, describe the difference between the declaration and the definition of the function in C.
   * Function declaration - You just declare there is something with name and its type
   * Function definition - You provide all of the necessary information to create the thing you defined

2. Part of the C code listing with syntax highlighting, which toggles LEDs only if push button is pressed. Otherwise, the value of the LEDs does not change. Use function from your GPIO library. Let the push button is connected to port D:

```c
    // Configure Push button at port D and enable internal pull-up resistor
    GPIO_config_input_pullup(&DDRD, BUTTON)  //button is defined as :  #define BUTTON   PD2

    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(BLINK_DELAY);

        //loop when PIN PD2 is 0
        if (GPIO_read(&DDRD, BUTTON)) 
        { 
           //short delay 
           _delay_ms(SHORT_DELAY); 

           //switch both LEDs 
           GPIO_toggle(&PORTB, LED_INT);
           GPIO_toggle(&PORTC, LED_EXT);
        }
        
        
        
    }
```


### Traffic light

1. Scheme of traffic light application with one red/yellow/green light for cars and one red/green light for pedestrians. Connect AVR device, LEDs, resistors, one push button (for pedestrians), and supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values!

   ![Traffic](https://github.com/xrotre05/Digital-electronics-2/blob/main/Labs/03-gpio/Traffic.PNG)

