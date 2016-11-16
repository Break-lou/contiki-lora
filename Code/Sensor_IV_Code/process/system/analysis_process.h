#ifndef __ANALYSIS_PROCESS_H__
#define __ANALYSIS_PROCESS_H__



#include "contiki.h"



PROCESS_NAME(analysis_process);

//void calibrate_next_sample_start_line_by_second(uint32_t timestamp);
void calibrate_next_sample_start_line_by_mils(uint64_t timestamp);
uint32_t get_next_sample_value(void);
uint32_t get_next_transmit_value(void);
#endif
