#include "ext_flash_include.h"
#include "crc.h"
#include <string.h>
#include "delay.h"
#include "LED.h"


/**
flash每页设置为264字节，其中0~255存储数据，256~257存储上一页的页数

**/

uint16_t read = 0;
uint16_t write = 0;
uint16_t flash_page_offset = FLASH_CACHE_BUFF_LEN;
uint16_t flash_idle_page;					 //空闲页面起始页				
uint16_t flash_page_num_in_use = 0;//多少页是被使用过了
uint8_t storage_read_pending_flag = 0;

uint16_t flash_program_start_page;//开始页
uint16_t flash_program_page_index;//页索引
uint16_t flash_top_page;					//顶页
uint16_t flash_last_page;
uint16_t flash_data_page_num;			//总共使用页
uint16_t capacity = FLASH_CACHE_BUFF_LEN;

uint8_t flash_cache_buff[FLASH_CACHE_BUFF_LEN];							
uint8_t flash_cache_temp_buff[FLASH_CACHE_BUFF_LEN+FLASH_INDEX_LEN];	//临时缓存

uint32_t flash_content_bytes_num = 0;				//总共使用多少个字节
uint32_t flash_content_hex_bytes_num = 0;		//历史记录总条数

storage_index read_index;
storage_index real_index;
//容量设置
void cache_init(void)
{
	read = 0;
	write = 0;
	capacity = FLASH_CACHE_BUFF_LEN;
}

bool cache_is_full(void)
{
	return (capacity == 0);
}

bool cache_is_empty(void)
{
	return (capacity == FLASH_CACHE_BUFF_LEN);
}

//向flash_cache_buff写入缓存数据
uint16_t cache_write(uint8_t *buff, uint16_t len)
{
	uint16_t write_len;
	uint16_t i = 0;
	if(len <= capacity)
	{
		write_len = len;
		capacity -= len;
	}
	else
	{
		write_len = capacity;
		len = capacity;
		capacity = 0;
	}
	while(len--)
	{
		flash_cache_buff[write++] = buff[i++];
		if(write == FLASH_CACHE_BUFF_LEN)
			write = 0;
	}
	#if FLASH_DEBUG_PRINT == 1
		printf("FLASH WRITE = %d,CAPACITY=%d\n ", write,capacity);
	#endif
	return write_len;
}
//从flash_cache_buff读出缓存数据
uint16_t cache_read(uint8_t *buff, uint16_t len)
{
	uint16_t read_len = 0;
	uint16_t i = 0;
	uint16_t content = FLASH_CACHE_BUFF_LEN - capacity;
	if(len <= content)
	{
		read_len = len;
		capacity += len;
	}
	else
	{
		read_len = content;
		len = content;
		capacity = FLASH_CACHE_BUFF_LEN;
	}
	while(len--)
	{
		buff[i++] =  flash_cache_buff[read++];
		if(read == FLASH_CACHE_BUFF_LEN)
			read = 0;
	}
	#if FLASH_DEBUG_PRINT == 1
		printf("FLASH READ = %d,CAPACITY=%d\n ", read,capacity);
	#endif
	return read_len;
}
//寻找空的页
//检查256和257的字节是否有索引来判断是否为新页
uint16_t storage_find_idle_page(void)
{
	int has_idle_flag = 0;
	uint16_t idle_page = 0;
	uint16_t cnt = 0;
	uint16_t page_index;
	do{
		flash_idle_page = (flash_idle_page + 1)%flash_data_page_num;//使用页的顶页再加一
		cnt++;
		if(!flash_idle_page)//若超过flash_data_page_num页数
		{
			flash_idle_page++;//设置为1
			cnt++;
		}
		if(cnt == flash_data_page_num)
		{
			has_idle_flag = -1;
			break;
		}
		flash_tat_read_data(flash_idle_page, FLASH_CACHE_BUFF_LEN, (uint8_t *)(&page_index), FLASH_INDEX_LEN);
	}while(page_index != 0XFFFF);

	if(has_idle_flag == -1)
	{
		idle_page = 0;
	}		
	else
	{
		idle_page = flash_idle_page;
	}
	return idle_page;
}
//向新的页写入数据 flash_cache_temp_buff：长度为FLASH_CACHE_BUFF_LEN+FLASH_INDEX_LEN
int storage_write_new_page(uint8_t *data)
{
	int ret = 0;
	uint16_t idle_page;
	idle_page = storage_find_idle_page();
	if(idle_page > 0)
	{
		flash_page_num_in_use++;//使用过的页数计数器加一
		data[FLASH_CACHE_BUFF_LEN] = (uint8_t)flash_top_page;//当前顶页保存在新页的256-257字节中
		data[FLASH_CACHE_BUFF_LEN+1] = (uint8_t)(flash_top_page>>8);
		//从缓冲区写入flash不带擦除
		flash_tat_write_data_without_erase(flash_idle_page, data, FLASH_CACHE_BUFF_LEN+FLASH_INDEX_LEN);
		flash_top_page = flash_idle_page;//新页作为定页
	}
	else
	{
		ret = -1;
	}
	return ret;
}

uint32_t write_new_page_cnt = 0;
uint32_t write_old_page_cnt = 0;
void storage_write_cache_buffer(void)
{
	memcpy(flash_cache_temp_buff, flash_cache_buff, FLASH_CACHE_BUFF_LEN);
	flash_cache_temp_buff[FLASH_CACHE_BUFF_LEN] = write&0xff;
	flash_cache_temp_buff[FLASH_CACHE_BUFF_LEN+1] = read&0xff;
	flash_tat_write_data(flash_data_page_num, flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN+2);
}
int storage_write_data(uint8_t *buff, uint16_t len)
{
	uint16_t write_len;

	while(len)
	{
		if(cache_is_full())//缓存是否满
		{
			if(storage_read_pending_flag)//读取挂起标志
			{
				return -1;
				//while(storage_read_pending_flag);
				
			}
			//flash_page_offset一页的数据的计数器
			if(flash_page_offset == FLASH_CACHE_BUFF_LEN)//页偏移是否等于缓存长度256
			{
				cache_read(flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN);//从软件缓存区读取该页的整片数据到软件临时缓存区
				storage_write_new_page(flash_cache_temp_buff);//将该数据写入新页中
			}
			else
			{
				//基于读缓存的机制可以判定是从头开始存
				write_old_page_cnt++;
				flash_tat_read_data(flash_top_page, 0, flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN+FLASH_INDEX_LEN);//读取顶页258个数据到软件临时缓存区
				cache_read(flash_cache_temp_buff+flash_page_offset, FLASH_CACHE_BUFF_LEN-flash_page_offset);//将待存的数据和已有的数据重新组成待存数组
				flash_tat_write_data(flash_top_page, flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN+FLASH_INDEX_LEN);//写入flash中
				flash_page_offset = FLASH_CACHE_BUFF_LEN;//页已满
			}
		}
		write_len = cache_write(buff, len);//将新的数据写入软件缓冲区
		buff += write_len;
		len -= write_len;
	}
	flash_content_bytes_num = (flash_page_num_in_use<<8) + flash_page_offset - capacity;//总共字节数
	flash_content_hex_bytes_num = (flash_content_bytes_num>>4);

	real_index.current_page = flash_top_page;
	real_index.read = read;
	real_index.write = write;
	#if FLASH_DEBUG_PRINT == 1
		printf("storage_write_data()\n ");
		printf("FLASH READ = %d,FALSH WRITE=%d\n ", read,write);
		printf("FLASH TOP PAGE = %d,FALSH PAGE OFFSET=%d\n ", flash_top_page,flash_page_offset);
	#endif
	//storage_write_cache_buffer();
	return 0;
}
//存储擦除
//int storage_flush_program(void)
//{
//	uint16_t read_len; 
//	uint16_t crc;
//	if(!cache_is_empty())//软件缓冲区是否为空
//	{
//		//不为空
//		read_len = cache_read(flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN);
//		memset(flash_cache_temp_buff+read_len, 0xff, FLASH_CACHE_BUFF_LEN - read_len);
//		crc = crc_compute(flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN, INITIAL_VALUE, 1);
//		*(uint16_t *)&(flash_cache_temp_buff[FLASH_CACHE_BUFF_LEN]) = crc;
//		flash_tat_write_data(flash_program_page_index, flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN+FLASH_INDEX_LEN);	
//	}
//	return 0;
//}
//格式化flash和缓存
uint8_t format_flash(void)
{
	uint16_t next_index;
	uint32_t cpu_sr=cpu_sr;
	flash_page_offset = FLASH_CACHE_BUFF_LEN;
	flash_top_page=0;
	flash_idle_page=0;
	flash_page_num_in_use = 0;//多少页是被使用过了
	flash_content_bytes_num = 0;//总共字节数
	flash_content_hex_bytes_num = 0;
	read = 0;
	write = 0;
	capacity = FLASH_CACHE_BUFF_LEN;		
	storage_read_pending_flag = 0;
	flash_last_page=flash_top_page;
	
//flash_capacity_via_KB = 1024;
//		flash_pages = 4096;
//		flash_data_page_num = 3840;
//		flash_program_start_page = 3840;
//		flash_program_page_index = flash_program_start_page;
	ext_flash_port_init();
	ext_flash_spi_init();
	ext_flash_reset();
	
	ENTER_CRITICAL_REGION();
	for( uint16_t i = 0; i <flash_data_page_num ; i++)//flash_data_page_num
	{
		flash_tat_erase_page(i);
	}
	for( uint16_t i = 0; i <flash_data_page_num ; i++)//flash_data_page_num
	{
		flash_tat_read_data(i, FLASH_CACHE_BUFF_LEN, (uint8_t *)(&next_index), 2);
		if(next_index!=0xffff)
		{
			flash_tat_erase_page(i);
		}
	}
	LEAVE_CRITICAL_REGION();
	return 1;
}
uint32_t flash_parameter_display(uint8_t data)
{
	uint32_t data_parameter;
	switch(data)
	{
		case 1:
			data_parameter=read;
			break;
		case 2:
			data_parameter=write;
			break;
		case 3:
			data_parameter=capacity;
			break;
		case 4:
			data_parameter=flash_top_page;
			break;
		case 5:
			data_parameter=flash_idle_page;
			break;
		case 6:
			data_parameter=flash_last_page;
			break;
		case 7:
			data_parameter=flash_page_offset;
			break;
		case 8:
			data_parameter=flash_page_num_in_use;
			break;
		case 9:
			data_parameter=flash_content_bytes_num;
			break;
		case 10:
			data_parameter=flash_content_hex_bytes_num;
			break;
		case 11:
			data_parameter=storage_read_pending_flag;
			break;
	}
	return data_parameter;
}
//int storage_write_program(uint8_t *buff, uint16_t len)
//{
//	uint16_t write_len;
//	uint16_t crc;
//	while(len)
//	{
//		if(cache_is_full())
//		{
//			cache_read(flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN);
//			crc = crc_compute(flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN, INITIAL_VALUE, 1);
//			*(uint16_t *)&(flash_cache_temp_buff[FLASH_CACHE_BUFF_LEN]) = crc;
//			
//			flash_tat_write_data(flash_program_page_index, flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN+FLASH_INDEX_LEN);
//			
//			flash_program_page_index++;
//		}
//		write_len = cache_write(buff, len);
//		buff += write_len;
//		len -= write_len;
//	}
//	return 0;
//}

uint16_t storage_read_data(uint8_t *buff, uint16_t len)
{
	uint16_t temp_flash_page;
	uint16_t read_len = 0;
	if(!storage_read_pending_flag)//将缓存的信息保存。用于后面的恢复
	{
		storage_read_pending_flag = 1;
		read_index.read = read;
		read_index.write = write;
		read_index.capacity = capacity;
		read_index.current_page = flash_top_page;	
		read_index.page_offset = flash_page_offset;
		flash_last_page = flash_top_page;
	}

	memset(buff, 0, len);
	while(len)
	{
		if(cache_is_empty())  //软件缓存中为空则从flash中读取数据
		{
			if(flash_top_page > 0)
			{
				if(len < flash_page_offset)//读取的数据小于当前页存的数据长度
				{
					flash_tat_read_data(flash_top_page, flash_page_offset-len, buff, len);
					flash_page_offset -= len;
					read_len += len;
					len = 0;					
				}
				else
				{
					flash_tat_read_data(flash_top_page, 0, buff, flash_page_offset);//读取数据大于当前页存的数据长度则分几次读取
					buff += flash_page_offset;
					len -= flash_page_offset;
					read_len += flash_page_offset;
					flash_page_offset = FLASH_CACHE_BUFF_LEN;
					flash_tat_read_data(flash_top_page, FLASH_CACHE_BUFF_LEN, (uint8_t *)(&temp_flash_page), FLASH_INDEX_LEN);
					flash_top_page = temp_flash_page;				
				}			
			}
			else
			{
				read_len=0;
				break;
			}
		}
		else
		{
			read_len += cache_read(buff, len);//直接从缓存中读取数据
			buff += read_len;
			len -= read_len;			
		}
	}
	#if FLASH_DEBUG_PRINT == 1
		printf("storage_read_data()\n ");
		printf("FLASH READ = %d,FALSH WRITE=%d\n ", read,write);
		printf("FLASH TOP PAGE = %d,FALSH PAGE OFFSET=%d\n ", flash_top_page,flash_page_offset);
	#endif
	if(!read_len)//若没有数据则不挂起存储读取标记
		storage_read_pending_flag = 0;
	return read_len;
}
//取消读取则把之前保存的存储的控制信息恢复
int storage_cancle_read(void)
{
	if(storage_read_pending_flag)
	{
		storage_read_pending_flag = 0;
		read = read_index.read;
		write = read_index.write;
		capacity = read_index.capacity;
		flash_top_page = read_index.current_page;
		flash_page_offset = read_index.page_offset;
	}

	return 0;
}
//完成读取 则擦除读取页，更新控制信息
int storage_confirm_read(void)
{
	uint16_t temp_flash_page;
	if(storage_read_pending_flag)
	{
		storage_read_pending_flag = 0;
		while(flash_top_page != flash_last_page)
		{
			flash_page_num_in_use--;
			flash_tat_read_data(flash_last_page , FLASH_CACHE_BUFF_LEN, (uint8_t *)(&temp_flash_page), FLASH_INDEX_LEN);
			flash_tat_erase_page(flash_last_page);
			flash_last_page = temp_flash_page;		
		}

		flash_content_bytes_num = (flash_page_num_in_use<<8) + flash_page_offset - capacity;
		flash_content_hex_bytes_num = (flash_content_bytes_num>>4);		
		real_index.read = read;
		real_index.write = write;
		real_index.capacity = capacity;
		real_index.current_page = flash_top_page;
		real_index.page_offset = flash_page_offset;		
		
	}

	return 0;
}


uint32_t idle_page_num = 0;
uint32_t busy_page_num = 0;
void storage_check_stack(void)
{
	uint16_t i = 0;
	uint16_t temp_page;
	uint16_t index_page;
	uint8_t index_error1 = 0;
	uint8_t index_error2 = 0;
	uint16_t used_cnt1=0, used_cnt2=0;
	uint16_t next_index;
	uint64_t test_current = 0;
	uint64_t test_index = 0;
	uint16_t cnt = 0;
	int temp_top_page = 0;//临时的顶页
	//页偏移                索引页偏移
	flash_page_offset = real_index.page_offset = FLASH_CACHE_BUFF_LEN;
	
	for(i = 1; i < flash_data_page_num; i++)//1--3840
	{
		flash_tat_read_data(i, FLASH_CACHE_BUFF_LEN, (uint8_t *)(&next_index), 2);//获取每页第256和257个字节的数据
		cnt++;
		if(next_index != 0xffff)
		{
			temp_top_page += i;
			temp_top_page -= next_index;
			test_current += i;
			test_index += next_index;
			flash_page_num_in_use++;
		}
	}

	flash_top_page = (uint16_t)temp_top_page;
	flash_idle_page = (uint16_t)temp_top_page;
	flash_content_bytes_num = (flash_page_num_in_use<<8);//flash_page_num_in_use*256
	flash_content_hex_bytes_num = (flash_content_bytes_num>>4);//flash_content_bytes_num/16   历史记录总条数 16个字节一条

	for( i = 0; i < flash_data_page_num; i++)
	{
		flash_tat_read_data(i, FLASH_CACHE_BUFF_LEN, (uint8_t *)&temp_page, 2);
		if((temp_page > flash_data_page_num) && (temp_page != 0xffff))
		{
			index_error1 = 1;
			break;
		}
		if(temp_page != 0xffff)
		{
			used_cnt1++;//使用计数
		}
	}
	for(temp_page = flash_top_page; temp_page != 0; temp_page = index_page)
	{
		flash_tat_read_data(temp_page, FLASH_CACHE_BUFF_LEN, (uint8_t *)(&index_page), 2);
		used_cnt2++;
		if((index_page > flash_data_page_num) || (used_cnt2 > flash_data_page_num))
		{
			index_error2 = 1;
			break;
		}
	}
	#if FLASH_DEBUG_PRINT == 1
		printf("FLASH TOP PAGE = %d\n ", flash_top_page);
		printf("index_error1 = %d,index_error2=%d\n ", index_error1,index_error2);
	#endif
	if((used_cnt1 != used_cnt2) || (index_error1) || (index_error2))
	{
		led_red_on();
		flash_top_page = 0;
		flash_page_num_in_use = 0;
		flash_idle_page = 0;
		flash_content_bytes_num = 0;
		flash_content_hex_bytes_num = 0;
		flash_tat_erase_chip();
		led_red_off();
	}
}

void storage_empty(void)
{
	cache_init();
	flash_top_page = 0;
	flash_page_num_in_use = 0;
	flash_idle_page = 0;
	flash_content_bytes_num = 0;
	flash_content_hex_bytes_num = 0;
}


int storage_init(void)
{
	cache_init();
	
	led_blue_on();

	flash_init();//访问设备设置，读取设备参数
	
	flash_tat_init();//设置当前外部FLASH可用有效

	delay_Xus(100);

	storage_check_stack();//检测存储堆栈

	#ifdef STORAGE_DEBUG
		storage_empty();
		flash_tat_erase_chip();		
		debug_storage();
	#endif
	
	led_blue_off();
	
	return 0;
}

