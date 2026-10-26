#include "stdafx.h"
#include "cooldown.h"
#include "game_world.h"

CCoolDown::CCoolDown(void)
{
    m_bDisabled = FALSE;
}

BOOL CCoolDown::Add(INT32 nKey, INT32 nInterval)
{
	TCoolDownMap::iterator itr = m_CoolDownMap.find(nKey);
	if(itr == m_CoolDownMap.end())
		m_CoolDownMap[nKey] = CGameWorld::GetInstance().GetGameFrame() + nInterval;
	else
		itr->second = CGameWorld::GetInstance().GetGameFrame() + nInterval;

	return TRUE;
}

void CCoolDown::Reset(INT32 nKey)
{
    m_CoolDownMap.erase(nKey);
}

void CCoolDown::ResetAll(void)
{
	m_CoolDownMap.clear();
}

BOOL CCoolDown::CheckReady(INT32 nKey)
{
    TCoolDownMap::iterator itr;

	if (m_bDisabled)
		return TRUE;

	itr = m_CoolDownMap.find(nKey);
	if (itr == m_CoolDownMap.end())
		return TRUE;

	if (itr->second <= CGameWorld::GetInstance().GetGameFrame())
	{
		m_CoolDownMap.erase(itr);
		return TRUE;
	}

	return FALSE;
}

INT32 CCoolDown::GetRemainFrm(INT32 nKey)
{
    TCoolDownMap::iterator itr;

    if (m_bDisabled)
        return 0;

    itr = m_CoolDownMap.find(nKey);
    if (itr == m_CoolDownMap.end())
        return 0;

    if (itr->second <= CGameWorld::GetInstance().GetGameFrame())
    {
        m_CoolDownMap.erase(itr);
        return 0;
    }

	return itr->second - CGameWorld::GetInstance().GetGameFrame();
}

void CCoolDown::Enable(BOOL bEnabled)
{
    m_bDisabled = !bEnabled;
}

BOOL CCoolDown::ChangeRemainFrm(INT32 nKey, INT32 nValue)
{
    TCoolDownMap::iterator itr = m_CoolDownMap.find(nKey);
	PROCESS_ERROR(itr != m_CoolDownMap.end());

	itr->second += nValue;
	return TRUE;
Exit0:
	return FALSE;
}

void CCoolDown::Begin(void)
{
	m_CoolDownItr = m_CoolDownMap.begin();
}

BOOL CCoolDown::Next(INT32& nKey, UINT32& dwTimeupFrm)
{
	if(m_CoolDownItr == m_CoolDownMap.end())
		return FALSE;

	nKey = m_CoolDownItr->first;
	dwTimeupFrm = m_CoolDownItr->second;

	++m_CoolDownItr;

	return TRUE;
}

BOOL CCoolDown::IsDisabled(void)
{
	return m_bDisabled;
}

void CCoolDown::Init(void)
{
	m_bDisabled = FALSE;
	m_CoolDownMap.clear();
}

void CCoolDown::UnInit(void)
{

}
