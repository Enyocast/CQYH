#ifndef _BT_EDIT_NOD_H_
#define _BT_EDIT_NOD_H_

#include "btnod.h"

#define MAX_BT_STRING_LEN	(256)
#define MAX_TREE_COUNT		(256)

struct BT_EDIT_NOD
{
	char					szType[MAX_BT_STRING_LEN];
	char					szParam[MAX_BT_PARAM][MAX_BT_STRING_LEN];
	BT_EDIT_NOD*			pParent;
	std::list<BT_EDIT_NOD*>	Children;
};

BT_EDIT_NOD* CloneNod(BT_EDIT_NOD* nod);
void DestroyNod(BT_EDIT_NOD* nod);

class CLuaScript;

class CBTreeFile
{
public:
	CBTreeFile();
	virtual ~CBTreeFile();

    static const char* GetErrorString();

	BOOL Init(void);
    BOOL UnInit(void);

	BOOL Load(const char* pcszFileName);
	BOOL Save(void);
	BOOL SaveAs(const char* pcszFileName);

	BOOL IsModified(void);
	void SetModified(void);

	BT_EDIT_NOD* NewTree(BT_EDIT_NOD* pNod, int nPos = -1 );
    BT_EDIT_NOD* FindTree(const char* pcszTreeName);
    BOOL IsTreeRoot(BT_EDIT_NOD* pNod);
	BOOL AddTree(BT_EDIT_NOD* pRoot);
	BOOL DelTree(INT32 nTreeIndex);

	INT32 GetTreeCount(void);
	BT_EDIT_NOD* GetRootNode(INT32 nTreeIndex);

	QStringList GetEnumValues(const char* pcszEnum);
	const char* GetFileName(void);
    void SetFileName(const char* pcszFileName);

	INT32 GetNodeIndex(BT_EDIT_NOD* pNode);
	BT_EDIT_NOD* GetNodeByIndex(INT32 nIndex);

    BOOL ParseAction( const char* pcszAction, int paramIndex, char** pcszType );
    BOOL ParseEvent( const char* pcszEvent, char** pcszType, int& nID );

private:
    BOOL _IsEnumAction( const char* pcszAction );
    BOOL _IsEnumParam( const char* pcszType, int nParam, const char* pcszParam );
    void _SaveTree(BT_EDIT_NOD* pNode, INT32 nLayer, char pcszComment[], int nLenComment );

	char			m_szFileName[MAX_PATH];
	BT_EDIT_NOD*	m_pTreeList[MAX_TREE_COUNT];
	INT32			m_nTreeCount;
	BOOL			m_bModified;
	CLuaScript*		m_pLuaScript;
};

extern CBTreeFile g_BTreeFile;

#endif	//_BT_EDIT_NOD_H_