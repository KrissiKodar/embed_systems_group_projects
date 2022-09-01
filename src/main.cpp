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
double deg = 0;

int main()
{
	Serial.begin(9600);
	led.init();
	encoder_input1.init();
	encoder_input2.init();
	enc.init(encoder_input1.is_hi());
	
	enc.init_interrupt(); // nota ef thad a ad nota interrupts!!

	//timer.init(3);
	sei(); // enable interrupts

	while(1)
	{
		/* 
		enc.position(encoder_input1.is_hi(), encoder_input2.is_hi());
		if (enc.get_counter() > old_counter)
		{
			led.set_hi();
		}
		else {
			led.set_lo();
		}
		deg = enc.get_counter()*360.0/1400.0;
		Serial.print(deg);
		Serial.print('\n');
		old_counter = enc.get_counter(); */
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
	//Serial.print(enc.get_counter());
	deg = enc.get_counter()*360.0/1400.0;
	Serial.print(deg);
	Serial.print('\n');
	old_counter = enc.get_counter();
}

// hinn interrupt pinninn
//ISR (INT1_vect)
//{
//	/* interrupt handler code here */
//	Serial.print('int1 active');
//	Serial.print('\n');	
//}