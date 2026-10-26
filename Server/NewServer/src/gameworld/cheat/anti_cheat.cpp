#include "stdafx.h"
#include "anti_cheat.h"
#include "string_def.h"
#include "dds_def.h"
#include "game_world_config.h"
#include "ifile.h"

CAntiCheatMgr CAntiCheatMgr::ms_Instance;

CAntiCheatMgr::CAntiCheatMgr(void)
{

}

CAntiCheatMgr::~CAntiCheatMgr(void)
{

}

CAntiCheatMgr& CAntiCheatMgr::GetInstance(void)
{
	return ms_Instance;
}

BOOL CAntiCheatMgr::Init(void)
{
	INT32 nRetCode = 0;
	INT32 nFileIdx = 0;
	char szPath[MAX_PATH] = { 0 };

	while (TRUE)
	{
		snprintf(szPath, MAX_PATH, "%s/%s/%d.dds", g_GWConfig.szConfigPath, ANTI_CHEAT_FILE_FOLDER, ++nFileIdx);

		if (!g_IsFileExist(szPath))
			break;

		nRetCode = _ProcessDDS(szPath);
		if (!nRetCode)
			break;

		INF("anti-cheat file loaded: %s", szPath);
	}

	for (INT32 i = 0; i < 10; i++)
	{
		JigsawImage Image;
		JigsawAnswer Answer;
		GenerateJigsaw(&Image, &Answer);
	}

	return TRUE;
Exit0:
	return FALSE;
}

void CAntiCheatMgr::UnInit(void)
{
	for (TPicDataList::iterator itr = m_List.begin(); itr != m_List.end(); ++itr)
	{
		delete (*itr);
	}

	m_List.clear();
}

BOOL CAntiCheatMgr::_ProcessDDS(const char* szFileName)
{
	INT32 nRetCode = 0;
	DDS_HEADER hdr = { 0 };
	UINT32 dwMagic = 0;
	JigsawImage* poImage = NULL;

	IFile* poFile = g_OpenFile(szFileName, "rb");
	LOG_PROCESS_ERROR(poFile);

	nRetCode = poFile->Read(&dwMagic, sizeof(UINT32));
	LOG_PROCESS_ERROR(nRetCode == sizeof(UINT32));

	LOG_PROCESS_ERROR(dwMagic = 0x20534444);

	nRetCode = poFile->Read(&hdr, sizeof(DDS_HEADER));
	LOG_PROCESS_ERROR(nRetCode == sizeof(DDS_HEADER));

	LOG_PROCESS_ERROR(hdr.dwWidth == JIGSAW_PIC_WIDTH && hdr.dwHeight == JIGSAW_PIC_WIDTH);
	LOG_PROCESS_ERROR(hdr.dwPitchOrLinearSize == JIGSAW_DATA_SIZE);
	LOG_PROCESS_ERROR(hdr.ddspf.dwFourCC == JIGSAW_PIC_FOURCC);

	poImage = new JigsawImage;

	for (INT32 i = 0; i < JIGSAW_PIC_WIDTH_IN_BLOCK; i++)
	{
		for (INT32 j = 0; j < JIGSAW_PIC_WIDTH_IN_BLOCK; j++)
		{
			nRetCode = poFile->Read(&poImage->qwBlock[i][j], sizeof(UINT64));
			LOG_PROCESS_ERROR(nRetCode == sizeof(UINT64));
		}
	}

	m_List.push_back(poImage);

	poFile->Close();
	return TRUE;
Exit0:
	if (poFile)
		poFile->Close();

	if (poImage)
		delete poImage;
	poImage = NULL;

	return FALSE;
}

BOOL CAntiCheatMgr::GenerateJigsaw(JigsawImage* poImage, JigsawAnswer* poAnswer)
{
	INT32 nAnswerX = 0, nAnswerY = 0;
	JigsawImage* poOriginImage = NULL;
	JigsawImage* poFakeImage = NULL;
	INT32 nUsedIdx[JIGSAW_ANSWER_COUNT];
	BOOL bSucc = TRUE;
	INT32 nX = 0, nY = 0;
	INT32 nImageIndex = 0;
	INT32 nFakeImageIndex = 0;

	LOG_PROCESS_ERROR(poImage);
	LOG_PROCESS_ERROR(poAnswer);

	for (INT32 i = 0; i < JIGSAW_ANSWER_COUNT; i++)
		nUsedIdx[i] = -1;

	poAnswer->nAnswerIdx = g_Random(JIGSAW_ANSWER_COUNT);

	nImageIndex = g_Random(m_List.size());

	if (nImageIndex > 0)
		nFakeImageIndex = nImageIndex - 1;
	else
		nFakeImageIndex = m_List.size() - 1;

	poOriginImage = m_List[nImageIndex];
	poFakeImage = m_List[nFakeImageIndex];

	memcpy(poImage, poOriginImage, sizeof(JigsawImage));

	poImage->nImageIndex = nImageIndex;

//	DBG("avaiable count: %d, line size: %d", JIGSAW_AVAIABLE_COUNT, JIGSAW_AVAIABLE_COUNT_PER_LINE);

	for (INT32 n = 0; n < JIGSAW_ANSWER_COUNT; )
	{
		INT32 nIndex = g_Random(0, JIGSAW_AVAIABLE_COUNT);

		for (INT32 m = 0; m < n; m++)
		{
			if (nUsedIdx[m] == nIndex)
			{
				bSucc = FALSE;
				break;
			}
			bSucc = TRUE;
		}

		if (!bSucc)
			continue;

		nUsedIdx[n] = nIndex;

		INT32 nTest = JIGSAW_AVAIABLE_COUNT_PER_LINE;

		nY = nIndex / JIGSAW_AVAIABLE_COUNT_PER_LINE * JIGSAW_ANSWER_DIFF_IN_BLOCK;
		nX = nIndex % JIGSAW_AVAIABLE_COUNT_PER_LINE * JIGSAW_ANSWER_DIFF_IN_BLOCK;

//		DBG("-- idx: %d, x: %d, y: %d", nIndex, nX, nY);

		nX += JIGSAW_ANSWER_BORDER_OFFSET_IN_BLOCK;
		nY += JIGSAW_ANSWER_BORDER_OFFSET_IN_BLOCK;

		if (n == poAnswer->nAnswerIdx)
		{
			nAnswerX = nX; nAnswerY = nY;
			// fill answer pics block by block.
			for (INT32 i = 0; i < JIGSAW_ANSWER_WIDTH_IN_BLOCK; i++)
			{
				for (INT32 j = 0; j < JIGSAW_ANSWER_WIDTH_IN_BLOCK; j++)
				{
					poAnswer->Answer[n].qwBlock[i][j] = poImage->qwBlock[nX + i][nY + j];
				}
			}
		}
		else
		{
			for (INT32 i = 0; i < JIGSAW_ANSWER_WIDTH_IN_BLOCK; i++)
			{
				for (INT32 j = 0; j < JIGSAW_ANSWER_WIDTH_IN_BLOCK; j++)
				{
					poAnswer->Answer[n].qwBlock[i][j] = poFakeImage->qwBlock[nX + i][nY + j];
				}
			}

		}



		n++;
	}

	for (INT32 i = 0; i < JIGSAW_ANSWER_WIDTH_IN_BLOCK; i++)
	{
		for (INT32 j = 0; j < JIGSAW_ANSWER_WIDTH_IN_BLOCK; j++)
		{
			poImage->qwBlock[nAnswerX + i][nAnswerY + j] = 0;
		}
	}

	poAnswer->nBlockX = nAnswerX;
	poAnswer->nBlockY = nAnswerY;

	return TRUE;
Exit0:
	return FALSE;
}
