#ifndef __DATA_DOWNLOAD_PROCESS_H__
#define __DATA_DOWNLOAD_PROCESS_H__




#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"




PROCESS_NAME(data_download_process);

void stop_data_download_timeout(void);

void post_data_download_ev(process_event_t ev);



#endif
