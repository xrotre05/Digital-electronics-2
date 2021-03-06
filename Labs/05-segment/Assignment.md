# Lab 5: Tomas Rotrekl 

Link to your `Digital-electronics-2` GitHub repository:

   [https://github.com/xrotre05/Digital-electronics-2](https://github.com/xrotre05/Digital-electronics-2)


### 7-segment library

1. In your words, describe the difference between Common Cathode and Common Anode 7-segment display.
   * CC SSD -connected to GND, segment is on when bit is 1
   * CA SSD -connected to Vcc, segment is on when bit is 0

2. Code listing with syntax highlighting of two interrupt service routines (`TIMER1_OVF_vect`, `TIMER0_OVF_vect`) from counter application with at least two digits, ie. values from 00 to 59:

```c
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Increment counter value from 00 to 59.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    static uint16_t i=0;
	static uint16_t j=0;

	if (i==9){
		i=0;
		j++;
		
		if (j==6){
			j=0;
		}
		
	}
	else{
	i++;	
	} 
	

}
```

```c
/**********************************************************************
 * Function: Timer/Counter0 overflow interrupt
 * Purpose:  Display tens and units of a counter at SSD.
 **********************************************************************/
ISR(TIMER0_OVF_vect)
ISR(TIMER0_OVF_vect)
{
	static uint8_t pos = 0;  // This line will only run the first time
			
	switch (pos)
	{
		case 0:
			SEG_update_shift_regs(i, pos);
			break;
		case 1:
			SEG_update_shift_regs(j, pos);
			break;
		
		case 2:
			SEG_update_shift_regs(0, pos);
			break;
		
		case 3:
			SEG_update_shift_regs(0, pos);
			break;
		case 4:
			pos=0;
		break;
		
		default:
			pos=0;
	}
	pos++;
	
}
```

3. Flowchart figure for function `SEG_clk_2us()` which generates one clock period on `SEG_CLK` pin with a duration of 2&nbsp;us. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   ![SEG_clk_2us()](https://github.com/xrotre05/Digital-electronics-2/blob/main/Labs/05-segment/SEG_clk_2us().PNG)


### Kitchen alarm

Consider a kitchen alarm with a 7-segment display, one LED and three push buttons: start, +1 minute, -1 minute. Use the +1/-1 minute buttons to increment/decrement the timer value. After pressing the Start button, the countdown starts. The countdown value is shown on the display in the form of mm.ss (minutes.seconds). At the end of the countdown, the LED will start blinking.

1. Scheme of kitchen alarm; do not forget the supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values.

   ![Kitchen alarm](https://github.com/xrotre05/Digital-electronics-2/blob/main/Labs/05-segment/Kitchen_alarm.PNG)
