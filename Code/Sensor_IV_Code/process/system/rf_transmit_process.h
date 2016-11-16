#ifndef __RF_SEND_PROCESS_H__
#define __RF_SEND_PROCESS_H__





#include "contiki.h"



PROCESS_NAME(rf_transmit_process);
#define OPERATE_RF OPERATE_LORA
#define DIS_OPERATE_RF DIS_OPERATE_LORA

void post_rf_transmit_ev(process_event_t ev, process_data_t data);
void data_retransmit_event(void);


void transmit_sensor_data_timeout_event(void);
void transmit_sensor_history_payload_timeout_event(void);

void stop_rf_transmit_timeout_etimer(void);
void stop_rf_transmit_moment_etimer(void);
void stop_rf_listen_broadcast_etimer(void);
void stop_rf_transmit_duration_etimer(void);
void stop_rf_transmit_start_line_etimer(void);
void stop_rf_random_transmit_etimer(void);

void save_sensor_data_from_ram_to_flash(void);

#endif
