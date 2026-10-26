#include "stdafx.h"
#include "processed_mails.h"

void CProMails::Clear()
{
    m_lstProcessedMailID.clear();
}

void CProMails::AddProcessMail(UINT32 mailid)
{
    while (m_lstProcessedMailID.size() >= 10)
        m_lstProcessedMailID.pop_front();

    m_lstProcessedMailID.push_back(mailid);
}

