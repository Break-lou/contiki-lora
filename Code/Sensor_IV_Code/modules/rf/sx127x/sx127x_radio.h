#ifndef __SX127X_RADIO_H__
#define __SX127X_RADIO_H__


#include "sx127x_app.h"


typedef struct sRadioDriver
{
    int ( *Init )( void );
    void ( *Reset )( void );
    void ( *StartRx )( void );
    void ( *GetRxPacket )( uint8_t *buffer, uint8_t *size );
    void ( *SetTxPacket )( uint8_t *buffer, uint8_t size );
	void ( *Sleep )( void );
	int8_t ( *GetRssi ) ( void );
	void ( *StartCAD )( void );
	uint8_t ( *GetPktRssiRegister) ( void );
}tRadioDriver;


extern tRadioDriver RadioDriver;
void radio_driver_init( void );



#endif
