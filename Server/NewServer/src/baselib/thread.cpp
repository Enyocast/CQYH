#include "stdafx.h"
#include "thread.h"

#if defined(WIN32) | defined(WIN64)
#include <process.h>
#endif  // WIN32 | WIN64

CThread::CThread(void)
{
    m_bstart = FALSE;
    m_handle = 0;
    m_tid = 0;
}

CThread::~CThread(void)
{
    if (m_handle != 0)
    {
        Terminate();
        m_handle = 0;
    }
}

THREAD_HANDLE _CreateThread(PFThrdProc pThrdProc, void * pParam, THREAD_ID * pThreadId, BOOL bSuspend)
{
#if (defined(WIN32) || defined(WIN64))
    int thrdFlag = bSuspend ? CREATE_SUSPENDED : 0;
    // CreateThread(NULL, 0, pThrdProc, pParam, thrdFlag, pThreadId);
    return (THREAD_HANDLE)_beginthreadex(NULL, 0, pThrdProc, pParam, thrdFlag, pThreadId);
#else
    if (0 != pthread_create((pthread_t*)pThreadId, NULL, pThrdProc, pParam))
    {
        return SDINVALID_HANDLE;
    }
    return *pThreadId;
#endif // 
}

INT32 _ThreadWait(THREAD_HANDLE handle)
{
#if (defined(WIN32) || defined(WIN64))
    return ::WaitForSingleObject(handle, INFINITE);
#else
    return pthread_join(handle,NULL);
#endif //
}

void  _ThreadTerminate(THREAD_HANDLE handle)
{
#if (defined(WIN32) || defined(WIN64))
    TerminateThread(handle, 0);
    CloseHandle(handle);
#else
    pthread_cancel(handle);
#endif
}

BOOL CThread::Start(void)
{
    if (!m_bstart)
    {
        m_handle = _CreateThread(ThreadFunc, this, &m_tid, FALSE);
        if (0 == m_handle)
        {
            return FALSE;
        }
        m_bstart = TRUE;
    }
    return m_bstart;
}

BOOL CThread::Start(PFThrdProc pFunc, void* pParam)
{
    if (!m_bstart)
    {
        m_handle = _CreateThread(pFunc, pParam, &m_tid, FALSE);
        if (0 == m_handle)
        {
            return FALSE;
        }
        m_bstart = TRUE;
    }
    return m_bstart;
}

void CThread::Wait(void)
{
    if (m_bstart)
    {
        m_bstart = FALSE;
        _ThreadWait(m_handle);
    }
}

void CThread::Terminate(void)
{
    if (m_bstart)
    {
        _ThreadTerminate(m_handle);
        m_bstart = FALSE;
    }
}

THREAD_DECLARE(CThread::ThreadFunc) (void * pParam)
{
    CThread *pThread = static_cast<CThread*>(pParam);
    if (pThread != NULL)
    {
        pThread->ThrdProc();
    }
    return 0;
}

THREAD_ID CThread::GetThreadID(void)
{
#if (defined(WIN32) || defined(WIN64))
    return ::GetCurrentThreadId();
#else
    return pthread_self();
#endif  //WIN32
}
