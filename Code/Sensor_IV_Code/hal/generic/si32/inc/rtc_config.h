#ifndef __RTC_CONFIG_H__
#define __RTC_CONFIG_H__



#include "board_cfg.h"
#include <SI32_RTC_B_Type.h>
#include <SI32_PMU_A_Type.h>

#include "si32_system_it.h"

void rtc_init(void);
uint32_t get_rtc_counter_value(void);
void rtc_alarm1_enable(uint32_t rtc_time);
void rtc_alarm1_disable(void);
void rtc_alarm2_disable(void);
void rtc_alarm2_enable(uint32_t rtc_time);

uint32_t get_rtc_time(void);
void set_next_rtc_time(uint32_t next_time);

uint64_t get_current_time(void);
void set_current_time(uint32_t time);
void set_current_time_by_mils(uint64_t set_time);
uint64_t get_real_time(void);
uint64_t get_upload_time(void);
int64_t check_current_time(uint64_t gTime);
uint64_t get_current_time_by_seconds(void);



#endif
