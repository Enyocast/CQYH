#include "stdafx.h"
#include "trie.h"

TRIE_NODE* trie_create(void)
{
	TRIE_NODE* pRoot = NULL;

	pRoot = new TRIE_NODE;
	LOG_PROCESS_ERROR(pRoot);

	memset(pRoot, 0, sizeof(*pRoot));

	return pRoot;
Exit0:
	if (pRoot)
		trie_destroy(pRoot);
	return NULL;
}

BOOL trie_insert(TRIE_NODE* pRoot, const char* pcszKeywordList)
{
    INT32 nWordCounter = 0;

	LOG_PROCESS_ERROR(pRoot);
    LOG_PROCESS_ERROR(pcszKeywordList);

    while (*pcszKeywordList != 0)
    {
        TRIE_NODE* pNode = pRoot;
        while (*pcszKeywordList != '\n' && *pcszKeywordList != 0)
        {
            unsigned char ucChar = *pcszKeywordList;
            if (pNode->pNextNode[ucChar])
            {
                pNode = pNode->pNextNode[ucChar];
            }
            else
            {
                pNode->pNextNode[ucChar] = new TRIE_NODE;
                LOG_PROCESS_ERROR(pNode->pNextNode[ucChar]);

                pNode = pNode->pNextNode[ucChar];
                memset(pNode, 0, sizeof(*pNode));
            }

            pcszKeywordList++;
        }

        pNode->bKeyword = TRUE;

        if (*pcszKeywordList != 0)
            pcszKeywordList++;

        nWordCounter++;
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL trie_destroy(TRIE_NODE* pRoot)
{
    LOG_PROCESS_ERROR(pRoot);

    for (INT32 nIndex = 0; nIndex < 256; nIndex++)
    {
        if (pRoot->pNextNode[nIndex])
            trie_destroy(pRoot->pNextNode[nIndex]);
    }

    SAFE_DELETE(pRoot);

    return TRUE;
Exit0:

    return FALSE;
}

BOOL trie_search(TRIE_NODE* pRoot, const char* pcszText)
{
    LOG_PROCESS_ERROR(pRoot);
    LOG_PROCESS_ERROR(pcszText);

    while (*pcszText != 0)
    {
        const char* pPointer = pcszText;
        TRIE_NODE* pNode = pRoot;

        while (pNode->pNextNode[(unsigned char)*pPointer] && !pNode->bKeyword)
        {
            pNode = pNode->pNextNode[(unsigned char)*pPointer];
            pPointer++;
        }
        PROCESS_SUCCESS(pNode->bKeyword);

        pcszText++;
    }

    return FALSE;
Exit0:
Exit1:
    return TRUE;
}

BOOL trie_replace(TRIE_NODE* pRoot, char* pszText)
{
	LOG_PROCESS_ERROR(pRoot);
	LOG_PROCESS_ERROR(pszText);

	while (*pszText != 0)
	{
		char* pPointer = pszText;
		char* pMatchPointer = NULL;
		TRIE_NODE* pNode = pRoot;

		while (pNode->pNextNode[(unsigned char)*pPointer])
		{
			pNode = pNode->pNextNode[(unsigned char)*pPointer];
			pPointer++;
			if (pNode->bKeyword)
				pMatchPointer = pPointer;
		}
		if (pMatchPointer)
		{
			while (pszText < pMatchPointer)
			{
				*pszText = '*';
				pszText++;
			}
		}
		else
		{
			pszText++;
		}
	}

	return TRUE;
Exit0:
	return FALSE;
}

void _trie_print_char(unsigned char ch, BOOL bFirst, INT32 nTab)
{
    if (bFirst)
    {
        if (isalnum(ch))
            printf("- %c", ch);
        else
            printf("-%02X", ch);
    }
    else
    {
        printf("\n");
        for (int i = 0; i < nTab; i++)
            printf("   ");
        if (isalnum(ch))
            printf("- %c", ch);
        else
            printf("-%02X", ch);
    }
}

BOOL trie_print(TRIE_NODE* pRoot, INT32 nTab)
{
    BOOL bFirst = TRUE;

    LOG_PROCESS_ERROR(pRoot);

    for (INT32 nIndex = 0; nIndex < 256; nIndex++)
    {
        if (pRoot->pNextNode[nIndex])
        {
            _trie_print_char(nIndex, bFirst, nTab);
            bFirst = FALSE;
            trie_print(pRoot->pNextNode[nIndex], nTab + 1);
        }
    }

    return TRUE;
Exit0:

    return FALSE;
}
