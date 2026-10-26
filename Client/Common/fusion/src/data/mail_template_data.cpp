#include "stdafx.h"
#include "mail_template_data.h"

BOOL MAIL_TEMPLATE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, MAIL_TEMPLATE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();
    char* pValue = NULL;
    char szValue[128] = { 0 };

    READ_INT("TemplateID", m_nTemplateID);
    READ_STR("MailSubject", m_szMailSubject);
    READ_STR("MailContent", m_szMailContent);
    READ_INT("ItemID", m_nItemID);
    READ_INT("ItemCount", m_nItemCount);

    READ_END(m_nTemplateID);
}
