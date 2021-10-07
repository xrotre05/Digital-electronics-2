/*
 * 03-gpio.cpp
 *
 * Created: 07.10.2021 9:33:21
 * Author : student
 */ 
#define LED_INT   PB5 // AVR pin where green LED is connected
#define LED_EXT   PC1
#define SHORT_DELAY 250 // Delay in milliseconds
#ifndef F_CPU           // Preprocessor directive allows for conditional
// compilation. The #ifndef means "if not defined".
# define F_CPU 16000000 // CPU frequency in Hz required for delay
#endif                  // The #ifndef directive must be closed by #endif


#include <util/delay.h>
#include <avr/io.h>
int main(void)
{
    //input output setup
    
        GPIO_config_output(&DDRB, LED_INT);
        GPIO_write_high(&PORTB, LED_INT);
    //PORTB = PORTB & ~(1<<LED_INT);
    //DDRB = DDRB | (1<<LED_INT);
    
        GPIO_config_output(&DDRC, LED_EXT);
        GPIO_write_high(&PORTC, LED_EXT);
    //PORTC = PORTC | (1<<LED_EXT);
    //DDRC = DDRC | (1<<LED_EXT);
    
    //PORTB = PORTB ^ (1<<LED_INT);

    // Infinite loop
    while (1)
    {
        _delay_ms(SHORT_DELAY);
        //PORTB = PORTB ^ (1<<LED_INT);
        //PORTC = PORTC ^ (1<<LED_EXT);
        GPIO_toggle(&PORTB, LED_INT);
        GPIO_toggle(&PORTC, LED_EXT);
        
    }
    return 0;
}
