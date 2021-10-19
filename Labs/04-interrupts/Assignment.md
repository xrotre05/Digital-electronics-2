# Lab 4: Tomas Rotrekl 

Link to your `Digital-electronics-2` GitHub repository:

   [https://github.com/xrotre05/Digital-electronics-2](https://github.com/xrotre05/Digital-electronics-2)


### Overflow times

1. Complete table with overflow times.

| **Module** | **Number of bits** | **1** | **8** | **32** | **64** | **128** | **256** | **1024** |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| Timer/Counter0 | 8  | 16u | 128u | -- | 1024u | -- | 4096u | 16,38m |
| Timer/Counter1 | 16 | 4096u | 32,77m | -- | 262,1m | -- | 1,048s | 4,194s |
| Timer/Counter2 | 8  | 16u | 128u |  512u  | 1024u | 2048u | 4096u | 16,38m |



### Timer library

1. In your words, describe the difference between common C function and interrupt service routine.
   * Function - is usually located in the main loop in intervals checks if conditions are met, when they are it executes the function. It can miis an trigger condition if is is between checks for conditions. 
   * Interrupt service routine - interrupts the operations in main loop immediately when it is triggered 

2. Part of the header file listing with syntax highlighting, which defines settings for Timer/Counter0:

```c
/**
 * @name  Definitions of Timer/Counter0
 * @note  F_CPU = 16 MHz
 */
/** @brief Stop timer, prescaler 000 --> STOP */
	#define TIM1_stop()           TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
	/** @brief Set overflow 4ms, prescaler 001 --> 1 */
	#define TIM1_overflow_4ms()   TCCR0B &= ~((1<<CS02) | (1<<CS01)); TCCR0B |= (1<<CS00);
	/** @brief Set overflow 33ms, prescaler 010 --> 8 */
	#define TIM1_overflow_33ms()  TCCR0B &= ~((1<<CS02) | (1<<CS00)); TCCR0B |= (1<<CS01);
	/** @brief Set overflow 262ms, prescaler 011 --> 64 */
	#define TIM1_overflow_262ms() TCCR0B &= ~(1<<CS02); TCCR0B |= (1<<CS01) | (1<<CS00);
	/** @brief Set overflow 1s, prescaler 100 --> 256 */
	#define TIM1_overflow_1s()    TCCR0B &= ~((1<<CS01) | (1<<CS00)); TCCR0B |= (1<<CS02);
	/** @brief Set overflow 4s, prescaler // 101 --> 1024 */
	#define TIM1_overflow_4s()    TCCR0B &= ~(1<<CS01); TCCR0B |= (1<<CS02) | (1<<CS00);
	/** @brief Enable overflow interrupt, 1 --> enable */
	#define TIM1_overflow_interrupt_enable()  TIMSK0 |= (1<<TOIE0);
	/** @brief Disable overflow interrupt, 0 --> disable */
	#define TIM1_overflow_interrupt_disable() TIMSK0 &= ~(1<<TOIE0);
```

3. Flowchart figure for function `main()` and interrupt service routine `ISR(TIMER1_OVF_vect)` of application that ensures the flashing of one LED in the timer interruption. When the button is pressed, the blinking is faster, when the button is released, it is slower. Use only a timer overflow and not a delay library.The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   ![your figure]()


### Knight Rider

1. Scheme of Knight Rider application with four LEDs and a push button, connected according to Multi-function shield. Connect AVR device, LEDs, resistors, push button, and supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values!

   ![your figure]()
