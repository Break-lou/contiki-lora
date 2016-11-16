#ifndef __PMU_CONFIG_H__
#define __PMU_CONFIG_H__
#include <stdint.h>

void dcdc0_off(void);
void vdrv_off(void);
void vdrv_select_vbat(void);
void pmu_set(void);
void pmu_close(void);
void open_debug(void);
void pinwake_init(void);
void pinwake_enable(void);
void pinwake_disable(void);
void debug_output_enable(void);
void DCDC0_off(void);

void enable_pullup_from_wakeup(void);
void disable_pullup_before_sleep(void);

void DCDC_SET(uint8_t dcdc_voltage);

#define DCDC_1_25V	0
#define DCDC_1_3V	1
#define DCDC_1_35V	2
#define DCDC_1_4V	3
#define DCDC_1_45V	4
#define DCDC_1_5V	5
#define DCDC_1_55V	6
#define DCDC_1_6V	7
#define DCDC_1_65V	8
#define DCDC_1_7V	9
#define DCDC_1_75V	10
#define DCDC_1_8V	11	
#define DCDC_1_9V	12
#define DCDC_2_0V	13
#define DCDC_2_1V	14
#define DCDC_2_2V	15
#define DCDC_2_3V	16
#define DCDC_2_4V	17
#define DCDC_2_5V	18
#define DCDC_2_6V	19
#define DCDC_2_7V	20
#define DCDC_2_8V	21
#define DCDC_2_9V	22
#define DCDC_3_0V	23
#define DCDC_3_1V	24
#define DCDC_3_2V	25
#define DCDC_3_3V	26
#define DCDC_3_4V	27
#define DCDC_3_5V	28
#define DCDC_3_6V	29
#define DCDC_3_7V	30
#define DCDC_3_8V	31


#endif
