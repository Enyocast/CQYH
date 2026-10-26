#include "stdafx.h"
#include "transmit_file_mgr.h"

#include "id_object_pool.h"
#include "ifile.h"
#include "pak_loader.h"

#include "maintaintool.h"
#include "message_handler.h"

#include <string>
//#include "sddir.h"
//#include "sdfile.h"
//using namespace SGDP;

CTransmitFileMgr CTransmitFileMgr::ms_Instance;
CTransmitFileMgr::CTransmitFileMgr()
{
	m_mapGuardVersionPool.clear();
	m_mapGuardVersionSending.clear();
}

CTransmitFileMgr::~CTransmitFileMgr()
{
    UnInit();
}

BOOL CTransmitFileMgr::Reload()
{
	m_mapGuardVersionPool.clear();
	m_mapGuardVersionSending.clear();

	for(INT32 i = 1; i < MAX_AREA_COUNT; ++i)
	{
		if(g_MTConfig.AreaConfig[i].areaID > 0)
		{
			for(INT32 j = 1; j < MAX_GUARD_COUNT_PER_AREA; ++j)
			{
				if(g_MTConfig.AreaConfig[i].guardList[j].szAddress[0] != 0)
				{
					STransmitFileCtx* pstVersion = new STransmitFileCtx();
					memset(pstVersion, 0, sizeof(STransmitFileCtx));
					pstVersion->nAreaID = g_MTConfig.AreaConfig[i].areaID;
					pstVersion->dwIp = inet_addr(g_MTConfig.AreaConfig[i].guardList[j].szAddress);

					INT64 qwKey = _GenerateKey(pstVersion->nAreaID, pstVersion->dwIp);
					m_mapGuardVersionPool.insert(std::make_pair(qwKey, pstVersion));
				}
			}	
		}
	}

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CTransmitFileMgr::UnInit(void)
{
    INT32 nRetCode = 0;

	for(iterKey2GuardVersion itr = m_mapGuardVersionPool.begin(); itr != m_mapGuardVersionPool.end(); ++itr)
	{
        STransmitFileCtx* pGuardSend = itr->second;
		if(pGuardSend != NULL)
        {
            //if(pGuardSend->m_poFileHandler)
            //{
            //    nRetCode = fclose(pGuardSend->m_poFileHandler);
            //    LOG_CHECK_ERROR(nRetCode == 0);
            //}
			SAFE_DELETE(pGuardSend);
        }
	}

	for(iterKey2GuardVersion itr = m_mapGuardVersionSending.begin(); itr != m_mapGuardVersionSending.end(); ++itr)
    {
        STransmitFileCtx* pGuardSend = itr->second;
        if(pGuardSend != NULL)
        {
            if(pGuardSend->pFileHandler)
            {
                nRetCode = fclose(pGuardSend->pFileHandler);
                LOG_CHECK_ERROR(nRetCode == 0);
            }
            SAFE_DELETE(pGuardSend);
        }
	}

	m_mapGuardVersionPool.clear();
	m_mapGuardVersionSending.clear();

    return TRUE;
}

STransmitFileCtx* CTransmitFileMgr::NewGuardSending(INT64 qwKey)
{
	STransmitFileCtx* pstNewBaseSend = NULL;
     std::pair<iterKey2GuardVersion, bool> InsertRes;

    iterKey2GuardVersion iter = m_mapGuardVersionPool.find( qwKey );
    LOG_PROCESS_ERROR( iter != m_mapGuardVersionPool.end() );

    pstNewBaseSend = iter->second;
	if(pstNewBaseSend)
    {
        InsertRes = m_mapGuardVersionSending.insert( std::make_pair(qwKey, pstNewBaseSend) );
        LOG_PROCESS_ERROR( InsertRes.second == true );
    }

    m_mapGuardVersionPool.erase(iter);

	return pstNewBaseSend;
Exit0:
    return NULL;
}

BOOL CTransmitFileMgr::DeleteGuardSending( INT64 qwKey )
{
    STransmitFileCtx* pstBaseVersionSend = NULL;
    std::pair<iterKey2GuardVersion, bool > InsertRes;

	iterKey2GuardVersion iter = m_mapGuardVersionSending.find(qwKey);
    PROCESS_ERROR( iter != m_mapGuardVersionSending.end() );

    pstBaseVersionSend = iter->second;
    LOG_PROCESS_ERROR(pstBaseVersionSend);

	pstBaseVersionSend->wBufferIndex = 0;
	pstBaseVersionSend->wBufferTotal = 0;

    if( pstBaseVersionSend->pFileHandler )
    {
        fclose( pstBaseVersionSend->pFileHandler );
        pstBaseVersionSend->pFileHandler = NULL;
    }
	pstBaseVersionSend->nFileType = InternalMessage::etftInvalid;
    memset(pstBaseVersionSend->szFileNames, 0, sizeof(pstBaseVersionSend->szFileNames) );
    memset(pstBaseVersionSend->szFilePaths, 0, sizeof(pstBaseVersionSend->szFilePaths) );
    pstBaseVersionSend->wBufferTotal = 0;
    pstBaseVersionSend->wBufferIndex = 0;
    pstBaseVersionSend->wFileIndex = 0;
    pstBaseVersionSend->wFileTotal = 0;

	m_mapGuardVersionSending.erase(qwKey);

	InsertRes = m_mapGuardVersionPool.insert(std::make_pair(qwKey, pstBaseVersionSend));
    LOG_PROCESS_ERROR( InsertRes.second );

	return TRUE;
Exit0:
	return FALSE;
}

STransmitFileCtx* CTransmitFileMgr::GetPendingSending( INT32 nAreaID, UINT32 dwIp )
{
	INT64 qwKey = _GenerateKey( nAreaID, dwIp );
    STransmitFileCtx* pstBaseSend = NULL;
    iterKey2GuardVersion itr = m_mapGuardVersionSending.find( qwKey );
    if ( itr != m_mapGuardVersionSending.end() )
    {
        pstBaseSend = itr->second;
    }

Exit0:
    return pstBaseSend;
}

CTransmitFileMgr& CTransmitFileMgr::GetInstance(void)
{
    return ms_Instance;
}


BOOL CTransmitFileMgr::MainLoop()
{
	INT32 nRetCode = 0;
	STransmitFileCtx* pCtx = NULL;
	
	UINT16 wBufferSize = 0;
	static char szBuffer[G_FILE_SEND_BLOCK];

    for(iterKey2GuardVersion itr = m_mapGuardVersionSending.begin(); itr != m_mapGuardVersionSending.end(); ++itr)
    {
        pCtx = itr->second;
        LOG_PROCESS_ERROR( pCtx );
        if(pCtx->wBufferIndex >= pCtx->wBufferTotal &&
            pCtx->wFileIndex >= pCtx->wFileTotal)
        {
            LOG_PROCESS_ERROR( NULL == pCtx->pFileHandler );
            continue;
        }

        for(INT32 index = 0;  index < SEND_BLOCK_PER_LOOP; ++index)
        {
            if(pCtx->wBufferIndex >= pCtx->wBufferTotal &&
               pCtx->wFileIndex >= pCtx->wFileTotal)
            {
                LOG_PROCESS_ERROR( NULL == pCtx->pFileHandler );
                break;
            }

            //1 open file if need
            if( NULL == pCtx->pFileHandler )
            {
                INT32 nFileSize = 0;
                LOG_PROCESS_ERROR( pCtx->wFileIndex < pCtx->wFileTotal );

                pCtx->pFileHandler = fopen(pCtx->szFilePaths[pCtx->wFileIndex], "rb");
				if (pCtx->pFileHandler == NULL)
				{
					CRI("can't find file %s to send", pCtx->szFilePaths[pCtx->wFileIndex]);
					LOG_PROCESS_ERROR(FALSE);
				}

                nRetCode = fseek(pCtx->pFileHandler, 0, SEEK_END);
                LOG_PROCESS_ERROR(nRetCode == 0);
                nFileSize = ftell(pCtx->pFileHandler);

                nRetCode = fseek(pCtx->pFileHandler, 0, SEEK_SET);
                LOG_PROCESS_ERROR(nRetCode == 0);

                pCtx->wBufferTotal = (nFileSize - 1) / G_FILE_SEND_BLOCK + 1;
                pCtx->wBufferIndex = 0;
            }

            //2 read
            wBufferSize = fread(szBuffer, 1, G_FILE_SEND_BLOCK, pCtx->pFileHandler);

            //3 todo: as callback
            nRetCode = CMTMessageHandler::GetInstance().DoGDSendFiles(pCtx->nAreaID, pCtx->dwIp, pCtx->nFileType, pCtx->szFileNames[pCtx->wFileIndex], 
                pCtx->wBufferIndex, pCtx->wBufferTotal, wBufferSize, szBuffer, pCtx->wFileIndex, pCtx->wFileTotal);
            LOG_PROCESS_ERROR( nRetCode );

			nRetCode = MaintainTool::GetInstance().UpdateGuardSendProgress(pCtx->nAreaID, pCtx->dwIp,
                (double)(pCtx->wBufferIndex * 100 / pCtx->wBufferTotal) );
            LOG_PROCESS_ERROR( nRetCode );

            //4 close file if need
            if(feof(pCtx->pFileHandler))
            {
                LOG_PROCESS_ERROR( pCtx->wBufferIndex + 1 == pCtx->wBufferTotal );

                nRetCode = fclose(pCtx->pFileHandler);
                LOG_CHECK_ERROR(nRetCode == 0);

                pCtx->pFileHandler = NULL;
            }

            //5 proceeding
            if ( NULL == pCtx->pFileHandler )
            {
                ++pCtx->wFileIndex;     // next file
                pCtx->wBufferIndex = 0;
                pCtx->wBufferTotal = 0;
            }
            else
            {
                ++pCtx->wBufferIndex;
            }
        }
    }

Exit1:
    return TRUE;
Exit0:
    if(pCtx)
        StopSending(pCtx->nAreaID, pCtx->dwIp);
	return TRUE;// keep running
}

INT64 CTransmitFileMgr::_GenerateKey(INT32 nAreaID, UINT32 dwIP)
{ 
	return (((INT64)nAreaID) << 32) + (INT64)dwIP; 
}

BOOL CTransmitFileMgr::StartSending(INT32 nAreaID, UINT32 dwIp, INT32 nFileNum, const char* pFileNames[], const char* pFilePaths[], INT32 nFileType)
{
    INT32 nRetCode = 0;
    INT32 nFileSize = 0;
	INT64 qwKey = _GenerateKey(nAreaID, dwIp);

    STransmitFileCtx* pstSendCtx = NULL;
 
    LOG_PROCESS_ERROR( nFileNum < MAX_SENDING_FILES );

	pstSendCtx = NewGuardSending(qwKey);
    LOG_PROCESS_ERROR(pstSendCtx);

	pstSendCtx->nFileType = nFileType;
    for ( INT32 i=0; i<nFileNum; ++i)
    {
        strxcpy(pstSendCtx->szFileNames[i], pFileNames[i], COMMON_NAME_LEN);
        strxcpy(pstSendCtx->szFilePaths[i], pFilePaths[i], COMMON_NAME_LEN);
    }
    pstSendCtx->wFileTotal = nFileNum;
    pstSendCtx->wFileIndex = 0;

    pstSendCtx->wBufferIndex = 0; // mainloop proceed
    pstSendCtx->wBufferTotal = 0;

    return TRUE;
Exit0:
    StopSending( nAreaID, dwIp );
    return FALSE;

}

BOOL CTransmitFileMgr::StopSending(INT32 nAreaID, UINT32 dwIp)
{
	INT64 qwKey = _GenerateKey(nAreaID, dwIp);
	INT32 nRetCode = 0;

    STransmitFileCtx* pCtx = NULL;
    iterKey2GuardVersion itr = m_mapGuardVersionSending.find( qwKey );
    PROCESS_ERROR( itr != m_mapGuardVersionSending.end() );

    pCtx = itr->second;

    if(pCtx->pFileHandler)
    {
        nRetCode = fclose(pCtx->pFileHandler);
        LOG_CHECK_ERROR(nRetCode == 0);

        pCtx->pFileHandler = NULL;
        pCtx->wFileTotal = 0;
        pCtx->wFileIndex = 0;
        pCtx->wBufferIndex = 0;
        pCtx->wBufferTotal = 0;
    }

    DeleteGuardSending( qwKey );

    return TRUE;
Exit0:
	return FALSE;
}
