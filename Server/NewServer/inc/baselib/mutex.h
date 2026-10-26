#ifndef _MUTEX_H_
#define _MUTEX_H_

#if !(defined(WIN32) || defined(WIN64))
#include <pthread.h>
#endif

class CMutex
{
public:
    CMutex();
    ~CMutex();

    void Lock();
    void Unlock();
private:
    //  no value sematics, therefore private and not implemented.
    CMutex (const CMutex&);
    CMutex& operator= (const CMutex&);

private:
#if (defined(WIN32) || defined(WIN64))
    CRITICAL_SECTION m_mutexId;
#else
    mutable pthread_mutex_t m_mutexId;
#endif
};

#endif  // _MUTEX_H_