#include "flash_config.h"
#include "board_cfg.h"

//Flash操作完成后，需将flash的写指针指定到空闲地址


#define PAGE_MASK 0xfffffc00
#define FLASH_PAGE_SIZE 256


void write_to_flash_from_buff(uint32_t addr,  uint8_t *buff, uint16_t len);
void erase_flash(uint32_t addr, uint16_t pages, uint16_t value);


void read_from_flash_to_buff(uint32_t addr, uint8_t *buff, uint16_t len)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0,SI32_CLKCTRL_A_APBCLKG0_FLCTRLCEN_ENABLED_U32);
	SI32_FLASHCTRL_A_select_flash_speed_mode(SI32_FLASHCTRL_0,0x00);
	SI32_FLASHCTRL_A_exit_read_store_mode(SI32_FLASHCTRL_0);
	SI32_FLASHCTRL_A_disable_data_prefetch(SI32_FLASHCTRL_0);
	SI32_FLASHCTRL_A_disable_prefetch(SI32_FLASHCTRL_0);
	SI32_FLASHCTRL_A_select_flash_read_time_fast(SI32_FLASHCTRL_0);

	while(len > 0)
	{
		*(uint16_t *)buff = *(uint16_t *)addr;
		buff += 2;
		addr += 2;
		len -= 2;
	}

}

void write_data_to_flash(uint32_t addr,  uint8_t *buff, uint16_t len)
{
	uint32_t pages;
	uint16_t page_nums;
	
	if(!len) return;
	
	pages = (addr&PAGE_MASK);
	if(!(addr&(~PAGE_MASK)))
	{
		erase_flash(addr, 1, 0xff);
	}
	if(((addr+len-1)&PAGE_MASK) > pages)
	{
		page_nums = (((addr+len)&PAGE_MASK) - pages)>>10;
		erase_flash(pages+1024, page_nums, 0xff);
	}

	write_to_flash_from_buff(addr, buff, len);

}

void write_to_flash_from_buff(uint32_t addr,  uint8_t *buff, uint16_t len)
{
	uint32_t cpu_sr = cpu_sr;
	uint32_t dest_addr = addr;
	uint16_t data;
	
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0,SI32_CLKCTRL_A_APBCLKG0_FLCTRLCEN_ENABLED_U32);
	SI32_FLASHCTRL_A_select_flash_speed_mode(SI32_FLASHCTRL_0,0x00);
	SI32_FLASHCTRL_A_exit_read_store_mode(SI32_FLASHCTRL_0);
	SI32_FLASHCTRL_A_disable_data_prefetch(SI32_FLASHCTRL_0);
	SI32_FLASHCTRL_A_disable_prefetch(SI32_FLASHCTRL_0);
	SI32_FLASHCTRL_A_exit_multi_byte_write_mode(SI32_FLASHCTRL_0);
	SI32_FLASHCTRL_A_exit_flash_erase_mode(SI32_FLASHCTRL_0);
	
	SI32_VMON_B_enable_vbat_supply_monitor(SI32_VMON_0);
  	SI32_RSTSRC_A_enable_vdd_monitor_reset_source(SI32_RSTSRC_0);
	ENTER_CRITICAL_REGION();
	while(len > 0)
	{
		data = *(uint16_t *)buff;
		SI32_FLASHCTRL_A_write_wraddr(SI32_FLASHCTRL_0,dest_addr);
		
		SI32_FLASHCTRL_A_write_flash_key(SI32_FLASHCTRL_0, 0xA5);
		SI32_FLASHCTRL_A_write_flash_key(SI32_FLASHCTRL_0, 0xF1);
		SI32_FLASHCTRL_A_write_wrdata(SI32_FLASHCTRL_0, data);
		buff += 2;
		dest_addr += 2;
		len -= 2;		
	}
	
	LEAVE_CRITICAL_REGION();				

} 


void erase_flash(uint32_t addr, uint16_t pages, uint16_t value)
{
	uint32_t cpu_sr = cpu_sr;
	// 1. Enable VDD Supply Monitor and set as a reset source
	SI32_VMON_B_enable_vbat_supply_monitor(SI32_VMON_0);
	SI32_RSTSRC_A_enable_vdd_monitor_reset_source(SI32_RSTSRC_0);
	
	// 2. Enter Flash Erase Mode
	SI32_FLASHCTRL_A_enter_flash_erase_mode(SI32_FLASHCTRL_0);
	
	// 3. Disable Interrupts
	ENTER_CRITICAL_REGION();
	// 4. Write the inital unlock value to KEY
	SI32_FLASHCTRL_A_write_flash_key(SI32_FLASHCTRL_0, 0xA5);
	
	// 5. Write the single unlock value to KEY
	SI32_FLASHCTRL_A_write_flash_key(SI32_FLASHCTRL_0, 0xF1);

	while(pages--)
	{		
		// 6. Write the address of the Flash page to WRADDR
		SI32_FLASHCTRL_A_write_wraddr(SI32_FLASHCTRL_0, addr);		

		// 7. Write any value to WRDATA in right-justified format to
		//	  initiate the page erase
		SI32_FLASHCTRL_A_write_wrdata(SI32_FLASHCTRL_0, value);

	}

	
	// 8. (optional) poll BUSYF if executing code from other than Flash Memory
	// We are executing code from Flash, so no need to poll.
	
	// 9. Enable Interrupts
	LEAVE_CRITICAL_REGION();

}







