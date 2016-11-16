#include "si32_system_init.h"
#include "generic_include.h"
#include "ext_flash_include.h"
#include "battery.h"
#include "internal_adc.h"
#include "delay.h"
#include "download_history.h"
#include "broadcast_program.h"


 void system_init_from_reset()
{
	 
	sysclk_init_from_reset();
	
	debug_output_enable();
	
	port_init();

	rstsrc_init();//使能看门狗复位
	
	DCDC_SET(DCDC_3_3V);
	
	pmu_set();    //关闭DCDC
	
	wdtimer_init();
	
	storage_init();
	
	download_data_init();
		
	broadcast_program_init();

	rtc_init();
	
	open_debug();	

	pmatch_init();//按键唤醒初始化

	internal_adc_init();
	
	battery_init();
	
	wdtimer_reset();
	wdtimer_stop();
}

