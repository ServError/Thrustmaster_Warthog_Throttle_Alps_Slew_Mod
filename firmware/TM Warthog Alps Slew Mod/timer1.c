/*
 * timer1.c
 *
 * Created: 2/14/2022 12:52:49 PM
 *  Author: eserv
 */ 

#include "avr/io.h"
#include "avr/interrupt.h"
#include "timer1.h"

#ifndef F_CPU
#define F_CPU 8000000
#endif

void timer1_setup(void)
{
	TIMSK1 = (1 << TOIE1); // Enable timer overflow interrupt
}

uint8_t timer1_set_4_5_usec(void)
{
	uint16_t ticks;
	
#if (F_CPU ==  8000000)
	ticks = 4500;
#elif (F_CPU == 4000000)
	ticks = 2250;
#else
	ticks = 562; // 1Mhz assumed
#endif

	TCNT1 = 0xFFFF - ticks;
	
	return 1;
}

void timer1_start(void)
{
	TCCR1B = ((0 << CS12) | (1 << CS11) | (0 << CS10)); // Set prescaler to CLKio/8
}

void timer1_stop(void)
{
	TCCR1B = 0;
}

uint16_t timer1_read_counter(void)
{
	return TCNT1;
}

ISR(TIMER1_OVF_vect)
{
	timer1_stop();
	timer1_callback();
}