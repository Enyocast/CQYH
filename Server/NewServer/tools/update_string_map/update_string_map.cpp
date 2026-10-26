// update_string_map.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define ERROR_CODE_DEF_FILE_NAME    "../../common/define/error_def.h"
#define STRING_MAP_FILE_NAME        L"../../client/ue3/mmogame/config/stringmap.txt"
#define NEW_STRING_MAP_FILE_NAME    L"../../client/ue3/mmogame/config/stringmap_new.txt"

int _tmain(int argc, _TCHAR* argv[])
{
    FILE* pErrorCodeFile = NULL;
    FILE* pStringMapFile = NULL;
    FILE* pNewStringMapFile = NULL;
    std::map<std::wstring, int> error_map1;
    std::map<int, std::wstring> error_map2;
    std::map<int, std::wstring> comment_map;

    int newcount = 0;
    int erasecount = 0;
    bool start_def = false;
    int error_code_num = -1;

    pErrorCodeFile = fopen(ERROR_CODE_DEF_FILE_NAME, "r");
    if (pErrorCodeFile == NULL)
    {
        wprintf(L"cannot find %s", L"common/define/error_def.h");
        goto Exit0;
    }

    while (!feof(pErrorCodeFile))
    {
        char line[1024];
        wchar_t error_name[1024];
        int error_name_len = 0;
        wchar_t comment[1024];
        int comment_len = 0;
        fgets(line, 1024, pErrorCodeFile);

        if (!start_def)
        {
            char* pszStartTag = strstr(line, "enum ERROR_CODE_DEF");
            if (pszStartTag)
                start_def = true;
            else
                continue;
        }

        char* pszEndTag = strstr(line, "};");
        if (pszEndTag)
            break;

        char* pszPrefix = strstr(line, "err");
        if (pszPrefix == NULL)
            continue;

        error_code_num++;

        char* pszBeginWord = strstr(line, "Begin");
        char* pszEndWord = strstr(line, "End");
        char* pszGMWord = strstr(line, "errGM");
        if (pszBeginWord || pszEndWord || pszGMWord)
            continue;

        char* pszComment = strstr(line, "///<");

        char* pszName = strtok(pszPrefix, " ,=");
        if (pszName == NULL)
            continue;

        while (*pszName)
        {
            error_name[error_name_len] = *pszName;
            error_name_len++;
            pszName++;
        }
        error_name[error_name_len] = 0;

        if (error_map1.find(error_name) != error_map1.end())
        {
            wprintf(L"duplicated error name %s\n", error_name);
        }
        error_map1[error_name] = error_code_num;
        error_map2[error_code_num] = std::wstring(error_name);

        if (pszComment)
        {
            pszComment += 4;
            pszComment = strtok(pszComment, " ,;\n");
            MultiByteToWideChar(CP_UTF8, 0, pszComment, -1, comment, 1024);
            comment_map[error_code_num] = std::wstring(comment);
        }
        else
        {
            comment_map[error_code_num] = std::wstring(L"no comment");
        }
    }

    pStringMapFile = _wfopen(STRING_MAP_FILE_NAME, L"rb");
    if (pStringMapFile == NULL)
    {
        wprintf(L"cannot find %s", STRING_MAP_FILE_NAME);
        goto Exit0;
    }

    pNewStringMapFile = _wfopen(NEW_STRING_MAP_FILE_NAME, L"wb");
    if (pNewStringMapFile == NULL)
    {
        wprintf(L"cannot find %s", STRING_MAP_FILE_NAME);
        goto Exit0;
    }

    unsigned short bom = 0xFEFF;
    fwrite(&bom, 1, 2, pNewStringMapFile);

    while (!feof(pStringMapFile))
    {
        wchar_t line[1024];
        fgetws(line, 1024, pStringMapFile);

        wchar_t* pszPrefix = wcsstr(line, L"MMOErrorInfo.ERROR_CODE_DEF.");
        if (pszPrefix == NULL)
            continue;

        wchar_t* pszErrorName = wcstok(line + wcslen(L"MMOErrorInfo.ERROR_CODE_DEF."), L"\t");
        if (pszErrorName == NULL)
            continue;

        if (error_map1.find(pszErrorName) == error_map1.end())
        {
            fwprintf(pNewStringMapFile, L"MMOErrorInfo.ERROR_CODE_DEF.%s\tinvalid enum value, please erase it\tinvalid enum value, please erase it\t0\t0\n", pszErrorName);
            erasecount++;
            continue;
        }
        else
        {
            error_map1.erase(pszErrorName);
        }
    }

    for (std::map<int, std::wstring>::iterator it = error_map2.begin();
        it != error_map2.end(); ++it)
    {
        if (error_map1.find(it->second) != error_map1.end())
        {
            fwprintf(pNewStringMapFile, L"MMOErrorInfo.ERROR_CODE_DEF.%s\t%s\t%s\t0\t0\n", it->second.c_str(),
                comment_map[it->first].c_str(), comment_map[it->first].c_str());
            newcount++;
        }
    }

    wprintf(L"%d old error code(s), %d new error code(s)\n", erasecount, newcount);
    wprintf(L"generated stringmap_new.txt in folder client/ue3/mmogame/config\n");

Exit0:
    if (pErrorCodeFile)
        fclose(pErrorCodeFile);
    if (pStringMapFile)
        fclose(pStringMapFile);
    if (pNewStringMapFile)
        fclose(pNewStringMapFile);

	return 0;
}

