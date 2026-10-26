#include "stdafx.h"
#include "lua_script.h"
#include "btree_file.h"
#include "utf8.h"
#include "script_mgr.h"

int lua_create_node(lua_State* L)
{
	BT_EDIT_NOD* pNode = NULL;
	BT_EDIT_NOD* pParent = NULL;
	const char* pcszParam[MAX_BT_PARAM] = {0};

	pParent = (BT_EDIT_NOD*)lua_touserdata(L, 1);

	const char* pcszName = lua_tostring(L, 2);
	LOG_PROCESS_ERROR(pcszName);

	pcszParam[0] = lua_tostring(L, 3);
	pcszParam[1] = lua_tostring(L, 4);
	pcszParam[2] = lua_tostring(L, 5);
	pcszParam[3] = lua_tostring(L, 6);

	pNode = new BT_EDIT_NOD;
	LOG_PROCESS_ERROR(pNode);

	strxcpy(pNode->szType, pcszName, MAX_BT_STRING_LEN);

	for (INT32 nIndex = 0; nIndex < MAX_BT_PARAM; nIndex++)
	{
		if (pcszParam[nIndex])
			strxcpy(pNode->szParam[nIndex], pcszParam[nIndex], MAX_BT_STRING_LEN);
		else
			pNode->szParam[nIndex][0] = 0;
	}

	if (pParent)
	{
		pNode->pParent = pParent;
		pParent->Children.push_back(pNode);
	}
	else
	{
		pNode->pParent = NULL;
	}

	lua_pushlightuserdata(L, pNode);

	return 1;
Exit0:
	return 0;
}

void print_tree(BT_EDIT_NOD* pRoot, INT32 nLayer)
{
	char szTab[MAX_PATH] = {0};
	INT32 childIndex = 0;
	BT_EDIT_NOD* nod = NULL;

	LOG_PROCESS_ERROR(pRoot);
	LOG_PROCESS_ERROR(nLayer * 4 < MAX_PATH);

	memset(szTab, ' ', nLayer * 4);

	INF("%s %s(%s,%s,%s,%s)", szTab, pRoot->szType, 
		pRoot->szParam[0], pRoot->szParam[1], pRoot->szParam[2], pRoot->szParam[3]);

	for (std::list<BT_EDIT_NOD*>::iterator it = pRoot->Children.begin();
		it != pRoot->Children.end(); ++it)
	{
		print_tree(*it, nLayer+1);
	}

Exit0:
	return;
}

int lua_print_tree(lua_State* L)
{
	BT_EDIT_NOD* pNode = NULL;

	pNode = (BT_EDIT_NOD*)lua_touserdata(L, 1);
	LOG_PROCESS_ERROR(pNode);

	print_tree(pNode, 0);

Exit0:
	return 0;
}

void destroy_bt(BT_EDIT_NOD* pRoot)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(pRoot);

	for (std::list<BT_EDIT_NOD*>::iterator it = pRoot->Children.begin();
		it != pRoot->Children.end(); ++it)
	{
		destroy_bt(*it);
	}

	SAFE_DELETE(pRoot);

Exit0:
	return;
}

int lua_destroy_tree(lua_State* L)
{
	BT_EDIT_NOD* pNode = NULL;

	pNode = (BT_EDIT_NOD*)lua_touserdata(L, 1);
	LOG_PROCESS_ERROR(pNode);

	destroy_bt(pNode);

Exit0:
	return 0;
}

int lua_add_tree(lua_State* L)
{
	INT32 nRetCode = 0;
	BT_EDIT_NOD* pNode = NULL;
	BT_EDIT_NOD* pRoot = NULL;

	const char* pcszTreeName = lua_tostring(L, 1);
	LOG_PROCESS_ERROR(pcszTreeName);

	pNode = (BT_EDIT_NOD*)lua_touserdata(L, 2);
	LOG_PROCESS_ERROR(pNode);

	pRoot = new BT_EDIT_NOD;
	LOG_PROCESS_ERROR(pRoot);

	strxcpy(pRoot->szType, pcszTreeName, MAX_BT_STRING_LEN);
	memset(pRoot->szParam, 0, sizeof(pRoot->szParam));
	pRoot->pParent = NULL;
	pRoot->Children.push_back(pNode);
	pNode->pParent = pRoot;

	nRetCode = g_BTreeFile.AddTree(pRoot);
	LOG_PROCESS_ERROR(nRetCode);

	return 0;
Exit0:
	SAFE_DELETE(pRoot);

	return 0;
}

int lua_read_tree_file(lua_State* L)
{
	INT32 nRetCode = 0;
	char szFilePath[MAX_PATH];
	FILE* pFile = NULL;
	INT32 nSize = 0;
	char* pData = NULL;

	const char* pcszFileName = lua_tostring(L, 1);
	LOG_PROCESS_ERROR(pcszFileName);

	sprintf(szFilePath, "%s/%s", CScriptMgr::GetInstance().GetRootPath(), pcszFileName);
	pFile = fopen(szFilePath, "rb");
	LOG_PROCESS_ERROR(pFile);

	fseek(pFile, 0, SEEK_END);
	nSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	pData = new char[nSize + 1];
	LOG_PROCESS_ERROR(pData);

	nRetCode = fread(pData, 1, nSize, pFile);
	LOG_PROCESS_ERROR(nRetCode == nSize);
	pData[nSize] = 0;

	fclose(pFile);
	pFile = NULL;

	if ((*(UINT32*)pData & 0x00FFFFFF) == UTF8_BOM)
	{
		lua_pushstring(L, pData + 3);
	}
	else
	{
		lua_pushstring(L, pData);
	}

Exit0:
	if (pFile)
		fclose(pFile);
	SAFE_DELETE_ARRAY(pData);

	return 1;
}

int lua_print_content(lua_State* L)
{
	OutputDebugString(lua_tostring(L, 1));

	return 0;
}

LUA_FUNC g_EditorScriptFuncTable[] =
{
	{"create_bt_edit_node",		lua_create_node}, 
	{"print_tree",				lua_print_tree},
	{"destroy_tree",			lua_destroy_tree},
	{"add_tree",				lua_add_tree},
	{"read_tree_file",			lua_read_tree_file},
	{"print_content",			lua_print_content},

	{0, 0}
};