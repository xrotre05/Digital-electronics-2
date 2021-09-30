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
    PORTB = PORTB & ~(1<<LED_INT);
    DDRB = DDRB | (1<<LED_INT);
    
    PORTC = PORTC | (1<<LED_EXT);
    DDRC = DDRC | (1<<LED_EXT);
    
    PORTB = PORTB ^ (1<<LED_INT);

    // Infinite loop
    while (1)
    {
        _delay_ms(SHORT_DELAY);
        PORTB = PORTB ^ (1<<LED_INT);
        PORTC = PORTC ^ (1<<LED_EXT);
    }
    return 0;
}
