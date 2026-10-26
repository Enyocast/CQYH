#include "stdafx.h"
#include "time_ex.h"

#include <time.h>

static tm_ex t;

#if defined(WIN32) | defined(WIN64)
const tm_ex* localtime_ex(void)
{
	SYSTEMTIME SystemTime;

	GetLocalTime(&SystemTime);

	t.tm_msec = SystemTime.wMilliseconds;
	t.tm_sec = SystemTime.wSecond;
	t.tm_min = SystemTime.wMinute;
	t.tm_hour = SystemTime.wHour;
	t.tm_mday = SystemTime.wDay;
	t.tm_mon = SystemTime.wMonth;
	t.tm_year = SystemTime.wYear;
	t.tm_wday = SystemTime.wDayOfWeek;

	return &t;
}
#else
const tm_ex* localtime_ex(void)
{
    time_t CurrentTime;
    struct tm* tm;

    time(&CurrentTime);
    tm = localtime(&CurrentTime);

    t.tm_msec = 0;
    t.tm_sec = tm->tm_sec;
    t.tm_min = tm->tm_min;
    t.tm_hour = tm->tm_hour;
    t.tm_mday = tm->tm_mday;
    t.tm_mon = tm->tm_mon + 1;
    t.tm_year = tm->tm_year + 1900;
    t.tm_wday = tm->tm_wday;

    return &t;
}
#endif	// WIN32

bool is_leap_year(int nYear)
{
    if (nYear % 100 == 0)
    {
        if (nYear % 400 == 0)
            return true;
        else
            return false;
    }
    else
    {
        if (nYear % 4 == 0)
            return true;
        else
            return false;
    }
}

int get_month_day_count(int nYear, int nMonth)
{
    static int nMonthDayCount[] =
    {
        31, // Jan 
        28, // Feb
        31, // Mar
        30, // Apr
        31, // May
        30, // Jun
        31, // Jul
        31, // Aug
        30, // Sep
        31, // Oct
        30, // Nov
        31, // Dec
    };

    if (nMonth == 1 && is_leap_year(nYear))
        return 29;
    else
        return nMonthDayCount[nMonth];
}

UINT64 GetTickCountEx()
{
#if (defined(WIN32) || defined(WIN64))
	return GetTickCount64();
#else
	struct timeval cateq_v;

	gettimeofday(&cateq_v, NULL);

	return 1000LL * cateq_v.tv_sec + cateq_v.tv_usec / 1000LL;
#endif //
}

const char*	get_time_str(UINT32 dwTime)
{
	static char s_szTime[64];
	time_t t = dwTime;

	struct tm* stCurrenttm = localtime(&t);
	if (stCurrenttm)
	{
		snprintf(s_szTime, 64, "%d-%02d-%02d %02d:%02d:%02d", (stCurrenttm->tm_year + 1900),
			(stCurrenttm->tm_mon + 1), stCurrenttm->tm_mday, stCurrenttm->tm_hour, stCurrenttm->tm_min, stCurrenttm->tm_sec);
		if (stCurrenttm->tm_year + 1900 == 2150)
			INT3();
	}
	else
	{
		itoa(dwTime, s_szTime, 10);
	}

	return s_szTime;
}

int get_time_zone(void)
{
	time_t now = time(NULL);

	struct tm* gt = gmtime(&now);
	time_t gmt = mktime(gt);

	struct tm* lt = localtime(&now);
	time_t lmt = mktime(lt);

	return difftime(lmt, gmt);
}
