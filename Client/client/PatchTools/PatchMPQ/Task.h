#ifndef __TASK_H__
#define __TASK_H__

#include "RunObject.h"
#include "../ViGenerator/PatchHelper.h"

extern CCriticalSection g_logLock;

// typedef std::vector<bool> TaskCompleteList;
// TaskCompleteList g_taskCompleteList;
// CCriticalSection g_taskCompleteListLock;
//extern const int g_iVersion = 2;
extern CString g_srcPath;
extern CString g_srcPathReplace;
extern CString g_targPath;

// extern VersionInfoes g_verInfoList;
// extern VersionInfoes g_verInfoCopyFileList;

extern CThreadPool* g_packThreadPool;
//CCriticalSection g_verInfoListLock;

//extern int g_threadCnt;
extern unsigned __int64 g_maxThreadTaskWeight;
extern unsigned __int64 g_totalFileSize;

extern long g_completedTaskCnt;
extern int g_totalTaskCnt;

extern volatile LONG g_writeFileTaskCompletedCount;

// add by zhangrui
// >>
typedef bool(*pfMergePackFile)(LPCWSTR lpszSrcDir, LPCWSTR lpszDeltaDir, LPCWSTR lpszDestDir);
typedef bool(*pfDeletePackFile)(LPCWSTR lpszArchivePath, LPCWSTR lpszFilePath);
typedef bool(*pfExtractPackFile)(LPCWSTR lpszSrcPath, LPCWSTR lpszTempPath, LPCWSTR lpszFilePath, int& iPackIndex);
typedef bool(*pfAddPackFile)(LPCWSTR lpszArchivePath, LPCWSTR lpszFilePath, bool bCreateArchive, DWORD dwNewFileCount);

extern HMODULE g_hXDelta3;
extern pfMergePackFile g_pfMergePackFile;
extern pfDeletePackFile g_pfDeletePackFile;
extern pfExtractPackFile g_pfExtractPackFile;
extern pfAddPackFile g_pfAddPackFile;

extern CRITICAL_SECTION g_csGenMD5;
// <<

void CompleteCompress(class CompressTask* task);
CString GetPathFolderName(const CString& srcPath);
bool isDirExist(const CString& dir);
bool mkDir(CString filePath, bool bRecurse);
void RecurseFindFiles(LPCTSTR pstr/*, VersionInfoes& VIs*/);
bool ShouldSkipFile(const CString& strExt);

class AbstractTask : public IRunObject
{
protected:
	int _taskID;

public:
	AbstractTask(int taskID)
		: _taskID(taskID)
	{

	}

	virtual ~AbstractTask(){}
};

class WriteToFileTask : public AbstractTask
{
	BYTE* _buffer;
	UINT _bufLen;
	CString _filePath;
	bool _compressed;
	UINT _uncompressLen;
public:

	WriteToFileTask(int taskID, BYTE* buffer, UINT bufLen, const CString& filePath, bool compressed, uLong uncompressLen)
		:  AbstractTask(taskID)
		, _buffer(buffer)
		, _bufLen(bufLen)
		, _filePath(filePath)
		, _compressed(compressed)
		, _uncompressLen(uncompressLen)
	{
	}

	virtual bool AutoDelete()
	{
		return true;
	}

	virtual void Run();
};

#endif