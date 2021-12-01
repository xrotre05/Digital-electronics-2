/*
 * Project.c
 *
 * Created: 30.11.2021 14:04:20
 * Author : xrotre05
 */ 

/* Defines -----------------------------------------------------------*/

#define TRIGGER		PB4		
#define ECHO		PB5
#define DELAY		1
#define PUMP		PB3

#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <stdlib.h>         // C library. Needed for conversion function
#include "uart.h"           // Peter Fleury's UART library
#include "twi.h"            // TWI library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include "gpio.h"
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <string.h>

int TimerOverflow = 0;

int main(void)
{
     char string[10];
     long count;
     double distance;
	 
	 //input output setup
     
     GPIO_config_output(&DDRB, TRIGGER);
     GPIO_write_low(&PORTB, TRIGGER);
     //PORTB = PORTB & ~(1<<LED_INT);
     //DDRB = DDRB | (1<<LED_INT);
	 
	 GPIO_config_input_pullup(&DDRB, ECHO);
	 
	 //PORTB = PORTB & ~(1<<LED_INT);
	 //DDRB = DDRB | (1<<LED_INT);
	 
	 GPIO_config_output(&DDRB, PUMP);
	 GPIO_write_low(&PORTB, PUMP);
	 //PORTB = PORTB & ~(1<<LED_INT);
	 //DDRB = DDRB | (1<<LED_INT);
	
	
	// Initialize LCD display
	lcd_init(LCD_DISP_ON);
	lcd_gotoxy(1, 0); lcd_puts("level:");
	lcd_gotoxy(3, 1); lcd_puts("state:");
	lcd_gotoxy(8, 0); lcd_puts("a");    // Put ADC value in decimal
	lcd_gotoxy(8, 1); lcd_puts("b");    // Put button name here
	
	// Initialize I2C (TWI)
    twi_init();

    // Initialize UART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600, F_CPU));

    // Configure 16-bit Timer/Counter0 to update FSM
    // Set prescaler to 1 s and enable interrupt
    TIM0_overflow_1s();
    TIM0_overflow_interrupt_enable();

	TIM1_stop();
	TIM1_overflow_interrupt_enable();
    // Enables interrupts by setting the global interrupt mask
    sei();


    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
		GPIO_write_high(&PORTB, TRIGGER);
		_delay_us(10);
		GPIO_write_low(&PORTB, TRIGGER);
		
		TCNT1 = 0;		/* Clear Timer counter */
		TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/
		TIFR1 = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
		TIFR1 = 1<<TOV1;	/* Clear Timer Overflow flag */
		
		/*Calculate width of Echo by Input Capture (ICP) */
		
		while ((TIFR1 & (1 << ICF1)) == 0);/* Wait for rising edge */
		TCNT1 = 0;	/* Clear Timer counter */
		TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
		TIFR1 = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
		TIFR1 = 1<<TOV1;	/* Clear Timer Overflow flag */
		TimerOverflow = 0;/* Clear Timer overflow count */

		while ((TIFR1 & (1 << ICF1)) == 0);/* Wait for falling edge */
		count = ICR1 + (65535 * TimerOverflow);	/* Take count */
		/* 8MHz Timer freq, sound speed =343 m/s */
		distance = (double)count / 466.47;

		dtostrf(distance, 2, 2, string);/* distance to string */
		strcat(string, " cm   ");	/* Concat unit i.e.cm */
		
		lcd_gotoxy(8, 0); 
		lcd_puts(string);	/* Print distance */
		uart_puts(string);
		uart_putc('\n');
		uart_putc('\r');
		_delay_ms(200);
    }

    // Will never reach this
    return 0;
}

ISR(TIMER1_OVF_vect)
{
	
	TimerOverflow++;	/* Increment Timer Overflow count */			

}