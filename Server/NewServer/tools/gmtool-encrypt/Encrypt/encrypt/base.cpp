#include "stdafx.h"
#include "base.h"
#include <string.h>


bool Encrypt(__int32 nInputLength, const char *pInputData, __int32 &nOutputLength, char *pOutputData)
{
    __int32     tmp = 0;
    const __int32     nMaxLength = nOutputLength;
    __int32     k = 1000000 / 7;

    if (pInputData == 0 || pOutputData == 0)
        return false;
    if (nInputLength + 7 > nMaxLength)
        return false;

    memset(pOutputData, 0, nMaxLength);

    nOutputLength = nInputLength + sizeof(__int32);
    tmp = nOutputLength / sizeof(__int32);
    if (tmp * sizeof(__int32) != nOutputLength)
        nOutputLength = sizeof(__int32) * (tmp + 1);
    
    *(__int32*)pOutputData = nInputLength;
    memcpy(pOutputData + sizeof(__int32), pInputData, nInputLength);
    
    ++tmp;
    __int32 *pData = 0;
    pData = (__int32 *)pOutputData;
    for (__int32 i = 0; i < tmp; ++i)
    {
        if (i == 0)
            pData[i] ^= k;
        else
            pData[i] ^= pData[i - 1];
    }

    return true;
}

bool Decrypt(__int32 nInputLength, const char *pInputData, __int32 &nOutputLength, char *pOutputData)
{
    __int32     tmp = 0;
    const __int32     nMaxLength = nOutputLength;
    __int32     k = 1000000 / 7;

    if (pInputData == 0 || pOutputData == 0)
        return false;
    if (nInputLength > nMaxLength)
        return false;

    memset(pOutputData, 0, nMaxLength);

    tmp = nInputLength / sizeof(__int32);
    if (tmp * sizeof(__int32) != nInputLength)
        return false;

    *(__int32*)pOutputData = nInputLength;
    memcpy(pOutputData, pInputData, nInputLength);

    ++tmp;
    __int32 *pData = 0;
    pData = (__int32 *)pOutputData;
    for (__int32 i = tmp - 1; i >= 0; --i)
    {
        if (i == 0)
            pData[i] ^= k;
        else
            pData[i] ^= pData[i - 1];
    }

    tmp = *(__int32*)pData;

    memcpy(pOutputData, pOutputData + sizeof(__int32), tmp);
    nOutputLength = tmp;


    return true;
}




