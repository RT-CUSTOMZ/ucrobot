#ifndef MOTOR_H
#define MOTOR_H

//Motorsteuerung

/*
 * motor.h
 *
 * Created: 08.07.2014 07:32:14
 *  Author: olli
 *
 *	Stellt einige Funktionen Bereit:
 *	init_Motor() Initialisiert die Motoren bzw deren Pins
 *	m_r(uint8_t speed, uint8_t richtung) -> Motor Rechts mit Geschwindigkeit speed, richtung != 0 -> Rückwärts
 */ 

#define Mr_1 PD4 //Motor Rechts Anschluss 1 (OC1B)
#define Ml_1 PD5 //Motor Links Anschluss 1 (OC1A)
#define Mr_2 PC3 //Motor Rechts Anschluss 2
#define Ml_2 PC2 //Motor Links Anschluss 2


int init_Motor(void) //Init Funktion
{
	uint8_t temp_sreg = SREG;
	cli();						//Interrupts aus
	DDRD |= (1 << Mr_1) | (1 << Ml_1);			 //DDRD passend setzen
	DDRC |= (1 << Mr_2) | (1 << Ml_2);			 //DDRC passend setzen
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1A0) | (1 << WGM11); //Phase Correct PWM 16 Bit
	TCCR1B = (1 << CS10) | (1 << WGM13) | (1 << CS11); 	//Kein Prescaler, clk 20MHz / (2*256) = ca 40kHz
	ICR1 = 0x300;		//Timer1 zählt bis 2
	PORTC |= (1 << Mr_2) | (1 << Ml_2);
	SREG = temp_sreg;
	return 0;
}



uint8_t m_l(uint8_t speed, uint8_t richtung){
	if(richtung != 0)
	{
		TCCR1A &= ~( (1 << COM1B0) );
		//PORTC |= (1 << Mr_2);
		PORTC &= ~( (1 << Mr_2) );
	} else {
		TCCR1A |= (1 << COM1B0);
		//PORTC &= ~( (1 << Mr_2) );
		PORTC |= (1 << Mr_2);
	}
	OCR1B = speed;
	return 0;
}


uint8_t m_r(uint8_t speed, uint8_t richtung){
	if(richtung != 0)
	{
		TCCR1A &= ~( (1 << COM1A0) );
		//PORTC |= (1 << Ml_2);
		PORTC &= ~( (1 << Ml_2) );
	} else {
		TCCR1A |= (1 << COM1A0);
		//PORTC &= ~( (1 << Ml_2) );
		PORTC |= (1 << Ml_2);
	}
	OCR1A = speed;
	return 0;
}

uint8_t m_r_geschw(void)
{
	return OCR1AL;
}


uint8_t m_l_geschw(void)
{
	return OCR1BL;
}

uint8_t m_r_richtung(void)
{
	if(TCCR1A & ((1 << COM1A0)))
		return 0;
	else return 0xFF;
}

uint8_t m_l_richtung(void)
{
	if(TCCR1A & ((1 << COM1B0)))
		return 0;
	else return 0xFF;
}
#endif
