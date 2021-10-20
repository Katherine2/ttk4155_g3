/*
 * mcp2515.c
 *
 * Created: 04.10.2021 14:36:52
 *  Author: kathersi
 */ 

//Low level driver for setting up the CAN controller and accessing its control and status registers

#include "mcp2515.h"
#include "spi.h"
#include <avr/io.h>
#include <stdio.h>

int status;

void mcp2515_init(void){
	uint8_t value;

	SPI_MasterInit();
	mcp2515_reset();
	
	value = mcp2515_read(MCP_CANSTAT);
	if((value & MODE_MASK) != MODE_CONFIG){
		printf("MCP2515 is NOT in configuration mode after reset!\n");
	}
	//bit timing: BRP = 3 & 16TQ => SyncSeg = 1, PropSeg = 2, PS1 = 7, PS2 = 6, SJW = 1
	/*
	SPI_MasterTransmit(MCP_CNF1);
	SPI_MasterTransmit(0x03);
	SPI_MasterTransmit(MCP_CNF2);
	SPI_MasterTransmit(0b10111010);
	SPI_MasterTransmit(MCP_CNF3);
	SPI_MasterTransmit(0b00000110);
	*/
}

uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	
	PORTB &= ~(1<<PB4);
	
	SPI_MasterTransmit(MCP_READ);
	SPI_MasterTransmit(address);
	result = SPI_MasterReceive();
	
	PORTB |= (1<<PB4);
	
	return result;
}

void mcp2515_write(uint8_t address, uint8_t data){
	PORTB &= ~(1<<PB4);
	SPI_MasterTransmit(MCP_WRITE);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	PORTB |= (1<<PB4);
}

void mcp2515_reset(void){
	PORTB &= ~(1<<PB4);
	SPI_MasterTransmit(MCP_RESET);
	PORTB |= (1<<PB4);
}


void mcp2515_request_to_send(uint8_t buffer){
	PORTB &= ~(1<<PB4);
	switch(buffer){
	case 0:
		SPI_MasterTransmit(MCP_RTS_TX0);
	break;
	case 1:
		SPI_MasterTransmit(MCP_RTS_TX1);
	break;
	case 2:
		SPI_MasterTransmit(MCP_RTS_TX2);
	break;
	case 9:
		SPI_MasterTransmit(MCP_RTS_ALL);
	break;
	default:
		printf("Not a valid entry\n\r try again");
	break;
	}
	PORTB |= (1<<PB4);
}

uint8_t mcp2515_read_status(void){
	uint8_t result;
	PORTB &= ~(1<<PB4);
	SPI_MasterTransmit(MCP_READ_STATUS);
	result = SPI_MasterReceive();
	PORTB |= (1<<PB4);
	return result;
}

void mcp2515_bit_modify(uint8_t address, uint8_t data_mask, uint8_t data){
	PORTB &= ~(1<<PB4);
	SPI_MasterTransmit(MCP_BITMOD);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data_mask);
	SPI_MasterTransmit(data);
	PORTB |= (1<<PB4);
}

/*
char mcp2515_read_array(uint8_t address, uint8_t length){
	char result[8];
	for (int i=0; i<length; i++){
		result[i] = mcp2515_read(address + i);
		printf(mcp2515_read(address + i));
	}
	return result;
}
*/
// void mcp2515_write_array(uint8_t address, uint8_t length, char data){
// 	for (int i=0; i<length; i++){
// 		mcp2515_write(address + i, data[i]);
// 		/*printf(mcp2515_read(address + i));*/
// 	}
//}