/********************************************************************
	created:	1:3:2014   11:09
	file:		gm_log.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#include "stdafx.h"
#include "gm_log.h"
#include "gm_manager.h"

#include "gmtool.h"

CGMLog  CGMLog::m_Instance;

CGMLog &CGMLog::GetInstance()
{
    return m_Instance;
}

CGMLog::CGMLog()
{

}

CGMLog::~CGMLog()
{

}



BOOL CGMLog::Init()
{

    return TRUE;
}

BOOL CGMLog::UnInit()
{

    return TRUE;
}




BOOL CGMLog::Log(const char *pcszLog, ...)
{
    INT32       nRetCode = 0;
    char        szMessage[1024*4] = {0};

    LOG_PROCESS_ERROR(pcszLog);

    va_list     vaList;

    va_start(vaList, pcszLog);
    vsnprintf(szMessage, 1024*4, pcszLog, vaList);

    nRetCode = g_gmtool.OutputLog(szMessage);
    LOG_PROCESS_ERROR(nRetCode);

    INF(szMessage);


    va_end(vaList);

    return TRUE;
Exit0:
    return FALSE;
}







