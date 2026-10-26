#ifndef _ID_OBJECT_POOL_H_
#define _ID_OBJECT_POOL_H_

#include "process_error.h"
#include "linux_map.h"
#include <typeinfo>
#include <stdlib.h> // for linux malloc in template
#include <psapi.h>

#ifdef WIN32
    #pragma warning(push)
    #pragma warning(disable : 4312)
#endif  // WIN32

#define FENCE_NUMBER    (0xABCDEF0123456789)
#define MAGIC_FREE_TAG  (0x87654321)
#define HASH_TABLE_SIZE	(1024 * 64)

template<class T, class N>
class CIDObjectPool
{
public:
    CIDObjectPool();
    ~CIDObjectPool();

    BOOL Init(INT32 nInitSize);
    BOOL UnInit(void);

    T* New(N dwID);
    BOOL Delete(T* pObject);
    T* Find(N dwID);

    template<class TFunc>
    inline BOOL Traverse(TFunc& rFunc);

    inline INT32 GetSize(void);
	inline INT32 GetFreeSize(void);
	inline INT32 GetUsedSize(void);
	inline INT32 GetObjSize(void);

    UINT32 GetObjID(T* pObject);

    void CheckFence(void);

private:
    INT32			m_nSize;
    LM_MAP_NODE<N>*	m_pDataMapRoot[HASH_TABLE_SIZE];
    LM_MAP_NODE<N>	m_FreeListHead;
    INT32			m_nFreeListSize;
	INT32			m_nObjSize;

    struct T_NODE
    {
        T           Data;
#ifdef _DEBUG_FENCE
        UINT64      qwFence;
#endif  // _DEBUG_FENCE
    };

    struct CHUNK_NODE
    {
        LM_MAP_NODE<N>*	pDataNode;
        T_NODE*         pTNode;
        INT32			nSize;
        CHUNK_NODE*		pNext;
    }				m_ChunkListHead;

    BOOL _CreateChunk(INT32 nSize);
    LM_MAP_NODE<N>* _GetDataNode(T* pData);
    T* _GetData(LM_MAP_NODE<N>* pDataNode);
};

template<class T, class N>
CIDObjectPool<T, N>::CIDObjectPool()
{
    m_nSize = 0;
    m_nFreeListSize = 0;
    memset(m_pDataMapRoot, NULL, sizeof(m_pDataMapRoot));
    memset(&m_FreeListHead, 0, sizeof(m_FreeListHead));
    memset(&m_ChunkListHead, 0, sizeof(m_ChunkListHead));
	m_nObjSize = 0;
}

template<class T, class N>
CIDObjectPool<T, N>::~CIDObjectPool()
{
    UnInit();
}

template<class T, class N>
BOOL CIDObjectPool<T, N>::_CreateChunk(INT32 nSize)
{
    LM_MAP_NODE<N>* pNewChunk = NULL;
    CHUNK_NODE* pNewChunkNode = NULL;
    LM_MAP_NODE<N>* pNode = NULL;

    LOG_PROCESS_ERROR(nSize > 0);

    // alloc memory
    pNewChunk = (LM_MAP_NODE<N>*)malloc((sizeof(LM_MAP_NODE<N>) + sizeof(T_NODE)) * nSize);
    LOG_PROCESS_ERROR(pNewChunk);
    LOG_PROCESS_ERROR(((INT64)pNewChunk & 3) == 0);       // check 4 bytes aligned
	LOG_PROCESS_ERROR(sizeof(T) % 4 == 0);

    pNewChunkNode = new CHUNK_NODE;
    LOG_PROCESS_ERROR(pNewChunkNode);

    // link chunk list
    pNewChunkNode->pDataNode = pNewChunk;
    pNewChunkNode->pTNode = (T_NODE*)(pNewChunk + nSize);
    pNewChunkNode->nSize = nSize;
    pNewChunkNode->pNext = m_ChunkListHead.pNext;
    m_ChunkListHead.pNext = pNewChunkNode;

    // call constructor
    for (int nIndex = 0; nIndex < nSize; nIndex++)
    {
        T_NODE* pTNode = pNewChunkNode->pTNode + nIndex;

#ifdef _DEBUG_FENCE
        pTNode->qwFence = FENCE_NUMBER;
#endif  // _DEBUG_FENCE

#ifdef new
#define REPLACEMENT_NEW new
#undef new
        REPLACEMENT_NEW (&pTNode->Data) T;
#define new _DEBUG_NEW
#undef REPLACEMENT_NEW
#else
        new (&pTNode->Data) T;
#endif  // new
    }

    // put into free list
    pNode = pNewChunk;
    for (int nIndex = 1; nIndex < nSize; nIndex++)
    {
        LM_MAP_NODE<N>* pNextNode = pNewChunk + nIndex;
        pNode->pNext = pNextNode;
        pNode->pLeft = (LM_MAP_NODE<N>*)MAGIC_FREE_TAG;
        pNode = pNextNode;
    }
    pNode->pNext = m_FreeListHead.pNext;
    pNode->pLeft = (LM_MAP_NODE<N>*)MAGIC_FREE_TAG;
    m_FreeListHead.pNext = pNewChunk;

    m_nSize += nSize;
    m_nFreeListSize += nSize;

    return TRUE;
Exit0:
    if (pNewChunk)
    {
        free(pNewChunk);
    }
    if (pNewChunkNode)
        SAFE_DELETE(pNewChunkNode);

    return FALSE;
}

template<class T, class N>
LM_MAP_NODE<N>* CIDObjectPool<T, N>::_GetDataNode(T* pData)
{
    T_NODE* pTNode = (T_NODE*)pData;
    CHUNK_NODE* pChunkNode = m_ChunkListHead.pNext;
    while (pChunkNode)
    {
        ptrdiff_t nOffset = pTNode - pChunkNode->pTNode;
        if (nOffset >= 0 && nOffset < pChunkNode->nSize)
        {
            return pChunkNode->pDataNode + nOffset;
        }
        pChunkNode = pChunkNode->pNext;
    }

    return NULL;
}

template<class T, class N>
T* CIDObjectPool<T, N>::_GetData(LM_MAP_NODE<N>* pDataNode)
{
    CHUNK_NODE* pChunkNode = m_ChunkListHead.pNext;
    while (pChunkNode)
    {
        ptrdiff_t nOffset = pDataNode - pChunkNode->pDataNode;
        if (nOffset >= 0 && nOffset < pChunkNode->nSize)
        {
            return (T*)(pChunkNode->pTNode + nOffset);
        }
        pChunkNode = pChunkNode->pNext;
    }

    return NULL;
}

template<class T, class N>
BOOL CIDObjectPool<T, N>::Init(INT32 nInitSize)
{
    INT32 nRetCode = 0;
	HANDLE hHeap = NULL;
	//PROCESS_HEAP_ENTRY Entry;
	INT64 llOldMemorySize = 0;
	INT64 llNewMemorySize = 0;
	INT32 nOldCount = 0;
	INT32 nNewCount = 0;

	//hHeap = GetProcessHeap();
	//LOG_PROCESS_ERROR(hHeap);

	//nRetCode = HeapLock(hHeap);
	//LOG_PROCESS_ERROR(nRetCode);

	//Entry.lpData = NULL;
	//while (HeapWalk(GetProcessHeap(), &Entry))
	//	if (Entry.wFlags & PROCESS_HEAP_ENTRY_BUSY)
	//		llOldMemorySize += Entry.cbData + Entry.cbOverhead;

    nRetCode = _CreateChunk(nInitSize);
    LOG_PROCESS_ERROR(nRetCode);

	//Entry.lpData = NULL;
	//while (HeapWalk(GetProcessHeap(), &Entry))
	//	if (Entry.wFlags & PROCESS_HEAP_ENTRY_BUSY)
	//		llNewMemorySize += Entry.cbData + Entry.cbOverhead;

	//nRetCode = HeapUnlock(hHeap);
	//LOG_CHECK_ERROR(nRetCode);

	//m_nObjSize = (INT32)((llNewMemorySize - llOldMemorySize) / nInitSize);
	m_nObjSize = sizeof(T);

    return TRUE;
Exit0:
	if (hHeap)
		HeapUnlock(hHeap);

    return FALSE;
}

template<class T, class N>
BOOL CIDObjectPool<T, N>::UnInit(void)
{
    CHUNK_NODE* pChunkNode = NULL;

    // Check memory leak
    LOG_CHECK_ERROR(m_nFreeListSize == m_nSize);

    pChunkNode = m_ChunkListHead.pNext;
    while (pChunkNode)
    {
        CHUNK_NODE* pNextChunk = pChunkNode->pNext;

        // call destructor
        for (int nIndex = 0; nIndex < pChunkNode->nSize; nIndex++)
        {
            T_NODE* pTNode = pChunkNode->pTNode + nIndex;
#ifdef _DEBUG_FENCE
            LOG_CHECK_ERROR_BREAK(pTNode->qwFence);
#endif //_DEBUG_FENCE

            (&pTNode->Data)->T::~T();
        }

        free(pChunkNode->pDataNode);
        SAFE_DELETE(pChunkNode);
        pChunkNode = pNextChunk;
    }

    m_nSize = 0;
    m_nFreeListSize = 0;
    memset(m_pDataMapRoot, NULL, sizeof(m_pDataMapRoot));
    m_FreeListHead.pNext = NULL;
    m_ChunkListHead.pNext = NULL;

    return TRUE;
}

template<class T, class N>
T* CIDObjectPool<T, N>::New(N ID)
{
    INT32 nRetCode = 0;
    LM_MAP_NODE<N>* pDataNode = NULL;

    // take from free list
    if (m_FreeListHead.pNext == NULL)
    {
        nRetCode = _CreateChunk(m_nSize);
        LOG_PROCESS_ERROR(nRetCode);

        INF("expanded %s pool to %d in file %s", typeid(T).name(), m_nSize, __FILE__);
    }
    LOG_PROCESS_ERROR(m_FreeListHead.pNext);

    pDataNode = m_FreeListHead.pNext;
    LOG_PROCESS_ERROR(pDataNode->pLeft == (LM_MAP_NODE<N>*)MAGIC_FREE_TAG);
    m_FreeListHead.pNext = pDataNode->pNext;
    m_nFreeListSize--;

    // insert into map
    pDataNode->ID = ID;
    nRetCode = LM_Insert(pDataNode, m_pDataMapRoot + (ID % HASH_TABLE_SIZE));
    LOG_PROCESS_ERROR(nRetCode);

    return _GetData(pDataNode);
Exit0:
    if (pDataNode)
    {
        // put back to free list
        pDataNode->pNext = m_FreeListHead.pNext;
        m_FreeListHead.pNext = pDataNode;
        m_nFreeListSize++;
    }

    return NULL;
}

template<class T, class N>
BOOL CIDObjectPool<T, N>::Delete(T* pObject)
{
    LM_MAP_NODE<N>* pDataNode = NULL;

    LOG_PROCESS_ERROR(pObject);

    pDataNode = _GetDataNode(pObject);
    LOG_PROCESS_ERROR(pDataNode);
	LOG_PROCESS_ERROR(pDataNode->pLeft != (LM_MAP_NODE<N>*)MAGIC_FREE_TAG);

    // remove from map
    LM_Erase(pDataNode, m_pDataMapRoot + (pDataNode->ID % HASH_TABLE_SIZE));

    // put into free list
    pDataNode->pNext = m_FreeListHead.pNext;
    m_FreeListHead.pNext = pDataNode;
    pDataNode->pLeft = (LM_MAP_NODE<N>*)MAGIC_FREE_TAG;
    m_nFreeListSize++;

    return TRUE;
Exit0:

    return FALSE;
}

template<class T, class N>
T* CIDObjectPool<T, N>::Find(N ID)
{
    LM_MAP_NODE<N>* pDataNode = NULL;

    pDataNode = LM_Search(ID, m_pDataMapRoot[ID % HASH_TABLE_SIZE]);
    PROCESS_ERROR(pDataNode);

    return _GetData(pDataNode);
Exit0:

    return NULL;
}

template<class T, class N>
template<class TFunc>
inline BOOL CIDObjectPool<T, N>::Traverse(TFunc& rFunc)
{
    INT32 nRetCode = 0;

    for (INT32 nIndex = 0; nIndex < HASH_TABLE_SIZE; nIndex++)
    {
        LM_MAP_NODE<N>* pRootNode = m_pDataMapRoot[nIndex];
        if (pRootNode)
        {
            LM_MAP_NODE<N>* pDataNode = LM_First(pRootNode);
            while (pDataNode)
            {
                LM_MAP_NODE<N>* pNextNode = LM_Next(pDataNode);

                nRetCode = rFunc(pDataNode->ID, _GetData(pDataNode));
                PROCESS_ERROR(nRetCode);

                pDataNode = pNextNode;
            }
        }
    }

    return TRUE;
Exit0:

    return FALSE;
}

template<class T, class N>
inline INT32 CIDObjectPool<T, N>::GetSize(void)
{
    return m_nSize;
}

template<class T, class N>
inline INT32 CIDObjectPool<T, N>::GetFreeSize(void)
{
    return m_nFreeListSize;
}

template<class T, class N>
inline INT32 CIDObjectPool<T, N>::GetUsedSize(void)
{
    return m_nSize - m_nFreeListSize;
}

template<class T, class N>
inline INT32 CIDObjectPool<T, N>::GetObjSize(void)
{
	return m_nObjSize;
}

template<class T, class N>
UINT32 CIDObjectPool<T, N>::GetObjID(T* pObject)
{
    LM_MAP_NODE<N>* pDataNode = _GetDataNode(pObject);
    PROCESS_ERROR(pDataNode);

    return pDataNode->ID;
Exit0:
    return 0;
}

template<class T, class N>
void CIDObjectPool<T, N>::CheckFence(void)
{
#ifdef _DEBUG_FENCE
    CHUNK_NODE* pChunkNode = m_ChunkListHead.pNext;
    while (pChunkNode)
    {
        for (INT32 nIndex = 0; nIndex < pChunkNode->nSize; nIndex++)
        {
            LOG_CHECK_ERROR_BREAK(pChunkNode->pTNode[nIndex].qwFence == FENCE_NUMBER);
        }
        pChunkNode = pChunkNode->pNext;
    }
#endif
    return;
}

#ifdef WIN32
    #pragma warning(pop)
#endif  // WIN32

#ifdef _DEBUG_FENCE
#undef _DEBUG_FENCE
#endif  // _DEBUG_FENCE

#endif	// _ID_OBJECT_POOL_H_
