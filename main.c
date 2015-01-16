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
uint8_t ticks;	//Anzahl der Ticks, wird alle 10ms um 1 erhöht (Zeitmessung)
uint16_t sek;	//Vergangene Zeit in Sekunden, läuft nach ca. 18 Stunden über (wird wieder 0)
uint16_t m_r_ticks, m_l_ticks;		//Anzahl der Durchläufe des Räder-Löcher

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
		
		if (~PINB & 0x01)			//Wenn der invertierte Wert des ersten Bits in PINB 1 ist, dann (also wenn der Button gedrückt wird)
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
			m_r(255,1);				//Richtungen ändern
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
