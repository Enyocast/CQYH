#ifndef _TRANSMIT_FILE_MGR_H_
#define _TRANSMIT_FILE_MGR_H_

#include "server_def.h"
#include "string_def.h"

#include <map>

#define SEND_BLOCK_PER_LOOP 10 
#define MAX_SENDING_FILES 8 

struct STransmitFileCtx
{
	INT32	nAreaID;
	UINT32	dwIp;

    UINT16	wFileIndex;
    UINT16	wFileTotal;
	INT32	nFileType;
    char	szFileNames[MAX_SENDING_FILES][COMMON_NAME_LEN];
    char	szFilePaths[MAX_SENDING_FILES][COMMON_NAME_LEN];

    FILE*   pFileHandler;

	UINT16	wBufferTotal;
	UINT16	wBufferIndex;

};


class CTransmitFileMgr
{
public:
    CTransmitFileMgr();
    ~CTransmitFileMgr();

    BOOL Reload();
    BOOL UnInit(void);
    static CTransmitFileMgr& GetInstance(void);

	BOOL StartSending(INT32 nAreaID, UINT32 dwIp, INT32 nFileNum, const char* pFileNames[], const char* pFilePaths[], INT32 nFileType);
	BOOL StopSending(INT32 nAreaID, UINT32 dwIp);
	STransmitFileCtx*   GetPendingSending(INT32 nAreaID, UINT32 dwIp);

    BOOL MainLoop();

private:
	INT64 _GenerateKey(INT32 nAreaID, UINT32 dwIP);
	STransmitFileCtx*	NewGuardSending(INT64 qwKey);
	BOOL				DeleteGuardSending(INT64 qwKey);


    typedef std::map<INT64, STransmitFileCtx*>			mapKey2GuardVersion;
    typedef std::map<INT64, STransmitFileCtx*>::iterator	iterKey2GuardVersion;

    mapKey2GuardVersion			m_mapGuardVersionPool;
    mapKey2GuardVersion			m_mapGuardVersionSending;
	
    static CTransmitFileMgr		ms_Instance;
};
#endif  // _TRANSMIT_FILE_MGR_H_