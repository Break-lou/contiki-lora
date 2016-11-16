#include "timestamp.h"

static const unsigned char mon_lengths[2][MONSPERYEAR] = {
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,}
};

static const unsigned short year_lengths[2] = {365, 366,};
static const unsigned short _DAYS_BEFORE_MONTH[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,};

void gmtime_new(tm_new * res, unsigned long timestamp) {
    unsigned long days, rem,temp_d;
    unsigned int y;
    unsigned int yleap;
    const unsigned char * ip;

	timestamp += LOCALTIMEADJ;	   // 标准时间戳应加上该句
    days = timestamp / SECSPERDAY; // 得到天
    rem  = timestamp % SECSPERDAY; // 得到天之后秒数

    /* compute hour, min, and sec */
    temp_d = (rem / SECSPERHOUR);
    res->tm_hour = temp_d;
    temp_d = rem % SECSPERHOUR;
    rem = temp_d;
    res->tm_min = (rem / SECSPERMIN);
    res->tm_sec = (rem % SECSPERMIN);

    /* compute day of week */
    if ((res->tm_wday = ((EPOCH_WDAY + days) % DAYSPERWEEK)) < 0)
        res->tm_wday += DAYSPERWEEK;

    /* compute year & day of year */
    y = EPOCH_YEAR;
    for (;;) {
        yleap = isleap(y);
        if (days < year_lengths[yleap]) 
            break;

        y++;
        days -= year_lengths[yleap];
    }

    res->tm_year = y - YEAR_BASE;
    res->tm_yday = days;
    ip = mon_lengths[yleap];
    for (res->tm_mon = 0; days >= ip[res->tm_mon]; ++res->tm_mon) {
        days -= ip[res->tm_mon];
    }

	res->tm_mon += 1;	// 标准时间戳应加上该句
    res->tm_mday = days + 1;

    /* set daylight saving time flag */
    res->tm_isdst = -1;
}

unsigned long mktime_new(tm_new *tim_p) {
    unsigned long tim=0;
    unsigned long days = 0;
    unsigned long year;

    /* compute hours, minutes, seconds */
    tim += tim_p->tm_sec + (tim_p->tm_min * _SEC_IN_MINUTE) +
           ((tim_p->tm_hour) * _SEC_IN_HOUR);

    /* compute days in year */
    days += tim_p->tm_mday - 1;
    days += _DAYS_BEFORE_MONTH[tim_p->tm_mon-1];	 

    if (tim_p->tm_mon > 1 && _DAYS_IN_YEAR (tim_p->tm_year) == 366)
        days++;

    /* compute days in other years */
    for (year = 70; year < tim_p->tm_year; year++)
        days += _DAYS_IN_YEAR (year);

    /* compute total seconds */
    tim += (days * _SEC_IN_DAY);
	tim -= LOCALTIMEADJ;   // 标准时间戳应加上该句

    return tim;
}
