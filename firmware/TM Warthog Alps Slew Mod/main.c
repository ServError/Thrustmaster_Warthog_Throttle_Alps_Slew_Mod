/**
 * brief ATTiny441 ADC read 2 channels to TWI module as I2C slave
 *
 * Created: 1/23/2022 10:01:07 PM
 *  Author: ServError
 */

#ifndef F_CPU
#define F_CPU 8000000
#endif

//#define PB1_DEBUG

#include <xc.h>
#include "avr/interrupt.h"
#include "avr/sleep.h"

#include "twi_slave.h"
#include "timer1.h"

uint8_t command; 
int8_t x_ready;
int8_t y_ready;
uint8_t sleep_with_timer = 0;
uint8_t sleep_when_idle = 0;
uint8_t wake_source_timer1 = 0;

uint8_t state = 0;

void adc_setup(void)
{
	// Set pin direction to input and turn off pull-ups
	DDRA &= ~((1 << ADC1D) | (1 << ADC2D));
	PORTA &= ~((1 << ADC1D) | (1 << ADC2D));
	
	ADMUXA |= (0b0001 << MUX0);  // select ADC channel 1 (PA1)
	ADMUXB &= 0x00;              // Select VCC reference (3.3V) and 1x Gain
	ADCSRA |= (1 << ADEN);       // Enable the ADC module
	ADCSRA |= (0b100 << ADPS0);  // Enable ADC with Clock prescaled by 16 ; If Clock speed is 8MHz, then ADC clock =
	// 8MHz/16 = 500kHz
	DIDR0  |= ((1 << ADC2D) | (1 << ADC1D)); // Disable digital inputs for ADC pins to save power
}

void adc_sleep(void)
{
	ADCSRA &= ~(1 << ADEN);      // Disable the ADC module	
}

void adc_wake(void)
{
	ADCSRA |= (1 << ADEN);       // Enable the ADC module	
}

uint16_t adc_single_conversion(uint8_t channel)
{
	uint16_t adcResult;
	
	if (channel < 1) return 0; // channel not allowed in this configuration

	ADMUXA &= 0x00; // Clear channel selection
	ADMUXA |= (1 << (channel - 1));  // set ADC channel
	ADCSRA |= (1 << ADSC); // start a single conversion

	while ((ADCSRA & (1 << ADSC)) != 0)
	;                      // Wait till conversion is complete
	adcResult = ADCW;      // Read the ADC result

	return adcResult;
}

void twi_data_from_master(uint8_t data)
{
	command = data;
	sleep_when_idle = 1;
}

uint8_t twi_data_to_master(void)
{
	uint8_t data_to_master;
	
	switch (command)
	{
		case 0x10:
			data_to_master = x_ready;
			break;
		case 0x11:
			data_to_master = y_ready;
			break;
		case 0x0F:
			data_to_master = 0xF1;
			break;
		default:
			data_to_master = 0x00;
			break;
	}
	
	sleep_when_idle = 1;
	
	return data_to_master;
}

void twi_stop_callback(void)
{
	sleep_with_timer = 1; // Set a flag to go to sleep once back in main loop
}

void twi_address_callback(void)
{
	sleep_when_idle = 1;
}

void timer1_callback(void)
{
	wake_source_timer1 = 1;
}

inline void debug_pb1_high(void)
{
#ifdef PB1_DEBUG
	PORTB |= (1 << PORTB1);
#endif
}

inline void debug_pb1_low(void)
{
#ifdef PB1_DEBUG
	PORTB &= ~(1 << PORTB1);
#endif
}

int main(void)
{
	int8_t x_conv, y_conv;

	CCP = 0xD8; // write access signature to Configuration Change Protection Register. Might be redundant
	CLKPR = 0;  // Force clock to 8MHz
	
	MCUCR = (0 << SM1) | (0 << SM0) | (0 << SE); // Idle Sleep Mode
	
	// Set unterminated pins as pulled up inputs

#ifdef PB1_DEBUG
	DDRB &= ~((1 << PORTB0) | (1 << PORTB2));
	PUEB |= ((1 << PUEB0) | (1 << PUEB2));
	// Set up PORTB2 for debug
	DDRB |= (1 << PORTB1);
#else
	DDRB &= ~((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2));
	PUEB |= ((1 << PUEB0) | (1 << PUEB1) | (1 << PUEB2));
#endif
	DDRA &= ~((1 << PORTA0) | (1 << PORTA3) | (1 << PORTA5) | (1 << PORTA7));
	PUEA |= ((1 << PUEA0) | (1 << PUEA3) | (1 << PUEA5) | (1 << PUEA7));
	
	// Leave ADC, TWI, and Timer1 peripherals enabled
	PRR =  (1<<PRUSART0) | (1<<PRUSART0) | (1<<PRSPI) | (1<<PRTIM2) | (1<<PRTIM0); // Disable unused peripherals
	
	adc_setup();

	// Unnecessary, but explicitly set TWI pins as inputs, no pull
	DDRA &= ~((1 << PORTA4) | (1 << PORTA6));
	PUEA &= ~((1 << PUEA4) | (1 << PUEA6));
	
	/* initialize TWI Slave */
	twi_slave_initialise();
	
	// Setup Timer 1
	timer1_setup();

	// Enable interrupts
	sei();

	while(1)
	{
		debug_pb1_low(); // Drive low while awake
		
		if (wake_source_timer1 == 1)
		{
			wake_source_timer1 = 0;
			
			adc_wake();
			x_conv = (-1 * (int8_t)(adc_single_conversion(PINA1) / 4)) + 127;
			y_conv = (int8_t)(adc_single_conversion(PINA2) / 4) - 128;
			
			x_ready = x_conv;
			y_ready = y_conv;

			adc_sleep();
			// Now that we've polled the joystick, we can sleep until the TWI address match interrupt wakes us
			debug_pb1_high(); // Drive high while asleep
			sleep_mode();
		}
		
		if (sleep_with_timer == 1)
		{
			// Configure to sleep and only poll each channel once about 4.5ms after the sending of y axis data completes
			sleep_with_timer = 0;
			
			timer1_set_4_5_usec();
			timer1_start();

			debug_pb1_high(); // Drive high while asleep
			sleep_mode();
		}
		else if (sleep_when_idle == 1)
		{
			sleep_when_idle = 0;
			debug_pb1_high(); // Drive high while asleep
			sleep_mode();
		}
	}
	return 0;
}
