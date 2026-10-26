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

extern CThreadPool* g_genMD5ThreadPool;
extern CThreadPool* g_compareMD5ThreadPool;
extern CThreadPool* g_downloadThreadPool;
extern CThreadPool* g_writeFileThreadPool;
//CCriticalSection g_verInfoListLock;

//extern int g_threadCnt;
extern unsigned __int64 g_maxThreadTaskWeight;
extern unsigned __int64 g_totalFileSize;

extern long g_completedTaskCnt;
extern int g_totalTaskCnt;


extern volatile LONG g_genMD5TaskTotalCount;
extern volatile LONG g_genMD5TaskCompletedCount;

extern volatile LONG g_compareMD5TaskTotalCount;
extern volatile LONG g_compareMD5TaskCompletedCount;

extern volatile LONG g_downloadTaskTotalCount;
extern volatile LONG g_downloadTaskCompletedCount;

extern volatile LONG g_writeFileTaskCompletedCount;

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

class GenerateMD5Task : public AbstractTask
{
public:

	CString _srcFile;
	CString& _targetMD5;

	GenerateMD5Task(int taskID, const CString& srcFile, CString& targetMD5)
		:  AbstractTask(taskID)
		, _srcFile(srcFile)
		, _targetMD5(targetMD5)
	{

	}

	virtual bool AutoDelete()
	{
		return true;
	}

	virtual void Run();
};


class CompareMD5Task : public AbstractTask
{
public:

	SLocalVersionInfo& _infoLocal;
	SFilePatch& _filePatch;

	CompareMD5Task(int taskID, SLocalVersionInfo& localInfo, SFilePatch& filePatch)
		: AbstractTask(taskID)
		, _infoLocal(localInfo)
		, _filePatch(filePatch)
	{
	}

	virtual bool AutoDelete()
	{
		return true;
	}

	virtual void Run();
};

class DownloadTask : public AbstractTask
{
public:

	class CInternetSession* _internetSession;
	class CHttpConnection* _httpConnection;

	CString			_strServerIP;
	INTERNET_PORT	_serverPort;
	CString			_strInitRoot;


	SLocalVersionInfo _localInfo;
	CString			_strInstallDir;
	CString			_strTmpDir;

	DownloadTask(int taskID, const CString& serverIP, INTERNET_PORT serverPort,
		const CString& initRoot, const SLocalVersionInfo& localInfo,
		const CString& strInstallDir, const CString& strTmpDir)
		:  AbstractTask(taskID)
		, _internetSession(0)
		, _httpConnection(0)
		, _strServerIP(serverIP)
		, _serverPort(serverPort)
		, _localInfo(localInfo)
		, _strInitRoot(initRoot)
		, _strInstallDir(strInstallDir)
		, _strTmpDir(strTmpDir)
	{
	}

	virtual bool AutoDelete()
	{
		return true;
	}

	virtual void Run();
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