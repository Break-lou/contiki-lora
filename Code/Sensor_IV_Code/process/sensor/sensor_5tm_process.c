#include "sensor_5TM_process.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sensor_sixteen.h"
#include "battery.h"
#include "board_cfg.h"
#include "pmu_config.h"
#include "delay.h"
#include "sensor_parameter.h"
#include "data_conversion.h"
#include "sx127x_radio.h"
#include "sensor_process_include.h"
#include "system_process_include.h"
#include "AT_OPERATION.h"
#include "sensor_payload.h"
#include "power_manager.h"
#include "uart.h"
#include <stdio.h>
#include "sdi12_include.h"
#include "delay.h"
#define SENSOR_5TM_TYPE 		0x03
uint8_t SENSOR_5TE_OR_5TM_DATA_TYPE=0x25;//0x0a

#if S_5TM_OPERATE 
#define PARAM_VALID_5TM_VALUE 0X20160226
extern uint8_t (*uart_recv_option)(uint8_t data);



//void send_s_5TM_value(uint16_t s_5TM_value);
void waiting_power_s_5tm(void);
void s_5tm_sample_event(void);
void s_5tm_sample_collect(void);
void s_5tm_sample_data_collect(void);
void s_5tm_query_address(void);
void s_5tm_change_address(void);
void s_5tm_add(uint8_t *data);
void s_5tm_del(uint8_t *data);
uint8_t s_5tm_analyster(uint8_t data);						
struct etimer s_5tm_power_wait_etimer;
struct etimer s_5tm_receive_timeout_etimer;
struct etimer s_5tm_wait_etimer,s_5tm_wait_next_etimer,s_5tm_wait_second_etimer;
struct etimer s_5tm_setup_return_etimer;
uint8_t temp_s_5tm_value[12];
uint8_t battery_5tm;
uint8_t data_5tm_setup;
sdi_data_type s_5tm_data;

#define S_5TM_FAIL_MAX_NUM 3
uint8_t receive_5tm_fail_cnt=0;
#define OPEN_5TM_SENSOR_POWER			SI32_PBSTD_A_set_pins_push_pull_output( SI32_PBSTD_3,  PBX_3); \
																	SI32_PBSTD_A_write_pins_high( SI32_PBSTD_3,  PBX_3)

#define CLOSE_5TM_SENSOR_POWER	  SI32_PBSTD_A_set_pins_push_pull_output( SI32_PBSTD_3,  PBX_3); \
																	SI32_PBSTD_A_write_pins_low( SI32_PBSTD_3,  PBX_3)


typedef enum
{
	s_5tm_status_init = 1,
	s_5tm_status_power_on,
	s_5tm_status_collect,
	s_5tm_status_end,
	s_5tm_status_calibrate
}s_5tm_status_t;

static s_5tm_status_t s_5tm_work_status = s_5tm_status_init;
measure_type measure_data;
uint8_t tm_flag=3;
extern uint8_t sdi12_address;
PROCESS(sensor_5tm_process,"sensor_s_5TM_process");
PROCESS_THREAD(sensor_5tm_process,ev,data)
{
	PROCESS_BEGIN();
	uart_port_configuration();
	SDI12_MARKING();
	sdi12_param_init();

	s_5tm_work_status = s_5tm_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					#if DEBUG_PRINT
						printf("s_5TM sensor start power on... \n");
					#endif
					battery_5tm = battery_sample_data();
					s_5tm_work_status = s_5tm_status_power_on;	
					uart_rx_disable();
					//如果在标定情况下，计数值超过或等于数组长度，则清零
					if((node_parameter.valid_5tm == PARAM_VALID_5TM_VALUE)&&(node_parameter.channel_cnt>=node_parameter.channel_len))
					{
							node_parameter.channel_cnt=0;
					}
					//若没有设置过则按查询，测量，采集的流程进行数据采集
					if(node_parameter.valid_5tm != PARAM_VALID_5TM_VALUE)//是否标定过
					{
						//没有标定过
						node_parameter.channel_len=1;
						node_parameter.channel_cnt=0;
						node_parameter.channel_num=0;
						tm_flag=3;
					}
					else//标定过的，则按序号轮询进行测量，采集进行数据采集
					{
						//计数器是否超过数组长度
						if(node_parameter.channel_cnt<node_parameter.channel_len)
						{
							//由于删除等一些检测出数组存放序列号出错，则跳过该值并计数器加一，直至采集完成
							if(node_parameter.channel[node_parameter.channel_cnt]==0)
							{
									node_parameter.channel_cnt++;
									temp_s_5tm_value[0]=0xff;
									memset(temp_s_5tm_value+1,0,6);
									sensor_sixteen_buffer_put(SENSOR_5TM_TYPE, SENSOR_5TE_OR_5TM_DATA_TYPE, node_parameter.MAC,
															temp_s_5tm_value, 7, battery_5tm, node_running_flags.sensor_sample_time);
									if(node_parameter.channel_cnt<node_parameter.channel_len)
									{
										process_post(&sensor_5tm_process,SENSOR_PROCESS_START,NULL);
									}
									else
									{
										s_5tm_sample_event();
									}
									return 0;							
							}
							//将相对应的数组里的标号传给缓存
							sdi12_address=node_parameter.channel[node_parameter.channel_cnt];		
							tm_flag=0;//直接测量命令，不能进行查询命令
							
					   }
						else
							return 0;
					 }
//						uart_recv_option=sdi12_analyster;	
//						uart_rx_enable();					
					OPEN_5TM_SENSOR_POWER;	//5TM??
					
					waiting_power_s_5tm();				
				}
				if( (ev==PROCESS_SDI12_START)||(ev == PROCESS_EVENT_TIMER && data == &s_5tm_power_wait_etimer))
				{
					
					SDI12_BREAK();	
					etimer_set(&s_5tm_wait_etimer, 16 ms);
				}
				if( ev == PROCESS_EVENT_TIMER && data == &s_5tm_wait_etimer)
				{

					SDI12_MARKING();
					etimer_set(&s_5tm_wait_next_etimer, 9 ms);
				}
				if( ev == PROCESS_EVENT_TIMER && data == &s_5tm_wait_next_etimer)
				{		
					if(tm_flag==0)
					{
							s_5tm_sample_collect();//测量数据命令
					}
					else if(tm_flag==1)
					{
							s_5tm_sample_data_collect();//采集数据命令
					}						
					else if(tm_flag==3)
					{
							s_5tm_query_address();//查传感器编号命令
					}
					else if(tm_flag==4)
					{
							s_5tm_change_address();//更改传感器编号命令
					}
						
				}			
				if(ev==PROCESS_RECEIVE_QUERY_ADDRESS_EVENT)//搜寻地址
				{
						etimer_stop(&s_5tm_receive_timeout_etimer);
						//在标定下先搜寻传感器的编号是否与设置的相同
						if(s_5tm_work_status == s_5tm_status_calibrate)
						{
								uint8_t i=node_parameter.channel_num;	
								//不同则发送更改命令，相同直接结束
								if(sdi12_address_response(data)!=node_parameter.channel[i])
								{
										tm_flag=4;
										process_post(&sensor_5tm_process,PROCESS_SDI12_START,NULL);
										//设置地址
								}
								else
								{
										tm_flag=0;
										node_parameter.channel_cnt++;//计数值加一
										s_5tm_work_status = s_5tm_status_power_on;
										data_5tm_setup=add_data_ok;
										etimer_set(&s_5tm_setup_return_etimer,100 ms);
										
								}
								
						}
						//对于单个未标号的设备要先访问传感器的编号
						else
						{
							node_parameter.channel[node_parameter.channel_num]=sdi12_address_response(data);
							process_post(&sensor_5tm_process,PROCESS_SDI12_START,NULL);	
						}
				}
				if(ev==PROCESS_RECEIVE_CHANGE_ADDRESS_EVENT)
				{
						etimer_stop(&s_5tm_receive_timeout_etimer);
						//更副嗪拍后通过返回命令来确认是否成功
						if(sdi12_address_response(data)==node_parameter.channel[node_parameter.channel_num])
						{
						//	node_parameter.channel_cnt++;//计数值加一		
							uint8_t channel_cnt=node_parameter.channel_cnt;
							uint8_t channel_num=node_parameter.channel_num;
							node_parameter.channel_cnt=0;
							node_parameter.channel_num=0;
							update_sysparam();//存入flash
							node_parameter.channel_cnt=channel_cnt;
							node_parameter.channel_num=channel_num;
							data_5tm_setup=add_data_ok;
							etimer_set(&s_5tm_setup_return_etimer,100 ms);
							
						}
						else
						{
							data_5tm_setup=data_add_error;
							etimer_set(&s_5tm_setup_return_etimer,100 ms);
						}
						tm_flag=0;
						s_5tm_work_status = s_5tm_status_power_on;
				}
				if(ev==PROCESS_RECEIVE_MEASURE_COMPLETE_EVENT)//测量测试
				{
						etimer_stop(&s_5tm_receive_timeout_etimer);
						measure_data=sdi12_measure_response(data);
						etimer_set(&s_5tm_wait_second_etimer, measure_data.time s);
				}
				if( ev == PROCESS_EVENT_TIMER && data == &s_5tm_wait_second_etimer)
				{		
						process_post(&sensor_5tm_process,PROCESS_SDI12_START,NULL);				
				}
				////////////////////////////////////////////////////////////
				if(ev==PROCESS_RECEIVE_DATA_COMPLETE_EVENT)//完成数据
				{
						etimer_stop(&s_5tm_receive_timeout_etimer);
						s_5tm_data=sdi12_data_response(data);
						s_5tm_work_status = s_5tm_status_collect;
						process_post(&sensor_5tm_process,PROCESS_RECEIVE_COMPLETE_EVENT,NULL);
				}
				//超时重新发送
				if( ev == PROCESS_EVENT_TIMER && data == &s_5tm_receive_timeout_etimer)
				{	
					//在标定的时候如果访问超时。则根据之前的状态继续访问
					if(s_5tm_work_status == s_5tm_status_calibrate)
					{
						if(receive_5tm_fail_cnt >= S_5TM_FAIL_MAX_NUM)
						{						
								data_5tm_setup=time_out;
								etimer_set(&s_5tm_setup_return_etimer,10 ms);
								node_parameter.channel[node_parameter.channel_num]=0;
								receive_5tm_fail_cnt=0;
						}
						else
						{
								process_post(&sensor_5tm_process,PROCESS_SDI12_START,NULL);	
								receive_5tm_fail_cnt++;
						}
					}
					else 
					{
						//访问数据出错，则返回出错数据包
						if(receive_5tm_fail_cnt >= S_5TM_FAIL_MAX_NUM)
						{						
								sensor_sixteen_buffer_put(SENSOR_5TM_TYPE, 0xf3, node_parameter.MAC,
															temp_s_5tm_value, 7, battery_5tm, node_running_flags.sensor_sample_time);
								node_parameter.channel_cnt++;							
								if(node_parameter.channel_cnt<node_parameter.channel_len)
								{
									process_post(&sensor_5tm_process,SENSOR_PROCESS_START,NULL);	
								}
								else
								{
									
									s_5tm_sample_event();
									receive_5tm_fail_cnt=0;
								}
								
						}
						else
						{
								
								//tm_flag=0;
								CLOSE_5TM_SENSOR_POWER;
								process_post(&sensor_5tm_process,SENSOR_PROCESS_START,NULL);	
								receive_5tm_fail_cnt++;
						}
					}
				}
				if( ev == PROCESS_RECEIVE_COMPLETE_EVENT)	
				{	
						
						DIS_OPERATE_5TM;
						ENABLE_LOW_POWER;		//不断电					
						if(s_5tm_work_status == s_5tm_status_collect)
						{				
																
								if(s_5tm_data.dielectric == 0xFFFF&&s_5tm_data.dielectric ==0
								 &&s_5tm_data.Temperature == 0xFFFF&&s_5tm_data.Temperature ==0	)
								{
										receive_5tm_fail_cnt++;
										if(receive_5tm_fail_cnt >= S_5TM_FAIL_MAX_NUM)
										{
												sensor_sixteen_buffer_put(SENSOR_5TM_TYPE, 0xf4, node_parameter.MAC,
															temp_s_5tm_value, 7, battery_5tm, node_running_flags.sensor_sample_time);	
												receive_5tm_fail_cnt=0;
												s_5tm_sample_event();
										}else{
												CLOSE_5TM_SENSOR_POWER;
												process_post(&sensor_5tm_process,SENSOR_PROCESS_START,NULL);	
												receive_5tm_fail_cnt++;
										}
								 }
								 else
								 {

											receive_5tm_fail_cnt = 0;
											temp_s_5tm_value[0]=sdi12_address;
											//s_5tm_data.humidity=s_5tm_data.humidity/pow(10,s_5tm_data.dp3_num)*pow(10,s_5tm_data.dp3_num)+s_5tm_data.humidity%pow(10,s_5tm_data.dp3_num)/(pow(10,s_5tm_data.dp3_num)/100)*(pow(10,s_5tm_data.dp3_num)/100);
											//temp_s_5tm_value[6] = s_5tm_data.dp3;
											//temp_s_5tm_value[6] = s_5tm_data.dp3_num;
											temp_s_5tm_value[1] = s_5tm_data.humidity&0xff;//湿度
											temp_s_5tm_value[2] = (s_5tm_data.humidity>>8)&0xff;
									 
											if(s_5tm_data.FLAG_5TE_OR_5TM==3)
											{
												//temp_s_5tm_value[0] = s_5tm_data.dp1;
												//temp_s_5tm_value[0] = s_5tm_data.dp1_num;
												temp_s_5tm_value[3] = s_5tm_data.dielectric&0xff;//电导率
												temp_s_5tm_value[4] = (s_5tm_data.dielectric>>8)&0xff;
												
												s_5tm_data.Temperature=s_5tm_data.Temperature*2;
												s_5tm_data.Temperature+=s_5tm_data.dp2;
												//temp_s_5tm_value[4] = s_5tm_data.dp2;
												//temp_s_5tm_value[3] = s_5tm_data.dp2_num;
												temp_s_5tm_value[5] = s_5tm_data.Temperature&0xff;//温度
												temp_s_5tm_value[6] = (s_5tm_data.Temperature>>8)&0xff;
												SENSOR_5TE_OR_5TM_DATA_TYPE=0x25;
											}
											else if(s_5tm_data.FLAG_5TE_OR_5TM==2)
											{
													s_5tm_data.dp2 = s_5tm_data.dp1;
													s_5tm_data.dp2_num = s_5tm_data.dp1_num;
													s_5tm_data.Temperature = s_5tm_data.dielectric&0xffff;		
												
													s_5tm_data.Temperature=s_5tm_data.Temperature*2;
													s_5tm_data.Temperature+=s_5tm_data.dp2;
													temp_s_5tm_value[3] = s_5tm_data.Temperature&0xff;//温度
													temp_s_5tm_value[4] = (s_5tm_data.Temperature>>8)&0xff;
													SENSOR_5TE_OR_5TM_DATA_TYPE=0x0a;										
											}
											sensor_sixteen_buffer_put(SENSOR_5TM_TYPE, SENSOR_5TE_OR_5TM_DATA_TYPE, node_parameter.MAC,
															temp_s_5tm_value, 7, battery_5tm, node_running_flags.sensor_sample_time);				 
											//CLOSE_5TM_SENSOR_POWER;	
											//ENABLE_LOW_POWER;		
											node_parameter.channel_cnt++;
											if(node_parameter.channel_cnt<node_parameter.channel_len)
											{
												process_post(&sensor_5tm_process,SENSOR_PROCESS_START,NULL);	
											}
											else
											{
												s_5tm_sample_event();
											}
									 }
							#if DEBUG_PRINT
								printf("s_5TM Temperature_value: %d s_5TM humidity_value: %d	s_5TM dielectric_value: %d \n", s_5tm_data.Temperature,s_5tm_data.humidity,s_5tm_data.dielectric);
							#endif
							}	
				}	
				if(ev==PROCESS_SENSOR_NUM_CFG)
				{
					if(*(uint8_t *)data>sizeof(node_parameter.channel))//总过标记的数量不能超过数组的长度
					{					
						data_5tm_setup=num_len_overflow;
						etimer_set(&s_5tm_setup_return_etimer,100 ms);			
					}
					else
					{
						node_parameter.channel_len=*(uint8_t *)data;
						//node_parameter.channel[sizeof(node_parameter.channel)-2]=0;
						s_5tm_work_status = s_5tm_status_calibrate;
						update_sysparam();
						data_5tm_setup=num_set_ok;
						etimer_set(&s_5tm_setup_return_etimer,100 ms);
					}		
				}
				if(ev==PROCESS_SENSOR_NUM_SET)
				{
					s_5tm_add((uint8_t *)data);				
				}
				if(ev==PROCESS_SENSOR_NUM_DEL)
				{
					s_5tm_del((uint8_t *)data);				
				}
				if( ev == PROCESS_EVENT_TIMER && data == &s_5tm_setup_return_etimer)
				{
					send_set_5tm_ack(data_5tm_setup);
					
				}
	}		
	PROCESS_END();
}
//输入的数据为数值
void post_5tm_cfg(uint8_t *data)
{
	OPEN_5TM_SENSOR_POWER;
	if(node_parameter.valid_5tm != PARAM_VALID_5TM_VALUE)//第一次的话先清零
	{
		node_parameter.valid_5tm=PARAM_VALID_5TM_VALUE;
		memset(node_parameter.channel,0,sizeof(node_parameter.channel));
		node_parameter.channel_cnt=0;
		node_parameter.channel_len=0;
		node_parameter.channel_num=0;
		//copy_sysparam_to_flash((uint8_t *)&node_parameter);
	}
	process_post(&sensor_5tm_process,PROCESS_SENSOR_NUM_CFG,(uint8_t *)data);
}
//输入的数据为ASCII码
void post_5tm_add(uint8_t *data)
{
	process_post(&sensor_5tm_process,PROCESS_SENSOR_NUM_SET,(uint8_t *)data);
}
void s_5tm_add(uint8_t *data)
{
	uint8_t i=0,cnt;
	OPEN_5TM_SENSOR_POWER;
	//从已有的数组中找到空缺位
	for(i=0;i<(node_parameter.channel_len);i++)
	{
		 if(node_parameter.channel[i]==0)
		 {
			 break;
		 }
	}
	
	//没有空缺位置
	if(i>=node_parameter.channel_len)
	{
		 data_5tm_setup=add_data_len_error;
		 etimer_set(&s_5tm_setup_return_etimer,100 ms);
		 return;
	}
	//增加编号不在范围内则返回错误
	if(((*data)<0x30)||(((*data)>0x39)&&((*data)<0x41))||(((*data)>0x5a)&&((*data)<0x61))||((*data)>0x7a))
	{
			data_5tm_setup=add_data_error;
		  etimer_set(&s_5tm_setup_return_etimer,100 ms);
			return;
	}
	//增加编号是否已存在  
	for(cnt=0;cnt<(node_parameter.channel_len);cnt++)
	{
		if((*data)==node_parameter.channel[cnt])
		{
			data_5tm_setup=add_data_repeat;
		  etimer_set(&s_5tm_setup_return_etimer,100 ms);
			return;
		}
	}
	//是否有位置空余
//	if(node_parameter.channel_cnt>(node_parameter.channel_len-1))
//	{
//		delayXms(100);
//		send_set_5tm_ack(add_data_len_error);
//		return;
//	}
	node_parameter.channel[i]=*data;//存储地址
	node_parameter.channel_num=i;
	tm_flag=3;		
	//搜寻当前地址
	
	s_5tm_work_status = s_5tm_status_calibrate;
	process_post(&sensor_5tm_process,PROCESS_SDI12_START,NULL);
	 
}
//删除编号
void s_5tm_del(uint8_t *data)
{
		uint8_t i=0;
		for(i=0;i<(node_parameter.channel_len);i++)
		{
			 if(node_parameter.channel[i]==*data)
			 {
				 node_parameter.channel[i]=0;
				 //node_parameter.channel_cnt--;
				 update_sysparam();
				 data_5tm_setup=del_data_ok;
				 etimer_set(&s_5tm_setup_return_etimer,100 ms);
				 return;
			 }
		}
		data_5tm_setup=data_del_error;
		etimer_set(&s_5tm_setup_return_etimer,100 ms);

}
void post_5tm_del(uint8_t *data)
{
	process_post(&sensor_5tm_process,PROCESS_SENSOR_NUM_DEL,(uint8_t *)data);
}
void s_5tm_change_address(void)
{
		uart_recv_option=sdi12_receive;
		sdi12_change_address(sdi12_address,node_parameter.channel[node_parameter.channel_num]);
		s_5tm_uart_enable_wake_event();
		etimer_set(&s_5tm_receive_timeout_etimer, 3 s);
}
void waiting_power_s_5tm(void)
{
	if(s_5tm_work_status == s_5tm_status_power_on)
	{
		//????
		etimer_set(&s_5tm_power_wait_etimer, node_parameter.SPTD ms);		
		OPERATE_5TM;
		ENABLE_LOW_POWER;
	}
	else
	{
		etimer_set(&s_5tm_power_wait_etimer, 200 ms);						//????
	}
}
void s_5tm_sample_data(void)
{
	sdi12_query_address();
}
void s_5tm_query_address(void)
{	
		uart_recv_option=sdi12_receive;
		sdi12_query_address();
		s_5tm_uart_enable_wake_event();
		etimer_set(&s_5tm_receive_timeout_etimer, 3 s);
}
void s_5tm_sample_collect(void)
{	
	uart_recv_option=sdi12_analyster;
	sdi12_measure();
	s_5tm_uart_enable_wake_event();
	etimer_set(&s_5tm_receive_timeout_etimer, 3 s);
}
void s_5tm_sample_data_collect(void)
{	
		uart_recv_option=sdi12_analyster;
		sdi12_data_receive(measure_data);
		s_5tm_uart_enable_wake_event();
		etimer_set(&s_5tm_receive_timeout_etimer, 3 s);
}

//5TM 3????????
void s_5tm_sample_event(void)
{
	receive_5tm_fail_cnt = 0;
	s_5tm_work_status = s_5tm_status_end;
	DIS_OPERATE_5TM;
	uart_rx_disable();		
	s_5tm_uart_disable_wake_event();	
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
}

#endif

