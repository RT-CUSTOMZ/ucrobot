/*
 *	leds.h
 *
 *	Created: 16.07.14 14:46
 *  Author: olli
 *
 *	Led Funktionen
 *	init_leds()	-		Initialisierung der LED Ports
 *	led1()		-		Steuert die erste LED, led1(AN) zum einschalten, led1(AUS) zum abschalten
 *	led2()		-		usw für led1() - led4()
 */

#ifndef LEDS_H
#define LEDS_H


#define AN 1
#define AUS 0

uint8_t init_leds(){
	DDRA = (1 << PA3) | (1 << PA4) | (1 << PA5) | (1 << PA6);
	return 0;
}

uint8_t led1(uint8_t status){
	if (status == AN)
	{
		PORTA |= (1 << PA3);
		return 1;
	} else {
		PORTA &= ~(1 << PA3);
		return 0;
	}
}

uint8_t led2(uint8_t status){
	if (status == AN)
	{
		PORTA |= (1 << PA4);
		return 1;
	} else {
		PORTA &= ~(1 << PA4);
		return 0;
	}
}

uint8_t led3(uint8_t status){
	if (status == AN)
	{
		PORTA |= (1 << PA5);
		return 1;
	} else {
		PORTA &= ~(1 << PA5);
		return 0;
	}
}

uint8_t led4(uint8_t status){
	if (status == AN)
	{
		PORTA |= (1 << PA6);
		return 1;
	} else {
		PORTA &= ~(1 << PA6);
		return 0;
	}
}

#endif