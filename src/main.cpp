#include <digital_out.h>
#include <digital_in.h>
#include <timer_msec.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <encoder.h>
#include <Arduino.h>

Digital_out led(5);
Digital_in encoder_input1(2);
Digital_in encoder_input2(3);
encoder enc;
//Timer_msec timer;

bool flag = 0;
int old_counter = 0;



int main()
{
	Serial.begin(9600);
	led.init();
	encoder_input1.init();
	encoder_input2.init();
	enc.init(encoder_input1.is_hi());
	enc.init_interrupt();

	//timer.init(3);
	sei(); // enable interrupts
	
	//bool last_input1 = encoder_input1.is_hi();
	while(1)
	{
		/* led.set_hi();
		enc.position(encoder_input1.is_hi(), encoder_input2.is_hi());
		led.set_lo();
		Serial.print(enc.get_counter());
        Serial.print('\n'); */
	}

	
}

ISR (INT0_vect)
{
	enc.position(encoder_input1.is_hi(), encoder_input2.is_hi());
	
	if (enc.get_counter() > old_counter)
	{
		led.set_hi();
	}
	else {
		led.set_lo();
	}
	
	Serial.print(enc.get_counter());
	Serial.print('\n');
	old_counter = enc.get_counter();
}

//ISR (INT1_vect)
//{
//	/* interrupt handler code here */
//	Serial.print('int1 active');
//	Serial.print('\n');	
//}

//////////////////////////////////////////////////////////
////////////// svor vid spurningum ///////////////////////

/* 
Part 1:
max sirka 4.2 er max sek thvi: 16000000 / 1024 - 1 = 15624 en ma max 
fara upp i 65536.


//
// Part 2:
vid 25 ms (40 hz) og 0.2 duty cycle virdist
ljosid vera ordid stodugt og haett ad blikka!

//
// Part 3:
Thad sest greinilega ad birtustigid haekkar thegar
ad duty cycle er haekkad!

 */


/* ISR(TIMER1_COMPA_vect)
{
	// action to be done every 1 sec
	led.toggle();
}

// fyrir duty cycle
ISR (TIMER1_COMPA_vect)
{
// action to be taken at the start of the on-cycle
	led.set_hi();
}
ISR (TIMER1_COMPB_vect)
{
// action to be taken at the start of the off-cycle
	led.set_lo();
} */