#ifndef _ASIO_NET_H_
#define _ASIO_NET_H_

#include <memory>

#include "net.h"

// TCP transport built on asio. It replaces the old winsock IOCP (Windows) and epoll (Linux) implementations and
// keeps their contract:
//   * socket I/O runs on ASIO_INIT_PARAM::nThreadCount worker threads and only moves bytes in and out of
//     per-session ring buffers;
//   * everything else - parsing packets, INetEventHandler callbacks, connection state changes - happens inside
//     MainLoop(), i.e. on the thread that calls it.
namespace AsioNet
{
    class NetImpl;

    class CNet : public INet
    {
    public:
        CNet();
        ~CNet();

        virtual BOOL Init(IPacketAllocator* pPacketAllocator, INetEventHandler* pNetEventHandler, void* pInitParam);
        virtual BOOL UnInit(void);

        virtual ISocketAcceptor* CreateAcceptor(void);
        virtual BOOL DestroyAcceptor(ISocketAcceptor* pSocketAcceptor);

        virtual ISocketSession* Connect(UINT32 dwAddr, UINT16 wPort);
        virtual BOOL MainLoop(void);

        virtual INT64 PrintMemoryStat(void);

    private:
        std::unique_ptr<NetImpl> m_pImpl;
    };
}

#endif  // _ASIO_NET_H_
