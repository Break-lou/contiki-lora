#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__


#include <SI32_SPI_B_Type.h>
#include <SI32_PBCFG_A_Type.h>
#include <SI32_PBSTD_A_Type.h>
#include <SI32_CLKCTRL_A_Type.h>
#include <SI32_PMU_A_Type.h>
#include "board_cfg.h"
#include "pmu_config.h"


void spi1_init(void);
int spi1_write_buffer_with_addr(uint8_t addr, const uint8_t* buf, uint8_t len);
int spi1_read_buffer_with_addr(const uint8_t addr, uint8_t* buf, uint8_t len);

void spi1_init_from_wakeup(void);
void spi1_setting_before_sleep(void);


#endif
