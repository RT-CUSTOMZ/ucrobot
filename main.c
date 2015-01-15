/*
 * board324t1.c
 *
 * Created: 08.07.2014 07:32:14
 *  Author: olli
 *
 */ 

/*
 *	Hier werden die Funktionen eingebunden
 */

#define F_CPU 14745600UL			//CPU Frequenz festlegen, um delays und co zu berechnen
#include <avr/io.h>					//IO Ports
#include <avr/interrupt.h>			//Interrupts
#include <stdint.h>					//einige Hilfsfunktionen
#include <util/delay.h>				//delays
#include "system_tick.h"			//Unser System-Tick
#include "leds.h"					//LED-Funktionen
#include "motor.h"					//Motor-Funktionen
#include "drehzahlsensor.h"			//Drehzahlsensor
#include "hupe.h"

/*
 *	Wichtige Systemvariablen
 */
uint8_t ticks;	//Anzahl der Ticks, wird alle 10ms um 1 erh�ht (Zeitmessung)
uint16_t sek;	//Vergangene Zeit in Sekunden, l�uft nach ca. 18 Stunden �ber (wird wieder 0)
uint16_t m_r_ticks, m_l_ticks;		//Anzahl der Durchl�ufe des R�der-L�cher

/*
 *	Eigene Variablen
 */

uint8_t run;

int main(void)
{
	//Hier wird alles initialisiert, dh Grundeinstellungen festgelegt
	
	init_Motor();				//Motor einstellen
	init_system_tick();			//System Tick einstellen
	init_drehzahlsensor();		//Drehzahlsensor einstellen
	init_leds();				//LEDs einstellen
	init_hupe();				//Hupe einstellen
	sei();						//Alle Interrupts einschalten
    
	
	while(1)		//Alles innerhalb der while Schleife wird immer wieder wiederholt
    {	
		
		if (~PINB & 0x01)			//Wenn der invertierte Wert des ersten Bits in PINB 1 ist, dann (also wenn der Button gedr�ckt wird)
		{
			led1(AN);				//Mach die LEDs 1 und 3 an
			led3(AN);
			m_r(255,0);				//Und die Motoren mit Vollgas (255) in 2 Richtungen
			m_l(255,1);
			_delay_ms(500);			//Warte 500 ms
			led1(AUS);				//LEDs 1 und 3 aus, LEDs 2 und 4 an
			led3(AUS);
			led2(AN);
			led4(AN);
			m_r(255,1);				//Richtungen �ndern
			m_l(255,0);
			_delay_ms(500);			//und wieder 500ms in die andere Richtung
			m_r(0,0);				//Motoren aus
			m_l(0,0);
			led2(AUS);				//Leds aus
			led4(AUS);
			hupe(AN);				//Hupe an
			_delay_ms(1000);		//1 s warten
			hupe(AUS);				//Hupe aus
			_delay_ms(300);			//300ms warten
			hupe(AN);				//Hupe an
			_delay_ms(500);			//warte 500 ms
			hupe(AUS);				//Hupe aus
		}							//wieder nach oben
	}
}
=======
//Bisher ATMEGA32, anpassen an ATMEGA324:
//TCCR0A usw statt TCCR1

//Defines Allgemein
#define F_CPU 20000000UL

//Defines uCroBot
//zZ Motor ganz an PortD!
#define Mr_1 PD5 //Motor Rechts Anschluss 1 (OC1A)
#define Ml_1 PD4 //Motor Links Anschluss 1 (OC1B)
#define Mr_2 PD0 //Motor Rechts Anschluss 2
#define Ml_2 PD1 //Motor Links Anschluss 2

#include <avr/io.h>			// Einbinden von Einstellungen/Definitionen/usw. für den Mikrocontroller
#include <avr/interrupt.h>
#include <util/delay.h>		// Delayfunktionen

//Globale Variablen
//Motoren
uint8_t Mr_Status = 0; //Bit 0 & 1: Zähler Motor Rechts
uint8_t Ml_Status = 0; //Bit 0 & 1: Zähler Motor Rechts
uint8_t Mr_geschw = 0; //Geschwindigkeit Motor Rechts
uint8_t Ml_geschw = 0; //Geschwindigkeit Motor Links

void init_Motor(void)			// DDRD setzen
{
	uint8_t temp_sreg = SREG;
	cli();						//Interrupts aus
	DDRD |= (1 << Mr_1) | (1 << Mr_2) | (1 << Ml_1) | (1 << Ml_2);			 //DDRD passend setzen
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1A0) | (1 << WGM11); //Phase Correct PWM 16 Bit
	TCCR1B = (1 << CS10) | (1 << WGM13); 	//Kein Prescaler, clk 20MHz / (2*256) = ca 40kHz
	SREG = temp_sreg;
}

void set_Mr_geschw(uint16_t geschw)
{
	OCR1A = geschw;
}

int main (void)				// Hauptprogramm, hier startet der Mikrocontroller
{
	// Initialisierung 
	init_Motor();
	sei();
	set_Mr_geschw(0xFFFF);
	while(1)			// Nie endende Hauptschleife (Endlosschleife)
	{	
		_delay_ms(1000);
		set_Mr_geschw(0x0F00);
		_delay_ms(1000);
		set_Mr_geschw(0x0);
	}					// Ende der Endlosschleife (Es wird wieder zu "while(1)" gesprungen)
	return 0;			// Wird nie erreicht, aber ohne schreibt der GCC eine Warnung
}
