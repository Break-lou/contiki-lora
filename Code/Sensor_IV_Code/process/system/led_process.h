#ifndef __LED_PROCESS_H__
#define __LED_PROCESS_H__
#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"

PROCESS_NAME(led_process);

void stop_led_etimer(void);


#endif
