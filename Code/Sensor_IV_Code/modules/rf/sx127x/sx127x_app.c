#include "sx127x_app.h"
#include "sx127x_hal.h"
#include <stdio.h>
#include "sensor_parameter.h"

#define PREAMBLE_LSB	10
#define PREAMBLE_MSB	0

#define RECEVIOR_PREAMBLE_LSB	10
#define RECEVIOR_PREAMBLE_MSB	0


uint32_t calc_frq(uint16_t frq);
uint8_t sx127x_get_opmode(void);
void sx127x_set_payload_crc_on(uint8_t on);


#define SPD_PARAMETER_LEN 16
//每行分别是 bw cr sf 超时时间
const uint16_t LORA_SPD_PARMATER[] = 
{
	//0 1 2 3
	RFLR_MODEMCONFIG1_BW_500_KHZ, RFLR_MODEMCONFIG1_CODINGRATE_4_5, RFLR_MODEMCONFIG2_SF_7, 10,
	RFLR_MODEMCONFIG1_BW_500_KHZ, RFLR_MODEMCONFIG1_CODINGRATE_4_8, RFLR_MODEMCONFIG2_SF_7, 8,
	RFLR_MODEMCONFIG1_BW_250_KHZ, RFLR_MODEMCONFIG1_CODINGRATE_4_5, RFLR_MODEMCONFIG2_SF_7, 4,
	RFLR_MODEMCONFIG1_BW_125_KHZ, RFLR_MODEMCONFIG1_CODINGRATE_4_5, RFLR_MODEMCONFIG2_SF_7, 2
};

////////////////////////////////////////////////////////////////////////////////
// 功能描述 : RF初始化
// 输入参数 : tSX127xInitPara initPara  输入速率Init_LoRa_0_8K, Init_LoRa_4_8K , Init_LoRa_10k,
// 返回参数 : tSX127xError              错误枚举内容
// 说明     :  初始化时，信道初始化默认为0信道
////////////////////////////////////////////////////////////////////////////////
tSX127xError sx127x_init(tSX127xInitSPD initPara,unsigned char Pout)
{
    if(initPara>Init_LoRa_12K)   	        	//如果输入参数错误
    {
        return PARAMETER_INVALID;              	//报错输入
    }
    SX1276_InitIO();                	        //IO口初始化           
    SX1276_Reset();                 	        //复位RF
    SX1276_InitSPI();              	        	//SPI初始化
    //init Regs
    SX1276_Write( REG_LR_OPMODE, RFLR_OPMODE_SLEEP );            
    SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_SLEEP );       
    SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );     
    SX1276_Write( REG_LR_PACONFIG, 0x70 | node_parameter.PWR );  	//设置发送功率    0xff--17dB      0xfb--13dB      0xf8--10dB              
    if(Pout==1)
	{
        SX1276_Write( REG_LR_PADAC, RFLR_PADAC_20DBM_OFF );  
    }
	else
	{
    	SX1276_Write( REG_LR_PADAC, RFLR_PADAC_20DBM_ON );
    }
	SX1276_Write( REG_LR_PARAMP,RFLR_PARAMP_1000_US);            
    SX1276_Write( REG_LR_OCP,0x20|RFLR_OCP_TRIM_240_MA);         
    SX1276_Write( REG_LR_PAYLOADLENGTH,80); 
    
    SX1276_Write( REG_LR_MODEMCONFIG3,RFLR_MODEMCONFIG3_LOWDATARATEOPTIMIZE_ON | RFLR_MODEMCONFIG3_AGCAUTO_ON);      
          
    sx127x_set_payload_crc_on(RFLR_MODEMCONFIG2_RXPAYLOADCRC_ON);
	
    if(!sx127x_modify_frq(node_parameter.FRQ))    			//设置中心频率 
	{
		return SPI_READCHECK_WRONG;
	}
    
    return NORMAL;
}
//
void sx127x_reset(void)
{
	SX1276_Reset();                 	  //复位RF
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : RF发送数据包
// 输入参数 : uint8_t*data：发送数据指针，uint8_t size发送数据长度
// 返回参数 : 无
// 说明     : 设置为发送是， preamble改回默认值
////////////////////////////////////////////////////////////////////////////////
void sx127x_send_packet(uint8_t*data,uint8_t size)
{
    uint8_t irqflag;
    SX1276_Read(REG_LR_IRQFLAGS, &irqflag);
	
    SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );     
	SX1276_Write( REG_LR_PREAMBLEMSB,PREAMBLE_MSB);
	SX1276_Write( REG_LR_PREAMBLELSB,PREAMBLE_LSB);
    SX1276_Write( REG_LR_PAYLOADLENGTH,size);                    
    SX1276_EnableRFSW();   
    SX1276_Write(REG_LR_FIFOTXBASEADDR, 0x80);
    SX1276_Write( REG_LR_FIFOADDRPTR, 0x80);        	//0x80              
    SX1276_WriteBuffer(REG_LR_FIFO,data,size);                   
    SX1276_Write(REG_LR_IRQFLAGS,0xff);                          
    SX1276_Write( REG_LR_IRQFLAGSMASK, ~(RFLR_IRQFLAGS_TXDONE)); 
    SX1276_Write( REG_LR_DIOMAPPING1, RFLR_DIOMAPPING1_DIO0_01 );	//TxDone
	
    SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_TRANSMITTER );  	
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : RF进入接收状态
// 输入参数 : uint8_t clen 可变数据包下此值无效，固定数据包为长度值
// 返回参数 : 无
// 说明     : 进入接收后preamble设置回默认值
////////////////////////////////////////////////////////////////////////////////
void sx127x_rx_mode(uint8_t clen)
{
    uint8_t rxBase[1],temp;
    SX1276_Read(REG_LR_FIFORXCURRENTADDR,rxBase);
    
    SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );      
    SX1276_Write( REG_LR_PREAMBLEMSB,RECEVIOR_PREAMBLE_MSB);
	SX1276_Write( REG_LR_PREAMBLELSB,RECEVIOR_PREAMBLE_LSB);
    SX1276_Write( REG_LR_PAYLOADLENGTH,clen);   
    
    SX1276_Read(REG_LR_IRQFLAGSMASK, rxBase);
    SX1276_Write( REG_LR_IRQFLAGSMASK, ~(RFLR_IRQFLAGS_RXDONE) ); 
	
    SX1276_Read(REG_LR_IRQFLAGSMASK, rxBase);
    
    SX1276_Write( REG_LR_DIOMAPPING1, RFLR_DIOMAPPING1_DIO0_00 );
    SX1276_EnableRFSW();
    SX1276_Write(REG_LR_FIFORXBASEADDR,0x00);
    SX1276_Write( REG_LR_FIFOADDRPTR,0x00);      
	SX1276_Read(REG_LR_IRQFLAGS,&temp);   	
    SX1276_Write( REG_LR_IRQFLAGS,0xff);                          
    SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_RECEIVER );     
	
	temp = sx127x_get_opmode();
	while((temp&RFLR_OPMODE_RECEIVER) != RFLR_OPMODE_RECEIVER)
	{
		SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_RECEIVER );     
		temp = sx127x_get_opmode();
	}
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : RF接收可变数据包
// 输入参数 : uint8_t*cbuf接收数组指针,uint8_t *csize返回长度指针
// 返回参数 : 无
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
void sx127x_rx_vari_packet(uint8_t*cbuf,uint8_t *csize)
{
    uint8_t rxBase[1];
    SX1276_Read(REG_LR_NBRXBYTES,csize);
    //判断最多收到的字节数
    if(*csize > 128)
    {
        //超过接收缓存的最大容量，则抛弃
        return;
    }
    
    SX1276_Read(REG_LR_FIFORXCURRENTADDR,rxBase);
    SX1276_Write( REG_LR_FIFOADDRPTR,rxBase[0]);  
    SX1276_ReadFIFO(cbuf,*csize);              
    SX1276_Write(REG_LR_IRQFLAGS,0xff);        
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : RF接收固定数据包
// 输入参数 : uint8_t*cbuf接收数组指针,uint8_t csize接收固定长度
// 返回参数 : 无
// 说明     : 在速率10k时只能采用固定数据包长度
////////////////////////////////////////////////////////////////////////////////
void sx127x_rx_fixi_packet(uint8_t*cbuf,uint8_t csize)
{
    SX1276_Write( REG_LR_FIFOADDRPTR,0x00);  
    SX1276_ReadFIFO(cbuf,csize);              
    SX1276_Write(REG_LR_IRQFLAGS,0xff);      
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : RF进入SLEEP状态
// 输入参数 : 无
// 返回参数 : 无
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
void sx127x_sleep_mode(void)
{
    SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );     
    SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_SLEEP );     
	
	SX1276_RXE_OUT_LOW();
	SX1276_TXE_OUT_LOW();
	
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : RF进入standby状态
// 输入参数 : 无
// 返回参数 : 无
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
void sx127x_standby_mode(void)
{
    SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );      
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 获取射频模式
// 输入参数 : 无
// 返回参数 : 无
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
uint8_t sx127x_get_opmode(void)
{
	uint8_t mode;
	SX1276_Read( REG_LR_OPMODE, &mode);
	
	return mode;
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 设置射频模式
// 输入参数 : 无
// 返回参数 : 无
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
void sx127x_set_opmode(uint8_t mode)
{
	SX1276_Write( REG_LR_OPMODE, mode);
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 修改频段
// 输入参数 : 实际频段值*10，为了兼容212射频芯片
// 返回参数 : 无
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
uint8_t sx127x_modify_frq(uint16_t frq)
{
	uint8_t test_FRFMSB = 0,test_FRFMID=0,test_FRFLSB=0;
	uint8_t mode;
	
	mode = sx127x_get_opmode();
	
	sx127x_standby_mode();
	
	uint32_t frq_val = calc_frq(frq);
	uint8_t msb = (frq_val&0xff0000)>>16;
	uint8_t mid = (frq_val&0x00ff00)>>8;
	uint8_t lsb = frq_val&0xff;
	
	SX1276_Write( REG_LR_FRFMSB, msb);
	SX1276_Write( REG_LR_FRFMID, mid);
	SX1276_Write( REG_LR_FRFLSB, lsb);
	
	SX1276_Read(REG_LR_FRFMSB,&test_FRFMSB);
    SX1276_Read(REG_LR_FRFMID,&test_FRFMID);
    SX1276_Read(REG_LR_FRFLSB,&test_FRFLSB);
	
	if(test_FRFMSB != msb)
	{
		return 0;
	}
    if(test_FRFMID != mid)
	{
		return 0;
	}
    if(test_FRFLSB != lsb)
	{
		return 0;
	}
	
	sx127x_set_opmode(mode);	//还原模式
	
	return 1;
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 修改spd值
// 输入参数 : 
// 返回参数 : 
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
uint8_t sx127x_modify_spd(tSX127xInitSPD spd)
{
	uint8_t ret = 1;
	switch(spd)
	{
	/*
	case Init_LoRa_0_8K:
		SX1276_Write( REG_LR_MODEMCONFIG1, RFLR_MODEMCONFIG1_BW_125_KHZ + RFLR_MODEMCONFIG1_CODINGRATE_4_8 + RFLR_MODEMCONFIG1_IMPLICITHEADER_ON); 
		SX1276_Write( REG_LR_MODEMCONFIG2,RFLR_MODEMCONFIG2_SF_9 | RFLR_MODEMCONFIG2_RXPAYLOADCRC_OFF);     
		SX1276_Write( REG_LR_PREAMBLEMSB,PREAMBLE_MSB);
		SX1276_Write( REG_LR_PREAMBLELSB,PREAMBLE_LSB);
		break;
	case Init_LoRa_4_8K:      
		SX1276_Write( REG_LR_MODEMCONFIG1,RFLR_MODEMCONFIG1_BW_500_KHZ+RFLR_MODEMCONFIG1_CODINGRATE_4_8 | RFLR_MODEMCONFIG1_IMPLICITHEADER_OFF); 
		SX1276_Write( REG_LR_MODEMCONFIG2,RFLR_MODEMCONFIG2_SF_8 | RFLR_MODEMCONFIG2_RXPAYLOADCRC_OFF);     
		SX1276_Write( REG_LR_PREAMBLEMSB,PREAMBLE_MSB);
		SX1276_Write( REG_LR_PREAMBLELSB,PREAMBLE_LSB);
		break;
	case Init_LoRa_10K:
		SX1276_Read( 0x31,&test);
		SX1276_Write(  0x31,(test& 0xF8)|0x05);
		SX1276_Write(  0x37,0x0C);       
		SX1276_Write( REG_LR_MODEMCONFIG1,RFLR_MODEMCONFIG1_BW_500_KHZ+RFLR_MODEMCONFIG1_CODINGRATE_4_8 | RFLR_MODEMCONFIG1_IMPLICITHEADER_ON); 
		SX1276_Write( REG_LR_MODEMCONFIG2,RFLR_MODEMCONFIG2_SF_6 | RFLR_MODEMCONFIG2_RXPAYLOADCRC_OFF);     
		SX1276_Write( REG_LR_PREAMBLEMSB,PREAMBLE_MSB);
		SX1276_Write( REG_LR_PREAMBLELSB,PREAMBLE_LSB);
		break;
	*/
	case Init_LoRa_0_5K:
		SX1276_Write( REG_LR_MODEMCONFIG1,RFLR_MODEMCONFIG1_BW_125_KHZ | RFLR_MODEMCONFIG1_CODINGRATE_4_5 | RFLR_MODEMCONFIG1_IMPLICITHEADER_OFF); 
		SX1276_Write( REG_LR_MODEMCONFIG2,RFLR_MODEMCONFIG2_SF_12 | RFLR_MODEMCONFIG2_RXPAYLOADCRC_ON);     
		SX1276_Write( REG_LR_PREAMBLEMSB,PREAMBLE_MSB);
		SX1276_Write( REG_LR_PREAMBLELSB,PREAMBLE_LSB);
		break;
	case Init_LoRa_1K:
		SX1276_Write( REG_LR_MODEMCONFIG1,RFLR_MODEMCONFIG1_BW_250_KHZ | RFLR_MODEMCONFIG1_CODINGRATE_4_5 | RFLR_MODEMCONFIG1_IMPLICITHEADER_OFF); 
		SX1276_Write( REG_LR_MODEMCONFIG2,RFLR_MODEMCONFIG2_SF_11 | RFLR_MODEMCONFIG2_RXPAYLOADCRC_ON);     
		SX1276_Write( REG_LR_PREAMBLEMSB,PREAMBLE_MSB);
		SX1276_Write( REG_LR_PREAMBLELSB,PREAMBLE_LSB);
		break;
	case Init_LoRa_4K:
		SX1276_Write( REG_LR_MODEMCONFIG1,RFLR_MODEMCONFIG1_BW_250_KHZ | RFLR_MODEMCONFIG1_CODINGRATE_4_8 | RFLR_MODEMCONFIG1_IMPLICITHEADER_OFF); 
		SX1276_Write( REG_LR_MODEMCONFIG2,RFLR_MODEMCONFIG2_SF_8 | RFLR_MODEMCONFIG2_RXPAYLOADCRC_ON);     
		SX1276_Write( REG_LR_PREAMBLEMSB,PREAMBLE_MSB);
		SX1276_Write( REG_LR_PREAMBLELSB,PREAMBLE_LSB);
		break;
	case Init_LoRa_8K:
		SX1276_Write( REG_LR_MODEMCONFIG1,RFLR_MODEMCONFIG1_BW_500_KHZ | RFLR_MODEMCONFIG1_CODINGRATE_4_5 | RFLR_MODEMCONFIG1_IMPLICITHEADER_OFF); 
		SX1276_Write( REG_LR_MODEMCONFIG2,RFLR_MODEMCONFIG2_SF_7 | RFLR_MODEMCONFIG2_RXPAYLOADCRC_ON);     
		SX1276_Write( REG_LR_PREAMBLEMSB,PREAMBLE_MSB);
		SX1276_Write( REG_LR_PREAMBLELSB,PREAMBLE_LSB);
		break;
	case Init_LoRa_12K:
		SX1276_Write( REG_LR_MODEMCONFIG1,RFLR_MODEMCONFIG1_BW_500_KHZ | RFLR_MODEMCONFIG1_CODINGRATE_4_5 | RFLR_MODEMCONFIG1_IMPLICITHEADER_OFF); 
		SX1276_Write( REG_LR_MODEMCONFIG2,RFLR_MODEMCONFIG2_SF_7 | RFLR_MODEMCONFIG2_RXPAYLOADCRC_ON);     
		SX1276_Write( REG_LR_PREAMBLEMSB,PREAMBLE_MSB);
		SX1276_Write( REG_LR_PREAMBLELSB,PREAMBLE_LSB);
		break;
	default:
		ret = 0;
		break;
    
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 计算频段
// 输入参数 : 实际频段值*10，为了兼容212射频芯片
// 返回参数 : 无
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
uint32_t calc_frq(uint16_t frq)
{
	uint32_t frq_val = frq/10;
	frq_val = frq_val*1024*16;
	
	return frq_val;
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 获取RSSI值
// 输入参数 : 
// 返回参数 : 
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
uint8_t sx127x_get_rssi(void)
{
	uint8_t rssi, pktrssi, snr;
	SX1276_Read(REG_LR_RSSIVALUE, &rssi);
	SX1276_Read(REG_LR_PKTRSSIVALUE, &pktrssi);
	SX1276_Read(REG_LR_PKTSNRVALUE, &snr);
	
//	printf("rssi = %d, pktrssi = %d, snr = %d \n", rssi, pktrssi, snr);
	
	return pktrssi;
}

void sx127x_set_payload_crc_on(uint8_t on)
{
	uint8_t temp;
	SX1276_Read( REG_LR_MODEMCONFIG2, &temp);
	temp = temp & RFLR_MODEMCONFIG2_RXPAYLOADCRC_MASK;
	on = on & (~RFLR_MODEMCONFIG2_RXPAYLOADCRC_MASK);
	temp = on | temp;
	SX1276_Write( REG_LR_MODEMCONFIG2,temp); 
}

uint8_t sx127x_read_bw(void)
{
	uint8_t bw;
	SX1276_Read( REG_LR_MODEMCONFIG1,&bw); 
	
	bw = bw&(~RFLR_MODEMCONFIG1_BW_MASK);
	
	return bw;
}

void sx127x_modify_bw(uint8_t bw)
{
	uint8_t temp;
	SX1276_Read( REG_LR_MODEMCONFIG1,&temp); 
	temp = temp & RFLR_MODEMCONFIG1_BW_MASK;
    bw = bw&(~RFLR_MODEMCONFIG1_BW_MASK);
	temp = temp | bw;
	SX1276_Write( REG_LR_MODEMCONFIG1,temp); 
}

uint8_t sx127x_read_cr(void)
{
	uint8_t cr;
	SX1276_Read( REG_LR_MODEMCONFIG1,&cr); 
	
	cr = cr&(~RFLR_MODEMCONFIG1_CODINGRATE_MASK);
	
	return cr;
}

void sx127x_modify_cr(uint8_t cr)
{
	uint8_t temp;
	SX1276_Read( REG_LR_MODEMCONFIG1,&temp); 
	temp = temp & RFLR_MODEMCONFIG1_CODINGRATE_MASK;
    cr = cr & (~RFLR_MODEMCONFIG1_CODINGRATE_MASK);
	temp = temp | cr;
	SX1276_Write( REG_LR_MODEMCONFIG1,temp); 
}

uint8_t sx127x_read_sf(void)
{
	uint8_t sf;
	SX1276_Read( REG_LR_MODEMCONFIG2,&sf); 
	
	sf = sf&(~RFLR_MODEMCONFIG2_SF_MASK);
	
	return sf;
}

void sx127x_modify_sf(uint8_t sf)
{
	uint8_t temp;
	SX1276_Read( REG_LR_MODEMCONFIG2,&temp); 
	temp = temp & RFLR_MODEMCONFIG2_SF_MASK;
    sf = sf&(~RFLR_MODEMCONFIG2_SF_MASK);
	temp = temp | sf;
	SX1276_Write( REG_LR_MODEMCONFIG2,temp); 
}

uint8_t check_bw(uint8_t bw)
{
	if(bw == RFLR_MODEMCONFIG1_BW_7_81_KHZ ||
	   bw == RFLR_MODEMCONFIG1_BW_10_41_KHZ ||
	   bw == RFLR_MODEMCONFIG1_BW_15_62_KHZ ||
	   bw == RFLR_MODEMCONFIG1_BW_20_83_KHZ ||
	   bw == RFLR_MODEMCONFIG1_BW_31_25_KHZ ||
	   bw == RFLR_MODEMCONFIG1_BW_41_66_KHZ ||
	   bw == RFLR_MODEMCONFIG1_BW_62_50_KHZ ||
	   bw == RFLR_MODEMCONFIG1_BW_125_KHZ ||
	   bw == RFLR_MODEMCONFIG1_BW_250_KHZ ||
	   bw == RFLR_MODEMCONFIG1_BW_500_KHZ )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t check_cr(uint8_t cr)
{
	if(cr == RFLR_MODEMCONFIG1_CODINGRATE_4_5 ||
	   cr == RFLR_MODEMCONFIG1_CODINGRATE_4_6 ||
	   cr == RFLR_MODEMCONFIG1_CODINGRATE_4_7 ||
	   cr == RFLR_MODEMCONFIG1_CODINGRATE_4_8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t check_sf(uint8_t sf)
{
	if(sf == RFLR_MODEMCONFIG2_SF_6 ||
	   sf == RFLR_MODEMCONFIG2_SF_7 ||
	   sf == RFLR_MODEMCONFIG2_SF_8 ||
	   sf == RFLR_MODEMCONFIG2_SF_9 ||
	   sf == RFLR_MODEMCONFIG2_SF_10 ||
	   sf == RFLR_MODEMCONFIG2_SF_11 ||
	   sf == RFLR_MODEMCONFIG2_SF_12)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


uint16_t get_spd_parameter(void)
{
	int i;
	uint16_t timeout;
	for(i=0; i<SPD_PARAMETER_LEN/4; i++)
	{
		if(    node_parameter.SBW == LORA_SPD_PARMATER[i*4]
			&& node_parameter.SCR == LORA_SPD_PARMATER[i*4+1]
			&& node_parameter.SSF == LORA_SPD_PARMATER[i*4+2])
		{
			timeout = LORA_SPD_PARMATER[i*4+3];
			break;
		}
	}
	return timeout;
}

void start_cad(void)
{
	uint8_t temp;
	SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );
	SX1276_Write( REG_LR_DIOMAPPING1, RFLR_DIOMAPPING1_DIO0_10 );	//CADDone
	
	SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_CAD );
	temp = sx127x_get_opmode();
	while((temp&RFLR_OPMODE_CAD) != RFLR_OPMODE_CAD)
	{
		SX1276_Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_CAD );     
		temp = sx127x_get_opmode();
	}
}

void convert_sbw_to_ascii(uint8_t sbw, uint8_t* buffer, uint8_t* len)
{
	switch(sbw)
	{
		case 0x00:
			*len = 4;
			memcpy(buffer, "7_81", *len);
			break;
		case 0x10:
			*len = 5;
			memcpy(buffer, "10_41", *len);
			break;
		case 0x20:
			*len = 5;
			memcpy(buffer, "15_62", *len);
			break;
		case 0x30:
			*len = 5;
			memcpy(buffer, "20_83", *len);
			break;
		case 0x40:
			*len = 5;
			memcpy(buffer, "31_25", *len);
			break;
		case 0x50:
			*len = 5;
			memcpy(buffer, "41_66", *len);
			break;
		case 0x60:
			*len = 5;
			memcpy(buffer, "62_50", *len);
			break;
		case 0x70:
			*len = 3;
			memcpy(buffer, "125", *len);
			break;
		case 0x80:
			*len = 3;
			memcpy(buffer, "250", *len);
			break;
		case 0x90:
			*len = 3;
			memcpy(buffer, "500", *len);
			break;
		default:
			break;
	}
}

uint8_t convert_ascii_to_sbw(uint8_t* bw_str)
{
	uint8_t bw = 0xff;
	if(strncmp((char*)bw_str, "7_81", 4)==0)		bw = 0x00;
	else if(strncmp((char*)bw_str, "10_41", 5)==0)	bw = 0x10;
	else if(strncmp((char*)bw_str, "15_62", 5)==0)	bw = 0x20;
	else if(strncmp((char*)bw_str, "20_83", 5)==0)	bw = 0x30;
	else if(strncmp((char*)bw_str, "31_25", 5)==0)	bw = 0x40;
	else if(strncmp((char*)bw_str, "41_66", 5)==0)	bw = 0x50;
	else if(strncmp((char*)bw_str, "62_50", 5)==0)	bw = 0x60;
	else if(strncmp((char*)bw_str, "125", 3)==0)	bw = 0x70;
	else if(strncmp((char*)bw_str, "250", 3)==0)	bw = 0x80;
	else if(strncmp((char*)bw_str, "500", 3)==0)	bw = 0x90;
	
	return bw;
}

void convert_scr_to_ascii(uint8_t scr, uint8_t* buffer, uint8_t* len)
{
	switch(scr)
	{
		case 0x02:
			*len = 3;
			memcpy(buffer, "4_5", *len);
			break;
		case 0x04:
			*len = 3;
			memcpy(buffer, "4_6", *len);
			break;
		case 0x06:
			*len = 3;
			memcpy(buffer, "4_7", *len);
			break;
		case 0x08:
			*len = 3;
			memcpy(buffer, "4_8", *len);
			break;
		default:
			break;
	}
}

uint8_t convert_ascii_to_scr(uint8_t* cr_str)
{
	uint8_t cr = 0xff;
	if(strncmp((char*)cr_str, "4_5", 4)==0)			cr = 0x02;
	else if(strncmp((char*)cr_str, "4_6", 5)==0)	cr = 0x04;
	else if(strncmp((char*)cr_str, "4_7", 5)==0)	cr = 0x06;
	else if(strncmp((char*)cr_str, "4_8", 5)==0)	cr = 0x08;
	
	return cr;
}

void convert_ssf_to_ascii(uint8_t ssf, uint8_t* buffer, uint8_t* len)
{
	switch(ssf)
	{
		case 0x60:
			*len = 1;
			memcpy(buffer, "6", *len);
			break;
		case 0x70:
			*len = 1;
			memcpy(buffer, "7", *len);
			break;
		case 0x80:
			*len = 1;
			memcpy(buffer, "8", *len);
			break;
		case 0x90:
			*len = 1;
			memcpy(buffer, "9", *len);
			break;
		case 0xA0:
			*len = 2;
			memcpy(buffer, "10", *len);
			break;
		case 0xB0:
			*len = 2;
			memcpy(buffer, "11", *len);
			break;
		case 0xC0:
			*len = 2;
			memcpy(buffer, "12", *len);
			break;
		default:
			break;
	}
}

uint8_t convert_ascii_to_ssf(uint8_t* ssf_str)
{
	uint8_t ssf = 0xff;
	if(strncmp((char*)ssf_str, "6", 4)==0)		ssf = 0x60;
	else if(strncmp((char*)ssf_str, "7", 4)==0)	ssf = 0x70;
	else if(strncmp((char*)ssf_str, "8", 4)==0)	ssf = 0x80;
	else if(strncmp((char*)ssf_str, "9", 4)==0)	ssf = 0x90;
	else if(strncmp((char*)ssf_str, "10", 5)==0)	ssf = 0xA0;
	else if(strncmp((char*)ssf_str, "11", 5)==0)	ssf = 0xB0;
	else if(strncmp((char*)ssf_str, "12", 5)==0)	ssf = 0xC0;
	
	return ssf;
}
