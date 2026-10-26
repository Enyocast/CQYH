#ifndef _PROCESSED_MAIL_IDS_H_
#define _PROCESSED_MAIL_IDS_H_

class CProMails
{
public:
    void Clear();
    void AddProcessMail(UINT32 mailid);

	BOOL Load_v_1(const char* pcData, UINT32 dwSize);
    BOOL Save(const char* pcData, UINT32& rdwSize);

private:
    std::list<UINT32> m_lstProcessedMailID;
};

#endif // _PROCESSED_MAIL_IDS_H_
