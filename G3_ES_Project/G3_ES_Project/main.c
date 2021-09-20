/*
 * G3_ES_Project.c
 *
 * Created: 19.09.2021 11:44:30
 * Author : kathersi
 */ 

#define F_CPU 4915200

#include "uart.h"
#include "sram.h"
#include "adc.h"

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void)
{	
	USART_Init(MYUBRR);
	
	fdevopen(USART_Transmit, USART_Receive);
	
	/* ADC_Timer in PastFiles
	clock_timer();
	*/
	
	/* SRAM in PastFiles	*/
	//setting the SRAM CS to low to select it (active low) from the NAND gates
	DDRC |= (1 << PC3);
	PORTC = 0x04;
	
	SRAM_init();
	SRAM_test();	
	
	
	/* Latch in PastFiles
	DDRA |= (1 << PA7);
	DDRE |= (1 << PE1);
	PORTA = 0x1;
	PORTE = 0x02;
	PORTA |= (1 << PA7);
	_delay_ms(1000);
	PORTE = 0x00;
	PORTA &= ~(1 << PA7);
	_delay_ms(100);
	*/
	
	/* UART in PastFiles
	
	while (1) {
		char c = USART_Receive();
		
		printf("Character received: %c\r\n", c);
	}*/
}


