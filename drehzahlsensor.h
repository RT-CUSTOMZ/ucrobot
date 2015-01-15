#ifndef DREHZAHLSENSOR_H
#define DREHZAHLSENSOR_H

extern uint16_t m_l_ticks;
extern uint16_t m_r_ticks;



uint8_t init_drehzahlsensor(void)
{
	DDRA &= ~(1 << PA7);	//Sensor Links
	DDRC &= ~(1 << PC7);	//Sensor Rechts
	PCMSK2 |= (1 << PCINT23);	//Interrupt Mask
	PCMSK0 |= (1 << PCINT7);
	PCICR |= (1 << PCIE0) | (1 << PCIE2); //Interrupt Enable
	m_r_ticks = 0;
	m_l_ticks = 0;
	return 0;
}

ISR(PCINT0_vect)
{
	if (PINA & (1 << PA7)) //nur wenn auch 1
	{
		m_r_ticks++; //Dann mach +1
		/*PORTA |= (1 << PA5);
		PORTA &= ~(1 << PA5);*/
	}
}

ISR(PCINT2_vect)
{
	if (PINC & (1 << PC7)) //nur wenn auch 1
	{
		m_l_ticks++; //Dann mach +1
		/*PORTA |= (1 << PA5);
		PORTA &= ~(1 << PA5);*/
	}
}

#endif