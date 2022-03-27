/*
 * timer1.h
 *
 * Created: 2/14/2022 12:52:58 PM
 *  Author: eserv
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

void timer1_setup(void);

uint8_t timer1_set_4_5_usec(void);

void timer1_start(void);

void timer1_stop(void);

uint16_t timer1_read_counter(void);

void timer1_callback(void);

#endif /* TIMER1_H_ */