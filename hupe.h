#ifndef HUPE_H
#define HUPE_H
#include <math.h>
#include <stdint.h>
#define F_CPU 14745600UL


uint16_t value;

uint8_t init_hupe(){
	TCCR2A |= (1 << COM2A0) | (1 << WGM21);						//Timer2 CTC Mode
	TCCR2B |= /*(1 << CS22) | */(1 << CS20) | (1 << CS21);		//Vorteiler 32
	OCR2A = 0;													//Aus machen
	DDRD |= (1 << PD7);											//Ausgang beschalten
	return 0;
}

uint8_t hupe_freq(uint16_t freq){
	if(freq < 900){		//minimale freq
		OCR2A = 0xFF; 
		return 0xFF;
	}
	value = (230400 / freq) - 1;
	OCR2A = ((value >> 0) & 0xff);
	return OCR2A;
}

uint8_t beep(uint16_t freq){
	hupe_freq(2 * freq);
return 0;
}

uint8_t hupe(uint8_t status){
	if (status == AN)
	{
		PORTD |= (1 << PD7);
		hupe_freq(2048);
		return 1;
	} else {
		PORTD &= ~(1 << PD7);
		return 0;
	}
}

#endif