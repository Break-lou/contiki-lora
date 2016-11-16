#include "clock_config.h"


SI32_RSTSRC_Enum_Type reset_source;



system_core_clock system_clock;
system_periph_clock periph_clock;

uint32_t extosc_clock_base = 16000000;
uint32_t SystemPeripheralClock;

uint32_t current_sysclk;

//时钟初始化
void si32_clock_init(void)
{
	//配置外设时钟
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0,
										   SI32_CLKCTRL_A_APBCLKG0_PB0 |
										   SI32_CLKCTRL_A_APBCLKG0_USART0 |
										   SI32_CLKCTRL_A_APBCLKG0_SPI1 |
										   SI32_CLKCTRL_A_APBCLKG0_FLCTRLCEN_ENABLED_U32);
	//配置MISC0、MISC1
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0,
										   SI32_CLKCTRL_A_APBCLKG1_MISC0 |
										   SI32_CLKCTRL_A_APBCLKG1_MISC1);
	
}

//系统滴答时钟初始化
void systick_init(void)
{
	SystemCoreClock = 20000000;
	SysTick_Config(SystemCoreClock / 1000);
}

uint32_t get_periph_clock(void)
{
	return periph_clock.apb_clock;
}

void sysclk_init_before_sample(void)
{
	set_system_clock(CLOCK_LOW_POWER_OSC, SYSTEMCORECLOCK_5M);
	set_periph_clock(PERIPH_DIVIDER2);
}

void sysclk_init_after_sample(void)
{
	set_system_clock(CLOCK_LOW_POWER_OSC, SYSTEMCORECLOCK_20M);
	set_periph_clock(PERIPH_DIVIDER2);
}

void sysclk_init_from_reset(void)
{	
	set_system_clock(CLOCK_LOW_POWER_OSC, SYSTEMCORECLOCK_5M);
	set_periph_clock(PERIPH_DIVIDER1);
	si32_clock_init();
}

void set_system_clock(uint32_t clk_source, uint32_t clock)
{
	current_sysclk = clock;
	switch(clk_source)
	{
		case CLOCK_LOW_POWER_OSC:
			SI32_CLKCTRL_A_select_ahb_source_low_power_oscillator(SI32_CLKCTRL_0);
			switch(clock)
			{
				case SYSTEMCORECLOCK_20M:
					SystemCoreClock = SYSTEMCORECLOCK_20M;
					SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);					
					break;
				case SYSTEMCORECLOCK_10M:
					SystemCoreClock = SYSTEMCORECLOCK_10M;
					SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_2);					
					break;
				case SYSTEMCORECLOCK_5M:
					SystemCoreClock = SYSTEMCORECLOCK_5M;
					SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_4);						
					break;
				case SYSTEMCORECLOCK_2_5M:
					SystemCoreClock = SYSTEMCORECLOCK_2_5M;
					SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_8);						
					break;
				case SYSTEMCORECLOCK_1_25M:
					SystemCoreClock = SYSTEMCORECLOCK_1_25M;
					SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_16);						
					break;					
				default:
					SystemCoreClock = SYSTEMCORECLOCK_20M;
					SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);	
					break;
			}
			
			break;
		case CLOCK_LOW_FREQUENCY_OSC:			
			SI32_CLKCTRL_A_select_ahb_source_low_frequency_oscillator(SI32_CLKCTRL_0);
			switch(clock)
			{
				case SYSTEMCORECLOCK_2_5M:
					SystemCoreClock = SYSTEMCORECLOCK_2_5M;
					SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);						
					break;
				case SYSTEMCORECLOCK_1_25M:
					SystemCoreClock = SYSTEMCORECLOCK_1_25M;
					SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_2);						
					break;					
				default:
					SystemCoreClock = SYSTEMCORECLOCK_2_5M;
					SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);	
					break;
			}			
			break;
		case CLOCK_RTC0:
			SI32_CLKCTRL_A_select_ahb_source_rtc0tclk(SI32_CLKCTRL_0);
			break;
		case CLOCK_EXTERNAL_OSC:
			SI32_CLKCTRL_A_select_ahb_source_external_oscillator(SI32_CLKCTRL_0);
			switch(clock)
			{
				case SYSTEMCORECLOCK_16M:
					switch(extosc_clock_base)
					{
						case SYSTEMCORECLOCK_16M:
							SystemCoreClock = SYSTEMCORECLOCK_16M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);							
							break;
						case SYSTEMCORECLOCK_8M:
							SystemCoreClock = SYSTEMCORECLOCK_8M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);								
							break;
						default:
							SystemCoreClock = SYSTEMCORECLOCK_16M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);								
							break;
					}						
					break;
				case SYSTEMCORECLOCK_8M:
					switch(extosc_clock_base)
					{
						case SYSTEMCORECLOCK_16M:
							SystemCoreClock = SYSTEMCORECLOCK_8M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_2);							
							break;
						case SYSTEMCORECLOCK_8M:
							SystemCoreClock = SYSTEMCORECLOCK_8M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);								
							break;
						default:
							SystemCoreClock = SYSTEMCORECLOCK_8M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);								
							break;
					}										
					break;
				case SYSTEMCORECLOCK_4M:
					switch(extosc_clock_base)
					{
						case SYSTEMCORECLOCK_16M:
							SystemCoreClock = SYSTEMCORECLOCK_4M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_4);							
							break;
						case SYSTEMCORECLOCK_8M:
							SystemCoreClock = SYSTEMCORECLOCK_4M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_2);								
							break;
						default:
							SystemCoreClock = SYSTEMCORECLOCK_4M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);								
							break;
					}						
					break;		
				case SYSTEMCORECLOCK_2M:
					switch(extosc_clock_base)
					{
						case SYSTEMCORECLOCK_16M:
							SystemCoreClock = SYSTEMCORECLOCK_2M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_8);							
							break;
						case SYSTEMCORECLOCK_8M:
							SystemCoreClock = SYSTEMCORECLOCK_2M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_4);								
							break;
						default:
							SystemCoreClock = SYSTEMCORECLOCK_2M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);								
							break;
					}					
					break;	
				case SYSTEMCORECLOCK_1M:
					switch(extosc_clock_base)
					{
						case SYSTEMCORECLOCK_16M:
							SystemCoreClock = SYSTEMCORECLOCK_1M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_16);							
							break;
						case SYSTEMCORECLOCK_8M:
							SystemCoreClock = SYSTEMCORECLOCK_1M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_8);								
							break;
						default:
							SystemCoreClock = SYSTEMCORECLOCK_1M;
							SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);								
							break;
					}					
					break;						
				default:
					SystemCoreClock = extosc_clock_base;
					SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, AHB_CLOCK_DEVIDED_1);	
					break;
			}			
			break;			
		case CLOCK_VIORFCLK:
			SI32_CLKCTRL_A_select_ahb_source_viorfclock(SI32_CLKCTRL_0);
			break;
		case CLOCK_PLL:
			SI32_CLKCTRL_A_select_ahb_source_pll(SI32_CLKCTRL_0);
			break;
		case CLOCK_DIVIDED_LOW_POWER_OSC:
			SI32_CLKCTRL_A_select_ahb_source_divided_low_power_oscillator(SI32_CLKCTRL_0);
			break;
		default:
			break;

	}
	
	system_clock.clk_source = clk_source;
	system_clock.core_clock = SystemCoreClock;	
}

int set_periph_clock(uint32_t divider)
{
	int ret = 0;
	switch(divider)
	{
		case PERIPH_DIVIDER1:
			periph_clock.apb_clock = SystemCoreClock;
			SystemPeripheralClock = SystemCoreClock;
			SI32_CLKCTRL_A_select_apb_divider_1(SI32_CLKCTRL_0);
			break;
		case PERIPH_DIVIDER2:			
			periph_clock.apb_clock = (SystemCoreClock >> 1);
			SystemPeripheralClock = (SystemCoreClock >> 1);
			SI32_CLKCTRL_A_select_apb_divider_2(SI32_CLKCTRL_0);
			break;
		default:
			periph_clock.apb_clock = SystemCoreClock;
			SI32_CLKCTRL_A_select_apb_divider_1(SI32_CLKCTRL_0);
			ret = -1;
			break;
	}
	return ret;
}

/*******************************************************************************
  * @brief rstsrc_init()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 查询系统复位源，使能开门狗复位
	 *****************************************************************************
  */
void rstsrc_init(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0,SI32_CLKCTRL_A_APBCLKG1_MISC0 |SI32_CLKCTRL_A_APBCLKG1_MISC1);	
	get_reset_source();//得到复位远
	SI32_RSTSRC_A_enable_watchdog_timer_reset_source(SI32_RSTSRC_0);
//	SI32_RSTSRC_A_disable_watchdog_timer_reset_source(SI32_RSTSRC_0);
//	SI32_LOCK_A_lock_module(SI32_LOCK_0, SI32_LOCK_A_SELECT_RSTSRC_LOCK);
}
/*******************************************************************************
  * @brief get_reset_source()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 查询系统复位源
	 *****************************************************************************
  */
SI32_RSTSRC_Enum_Type get_reset_source(void)
{
	reset_source = SI32_RSTSRC_A_get_last_reset_source(SI32_RSTSRC_0);
	return reset_source;	
}
/*******************************************************************************
  * @brief set_software_reset_source()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 设置软件复位
	 *****************************************************************************
  */
void set_software_reset_source(void)
{
	SI32_RSTSRC_A_generate_software_reset(SI32_RSTSRC_0);
}
