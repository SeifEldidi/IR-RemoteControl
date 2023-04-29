#include "main.h"

uint8 Protcol[5]={0};
Bool Flag=0;
Bool Ret;
uint32 Code;
uint8 Code_str[16];

LCD_4BIT_t LCD={
		.LCD_E.GPIO_PORT=PORTD_INDEX,
		.LCD_E.GPIO_PIN=GPIO_PIN2,
		.LCD_E.GPIO_STATE=GPIO_OUTPUT,
		.LCD_E.GPIO_LOGIC_LEVEL=GPIO_LOW,
		.LCD_RS.GPIO_PORT=PORTD_INDEX,
		.LCD_RS.GPIO_PIN=GPIO_PIN0,
		.LCD_RS.GPIO_STATE=GPIO_OUTPUT,
		.LCD_RS.GPIO_LOGIC_LEVEL=GPIO_LOW,
		.LCD_RW.GPIO_PORT=PORTD_INDEX,
		.LCD_RW.GPIO_PIN=GPIO_PIN1,
		.LCD_RW.GPIO_STATE=GPIO_OUTPUT,
		.LCD_RW.GPIO_LOGIC_LEVEL=GPIO_LOW,
		.LCD_Data[0].GPIO_PORT=PORTD_INDEX,
		.LCD_Data[0].GPIO_PIN=GPIO_PIN3,
		.LCD_Data[0].GPIO_STATE=GPIO_OUTPUT,
		.LCD_Data[0].GPIO_LOGIC_LEVEL=GPIO_LOW,
		.LCD_Data[1].GPIO_PORT=PORTD_INDEX,
		.LCD_Data[1].GPIO_PIN=GPIO_PIN4,
		.LCD_Data[1].GPIO_STATE=GPIO_OUTPUT,
		.LCD_Data[1].GPIO_LOGIC_LEVEL=GPIO_LOW,
		.LCD_Data[2].GPIO_PORT=PORTD_INDEX,
		.LCD_Data[2].GPIO_PIN=GPIO_PIN5,
		.LCD_Data[2].GPIO_STATE=GPIO_OUTPUT,
		.LCD_Data[2].GPIO_LOGIC_LEVEL=GPIO_LOW,
		.LCD_Data[3].GPIO_PORT=PORTD_INDEX,
		.LCD_Data[3].GPIO_PIN=GPIO_PIN6,
		.LCD_Data[3].GPIO_STATE=GPIO_OUTPUT,
		.LCD_Data[3].GPIO_LOGIC_LEVEL=GPIO_LOW,
};


int main()
{
	DDRA|=(1<<2);
	Ret=LCD_4BIT_INIT(&LCD);
	Ret=LCD_4BIT_SEND_STRING_POS(&LCD,"Type:",1,0);
	Ret=LCD_4BIT_SEND_STRING_POS(&LCD,"Code:",2,0);
	IR_INIT(IR_RECIEVER);
	while(1)
	{
		Flag=IR_Read(Protcol,&Code);
		if(Flag==E_OK)
		{
			Ret=LCD_4BIT_SEND_STRING_POS(&LCD,Protcol,1,5);
			convert_int_to_Hex(Code,Code_str);
			LCD_4BIT_SEND_STRING_POS(&LCD,Code_str,2,5);
			if((Flag==E_OK)&&(Code==0xA10))
				PORTA^=(1<<2);
		}
	}
	return 0;
}



