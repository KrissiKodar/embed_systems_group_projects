#include <digital_out.h>
#include <digital_in.h>
#include <timer_msec.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <encoder.h>
#include <Arduino.h>

Digital_out in_1(0);
Digital_out in_2(4);
//Digital_out PWM_pin(1);
Digital_in encoder_input1(2);
Digital_in encoder_input2(3);
encoder enc;
Timer_msec timer1;

int old_counter = 0;
double deg = 0.0;
double interval = 200.0;
double speed = 0.0;
double max_speed = 1000.0;
bool check = true;
double time_constant = 0.0;

int timer1_count = 0;
float duty_cycle = 0.5;

double set_speed = 10.0;
double error = 0.0;
double P = 1.0;

int main()
{
	///////// for serial monitor /////////
	Serial.begin(9600);

	/////////// for H-bridge /////////////
	in_1.init();
	in_2.init();
	in_1.set_hi();
	in_2.set_lo();

	PWM_pin.init();

	/////////// for encoder /////////////
	encoder_input1.init();
	encoder_input2.init();
	enc.init(encoder_input1.is_hi());
	// use if encoder is connected to interrupt pins
	enc.init_interrupt();

	/////////// for timer /////////////
	// find out what frequency is needed for PWM
	timer1.init(interval);
	//timer1.init(interval,duty_cycle);
	
	sei(); // enable interrupts

	while(1)
	{	

		// Part 2 measure maximum motor speed
		if (speed >= max_speed)
		{
			speed = max_speed;
			Serial.println("Maximum speed: ");
			Serial.println(speed);
		}

		// Part 2 measure time constant
		// measure time it takes to reach 63% of max speed
		// the max speed needs to  be measured first !!!!
		/* if (speed >= 0.63 * max_speed && check)
		{
			time_constant = time_value;
			Serial.print("time constant: ");
			Serial.println(time_constant);
			check = false;
		} */

		// Part 3 P control
		// control output should be updated at a mininum rate
		// set speed to x pulses per second
		// calculate error
		//error = set_speed - speed;
		//duty_cycle = P*error;
		//timer1.set(duty_cycle);
	}
}

ISR (INT0_vect)
{
	// increment/decrement counter
	enc.position(encoder_input1.is_hi(), encoder_input2.is_hi());
}

ISR(TIMER1_COMPA_vect)
{
	// interrupts every interval ms
	// speed -> pulses per second
	speed = (enc.get_counter()/interval)/1000.0;
	// or in RPM
	//speed = (((enc.get_counter()/interval)*1000.0)/1400.0)*60.0;
	// 
	enc.reset_counter();
	Serial.print(speed);
	Serial.print('\n');

	// for PWM
	PWM_pin.set_hi();
}

/* //PWM
ISR(TIMER0_COMPB_vect)
{
	PWM_pin.set_lo();
} */

// The other interrupt pin
//ISR (INT1_vect)
//{
//	/* interrupt handler code here */
//	Serial.print('int1 active');
//	Serial.print('\n');	
//}

