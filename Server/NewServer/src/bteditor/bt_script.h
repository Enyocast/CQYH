#ifndef _BT_EDITOR_SCRIPT_H_
#define _BT_EDITOR_SCRIPT_H_

struct BTNod;

struct BTTree  // loacate in BTNod ?
{
    const char* pEventName;
    BTNod* pTreeRoot;
};

BOOL LoadScriptTrees( QString filename, BTTree pOutBTRootArray[] );

int InitScript(const char* pszScriptPath);

#endif // _BT_EDITOR_SCRIPT_H_
