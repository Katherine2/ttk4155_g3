/*
 * G3_ES_Project_Node2.c
 *
 * Created: 18.10.2021 14:07:15
 * Author : kathersi
 */ 


#define F_CPU 84000000

#include <stdio.h>

#include "sam.h"
#include "can_controller.h"
#include "joystick.h"
#include "servo.h"
#include "ir.h"

#define PASSWD_PIO_PWM 0x50494F00

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
    WDT->WDT_MR = WDT_MR_WDDIS;		//disable the watchdog timer
	configure_uart();
	can_init_def_tx_rx_mb(0x00290561);

	/******************* Receiving messages over CAN **********************/
	
	//CAN_MESSAGE msg;
	/*while (1){
		//msg = get_positions();
		/*
		
		msg.id = 2;
		msg.data_length = 1;
		msg.data[0] = 'x';
		
		if(new_message_received()){
			msg = get_message();
			printf("new message: \n\r");
			printf("message id: %d\n\r", msg.id);
			printf("message data length: %d\n\rmessage data: ", msg.data_length);
			for (int i = 0; i < msg.data_length; i++)
			{
				printf("%d ", msg.data[i]);
			}
			printf("\n\n\r");
		}*/
	//}
	
	/************************** BUTTON & Solenoid ***********************************/
	/*
	PIOB -> PIO_PER = PIO_PB26;
	PIOB -> PIO_ODR = PIO_PB26;
	PIOB -> PIO_PUDR = PIO_PB26;
	//PMC->PMC_PCER0 |= PMC_PCER0_PID12;
	
	PIOC -> PIO_PER = PIO_PC16;		//enables input/output function
	PIOC -> PIO_OER = PIO_PC16;		//sets pin PC16 (pin 47) as output
	PIOC -> PIO_PUDR = PIO_PC16;
	while(1){
		int pin_status = PIOB->PIO_PDSR & PIO_PDSR_P22;
		printf("button value: %d\n\r", pin_status);
		/*if (PIOA -> PIO_PDSR_P19){
			PIOC -> PIO_CODR = PIO_PC16;
		}
		else{
			PIOC -> PIO_SODR = PIO_PC16;
		}
		/*PIOC -> PIO_SODR = PIO_PC16;	//sets output data register
		for(int i = 0; i < 30000000; i++){
			j++;
		}
		PIOC -> PIO_CODR = PIO_PC16;	//clear output data register
		for(int i = 0; i < 30000000; i++){
			j++;
		}*/
//	}
	
	/*************************** ADC *************************************/
	/*
	adc_init();
	int goal = 0;
	int adc;
	/************************** SERVO ************************************/
	/*
	pwm_init();
	
	while(1){
		move_servo();
		adc = adc_read();
		goal = is_goal(adc, goal);
	}
	
	/*************************** MOTOR BOX *************************************/
	//DAC
	PMC->PMC_PCER1 |= PMC_PCER1_PID38; //enable clock for DACC
	REG_DACC_MR = DACC_MR_REFRESH(10) | DACC_MR_USER_SEL_CHANNEL1;
	REG_DACC_CHER = DACC_CHER_CH1;
	//REG_DACC_CDR //USE THIS TO SEND JOYSTICK POS
	
	//MotorBox
	PIOD -> PIO_PER = PIO_PD0;		//enables input/output function
	PIOD -> PIO_OER = PIO_PD0;		//sets pin PA19 (pin 42) as output
	PIOD -> PIO_PUDR = PIO_PD0;		//disables pull-ups
	//PIOD -> PIO_CODR = PIO_PD0;	//set OE to low
	//PIOD -> PIO_SODR = PIO_PD0;
	/*************************** SOLENOID *************************************/
/*
	PIOC -> PIO_PER = PIO_PC16; //enables input/output function
	PIOC -> PIO_OER = PIO_PC16;		//sets pin PC16 (pin 47) as output
	PIOC -> PIO_PUDR = PIO_PC16;	//disables pull-ups
	int j = 0;
	while(1){
		PIOC -> PIO_SODR = PIO_PC16;	//sets output data register
		for(int i = 0; i < 30000000; i++){
			j++;
		}
		PIOC -> PIO_CODR = PIO_PC16;	//clear output data register
		for(int i = 0; i < 30000000; i++){
			j++;
		}
	}
	/*
	PIOC -> PIO_PDR |= PIO_PDR_P18;		//enable peripheral control of the pin
	PIOC -> PIO_ABSR |= PIO_ABSR_P18;	//set it to peripheral B mode
	//need to clear WPEN bit in PMC Write Protect Register (we are assuming it defaults to 0)
	//PIOC -> PMC_PCER0 = PIO_PC18;
	PIOC->PIO_WPMR = PASSWD_PIO_PWM;	//disable write protection
	PMC->PMC_PCER1 |= (1 << 4);		//enable PWM clock

	//REG_PMC_PCER0 = 0x00002000;
	PWM->PWM_CLK = 0x002A0000;
	REG_PWM_CPRD6 = 0x00004E20;
	REG_PWM_CDTY6 = 0x00002710; //need to vary this with joystick
	//REG_PWM_ENA = 0x00000040;
	
	PWM->PWM_ENA |= PWM_ENA_CHID6; // enable PWM channel 6*/

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
