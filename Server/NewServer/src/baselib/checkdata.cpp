#include "stdafx.h"
#include "tabfile.h"
#include "checkdata.h"
#include "process_error.h"
#include "lua_script.h"
#include "script_mgr.h"
#include "string_def.h"
#include "utf8.h"

CCheckData CCheckData::ms_Instance;

CCheckData::CCheckData()
{
	m_bIsProgrammer = FALSE;
}

CCheckData::~CCheckData()
{

}

INT32 CCheckData:: Init(BOOL bIsProgrammer)
{
	memset(chString, 0, sizeof(chString));
	m_bIsProgrammer = bIsProgrammer;

	return TRUE;
}

INT32 CCheckData::UnInit()
{
	INT32 nRetCode = 0;

	nRetCode = _UnLoad();
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;

Exit0:
	return FALSE;
}

CCheckData& CCheckData::GetInstance(void)
{
	return ms_Instance;
}

BOOL CCheckData::Check(const char* pPath, const char* pFolderName)
{
//	INT32 nRetCode = 0;
//
//	CLog::GetInstance().WriteLog(lltLua, "Check Data Begin!");
//
//	IterMapConfig it;
//
//	CHAR szFilePath[256] = {0};
//	snprintf(szFilePath, sizeof(szFilePath), "%s/%s", pPath, pFolderName);
//
//	_Load(szFilePath);
//
//	it = m_MapConfig.begin();
//
//	while(it != m_MapConfig.end())
//	{
//		CLuaScript* pScript = NULL;
//
//		pScript = CScriptMgr::GetInstance().FindScript(CHECK_WORLD_DATA);
//		LOG_PROCESS_ERROR(pScript);
//
//		nRetCode = pScript->CallFunction("check", "s", it->first.c_str());
//		LOG_PROCESS_ERROR(nRetCode);
//
//		it++;
//	}
//
	return TRUE;
//Exit0:
//	return FALSE;
}

BOOL CCheckData::_Load(const char* pPath)
{
//	INT32 nRetCode = 0;
//	BOOL  bRet = FALSE;
//
//	char szFileName[256] = {0};
//	char* szFileNameTail = ".txt";
//	char* pTail = NULL;
//	CTabFile* pTabConfig = NULL;
//
//	CSDDirectory oDirectory;
//	nRetCode = oDirectory.Open( pPath );
//	LOG_PROCESS_ERROR(nRetCode);
//
//	// for file in directory
//	while( TRUE )
//	{
//		nRetCode = oDirectory.Read( szFileName, sizeof(szFileName), NULL);
//		if( !nRetCode )
//			break;
//
//		pTail = szFileName + strlen(szFileName) - strlen(szFileNameTail); 
//		if( strncmp( pTail, szFileNameTail, strlen(szFileNameTail) ) != 0 )
//			continue;
//
//		szFileName[strlen(szFileName) - strlen(szFileNameTail)] = '\0';
//		pTabConfig = new CTabFile;
//		LOG_PROCESS_ERROR(pTabConfig);
//
//		bRet = pTabConfig->Init(szFileName, pPath);
//		LOG_PROCESS_ERROR(bRet);
//
//		_RegisterName2TabConfig(szFileName, pTabConfig);
//	}
//
//	oDirectory.Close();
//
//	return TRUE;
//
//Exit0:
//	oDirectory.Close();
	
	return FALSE;

}

BOOL CCheckData::_UnLoad()
{
	IterMapConfig it;

	it = m_MapConfig.begin();
	while (it != m_MapConfig.end())
	{
		SAFE_DELETE(it->second)
		it++;
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CCheckData::_RegisterName2TabConfig(const char* pName, CTabFile* pTabConfig)
{	
	IterMapConfig it;

	it = m_MapConfig.find(pName);
	LOG_PROCESS_ERROR( it == m_MapConfig.end() );

	m_MapConfig.insert(std::make_pair(pName, pTabConfig));

	return TRUE;
Exit0:
	return FALSE;
}

CTabFile* CCheckData::GetDataByName(const char* pName)
{
	IterMapConfig it;

	LOG_PROCESS_ERROR(pName);

	it = m_MapConfig.find(pName);
	LOG_PROCESS_ERROR( it != m_MapConfig.end() );

	return it->second;

Exit0:
	return NULL;
}

INT32 CCheckData::GetTabRowCount(CTabFile* pTab)
{
	LOG_PROCESS_ERROR(pTab);

	return pTab->GetRowCount();
Exit0:
	return 0;
}

INT32 CCheckData::GetTabColCount(CTabFile* pTab)
{
	LOG_PROCESS_ERROR(pTab);

	return pTab->GetColCount();
Exit0:
	return 0;

}

INT32 CCheckData::GetNumber(CTabFile* pTab, char* pCol, INT32 nRow)
{	
	INT32 nValue = 0;
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(pTab);
	LOG_PROCESS_ERROR(pCol);
	LOG_PROCESS_ERROR(nRow < pTab->GetRowCount());

	nRetCode = pTab->ReadData(pCol, nRow, nValue);
	LOG_PROCESS_ERROR(nRetCode);

	return nValue;
Exit0:
	return -1;
}

const char* CCheckData::GetColName(CTabFile* pTab, INT32 nColID)
{
	LOG_PROCESS_ERROR(pTab);

	return pTab->GetColName(nColID);
Exit0:
	return NULL;
}

char* CCheckData::GetString(CTabFile* pTab, char* pCol, INT32 nRow)
{	
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(pTab);
	LOG_PROCESS_ERROR(pCol);
	LOG_PROCESS_ERROR(nRow < pTab->GetRowCount());

	nRetCode = pTab->ReadData(pCol, nRow, chString, sizeof(chString));
	LOG_PROCESS_ERROR(nRetCode);

	return chString;
Exit0:
	return NULL;
}

void CCheckData::PrintInfo(char* pInfo)
{
	CLog::GetInstance().InfLog(pInfo);
}

void CCheckData::PrintWrn(char* pWrn)
{
	CLog::GetInstance().WrnLog(pWrn);
	if (!m_bIsProgrammer)
	{
		INT32 nLen = 0;
		wchar_t szMessage[1024];
		nLen = utf8_2_utf16(pWrn, strlen(pWrn), szMessage, 1024);
		szMessage[nLen] = 0;
		MessageBoxW(NULL, szMessage, 0, 0);
	}
}