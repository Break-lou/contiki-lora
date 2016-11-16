#include "power_manager_process.h"
#include "generic_include.h"
#include "sx127x_radio.h"
#include "sensor_parameter.h"
#include "power_manager.h"
#include "system_process_include.h"
#include <stdio.h>

//功耗管理线程

PROCESS(power_manager_process, "power_manager_process");

PROCESS_THREAD(power_manager_process,ev,data)
{
	PROCESS_BEGIN();

	while(1)
	{
		PROCESS_WAIT_EVENT();
		
		if(ev == POWER_MANAGER_LORA_SLEEP)
		{
			node_running_flags.goto_sleep = true;
			RadioDriver.Sleep();
			if(node_running_flags.sensor_system_state == SYSTEM_STATE_WORK)
			{
				//在工作阶段数据阶段
				if(!node_running_flags.begin_sample)
				{
					//如果不在采集
					if(!check_sample_is_expired())
					{
						//如果采集定时还没到期
						if(check_sample_etime())
						{
							//对比下一次采集时间与当前时间
							process_post(&power_manager_process, POWER_MANAGER_PM8, NULL);
						}
					}
					else
					{
						printf("sample time is expired... \n");
					}
				}
				else
				{
					printf("current sensor is sampling... \n");
				}
			}
			else
			{
				process_post(&power_manager_process, POWER_MANAGER_PM8, NULL);
			}
		}
		if(ev == POWER_MANAGER_PM8)
		{
			printf("into deep sleep... \n");
			enter_deep_sleep();
		}
		if(ev == POWER_MANAGER_PM8_WITH_SHT25)
		{
			RadioDriver.Sleep();
			enter_deep_sleep_with_sht25();
		}
		if(ev == POWER_MANAGER_PM8_WITH_RF)
		{
			enter_deep_sleep_with_rf();
		}
		if(ev == POWER_MANAGER_PM8_WITH_CO2)
		{
			RadioDriver.Sleep();
			enter_deep_sleep_with_co2();
		}
	}
	
	PROCESS_END();
}

void post_power_manager_ev(process_event_t ev)
{
	process_post(&power_manager_process,ev,NULL);	
}

