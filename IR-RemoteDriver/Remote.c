/*
 * Remote.c
 *
 *  Created on: Apr 27, 2023
 *      Author: Seif pc
 */
#include "Remote.h"
Bool flag=0;
volatile int32 OVF_COUNT=0;

void TIMER2_OVF_INC(void)
{
	OVF_COUNT++;
}


Bool IR_INIT(IR_CONFIG Config_t)
{
	OVF_COUNT=0;
	Bool E_stat=E_OK;
	switch(Config_t)
	{
		case IR_RECIEVER:
			IR_PIN_INPUT();
			break;
		case IR_TRANSMITTER:
			IR_PIN_OUTPUT();
			break;
		default:
			E_stat=E_NOK;
	}
	TIMER1_CONFIG_t Timer1={
				.TIMER1_mode=TIMER1_Normal_non_pwm_mode,
				.WVFM_GEN=TIMER1_Normal_T1,
				.Prescaler=TIMER_FOSC_1,
				.Preload_val=0,
	};
	TIMER1_INIT(&Timer1);//init Timer 1 as 1us Counter to construct code sent by remote
	return E_stat;
}


static Bool IR_Analysis(uint16 *Buffer)
{
	//tsopvs17038 complements the decoded output
	Bool ret=E_OK;
	uint8_t i=0;
	if(BIT_IS_CLEAR(IR_PORT_IN,IR_PIN))
	{
			do
			{
			   TCNT1=3;//start Timer 1 with 3 in TCNT1 and keep waiting
				do {
					Buffer[i]=TCNT1;
				} while ((BIT_IS_CLEAR(IR_PORT_IN, IR_PIN) ) && (Buffer[i] <= 20000));


				TCNT1=3;
				do {
					Buffer[i+1]=TCNT1;
				} while ((BIT_IS_SET(IR_PORT_IN, IR_PIN)) && (Buffer[i + 1] <= 20000));

			   i=i+2;
			}while((*(Buffer+i-2)<=20000)&&(*(Buffer+i-1)<=20000)&&i<=68);
			ret=E_OK;
	}
	else
		ret=E_NOK;
	return ret;
}

Bool IR_Read(char *Protocol_Type,uint32 *Code)
{
	static uint8 RX_flag=0;
	Bool Ret_flag=E_OK;
	uint8 i=0;
	uint8 k=0;
	uint16 Decode_Array[68];
	Ret_flag=IR_Analysis(Decode_Array);//analyse the incoming waveform
	if(Ret_flag==E_OK)
	{
		if((Decode_Array[0]>=8400&&Decode_Array[0]<=10000)&&(Decode_Array[1]>=3800&&Decode_Array[1]<=4700))
		{
			i=START_FRAME;
			Protocol_Type[0]='N';
			Protocol_Type[1]='E';
			Protocol_Type[2]='C';
			Protocol_Type[3]='\0';
			while(i<=64)
			{
				if((Decode_Array[i]>=100&&Decode_Array[i]<=700)&&(Decode_Array[i+1]>=100&&Decode_Array[i+1]<=700))
					CLEAR_BIT(*Code,(NEC_SIZE-k));
				else if((Decode_Array[i]>=100&&Decode_Array[i]<=700)&&(Decode_Array[i+1]>=1200&&Decode_Array[i+1]<=1800))//1560us
					SET_BIT(*Code,(NEC_SIZE-k));
				k++;
				i+=2;
			}
		}
		else if((Decode_Array[0]>=2000&&Decode_Array[0]<=2800)&&(Decode_Array[1]>=100&&Decode_Array[1]<=800))
		{
			i=START_FRAME;
			Protocol_Type[0]='S';
			Protocol_Type[1]='O';
			Protocol_Type[2]='N';
			Protocol_Type[3]='Y';
			Protocol_Type[4]='\0';
			while (i <=24) {//12bits 12*2=24
				if ((Decode_Array[i] >= 100 && Decode_Array[i] <= 750)&&(Decode_Array[i+1]>=100&&Decode_Array[i+1]<=750))
					CLEAR_BIT(*Code,(SONY_SIZE-k));
				else if ((Decode_Array[i] >= 950 && Decode_Array[i] <= 1400)&&(Decode_Array[i+1]>=100&&Decode_Array[i+1]<=750))
					SET_BIT(*Code,(SONY_SIZE-k));
				k++;
				i += 2;
			}
//			RX_flag++;
//			if(RX_flag==4)
//			{
//				RX_flag=0;
//				Ret_flag=E_OK;
//			}
//			else
//				Ret_flag=E_NOK;
		}
	}
	return Ret_flag;
}

