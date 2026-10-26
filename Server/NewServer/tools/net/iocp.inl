
inline void* CSocketSession::GetAcceptBuffer(void)
{
    return m_AcceptBuffer;
}

inline SOCKET CSocketSession::GetSocket(void)
{
    return m_Socket;
}

inline IO_DATA* CSocketSession::GetSendIoData(void)
{
    return &m_SendIoData;
}

inline IO_DATA* CSocketSession::GetRecvIoData(void)
{
    return &m_RecvIoData;
}

inline IO_DATA* CSocketSession::GetCommonIoData(void)
{
    return &m_CommonIoData;
}

inline SESSION_STATE CSocketSession::GetState(void)
{
    return m_eState;
}

inline void CSocketSession::SetState(SESSION_STATE eState)
{
    m_eState = eState;
}

inline BASE_LIST_NODE& CSocketSession::GetListNode(void)
{
    return m_ListNode;
}

inline CSocketAcceptor* CSocketSession::GetSocketAcceptor(void)
{
    return m_pSocketAcceptor;
}

inline UINT64 CSocketSession::GetShutdownTimer(void)
{
    return m_qwShutdownTimer;
}

/************************************************************************/
inline SOCKET CSocketAcceptor::GetSocket(void)
{
    return m_sockListen;
}

/************************************************************************/
inline HANDLE CNet::GetIOCPHandle(void)
{
    return m_hIOCP;
}

inline IOCP_INIT_PARAM& CNet::GetInitParam(void)
{
    return m_InitParam;
}

IPacketAllocator* CNet::GetPacketAllocator(void)
{
    return m_pPacketAllocator;
}

inline INetEventHandler* CNet::GetEventHandler(void)
{
    return m_pEventHandler;
}
