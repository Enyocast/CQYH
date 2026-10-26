#ifndef _DL_MESSAGE_HANDLER_H_
#define _DL_MESSAGE_HANDLER_H_

#include "net.h"
#include "internal_message_header.h"
#include "logdata.h"

struct BASE_SESSION;
class CRole;
namespace InternalMessage
{
	struct G2O_ROLE_LOGOUT;
}

#define MAX_CONSECUTIVE_KILL_COUNT		(99)
#define MAX_CONSECUTIVE_KILL_DURATION	(20)

#define MAX_MOMENTARY_KILL_COUNT		(18)
#define MAX_MOMENTARY_KILL_DURATION		(MAX_MOMENTARY_KILL_COUNT - MIN_MOMENTARY_KILL_NPC_COUNT + 1)


BOOL LogItem(UINT32 dwTime, INT32 nGroupID, UINT64 qwItemGuid, UINT32 dwRoleID, INT32 nItemTemplateID,
    INT32 nItemCount, INT32 nReason, INT32 nAction, UINT64 qwUserDefinedID);

BOOL StatItem(INT32 nGroupID, INT32 nItemTemplateID, INT32 nItemCount, INT32 nAction);

class CDLMessageHandler : public INetEventHandler
{
public:
	virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
	virtual void OnConnected(ISocketSession* pSocketSession);
	virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
	virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
	CDLMessageHandler();
	~CDLMessageHandler();

	BOOL Init(INet* pNet, IPacketAllocator* pPacketAllocator, ISocketAcceptor* pGSSocketAcceptor);
	BOOL UnInit(void);
	static CDLMessageHandler& GetInstance(void);

	BOOL	MainLoop();

    CLogData &GetLogData()  { return m_LogData; }

protected:
    BOOL _StatItem(INT32 nGroupID, INT32 nItemTemplateID, INT32 nItemCount, INT32 nAction);
public:
	/************************************************************************/
	// To ALL
	BOOL DoAllPing(void);

	// To GD
    BOOL DoGDRegister(void);

	// To MS
    BOOL DoMSRegister(UINT32 dwAddr, UINT16 wPort);
	BOOL DoMSReady(void);
	BOOL DoMSCloseAck(void);

	//To GS
	BOOL DoGSRegisterAck(UINT32 dwGSSessionID);

private:
	/************************************************************************/
	void OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	// From MS
	void OnMSRegisterAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSAllReady(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSClose(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSServerInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	
	// ----------- log data --------------

	void OnMSChatMessage(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSLogItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSStatItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnMSLogin(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSLogout(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnMSCreateTeam(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSJoinTeam(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSLeaveTeam(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSBreakDownTeam(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSEnterScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);		
    void OnMSLeaveScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSGMCommand(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnMSTradeItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnMSRealMoneyToItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnMSRealMoneyToMoney02(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSGuildEvent(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildChest(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGuildStat(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSBillingRequest(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSBillingResult(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	// From GS
	void OnGSRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	// ----------- log data --------------

	void OnGSChatMessage(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSAcceptQuest(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSCompleteQuest(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSAbandonQuest(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSCompleteAchievement(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSLevelUp(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSDie(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSCreateScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSDestoryScene(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);	

	void OnGSBuyConSlot(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSLogItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSStatItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSRuneItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSChangeItem(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSGMCommand(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);	

	void OnGSRoleLogout(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSAddMoney(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);	
	void OnGSSubMoney(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);	

	void OnGSCreateTeam(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);	
	void OnGSJoinTeam(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSLeaveTeam(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSRolePosition(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	
	void OnGSNpcDie(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnGSNpcMoney(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSConsecutiveKillNpcCount(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSMomentaryKillNpcCount(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSClientHardwareInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSClientFpsInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSSpellEffect(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSCastSpell(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	void OnGSLearnSpell(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

	void OnGSAntiCheat(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);


private:
	BOOL _LoadPosInfo(const char* pcData, CRole* pRole);
	BOOL _SaveStatData(UINT32 dwTime, INT32 nGroupID);
	BOOL _LogBase(CRole* pRole, InternalMessage::G2O_ROLE_LOGOUT* pMsg);
	//BOOL _LogFriend(CRole* pRole, InternalMessage::G2O_ROLE_LOGOUT* pMsg);
	BOOL _LogItem(CRole* pRole, InternalMessage::G2O_ROLE_LOGOUT* pMsg);
	//BOOL _LogMaster(CRole* pRole, InternalMessage::G2O_ROLE_LOGOUT* pMsg);

    BOOL _SaveStatConsecutiveKill(const char* szTime, INT32 nAreaID, INT32 nGroupID);
    BOOL _SaveStatMomentaryKill(const char* szTime, INT32 nAreaID, INT32 nGroupID);
    BOOL _SaveStatNpcDie(const char* szTime, INT32 nAreaID, INT32 nGroupID);
    BOOL _SaveStatNpcMoney(const char* szTime, INT32 nAreaID, INT32 nGroupID);
    BOOL _SaveStatQuestComplete(const char* szTime, INT32 nAreaID, INT32 nGroupID);
    BOOL _SaveStatMoney(const char* szTime, INT32 nAreaID, INT32 nGroupID);
    BOOL _SaveStatRealMoney(const char* szTime, INT32 nAreaID, INT32 nGroupID);
    BOOL _SaveStatItem(const char* szTime, INT32 nAreaID, INT32 nGroupID);

	void _Test(void);

	inline BOOL _SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
	inline BOOL _SendGS(UINT32 dwGSSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);

private:
	INet*                               m_pNet;
	IPacketAllocator*                   m_pPacketAllocator;
	ISocketAcceptor*					m_pGSSocketAcceptor;
	static CDLMessageHandler            ms_Instance;

	CLogData							m_LogData;

    UINT32                              m_dwNextSaveMonitorDataTime[MAX_SERVER_GROUP_COUNT];

	typedef std::map<UINT64, INT32>			AREA_STATISTIC_MAP;
    typedef AREA_STATISTIC_MAP::iterator	MapIter;

	// npc die statistic
	AREA_STATISTIC_MAP					m_MapNpcIDDieStatistic[MAX_SERVER_GROUP_COUNT];
	INT64								m_llNpcTotalDieCount[MAX_SERVER_GROUP_COUNT];

    // npc money statistics
    AREA_STATISTIC_MAP                  m_MapNpcIDMoneyStatistic[MAX_SERVER_GROUP_COUNT];
    INT64                               m_llNpcTotalMoneyCount[MAX_SERVER_GROUP_COUNT];

	// money statistic
	INT64								m_llMoneyProduce[MAX_SERVER_GROUP_COUNT][MONEYTYPE_02 + 1];
	INT64								m_llMoneyDestory[MAX_SERVER_GROUP_COUNT][MONEYTYPE_02 + 1];

	// kill statistic
	INT64								m_llConsecutiveKill[MAX_SERVER_GROUP_COUNT][MAX_CONSECUTIVE_KILL_DURATION];
	INT64								m_llMomentaryKill[MAX_SERVER_GROUP_COUNT][MAX_MOMENTARY_KILL_DURATION];

	// quest complete
	INT64								m_llQuestCompleteCount[MAX_SERVER_GROUP_COUNT];

	// real money
	INT64								m_llRealMoneyToMoney02[MAX_SERVER_GROUP_COUNT];
	INT64								m_llRealMoneyToItem[MAX_SERVER_GROUP_COUNT];

    // item
    struct ItemStat
    {
        INT64 llProduce, llDestroy;
        ItemStat() { memset(this, 0, sizeof(ItemStat)); }
    };
    std::map<INT32, ItemStat>           m_MapItemStat[MAX_SERVER_GROUP_COUNT];

	typedef void (CDLMessageHandler::*MESSAGE_FUNC)(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
	MESSAGE_FUNC                        m_MessageFuncList[InternalMessage::max_message_count];
};

#endif // _DL_MESSAGE_HANDLER_H_
