#include "stdafx.h"
#include "string_ex.h"

size_t strxcpy(char *dst, const char *src, size_t size)
{
    const char *d = dst;

    if (dst == NULL || src == NULL || size == 0)
        return 0;

    while (--size > 0)
    {
        if ((*dst++ = *src++) == 0)
            break;
    }

    if (size == 0)
    {
        *dst++ = 0;
    }

    return dst - d - 1;
}

size_t strxcat(char *dst, const char *src, size_t size)
{
    const char *d = dst;

    if (dst == NULL || src == NULL || size == 0)
        return 0;

    while (size && *dst)
    {
        size--;
        dst++;
    }

    while (--size > 0)
    {
        if ((*dst++ = *src++) == 0)
            break;
    }

    if (size == 0)
    {
        *dst++ = 0;
    }

    return dst - d - 1;
}

char* SplitStr(char*& tszString, char nSep)
{
    INT32 nIdx = 0;
    INT32 nLen = (INT32)strlen(tszString);
    char* pRet = NULL;

    for(INT32 i = 0; i < nLen; i++)
    {
        if(tszString[i] == nSep)
        {
            tszString[i] = 0;
            pRet = tszString;
            tszString = tszString + i + 1;

            return pRet;
        }
    }

    return NULL;
}
