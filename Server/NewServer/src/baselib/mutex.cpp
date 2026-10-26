#include "stdafx.h"
#include "mutex.h"

#if (defined(WIN32) || defined(WIN64))
CMutex::CMutex()
{
    InitializeCriticalSection(&m_mutexId);
}

CMutex::~CMutex()
{
    DeleteCriticalSection(&m_mutexId);
}

void CMutex::Lock()
{
    EnterCriticalSection(&m_mutexId);
}

void CMutex::Unlock()
{
    LeaveCriticalSection(&m_mutexId);
}
#else
CMutex::CMutex()
{
    pthread_mutex_init(&m_mutexId,0)
}

CMutex::~CMutex()
{
    pthread_mutex_destroy(&m_mutexId);
}

void CMutex::Lock()
{
    pthread_mutex_lock(&m_mutexId);
}

void CMutex::Unlock()
{
    pthread_mutex_unlock(&m_mutexId);
}
#endif
