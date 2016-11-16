#include "software_version.h"

#define Jan	(('J'<<16)+('a'<<8)+('n'))
#define Feb	(('F'<<16)+('e'<<8)+('b'))
#define Mar	(('M'<<16)+('a'<<8)+('r'))
#define Apr	(('A'<<16)+('p'<<8)+('r'))
#define May	(('M'<<16)+('a'<<8)+('y'))
#define Jun	(('J'<<16)+('u'<<8)+('n'))
#define Jul	(('J'<<16)+('u'<<8)+('l'))
#define Aug	(('A'<<16)+('u'<<8)+('g'))
#define Sep	(('S'<<16)+('e'<<8)+('p'))
#define Oct	(('O'<<16)+('c'<<8)+('t'))
#define Nov	(('N'<<16)+('o'<<8)+('v'))
#define Dec	(('D'<<16)+('e'<<8)+('c'))


#define GEN_MON_TO_VALUE(x,y,z) (((x)<<16)+((y)<<8) + (z))
#define GEN_MON_HIGH(x, y, z)		(((GEN_MON_TO_VALUE(x,y,z) == Jan)?'0':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Feb)?'0':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Mar)?'0':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Apr)?'0':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == May)?'0':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Jun)?'0':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Jul)?'0':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Aug)?'0':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Sep)?'0':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Oct)?'1':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Nov)?'1':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Dec)?'1':0)\
									)
#define GEN_MON_LOW(x, y, z)	   (((GEN_MON_TO_VALUE(x,y,z) == Jan)?'1':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Feb)?'2':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Mar)?'3':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Apr)?'4':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == May)?'5':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Jun)?'6':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Jul)?'7':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Aug)?'8':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Sep)?'9':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Oct)?'0':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Nov)?'1':0)+\
									((GEN_MON_TO_VALUE(x,y,z) == Dec)?'2':0)\
									)




#define GEN_SOFTWARE_VERSION_DATE()	(__DATE__[9]), \
	(__DATE__[10]), \
	GEN_MON_HIGH(__DATE__[0], __DATE__[1], __DATE__[2]),\
	GEN_MON_LOW(__DATE__[0], __DATE__[1], __DATE__[2]),\
	((__DATE__[4] == ' ')?'0':__DATE__[4]),\
	(__DATE__[5]),\
	(__TIME__[0]),\
	(__TIME__[1])

#define MAJOR_SOFTWARE_VERSION(x)	(x+'0')
#define MINOR_SOFTWARE_VERSION(x)	(x+'0')


#define GEN_SOFTWARE_VERSION(major, minor)	{\
			MAJOR_SOFTWARE_VERSION(major),\
			MINOR_SOFTWARE_VERSION(minor),\
			GEN_SOFTWARE_VERSION_DATE()\
}

const uint8_t software_version[]  __attribute__ ((at(0x00001000))) =  GEN_SOFTWARE_VERSION(2,0);	//设置变量处于0x00001000这个地址

void get_software_version(uint8_t *version_buff, uint8_t *version_len)
{
	*version_len = sizeof(software_version);
	memcpy(version_buff, software_version, sizeof(software_version));	
}

int software_version_compare(uint8_t *buff)
{
	int ret;

	ret = memcmp(software_version, buff, 10);
	return ret;
}

