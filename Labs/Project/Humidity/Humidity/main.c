/*
 * Humidity.c
 *
 * Created: 13.12.2021 14:00:08
 * Author : xrotre05
 */ 
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <stdlib.h>         // C library. Needed for conversion function
#include "timer.h"          // Timer library for AVR-GCC
#include "uart.h"           // Peter Fleury's UART library
#include "twi.h"            // TWI library for AVR-GCC


int main(void)
{
	// Initialize I2C (TWI)
	twi_init();

	// Initialize UART to asynchronous, 8N1, 9600
	uart_init(UART_BAUD_SELECT(9600, F_CPU));

	// Configure 16-bit Timer/Counter1 to update FSM
	// Set prescaler to 33 ms and enable interrupt
	TIM1_overflow_1s();
	TIM1_overflow_interrupt_enable();

	// Enables interrupts by setting the global interrupt mask
	sei();

    /* Replace with your application code */
    while (1) 
    {
		//empty loop		
    }
}


ISR(TIMER1_OVF_vect)
{
	static uint8_t addr = 0x5c;            // I2C slave address
	uint8_t result = 1;                 // ACK result from the bus
	char uart_string[2] = "00"; // String for converting numbers by itoa()

	
		twi_start((addr<<1) + TWI_WRITE);	// start I2C comunication with sensor
				
		twi_write(0);						// state request of data from register 0 
		
		twi_start((addr<<1) + TWI_READ);	// request data from sensor
		
		uart_puts("\r\nHumidity:\r\n");		// write to uart
		result=twi_read_nack();				// write register data to var. result
		itoa(result,uart_string,10);		// convert result to string
		uart_puts(uart_string);				// write string to uart

		
		
		twi_stop();							// stop I2C communication with sensor
				
	}

