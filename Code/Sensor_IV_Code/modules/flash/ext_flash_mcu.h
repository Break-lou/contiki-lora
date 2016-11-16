#ifndef EXT_FLASH_MCU_H
#define EXT_FLASH_MCU_H

#include <SI32_SPI_B_Type.h>
#include <si32_device.h>
#include <SI32_PBSTD_A_Type.h>

#include "board_cfg.h"

#define EXT_FLASH_SPI_MAX_CLK	5000000

#define EXT_FLASH_CS_HIGH()	SI32_PBSTD_A_write_pins_high(FLASH_CS_PORT, FLASH_CS_PIN)
#define EXT_FLASH_CS_LOW()	SI32_PBSTD_A_write_pins_low(FLASH_CS_PORT, FLASH_CS_PIN)
#define EXT_FLASH_CS_OUT() 	SI32_PBSTD_A_set_pins_push_pull_output(FLASH_CS_PORT, FLASH_CS_PIN)

#define EXT_FLASH_RESET_HIGH()	SI32_PBSTD_A_write_pins_high(FLASH_RESET_PORT, FLASH_RESET_PIN)
#define EXT_FLASH_RESET_LOW()	SI32_PBSTD_A_write_pins_low(FLASH_RESET_PORT, FLASH_RESET_PIN)
#define EXT_FLASH_RESET_OUT()	SI32_PBSTD_A_set_pins_push_pull_output(FLASH_RESET_PORT, FLASH_RESET_PIN)

//sim3l144没有该端口
#define EXT_FLASH_PORT_POWER_OFF()	SI32_SPI_B_disable_module(SI32_SPI_0);\
		SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_1, 0X0013);\
		SI32_PBSTD_A_write_pins_low(SI32_PBSTD_1, 0X0013)
		
#define SPI0_PORT_GROUP	SI32_PBSTD_0


#define SPI0_SCK_PIN	PBX_3
#define SPI0_MISO_PIN	PBX_4
#define SPI0_MOSI_PIN	PBX_5

#define SPI0_SCK_OUT()		SI32_PBSTD_A_set_pins_push_pull_output(SPI0_PORT_GROUP, SPI0_SCK_PIN)
#define SPI0_SCK_HIGH()		SI32_PBSTD_A_set_pins_push_pull_output(SPI0_PORT_GROUP, SPI0_SCK_PIN);\
							SI32_PBSTD_A_write_pins_high(SPI0_PORT_GROUP, SPI0_SCK_PIN)
			
#define SPI0_SCK_LOW()		SI32_PBSTD_A_set_pins_push_pull_output(SPI0_PORT_GROUP, SPI0_SCK_PIN);\
							SI32_PBSTD_A_write_pins_low(SPI0_PORT_GROUP, SPI0_SCK_PIN)

#define SPI0_MISO_HIGH()	SI32_PBSTD_A_set_pins_push_pull_output(SPI0_PORT_GROUP, SPI0_MISO_PIN);\
							SI32_PBSTD_A_write_pins_high(SPI0_PORT_GROUP, SPI0_MISO_PIN)

#define SPI0_MISO_LOW()		SI32_PBSTD_A_set_pins_push_pull_output(SPI0_PORT_GROUP, SPI0_MISO_PIN);\
							SI32_PBSTD_A_write_pins_low(SPI0_PORT_GROUP, SPI0_MISO_PIN)

#define SPI0_MISO_IN()		SI32_PBSTD_A_set_pins_digital_input(SPI0_PORT_GROUP, SPI0_MISO_PIN)

#define SPI0_MOSI_OUT()		SI32_PBSTD_A_set_pins_push_pull_output(SPI0_PORT_GROUP, SPI0_MOSI_PIN)
#define SPI0_MOSI_HIGH()	SI32_PBSTD_A_set_pins_push_pull_output(SPI0_PORT_GROUP, SPI0_MOSI_PIN);\
							SI32_PBSTD_A_write_pins_high(SPI0_PORT_GROUP, SPI0_MOSI_PIN)
#define SPI0_MOSI_LOW()		SI32_PBSTD_A_set_pins_push_pull_output(SPI0_PORT_GROUP, SPI0_MOSI_PIN);\
							SI32_PBSTD_A_write_pins_low(SPI0_PORT_GROUP, SPI0_MOSI_PIN)

void ext_flash_port_init(void);

void ext_flash_spi_init(void);

void ext_flash_reset(void);

void ext_flash_spi_init_from_wakeup(void);

#endif

