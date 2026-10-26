#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const __int32 BUFFER_LENGTH = 1024 * 1024 * 8;


__int32 FindNumFromBuffer(const char *pcszModel, const char *pcszSouce)
{
    if (pcszModel == NULL || pcszSouce == NULL)
        return 0;

    __int32 i = 0;
    __int32 j = 0;

    while (pcszSouce[i] != '\0')
    {
        while ((pcszModel[j] != '\0') && (pcszSouce[i] == pcszModel[j]))
        {
            ++i;
            ++j;
        }

        if (pcszModel[j] == '\0')
        {
            char    szNum[128] = { 0 };

            while (pcszSouce[i++] != '(')
                ;

            __int32 nIndex = 0;
            while (pcszSouce[i] != ')')
            {
                szNum[nIndex++] = pcszSouce[i++];
            }

            return atoi(szNum);
        }
        else
            j = 0;


        ++i;
    }

    return 0;
}


__int32 main(_In_ int _Argc, _In_reads_(_Argc) _Pre_z_ char ** _Argv, _In_z_ char ** _Env)
{
    __int32  nActualCFileLength = 0;
    __int32   nCBufferLength = 1024 * 16;
    char    *pCFileBuffer = new char[nCBufferLength];
    if (pCFileBuffer == NULL)
        return 0;
    memset(pCFileBuffer, 0, nCBufferLength);
    FILE    *pF = fopen("../../../inc/gm/gm_version.h", "r");

    fseek(pF, 0, SEEK_END);
    nActualCFileLength = ftell(pF);
    fseek(pF, 0, SEEK_SET);
    fread(pCFileBuffer, 1, nActualCFileLength, pF);
    fclose(pF);


    __int32     nMajorVersion = 0;
    __int32     nMinorVersion = 0;

    nMajorVersion = FindNumFromBuffer("GM_MAJOR_VERSION", pCFileBuffer);
    nMinorVersion = FindNumFromBuffer("GM_MINOR_VERSION", pCFileBuffer);

    delete[] pCFileBuffer;
    pCFileBuffer = NULL;
    pF = NULL;

    if (nMajorVersion == 0 || nMinorVersion == 0)
        return 0;

    // init
    char        szVersion[64] = { 0 };
    __int32 nVersionLength = sprintf_s(szVersion, "%d.%d", nMajorVersion, nMinorVersion);

    FILE *pVersionFile = fopen("./pak-version.model", "r");
    if (pVersionFile == NULL)
    {
        return 1;
    }
    FILE    *pOutputFile = fopen("./pak.bat", "w");
    if (pOutputFile == NULL)
    {
        fclose(pVersionFile);
        return 1;
    }

    fseek(pVersionFile, 0, SEEK_END);
    __int32 nLength = ftell(pVersionFile);
    fseek(pVersionFile, 0, SEEK_SET);

    char    *pSBuffer = new char[BUFFER_LENGTH];
    memset(pSBuffer, 0, BUFFER_LENGTH);

    fread(pSBuffer, nLength, 1, pVersionFile);
    fclose(pVersionFile);



    // run
    char    *pOBuffer = new char[BUFFER_LENGTH];
    memset(pOBuffer, 0, BUFFER_LENGTH);

    __int32     nOIndex = 0;
    __int32     nSIndex = 0;
    __int32 nOlength = nVersionLength + nLength;


    while ((pOBuffer[nOIndex++] = pSBuffer[nSIndex++]) != '_')
        continue;
    for (__int32 i = 0; i < nVersionLength; ++i)
    {
        pOBuffer[nOIndex++] = szVersion[i];
    }
    memcpy(pOBuffer + nOIndex, pSBuffer + nSIndex, nLength - nSIndex);

    fwrite(pOBuffer, nOlength, 1, pOutputFile);
    fclose(pOutputFile);


    // release

    if (pSBuffer)
    {
        delete[] pSBuffer;
    }
    if (pOBuffer)
    {
        delete[] pOBuffer;
    }

    
    printf("OK!\n");

    return 0;
}
