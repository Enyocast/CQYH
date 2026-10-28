#ifndef _H_TITLE_DATA_H_
#define _H_TITLE_DATA_H_

#include "string_def.h"
#include "data_manager.h"

static const INT16  TitleAttrTableSize = 5; 
static const INT16  TitleConditionTableSize = 2;
struct TITLE_TEMPLATE
{
    UINT8       m_nTemplateID;
    char        m_szName[MAX_TITLE_NAME_LEN];
    INT32       m_nValidTime;
    INT32       nPow;

    //INT32       m_nAttrNum;
    //struct TitleAttrTemplate
    //{
    //    INT16 shAttrType;
    //    INT16 shParam;
    //};
    //INT32 m_Attr[TitleAttrTableSize];

    INT32 m_nAttrID[TitleAttrTableSize];        // redmine bug : 7943

    INT32 m_nNodeCount;
    INT32 m_nNodeIDs[TitleAttrTableSize];

    struct TitleCondition
    {
        INT16 shConType;
        INT16 shConValue;
    };
    TitleCondition m_Condition[2];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, TITLE_TEMPLATE* pData, CTabFile* pTabConfig, INT32 nRow);
};

const TITLE_TEMPLATE* GetTitleTemplate(INT8 nTemplateID);

#endif //_H_TITLE_DATA_H_







