#ifndef simple_list_h__
#define simple_list_h__

struct SimpleListNode
{
	SimpleListNode* pNext;
};

class CSimpleList
{
public:
	CSimpleList(void)
	{
		Clear();
	}

	~CSimpleList(void)
	{
		LOG_CHECK_ERROR(m_Top.pNext == NULL);
	}

	inline void Clear(void);
	inline BOOL IsEmpty(void);
	inline INT32 Size(void);

	inline void Push(SimpleListNode* pNode);
	inline SimpleListNode* Pop(void);
	inline SimpleListNode* Top(void);

	inline BOOL InsertAfter(SimpleListNode* pTargetNode, SimpleListNode* pInsertNode);
	inline BOOL InsertBefore(SimpleListNode* pTargetNode, SimpleListNode* pInsertNode);

	inline BOOL Remove(SimpleListNode* pNode);

private:
	SimpleListNode m_Top;
	INT32 m_nSize;
};

inline SimpleListNode* CSimpleList::Top(void)
{
	PROCESS_ERROR(!IsEmpty());
	return m_Top.pNext;
Exit0:
	return NULL;
}

inline SimpleListNode* CSimpleList::Pop(void)
{
	SimpleListNode* pNode = NULL;
	PROCESS_ERROR(!IsEmpty());

	pNode = m_Top.pNext;
	m_Top.pNext = pNode->pNext;

	pNode->pNext = NULL;

	m_nSize--;

	return pNode;
Exit0:
	return NULL;
}

inline void CSimpleList::Push(SimpleListNode* pNode)
{
	LOG_PROCESS_ERROR(pNode->pNext == NULL);

	pNode->pNext = m_Top.pNext;
	m_Top.pNext = pNode;
	m_nSize++;
Exit0:
	return;
}

inline BOOL CSimpleList::IsEmpty(void)
{
	return m_Top.pNext == NULL;
}

inline void CSimpleList::Clear(void)
{
	m_Top.pNext = NULL;
	m_nSize = 0;
}

inline INT32 CSimpleList::Size(void)
{
	return m_nSize;
}

inline BOOL CSimpleList::InsertAfter(SimpleListNode* pTargetNode, SimpleListNode* pInsertNode)
{
	LOG_PROCESS_ERROR(pTargetNode);
	LOG_PROCESS_ERROR(pInsertNode);
	LOG_PROCESS_ERROR(pInsertNode->pNext == NULL);

	pInsertNode->pNext = pTargetNode->pNext;
	pTargetNode->pNext = pInsertNode;

	m_nSize++;

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CSimpleList::InsertBefore(SimpleListNode* pTargetNode, SimpleListNode* pInsertNode)
{
	LOG_PROCESS_ERROR(pTargetNode);
	LOG_PROCESS_ERROR(pInsertNode);
	LOG_PROCESS_ERROR(pInsertNode->pNext == NULL);

	for (SimpleListNode* pNode = m_Top.pNext; pNode != NULL; pNode = pNode->pNext)
	{
		if (pNode->pNext != pTargetNode)
			continue;

		return InsertAfter(pNode, pInsertNode);
	}

	LOG_PROCESS_ERROR(FALSE);

Exit0:
	return FALSE;
}

inline BOOL CSimpleList::Remove(SimpleListNode* pTargetNode)
{
	LOG_PROCESS_ERROR(pTargetNode);

	for (SimpleListNode* pNode = m_Top.pNext; pNode != NULL; pNode = pNode->pNext)
	{
		if (pNode->pNext != pTargetNode)
			continue;

		pNode->pNext = pTargetNode->pNext;
		pTargetNode->pNext = NULL;

		return TRUE;
	}

Exit0:
	return FALSE;
}

#endif // simple_stack_h__
