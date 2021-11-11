/***********************************************************************
 * 
 * The I2C bus scanner detects the addresses of the modules that are 
 * connected to the SDA and SCL signals. A simple description of FSM is 
 * used.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <stdlib.h>         // C library. Needed for conversion function
#include "uart.h"           // Peter Fleury's UART library
#include "twi.h"            // TWI library for AVR-GCC

/* Variables ---------------------------------------------------------*/
typedef enum {              // FSM declaration
    STATE_IDLE = 1,
    STATE_HUMID,
    STATE_TEMP,
    STATE_CHECK
} state_t;

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1 and send I2C (TWI) address every 33 ms.
 *           Send information about scanning process to UART.
 * Returns:  none
 **********************************************************************/
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

    // Put strings to ringbuffer for transmitting via UART
    

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Update Finite State Machine and test I2C slave addresses 
 *           between 8 and 119.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    static state_t state = STATE_IDLE;  // Current state of the FSM
    static uint8_t addr = 0x5c;            // I2C slave address
    uint8_t result = 1;                 // ACK result from the bus
    char uart_string[2] = "00"; // String for converting numbers by itoa()

    // FSM
    switch (state)
    {
    // Increment I2C slave address
    case STATE_IDLE:
        state= STATE_HUMID;
        

        break;
    
    
    case STATE_HUMID:
        twi_start((addr<<1) + TWI_WRITE);
        
        //if (result==0){
        //uart_puts("0\n\r");
        //}            
        //else{
        //uart_puts("1\n\r");               
        //}
        
        
        twi_write(0);
        
        twi_start((addr<<1) + TWI_READ);
        
        uart_puts("\r\nHumidity:\r\n");
        result=twi_read_ack();
        itoa(result,uart_string,10);
        uart_puts(uart_string);
        uart_puts(".");
        
        result=twi_read_nack();
        itoa(result,uart_string,10);
        uart_puts(uart_string);
        uart_putc('\n');
        uart_putc('\r');
        
        
        twi_stop();
        
        state=STATE_TEMP;
        break;

    
    case STATE_TEMP:
       
       twi_start((addr<<1) + TWI_WRITE);

       twi_write(2);
       
       twi_start((addr<<1) + TWI_READ);
       
       
       uart_puts("\r\nTemperature:\r\n");
       result=twi_read_ack();
       itoa(result,uart_string,10);
       uart_puts(uart_string);
       uart_puts(".");
       
       result=twi_read_nack();
       itoa(result,uart_string,10);
       uart_puts(uart_string);
       uart_putc('\n');
       uart_putc('\r');
       
       
       twi_stop();
       
       state=STATE_CHECK;

        break;


    case STATE_CHECK:
    
        state=STATE_IDLE;
    break;
  
    default:
        state = STATE_IDLE;
        break;
    }
}