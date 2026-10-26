#include "stdafx.h"
#include "title.h"

#include "game_world.h"
#include "role.h"
#include "modifier_tree.h"
#include "message_handler.h"


TITLE::TITLE() :
m_nExpireTime(0),
m_nTemplateID(INVALID_TITLE_ID)
{
}

BOOL TITLE::IsExpire()
{
    if (m_nExpireTime && CGameWorld::GetInstance().GetGameTime() > m_nExpireTime)
    {
        return TRUE;    
    }
    return FALSE;
}


BOOL TITLE::OnEquip(CRole* role)
{
    const TITLE_TEMPLATE *pType = GetTitleTemplate(m_nTemplateID);
    LOG_PROCESS_ERROR(pType);

    for (INT32 i=0; i<pType->m_nNodeCount; ++i)
    {
        CModifierTree::GetInstance().ApplyExtraNode(pType->m_nNodeIDs[i], role, NULL);
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL TITLE::OnUnEquip(CRole* role)
{
    const TITLE_TEMPLATE *pType = GetTitleTemplate(m_nTemplateID);
    LOG_PROCESS_ERROR(pType);

    for (INT32 i=0; i < pType->m_nNodeCount; ++i)
    {
        CModifierTree::GetInstance().RollBackExtraNode(pType->m_nNodeIDs[i], role, NULL);
    }

    return TRUE;
Exit0:
    return FALSE;
}


// -------------------------------------------------------------------- 

CTitle::CTitle() :
m_nEquipedTitleID(INVALID_TITLE_ID),
m_pOwner(NULL)
{
    m_Title_Map.clear();
}

CTitle::~CTitle()
{

}

BOOL CTitle::Init(CRole* role)
{
    m_pOwner = role;
    m_nEquipedTitleID = 0;
    m_Title_Map.clear();
    return TRUE;
}

BOOL CTitle::clear()
{
    return TRUE;
}

void CTitle::SetOwner(CRole* role)
{
    m_pOwner = role;
}

BOOL CTitle::IsTitleExist(UINT8 wTitleTemplateID)
{
    TITLE_MAP::iterator iter = m_Title_Map.find(wTitleTemplateID);

	if (iter == m_Title_Map.end())
		return FALSE;

	return TRUE;
}

INT32 CTitle::GetTitleCount()
{
	return m_Title_Map.size();
}

BOOL CTitle::AddTitle(UINT8 titleTemplateID)
{
#ifndef _ROBOT

    TITLE   data;
    TITLE_MAP::iterator iter;
    // todo_tq 性能可优化，map的insert部分 Allan Tao[18:2:2013] 
    const TITLE_TEMPLATE *pType = GetTitleTemplate(titleTemplateID);
    LOG_PROCESS_ERROR(pType);

    data.m_nTemplateID = titleTemplateID;
    if (pType->m_nValidTime == 0)
    {
        data.m_nExpireTime = NA_TITLE_EXPIRE_TIME;
    }
    else if (pType->m_nValidTime > 0)
    {
        data.m_nExpireTime = pType->m_nValidTime + CGameWorld::GetInstance().GetGameTime();
    }

    iter = m_Title_Map.find(titleTemplateID);
    if (iter == m_Title_Map.end())
    {
        m_Title_Map.insert(std::make_pair(titleTemplateID, data));
    }

    CCliMessageHandler::GetInstance().DoAddTitle(m_pOwner, titleTemplateID, pType->m_nValidTime > 0 ? data.m_nExpireTime - CGameWorld::GetInstance().GetGameTime() : NA_TITLE_EXPIRE_TIME);

#endif //_ROBOT

    return TRUE;

Exit0:
    return FALSE;


}

BOOL CTitle::DeleteTitle(UINT8 titleTemplateID, UINT8 nDelType)
{
#ifndef _ROBOT
    TITLE_MAP::iterator iter = m_Title_Map.find(titleTemplateID);
    if (iter != m_Title_Map.end())
    {
        if (m_nEquipedTitleID == titleTemplateID)
        {
            UnEquipTitle();
        }
        m_Title_Map.erase(titleTemplateID);
    }

    CCliMessageHandler::GetInstance().DoDelTitle(m_pOwner, titleTemplateID, nDelType);
#endif //_ROBOT

    return TRUE;

    //Exit0:
    //    return FALSE;
}

INT32 CTitle::EquipTile(UINT8 titleTemplateID)
{

    INT32 nResult = errSuccess;
#ifndef _ROBOT
    TITLE_MAP::iterator iter = m_Title_Map.find(titleTemplateID);
    LOG_PROCESS_ERROR_RET_CODE(iter != m_Title_Map.end(), errTitleNotFind);
    LOG_PROCESS_ERROR_RET_CODE(titleTemplateID != INVALID_TITLE_ID, errTitleNotFind);

    // move into the mainloop
    //if (iter->second.m_nExpireTime <= CGameWorld::GetInstance().GetGameTime())
    //{
    //    DeleteTitle(titleTemplateID);
    //    PROCESS_ERROR(FALSE);
    //}

    LOG_PROCESS_ERROR_RET_CODE(PreCheckEquipTitle(titleTemplateID), errTitleCondNotSatisfy);

    if (INVALID_TITLE_ID != m_nEquipedTitleID)
    {
        TITLE_MAP::iterator tempIter = m_Title_Map.find(m_nEquipedTitleID);
        LOG_CHECK_ERROR(tempIter != m_Title_Map.end());
        if (tempIter != m_Title_Map.end())
        {
            tempIter->second.OnUnEquip(m_pOwner);
        }
    }

    m_nEquipedTitleID = titleTemplateID;
    iter->second.OnEquip(m_pOwner);

    CCliMessageHandler::GetInstance().DoSyncEquipTitle(m_pOwner);

#endif //_ROBOT

    return errSuccess;
Exit0:
    return nResult;
}

BOOL CTitle::UnEquipTitle()
{
    TITLE_MAP::iterator it;

    LOG_PROCESS_ERROR(m_nEquipedTitleID != INVALID_TITLE_ID);

    it = m_Title_Map.find(m_nEquipedTitleID);
    LOG_PROCESS_ERROR(it != m_Title_Map.end());

    it->second.OnUnEquip(m_pOwner);
    m_nEquipedTitleID = INVALID_TITLE_ID;

#ifndef _ROBOT
    CCliMessageHandler::GetInstance().DoSyncEquipTitle(m_pOwner);
#endif //_ROBOT

    return TRUE;
Exit0:
    return FALSE;
}

INT32 CTitle::GetPow()
{
    const TITLE_TEMPLATE *pType  = NULL;
    PROCESS_ERROR(m_nEquipedTitleID != 0);
    pType = GetTitleTemplate(m_nEquipedTitleID);
    LOG_PROCESS_ERROR(pType);

    return pType->nPow;
Exit0:
    return 0;
}

#ifndef _ROBOT

void CTitle::fill(void* pData, UINT8 &nTitleCount)
{
    using namespace std;
	ExternalMessage::TITLE_DATA* pTitleData = (ExternalMessage::TITLE_DATA*)pData;

    nTitleCount = 0;
    for ( TITLE_MAP::iterator iter = m_Title_Map.begin(); iter != m_Title_Map.end(); ++iter, ++nTitleCount)
    {
        LOG_CHECK_ERROR(nTitleCount < MAX_TITLE_LIST_NUM);
        if (nTitleCount == MAX_TITLE_LIST_NUM)
            break;
		pTitleData[nTitleCount].m_nTemplateID = iter->second.m_nTemplateID;
        if (iter->second.m_nExpireTime > 0)
        {
			pTitleData[nTitleCount].m_nExpireTime = iter->second.m_nExpireTime - CGameWorld::GetInstance().GetGameTime();
			if (pTitleData[nTitleCount].m_nExpireTime < 0)
            {
                LOG_CHECK_ERROR(FALSE);
				pTitleData[nTitleCount].m_nExpireTime = 0;
            }
        }
        else
        {
			pTitleData[nTitleCount].m_nExpireTime = NA_TITLE_EXPIRE_TIME;
        }
    }

    return ;
}

BOOL CTitle::PreCheckEquipTitle(UINT8 titleID)
{
    const TITLE_TEMPLATE *pType = GetTitleTemplate(titleID);
    LOG_PROCESS_ERROR(pType);

    if (pType->m_Condition[0].shConType > 0)
    {
        LOG_PROCESS_ERROR(PreCheckEquipTitle_i(pType->m_Condition[0].shConType, pType->m_Condition[0].shConValue));
    }

    if (pType->m_Condition[1].shConType > 0)
    {
        LOG_PROCESS_ERROR(PreCheckEquipTitle_i(pType->m_Condition[1].shConType, pType->m_Condition[1].shConValue));
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CTitle::PreCheckEquipTitle_i(UINT16 nType, UINT16 nValue)
{
    switch (nType)
    {
    case TITLE_NEDD_LEVEL:
        {
            PROCESS_ERROR( nValue < m_pOwner->GetLevel() );
        }
        break;
    case TITLE_SPIRIT_LEVEL:
        break;
    case TITLE_NEED_VIP:
        break;
    case TITLE_NEDD_EVIL_VALUE:
        break;
    default:
        LOG_PROCESS_ERROR(FALSE);
        break;
    }

    return TRUE;
Exit0:
    return FALSE;
}

void CTitle::MainLoop(void)
{
    UINT32       nCurrentTime = CGameWorld::GetInstance().GetGameTime();
    // check expire
    for ( TITLE_MAP::iterator iter = m_Title_Map.begin(); iter != m_Title_Map.end(); )
    {
        if (NA_TITLE_EXPIRE_TIME != iter->second.m_nExpireTime && iter->second.m_nExpireTime <= nCurrentTime)
        {
            if (iter->second.m_nTemplateID == m_nEquipedTitleID)
            {
                m_nEquipedTitleID = INVALID_TITLE_ID;
                iter->second.OnUnEquip(m_pOwner);

#ifndef _ROBOT
                CCliMessageHandler::GetInstance().DoSyncEquipTitle(m_pOwner);
#endif //_ROBOT
            }
            CCliMessageHandler::GetInstance().DoDelTitle(m_pOwner, iter->second.m_nTemplateID, DEL_BY_EXPIRE);
            TITLE_MAP::iterator old_iter = iter;
            ++iter;
            m_Title_Map.erase(old_iter);
        }
        else
            ++iter;
    }
}

TITLE* CTitle::First()
{
    m_TitleMapCursor = m_Title_Map.begin();
    PROCESS_ERROR(m_TitleMapCursor != m_Title_Map.end());

    return &(m_TitleMapCursor->second);
Exit0:
    return NULL;
}

TITLE* CTitle::Next()
{
    ++m_TitleMapCursor;
    PROCESS_ERROR(m_TitleMapCursor != m_Title_Map.end());

    return &(m_TitleMapCursor->second);
Exit0:
    return NULL;
}

#else

void CTitle::OnAddTitle(UINT8 titleTemplateID, UINT32 nExpireTime)
{
    TITLE   data;
    TITLE_MAP::iterator iter;
    const TITLE_TEMPLATE *pType = GetTitleTemplate(titleTemplateID);
    LOG_PROCESS_ERROR(pType);

    data.m_nTemplateID = titleTemplateID;
    data.m_nExpireTime = nExpireTime;

    iter = m_Title_Map.find(titleTemplateID);
    if (iter == m_Title_Map.end())
    {
        m_Title_Map.insert(std::make_pair(titleTemplateID, data));
    }

    return ;

Exit0:
    return;
}

void CTitle::OnDelTitle(UINT8 titleTemplateID, UINT8 nDelType)
{
    TITLE_MAP::iterator iter = m_Title_Map.find(titleTemplateID);
    if (iter != m_Title_Map.end())
    {
        if (m_nEquipedTitleID == titleTemplateID)
        {
            iter->second.OnUnEquip(m_pOwner);
        }
        m_Title_Map.erase(titleTemplateID);
    }
}

void CTitle::OnEquipTitle(UINT8 titleID)
{
    m_nEquipedTitleID = titleID;
}


#endif //_ROBOT










