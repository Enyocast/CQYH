#ifndef _BASE_LIST_H_
#define _BASE_LIST_H_

struct BASE_LIST_NODE
{
	BASE_LIST_NODE*	pPrev;
	BASE_LIST_NODE* pNext;
};

inline void ClearNode(BASE_LIST_NODE* pNode)
{
	pNode->pPrev = NULL;
	pNode->pNext = NULL;
}

class CBaseList
{
public:
	CBaseList()
    {
		Clear();
    }
	~CBaseList()
    {
        LOG_CHECK_ERROR(m_Head.pPrev == NULL);
        LOG_CHECK_ERROR(m_Head.pNext == &m_Rear);
        LOG_CHECK_ERROR(m_Rear.pPrev == &m_Head);
        LOG_CHECK_ERROR(m_Rear.pNext == NULL);
    }

	inline void Clear(void);
	inline BOOL IsEmpty(void);

	inline BASE_LIST_NODE& Head(void);
	inline BASE_LIST_NODE& Rear(void);

	static inline BOOL InsertAfter(BASE_LIST_NODE* pNewNode, BASE_LIST_NODE* pInsertAfter);
	static inline BOOL InsertBefore(BASE_LIST_NODE* pNewNode, BASE_LIST_NODE* pInsertAfter);

	static inline BOOL Remove(BASE_LIST_NODE* pNode);

	inline BOOL PushHead(BASE_LIST_NODE* pNode);
	inline BASE_LIST_NODE* PopHead(void);

	inline BOOL PushRear(BASE_LIST_NODE* pNode);
	inline BASE_LIST_NODE* PopRear(void);

private:
	BASE_LIST_NODE  m_Head;
	BASE_LIST_NODE  m_Rear;
};

#define node_cast(__obj_class_ptr__, __member__, __node_ptr__)  \
	((__obj_class_ptr__)((char*)(__node_ptr__) - (char*)&(((__obj_class_ptr__)0)->__member__)))

inline void CBaseList::Clear()
{
	m_Head.pPrev = NULL;
	m_Head.pNext = &m_Rear;
	m_Rear.pPrev = &m_Head;
	m_Rear.pNext = NULL;
}

inline BOOL CBaseList::IsEmpty()
{
#ifdef _DEBUG
	LOG_PROCESS_ERROR(m_Head.pPrev == NULL);
	LOG_PROCESS_ERROR(m_Rear.pNext == NULL);
	PROCESS_ERROR(m_Head.pNext == &m_Rear);
#endif	// _DEBUG

	PROCESS_ERROR(m_Rear.pPrev == &m_Head);

	return TRUE;
Exit0:
	return FALSE;
}

inline BASE_LIST_NODE& CBaseList::Head(void)
{
	return m_Head;
}

inline BASE_LIST_NODE& CBaseList::Rear(void)
{
	return m_Rear;
}

inline BOOL CBaseList::InsertAfter(BASE_LIST_NODE* pNewNode, BASE_LIST_NODE* pTargetNode)
{
	LOG_PROCESS_ERROR(pNewNode && pTargetNode);
	LOG_PROCESS_ERROR(pNewNode->pPrev == NULL && pNewNode->pNext == NULL);
	LOG_PROCESS_ERROR(pTargetNode->pNext);

	pNewNode->pPrev = pTargetNode;

//	if(pTargetNode->pNext)
	{
		pNewNode->pNext = pTargetNode->pNext;
		pTargetNode->pNext->pPrev = pNewNode;
	}

	pTargetNode->pNext = pNewNode;

	return TRUE;
Exit0:

	return FALSE;
}

inline BOOL CBaseList::InsertBefore(BASE_LIST_NODE* pNewNode, BASE_LIST_NODE* pTargetNode)
{
	LOG_PROCESS_ERROR(pNewNode && pTargetNode);
	LOG_PROCESS_ERROR(pNewNode->pPrev == NULL && pNewNode->pNext == NULL);
	LOG_PROCESS_ERROR(pTargetNode->pPrev);

	pNewNode->pNext = pTargetNode;
//	if(pTargetNode->pPrev)
	{
		pNewNode->pPrev = pTargetNode->pPrev;
		pTargetNode->pPrev->pNext = pNewNode;

	}
	pTargetNode->pPrev = pNewNode;

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CBaseList::Remove(BASE_LIST_NODE* pNode)
{
	LOG_PROCESS_ERROR(pNode);
	PROCESS_ERROR(pNode->pPrev && pNode->pNext);

	pNode->pPrev->pNext = pNode->pNext;
	pNode->pNext->pPrev = pNode->pPrev;

	pNode->pNext = pNode->pPrev = NULL;

	return TRUE;
Exit0:

	return FALSE;
}

inline BOOL CBaseList::PushHead(BASE_LIST_NODE* pNode)
{
	LOG_PROCESS_ERROR(pNode->pNext == NULL && pNode->pPrev == NULL);

	pNode->pPrev = &m_Head;
	pNode->pNext = m_Head.pNext;

	pNode->pNext->pPrev = pNode;
	m_Head.pNext = pNode;

	return TRUE;
Exit0:
	return FALSE;
}

inline BASE_LIST_NODE* CBaseList::PopHead(void)
{
	BASE_LIST_NODE* pResult = NULL;

	PROCESS_ERROR(m_Head.pNext != &m_Rear);

	pResult = m_Head.pNext;
	m_Head.pNext = pResult->pNext;
	pResult->pNext->pPrev = &m_Head;

	pResult->pPrev = pResult->pNext = NULL;

	return pResult;
Exit0:
	return NULL;
}

inline BOOL CBaseList::PushRear(BASE_LIST_NODE* pNode)
{
	LOG_PROCESS_ERROR(pNode->pNext == NULL && pNode->pPrev == NULL);

	pNode->pPrev = m_Rear.pPrev;
	pNode->pNext = &m_Rear;

	m_Rear.pPrev = pNode;
	pNode->pPrev->pNext = pNode;

	return TRUE;
Exit0:
	return FALSE;
}

inline BASE_LIST_NODE* CBaseList::PopRear(void)
{
	BASE_LIST_NODE* pResult = NULL;

	PROCESS_ERROR(m_Rear.pPrev != &m_Head);

	pResult = m_Rear.pPrev;
	m_Rear.pPrev = pResult->pPrev;
	pResult->pPrev->pNext = &m_Rear;

	pResult->pPrev = pResult->pNext = NULL;

	return pResult;
Exit0:
	return NULL;
}

#endif	// _BASE_LIST_H_