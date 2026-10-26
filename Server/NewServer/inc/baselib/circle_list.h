#ifndef _CIRCLE_LIST_H_
#define _CIRCLE_LIST_H_

// This circle list is thread-safe for SISO
class CCircleList
{
public:
    CCircleList();
    ~CCircleList();

    BOOL Init(UINT32 dwSize);
    BOOL UnInit(void);

	inline BOOL Push(void* pData);
	inline void* Pop(void);
	inline void* Check(void);
	inline BOOL IsEmpty(void);

private:
    UINT32  m_dwSize;
    UINT32  m_dwHead;
    UINT32  m_dwRear;
    void**  m_ppData;
};

inline BOOL CCircleList::Push(void* pData)
{
	PROCESS_ERROR(m_dwSize > 0);
	PROCESS_ERROR((m_dwRear + 1) % m_dwSize != m_dwHead);

	PROCESS_ERROR(m_ppData);
	m_ppData[m_dwRear] = pData;
	m_dwRear = (m_dwRear + 1) % m_dwSize;

	return TRUE;
Exit0:
	return FALSE;
}

inline void* CCircleList::Pop(void)
{
	void* pResult = NULL;

	PROCESS_ERROR(m_dwRear != m_dwHead);

	pResult = m_ppData[m_dwHead];
	m_dwHead = (m_dwHead + 1) % m_dwSize;

Exit0:
	return pResult;
}

inline void* CCircleList::Check(void)
{
	PROCESS_ERROR(m_dwRear != m_dwHead);

	return m_ppData[m_dwHead];
Exit0:
	return NULL;
}

inline BOOL CCircleList::IsEmpty(void)
{
	return m_dwHead == m_dwRear;
}

#endif  // _CIRCLE_LIST_H_