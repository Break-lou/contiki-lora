#include "sensor_manager_process.h"
#include "sys_event.h"
#include "sensor_process_include.h"
#include "system_process_include.h"
#include <string.h>

#define MAX_SENSOR_NUM 5
#define CHECK_SENSOR_NUM(x) x<MAX_SENSOR_NUM?1:0

struct process * sensor_process[MAX_SENSOR_NUM];

void sensor_process_init(void);

uint8_t sensor_cnt = 0;

PROCESS(sensor_manager_process,"sensor_manager_process");
PROCESS_THREAD(sensor_manager_process,ev,data)
{
	PROCESS_BEGIN();
	
	sensor_process_init();
	
	while(1)
	{
		PROCESS_WAIT_EVENT();
		if(ev == SENSOR_MANAGER_START)
		{
			//开始采集
			if(sensor_process[sensor_cnt] != NULL)
			{
				process_post(sensor_process[sensor_cnt],SENSOR_PROCESS_START,NULL );
			}
		}
		if(ev == SENSOR_COLLECT_DATA_END)
		{
			//结束当前传感器采集，判断是否有下一个传感器
			sensor_cnt++;
			if(sensor_process[sensor_cnt] != NULL)
			{
				process_post(sensor_process[sensor_cnt],SENSOR_PROCESS_START,NULL );
			}
			else
			{	
				//采集结束，设置发包周期后休眠
				sensor_cnt = 0;
				switch(node_running_flags.current_work_stage)
				{
					case BROADCAST_JOIN_PAYLOAD_STAGE:
					case FULL_CYCLE_MONITOR_STAGE:		//add by yozen 2015.10.15
					case REQUEST_JOIN_PAYLOAD_STAGE:
					case TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE:
					case TRANSMIT_SENSOR_HISTORY_PAYLOAD_STAGE:
					case LISTEN_BROADCAST_STAGE:		//add by yozen 2015.10.15
						//????????
						post_cycle_work_ev(END_SAMPLE_CYCLE_WORK, NULL);	//采集周期结束
						break;
					case CONFIG_PAYLOAD_STAGE:
						//???????????
						post_sen_work_ev(SYSTEM_CHECK_MODE_SAMPLE_END);
						break;
					default:
						break;
				}
				
			}
		}
		
	}
	PROCESS_END();
	
}

void post_sensor_manager_ev(process_event_t ev)
{
	process_post(&sensor_manager_process, ev, NULL);
}

void sensor_process_init(void)
{
	switch(node_parameter.SETP)
	{
//		case SHT25_TYPE:
//			if(!process_is_running(&sensor_sht25_process))
//			{
//				process_start(&sensor_sht25_process, NULL);
//			}
//			sensor_process[0] = &sensor_sht25_process;
//			break;
//		case CO2_TYPE:
//			if(!process_is_running(&sensor_co2_process))
//			{
//				process_start(&sensor_co2_process, NULL);
//			}
//			sensor_process[0] = &sensor_co2_process;
//			break;
//		case SHT25CO2_TYPE:
//			if(!process_is_running(&sensor_sht25_process))
//			{
//				process_start(&sensor_sht25_process, NULL);
//			}
//			sensor_process[0] = &sensor_sht25_process;
//			if(!process_is_running(&sensor_co2_process))
//			{
//				process_start(&sensor_co2_process, NULL);
//			}
//			sensor_process[1] = &sensor_co2_process;
//			break;
		#if WATER_OPERATE
		case WATER_TYPE:
			if(!process_is_running(&sensor_water_power_process))
			{
				process_start(&sensor_water_power_process, NULL);
			}
			sensor_process[0] = &sensor_water_power_process;
			break;
		#endif	
			
		#if NHZF42_OPERATE
		case NHZF42_TYPE:
			if(!process_is_running(&sensor_nhzf42_process))
			{
				process_start(&sensor_nhzf42_process, NULL);
			}
			sensor_process[0] = &sensor_nhzf42_process;
			break;	
		#endif
			
		#if DS18B20_OPERATE
		case DS18B20_TYPE:
			if(!process_is_running(&sensor_ds18b20_process))
			{
				process_start(&sensor_ds18b20_process, NULL);
			}
			sensor_process[0] = &sensor_ds18b20_process;
			break;	
		#endif
			
		#if SOIL_OPERATE	
		case SOIL_MOISTURE:
			if(!process_is_running(&sensor_soil_moisture_process))
			{
				process_start(&sensor_soil_moisture_process, NULL);
			}
			sensor_process[0] = &sensor_soil_moisture_process;
			break;
		#endif
			
		#if ILLUMI_OPERATE
		case ILLUMI_TYPE:
		if(!process_is_running(&sensor_illumi_process))
		{
			process_start(&sensor_illumi_process, NULL);
		}
		sensor_process[0] = &sensor_illumi_process;
		break;
		#endif
		
		#if S_5TM_OPERATE 
		case S_5TM_TYPE:
		if(!process_is_running(&sensor_5tm_process))
		{
			process_start(&sensor_5tm_process, NULL);
		}
		sensor_process[0] = &sensor_5tm_process;
		break;
		#endif
		
		#if NHFS15_OPERATE
		case NHFS15_TYPE:
		if(!process_is_running(&sensor_nhfs15_process))
		{
			process_start(&sensor_nhfs15_process, NULL);
		}
		sensor_process[0] = &sensor_nhfs15_process;
		break;
		#endif
		#if ACA826T_OPERATE
		case ACA826T_TYPE:
		if(!process_is_running(&sensor_aca826t_process))
		{
			process_start(&sensor_aca826t_process, NULL);
		}
		sensor_process[0] = &sensor_aca826t_process;
		break;
		#endif
		#if SCA126T_OPERATE
		case SCA126T_TYPE:
		if(!process_is_running(&sensor_sca126t_process))
		{
			process_start(&sensor_sca126t_process, NULL);
		}
		sensor_process[0] = &sensor_sca126t_process;
		break;
		#endif
		#if NHZD10_OPERATE
		case NHZD10_TYPE:
		if(!process_is_running(&sensor_nhzd10_process))
		{
			process_start(&sensor_nhzd10_process, NULL);
		}
		sensor_process[0] = &sensor_nhzd10_process;
		break;
		#endif 
		#if NHUV11_OPERATE
		case NHUV11_TYPE:
		if(!process_is_running(&sensor_nhuv11_process))
		{
			process_start(&sensor_nhuv11_process, NULL);
		}
		sensor_process[0] = &sensor_nhuv11_process;
		break;
		#endif 
		#if modbus_mode
		case MODBUS_TYPE:
		if(!process_is_running(&sensor_modbus_process))
		{
			process_start(&sensor_modbus_process, NULL);
		}
		sensor_process[0] = &sensor_modbus_process; 
		break;
		#endif
		#if MLX90614_OPERATE
		case MLX90614:
		if(!process_is_running(&sensor_mlx90614_process))
		{
			process_start(&sensor_mlx90614_process, NULL);
		}
		sensor_process[0] = &sensor_mlx90614_process; 
		break;
		#endif
		#if SKD_100D_OPERATE
		case SKD_100D_TYPE:
		if(!process_is_running(&sensor_skd_100d_process))
		{
			process_start(&sensor_skd_100d_process, NULL);
		}
		sensor_process[0] = &sensor_skd_100d_process; 
		break;
		#endif
		#if LVDT_OPERATE
		case LVDT_TYPE:
		if(!process_is_running(&sensor_lvdt_process))
		{
			process_start(&sensor_lvdt_process, NULL);
		}
		sensor_process[0] = &sensor_lvdt_process; 
		break;
		#endif
		#if ROTONIC_OPERATE
		case ROTONIC_TYPE:
		if(!process_is_running(&sensor_rotonic_process))
		{
			process_start(&sensor_rotonic_process, NULL);
		}
		sensor_process[0] = &sensor_rotonic_process; 
		break;
		#endif
		default:
			break;
	}
	sensor_cnt = 0;
}

void sensor_process_exit(void)
{
	process_exit(&sensor_manager_process);
	process_exit(sensor_process[0]);

	
}

