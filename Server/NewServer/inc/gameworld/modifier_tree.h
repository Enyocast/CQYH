#ifndef _MODIFIER_TREE_H_
#define _MODIFIER_TREE_H_

#include "modifier_def.h"
#include "string_def.h"

struct MODIFIER_FILE_NODE;
struct ExtraParam;

#define EXTRA_NODE_COUNT	0x100000
#define MAX_DEPTH			64	

struct ModifierParam
{
	INT32 nXType;
	INT32 nParam;
};

struct ModifierNode
{
	INT32	nType;            // 节点修改函数类型
	INT32	nParentNode;      // 父节点编号
	INT32	nTrueRetNode;     // TRUE返回值后续节点编号
	INT32	nFalseRetNode;    // FALSE返回值后续节点编号
	INT32	nNextNode;        // 必然被执行的后续节点编号
	INT32	nKey;             // 修改函数编号
	ModifierParam Param[MODIFIER_PARAM_COUNT];    // 修改函数参数
};

class CModifierTree
{
public:
	CModifierTree(void);

	static CModifierTree& GetInstance(void);

	BOOL Init(const TCHAR* file, INT32 nExtraNodeCount);

	BOOL UnInit(void);

	BOOL Reload(void);

	INT32 ApplyGlobalNode(INT32 nRootIndex, void* pTarget, ExtraParam* Param);

	INT32 RollBackGlobalNode(INT32 nRootIndex, void* pTarget, ExtraParam* Param);

	INT32 ApplyExtraNode(INT32 nRootIndex, void* pTarget, ExtraParam* Param);

	INT32 RollBackExtraNode(INT32 nRootIndex, void* pTarget, ExtraParam* Param);

	INT32 GetGlobalNodeType(INT32 nIndex);

	ModifierNode* GetGlobalNode(INT32 nNodeID);

	ModifierNode* GetExtraNode(INT32& nNodeID);

	void DelExtraNode(INT32 nNodeID);

	inline INT32 GetDepth(void);

protected:

	INT32 _ApplyNode(ModifierNode* pRootNode, ModifierNode* pNode, void* pTarget, ExtraParam* poParam);

	INT32 _RollBack(ModifierNode* pRootNode, ModifierNode* pNode, void* pTarget, ExtraParam* poParam);

	BOOL _CheckNode(INT32 nRootIndex, INT32 nIndex, INT32 nType);

	BOOL _CheckConditionNode(INT32 nRootIndex, INT32 nIndex, INT32 nType);

private:
	static CModifierTree m_sInstance;

	char m_szFileName[PATH_LEN];

	ModifierNode* m_pData;

	ModifierNode* m_pExtraData;

	INT32 m_nGlobalNodeCount;
	INT32 m_nTotalNodeCount;
	INT32 m_nExtraNodeCount;
	INT32 m_nDepth;

	typedef std::list<INT32> TFreeNodeList;
	TFreeNodeList m_FreeNodeList;

	std::string* m_pstrNameList;
};

inline INT32 CModifierTree::GetDepth(void)
{
	return m_nDepth;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#endif // _modifier_tree_h__

