#ifndef _TRIE_H_
#define _TRIE_H_

struct TRIE_NODE
{
    BOOL        bKeyword;
    TRIE_NODE*  pNextNode[256];
};

TRIE_NODE* trie_create(void);
BOOL trie_insert(TRIE_NODE* pRoot, const char* pcszKeywordList);
BOOL trie_destroy(TRIE_NODE* pRoot);

BOOL trie_search(TRIE_NODE* pRoot, const char* pcszText);
BOOL trie_replace(TRIE_NODE* pRoot, char* pcszText);
BOOL trie_print(TRIE_NODE* pRoot, INT32 nTab);

#endif  // _TRIE_H_