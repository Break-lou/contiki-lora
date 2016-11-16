#include "data_download_process.h"
#include "sys_event.h"
#include "sensor_payload.h"
#include "sensor_parameter.h"
#include "ext_flash_include.h"
#include "led.h"
#include "wdtimer_config.h"

//数据下载线程

struct etimer data_download_timout_etimer;			//超时定时器

PROCESS(data_download_process, "data_download_process");
PROCESS_THREAD(data_download_process, ev, data)
{

	PROCESS_BEGIN();
	
	while(1)
	{
		PROCESS_WAIT_EVENT();
        
		if(ev == DATA_DOWNLOAD_DATA)
		{
				//1. 装配数据下载数据包
				bool ret = assamble_data_download_payload();
				if(ret)
				{
					//2. 发送数据包
					transmit();
					//3. 开启超时定时器
					etimer_set(&data_download_timout_etimer, 500 ms);			//设置超时
				}
		}
		if(ev == PROCESS_EVENT_TIMER && data == &data_download_timout_etimer)
		{
							//是否要考虑历史数据下载中涉及的参数：历史记录重传次数，历史记录重传超时，每次历史数据下载条数
				//超时，则继续本片下载，否则，会及时收到ACK，在解析中有停止掉
				node_running_flags.data_download_rtyn_cnt++;
				if(node_running_flags.data_download_rtyn_cnt<3)
				{
					transmit();
					etimer_set(&data_download_timout_etimer, 500 ms);			//设置超时
				}
		}
		if(ev == DATA_ERASE_DATA)
		{
			storage_empty();
			flash_tat_erase_chip_nonblock();
			post_data_download_ev(DATA_ERASE_CHECK_OVER);
		}
		if(ev == DATA_ERASE_CHECK_OVER)
		{
			led_on();
			cache_init();		
			if(flash_tat_check_idle())
			{
				flash_tat_enter_sleep();
				wdtimer_start();
			}
			else
			{
				post_data_download_ev(DATA_ERASE_CHECK_OVER);
			}
		}
		
    } 
        
    PROCESS_END();
}


void stop_data_download_timeout(void)
{
	etimer_stop(&data_download_timout_etimer);
}

void post_data_download_ev(process_event_t ev)
{
	process_post(&data_download_process, ev, NULL);
}
