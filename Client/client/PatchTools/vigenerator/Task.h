#ifndef __TASK_H__
#define __TASK_H__

#include "PatchHelper.h"
#include "RunObject.h"

extern CCriticalSection g_logLock;

// typedef std::vector<bool> TaskCompleteList;
// TaskCompleteList g_taskCompleteList;
// CCriticalSection g_taskCompleteListLock;
//extern const int g_iVersion = 2;
extern CString g_srcPath;
extern CString g_srcPathReplace;
extern CString g_targPath;
extern CString g_versionName;

extern bool g_useVerMD5FileNameFormat;

extern VersionInfoes g_verInfoList;
extern VersionInfoes g_verInfoCopyFileList;

extern CThreadPool* g_threadPool;
//CCriticalSection g_verInfoListLock;

extern int g_threadCnt;
extern unsigned __int64 g_maxThreadTaskWeight;
extern unsigned __int64 g_totalFileSize;

extern long g_completedTaskCnt;
extern int g_totalTaskCnt;

void CompleteCompress(class CompressTask* task);
CString GetPathFolderName(const CString& srcPath);
bool isDirExist(const CString& dir);
bool mkDir(CString filePath, bool bRecurse);
void RecurseFindFiles(LPCTSTR pstr/*, VersionInfoes& VIs*/);
bool ShouldSkipFile(const CString& strExt);

class CopyTask : public IRunObject
{
public:

	//VersionInfoes _verInfoCopyFileList;
	virtual bool AutoDelete();
	virtual void Run();
};

class AbstractCompressTask : public IRunObject
{
protected:

	int _idx;

public:

	AbstractCompressTask(int idx)
		: _idx(idx)
	{
	}

	virtual ~AbstractCompressTask()
	{

	}

	virtual bool AutoDelete()
	{
		return true;
	}

	void Compress(SVersionInfo* vi);

	int Idx() const { return _idx; }
	void Idx(int val) { _idx = val; }
};

class CompressTask : public AbstractCompressTask
{
	SVersionInfo* _vi;

public:

	CompressTask(int idx, SVersionInfo* vi)
		: AbstractCompressTask(idx)
		, _vi(vi)
	{
	}

// 	SVersionInfo* Vi() const { return _vi; }
// 	void Vi(SVersionInfo* val) { _vi = val; }


	virtual ~CompressTask()
	{
	}

	virtual void Run();
};


class CompressTaskBatch : public AbstractCompressTask
{
	VersionInfoePtrs _tasks;
	unsigned __int64 _totalWeight;

public:


	CompressTaskBatch(int idx)
		: AbstractCompressTask(idx)
		, _totalWeight(0)
	{
	}

	virtual ~CompressTaskBatch()
	{
	}

	void AddTask(SVersionInfo* vi)
	{
		_totalWeight += vi->_costWeight;
		_tasks.push_back(vi);
	}

	unsigned __int64 TotalWeight()
	{
		return _totalWeight;
	}

	virtual void Run();
};


#endif