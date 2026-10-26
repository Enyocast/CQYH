#include "stdafx.h"

#include <map>
#include <hash_map>
#include <direct.h>

#include "pak_file.h"
#include "md5.h"
#include "string_ex.h"
#include "hash.h"

CPakFile g_PakFile;

bool TraverseDir(const char* pcszDirName, bool bCompare)
{
	bool bResult = false;
	int nRetCode = 0;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	char* pszPackBuffer = NULL;
	char* pszDiskBuffer = NULL;
	FILE* pFile = NULL;

	if (pcszDirName == NULL)
		goto Exit0;

	printf("Traversing directory %s...\n", pcszDirName);

	char szPattern[MAX_PATH];
	if (pcszDirName[0])
		snprintf(szPattern, MAX_PATH, "%s\\*.*", pcszDirName);
	else
		snprintf(szPattern, MAX_PATH, "*.*", pcszDirName);
	hFind = FindFirstFile(szPattern, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		goto Exit0;

	do
	{
		if (FindFileData.cFileName[0] == L'.')
			continue;

		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
		{
			printf("\tSkip %s\n", FindFileData.cFileName);
			continue;
		}

		if (strncmp(FindFileData.cFileName, "Thumbs.db", MAX_PATH) == 0)
		{
			printf("\tSkip %s\n", FindFileData.cFileName);
			continue;
		}

		char* pszSuffix = (char*)(FindFileData.cFileName + 
			strlen(FindFileData.cFileName) - 4);
		unsigned long uSuffix = (pszSuffix[0] << 24) + (pszSuffix[1] << 16) + 
			(pszSuffix[2] << 8) + pszSuffix[3];
		switch (uSuffix)
		{
		case '.max':
		case '.log':
		case '.bak':
			printf("\tSkip %s\n", FindFileData.cFileName);
			continue;
		}

		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			char szNewDir[MAX_PATH];
			if (pcszDirName[0])
				snprintf(szNewDir, MAX_PATH, "%s\\%s", pcszDirName, FindFileData.cFileName);
			else
				snprintf(szNewDir, MAX_PATH, "%s", FindFileData.cFileName);

			nRetCode = TraverseDir(szNewDir, bCompare);
			if (!nRetCode)
				goto Exit0;

			continue;
		}

		char szCurrentDir[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, szCurrentDir);

		char szFilePath[MAX_PATH];
		if (pcszDirName[0])
			snprintf(szFilePath, MAX_PATH, "%s\\%s\\%s", szCurrentDir, 
			pcszDirName, FindFileData.cFileName);
		else
			snprintf(szFilePath, MAX_PATH, "%s\\%s", szCurrentDir, FindFileData.cFileName);

		char szPackagePath[MAX_PATH];
		if (pcszDirName[0])
			snprintf(szPackagePath, MAX_PATH, "%s\\%s", pcszDirName, FindFileData.cFileName);
		else
			snprintf(szPackagePath, MAX_PATH, "%s", FindFileData.cFileName);

		if (bCompare)
		{
			int nFileIndex = g_PakFile.FindFile(szPackagePath);
			if (nFileIndex == INVALID_PAK_FILE_INDEX)
				printf("Cannot find file %s in the package!\n", szPackagePath);

			size_t uPackFileSize = g_PakFile.GetFileSize(nFileIndex);

			pszPackBuffer = new char[uPackFileSize];
			if (pszPackBuffer == NULL)
				goto Exit0;

			pszDiskBuffer = new char[uPackFileSize];
			if (pszDiskBuffer == NULL)
				goto Exit0;

			nRetCode = g_PakFile.ReadFileData(nFileIndex, pszPackBuffer, uPackFileSize);
			if (!nRetCode)
			{
				printf("Failed to read file %s\n", szPackagePath);
				goto Exit0;
			}

			pFile = fopen(szFilePath, "rb");
			if (pFile == NULL)
			{
				printf("Failed to open file %s\n", szFilePath);
				goto Exit0;
			}

			nRetCode = fseek(pFile, 0, SEEK_END);
			if (nRetCode != 0)
			{
				printf("Failed to get file length %s\n", szFilePath);
				goto Exit0;
			}

			size_t uDiskFileSize = ftell(pFile);

			nRetCode = fseek(pFile, 0, SEEK_SET);
			if (nRetCode != 0)
			{
				printf("Failed to seek to file begin %s\n", szFilePath);
				goto Exit0;
			}

			if (uPackFileSize != uDiskFileSize)
			{
				printf("File sizes are different %s : %d, %d\n", szFilePath,
					uPackFileSize, uDiskFileSize);
				goto Exit0;
			}

			uPackFileSize = fread(pszDiskBuffer, 1, uDiskFileSize, pFile);
			if (uPackFileSize != uDiskFileSize)
			{
				printf("Failed to read file %s\n", szFilePath);
				goto Exit0;
			}

			fclose(pFile);

			unsigned char ucPackMD5Value[16];
			unsigned char ucDiskMD5Value[16];

			calc_md5(ucPackMD5Value, (UINT8*)pszPackBuffer, uPackFileSize);
			calc_md5(ucDiskMD5Value, (UINT8*)pszDiskBuffer, uDiskFileSize);

			for (int i = 0; i < 16; i++)
			{
				if (ucPackMD5Value[i] != ucDiskMD5Value[i])
				{
					printf("MD5 values are not equal %s\n", szFilePath);
					goto Exit0;
				}
			}

			SAFE_DELETE_ARRAY(pszPackBuffer);
			SAFE_DELETE_ARRAY(pszDiskBuffer);

			printf("Verified %s\n", szPackagePath);
		}
		else
		{
			nRetCode = g_PakFile.AddFile(szPackagePath, szFilePath);
			if (!nRetCode)
			{
				printf("Failed to add %s into package!\n", szFilePath);
				goto Exit0;
			}
			else
			{
				UINT32 dwHashA, dwHashB;
				hash_file_name(szPackagePath, &dwHashA, &dwHashB);
				printf("Added %s hash(%08X, %08X)\n", szFilePath, dwHashA, dwHashB);
			}
		}

	}while (FindNextFile(hFind, &FindFileData));

	bResult = true;

Exit0:
	if (hFind != INVALID_HANDLE_VALUE)
		FindClose(hFind);

	SAFE_DELETE_ARRAY(pszPackBuffer);
	SAFE_DELETE_ARRAY(pszDiskBuffer);

	if (pFile)
	{
		fclose(pFile);
		pFile = NULL;
	}

	return bResult;
}

bool CreatePackage(const char* pcszFolderName, BOOL bHasNameBuffer)
{
	bool bResult = false;
	bool nRetCode = false;

	if (pcszFolderName == NULL)
		return false;

	printf("Start to create package...\n");

	char szCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szCurrentDir);

	char szPackageName[MAX_PATH];
	snprintf(szPackageName, MAX_PATH, "%s.pak", pcszFolderName);

	nRetCode = g_PakFile.Create(szPackageName);
	if (!nRetCode)
	{
		printf("Cannot create pak file %s!\n", szPackageName);
		goto Exit0;
	}

	if (bHasNameBuffer)
		nRetCode = g_PakFile.SetPackageFlag(false, true, true, true);
	else
		nRetCode = g_PakFile.SetPackageFlag(false, false, false, true);
	if (!nRetCode)
	{
		printf("Failed to set package flag!\n");
		goto Exit0;
	}

	nRetCode = TraverseDir(pcszFolderName, false);
	if (!nRetCode)
		goto Exit0;

	bResult = true;
Exit0:

	SetCurrentDirectory(szCurrentDir);

	g_PakFile.Close();

	return bResult;
}

bool ComparePackage(const char* pcszFolderName, const char* pcszFileName)
{
	bool bResult = false;
	bool nRetCode = false;

	if (pcszFolderName == NULL || pcszFileName == NULL)
		return false;

	printf("Start to compare package...\n");

	char szCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szCurrentDir);

	nRetCode = g_PakFile.Open(pcszFileName);
	if (!nRetCode)
	{
		printf("Cannot open pak file %s!\n", pcszFileName);
		goto Exit0;
	}

	nRetCode = TraverseDir(pcszFolderName, true);
	if (!nRetCode)
		goto Exit0;

	bResult = true;
Exit0:

	SetCurrentDirectory(szCurrentDir);
	g_PakFile.Close();

	return bResult;
}

bool VerifyPackage(const char* pcszFileName)
{
	bool bResult = false;
	int nRetCode = 0;
	typedef stdext::hash_map<unsigned long, int> FILE_HASH_TABLE;
	FILE_HASH_TABLE FileHashTable; 

	if (pcszFileName == NULL)
		return false;

	printf("Start to verify package...\n");

	nRetCode = g_PakFile.Open(pcszFileName);
	if (!nRetCode)
	{
		printf("Cannot open pak file %s!\n", pcszFileName);
		goto Exit0;
	}

	for (int nFileIndex = 0; nFileIndex < g_PakFile.GetFileCount(); nFileIndex++)
	{
		const char* pcszFileName = g_PakFile.GetFileName(nFileIndex);
		if (pcszFileName == NULL)
		{
			printf("Cannot get name of file %d in package!\n", nFileIndex);
			goto Exit0;
		}

		unsigned long ulHashValueA = 0;
		unsigned long ulHashValueB = 0;
		nRetCode = g_PakFile.GetFileHashValue(nFileIndex, ulHashValueA, ulHashValueB);
		if (!nRetCode)
		{
			printf("Failed to get file hash value %s!\n", pcszFileName);
			goto Exit0;
		}

		FILE_HASH_TABLE::iterator it = FileHashTable.find(ulHashValueB);
		if (it != FileHashTable.end())
		{
			const char* pcszConflictFileName = g_PakFile.GetFileName(it->second);
			if (pcszConflictFileName == NULL)
			{
				printf("Failed to get conflict file name %s!\n", pcszFileName);
				goto Exit0;
			}

			printf("Hash value conflicted %s : %s !\n", pcszFileName, pcszConflictFileName);
		}

		FileHashTable.insert(std::make_pair(ulHashValueB, nFileIndex));

		nRetCode = g_PakFile.VerifyFile(nFileIndex);
		if (!nRetCode)
		{
			printf("Failed to verify file %s!\n", pcszFileName);
			goto Exit0;
		}
		else
		{
			printf("Verified %s!\n", pcszFileName);
		}
	}

	bResult = true;
Exit0:
	g_PakFile.Close();

	return bResult;
}

bool ExtractPackage(const char* pcszFileName, const char* pcszFolderName)
{
	bool bResult = false;
	int nRetCode = 0;

	if (pcszFileName == NULL || pcszFolderName == NULL)
		return false;

	printf("Start to extract package...\n");

	char szCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szCurrentDir);

	nRetCode = g_PakFile.Open(pcszFileName);
	if (!nRetCode)
	{
		printf("Cannot open pak file %s!\n", pcszFileName);
		goto Exit0;
	}

	char szNewDir[MAX_PATH];
	snprintf(szNewDir, MAX_PATH, "%s\\%s", szCurrentDir, pcszFolderName);

	mkdir(szNewDir);
	nRetCode = SetCurrentDirectory(szNewDir);
	if (!nRetCode)
	{
		printf("Wrong folder name %s!\n", szNewDir);
		goto Exit0;
	}

	for (int nFileIndex = 0; nFileIndex < g_PakFile.GetFileCount(); nFileIndex++)
	{
		if (g_PakFile.IsDeletedFile(nFileIndex))
			continue;

		const char* pcszFileName = g_PakFile.GetFileName(nFileIndex);
		if (pcszFileName == NULL)
		{
			printf("Cannot get name of file %d in package!\n", nFileIndex);
			goto Exit0;
		}

		nRetCode = g_PakFile.ExtractFile(nFileIndex);
		if (!nRetCode)
		{
			printf("Failed to extract file %s!\n", pcszFileName);
			goto Exit0;
		}
		else
		{
			printf("Extracted %s!\n", pcszFileName);
		}
	}

	bResult = true;
Exit0:
	SetCurrentDirectory(szCurrentDir);
	g_PakFile.Close();

	return bResult;
}

bool AppendPackage(const char* pcszDestFileName, const char* pcszSrcFileName)
{
	bool bResult = false;
	int nRetCode = 0;
	CPakFile DestPakFile;
	CPakFile SrcPakFile;

	if (pcszDestFileName == NULL || pcszSrcFileName == NULL)
		return false;

	printf("Start to append package...\n");

	nRetCode = DestPakFile.Open(pcszDestFileName);
	if (!nRetCode)
	{
		printf("Cannot open pak file %s!\n", pcszDestFileName);
		goto Exit0;
	}

	nRetCode = SrcPakFile.Open(pcszSrcFileName);
	if (!nRetCode)
	{
		printf("Cannot open pak file %s!\n", pcszSrcFileName);
		goto Exit0;
	}

	for (int nFileIndex = 0; nFileIndex < SrcPakFile.GetFileCount(); nFileIndex++)
	{
		const char* pcszFileName = SrcPakFile.GetFileName(nFileIndex);
		if (pcszFileName == NULL)
		{
			printf("Cannot get name of file %d in package!\n", nFileIndex);
			goto Exit0;
		}

		if (SrcPakFile.IsDeletedFile(nFileIndex))
		{
			DestPakFile.DelFile(pcszFileName);
			printf("Deleted %s\n", pcszFileName);
		}
		else
		{
			nRetCode = DestPakFile.AddFileFromPak(pcszFileName, &SrcPakFile, nFileIndex);
			if (!nRetCode)
			{
				printf("Failed to add file %s into package!\n", pcszFileName);
				goto Exit0;
			}

			printf("Added or modified %s\n", pcszFileName);
		}
	}

	bResult = true;
Exit0:
	SrcPakFile.Close();
	DestPakFile.Close();

	return bResult;
}

bool CompareMD5(unsigned char* pucMD5Value1, unsigned char* pucMD5Value2)
{
	if (pucMD5Value1 == NULL || pucMD5Value2 == NULL)
		return false;

	for (int nIndex = 0; nIndex < 16; nIndex++)
	{
		if (pucMD5Value1[nIndex] != pucMD5Value2[nIndex])
			return false;
	}
	return true;
}

bool GenPatch(const char* pcszOldFileName, const char* pcszNewFileName, const char* pcszPatchFileName)
{
	bool bResult = false;
	int nRetCode = 0;
	CPakFile OldFile;
	CPakFile NewFile;
	CPakFile PatchFile;

	if (pcszOldFileName == NULL || pcszNewFileName == NULL || pcszPatchFileName == NULL)
		goto Exit0;

	nRetCode = OldFile.Open(pcszOldFileName);
	if (!nRetCode)
	{
		printf("Cannot open file %s!\n", pcszOldFileName);
		goto Exit0;
	}

	nRetCode = NewFile.Open(pcszNewFileName);
	if (!nRetCode)
	{
		printf("Cannot open file %s!\n", pcszNewFileName);
		goto Exit0;
	}

	nRetCode = PatchFile.Create(pcszPatchFileName);
	if (!nRetCode)
	{
		printf("Cannot create file %s!\n", pcszPatchFileName);
		goto Exit0;
	}

	for (int nNewFileIndex = 0; nNewFileIndex < NewFile.GetFileCount(); nNewFileIndex++)
	{
		const char* pcszFileName = NewFile.GetFileName(nNewFileIndex);
		if (pcszFileName == NULL)
		{
			printf("Cannot get name of file %d in package!\n", nNewFileIndex);
			goto Exit0;
		}

		if (NewFile.IsDeletedFile(nNewFileIndex))
			continue;

		int nOldFileIndex = OldFile.FindFile(pcszFileName);
		if (nOldFileIndex == INVALID_PAK_FILE_INDEX)
		{
			// new file
			nRetCode = PatchFile.AddFileFromPak(pcszFileName, &NewFile, nNewFileIndex);
			if (!nRetCode)
			{
				printf("Failed to add file %s into package!\n", pcszFileName);
				goto Exit0;
			}

			printf("New file %s\n", pcszFileName);
		}
		else
		{
			unsigned char ucOldMD5Value[16];
			unsigned char ucNewMD5Value[16];

			nRetCode = NewFile.GetFileMD5Value(nNewFileIndex, ucNewMD5Value);
			if (!nRetCode)
			{
				printf("Failed to get md5 value of new file %d!\n", nNewFileIndex);
				goto Exit0;
			}

			nRetCode = OldFile.GetFileMD5Value(nOldFileIndex, ucOldMD5Value);
			if (!nRetCode)
			{
				printf("Failed to get md5 value of old file %d!\n", nOldFileIndex);
				goto Exit0;
			}

			nRetCode = CompareMD5(ucOldMD5Value, ucNewMD5Value);
			if (!nRetCode)
			{
				// modified file
				nRetCode = PatchFile.AddFileFromPak(pcszFileName, &NewFile, nNewFileIndex);
				if (!nRetCode)
				{
					printf("Failed to add file %s into package!\n", pcszFileName);
					goto Exit0;
				}

				printf("Modified file %s\n", pcszFileName);
			}
			else
			{
				// same file
			}
		}
	}

	for (int nOldFileIndex = 0; nOldFileIndex < OldFile.GetFileCount(); nOldFileIndex++)
	{
		const char* pcszFileName = OldFile.GetFileName(nOldFileIndex);
		if (pcszFileName == NULL)
		{
			printf("Cannot get name of file %d in package!\n", nOldFileIndex);
			goto Exit0;
		}

		int nNewFileIndex = NewFile.FindFile(pcszFileName);
		if (nNewFileIndex == INVALID_PAK_FILE_INDEX)
		{
			// deleted file
			int nData = 0xDDDDDDDD;
			nRetCode = PatchFile.AddFileFromData(pcszFileName, 0, 0, (char*)&nData, sizeof(nData));
			if (!nRetCode)
			{
				printf("Failed to add file %s!\n", pcszFileName);
				goto Exit0;
			}

			nRetCode = PatchFile.DelFile(pcszFileName);
			if (!nRetCode)
			{
				printf("Failed to delete file %s!\n", pcszFileName);
				goto Exit0;
			}

			printf("Deleted file %s\n", pcszFileName);
		}
	}

	bResult = true;

Exit0:
	OldFile.Close();
	NewFile.Close();
	PatchFile.Close();

	return bResult;
}

bool ListPackage(const char* pcszFileName)
{
	bool bResult = false;
	int nRetCode = 0;

	if (pcszFileName == NULL)
		goto Exit0;

	printf("File list in %s:\n", pcszFileName);

	nRetCode = g_PakFile.Open(pcszFileName);
	if (!nRetCode)
	{
		printf("Cannot open pak file %s!\n", pcszFileName);
		goto Exit0;
	}

	for (int nFileIndex = 0; nFileIndex < g_PakFile.GetFileCount(); nFileIndex++)
	{
		const char* pcszFileName = g_PakFile.GetFileName(nFileIndex);
		if (pcszFileName == NULL)
		{
			printf("Cannot get name of file %d in package!\n", nFileIndex);
			goto Exit0;
		}

		if (g_PakFile.IsDeletedFile(nFileIndex))
		{
			printf(" Deleted %s\n", pcszFileName);
		}
		else
		{
			size_t uSize = g_PakFile.GetFileSize(nFileIndex);

			printf(" %8u %s\n", uSize, pcszFileName);
		}
	}

	bResult = true;
Exit0:
	g_PakFile.Close();

	return bResult;
}

bool ListPackageMD5(const char* pcszFileName)
{
	bool bResult = false;
	int nRetCode = 0;

	if (pcszFileName == NULL)
		goto Exit0;

	printf("File MD5 list in %s:\n", pcszFileName);

	nRetCode = g_PakFile.Open(pcszFileName);
	if (!nRetCode)
	{
		printf("Cannot open pak file %s!\n", pcszFileName);
		goto Exit0;
	}

	for (int nFileIndex = 0; nFileIndex < g_PakFile.GetFileCount(); nFileIndex++)
	{
		const char* pcszFileName = g_PakFile.GetFileName(nFileIndex);
		if (pcszFileName == NULL)
		{
			printf("Cannot get name of file %d in package!\n", nFileIndex);
			goto Exit0;
		}

		if (g_PakFile.IsDeletedFile(nFileIndex))
		{
			printf(" Deleted %s\n", pcszFileName);
		}
		else
		{
			unsigned char ucMD5Value[16] = {0};
			g_PakFile.GetFileMD5Value(nFileIndex, ucMD5Value);
			for (int i = 0; i < 16; i++)
			{
				printf("%02X", ucMD5Value[i]);
			}

			printf(" *%s\n", pcszFileName);
		}
	}

	bResult = true;
Exit0:
	g_PakFile.Close();

	return bResult;
}

void PrintHelp(void)
{
	printf("package handler v1.0, written by Jame Zhu, 2009-2013\n");
	printf("pak create FolderName\n");
	printf("pak createraw FolderName\n");
	printf("pak list FileName\n");
	printf("pak listmd5 FileName\n");
	printf("pak verify FolderName FileName\n");
	printf("pak verify FileName\n");
	printf("pak extract FileName [FolderName]\n");
	printf("pak append DestFileName SourceFileName\n");
	printf("pak patch OldFileName NewFileName PatchFileName\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool nRetCode = false;
	int* pn = NULL;

	if (argc < 2)
	{
		PrintHelp();
		goto Exit0;
	}
	else
	{
		if (stricmp(argv[1], "create") == 0 && argc >= 3)
		{
			nRetCode = CreatePackage(argv[2], TRUE);
			if (!nRetCode)
			{
				printf("Failed to create package!\n");
				goto Exit0;
			}
			else
				printf("Created package successfully!\n");

			char szPackageName[MAX_PATH];
			snprintf(szPackageName, MAX_PATH, "%s.pak", argv[2]);

			nRetCode = ComparePackage(argv[2], szPackageName);
			if (!nRetCode)
			{
				printf("Failed to compare package!\n");
				goto Exit0;
			}
			else
				printf("Compare package successfully!\n");
		}
		else if (stricmp(argv[1], "createraw") == 0 && argc >= 3)
		{
			nRetCode = CreatePackage(argv[2], FALSE);
			if (!nRetCode)
			{
				printf("Failed to create package!\n");
				goto Exit0;
			}
			else
				printf("Created package successfully!\n");

			char szPackageName[MAX_PATH];
			snprintf(szPackageName, MAX_PATH, "%s.pak", argv[2]);

			nRetCode = ComparePackage(argv[2], szPackageName);
			if (!nRetCode)
			{
				printf("Failed to compare package!\n");
				goto Exit0;
			}
			else
				printf("Compare package successfully!\n");
		}
		else if (stricmp(argv[1], "verify") == 0 && argc >= 4)
		{
			nRetCode = ComparePackage(argv[2], argv[3]);
			if (!nRetCode)
			{
				printf("Failed to verify package!\n");
				goto Exit0;
			}
			else
				printf("Compare verify successfully!\n");
		}
		else if (stricmp(argv[1], "verify") == 0 && argc == 3)
		{
			nRetCode = VerifyPackage(argv[2]);
			if (!nRetCode)
			{
				printf("Failed to verify package!\n");
				goto Exit0;
			}
			else
				printf("Verify package successfully!\n");
		}
		else if (stricmp(argv[1], "extract") == 0 && argc == 4)
		{
			nRetCode = ExtractPackage(argv[2], argv[3]);
			if (!nRetCode)
			{
				printf("Failed to extract package!\n");
				goto Exit0;
			}
			else
				printf("Extract package successfully!\n");
		}
		else if (stricmp(argv[1], "extract") == 0 && argc == 3)
		{
			nRetCode = ExtractPackage(argv[2], ".");
			if (!nRetCode)
			{
				printf("Failed to extract package!\n");
				goto Exit0;
			}
			else
				printf("Extract package successfully!\n");
		}
		else if (stricmp(argv[1], "append") == 0 && argc >= 4)
		{
			nRetCode = AppendPackage(argv[2], argv[3]);
			if (!nRetCode)
			{
				printf("Failed to append package!\n");
				goto Exit0;
			}
			else
				printf("Append package successfully!\n");

			nRetCode = VerifyPackage(argv[2]);
			if (!nRetCode)
			{
				printf("Failed to verify package!\n");
				goto Exit0;
			}
			else
				printf("Verify package successfully!\n");

		}
		else if (stricmp(argv[1], "patch") == 0 && argc >= 5)
		{
			nRetCode = GenPatch(argv[2], argv[3], argv[4]);
			if (!nRetCode)
			{
				printf("Failed to create patch package!\n");
				goto Exit0;
			}
			else
				printf("Created patch package successfully!\n");

			nRetCode = VerifyPackage(argv[4]);
			if (!nRetCode)
			{
				printf("Failed to verify package!\n");
				goto Exit0;
			}
			else
				printf("Verify package successfully!\n");
		}
		else if (stricmp(argv[1], "list") == 0 && argc >= 3)
		{
			nRetCode = ListPackage(argv[2]);
			if (!nRetCode)
			{
				printf("Failed to list package file!\n");
				goto Exit0;
			}
		}
		else if (stricmp(argv[1], "listmd5") == 0 && argc >= 3)
		{
			nRetCode = ListPackageMD5(argv[2]);
			if (!nRetCode)
			{
				printf("Failed to list package file MD5 values!\n");
				goto Exit0;
			}
		}
		else
		{
			PrintHelp();
		}
	}

	/************************************************************************/

	/************************************************************************/

Exit0:
	g_PakFile.Close();

	return 0;
}

