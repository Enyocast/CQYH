#include "stdafx.h"
#include "net.h"
#include "share_mem_net.h"
#include "simple_net.h"
#include "intranet.h"
#include "asio_net.h"

#ifdef WIN32
#include <iphlpapi.h>
#endif

INet* g_CreateNetInterface(INT32 eNetType, IPacketAllocator* pPacketAllocator, INetEventHandler* pNetEventHandler, void* pInitParam)
{
    INet* pResult = NULL;
    INT32 nRetCode = 0;

    switch (eNetType)
    {
        case netSimple:
        {
            pResult = new SimpleNet::CNet;
            LOG_PROCESS_ERROR(pResult);

            nRetCode = ((SimpleNet::CNet*)pResult)->Init(pPacketAllocator, pNetEventHandler, pInitParam);
            LOG_PROCESS_ERROR(nRetCode);
        }
        break;
        case netShareMemory:
        {
#if defined(WIN32)
            ShareMem::CNet* pNet = new ShareMem::CNet();
            LOG_PROCESS_ERROR(pNet);

            pResult = pNet;

            nRetCode = pNet->Init(pPacketAllocator, pNetEventHandler, pInitParam);
            LOG_PROCESS_ERROR(nRetCode);
#endif
        }
        break;
        case netIntranet:
        {
            Intranet::CNet* pNet = new Intranet::CNet();
            LOG_PROCESS_ERROR(pNet);

            pResult = pNet;

            nRetCode = pNet->Init(pPacketAllocator, pNetEventHandler, pInitParam);
            LOG_PROCESS_ERROR(nRetCode);

        }
        break;
        case netAsio:
        {
            AsioNet::CNet* pNet = new AsioNet::CNet();
            LOG_PROCESS_ERROR(pNet);

            pResult = pNet;

            nRetCode = pNet->Init(pPacketAllocator, pNetEventHandler, pInitParam);
            LOG_PROCESS_ERROR(nRetCode);
        }
        break;
        default:
            LOG_PROCESS_ERROR(FALSE);
            break;
    }

    return pResult;
Exit0:
    SAFE_DELETE(pResult);

    return NULL;
}

BOOL g_DestroyNetInterface(INT32 eNetType, INet* pNet)
{
    INT32 nRetCode = 0;
    LOG_PROCESS_ERROR(pNet);

    switch (eNetType)
    {
        case netSimple:
        {
            SimpleNet::CNet* pSimpleNet = (SimpleNet::CNet*)pNet;

            nRetCode = pSimpleNet->UnInit();
            LOG_CHECK_ERROR(nRetCode);

            SAFE_DELETE(pSimpleNet);
        }
        break;
        case netShareMemory:
        {
#if defined(WIN32)
            ShareMem::CNet* pShareMem = (ShareMem::CNet*)pNet;

            nRetCode = pShareMem->UnInit();
            LOG_CHECK_ERROR(nRetCode);

            SAFE_DELETE(pShareMem);
#endif //WIN32
        }
        break;
        case netIntranet:
        {
            Intranet::CNet* pIntranet = (Intranet::CNet*)pNet;

            nRetCode = pIntranet->UnInit();
            LOG_CHECK_ERROR(nRetCode);

            SAFE_DELETE(pIntranet);
        }
        break;
        case netAsio:
        {
            AsioNet::CNet* pAsioNet = (AsioNet::CNet*)pNet;

            nRetCode = pAsioNet->UnInit();
            LOG_CHECK_ERROR(nRetCode);

            SAFE_DELETE(pAsioNet);
        }
        break;
        default:
            LOG_PROCESS_ERROR(FALSE);
            break;
    }

    return TRUE;
Exit0:
    return FALSE;
}

struct ADAPTER_INFO
{
    UINT32 dwIpAddr;
    UINT32 dwIpMask;
};

#if defined(WIN32)

UINT32 GetIp(const char* pcszIntranetAddr, const char* pcszIntranetMask, BOOL bIntranet, INT32 nIndex)
{
    INT32 nRetCode = 0;
    UINT32 dwSubnetAddr = 0;
    UINT32 dwSubnetMask = 0;
    IP_ADAPTER_INFO AdInfo[MAX_ADAPTER_COUNT];
    INT32 nLen = sizeof(AdInfo);
    IP_ADAPTER_INFO* pIpAdapterInfo = AdInfo;

    dwSubnetAddr = inet_addr(pcszIntranetAddr);
    dwSubnetMask = inet_addr(pcszIntranetMask);

    nRetCode = GetAdaptersInfo(AdInfo, (PULONG)&nLen);
    LOG_PROCESS_ERROR(nRetCode == ERROR_SUCCESS);

    while (pIpAdapterInfo)
    {
        IP_ADDR_STRING* pAddrString = &(pIpAdapterInfo->IpAddressList);
        while (pAddrString)
        {
            UINT32 dwAddr = inet_addr(pAddrString->IpAddress.String);
            UINT32 dwMask = inet_addr(pAddrString->IpMask.String);
            BOOL bMatch = FALSE;

            if (dwAddr == 0)
            {
                pAddrString = pAddrString->Next;
                continue;
            }

            if (dwSubnetMask == 0xFFFFFFFF)
            {
                bMatch = TRUE;
            }
            else if ((dwAddr & dwSubnetMask) == (dwSubnetAddr & dwSubnetMask))
            {
                if (bIntranet)
                    bMatch = TRUE;
            }
            else
            {
                if (!bIntranet)
                    bMatch = TRUE;
            }

            if (bMatch)
            {
                if (nIndex == 0)
                    return inet_addr(pAddrString->IpAddress.String);

                nIndex--;
            }

            pAddrString = pAddrString->Next;
        }
        pIpAdapterInfo = pIpAdapterInfo->Next;
    }

Exit0:
    return 0;
}

#elif defined(__linux__)

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <ifaddrs.h>

BOOL GetNetworkAdapterInfo(INT32 nAdapterIndex, ADAPTER_INFO* pAdapterInfo)
{
    INT32 nRetCode = 0;
    struct ifaddrs* ifap = NULL;
    struct ifaddrs* ifa = NULL;

    nRetCode = getifaddrs(&ifap);
    LOG_PROCESS_ERROR(nRetCode == 0);

    for (ifa = ifap; ifa; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL || ifa->ifa_netmask == NULL)
            continue;
        if (strncmp(ifa->ifa_name, "eth", 3) != 0)
            continue;

        if (nAdapterIndex == 0)
        {
            pAdapterInfo->dwIpAddr = ((sockaddr_in*)ifa->ifa_addr)->sin_addr.s_addr;
            pAdapterInfo->dwIpMask = ((sockaddr_in*)ifa->ifa_netmask)->sin_addr.s_addr;

            freeifaddrs(ifap);
            return TRUE;
        }
        nAdapterIndex--;
    }

Exit0:
    if (ifap)
        freeifaddrs(ifap);
    return FALSE;
}

UINT32 GetIp(const char* pcszIntranetAddr, const char* pcszIntranetMask, BOOL bIntranet, INT32 nIndex)
{
    ADAPTER_INFO info;
    UINT32 dwSubnetAddr = 0;
    UINT32 dwSubnetMask = 0;

    dwSubnetAddr = inet_addr(pcszIntranetAddr);
    dwSubnetMask = inet_addr(pcszIntranetMask);

    if (dwSubnetAddr == 0xFFFFFFFF)
    {
        for (INT32 i = 0; i < MAX_ADAPTER_COUNT; i++)
        {
            INT32 nRetCode = GetNetworkAdapterInfo(i, &info);
            LOG_PROCESS_ERROR(nRetCode);

            if (info.dwIpAddr == 0)
                continue;

            if (nIndex == 0)
                return info.dwIpAddr;
            nIndex--;
        }
    }
    else
    {
        for (INT32 i = 0; i < MAX_ADAPTER_COUNT; i++)
        {
            INT32 nRetCode = GetNetworkAdapterInfo(i, &info);
            PROCESS_ERROR(nRetCode);

            if (info.dwIpAddr == 0)
                continue;

            if ((info.dwIpAddr & dwSubnetMask) == (dwSubnetAddr & dwSubnetMask))
            {
                if (bIntranet)
                {
                    if (nIndex == 0)
                        return info.dwIpAddr;
                    nIndex--;
                }
            }
            else
            {
                if (!bIntranet)
                {
                    if (nIndex == 0)
                        return info.dwIpAddr;
                    nIndex--;
                }
            }
        }
    }

Exit0:
    return 0;
}

#endif //WIN32

