/********************************************************************
	created:	25:3:2013   15:45
	file:		master_award.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_MASTER_GIFT_H_
#define _H_MASTER_GIFT_H_

#include "data_manager.h"

const UINT32        MASTER_CONG_LVL_UP_TYPE_NUM = 3;


struct MS_MASTER_GIFT_TEMPLATE
{
    UINT32          m_dwLevel;
    UINT32          m_dwLvlUpStudMailID;
    UINT32          m_dwLvlUpTeacherMailID;

    INT32           m_arrCZMoneyConsume[MASTER_CONG_LVL_UP_TYPE_NUM];

    UINT32          m_arrCZT2STeacherMailID[MASTER_CONG_LVL_UP_TYPE_NUM];
    UINT32          m_arrCZT2SStudentMailID[MASTER_CONG_LVL_UP_TYPE_NUM];

    UINT32          m_arrCZS2TTeacherMailID[MASTER_CONG_LVL_UP_TYPE_NUM];
    UINT32          m_arrCZS2TStudentMailID[MASTER_CONG_LVL_UP_TYPE_NUM];

    UINT32          m_arrCZC2CSelfMailID[MASTER_CONG_LVL_UP_TYPE_NUM];
    UINT32          m_arrCZC2CTargetMailID[MASTER_CONG_LVL_UP_TYPE_NUM];

	static BOOL HasName(void)	{ return FALSE; }

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, MS_MASTER_GIFT_TEMPLATE* pData, CTabFile* pTabConfig, INT32 nRow);
};


const MS_MASTER_GIFT_TEMPLATE* GetMasterGiftTemplate(INT8 nTemplateID);

#endif //_H_MASTER_GIFT_H_




