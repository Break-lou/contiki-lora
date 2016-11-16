#include "delay.h"
#include <stdlib.h>

#define MAX_SYS_CLK 20000000 
extern uint32_t current_sysclk;

//延时time ms
void delayXms(uint32_t time)
{
	int i;
	for(i=0;i<time;i++)
	{
		delay_Xus(1000);
	}
}
//根据系统时钟的改变而定时
void delay_Xus(uint32_t cnt)
{

	delay_us(cnt);
	
}

//4*5*cnt个周期,loop一轮是4个周期,以下参数是5M主频是的定义
__asm void delay_us(uint32_t cnt)
{
	
ALIGN
	PUSH {r1}
	PUSH {r0}
	MOV r1,#1		
	MUL r0,r1		
	SUB r0,#1				
loop
	SUBS r0,#1	
	SUB r0,#0
	CMP r0,#0
	BNE loop
	POP {r0}
	POP {r1}
	BX lr	

}




uint32_t random(uint16_t n)
{
	uint32_t ret;
	uint32_t nMs = n*1000;
	
	if(n<=2)
	{
		
	}else{
		ret = 500 + rand()%(nMs-3000);
	}
	return ret;
}



