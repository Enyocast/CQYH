#include "stdafx.h"
#include "dir.h"

#include "string_ex.h"

#define PATH_IS_DELIMITER(x)  (x == '\\' || x == '/')

#if (defined(WIN32) || defined(WIN64))
    #define PATH_DELIMITER '\\'
    #include <direct.h>
#else
    #define MAX_PATH 260
    #define PATH_DELIMITER '/'
#endif

BOOL g_CreateDirectory(const char* dirName, BOOL bforce)
{

#if (defined(WIN32) || defined(WIN64))
    //Nonzero if successful; otherwise 0
    int ret = CreateDirectory(dirName,NULL);
    if(0 != ret)
    {
        ret = TRUE;
    }
    else
    {
        ret = FALSE;
    }
#else
    //returns zero on success, or -1 if an error occurred
    int ret = mkdir(dirName,
        S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(0 == ret)
    {
        ret = TRUE;
    }
    else
    {
        ret = FALSE;
    }
#endif
    if (!bforce)
    {
        return ret;
    }

    if (FALSE == ret)
    {
        if(bforce)
        {
            char path[MAX_PATH];
            char * pos = path;
            strxcpy(path, dirName, sizeof(path));
            char * end = path + strlen(path);
            while(*pos != '\0')
            {
                if(PATH_IS_DELIMITER(*pos))
                {
                    *pos = '\0';
                }
                ++pos;
            }
            pos = path;
            bool bfirst = true;
            while(pos < end)
            {
                //==== Check whether the first path segment is a drive letter ====
                if(bfirst)
                {
                    bool isdrive = false;
                    char * p = pos;
                    while(*p != '\0')
                    {
                        if(*p == ':')
                        {
                            isdrive = true;
                        }
                        ++p;
                    }
                    if(isdrive)
                    {
                        pos = path + strlen(path);
                        *pos = PATH_DELIMITER;
                        bfirst = false;
                        continue;
                    }
                    bfirst = false;
                }
                //==== Finished checking the first path segment for a drive letter ====

                //==== Create the directory if this path segment does not exist ====
                if(!g_DirectoryExists(path))
                {
#if (defined(WIN32) || defined(WIN64))
                    if(0 != _mkdir(path))
#else
                    if(0 != mkdir(path, S_IREAD | S_IWRITE))
#endif
                    {
                        return FALSE;
                    }
                }
                pos = path + strlen(path);
                *pos = PATH_DELIMITER;
            }
        }
        else//bforce == false
        {
            return FALSE;
        }
    }
    return TRUE;
}

BOOL g_DirectoryExists(const char *dirName)
{
#if (defined(WIN32) || defined(WIN64))
    int nCode = GetFileAttributesA(dirName);
    if (nCode == -1)
    {
        return false;
    }
    return FILE_ATTRIBUTE_DIRECTORY & nCode;
#else
    struct stat fileStat;
    int ret = stat(dirName, &fileStat);
    if ( ret == 0)
    {
        return S_ISDIR(fileStat.st_mode);
    }
    return FALSE;
#endif
}

BOOL g_DeleteDirectory(const char *dirName)
{
	INT32 nRetCode = 0;

	//char szTargetName[1024] = {};
	//LOG_PROCESS_ERROR(strlen(dirName) + 1 <= sizeof(szTargetName));

	//memset(szTargetName, 0, sizeof(szTargetName));
	//strxcpy(szTargetName, dirName, sizeof(szTargetName));

	//SHFILEOPSTRUCT file_op = {
	//	NULL,
	//	FO_DELETE,
	//	szTargetName,
	//	"",
	//	FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT,
	//	false,
	//	0,
	//	NULL
	//};

	//nRetCode = SHFileOperation(&file_op);
	//LOG_PROCESS_ERROR(nRetCode == 0);

	char szParam[MAX_PATH] = { 0 };
	sprintf(szParam, "/C \"echo ing 1>deleting_%s.txt && rmdir /S /Q %s && del /Q /F deleting_%s.txt\"", dirName, dirName, dirName);
	INF("cmd.exe %s", szParam);
	nRetCode = (INT32)ShellExecute(NULL, "open", "cmd.exe", szParam, NULL, SW_HIDE);
	LOG_CHECK_ERROR(nRetCode > 32);

	return TRUE;
Exit0:
	return FALSE;
}

