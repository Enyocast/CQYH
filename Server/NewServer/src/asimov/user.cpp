#include "stdafx.h"
#include "user.h"

#include "winsock2.h"

#include <QtWidgets/QTreeWidget>
#include "game_world.h"
#include "asimov.h"
#include "net_event_msg.h"
#include "string_ex.h"
#include "script_mgr.h"
#include "server_config.h"

#include "c2t_message.h"
#include "c2g_message.h"
#include "c2m_message.h"

#include "rsa_sign.h"
#include "chat.h"
#include "user_mgr.h"
#include "robot_message_handler.h"
#include "sdo/staticlogin.h"
#include "gs_guild.h"
#include "guild_mgr.h"
#include "external_message_size.h"

using namespace ExternalMessage;

#define CLIKEY_USERNAME "UserName"
#define CLIKEY_PASSWORD "Password"

struct LOGIN_INFO_ITEM
{
	UINT16  usLen;
	char    szItem[0];
};

char CUser::m_szRobotUserType[] = "pt";

CUser::CUser()
{
	m_szUserName[0] = 0;
	//m_szUserType[0] = 0;
	m_szPassword[0] = 0;
	m_szAuthID[0] = 0;
	m_bHasLoginReq = FALSE;
	m_szCoroutineName[0] = 0;
	m_bWaitLoginCallback = FALSE;

	m_eUserState = usInvalid;
	m_poPlayingRole = NULL;
	memset(m_poRoleList, 0, sizeof(m_poRoleList));
	m_pUserWidget = NULL;

	m_bAutoLogin = FALSE;
	m_bDeleted = FALSE;
	m_poSocketSession = NULL;
	m_bConnected = FALSE;
	m_poPacketAllocator = NULL;
	m_poNet = NULL;
	m_nSessionID = 0;
	m_dwTempIndex = 0;
	m_byEncryptCode = 0;

	memset(m_dwRecvMsgList, 0, sizeof(m_dwRecvMsgList));
}

CUser::~CUser()
{
	UnInit();
}

BOOL CUser::Init(INet* poNet, IPacketAllocator* poPacketAllocator, INT32 nUserID, const char* pcszUserName, const char* pcszUserType, const char* pcszPassword, UINT8 byGroupID)
{
	INT32 nRetCode = 0;
	m_bDeleted = FALSE;

	LOG_PROCESS_ERROR(pcszUserName);
	LOG_PROCESS_ERROR(pcszUserType);
	LOG_PROCESS_ERROR(pcszPassword);
	LOG_PROCESS_ERROR(poNet);
	LOG_PROCESS_ERROR(poPacketAllocator);

	LOG_PROCESS_ERROR(!m_bConnected);
	LOG_PROCESS_ERROR(!m_bWaitLoginCallback);
	LOG_PROCESS_ERROR(m_szCoroutineName[0] == 0);

	strncpy(m_szUserName, pcszUserName, COMMON_NAME_LEN);
	//strncpy(m_szUserType, pcszUserType, COMMON_NAME_LEN);
	strncpy(m_szPassword, pcszPassword, COMMON_NAME_LEN);
	m_szAuthID[0] = 0;
	m_bHasLoginReq = FALSE;
	m_szCoroutineName[0] = 0;
	m_byEncryptCode = 0;

	m_nSessionID = nUserID;
	m_poNet = poNet;
	m_poPacketAllocator = poPacketAllocator;
	m_bConnected = FALSE;
	m_dwServerAddress = INADDR_NONE;
	m_wServerPort = 0;
	m_byGroupID = byGroupID;


	memset(m_poRoleList, 0, sizeof(m_poRoleList));

	m_pUserWidget = NULL;
	SetUserState(usUnconnected);
	m_dwTempIndex = 0;
	m_qwLastPingTick = 0LL;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CUser::UnInit(void)
{
	INT32 nRetCode = 0;

	LOG_CHECK_ERROR(m_bConnected == FALSE);
	LOG_CHECK_ERROR(m_poSocketSession == NULL);
	LOG_CHECK_ERROR(m_szCoroutineName[0] == 0);
	LOG_CHECK_ERROR(m_bWaitLoginCallback == FALSE);
	LOG_CHECK_ERROR(m_poPlayingRole == NULL);

	m_szUserName[0] = 0;
	//m_szUserType[0] = 0;
	m_szPassword[0] = 0;
	m_eUserState = usInvalid;
	m_poPlayingRole = NULL;
	m_poSocketSession = NULL;
	m_bConnected = FALSE;
	m_szCoroutineName[0] = 0;
	m_bWaitLoginCallback = FALSE;
	m_poNet = NULL;
	m_poPacketAllocator = NULL;
	memset(m_poRoleList, 0, sizeof(m_poRoleList));

    return TRUE;
}


void CUser::OnConnected()
{
	INT32 nRetCode = 0;
	m_bConnected = TRUE;
	INF("user %s OnConnected", GetUserName());

	T2C_ROBOT_CONNECTED stMsg;
	LuaRecvMsg(t2c_robot_connected, &stMsg, sizeof(T2C_ROBOT_CONNECTED));

	if (m_bAutoLogin)
	{
		nRetCode = Login();
		LOG_PROCESS_ERROR(nRetCode);
		INF("user %s start to Login since m_bAutoLogin", GetUserName());
	}

	m_qwLastPingTick = GetTickCountEx() + 8000;

	ResetRecvData();
	ResetSendData();
	ResetChatData();

	m_qwBeginTick = m_qwLastPingTick;
	m_dwTotalRecvSize = 0;
	m_dwTotalSendSize = 0;

	m_dwMinPing = 0xFFFFFFFF;
	m_dwMaxPing = 0;
	m_qwPingValue = 0;
	m_qwPingCount = 0;

	return;
Exit0:
	return;
}

void CUser::OnBSConnected()
{
	INT32 nRetCode = 0;

	B2C_ROBOT_CONNECTED stMsg;
	LuaRecvMsg(b2c_robot_connected, &stMsg, sizeof(B2C_ROBOT_CONNECTED));

	return;
}

void CUser::OnBSDisConnected()
{
	INT32 nRetCode = 0;
	m_poSocketSession = NULL;

	//LOG_PROCESS_ERROR(m_dwServerAddress != INADDR_NONE && m_wServerPort > 0);
	if (m_dwServerAddress == INADDR_NONE || m_wServerPort <= 0)
	{
		CRI("balance server disconnected, but not get Gate Address and Port");
		LOG_PROCESS_ERROR(FALSE);
	}

	SetUserState(usUnconnected);
	nRetCode = ConnectServer(m_dwServerAddress, m_wServerPort, FALSE, m_bAutoLogin);
	LOG_PROCESS_ERROR(nRetCode);

	return;

Exit0:
	CRI("OnBSDisConnected failed! reset state for user %s", GetUserName());

	m_dwServerAddress = INADDR_NONE;
	m_wServerPort = 0;
	SetUserState(usUnconnected);

	//SetDeleteFlag();
	m_poSocketSession = NULL;
	CUserMgr::GetInstance().DelUser(this);
	
	m_bConnected = FALSE;

	return;
}

void CUser::OnDisconnected()
{
	m_bConnected = FALSE;
	INF("user %s OnDisconnected", GetUserName());

	LOG_CHECK_ERROR(m_poSocketSession);
	m_poSocketSession = NULL;
	//SetDeleteFlag();
	CUserMgr::GetInstance().DelUser(this);

	T2C_ROBOT_DISCONNECTED stMsg;
	LuaRecvMsg(t2c_robot_disconnected, &stMsg, sizeof(T2C_ROBOT_DISCONNECTED));

	if (m_poPlayingRole)
	{
		CRI("user %s role %s:%d session terminated",
			m_szUserName, m_poPlayingRole->GetName(), m_poPlayingRole->GetObjID());
	}
	else
	{
		CRI("user %s session terminated", m_szUserName);
	}

	for (INT32 i = 0; i < sizeof(m_dwRecvMsgList) / sizeof(m_dwRecvMsgList[0]);//1024;
		++i)
	{
		if (m_dwRecvMsgList[i] > 0)
			INF("\tmsg:%d\tcount:%d", i, m_dwRecvMsgList[i]);
	}

	return;
}

BOOL CUser::ConnectServer(const char* pcszIP, UINT16 wPort, BOOL bConnectBS, BOOL bAutoLogin)
{
	INT32 nRetCode = 0;
	UINT32 dwAddr;
	dwAddr = inet_addr(pcszIP);
	LOG_PROCESS_ERROR(dwAddr != INADDR_NONE);

	nRetCode = ConnectServer(dwAddr, wPort, bConnectBS, bAutoLogin);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CUser::ConnectServer(UINT32 dwIP, UINT16 wPort, BOOL bConnectBS, BOOL bAutoLogin)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(m_eUserState == usUnconnected);
	LOG_PROCESS_ERROR(m_poSocketSession == NULL);
	LOG_PROCESS_ERROR(m_poNet);
	LOG_PROCESS_ERROR(m_bConnected == FALSE);
	LOG_PROCESS_ERROR(dwIP != INADDR_NONE);

	m_poSocketSession = m_poNet->Connect(dwIP, wPort);
	LOG_PROCESS_ERROR(m_poSocketSession);
	m_poSocketSession->SetUserData((void*)this);

	if (bConnectBS)
		SetUserState(usConnectingBS);
	else
		SetUserState(usConnectingGT);

	m_bAutoLogin = bAutoLogin;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CUser::IsConnected()
{
	return m_bConnected;
}

BOOL CUser::Login(void)
{
	INT32 nRetCode = 0;
	LOG_PROCESS_ERROR(m_eUserState == usConnectingGT);
	LOG_PROCESS_ERROR(!CheckHasLoginReq());

	if (g_ServerConfig.LS.bOAAuthorizeEnable)
	{
		LOG_PROCESS_ERROR(!CheckPassedAuth());

		INF("user %s start to login OA due to bOAAuthorizeEnable", m_szUserName);

		nRetCode = COAStaticLoginMgr::GetInstance().DoLogin(this);
		LOG_PROCESS_ERROR(nRetCode);
	}
	else
	{
		nRetCode = LoginReq();
		LOG_PROCESS_ERROR(nRetCode);
	}

	return TRUE;
Exit0:

	return FALSE;
}

BOOL CUser::LoginReq()
{
	INT32 nRetCode = 0;
	LOGIN_INFO_ITEM* pItem = NULL;
	C2T_LOGIN_REQ* pMsg = NULL;

	LOG_PROCESS_ERROR(m_poPacketAllocator);
	LOG_PROCESS_ERROR(m_eUserState == usConnectingGT);
	LOG_PROCESS_ERROR(!CheckHasLoginReq());

	pMsg = (C2T_LOGIN_REQ*)m_poPacketAllocator->Alloc(sizeof(C2T_LOGIN_REQ));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2t_login_req;
	//pMsg->wSize = sizeof(C2T_LOGIN_REQ);
	pMsg->byGroup = m_byGroupID;
	//pMsg->nVersion = g_nMessageVersion;
	strxcpy(pMsg->szUserName, m_szUserName, USER_NAME_LEN);
	//strxcpy(pMsg->szUserType, m_szUserType, USER_TYPE_LEN);
	pMsg->wMajorVersion = EXTERNAL_MESSAGE_MAJOR_VERSION;
	LOG_PROCESS_ERROR(sizeof(pMsg->szSessionID) >= sizeof(m_szAuthID));
	memcpy(pMsg->szSessionID, m_szAuthID, sizeof(pMsg->szSessionID));

	INF("user %s get Session ID %s, then start to login", pMsg->szUserName, pMsg->szSessionID);
	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2T_LOGIN_REQ));
	LOG_PROCESS_ERROR(nRetCode);

	m_bHasLoginReq = TRUE;

	return TRUE;
Exit0:
	if (pMsg)
	{
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	}
	return FALSE;
}

BOOL CUser::AttachToCoroutine(const char* pcszCoroutineName)
{
	LOG_PROCESS_ERROR(pcszCoroutineName);

	INF("user %s AttachToCoroutine", GetUserName());
	strxcpy(m_szCoroutineName, pcszCoroutineName, COMMON_NAME_LEN);

	return TRUE;
Exit0:
	return FALSE;
}

void CUser::DetachFromCorouine(void)
{
	INF("user %s DetachFromCorouine", GetUserName());
	m_szCoroutineName[0] = 0;
}

const char* CUser::GetCoroutineName(void)
{
	return m_szCoroutineName;
}

void CUser::BeginWaitLoginCallback(void)
{
	INF("user %s BeginWaitLoginCallback", GetUserName());
	m_bWaitLoginCallback = TRUE;
}

void CUser::EndWaitLoginCallback(void)
{
	INF("user %s EndWaitLoginCallback", GetUserName());
	m_bWaitLoginCallback = FALSE;
}

BOOL CUser::IsWaitLoginCallback(void)
{
	return m_bWaitLoginCallback;
}

BOOL CUser::CheckPassedAuth()
{
	return (m_szAuthID[0] == '\0') ? FALSE : TRUE;
}

BOOL CUser::CheckHasLoginReq()
{
	return m_bHasLoginReq;
}

BOOL CUser::SetAuthID(char* szAuthID, INT32 nAuthLen)
{
	LOG_PROCESS_ERROR(nAuthLen <= sizeof(m_szAuthID));
	memcpy(m_szAuthID, szAuthID, nAuthLen);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CUser::CreateRole(const char* pcszRoleName, INT32 eSex,
	INT32 eFaceType, INT32 eHairType, INT32 eHairColor, INT32 eClass)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2T_CREATE_ROLE);
	C2T_CREATE_ROLE* pMsg = (C2T_CREATE_ROLE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2t_create_role;
	strxcpy(pMsg->szRoleName, pcszRoleName, ROLE_NAME_LEN);
	pMsg->byClass = eClass;
	pMsg->byFaceType = eFaceType;
	pMsg->byHairType = eHairType;
	pMsg->byHairColor = eHairColor;
	pMsg->bySkinColor = 1;
	pMsg->bySex = eSex;
	pMsg->bySkinColor = g_Random(1,MAX_ROLE_SKIN_COLOR);

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	SetUserState(usCreatingRole);
	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::DeleteRole(UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2T_DELETE_ROLE);
	C2T_DELETE_ROLE* pMsg = (C2T_DELETE_ROLE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2t_delete_role;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	SetUserState(usDeletingRole);
	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SelectRole(UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2T_SELECT_ROLE);
	C2T_SELECT_ROLE* pMsg = (C2T_SELECT_ROLE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2t_select_role;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR( nRetCode );

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::Teleport(UINT32 dwTelportID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_TELEPORT);
	C2G_TELEPORT* pMsg = (C2G_TELEPORT*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_teleport;
	pMsg->dwTeleportID = dwTelportID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::LeaveGame(UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_RETURN_SELECT_ROLE);
	C2G_RETURN_SELECT_ROLE* pMsg = (C2G_RETURN_SELECT_ROLE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_return_select_role;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::Logout()
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(m_bConnected);
	LOG_PROCESS_ERROR(m_poSocketSession);

	if (m_poPlayingRole)
	{
		nRetCode = CRobotMessageHandler::GetInstance().DoLogout(m_poPlayingRole);
		LOG_PROCESS_ERROR(nRetCode);
	}
	else
	{
		nRetCode = m_poSocketSession->Close();
		LOG_PROCESS_ERROR(nRetCode);
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CUser::LogoutCancel()
{
	INT32 nRetCode = 0;

	nRetCode = CRobotMessageHandler::GetInstance().DoLogoutCancel(m_poPlayingRole);
	LOG_CHECK_ERROR(nRetCode);

Exit1:
	return TRUE;
}

BOOL CUser::AddRole(CRole* poRole)
{
	INT nIndex = 0;

	for (; nIndex < MAX_ROLE_PER_USER; nIndex++)
	{
		if (m_poRoleList[nIndex] == NULL)
		{
			m_poRoleList[nIndex] = poRole;
			break;
		}
	}

	LOG_PROCESS_ERROR(nIndex < MAX_ROLE_PER_USER);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CUser::RemoveRole(UINT32 dwRoleID)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(dwRoleID != 0);
	LOG_PROCESS_ERROR(m_eUserState == usDeletingRole);

	for (INT32 nIndex = 0; nIndex < MAX_ROLE_PER_USER; nIndex++)
	{
		if (m_poRoleList[nIndex] == NULL)
			continue;

		if (m_poRoleList[nIndex]->GetObjID() != dwRoleID)
			continue;

		nRetCode = m_poRoleList[nIndex]->UnInit();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = CGameWorld::GetInstance().DelRole(m_poRoleList[nIndex]);
		LOG_CHECK_ERROR(nRetCode);

		m_poRoleList[nIndex] = NULL;
	}

	return TRUE;
Exit0:

	return FALSE;
}

BOOL CUser::MoveTo(INT32 nDestX, INT32 nDestY)
{
	return m_poPlayingRole->MoveTo(nDestX, nDestY);
}

BOOL CUser::LearnSpell(INT32 nSpellID, INT32 nSpellLevel)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_LEARN_SPELL);
	C2G_LEARN_SPELL* pMsg = (C2G_LEARN_SPELL*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_learn_spell;
	pMsg->wSpellID = nSpellID;
	pMsg->bySpellLevel = nSpellLevel;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}
//
//BOOL CUser::CastSpell(INT32 nSlotID, UINT32 dwTargetID, INT32 nX, INT32 nY, INT32 nZ)
//{
//	INT32 nRetCode = 0;
//	INT32 nSize = sizeof(C2G_ROLE_CAST_SPELL);
//	C2G_ROLE_CAST_SPELL* pMsg = (C2G_ROLE_CAST_SPELL*)m_poPacketAllocator->Alloc(nSize);
//	LOG_PROCESS_ERROR(pMsg);
//
//	pMsg->wMsg = c2g_role_cast_spell;
//	pMsg->bySpellSlot = nSlotID;
//	pMsg->dwTargetID = dwTargetID;
//	pMsg->wTargetX = ConvertCoordS2N(nX);
//	pMsg->wTargetY = ConvertCoordS2N(nY);
//	pMsg->wTargetZ = ConvertCoordS2N(nZ);
//
//	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
//	LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//	return FALSE;
//}

BOOL CUser::CastSpell(INT32 nSlotID, UINT32 dwTargetID, INT32 nX, INT32 nY, INT32 nZ)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_CAST_SPELL_EX);
	CRole* pRole = NULL;

	C2G_CAST_SPELL_EX* pMsg = (C2G_CAST_SPELL_EX*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pRole = GetPlayingRole();
	LOG_PROCESS_ERROR(pRole);
	
	CSpellSlot* pSpellSlot = pRole->GetSpellSlot(nSlotID);
	LOG_PROCESS_ERROR(pSpellSlot);

	pMsg->wMsg = c2g_cast_spell_ex;
	pMsg->wSpellID = pSpellSlot->GetMainSpellID();
	pMsg->bySerial = 1;
	pMsg->byRotateToTarget = TRUE;
	pMsg->dwTargetID = dwTargetID;
	pMsg->wTargetX = ConvertCoordS2N(nX);
	pMsg->wTargetY = ConvertCoordS2N(nY);
	pMsg->wTargetZ = ConvertCoordS2N(nZ);

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::CastSwitchSpell(INT32 nSwitchSlotID, UINT32 dwTargetID, INT32 nX, INT32 nY, INT32 nZ)
{
	INT32 nRetCode = 0;
	CRole* pRole = NULL;

	INT32 nSize = sizeof(C2G_CAST_SWITCH_SPELL);
	C2G_CAST_SWITCH_SPELL* pMsg = (C2G_CAST_SWITCH_SPELL*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pRole = GetPlayingRole();
	LOG_PROCESS_ERROR(pRole);

	CSpellSlot* pSwitchSpellSlot = pRole->GetSpellSlot(nSwitchSlotID);
	LOG_PROCESS_ERROR(pSwitchSpellSlot);

	pMsg->wMsg = c2g_cast_switch_spell;
	pMsg->wSpellID = pSwitchSpellSlot->GetMainSpellID();

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	{
		INT32 nSize = sizeof(C2G_CAST_SPELL_EX);
		C2G_CAST_SPELL_EX* pMsg = (C2G_CAST_SPELL_EX*)m_poPacketAllocator->Alloc(nSize);
		LOG_PROCESS_ERROR(pMsg);

		pRole = GetPlayingRole();
		LOG_PROCESS_ERROR(pRole);

		CSpellSlot* pSpellSlot = pRole->GetSpellSlot(qssNormalAtk);
		LOG_PROCESS_ERROR(pSpellSlot);

		pMsg->wMsg = c2g_cast_spell_ex;
		pMsg->wSpellID = pSpellSlot->GetMainSpellID();
		pMsg->bySerial = 1;
		pMsg->byRotateToTarget = TRUE;
		pMsg->dwTargetID = dwTargetID;
		pMsg->wTargetX = ConvertCoordS2N(nX);
		pMsg->wTargetY = ConvertCoordS2N(nY);
		pMsg->wTargetZ = ConvertCoordS2N(nZ);

		nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
		LOG_PROCESS_ERROR(nRetCode);
	}

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::DirectlyCastSpell(UINT16 wSpellID, INT32 nSpellLevel, UINT32 dwTargetID, INT32 nX, INT32 nY, INT32 nZ)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_DIRECTLY_CAST_SPELL);

	C2G_DIRECTLY_CAST_SPELL* pMsg = (C2G_DIRECTLY_CAST_SPELL*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_directly_cast_spell;
	pMsg->dwSpellID = wSpellID;
	pMsg->bySpellLevel = nSpellLevel;
	pMsg->dwTargetID = dwTargetID;
	pMsg->wTargetX = ConvertCoordS2N(nX);
	pMsg->wTargetY = ConvertCoordS2N(nY);
	pMsg->wTargetZ = ConvertCoordS2N(nZ);

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::GMCommand(const char* pcszGmcmd)
{
	INT32 nRetCode = 0;
	INT32 nStringLen = strnlen(pcszGmcmd, MAX_GM_COMMAND_LEN) + 1;
	INT32 nSize = sizeof(C2M_GM_COMMAND) + nStringLen;
	C2M_GM_COMMAND* pMsg = NULL;

	LOG_PROCESS_ERROR(m_poPacketAllocator);
	pMsg = (C2M_GM_COMMAND*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_gm_command;
	pMsg->wSize = nSize;
	memset(pMsg->szRoleName, 0, sizeof(pMsg->szRoleName));
	strxcpy(pMsg->szGMCommand, pcszGmcmd, nStringLen);

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::AwardUseNumber(char* pAwardNumber)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2M_AWARD_USE_NUMBER);
	C2M_AWARD_USE_NUMBER* pMsg = NULL;

	LOG_PROCESS_ERROR(m_poPacketAllocator);
	LOG_PROCESS_ERROR(pAwardNumber);

	pMsg = (C2M_AWARD_USE_NUMBER*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_award_use_number;
	strxcpy(pMsg->chAwardNumber, pAwardNumber, 32);

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::InteractNpc(UINT32 dwNpcID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_INTERACT_WITH_NPC);
	C2G_INTERACT_WITH_NPC* pMsg = (C2G_INTERACT_WITH_NPC*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_interact_with_npc;
	pMsg->dwNpcID = dwNpcID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}


BOOL CUser::MoveItem(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_MOVE_ITEM);
	C2G_MOVE_ITEM* pMsg = (C2G_MOVE_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_move_item;
	pMsg->bySrcConSlot = srcconslot;
	pMsg->bySrcItemSlot = srcitemslot;
	pMsg->byDstConSlot = dstconslot;
	pMsg->byDstItemSlot = dstitemslot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SplitItem(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot, INT16 itemcount)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SPLIT_ITEM);
	C2G_SPLIT_ITEM* pMsg = (C2G_SPLIT_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_split_item;
	pMsg->bySrcConSlot = srcconslot;
	pMsg->bySrcItemSlot = srcitemslot;
	pMsg->byDstConSlot = dstconslot;
	pMsg->byDstItemSlot = dstitemslot;
	pMsg->shItemCount = itemcount;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::DeleteItem(UINT8 conslot, UINT8 itemslot, INT16 itemcount)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_DELETE_ITEM);
	C2G_DELETE_ITEM* pMsg = (C2G_DELETE_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_delete_item;
	pMsg->byConSlot = conslot;
	pMsg->byItemSlot = itemslot;
	pMsg->shItemCount = itemcount;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::PickUpItem(UINT32 dwDropID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_PICKUP_ITEM);
	C2G_PICKUP_ITEM* pMsg = (C2G_PICKUP_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_pickup_item;
	pMsg->dwDropID = dwDropID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::BuyItem(INT32 nShopID, INT32 nShopItemIndex, INT32 nItemCount)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_BUY_ITEM);
	C2G_BUY_ITEM* pMsg = (C2G_BUY_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_buy_item;
	pMsg->nShopID = nShopID;
	pMsg->nShopItemIndex = nShopItemIndex;
	pMsg->shItemCount = nItemCount;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SellItem(UINT8 conslot, UINT8 itemslot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SELL_ITEM);
	C2G_SELL_ITEM* pMsg = (C2G_SELL_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_sell_item;
	pMsg->byConSlot = conslot;
	pMsg->byItemSlot = itemslot;
	pMsg->shItemCount = 1;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}


BOOL CUser::UseItem(UINT8 conslot, UINT8 itemslot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_USE_ITEM);
	C2G_USE_ITEM* pMsg = (C2G_USE_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_use_item;
	pMsg->byConSlot = conslot;
	pMsg->byItemSlot = itemslot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}


BOOL CUser::ViewSoldItem(void)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_VIEW_SOLD_ITEMS);
	C2G_VIEW_SOLD_ITEMS* pMsg = (C2G_VIEW_SOLD_ITEMS*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_view_sold_items;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::BuyBackItem(UINT8 slot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_BUY_BACK_ITEM);
	C2G_BUY_BACK_ITEM* pMsg = (C2G_BUY_BACK_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_buy_back_item;
	pMsg->bySlot = slot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::RepairItem(UINT8 conslot, UINT8 itemslot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_REPAIR_ITEM);
	C2G_REPAIR_ITEM* pMsg = (C2G_REPAIR_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_repair_item;
	pMsg->byConSlot = conslot;
	pMsg->byItemSlot = itemslot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::RepairAllEquippedItem(void)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_REPAIR_ALL_EQUIPPED_ITEM);
	C2G_REPAIR_ALL_EQUIPPED_ITEM* pMsg = (C2G_REPAIR_ALL_EQUIPPED_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_repair_all_equipped_item;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::Refine(UINT8 byRefineSlot, BOOL bAddEquip, UINT8 byConSlot, UINT8 byItemSlot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_REFINE);
	C2G_REFINE* pMsg = (C2G_REFINE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_refine;
	pMsg->byAddEquip = bAddEquip;
	pMsg->byConSlot = byConSlot;
	pMsg->byItemSlot = byItemSlot;
	pMsg->byRefineSlot = byRefineSlot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::BuyContainerSlot(UINT8 byConSlot, UINT8 byCount)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_BUY_CONTAINER_SLOT);
	C2G_BUY_CONTAINER_SLOT* pMsg = (C2G_BUY_CONTAINER_SLOT*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_buy_container_slot;
	pMsg->byConSlot = byConSlot;
	pMsg->byCount = byCount;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::OrganizeBag(UINT8 byConSlot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_ORGANIZE_BAG);
	C2G_ORGANIZE_BAG* pMsg = (C2G_ORGANIZE_BAG*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_organize_bag;
	pMsg->byConSlot = byConSlot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::IdentifyItem(UINT8 byConSlot, UINT8 byItemSlot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_IDENTIFY_ITEM);
	C2G_IDENTIFY_ITEM* pMsg = (C2G_IDENTIFY_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_identify_item;
	pMsg->byConSlot = byConSlot;
	pMsg->byItemSlot = byItemSlot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::RandomizeItem(UINT8 byConSlot, UINT8 byItemSlot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_RANDOMIZE_ITEM);
	C2G_RANDOMIZE_ITEM* pMsg = (C2G_RANDOMIZE_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_randomize_item;
	pMsg->byConSlot = byConSlot;
	pMsg->byItemSlot = byItemSlot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ConfirmRandomizeItem(void)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_CONFIRM_RANDOMIZE_ITEM);
	C2G_CONFIRM_RANDOMIZE_ITEM* pMsg = (C2G_CONFIRM_RANDOMIZE_ITEM*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_confirm_randomize_item;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::UseMoneyType01Only(BOOL bValue)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_USE_MONEYTYPE01_ONLY);
	C2G_USE_MONEYTYPE01_ONLY* pMsg = (C2G_USE_MONEYTYPE01_ONLY*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_use_moneytype01_only;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::CheckNpcShopData(UINT32 dwCrc)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_CHECK_NPC_SHOP_DATA);
	C2G_CHECK_NPC_SHOP_DATA* pMsg = (C2G_CHECK_NPC_SHOP_DATA*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_check_npc_shop_data;
	pMsg->dwCrc = dwCrc;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::UpgradeSoul(UINT8 byTargetConSlot, UINT8 byTargetItemSlot, UINT8 bySrcCount, UINT8* bySrcConSlot, UINT8* bySrcItemSlot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_UPGRADE_SOUL);
	C2G_UPGRADE_SOUL* pMsg = (C2G_UPGRADE_SOUL*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_upgrade_soul;
	pMsg->byTargetConSlot = byTargetConSlot;
	pMsg->byTargetItemSlot = byTargetItemSlot;

	LOG_PROCESS_ERROR(bySrcCount <= 5);

	pMsg->bySrcCount = bySrcCount;

	for (INT32 i = 0; i < bySrcCount; i++)
	{
		pMsg->bySrcConSlot[i] = bySrcConSlot[i];
		pMsg->bySrcItemSlot[i] = bySrcItemSlot[i];
	}

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::AddSoul(UINT8 byEquipConSlot, UINT8 byEquipItemSlot, UINT8 bySocketIndex, UINT8 bySoulConSlot, UINT8 bySoulItemSlot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_ADD_SOUL);
	C2G_ADD_SOUL* pMsg = (C2G_ADD_SOUL*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_add_soul;
	pMsg->byEquipConSlot = byEquipConSlot;
	pMsg->byEquipItemSlot = byEquipItemSlot;
	pMsg->bySocketIndex = bySocketIndex;
	pMsg->bySoulConSlot = bySoulConSlot;
	pMsg->bySoulItemSlot = bySoulItemSlot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::RemoveSoul(UINT8 byConSlot, UINT8 byItemSlot, UINT8 bySocketIndex)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_REMOVE_SOUL);
	C2G_REMOVE_SOUL* pMsg = (C2G_REMOVE_SOUL*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_remove_soul;
	pMsg->byConSlot = byConSlot;
	pMsg->byItemSlot = byItemSlot;
	pMsg->bySocketIndex = bySocketIndex;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::OpenStall()
{
	INT32 nRetCode = 0;
	C2G_OPEN_STALL* pMsg = (C2G_OPEN_STALL*)m_poPacketAllocator->Alloc(sizeof(C2G_OPEN_STALL));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_open_stall;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_OPEN_STALL));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::CloseStall()
{
	INT32 nRetCode = 0;
	C2G_CLOSE_STALL* pMsg = (C2G_CLOSE_STALL*)m_poPacketAllocator->Alloc(sizeof(C2G_CLOSE_STALL));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_close_stall;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_CLOSE_STALL));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::RealOpenStall()
{
	INT32 nRetCode = 0;
	C2G_REAL_OPEN_STALL* pMsg = (C2G_REAL_OPEN_STALL*)m_poPacketAllocator->Alloc(sizeof(C2G_REAL_OPEN_STALL));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_real_open_stall;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_REAL_OPEN_STALL));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::RealCloseStall()
{
	INT32 nRetCode = 0;
	C2G_REAL_CLOSE_STALL* pMsg = (C2G_REAL_CLOSE_STALL*)m_poPacketAllocator->Alloc(sizeof(C2G_REAL_CLOSE_STALL));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_real_close_stall;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_REAL_CLOSE_STALL));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::AddStallItem(UINT8 stallslot, UINT8 conslot, UINT8 itemslot, INT16 itemcount, INT32 price)
{
	INT32 nRetCode = 0;
	C2G_ADD_STALL_ITEM* pMsg = (C2G_ADD_STALL_ITEM*)m_poPacketAllocator->Alloc(sizeof(C2G_ADD_STALL_ITEM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_add_stall_item;
	pMsg->btStallSlot = stallslot;
	pMsg->byConSlot = conslot;
	pMsg->byItemSlot = itemslot;
	pMsg->shItemCount = itemcount;
	pMsg->nPrice = price;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_ADD_STALL_ITEM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ViewStallItem(UINT32 roleid)
{
	INT32 nRetCode = 0;
	C2G_VIEW_STALL_ITEM* pMsg = (C2G_VIEW_STALL_ITEM*)m_poPacketAllocator->Alloc(sizeof(C2G_VIEW_STALL_ITEM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_view_stall_item;
	pMsg->dwRoleID = roleid;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_VIEW_STALL_ITEM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::BuyStallItem(UINT32 roleid, UINT8 stallslot, INT16 itemcount, UINT32 modifytime)
{
	INT32 nRetCode = 0;
	C2G_BUY_STALL_ITEM* pMsg = (C2G_BUY_STALL_ITEM*)m_poPacketAllocator->Alloc(sizeof(C2G_BUY_STALL_ITEM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_buy_stall_item;
	pMsg->dwRoleID = roleid;
	pMsg->btStallSlot = stallslot;
	pMsg->shItemCount = itemcount;
	pMsg->llModfiyFrame = modifytime;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_BUY_STALL_ITEM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ChangeStallName(const char* stallname)
{
	INT32 nRetCode = 0;
	C2G_CHANGE_STALL_NAME* pMsg = (C2G_CHANGE_STALL_NAME*)m_poPacketAllocator->Alloc(sizeof(C2G_CHANGE_STALL_NAME));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_change_stall_name;
	strxcpy(pMsg->szStallName, stallname, STALL_NAME_LEN);

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_CHANGE_STALL_NAME));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::RemoveStallItem(UINT8 slot)
{
	INT32 nRetCode = 0;
	C2G_REMOVE_STALL_ITEM* pMsg = (C2G_REMOVE_STALL_ITEM*)m_poPacketAllocator->Alloc(sizeof(C2G_REMOVE_STALL_ITEM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_remove_stall_item;
	pMsg->btStallSlot = slot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_REMOVE_STALL_ITEM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::UpgradeStall(UINT8 upgradetype)
{
	INT32 nRetCode = 0;
	C2G_UPGRADE_STALL* pMsg = (C2G_UPGRADE_STALL*)m_poPacketAllocator->Alloc(sizeof(C2G_UPGRADE_STALL));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_upgrade_stall;
	pMsg->btUpgradeCostType = upgradetype;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_UPGRADE_STALL));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::AddFriend(UINT32 friendid, const char* friendname)
{
	INT32 nRetCode = 0;
	C2M_FRIEND_ADD* pMsg = (C2M_FRIEND_ADD*)m_poPacketAllocator->Alloc(sizeof(C2M_FRIEND_ADD));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_friend_add;
	pMsg->dwRoleID = friendid;
	strxcpy(pMsg->szRoleName, friendname, ROLE_NAME_LEN);

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_FRIEND_ADD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::DelFriend(UINT32 friendid)
{
	INT32 nRetCode = 0;
	C2M_FRIEND_DEL* pMsg = (C2M_FRIEND_DEL*)m_poPacketAllocator->Alloc(sizeof(C2M_FRIEND_DEL));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_friend_del;
	pMsg->dwRoleID = friendid;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_FRIEND_DEL));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ChangeFriendGroup(UINT32 friendid, UINT8 groupid)
{
	INT32 nRetCode = 0;
	C2M_FRIEND_CHANGE_GROUP* pMsg = (C2M_FRIEND_CHANGE_GROUP*)m_poPacketAllocator->Alloc(sizeof(C2M_FRIEND_CHANGE_GROUP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_friend_change_group;
	pMsg->dwRoleID = friendid;
	pMsg->byGroupID = groupid;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_FRIEND_CHANGE_GROUP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::AskTrade(UINT32 roleid)
{
	INT32 nRetCode = 0;
	C2G_TRADE_ASK* pMsg = (C2G_TRADE_ASK*)m_poPacketAllocator->Alloc(sizeof(C2G_TRADE_ASK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_ask;
	pMsg->dwRoleID = roleid;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_ASK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::AcceptTrade(UINT32 roleid)
{
	INT32 nRetCode = 0;
	C2G_TRADE_ACCEPT* pMsg = (C2G_TRADE_ACCEPT*)m_poPacketAllocator->Alloc(sizeof(C2G_TRADE_ACCEPT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_accept;
	pMsg->dwRoleID = roleid;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_ACCEPT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::CancelTrade()
{
	INT32 nRetCode = 0;
	C2G_TRADE_CANCEL* pMsg = (C2G_TRADE_CANCEL*)m_poPacketAllocator->Alloc(sizeof(C2G_TRADE_CANCEL));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_cancel;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_CANCEL));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::LockTrade()
{
	INT32 nRetCode = 0;
	C2G_TRADE_LOCK* pMsg = (C2G_TRADE_LOCK*)m_poPacketAllocator->Alloc(sizeof(C2G_TRADE_LOCK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_lock;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_LOCK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ConfirmTrade()
{
	INT32 nRetCode = 0;
	C2G_TRADE_CONFIRM* pMsg = (C2G_TRADE_CONFIRM*)m_poPacketAllocator->Alloc(sizeof(C2G_TRADE_CONFIRM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_confirm;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_CONFIRM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ExploreZone()
{
	INT32 nRetCode = 0;
	C2G_EXPLORE_ZONE* pMsg = (C2G_EXPLORE_ZONE*)m_poPacketAllocator->Alloc(sizeof(C2G_EXPLORE_ZONE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_explore_zone;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_EXPLORE_ZONE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::TalkToNpc(INT32	nQuestID, INT32 nTalkNpcID)
{
	INT32 nRetCode = 0;
	C2G_TALK_TO_NPC* pMsg = (C2G_TALK_TO_NPC*)m_poPacketAllocator->Alloc(sizeof(C2G_TALK_TO_NPC));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_talk_to_npc;
	pMsg->nQuestID = nQuestID;
	pMsg->dwTalkNpcID = nTalkNpcID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_TALK_TO_NPC));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::UnlockTrade()
{
	INT32 nRetCode = 0;
	C2G_TRADE_UNLOCK* pMsg = (C2G_TRADE_UNLOCK*)m_poPacketAllocator->Alloc(sizeof(C2G_TRADE_UNLOCK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_unlock;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_UNLOCK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SetTradeMoney(INT32 money)
{
	INT32 nRetCode = 0;
	C2G_TRADE_SET_MONEY* pMsg = (C2G_TRADE_SET_MONEY*)m_poPacketAllocator->Alloc(sizeof(C2G_TRADE_SET_MONEY));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_set_money;
	pMsg->nMoney = money;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_SET_MONEY));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SetTradeItem(UINT8 tradeslot, UINT8 bAdd, UINT8 conslot, UINT8 itemslot)
{
	INT32 nRetCode = 0;
	C2G_TRADE_SET_ITEM* pMsg = (C2G_TRADE_SET_ITEM*)m_poPacketAllocator->Alloc(sizeof(C2G_TRADE_SET_ITEM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_set_item;
	pMsg->byTradeSlot = tradeslot;
	pMsg->bAdd = bAdd;
	pMsg->byConSlot = conslot;
	pMsg->byItemSlot = itemslot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_SET_ITEM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SendMail(const char* rolename, const char* subject, const char* content)
{
	INT32 nRetCode = 0;
	UINT16 len = sizeof(C2M_MAIL_WRITE) + strlen(content) + 1;
	C2M_MAIL_WRITE* pMsg = (C2M_MAIL_WRITE*)m_poPacketAllocator->Alloc(len);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_mail_write;
	pMsg->wSize = len;
	strxcpy(pMsg->szRoleName, rolename, ROLE_NAME_LEN);
	strxcpy(pMsg->szMailSubject, subject, MAIL_SUBJECT_LEN);
	pMsg->dwMailContentLen = strlen(content);
	strxcpy(pMsg->szMailContent, content, MAIL_CONTENT_LEN);

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, len);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ListMail()
{
	INT32 nRetCode = 0;
	C2M_MAIL_LIST_RECV* pMsg = (C2M_MAIL_LIST_RECV*)m_poPacketAllocator->Alloc(sizeof(C2M_MAIL_LIST_RECV));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_mail_list_recv;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MAIL_LIST_RECV));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ReadMail(UINT32 mailid)
{
	INT32 nRetCode = 0;
	C2M_MAIL_READ* pMsg = (C2M_MAIL_READ*)m_poPacketAllocator->Alloc(sizeof(C2M_MAIL_READ));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_mail_read;
	pMsg->dwMailID = mailid;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MAIL_READ));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::DeleteMail(UINT32 mailid)
{
	INT32 nRetCode = 0;
	C2M_MAIL_DELETE* pMsg = (C2M_MAIL_DELETE*)m_poPacketAllocator->Alloc(sizeof(C2M_MAIL_DELETE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_mail_delete;
	pMsg->dwMailID = mailid;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MAIL_DELETE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::GetMailAttach(UINT32 mailid)
{
	INT32 nRetCode = 0;
	C2M_MAIL_GET_ATTACH* pMsg = (C2M_MAIL_GET_ATTACH*)m_poPacketAllocator->Alloc(sizeof(C2M_MAIL_GET_ATTACH));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_mail_get_attach;
	pMsg->dwMailID = mailid;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MAIL_GET_ATTACH));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::DoGatePing(UINT32 dwTick)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2T_PING);
	C2T_PING* pMsg = (C2T_PING*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2t_ping;
	pMsg->dwPingTick = dwTick;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::DoGamePing(UINT32 dwTick)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_PING);
	C2G_PING* pMsg = (C2G_PING*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_ping;
	pMsg->dwPingTick = dwTick;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::EquipSpell(INT32 nSlot, INT32 nSpellID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_EQUIP_SPELL);
	C2G_EQUIP_SPELL* pMsg = (C2G_EQUIP_SPELL*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_equip_spell;
	pMsg->bySlot = nSlot;
	pMsg->wSpellID = nSpellID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::SendMsg(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	LOG_PROCESS_ERROR(m_poSocketSession);

	if (m_eUserState != usConnectingBS)
		LOG_PROCESS_ERROR(m_bConnected);

	if (m_byEncryptCode)
	{
		for (INT32 nIndex = sizeof(FLEX_MESSAGE_HEADER); nIndex < dwSize; nIndex++)
		{
			pPacketBuffer[nIndex] ^= m_byEncryptCode;
		}
	}

	nRetCode = m_poSocketSession->Send(pPacketBuffer, dwSize, 0);
	LOG_PROCESS_ERROR(nRetCode);
	m_dwSendSize += dwSize;

	return TRUE;
Exit0:
	return FALSE;
}

const UINT32 CUser::GetServerAddress(void)
{
	LOG_PROCESS_ERROR(m_bConnected);
	LOG_PROCESS_ERROR(m_poSocketSession);

	return m_dwServerAddress;
Exit0:
	return NULL;
}

UINT16 CUser::GetServerPort(void)
{
	LOG_PROCESS_ERROR(m_bConnected);
	LOG_PROCESS_ERROR(m_poSocketSession);

	return m_wServerPort;
Exit0:
	return 0;
}

CRole* CUser::GetPlayingRole(void)
{
	PROCESS_ERROR(m_eUserState == usPlaying);

	return m_poPlayingRole;
Exit0:
	return NULL;
}

void CUser::SetPlayingRole(CRole* poRole)
{
	m_poPlayingRole = poRole;
}

CRole* CUser::GetRoleByID(UINT32 dwRoleID)
{
	for (INT32 idx = 0; idx < MAX_ROLE_PER_USER; ++idx)
	{
		if (m_poRoleList[idx] != NULL && m_poRoleList[idx]->GetObjID() == dwRoleID)
			return m_poRoleList[idx];
	}
	return NULL;
}

CRole* CUser::GetRoleByIndex(INT32 nIndex)
{
	LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < MAX_ROLE_PER_USER);
	LOG_PROCESS_ERROR(m_poRoleList[nIndex]);

	return m_poRoleList[nIndex];
Exit0:
	return NULL;
}

INT32 CUser::GetRoleCount(void)
{
	INT32 nResult = 0;
	for (INT32 idx = 0; idx < MAX_ROLE_PER_USER; ++idx)
	{
		if (m_poRoleList[idx] != NULL)
			nResult++;
	}
	return nResult;
}

void CUser::SetDeleteFlag(void)
{
	INF("user %s SetDeleteFlag", GetUserName());
	m_bDeleted = TRUE;
}

BOOL CUser::AcceptQuest(INT32 nQuestID, INT32 nAcceptType, INT32 nSrcID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_ACCEPT_QUEST);
	C2G_ACCEPT_QUEST* pMsg = (C2G_ACCEPT_QUEST*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_accept_quest;
	pMsg->nQuestID = nQuestID;
	pMsg->nAcceptType = nAcceptType;
	pMsg->nAcceptSrcID = nSrcID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::AbandonQuest(INT32 nQuestID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_ABANDON_QUEST);
	C2G_ABANDON_QUEST* pMsg = (C2G_ABANDON_QUEST*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_abandon_quest;
	pMsg->nQuestID = nQuestID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::CompleteQuest(INT32 nQuestID, INT32 nSelectedIdx)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_COMPLETE_QUEST);
	C2G_COMPLETE_QUEST* pMsg = (C2G_COMPLETE_QUEST*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_complete_quest;
	pMsg->nQuestID = nQuestID;
	pMsg->nSelectedAwardIdx = nSelectedIdx;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ShareQuest(INT32 nQuestID, INT32 nShareType)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SHARE_QUEST);
	C2G_SHARE_QUEST* pMsg = (C2G_SHARE_QUEST*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_share_quest;
	pMsg->nQuestID = nQuestID;
	pMsg->nShareType = nShareType;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ConfirmPublishQuest(INT32 nQuestID, INT32 nMasterID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_CONFIRM_PUBLISH_QUEST);
	C2G_CONFIRM_PUBLISH_QUEST* pMsg = (C2G_CONFIRM_PUBLISH_QUEST*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_confirm_publish_quest;
	pMsg->nQuestID = nQuestID;
	pMsg->dwMasterID = nMasterID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::GenerateCircleQuest()
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_GENERATE_CIRCLE_QUEST);
	C2G_GENERATE_CIRCLE_QUEST* pMsg = (C2G_GENERATE_CIRCLE_QUEST*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_generate_circle_quest;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::CompleteAchievement(INT32 nAchievementID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_COMPLETE_ACHIEVEMENT);

	C2G_COMPLETE_ACHIEVEMENT* pMsg = (C2G_COMPLETE_ACHIEVEMENT*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_complete_achievement;
	pMsg->nAchievementID = nAchievementID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::GetAchievementReward(INT32 nAchievementID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_REWARD_ACHIEVEMENT);

	C2G_REWARD_ACHIEVEMENT* pMsg = (C2G_REWARD_ACHIEVEMENT*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_reward_achievement;
	pMsg->nAchievementID = nAchievementID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::CompareAchievement(UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_COMPARE_ACHIEVEMENT);

	C2G_COMPARE_ACHIEVEMENT* pMsg = (C2G_COMPARE_ACHIEVEMENT*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_compare_achievement;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::InteractWithNpc(UINT32 dwNpcID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_INTERACT_WITH_NPC);

	C2G_INTERACT_WITH_NPC* pMsg = (C2G_INTERACT_WITH_NPC*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_interact_with_npc;
	pMsg->dwNpcID = dwNpcID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}


BOOL CUser::SelectDialogOption(INT32 nParam)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SELECT_DIALOG_OPTION);
	C2G_SELECT_DIALOG_OPTION* pMsg = (C2G_SELECT_DIALOG_OPTION*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_select_dialog_option;
	pMsg->nParam = nParam;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::OperateDoodad(UINT32 dwDoodadID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_OPERATE_DOODAD);
	C2G_OPERATE_DOODAD* pMsg = (C2G_OPERATE_DOODAD*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_operate_doodad;
	pMsg->dwDoodadID = dwDoodadID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::QueryRanklist(INT32 nPage, INT32 nRanklistID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2M_QUERY_RANKLIST);
	C2M_QUERY_RANKLIST* pMsg = (C2M_QUERY_RANKLIST*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_query_ranklist;
	pMsg->nPageSize = nPage;
	pMsg->nRanklistID = nRanklistID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ChangeSoul2Pts(BOOL bUseMoney, BOOL bIsOnline)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SPIRIT_EXP_CHANGE);
	C2G_SPIRIT_EXP_CHANGE* pMsg = (C2G_SPIRIT_EXP_CHANGE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_exp_change;
	pMsg->bIsOnline = bIsOnline;
	pMsg->bUseMoney = bUseMoney;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SpiritAddAir(BOOL bQuick)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SPIRIT_ADD_AIR);
	C2G_SPIRIT_ADD_AIR* pMsg = (C2G_SPIRIT_ADD_AIR*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_add_air;
	pMsg->bQuick = bQuick;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::MergeAir(INT32 nSrcSlot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SPIRIT_MERGE_AIR);
	C2G_SPIRIT_MERGE_AIR* pMsg = (C2G_SPIRIT_MERGE_AIR*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_merge_air;
	pMsg->nSrcCon = nSrcSlot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::MoveAir(INT32 nSrcType, INT32 nSrcSlot, INT32 nTarType, INT32 nTarSlot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SPIRIT_MOVE_AIR);
	C2G_SPIRIT_MOVE_AIR* pMsg = (C2G_SPIRIT_MOVE_AIR*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_move_air;

	pMsg->nSrcBagType = nSrcType;
	pMsg->nSrcIndex = nSrcSlot;
	pMsg->nTarBagType = nTarType;
	pMsg->nTarIndex = nTarSlot;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::BuyAirSlot(INT32 nBagType)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SPIRIT_BUY_AIR_SLOT);
	C2G_SPIRIT_BUY_AIR_SLOT* pMsg = (C2G_SPIRIT_BUY_AIR_SLOT*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_buy_air_slot;

	pMsg->nBagType = nBagType;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::BrushSlot(INT32 nPage, INT32 nIndex)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SPIRIT_BRUSH_SLOT);
	C2G_SPIRIT_BRUSH_SLOT* pMsg = (C2G_SPIRIT_BRUSH_SLOT*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_brush_slot;

	pMsg->nPage = nPage;
	pMsg->nIndex = nIndex;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SendLoadFinsh()
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_LOADFINISH);
	C2G_LOADFINISH* pMsg = (C2G_LOADFINISH*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_loadfinish;
	pMsg->nErrCode = errSuccess;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SelectDungeonDifficulty(UINT32 nDifficulty)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SELECT_SCENE_DIFFICULTY);
	C2G_SELECT_SCENE_DIFFICULTY* pMsg = (C2G_SELECT_SCENE_DIFFICULTY*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_select_scene_difficulty;
	pMsg->bySelectedDifficulty = nDifficulty;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::EnterDungeon(UINT32 nDifficulty)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_ENTER_DUNGEON);
	C2G_ENTER_DUNGEON* pMsg = (C2G_ENTER_DUNGEON*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_enter_dungeon;
	pMsg->bySelectedDifficulty = nDifficulty;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::LeaveScene(void)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_LEAVE_SCENE);

	C2G_LEAVE_SCENE* pMsg = (C2G_LEAVE_SCENE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_leave_scene;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::QueryRoleDetailData(UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_QUERY_ROLE_DETAIL_DATA);
	CACHE_MAP::iterator it;

	C2G_QUERY_ROLE_DETAIL_DATA* pMsg = (C2G_QUERY_ROLE_DETAIL_DATA*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_query_role_detail_data;
	pMsg->dwRoleID = dwRoleID;
	pMsg->dwAttrCRC = 0;
	pMsg->dwEquipCRC = 0;
	pMsg->dwSpiritCRC = 0;
	pMsg->dwSpellCRC = 0;

	it = m_AttrCacheMap.find(dwRoleID);
	if (it != m_AttrCacheMap.end())
		pMsg->dwAttrCRC = it->second;

	it = m_EquipCacheMap.find(dwRoleID);
	if (it != m_EquipCacheMap.end())
		pMsg->dwEquipCRC = it->second;

	it = m_SpiritCacheMap.find(dwRoleID);
	if (it != m_SpiritCacheMap.end())
		pMsg->dwSpiritCRC = it->second;

	it = m_SpellCacheMap.find(dwRoleID);
	if (it != m_SpellCacheMap.end())
		pMsg->dwSpellCRC = it->second;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::QueryRolePow(UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_QUERY_ROLE_POW);

	C2G_QUERY_ROLE_POW* pMsg = (C2G_QUERY_ROLE_POW*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_query_role_pow;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ChangeLine(INT32 nSceneID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_CHANGE_LINE);

	C2G_CHANGE_LINE* pMsg = (C2G_CHANGE_LINE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_change_line;
	pMsg->byLineIndex = (UINT8)nSceneID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::UpdateClientVariable(INT32 nVarIndex, INT32 nVarValue)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_UPDATE_CLIENT_VARIABLE);

	C2G_UPDATE_CLIENT_VARIABLE* pMsg = (C2G_UPDATE_CLIENT_VARIABLE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_update_client_variable;
	pMsg->byVarIndex = (UINT8)nVarIndex;
	pMsg->nVarValue = nVarValue;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

void CUser::UpdateRoleAttrCRC(UINT32 dwRoleID, UINT32 dwCRC)
{
	m_AttrCacheMap[dwRoleID] = dwCRC;
}

void CUser::UpdateRoleEquipCRC(UINT32 dwRoleID, UINT32 dwCRC)
{
	m_EquipCacheMap[dwRoleID] = dwCRC;
}

void CUser::UpdateRoleSpiritCRC(UINT32 dwRoleID, UINT32 dwCRC)
{
	m_SpiritCacheMap[dwRoleID] = dwCRC;
}

void CUser::UpdateRoleSpellCRC(UINT32 dwRoleID, UINT32 dwCRC)
{
	m_SpellCacheMap[dwRoleID] = dwCRC;
}

void CUser::RegisterMsg(const char* pcszCaseName, CMsgSet& oSetMsg)
{
	strncpy(m_szCaseName, pcszCaseName, 256);
	for (CMsgSetItr itr = oSetMsg.begin(); itr != oSetMsg.end(); ++itr)
		m_oSetMsg.insert(*itr);
}

void CUser::UnRegisterMsg()
{
	memset(m_szCaseName, 0, 256);
	m_oSetMsg.clear();
	m_dwTempIndex = 0;
}

void CUser::LuaRecvMsg(INT32 nMsgID, void* pData, UINT32 dwDataLen)
{
	CMsgSetItr itr = m_oSetMsg.find(nMsgID);
	if (itr != m_oSetMsg.end())
	{
		CLuaScript* poScript = CScriptMgr::GetInstance().FindScript(ROBOT_SCRIPT_NAME);
		if (poScript)
		{
			INT32 nStackTop = 0;

			if (m_dwTempIndex + dwDataLen + 1 >= 65536)
			{
				LOG_PROCESS_ERROR(0);
			}
			else
			{
				memcpy(&m_szTempData[m_dwTempIndex], pData, dwDataLen);
				m_szTempData[m_dwTempIndex + dwDataLen] = 0;
			}

			poScript->CallFunction("OnRecvMsg", "sddo",
				m_szCaseName, m_nSessionID, nMsgID, &m_szTempData[m_dwTempIndex], "ExternalMessage::G2C_ERROR_NOTIFY");

			m_dwTempIndex += dwDataLen;
			m_dwTempIndex += 1;
		}
	}

	return;
Exit0:
	return;
}

void CUser::ResetRecvData()
{
	m_qwStartRecvTick = GetTickCountEx();
	m_dwReceiveSize = 0;
}

void CUser::ResetSendData()
{
	m_qwStartSendTick = GetTickCountEx();
	m_dwSendSize = 0;
}

void CUser::ResetChatData()
{
	m_qwStartChatTick = GetTickCountEx();
	m_dwChatCount = 0;
}

BOOL CUser::VerifyItem(UINT32 dwSrcRoleId, char* pText)
{
	INT32 nRetCode = 0;
	UINT32 dwSignSize = 0;
	INT32 nMessageSize = 0;
	UCHAR ucSignItem[1024] = { 0 };
	UINT8 byPre[] = "I=<";
	UINT32 dwRoleID = 0;
	UINT32 dwPreSize = 0;

	//LOG_PROCESS_ERROR(pText);

	//   RSA* pPublickey = CGameWorld::GetInstance().GetRSAKey();
	//LOG_PROCESS_ERROR(pPublickey);

	//nRetCode = String2Buffer(ucSignItem, nMessageSize, pText);
	//LOG_PROCESS_ERROR(nRetCode);
	//dwSignSize = nMessageSize;

	//for(INT32 nIndex = 0; nIndex < sizeof(byPre)/sizeof(byPre[0]); nIndex++)
	//	LOG_PROCESS_ERROR(*(byPre + nIndex) == *(ucSignItem + nIndex + dwPreSize));
	//dwPreSize = dwPreSize + sizeof(byPre);

	//memcpy(&dwRoleID, ucSignItem + dwPreSize, sizeof(dwRoleID));
	//LOG_PROCESS_ERROR(dwRoleID == dwSrcRoleId);

	//// 注意还有一个结束符'>'
	//nRetCode = RSA_Verify(pPublickey, ucSignItem + dwPreSize, nMessageSize - RSA_KEY_LENGTH/8 - dwPreSize - 1, ucSignItem + (nMessageSize - RSA_KEY_LENGTH/8 - 1), RSA_KEY_LENGTH/8);
	//LOG_PROCESS_ERROR(nRetCode == errSuccess);

	//return TRUE;	
Exit0:
	return FALSE;
}

void CUser::AddPingPackage(UINT32 dwPingTick)
{
	if (dwPingTick < m_dwMinPing)
		m_dwMinPing = dwPingTick;

	if (dwPingTick > m_dwMaxPing)
		m_dwMaxPing = dwPingTick;

	m_qwPingValue += dwPingTick;
	m_qwPingCount++;

	//     if(m_qwPingCount && m_qwPingCount % 10 == 0)
	//         INF("ping Info:min=%dms, max=%dms, average=%dms", m_dwMinPing, m_dwMaxPing, m_qwPingValue/m_qwPingCount);
}

BOOL CUser::FireHero(void)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_FIRE_HERO);
	C2G_FIRE_HERO* pMsg = (C2G_FIRE_HERO*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_fire_hero;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SummonHero(void)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SUMMON_HERO);
	C2G_SUMMON_HERO* pMsg = (C2G_SUMMON_HERO*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_summon_hero;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::RecallHero(void)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_RECALL_HERO);
	C2G_RECALL_HERO* pMsg = (C2G_RECALL_HERO*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_recall_hero;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::QueryHeroAttrList(void)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_QUERY_HERO_ATTR_LIST);
	C2G_QUERY_HERO_ATTR_LIST* pMsg = (C2G_QUERY_HERO_ATTR_LIST*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_query_hero_attr_list;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::ChangeHeroAi(INT32 nAiType)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_CHANGE_HERO_AI);
	C2G_CHANGE_HERO_AI* pMsg = (C2G_CHANGE_HERO_AI*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_change_hero_ai;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

//////////////////////////////////////////////////////////////////////////
// title
BOOL CUser::EquipTitle(UINT8 byTitleID)
{
	INT32 nRetCode = 0;
	C2G_TITLE_EQUIP* pMsg = (C2G_TITLE_EQUIP*)m_poPacketAllocator->Alloc(sizeof(C2G_TITLE_EQUIP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_title_equip;
	pMsg->nTemplateTitleID = byTitleID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_TITLE_EQUIP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::UnEquipTitle()
{
	INT32 nRetCode = 0;
	C2G_TITLE_UNEQUIP* pMsg = (C2G_TITLE_UNEQUIP*)m_poPacketAllocator->Alloc(sizeof(C2G_TITLE_UNEQUIP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_title_unequip;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_TITLE_UNEQUIP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

// master
BOOL CUser::GetMasterInfo()
{
	INT32 nRetCode = 0;
	C2M_MASTER_INFO* pMsg = (C2M_MASTER_INFO*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_INFO));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_info;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_INFO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::GetMasterRecruitList()
{
	INT32 nRetCode = 0;
	C2M_MASTER_GET_RECRUIT_LIST* pMsg = (C2M_MASTER_GET_RECRUIT_LIST*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_GET_RECRUIT_LIST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_get_recruit_list;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_GET_RECRUIT_LIST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::GetMasterSoloList()
{
	INT32 nRetCode = 0;
	C2M_MASTER_GET_SOLO_LIST* pMsg = (C2M_MASTER_GET_SOLO_LIST*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_GET_SOLO_LIST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_get_solo_list;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_GET_SOLO_LIST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ApplyTeacher(UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_STUD_SUBMIT_APP* pMsg = (C2M_MASTER_STUD_SUBMIT_APP*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_STUD_SUBMIT_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_stud_submit_app;
	pMsg->dwTeacherID = dwRoleID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_STUD_SUBMIT_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::TeacherAgreeApp(UINT32 dwStudentID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_AGREE_STUD_APP* pMsg = (C2M_MASTER_AGREE_STUD_APP*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_AGREE_STUD_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_agree_stud_app;
	pMsg->dwStudentID = dwStudentID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_AGREE_STUD_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::TeacherRefuseApp(UINT32 dwStudID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_REFUSE_STUD_APP* pMsg = (C2M_MASTER_REFUSE_STUD_APP*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_REFUSE_STUD_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_refuse_stud_app;
	pMsg->dwStudentID = dwStudID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_REFUSE_STUD_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SoloCancelApp(UINT32 dwTeacherID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_CANCEL_STUD_APP* pMsg = (C2M_MASTER_CANCEL_STUD_APP*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_CANCEL_STUD_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_cancel_stud_app;
	pMsg->dwTeacherID = dwTeacherID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_CANCEL_STUD_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ApplyToStudent(UINT32 dwStudentID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_TEACHER_SUBMIT_APP* pMsg = (C2M_MASTER_TEACHER_SUBMIT_APP*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_TEACHER_SUBMIT_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_teacher_submit_app;
	pMsg->dwStudentID = dwStudentID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_TEACHER_SUBMIT_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SoloAgreeApp(UINT32 dwTeacherID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_AGREE_TEACHER_APP* pMsg = (C2M_MASTER_AGREE_TEACHER_APP*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_AGREE_TEACHER_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_agree_teacher_app;
	pMsg->dwTeacherID = dwTeacherID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_AGREE_TEACHER_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SoloRefuseApp(UINT32 dwTeacherID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_REFUSE_TEACHER_APP* pMsg = (C2M_MASTER_REFUSE_TEACHER_APP*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_REFUSE_TEACHER_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_refuse_teacher_app;
	pMsg->dwTeacherID = dwTeacherID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_REFUSE_TEACHER_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::TeacherCancelApp(UINT32 dwStudentID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_CANCEL_TEACHER_APP* pMsg = (C2M_MASTER_CANCEL_TEACHER_APP*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_CANCEL_TEACHER_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_cancel_teacher_app;
	pMsg->dwStudentID = dwStudentID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_CANCEL_TEACHER_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::LeaveTeacher()
{
	INT32 nRetCode = 0;
	C2M_MASTER_LEAVE_TEACHER* pMsg = (C2M_MASTER_LEAVE_TEACHER*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_LEAVE_TEACHER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_leave_teacher;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_LEAVE_TEACHER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::FireStudent(UINT32 dwStudentID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_FIRE_STUD* pMsg = (C2M_MASTER_FIRE_STUD*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_FIRE_STUD));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_fire_stud;
	pMsg->dwStudentID = dwStudentID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_FIRE_STUD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::MasterCZ(UINT32 dwSelfID, UINT32 dwTargetID, UINT8 byCZType, const char *pcszText)
{
	INT32   nRetCode = 0;
	INT32   nSize = 0;
	C2M_MASTER_CZ* pMsg = NULL;

	LOG_PROCESS_ERROR(pcszText);

	nSize = strlen(pcszText) + 1;

	pMsg = (C2M_MASTER_CZ*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_cz;
    pMsg->wSize = sizeof(C2M_MASTER_CZ) + nSize;

	pMsg->dwRoleID = dwSelfID;
	pMsg->dwTargetID = dwTargetID;
	pMsg->byCZType = byCZType;
	strxcpy(pMsg->szText, pcszText, nSize);

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, pMsg->wSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::DesireGraduate()
{
	INT32 nRetCode = 0;
	//C2M_MASTER_DESIRE_GRAD* pMsg = (C2M_MASTER_DESIRE_GRAD*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_DESIRE_GRAD));
	//LOG_PROCESS_ERROR(pMsg);

	//pMsg->wMsg = c2m_master_desire_grad;

	//nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_DESIRE_GRAD));
	//LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::AgreeGraduate(UINT32 dwStudentID)
{
	INT32 nRetCode = 0;
//	C2M_MASTER_AGREE_GRAD* pMsg = (C2M_MASTER_AGREE_GRAD*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_AGREE_GRAD));
//	LOG_PROCESS_ERROR(pMsg);
//
//	pMsg->wMsg = c2m_master_agree_grad;
//	pMsg->dwStudentID = dwStudentID;
//
//	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_AGREE_GRAD));
//	LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ForceGraduate()
{
	INT32 nRetCode = 0;
//	C2M_MASTER_FORCE_GRAD* pMsg = (C2M_MASTER_FORCE_GRAD*)m_poPacketAllocator->Alloc(sizeof(C2M_MASTER_FORCE_GRAD));
//	LOG_PROCESS_ERROR(pMsg);
//
//	pMsg->wMsg = c2m_master_force_grad;
//
//	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_FORCE_GRAD));
//	LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::AuctionSearchType(UINT8 byAuctionType, UINT8 byAuctionSubType)
{
    INT32 nRetCode = 0;
    C2M_AUCTION_SEARCH_TYPE* pMsg = (C2M_AUCTION_SEARCH_TYPE*)m_poPacketAllocator->Alloc(sizeof(C2M_AUCTION_SEARCH_TYPE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_auction_search_type;
    pMsg->byAuctionType = byAuctionType;
    pMsg->byAuctionSubType = byAuctionSubType;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_AUCTION_SEARCH_TYPE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::AuctionSearch(UINT8 bySortBy, INT32 nItemID)
{
    INT32 nRetCode = 0;
    C2M_AUCTION_SEARCH* pMsg = (C2M_AUCTION_SEARCH*)m_poPacketAllocator->Alloc(sizeof(C2M_AUCTION_SEARCH));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_auction_search;
    pMsg->bySortBy = bySortBy;
    pMsg->nItemTemplateID = nItemID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_AUCTION_SEARCH));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::AuctionQuery(UINT32 dwAuctionID)
{
    INT32 nRetCode = 0;
    C2M_AUCTION_QUERY* pMsg = (C2M_AUCTION_QUERY*)m_poPacketAllocator->Alloc(sizeof(C2M_AUCTION_QUERY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_auction_query;
    pMsg->dwAuctionID = dwAuctionID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_AUCTION_QUERY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::AuctionSell(UINT8 byConSlot, UINT8 byItemSlot, INT32 nPrice, INT32 nBuyoutPrice)
{
    INT32 nRetCode = 0;
    C2M_AUCTION_SELL* pMsg = (C2M_AUCTION_SELL*)m_poPacketAllocator->Alloc(sizeof(C2M_AUCTION_SELL));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_auction_sell;
    pMsg->byConSlot = byConSlot;
    pMsg->byItemSlot = byItemSlot;
    pMsg->nPrice = nPrice;
    pMsg->nBuyoutPrice = nBuyoutPrice;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_AUCTION_SELL));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::AuctionCancelSell(UINT32 dwAuctionID)
{
    INT32 nRetCode = 0;
    C2M_AUCTION_CANCEL_SELL* pMsg = (C2M_AUCTION_CANCEL_SELL*)m_poPacketAllocator->Alloc(sizeof(C2M_AUCTION_CANCEL_SELL));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_auction_cancel_sell;
    pMsg->dwAuctionID = dwAuctionID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_AUCTION_CANCEL_SELL));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::AuctionBuy(UINT32 dwAuctionID, INT32 nPrice)
{
    INT32 nRetCode = 0;
    C2M_AUCTION_BUY* pMsg = (C2M_AUCTION_BUY*)m_poPacketAllocator->Alloc(sizeof(C2M_AUCTION_BUY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_auction_buy;
    pMsg->dwAuctionID = dwAuctionID;
    pMsg->nPrice = nPrice;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_AUCTION_BUY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::AuctionListMySelling()
{
    INT32 nRetCode = 0;
    C2M_AUCTION_LIST_MY_SELLING* pMsg = (C2M_AUCTION_LIST_MY_SELLING*)m_poPacketAllocator->Alloc(sizeof(C2M_AUCTION_LIST_MY_SELLING));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_auction_list_my_selling;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_AUCTION_LIST_MY_SELLING));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::AuctionListMyBuying()
{
    INT32 nRetCode = 0;
    C2M_AUCTION_LIST_MY_BUYING* pMsg = (C2M_AUCTION_LIST_MY_BUYING*)m_poPacketAllocator->Alloc(sizeof(C2M_AUCTION_LIST_MY_BUYING));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_auction_list_my_buying;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_AUCTION_LIST_MY_BUYING));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::SubscribeVIP(INT32 nVIPLevel, INT32 nMonth)
{
	INT32 nRetCode = 0;

	C2G_SUBSCRIBE_VIP* pMsg = (C2G_SUBSCRIBE_VIP*)m_poPacketAllocator->Alloc(sizeof(C2G_SUBSCRIBE_VIP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_subscribe_vip;
	pMsg->byVIPLevel = (UINT8)nVIPLevel;
	pMsg->byMonth = (UINT8)nMonth;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_SUBSCRIBE_VIP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::ShieldRole(UINT32  dwRoleID)
{
    INT32 nRetCode = 0;

    C2M_SHIELD* pMsg = (C2M_SHIELD*)m_poPacketAllocator->Alloc(sizeof(C2M_SHIELD));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_shield;
    pMsg->dwRoleID = dwRoleID;
    memset(pMsg->szRoleName, 0, sizeof(pMsg->szRoleName));

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_SHIELD));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::UnShieldRole(UINT32  dwRoleID)
{
    INT32 nRetCode = 0;

    C2G_UNSHIELD* pMsg = (C2G_UNSHIELD*)m_poPacketAllocator->Alloc(sizeof(C2G_UNSHIELD));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2g_unshield;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_UNSHIELD));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

// guild
BOOL CUser::QueryGuildInfo(UINT32 dwGuildID)
{
    INT32   nRetCode = 0;
    C2M_QUERY_GUILD_NAME* pMsg = (C2M_QUERY_GUILD_NAME*)m_poPacketAllocator->Alloc(sizeof(C2M_QUERY_GUILD_NAME));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_query_guild_name;
    pMsg->dwGuildID = dwGuildID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_QUERY_GUILD_NAME));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::CreateGuild(const char *pcszGuildName, const char *pcszAnnounce)
{
    INT32       nRetCode = 0;
    INT32       nSize = 0;
    C2G_GUILD_CREATE    *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszGuildName);
    LOG_PROCESS_ERROR(pcszAnnounce);

    nSize = strlen(pcszAnnounce) + 1;

    LOG_PROCESS_ERROR( (nSize + sizeof(C2G_GUILD_CREATE)) < (MAX_MESSAGE_SIZE - 1) );

    pMsg = (C2G_GUILD_CREATE *)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    strxcpy(pMsg->szGuildName, pcszGuildName, sizeof(pMsg->szGuildName));
    strxcpy(pMsg->szAnnounce, pcszAnnounce, nSize);

    nSize += sizeof(C2G_GUILD_CREATE);
    pMsg->wSize = nSize;
    pMsg->wMsg = c2g_guild_create;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::GetGuildMoreInfo()
{
    INT32   nRetCode = 0;
    C2M_MORE_GUILD_INFO* pMsg = (C2M_MORE_GUILD_INFO*)m_poPacketAllocator->Alloc(sizeof(C2M_MORE_GUILD_INFO));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_more_guild_info;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_MORE_GUILD_INFO));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::ViewGuildList(UINT32 dwLastGuildID)
{
    INT32   nRetCode = 0;
    C2M_VIEW_GUILD_LIST* pMsg = (C2M_VIEW_GUILD_LIST*)m_poPacketAllocator->Alloc(sizeof(C2M_VIEW_GUILD_LIST));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_view_guild_list;
    pMsg->byViewType = GUILD_VIEW_DOWN;
    pMsg->dwLastGuildID = dwLastGuildID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_VIEW_GUILD_LIST));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

//BOOL CUser::FindGuild(const char *pcszName)
//{
//    INT32 nRetCode = 0;
//    C2M_FIND_GUILD* pMsg = NULL;
//    
//    LOG_PROCESS_ERROR(pcszName);
//
//    pMsg = (C2M_FIND_GUILD*)m_poPacketAllocator->Alloc(sizeof(C2M_FIND_GUILD));
//    LOG_PROCESS_ERROR(pMsg);
//
//    pMsg->wMsg = c2m_find_guild;
//    pMsg->dwGuildID = 0;
//    memcpy(pMsg->szGuildName, pcszName, GUILD_NAME_LEN);
//
//    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_FIND_GUILD));
//    LOG_PROCESS_ERROR(nRetCode);
//
//    return TRUE;
//Exit0:
//    if (pMsg)
//        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//    return FALSE;
//}

BOOL CUser::FindGuild(UINT32 dwGuildID)
{
    INT32 nRetCode = 0;
    C2M_FIND_GUILD* pMsg = NULL;

    pMsg = (C2M_FIND_GUILD*)m_poPacketAllocator->Alloc(sizeof(C2M_FIND_GUILD));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_find_guild;
    pMsg->dwGuildID = dwGuildID;
    memset(pMsg->szGuildName, 0, sizeof(pMsg->szGuildName));

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_FIND_GUILD));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::ApplyToJoinGuild(UINT32 dwGuildID)
{
    INT32 nRetCode = 0;
    C2M_APPLY_TO_JOIN_GUILD* pMsg = NULL;

    pMsg = (C2M_APPLY_TO_JOIN_GUILD*)m_poPacketAllocator->Alloc(sizeof(C2M_APPLY_TO_JOIN_GUILD));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_apply_to_join_guild;
    pMsg->dwGuildID = dwGuildID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_APPLY_TO_JOIN_GUILD));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::GetGuildAppList()
{
    INT32 nRetCode = 0;
    C2M_GET_APPLY_GUILD_LIST* pMsg = NULL;

    pMsg = (C2M_GET_APPLY_GUILD_LIST*)m_poPacketAllocator->Alloc(sizeof(C2M_GET_APPLY_GUILD_LIST));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_get_apply_guild_list;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GET_APPLY_GUILD_LIST));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::RefuseGuildApp(UINT32 dwRoleID)
{
    INT32 nRetCode = 0;
    C2M_REVERT_GUILD_APPLY* pMsg = NULL;

    pMsg = (C2M_REVERT_GUILD_APPLY*)m_poPacketAllocator->Alloc(sizeof(C2M_REVERT_GUILD_APPLY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_revert_guild_apply;
    pMsg->byRevert = GUILD_REVERT_REFUSE;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_REVERT_GUILD_APPLY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::AgreeGuildApp(UINT32 dwRoleID)
{
    INT32 nRetCode = 0;
    C2M_REVERT_GUILD_APPLY* pMsg = NULL;

    pMsg = (C2M_REVERT_GUILD_APPLY*)m_poPacketAllocator->Alloc(sizeof(C2M_REVERT_GUILD_APPLY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_revert_guild_apply;
    pMsg->byRevert = GUILD_REVERT_AGREE;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_REVERT_GUILD_APPLY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::RevertGuildApp(UINT8 byRevertType, UINT32 dwRoleID)
{
    INT32 nRetCode = 0;
    C2M_REVERT_GUILD_APPLY* pMsg = NULL;

    pMsg = (C2M_REVERT_GUILD_APPLY*)m_poPacketAllocator->Alloc(sizeof(C2M_REVERT_GUILD_APPLY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_revert_guild_apply;
    pMsg->byRevert = byRevertType;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_REVERT_GUILD_APPLY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::InviteToJoinGuild(const char *pcszRoleName)
{
    INT32 nRetCode = 0;
    C2M_INVITE_TO_JOIN_GUILD* pMsg = NULL;

    LOG_PROCESS_ERROR(pcszRoleName);

    pMsg = (C2M_INVITE_TO_JOIN_GUILD*)m_poPacketAllocator->Alloc(sizeof(C2M_INVITE_TO_JOIN_GUILD));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_invite_to_join_guild;
    strxcpy(pMsg->szRoleName, pcszRoleName, ROLE_NAME_LEN);

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_INVITE_TO_JOIN_GUILD));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::RevertGuildInvitation(UINT8 byResult, UINT32 dwRoleID)
{
    INT32 nRetCode = 0;
    C2M_REVERT_GUILD_INVITATION* pMsg = NULL;

    pMsg = (C2M_REVERT_GUILD_INVITATION*)m_poPacketAllocator->Alloc(sizeof(C2M_REVERT_GUILD_INVITATION));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_revert_guild_invitation;
    pMsg->byResult = byResult;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_REVERT_GUILD_INVITATION));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::DisbandGuild()
{
    INT32 nRetCode = 0;
    C2M_DISBAND_GUILD* pMsg = NULL;

    pMsg = (C2M_DISBAND_GUILD*)m_poPacketAllocator->Alloc(sizeof(C2M_DISBAND_GUILD));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_disband_guild;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_DISBAND_GUILD));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::ChangeNotice(const char *pStr)
{
    INT32 nRetCode = 0;
    INT32   nSize = 0;
    C2M_GUILD_NOTICE_CHANGE* pMsg = NULL;

    LOG_PROCESS_ERROR(pStr);
    pMsg = (C2M_GUILD_NOTICE_CHANGE*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    nSize = strlen(pStr) + 1;
    LOG_PROCESS_ERROR(nSize < GUILD_NOTICE_LEN);

    pMsg->wMsg = c2m_guild_notice_change;
    strxcpy(pMsg->szNotice, pStr, nSize);
    pMsg->wSize = nSize + sizeof(C2M_GUILD_NOTICE_CHANGE);
    
    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::ChangePosition(UINT32 dwRoleID, INT32 nPosition)
{
    INT32 nRetCode = 0;
    C2M_GUILD_CHANGE_POSITION* pMsg = NULL;

    pMsg = (C2M_GUILD_CHANGE_POSITION*)m_poPacketAllocator->Alloc(sizeof(C2M_GUILD_CHANGE_POSITION));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_guild_change_position;
    pMsg->dwRoleID = dwRoleID;
    pMsg->byPosition = nPosition;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_CHANGE_POSITION));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::LeaveGuild()
{
    INT32 nRetCode = 0;
    C2M_GUILD_ROLE_LEAVE* pMsg = NULL;

    pMsg = (C2M_GUILD_ROLE_LEAVE*)m_poPacketAllocator->Alloc(sizeof(C2M_GUILD_ROLE_LEAVE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_guild_role_leave;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_ROLE_LEAVE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::BanishRole(UINT32 dwRoleID)
{
    INT32 nRetCode = 0;
    C2M_GUILD_BANISH_ROLE* pMsg = NULL;

    pMsg = (C2M_GUILD_BANISH_ROLE*)m_poPacketAllocator->Alloc(sizeof(C2M_GUILD_BANISH_ROLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_guild_banish_role;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_BANISH_ROLE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::Demise(UINT32 dwRoleID)
{
    INT32 nRetCode = 0;
    C2M_GUILD_DEMISE* pMsg = NULL;

    pMsg = (C2M_GUILD_DEMISE*)m_poPacketAllocator->Alloc(sizeof(C2M_GUILD_DEMISE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_guild_demise;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_DEMISE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::DrawSalary()
{
    INT32 nRetCode = 0;
    C2G_GUILD_DRAW_SALARY* pMsg = NULL;

    pMsg = (C2G_GUILD_DRAW_SALARY*)m_poPacketAllocator->Alloc(sizeof(C2G_GUILD_DRAW_SALARY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2g_guild_draw_salary;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_GUILD_DRAW_SALARY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::ContributeFund(INT32 nType, INT32 nMoney)
{
    INT32 nRetCode = 0;
    C2G_GUILD_CONTRIBUTE_FUND* pMsg = NULL;

    pMsg = (C2G_GUILD_CONTRIBUTE_FUND*)m_poPacketAllocator->Alloc(sizeof(C2G_GUILD_CONTRIBUTE_FUND));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2g_guild_contribute_fund;
    //pMsg->nType = nType;
    pMsg->nMoney = nMoney;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_GUILD_CONTRIBUTE_FUND));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::ForbidChat(INT32 nOP, UINT32 dwRoleID)
{
    INT32 nRetCode = 0;
    C2M_GUILD_FORBID_CHAT* pMsg = NULL;

    pMsg = (C2M_GUILD_FORBID_CHAT*)m_poPacketAllocator->Alloc(sizeof(C2M_GUILD_FORBID_CHAT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_guild_forbid_chat;
    pMsg->byOperation = nOP;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_FORBID_CHAT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::ChangeWeather(INT32 nWeatherType, INT32 nTimeType)
{
    INT32 nRetCode = 0;
    C2G_GUILD_CHANGE_WEATHER* pMsg = NULL;

    pMsg = (C2G_GUILD_CHANGE_WEATHER*)m_poPacketAllocator->Alloc(sizeof(C2G_GUILD_CHANGE_WEATHER));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2g_guild_change_weather;
    pMsg->byWeatherType = nWeatherType;
    pMsg->byTimeType = nTimeType;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2G_GUILD_CHANGE_WEATHER));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::MoreHistory()
{
    INT32 nRetCode = 0;
    C2M_GUILD_MORE_HISTORY* pMsg = NULL;

    pMsg = (C2M_GUILD_MORE_HISTORY*)m_poPacketAllocator->Alloc(sizeof(C2M_GUILD_MORE_HISTORY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_guild_more_history;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_MORE_HISTORY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::MoreChest()
{
    INT32 nRetCode = 0;
    C2M_GUILD_MORE_CHEST* pMsg = NULL;

    pMsg = (C2M_GUILD_MORE_CHEST*)m_poPacketAllocator->Alloc(sizeof(C2M_GUILD_MORE_CHEST));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_guild_more_chest;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_MORE_CHEST));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::ChangeStorageRight(INT32 nPosition, INT32 nRight)
{
    INT32 nRetCode = 0;
    C2M_GUILD_CHANGE_STORAGE_RIGHT* pMsg = NULL;

    pMsg = (C2M_GUILD_CHANGE_STORAGE_RIGHT*)m_poPacketAllocator->Alloc(sizeof(C2M_GUILD_CHANGE_STORAGE_RIGHT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_guild_change_storage_right;
    pMsg->byPosition = nPosition;
    pMsg->wRight = nRight;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_CHANGE_STORAGE_RIGHT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::DiplomatApp(INT32 nOP, INT32 nTimeType, const char *pcszGuildName)
{
    INT32 nRetCode = 0;
    C2M_GUILD_DIPLOMAT_APP* pMsg = NULL;

    LOG_PROCESS_ERROR(pcszGuildName);

    pMsg = (C2M_GUILD_DIPLOMAT_APP*)m_poPacketAllocator->Alloc(sizeof(C2M_GUILD_DIPLOMAT_APP));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_guild_diplomat_app;
    pMsg->byOpType = nOP;
    pMsg->byTimeType = nTimeType;
    strxcpy(pMsg->szGuildName, pcszGuildName, sizeof(pMsg->szGuildName));

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_DIPLOMAT_APP));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::GetApplyUnionList()
{
    INT32 nRetCode = 0;
    C2M_GUILD_GET_APPLY_UNION_LIST* pMsg = NULL;

    pMsg = (C2M_GUILD_GET_APPLY_UNION_LIST*)m_poPacketAllocator->Alloc(sizeof(C2M_GUILD_GET_APPLY_UNION_LIST));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_guild_get_apply_union_list;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_GET_APPLY_UNION_LIST));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CUser::ReplyUnionApp(INT32 nOP, UINT32 dwGuildID)
{
    INT32 nRetCode = 0;
    C2M_GUILD_REPLY_UNION_APP* pMsg = NULL;

    pMsg = (C2M_GUILD_REPLY_UNION_APP*)m_poPacketAllocator->Alloc(sizeof(C2M_GUILD_REPLY_UNION_APP));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = c2m_guild_reply_union_app;

    nRetCode = SendMsg((PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_REPLY_UNION_APP));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}



// lua
INT32 CUser::LuaMasterGetRecruitNum()
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovGetRecruitNum();
Exit0:
	return 0;
}

UINT32 CUser::LuaMasterGetRecruitRoleByIndex(INT32 nIndex)
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovGetRecruitRoleByIndex(nIndex);
Exit0:
	return 0;
}

INT32 CUser::LuaMasterGetSoloNum()
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovGetSoloNum();
Exit0:
	return 0;
}

UINT32 CUser::LuaMasterGetSoloRoleByIndex(INT32 nIndex)
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovGetSoloRoleByIndex(nIndex);
Exit0:
	return 0;
}

INT32 CUser::LuaMasterGetSendListNum()
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovGetSendListNum();
Exit0:
	return 0;
}

UINT32 CUser::LuaMasterGetSendRoleIDByIndex(INT32 nIndex)
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovGetSendRoleIDByIndex(nIndex);
Exit0:
	return 0;
}

INT32 CUser::LuaMasterGetRecvAppNum()
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovGetRecvNum();
Exit0:
	return 0;
}

UINT32 CUser::LuaMasterGetRecvRoleIDByIndex(INT32 nIndex)
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovGetRecvRoleIDByIndex(nIndex);
Exit0:
	return 0;
}

BOOL CUser::LuaMasterIsSendListFull()
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovIsSendListFull();
Exit0:
	return TRUE;
}

//BOOL CUser::LuaMasterIsInSendAppList(UINT32 dwRoleID)
//{
//    LOG_PROCESS_ERROR(m_poPlayingRole);
//    
//    return m_poPlayingRole->GetMaster().AsimovIsInSendAppList(dwRoleID);
//Exit0:
//    return TRUE;
//}

//BOOL CUser::LuaMasterAddSendApp(UINT32 dwRoleID)
//{
//    LOG_PROCESS_ERROR(m_poPlayingRole);
//
//    return m_poPlayingRole->GetMaster().AsimovAddSendAppList(dwRoleID);
//Exit0:
//    return FALSE;
//}
//
//BOOL CUser::LuaMasterDelSendApp(UINT32 dwRoleID)
//{
//    LOG_PROCESS_ERROR(m_poPlayingRole);
//
//    return m_poPlayingRole->GetMaster().AsimovDelSendAppList(dwRoleID);
//Exit0:
//    return FALSE;
//}

BOOL CUser::LuaMasterClearSendList()
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovClearSendAppList();
Exit0:
	return FALSE;
}

BOOL CUser::LuaMasterIsRecvListFull()
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovIsRecvListFull();
Exit0:
	return TRUE;
}

//BOOL CUser::LuaMasterIsInRecvAppList(UINT32 dwRoleID)
//{
//    LOG_PROCESS_ERROR(m_poPlayingRole);
//
//    return m_poPlayingRole->GetMaster().AsimovIsInRecvAppList(dwRoleID);
//Exit0:
//    return TRUE;
//}

//BOOL CUser::LuaMasterAddRecvApp(UINT32 dwRoleID)
//{
//    LOG_PROCESS_ERROR(m_poPlayingRole);
//
//    return m_poPlayingRole->GetMaster().AsimovAddRecvAppList(dwRoleID);
//Exit0:
//    return FALSE;
//}
//
//BOOL CUser::LuaMasterDelRecvApp(UINT32 dwRoleID)
//{
//    LOG_PROCESS_ERROR(m_poPlayingRole);
//
//    return m_poPlayingRole->GetMaster().AsimovDelRecvAppList(dwRoleID);
//Exit0:
//    return FALSE;
//}

BOOL CUser::LuaMasterClearRecvLIst()
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovClearRecvAppList();
Exit0:
	return FALSE;
}

BOOL CUser::LuaMasterCanCZTeacher()
{
    LOG_PROCESS_ERROR(m_poPlayingRole);

    return m_poPlayingRole->GetMaster().AsimovCanCZTeacher();
Exit0:
    return FALSE;
}

BOOL CUser::LuaMasterCanCZStudent(UINT32 dwRoleID)
{
    LOG_PROCESS_ERROR(m_poPlayingRole);

    return m_poPlayingRole->GetMaster().AsimovCanCZStudent(dwRoleID);
Exit0:
    return FALSE;
}

BOOL CUser::LuaMasterSetGraduateRoleID(UINT32 dwRoleID)
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovSetGraduateRoleID(dwRoleID);
Exit0:
	return FALSE;
}

UINT32 CUser::LuaMasterGetGraduateRoleID()
{
	LOG_PROCESS_ERROR(m_poPlayingRole);

	return m_poPlayingRole->GetMaster().AsimovGetGraduateRoleID();
Exit0:
	return 0;
}



//INT32 CUser::LuaGGetViewListNum()
//{
//    CUser       *poUser = NULL;
//    CGSGuild    *poGSGuild = NULL;
//    LOG_PROCESS_ERROR(m_poPlayingRole);
//
//    poGSGuild = CGuildMgr::GetInstance().FindGuild(m_poPlayingRole->GetGuildID());
//    LOG_PROCESS_ERROR(poGSGuild);
//
//    return poGSGuild->GetViewListNum();
//Exit0:
//    return 0;
//}
//
//UINT32 CUser::LuaGGetViewListGuildIDByIndex(INT32 nIndex)
//{
//    CGSGuild    *poGSGuild = NULL;
//    LOG_PROCESS_ERROR(m_poPlayingRole);
//
//    poGSGuild = CGuildMgr::GetInstance().FindGuild(m_poPlayingRole->GetGuildID());
//    LOG_PROCESS_ERROR(poGSGuild);
//
//    return poGSGuild->GetViewListGuildIDByIndex(nIndex);
//Exit0:
//    return 0;
//}


BOOL CUser::CancelCutScene(void)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_CANCEL_CUTSCENE);
	C2G_CANCEL_CUTSCENE* pMsg = (C2G_CANCEL_CUTSCENE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_cancel_cutscene;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SelectFocus(UINT32 dwCharID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_SELECT_FOCUS);
	C2G_SELECT_FOCUS* pMsg = (C2G_SELECT_FOCUS*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_select_focus;
	pMsg->dwFocusID = dwCharID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::CancelSpell(INT32 nSlot)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_ROLE_CANCEL_CAST);
	C2G_ROLE_CANCEL_CAST* pMsg = (C2G_ROLE_CANCEL_CAST*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_role_cancel_cast;
	pMsg->wSpellID = nSlot;//protocol changed, fix compile error only

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::CombatPoseSwitch(BOOL bPoseOn)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_COMBAT_POSE_SWITCH);
	C2G_COMBAT_POSE_SWITCH* pMsg = (C2G_COMBAT_POSE_SWITCH*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_combat_pose_switch;
	pMsg->byCombatPoseOn = bPoseOn;
	pMsg->byClientFlag = 0;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::CancelAura(UINT32 dwInstanceID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_CANCEL_AURA);
	C2G_CANCEL_AURA* pMsg = (C2G_CANCEL_AURA*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_cancel_aura;
	pMsg->dwInstanceID = dwInstanceID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CUser::OnMount(INT32 nMountID)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_ON_MOUNT);
	C2G_ON_MOUNT* pMsg = (C2G_ON_MOUNT*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_on_mount;
	pMsg->nMountID = nMountID;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::OffMount(void)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_OFF_MOUNT);
	C2G_OFF_MOUNT* pMsg = (C2G_OFF_MOUNT*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_off_mount;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::AdjustTargetPt(INT32 nX, INT32 nY, INT32 nZ)
{
	INT32 nRetCode = 0;
	INT32 nSize = sizeof(C2G_ROLE_ADJUST_TARGET_POINT);
	C2G_ROLE_ADJUST_TARGET_POINT* pMsg = (C2G_ROLE_ADJUST_TARGET_POINT*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_role_adjust_target_point;
	pMsg->wTargetX = nX;
	pMsg->wTargetY = nY;
	pMsg->wTargetZ = nZ;

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CUser::SendRandomMessage(void)
{
	INT32 nRetCode = 0;
	static INT32 s_nMsgCount = 0;
	static INT32 s_nMsgIDList[max_message_count] = { 0 };

	if (s_nMsgCount == 0)
	{
		for (INT32 nIndex = 0; nIndex < max_message_count; nIndex++)
		{
			if (g_nC2SMessageSize[nIndex] != 0)
			{
				s_nMsgIDList[s_nMsgCount++] = nIndex;
			}
		}
	}

	INT32 nMsgID = g_Random(s_nMsgCount);
	INT32 nSize = g_nC2SMessageSize[nMsgID];
	if (nSize == flex_message_size)
		nSize = g_Random(MAX_MESSAGE_SIZE);

	FLEX_MESSAGE_HEADER* pMsg = (FLEX_MESSAGE_HEADER*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = (UINT16)nMsgID;
	if (g_nC2SMessageSize[nMsgID] == flex_message_size)
		pMsg->wSize = (UINT16)nSize;

	for (INT32 nIndex = sizeof(MESSAGE_HEADER); nIndex < nSize; nIndex++)
	{
		((UINT8*)pMsg)[nIndex] = (UINT8)g_Random(256);
	}

	nRetCode = SendMsg((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}


