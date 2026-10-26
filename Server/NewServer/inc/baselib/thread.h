#ifndef _THREAD_H_
#define _THREAD_H_

#if (defined(WIN32) || defined(WIN64))
	typedef UINT32 THREAD_ID;
	typedef HANDLE  THREAD_HANDLE;
	typedef unsigned int (WINAPI *PFThrdProc)(void *);
	#define THREAD_DECLARE(x)  unsigned int WINAPI  x
	#define THREAD_RETURN(x)   return x;
#else
	typedef pthread_t THREAD_ID;
	typedef long    THREAD_HANDLE;
	typedef void *  (*PFThrdProc)(void *);
	#define THREAD_DECLARE(x)  void *  x
	#define THREAD_RETURN(x)   return x;
#endif // WIN32 | WIN64

class CThread
{
public:
	CThread(void);
	virtual ~CThread(void);

	BOOL Start(void);
	BOOL Start(PFThrdProc pFunc, void* pParam);
	void Wait(void);
	void Terminate(void);

	static THREAD_ID GetThreadID(void);

protected:
	virtual void ThrdProc(void) { }

protected:
	static THREAD_DECLARE(ThreadFunc) (void* pParam);
	CThread(const CThread&);
	CThread& operator = (const CThread&);

	BOOL			m_bstart;
	THREAD_ID		m_tid;
	THREAD_HANDLE	m_handle;
};

#endif  // _THREAD_H_