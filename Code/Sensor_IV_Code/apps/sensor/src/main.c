#include "generic_include.h"
#include "si32_system_it.h"
#include "board_cfg.h"
#include "delay.h"
#include "contiki.h"

#include "si32_system_init.h"

#include <stdio.h> 

#include "sx127x_radio.h"

#include "sys_event.h"
#include "analysis_process.h"
#include "sen_work_process.h"
#include "data_download_process.h"
//#include "sensor_sht25_process.h"
#include "cycle_work_process.h"
#include "power_manager_process.h"
//#include "sensor_co2_process.h"
#include "key_process.h"
#include "led_process.h"

#include "sensor_sixteen.h"
#include "sensor_parameter.h"
#include "wdtimer_config.h"

#include "sensor_process_include.h"
#include "system_process_include.h"

#include "power_manager.h"
#include "nhzf42.h"
#include "ds18b20_bus.h"
#include <stdlib.h>
#include "ext_flash_include.h"
#include "mlx90614.h"
#include "simulate_i2c.h"
AUTOSTART_PROCESSES(&cycle_work_process,&key_process,&led_process,
					&analysis_process,&sen_work_process,&data_download_process,
					&quick_work_process,&rf_transmit_process);	

//按行为来重新组织下代码
int main(void)
{
	// hardware initialize
	system_init_from_reset();	
	// sensor parameter initialize
	sensor_parameter_init();
	
	// rf initialize
	radio_driver_init();
	// sensor sixteen buffer initialize
	sensor_sixteen_buffer_init();
	// contiki initialize
	process_init();
	process_start(&etimer_process, NULL);
	autostart_start(autostart_processes);
	// post system_state to work
	process_post(&cycle_work_process,CHANGE_SYSTEM_STATE_TO_WORK,NULL);//CHANGE_SYSTEM_STATE_TO_WORK	
	// port match enable
	pmatch_enable();
	// start wdtimer
	wdtimer_start();
	// syns local time
	set_current_time(BEGIN_TIME);
	
	while(1)
	{
		// process manage
		while(process_run() > 0);
		// clear watchdog counter
		wdtimer_reset();
		// low power manager
		sensor_iv_low_power_manager();
	}
}




