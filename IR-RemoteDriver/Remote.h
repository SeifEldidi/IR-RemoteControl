/*
 * Remote.h
 *
 *  Created on: Apr 27, 2023
 *      Author: Seif pc
 */

#ifndef REMOTE_H_
#define REMOTE_H_

/************Includes Section**************/
#include "mcalStdtypes.h"
#include "Gpiodriver.h"
#include "Interrupts.h"
#include "Timer1.h"
#include "Timer2.h"

/************Define Section******************/
#define IR_PIN 0
#define IR_PORT_OUT PORTA
#define IR_PORT_IN PINA
#define IR_PORT_DIR DDRA
#define NEC_SIZE 31
#define SONY_SIZE 11
#define NEC_PROTOCOL 1
#define SONY_PROTCOL 2
#define START_FRAME 2
#define BASE_CLICK_REPEAT_CODE 3
/***********Macro Like Function**************/
#define IR_PIN_OUTPUT() \
	{\
	SET_BIT(IR_PORT_DIR,IR_PIN);\
	CLEAR_BIT(IR_PORT_OUT,IR_PIN);\
	}\

#define IR_PIN_INPUT()  (CLEAR_BIT(IR_PORT_DIR,IR_PIN))
/*************Defined Data types**************/
typedef enum
{
	IR_RECIEVER,
	IR_TRANSMITTER,
}IR_CONFIG;
/*********Software Interfaces*******************/
Bool IR_INIT(IR_CONFIG Config_t);
Bool IR_Read(char *Protocol_Type,uint32 *Code);

#endif /* REMOTE_H_ */
