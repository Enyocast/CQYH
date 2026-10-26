#ifndef _H_PRE_SAVE_LIST_H_
#define _H_PRE_SAVE_LIST_H_

#include <set>
#include "object_pool.h"

enum PER_SAVE_TYPE
{
    PRE_SAVE_INVALID        = -1,
    PRE_SAVE_GUILD_MAIN     = 0,
    PRE_SAVE_GUILD_NOTICE   = 1,
    PRE_SAVE_GUILD_LEADER   = 2,
    PRE_SAVE_GUILD_ANNOUNCE = 3,

    PRE_SAVE_TOTAL,
};

#define MAX_MS_SAVE_COMMIT_NUM   (100)



template<typename T>
class CQueue
{
public:
    CQueue()
    {
        m_pIDListHead = NULL;
        m_pIDListRear = NULL;
    }
    ~CQueue()
    {
        m_pIDListHead = NULL;
        m_pIDListRear = NULL;
    }

    BOOL Init()
    {
        m_pIDListHead = NULL;
        m_pIDListRear = NULL;
        return TRUE;
    }

    BOOL UnInit()
    {
        m_pIDListHead = NULL;
        m_pIDListRear = NULL;
        return TRUE;
    }

public:
    inline T* PopFront();
    inline void PushBack(T *pNode);

private:
    T   *m_pIDListHead;
    T   *m_pIDListRear;
};


class CPreSaveList
{
    struct ID_NODE;

public:
    static CPreSaveList    &GetInstance();

    BOOL    Init();
    BOOL    UnInit();

    BOOL    MainLoop();

    BOOL    SaveToList(INT32 nType, UINT32 dwObjID);

protected:
    CPreSaveList();
    ~CPreSaveList();

    static CPreSaveList     m_Instance;

    BOOL    _SaveToList(ID_NODE *pNode);
    BOOL    _Save(INT32 nType, UINT32 dwID);

    inline ID_NODE *_PopFront();
    inline void _PushBack(ID_NODE *pNode);
private:

#define SAVE_BUFFER_SIZE     (1024*64)

    struct ID_NODE
    {
        UINT32      dwID;
        INT32       nType;
        ID_NODE     *pNext;
    };

    typedef     std::set<UINT64>    ID_SET;
    ID_SET      m_set;

    CQueue<ID_NODE>         m_queue;

    char        *m_pBuffer;
    CObjectPool<ID_NODE>    m_IDPool;

};



template<typename T>
inline T* CQueue<T>::PopFront()
{
    T     *pNode = NULL;

    // last node
    if (m_pIDListHead == m_pIDListRear)
    {
        pNode = m_pIDListHead;
        m_pIDListHead = NULL;
        m_pIDListRear = NULL;
        return pNode;
    }

    pNode = m_pIDListHead;
    m_pIDListHead = m_pIDListHead->pNext;
    return pNode;
}

template<typename T>
inline void CQueue<T>::PushBack(T *pNode)
{
    LOG_PROCESS_ERROR(pNode);

    if (m_pIDListHead == m_pIDListRear)
    {
        if (NULL == m_pIDListHead)
        {
            m_pIDListHead = pNode;
            m_pIDListRear = pNode;
            return;
        }
    }

    m_pIDListRear->pNext = pNode;
    m_pIDListRear = pNode;
    m_pIDListRear->pNext = NULL;

Exit0:
    return;
}





#endif //_H_PRE_SAVE_LIST_H_
