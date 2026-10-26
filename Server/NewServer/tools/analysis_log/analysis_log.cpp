// analysis_log.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iocp_mgr.h"

ERROR_MAP g_ErrorMap;

BOOL _ReadFileData(IOCP_TASK* pTask)
{
	INT32 nRetCode = 0;

	pTask->dwCreateTick = GetTickCount64();

	pTask->hFile = CreateFile(pTask->szFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	LOG_PROCESS_ERROR(pTask->hFile != INVALID_HANDLE_VALUE);

	HANDLE hRetCode = CreateIoCompletionPort(pTask->hFile, CIocpMgr::GetInstance().GetIocpHandle(), (ULONG_PTR)pTask, 0);
	LOG_PROCESS_ERROR(hRetCode);

	nRetCode = GetFileSizeEx(pTask->hFile, (PLARGE_INTEGER)&pTask->qwFileSize);
	LOG_PROCESS_ERROR(nRetCode);

	if (pTask->qwFileSize > 0)
	{
		pTask->pFileData = new char[pTask->qwFileSize + 1];
		LOG_PROCESS_ERROR(pTask->pFileData);

		nRetCode = ReadFile(pTask->hFile, pTask->pFileData, pTask->qwFileSize, NULL, pTask);
		LOG_PROCESS_ERROR(nRetCode || GetLastError() == ERROR_IO_PENDING);
	}
	else
	{
		CloseHandle(pTask->hFile);
		pTask->hFile = INVALID_HANDLE_VALUE;
	}

	pTask->dwReadTick = GetTickCount64();
//	INF("create file");

	return TRUE;
Exit0:
	return FALSE;
}

void _ExtractError(IOCP_TASK* pTask)
{
	UINT32 dwStartIndex = 0;
	UINT32 dwPointer = 0;
	char* pcszLine = pTask->pFileData;
	while (dwPointer < pTask->qwFileSize)
	{
		if (pTask->pFileData[dwPointer] == '\r')
		{
			pTask->pFileData[dwPointer] = 0;
			if (pTask->pFileData + dwPointer - pcszLine > dwStartIndex)
			{
				if (dwStartIndex == 0)
				{
					while (pcszLine[dwStartIndex] != '[' && pcszLine[dwStartIndex] != 0)
						dwStartIndex++;
					LOG_PROCESS_ERROR(dwStartIndex > 0);
				}
				char* pcszError = pcszLine + dwStartIndex;
				if (*(UINT32*)pcszError == ' ]E[' ||
					*(UINT32*)pcszError == ' ]C[')
				{
					if (pTask->pErrorMap == NULL)
						pTask->pErrorMap = new ERROR_MAP;
					(*(pTask->pErrorMap))[(pcszError + 15)]++;
				}
			}
		}
		if (pTask->pFileData[dwPointer] == '\n')
			pcszLine = pTask->pFileData + dwPointer + 1;
		dwPointer++;
	}

Exit0:
	return;
}

void _ExtractNetworkFlow(IOCP_TASK* pTask)
{
	UINT32 pt = 0;
	char* data = pTask->pFileData;
	char* line = NULL;
	char* time = NULL;
	bool bNewTab = true;

	const char* down_header = "========================download================================";
	const char* up_header = "========================upload================================";

	enum SearchingState
	{
		ssSearcingHeader = 0,
		ssPrintingDownloadFlow,
		ssPrintingUploadFlow,
	};

	INT32 eSearchingState = ssSearcingHeader;

	while (pt < pTask->qwFileSize)
	{
		switch (eSearchingState)
		{
		case ssSearcingHeader:
		{
			line = strstr(data, down_header);
			PROCESS_ERROR(line);

			time = line + strlen(down_header) + 2;
			line = time + 39;
			pt = time - pTask->pFileData;
			data = line;
			eSearchingState = ssPrintingDownloadFlow;
			bNewTab = true;
		}
			break;
		case ssPrintingDownloadFlow:
		{
			if (pTask->pFileData[pt] == '=')
			{
				time = line + strlen(up_header) + 2;
				line = time + 39;
				pt = time - pTask->pFileData;
				data = line;
				eSearchingState = ssPrintingUploadFlow;
				bNewTab = true;
			}
			else
			{
				if (bNewTab && pTask->pFileData[pt] == '\t')
				{
					pTask->pFileData[pt] = 0;
					bNewTab = false;
				}

				if (pTask->pFileData[pt] == '\r')
				{
					pTask->pFileData[pt] = 0;
					printf("%s\t%s\n", time, line);
				}

				if (pTask->pFileData[pt] == '\n')
				{
					time = pTask->pFileData + pt + 1;
					line = time + 39;
					pt = time - pTask->pFileData;
					bNewTab = true;
				}
				else
				{
					pt++;
				}
			}
		}
			break;
		case ssPrintingUploadFlow:
		{
			if (line[0] != 'c' && line[1] != '2')
			{
				eSearchingState = ssSearcingHeader;
				data = line;
			}
			else
			{
				if (bNewTab && pTask->pFileData[pt] == '\t')
				{
					pTask->pFileData[pt] = 0;
					bNewTab = false;
				}
				if (pTask->pFileData[pt] == '\r')
				{
					pTask->pFileData[pt] = 0;
					printf("\t\t\t\t\t\t%s\t%s\n", time, line);
				}

				if (pTask->pFileData[pt] == '\n')
				{
					time = pTask->pFileData + pt + 1;
					line = time + 39;
					pt = time - pTask->pFileData;
					bNewTab = true;
				}
				else
				{
					pt++;
				}
			}


		}
			break;
		default:
			break;
		}

	}

Exit0:
	return;
}

void _ProcessFile(IOCP_TASK* pTask)
{
	UINT32 dwStartIndex = 0;
	UINT32 dwPointer = 0;

	switch (pTask->eWorkingMode)
	{
	case wmExtractError:
		_ExtractError(pTask);
		break;
	case wmExtractNetworkFlow:
		_ExtractNetworkFlow(pTask);
		break;
	default:
		break;
	}

	delete[] pTask->pFileData;
	pTask->pFileData = NULL;

	CloseHandle(pTask->hFile);
	pTask->hFile = INVALID_HANDLE_VALUE;

	pTask->dwProcessTick = GetTickCount64();

	return;
Exit0:

	return;
}

void _FetchTask(IOCP_TASK* pTask)
{
	if (pTask->pErrorMap)
	{
		for (ERROR_MAP::iterator it = pTask->pErrorMap->begin();
			it != pTask->pErrorMap->end(); ++it)
		{
			g_ErrorMap[it->first] += it->second;
		}
	}

//	INF("fetch %s", pTask->szFilePath);

	//INF("%d %d %d %d",
	//	pTask->dwCreateTick - pTask->dwSubmitTick,
	//	pTask->dwReadTick - pTask->dwCreateTick,
	//	pTask->dwProcessTick - pTask->dwReadTick,
	//	pTask->dwFetchTick - pTask->dwProcessTick);
}

void _CleanTask(IOCP_TASK* pTask)
{
	if (pTask && pTask->pErrorMap)
		delete pTask->pErrorMap;
	if (pTask && pTask->pFileData)
		delete[] pTask->pFileData;
	if (pTask && pTask->hFile != INVALID_HANDLE_VALUE)
		CloseHandle(pTask->hFile);
	if (pTask)
		delete pTask;
}

int main(int argc, char* argv[])
{
	INT32 nRetCode = 0;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	char szFindPattern[MAX_PATH];
	INT32 eWorkingMode = 0;

	CLog::GetInstance().Init("analysis", lltAll, lotAll, FALSE, FALSE, TRUE);

	if (argc < 3)
		return 0;

	eWorkingMode = atoi(argv[2]);
	LOG_PROCESS_ERROR(eWorkingMode > wmInvalid && eWorkingMode < wmTotal);

	nRetCode = CIocpMgr::GetInstance().Init();
	LOG_PROCESS_ERROR(nRetCode);

	snprintf(szFindPattern, MAX_PATH, "%s\\*.log", argv[1]);

	hFind = FindFirstFile(szFindPattern, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		return 0;

	do
	{
		IOCP_TASK* pTask = NULL;

		if (FindFileData.cFileName[0] == L'.')
			continue;

		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;

		if (FindFileData.nFileSizeHigh <= 0 && FindFileData.nFileSizeLow <= 0)
			continue;

		pTask = new IOCP_TASK;
		LOG_PROCESS_ERROR(pTask);

		memset(pTask, 0, sizeof(IOCP_TASK));
		snprintf(pTask->szFilePath, MAX_PATH, "%s\\%s", argv[1], FindFileData.cFileName);
		pTask->hFile = INVALID_HANDLE_VALUE;
		pTask->eWorkingMode = eWorkingMode;

		//_ReadFileData(pTask);
		//_ProcessFileData(pTask);

		nRetCode = CIocpMgr::GetInstance().SubmitTask(pTask);
		LOG_PROCESS_ERROR(nRetCode);

		while (CIocpMgr::GetInstance().GetUncompletedTaskCount() > IOCP_THREAD_COUNT / 2)
		{
			pTask = CIocpMgr::GetInstance().FetchResult();
			if (pTask)
			{
				_FetchTask(pTask);
				_CleanTask(pTask);
			}
			else
			{
				Sleep(1);
			}
		}

		continue;
	Exit0:
		WRN("failed to analysis log file %s\n", FindFileData.cFileName);
		_CleanTask(pTask);
	} while (FindNextFile(hFind, &FindFileData));

	while (CIocpMgr::GetInstance().GetUncompletedTaskCount() > 0)
	{
		IOCP_TASK* pTask = CIocpMgr::GetInstance().FetchResult();
		if (pTask)
		{
			_FetchTask(pTask);
			_CleanTask(pTask);
		}
		else
		{
			Sleep(1);
		}
	}

	for (ERROR_MAP::iterator it = g_ErrorMap.begin();
		it != g_ErrorMap.end(); ++it)
	{
		printf("%s\t%d\n", it->first.c_str(), it->second);
	}

	CIocpMgr::GetInstance().UnInit();

	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
	}

	CLog::GetInstance().UnInit();

	return 0;
}

