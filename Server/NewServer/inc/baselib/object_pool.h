#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <exception>
#include <typeinfo>
#include <psapi.h>

#ifdef WIN32
    #pragma warning(push)
    #pragma warning(disable : 4312)
#endif  

#define MAGIC_USED_TAG         (0x87654321)

template<class T>
class CObjectPool
{
public:
	CObjectPool();
	~CObjectPool();

	BOOL Init(INT32 nInitSize);
	BOOL UnInit(void);

	T* New(void);
	BOOL Delete(T* pObject);

	INT32 GetSize(void);
	INT32 GetFreeSize(void);
    INT32 GetUsedSize(void);
	INT32 GetObjSize(void);

private:
	INT32 m_nSize;
	INT32 m_nFreeSize;
	INT32 m_nObjSize;

	struct DATA_NODE
	{
		T			Data;
		DATA_NODE*	pNext;
	}	m_FreeListHead;

	struct CHUNK_NODE
	{
		DATA_NODE*	pDataNode;
		CHUNK_NODE* pNext;
	}	m_ChunkListHead;

	BOOL _CreateChunk(INT32 nSize);
};

template<class T>
CObjectPool<T>::CObjectPool()
{
	m_nSize = 0;
	m_nFreeSize = 0;
	m_nObjSize = 0;
	m_FreeListHead.pNext = NULL;

	m_ChunkListHead.pDataNode = NULL;
	m_ChunkListHead.pNext = NULL;
}

template<class T>
CObjectPool<T>::~CObjectPool()
{
	UnInit();
}

template<class T>
BOOL CObjectPool<T>::_CreateChunk(INT32 nSize)
{
	DATA_NODE* pNewChunk = NULL;
	CHUNK_NODE* pChunkNode = NULL;
	DATA_NODE* pNode = NULL;

    LOG_PROCESS_ERROR(nSize > 0);

	pNewChunk = new DATA_NODE[nSize];
	LOG_PROCESS_ERROR(pNewChunk);

	pChunkNode = new CHUNK_NODE;
	LOG_PROCESS_ERROR(pChunkNode);

	pChunkNode->pDataNode = pNewChunk;
	pChunkNode->pNext = m_ChunkListHead.pNext;
	m_ChunkListHead.pNext = pChunkNode;

	pNode = pNewChunk;
	for (int nIndex = 1; nIndex < nSize; nIndex++)
	{
		DATA_NODE* pNextNode = pNewChunk + nIndex;
		pNode->pNext = pNextNode;
		pNode = pNextNode;
	}
	pNode->pNext = m_FreeListHead.pNext;
	m_FreeListHead.pNext = pNewChunk;

	m_nSize += nSize;
	m_nFreeSize += nSize;

	return TRUE;
Exit0:
	SAFE_DELETE(pChunkNode);
	SAFE_DELETE_ARRAY(pNewChunk);

	return FALSE;
}

template<class T>
BOOL CObjectPool<T>::Init(INT32 nInitSize)
{
	INT32 nRetCode = 0;
	PROCESS_MEMORY_COUNTERS pmc;
	INT64 llMemorySize = 0;

	nRetCode = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	LOG_PROCESS_ERROR(nRetCode);

	llMemorySize = pmc.PagefileUsage;

	m_nSize = 0;
	m_nFreeSize = 0;
	m_FreeListHead.pNext = NULL;

	nRetCode = _CreateChunk(nInitSize);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	LOG_PROCESS_ERROR(nRetCode);

	m_nObjSize = (INT32)((pmc.PagefileUsage - llMemorySize) / nInitSize);

	return TRUE;
Exit0:
	UnInit();

	return FALSE;
}

template<class T>
BOOL CObjectPool<T>::UnInit(void)
{
	LOG_CHECK_ERROR(m_nFreeSize == m_nSize);

	CHUNK_NODE* pChunkNode = m_ChunkListHead.pNext;
	while (pChunkNode)
	{
		CHUNK_NODE* pNext = pChunkNode->pNext;
		SAFE_DELETE_ARRAY(pChunkNode->pDataNode);
		SAFE_DELETE(pChunkNode);

		pChunkNode = pNext;
	}

	m_ChunkListHead.pNext = NULL;
	m_FreeListHead.pNext = NULL;
	m_nFreeSize = 0;
	m_nSize = 0;

	return TRUE;
}

template<class T>
T* CObjectPool<T>::New(void)
{
	DATA_NODE* pResult = NULL;
	INT32 nRetCode = 0;

	if (m_FreeListHead.pNext == NULL)
	{
		nRetCode = _CreateChunk(m_nSize);
		LOG_PROCESS_ERROR(nRetCode);

        INF("expanded %s pool to %d in file %s", typeid(T).name(), m_nSize, __FILE__);
    }

	pResult = m_FreeListHead.pNext;
    LOG_PROCESS_ERROR(pResult);

	m_FreeListHead.pNext = pResult->pNext;
    pResult->pNext = ((DATA_NODE*)MAGIC_USED_TAG);
	m_nFreeSize--;

	return &(pResult->Data);
Exit0:
	return NULL;
}

template<class T>
BOOL CObjectPool<T>::Delete(T* pObject)
{
    DATA_NODE* pDataNode = (DATA_NODE*)pObject;

    LOG_PROCESS_ERROR(pObject);
    LOG_PROCESS_ERROR(pDataNode->pNext == (DATA_NODE*)MAGIC_USED_TAG);

    pDataNode->pNext = m_FreeListHead.pNext;
	m_FreeListHead.pNext = (DATA_NODE*)pObject;
	m_nFreeSize++;

	return TRUE;
Exit0:
	return FALSE;
}

template<class T>
inline INT32 CObjectPool<T>::GetSize(void)
{
	return m_nSize;
}

template<class T>
inline INT32 CObjectPool<T>::GetFreeSize(void)
{
	return m_nFreeSize;
}

template<class T>
inline INT32 CObjectPool<T>::GetUsedSize(void)
{
    return m_nSize - m_nFreeSize;
}

template<class T>
inline INT32 CObjectPool<T>::GetObjSize(void)
{
	return m_nObjSize;
}

#ifdef WIN32
    #pragma warning(pop)
#endif  // WIN32

#endif	// _OBJECT_POOL_H_
