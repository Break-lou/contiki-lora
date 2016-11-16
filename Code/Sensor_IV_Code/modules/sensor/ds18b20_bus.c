#include "ds18b20_bus.h"
#include "wdtimer_config.h"
#if DS18B20_OPERATE
void ds18b20_bus_init(void)
{
	DS18B20_BUS_PORT_IN;
	DS18B20_BUS_PORT_HIGH;
}

// 	PUSH.W {r1}		//
// 	MOV r1,#18		//
// 	MUL r0,r1		//
// 	SUB r0,#3		//

// 	ALIGN
// 	MOV r2,#20
// 	MUL r0,r2		
// 	LSR r0,r0,#2	
// 	SUB r0,#3		
// 	NOP		

// __asm void Dellayus(uint32_t usec)	 
// {	 						
// 	ALIGN
// 	PUSH {r1}
// 	MOV r1,#5		//
// 	MUL r0,r1		//
// 	SUB r0,#4		//			
// loop
// 	SUBS r0,#1	
// 	CMP r0,#0
// 	BNE loop
// 	POP {r1}
// 	BX lr				//3				
// }

int ds18b20_bus_reset(void)
{
    int ret = 1;

    DS18B20_BUS_CLR_BUS;
		delay_Xus(500);	//拉低总线至少480us
    DS18B20_BUS_SET_BUS;
    delay_Xus( 50 );//释放总线后等待15-60us
		//DS18B20_BUS_PORT_IN;
	//	delay_Xus( 10 );
    if(DS18B20_BUS_GET_BUS==0)//检测到DS18B20把总线拉低
    	ret = 0;        //复位成功
		DS18B20_BUS_SET_BUS;
    delay_Xus(500);//等待器件释放总线480us
	//	DS18B20_BUS_SET_BUS;

    return ret;
}

//单总线读一位
uint8_t ds18b20_bus_read_bit(void)
{
	uint8_t data=0;

	DS18B20_BUS_CLR_BUS;//上升沿
	delay_Xus( 2 );//>1us
	DS18B20_BUS_SET_BUS;
	delay_Xus( 5 );//<15us
	if(DS18B20_BUS_GET_BUS)
		data = 1;
	delay_Xus( 60 );//>60us

	return(data);
}

//单总线写一位
void ds18b20_bus_write_bit(uint8_t data)
{
	if(data&0x01)
	{
		DS18B20_BUS_CLR_BUS;
		delay_Xus( 2 );//>1us
		DS18B20_BUS_SET_BUS;
		delay_Xus( 60 );//60us
	}
	else
	{
		DS18B20_BUS_CLR_BUS;
		delay_Xus( 60 );//60us
		DS18B20_BUS_SET_BUS;
		delay_Xus( 2 );//>1us
	}
}

//单总线读一字节
uint8_t ds18b20_bus_read_byte(void)
{
	uint8_t data=0;
	uint8_t i=0;
	//wdtimer_stop();
	for(i=0;i<8;i++)
	{

		data>>=1;
		DS18B20_BUS_CLR_BUS;
		delay_Xus( 2 );//>1us
		DS18B20_BUS_SET_BUS;
		delay_Xus( 4 );//<15us
		if(DS18B20_BUS_GET_BUS) 
			data|= 0x80;
		delay_Xus( 60 );//>60us
		
		DS18B20_BUS_SET_BUS;
		delay_Xus( 2 );
	}
	//wdtimer_start();
  	return(data);
}

//单总线写一字节
void ds18b20_bus_write_byte(uint8_t data)
{
	uint8_t i=0;
	for(i=0;i<8;i++)
	{
		if(data&0x01)
		{
			DS18B20_BUS_CLR_BUS;
			delay_Xus( 5  );//>1us
			DS18B20_BUS_SET_BUS;
			delay_Xus( 60 );//60us
		}
		else
		{
			DS18B20_BUS_CLR_BUS;
			delay_Xus( 60 );//60us
			DS18B20_BUS_SET_BUS;
			delay_Xus( 5 );//>1us
		}
		data>>=1;
		DS18B20_BUS_SET_BUS;
		delay_Xus( 2 );
	}
}
#endif
