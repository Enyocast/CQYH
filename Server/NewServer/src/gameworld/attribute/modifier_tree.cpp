#include "stdafx.h"
#include "modifier_tree.h"

#include "ifile.h"

#include "modifier_file_def.h"
#include "attr_modifier.h"
#include "game_world.h"

CModifierTree CModifierTree::m_sInstance;

#ifdef _DEBUG
static const char* szModifierType[] =
{
    "Character Modifier",
    "Bullet Modifier",
    "Missile Modifier",
};
#endif

CModifierTree& CModifierTree::GetInstance(void)
{
    return m_sInstance;
}

CModifierTree::CModifierTree(void)
{
    m_pData = NULL;
    m_pExtraData = NULL;
    m_nGlobalNodeCount = 0;
    m_nExtraNodeCount = 0;
    m_nDepth = 0;
    m_nTotalNodeCount = 0;
    m_pstrNameList = NULL;
}

BOOL CModifierTree::Init(const TCHAR* file, INT32 nExtraNodeCount)
{
    INT32 nRetCode = 0;
    m_nDepth = 0;
    m_pstrNameList = NULL;

    snprintf(m_szFileName, sizeof(m_szFileName), "%s/%s",
        CGameWorld::GetInstance().GetConfigPath(), file);

    m_nExtraNodeCount = nExtraNodeCount;    // 65536

    nRetCode = Reload();
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CModifierTree::Reload(void)
{
    INT32 nRetCode = 0;
    IFile* pFile = NULL;
    MODIFIER_FILE_HEADER Header;
    BOOL bCheckSuccess = TRUE;

    UnInit();

    pFile = g_OpenFile(m_szFileName, "rb");
    LOG_PROCESS_ERROR(pFile);

    nRetCode = pFile->Read(&Header, sizeof(Header));
    LOG_PROCESS_ERROR(nRetCode);

    LOG_PROCESS_ERROR(Header.dwTag == MODIFIER_FILE_TAG);
    LOG_PROCESS_ERROR(Header.dwVersion == MODIFIER_FILE_VERSION);

    m_nGlobalNodeCount = Header.nBlockCount;

    m_pData = (ModifierNode*)calloc(m_nGlobalNodeCount, sizeof(ModifierNode));
    LOG_PROCESS_ERROR(m_pData);

    m_pExtraData = (ModifierNode*)calloc(m_nExtraNodeCount, sizeof(ModifierNode));
    LOG_PROCESS_ERROR(m_pExtraData);

    m_pstrNameList = new std::string[m_nGlobalNodeCount];

    for (INT32 i = 1; i < m_nExtraNodeCount; i++)
        m_FreeNodeList.push_back(i);

    // 下标 i, 就是节点下标
    for (INT32 i = 0; i < m_nGlobalNodeCount && !pFile->Eof(); i++)
    {
        MODIFIER_FILE_NODE_NEW FileNode;

        nRetCode = pFile->Read(&FileNode, sizeof(MODIFIER_FILE_NODE_NEW));
        LOG_PROCESS_ERROR(nRetCode);

        m_pData[i].nKey = FileNode.nKey;
        m_pData[i].nType = FileNode.nType;
        m_pData[i].nNextNode = FileNode.nNextNode;
        m_pData[i].nTrueRetNode = FileNode.nTrueRetNode;
        m_pData[i].nFalseRetNode = FileNode.nFalseRetNode;
        m_pData[i].nParentNode = FileNode.nParentNode;

        m_pstrNameList[i] = FileNode.szObjName;

        // 修改节点数据
        switch (i)
        {
        // 默认
        default:
        {
            for (INT32 j = 0; j < MODIFIER_PARAM_COUNT; j++)
            {
                m_pData[i].Param[j].nXType = FileNode.Param[j].nXType;

                if (FileNode.Param[j].nXType != mxtUseNone)
                    continue;

                if (FileNode.Param[j].szParam[0] != '\0')
                {
                    nRetCode = g_pReadDataScript->CallFunction("read_int_expr", "s:d", FileNode.Param[j].szParam, &(m_pData[i].Param[j].nParam));
                    if (!nRetCode)
                    {
                        CRI("read modifier node error, id: %d, key: %d, param: %s, nodename: %s", i, FileNode.nKey, FileNode.Param[j].szParam, FileNode.szObjName);

                        INT32 nParent = FileNode.nParentNode;
                        while (nParent != 0)
                        {
                            CRI("prev node name: %s", m_pstrNameList[nParent].c_str());
                            nParent = m_pData[nParent].nParentNode;
                        }
                    }
                }
            }
            break;
        }

        // 召唤骷髅/神兽, 最大召唤数量2改1
        case 1134:
        case 1100:
        case 1138:
        case 1128:
        case 1641:
        case 1614:
        case 1626:
        case 1632:
        {
            m_pData[i].Param[0].nXType = FileNode.Param[0].nXType;
            m_pData[i].Param[0].nParam = 1;  // 控制道士召唤物数量

            m_pData[i].Param[1].nXType = FileNode.Param[1].nXType;
            m_pData[i].Param[1].nParam = 1;  // 这个参数没啥用

            m_pData[i].Param[2].nXType = FileNode.Param[2].nXType;
            m_pData[i].Param[2].nParam = 0;
            break;
        }

        // 召唤骷髅-迦兰印, 额外属性类型 7 => 4, 和君王印一样
        case 1152:
        case 1155:
        {
            m_pData[i].Param[0].nXType = FileNode.Param[0].nXType;
            m_pData[i].Param[0].nParam = 3003;  // 技能ID

            m_pData[i].Param[1].nXType = FileNode.Param[1].nXType;
            m_pData[i].Param[1].nParam = 2;  // 额外属性类型

            m_pData[i].Param[2].nXType = FileNode.Param[2].nXType;
            m_pData[i].Param[2].nParam = 0;
            break;
        }

        // 恶灵攻击宠物, 按百分比掉血 (3500 => 1000)
        case 2954:
        {
            m_pData[i].Param[0].nXType = FileNode.Param[0].nXType;
            m_pData[i].Param[0].nParam = 1000;

            m_pData[i].Param[1].nXType = FileNode.Param[1].nXType;
            m_pData[i].Param[1].nParam = 0;

            m_pData[i].Param[2].nXType = FileNode.Param[2].nXType;
            m_pData[i].Param[2].nParam = 67;  // 这个参数没啥用
            break;
        }
        case 2956:
        {
            m_pData[i].Param[0].nXType = FileNode.Param[0].nXType;
            m_pData[i].Param[0].nParam = 1000;

            m_pData[i].Param[1].nXType = FileNode.Param[1].nXType;
            m_pData[i].Param[1].nParam = 0;

            m_pData[i].Param[2].nXType = FileNode.Param[2].nXType;
            m_pData[i].Param[2].nParam = 60;  // 这个参数没啥用
            break;
        }
        case 2957:
        {
            m_pData[i].Param[0].nXType = FileNode.Param[0].nXType;
            m_pData[i].Param[0].nParam = 1000;

            m_pData[i].Param[1].nXType = FileNode.Param[1].nXType;
            m_pData[i].Param[1].nParam = 0;

            m_pData[i].Param[2].nXType = FileNode.Param[2].nXType;
            m_pData[i].Param[2].nParam = 54;  // 这个参数没啥用
            break;
        }
        case 2988:
        {
            m_pData[i].Param[0].nXType = FileNode.Param[0].nXType;
            m_pData[i].Param[0].nParam = 1000;

            m_pData[i].Param[1].nXType = FileNode.Param[1].nXType;
            m_pData[i].Param[1].nParam = 0;

            m_pData[i].Param[2].nXType = FileNode.Param[2].nXType;
            m_pData[i].Param[2].nParam = 64;  // 这个参数没啥用
            break;
        }
        case 2989:
        {
            m_pData[i].Param[0].nXType = FileNode.Param[0].nXType;
            m_pData[i].Param[0].nParam = 1000;

            m_pData[i].Param[1].nXType = FileNode.Param[1].nXType;
            m_pData[i].Param[1].nParam = 0;

            m_pData[i].Param[2].nXType = FileNode.Param[2].nXType;
            m_pData[i].Param[2].nParam = 62;  // 这个参数没啥用
            break;
        }
        case 2992:
        {
            m_pData[i].Param[0].nXType = FileNode.Param[0].nXType;
            m_pData[i].Param[0].nParam = 1000;

            m_pData[i].Param[1].nXType = FileNode.Param[1].nXType;
            m_pData[i].Param[1].nParam = 0;

            m_pData[i].Param[2].nXType = FileNode.Param[2].nXType;
            m_pData[i].Param[2].nParam = 57;  // 这个参数没啥用
            break;
        }
        case 2993:
        {
            m_pData[i].Param[0].nXType = FileNode.Param[0].nXType;
            m_pData[i].Param[0].nParam = 1000;

            m_pData[i].Param[1].nXType = FileNode.Param[1].nXType;
            m_pData[i].Param[1].nParam = 0;

            m_pData[i].Param[2].nXType = FileNode.Param[2].nXType;
            m_pData[i].Param[2].nParam = 55;  // 这个参数没啥用
            break;
        }
        case 2996:
        {
            m_pData[i].Param[0].nXType = FileNode.Param[0].nXType;
            m_pData[i].Param[0].nParam = 1000;

            m_pData[i].Param[1].nXType = FileNode.Param[1].nXType;
            m_pData[i].Param[1].nParam = 0;

            m_pData[i].Param[2].nXType = FileNode.Param[2].nXType;
            m_pData[i].Param[2].nParam = 51;  // 这个参数没啥用
            break;
        }
        case 2997:
        {
            m_pData[i].Param[0].nXType = FileNode.Param[0].nXType;
            m_pData[i].Param[0].nParam = 1000;

            m_pData[i].Param[1].nXType = FileNode.Param[1].nXType;
            m_pData[i].Param[1].nParam = 0;

            m_pData[i].Param[2].nXType = FileNode.Param[2].nXType;
            m_pData[i].Param[2].nParam = 48;  // 这个参数没啥用
            break;
        }
        }


        // 默认代码
        //for(INT32 j = 0; j < MODIFIER_PARAM_COUNT; j++)
        //{
        //	m_pData[i].Param[j].nXType = FileNode.Param[j].nXType;
        //
        //	if(FileNode.Param[j].nXType != mxtUseNone)
        //		continue;
        //
        //	if(FileNode.Param[j].szParam[0] != '\0')
        //	{
        //		nRetCode = g_pReadDataScript->CallFunction("read_int_expr", "s:d", FileNode.Param[j].szParam, &(m_pData[i].Param[j].nParam));
        //		if(!nRetCode)
        //		{
        //			CRI("read modifier node error, id: %d, key: %d, param: %s, nodename: %s", i, FileNode.nKey, FileNode.Param[j].szParam, FileNode.szObjName);
        //
        //			INT32 nParent = FileNode.nParentNode;
        //			while(nParent != 0)
        //			{
        //				CRI("prev node name: %s", m_pstrNameList[nParent].c_str());
        //				nParent = m_pData[nParent].nParentNode;
        //			}
        //		}
        //	}
        //}
    }

    pFile->Close();
    pFile = NULL;

    for (INT32 nCheckingNode = 0; nCheckingNode < m_nGlobalNodeCount; nCheckingNode++)
    {
        m_nDepth = 0;

        nRetCode = _CheckNode(nCheckingNode, nCheckingNode, m_pData[nCheckingNode].nType);
        if (!nRetCode) goto Checking_Error;

        continue;

    Checking_Error:
        WRN("Check node failed, name: %s, type: %d, key: ", m_pstrNameList[nCheckingNode].c_str(), m_pData[nCheckingNode].nType, m_pData[nCheckingNode].nKey);
        bCheckSuccess = FALSE;
    }

    LOG_PROCESS_ERROR(bCheckSuccess);

    return TRUE;
Exit0:

    if (pFile)
        pFile->Close();
    UnInit();
    return FALSE;
}

INT32 CModifierTree::ApplyGlobalNode(INT32 nRootIndex, void* pTarget, ExtraParam* poParam)
{
    INT32 nRetCode = 0;

    //if (nRootIndex != 0)
    //{
    //	WRN("ApplyGlobalNode %d", nRootIndex);
    //    if (nRootIndex == 444)
    //    {
    //        int a = 0;
    //    }
    //}

    if (nRootIndex == 0)
        return mrcTrue;

    LOG_PROCESS_ERROR(nRootIndex > 0 && nRootIndex < m_nGlobalNodeCount);

    nRetCode = _ApplyNode(m_pData, &m_pData[nRootIndex], pTarget, poParam);

    if (m_nDepth >= MAX_DEPTH)
        CRI("global depth warning: %s", m_pstrNameList[nRootIndex].c_str());
    m_nDepth = 0;

    LOG_PROCESS_ERROR(nRetCode >= 0);

    return nRetCode;
Exit0:
    if (nRootIndex > 0 && nRootIndex < m_nGlobalNodeCount)
    {
        CRI("apply global node error, key: %d, type: %d, param1: %d, param2: %d, param3: %d", m_pData[nRootIndex].nKey, m_pData[nRootIndex].nType, m_pData[nRootIndex].Param[0].nParam, m_pData[nRootIndex].Param[1].nParam, m_pData[nRootIndex].Param[2].nParam);
    }
    if (poParam)
        CRI("exparam1: %d, exparam2: %d, exparam3: %d, exparam4: %d", poParam->m_nX[0], poParam->m_nX[1], poParam->m_nX[2], poParam->m_nX[3]);

    return mrcError;
}

INT32 CModifierTree::RollBackGlobalNode(INT32 nRootIndex, void* pTarget, ExtraParam* poParam)
{
    INT32 nRetCode = 0;

    if (nRootIndex == 0)
        return mrcTrue;

    LOG_PROCESS_ERROR(nRootIndex > 0 && nRootIndex < m_nGlobalNodeCount);

    nRetCode = _RollBack(m_pData, &m_pData[nRootIndex], pTarget, poParam);
    LOG_PROCESS_ERROR(nRetCode >= 0);

    return nRetCode;

Exit0:
    if (nRootIndex > 0 && nRootIndex < m_nGlobalNodeCount)
        CRI("rollback global node error, key: %d, type: %d, param1: %d, param2: %d, param3: %d", m_pData[nRootIndex].nKey, m_pData[nRootIndex].nType, m_pData[nRootIndex].Param[0].nParam, m_pData[nRootIndex].Param[1].nParam, m_pData[nRootIndex].Param[2].nParam);
    if (poParam)
        CRI("exparam1: %d, exparam2: %d, exparam3: %d, exparam4: %d", poParam->m_nX[0], poParam->m_nX[1], poParam->m_nX[2], poParam->m_nX[3]);

    return mrcError;
}

BOOL CModifierTree::_CheckNode(INT32 nRootIndex, INT32 nIndex, INT32 nType)
{
    INT32 nRetCode = 0;

    ModifierFunc* pRootFunc = NULL;
    ModifierFunc* pFunc = NULL;

    if (nIndex == 0)
        return TRUE;

    LOG_PROCESS_ERROR(m_pData[nIndex].Param[0].nXType >= mxtUseNone && m_pData[nIndex].Param[0].nXType < mxtTotal);
    LOG_PROCESS_ERROR(m_pData[nIndex].Param[1].nXType >= mxtUseNone && m_pData[nIndex].Param[1].nXType < mxtTotal);
    LOG_PROCESS_ERROR(m_pData[nIndex].Param[2].nXType >= mxtUseNone && m_pData[nIndex].Param[2].nXType < mxtTotal);

    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < m_nGlobalNodeCount);
    LOG_PROCESS_ERROR(m_pData[nIndex].nType == nType);
    LOG_PROCESS_ERROR(m_pData[nIndex].nTrueRetNode != nRootIndex);
    LOG_PROCESS_ERROR(m_pData[nIndex].nFalseRetNode != nRootIndex);
    LOG_PROCESS_ERROR(m_pData[nIndex].nNextNode != nRootIndex);

    // 根函数
    pRootFunc = GetModifierFunction(m_pData[nRootIndex].nType, m_pData[nRootIndex].nKey);
    LOG_PROCESS_ERROR(pRootFunc);

    // 子函数
    pFunc = GetModifierFunction(m_pData[nIndex].nType, m_pData[nIndex].nKey);
    LOG_PROCESS_ERROR(pFunc);

    m_nDepth++;

    // 条件节点
    nRetCode = _CheckConditionNode(nRootIndex, m_pData[nIndex].nTrueRetNode, nType);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = _CheckConditionNode(nRootIndex, m_pData[nIndex].nFalseRetNode, nType);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = _CheckNode(nRootIndex, m_pData[nIndex].nNextNode, nType);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    WRN("\tSub Node Error: %s", m_pstrNameList[nIndex].c_str());
    return FALSE;
}

BOOL CModifierTree::_CheckConditionNode(INT32 nRootIndex, INT32 nIndex, INT32 nType)
{
    INT32 nRetCode = 0;
    ModifierFunc* pFunc = NULL;

    if (nIndex == 0)
        return TRUE;

    LOG_PROCESS_ERROR(m_pData[nIndex].Param[0].nXType >= mxtUseNone && m_pData[nIndex].Param[0].nXType < mxtTotal);
    LOG_PROCESS_ERROR(m_pData[nIndex].Param[1].nXType >= mxtUseNone && m_pData[nIndex].Param[1].nXType < mxtTotal);
    LOG_PROCESS_ERROR(m_pData[nIndex].Param[2].nXType >= mxtUseNone && m_pData[nIndex].Param[2].nXType < mxtTotal);

    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < m_nGlobalNodeCount);
    LOG_PROCESS_ERROR(m_pData[nIndex].nType == nType);
    LOG_PROCESS_ERROR(m_pData[nIndex].nTrueRetNode != nRootIndex);
    LOG_PROCESS_ERROR(m_pData[nIndex].nFalseRetNode != nRootIndex);
    LOG_PROCESS_ERROR(m_pData[nIndex].nNextNode != nRootIndex);

    pFunc = GetModifierFunction(m_pData[nIndex].nType, m_pData[nIndex].nKey);
    LOG_PROCESS_ERROR(pFunc);

    LOG_PROCESS_ERROR(!pFunc->Rollback);

    m_nDepth++;

    nRetCode = _CheckConditionNode(nRootIndex, m_pData[nIndex].nTrueRetNode, nType);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = _CheckConditionNode(nRootIndex, m_pData[nIndex].nFalseRetNode, nType);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = _CheckConditionNode(nRootIndex, m_pData[nIndex].nNextNode, nType);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    WRN("\tSub Node Error: %s", m_pstrNameList[nIndex].c_str());
    return FALSE;
}

INT32 CModifierTree::GetGlobalNodeType(INT32 nIndex)
{
    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < m_nGlobalNodeCount);

    return m_pData[nIndex].nType;

Exit0:
    return -1;
}

ModifierNode* CModifierTree::GetGlobalNode(INT32 nNodeID)
{
    LOG_PROCESS_ERROR(nNodeID >= 0 && nNodeID < m_nGlobalNodeCount);

    return &m_pData[nNodeID];
Exit0:
    return NULL;
}

ModifierNode* CModifierTree::GetExtraNode(INT32& nNodeID)
{
    LOG_PROCESS_ERROR(!m_FreeNodeList.empty());

    nNodeID = m_FreeNodeList.front();

    m_FreeNodeList.pop_front();

    return &m_pExtraData[nNodeID];
Exit0:
    return NULL;
}

void CModifierTree::DelExtraNode(INT32 nNodeID)
{
    LOG_PROCESS_ERROR(nNodeID >= 0 && nNodeID < m_nExtraNodeCount);

    memset(&m_pExtraData[nNodeID], 0, sizeof(ModifierNode));

    m_FreeNodeList.push_front(nNodeID);

Exit0:
    return;
}

BOOL CModifierTree::UnInit(void)
{
    if (m_pData != NULL)
        free(m_pData);

    if (m_pExtraData != NULL)
        free(m_pExtraData);

    m_pData = NULL;
    m_pExtraData = NULL;

    m_FreeNodeList.clear();

    if (m_pstrNameList != NULL)
        delete[] m_pstrNameList;

    m_pstrNameList = NULL;

    return TRUE;
}

INT32 CModifierTree::_ApplyNode(ModifierNode* pRootNode, ModifierNode* pNode, void* pTarget, ExtraParam* poParam)
{
    INT32 nRetCode = 0;
    INT32 nParam[MODIFIER_PARAM_COUNT] = { 0 };

    if (pNode == pRootNode)
        return mrcTrue;

    m_nDepth++;
    LOG_PROCESS_ERROR(m_nDepth <= MAX_DEPTH);

    if (poParam != NULL)
    {
        static INT32 ExParamIndex[mxtTotal] =
        {
            -1, 0, 1, 2, 3
        };

        for (INT32 i = 0; i < MODIFIER_PARAM_COUNT; i++)
        {
            if (pNode->Param[i].nXType == mxtUseNone)
                nParam[i] = pNode->Param[i].nParam;
            else
            {
                nParam[i] = poParam->m_nX[pNode->Param[i].nXType - 1];
                //				SPL("Param %d, Use X%d", i, pNode->Param[i].nXType);
            }
        }
    }
    else
    {
        nParam[0] = pNode->Param[0].nParam;
        nParam[1] = pNode->Param[1].nParam;
        nParam[2] = pNode->Param[2].nParam;
    }

    {
        ModifierFunc* Func = GetModifierFunction(pNode->nType, pNode->nKey);
        LOG_PROCESS_ERROR(Func != NULL);
        LOG_PROCESS_ERROR(Func->ImplFunc != NULL);

        nRetCode = Func->ImplFunc(pTarget, FALSE, nParam[0], nParam[1], nParam[2], poParam);
    }

#ifdef _DEBUG
    SPL("apply key: %d, type: %s, retcode: %d", pNode->nKey, szModifierType[pNode->nType], nRetCode);
#endif

    PROCESS_SUCCESS(nRetCode == mrcTrueAndBreak);

    if (nRetCode == mrcTrue)
    {
        if (pNode->nTrueRetNode != 0)
        {
            //WRN("nTrueRetNode %d", pNode->nTrueRetNode);
            nRetCode = _ApplyNode(pRootNode, &pRootNode[pNode->nTrueRetNode], pTarget, poParam);
            LOG_PROCESS_ERROR(nRetCode >= 0);
        }
    }
    else
    {
        if (pNode->nFalseRetNode != 0)
        {
            //WRN("nFalseRetNode %d", pNode->nFalseRetNode);
            nRetCode = _ApplyNode(pRootNode, &pRootNode[pNode->nFalseRetNode], pTarget, poParam);
            LOG_PROCESS_ERROR(nRetCode >= 0);
        }
    }

    if (pNode->nNextNode != 0)
    {
        //WRN("nNextNode %d", pNode->nNextNode);
        nRetCode = _ApplyNode(pRootNode, &pRootNode[pNode->nNextNode], pTarget, poParam);
        LOG_PROCESS_ERROR(nRetCode >= 0);
    }

Exit1:
    m_nDepth--;
    return nRetCode;
Exit0:
    m_nDepth--;
    return mrcError;
}

INT32 CModifierTree::_RollBack(ModifierNode* pRootNode, ModifierNode* pNode, void* pTarget, ExtraParam* poParam)
{
    INT32 nRetCode = 0;
    INT32 nParam[MODIFIER_PARAM_COUNT] = { 0 };

    if (pNode == pRootNode)
        return TRUE;

    m_nDepth++;
    LOG_PROCESS_ERROR(m_nDepth <= MAX_DEPTH);

#ifdef _DEBUG
    SPL("Rollback Key: %d, Type: %s", pNode->nKey, szModifierType[pNode->nType]);
#endif

    if (poParam != NULL)
    {
        static INT32 ExParamIndex[mxtTotal] =
        {
            -1, 0, 1, 2, 3
        };

        for (INT32 i = 0; i < MODIFIER_PARAM_COUNT; i++)
        {
            if (pNode->Param[i].nXType == mxtUseNone)
                nParam[i] = pNode->Param[i].nParam;
            else
                nParam[i] = poParam->m_nX[pNode->Param[i].nXType - 1];
        }
    }
    else
    {
        nParam[0] = pNode->Param[0].nParam;
        nParam[1] = pNode->Param[1].nParam;
        nParam[2] = pNode->Param[2].nParam;
    }

    {
        ModifierFunc* Func = GetModifierFunction(pNode->nType, pNode->nKey);
        LOG_PROCESS_ERROR(Func != NULL);

        if (Func->Rollback)
        {
            nRetCode = Func->ImplFunc(pTarget, TRUE, -nParam[0], -nParam[1], -nParam[2], poParam);
            LOG_CHECK_ERROR(nRetCode >= 0);
        }

        if (pNode->nNextNode != 0)
        {
            nRetCode = _RollBack(pRootNode, &pRootNode[pNode->nNextNode], pTarget, poParam);
            LOG_CHECK_ERROR(nRetCode >= 0);
        }
    }

    m_nDepth--;
    return nRetCode;
Exit0:
    m_nDepth--;
    return FALSE;
Exit1:
    m_nDepth--;
    return TRUE;
}

INT32 CModifierTree::ApplyExtraNode(INT32 nRootIndex, void* pTarget, ExtraParam* Param)
{
    INT32 nRetCode = 0;

    //if (nRootIndex != 0)
    //{
    //	WRN("ApplyExtraNode %d", nRootIndex);
    //}

    if (nRootIndex == 0)
        return TRUE;

    LOG_PROCESS_ERROR(nRootIndex > 0 && nRootIndex < m_nExtraNodeCount);

    nRetCode = _ApplyNode(m_pExtraData, &m_pExtraData[nRootIndex], pTarget, Param);

    if (m_nDepth >= MAX_DEPTH)
        CRI("extra depth warning: %s", m_pstrNameList[nRootIndex].c_str());
    m_nDepth = 0;

    LOG_PROCESS_ERROR(nRetCode >= 0);

    return nRetCode;
Exit0:
    return mrcError;
}

INT32 CModifierTree::RollBackExtraNode(INT32 nRootIndex, void* pTarget, ExtraParam* Param)
{
    INT32 nRetCode = 0;

    if (nRootIndex == 0)
        return TRUE;

    LOG_PROCESS_ERROR(nRootIndex > 0 && nRootIndex < m_nExtraNodeCount);

    nRetCode = _RollBack(m_pExtraData, &m_pExtraData[nRootIndex], pTarget, Param);
    LOG_PROCESS_ERROR(nRetCode >= 0);

    return nRetCode;
Exit0:
    return mrcError;
}


