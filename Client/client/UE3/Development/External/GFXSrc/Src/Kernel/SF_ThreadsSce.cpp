/**************************************************************************

Filename    :   SF_ThreadsSce.cpp
Content     :   Sce threads support
Created     :   May 5, 2003
Authors     :   Andrew Reisse

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "SF_Threads.h"
#include "SF_Hash.h"
#include "SF_Debug.h"

#ifdef SF_ENABLE_THREADS

#include "SF_Timer.h"
#include <kernel.h>

namespace Scaleform {

// ***** Mutex implementation

// Interface used internally in a mutex
class Mutex_AreadyLockedAcquireInterface : public AcquireInterface
{
public:
    // Mutex we belong to
    Scaleform::Mutex *pMutex;

    Mutex_AreadyLockedAcquireInterface()
    {
        pMutex = 0;
    }

    // Acquire interface implementation
    virtual bool    CanAcquire();
    virtual bool    TryAcquire();
    virtual bool    TryAcquireCommit();
    virtual bool    TryAcquireCancel();

    // Interface - no implementation
    virtual void        AddRef()                            { }
    virtual void        Release(unsigned flags=0)               { }
    virtual bool        SetRefCountMode(unsigned RefCountFlags) { return 1; }
};


// Acquire interface implementation
bool    Mutex_AreadyLockedAcquireInterface::CanAcquire()       { return 1; }
bool    Mutex_AreadyLockedAcquireInterface::TryAcquire()       { return pMutex->TryAcquire(); }
bool    Mutex_AreadyLockedAcquireInterface::TryAcquireCommit() { return pMutex->TryAcquireCommit(); }
bool    Mutex_AreadyLockedAcquireInterface::TryAcquireCancel() { return pMutex->TryAcquireCancel(); }


// *** Internal Mutex implementation structure

class MutexImpl : public NewOverrideBase<Stat_Default_Mem>
{
    // System mutex or semaphore
    SceUID        Mutex;
    bool          Recursive;
    unsigned      LockCount;
    SceUID        LockedBy;

    Mutex_AreadyLockedAcquireInterface AreadyLockedAcquire;
    
    friend class WaitConditionImpl;

public:
    // Constructor/destructor
    MutexImpl(Scaleform::Mutex* pmutex, bool recursive = 1);
    ~MutexImpl();

    // Locking functions
    void                Lock();
    bool                TryLock();
    void                Unlock(Scaleform::Mutex* pmutex);
    // Returns 1 if the mutes is currently locked
    bool                IsLockedByAnotherThread(Scaleform::Mutex* pmutex);        
    bool                IsSignaled() const;
    AcquireInterface*  GetAcquireInterface(Scaleform::Mutex* pmutex);
};

// *** Constructor/destructor
MutexImpl::MutexImpl(Scaleform::Mutex* pmutex, bool recursive)
{   
    AreadyLockedAcquire.pMutex  = pmutex;
    Recursive           = recursive;
    LockCount           = 0;
    LockedBy            = 0;

    Mutex = sceKernelCreateMutex("Mutex", SCE_KERNEL_ATTR_TH_FIFO | (Recursive ? SCE_KERNEL_MUTEX_ATTR_RECURSIVE : 0), 0, NULL);
    SF_ASSERT(Mutex > 0);
}

MutexImpl::~MutexImpl()
{
    sceKernelDeleteMutex(Mutex);
}


// Lock and try lock
void MutexImpl::Lock()
{
    //while (sceKernelLockMutex(Mutex, 1, NULL) != SCE_KERNEL_OK);
    int result;
    do {
        result = sceKernelLockMutex(Mutex, 1, NULL);
        result = result;
    } while (result != SCE_KERNEL_OK);

    LockCount++;
    LockedBy = sceKernelGetThreadId();
}

bool MutexImpl::TryLock()
{
    if (sceKernelTryLockMutex(Mutex, 1) == SCE_KERNEL_OK)
    {
        LockCount++;
        LockedBy = sceKernelGetThreadId();
        return 1;
    }
    
    return 0;
}

void MutexImpl::Unlock(Scaleform::Mutex* pmutex)
{
    SF_ASSERT(sceKernelGetThreadId() == LockedBy && LockCount > 0);

    unsigned lockCount;
    LockCount--;
    lockCount = LockCount;

    // At this point handlers, if any, MUST already be created and
    // lazy initialization for pHandlers can not be used. To address this,
    // we allow an optional handler enable flag to be passed in constructor.
    // If we allowed lazy initialization, a call to AddHandlers in another
    // thread could access us after pHandlers read, causing the handler
    // to never be called (never informed about Unlock).
    Mutex::CallableHandlers handlers;
    pmutex->GetCallableHandlers(&handlers);

    // Release and Notify waitable objects
    sceKernelUnlockMutex(Mutex, 1);

    // Call wait handlers indirectly here in case owner
    // destroys mutex after finishing wait on it.
    if (lockCount == 0)
        handlers.CallWaitHandlers();
}

bool    MutexImpl::IsLockedByAnotherThread(Scaleform::Mutex* pmutex)
{
    // There could be multiple interpretations of IsLocked with respect to current thread
    if (LockCount == 0)
        return 0;
    if (sceKernelGetThreadId() != LockedBy)
        return 1;
    return 0;
}

bool    MutexImpl::IsSignaled() const
{
    // An mutex is signaled if it is not locked ANYWHERE
    // Note that this is different from IsLockedByAnotherThread function,
    // that takes current thread into account
    return LockCount == 0;
}

// Obtain the acquisition interface
AcquireInterface*  MutexImpl::GetAcquireInterface(Scaleform::Mutex* pmutex)
{
    // If the mutex is already locked by us, return 'owned' acquire interface
    if (LockCount && !IsLockedByAnotherThread(pmutex))
        return &AreadyLockedAcquire;
    // Otherwise, just return pointer to us
    return pmutex;
}



// *** Actual Mutex class implementation

Mutex::Mutex(bool recursive, bool multiWait)
    : Waitable(multiWait)
{
    // NOTE: RefCount mode already thread-safe for all waitables.
    pImpl = new MutexImpl(this, recursive);
}

Mutex::~Mutex()
{
    delete pImpl;
}

// Lock and try lock
void Mutex::DoLock()
{
    pImpl->Lock();
}
bool Mutex::TryLock()
{
    return pImpl->TryLock();
}
void Mutex::Unlock()
{
    pImpl->Unlock(this);
}
bool    Mutex::IsLockedByAnotherThread()
{
    return pImpl->IsLockedByAnotherThread(this);
}
bool    Mutex::IsSignaled() const
{
    return pImpl->IsSignaled();
}
// Obtain the acquisition interface
AcquireInterface*  Mutex::GetAcquireInterface()
{
    return pImpl->GetAcquireInterface(this);
}

// Acquire interface implementation
bool    Mutex::CanAcquire()
{
    return !IsLockedByAnotherThread();
}
bool    Mutex::TryAcquire()
{
    return TryLock();
}
bool    Mutex::TryAcquireCommit()
{
    // Nothing.
    return 1;
}
bool    Mutex::TryAcquireCancel()
{
    Unlock();
    return 1;
}


// ***** Wait Condition Implementation

// Internal implementation class
class WaitConditionImpl : public NewOverrideBase<Stat_Default_Mem>
{
    SceUID          Sem, SMutex;
    AtomicInt<int>  Waiters;

public:

    // Constructor/destructor
    WaitConditionImpl();
    ~WaitConditionImpl();

    // Release mutex and wait for condition. The mutex is re-aqured after the wait.
    bool    Wait(Mutex *pmutex, unsigned delay = SF_WAIT_INFINITE);

    // Notify a condition, releasing at one object waiting
    void    Notify();
    // Notify a condition, releasing all objects waiting
    void    NotifyAll();
};


WaitConditionImpl::WaitConditionImpl() : Waiters(0)
{
    Sem = sceKernelCreateSema("WaitCondition", SCE_KERNEL_ATTR_TH_FIFO, 0, 255, NULL);
    SF_ASSERT(Sem > 0);
    SMutex = sceKernelCreateMutex("WaitConditionMutex", SCE_KERNEL_MUTEX_ATTR_RECURSIVE | SCE_KERNEL_ATTR_TH_FIFO, 0, NULL);
    SF_ASSERT(SMutex > 0);
}

WaitConditionImpl::~WaitConditionImpl()
{
    sceKernelDeleteSema(Sem);
    sceKernelDeleteMutex(SMutex);
}    

bool    WaitConditionImpl::Wait(Mutex *pmutex, unsigned delay)
{
    unsigned            lockCount = pmutex->pImpl->LockCount;

    // Mutex must have been locked
    if (lockCount == 0)
        return 0;

    sceKernelLockMutex(SMutex, 1, NULL);
    Waiters++;

    // Finally, release a mutex or semaphore
    pmutex->pImpl->LockCount = 0;
    pmutex->pImpl->LockedBy = 0;
    sceKernelUnlockMutex(pmutex->pImpl->Mutex, lockCount);

    // Note that there is a gap here between mutex.Unlock() and Wait().
    // The other mutex protects this gap.

    int result;

    if (delay == SF_WAIT_INFINITE)
        result = sceKernelWaitSema(Sem, 1, NULL);
    else
    {
        SceUInt timeout = delay * 1000;
        result = sceKernelWaitSema(Sem, 1, &timeout);
    }
    SF_ASSERT(result == (int)SCE_KERNEL_OK ||
            result == (int)SCE_KERNEL_ERROR_WAIT_CANCEL ||
            result == (int)SCE_KERNEL_ERROR_WAIT_TIMEOUT);

    sceKernelUnlockMutex(SMutex, 1);

    // Re-aquire the mutex
    while (sceKernelLockMutex(pmutex->pImpl->Mutex, lockCount, NULL) != SCE_KERNEL_OK);
    pmutex->pImpl->LockCount = lockCount;
    pmutex->pImpl->LockedBy = sceKernelGetThreadId();

    // Return the result
    return result != (int)SCE_KERNEL_ERROR_WAIT_TIMEOUT;
}

// Notify a condition, releasing the least object in a queue
void    WaitConditionImpl::Notify()
{
    UInt32 r;
    for(;;)
    {
        r = __ldrex(&Waiters.Value);
        if (r == 0)
            return;
        if (__strex(r-1, &Waiters.Value) == 0)
            break;
    }

    if (r)
        sceKernelSignalSema(Sem, 1);
}

// Notify a condition, releasing all objects waiting
void    WaitConditionImpl::NotifyAll()
{
    int nw = Waiters.Exchange_NoSync(0);
    sceKernelSignalSema(Sem, nw);
}



// *** Actual implementation of WaitCondition

WaitCondition::WaitCondition()
{
    pImpl = new WaitConditionImpl;
}
WaitCondition::~WaitCondition()
{
    delete pImpl;
}
    
bool    WaitCondition::Wait(Mutex *pmutex, unsigned delay)
{
    return pImpl->Wait(pmutex, delay);
}
// Notification
void    WaitCondition::Notify()
{
    pImpl->Notify();
}
void    WaitCondition::NotifyAll()
{
    pImpl->NotifyAll();
}


// *** Thread constructors.

Thread::Thread(UPInt stackSize, int processor) : Waitable(1)
{
    // NOTE: RefCount mode already thread-safe for all Waitable objects.
    CreateParams params;
    params.stackSize = stackSize;
    params.processor = processor;
    Init(params);
}

Thread::Thread(Thread::ThreadFn threadFunction, void*  userHandle, UPInt stackSize,
                 int processor, Thread::ThreadState initialState)
    : Waitable(1)
{
    CreateParams params(threadFunction, userHandle, stackSize, processor, initialState);
    Init(params);
}

Thread::Thread(const CreateParams& params) : Waitable(1)
{
    Init(params);
}

void Thread::Init(const CreateParams& params)
{
    // Clear the variables    
    ThreadFlags     = 0;
    ThreadHandle    = 0;
    ExitCode        = 0;
    SuspendCount    = 0;
    StackSize       = params.stackSize;
    Processor       = params.processor;
    Priority        = params.priority;

    // Clear Function pointers
    ThreadFunction  = params.threadFunction;
    UserHandle      = params.userHandle;
    if (params.initialState != NotRunning)
        Start(params.initialState);
}

Thread::~Thread()
{
    // Thread should not running while object is being destroyed,
    // this would indicate ref-counting issue.
    //SF_ASSERT(IsRunning() == 0);

    // Clean up thread.    
    ThreadHandle = 0;
}



// *** Overridable User functions.

// Default Run implementation
int    Thread::Run()
{
    // Call pointer to function, if available.    
    return (ThreadFunction) ? ThreadFunction(this, UserHandle) : 0;
}
void    Thread::OnExit()
{   
}


// Finishes the thread and releases internal reference to it.
void    Thread::FinishAndRelease()
{
    // et callable handlers so that they can still be called
    // after Thread object is released.
    CallableHandlers handlers;
    GetCallableHandlers(&handlers);

    // Note: thread must be US.
    ThreadFlags &= (UInt32)~(SF_THREAD_STARTED);
    ThreadFlags |= SF_THREAD_FINISHED;

    // Release our reference; this is equivalent to 'delete this'
    // from the point of view of our thread.
    Release();

    // Call handlers, if any, signifying completion.
    handlers.CallWaitHandlers();
}



// *** ThreadList - used to tack all created threads

class ThreadList : public NewOverrideBase<Stat_Default_Mem>
{
    //------------------------------------------------------------------------
    struct ThreadHashOp
    {
        size_t operator()(const Thread* ptr)
        {
            return (((size_t)ptr) >> 6) ^ (size_t)ptr;
        }
    };

    HashSet<Thread*, ThreadHashOp>       ThreadSet;
    Mutex                                 ThreadMutex;
    WaitCondition                         ThreadsEmpty;
    // Track the root thread that created us.
    SceUID                                 RootThreadId;

    static ThreadList* volatile pRunningThreads;

    void addThread(Thread *pthread)
    {
        Mutex::Locker lock(&ThreadMutex);
        ThreadSet.Add(pthread);
    }

    void removeThread(Thread *pthread)
    {
        Mutex::Locker lock(&ThreadMutex);
        ThreadSet.Remove(pthread);
        if (ThreadSet.GetSize() == 0)
            ThreadsEmpty.Notify();
    }

    void finishAllThreads()
    {
        // Only original root thread can call this.
        SF_ASSERT(sceKernelGetThreadId() == RootThreadId);

        Mutex::Locker lock(&ThreadMutex);
        while (ThreadSet.GetSize() != 0)
            ThreadsEmpty.Wait(&ThreadMutex);
    }

public:

    ThreadList()
    {
        RootThreadId = sceKernelGetThreadId();
    }
    ~ThreadList() { }


    static void AddRunningThread(Thread *pthread)
    {
        // Non-atomic creation ok since only the root thread
        if (!pRunningThreads)
        {
            pRunningThreads = new ThreadList;
            SF_ASSERT(pRunningThreads);
        }
        pRunningThreads->addThread(pthread);
    }

    // NOTE: 'pthread' might be a dead pointer when this is
    // called so it should not be accessed; it is only used
    // for removal.
    static void RemoveRunningThread(Thread *pthread)
    {
        SF_ASSERT(pRunningThreads);        
        pRunningThreads->removeThread(pthread);
    }

    static void FinishAllThreads()
    {
        // This is ok because only root thread can wait for other thread finish.
        if (pRunningThreads)
        {           
            pRunningThreads->finishAllThreads();
            delete pRunningThreads;
            pRunningThreads = 0;
        }        
    }
};

// By default, we have no thread list.
ThreadList* volatile ThreadList::pRunningThreads = 0;


// FinishAllThreads - exposed publicly in Thread.
void Thread::FinishAllThreads()
{
    ThreadList::FinishAllThreads();
}

// *** Run override

int    Thread::PRun()
{
    // Suspend us on start, if requested
    if (ThreadFlags & SF_THREAD_START_SUSPENDED)
    {
        Suspend();
        ThreadFlags &= (UInt32)~SF_THREAD_START_SUSPENDED;
    }

    // Call the virtual run function
    ExitCode = Run();    
    return ExitCode;
}




// *** User overridables

bool    Thread::GetExitFlag() const
{
    return (ThreadFlags & SF_THREAD_EXIT) != 0;
}       

void    Thread::SetExitFlag(bool exitFlag)
{
    // The below is atomic since ThreadFlags is AtomicInt.
    if (exitFlag)
        ThreadFlags |= SF_THREAD_EXIT;
    else
        ThreadFlags &= (UInt32) ~SF_THREAD_EXIT;
}


// Determines whether the thread was running and is now finished
bool    Thread::IsFinished() const
{
    return (ThreadFlags & SF_THREAD_FINISHED) != 0;
}
// Determines whether the thread is suspended
bool    Thread::IsSuspended() const
{   
    return SuspendCount > 0;
}
// Returns current thread state
Thread::ThreadState Thread::GetThreadState() const
{
    if (IsSuspended())
        return Suspended;    
    if (ThreadFlags & SF_THREAD_STARTED)
        return Running;    
    return NotRunning;
}


// ***** Thread management


// The actual first function called on thread start
int Thread_Psp2ThreadStartFn(SceSize size, void* phandle)
{
    SF_ASSERT(size == sizeof(Thread*));
    Thread* pthread = *(Thread**)phandle;
    int     result = pthread->PRun();
    // Signal the thread as done and release it atomically.
    pthread->FinishAndRelease();
    // At this point Thread object might be dead; however we can still pass
    // it to RemoveRunningThread since it is only used as a key there.   
    ThreadList::RemoveRunningThread(pthread);

    sceKernelExitDeleteThread(result); // delete thread (~Thread doesn't)
    return result;
}

static inline int MapToSystemPrority(Thread::ThreadPriority p)
{
    switch(p)
    {
    case Thread::CriticalPriority:
        return 64;
    case Thread::HighestPriority:
        return 72;
    case Thread::AboveNormalPriority:
        return 80;
    case Thread::NormalPriority:
        return SCE_KERNEL_DEFAULT_PRIORITY_USER;
    case Thread::BelowNormalPriority:
        return 128;
    case Thread::LowestPriority:
        return 160;
    case Thread::IdlePriority:
        return 191;
    }
    return SCE_KERNEL_DEFAULT_PRIORITY_USER;
}

bool    Thread::Start(ThreadState initialState)
{
    if (initialState == NotRunning)
        return 0;

    // If the thread is already running then wait
    // until its finished to begin running this thread
    if ((GetThreadState() != NotRunning) && !Wait())
        return 0;

    ExitCode        = 0;
    SuspendCount    = 0;
    ThreadFlags     = (initialState == Running) ? 0 : SF_THREAD_START_SUSPENDED;

    // AddRef to us until the thread is finished
    AddRef();
    ThreadList::AddRunningThread(this);

    ThreadHandle = sceKernelCreateThread("SF Thread", Thread_Psp2ThreadStartFn, MapToSystemPrority(Priority), StackSize,
        0, SCE_KERNEL_CPU_MASK_USER_ALL, NULL);

    Thread* pthis = this;
    if (ThreadHandle <= 0 ||
        sceKernelStartThread(ThreadHandle, sizeof(Thread*), &pthis) != SCE_KERNEL_OK)
    {
        ThreadFlags = 0;
        Release();
        ThreadList::RemoveRunningThread(this);
        return 0;
    }

    return 1;
}


// Suspend the thread until resumed
bool    Thread::Suspend()
{
    SF_DEBUG_WARNING(1, "cannot suspend threads on this system");
    return 0;
}

// Resumes currently suspended thread
bool    Thread::Resume()
{
    return 0;
}


// Quits with an exit code  
void    Thread::Exit(int exitCode)
{
    // Can only exist the current thread
   // if (etThread() != this)
   //     return;

    // Call the virtual OnExit function
    OnExit();   

    // Signal this thread object as done and release it's references.
    FinishAndRelease();
    ThreadList::RemoveRunningThread(this);

    sceKernelExitDeleteThread(exitCode);
}


ThreadId GetCurrentThreadId()
{
    return sceKernelGetThreadId();
}

// *** Sleep functions

/* static */
bool    Thread::Sleep(unsigned secs)
{
    sceKernelDelayThread(secs * 1000000);
    return 1;
}
/* static */
bool    Thread::MSleep(unsigned msecs)
{
    sceKernelDelayThread(msecs * 1000);
    return 1;
}

/* static */
int     Thread::GetCPUCount()
{
    return 3;
}

}

#endif  // SF_NO_THREADSUPPORT
