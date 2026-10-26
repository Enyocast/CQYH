#include "stdafx.h"
#include "Task.h"
#include "../pakpatcher/md5.h"
#include "ThreadPool.h"
#include "File.h"

#define M_LOG_TO_CONSOLE 1

CThreadPool* g_packThreadPool;

CCriticalSection g_logLock;
CCriticalSection _patchCountLock;

volatile LONG g_writeFileTaskCompletedCount = 0;

extern CString g_versionName;
extern CString g_downloadURLRoot;
extern DWORD g_downloadServiceType;
extern INTERNET_PORT g_downloadServerPort;
extern CString g_downloadServerIP;
extern CString g_downloadObjectURI;

// add by zhangrui 
// >>
HMODULE g_hXDelta3 = NULL;
pfDeletePackFile g_pfDeletePackFile = NULL;
pfExtractPackFile g_pfExtractPackFile = NULL;
pfAddPackFile g_pfAddPackFile = NULL;
pfMergePackFile g_pfMergePackFile = NULL;

CRITICAL_SECTION g_csGenMD5;

// <<

void LogMsgToUI(const CString& msg)
{
//#if M_LOG_TO_CONSOLE
	CSingleLock lock(&g_logLock, TRUE);
	//_tprintf(_T("%s\n"), (LPCTSTR)msg);
	std::wcout << (LPCTSTR)(msg) << std::endl;
//#endif
}

void WriteToFileTask::Run()
{
#if M_LOG_TO_CONSOLE
	CString str;
	str.Format(_T("[%d] Write to file:%s"), _taskID, (LPCTSTR)_filePath);		
	LogMsgToUI(str);
#endif

	if(_compressed)
	{
		CFile cf;
		//if( cf.Open(strPutLocalFileName, CFile::modeRead | CFile::typeBinary, 0) )
		{
			UINT iSrcLen = _bufLen;//(UINT)cf.GetLength();
			BYTE* pbyteBuffer = _buffer;//new BYTE[iSrcLen];
			//cf.Read(pbyteBuffer, iSrcLen);
			//cf.Close();

			uLong uncomprLen = _uncompressLen;
			Byte *uncompr = new Byte[uncomprLen];
			int err = uncompress(uncompr, &uncomprLen, pbyteBuffer, iSrcLen);
			if (err != Z_OK)
			{
				// _strLog += _T("Failed to Uncompress file: ") + strRealLocalFileName;
				// _strLog += _T("\n");

				CString str;
				str.Format(_T("=== uncompress error:%s"), (LPCTSTR)_filePath);		
				LogMsgToUI(str);

				delete[] _buffer;//delete [] pbyteBuffer;
				delete[] uncompr;

				InterlockedIncrement(&g_writeFileTaskCompletedCount);
				return;
			}
			else
			{
				CFile out;
				if( out.Open(_filePath, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, 0) )
				{
					out.Write(uncompr, uncomprLen);
					out.Close();
				}
			}

			//delete [] pbyteBuffer;
			delete [] uncompr;
		}
	}
	else
	{
		CFile out;
		if( out.Open(_filePath, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, 0) )
		{
			out.Write(_buffer, _bufLen);
			out.Close();
		}
	}

	delete[] _buffer;

	InterlockedIncrement(&g_writeFileTaskCompletedCount);
}
