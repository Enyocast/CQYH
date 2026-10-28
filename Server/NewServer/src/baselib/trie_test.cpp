#include "stdafx.h"
#include "trie.h"
#include "utf8.h"
#include "censored_word_list.h"

static wchar_t s_szKeywordList[] = \
    L"中\n"\
	L"文\n"\
	L"中文\n"\
	L"非常非常非常非常非常长的中文\n"\
	L"a\n"\
	L"b\n"\
	L"c\n"\
	L"ab\n"\
	L"abc\n"\
	L"abcd\n"\
	L"bc\n"\
	L"bcd\n"\
	L"0\n"\
	L"99\n"\
	L"99\n"\
	L"99\n"\
	L"end";

struct TRIE_TEST_CASE
{
	const wchar_t*	pcszText;
    BOOL			bResult;
};

static TRIE_TEST_CASE s_TrieTestCase[] =
{
    {L"a",                              TRUE},
    {L"b",                              TRUE},
    {L"c",                              TRUE},
    {L"ab",                             TRUE},
    {L"abc",                            TRUE},
    {L"abcd",                           TRUE},
    {L"bc",                             TRUE},
    {L"bcd",                            TRUE},
    {L"0",                              TRUE},
    {L"99",                             TRUE},
    {L"中",								TRUE},
    {L"文",								TRUE},
    {L"中文",							TRUE},
    {L"非常非常非常非常非常长的中文",		TRUE},
    {L"end",                            TRUE},

    {L"0a",                             TRUE},
    {L"1b",                             TRUE},
    {L"dc",                             TRUE},
    {L"f2pab",                          TRUE},
    {L"ggabc",                          TRUE},
    {L"ddabcdabcd",                     TRUE},
    {L"bccb",                           TRUE},
    {L"fsdfasdfsdfasdfbcd",             TRUE},
    {L"31230",                          TRUE},
    {L"fdsaf9923",                      TRUE},
    {L"无效字符中无效字符",				TRUE},
    {L"无效23123字a符文无效字sdaf符",		TRUE},
    {L"中文中文中文",						TRUE},
    {L"a非常非常非常非常非常长的中文1",		TRUE},
    {L"2end3a",                         TRUE},

    {L"d",                              FALSE},
    {L"2",                              FALSE},
    {L"Z",                              FALSE},
    {L"d2e",                            FALSE},
    {L"1",                              FALSE},
    {L"929",                            FALSE},
    {L"9",                              FALSE},
    {L"111111",                         FALSE},
    {L"非常非常非常非常非常长的2d",		FALSE},
    {L"e2npd",                          FALSE},

};

struct REPLACE_TEST_CASE
{
	const wchar_t*	pcszText;
	const wchar_t*	pcszResult;
};

static REPLACE_TEST_CASE s_ReplaceTestCase[] =
{
    {L"0a",                             L"**"},
    {L"1b",                             L"1*"},
    {L"dc",                             L"d*"},
    {L"f2pab",                          L"f2p**"},
    {L"ggabc",                          L"gg***"},
    {L"ddabcdabcd",                     L"dd********"},
    {L"bccb",                           L"****"},
    {L"fsdfasdfsdfasdfbcd",             L"fsdf*sdfsdf*sdf***"},
    {L"31230",                          L"3123*"},
    {L"fdsaf9923",                      L"fds*f**23"},
    {L"无效字符中无效字符",				L"无效字符***无效字符"},
    {L"无效23123字a符文无效字sdaf符",		L"无效23123字*符***无效字sd*f符"},
    {L"中文中文中文",						L"******************"},
    {L"a非常非常非常非常非常长的中文1",		L"*******************************************1"},
    {L"2end3a",                         L"2***3*"},
};

BOOL TestTrie(void)
{
    INT32 nRetCode = 0;
    TRIE_NODE* pRoot = NULL;
    char* pPointer = NULL;
	char szKeywordList[1024];

    pRoot = trie_create();
    LOG_PROCESS_ERROR(pRoot);

	utf16_2_utf8(s_szKeywordList, wcslen(s_szKeywordList) + 1, szKeywordList, 1024);

	nRetCode = trie_insert(pRoot, szKeywordList);
	LOG_PROCESS_ERROR(nRetCode);

    for (INT32 nIndex = 0; nIndex < sizeof(s_TrieTestCase) / sizeof(s_TrieTestCase[0]); nIndex++)
    {
		char szText[1024];

		utf16_2_utf8(s_TrieTestCase[nIndex].pcszText, wcslen(s_TrieTestCase[nIndex].pcszText) + 1, szText, 1024);
		
		nRetCode = trie_search(pRoot, szText);
        if (nRetCode != s_TrieTestCase[nIndex].bResult)
        {
            printf("text %d:%s is not passed\n", nIndex, szText);
        }
    }

	for (INT32 nIndex = 0; nIndex < sizeof(s_ReplaceTestCase) / sizeof(s_ReplaceTestCase[0]); nIndex++)
	{
		char szText[1024];
		char szResult[1024];

		utf16_2_utf8(s_ReplaceTestCase[nIndex].pcszText, wcslen(s_ReplaceTestCase[nIndex].pcszText) + 1, szText, 1024);
		utf16_2_utf8(s_ReplaceTestCase[nIndex].pcszResult, wcslen(s_ReplaceTestCase[nIndex].pcszResult) + 1, szResult, 1024);

		nRetCode = trie_replace(pRoot, szText);
		if (!nRetCode || strcmp(szText, szResult) != 0)
		{
			printf("text %d:%s is not passed\n", nIndex, szText);
		}
	}

    nRetCode = trie_destroy(pRoot);
    LOG_PROCESS_ERROR(nRetCode);

    /************************************************************************/

    pRoot = trie_create();
    LOG_PROCESS_ERROR(pRoot);

	nRetCode = trie_insert(pRoot, g_szCensoredWordList);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = trie_insert(pRoot, g_szCensoredWordList);
	LOG_PROCESS_ERROR(nRetCode);

    nRetCode = trie_print(pRoot, 0);
    LOG_PROCESS_ERROR(nRetCode);

    printf("\n");

    static char szTemp[1024 * 1024];
    strcpy(szTemp, g_szCensoredWordList);
    pPointer = szTemp;

    while (*pPointer)
    {
        char* pWord = strtok(pPointer, "\n");
        pPointer += strlen(pWord);

        nRetCode = trie_search(pRoot, pWord);
        if (!nRetCode)
        {
            printf("text %s is not passed\n", pWord);
        }
    }

    nRetCode = trie_destroy(pRoot);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:

    return FALSE;
}
