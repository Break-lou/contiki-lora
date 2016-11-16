#include "debug_util.h"
#include "rtc_config.h"
#include "timestamp.h"
#include <stdlib.h>



void print_buff(uint8_t *buff, uint16_t size)
{
	uint16_t i = 0;
	while(size--)
	{
		printf("%0.2X ", buff[i++]);
		//printf("%c", buff[i++]);
	}
	
	printf("\n");
}


void printf_time(void)
{
	uint64_t time;
	uint8_t h,m,ss,mon,mday;
	uint16_t sss;
	//以下打印的是从上电开始运行的ticks数
//	time = get_rtc_counter_value();
//	h = time/(32768*60*60);
//	m = time%(32768*60*60)/(32768*60);
//	ss = time%(32768*60)/32768;
//	sss = time%32768/32;
//	printf("time is %d:%d:%d.%3d\n",h,m,ss,sss);
	tm_new tm;
	time = get_real_time();
	uint32_t seconds_time = time/RTC_OSA;
	gmtime_new(&tm, seconds_time);
	
	mon = tm.tm_mon;	//月
	mday = tm.tm_mday;	//日
	h = tm.tm_hour;		//时
	m = tm.tm_min;		//分
	ss = tm.tm_sec;		//秒
	sss = (time&0x7fff)*1000/RTC_OSA;	//毫秒
	printf("current time is %02d-%02d %02d:%02d:%02d.%03d\n",mon,mday,h,m,ss,sss);
}

//获取指定范围内的随机数
uint16_t get_rand_time(uint16_t rand_value)
{
	srand(get_current_time());
	uint16_t rand_num = rand();
	uint16_t ret = rand_num%rand_value;
	return ret;
}
//获取指定范围内的随机数
uint32_t get_rand_time32(uint32_t rand_value)
{
	srand(get_current_time());
	uint32_t rand_num = rand();
	uint32_t ret = rand_num%rand_value;
	return ret;
}



