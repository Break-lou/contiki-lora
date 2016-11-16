#include "LED.h"
#include <SI32_PBCFG_A_Type.h>
#include <SI32_PBSTD_A_Type.h>
#include <SI32_PBGP_A_Type.h>
#include <si32_device.h>
#include "delay.h"
#include "board_cfg.h"

void led_off(void)
{
	LED_BLUE_OFF;
	LED_RED_OFF;
	LED_GREEN_OFF;
}
void led_on(void)
{
	LED_BLUE_ON;
	LED_RED_ON;
	LED_GREEN_ON;
}

void led_red_on(void)
{
	LED_RED_ON;
}
void led_red_off(void)
{
	LED_RED_OFF;
}
void led_blue_on(void)
{
	LED_BLUE_ON;
}

void led_blue_off(void)
{
	LED_BLUE_OFF;
}

void led_green_on(void)
{
	LED_GREEN_ON;
}

void led_green_off(void)
{
	LED_GREEN_OFF;
}

void led_start(void)
{
	uint32_t cnt = 10;
	while(cnt--)
	{
		led_on();
		delay_Xus(35000);
		led_off();
		delay_Xus(35000);
	}
}

void led_green_shining(void)
{
	LED_GREEN_ON;
	delay_Xus(1000);
	LED_GREEN_OFF;
}	

void led_red_shining(void)
{
	LED_RED_ON;
	delay_Xus(10000);
	LED_RED_OFF;
}

void led_blue_shing(void)
{
	LED_BLUE_ON;
	delay_Xus(2000);
	LED_BLUE_OFF;
}

