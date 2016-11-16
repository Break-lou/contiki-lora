#include "rtc_config.h"
#include <SI32_PBCFG_A_Type.h>
#include <SI32_PBSTD_A_Type.h>
#include <SI32_PBGP_A_Type.h>
#include <si32_device.h>
#include <SI32_CLKCTRL_A_Type.h>
#include <math.h>
#include "clock_config.h"

#define RTC_ALARM0_WORKFLOW_VALUE	0xFFFFFFFF

extern clock_time_t time_36h_cycle;
int64_t real_time_offset;


void rtc_alarm0_enable(uint32_t rtc_time);
void rtc_alarm0_disable(void);
void rtc_alarm1_enable(uint32_t rtc_time);
void rtc_alarm1_disable(void);
void rtc_alarm2_enable(uint32_t rtc_time);
void rtc_alarm2_disable(void);


void rtc_set_from_reset(void)
{
	SI32_RTC_B_stop_timer(SI32_RTC_0);
	NVIC_DisableIRQ(RTC0ALRM_IRQn);
	NVIC_DisableIRQ(RTC0FAIL_IRQn);	
	SI32_RTC_B_disable_alarm0(SI32_RTC_0);  	
	SI32_RTC_B_disable_alarm1(SI32_RTC_0);  	
	SI32_RTC_B_disable_alarm2(SI32_RTC_0); 
	SI32_RTC_B_clear_alarm0_interrupt(SI32_RTC_0);
	SI32_RTC_B_clear_alarm1_interrupt(SI32_RTC_0);
	SI32_RTC_B_clear_alarm2_interrupt(SI32_RTC_0);
	SI32_PMU_A_disable_rtc0_fail_wake_event(SI32_PMU_0);
	SI32_PMU_A_disable_rtc0_alarm_wake_event(SI32_PMU_0);		
	SI32_RTC_B_start_timer_set(SI32_RTC_0);
	SI32_RTC_B_write_setcap(SI32_RTC_0, 0);
	while(SI32_RTC_B_is_timer_set_in_progress(SI32_RTC_0));	

	NVIC_ClearPendingIRQ(RTC0ALRM_IRQn);	
}
/*******************************************************************************
  * @brief  rtc_init()
  * @param  
  * @retval 
	******************************************************************************
	 @attention RTC初始化
	 *****************************************************************************
  */
void rtc_init(void)
{
	uint32_t i;
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG1_MISC0CEN_ENABLED_U32);

	rtc_set_from_reset();
	SI32_RTC_B_disable_auto_gain_control (SI32_RTC_0);
	SI32_RTC_B_enable_bias_doubler (SI32_RTC_0);
	SI32_RTC_B_enable_autostep (SI32_RTC_0);
	SI32_RTC_B_set_rtc_load_capacitance(SI32_RTC_0,10);
	SI32_RTC_B_enable_clock_out(SI32_RTC_0);
	SI32_RTC_B_enable_crystal_oscillator (SI32_RTC_0);
	SI32_RTC_B_set_clock_source_rtc (SI32_RTC_0);		//选择外部时钟

	SI32_RTC_B_enable_rtc_timer(SI32_RTC_0);

	for (i = 0; i < 70000; i++);   // Should wait 20ms here before next poll
	while(!SI32_RTC_B_is_external_oscillator_valid(SI32_RTC_0));
	while(!SI32_RTC_B_is_load_capacitance_ready(SI32_RTC_0));
	SI32_RTC_B_disable_external_pin_clock_drive(SI32_RTC_0);
	SI32_RTC_B_enable_auto_gain_control(SI32_RTC_0);
	SI32_RTC_B_disable_bias_doubler(SI32_RTC_0);
	SI32_RTC_B_enable_missing_clock_detector(SI32_RTC_0);

	SI32_RTC_B_disable_alarm0_auto_reset(SI32_RTC_0);

	SI32_RTC_B_enable_high_speed_mode(SI32_RTC_0);

	SI32_PMU_A_disable_rtc0_fail_wake_event(SI32_PMU_0);
	SI32_PMU_A_enable_rtc0_alarm_wake_event(SI32_PMU_0);	

	NVIC_ClearPendingIRQ(RTC0ALRM_IRQn);
	NVIC_ClearPendingIRQ(RTC0FAIL_IRQn);
	NVIC_EnableIRQ(RTC0ALRM_IRQn);
	SI32_RTC_B_clear_alarm0_interrupt(SI32_RTC_0);
	SI32_RTC_B_clear_alarm1_interrupt(SI32_RTC_0);
	SI32_RTC_B_clear_alarm2_interrupt(SI32_RTC_0);
	
	SI32_RTC_B_enable_alarm0_auto_reset(SI32_RTC_0);
	rtc_alarm0_enable(RTC_ALARM0_WORKFLOW_VALUE);
	rtc_alarm1_enable(0xffffffff);
	
	SI32_RTC_B_start_timer(SI32_RTC_0);
	
}
/*******************************************************************************
  * @brief get_rtc_counter_value()
  * @param  
  * @retval 当前RTC计数值
	******************************************************************************
	 @attention 获取当前RTC计数值
	 *****************************************************************************
  */
uint32_t get_rtc_counter_value()
{
	uint32_t rtc_time;
	SI32_RTC_B_start_timer_capture(SI32_RTC_0);	
	while(SI32_RTC_B_is_timer_capture_in_progress(SI32_RTC_0));
	rtc_time = SI32_RTC_B_read_setcap(SI32_RTC_0);
	
	return rtc_time;
}
/*******************************************************************************
  * @brief set_next_rtc_time()
  * @param  next_time
  * @retval 
	******************************************************************************
	 @attention 设置RTC alarm1中断计数值
	 *****************************************************************************
  */
void set_next_rtc_time(uint32_t next_time)
{	
	SI32_RTC_B_clear_alarm1_interrupt(SI32_RTC_0);
	SI32_RTC_B_write_alarm1(SI32_RTC_0, next_time);
	SI32_RTC_B_enable_alarm1(SI32_RTC_0);  	
}
/*******************************************************************************
  * @brief rtc_alarm0_enable()
  * @param  rtc_time
  * @retval 
	******************************************************************************
	 @attention 设置RTC alarm0中断计数值
	 *****************************************************************************
  */
void rtc_alarm0_enable(uint32_t rtc_time)
{
	if(!(SI32_RTC_B_is_alarm0_enabled(SI32_RTC_0)))
	{
		SI32_RTC_B_clear_alarm0_interrupt(SI32_RTC_0);
		SI32_RTC_B_write_alarm0(SI32_RTC_0, rtc_time);
		SI32_RTC_B_enable_alarm0(SI32_RTC_0);
	}
	else
	{
		SI32_RTC_B_write_alarm0(SI32_RTC_0, rtc_time);
	}
}
/*******************************************************************************
  * @brief rtc_alarm0_disable()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 禁用 RTC alarm0
	 *****************************************************************************
  */
void rtc_alarm0_disable(void)
{
	SI32_RTC_B_clear_alarm0_interrupt(SI32_RTC_0);
	SI32_RTC_B_disable_alarm0(SI32_RTC_0); 
}
/*******************************************************************************
  * @brief rtc_alarm1_enable()
  * @param  rtc_time
  * @retval 
	******************************************************************************
	 @attention 设置RTC alarm1中断计数值
	 *****************************************************************************
  */
void rtc_alarm1_enable(uint32_t rtc_time)
{
	if(!(SI32_RTC_B_is_alarm1_enabled(SI32_RTC_0)))
	{
		SI32_RTC_B_clear_alarm1_interrupt(SI32_RTC_0);
		SI32_RTC_B_write_alarm1(SI32_RTC_0, rtc_time);
		SI32_RTC_B_enable_alarm1(SI32_RTC_0);
	}
	else
	{
		SI32_RTC_B_write_alarm1(SI32_RTC_0, rtc_time);
	}
}
/*******************************************************************************
  * @brief rtc_alarm1_disable()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 禁用RTC alarm1中断计数值
	 *****************************************************************************
  */
void rtc_alarm1_disable(void)
{
	SI32_RTC_B_clear_alarm1_interrupt(SI32_RTC_0);
	SI32_RTC_B_disable_alarm1(SI32_RTC_0); 
}
/*******************************************************************************
  * @brief rtc_alarm2_enable()
  * @param  rtc_time
  * @retval 
	******************************************************************************
	 @attention 设置RTC alarm2中断计数值
	 *****************************************************************************
  */
void rtc_alarm2_enable(uint32_t rtc_time)
{
	if(!(SI32_RTC_B_is_alarm2_enabled(SI32_RTC_0)))
	{
		SI32_RTC_B_clear_alarm2_interrupt(SI32_RTC_0);
		SI32_RTC_B_write_alarm2(SI32_RTC_0, rtc_time);
		SI32_RTC_B_enable_alarm2(SI32_RTC_0);
	}
	else
	{
		SI32_RTC_B_write_alarm2(SI32_RTC_0, rtc_time);
	}	
}
/*******************************************************************************
  * @brief rtc_alarm2_disable()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 禁用RTC alarm2
	 *****************************************************************************
  */
void rtc_alarm2_disable(void)
{
	SI32_RTC_B_disable_alarm2(SI32_RTC_0); 
}
/*******************************************************************************
  * @brief get_rtc_time()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 获取RTC当前运行计数器
	 *****************************************************************************
  */
uint32_t get_rtc_time()
{
	SI32_RTC_B_start_timer_capture(SI32_RTC_0);	
	while(SI32_RTC_B_is_timer_capture_in_progress(SI32_RTC_0));
	return (SI32_RTC_B_read_setcap(SI32_RTC_0));
}
/*******************************************************************************
  * @brief get_current_time()
  * @param  
  * @retval ret_time
	******************************************************************************
	 @attention 获取运行时间
	 *****************************************************************************
  */
uint64_t get_current_time(void)
{
	int cpu_sr;
	uint32_t rtc_time;
	uint64_t ret_time;
	
	ENTER_CRITICAL_REGION();
	
	rtc_time = get_rtc_time();	
//	if(SI32_RTC_B_is_alarm0_interrupt_pending(SI32_RTC_0))
//	{
//		SI32_RTC_B_clear_alarm0_interrupt(SI32_RTC_0);
//		time_36h_cycle += 1;		
//		rtc_time = 0;
//	}
	ret_time = (((uint64_t)time_36h_cycle)<<32) + rtc_time;
	
	LEAVE_CRITICAL_REGION();
	
	return ret_time;
}
/*******************************************************************************
  * @brief set_current_time()
  * @param  time：秒单位的时间戳
  * @retval 
	******************************************************************************
	 @attention 判断复位源来设置当前时间
	 *****************************************************************************
  */
void set_current_time(uint32_t time)
{
	uint64_t set_time;
	uint64_t real_time;
	uint64_t hard_time;
	SI32_RSTSRC_Enum_Type reset_source;
	reset_source=get_reset_source();
	if(reset_source != SI32_WDT_RESET)//时间戳设定选项
	{		
		set_time = ((uint64_t)time << 15);				//整秒
		
		hard_time = get_current_time();						//当前运行的时间
		real_time = hard_time + real_time_offset;	//实时时间
		set_time |= (real_time&((uint64_t)(0x7fff)));	
		
		real_time_offset = set_time - hard_time;
	}
}
/*******************************************************************************
  * @brief set_current_time_by_mils()
  * @param  time：毫秒单位的时间戳
  * @retval 
	******************************************************************************
	 @attention 设置当前时间戳
							time*32.768;分解 1.time/1000
															 2.time<<15
	 *****************************************************************************
  */
 void set_current_time_by_mils(uint64_t time)
{
	uint64_t hard_time=0;
	uint64_t set_time=0;
	
	hard_time = get_current_time();
	set_time = (uint64_t)time*32.768;//time/1000*32768
	real_time_offset = set_time - hard_time;
}
/*******************************************************************************
  * @brief get_real_time()
  * @param  hard_time
  * @retval 
	******************************************************************************
	 @attention 获取当前时间戳 linux时间戳+设备运行时间
	 *****************************************************************************
  */
uint64_t get_real_time(void)
{
	uint64_t hard_time;
	hard_time = get_current_time();					//当前已经运行的时间
	hard_time += real_time_offset;
	return hard_time;
}
/*******************************************************************************
  * @brief get_upload_time()
  * @param  
  * @retval get_real_time()>>13 1/4秒
	******************************************************************************
	 @attention 获取当前时间戳 linux时间戳+设备运行时间的最高二位
	 *****************************************************************************
  */
uint64_t get_upload_time(void)
{
	return get_real_time()>>13;
}
/*******************************************************************************
  * @brief get_current_time_by_seconds()
  * @param  
  * @retval get_real_time()/RTC_OSA
	******************************************************************************
	 @attention 获取当前时间戳 linux时间戳
	 *****************************************************************************
  */
uint64_t get_current_time_by_seconds()
{
	return get_real_time()/RTC_OSA;
}

/*******************************************************************************
  * @brief check_current_time()
  * @param  gTime
  * @retval t()
	******************************************************************************
	 @attention 输入的时间戳和当前的时间戳的相差数
	 *****************************************************************************
  */
int64_t check_current_time(uint64_t gTime)
{
	uint64_t cur_time = get_real_time()/RTC_OSA;
	int64_t t = gTime - cur_time;
	return t;
}

