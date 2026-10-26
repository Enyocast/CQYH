/********************************************************************
	created:	20:11:2013   17:52
	file:		message_handler.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_MESSAGE_HANDLER_H_
#define _H_MESSAGE_HANDLER_H_


#include "net.h"
#include "internal_message_header.h"
#include "gm_data.h"
#include "gmtl_message.h"

struct DB_OP_LOG_ITEM_RESULT;
class CGMRoleData;
struct CMD_DATA_BASE;

class CMessageHandler : public INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
    virtual void OnConnected(ISocketSession* pSocketSession);
    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown);

public:
    CMessageHandler();
    virtual ~CMessageHandler();

    BOOL Init(INet *pNet, IPacketAllocator *pPacketAllocator, ISocketAcceptor *pMSAcceptor, ISocketAcceptor *pTLAcceptor);
    BOOL UnInit();
    static CMessageHandler &GetInstance();

    BOOL SendMS(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL SendTL(UINT32 dwTLSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL SendGD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL BroadcastLD(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
    BOOL BroadcastLD(INT32 nGroupID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset = 0);
public:
    BOOL DoAllPing();
    BOOL DoGDRegister();


private:
    void OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // From MS
    void OnMSRegister(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSClearRoleCacheAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSUnlockRoleAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSQueryRoleDataAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSForbidChatAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSFreezeRoleAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSKickRoleAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSSendMailAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSAnnounceAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGetAnnounceAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSDelAnnounceAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSExeGMStrAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGMStrCmdLog(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSDelMail(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSCheckRoleFreezeAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnMSGetExchangePriceAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSQueryOrderDetailAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSAddSystemOrderAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSDelSystemOrderAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSGetExchangeLimitAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnMSSetExchangeLimitAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    // From GM Tool
    void OnTLRegister(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnTLVerify(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnTLLogin(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    void OnTLLogout(PACKET_BUFFER *pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);

    void OnTLPreQuery(CTLUser *pTLUser, const char *pcData);
    void OnTLQueryRoleID(CTLUser *pTLUser, const char *pcData);
    void OnTLQueryRoleData(CTLUser *pTLUser, const char *pcData);
    void OnTLForbidChat(CTLUser *pTLUser, const char *pcData);
    void OnTLFreezeRole(CTLUser *pTLUser, const char *pcData);
    void OnTLKickRole(CTLUser *pTLUser, const char *pcData);
    void OnTLSendMail(CTLUser *pTLUser, const char *pcData);
    void OnTLAnnounce(CTLUser *pTLUser, const char *pcData);
    void OnTLGetAnnounceList(CTLUser *pTLUser, const char *pcData);
    void OnTLDelAnnouce(CTLUser *pTLUser, const char *pcData);
    void OnTLLog(CTLUser *pTLUser, const char *pcData);
    void OnTLExeGMStr(CTLUser *pTLUser, const char *pcData);
    void OnTLLoadRole(CTLUser *pTLUser, const char *pcData);
    void OnTLModifyRole(CTLUser *pTLUser, const char *pcData);
    void OnTLReleaseRole(CTLUser *pTLUser, const char *pcData);
    void OnTLQueryNameToID(CTLUser *pTLUser, const char *pcData);
    void OnTLRoleExeCmd(CTLUser *pTLUser, const char *pcData);

    void OnTLSelectGroup(CTLUser *pTLUser, const char *pcData);
    void OnTLQueryExchangePriceLog(CTLUser *pTLUser, const char *pcData);
    void OnTLQueryExchangeHistory(CTLUser *pTLUser, const char *pcData);
    void OnTLQueryOrderDetail(CTLUser *pTLUser, const char *pcData);
    void OnTLAddSystemOrder(CTLUser *pTLUser, const char *pcData);
    void OnTLDelSystemOrder(CTLUser *pTLUser, const char *pcData);
    void OnTLSystemExchangeInfo(CTLUser *pTLUser, const char *pcData);
    void OnTLQueryExchangeLimit(CTLUser *pTLUser, const char *pcData);
    void OnTLSetExchangeLimit(CTLUser *pTLUser, const char *pcData);


public:
    // To MS
    BOOL DoMSRegisterAck( );
    BOOL DoMSClearRoleCache(UINT32 dwTLUserID, UINT32 dwRoleID, UINT32 dwCmdSerialID);
    BOOL DoMSUnlockRole(UINT32 dwRoleID, const char *pcszUserName);
    BOOL DoMSQueryRoleData(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwRoleID);
    BOOL DoMSForbidChat(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwTime, UINT32 dwRoleID);
    BOOL DoMSFreezeRole(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwTime, UINT32 dwRoleID);
    BOOL DoMSKickRole(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwRoleID);
    BOOL DoMSSendMail(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwRoleID, const char *pcszSubject, const char *pcszContent, UINT32 dwItemID, INT32 nItemNum);
    BOOL DoMSAnnounce(INT32 nGroupID, UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwBeginTime, INT32 nRepeatNum, UINT32 dwIntervalTime, const char *pcszBuffer);
    BOOL DoMSGetAnnounceList(INT32 nGroupID, UINT32 dwTLUserID, UINT32 dwCmdSerialID);
    BOOL DoMSDelAnnounce(INT32 nGroupID, UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwAnnounceSerial);
    BOOL DoMSExeGMStrCmd(UINT32 dwTLUserID, UINT32 dwCmdSerialID, const char *pcszGMCmd);
    BOOL DoMSDelMail(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwRoleID, UINT32 dwMailID);
    BOOL DoCheckRoleFreeze(UINT32 dwTLUserID, UINT32 dwCmdSerialID, UINT32 dwRoleID);

    // order
    BOOL DoMSGetExchangePrice(INT32 nGroupID);
    BOOL DoMSQueryOrderDetail(UINT8 byGroupID, INT32 nPrice, UINT8 byOrderType, UINT32 TLUserID);
    BOOL DoMSAddSystemOrder(UINT32 dwTLUserID, INT32 nGroupID, INT32 nPrice, INT32 nCount);
    BOOL DoMSDelSystemOrder(UINT32 dwTLUserID, INT32 nGroupID, UINT64 qwOrderID);
    BOOL DoMSQueryExchangeLimit(UINT32 dwTLUserID, INT32 nGroupID);
    BOOL DoMSSetExchangeLimit(UINT32 dwTLUserID, INT32 nGroupID, INT32 nPriceHigh, INT32 nPriceLow, INT32 nSingleOrderLimit, INT32 nDailyOrderLimit);



    // To GM Tool
    BOOL DoTLRegisterAck(UINT32 dwTLSessionID, INT32 nResult);
    BOOL DoTLVerifyAck(UINT32 dwTLSessionID, INT32 nResult, BOOL bLD);
    BOOL DoTLLoginAck(UINT32 dwTLSessionID, INT32 nResult);
    BOOL DoTLLogoutAck(UINT32 dwTLSessionID);

    BOOL DoTLItemListNtf(UINT32 dwTLSessionID);
    BOOL DoTLPreQueryAck(UINT32 dwTLSessionID, const char *pcszRoleName, UINT32 dwRoleID);
    BOOL DoTLQueryRoleIDAck(UINT32 dwTLSessionID, INT32 nCount, GM_ROLE_KEY *pRoleKey);
    BOOL DoTLQueryRoleDataAck(UINT32 dwTLSessionID, UINT32 dwRoleID, BOOL bIsOnline, INT32 nLength, const char *pData);
    BOOL DoTLForbidChatAck(UINT32 dwTLSessionID, UINT32 dwRoleID);
    BOOL DoTLFreezeRoleAck(UINT32 dwTLSessionID, UINT32 dwRoleID);
    BOOL DoTLKickRoleAck(UINT32 dwTLSessionID, UINT32 dwRoleID);
    BOOL DoTLSendMailAck(UINT32 dwTLSessionID, UINT32 dwRoleID);
    BOOL DoTLAnnounceAck(INT32 nGroupID, UINT32 dwTLSessionID, INT32 nResult);
    BOOL DoTLGetAnnounceListAck(INT32 nGroupID, UINT32 dwTLSessionID, CMD_DATA_BASE *pCmd);
    BOOL DoTLDelAnnounceAck(INT32 nGroupID, UINT32 dwTLSessionID, UINT32 dwAnnounceSerial);
    BOOL DoTLLogAck(UINT32 dwTLSessionID, INT32 nLogType, BOOL bTruncated, INT32 nLength, const char *pcszBuffer);
    BOOL DoTLExeGMStrAck(UINT32 dwTLSessionID);
    BOOL DoTLLoadRoleDataAck(UINT32 dwTLSessionID, UINT32 dwRoleID, INT32 nLength, const char *pData);
    BOOL DoTLModifyRoleDataAck(UINT32 dwTLSessionID, UINT32 dwRoleID);
    BOOL DoTLQueryNameToIDAck(UINT32 dwTLSessionID, INT32 nIndex, UINT32 dwRoleID);
    BOOL DoTLErrorStr(UINT32 dwTLSessionID, const char *pcszErrStr);
    BOOL DoTLRoleExeGMCmdAck(UINT32 dwTLSessionID, UINT32 dwRoleID);

    BOOL DoTLSelectGroupAck(UINT32 dwTLSessionID, UINT8 byGroupID);
    BOOL DoTLQueryExchangeLogAck(UINT32 dwSessionID, UINT8 byGroupID, BOOL bClear, INT32 nCount, INT32 nLength, const char *pcData);
    BOOL DoTLQueryExchangeHistoryAck(UINT32 dwSessionID, UINT8 byGroupID, BOOL bClear, INT32 nCount, INT32 nLength, const char *pcData);
    BOOL DoTLExchangePrice(INT32 nGroupID, INT32 nSellNum, INT32 nBuyNum, const char *pcData);
    BOOL DoTLQueryOrderDetailAck(UINT32 dwSessionID, UINT8 byGroupID, UINT8 byOrderType, INT32 nPrice, INT32 nCount, const char *pcData);
    BOOL DoTLAddSystemOrderAck(INT32 nGroupID, UINT64 qwOrderID, INT32 nResult, INT32 nPrice, INT32 nCount);
    BOOL DoTLDelSystemOrderAck(INT32 nGroupID, UINT64 qwOrderID, INT32 nResult, INT32 nPrice, INT32 nCount);
    BOOL DoTLQuerySystemExchangeInfo(UINT32 dwSessionID,
        UINT32 dwBeginTime, UINT32 dwEndTime,
        UINT8 byGroupID, UINT8 byFlag, 
        INT64 llSysTotalMoney, INT64 llTotalMoney,
        INT64 llSysTotalExchangeMoney, INT64 llTotalExchangeMoney,
        INT64 llSysExchangeRMB, INT64 llExchangeRMB, 
        INT32 nAveragePriceToday, INT32 nAveragePriceLastHour);

    BOOL DoTLGetExchangeLimitAck(UINT32 dwSessionID, INT32 nGroup, INT32 nPriceHigh, INT32 nPriceLow, INT32 nSingleOrderLimit, INT32 nDailyOrderLimit);
    BOOL DoTLSetExchangeLimitAck(UINT32 dwSessionID, INT32 nGroup, INT32 nPriceHigh, INT32 nPriceLow, INT32 nSingleOrderLimit, INT32 nDailyOrderLimit);

private:
    static  CMessageHandler     ms_Instance;

    INet                *m_pNet;
    IPacketAllocator    *m_pPacketAllocator;

    ISocketAcceptor     *m_poTLAcceptor;
    ISocketAcceptor     *m_poMSAcceptor;

    typedef void (CMessageHandler::*INTERNAL_MESSAGE_FUNC)(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession);
    INTERNAL_MESSAGE_FUNC               m_InternalMessageFuncList[InternalMessage::max_message_count];

    typedef void (CMessageHandler::*GMTL_MESSAGE_FUNC)(CTLUser *pTLUser, const char *pcData);
    GMTL_MESSAGE_FUNC                   m_GmtlMessageFuncList[InternalMessage::max_message_count];

};




#endif //_H_MESSAGE_HANDLER_H_



