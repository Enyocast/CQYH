#ifndef _GUARD_SERVER_H_
#define _GUARD_SERVER_H_

#include <list>
#include <vector>

#include "server_def.h"
#include "packet_allocator.h"

#include "gd_message_handler.h"


class INet;
class ISocketAcceptor;

class CGuardServer
{
public:
    CGuardServer();
    ~CGuardServer();

    static CGuardServer& GetInstance(void);

    BOOL Init(INetEventHandler* poNetEventHandler);
    BOOL UnInit(void);
    
    BOOL Close(void);
    BOOL MainLoop(void);

    INet* GetNetInterface(void)                     {return m_pNet;}
    IPacketAllocator* GetPacketAllocator(void)      {return &m_PacketAllocator;}

    BOOL IsRuning()                                 {return m_bRun;}
    
	void Cls();
    BOOL PrintCmdPrompt();

	BOOL ReloadConfig();

	void SetProcessingVersion(const char* szVersion)	{ strxcpy(m_szProcessingVersion, szVersion, sizeof(m_szProcessingVersion)); }
	void SetProcessingPatch(const char* szPatch)	{ strxcpy(m_szProcessingPatch, szPatch, sizeof(m_szProcessingPatch)); }

	BOOL ProcessDeployServerVersion();
	BOOL ProcessHotUpdatePatch();
    BOOL FetchCurrentVersion( char* pcszCurrentVersion, int nLen  );

private:
    BOOL _UpdateScreen();
	BOOL _PrintProcessContent();
	BOOL _GetLogSubFolders(const char* pszTargetDir);
	BOOL _EraseOldestLogSubFolders(std::string strSubFolderName);
	BOOL _AsyncEraseOldestLogSubFolders(std::string strSubFolderName);

	std::vector<std::string> m_roLogFolderEntries;
    static CGuardServer     ms_Instance;
	BOOL                    m_bRun;
	UINT64					m_qwLatestTickCheckDiskSpace;

    INet*                   m_pNet;
    ISocketAcceptor*        m_pSocketAcceptor;
    CPacketAllocator        m_PacketAllocator;

	CHAR					m_szProcessingVersion[128];
	CHAR					m_szProcessingPatch[128];
};

#endif  // _GUARD_SERVER_H_