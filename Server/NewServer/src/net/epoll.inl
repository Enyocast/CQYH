#ifndef _EPOLL_INL_
#define _EPOLL_INL_

inline CCircleList& CSocketSession::GetSendMsgList()
{
    return m_oSendMsg;
}

inline CCircleList& CSocketSession::GetRecvMsgList()
{
    return m_oRecvMsg;
}

inline VOID   CSocketSession::SetCurRecvMsgSize(UINT16 wMsgSize)
{
    m_wRecvMsgSize = wMsgSize;
}

inline UINT16 CSocketSession::GetCurRecvMsgSize()
{
    return m_wRecvMsgSize;
}

inline VOID  CSocketSession::SetRecvPacketBuffer(PACKET_BUFFER* poRecvBuff)
{
    m_poRecvBuff = poRecvBuff;
}

inline PACKET_BUFFER* CSocketSession::GetRecvPacketBuffer()
{
    return m_poRecvBuff;
}

inline VOID CSocketSession::SetSocketID(SOCKET nSocketFD)
{
    m_nSockedFD = nSocketFD;
}

inline SOCKET CSocketSession::GetSocketID()
{
    return m_nSockedFD;
}

inline VOID CSocketSession::SetAcceptor(CSocketAcceptor* poAcceptor)
{
    m_poAcceptor = poAcceptor;
}

inline CSocketAcceptor* CSocketSession::GetAcceptor()
{
    return m_poAcceptor;
}


inline VOID CSocketSession::SetState(ESessionState eState)
{
    m_eState = eState;
}


inline ESessionState CSocketSession::GetState()
{
    return m_eState;
}

inline VOID CSocketAcceptor::SetSession(CSocketSession* poSession)
{
    m_poSession = poSession;
}

inline CSocketSession* CSocketAcceptor::GetSession()
{
    return m_poSession;
}

inline PACKET_BUFFER* CNet::AllocBuffer(INT32 nSize)
{
    return m_pPacketAllocator->Alloc(nSize);
}

inline VOID CNet::FreeBuffer(PACKET_BUFFER* poBuffer)
{
    m_pPacketAllocator->Free(poBuffer);
}

inline UINT32 CNet::GetPacketBufferSize()
{
    return m_oInitParam.nPacketBufferSize;
}


#endif  // _EPOLL_INL_
