#include "stdafx.h"
#include "btree_file.h"

#include "bt_config.h"      // save check data
#include "script_mgr.h"
#include "p4.h"

#define BT_EDIT_FILE_NAME	"btedit/main.lua"

CBTreeFile g_BTreeFile;
static char s_szContent[1024 * 1024];
static INT32 s_nPointer = 0;
static char s_szCommont[1024 * 1024];


enum errCode
{
    ecSuccess = 0,
    ecInvalidAction,
    ecInvalidEvent,
    ecEventShouldHas1Node,
    ecTotal,
};

const char* s_ErrorString[ecTotal] = 
{
    "success",
    "Invalid Action name",
    "Invalid Event name",
    "Event should has only one Node",
};

INT32 s_nCurrentErrorCode = 0;

const char* CBTreeFile::GetErrorString()
{
    LOG_PROCESS_ERROR( s_nCurrentErrorCode > 0 && s_nCurrentErrorCode < sizeof(s_ErrorString)/sizeof(s_ErrorString[0]) );
    return s_ErrorString[s_nCurrentErrorCode];
Exit0:
    return NULL;
}

CBTreeFile::CBTreeFile()
{
	m_szFileName[0] = 0;
	memset(m_pTreeList, NULL, sizeof(m_pTreeList));
	m_nTreeCount = 0;
	m_pLuaScript = NULL;
	m_bModified = FALSE;
}

CBTreeFile::~CBTreeFile()
{
	UnInit();
}

BOOL CBTreeFile::Init(void)
{
	INT32 nRetCode = 0;

	m_pLuaScript = CScriptMgr::GetInstance().FindScript(BT_EDIT_FILE_NAME);
	if (m_pLuaScript == NULL)
	{
		m_pLuaScript = CScriptMgr::GetInstance().NewScript(BT_EDIT_FILE_NAME);
		LOG_PROCESS_ERROR(m_pLuaScript);
	}

	m_szFileName[0] = 0;
	memset(m_pTreeList, NULL, sizeof(m_pTreeList));
	m_nTreeCount = 0;
	m_bModified = FALSE;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CBTreeFile::UnInit(void)
{
	INT32 nRetCode = 0;

	for (INT32 nIndex = 0; nIndex < m_nTreeCount; nIndex++)
	{
		nRetCode = DelTree(0);
		LOG_CHECK_ERROR(nRetCode);
	}
	memset(m_pTreeList, NULL, sizeof(m_pTreeList));
	m_bModified = FALSE;
	m_pLuaScript = NULL;

	return TRUE;
}

void CBTreeFile::SetFileName(const char* pcszFileName)
{
    Q_ASSERT(pcszFileName);
    strxcpy(m_szFileName, pcszFileName, MAX_PATH);
}

BOOL CBTreeFile::Load(const char* pcszFileName)
{
	INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(pcszFileName);
    strxcpy(m_szFileName, pcszFileName, MAX_PATH);

	LOG_PROCESS_ERROR(m_pLuaScript);
	nRetCode = m_pLuaScript->CallFunction("load_tree_file", "s", pcszFileName);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CBTreeFile::ParseAction( const char* pcszAction, int paramIndex, char** pcszType )
{
    const ACTION_CONFIG* pConfig = BTConfig::GetInstance().FindActionConfig(pcszAction);
    if (NULL == pConfig)
        return FALSE;

    if (paramIndex >= MAX_BT_PARAM)
        return FALSE;

    if ( ( strcmp(pcszAction, "batSpawnSingleNpc") == 0 && paramIndex == 0 ) ||
              ( strcmp(pcszAction, "batSpawnNpcAtPoint") == 0 && paramIndex == 1 ) )
    {
        *pcszType = "NPCServerInstance";
    }
    else if ( strcmp(pcszAction, "batSpawnMediumGroup") == 0 && paramIndex == 0 )
    {
        *pcszType = "NPCNewSpawnGroupMediumActor";
    }
    else if ( strcmp(pcszAction, "batSpawnLargeGroup") == 0 && paramIndex == 0 )
    {
        *pcszType = "NPCNewSpawnGroupActor";
    }
    else if ( strcmp(pcszAction, "batPatrol") == 0 && paramIndex == 0 )
    {
        *pcszType = "MMOServerPoint";
    }
    else if ( strcmp(pcszAction, "") == 0 && paramIndex == 0 )
    {
        *pcszType = "MMOVolume_Trigger";
    }
    else 
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CBTreeFile::ParseEvent( const char* pcszEvent, char** pcszType, int& nID )
{
    if ( strncmp( pcszEvent, "evt", strlen("evt") ) != 0 )  // check enum string
        return FALSE;

    const EVENT_CONFIG* pConfig = BTConfig::GetInstance().MatchEventConfig(pcszEvent, &nID);
    if (NULL == pConfig)
        return FALSE;

    if ( nID <= 0 )
    {
        return FALSE;
    }

    if ( pConfig->EventName == "evtTouchVolume" )
    {
        *pcszType = "MMOVolume_Trigger";
    }
    else if( pConfig->EventName == "evtSingleNpcDie" )
    {
        *pcszType = "NPCServerInstance";
    }
    else if( pConfig->EventName == "evtMediumGroupDie" )
    {
        *pcszType = "NPCNewSpawnGroupMediumActor";
    }
    else if( pConfig->EventName == "evtLargeGroupDie" )
    {
        *pcszType = "NPCNewSpawnGroupActor";
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CBTreeFile::_IsEnumAction( const char* pcszAction )
{
    if ( strncmp( pcszAction, "bat", strlen("bat") ) != 0 )  // check enum string
        return FALSE;

    const ACTION_CONFIG* pConfig = BTConfig::GetInstance().FindActionConfig(pcszAction);
    if (NULL == pConfig)
        return FALSE;

    return TRUE;
}

BOOL CBTreeFile::_IsEnumParam( const char* pcszType, int nParam, const char* pcszParam )
{
    // is digit
    char* pEndChar = NULL;
    long value = strtol( pcszParam, &pEndChar, 10 );
    if ( NULL == *pEndChar )
        return TRUE;

    // is enum string
    QStringList values;
    const ACTION_CONFIG* pConfig = BTConfig::GetInstance().FindActionConfig(pcszType);
    if (pConfig)
    {
        if (pConfig->Param[nParam].indexOf('#') == 0 )
            values = GetEnumValues(pConfig->Param[nParam].toAscii().data() + 1);
    }
    if ( !values.isEmpty() && values.contains( pcszParam ) )
        return TRUE;

    // no quotation marks around    
    if ((pcszParam[0] == '\"') &&   
        (pcszParam[strlen(pcszParam)-1] == '\"') )
        return TRUE;

    return FALSE;
}
void CBTreeFile::_SaveTree(BT_EDIT_NOD* pNode, INT32 nLayer, char pcszComment[], int nLenComment )
{
    char szNodeText[1024];
    szNodeText[0] = 0;
	INT32 nLen = 0;

    char szTabText[1024] = {};
    for (INT32 nTab = 0; nTab < nLayer; nTab++)
        szTabText[nTab] = '\t';
    szTabText[nLayer] = 0;

    sprintf(szNodeText, "%s{ %s", szTabText, pNode->szType);

    if ( !_IsEnumAction(pNode->szType) )  // check enum string
    {
        snprintf( pcszComment + strlen(pcszComment), nLenComment - strlen(pcszComment), 
                    "-- external table or function:  %s\n", pNode->szType  );
    }

    INT32 nParamCount = MAX_BT_PARAM;
    while (nParamCount > 0 && pNode->szParam[nParamCount - 1][0] == 0 )
        nParamCount--;

    if (nParamCount > 0)
    {
        sprintf(szNodeText, "%s, param = {", szNodeText);

        for (INT32 nParam = 0; nParam < nParamCount - 1; nParam++)
        {
            if(!_IsEnumParam(pNode->szType, nParam, pNode->szParam[nParam]) )
            {
                snprintf( pcszComment + strlen(pcszComment), nLenComment - strlen(pcszComment), 
                    "-- external consistant var:  %s\n", pNode->szParam[nParam]  );
            }

            if (pNode->szParam[nParam][0])
            {
                sprintf(szNodeText, "%s %s,", szNodeText, pNode->szParam[nParam]);
            }
            else
            {
                sprintf(szNodeText, "%s ,", szNodeText);
            }
        }
        sprintf(szNodeText, "%s %s }", szNodeText, pNode->szParam[nParamCount - 1]);
    }
    nLen = strlen(szNodeText);
    memcpy(s_szContent + s_nPointer, szNodeText, nLen);
    s_nPointer += nLen;

    if (pNode->Children.size() > 0)
    {
        sprintf(szNodeText, ",\n");
        nLen = strlen(szNodeText);
        memcpy(s_szContent + s_nPointer, szNodeText, nLen);
        s_nPointer += nLen;

        for (std::list<BT_EDIT_NOD*>::iterator it = pNode->Children.begin();
            it != pNode->Children.end(); ++it)
        {
            _SaveTree(*it, nLayer+1, pcszComment, nLenComment);
        }
    }

    if (pNode->Children.size() > 0)
        sprintf(szNodeText, "%s},\n", szTabText);
    else
        sprintf(szNodeText, " },\n");

    nLen = strlen(szNodeText);
    memcpy(s_szContent + s_nPointer, szNodeText, nLen);
    s_nPointer += nLen;

	return;
}

BOOL CBTreeFile::Save(void)
{
	INT32 nRetCode = 0;
	char szFilePath[MAX_PATH];
	FILE* pFile = NULL;

	LOG_PROCESS_ERROR(m_szFileName[0]);
	PROCESS_SUCCESS(!m_bModified);

	s_nPointer = 0;
    s_szContent[0] = '\0';
    //memset( s_szContent, 0, sizeof(s_szContent) );
    s_szCommont[0] = '\0';
	for (INT32 nIndex = 0; nIndex < m_nTreeCount; nIndex++)
	{
        char szTreeType[128] = {0};
        sprintf(szTreeType, "%s = \n", m_pTreeList[nIndex]->szType );
        sprintf(s_szContent+s_nPointer, "%s", szTreeType);
		s_nPointer += strlen(szTreeType);

        char szThisComment[1024*16] = {0};
        //for(std::list<BT_EDIT_NOD*>::iterator it = m_pTreeList[nIndex]->Children.begin();
        //    it != m_pTreeList[nIndex]->Children.end(); ++it )
        if (m_pTreeList[nIndex]->Children.size() == 1) 
        {
            //BT_EDIT_NOD* pNod = *it;
            BT_EDIT_NOD* pNod = *(m_pTreeList[nIndex]->Children.begin());
			_SaveTree( pNod, 0, szThisComment, sizeof(szThisComment) );
        }
        else
        {
            s_nCurrentErrorCode = ecEventShouldHas1Node;
            return FALSE;    // report error
        }

		s_szContent[s_nPointer - 2] = ';';  // ",\n" -> ";\n"
		//s_szContent[s_nPointer++] = '\n';s_szContent[s_nPointer++] = '\0';

        if ( szThisComment[0] != '\0' )
        {
            sprintf(s_szCommont, "-- tree %s refer external: -- \n%s", m_pTreeList[nIndex]->szType, szThisComment );
        }
	}

	sprintf(szFilePath, "//AgeOfDawn/08.Prog/NewServer/bin/%s/%s", CScriptMgr::GetInstance().GetRootPath(), m_szFileName);
	nRetCode = check_out(szFilePath);
	LOG_PROCESS_ERROR(nRetCode);

	sprintf(szFilePath, "%s/%s", CScriptMgr::GetInstance().GetRootPath(), m_szFileName);
	pFile = fopen(szFilePath, "wb");
	LOG_PROCESS_ERROR(pFile);

    strcat(s_szCommont,"\n" );
    nRetCode = fwrite(s_szCommont, 1, strlen(s_szCommont), pFile);
    LOG_PROCESS_ERROR(nRetCode == strlen(s_szCommont));

	nRetCode = fwrite(s_szContent, 1, s_nPointer, pFile);
	LOG_PROCESS_ERROR(nRetCode == s_nPointer);

	fclose(pFile);
	pFile = NULL;
	m_bModified = FALSE;

Exit1:
	return TRUE;
Exit0:
	if (pFile)
		fclose(pFile);

	return FALSE;
}

BOOL CBTreeFile::SaveAs(const char* pcszFileName)
{

	return FALSE;
}

BOOL CBTreeFile::IsModified(void)
{
	return m_bModified;
}

void CBTreeFile::SetModified(void)
{
	m_bModified = TRUE;
}

BT_EDIT_NOD* CBTreeFile::NewTree(BT_EDIT_NOD* pNod, int nPos )
{
	BT_EDIT_NOD* pResult = NULL;

	LOG_PROCESS_ERROR(m_nTreeCount < MAX_TREE_COUNT);

    if ( NULL == pNod )
    {
        pResult = new BT_EDIT_NOD;
        Q_ASSERT(pResult);

        strxcpy(pResult->szType, "evtInvalid", MAX_BT_STRING_LEN);
        pResult->szParam[0][0] = pResult->szParam[1][0] = pResult->szParam[2][0] = pResult->szParam[3][0] = 0;
        pResult->pParent = NULL;
    }
    else
    {
        pResult = pNod;
    }

    if (nPos >= 0)
    {
        for (int i=m_nTreeCount-1; i>=nPos; --i)
        {
            m_pTreeList[i+1] = m_pTreeList[i];
        }
        m_pTreeList[nPos] = pResult;
        ++m_nTreeCount;
    }
    else
    {
	    m_pTreeList[m_nTreeCount++] = pResult;
    }

	return pResult;
Exit0:
	SAFE_DELETE(pResult);

	return NULL;
}

BOOL CBTreeFile::AddTree(BT_EDIT_NOD* pRoot)
{
	LOG_PROCESS_ERROR(pRoot);
	LOG_PROCESS_ERROR(m_nTreeCount < MAX_TREE_COUNT);

	m_pTreeList[m_nTreeCount++] = pRoot;

	return TRUE;
Exit0:

	return FALSE;
}

BOOL CBTreeFile::IsTreeRoot(BT_EDIT_NOD* pNod)
{
    for (INT32 nIndex = 0; nIndex < m_nTreeCount; nIndex++)
    {
        if( m_pTreeList[nIndex] == pNod )
        {
            return TRUE;
        }
    }
    return FALSE;
}

BT_EDIT_NOD* CBTreeFile::FindTree(const char* pcszTreeName)
{

	return FALSE;
}

void _DelNode(BT_EDIT_NOD* pNode)
{
	LOG_PROCESS_ERROR(pNode);

	for (std::list<BT_EDIT_NOD*>::iterator it = pNode->Children.begin();
		it != pNode->Children.end(); ++it)
	{
		_DelNode(*it);
	}

	SAFE_DELETE(pNode);

Exit0:
	return;
}

BOOL CBTreeFile::DelTree(INT32 nTreeIndex)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(nTreeIndex >= 0 && nTreeIndex < m_nTreeCount);

	_DelNode(m_pTreeList[nTreeIndex]);

	for (INT32 nIndex = nTreeIndex; nIndex < m_nTreeCount - 1; nIndex++)
	{
		m_pTreeList[nIndex] = m_pTreeList[nIndex + 1];
	}
	m_nTreeCount--;

	return TRUE;
Exit0:
	return FALSE;
}

INT32 CBTreeFile::GetTreeCount(void)
{
	return m_nTreeCount;
}

BT_EDIT_NOD* CBTreeFile::GetRootNode(INT32 nTreeIndex)
{
	LOG_PROCESS_ERROR(nTreeIndex >= 0 && nTreeIndex < m_nTreeCount);

	return m_pTreeList[nTreeIndex];
Exit0:
	return NULL;
}

QStringList CBTreeFile::GetEnumValues(const char* pcszEnum)
{
	QStringList Result;
	INT32 nRetCode = 0;
	char szResult[64 * 1024];

	nRetCode = m_pLuaScript->CallFunction("get_enum_values", "s:s", pcszEnum, szResult);
	LOG_PROCESS_ERROR(nRetCode);

	Result = QString(szResult).split(",");

	return Result;
Exit0:
	return QStringList();
}

const char* CBTreeFile::GetFileName(void)
{
    if( '\0' == m_szFileName[0] )
        return NULL;

	return m_szFileName;
}

BOOL _SearchNodeIndex(BT_EDIT_NOD* pNode, BT_EDIT_NOD* pDestNode, INT32& rnIndex)
{
    INT32 nRetCode = 0;

    if (pNode == pDestNode)
        return TRUE;
    rnIndex++;

    for (std::list<BT_EDIT_NOD*>::iterator it = pNode->Children.begin();
        it != pNode->Children.end();++it)
    {
        nRetCode = _SearchNodeIndex(*it, pDestNode, rnIndex);
        if (nRetCode)
            return nRetCode;
    }

    return FALSE;
}

INT32 CBTreeFile::GetNodeIndex(BT_EDIT_NOD* pNode)
{
    INT32 nIndex = 0;
    INT32 nRetCode = 0;

	for (INT32 nTreeIndex = 0; nTreeIndex < m_nTreeCount; nTreeIndex++)
	{
        nRetCode = _SearchNodeIndex(m_pTreeList[nTreeIndex], pNode, nIndex);
        if (nRetCode)
            return nIndex;
	}

    return -1;
}

BT_EDIT_NOD* _SearchNode(BT_EDIT_NOD* pNode, INT32& rnIndex)
{
    if(rnIndex < 0)
        return NULL;
	else if (rnIndex == 0)
		return pNode;
    rnIndex--;

	for (std::list<BT_EDIT_NOD*>::iterator it = pNode->Children.begin();
		it != pNode->Children.end();++it)
	{
		BT_EDIT_NOD* pTempNode = _SearchNode(*it, rnIndex);
		if (pTempNode)
			return pTempNode;
	}
}

BT_EDIT_NOD* CBTreeFile::GetNodeByIndex(INT32 nIndex)
{
	for (INT32 nTreeIndex = 0; nTreeIndex < m_nTreeCount; nTreeIndex++)
	{
		BT_EDIT_NOD* pNode = m_pTreeList[nTreeIndex];

		pNode = _SearchNode(pNode, nIndex);
		if (pNode)
			return pNode;
	}

	return NULL;
}


BT_EDIT_NOD* CloneNod(BT_EDIT_NOD* nod)
{
    BT_EDIT_NOD* pResult = NULL;
    BT_EDIT_NOD* pNod = NULL;
    BT_EDIT_NOD* pChildNod = NULL;
    std::list<BT_EDIT_NOD*>::iterator it;

    PROCESS_ERROR( nod );

    pNod = new BT_EDIT_NOD;
    LOG_PROCESS_ERROR( pNod );

    pNod->pParent = NULL;
    strxcpy(pNod->szType, nod->szType, MAX_BT_STRING_LEN);
    strxcpy(pNod->szParam[0], nod->szParam[0], MAX_BT_STRING_LEN);
    strxcpy(pNod->szParam[1], nod->szParam[1], MAX_BT_STRING_LEN);
    strxcpy(pNod->szParam[2], nod->szParam[2], MAX_BT_STRING_LEN);
    strxcpy(pNod->szParam[3], nod->szParam[3], MAX_BT_STRING_LEN);

    for (it = nod->Children.begin(); it != nod->Children.end(); ++it )
    {
        pChildNod = CloneNod( *it );
        LOG_PROCESS_ERROR( nod );

        pChildNod->pParent = pNod;
        pNod->Children.push_back( pChildNod );
    }

    pResult = pNod;
Exit0:
    return pResult;
}

void DestroyNod(BT_EDIT_NOD* nod)
{
    if ( NULL == nod )
        return ;

    std::list<BT_EDIT_NOD*>::iterator it;
    for ( it = nod->Children.begin(); it != nod->Children.end(); ++it )
    {
        BT_EDIT_NOD* pNod = *it;
        if ( pNod )
        {
            DestroyNod( pNod );

            delete( pNod );
        }
    }
}