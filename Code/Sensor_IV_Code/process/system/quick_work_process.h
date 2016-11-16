#ifndef __QUICK_WORK_PROCESS_H__
#define __QUICK_WORK_PROCESS_H__



#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"


PROCESS_NAME(quick_work_process);

void post_quick_work_ev(process_event_t ev);
void stop_quick_work_timer(void);
void stop_quick_work_timeout_timer(void);

#define TEST_MAX_NUM 20

typedef struct CTestInfo
{
	uint16_t g_mac;			//所属网关MAC
	uint8_t n_sensitivity;	//节点灵敏度	
	uint8_t g_sensitivity;	//网关灵敏度
}CTestInfo_t;

typedef struct CInfo
{
	CTestInfo_t c_info[TEST_MAX_NUM];
	uint8_t g_num;						//已接入网关个数
}CInfo_t;

extern CInfo_t c_infos;

#endif
