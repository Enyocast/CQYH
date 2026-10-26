/********************************************************************
	created:	7:6:2013   16:50
	file:		time_washout_mgr.cpp
	author:		Allan Tao
	
	purpose:	时间定时淘汰，用于各种记录申请
*********************************************************************/

#include "stdafx.h"
#include "time_washout_mgr.h"

CTimeWashoutMgr  CTimeWashoutMgr::m_Instance;
CTimeWashoutMgr &CTimeWashoutMgr::GetInstance()
{
    return m_Instance;
}

CTimeWashoutMgr::CTimeWashoutMgr()
{

}

CTimeWashoutMgr::~CTimeWashoutMgr()
{

}

BOOL CTimeWashoutMgr::Init()
{
    m_pTimerHeader[0] = NULL;

    return TRUE;
}

BOOL CTimeWashoutMgr::PushBack(WASHOUT_BASE *pNode)
{
    return TRUE;
}

BOOL CTimeWashoutMgr::Remove(WASHOUT_BASE *pNode)
{
    return TRUE;
}

BOOL CTimeWashoutMgr::MainLoop()
{
    return TRUE;
}




