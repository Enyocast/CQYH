#include "stdafx.h"
#include "gs_message_handler.h"

#include "time_ex.h"
#include "dir.h"
#include "report.h"
#include "process_option.h"
#include "error_def.h"
#include "server_config.h"
#include "guild_config.h"
#include "version.h"
#include "dump.h"
#include "statis_info.h"

#include "g2d_message.h"
#include "d2g_message.h"
#include "g2m_message.h"
#include "m2g_message.h"
#include "g2t_message.h"
#include "t2g_message.h"
#include "o2g_message.h"
#include "g2o_message.h"
#include "common_message.h"

#include "gs_session_mgr.h"
#include "gameserver.h"

#include "game_world.h"
#include "message_handler.h"
#include "rsa_sign.h"
//#include "scenemgr.h"

#include "master_def.h"
#include "mail_def.h"
#include "statistic.h"
#include "script_mgr.h"
#include "item_mgr.h"
#include "drop_generator.h"
#include "guild_def.h"
#include "guild_mgr.h"
#include "guild_building_data.h"
#include "achievement_def.h"
#include "../3rd/toluapp/include/tolua++.h"
#include "guild_dungeon_data.h"
#include "scene_file_mgr.h"
#include "adventure.h"
#include "adventure_data.h"
#include "mail_template_data.h"
#include "money_data.h"
#include "sabac_mgr.h"
#include "./gm/gm_def.h"
#include "guild_achievement.h"

using namespace InternalMessage;
CGSMessageHandler CGSMessageHandler::ms_Instance;

void CGSMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
    LOG_PROCESS_ERROR(FALSE);
    LOG_PROCESS_ERROR(CGSSessionMgr::GetInstance().GetServerState() != sgsClosing );

Exit0:
	if (pSocketSession)
		pSocketSession->Close();

	return;
}

void CGSMessageHandler::OnConnected(ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	GS_BASE_SESSION* pBaseSession = NULL;

	LOG_PROCESS_ERROR(pSocketSession);

	pBaseSession = (GS_BASE_SESSION*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pBaseSession);

	pBaseSession->bConnected = true;
	pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nServerPingTimeout;

	switch (pBaseSession->byType)
	{
	case stGD:
        {
            INF("On GD Connected");

			pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nRegisterGuardTimeout;

			if(CGSSessionMgr::GetInstance().GetServerState() == sgsSelfReady || 
				CGSSessionMgr::GetInstance().GetServerState() == sgsAllReady)
            {
				if (CGSSessionMgr::GetInstance().GetSelfSessionID() > 0)
				{
					INF("self ready at least, DoGDRegister");

					nRetCode = DoGDRegister();
					LOG_PROCESS_ERROR(nRetCode);
				}
			}
		}
		break;
	case stMS:
        {
            INF("On MS Connected, DoMSRegister");

			nRetCode = DoMSRegister();
			LOG_PROCESS_ERROR(nRetCode);
		}
		break;
	case stDB:
        {
            INF("On DB Connected, DoDBRegister");

			nRetCode = DoDBRegister();
			LOG_PROCESS_ERROR(nRetCode);
		}
		break;
	case stDL:
        {
            INF("On DL Connected, DoDLRegister");

			nRetCode = DoDLRegister();
			LOG_PROCESS_ERROR(nRetCode);
		}
		break;
	case stGT:
        {
            INF("On GT Connected, DoGTRegister");

			GT_SESSION* pGTSession = (GT_SESSION*)pBaseSession;

			nRetCode = DoGTRegister(pGTSession->dwSessionID);
			LOG_PROCESS_ERROR(nRetCode);
		}
		break;
	default:
		LOG_PROCESS_ERROR(FALSE);
		break;
	}

	return;
Exit0:
	if (pSocketSession)
		pSocketSession->Close();

	return;
}

void CGSMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	MESSAGE_HEADER* pHeader = (MESSAGE_HEADER*)pPacketBuffer;
	LOG_PROCESS_ERROR(pHeader);

    g_ChangeStatisInfo(statInternalNetflowIncome, (INT32)dwSize);
    g_ChangeStatisInfo(statInternalPacketIncome, 1);

	LOG_PROCESS_ERROR(m_MessageFuncList[pHeader->wMsg]);
	LOG_PROCESS_ERROR(pSocketSession);

#if defined(WIN32) | defined (WIN64)
	__try
	{
		(this->*m_MessageFuncList[pHeader->wMsg])(pPacketBuffer, dwSize, pSocketSession);
	}
	__except(DumpExceptionFilter(GetExceptionInformation()))
	{
		CRI("failed to process internal message %d size %d", pHeader->wMsg, dwSize);
	}
#elif defined (__linux__)
	(this->*m_MessageFuncList[pHeader->wMsg])(pPacketBuffer, dwSize, pSocketSession);
#endif 

	m_pPacketAllocator->Free(pPacketBuffer);

	return;
Exit0:
    if (pHeader)
    	CRI("unknown internal message id %d size %d", pHeader->wMsg, dwSize);
    else
        CRI("unknown internal message with null pointer");
	if (pPacketBuffer)
		m_pPacketAllocator->Free(pPacketBuffer);
	if (pSocketSession)
		pSocketSession->Close();
	return;
}

void CGSMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
{
	INT32 nRetCode = 0;
	GS_BASE_SESSION* pBaseSession = NULL;

	LOG_PROCESS_ERROR(pSocketSession);

	pBaseSession = (GS_BASE_SESSION*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pBaseSession);

	pBaseSession->pSocketSession = NULL;

	switch (pBaseSession->byType)
	{
	case stGD:
		{
			GD_SESSION* pGDSession = (GD_SESSION*)pBaseSession;
			pGDSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;
			pGDSession->bConnected = false;
			CRI("GD disconnected");
		}
		break;
	case stMS:
		{
			MS_SESSION* pMSSession = (MS_SESSION*)pBaseSession;
			pMSSession->bConnected = false;
			pMSSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;

			if (CGSSessionMgr::GetInstance().GetServerState() != sgsInitializing && 
				CGSSessionMgr::GetInstance().GetServerState() != sgsSelfReady)
			{
				pMSSession->qwTimer = 0xFFFFFFFF;

				CRI("MS disconnected");

				CGSSessionMgr::GetInstance().SetServerState(sgsClosing);
				CGameServer::GetInstance().SetForceClose();

                CRI("Ms disconnected, now CGameWorld clean up scene");
                CGameWorld::GetInstance().CleanUpScenes();
			}
		}
		break;
	case stDB:
		{
			DB_SESSION* pDBSession = (DB_SESSION*)pBaseSession;
			pDBSession->byReady = 0;
			pDBSession->bConnected = false;
			pDBSession->qwTimer = 0xFFFFFFFF;

			CRI("DB disconnected");

			CGSSessionMgr::GetInstance().SetServerState(sgsClosing);
			CGameServer::GetInstance().SetForceClose();
		}
		break;
	case stGT:
		{
			GT_SESSION* pGTSession = (GT_SESSION*)pBaseSession;
			pGTSession->bConnected = false;
			pGTSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;
			pGTSession->dwAddr = 0;
			CRI("GT %d disconnected", pGTSession->dwSessionID);
		}
		break;
	case stDL:
		{
			DL_SESSION* pDLSession = (DL_SESSION*)pBaseSession;
			pDLSession->byReady = 0;
			pDLSession->bConnected = false;
			pDLSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nReconnectTime;
			pDLSession->dwAddr = 0;
			CRI("DL disconnected");
		}
		break;
	default:
		LOG_PROCESS_ERROR(FALSE);
		break;
	}

	return;
Exit0:
	return;
}

CGSMessageHandler::CGSMessageHandler()
{
	m_pNet = NULL;
	m_pPacketAllocator = NULL;
	m_pNotifier = NULL;
	memset(m_MessageFuncList, 0, sizeof(m_MessageFuncList));
}

CGSMessageHandler::~CGSMessageHandler()
{
	UnInit();
}

BOOL CGSMessageHandler::Init(INet* pNet, IPacketAllocator* pPacketAllocator, IMessageNotifier* pNotifier)
{
	LOG_PROCESS_ERROR(pNet);
	LOG_PROCESS_ERROR(pPacketAllocator);
	LOG_PROCESS_ERROR(pNotifier);

	m_pNet = pNet;
	m_pPacketAllocator = pPacketAllocator;
	m_pNotifier = pNotifier;

	m_MessageFuncList[a2a_ping] = &CGSMessageHandler::OnAllPing;

	m_MessageFuncList[m2g_register_ack] = &CGSMessageHandler::OnMSRegisterAck;
	m_MessageFuncList[m2a_server_info] = &CGSMessageHandler::OnMSServerInfo;
	m_MessageFuncList[m2a_all_ready] = &CGSMessageHandler::OnMSAllReady;
    m_MessageFuncList[m2a_close] = &CGSMessageHandler::OnMSClose;

	m_MessageFuncList[m2g_pre_enter_gs] = &CGSMessageHandler::OnMSPreEnterGS;
	m_MessageFuncList[m2g_enter_gs_ack] = &CGSMessageHandler::OnMSEnterGSAck;
	m_MessageFuncList[m2g_leave_gs] = &CGSMessageHandler::OnMSLeaveGS;
	m_MessageFuncList[m2g_create_scene] = &CGSMessageHandler::OnMSCreateScene;
	m_MessageFuncList[m2g_destroy_scene] = &CGSMessageHandler::OnMSDestroyScene;
	m_MessageFuncList[m2g_close_scene] = &CGSMessageHandler::OnMSCloseScene;
	m_MessageFuncList[m2g_query_scene_ack] = &CGSMessageHandler::OnMSQuerySceneAck;
	m_MessageFuncList[m2g_change_scene] = &CGSMessageHandler::OnMSChangeScene;
	m_MessageFuncList[m2g_sync_rsakey] = &CGSMessageHandler::OnMSSyncRSAKey;
	m_MessageFuncList[m2g_join_battle] = &CGSMessageHandler::OnMSJoinBattle;

	m_MessageFuncList[d2g_register_ack] = &CGSMessageHandler::OnDBRegisterAck;
	m_MessageFuncList[d2g_load_lock_role_data_ack] = &CGSMessageHandler::OnDBLoadLockRoleDataAck;
	m_MessageFuncList[d2g_unlock_role_data_ack] = &CGSMessageHandler::OnDBUnlockRoleDataAck;
	m_MessageFuncList[d2g_load_lock_role_data_fail_ack] = &CGSMessageHandler::OnDBLoadLockRoleDataFailAck;

	m_MessageFuncList[t2g_register_ack] = &CGSMessageHandler::OnGTRegisterAck;
	m_MessageFuncList[t2g_role_enter] = &CGSMessageHandler::OnGTRoleEnter;
	m_MessageFuncList[t2g_client_msg] = &CGSMessageHandler::OnGTClientMsg;

	m_MessageFuncList[m2g_team_new] = &CGSMessageHandler::OnMSTeamNew;
	m_MessageFuncList[m2g_team_add_member] = &CGSMessageHandler::OnMSTeamAddMember;
	m_MessageFuncList[m2g_team_remove_member] = &CGSMessageHandler::OnMSTeamRemoveMember;
	m_MessageFuncList[m2g_team_changeinfo] = &CGSMessageHandler::OnMSTeamChangeInfo;
	m_MessageFuncList[m2g_room_enter_dungeon] = &CGSMessageHandler::OnMSRoomEnterDungeon;

	m_MessageFuncList[m2g_change_info] = &CGSMessageHandler::OnMSChangeInfo;
	m_MessageFuncList[m2g_friend_add] = &CGSMessageHandler::OnMSFriendAdd;
	m_MessageFuncList[m2g_friend_del] = &CGSMessageHandler::OnMSFriendDel;

    m_MessageFuncList[m2g_mst_submit_teacher_app] = &CGSMessageHandler::OnMSSubmitTeacherApp;
    m_MessageFuncList[m2g_mst_agree_teacher_app] = &CGSMessageHandler::OnMSMstAgreeTeacherApp;
    m_MessageFuncList[m2g_mst_submit_stud_app] = &CGSMessageHandler::OnMSSubmitStudApp;
    m_MessageFuncList[m2g_mst_agree_stud_app] = &CGSMessageHandler::OnMSMstAgreeStudApp;
    m_MessageFuncList[m2g_mst_cz] = &CGSMessageHandler::OnMSMstCZ;
    m_MessageFuncList[m2g_mst_sync_state] = &CGSMessageHandler::OnMSMstSyncState;
    m_MessageFuncList[m2g_mst_sync_data] = &CGSMessageHandler::OnMSMstSyncData;
    m_MessageFuncList[m2g_mst_create_relation_ntf] = &CGSMessageHandler::OnMSMstCreateRelation;
    m_MessageFuncList[m2g_mst_del_relation_ntf] = &CGSMessageHandler::OnMSMstDelRelation;
    m_MessageFuncList[m2g_mst_update_data] = &CGSMessageHandler::OnMSMstUpdateData;

	m_MessageFuncList[m2g_mail_cost_check] = &CGSMessageHandler::OnMSMailCostCheck;
	m_MessageFuncList[m2g_mail_get_simple_attach] = &CGSMessageHandler::OnMSMailGetSimpleAttach;
	m_MessageFuncList[m2g_mail_get_buffer_attach] = &CGSMessageHandler::OnMSMailGetBufferAttach;

	m_MessageFuncList[m2g_call_lua_function] = &CGSMessageHandler::OnMSCallLuaFunction;

	m_MessageFuncList[m2g_pre_create_guild] = &CGSMessageHandler::OnMSPreCreateGuild;
	m_MessageFuncList[m2g_role_add_guild] = &CGSMessageHandler::OnMSRoleAddGuild;
	m_MessageFuncList[m2g_guild_add_member] = &CGSMessageHandler::OnMSGuildAddMember;
	m_MessageFuncList[m2g_guild_disband] = &CGSMessageHandler::OnMSGuildDelete;
	m_MessageFuncList[m2g_guild_del_member] = &CGSMessageHandler::OnMSGuildDelMember;
	m_MessageFuncList[m2g_sync_guild_data_ntf] = &CGSMessageHandler::OnMSGuildSyncDataNtf;
	m_MessageFuncList[m2g_guild_add_diplomat_ntf] = &CGSMessageHandler::OnMSGuildAddDiplomat;
	m_MessageFuncList[m2g_guild_del_diplomat_ntf] = &CGSMessageHandler::OnMSGuildDelDiplomat;
    m_MessageFuncList[m2g_guild_sync_attr_ntf] = &CGSMessageHandler::OnMSGuildSyncGuildAttrNtf;
    m_MessageFuncList[m2g_guild_sync_variable_ntf] = &CGSMessageHandler::OnMSGuildSyncVariableNtf;
	m_MessageFuncList[m2g_guild_draw_salary] = &CGSMessageHandler::OnMSGuildDrawSalary;
	m_MessageFuncList[m2g_guild_pre_push_item_ack] = &CGSMessageHandler::OnMSGuildPrePushItemAck;
	m_MessageFuncList[m2g_guild_pre_pop_item_ack] = &CGSMessageHandler::OnMSGuildPrePopItemAck;
	m_MessageFuncList[m2g_guild_pop_item_ack] = &CGSMessageHandler::OnMSGuildPopItemAck;
    m_MessageFuncList[m2g_guild_upgrade_building_ntf] = &CGSMessageHandler::OnMSGuildUpgradeBuildingNtf;
	m_MessageFuncList[m2g_guild_update_building_ntf] = &CGSMessageHandler::OnMSGuildUpdateBuildingLevel;
    m_MessageFuncList[m2g_guild_del_building_ntf] = &CGSMessageHandler::OnMSGuildDelBuilding;   
    m_MessageFuncList[m2g_guild_sync_building_state_ntf] = &CGSMessageHandler::OnMSGuildSyncBuildingStateNtf;
	m_MessageFuncList[m2g_guild_update_welfare_ntf] = &CGSMessageHandler::OnMSGuildUpdateWelfareID;
    m_MessageFuncList[m2g_guild_update_state_ntf] = &CGSMessageHandler::OnMSGuildUpdateState;
    m_MessageFuncList[m2g_guild_change_position_ntf] = &CGSMessageHandler::OnMSGuildChangePosition;
    m_MessageFuncList[m2g_guild_pre_open_dungeon_ack] = &CGSMessageHandler::OnMSGuildPreOpenDungeonAck;
    m_MessageFuncList[m2g_guild_enter_dungeon] = &CGSMessageHandler::OnMSGuildEnterDungeon;
    m_MessageFuncList[m2g_guild_sync_war_relation] = &CGSMessageHandler::OnMSGuildSyncWarRelation;
    m_MessageFuncList[m2g_guild_sync_war_char] = &CGSMessageHandler::OnMSGuildSyncWarCharacter;
    m_MessageFuncList[m2g_guild_change_res_ack] = &CGSMessageHandler::OnMSGuildChangeResAck;
    m_MessageFuncList[m2g_guild_war_end] = &CGSMessageHandler::OnMSGuildWarEnd;
    
    m_MessageFuncList[m2g_guild_sync_member_salary_ntf] = &CGSMessageHandler::OnMSGuildSyncMemberSalaryNtf;
	m_MessageFuncList[m2g_sync_role_social_data] = &CGSMessageHandler::OnMSSyncRoleSocialData;
    m_MessageFuncList[m2g_guild_achievement_reward] = &CGSMessageHandler::OnMSGuildAchievementReward;
	m_MessageFuncList[m2g_enroll_sabac] = &CGSMessageHandler::OnMSEnrollSabac;
	m_MessageFuncList[m2g_occupy_sabac] = &CGSMessageHandler::OnMSOccupySabac;

    m_MessageFuncList[m2g_jump_arena_scene] = &CGSMessageHandler::OnMSJumpArenaScene;
    m_MessageFuncList[m2g_arena_reward] = &CGSMessageHandler::OnMSArenaReward;

	m_MessageFuncList[m2g_shield] = &CGSMessageHandler::OnMSShield;
    m_MessageFuncList[m2g_sync_gm_data] = &CGSMessageHandler::OnMSSyncGMData;

	m_MessageFuncList[m2g_call_gm_command] = &CGSMessageHandler::OnMSCallGsGMCommand;

	m_MessageFuncList[m2g_drop_limit] = &CGSMessageHandler::OnMSDropLimit;

	// auction 交易行
	m_MessageFuncList[m2g_auction_sell] = &CGSMessageHandler::OnMSAuctionSell;
	m_MessageFuncList[m2g_auction_buy] = &CGSMessageHandler::OnMSAuctionBuy;
	m_MessageFuncList[m2g_auction_pay] = &CGSMessageHandler::OnMSAuctionPay;

    m_MessageFuncList[m2g_exchange_add_order] = &CGSMessageHandler::OnMSExchangeAddOrder;

    m_MessageFuncList[m2g_complete_achievement] = &CGSMessageHandler::OnMSCompleteAchievement;

    m_MessageFuncList[m2g_adventure_reward] = &CGSMessageHandler::OnMSAdventureReward;
    m_MessageFuncList[m2g_query_role_location] = &CGSMessageHandler::OnMSQueryRoleLocation;
    m_MessageFuncList[m2g_query_role_location_ack] = &CGSMessageHandler::OnMSQueryRoleLocationAck;
    m_MessageFuncList[m2g_take_role] = &CGSMessageHandler::OnMSTakeRole;
	m_MessageFuncList[m2g_arrest_role] = &CGSMessageHandler::OnMSArrestRole;

    m_MessageFuncList[m2g_fcm_state] = &CGSMessageHandler::OnMSFcmState;

    m_MessageFuncList[m2g_free_mode] = &CGSMessageHandler::OnMSFreeMode;
    m_MessageFuncList[m2g_award] = &CGSMessageHandler::OnMSAward;
	m_MessageFuncList[m2g_spawn_npc] = &CGSMessageHandler::OnMSSpawnNpc;
    m_MessageFuncList[m2g_update_statistic_value] = &CGSMessageHandler::OnMSUpdateStatisticVariable;

	m_MessageFuncList[m2g_sync_server_variable] = &CGSMessageHandler::OnMSSyncServerVariable;
	m_MessageFuncList[m2g_update_server_variable] = &CGSMessageHandler::OnMSUpdateServerVariable;

	m_MessageFuncList[m2g_update_average_level] = &CGSMessageHandler::OnMSUpdateAverageLevel;

    m_MessageFuncList[m2g_get_black_market_limit_info] = &CGSMessageHandler::OnMSGetBlackMarketLimitInfo;
    m_MessageFuncList[m2g_check_black_market_product] = &CGSMessageHandler::OnMSCheckBlackMarketProduct;

    m_MessageFuncList[m2g_add_exercise_time] = &CGSMessageHandler::OnMSAddExerciseTime;

	// 下面新加代码
	m_MessageFuncList[m2g_query_real_money_req] = &CGSMessageHandler::OnMSQueryRealMoneyRole;
	m_MessageFuncList[m2g_real_money_buy_success] = &CGSMessageHandler::OnMSRealMoneyBuySuccess;
    m_MessageFuncList[m2g_role_real_money_shop_buy_item_req] = &CGSMessageHandler::OnMSRoleRealMoneyShopBuyItemReq;
    m_MessageFuncList[m2g_custom_role_buy_time] = &CGSMessageHandler::OnMSCustomRoleBuyTimeReq;

	m_MessageFuncList[o2g_register_ack] = &CGSMessageHandler::OnDLRegisterAck;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CGSMessageHandler::UnInit(void)
{

	return TRUE;
}

CGSMessageHandler& CGSMessageHandler::GetInstance(void)
{
	return ms_Instance;
}

inline BOOL CGSMessageHandler::_SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	GD_SESSION& rGDSession = CGSSessionMgr::GetInstance().GetGDSession();
	LOG_PROCESS_ERROR(rGDSession.bConnected);
	LOG_PROCESS_ERROR(rGDSession.pSocketSession);

	nRetCode = rGDSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

    g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
    g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CGSMessageHandler::_SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	MS_SESSION& rMSSession = CGSSessionMgr::GetInstance().GetMSSession();
	LOG_PROCESS_ERROR(rMSSession.bConnected);
	LOG_PROCESS_ERROR(rMSSession.pSocketSession);

	nRetCode = rMSSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

    g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
    g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CGSMessageHandler::_SendDB(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	DB_SESSION& rDBSession = CGSSessionMgr::GetInstance().GetDBSession();
	LOG_PROCESS_ERROR(rDBSession.bConnected);
	LOG_PROCESS_ERROR(rDBSession.pSocketSession);

	nRetCode = rDBSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

    g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
    g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CGSMessageHandler::_SendDL(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	if(g_ServerConfig.MS.nInitDLCount > 0)
	{
		DL_SESSION& rDLSession = CGSSessionMgr::GetInstance().GetDLSession();
		LOG_PROCESS_ERROR(rDLSession.bConnected);
		LOG_PROCESS_ERROR(rDLSession.pSocketSession);

		nRetCode = rDLSession.pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
		LOG_PROCESS_ERROR(nRetCode == dwSize);

        g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
        g_ChangeStatisInfo(statInternalPacketOutgoing, 1);
    }
	else
	{
		if(pPacketBuffer)
			m_pPacketAllocator->Free(pPacketBuffer);
	}

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CGSMessageHandler::_SendGT(UINT32 dwGTSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	GT_SESSION* pGTSession = CGSSessionMgr::GetInstance().GetGTSession(dwGTSessionID);
	LOG_PROCESS_ERROR(pGTSession);
	LOG_PROCESS_ERROR(pGTSession->bConnected);
	LOG_PROCESS_ERROR(pGTSession->pSocketSession);

	nRetCode = pGTSession->pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

    g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
    g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;
}

/************************************************************************/
// To All
BOOL CGSMessageHandler::DoAllPing(void)
{
	INT32 nRetCode = 0;
	A2A_PING* pMsg = NULL;

	if (CGSSessionMgr::GetInstance().GetGDSession().bConnected)
	{
		pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
		LOG_PROCESS_ERROR(pMsg);

		pMsg->wMsg = a2a_ping;

		nRetCode = _SendGD((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
		LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
		pMsg = NULL;
	}

	if (CGSSessionMgr::GetInstance().GetMSSession().bConnected)
	{
		pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
		LOG_PROCESS_ERROR(pMsg);

		pMsg->wMsg = a2a_ping;

		nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
	}

	if (CGSSessionMgr::GetInstance().GetDBSession().bConnected)
	{
		pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
		LOG_PROCESS_ERROR(pMsg);

		pMsg->wMsg = a2a_ping;

		nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
	}

	if (CGSSessionMgr::GetInstance().GetDLSession().bConnected)
	{
		pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
		LOG_PROCESS_ERROR(pMsg);

		pMsg->wMsg = a2a_ping;

		nRetCode = _SendDL((PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
        LOG_CHECK_ERROR(nRetCode);

        if (!nRetCode)
            m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
        pMsg = NULL;
	}

	for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
	{
		GT_SESSION* pGTSession = CGSSessionMgr::GetInstance().GetGTSession(nIndex);
		if (pGTSession && pGTSession->bConnected)
		{
			pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
			LOG_PROCESS_ERROR(pMsg);

			pMsg->wMsg = a2a_ping;

			nRetCode = _SendGT(pGTSession->dwSessionID, (PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
            LOG_CHECK_ERROR(nRetCode);

            if (!nRetCode)
                m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
            pMsg = NULL;
		}
	}

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}
/************************************************************************/
// To GD
BOOL CGSMessageHandler::DoGDRegister(void)
{
	INT32 nRetCode = 0;

	A2U_REGRISTER* pMsg = (A2U_REGRISTER*)m_pPacketAllocator->Alloc(sizeof(A2U_REGRISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = a2u_regrister;
	pMsg->byType = stGS;
	pMsg->bySessionID =  (UINT8)CGSSessionMgr::GetInstance().GetSelfSessionID();
	pMsg->dwProcessID = GetCurrentProcessId();

	nRetCode = _SendGD((PACKET_BUFFER*)pMsg, sizeof(A2U_REGRISTER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoGDNotify(UINT8 byLevel, const char* szContent, ...)
{
	INT32 nRetCode = 0;
	char szInfo[4096] = { 0 };
	va_list valist;
	va_start(valist, szContent);
	vsnprintf(szInfo, sizeof(szInfo), szContent, valist);
	va_end(valist);

	INT32 nSize = sizeof(A2U_NOTIFY) + strlen(szInfo) + 1;

	A2U_NOTIFY* pMsg = (A2U_NOTIFY*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = a2u_notify;
	pMsg->bySvrType = stGS;
	pMsg->bySvrID = (UINT8)CGSSessionMgr::GetInstance().GetSelfSessionID();
	pMsg->byLevel = byLevel;
	pMsg->nErrorCode = errCritical;
	strxcpy(pMsg->szContent, szInfo, strlen(szInfo) + 1);

	nRetCode = _SendGD((PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// To MS
BOOL CGSMessageHandler::DoMSRegister(void)
{
	INT32 nRetCode = 0;
	INT32 nDataCount = CGlobalDataManager::GetInstance().GetDataCount();

	G2M_REGISTER* pMsg = (G2M_REGISTER*)m_pPacketAllocator->Alloc(sizeof(G2M_REGISTER) + nDataCount * sizeof(UINT32));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_register;
	CGlobalDataManager::GetInstance().GetDataCRC(pMsg->dwCRCList);

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_REGISTER) + nDataCount * sizeof(UINT32));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSReady(void)
{
	INT32 nRetCode = 0;

	G2M_READY* pMsg = (G2M_READY*)m_pPacketAllocator->Alloc(sizeof(G2M_READY));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_ready;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_READY));
	LOG_PROCESS_ERROR(nRetCode);

	CGSSessionMgr::GetInstance().SetServerState(sgsSelfReady);

	INF("GS %d is self ready", CGSSessionMgr::GetInstance().GetSelfSessionID());

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSCloseBeginAck(void)
{
	INT32 nRetCode = 0;

	G2M_CLOSE_ACK* pMsg = (G2M_CLOSE_ACK*)m_pPacketAllocator->Alloc(sizeof(G2M_CLOSE_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_close_ack;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_CLOSE_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSPreEnterGSAck(UINT32 dwClientSessionID, UINT32 dwRoleID, INT32 nErrCode)
{
	INT32 nRetCode = 0;

	G2M_PRE_ENTER_GS_ACK* pMsg = (G2M_PRE_ENTER_GS_ACK*)m_pPacketAllocator->Alloc(sizeof(G2M_PRE_ENTER_GS_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_pre_enter_gs_ack;
	pMsg->dwClientSessionID = dwClientSessionID;
	pMsg->dwRoleID = dwRoleID;
	pMsg->nErrCode = nErrCode;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_PRE_ENTER_GS_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSEnterGS(UINT32 dwClientSessionID, UINT32 dwRoleID, INT64 llMasterExp, UINT32 dwMasterCD, UINT32 dwGuildCD, UINT8 byGMLevel, UINT8 byTwitter, UINT32 dwMasterTwitterCD, const char* szSignature)
{
	INT32 nRetCode = 0;

	G2M_ENTER_GS* pMsg = (G2M_ENTER_GS*)m_pPacketAllocator->Alloc(sizeof(G2M_ENTER_GS));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_enter_gs;
	pMsg->dwClientSessionID = dwClientSessionID;
	pMsg->dwRoleID = dwRoleID;
	pMsg->llMasterExp = llMasterExp;
    pMsg->dwMasterCD = dwMasterCD;
    pMsg->dwGuildCD = dwGuildCD;
    pMsg->byGMLevel = byGMLevel;
    pMsg->byTwitter = byTwitter;
    pMsg->dwMasterTwitterCD = dwMasterTwitterCD;
	strxcpy(pMsg->szSignature, szSignature, SIGNATURE_LEN);

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_ENTER_GS));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSLeaveGSAck(UINT32 dwClientSessionID, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;

	G2M_LEAVE_GS_ACK* pMsg = (G2M_LEAVE_GS_ACK*)m_pPacketAllocator->Alloc(sizeof(G2M_LEAVE_GS_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_leave_gs_ack;
	pMsg->dwClientSessionID = dwClientSessionID;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_LEAVE_GS_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSCreateSceneAck(UINT8 byGroupID, INT32 nSceneTempID, INT32 nSceneID, INT32 nErrCode)
{
	INT32 nRetCode = 0;

	G2M_CREATE_SCENE_ACK* pMsg = (G2M_CREATE_SCENE_ACK*)m_pPacketAllocator->Alloc(sizeof(G2M_CREATE_SCENE_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_create_scene_ack;
	pMsg->byGroupID = byGroupID;
	pMsg->nSceneTempID = nSceneTempID;
	pMsg->nSceneID = nSceneID;
	pMsg->nErrCode = nErrCode;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_CREATE_SCENE_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSDestroySceneAck(UINT8 byGroupID, INT32 nSceneTempID, INT32 nSceneID, INT32 nErrCode)
{
	INT32 nRetCode = 0;

	G2M_DESTROY_SCENE_ACK* pMsg = (G2M_DESTROY_SCENE_ACK*)m_pPacketAllocator->Alloc(sizeof(G2M_DESTROY_SCENE_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_destroy_scene_ack;
	pMsg->byGroupID = byGroupID;
	pMsg->nSceneTempID = nSceneTempID;
	pMsg->nSceneID = nSceneID;
	pMsg->nErrCode = nErrCode;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_DESTROY_SCENE_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSMailCostCheck(INT32 nResult, void* params)
{
	INT32 nRetCode = 0;
	M2G_MAIL_COST_CHECK* pOriginalMsg = (M2G_MAIL_COST_CHECK*)params;
	G2M_MAIL_COST_CHECK* pMsg = (G2M_MAIL_COST_CHECK*)m_pPacketAllocator->Alloc(sizeof(G2M_MAIL_COST_CHECK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_mail_cost_check;
	pMsg->nResult = nResult;
	pMsg->dwSenderRoleID = pOriginalMsg->dwSenderRoleID;
	pMsg->dwReceiverRoleID = pOriginalMsg->dwReceiverRoleID;
	strxcpy(pMsg->szMailSubject, pOriginalMsg->szMailSubject, MAIL_SUBJECT_LEN);
	strxcpy(pMsg->szMailContent, pOriginalMsg->szMailContent, MAIL_CONTENT_LEN);

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_MAIL_COST_CHECK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSMailGetAttach(INT32 nResult, UINT32 dwMailID)
{
	INT32 nRetCode = 0;
	G2M_MAIL_GET_ATTACH* pMsg = (G2M_MAIL_GET_ATTACH*)m_pPacketAllocator->Alloc(sizeof(G2M_MAIL_GET_ATTACH));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_mail_get_attach;
	pMsg->nResult = nResult;
	pMsg->dwMailID = dwMailID;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_MAIL_GET_ATTACH));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSPreCreateGuildAck(INT32 nResult, UINT32 dwRoleID, const char *pcszGuildName)
{
	INT32   nRetCode = 0;

	G2M_PRE_CREATE_GUILD_ACK *pMsg = (G2M_PRE_CREATE_GUILD_ACK*)m_pPacketAllocator->Alloc(sizeof(G2M_PRE_CREATE_GUILD_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_pre_create_guild_ack;
	pMsg->nResult = nResult;
	pMsg->dwRoleID = dwRoleID;
	strxcpy(pMsg->szName, pcszGuildName, GUILD_NAME_LEN);

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_PRE_CREATE_GUILD_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSQueryRoleLocationAck(UINT32 dwClientSessionID, UINT32 dwRoleID, 
	INT32 nSceneTempID, INT32 nSceneID, INT32 nX, INT32 nY, INT32 nZ, BOOL bFromItem)
{
    INT32   nRetCode = 0;

    G2M_QUERY_ROLE_LOCATION_ACK *pMsg = (G2M_QUERY_ROLE_LOCATION_ACK*)m_pPacketAllocator->Alloc(sizeof(G2M_QUERY_ROLE_LOCATION_ACK));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2m_query_role_location_ack;
    pMsg->dwClientSessionID = dwClientSessionID;
    pMsg->dwRoleID = dwRoleID;
    pMsg->nSceneTempID = nSceneTempID;
    pMsg->nSceneID = nSceneID;
    pMsg->nX = nX;
    pMsg->nY = nY;
    pMsg->nZ = nZ;
	pMsg->bFromItem = (UINT8)bFromItem;

    nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_QUERY_ROLE_LOCATION_ACK));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CGSMessageHandler::DoMSGMLog(UINT32 dwTime, UINT32 dwRoleID, INT32 nResult, const char *pcszCmd)
{
    INT32   nRetCode = 0;
    INT32   nCmdLength = 0;
    G2M_GM_LOG *pMsg = NULL;

    LOG_PROCESS_ERROR(pcszCmd);

    pMsg = (G2M_GM_LOG*)m_pPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    nCmdLength = strlen(pcszCmd) + 1;
    pMsg->wMsg = g2m_gm_log;
    pMsg->dwTime = dwTime;
    pMsg->dwRoleID = dwRoleID;
    pMsg->nResult = nResult;
    strxcpy(pMsg->szGMCmd, pcszCmd, nCmdLength);


    nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_GM_LOG) + nCmdLength);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CGSMessageHandler::DoMSQueryRealMoneyRole(UINT32 dwClientSessionID, UINT32 dwRoleID, INT64 llRealMoney)
{
	INT32 nRetCode = 0;
	G2M_QUERY_REAL_MONEY_ACK* pMsg = (G2M_QUERY_REAL_MONEY_ACK*)m_pPacketAllocator->Alloc(sizeof(G2M_QUERY_REAL_MONEY_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_query_real_money_ack;
	pMsg->dwCliSessionID = dwClientSessionID;
	pMsg->dwRoleID = dwRoleID;
	pMsg->llRealMoney = llRealMoney;

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_QUERY_REAL_MONEY_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoMSRoleRealMoneyShopBuyItemAck(UINT32 dwClientSessionID, INT32 nResult, UINT32 dwRoleID, INT32 nItemID, INT32 nItemCount, CHAR* pcszRoleName)
{
	INT32 nRetCode = 0;

	G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK* pMsg = (G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK*)m_pPacketAllocator->Alloc(sizeof(G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2m_role_rela_money_shop_buy_item_ack;
	pMsg->nResult = 0;
	pMsg->dwCliSessionID = dwClientSessionID;
	pMsg->dwRoleID = dwRoleID;
	pMsg->nItemID = nItemID;
	pMsg->nItemCount = nItemCount;
	strxcpy(pMsg->szRoleName, pcszRoleName, ROLE_NAME_LEN);

	nRetCode = _SendMS((PACKET_BUFFER*)pMsg, sizeof(G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// To DB

BOOL CGSMessageHandler::DoDBRegister(void)
{
	INT32 nRetCode = 0;

	G2D_REGISTER* pMsg = (G2D_REGISTER*)m_pPacketAllocator->Alloc(sizeof(G2D_REGISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2d_register;
	pMsg->dwGSSessionID = CGSSessionMgr::GetInstance().GetSelfSessionID();

	nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(G2D_REGISTER), 0);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoDBLoadLockRoleData(UINT32 dwClientSessionID, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;

	G2D_LOAD_LOCK_ROLE_DATA* pMsg = (G2D_LOAD_LOCK_ROLE_DATA*)m_pPacketAllocator->Alloc(sizeof(G2D_LOAD_LOCK_ROLE_DATA));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2d_load_lock_role_data;
	pMsg->dwRoleID = dwRoleID;
	pMsg->dwClientSessionID = dwClientSessionID;

	nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(G2D_LOAD_LOCK_ROLE_DATA), 0);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoDBSaveRoleData(CRole* poRole, BOOL bSaveToFile)
{
	INT32 nRetCode = 0;
	FILE* pFile = NULL;

	G2D_SAVE_ROLE_DATA* pMsg = (G2D_SAVE_ROLE_DATA*)m_pPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
	LOG_PROCESS_ERROR(pMsg);

	LOG_PROCESS_ERROR(poRole);

	pMsg->wMsg = g2d_save_role_data;
	pMsg->dwClientSessionID = poRole->GetSessionID();
	pMsg->dwRoleID = poRole->GetObjID();

	nRetCode = poRole->Save(pMsg->RoleData, pMsg->dwDataSize);
	LOG_PROCESS_ERROR(nRetCode);

	if (bSaveToFile)
	{
		char szFileName[PATH_LEN];

		g_CreateDirectory("Log", TRUE);
		g_CreateDirectory("Log/RoleDump", TRUE);

		snprintf(szFileName, PATH_LEN, "Log/RoleDump/%lld", CGameServer::GetInstance().GetStartTick());
		g_CreateDirectory(szFileName, TRUE);

		snprintf(szFileName, PATH_LEN, "Log/RoleDump/%lld/%d.dat", CGameServer::GetInstance().GetStartTick(), poRole->GetObjID());
		pFile = fopen(szFileName, "wb");

		nRetCode = (INT32)fwrite(pMsg->RoleData, pMsg->dwDataSize, 1, pFile);
		LOG_CHECK_ERROR(nRetCode == pMsg->dwDataSize);

		fclose(pFile);
		pFile = NULL;
	}

	nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(G2D_SAVE_ROLE_DATA) + pMsg->dwDataSize);
	LOG_PROCESS_ERROR(nRetCode);

	poRole->UpdateLastSaveFrame();
	CGameWorld::GetInstance().PushToSaveListRear(poRole);

	return TRUE;
Exit0:
	if (poRole)
		CRI("failed to save role %d session <%08X>", poRole->GetObjID(), poRole->GetSessionID());
	else
		CRI("failed to save null role");

	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	if (pFile)
		fclose(pFile);
	return FALSE;
}

BOOL CGSMessageHandler::DoDBUnlockRoleData(CRole* poRole)
{
	INT32 nRetCode = 0;

	G2D_UNLOCK_ROLE_DATA* pMsg = (G2D_UNLOCK_ROLE_DATA*)m_pPacketAllocator->Alloc(sizeof(G2D_UNLOCK_ROLE_DATA));
	LOG_PROCESS_ERROR(pMsg);

	LOG_PROCESS_ERROR(poRole);

	pMsg->wMsg = g2d_unlock_role_data;
	pMsg->dwClientSessionID = poRole->GetSessionID();
	pMsg->dwRoleID = poRole->GetObjID();

	nRetCode = _SendDB((PACKET_BUFFER*)pMsg, sizeof(G2D_UNLOCK_ROLE_DATA));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// To GT

BOOL CGSMessageHandler::DoGTRegister(UINT32 dwGTSessionID)
{
	INT32 nRetCode = 0;

	G2T_REGISTER* pMsg = (G2T_REGISTER*)m_pPacketAllocator->Alloc(sizeof(G2T_REGISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2t_register;
	pMsg->dwGSSessionID = CGSSessionMgr::GetInstance().GetSelfSessionID();

	nRetCode = _SendGT(dwGTSessionID, (PACKET_BUFFER*)pMsg, sizeof(G2T_REGISTER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoGTReturnSelectRole(UINT32 dwCliSessionID)
{
	INT32 nRetCode = 0;

	G2T_RETURN_ROLE_SELECT* pMsg = (G2T_RETURN_ROLE_SELECT*)m_pPacketAllocator->Alloc(sizeof(G2T_RETURN_ROLE_SELECT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2t_return_role_select;
	pMsg->dwClientSessionID = dwCliSessionID;

	nRetCode = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwCliSessionID), (PACKET_BUFFER*)pMsg, sizeof(G2T_RETURN_ROLE_SELECT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CGSMessageHandler::DoGTCloseClientSession(UINT32 dwCliSessionID, BOOL bLogout)
{
	INT32 nRetCode = 0;

	G2T_CLOSE_CLIENT_SESSION* pMsg = (G2T_CLOSE_CLIENT_SESSION*)m_pPacketAllocator->Alloc(sizeof(G2T_CLOSE_CLIENT_SESSION));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2t_close_client_session;
	pMsg->dwClientSessionID = dwCliSessionID;
	pMsg->byLogout = bLogout;

	nRetCode = _SendGT(GET_GT_INDEX_FROM_SESSION_ID(dwCliSessionID), (PACKET_BUFFER*)pMsg, sizeof(G2T_CLOSE_CLIENT_SESSION));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoDLRegister()
{
	INT32 nRetCode = 0;

	G2O_REGISTER* pMsg = (G2O_REGISTER*)m_pPacketAllocator->Alloc(sizeof(G2O_REGISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2o_register;
	pMsg->dwGSSessionID = CGSSessionMgr::GetInstance().GetSelfSessionID();

	nRetCode = _SendDL((PACKET_BUFFER*)pMsg, sizeof(G2O_REGISTER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoDLCreateScene(UINT32 dwTime, INT32 nGroupID, INT32 nSceneID, INT32 nSceneTemplateID)
{
	INT32 nRetCode = 0;

	G2O_CREATE_SCENE* pMsg = (G2O_CREATE_SCENE*)m_pPacketAllocator->Alloc(sizeof(G2O_CREATE_SCENE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2o_create_scene;

	pMsg->dwTime = dwTime;
	pMsg->nGroupID = nGroupID;

	pMsg->nSceneID = nSceneID;
	pMsg->nTemplateID = nSceneTemplateID;

	nRetCode = _SendDL((PACKET_BUFFER*)pMsg, sizeof(G2O_CREATE_SCENE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CGSMessageHandler::DoDLDestoryScene(UINT32 dwTime, INT32 nGroupID, INT32 nSceneID, INT32 nSceneTemplateID)
{
	INT32 nRetCode = 0;

	G2O_DESTORY_SCENE* pMsg = (G2O_DESTORY_SCENE*)m_pPacketAllocator->Alloc(sizeof(G2O_DESTORY_SCENE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2o_destory_scene;

	pMsg->dwTime = dwTime;
	pMsg->nGroupID = nGroupID;

	pMsg->nTemplateID = nSceneTemplateID;
	pMsg->nSceneID = nSceneID;

	nRetCode = _SendDL((PACKET_BUFFER*)pMsg, sizeof(G2O_DESTORY_SCENE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

/************************************************************************/
// From All
void CGSMessageHandler::OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	GS_BASE_SESSION* pBaseSession = (GS_BASE_SESSION*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pBaseSession);

	if(pBaseSession->byType == stGD)
		pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nPingGuardTimeout;
	else
		pBaseSession->qwTimer = GetTickCountEx() + g_ServerConfig.Common.nServerPingTimeout;


	return;
Exit0:
	if (pSocketSession)
		pSocketSession->Close();

	return;
}

/************************************************************************/
// From MS
void CGSMessageHandler::OnMSRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	M2G_REGISTER_ACK* pMsg = (M2G_REGISTER_ACK*)pPacketBuffer;
	CGSSessionMgr::GetInstance().SetSelfSessionID(pMsg->dwGSSessionID);
	INF("GS %d registered to MS", pMsg->dwGSSessionID);

	CGameWorld::GetInstance().SetGsSessionID(pMsg->dwGSSessionID);

	g_InitReportSetting(GetServerShortName(stGS), pMsg->dwGSSessionID, g_ServerConfig.Common.szReportAbsolutePath);

#if defined(WIN32)
	{
		char szTitle[1024];
#ifdef _FINAL
		snprintf(szTitle, 1024, "Game Server %d, ver %d.%d.%d final", pMsg->dwGSSessionID, MAJOR_VERSION, MINOR_VERSION, BUILD_NUMBER);
#else
		snprintf(szTitle, 1024, "Game Server %d, ver %d.%d.%d", pMsg->dwGSSessionID, MAJOR_VERSION, MINOR_VERSION, BUILD_NUMBER);
#endif	// _FINAL
		SetConsoleTitle(szTitle);
		INF(szTitle);
	}
#endif  // WIN32

}

void CGSMessageHandler::OnMSServerInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2A_SERVER_INFO* pMsg = (M2A_SERVER_INFO*)pPacketBuffer;

	DB_SESSION& rDBSession = CGSSessionMgr::GetInstance().GetDBSession();
	rDBSession.dwAddr = pMsg->DB.dwAddr;
	rDBSession.wPort = pMsg->DB.wPort;

	DL_SESSION& rDLSession = CGSSessionMgr::GetInstance().GetDLSession();
	rDLSession.dwAddr = pMsg->DL.dwAddr;
	rDLSession.wPort = pMsg->DL.wPort;

	for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
	{
		GT_SESSION* pGTSession = CGSSessionMgr::GetInstance().GetGTSession(nIndex);
		LOG_PROCESS_ERROR(pGTSession);

		pGTSession->dwAddr = pMsg->GT[nIndex].dwAddr;
		pGTSession->wPort = pMsg->GT[nIndex].wPort;
		if(pGTSession->wPort > 0)
		{
			in_addr stAddr;
			stAddr.s_addr = pGTSession->dwAddr;
		}
	}

Exit0:
	return;
}

void CGSMessageHandler::OnMSAllReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	{
		INT64 llTotalSize = 0;
		llTotalSize += CGameWorld::GetInstance().PrintMemoryStat();
		llTotalSize += CScriptMgr::GetInstance().PrintMemoryStat();
		llTotalSize += CGlobalDataManager::GetInstance().PrintMemoryStat();
		llTotalSize += CGameServer::GetInstance().GetNetInterface()->PrintMemoryStat();

		INF("total memory allocated %.2fMB", llTotalSize / (1024 * 1024.0f));
	}

	CGSSessionMgr::GetInstance().SetServerState(sgsAllReady);
	INF("all servers are ready");
}

void CGSMessageHandler::OnMSClose(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	CGSSessionMgr::GetInstance().SetServerState(sgsClosing);
	INF("GS %d is closing", CGSSessionMgr::GetInstance().GetSelfSessionID());
}

// 进入游戏, new Role 对象
void CGSMessageHandler::OnMSPreEnterGS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	CRole* poRole = NULL;
	CScene* poScene = NULL;
	UINT32 dwClientSessionID = 0;
	const ZONE_DATA* pcZoneData = NULL;
	const GRID_DATA* pcGridData = NULL;
	GRID_INSTANCE_DATA* pGridInstance = NULL;
	CRegion* poRegion = NULL;
	M2G_PRE_ENTER_GS* pMsg = (M2G_PRE_ENTER_GS*)pPacketBuffer;

	LOG_PROCESS_ERROR(CGSSessionMgr::GetInstance().GetServerState() == sgsAllReady);

	poRole = CGameWorld::GetInstance().NewRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole != NULL);

	nRetCode = poRole->Init(pMsg->dwRoleID, pMsg->dwCliSessionID);
	LOG_PROCESS_ERROR(nRetCode);

    poRole->SetFcmState(pMsg->byFcmState);
    poRole->SetX(pMsg->nDestX);
	poRole->SetY(pMsg->nDestY);
	poRole->SetZ(pMsg->nDestZ);
	poRole->SetFaceDirection(pMsg->wFaceDirection);
	poRole->SetIpWhiteList(pMsg->bIpWhiteList);
	poRole->SetUserWhiteList(pMsg->bUserWhiteList);
	poRole->SetIpAddr(pMsg->dwIpAddr);

	poRole->SetSceneTempID(pMsg->nSceneTempID);
	poRole->SetSceneID(pMsg->nSceneID);
	poRole->SetState(rsPreEntered);

	dwClientSessionID = poRole->GetSessionID();
	poScene = CGameWorld::GetInstance().FindScene(MakeSceneObjID(pMsg->nSceneTempID, pMsg->nSceneID));
	LOG_PROCESS_ERROR(poScene);

	nRetCode = poScene->FindValidPos(poRole, TRUE, pcZoneData, pcGridData, pGridInstance, poRegion);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CGSSessionMgr::GetInstance().AttachRoleToSession(pMsg->dwCliSessionID, poRole);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = DoMSPreEnterGSAck(pMsg->dwCliSessionID, pMsg->dwRoleID, errSuccess);
	LOG_PROCESS_ERROR(nRetCode);

	GS_SYS_LOG_SUCCESS(poRole);
	return;
Exit0:
	GS_SYS_LOG_ERROR(poRole);

	nRetCode = DoMSPreEnterGSAck(pMsg->dwCliSessionID, pMsg->dwRoleID, errUnknownError);
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CGSSessionMgr::GetInstance().DetachRoleFromSession(pMsg->dwCliSessionID);
	LOG_CHECK_ERROR(nRetCode);

	if(poRole)
	{
		nRetCode = poRole->UnInit();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = CGameWorld::GetInstance().DelRole(poRole);
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
}

// 人物上线, 进入游戏 同步各种数据
void CGSMessageHandler::OnMSEnterGSAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_ENTER_GS_ACK* pMsg = (M2G_ENTER_GS_ACK*)pPacketBuffer;
	CRole* poRole = NULL;

	// 必然能找到Role，否则有BUG
	poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwClientSessionID);
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetState() == rsWaitMSApprove);
	LOG_PROCESS_ERROR(poRole->GetObjID() == pMsg->dwRoleID);

	if (!poRole->IsInJump())
	{
		nRetCode = CCliMessageHandler::GetInstance().DoSyncGameDataBegin(poRole);
		LOG_PROCESS_ERROR(nRetCode);

#if !defined(_ROBOT) & !defined(_FINAL)
        if (g_GWConfig.DebugOption.bShowErrorDialog)
        {
            nRetCode = CCliMessageHandler::GetInstance().DoSyncDataError(poRole);
            LOG_PROCESS_ERROR(nRetCode);
        }
#endif

		nRetCode = CCliMessageHandler::GetInstance().DoSyncAchievementList(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncSpellBook(poRole);
		LOG_PROCESS_ERROR(nRetCode);

        nRetCode = CCliMessageHandler::GetInstance().DoSyncRefineLevels(poRole);
        LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncMoney(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncContainerSizes(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncItemBag(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncQuestList(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncDailyQuest(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncReputation(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncSpellSlot(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncFriendGroupName(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncStall(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncRoleVariables(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncTitle(poRole);
		LOG_PROCESS_ERROR(nRetCode);

        nRetCode = CCliMessageHandler::GetInstance().DoSyncMaster(poRole);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = CCliMessageHandler::GetInstance().DoSyncGuild(poRole);
        LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncSpirit(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncClientVariables(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncTeleportPlatform(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncMountList(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncPurchaseAuraRecord(poRole);
		LOG_PROCESS_ERROR(nRetCode);

        nRetCode = CCliMessageHandler::GetInstance().DoClientArenaSyncData(poRole);
        LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncKillNpcQuest(poRole);
		LOG_PROCESS_ERROR(nRetCode);

        nRetCode = CCliMessageHandler::GetInstance().DoSyncGuildAchievement(poRole);
        LOG_PROCESS_ERROR(nRetCode);

		{
			CHero* poHero = poRole->GetHero();
			if(poHero != NULL)
			{
				nRetCode = CCliMessageHandler::GetInstance().DoSyncHeroAttrList(poRole);
				LOG_PROCESS_ERROR(nRetCode);
			}
		}

		nRetCode = CCliMessageHandler::GetInstance().DoSyncShieldList(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncCheckInInfo(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CCliMessageHandler::GetInstance().DoSyncGameDataEnd(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		// temp code
		nRetCode = CCliMessageHandler::GetInstance().DoActivityChange(poRole);
		LOG_CHECK_ERROR(nRetCode);
		// temp code
	}
	else
	{
		nRetCode = CCliMessageHandler::GetInstance().DoChangeSceneEnter(poRole, TRUE);
		LOG_PROCESS_ERROR(nRetCode);
	}

	nRetCode = CCliMessageHandler::GetInstance().DoSyncAttrList(poRole);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CCliMessageHandler::GetInstance().DoSyncAuraList(poRole);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CCliMessageHandler::GetInstance().DoMSUpdateRankListData(poRole);
	LOG_CHECK_ERROR(nRetCode);

	if (poRole->GetMoveState() == CMS_DIE)
		CCliMessageHandler::GetInstance().DoReviveInfo(poRole);

#ifdef _FINAL
	CCliMessageHandler::GetInstance().DoGpkDynCode(poRole);
#endif

	// 新增代码
	poRole->NotifyRole_GameTimeCard();    // 角色上线, 通知点卡时间

	poRole->SetState(rsWaitClientLoad);
	poRole->SetLoadingSceneEndFrame(CGameWorld::GetInstance().GetGameFrame() + (g_GWConfig.nSceneLoadTimeOut * GAME_FPS / 1000));

	GS_SYS_LOG_SUCCESS(poRole);
	return;
Exit0:
	GS_SYS_LOG_ERROR(poRole);
	nRetCode = DoGTCloseClientSession(pMsg->dwClientSessionID);
	LOG_CHECK_ERROR(nRetCode);

	return;
}

void CGSMessageHandler::OnMSLeaveGS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_LEAVE_GS* pMsg = (M2G_LEAVE_GS*)pPacketBuffer;
	CRole* poRole = NULL;

	// 找不到Role为合理异常，预进场景失败就会找不到
	poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwClientSessionID);
	PROCESS_ERROR(poRole);

	switch (poRole->GetState())
	{
	case rsPreEntered:
		{
			nRetCode = CGSSessionMgr::GetInstance().DetachRoleFromSession(pMsg->dwClientSessionID);
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = poRole->UnInit();
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = CGameWorld::GetInstance().DelRole(poRole);
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = DoMSLeaveGSAck(pMsg->dwClientSessionID, pMsg->dwRoleID);
			LOG_CHECK_ERROR(nRetCode);
		}
		break;
	case rsWaitRoleData:
	case rsWaitMSApprove:
		{            
			nRetCode = DoDBUnlockRoleData(poRole);
			LOG_PROCESS_ERROR(nRetCode);

			poRole->SetState(rsWaitUnlockRoleData);
		}
		break;
	case rsWaitClientLoad:
		{
			nRetCode = DoDBSaveRoleData(poRole, FALSE);
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = DoDBUnlockRoleData(poRole);
			LOG_PROCESS_ERROR(nRetCode);

			poRole->SetState(rsWaitUnlockRoleData);
		}
		break;
	case rsPlaying:
		{
			const GRID_DATA* pcGrid = NULL;
			UINT32 dwDelayTime = ROLE_DELAY_LOGOUT_FRAME;

			pcGrid = poRole->GetGrid();
			LOG_PROCESS_ERROR(pcGrid);

			if(pcGrid->uPkType != gptSafe)
				dwDelayTime = ROLE_DELAY_LOGOUT_FRAME_ABNORMAL;

			poRole->GetAchievementList().SetVariable(avdLastOfflineTime, CGameWorld::GetInstance().GetGameTime());

			nRetCode = poRole->Logout(rltDisconnect, dwDelayTime);
			LOG_PROCESS_ERROR(nRetCode);
		}
		break;
	case rsLogout:
		{
            switch (poRole->GetLogoutType())
            {
            case rltReturnLogin:
	        case rltReturnSelectRole:
            case rltKickout:
                if (poRole->GetLogoutFrame() == 0)
                {
					poRole->GetAchievementList().SetVariable(avdLastOfflineTime, CGameWorld::GetInstance().GetGameTime());

					nRetCode = CCliMessageHandler::GetInstance().DoDLRoleLogout(poRole, FALSE);
					LOG_CHECK_ERROR(nRetCode);

                    nRetCode = poRole->Exit();
                    LOG_PROCESS_ERROR(nRetCode);
                }
                else
                {
					poRole->GetAchievementList().SetVariable(avdLastOfflineTime, CGameWorld::GetInstance().GetGameTime());

                    nRetCode = poRole->Logout(rltDisconnect, 0);
					LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case rltDisconnect:
                LOG_PROCESS_ERROR(FALSE);
                break;
            default:
                LOG_PROCESS_ERROR(FALSE);
            }
		}
		break;
	case rsInJump:
		{
			nRetCode = CCliMessageHandler::GetInstance().DoDLRoleLogout(poRole, TRUE);
			LOG_CHECK_ERROR(nRetCode);

            nRetCode = poRole->Exit();
			LOG_PROCESS_ERROR(nRetCode);
		}
		break;
	case rsJumpInGSWaitClientLoad:
		{
			nRetCode = CCliMessageHandler::GetInstance().DoDLRoleLogout(poRole, FALSE);
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = poRole->Exit();
			LOG_PROCESS_ERROR(nRetCode);
		}
		break;
	case rsWaitUnlockRoleData:
	default:
		LOG_PROCESS_ERROR(FALSE);
		break;
	}

	GS_SYS_LOG_SUCCESS(poRole);
	return;
Exit0:
	GS_SYS_LOG_ERROR(poRole);

	if (poRole)
	{
		if (poRole->GetScene())
		{
			nRetCode = poRole->GetScene()->RemoveRole(poRole);
			LOG_CHECK_ERROR(nRetCode);
		}

		nRetCode = poRole->UnInit();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = CGameWorld::GetInstance().DelRole(poRole);
		LOG_CHECK_ERROR(nRetCode);
	}

	nRetCode = DoMSLeaveGSAck(pMsg->dwClientSessionID, pMsg->dwRoleID);
	LOG_CHECK_ERROR(nRetCode);

	return;
}

void CGSMessageHandler::OnMSCreateScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_CREATE_SCENE* pMsg = (M2G_CREATE_SCENE*)pPacketBuffer;
	CScene* poScene = NULL;

	poScene = CGameWorld::GetInstance().NewScene(MakeSceneObjID(pMsg->nSceneTempID, pMsg->nSceneID));
	LOG_PROCESS_ERROR(poScene);

	nRetCode = poScene->Init(pMsg->byGroupID, pMsg->nSceneTempID, pMsg->nSceneID);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = DoMSCreateSceneAck(pMsg->byGroupID, pMsg->nSceneTempID, pMsg->nSceneID, errSuccess);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = DoDLCreateScene(CGameWorld::GetInstance().GetGameTime(), 0, poScene->GetSceneID(), poScene->GetSceneTempID());
	LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	if(poScene)
	{
		nRetCode = poScene->UnInit();
		LOG_CHECK_ERROR(nRetCode);
		CGameWorld::GetInstance().DelScene(poScene);
	}

	nRetCode = DoMSCreateSceneAck(pMsg->byGroupID, pMsg->nSceneTempID, pMsg->nSceneID, errSceneCreateSceneFailed);
	LOG_CHECK_ERROR(nRetCode);

	return;
}

void CGSMessageHandler::OnMSDestroyScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_DESTROY_SCENE* pMsg = (M2G_DESTROY_SCENE*)pPacketBuffer;
	CScene* poScene = NULL;

	poScene = CGameWorld::GetInstance().FindScene(MakeSceneObjID(pMsg->nSceneTempID, pMsg->nSceneID));
	LOG_PROCESS_ERROR(poScene);
	LOG_PROCESS_ERROR(poScene->GetRoleCount() == 0);

	nRetCode = DoDLDestoryScene(CGameWorld::GetInstance().GetGameTime(), 0, poScene->GetSceneID(), poScene->GetSceneTempID());
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = poScene->UnInit();
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CGameWorld::GetInstance().DelScene(poScene);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = DoMSDestroySceneAck(pMsg->byGroupID, pMsg->nSceneTempID, pMsg->nSceneID, errSuccess);
	LOG_PROCESS_ERROR(nRetCode);

	return;
Exit0:
	nRetCode = DoMSDestroySceneAck(pMsg->byGroupID, pMsg->nSceneTempID, pMsg->nSceneID, errSceneDestroySceneFailed);
	LOG_CHECK_ERROR(nRetCode);

	return;
}

void CGSMessageHandler::OnMSCloseScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_CLOSE_SCENE* pMsg = (M2G_CLOSE_SCENE*)pPacketBuffer;
	CScene* poScene = NULL;

	poScene = CGameWorld::GetInstance().FindScene(MakeSceneObjID(pMsg->nSceneTempID, pMsg->nSceneID));
	LOG_PROCESS_ERROR(poScene);
	LOG_PROCESS_ERROR(poScene->GetServerGroup() == pMsg->byServerGroup);

	nRetCode = poScene->Close(1 * GAME_FPS);
	LOG_PROCESS_ERROR(nRetCode);

	INF("close scene %d-%X on group", pMsg->nSceneTempID, pMsg->nSceneID, pMsg->byServerGroup);

	return;
Exit0:
	CRI("failed to close scene %d-%X on group", pMsg->nSceneTempID, pMsg->nSceneID, pMsg->byServerGroup);

	nRetCode = DoMSDestroySceneAck(pMsg->byServerGroup, pMsg->nSceneTempID, pMsg->nSceneID, errSceneDestroySceneFailed);
	LOG_CHECK_ERROR(nRetCode);

	return;
}

void CGSMessageHandler::OnMSQuerySceneAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_QUERY_SCENE_ACK* pMsg = (M2G_QUERY_SCENE_ACK*)pPacketBuffer;
	CScene* poSrcScene;

	CRole* poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwCliSessionID);
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetObjID() == pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole->GetState() == rsInJump);

	if (pMsg->nErrCode == errSuccess)
	{
		nRetCode = DoDBSaveRoleData(poRole, FALSE);
		LOG_PROCESS_ERROR(nRetCode);

		poSrcScene = poRole->GetScene();
		LOG_PROCESS_ERROR(poSrcScene);

		nRetCode = poSrcScene->RemoveRole(poRole);
		LOG_PROCESS_ERROR(nRetCode);

		poRole->SetSceneTempID(pMsg->nSceneTempID);
		poRole->SetSceneID(pMsg->nSceneID);
		poRole->SetX(pMsg->nDestX);
		poRole->SetY(pMsg->nDestY);
		poRole->SetZ(pMsg->nDestZ);
		poRole->SetFaceDirection(pMsg->nFaceDirection);

		nRetCode = CCliMessageHandler::GetInstance().DoChangeSceneEnter(poRole, FALSE);
		LOG_PROCESS_ERROR(nRetCode);

		poRole->SetState(rsJumpInGSWaitClientLoad);
		poRole->SetLoadingSceneEndFrame(CGameWorld::GetInstance().GetGameFrame() + (g_GWConfig.nSceneLoadTimeOut * GAME_FPS / 1000));

	}
	else
	{
		nRetCode = poRole->ErrorCodeNotify( pMsg->nErrCode, 0, 0);
		LOG_PROCESS_ERROR(nRetCode);

		poRole->SetState(rsPlaying);
	}

	GS_SYS_LOG_SUCCESS(poRole);
	return;
Exit0:
	if(poRole)
	{
		nRetCode = CGSMessageHandler::GetInstance().DoGTCloseClientSession(poRole->GetSessionID(), FALSE);
		LOG_CHECK_ERROR(nRetCode);
	}

	GS_SYS_LOG_ERROR(poRole);
	return;
}

void CGSMessageHandler::OnMSChangeScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_CHANGE_SCENE* pMsg = (M2G_CHANGE_SCENE*)pPacketBuffer;
	CScene* poScene = NULL;

	CRole* poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwCliSessionID);
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetObjID() == pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole->GetState() == rsPreEntered);

	nRetCode = DoDBLoadLockRoleData(pMsg->dwCliSessionID, pMsg->dwRoleID);
	LOG_PROCESS_ERROR(nRetCode);

	poRole->SetInJump();
	poRole->SetState(rsWaitRoleData);

	GS_SYS_LOG_SUCCESS(poRole);
	return;
Exit0:
	GS_SYS_LOG_ERROR(poRole);
	return;
}

void CGSMessageHandler::OnMSSyncRSAKey(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	//INT32 nRetCode = 0;
	//M2G_SYNC_RSAKEY* pMsg = (M2G_SYNC_RSAKEY*)pPacketBuffer;
	//BIG_NUM_DATA* pBigNum = NULL;

	//RSA* pKey = CGameWorld::GetInstance().GetRSAKey();
	//LOG_PROCESS_ERROR(pKey);

	//   pBigNum = (BIG_NUM_DATA*)pMsg->szData;

	//   nRetCode = RSA_FromData2Key(pBigNum, pKey, TRUE);
	//   LOG_PROCESS_ERROR(nRetCode);

	//   nRetCode = RSA_FromData2Key(pBigNum + 1, pKey, FALSE);
	//   LOG_PROCESS_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CGSMessageHandler::OnMSJoinBattle(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_JOIN_BATTLE* pMsg = (M2G_JOIN_BATTLE*)pPacketBuffer;

	CRole* poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwCliSessionID);
    LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetState() == rsPlaying);
	LOG_PROCESS_ERROR(poRole->GetObjID() == pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole->GetMoveState() != CMS_DIE);

	poRole->SetBattleEnterPos(pMsg->dwSceneTempID, pMsg->dwSceneID, pMsg->bySide);
	CCliMessageHandler::GetInstance().OnEnterBattle(poRole);

	return;
Exit0:
	return;
}

void CGSMessageHandler::OnMSTeamNew(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_TEAM_NEW* pMsg = (M2G_TEAM_NEW*)pPacketBuffer;
	CTeamInGS* pstTeam = NULL;

	pstTeam = CGameWorld::GetInstance().NewTeam(pMsg->dwTeamID);
	LOG_PROCESS_ERROR(pstTeam);

	nRetCode = pstTeam->Init();
	LOG_CHECK_ERROR(nRetCode);

	pstTeam->SetGroupID(pMsg->byGroupID);
	pstTeam->SetTeamID(pMsg->dwTeamID);
	pstTeam->SetLeaderID(pMsg->dwLeadID);
	pstTeam->SetAssignType(pMsg->byAssignType);
	pstTeam->SetMaxMemberCount(pMsg->nMemberSizeLimit);
	pstTeam->SetCreateTime(pMsg->dwCreateTime);
	pstTeam->SetMemberCount(pMsg->byCount);
	strxcpy(pstTeam->GetTeamName(), pMsg->szTeamName, TEAM_NAME_LEN);

	for(INT32 i = 0; i < pMsg->byCount; ++i)
	{
		pstTeam->GetMemberTable(i).dwRoleID = pMsg->stTeamMemberList[i].dwMemberID;
		strxcpy(pstTeam->GetMemberTable(i).szRoleName, pMsg->stTeamMemberList[i].szRoleName, ROLE_NAME_LEN);
		pstTeam->GetMemberTable(i).nSex = pMsg->stTeamMemberList[i].btSex;
		pstTeam->GetMemberTable(i).nClass = pMsg->stTeamMemberList[i].btClass;
		pstTeam->GetMemberTable(i).nLevel = pMsg->stTeamMemberList[i].btLevel;
		CRole* poRole = CGameWorld::GetInstance().FindValidRole(pstTeam->GetMemberTable(i).dwRoleID);
		if(poRole)
		{
			poRole->SetTeamID(pstTeam->GetTeamID());

			nRetCode = CCliMessageHandler::GetInstance().DoClientSyncRoleTeam(poRole);
			LOG_PROCESS_ERROR(nRetCode);
		
			poRole->GetAchievementList().AddVariable(avdJoinTeamCount, 1);
		}
	}
	return;
Exit0:
	return;
}

void CGSMessageHandler::OnMSTeamAddMember(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_TEAM_ADD_MEMBER* pMsg = (M2G_TEAM_ADD_MEMBER*)pPacketBuffer;
	CTeamInGS* pstTeam = NULL;

	pstTeam = CGameWorld::GetInstance().FindTeam(pMsg->dwTeamID);
	LOG_PROCESS_ERROR(pstTeam);

	nRetCode = pstTeam->AddNewMember(pMsg->stMemberInfo.dwMemberID, pMsg->stMemberInfo.szRoleName, pMsg->stMemberInfo.btLevel, pMsg->stMemberInfo.btSex, pMsg->stMemberInfo.btClass);
	LOG_PROCESS_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CGSMessageHandler::OnMSTeamRemoveMember(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_TEAM_REMOVE_MEMBER* pMsg = (M2G_TEAM_REMOVE_MEMBER*)pPacketBuffer;
	CTeamInGS* poTeam = NULL;

	poTeam = CGameWorld::GetInstance().FindTeam(pMsg->dwTeamID);
	LOG_PROCESS_ERROR(poTeam);

	nRetCode = poTeam->RemoveMember(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(nRetCode);

	if(poTeam->GetMemberCount() == 0)
	{
		nRetCode = poTeam->UnInit();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = CGameWorld::GetInstance().DelTeam(poTeam);
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
Exit0:
	return;
}

void CGSMessageHandler::OnMSTeamChangeInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_TEAM_CHANGEINFO* pMsg = (M2G_TEAM_CHANGEINFO*)pPacketBuffer;
	CTeamInGS* pstTeam = NULL;

	pstTeam = CGameWorld::GetInstance().FindTeam(pMsg->dwTeamID);
	LOG_PROCESS_ERROR(pstTeam);

	pstTeam->SetLeaderID(pMsg->dwLeadID);
	pstTeam->SetAssignType(pMsg->byAssignType);
	pstTeam->SetMaxMemberCount(pMsg->nTeamMemberLimit);
	pstTeam->SetRoomID(pMsg->dwRoomID);
	pstTeam->SetAuctionItemColorLimit(pMsg->byAuctionItemColorLimit);
	pstTeam->SetActivityID(pMsg->dwActivityID);
	pstTeam->SetActivityType(pMsg->dwActivityType);

	strxcpy(pstTeam->GetTeamName(), pMsg->szTeamName, TEAM_NAME_LEN);

	return;
Exit0:
	return;
}

void CGSMessageHandler::OnMSRoomEnterDungeon(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_ROOM_ENTER_DUNGEON* pMsg = (M2G_ROOM_ENTER_DUNGEON*)pPacketBuffer;

	CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole);

	return;
Exit0:
	return;
}

void CGSMessageHandler::OnMSChangeInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	M2G_CHANGE_INFO* pMsg = (M2G_CHANGE_INFO*)pPacketBuffer;
	CRole* poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwCliSessionID);
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetObjID() == pMsg->dwRoleID);

	poRole->GetFriend()->SetSignature(pMsg->szSignature);

Exit0:
	return;
}

void CGSMessageHandler::OnMSFriendAdd(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32   nRetCode = 0;
	M2G_FRIEND_ADD* pMsg = (M2G_FRIEND_ADD*)pPacketBuffer;
	CRole* poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwCliSessionID);
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetObjID() == pMsg->dwRoleID);

	poRole->GetFriend()->AddFriend(pMsg->byGroupID, pMsg->dwFriendID);

    if (pMsg->byGroupID != FRIEND_GROUP_ENEMY)
    {
        PROCESS_ERROR(poRole->GetShieldList()->IsAlreadyShielded(pMsg->dwFriendID));
        poRole->GetShieldList()->UnShieldRole(pMsg->dwFriendID);
        nRetCode = CCliMessageHandler::GetInstance().DoUnShieldAck(poRole, pMsg->dwFriendID);
        LOG_PROCESS_ERROR(nRetCode);
    }


Exit0:
	return;
}

void CGSMessageHandler::OnMSFriendDel(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	M2G_FRIEND_DEL* pMsg = (M2G_FRIEND_DEL*)pPacketBuffer;
	CRole* poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwCliSessionID);
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetObjID() == pMsg->dwRoleID);

	poRole->GetFriend()->DelFriend(pMsg->byGroupID, pMsg->dwFriendID);
Exit0:
	return;
}

void CGSMessageHandler::OnMSMstSyncState(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    M2G_MST_SYNC_STATE *pMsg = (M2G_MST_SYNC_STATE*)pPacketBuffer;

    CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    if (poRole)
    {
        poRole->GetMaster().SetState(pMsg->nState);
        if (pMsg->nState == MASTER_BECOME_TEACHER)
        {
            poRole->GetMaster().SetState(MASTER_TEACHER);
            poRole->GetMaster().SetTwitter(FALSE);      // 默认关闭 "接受徒弟推送"
        }
    }

Exit0:
    return;
}

void CGSMessageHandler::OnMSMstSyncData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	M2G_MST_SYNC_DATA* pMsg = (M2G_MST_SYNC_DATA*)pPacketBuffer;
	CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	if (poRole)
	{
        poRole->GetMaster().Onload(pMsg->dwTeacherID, pMsg->byStudNum, pMsg->arrStudentID);
	}
	
Exit0:
	return;
}

void CGSMessageHandler::OnMSMstCreateRelation(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    M2G_MST_CREATE_RELATION_NTF* pMsg = (M2G_MST_CREATE_RELATION_NTF*)pPacketBuffer;
    CRole* poRole = NULL; 

    poRole = CGameWorld::GetInstance().FindRole(pMsg->dwTeacherID);
    if (poRole)
    {
        poRole->GetMaster().AddStudent(pMsg->dwStudentID);
    }

    poRole = CGameWorld::GetInstance().FindRole(pMsg->dwStudentID);
    if (poRole)
    {
        poRole->GetMaster().AddTeacher(pMsg->dwTeacherID);
        poRole->GetMaster().SetStudentRewardMasterID(pMsg->dwTeacherID);
    }


Exit0:
    return;
}

void CGSMessageHandler::OnMSMstDelRelation(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32   nRetCode = 0;
    M2G_MST_DEL_RELATION_NTF* pMsg = (M2G_MST_DEL_RELATION_NTF*)pPacketBuffer;
    CRole* poRole = NULL; 

    poRole = CGameWorld::GetInstance().FindRole(pMsg->dwTeacherID);
    if (poRole)
    {
        poRole->GetMaster().DelStudent(pMsg->dwStudentID);
    }

    poRole = CGameWorld::GetInstance().FindRole(pMsg->dwStudentID);
    if (poRole)
    {
        poRole->GetMaster().DelTeacher(pMsg->dwTeacherID);
    }
Exit0:
    return;
}

void CGSMessageHandler::OnMSMstUpdateData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32   nRetCode = 0;
    M2G_MST_UPDATE_DATA* pMsg = (M2G_MST_UPDATE_DATA*)pPacketBuffer;
    CRole* poRole = NULL;

    switch (pMsg->nType)
    {
    case MST_SYNC_GS_CD:
    {
        poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
        if (poRole)
        {
            poRole->GetMaster().SetCD(pMsg->nValue);
        }
    }
        break;
    //case MST_SYNC_GS_TWITTER_CD:
    //{
    //    poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    //    if (poRole)
    //    {
    //        poRole->GetMaster().SetTwitter(pMsg->nValue);
    //    }
    //}
    //    break;
    case MST_SYNC_PUNISH_EXP:
    {
        poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
        if (poRole)
        {
            if (poRole->GetMaster().IsTeacher())
            {
                INT64 llExp = poRole->GetMaster().GetTeacherRewardExp((UINT32)pMsg->nValue);
                llExp = llExp * g_GWConfig.nMasterRewardExpPunishRate / RATE_MAX;
                poRole->GetMaster().SetTeacherRewardExp((UINT32)pMsg->nValue, llExp);
            }
            else if (poRole->GetMaster().IsStudent())
            {
                INT64 llExp = poRole->GetMaster().GetStudentRewardExp();
                llExp = llExp * g_GWConfig.nMasterRewardExpPunishRate / RATE_MAX;
                poRole->GetMaster().SetStudentRewardExp(llExp);
            }
            else
                LOG_PROCESS_ERROR(FALSE);           
        }
    }
        break;
    case MST_SYNC_MASTER_EXP_DEC:
    {
        poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
        if (poRole)
        {
            INT32 nDecMoney = poRole->GetItemBag()->GetMoney(MONEYTYPE_MASTER_EXP);
            if (nDecMoney >= pMsg->nValue)
                poRole->GetItemBag()->SubMoney(MONEYTYPE_MASTER_EXP, pMsg->nValue, MONEYLOG_INVALID, 0);
            else
                poRole->GetItemBag()->SubMoney(MONEYTYPE_MASTER_EXP, nDecMoney, MONEYLOG_INVALID, 0);

            nRetCode = CCliMessageHandler::GetInstance().DoMSSyncMasterExp(pMsg->dwRoleID, poRole->GetItemBag()->GetMoney(MONEYTYPE_MASTER_EXP));
            LOG_PROCESS_ERROR(nRetCode);
        }
    }
        break;
    default:
        break;
    }

    return;
Exit0:
    return;
}


void CGSMessageHandler::OnMSSubmitTeacherApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32   nRetCode = 0;
    INT32   nResult = errUnknownError;
    BOOL    bCanRecvStudent = TRUE;
    const TEACHER_REWARD*       pReward = NULL;
    M2G_MST_SUBMIT_TEACHER_APP  *pMsg = (M2G_MST_SUBMIT_TEACHER_APP*)pPacketBuffer;

    CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwTeacherID);
    LOG_PROCESS_ERROR(poRole);

    PROCESS_ERROR_RET_CODE(poRole->GetMaster().GetStudentRewardExp() == 0, errMasterNeedGetRewardExp);

    pReward = poRole->GetMaster().GetTeacherRewardList();
    LOG_PROCESS_ERROR(pReward);

    for (INT32 i = 0, j = 0; i < MAX_STUDENT_NUM; ++i)
    {
        if (pReward[i].dwRoleID == 0)
            continue;
        for (; j < poRole->GetMaster().GetStudentCount(); ++j)
        {
            if (pReward[i].dwRoleID == poRole->GetMaster().GetStudentByIndex(j))
                break;
        }

        PROCESS_ERROR_RET_CODE(j != poRole->GetMaster().GetStudentCount(), errMasterNeedGetRewardExp);
    }

    nRetCode = CCliMessageHandler::GetInstance().DoMSMstSubmitTeacherAppAck(pMsg->bySourceType, pMsg->dwTeacherID, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

    return;
Exit0:
    if (nResult != errUnknownError)
        CCliMessageHandler::GetInstance().DoErrorCodeNotify(poRole, errMasterNeedGetRewardExp, 0, 0);
    return;
}

void CGSMessageHandler::OnMSMstAgreeTeacherApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32   nRetCode = 0;
    INT32   nResult = errUnknownError;
    M2G_MST_AGREE_TEACHER_APP  *pMsg = (M2G_MST_AGREE_TEACHER_APP*)pPacketBuffer;

    CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwStudentID);
    LOG_PROCESS_ERROR(poRole);

    PROCESS_ERROR_RET_CODE(poRole->GetMaster().GetStudentRewardExp() == 0, errMasterNeedGetRewardExp);

    nRetCode = CCliMessageHandler::GetInstance().DoMSMstAgreeTeacherAppAck(pMsg->dwTeacherID, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

    return;
Exit0:
    if (nResult != errUnknownError)
        CCliMessageHandler::GetInstance().DoErrorCodeNotify(poRole, errMasterNeedGetRewardExp, 0, 0);
    return;
}

void CGSMessageHandler::OnMSSubmitStudApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32   nRetCode = 0;
    INT32   nResult = errUnknownError;
    M2G_MST_SUBMIT_STUD_APP  *pMsg = (M2G_MST_SUBMIT_STUD_APP*)pPacketBuffer;

    CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwStudentID);
    LOG_PROCESS_ERROR(poRole);

    PROCESS_ERROR_RET_CODE(poRole->GetMaster().GetStudentRewardExp() == 0, errMasterNeedGetRewardExp);

    nRetCode = CCliMessageHandler::GetInstance().DoMSMstSubmitStudAppAck(pMsg->dwTeacherID, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

    return;
Exit0:
    if (nResult != errUnknownError)
        CCliMessageHandler::GetInstance().DoErrorCodeNotify(poRole, errMasterNeedGetRewardExp, 0, 0);
    return;
}

void CGSMessageHandler::OnMSMstAgreeStudApp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32   nRetCode = 0;
    INT32   nResult = errUnknownError;
    BOOL    bCanRecvStudent = TRUE;
    const TEACHER_REWARD*       pReward = NULL;
    M2G_MST_AGREE_STUD_APP  *pMsg = (M2G_MST_AGREE_STUD_APP*)pPacketBuffer;

    CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwTeacherID);
    LOG_PROCESS_ERROR(poRole);
    
    PROCESS_ERROR_RET_CODE(poRole->GetMaster().GetStudentRewardExp() == 0, errMasterNeedGetRewardExp);

    pReward = poRole->GetMaster().GetTeacherRewardList();
    LOG_PROCESS_ERROR(pReward);

    for (INT32 i = 0, j = 0; i < MAX_STUDENT_NUM; ++i)
    {
        if (pReward[i].dwRoleID == 0)
            continue;
        for (; j < poRole->GetMaster().GetStudentCount(); ++j)
        {
            if (pReward[i].dwRoleID == poRole->GetMaster().GetStudentByIndex(j))
                break;
        }

        PROCESS_ERROR_RET_CODE(j != poRole->GetMaster().GetStudentCount(), errMasterNeedGetRewardExp);
    }

    nRetCode = CCliMessageHandler::GetInstance().DoMSMstAgreeStudAppAck(pMsg->dwTeacherID, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

    return;
Exit0:
    if (nResult != errUnknownError)
        CCliMessageHandler::GetInstance().DoErrorCodeNotify(poRole, errMasterNeedGetRewardExp, 0, 0);
    return;
}

void CGSMessageHandler::OnMSMstCZ(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    INT32       nResult = errUnknownError;
    M2G_MST_CZ* pMsg = (M2G_MST_CZ*)pPacketBuffer;
    CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(poRole);
    LOG_PROCESS_ERROR(poRole->GetObjID() == pMsg->dwRoleID);

    if (pMsg->byCZType == MASTER_CONG_BY_FREE)
    {
        
    }
    else if (pMsg->byCZType == MASTER_CONG_BY_MONEY)
    {
        LOG_PROCESS_ERROR_RET_CODE(poRole->GetItemBag()->GetMoney(MONEYTYPE_02) >= pMsg->nConsumption, errNotEnoughMoney);
        poRole->GetItemBag()->SubMoney(MONEYTYPE_02, pMsg->nConsumption, MONEYLOG_MASTER_CZ, 0);
    }
    else if (pMsg->byCZType == MASTER_CONG_BY_GOLD)
    {
        LOG_PROCESS_ERROR_RET_CODE(poRole->GetItemBag()->GetMoney(MONEYTYPE_02) >= pMsg->nConsumption, errNotEnoughMoney);
        poRole->GetItemBag()->SubMoney(MONEYTYPE_02, pMsg->nConsumption, MONEYLOG_MASTER_CZ, 0);
    }

    nRetCode = CCliMessageHandler::GetInstance().DoMSMasterCZ(pMsg->dwRoleID, pMsg->dwTargetID, pMsg->byCZType, pMsg->byCZLevel, pMsg->szText);
    LOG_PROCESS_ERROR(nRetCode);

    return;
Exit0:
    if(nResult != errUnknownError)
        poRole->ErrorCodeNotify(nResult, 0, 0);
    else
        KICK_ROLE(poRole, ktLogged);
    return;
}


void CGSMessageHandler::OnMSMailCostCheck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nResult = errMailUnknown;
	M2G_MAIL_COST_CHECK* pMsg = (M2G_MAIL_COST_CHECK*)pPacketBuffer;
	CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwSenderRoleID);
	LOG_PROCESS_ERROR(poRole);

	if (poRole->GetItemBag()->GetMoney(MONEYTYPE_02) >= MAIL_COST)
	{
		poRole->GetItemBag()->SubMoney(MONEYTYPE_02, MAIL_COST, MONEYLOG_MAIL_COST, 0);
		nResult = errSuccess;
	}
	else
	{
		nResult = errMailCostNotEnough;
	}

Exit0:
	DoMSMailCostCheck(nResult, pMsg);
}

void CGSMessageHandler::OnMSMailGetSimpleAttach(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nResult = errMailUnknown;
	M2G_MAIL_GET_SIMPLE_ATTACH* pMsg = (M2G_MAIL_GET_SIMPLE_ATTACH*)pPacketBuffer;
	CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole);

    if (pMsg->nItemID >= 99)
	    nResult = poRole->GetItemBag()->AddItem(pMsg->nItemID, pMsg->nItemCount, ITEMLOG_GET_MAIL_ATTACH, 0, FALSE);
    else
        nResult = poRole->GetItemBag()->AddMoney(pMsg->nItemID, pMsg->nItemCount, MONEYLOG_GET_MAIL_ATTACH, 0);

	if (nResult == errSuccess)
		poRole->GetProMails()->AddProcessMail(pMsg->dwMailID);

Exit0:
	DoMSMailGetAttach(nResult, pMsg->dwMailID);
}

void CGSMessageHandler::OnMSMailGetBufferAttach(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nResult = errMailUnknown;
	UINT32 dwReadLen = 0;
	ItemInfo iteminfo;
	Item* item = NULL;
	M2G_MAIL_GET_BUFFER_ATTACH* pMsg = (M2G_MAIL_GET_BUFFER_ATTACH*)pPacketBuffer;
	CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole);

	dwReadLen = iteminfo.Load(pMsg->acBuffer);
	LOG_PROCESS_ERROR(dwReadLen > 0 && dwReadLen <= pMsg->byBufferLen);

	item = CItemMgr::GetInstance().LoadItem(iteminfo);
    if (item == NULL)
    {
        CRI("LoadItem Failed: RoleID:%u, GUID:%I64u, TemplateID:%d, Dur:%d", poRole->GetObjID(), iteminfo.m_llGuid, iteminfo.m_nTemplateID, iteminfo.m_nCurDur);
    }
	LOG_PROCESS_ERROR(item);

	nResult = poRole->GetItemBag()->AddItem(item, ITEMLOG_GET_MAIL_ATTACH, 0);
	if (nResult == errSuccess)
		poRole->GetProMails()->AddProcessMail(pMsg->dwMailID);
    else
    {
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(item);
        LOG_CHECK_ERROR(bItemRet);
    }

Exit0:
	DoMSMailGetAttach(nResult, pMsg->dwMailID);
}

void CGSMessageHandler::OnMSCallLuaFunction(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	CLuaScript* poLuaScript = NULL;

	M2G_CALL_LUA_FUNCTION* pMsg = (M2G_CALL_LUA_FUNCTION*)pPacketBuffer;
	LOG_PROCESS_ERROR(pMsg);

	poLuaScript = CScriptMgr::GetInstance().FindScript(pMsg->chFileName);
	LOG_PROCESS_ERROR(poLuaScript);

	nRetCode = poLuaScript->CallFunction(pMsg->chFuncName, "ddd", pMsg->nValue1, pMsg->nValue2, pMsg->nValue3);
	LOG_PROCESS_ERROR(nRetCode);	

	return;
Exit0:

	return;
}


void CGSMessageHandler::OnMSPreCreateGuild(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32   nRetCode = 0;
	INT32   nResult = errUnknownError;
	M2G_PRE_CREATE_GUILD    *pMsg = (M2G_PRE_CREATE_GUILD*)pPacketBuffer;

	CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole);

    if (pMsg->byIsNeedToConsume)
    {
        // pre check
        PROCESS_ERROR_RET_CODE(poRole->GetItemBag()->GetMoney(MONEYTYPE_02) >= g_GuildConfig.nCanCreateGuildMoney, errGuildNotEnoughMoney);

        // consume item
        nRetCode = poRole->GetItemBag()->DeleteItemId(g_GuildConfig.nCanCreateGuildItemTypeID, 
			g_GuildConfig.nCanCreateGuildItemNum, ITEMLOG_CREATE_GUILD, FALSE, 0);
        PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, errGuildNoItem);

        // consume money
        nRetCode = poRole->GetItemBag()->SubMoney(MONEYTYPE_02, g_GuildConfig.nCanCreateGuildMoney, MONEYLOG_CREATE_GUILD, 0);
        LOG_PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, errGuildSubRoleMoneyFailed);
    }

	nRetCode = DoMSPreCreateGuildAck(errSuccess, pMsg->dwRoleID, pMsg->szGuildName);
	LOG_CHECK_ERROR(nRetCode);
	return ;
Exit0:
	DoMSPreCreateGuildAck(nResult, pMsg->dwRoleID, pMsg->szGuildName);
	return ;
}

void CGSMessageHandler::OnMSRoleAddGuild(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32       nRetCode = 0;
	INT32       nResult = errUnknownError;
    CGSGuild    *poGSGuild = NULL;
	M2G_ROLE_ADD_GUILD_NTF *pMsg = (M2G_ROLE_ADD_GUILD_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().NewGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

    nRetCode = poGSGuild->Create(pMsg->dwGuildID, pMsg->nState, pMsg->dwLeaderID, pMsg->szGuildName, 
		0, NULL, 0, NULL, NULL, NULL, pMsg->byServerGroup);
    LOG_PROCESS_ERROR(nRetCode);

    for (INT32 i = 0; i < pMsg->byBuildingNum; ++i)
    {
        nRetCode = poGSGuild->AddBuilding(pMsg->arrBData[i].qwNameID, pMsg->arrBData[i].nType, pMsg->arrBData[i].nLevel);
        LOG_PROCESS_ERROR(nRetCode);
    }
    for (INT32 i = pMsg->byBuildingNum; i < pMsg->byUpgradeBuildingNum; ++i)
    {
        nRetCode = poGSGuild->AddUpgradeBuilding(pMsg->arrBData[i].qwNameID, pMsg->arrBData[i].nType, pMsg->arrBData[i].nLevel);
        LOG_PROCESS_ERROR(nRetCode);
    }

	return ;
Exit0:
    return;
}

void CGSMessageHandler::OnMSGuildAddMember(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32       nRetCode = 0;
	INT32       nResult = errUnknownError;
    CGSGuild    *poGSGuild = NULL;
    CRole       *poRole = NULL;
	M2G_GUILD_ADD_MEMBER_NTF *pMsg = (M2G_GUILD_ADD_MEMBER_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

    nRetCode = poGSGuild->AddMember(pMsg->dwRoleID, pMsg->byPosition);
    LOG_PROCESS_ERROR(nRetCode);

	poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	if (poRole)
	{
		poRole->SetGuildID(pMsg->dwGuildID);
        if (poRole->GetScene() != NULL)
        {
            nRetCode = CCliMessageHandler::GetInstance().DoSyncGuildName(poRole, poGSGuild->GetID());
            LOG_PROCESS_ERROR(nRetCode);
        }
	}

	return ;
Exit0:
    return;
}

void CGSMessageHandler::OnMSGuildDelMember(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32       nRetCode = 0;
    CGSGuild    *poGSGuild = NULL;
    CRole       *poRole  = NULL;
	M2G_GUILD_DEL_MEMBER_NTF *pMsg = (M2G_GUILD_DEL_MEMBER_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

	poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	if (poRole)
	{
		poRole->SetGuildID(INVALID_OBJECT_ID);
        poRole->GetRoleGuildData().SetCD(pMsg->dwCD);
		nRetCode = CCliMessageHandler::GetInstance().DoSyncGuildName(poRole, 0);
		LOG_CHECK_ERROR(nRetCode);

        if (poRole->GetScene() && poRole->GetScene()->GetSceneID() == pMsg->dwGuildID)
        {
            nRetCode = poRole->JumpToReturnPos();           // redmine bug: 7299
            LOG_CHECK_ERROR(nRetCode);
        }
	}

    nRetCode = poGSGuild->DelMember(pMsg->dwRoleID);
    LOG_CHECK_ERROR(nRetCode);

	return ;
Exit0:
    return;
}

void CGSMessageHandler::OnMSGuildSyncDataNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32       nRetCode = 0;
    CGSGuild    *poGSGuild = NULL;
	M2G_SYNC_GUILD_DATA_NTF *pMsg = (M2G_SYNC_GUILD_DATA_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().NewGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

    nRetCode = poGSGuild->Create(pMsg->dwGuildID, pMsg->nState, pMsg->dwLeaderID, pMsg->szGuildName, 
        pMsg->byAllianceNum, pMsg->arrAllianceID, 
        pMsg->byEnemyNum, pMsg->arrEnemyID, pMsg->arrWelfareAuraLvl, pMsg->arrVariables, pMsg->byServerGroup);
    LOG_PROCESS_ERROR(nRetCode);

    for (INT32 nIndex = 0; nIndex < pMsg->byMemberNum; ++nIndex)
    {
        poGSGuild->AddMember(pMsg->memberList[nIndex].dwRoleID, pMsg->memberList[nIndex].byPosition);
    }

	for (INT32 nIndex = 0; nIndex < MAX_SABAC_ENROLL_COUNT; nIndex++)
	{
		if (pMsg->dwSabacEnrollTime[nIndex] > 0)
		{
			poGSGuild->SetSabacEnrollTime(pMsg->dwSabacEnrollTime[nIndex]);
			CSabacMgr::GetInstance().Enroll(pMsg->dwGuildID, pMsg->dwSabacEnrollTime[nIndex], poGSGuild->GetServerGroup());
		}
	}
	poGSGuild->OccupySabac(pMsg->bySabacOccupied);
	if (pMsg->bySabacOccupied)
		CSabacMgr::GetInstance().SetOccupyGuildID(pMsg->byServerGroup, pMsg->dwGuildID);

    for (INT32 i = 0; i < pMsg->byBuildingNum; ++i)
    {
        nRetCode = poGSGuild->AddBuilding(pMsg->arrBData[i].qwNameID, pMsg->arrBData[i].nType, pMsg->arrBData[i].nLevel);
        LOG_PROCESS_ERROR(nRetCode);
    }
    for (INT32 i = pMsg->byBuildingNum; i < pMsg->byUpgradeBuildingNum; ++i)
    {
        nRetCode = poGSGuild->AddUpgradeBuilding(pMsg->arrBData[i].qwNameID, pMsg->arrBData[i].nType, pMsg->arrBData[i].nLevel);
        LOG_PROCESS_ERROR(nRetCode);
    }

	return ;
Exit0:
	return ;
}

void CGSMessageHandler::OnMSGuildDelete(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32       nRetCode = 0;
    CGSGuild    *poGSGuild = NULL;
	M2G_GUILD_DELETE_NTF *pMsg = (M2G_GUILD_DELETE_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

    nRetCode = poGSGuild->Destory();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CGuildMgr::GetInstance().DelGuild(poGSGuild);
    LOG_PROCESS_ERROR(nRetCode);

	return ;
Exit0:
    return ;
}

void CGSMessageHandler::OnMSGuildAddDiplomat(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32       nRetCode = 0;
	INT32       nResult = errUnknownError;
    CGSGuild    *poGSGuild = NULL;
    CGSGuild    *poGSTargetGuild = NULL;
	M2G_GUILD_ADD_DIPLOMAT_NTF *pMsg = (M2G_GUILD_ADD_DIPLOMAT_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

    poGSTargetGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwTargetGuildID);
    LOG_PROCESS_ERROR(poGSTargetGuild);

	if (GUILD_DIPLOMAT_ENEMY == pMsg->byType)
	{
        nRetCode = poGSGuild->AddEnemy(pMsg->dwTargetGuildID);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = poGSTargetGuild->AddEnemy(pMsg->dwGuildID);
        LOG_PROCESS_ERROR_RET_CODE(nRetCode, errGuildFailed);
	}
	else if (GUILD_DIPLOMAT_ALLIANCE == pMsg->byType)
	{
        nRetCode = poGSGuild->AddAlliance(pMsg->dwTargetGuildID);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = poGSTargetGuild->AddAlliance(pMsg->dwGuildID);
        LOG_PROCESS_ERROR_RET_CODE(nRetCode, errGuildFailed);
	}

	return ;
Exit0:
    if (errGuildFailed == nResult)
    {
        if (GUILD_DIPLOMAT_ENEMY == pMsg->byType)
        {
            nRetCode = poGSGuild->DelEnemy(pMsg->dwTargetGuildID);
            LOG_CHECK_ERROR(nRetCode);
        }
        else if (GUILD_DIPLOMAT_ALLIANCE == pMsg->byType)
        {
            nRetCode = poGSGuild->DelAlliance(pMsg->dwTargetGuildID);
            LOG_CHECK_ERROR(nRetCode);
        }
    }
    return ;
}

void CGSMessageHandler::OnMSGuildDelDiplomat(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32       nRetCode = 0;
	INT32       nResult = errUnknownError;
    CGSGuild    *poGSGuild = NULL;
    CGSGuild    *poGSTargetGuild = NULL;
	M2G_GUILD_DEL_DIPLOMAT_NTF *pMsg = (M2G_GUILD_DEL_DIPLOMAT_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

    poGSTargetGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwTargetGuildID);
    LOG_PROCESS_ERROR(poGSTargetGuild);

	if (GUILD_DIPLOMAT_ENEMY == pMsg->byType)
	{
        nRetCode = poGSGuild->DelEnemy(pMsg->dwTargetGuildID);
        LOG_CHECK_ERROR(nRetCode);

        nRetCode = poGSTargetGuild->DelEnemy(pMsg->dwGuildID);
        LOG_PROCESS_ERROR(nRetCode);
	}
	else if (GUILD_DIPLOMAT_ALLIANCE == pMsg->byType)
	{
        nRetCode = poGSGuild->DelAlliance(pMsg->dwTargetGuildID);
        LOG_CHECK_ERROR(nRetCode);

        nRetCode = poGSTargetGuild->DelAlliance(pMsg->dwGuildID);
        LOG_PROCESS_ERROR(nRetCode);
	}

	return ;
Exit0:
    return;
}

void CGSMessageHandler::OnMSGuildSyncGuildAttrNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    CGSGuild    *poGuild = NULL;
    M2G_GUILD_SYNC_ATTR_NTF *pMsg = (M2G_GUILD_SYNC_ATTR_NTF*)pPacketBuffer;

    poGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGuild);

    switch (pMsg->nAttrType)
    {
    case GUILD_ATTR_MONEY:
    {
        poGuild->SetMoney(pMsg->dwAttrValue);
    }
        break;
    case GUILD_ATTR_HERB:
    {
        poGuild->SetHerb(pMsg->dwAttrValue);
    }
        break;
    case GUILD_ATTR_WOOD:
    {
        poGuild->SetWood(pMsg->dwAttrValue);
    }
        break;
    case GUILD_ATTR_CRYSTAL:
    {
        poGuild->SetCrystal(pMsg->dwAttrValue);
    }
        break;
    case GUILD_ATTR_SILVER:
    {
        poGuild->SetSilver(pMsg->dwAttrValue);
    }
        break;
    default:
        break;
    }

Exit0:
    return;
}

void CGSMessageHandler::OnMSGuildSyncVariableNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    CGSGuild    *poGuild = NULL;
    M2G_GUILD_SYNC_VARIABLE_NTF *pMsg = (M2G_GUILD_SYNC_VARIABLE_NTF*)pPacketBuffer;

    poGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGuild);

    nRetCode = poGuild->SetVariable(pMsg->nIndex, pMsg->nValue);
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return;
}

void CGSMessageHandler::OnMSGuildDrawSalary(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_GUILD_DRAW_SALARY *pMsg = (M2G_GUILD_DRAW_SALARY*)pPacketBuffer;

	CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole);

	nRetCode = poRole->GetItemBag()->AddMoney(MONEYTYPE_02, pMsg->nSalary, MONEYLOG_GUILD_SALARY, 0);
	LOG_PROCESS_ERROR(errSuccess == nRetCode);

    nRetCode = CCliMessageHandler::GetInstance().DoGuildDrawSalaryAck(poRole, pMsg->nSalary);
    LOG_PROCESS_ERROR(nRetCode);

	return ;
Exit0:
	return ; 
}

void CGSMessageHandler::OnMSGuildPrePushItemAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	INT32   nResult = errUnknownError;
	ItemInfo data;
	Item    *pItem  = NULL;
	M2G_GUILD_PRE_PUSH_ITEM_ACK *pMsg = (M2G_GUILD_PRE_PUSH_ITEM_ACK*)pPacketBuffer;

	CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetItemBag());


	pItem = poRole->GetItemBag()->GetItem(pMsg->wConSlot, pMsg->wSlot);
	LOG_PROCESS_ERROR_RET_CODE(pItem, errItemNotFound);
    LOG_PROCESS_ERROR_RET_CODE(pItem->m_iteminfo.m_byBindType != BINDTYPE_BINDED, errItemBinded);

    memcpy(&data, &pItem->m_iteminfo, sizeof(ItemInfo));

    nRetCode = poRole->GetItemBag()->DeleteItemPos(pMsg->wConSlot, pMsg->wSlot,
        pItem->m_pTemplate->m_byDurType == DURTYPE_STACK ? pItem->m_iteminfo.m_nCurDur : 1, ITEMLOG_GUILD_STORAGE, 0);
	LOG_PROCESS_ERROR_RET_CODE(errSuccess == nRetCode, nRetCode);


	nRetCode = CCliMessageHandler::GetInstance().DoMSGuildPushItem(errSuccess, pMsg->dwRoleID, pMsg->byConSlot, pMsg->bySlot, data);
	LOG_CHECK_ERROR(nRetCode);
	return ;
Exit0:
	nRetCode = CCliMessageHandler::GetInstance().DoMSGuildPushItem(nResult, pMsg->dwRoleID, pMsg->byConSlot, pMsg->bySlot, data);
	LOG_CHECK_ERROR(nRetCode);
	return ; 
}

void CGSMessageHandler::OnMSGuildPrePopItemAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	INT32   nResult = errUnknownError;
	Item    *pItem = NULL;
	M2G_GUILD_PRE_POP_ITEM_ACK *pMsg = (M2G_GUILD_PRE_POP_ITEM_ACK*)pPacketBuffer;

	CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole);

	pItem = poRole->GetItemBag()->GetItem(pMsg->wConSlot, pMsg->wSlot);
	LOG_PROCESS_ERROR_RET_CODE(NULL == pItem, errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(CONSLOT_DEFAULT == pMsg->wConSlot, errItemInvalidPos);
	LOG_PROCESS_ERROR_RET_CODE(poRole->GetItemBag()->GetMoney(MONEYTYPE_02) >= g_GuildConfig.nGuildPopItemComsumeMoney, errGuildNotEnoughMoney);

	nRetCode = poRole->GetItemBag()->SubMoney(MONEYTYPE_02, g_GuildConfig.nGuildPopItemComsumeMoney, MONEYLOG_GUILD_POP_ITEM, 0);
	LOG_PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, errGuildNotEnoughMoney);

	nRetCode = CCliMessageHandler::GetInstance().DoMSGuildPopItem(errSuccess, pMsg->dwRoleID, pMsg->byConSlot, pMsg->bySlot, pMsg->wConSlot, pMsg->wSlot);
	LOG_CHECK_ERROR(nRetCode);

	return ;
Exit0:
	nRetCode = CCliMessageHandler::GetInstance().DoMSGuildPopItem(nResult, pMsg->dwRoleID, pMsg->byConSlot, pMsg->bySlot, pMsg->wConSlot, pMsg->wSlot);
	LOG_CHECK_ERROR(nRetCode);
	return ; 
}

void CGSMessageHandler::OnMSGuildPopItemAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32       nRetCode = 0;
	INT32       nResult = errUnknownError;
	ItemInfo    iteminfo;
	Item        *pItem = NULL;
	CRole*      poRole = NULL;
    INT32       nItemLength = 0;
	M2G_GUILD_POP_ITEM_ACK *pMsg = (M2G_GUILD_POP_ITEM_ACK*)pPacketBuffer;

	poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole);

    nItemLength = iteminfo.Load(pMsg->buff);
    LOG_PROCESS_ERROR(nItemLength == pMsg->nLength);
	pItem = CItemMgr::GetInstance().LoadItem(iteminfo);
    if (pItem == NULL)
        CRI("LoadItem Failed: RoleID:%u, GUID:%I64u, TemplateID:%d, Dur:%d", poRole->GetObjID(), iteminfo.m_llGuid, iteminfo.m_nTemplateID, iteminfo.m_nCurDur);
	LOG_PROCESS_ERROR(pItem);

    nRetCode = poRole->GetItemBag()->AddItemToDefaultCon(pItem, pMsg->wConSlot, pMsg->wSlot, ITEMLOG_GUILD_STORAGE);
    LOG_PROCESS_ERROR_RET_CODE(errSuccess == nRetCode, nRetCode);

	return ;
Exit0:
    if (pItem != NULL)
    {
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(pItem);
        LOG_CHECK_ERROR(bItemRet);
        CRI("Guild Storage Pop Item, target pos has item, destroy one: RoleID:%u, GUID:%I64u, TemplateID:%d, Dur:%d", poRole->GetObjID(), 
            iteminfo.m_llGuid, iteminfo.m_nTemplateID, iteminfo.m_nCurDur);
    }
    if (nResult != errUnknownError)
        poRole->ErrorCodeNotify(nResult, 0, 0);
    return;
}

void CGSMessageHandler::OnMSGuildUpgradeBuildingNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    CGSGuild    *poGSGuild = NULL;
    CScene      *poScene = NULL;
    GS_G_B_DATA *pGSBuilding = NULL;
    const NPC_SPAWN_POINT   *pSpawnPoint = NULL;
    CNpc        *poNpc = NULL;

    M2G_GUILD_UPDATE_BUILDING_NTF *pMsg = (M2G_GUILD_UPDATE_BUILDING_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

    pGSBuilding = poGSGuild->GetUpgradBuildingDataByNpcID(pMsg->qwNameID);
    LOG_PROCESS_ERROR(!pGSBuilding);

    nRetCode = poGSGuild->AddUpgradeBuilding(pMsg->qwNameID, pMsg->nType, pMsg->nLevel);
    LOG_PROCESS_ERROR(nRetCode);
    
    poScene = CGameWorld::GetInstance().FindScene(MakeSceneObjID(g_GuildConfig.dwSceneTemplateID, pMsg->dwGuildID));
    if (poScene)
    {
        pSpawnPoint = poScene->GetStaticData()->GetSingleNpcByName(pMsg->qwNameID);
        LOG_PROCESS_ERROR(pSpawnPoint);

        poNpc = poScene->FindNpc(pSpawnPoint->nID);
        LOG_PROCESS_ERROR(poNpc);

        poScene->SetVariable(1, pSpawnPoint->nID);
        poScene->SetVariable(2, pMsg->nType);
        poScene->SetVariable(3, pMsg->nLevel);

        if (poScene->GetStaticData()->GetBT(evtGuildBuildingUpgrade))
        {
            nRetCode = poScene->RunBT(evtGuildBuildingUpgrade, 0, poScene->GetStaticData()->GetBT(evtGuildBuildingUpgrade));
            LOG_CHECK_ERROR(nRetCode);
        }
    }

    return ;
Exit0:
    return ;  
}

void CGSMessageHandler::OnMSGuildUpdateBuildingLevel(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32       nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;
    CScene      *poScene = NULL;
    GS_G_B_DATA *pGSBuilding = NULL;
    const NPC_SPAWN_POINT   *pSpawnPoint = NULL;
    CNpc        *poNpc = NULL;

	M2G_GUILD_UPDATE_BUILDING_NTF *pMsg = (M2G_GUILD_UPDATE_BUILDING_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

    pGSBuilding = poGSGuild->GetBuildingDataByNpcID(pMsg->qwNameID);
    if (pGSBuilding)
    {
        pGSBuilding->nLevel = pMsg->nLevel;
        PROCESS_ERROR(pGSBuilding->dwReviveTime == 0);
    }
    else
    {
        nRetCode = poGSGuild->AddBuilding(pMsg->qwNameID, pMsg->nType, pMsg->nLevel);
        LOG_PROCESS_ERROR(nRetCode);
    }

    // del upgrading data
    poGSGuild->DelUpgradeBuilding(pMsg->qwNameID);

    poScene = CGameWorld::GetInstance().FindScene(MakeSceneObjID(g_GuildConfig.dwSceneTemplateID, pMsg->dwGuildID));
    if (poScene)
    {
        pSpawnPoint = poScene->GetStaticData()->GetSingleNpcByName(pMsg->qwNameID);
        LOG_PROCESS_ERROR(pSpawnPoint);

        poNpc = poScene->FindNpc(pSpawnPoint->nID);
        LOG_PROCESS_ERROR(poNpc);

        poScene->SetVariable(1, pSpawnPoint->nID);
        poScene->SetVariable(2, pMsg->nType);
        poScene->SetVariable(3, pMsg->nLevel);

        if (poScene->GetStaticData()->GetBT(evtGuildBuildingUpdate))
        {
            nRetCode = poScene->RunBT(evtGuildBuildingUpdate, 0, poScene->GetStaticData()->GetBT(evtGuildBuildingUpdate));
            LOG_CHECK_ERROR(nRetCode);
        }
    }

	return ;
Exit0:
	return ;  
}

void CGSMessageHandler::OnMSGuildDelBuilding(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    CGSGuild    *poGSGuild = NULL;
    CScene      *poScene = NULL;
    const NPC_SPAWN_POINT   *pSpawnPoint = NULL;
    CNpc        *poNpc = NULL;

    M2G_GUILD_DEL_BUILDING_NTF *pMsg = (M2G_GUILD_DEL_BUILDING_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

    poGSGuild->DelUpgradeBuilding(pMsg->qwNameID);
    poGSGuild->DelBuilding(pMsg->qwNameID);

    poScene = CGameWorld::GetInstance().FindScene(MakeSceneObjID(g_GuildConfig.dwSceneTemplateID, pMsg->dwGuildID));
    if (poScene)
    {
        pSpawnPoint = poScene->GetStaticData()->GetSingleNpcByName(pMsg->qwNameID);
        LOG_PROCESS_ERROR(pSpawnPoint);

        poNpc = poScene->FindNpc(pSpawnPoint->nID);
        LOG_PROCESS_ERROR(poNpc);

        poScene->SetVariable(1, pSpawnPoint->nID);
        poScene->SetVariable(2, pMsg->nType);
        poScene->SetVariable(3, 0);

        if (poScene->GetStaticData()->GetBT(evtGuildBuildingDel))
        {
            nRetCode = poScene->RunBT(evtGuildBuildingDel, 0, poScene->GetStaticData()->GetBT(evtGuildBuildingDel));
            LOG_CHECK_ERROR(nRetCode);
        }
    }

    return ;
Exit0:
    return ;  
}

void CGSMessageHandler::OnMSGuildSyncBuildingStateNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    INT32       nResult = errUnknownError;
    CGSGuild    *poGSGuild = NULL;
    GS_G_B_DATA *pBuilding = NULL;

    CScene      *poScene = NULL;
    const NPC_SPAWN_POINT   *pSpawnPoint = NULL;
    CNpc        *poNpc = NULL;

    M2G_GUILD_SYNC_BUILDING_STATE_NTF *pMsg = (M2G_GUILD_SYNC_BUILDING_STATE_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

    pBuilding = poGSGuild->GetBuildingDataByNpcID(pMsg->qwNameID);
    LOG_PROCESS_ERROR(pBuilding);

    pBuilding->dwReviveTime = pMsg->dwReviveTime;

    // revive, update building
    if (pBuilding->dwReviveTime == 0)
    {
        poScene = CGameWorld::GetInstance().FindScene(MakeSceneObjID(g_GuildConfig.dwSceneTemplateID, pMsg->dwGuildID));
        if (poScene)
        {
            pSpawnPoint = poScene->GetStaticData()->GetSingleNpcByName(pMsg->qwNameID);
            LOG_PROCESS_ERROR(pSpawnPoint);

            poNpc = poScene->FindNpc(pSpawnPoint->nID);
            LOG_PROCESS_ERROR(poNpc);

            poScene->SetVariable(1, pSpawnPoint->nID);
            poScene->SetVariable(2, pBuilding->nType);
            poScene->SetVariable(3, pBuilding->nLevel);

            if (poScene->GetStaticData()->GetBT(evtGuildBuildingUpdate))
            {
                nRetCode = poScene->RunBT(evtGuildBuildingUpdate, 0, poScene->GetStaticData()->GetBT(evtGuildBuildingUpdate));
                LOG_CHECK_ERROR(nRetCode);
            }
        }
    }

    return;
Exit0:
    return;
}

void CGSMessageHandler::OnMSGuildUpdateWelfareID(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32       nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;
	M2G_GUILD_UPDATE_WELFARE_NTF *pMsg = (M2G_GUILD_UPDATE_WELFARE_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

	nRetCode = poGSGuild->SetWelfareLevelByType(pMsg->nType, pMsg->nLevel);
	LOG_PROCESS_ERROR(nRetCode);

	return ;
Exit0:
	return ; 
}

void CGSMessageHandler::OnMSGuildUpdateState(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32   nRetCode = 0;
    INT32   nResult = errUnknownError;
    CRole *poRole = NULL;
    CGSGuild        *poGSGuild = NULL;

    M2G_GUILD_UPDATE_STATE_NTF *pMsg = (M2G_GUILD_UPDATE_STATE_NTF*)pPacketBuffer;

    poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGSGuild);

    poGSGuild->SetState(pMsg->nState);

    return ;
Exit0:
    return ;
}

void CGSMessageHandler::OnMSGuildChangePosition(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    CRole       *poRole = NULL;
    CGSGuild    *poGSGuild = NULL;
    
    M2G_GUILD_CHANGE_POSITION_NTF   *pMsg = (M2G_GUILD_CHANGE_POSITION_NTF*)pPacketBuffer;

    if (pMsg->nPosition == GUILD_POSITION_LEADER)
    {
        poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
        LOG_PROCESS_ERROR(poGSGuild);

        poGSGuild->SetLeaderID(pMsg->dwRoleID);
    }

    return ;
Exit0:
    return ;
}

void CGSMessageHandler::OnMSGuildPreOpenDungeonAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    INT32       nResult = errUnknownError;
    CRole       *poRole = NULL;

    M2G_GUILD_PRE_OPEN_DUNGEON_ACK  *pMsg = (M2G_GUILD_PRE_OPEN_DUNGEON_ACK*)pPacketBuffer;

    poRole = CGameWorld::GetInstance().FindRole(pMsg->dwOwnerID);
    LOG_PROCESS_ERROR(poRole);

    PROCESS_ERROR_RET_CODE(pMsg->nConsumeMoney <= poRole->GetItemBag()->GetMoney(MONEYTYPE_02), errNotEnoughMoney);

    nRetCode = poRole->GetItemBag()->SubMoney(MONEYTYPE_02, pMsg->nConsumeMoney, MONEYLOG_OPEN_GUILD_DUNGEON, 0);
    PROCESS_ERROR_RET_CODE(errSuccess == nRetCode, nRetCode);

    nRetCode = CCliMessageHandler::GetInstance().DoMSGuildOpenDungeon(pMsg->dwOwnerID, pMsg->dwLeaderID, pMsg->dwTemplateID);
    LOG_PROCESS_ERROR_RET_CODE(nRetCode, errGuildMsgError);

    return ;
Exit0:
    if (nResult != errUnknownError)
        poRole->ErrorCodeNotify(nResult, 0, 0);
    return;
}

void CGSMessageHandler::OnMSGuildEnterDungeon(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    INT32       nResult = errUnknownError;
    CRole       *poRole = NULL;
    CTeamInGS     *poTeam = NULL;
    const GUILD_DUNGEON_DATA *pTemplate = NULL;
    INT32       nTeamMemberCount = 0;
    BOOL        bLeaderInTeam = FALSE;

    M2G_GUILD_ENTER_DUNGEON *pMsg = (M2G_GUILD_ENTER_DUNGEON*)pPacketBuffer;

    poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(poRole);
    LOG_PROCESS_ERROR_RET_CODE(poRole->GetGuildID() != 0, errGuildNoGuild);

    poTeam = CGameWorld::GetInstance().FindTeam(poRole->GetTeamID());
    LOG_PROCESS_ERROR_RET_CODE(poTeam, errTeamNotInTeam);

    nTeamMemberCount = poTeam->GetMemberCount();
    for (INT32 i = 0; i < nTeamMemberCount; ++i)
    {
        TeamMember &rMember = poTeam->GetMemberTable(i);
        if (rMember.dwRoleID == pMsg->dwDungeonLeaderID)
            bLeaderInTeam = TRUE;
    }
    LOG_PROCESS_ERROR_RET_CODE(bLeaderInTeam, errGuildNotDungeonLeader);

    pTemplate = GetGuildDungeonData(pMsg->dwTemplateID);
    LOG_PROCESS_ERROR(pTemplate);

    LOG_PROCESS_ERROR_RET_CODE(poRole->GetItemBag()->GetMoney(MONEYTYPE_FATIGUE) >= pTemplate->nFatigueComsume, errSceneNoFatigue);
    LOG_PROCESS_ERROR_RET_CODE(poRole->GetLevel() >= pTemplate->nConditionLevel, errSceneNoLevel);

    nRetCode = poRole->GetItemBag()->SubMoney(MONEYTYPE_FATIGUE, pTemplate->nFatigueComsume, MOMEYLOG_GUILD_ENTER_DUNGEON, 0);
    LOG_PROCESS_ERROR_RET_CODE(errSuccess == nRetCode, nRetCode);

    //if (0 == poRole->GetTeamID())
    {
        nRetCode = CGameWorld::GetInstance().JumpTo(poRole, pMsg->dwTemplateID, poRole->GetGuildID(),
            pTemplate->nPosX, pTemplate->nPosY, pTemplate->nPosZ, pTemplate->nDirection);
        LOG_PROCESS_ERROR_RET_CODE(nRetCode, errGuildEnterDungeonFailed);
    }
    //else
    //{
    //    poTeam = CGameWorld::GetInstance().FindTeam(poRole->GetTeamID());
    //    LOG_PROCESS_ERROR(poTeam);

    //    for (INT32 nIndex = 0; nIndex < poTeam->GetMaxMemberCount(); nIndex++)
    //    {
    //        CRole* poMemeber = CGameWorld::GetInstance().FindRole(poTeam->GetMemberTable(nIndex).dwRoleID);
    //        if (poMemeber)
    //        {
    //            if (poMemeber->GetGuildID() == poRole->GetGuildID())
    //            {
    //                nRetCode = CGameWorld::GetInstance().JumpTo(poMemeber, pMsg->dwTemplateID, poMemeber->GetGuildID(), 0, 2, 
    //                    pTemplate->nPosX, pTemplate->nPosY, pTemplate->nPosZ, pTemplate->nDirection);
    //                LOG_CHECK_ERROR(nRetCode);
    //            }
    //        }
    //    }
    //}

    return ;
Exit0:
    if (nResult != errUnknownError)
        poRole->ErrorCodeNotify(nResult, 0, 0);
    return;
}

void CGSMessageHandler::OnMSGuildSyncWarRelation(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    INT32       nResult = errUnknownError;
    CScene      *poScene = NULL;
    M2G_GUILD_SYNC_WAR_RELATION *pMsg = (M2G_GUILD_SYNC_WAR_RELATION*)pPacketBuffer;
    LOG_PROCESS_ERROR(pMsg);

    nRetCode = CGuildMgr::GetInstance().AddWarRelation(pMsg->dwIntruderID, pMsg->dwDefenderID);
    LOG_PROCESS_ERROR(nRetCode);

    poScene = CGameWorld::GetInstance().FindScene(MakeSceneObjID(g_GuildConfig.dwSceneTemplateID, pMsg->dwDefenderID));
    PROCESS_ERROR(poScene);

    // end
    if (poScene && poScene->GetStaticData() && poScene->GetStaticData()->GetBT(evtGuildWarBegin))
    {
        nRetCode = poScene->RunBT(evtGuildWarBegin, 0, poScene->GetStaticData()->GetBT(evtGuildWarBegin));
        LOG_CHECK_ERROR(nRetCode);
    }

    return;
Exit0:
    return;
}

void CGSMessageHandler::OnMSGuildSyncWarCharacter(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    INT32       nResult = errUnknownError;
    CGSGuild    *poGuild = NULL;
    M2G_GUILD_SYNC_WAR_CHAR *pMsg = (M2G_GUILD_SYNC_WAR_CHAR*)pPacketBuffer;
    LOG_PROCESS_ERROR(pMsg);

    poGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGuild);

    poGuild->SetWarCharacter(pMsg->byCharacter);

    return;
Exit0:
    return;
}

void CGSMessageHandler::OnMSGuildChangeResAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    CGSGuild    *poGuild = NULL;
    CNpc        *poNpc = NULL;
    M2G_GUILD_CHANGE_RES_ACK    *pMsg = (M2G_GUILD_CHANGE_RES_ACK*)pPacketBuffer;

    poNpc = CGameWorld::GetInstance().FindNpc(pMsg->dwNpcID);
    PROCESS_ERROR(poNpc);

    poGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    LOG_PROCESS_ERROR(poGuild);

    LOG_PROCESS_ERROR(poNpc->GetAIProcessor());

    if (pMsg->byCtxType == 0)
    {
        LOG_PROCESS_ERROR(poNpc->GetAIProcessor()->GetBTCustomCtx().eRunningType == brtWaitMSGuildData);
        poNpc->GetAIProcessor()->GetBTCustomCtx().eRunningType = brtInvalid;
        poNpc->GetAIProcessor()->GetBTCustomCtx().returnValue = brvSuccess;
    }
    else
    {
        LOG_PROCESS_ERROR(poNpc->GetAIProcessor()->GetBTDieCtx().eRunningType == brtWaitMSGuildData);
        poNpc->GetAIProcessor()->GetBTDieCtx().eRunningType = brtInvalid;
        poNpc->GetAIProcessor()->GetBTDieCtx().returnValue = brvSuccess;
    }
        


    if (pMsg->bAdd == FALSE)        // dec
    {
        poNpc->GetAIProcessor()->SetVariable(0, 2); // success
        poNpc->GetAIProcessor()->SetVariable(1, pMsg->nCount);
    }

Exit0:
    return;
}

void CGSMessageHandler::OnMSGuildWarEnd(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    CScene      *poScene = NULL;
    M2G_GUILD_WAR_END *pMsg = (M2G_GUILD_WAR_END*)pPacketBuffer;

    poScene = CGameWorld::GetInstance().FindScene(MakeSceneObjID(g_GuildConfig.dwSceneTemplateID, pMsg->dwDefenderID));
    PROCESS_ERROR(poScene);

    // 陈凯说，现在不用锁定了。结束了也随便他们杀
    //nRetCode = GuildWarLockRole(poScene);
    //LOG_PROCESS_ERROR(nRetCode);

    // end
    if (poScene->GetStaticData() && poScene->GetStaticData()->GetBT(evtGuildWarEnd))
    {
        nRetCode = poScene->RunBT(evtGuildWarEnd, 0, poScene->GetStaticData()->GetBT(evtGuildWarEnd));
        LOG_CHECK_ERROR(nRetCode);
    }

Exit0:
    return;
}

void CGSMessageHandler::OnMSGuildSyncMemberSalaryNtf(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    INT32       nResult = errUnknownError;
    CGSGuild    *poGSGuild = NULL;
    CRole       *poRole = NULL;
    M2G_GUILD_SYNC_MEMBER_SALARY_NTF    *pMsg = (M2G_GUILD_SYNC_MEMBER_SALARY_NTF*)pPacketBuffer;

    //poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
    //LOG_PROCESS_ERROR(poGSGuild);

    poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(poRole);

    poRole->GetRoleGuildData().SetSalary(pMsg->nSalary);

    return ;
Exit0:
    return ;
}

void CGSMessageHandler::OnMSSyncRoleSocialData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32   nRetCode = 0;
	INT32   nResult = errUnknownError;
	CRole *poRole = NULL;

	M2G_SYNC_ROLE_SOCIAL_DATA   *pMsg = (M2G_SYNC_ROLE_SOCIAL_DATA*)pPacketBuffer;
	LOG_PROCESS_ERROR(pMsg);

	poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole);

	poRole->SetGuildID(pMsg->dwGuildID);
    poRole->SetForbidChatTime(pMsg->dwForbidChatTime);

	return ;
Exit0:
	return ;
}

void CGSMessageHandler::OnMSGuildAchievementReward(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    INT32       nResult = errUnknownError;
    CRole       *poRole = NULL;
    const GUILD_ACHIEVEMENT *pData = NULL;
    M2G_GUILD_ACHIEVEMENT_REWARD    *pMsg = (M2G_GUILD_ACHIEVEMENT_REWARD*)pPacketBuffer;

    pData = GetGuildAchievement(pMsg->nID);
    LOG_PROCESS_ERROR(pData);

    poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(poRole);

    nRetCode = poRole->GetRoleGuildData().SetAchievementReward(pMsg->nID);
    LOG_PROCESS_ERROR(nRetCode);

    for (INT32 i = 0; i < GuildAchiAwardTableSize; ++i)
    {
        if (pData->AwardData[i].nAwardType == 0)
            continue;
        LOG_PROCESS_ERROR(pData->AwardData[i].nAwardType > GA_AWARD_NONE && pData->AwardData[i].nAwardType < GA_AWARD_NUM);
        switch ((GUILD_ACHIEVEMENT_AWARD_TYPE)pData->AwardData[i].nAwardType)
        {
        case GA_AWARD_POINT:
        {
            nRetCode = poRole->GetItemBag()->AddMoney(MONEYTYPE_ACHIEVEMENTPTS, pData->AwardData[i].nNum, EMoneyLog::MONEYLOG_ACHIEVEMENT_REWARD, 0);
            LOG_CHECK_ERROR(nRetCode == errSuccess);
        }
            break;
        case GA_AWARD_EXP:
        {
            poRole->AddExp(pData->AwardData[i].nNum, FALSE, TRUE);
        }
            break;
        case GA_AWARD_ITEM:
        {
            nRetCode = poRole->GetItemBag()->AddItem(pData->AwardData[i].dwTemplateID, pData->AwardData[i].nNum, EItemLog::ITEMLOG_ACHIEVEMENT_REWARD, 0, FALSE);
            LOG_CHECK_ERROR(nRetCode == errSuccess);
        }
            break;
        case GA_AWARD_TITLE:
        {
            nRetCode = poRole->GetTitle().AddTitle(pData->AwardData[i].dwTemplateID);
            LOG_CHECK_ERROR(nRetCode);
        }
            break;
        default:
            break;
        }
    }

    nRetCode = CCliMessageHandler::GetInstance().DoSyncGuildAchievement(poRole);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = poRole->ErrorCodeNotify( errGuildAchiRewardSucc, pMsg->nID, 0);
    LOG_CHECK_ERROR(nRetCode);

    return;
Exit0:
    if (poRole)
    {
        nRetCode = poRole->ErrorCodeNotify(nResult, 0, 0);
        LOG_CHECK_ERROR(nResult);
    }
    return;
}


void CGSMessageHandler::OnMSEnrollSabac(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_ENROLL_SABAC* pMsg = (M2G_ENROLL_SABAC*)pPacketBuffer;

	CGSGuild* poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
	LOG_PROCESS_ERROR(poGSGuild);

	poGSGuild->SetSabacEnrollTime(pMsg->dwEnrollTime);
	CSabacMgr::GetInstance().Enroll(pMsg->dwGuildID, pMsg->dwEnrollTime, poGSGuild->GetServerGroup());

	return;
Exit0:
	return;
}

void CGSMessageHandler::OnMSOccupySabac(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_OCCUPY_SABAC* pMsg = (M2G_OCCUPY_SABAC*)pPacketBuffer;

	CGSGuild* poOldGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwOldGuildID);
	if (poOldGSGuild)
	{
		poOldGSGuild->OccupySabac(FALSE);
	}

	CGSGuild* poNewGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwNewGuildID);
	if (poNewGSGuild)
	{
		poNewGSGuild->OccupySabac(TRUE);
		CSabacMgr::GetInstance().SetOccupyGuildID(poNewGSGuild->GetServerGroup(), pMsg->dwNewGuildID);
	}

	return;
Exit0:
	return;
}

void CGSMessageHandler::OnMSJumpArenaScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    CSceneStaticData* pStaticData = NULL;
    const SERVER_POINT* pServerPoint = NULL;
    CHAR szServerPointName[COMMON_NAME_LEN] = { 0 };
    M2G_JUMP_ARENA_SCENE* pMsg = (M2G_JUMP_ARENA_SCENE*)pPacketBuffer;

    CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(poRole);

    pStaticData = CSceneFileMgr::GetInstance().GetStaticData(pMsg->dwSceneTempID);
    LOG_PROCESS_ERROR(pStaticData);

    snprintf(szServerPointName, COMMON_NAME_LEN, "%s%d", ENTER_POS_SIDE_NAME, pMsg->bySide);
    pServerPoint = pStaticData->GetServerPoint(szServerPointName);
    LOG_PROCESS_ERROR(pServerPoint);

    nRetCode = CGameWorld::GetInstance().JumpTo(poRole, pMsg->dwSceneTempID, pMsg->dwSceneID, 
        pServerPoint->nX, pServerPoint->nY, pServerPoint->nZ, 0);
    LOG_PROCESS_ERROR(nRetCode);

    return;
Exit0:
    return;
}

void CGSMessageHandler::OnMSArenaReward(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32   nRetCode = 0;
    INT32   nResult = errUnknownError;
    CRole *poRole = NULL;

    M2G_ARENA_REWARD   *pMsg = (M2G_ARENA_REWARD*)pPacketBuffer;
    LOG_PROCESS_ERROR(pMsg);

    poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(poRole);

    nRetCode = poRole->GetArena().GetCommonReward(pMsg->dwItemID, pMsg->nMoney);
    LOG_PROCESS_ERROR(nRetCode);

    return ;
Exit0:
    return ;
}

void CGSMessageHandler::OnMSShield(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32   nResult = errUnknownError;
	INT32   nRetCode = 0;
	CRole   *poRole = NULL;

	M2G_SHIELD* pMsg = (M2G_SHIELD*)pPacketBuffer;
	LOG_PROCESS_ERROR(pMsg);

	poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole);
	PROCESS_ERROR_RET_CODE(!poRole->GetShieldList()->IsAlreadyShielded(pMsg->dwTargetRoleID), errAlreadyShield);
	LOG_PROCESS_ERROR_RET_CODE(!poRole->GetShieldList()->IsShieldedListFull(), errShieldedListFull);

	poRole->GetShieldList()->ShieldRole(pMsg->dwTargetRoleID);

	nRetCode = CCliMessageHandler::GetInstance().DoShieldAck(poRole, pMsg->dwTargetRoleID, pMsg->szTargetRoleName);
	LOG_PROCESS_ERROR(nRetCode);

	return ;
Exit0:
	if (nResult != errUnknownError)
		poRole->ErrorCodeNotify(nResult, 0, 0);
	return ; 
}

void CGSMessageHandler::OnMSSyncGMData(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32       nRetCode = 0;
    CRole       *poRole = NULL;

    M2G_SYNC_GM_DATA    *pMsg = (M2G_SYNC_GM_DATA*)pPacketBuffer;
    LOG_PROCESS_ERROR(pMsg);

    poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(poRole);

    poRole->SetForbidChatTime(pMsg->dwForbidChatTime);


    return ;
Exit0:
    return ; 
}

void CGSMessageHandler::OnMSUpdateStatisticVariable(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32   nResult = errUnknownError;
	INT32   nRetCode = 0;

	CRole* poRole = NULL;

	M2G_UPDATE_STATISTIC_VALUE* pMsg = (M2G_UPDATE_STATISTIC_VALUE*)pPacketBuffer;
	LOG_PROCESS_ERROR(pMsg);

	poRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwID);
	LOG_PROCESS_ERROR(poRole);

	switch (pMsg->dwType)
	{
	case vtRole:
		break;
	case vtAchievement:
		{
			LOG_PROCESS_ERROR(pMsg->dwIndex > avdInvalid && pMsg->dwIndex < avdTotal);
			poRole->GetAchievementList().AddVariable(pMsg->dwIndex, pMsg->nValue);
		}
		break;
	default:
		LOG_PROCESS_ERROR(FALSE);
		break;
	}

	return ;
Exit0:
	return ; 
}

BOOL CGSMessageHandler::_CallDebugGMCommand(CRole* poRole, const char* pcszCommand)
{
	INT32       nRetCode = 0;
	CLuaScript* poScript = NULL;
	BOOL        bGMRet = FALSE;
    UINT32      dwTime = CGameWorld::GetInstance().GetGameTime();

	if (strnicmp(pcszCommand, "reload", sizeof("reload") - 1) == 0)
	{
		if (strlen(pcszCommand) > sizeof("reload"))
			CGameWorld::GetInstance().Reload(pcszCommand  + sizeof("reload"));
		else
			CGameWorld::GetInstance().Reload("all");
	}
	else if (strnicmp(pcszCommand, "run", sizeof("run") - 1) == 0)
	{
		if (strlen(pcszCommand) > sizeof("run"))
		{
			poScript = CScriptMgr::GetInstance().FindScript(GM_SCRIPT_NAME);
			LOG_PROCESS_ERROR(poScript);

			nRetCode = poScript->CallFunction("OnRunScript", "s:b", pcszCommand + sizeof("run"), &bGMRet);
			LOG_PROCESS_ERROR(nRetCode && bGMRet);
		}
	}
	else
	{
		poScript = CScriptMgr::GetInstance().FindScript(GM_SCRIPT_NAME);
		LOG_PROCESS_ERROR(poScript);

		if (poRole)
		{
			tolua_pushusertype(poScript->GetLuaState(), poRole, "CRole");
			lua_setglobal(poScript->GetLuaState(), "TargetRole");
		}
		else
		{
			lua_pushnil(poScript->GetLuaState());
			lua_setglobal(poScript->GetLuaState(), "TargetRole");
		}

		nRetCode = poScript->CallFunction("OnNewGMCommand", "s:b", pcszCommand, &bGMRet);
		LOG_PROCESS_ERROR(nRetCode);
		LOG_PROCESS_ERROR(bGMRet);
		
		INF("role %s executed gm command %s", poRole->GetName(), pcszCommand);
	}

    //nRetCode = CGSMessageHandler::GetInstance().DoMSGMLog(dwTime, poRole->GetObjID(), errGMSuccess, pcszCommand);
    //LOG_CHECK_ERROR(nRetCode);

	return TRUE;
Exit0:
    if (poRole)
    {
        CRI("role %s failed to execute gm command %s", poRole->GetName(), pcszCommand);

        //nRetCode = CGSMessageHandler::GetInstance().DoMSGMLog(dwTime, poRole->GetObjID(), (nRetCode == errSuccess) ? errGMStrCommandFailed : errGMStrCmdExeFailed, pcszCommand);
        //LOG_PROCESS_ERROR(nRetCode);
    }

	return FALSE;
}

BOOL CGSMessageHandler::_CallFinalGMCommand(CRole* poRole, const char* pcszCommand)
{
	INT32 nRetCode = 0;
	CLuaScript* poScript = NULL;
	BOOL bGMRet = FALSE;
	INT32 nGMLevel = 100;
    UINT32  dwTime = CGameWorld::GetInstance().GetGameTime();

	if (poRole)
		nGMLevel = poRole->GetGMLevel();

	if (strnicmp(pcszCommand, "reload", sizeof("reload") - 1) == 0)
	{
		LOG_PROCESS_ERROR(nGMLevel == MAX_GM_LEVEL);

		if (strlen(pcszCommand) > sizeof("reload"))
			CGameWorld::GetInstance().Reload(pcszCommand + sizeof("reload"));
		else
			CGameWorld::GetInstance().Reload("all");
	}
	else if (strnicmp(pcszCommand, "run", sizeof("run") - 1) == 0)
	{
		LOG_PROCESS_ERROR(nGMLevel == MAX_GM_LEVEL);

		if (strlen(pcszCommand) > sizeof("run"))
		{
			poScript = CScriptMgr::GetInstance().FindScript(GS_CS_SCRIPT_NAME);
			LOG_PROCESS_ERROR(poScript);

			nRetCode = poScript->CallFunction("OnRunScript", "s:b", pcszCommand + sizeof("run"), &bGMRet);
			LOG_PROCESS_ERROR(nRetCode && bGMRet);
		}
	}
	else
	{
		LOG_PROCESS_ERROR(poRole);

		poScript = CScriptMgr::GetInstance().FindScript(GS_CS_SCRIPT_NAME);
		LOG_PROCESS_ERROR(poScript);

		tolua_pushusertype(poScript->GetLuaState(), poRole, "CRole");
		lua_setglobal(poScript->GetLuaState(), "role");

		nRetCode = poScript->CallFunction("OnGSCommand", "s:b", pcszCommand, &bGMRet);
		LOG_PROCESS_ERROR(nRetCode && bGMRet);

		//nRetCode = CGSMessageHandler::GetInstance().DoMSCSCmdAck(poRole->GetObjID(), 
		//	CGameWorld::GetInstance().GetGameTime(), errSuccess, pcszCommand);
		//LOG_CHECK_ERROR(nRetCode);
	}

    if (poRole)
        INF("role %s:%d executed gm command %s", poRole->GetName(), poRole->GetObjID(), pcszCommand);
	else
		INF("role guard:0 executed gm command %s", pcszCommand);

	return TRUE;
Exit0:
    if (poRole)
        INF("role %s:%d failed to execute gm command %s", poRole->GetName(), poRole->GetObjID(), pcszCommand);
	else
		INF("role guard:0 failed to execute gm command %s", pcszCommand);

	return FALSE;
}

void CGSMessageHandler::OnMSCallGsGMCommand(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
	INT32       nRetCode = 0;
	CRole       *poRole = NULL;
	M2G_CALL_GM_COMMAND *pMsg = (M2G_CALL_GM_COMMAND*)pPacketBuffer;

	if (pMsg->dwRoleID != 0)
	{
		poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
		LOG_PROCESS_ERROR(poRole);
	}

#ifdef _FINAL
	nRetCode = _CallFinalGMCommand(poRole, pMsg->szGMCommand);
	LOG_PROCESS_ERROR(nRetCode);
#else
	nRetCode = _CallDebugGMCommand(poRole, pMsg->szGMCommand);
	LOG_PROCESS_ERROR(nRetCode);
#endif	// _FINAL

	return ;
Exit0:
	return;
}

void CGSMessageHandler::OnMSDropLimit(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
	M2G_DROP_LIMIT* pMsg = (M2G_DROP_LIMIT*)pPacketBuffer;
	LOG_PROCESS_ERROR(pMsg);

	CDropGenerator::GetInstance().SetDropLimit(pMsg->nItemID, pMsg->nLimit);

Exit0:
	return;
}

void CGSMessageHandler::OnMSAuctionSell(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
	M2G_AUCTION_SELL* pMsg = (M2G_AUCTION_SELL*)pPacketBuffer;

	CRole* pRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	if (pRole == NULL)
	{
		CCliMessageHandler::GetInstance().DoMSAuctionSell(errUnknownError, pMsg->dwRoleID, pMsg->byAuctionTimeType, pMsg->byOpen, pMsg->llPrice, pMsg->llBuyoutPrice, pMsg->llDepositePrice, NULL, 0);
	}
	else
	{
		INT32 err = pRole->GetItemBag()->AuctionSell(pMsg->byConSlot, pMsg->byItemSlot, pMsg->byAuctionTimeType, pMsg->byOpen, pMsg->llPrice, pMsg->llBuyoutPrice, pMsg->llDepositePrice);
		if (err != errSuccess)
			CCliMessageHandler::GetInstance().DoMSAuctionSell(err, pMsg->dwRoleID, pMsg->byAuctionTimeType, pMsg->byOpen, pMsg->llPrice, pMsg->llBuyoutPrice, pMsg->llDepositePrice, NULL, 0);
	}
}

void CGSMessageHandler::OnMSAuctionBuy(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
	M2G_AUCTION_BUY* pMsg = (M2G_AUCTION_BUY*)pPacketBuffer;

	CRole* pRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	if (pRole == NULL)
	{
		CCliMessageHandler::GetInstance().DoMSAuctionBuy(errUnknownError, pMsg->dwRoleID, pMsg->dwAuctionID, pMsg->llBidPrice);
	}
	else
	{
		INT32 err = pRole->GetItemBag()->AuctionBuy(pMsg->dwAuctionID, pMsg->llBidPrice, pMsg->llAuctionPrice, pMsg->llDepositPrice, pMsg->byBuyType);
		if (err != errSuccess)
		{
			CCliMessageHandler::GetInstance().DoMSAuctionBuy(err, pMsg->dwRoleID, pMsg->dwAuctionID, pMsg->llBidPrice);
		}
	}
}

void CGSMessageHandler::OnMSAuctionPay(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	M2G_AUCTION_PAY* pMsg = (M2G_AUCTION_PAY*)pPacketBuffer;

	CRole* pRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	if (pRole == NULL)
	{
		CCliMessageHandler::GetInstance().DoMSAuctionPay(errUnknownError, pMsg->dwRoleID, pMsg->dwAuctionID, pMsg->llPrice);
	}
	else
	{
		INT32 err = pRole->GetItemBag()->AuctionPay(pMsg->dwAuctionID, pMsg->llPrice);
		if (err != errSuccess)
			CCliMessageHandler::GetInstance().DoMSAuctionPay(err, pMsg->dwRoleID, pMsg->dwAuctionID, pMsg->llPrice);
	}
}

void CGSMessageHandler::OnMSExchangeAddOrder(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    M2G_EXCHANGE_ADD_ORDER* pMsg = (M2G_EXCHANGE_ADD_ORDER*)pPacketBuffer;

    CRole* pRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    if (pRole == NULL)
    {
        CCliMessageHandler::GetInstance().DoMSExchangeAddOrder(errUnknownError, pMsg->dwRoleID, pMsg->nItemIDRequire, pMsg->nItemCountRequire, pMsg->byOrderType, pMsg->nPriceOrder, pMsg->nCountOrder);
    }
    else
    {
        INT32 err = pRole->ExchangeAddOrder(pMsg->nItemIDRequire, pMsg->nItemCountRequire, pMsg->byOrderType, pMsg->nPriceOrder, pMsg->nCountOrder);
        if (err != errSuccess)
            CCliMessageHandler::GetInstance().DoMSExchangeAddOrder(err, pMsg->dwRoleID, pMsg->nItemIDRequire, pMsg->nItemCountRequire, pMsg->byOrderType, pMsg->nPriceOrder, pMsg->nCountOrder);
    }
}

void CGSMessageHandler::OnMSCompleteAchievement(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
	INT32 nRetCode = 0;

	M2G_COMPLETE_ACHIEVEMENT* pMsg = (M2G_COMPLETE_ACHIEVEMENT*)pPacketBuffer;

    CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	PROCESS_ERROR(poRole);

	nRetCode = poRole->GetAchievementList().CanComplete(pMsg->nAchievementID);
	PROCESS_ERROR(nRetCode == errSuccess);

	nRetCode = poRole->GetAchievementList().Complete(pMsg->nAchievementID);
	LOG_PROCESS_ERROR(nRetCode);

Exit0:
	return;
}


void CGSMessageHandler::OnMSAdventureReward(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    M2G_ADVENTURE_REWARD* pMsg = (M2G_ADVENTURE_REWARD*)pPacketBuffer;
    CRole* poRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwRoleID);
    const ADVENTURE_DATA* pAdventureData = CDataManager<ADVENTURE_DATA>::GetInstance().GetData(pMsg->nAdventureID);

    if (pAdventureData->nRewardType == adrSpawnNpcAtPoint)
    {
        CAdventure::GetInstance().SpawnNpcAtPoint(pMsg->nServerGroup, pAdventureData);
    }
    else if (pAdventureData->nRewardType == adrSpawnDoodadAtPoint)
    {
        CAdventure::GetInstance().SpawnDoodadAtPoint(pMsg->nServerGroup, pAdventureData);
    }
    else if (poRole)
    {
        CAdventure::GetInstance().TriggerReward(pAdventureData, poRole);
    }
    else
    {
        LOG_PROCESS_ERROR(FALSE);
    }

Exit0:
    return;
}

void CGSMessageHandler::OnMSQueryRoleLocation(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32 nRetCode = 0;
    M2G_QUERY_ROLE_LOCATION* pMsg = (M2G_QUERY_ROLE_LOCATION*)pPacketBuffer;
	CRole* poRole = NULL;
	CRole* poTargetRole = NULL;

    poTargetRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwTargetRoleID);
    PROCESS_ERROR(poTargetRole && poTargetRole->GetScene());

	nRetCode = DoMSQueryRoleLocationAck(pMsg->dwClientSessionID, pMsg->dwRoleID,
		poTargetRole->GetScene()->GetSceneTempID(), poTargetRole->GetScene()->GetSceneID(),
		poTargetRole->GetX(), poTargetRole->GetY(), poTargetRole->GetZ(), pMsg->bFromItem);
	LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	nRetCode = DoMSQueryRoleLocationAck(pMsg->dwClientSessionID, pMsg->dwRoleID,
		0, 0, 0, 0, 0, pMsg->bFromItem);
	LOG_CHECK_ERROR(nRetCode);

    return;
}

void CGSMessageHandler::OnMSQueryRoleLocationAck(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32 nRetCode = 0;
    M2G_QUERY_ROLE_LOCATION_ACK* pMsg = (M2G_QUERY_ROLE_LOCATION_ACK*)pPacketBuffer;
    CRole* poRole = NULL;

    poRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(poRole && poRole->GetSessionID() == pMsg->dwClientSessionID);

	if (pMsg->bFromItem)
	{
		char szMessage[1024];

		if (pMsg->nSceneTempID > 0)
		{
			INT32 nX, nY, nZ;
			nX = pMsg->nX / POINT_PER_CM;
			nY = pMsg->nY / POINT_PER_CM;
			ConvertCoordN2O(nX, nY, nZ);

			LOG_PROCESS_ERROR(poRole->GetScene()->GetSceneData());
			if (poRole->GetScene()->GetSceneData()->nType == estLine)
			{
				snprintf(szMessage, 1024, "line %d (%d, %d)", pMsg->nSceneID & 0xFF, nX / 100, nY / 100);
			}
			else
			{
				snprintf(szMessage, 1024, "(%d, %d)", nX / 100, nY / 100);
			}

			nRetCode = poRole->GetCoolDown().Add(MakeCoolDownID(COOLDOWN_SPECIAL_ITEM, cclProbeNecklace),
				g_GWConfig.nTeleportRingCDTime * GAME_FPS / 1000);
			LOG_PROCESS_ERROR(nRetCode);

			poRole->GetScene()->Say(pMsg->dwRoleID, cltNormal, szMessage);
		}
		else
		{
			nRetCode = poRole->ErrorCodeNotify( errItemRoleNotFound, 0, 0);
			LOG_CHECK_ERROR(nRetCode);
		}
	}
	else
	{
		if (pMsg->nSceneTempID > 0)
		{
			nRetCode = CGameWorld::GetInstance().JumpTo(poRole,
				pMsg->nSceneTempID, pMsg->nSceneID,
				pMsg->nX, pMsg->nY, pMsg->nZ, poRole->GetFaceDirection());
			LOG_PROCESS_ERROR(nRetCode);
		}
	}

Exit0:
    return;
}

void CGSMessageHandler::OnMSTakeRole(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    INT32 nRetCode = 0;
    M2G_TAKE_ROLE* pMsg = (M2G_TAKE_ROLE*)pPacketBuffer;
    CRole* poRole = NULL;

    poRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwRoleID);
    LOG_PROCESS_ERROR(poRole && poRole->GetSessionID() == pMsg->dwClientSessionID);

    nRetCode = CGameWorld::GetInstance().JumpTo(poRole, pMsg->nSceneTempID, pMsg->nSceneID, 
        pMsg->nX, pMsg->nY, pMsg->nZ, poRole->GetFaceDirection());
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return;   
}

void CGSMessageHandler::OnMSArrestRole(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
	INT32 nRetCode = 0;
	M2G_ARREST_ROLE* pMsg = (M2G_ARREST_ROLE*)pPacketBuffer;
	CRole* poRole = NULL;

	poRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poRole && poRole->GetSessionID() == pMsg->dwClientSessionID);

	if (pMsg->nDuration > 0)
	{
		nRetCode = CGameWorld::GetInstance().JumpTo(poRole, g_GWConfig.ArrestConfig.nSceneTempID, 0,
			g_GWConfig.ArrestConfig.Pos.x * POINT_PER_CM,
			g_GWConfig.ArrestConfig.Pos.y * POINT_PER_CM,
			g_GWConfig.ArrestConfig.Pos.z * POINT_PER_CM,
			poRole->GetFaceDirection());
		LOG_PROCESS_ERROR(nRetCode);
	}

	nRetCode = poRole->AddCooldown(MakeCoolDownID(COOLDOWN_MISC, COOLDOWN_MISC_ARREST), pMsg->nDuration);
	LOG_PROCESS_ERROR(nRetCode);

Exit0:
	return;
}

// 玩家查询元宝
void CGSMessageHandler::OnMSQueryRealMoneyRole(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT64 llRealMoney = 0;
	M2G_QUERY_REAL_MONEY_REQ* pMsg = (M2G_QUERY_REAL_MONEY_REQ*)pPacketBuffer;

	CRole* poRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwRoleID);
	if (poRole)
	{
		llRealMoney = poRole->GetItemBag()->GetMoney(MONEYTYPE_04);
	}

	DoMSQueryRealMoneyRole(pMsg->dwCliSessionID, pMsg->dwRoleID, llRealMoney);
}

void CGSMessageHandler::OnMSRealMoneyBuySuccess(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    M2G_REAL_MONEY_BUY_SUCCESS* pMsg = (M2G_REAL_MONEY_BUY_SUCCESS*)pPacketBuffer;
    CRole* poRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwRoleID);
	CRole* poBuyer = NULL;
    INT32 nAddResult = errUnknownError;

    char mail_subject[MAIL_SUBJECT_LEN];
    char mail_content[MAIL_CONTENT_LEN];
    char item_name[MAX_ITEM_NAME_LEN];
    bool giving = strlen(pMsg->szGiverRoleName) > 0;
    const MAIL_TEMPLATE_DATA* mail_data = NULL;
    
    if (giving)
	{
        mail_data = CDataManager<MAIL_TEMPLATE_DATA>::GetInstance().GetData(mtiRealMoneyShopGive);

		poBuyer = CGameWorld::GetInstance().FindValidRole(pMsg->dwGiveRoleID);
		if (poBuyer)
		{
			if (pMsg->nItemID < MONEYTYPE_COUNT)
			{
				poBuyer->GetAchievementList().AddVariable(avdRealMoneyToMoney02Count, pMsg->nItemCount*pMsg->nOriginalPrice);
			}
			else
			{
				poBuyer->GetAchievementList().AddVariable(avdRealMoneyToItemCount, pMsg->nItemCount*pMsg->nOriginalPrice);
			}
		}
	}
    else
	{
        mail_data = CDataManager<MAIL_TEMPLATE_DATA>::GetInstance().GetData(mtiRealMoneyShop);
	}

	if (mail_data)
    {
        char item_name[MAX_ITEM_NAME_LEN];
        if (pMsg->nItemID < MONEYTYPE_COUNT)
        {
            const MONEY_DATA* money_data = CDataManager<MONEY_DATA>::GetInstance().GetData(pMsg->nItemID);
            if (money_data)
                strxcpy(item_name, money_data->m_szMoneyName, MAX_ITEM_NAME_LEN);
            else
                strxcpy(item_name, "Unknown Money", MAX_ITEM_NAME_LEN);
        }
        else
        {
            const ITEM_DATA* item_data = GetItemData(pMsg->nItemID);
            if (item_data)
                strxcpy(item_name, item_data->m_szName, MAX_ITEM_NAME_LEN);
            else
                strxcpy(item_name, "Unknown Item", MAX_ITEM_NAME_LEN);
        }

        if (giving)
            snprintf(mail_subject, MAIL_SUBJECT_LEN, mail_data->m_szMailSubject, pMsg->szGiverRoleName, item_name);
        else
            snprintf(mail_subject, MAIL_SUBJECT_LEN, mail_data->m_szMailSubject, item_name);

        strxcpy(mail_content, mail_data->m_szMailContent, MAIL_CONTENT_LEN);
    }
    else
    {
        strxcpy(mail_subject, "Unknown Mail Subject", MAIL_SUBJECT_LEN);
        strxcpy(mail_content, "Unknown Mail Content", MAIL_CONTENT_LEN);
    }

    if (pMsg->nItemID < MONEYTYPE_COUNT)
    {
        if (poRole)
		{
            nAddResult = poRole->GetItemBag()->AddMoney(pMsg->nItemID, pMsg->nStackCount * pMsg->nItemCount, MONEYLOG_REAL_MONEY_SHOP, 0);
		}

        if (poRole == NULL || nAddResult != errSuccess)
        {
            BOOL bRes = CCliMessageHandler::GetInstance().DoMSSendSystemMailWithSimpleAttach(pMsg->dwRoleID, mail_subject, mail_content, pMsg->nItemID, pMsg->nStackCount * pMsg->nItemCount);
            if (!bRes)
            {
                WRN("Send Real Money Shop Mail Error: RoleID:%u, ItemID:%d, ItemCount: %d", pMsg->dwRoleID, pMsg->nItemID, pMsg->nStackCount * pMsg->nItemCount);
            }
        }
    }
    else
    {
        for (INT32 i=0; i<pMsg->nItemCount; i++)
        {
            if (poRole)
                nAddResult = poRole->GetItemBag()->AddItem(pMsg->nItemID, pMsg->nStackCount, ITEMLOG_REAL_MONEY_SHOP, 0, FALSE);
            if (poRole == NULL || nAddResult != errSuccess)
            {
                BOOL bRes = CCliMessageHandler::GetInstance().DoMSSendSystemMailWithSimpleAttach(pMsg->dwRoleID, mail_subject, mail_content, pMsg->nItemID, pMsg->nStackCount);
                if (!bRes)
                {
                    WRN("Send Real Money Shop Mail Error: RoleID:%u, ItemID:%d, ItemCount: %d", pMsg->dwRoleID, pMsg->nItemID, pMsg->nStackCount);
                }
            }
        }
    }

	if (poRole)
	{
		CStatistic::GetInstance().OnRealShopMoney(poRole, pMsg->nItemID, pMsg->nStackCount, pMsg->nItemCount, pMsg->nOriginalPrice);
	}
}

void CGSMessageHandler::OnMSFcmState(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    M2G_FCM_STATE* pMsg = (M2G_FCM_STATE*)pPacketBuffer;
    CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);

    if (poRole)
        poRole->SetFcmState(pMsg->byFcmState);
}

void CGSMessageHandler::OnMSFreeMode(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    M2G_FREE_MODE* pMsg = (M2G_FREE_MODE*)pPacketBuffer;
    CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);

    if (poRole)
        poRole->SetFreeMode(pMsg->byFreeMode);
}

void CGSMessageHandler::OnMSAward(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    M2G_AWARD* pMsg = (M2G_AWARD*)pPacketBuffer;
    CRole* poRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    INT32 nRetCode = 0;

    if (poRole)
    {
        if (pMsg->nItemID < MONEYTYPE_COUNT)
            poRole->GetItemBag()->AddMoney(pMsg->nItemID, pMsg->nItemCount, MONEYLOG_AWARD, 0);
        else
            nRetCode = poRole->GetItemBag()->AddItem(pMsg->nItemID, pMsg->nItemCount, ITEMLOG_AWARD, 0, FALSE);
    }

    if (poRole == NULL || nRetCode == errItemBagFull)
    {
        const MAIL_TEMPLATE_DATA* data = CDataManager<MAIL_TEMPLATE_DATA>::GetInstance().GetData(mtiAward);
        if (data)
        {
            CCliMessageHandler::GetInstance().DoMSSendSystemMailWithSimpleAttach(
                pMsg->dwRoleID, data->m_szMailSubject, data->m_szMailContent, pMsg->nItemID, pMsg->nItemCount);
        }
        else
        {
            CCliMessageHandler::GetInstance().DoMSSendSystemMailWithSimpleAttach(
                pMsg->dwRoleID, "award", "award", pMsg->nItemID, pMsg->nItemCount);
        }
    }
}

struct CTraveseSceneSpawnNpc
{
	INT32 m_nSceneTempID;
	INT32 m_nX;
	INT32 m_nY;
	INT32 m_nZ;
	INT32 m_nRange;
	INT32 m_nNpcTemplateID;
	INT32 m_nNpcCount;
	UINT32 m_dwSuicideTime;

	bool operator()(UINT64 qwID, CScene* poScene)
	{
		INT32 nRetCode = 0;
		INT32 nSceneTempID = qwID >> 32;

		if (nSceneTempID == m_nSceneTempID)
		{
			for (INT32 nIndex = 0; nIndex < m_nNpcCount; nIndex++)
			{
				INT32 nPos[1][3];
				INT32 nCenterX, nCenterY;
				nCenterX = m_nX + g_Random(m_nRange * 2) - m_nRange;
				nCenterY = m_nY + g_Random(m_nRange * 2) - m_nRange;

				nRetCode = poScene->GetStaticData()->GetNearestAvailablePos(nCenterX, nCenterY, m_nZ, 16, 1, nPos);
				if (nRetCode)
				{
					CNpc* poNpc = poScene->SpawnNpc(m_nNpcTemplateID, nPos[0][0], nPos[0][1], nPos[0][2], 0, 0, NULL);
					if (poNpc)
					{
						poScene->AddNpcLiveTimer(poNpc->GetObjID(), m_dwSuicideTime);
					}
				}
			}
		}

		return TRUE;
	}
};

void CGSMessageHandler::OnMSSpawnNpc(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
	M2G_SPAWN_NPC* pMsg = (M2G_SPAWN_NPC*)pPacketBuffer;
	CTraveseSceneSpawnNpc TraveseSceneSpawnNpc;

	TraveseSceneSpawnNpc.m_nSceneTempID = pMsg->nSceneTempID;
	TraveseSceneSpawnNpc.m_nX = pMsg->nX;
	TraveseSceneSpawnNpc.m_nY = pMsg->nY;
	TraveseSceneSpawnNpc.m_nZ = pMsg->nZ;
	TraveseSceneSpawnNpc.m_nRange = pMsg->nRange;
	TraveseSceneSpawnNpc.m_nNpcTemplateID = pMsg->nNpcTemplateID;
	TraveseSceneSpawnNpc.m_nNpcCount = pMsg->nNpcCount;
	TraveseSceneSpawnNpc.m_dwSuicideTime = pMsg->dwSuicideTime;
	CGameWorld::GetInstance().TraverseScene(TraveseSceneSpawnNpc);

	return;
}

void CGSMessageHandler::OnMSSyncServerVariable(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
	M2G_SYNC_SERVER_VARIABLE* pMsg = (M2G_SYNC_SERVER_VARIABLE*)pPacketBuffer;
	INT32 nCount = (dwSize - sizeof(M2G_SYNC_SERVER_VARIABLE)) / sizeof(pMsg->VarList[0]);

	for (INT32 nIndex = 0; nIndex < nCount; nIndex++)
	{
		CGameWorld::GetInstance()._SetServerVariable(pMsg->byServerGroup, 
			pMsg->VarList[nIndex].qwKey, pMsg->VarList[nIndex].nValue);
	}

	return;
}

void CGSMessageHandler::OnMSUpdateServerVariable(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
	M2G_UPDATE_SERVER_VARIABLE* pMsg = (M2G_UPDATE_SERVER_VARIABLE*)pPacketBuffer;

	CGameWorld::GetInstance()._SetServerVariable(pMsg->byServerGroup, pMsg->qwKey, pMsg->nValue);
}

void CGSMessageHandler::OnMSUpdateAverageLevel(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
	M2G_UPDATE_AVERAGE_LEVEL* pMsg = (M2G_UPDATE_AVERAGE_LEVEL*)pPacketBuffer;

	for (INT32 nServerGroup = 0; nServerGroup < MAX_SERVER_GROUP_COUNT; nServerGroup++)
	{
		CGameWorld::GetInstance().SetAverageLevel(nServerGroup, pMsg->nAverageLevel[nServerGroup]);
	}
}

void CGSMessageHandler::OnMSGetBlackMarketLimitInfo(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    M2G_GET_BLACK_MARKET_LIMIT_INFO* pMsg = (M2G_GET_BLACK_MARKET_LIMIT_INFO*)pPacketBuffer;

    for (INT32 i = 0; i < pMsg->nLimitInfoCount; i++)
    {
        CGameWorld::GetInstance().UpdateMSBMLimitMap(pMsg->LimitInfo[i].nBlackMarketProductID, pMsg->LimitInfo[i].dwCount);
    }
    CGameWorld::GetInstance().UpdateMSBMTime();

    CRole* role = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    if (role)
        CCliMessageHandler::GetInstance().DoBlackMarketLimitInfo(role);
}

void CGSMessageHandler::OnMSCheckBlackMarketProduct(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    M2G_CHECK_BLACK_MARKET_PRODUCT* pMsg = (M2G_CHECK_BLACK_MARKET_PRODUCT*)pPacketBuffer;

    CRole* role = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    if (role)
    {
        if (pMsg->nResult == errSuccess)
        {
            INT32 err = role->GetItemBag()->OnMsBlackMarketBuy(pMsg->nBlackMarketProductID, pMsg->nCount);
            if (err != errSuccess)
            {
				role->ErrorCodeNotify(err, 0, 0);
            }

            CGameWorld::GetInstance().UpdateMSBMLimitMap(pMsg->nBlackMarketProductID, pMsg->nCount);
        }
        else
        {
			role->ErrorCodeNotify(pMsg->nResult, 0, 0);
        }
    }
}

void CGSMessageHandler::OnMSAddExerciseTime(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession *pSocketSession)
{
    M2G_ADD_EXERCISE_TIME* pMsg = (M2G_ADD_EXERCISE_TIME*)pPacketBuffer;

    CRole* role = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
    if (role)
    {
        LOG_CHECK_ERROR(role->GetDoingSubTime());
        role->SetDoingSubTime(FALSE);

        if (pMsg->nResult == errSuccess)
        {
            role->SetTotalExerciseTime(pMsg->nHour * 3600);
            role->SetStartExerciseTime(CGameWorld::GetInstance().GetGameTime());

            CCliMessageHandler::GetInstance().DoAddExerciseTime(role, pMsg->nHour);
        }
        else
        {
            role->ErrorCodeNotify(pMsg->nResult, 0, 0);
        }
    }
    else
    {
        if (pMsg->nResult == 0)
        {
            INF("Failed To Add Exercise Time: RoleID:%u, Hour:%d", pMsg->dwRoleID, pMsg->nHour);
        }
    }
}

// 玩家购买商城物品
void CGSMessageHandler::OnMSRoleRealMoneyShopBuyItemReq(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nResult = errNotEnoughMoney;
	M2G_ROLE_REAL_MONEY_SHOP_BUY_ITEM_REQ* pMsg = (M2G_ROLE_REAL_MONEY_SHOP_BUY_ITEM_REQ*)pPacketBuffer;

	CRole* poRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwRoleID);
	if (poRole)
	{
		// 这里需要补充, 扣钱之前 先计算空余格子是否足够, 要考虑多种情况, 比如铭文石一组20个, 买100个就要5个格子
		//...

		nResult = poRole->GetItemBag()->SubMoney(MONEYTYPE_04, pMsg->nTotalCost, MONEYLOG_REAL_MONEY_SHOP, 0);
		if (nResult == errSuccess)
		{
			// 扣元宝成功, 发放物品, 同步元宝数量
			DoMSRoleRealMoneyShopBuyItemAck(pMsg->dwCliSessionID, 0, pMsg->dwRoleID, pMsg->nItemID, pMsg->nItemCount, pMsg->szRoleName);
			DoMSQueryRealMoneyRole(pMsg->dwCliSessionID, pMsg->dwRoleID, poRole->GetItemBag()->GetMoney(MONEYTYPE_04));
		}
		else
		{
			// 扣元宝失败
			poRole->ErrorCodeNotify(errNotEnoughMoney, 0, 0);
		}
	}
}

// 玩家购买点卡
void CGSMessageHandler::OnMSCustomRoleBuyTimeReq(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nResult = errNotEnoughMoney;
	M2G_CUSTOM_ROLE_BUY_TIME* pMsg = (M2G_CUSTOM_ROLE_BUY_TIME*)pPacketBuffer;

	CRole* poRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwRoleID);
	if (poRole)
	{
		nResult = poRole->GetItemBag()->SubMoney(MONEYTYPE_04, pMsg->dwBuyTimeCost, MONEYLOG_CUSTOM_ROLE_BUY_TIME, 0);
		if (nResult == errSuccess)
		{
			UINT32 dwBuySeconds = (pMsg->dwBuyTimeCost / 100) * 6000;    // 价格 [1.00元宝 = 6000秒]
			poRole->AddGameTimeCard(dwBuySeconds);
		}
		else
		{
			poRole->ErrorCodeNotify(errNotEnoughMoney, 0, 0);
		}
	}
}

/************************************************************************/
// From DB
void CGSMessageHandler::OnDBRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	CGSSessionMgr::GetInstance().GetDBSession().byReady = 1;

    if ((g_ServerConfig.MS.nInitDLCount == 0 || CGSSessionMgr::GetInstance().GetDLSession().byReady) && CGSSessionMgr::GetInstance().GetServerState() == sgsSelfReady)
	{
		nRetCode = DoMSReady();
		LOG_PROCESS_ERROR(nRetCode);
	}

	if(CGSSessionMgr::GetInstance().GetGDSession().bConnected)
	{
		if (CGSSessionMgr::GetInstance().GetSelfSessionID() > 0)
		{
			nRetCode = DoGDRegister();
			LOG_PROCESS_ERROR(nRetCode);
		}
	}
Exit0:
	return;
}

void CGSMessageHandler::OnDBLoadLockRoleDataAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	D2G_LOAD_LOCK_ROLE_DATA_ACK* pMsg = (D2G_LOAD_LOCK_ROLE_DATA_ACK*)pPacketBuffer;
	CRole* poRole = NULL;
	CLuaScript* poScript = NULL;

	//找不到是合理异常
	poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwClientSessionID);
	PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetState() == rsWaitRoleData);
	LOG_PROCESS_ERROR(poRole->GetObjID() == pMsg->dwRoleID);

	nRetCode = poRole->Load(pMsg->RoleData, pMsg->dwDataSize);  // 加载角色数据
	LOG_PROCESS_ERROR(nRetCode);

	poScript = CScriptMgr::GetInstance().FindScript(LOAD_ROLE_SCRIPT_NAME);
	LOG_PROCESS_ERROR(poScript);

	nRetCode = poScript->CallFunction("main", "o", poRole, "CRole");
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = DoMSEnterGS(pMsg->dwClientSessionID, pMsg->dwRoleID, 
		poRole->GetItemBag()->GetMoney(MONEYTYPE_MASTER_EXP), poRole->GetMaster().GetCD(), 
        poRole->GetRoleGuildData().GetCD(), poRole->GetGMLevel(), poRole->GetMaster().GetTwitter(), poRole->GetMaster().GetTwitterCD(), poRole->GetFriend()->GetSignature());
	LOG_PROCESS_ERROR(nRetCode);

	poRole->SetState(rsWaitMSApprove);

	GS_SYS_LOG_SUCCESS(poRole);
	return;
Exit0:
	GS_SYS_LOG_ERROR(poRole);
	nRetCode = DoGTCloseClientSession(pMsg->dwClientSessionID);
	LOG_CHECK_ERROR(nRetCode);

	return;
}

void CGSMessageHandler::OnDBUnlockRoleDataAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	D2G_UNLOCK_ROLE_DATA_ACK* pMsg = (D2G_UNLOCK_ROLE_DATA_ACK*)pPacketBuffer;
	CRole* poRole = NULL;
	BOOL bNormal = TRUE;

	LOG_CHECK_ERROR(pMsg->nError == errSuccess);
	//不可能找不到，找不到有严重BUG
	poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwClientSessionID);
	LOG_PROCESS_ERROR(poRole);
	LOG_CHECK_ERROR(poRole->GetObjID() == pMsg->dwRoleID);
	LOG_CHECK_ERROR(poRole->GetState() == rsWaitUnlockRoleData);

	GS_SYS_LOG_SUCCESS(poRole);
	nRetCode = poRole->UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CGameWorld::GetInstance().DelRole(poRole);
	LOG_CHECK_ERROR(nRetCode);

Exit0:
	nRetCode = CGSSessionMgr::GetInstance().DetachRoleFromSession(pMsg->dwClientSessionID);
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = DoMSLeaveGSAck(pMsg->dwClientSessionID, pMsg->dwRoleID);
	LOG_CHECK_ERROR(nRetCode);

	return;
}

void CGSMessageHandler::OnDBLoadLockRoleDataFailAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK* pMsg = (D2G_LOAD_LOCK_ROLE_DATA_FAIL_ACK*)pPacketBuffer;
	CRole* poRole = NULL;

	//找不到是合理异常
	poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwClientSessionID);
	PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetState() == rsWaitRoleData);
	LOG_PROCESS_ERROR(poRole->GetObjID() == pMsg->dwRoleID);

	PROCESS_ERROR(!poRole->IsInJump());

	nRetCode = poRole->ErrorCodeNotify( errLoginRoleBusy, 0, 0);
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = DoGTReturnSelectRole(pMsg->dwClientSessionID);
	LOG_PROCESS_ERROR(nRetCode);
	poRole->SetState(rsPreEntered);

	GS_SYS_LOG_SUCCESS(poRole);
	return;
Exit0:
	GS_SYS_LOG_ERROR(poRole);
	nRetCode = DoGTCloseClientSession(pMsg->dwClientSessionID);
	LOG_CHECK_ERROR(nRetCode);

	return;
}

/************************************************************************/
// From GT
void CGSMessageHandler::OnGTRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	T2G_REGISTER_ACK* pMsg = (T2G_REGISTER_ACK*)pPacketBuffer;
	INF("GS %d registered to GT %d", CGSSessionMgr::GetInstance().GetSelfSessionID(), pMsg->dwGTSessionID);
}

// 进入游戏 加载数据
void CGSMessageHandler::OnGTRoleEnter(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	T2G_ROLE_ENTER* pMsg = (T2G_ROLE_ENTER*)pPacketBuffer;
	CRole* poRole = NULL;

	//找不到是合理异常
	poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwClientSessionID);
	PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetState() == rsPreEntered);
	LOG_PROCESS_ERROR(poRole->GetObjID() == pMsg->dwRoleID);

	nRetCode = DoDBLoadLockRoleData(pMsg->dwClientSessionID, pMsg->dwRoleID);  // 加载角色数据
	LOG_PROCESS_ERROR(nRetCode);

	poRole->SetState(rsWaitRoleData);
    poRole->SetInLogin();

	GS_SYS_LOG_SUCCESS(poRole);
	return;
Exit0:
	GS_SYS_LOG_ERROR(poRole);
	nRetCode = DoGTCloseClientSession(pMsg->dwClientSessionID);
	LOG_CHECK_ERROR(nRetCode);

	return;
}

void CGSMessageHandler::OnGTClientMsg(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	CRole* poRole = NULL;

	T2G_CLIENT_MSG* pMsg = (T2G_CLIENT_MSG*)pPacketBuffer;

	poRole = CGSSessionMgr::GetInstance().FindRoleBySessionID(pMsg->dwSessionID);
	if (poRole)
	{
		poRole->Prefetch();
#if defined(WIN32)
		__try
		{
			nRetCode = CCliMessageHandler::GetInstance().OnRecv(poRole, pMsg->szData);
			LOG_PROCESS_ERROR(nRetCode);
		}
		__except(DumpExceptionFilter(GetExceptionInformation()))
		{
			goto Exit0;
		}
#elif defined(__linux__)
		nRetCode = CCliMessageHandler::GetInstance().OnRecv(poRole, pMsg->szData);
		LOG_PROCESS_ERROR(nRetCode);
#endif 
	}

	return;
Exit0:
	CRI("error external message id %d size %d", ((ExternalMessage::MESSAGE_HEADER*)pMsg->szData)->wMsg, dwSize-sizeof(T2G_CLIENT_MSG));

	if (poRole)
		KICK_ROLE(poRole, ktLogged);
	else
	{
		nRetCode = DoGTCloseClientSession(pMsg->dwSessionID);
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
}

void CGSMessageHandler::OnDLRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	O2G_REGISTER_ACK* pMsg = (O2G_REGISTER_ACK*)pPacketBuffer;
	INF("GS %d registered to DL", CGSSessionMgr::GetInstance().GetSelfSessionID());

	CGSSessionMgr::GetInstance().GetDLSession().byReady = 1;
    if (CGSSessionMgr::GetInstance().GetDBSession().byReady && CGSSessionMgr::GetInstance().GetServerState() == sgsSelfReady)
	{
		nRetCode = DoMSReady();
		LOG_CHECK_ERROR(nRetCode);
	}
}
