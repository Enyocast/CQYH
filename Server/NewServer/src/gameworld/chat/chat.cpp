#include "stdafx.h"
#include "chat.h"
#include "rsa_sign.h"
#include "error_def.h"

#define  CONVERT_0_TO	95
BOOL Buffer2String(UINT8* pBuffer, INT32 nBufferSize, char* pText, INT32& nTextSize)
{
	INT32 nRetCode = 0;
	INT32 nNumber = 0;
	char  chConvert0 = CONVERT_0_TO;

	LOG_PROCESS_ERROR(pBuffer);
	LOG_PROCESS_ERROR(pText);
	
	nTextSize = 0;
	for (INT32 nIndex = 0; nIndex < nBufferSize; nIndex++)
	{
		switch(pBuffer[nIndex])
		{
		case 0:
			pText[nTextSize++] = chConvert0;
			break;
		case CONVERT_0_TO:
			pText[nTextSize++] = chConvert0;
			pText[nTextSize++] = chConvert0 + 10;
			break;;
		default:
			pText[nTextSize++] = (char)pBuffer[nIndex] + '\0';
			break;
		}
 	}
	
	pText[nTextSize++] = '\0';
	return TRUE;

Exit0:
	return FALSE;
}

BOOL String2Buffer(UCHAR* pBuffer, INT32& nBufferSize, char* pText)
{
	INT32 nRetCode = 0;
	UINT32 dwSize = 0;
	char* pTextPointer = NULL;
    char chConvert0 = CONVERT_0_TO;

    LOG_PROCESS_ERROR(pBuffer);
	LOG_PROCESS_ERROR(pText);

	pTextPointer = pText;
	nBufferSize = 0;
	
	while (*pTextPointer)
	{
		switch(*pTextPointer)
		{
		case CONVERT_0_TO:
			{
				if (*(pTextPointer + 1) == chConvert0 + 10)
				{
					pBuffer[nBufferSize++] = chConvert0;
					pTextPointer = pTextPointer + 2;
				}
				else
				{
					pBuffer[nBufferSize++] = 0;
					pTextPointer++;
				}
			}
			break;
		default:
				pBuffer[nBufferSize++] = *pTextPointer++;
				break;
		}
	}

	return TRUE;

Exit0:
	return FALSE;
}