#ifndef _DIR_H_
#define _DIR_H_

BOOL g_CreateDirectory(const char* dirName, BOOL bforce);
BOOL g_DirectoryExists(const char* dirName);
BOOL g_DeleteDirectory(const char* dirName);

template<class TFunc>
inline BOOL g_DirectoryTraverse(const char* szDirectoryPath, TFunc& rFunc)
{
	INT32 nRetCode = 0;

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA FindFileData;
	char szPattern[MAX_PATH] = { 0 };

	snprintf(szPattern, MAX_PATH, "%s\\*.*", szDirectoryPath);
	hFind = FindFirstFile(szPattern, &FindFileData);
	PROCESS_ERROR(hFind != INVALID_HANDLE_VALUE);

	do
	{
		if (FindFileData.cFileName[0] == L'.')
			continue;

		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
			continue;

		if (!(rFunc.RequireDirectory()) == (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			continue;
		}

		nRetCode = rFunc(FindFileData.cFileName);
		LOG_CHECK_ERROR(nRetCode);

	} while (FindNextFile(hFind, &FindFileData));

	FindClose(hFind);
	hFind = INVALID_HANDLE_VALUE;

	return TRUE;
Exit0:
	if (hFind)
	{
		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
	}
	return FALSE;
}

#endif  // _DIR_H_