#ifndef SYSTEM_TICK_H
#define SYSTEM_TICK_H

/*
 * system_tick.c
 *
 * Created: 08.07.2014 07:32:14
 *  Author: olli
 *
 *	init_system_tick()		-	Stellt den Timer0 als Sytemtimer ein 
 */ 

//Externe Variablen einbinden
extern uint8_t ticks;
extern uint16_t sek;


void init_system_tick()	//Timer0 als System Tick, Vorteiler 1024
//ReloadWert 144, Vorteiler 1024 -> ca 100Hz Interrupt Takt
{
	TCCR0B |= (1 << CS02) | (1 << CS00);	//Vorteiler
	TIMSK0 |= (1 << TOIE0);					//Interrupt Mask
	ticks = 0;
}

ISR(TIMER0_OVF_vect)	//Timer0 Interrupt Funktion
{
	ticks++;
	TCNT0 = 112;
	//PORTA = ~PORTA;		//LEDs Blinken
}
#endif