/*
 * G3_ES_Project_Node2.c
 *
 * Created: 18.10.2021 14:07:15
 * Author : kathersi
 */ 


#define F_CPU 84000000

#include "sam.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include <stdio.h>

/*
#define FOSC 16000000 // Clock Speed
#define CANBAUD 125000
#define BRP 3
#define TQ (2*(BRP+1))/FOSC		//500ns
#define BITTIME 1/(TQ*CANBAUD)	//13TQ => SyncSeg = 1, PropSeg = 1, PS1 = 6, PS2 = 5, SJW = 1
*/

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
    WDT->WDT_MR = WDT_MR_WDDIS;
	configure_uart();
	can_init_def_tx_rx_mb(0x00290561);
	
	/************************** LEDS *************************************/
	/*
	PIOA -> PIO_PER = PIO_PA19;		//enables input/output function
	PIOA -> PIO_OER = PIO_PA19;		//sets pin PA19 (pin 42) as output
	PIOA -> PIO_PUDR = PIO_PA19;	//disables pull-ups
	while (1) {
		PIOA -> PIO_SODR = PIO_PA19;	//sets output data register
		//_delay_ms(500);
		//PIOA -> PIO_CODR = PIO_PA19;	//clear output data register
	}
	*/
	/************************** UART **************************************/
	/*
	configure_uart();
	
	while (1){
		//uart_putchar('!');
		UART_Handler();
		char c;
		uart_getchar(&c);
		printf("character received: %c\r\n", c);
	}*/
}
