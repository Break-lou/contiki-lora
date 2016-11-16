#include "si32_system_it.h"
#include "modbus.h"
#include "sys/process.h"
#include "KEY_PROCESS.h"
#include "sys_event.h"
#include "rtc_config.h"
#include "dio_handler.h"
#include <stdio.h>
#include "nhzf42.h"
#include "sensor_nhzf42_process.h"
#include "sensor_illumi_process.h"
#include "nhfs15.h"
#include "sensor_nhfs15_process.h"
#include "sdi12.h"
#include "sensor_5TM_process.h"
#include "aca826t.h"
#include "sensor_aca826t_process.h"
#include "sca126t.h"
#include "sensor_sca126t_process.h"
#include "nhzd10.h"
#include "sensor_nhzd10_process.h"
#include "nhuv11.h"
#include "sensor_nhuv11_process.h"
#include "sensor_modbus_process.h"
#include "sensor_skd_100d_process.h"
#include "lvdt.h"
#include "rotonic.h"
#include "sensor_lvdt_process.h"
#include "SOIL_TEMP_HUMIDITY_TRANSMIT_OPERATE_PROCESS.h"
#include "debug_util.h"
extern uint8_t nhzf42_recv_buff[];
extern uint8_t nhfs15_recv_buff[];
extern uint8_t aca826t_recv_buff[];
extern uint8_t sca126t_recv_buff[];
extern uint8_t sdi_recv_buff[];
extern uint8_t nhzd10_recv_buff[];
extern uint8_t nhuv11_recv_buff[];
extern uint8_t tm_flag;
extern modbus_structure aca_modbus;
extern modbus_structure sensor_modbus;
static volatile clock_time_t current_clock = 0;
clock_time_t time_36h_cycle = 0;
uint8_t (*uart_recv_option)(uint8_t data);
void halt(void)
{
	while(1);
}

void SysTick_Handler(void)
{

}

void NMI_Handler(void)
{
	halt();
}

void HardFault_Handler(void)
{
	if (CoreDebug->DHCSR & 1) {  //check C_DEBUGEN == 1 -> Debugger Connected  
		__breakpoint(0);  // halt program execution here         
	}  
	halt();
}

void MemManage_Handler(void)
{
	halt();
}

void BusFault_Handler(void)
{
	halt();
}

void UsageFault_Handler(void)
{
	halt();
}

void RTC0ALRM_IRQHandler(void)
{
	if (SI32_RTC_B_is_alarm0_interrupt_pending(SI32_RTC_0) & SI32_RTC_B_is_alarm0_enabled(SI32_RTC_0))     
	{
		//alarm0中断
		SI32_RTC_B_clear_alarm0_interrupt(SI32_RTC_0);
		time_36h_cycle++;
	}
	if (SI32_RTC_B_is_alarm1_interrupt_pending(SI32_RTC_0) & SI32_RTC_B_is_alarm1_enabled(SI32_RTC_0))  
	{
		//alarm1中断
		SI32_RTC_B_clear_alarm1_interrupt(SI32_RTC_0);
		current_clock = get_rtc_counter_value();
		if(etimer_pending() && etimer_next_expiration_time() <= current_clock) 
		{
			printf("alarm1 interrupt... \n");
			etimer_request_poll();	
		}
		else
		{
			printf("etimer not request poll... \n");
		}
	}
}

void RTC0FAIL_IRQHandler(void)
{
	while(1);
}
void PMATCH_IRQHandler(void)
{
	uint32_t button_pol, dio0_pol;
	uint16_t pw_pol;
	
	NVIC_DisableIRQ(PMATCH_IRQn);
	NVIC_ClearPendingIRQ(PMATCH_IRQn);
	SI32_PMU_A_clear_wakeup_flags(SI32_PMU_0);
	
	if(SI32_PMU_A_is_pin_wakeup_event_flag_set(SI32_PMU_0))
	{
		pw_pol = SI32_PMU_A_read_pwpol(SI32_PMU_0);
		button_pol = SI32_PBSTD_A_read_pin(BUTTON_PORT, BUTTON_PIN_NUM);
		dio0_pol = SI32_PBSTD_A_read_pin(LORA_DIO0_PORT, LORA_DIO0_PIN_NUM);
		
		if(button_pol && ((pw_pol&BUTTON_WAKE_SOURCE) == 0))
		{
			//高电平触发,按下按键
			process_post_synch(&key_process,KEY_PRESS_EVENT,NULL);		//产生KEY_PRESS_EVENT
		}
		if(dio0_pol && ((pw_pol&LORA_DIO0_WAKE_SOURCE) == 0))
		{
			//高电平触发,DIO0中断
			DIO0_handler();
		}
		
	}
	
	NVIC_ClearPendingIRQ(PMATCH_IRQn);
	SI32_PMU_A_clear_wakeup_flags(SI32_PMU_0);
	NVIC_EnableIRQ(PMATCH_IRQn);
	
}

//void TIMER0H_IRQHandler(void)
//{
//	NVIC_ClearPendingIRQ(TIMER0H_IRQn);
//	NVIC_DisableIRQ(TIMER0H_IRQn);	
//	SI32_TIMER_A_disable_high_overflow_interrupt(SI32_TIMER_0);
//	SI32_TIMER_A_stop_high_timer(SI32_TIMER_0);
//	
//	uart_rx_disable();
//	SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
//	SI32_UART_B_flush_rx_fifo(SI32_UART_0);	
//	process_post(&sensor_modbus_process,PROCESS_CHECK_EVENT,NULL);
//}

void WDTIMER0_IRQHandler(void)
{
	if ((SI32_WDTIMER_A_is_early_warning_interrupt_pending(SI32_WDTIMER_0) & SI32_WDTIMER_A_is_early_warning_interrupt_enabled(SI32_WDTIMER_0)))
   	{
		SI32_WDTIMER_A_clear_early_warning_interrupt (SI32_WDTIMER_0);
   	}
}
uint8_t uart_rx_value;
void UART0_IRQHandler(void)
{
	if(SI32_PMU_A_is_uart_wakeup_flag_set(SI32_PMU_0))
	{
		//SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_0, UART0_RX_PIN);
		SI32_PMU_A_clear_wakeup_flags(SI32_PMU_0);
		SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);		
	//	SI32_PBSTD_A_write_pins_high(SI32_PBSTD_0,PBX_7);
	}
	if(SI32_UART_B_is_tx_data_request_interrupt_pending(SI32_UART_0) && SI32_UART_B_is_tx_data_request_interrupt_enabled(SI32_UART_0))
	{
		
	}
	if(SI32_UART_B_is_rx_data_request_interrupt_pending(SI32_UART_0)&& SI32_UART_B_is_rx_data_request_interrupt_enabled(SI32_UART_0))
	{
		SI32_UART_B_clear_rx_data_request_interrupt(SI32_UART_0);
		uart_rx_value = SI32_UART_B_read_data_u8(SI32_UART_0);
		
		#if NHZF42_OPERATE
		if(node_parameter.SETP==NHZF42_TYPE)
		{
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
			if(uart_recv_option(uart_rx_value)==1)
			{
				uart_rx_disable();
				SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
				SI32_UART_B_flush_rx_fifo(SI32_UART_0);
				process_post(&sensor_nhzf42_process,PROCESS_RECEIVE_COMPLETE_EVENT,&nhzf42_recv_buff);
			}
		}
		#endif
		
		#if S_5TM_OPERATE 	
		if(node_parameter.SETP==S_5TM_TYPE)
		{
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);	
			if(uart_recv_option(uart_rx_value)==1)
			{
				uart_rx_disable();
				SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
				SI32_UART_B_flush_rx_fifo(SI32_UART_0);
				if(tm_flag==0)
				{
						process_post(&sensor_5tm_process,PROCESS_RECEIVE_MEASURE_COMPLETE_EVENT,&sdi_recv_buff);
						tm_flag=1;
				}
				else if(tm_flag==1)
				{
						process_post(&sensor_5tm_process,PROCESS_RECEIVE_DATA_COMPLETE_EVENT,&sdi_recv_buff);
						tm_flag=0;
				}
				else if(tm_flag==3)
				{
						process_post(&sensor_5tm_process,PROCESS_RECEIVE_QUERY_ADDRESS_EVENT,&sdi_recv_buff);
						tm_flag=0;//默认为0
				}
				else if(tm_flag==4)
				{
						process_post(&sensor_5tm_process,PROCESS_RECEIVE_CHANGE_ADDRESS_EVENT,&sdi_recv_buff);
				}
			}
		}
		#endif
		
		#if ILLUMI_OPERATE
		if(node_parameter.SETP==ILLUMI_TYPE)
		{
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);		
			if(uart_recv_option(uart_rx_value)==1)
			{
				SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
				SI32_UART_B_flush_rx_fifo(SI32_UART_0);
				process_post(&sensor_illumi_process, UART_RECEIVE_DATA_OVER, NULL);
			}
		}
		#endif
		
		#if NHFS15_OPERATE
		if(node_parameter.SETP==NHFS15_TYPE)	
		{
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
			if(nhfs15_analyster(uart_rx_value)==1)
			{
				uart_rx_disable();
				SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
				SI32_UART_B_flush_rx_fifo(SI32_UART_0);
				process_post(&sensor_nhfs15_process,PROCESS_RECEIVE_COMPLETE_EVENT,&nhfs15_recv_buff);
			}
		}
		#endif
		#if NHZD10_OPERATE
		if(node_parameter.SETP==NHZD10_TYPE)	
		{
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
			if(nhzd10_analyster(uart_rx_value)==1)
			{
				uart_rx_disable();
				SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
				SI32_UART_B_flush_rx_fifo(SI32_UART_0);
				process_post(&sensor_nhzd10_process,PROCESS_RECEIVE_COMPLETE_EVENT,&nhzd10_recv_buff);
			}
		}
		#endif
		#if NHUV11_OPERATE
		if(node_parameter.SETP==NHUV11_TYPE)	
		{
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
			if(nhuv11_analyster(uart_rx_value)==1)
			{
				uart_rx_disable();
				SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
				SI32_UART_B_flush_rx_fifo(SI32_UART_0);
				process_post(&sensor_nhuv11_process,PROCESS_RECEIVE_COMPLETE_EVENT,&nhuv11_recv_buff);
			}
		}
		#endif
		#if ACA826T_OPERATE
		if(node_parameter.SETP==ACA826T_TYPE)	
		{
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
		//	modbus_receive(uart_rx_value,&aca_modbus)==1
			if(aca826t_analyster(uart_rx_value)==1)
			{
				uart_rx_disable();
				SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
				SI32_UART_B_flush_rx_fifo(SI32_UART_0);
				process_post(&sensor_aca826t_process,PROCESS_RECEIVE_COMPLETE_EVENT,&aca_modbus);
			}
		}
		#endif
		#if SCA126T_OPERATE
		if(node_parameter.SETP==SCA126T_TYPE)	
		{
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
			if(sca126t_analyster(uart_rx_value)==1)
			{
				uart_rx_disable();
				SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
				SI32_UART_B_flush_rx_fifo(SI32_UART_0);
				process_post(&sensor_sca126t_process,PROCESS_RECEIVE_COMPLETE_EVENT,&sca126t_recv_buff);
			}
		}
		#endif
		
		#if modbus_mode
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
			modbus_receive(uart_rx_value,&sensor_modbus);
//			if(modbus_receive(uart_rx_value,&sensor_modbus)==0)
//			{
//				uart_rx_disable();
//				SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
//				SI32_UART_B_flush_rx_fifo(SI32_UART_0);			
//				
//			}
		#endif
		#if SKD_100D_OPERATE
		if(node_parameter.SETP==SKD_100D_TYPE)
		{
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
			if(uart_recv_option(uart_rx_value)==1)
			{
				uart_rx_disable();
				SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
				SI32_UART_B_flush_rx_fifo(SI32_UART_0);
				process_post(&sensor_skd_100d_process,PROCESS_RECEIVE_COMPLETE_EVENT,NULL);
			}
		}
		#endif
		#if LVDT_OPERATE
		if(node_parameter.SETP==LVDT_TYPE)
		{
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
			lvdt_analyster(uart_rx_value);
		}
		#endif
		#if ROTONIC_OPERATE
		if(node_parameter.SETP==ROTONIC_TYPE)
		{
			SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
			rotonic_rec_data(uart_rx_value);
		}
		#endif
//		else if(node_parameter.SETP==CO2_TYPE)
//		{
//			co2_analyster(uart_rx_value);
//		}
		
	}
	if(SI32_UART_B_is_tx_fifo_error_interrupt_pending(SI32_UART_0))
	{
		SI32_UART_B_clear_tx_fifo_error_interrupt(SI32_UART_0);
	}
}



