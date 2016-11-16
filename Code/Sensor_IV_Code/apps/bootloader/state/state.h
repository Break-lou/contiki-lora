#ifndef STATE_H
#define STATE_H

#include <stdint.h>

typedef enum{
	COMMON_MODE = 2,
	FAST_MODE = 3,
	CONFIG_MODE = 4,
	CLOSE_MODE = 5,

}state_mode_t;


typedef struct sys_param_tt
{
	uint32_t valid;
	uint32_t update_flag;
	uint32_t program_start_addr;
	uint32_t program_end_addr;	
	state_mode_t state_mode;
	uint16_t id;
	uint16_t pan;
	uint16_t prepanid;
	uint16_t interval;		
	uint16_t sample_interval;

}sys_param_t;

void set_close_state(void);


#endif

