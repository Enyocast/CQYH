// exportdb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sol_bindings.h"
#include "string_ex.h"
#include "sql_mgr.h"
#include "ifile.h"
#include "string_def.h"
#include "server_def.h"
#include "process_option.h"
#include "global_config.h"
#include "zlib.h"
#include "server_config.h"
#include "math_ex.h"
#include "game_world.h"
#include "net.h"
#include "packet_allocator.h"
#include "imessage_notifier.h"
#include "script_mgr.h"
#include "role_db_def.h"
#include "data_manager.h"
#include "achievement_data.h"

#include "../../src/manageserver/guild/guild_storage.h"


#include "define.h"
#include "guild.h"

BOOL check_item_guid = TRUE;

UINT32 g_dwStartID = 0;
UINT32 g_dwCount = 0;


SQL_STMT_DATA g_SqlStmtList[mysqlTotal] =
{
	{ 0, mysqlSelectAllRole, "SELECT RoleID{ud}, RoleName{s24}, UserName{s64}, RoleData{b8192} from role", },
	{ 0, mysqlSelect1DayRole, "SELECT t.RoleID{ud}, t.RoleName{s20}, t.UserName{s64}, t.RoleData{b8192} FROM \
							  (SELECT t1.RoleID, t1.RoleName, t1.UserName, t1.RoleData, t2.maxtime FROM role AS t1 \
							  INNER JOIN (SELECT username, MAX(logintime) AS maxtime, createtime FROM role GROUP BY username) t2 \
							  ON t1.username = t2.username AND t2.maxtime = logintime \
							  WHERE t2.maxtime < \"2014-09-26\" AND t2.createtime < \"2014-09-26\") AS t" },
	{ 0, mysqlSelectHighestRole, "SELECT t1.RoleID{ud}, t1.RoleName{s20}, t1.UserName{s64}, t1.RoleData{b8192} FROM role AS t1 \
								 INNER JOIN (SELECT roleid, username, rolename, roledata, MAX(logintime) AS maxtime, createtime \
								 FROM role GROUP BY username) t2 ON t1.username = t2.username AND t2.maxtime = logintime" },
    //{ 0, mysqlSelectGuildStorage , "SELECT GuildID{ud}, StorageData{b43008} FROM guild"},

    { -1, mysqlInsertRole, "INSERT INTO role (GroupID, RoleID, RoleName, UserName, CreateTime, DeleteTime, LoginTime, RoleDeleted, BaseData, RoleData) VALUES (0, [ud], [s24], [s63], now(), 0, now(), 0, [b8192], [b8192])" },

    { 0, mysqlSelectGuild, "SELECT CreateTime{s20}, DeleteTime{s20}, GuildID{ud}, Version{uh}, GuildName{s24}, GroupID{uc}, LeaderID{ud}, CreaterName{s24}, UNIX_TIMESTAMP(CreateTime){d}, Announce{s100}, Notice{s200}, MainData{z60000} FROM guild" },
    { 0, mysqlSelectGuildMemberCount , "SELECT count(*){d} from guild_member WHERE GuildID = [ud]"},
    { 0, mysqlSelectGuildMemberInfo , "SELECT a1.RoleID{ud}, a1.GuildID{ud}, a2.GuildName{s24}, a3.RoleName{s24}, a3.UserName{s64} FROM \
                                        guild_member AS a1 INNER JOIN (SELECT GuildID, GuildName FROM guild) a2 INNER JOIN (SELECT \
                                        RoleID, RoleName, UserName FROM role) a3 ON a1.GuildID = a2.GuildID AND a1.RoleID = a3.RoleID" },
};


CPacketAllocator g_PacketAllocator;

std::map<UINT64, INT32> g_ItemGuidMap;

class CMessageNotifier : public IMessageNotifier
{
	virtual BOOL SendToUser(UINT32 dwClientSessionID, PACKET_BUFFER* pData, UINT32 dwSize) { g_PacketAllocator.Free(pData); return TRUE; }
	virtual BOOL SendToUsers(UINT32 dwGTSessionID, UINT32 dwClientSessionIDList[], INT32 nSessionCount, PACKET_BUFFER* pData, UINT32 dwSize) 
	{
		g_PacketAllocator.Free(pData); 
		return TRUE;
	}
	virtual BOOL SendToMS(PACKET_BUFFER* pData, UINT32 dwSize) { g_PacketAllocator.Free(pData); return TRUE; }
	virtual BOOL SendToDL(PACKET_BUFFER* pData, UINT32 dwSize) { g_PacketAllocator.Free(pData); return TRUE; }

	virtual BOOL ReturnSelectRole(UINT32 dwClientSessionID) { return TRUE; }
	virtual BOOL SaveRoleData(CRole* poRole, BOOL bSaveFile) { return TRUE; }
	virtual BOOL UnlockRole(CRole* poRole) { return TRUE; }
	virtual BOOL _KickUser(UINT32 dwClientSessionID) { return TRUE; }

	virtual BOOL Logout(UINT32 dwClientSessionID) { return TRUE; }
};


void _InitMathTable(void)
{
	memset(&g_MathTable, 0, sizeof(g_MathTable));

	for (int nDirection = 0; nDirection < MAX_DIRECTION_COUNT; nDirection++)
	{
		g_MathTable.nSinTable[nDirection] = (INT32)floor(sin((double)nDirection * 2 * PI / MAX_DIRECTION_COUNT) * SIN_COS_NUMBER + 0.5f);
		g_MathTable.nCosTable[nDirection] = (INT32)floor(cos((double)nDirection * 2 * PI / MAX_DIRECTION_COUNT) * SIN_COS_NUMBER + 0.5f);
	}

	for (int nDirection = 0; nDirection < MAX_DIRECTION_COUNT / 4; nDirection++)
	{
		g_MathTable.nSinSquareTable[nDirection] = g_MathTable.nSinTable[nDirection] * g_MathTable.nSinTable[nDirection];
	}

	for (int i = 0; i < MAX_SQUARE; i++)
	{
		g_MathTable.wSqrtTable[i] = (UINT16)floor(sqrt((double)i) + 0.5f);
	}
}

BOOL _ExportCallBackFunc(std::list<void*>& rResult, void* pUserData)
{
#pragma pack(push, 1)
	struct RESULT_DATA
	{
		UINT32	dwRoleID;
		char	szRoleName[ROLE_NAME_LEN];
		char	szUserName[USER_NAME_LEN];
		UINT32	dwRoleDataSize;
		char	szRoleData[8192];
	};

	struct KEY_DATA
	{
		UINT32	dwRoleID;
		char	szRoleName[ROLE_NAME_LEN];
		INT32	nVarList[MAX_CLIENT_VARIABLE_COUNT];
	};
#pragma pack(pop)

	INT32 nRetCode = 0;
	FILE* pFile = NULL;
	static char s_szMessage[1024 * 1024 * 16];
	INT32 nMessaegSize = 0;
	static KEY_DATA* s_pData = NULL;
	INT32 nRoleCount = 0;

	s_pData = new KEY_DATA[rResult.size()];
	LOG_PROCESS_ERROR(s_pData);

	nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "roleid\trolename\tusername\tlevel\texp\tclass\tmoney0\tmoney1");
	nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\tdeleted");
	nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\tscenetempid\tsceneid\tposx\tposy");
	nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\tcreatetime\tsavetime\titemcount");
	nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\t spell1 \t spell2 \t spell3 \t spell4 \t spell5 \t spell6 \t spell7 \t spell8 \t spell9 \t spell10 \t spell11 \t spell12");

	for (INT32 nIndex = avdStatisticBegin; nIndex < avdStatisticEnd; nIndex++)
	{
		nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\tStat%d", nIndex);
	}

	for (INT32 nIndex = 0; nIndex < MAX_CLIENT_VARIABLE_COUNT; nIndex++)
	{
		nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\tClientVar%d", nIndex);
	}

	nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\n");

	for (std::list<void*>::iterator it = rResult.begin();
		it != rResult.end(); ++it)
	{
		CRole Role;
		RESULT_DATA * pResultData = (RESULT_DATA*)*it;
		static UINT8 s_szRoleData[65536];
		UINT32 dwRoleDataSize = 65536;
		UINT32 dwDeleteTime = 0;
		ROLE_DB_DATA* pRoleData = (ROLE_DB_DATA*)s_szRoleData;

		nRetCode = uncompress(s_szRoleData, (uLongf*)&dwRoleDataSize, (const Bytef*)pResultData->szRoleData, pResultData->dwRoleDataSize);
		if (nRetCode != Z_OK)
			continue;

		nRetCode = Role.Init(pResultData->dwRoleID, 0);
		if (!nRetCode)
			continue;

		nRetCode = Role.Load((const char*)s_szRoleData, dwRoleDataSize);
		if (!nRetCode)
		{
			if (pRoleData->BlockTable[0].btBlockType != rbtBase)
				continue;

			ROLE_DB_BASE_DATA* pBaseData = (ROLE_DB_BASE_DATA*)(pRoleData->RoleData + pRoleData->BlockTable[0].dwStartOffset);
			dwDeleteTime = pBaseData->dwDeleteTime;
			pBaseData->dwDeleteTime = 0;
			if (pBaseData->byLevel == 0)
			{
				pRoleData->dwCRC = crc32(0, (const Bytef*)&pRoleData->dwVersion,
					pRoleData->dwLen - sizeof(pRoleData->dwLen) - sizeof(pRoleData->dwCRC));
			}

			nRetCode = Role.Load((const char*)s_szRoleData, dwRoleDataSize);
			if (!nRetCode)
				continue;
		}
		ROLE_DB_BASE_DATA* pBaseData = (ROLE_DB_BASE_DATA*)(pRoleData->RoleData + pRoleData->BlockTable[0].dwStartOffset);

		char szRoleName[128];
		strxcpy(szRoleName, Role.GetName(), ROLE_NAME_LEN);
		for (int i = 0; i < strlen(szRoleName); i++)
		{
			if (szRoleName[i] == '\r' || szRoleName[i] == '\n')
				szRoleName[i] = '|';
		}
		nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "%d\t%s\t%s\t%d\t%d\t%d\t%d\t%d",
			Role.GetObjID(), Role.GetName(), pResultData->szUserName, Role.GetLevel(), Role.GetExp(), Role.GetClass(),
			Role.GetItemBag()->GetMoney(MONEYTYPE_01), Role.GetItemBag()->GetMoney(MONEYTYPE_02));

		if (dwDeleteTime > 0)
			nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\t%d", 1);
		else
			nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\t%d", 0);


		nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\t%d\t%d\t%d\t%d", 
			pBaseData->nSceneTempID, pBaseData->nSceneID, pBaseData->nX, pBaseData->nY);

		time_t CreateTime = Role.GetCreateTime();
		struct tm* t = localtime(&CreateTime);
		nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\t%d-%02d-%02d %02d:%02d:%02d", 
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

		time_t SaveTime = pBaseData->dwSaveTime;
		t = localtime(&SaveTime);
		nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\t%d-%02d-%02d %02d:%02d:%02d",
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

		{
			int nItemCount = 0;
			const Item* item = NULL;
			CItemBag* bag = Role.GetItemBag();
			bag->Begin();
			item = bag->Next();
			while (item)
			{
				if (item->m_iteminfo.m_nTemplateID == 93001)
					nItemCount += item->m_iteminfo.m_nCurDur;
				++g_ItemGuidMap[item->m_iteminfo.m_llGuid];
				item = bag->Next();
			}

			nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\t%d", nItemCount);
		}

		for (INT32 nIndex = qssActiveBegin; nIndex < qssActiveEnd; nIndex++)
		{
			nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\t%d", Role.GetSpellSlot(nIndex)->GetMainSpellID());
		}

		for (INT32 nIndex = avdStatisticBegin; nIndex < avdStatisticEnd; nIndex++)
		{
			nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\t%d", Role.GetAchievementList().GetVariable(nIndex));
		}


		for (INT32 nIndex = 0; nIndex < MAX_CLIENT_VARIABLE_COUNT; nIndex++)
		{
			nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\t%d", Role.GetClientVariable(nIndex));
			s_pData[nRoleCount].nVarList[nIndex] = Role.GetClientVariable(nIndex);
		}

		nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "\n");
		nRoleCount++;

        if (check_item_guid)
        {
            const Item* item = NULL;
            CItemBag* bag = Role.GetItemBag();
            bag->Begin();
            item = bag->Next();
            while (item)
            {
                ++g_ItemGuidMap[item->m_iteminfo.m_llGuid];
                item = bag->Next();
            }
        }

		nRetCode = Role.UnInit();
		LOG_CHECK_ERROR(nRetCode);
	}

	pFile = fopen("exportdb.txt", "wb");
	LOG_PROCESS_ERROR(pFile);

	nRetCode = fwrite(s_szMessage, 1, nMessaegSize, pFile);
	LOG_PROCESS_ERROR(nRetCode == nMessaegSize);

	fclose(pFile);
	pFile = NULL;

	pFile = fopen("exportdb.dat", "wb");
	LOG_PROCESS_ERROR(pFile);

	nRetCode = fwrite(s_pData, 1, sizeof(KEY_DATA) * nRoleCount, pFile);
	LOG_PROCESS_ERROR(nRetCode == sizeof(KEY_DATA) * nRoleCount);

	fclose(pFile);
	pFile = NULL;

    //if (check_item_guid)
    //{
    //    nMessaegSize = 0;

    //    nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "guid\tguidhex\tgentime\tdupe\n");
    //    for (std::map<UINT64, INT32>::const_iterator it = g_ItemGuidMap.begin(); it != g_ItemGuidMap.end(); ++it)
    //    {
    //        if (it->second > 1)
    //        {
    //            UINT64 guid = it->first;
    //            time_t gentime = guid >> 32;
    //            struct tm* t = localtime(&gentime);
    //            nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "%I64u\t%I64x\t%d-%02d-%02d %02d:%02d:%02d\t%d\n",
    //                guid, guid, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, it->second);
    //        }
    //    }

    //    pFile = fopen("itemguid.txt", "wb");
    //    LOG_PROCESS_ERROR(pFile);

    //    nRetCode = fwrite(s_szMessage, 1, nMessaegSize, pFile);
    //    LOG_PROCESS_ERROR(nRetCode == nMessaegSize);

    //    fclose(pFile);
    //    pFile = NULL;
    //}

Exit0:
	if (pFile)
		fclose(pFile);

	return TRUE;
}

BOOL CB_GuildStorage(std::list<void*>& rResult, void* pUserData)
{
#pragma pack(push, 1)
    struct RESULT_DATA
    {
        UINT32	dwGuildID;
        char	szData[43008];
    };
#pragma pack(pop)

    //INT32       nRetCode = 0;
    //DB_BUFFER   *pBuffer = NULL;
    //INT32       nBufferlength = 0;
    //GUILD_STORAGE_ITEM_DATA    *pItemData = NULL;
    //INT32       nReadBufferSize = 0;
    //ItemInfo      iteminfo;

    //for (std::list<void*>::iterator it = rResult.begin();
    //    it != rResult.end(); ++it)
    //{
    //    RESULT_DATA * pResult = (RESULT_DATA*)*it;
    //    pBuffer = (DB_BUFFER *)pResult->szData;
    //    nReadBufferSize = 0;
    //    nBufferlength = pBuffer->nLength;

    //    while (nReadBufferSize < nBufferlength)
    //    {
    //        pItemData = (GUILD_STORAGE_ITEM_DATA*)(pBuffer->szBuffer + nReadBufferSize);

    //        LOG_CHECK_ERROR(pItemData->byConSlot < GUILD_STORAGE_MAX_TAG_NUM);
    //        LOG_CHECK_ERROR(pItemData->byItemSlot < GUILD_STORAGE_MAX_ITEM_NUM_PER_TAG);

    //        iteminfo.Load(pItemData->szItemBuffer);
    //        ++g_ItemGuidMap[iteminfo.m_llGuid];

    //        nReadBufferSize += sizeof(GUILD_STORAGE_ITEM_DATA);
    //    }
    //    LOG_CHECK_ERROR(nReadBufferSize == nBufferlength);
    //}

Exit0:
    return TRUE;
}


void _Export(CSqlMgr& sqlmgr)
{
	INT32 nRetCode = 0;

    nRetCode = sqlmgr.SyncExecSqlStmt(mysqlSelectAllRole, _ExportCallBackFunc, NULL, "");
	LOG_PROCESS_ERROR(nRetCode);

//    nRetCode = sqlmgr.SyncExecSqlStmt(mysqlSelectGuildStorage, CB_GuildStorage, NULL, "");
//    LOG_PROCESS_ERROR(nRetCode);

Exit0:

	return;
}

void _InsertRoles(CSqlMgr& sqlmgr, CLuaScript* poScript)
{
    INT32 nRetCode = 0;
    CGameWorld::GetInstance().SetGameTime((UINT32)time(NULL));
	for (UINT32 i = g_dwStartID; i < g_dwStartID + g_dwCount; i++)
    {
        CRole role;
        role.Init(i, 0);

        BOOL bGMRet = FALSE;

		role.SetClass(g_Random(clsPlayerBegin, clsPlayerEnd - 1));
		role.SetSex(g_Random(cstMale, cstFemale));

        cqyh::lua::push_object(poScript->GetLuaState(), &role, "CRole");
        lua_setglobal(poScript->GetLuaState(), "TargetRole");

        nRetCode = poScript->CallFunction("OnNewGMCommand", "s:b", "InitRobot(false)", &bGMRet);
        LOG_PROCESS_ERROR(nRetCode);
        LOG_PROCESS_ERROR(bGMRet);

        for (INT32 achievemnet_id = 1; achievemnet_id < 480; achievemnet_id++)
        {
            if (g_Random(2) == 0)
            {
                const ACHIEVEMENT_DATA* pData = CDataManager<ACHIEVEMENT_DATA>::GetInstance().GetData(achievemnet_id);
                if (pData)
                {
					role.GetAchievementList().Complete(achievemnet_id); //pData, g_Random(2000000000) / 86400);
                }
            }
        }

        for (INT32 var = 0; var < MAX_ROLE_VARIABLE_COUNT; var++)
        {
            role.SetVariable(var, g_Random(2000000000));
        }

        char role_name[25];
        snprintf(role_name, 25, "role%u", i);
        char user_name[64];
        snprintf(user_name, 25, "user%u", i);

        char role_data[16384];
        UINT32 role_data_len = 0;
        role.Save(role_data, role_data_len);

        ROLE_DB_DATA* pRoleData = (ROLE_DB_DATA*)role_data;
        char* role_base_data = (pRoleData->RoleData + pRoleData->BlockTable[rbtBase].dwStartOffset);
        UINT32 role_base_data_len = sizeof(ROLE_DB_BASE_DATA);

        unsigned char zipped_role_data[16384];
        unsigned long zipped_role_data_len = 16384;
        INT32 nRet = compress(zipped_role_data, &zipped_role_data_len, (unsigned char*)role_data, role_data_len);
        LOG_CHECK_ERROR(nRet == Z_OK);

        BOOL bRet = sqlmgr.AsyncExecSqlStmt(mysqlInsertRole, NULL, NULL, "udssbb", i, role_name, user_name,
            role_base_data, role_base_data_len, zipped_role_data, zipped_role_data_len); // must cooperate with mainloop to recycle 
        LOG_CHECK_ERROR(bRet);

        if (i % 1000 == 0)
        {
            INF("%u data inserted", i);
            CGameWorld::GetInstance().SetGameTime((UINT32)time(NULL));
        }

        role.UnInit();

		sqlmgr.MainLoop();
    }
Exit0:
    return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	INT32 nRetCode = 0;
	CMessageNotifier MessageNotifier;
	char szDBName[256] = {0};

    FILE* pFile = NULL;
    static char s_szMessage[1024 * 1024 * 16];
    INT32 nMessaegSize = 0;

    CSqlMgr sqlmgr;

	//LOG_PROCESS_ERROR( argc > 2 );
	//g_dwStartID = atoi(argv[1]);
	//g_dwCount = atoi(argv[2]);

	if (argc > 1)
		strxcpy(szDBName, argv[1], 256);

	/************************************************************************/
	// process options
	nRetCode = LoadGlobalConfig(g_szGlobalConfigFileName);
	PROCESS_ERROR(nRetCode);

	timeBeginPeriod(1);
	/************************************************************************/
	// initialize
	nRetCode = CLog::GetInstance().Init("exportdb",
		g_ServerConfig.MS.Log.nLogLevelMask,
		g_ServerConfig.MS.Log.nLogOutputMask,
		g_ServerConfig.MS.Log.bEnableLogThread,
		g_ServerConfig.MS.Log.bPrintThreadID,
		g_ServerConfig.MS.Log.bFlushFile); 
	LOG_PROCESS_ERROR(nRetCode);

	WSADATA  wsd;
	nRetCode = WSAStartup(MAKEWORD(2, 2), &wsd);
	LOG_PROCESS_ERROR(nRetCode == 0);

	nRetCode = g_PacketAllocator.Init(64, 64);
	LOG_PROCESS_ERROR(nRetCode);

	if (g_ServerConfig.DB.bUseIndependentDB && szDBName[0] == 0)
	{
		char* psz = szDBName;
		gethostname(szDBName, 256);
		while (*psz)
		{
			if (*psz == '-')
				*psz = '_';
			psz++;
		}
	}

	if (szDBName[0] == 0)
		strxcpy(szDBName, g_ServerConfig.DB.szDBName, 256);

	nRetCode = sqlmgr.Init(
		g_ServerConfig.DB.szDBIPAddress,
		g_ServerConfig.DB.szDBAccount,
		g_ServerConfig.DB.szDBPassword,
		szDBName,
		g_ServerConfig.DB.szDBCharset,
		g_ServerConfig.DB.dwDBPort,
		g_SqlStmtList, mysqlTotal, 8);
	LOG_PROCESS_ERROR(nRetCode);

	_InitMathTable();

	nRetCode = g_InitGameWorldLib(GetTickCountEx(), &MessageNotifier, &g_PacketAllocator);
	LOG_PROCESS_ERROR(nRetCode);


    g_ItemGuidMap.clear();

    CLuaScript* poScript = CScriptMgr::GetInstance().FindScript(GM_SCRIPT_NAME);
    LOG_PROCESS_ERROR(poScript);
	
//	_InsertRoles(sqlmgr, poScript);

	//_Export(sqlmgr);

    _LoadGuild(sqlmgr);

    _LoadMember(sqlmgr);

/*    if (check_item_guid)
    {
        nMessaegSize = 0;

        nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "guid\tguidhex\tgentime\tdupe\n");
        for (std::map<UINT64, INT32>::const_iterator it = g_ItemGuidMap.begin(); it != g_ItemGuidMap.end(); ++it)
        {
            if (it->second > 1)
            {
                UINT64 guid = it->first;
                time_t gentime = guid >> 32;
                struct tm* t = localtime(&gentime);
                nMessaegSize += snprintf(s_szMessage + nMessaegSize, 8192, "%I64u\t%I64x\t%d-%02d-%02d %02d:%02d:%02d\t%d\n",
                    guid, guid, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, it->second);
            }
        }

        pFile = fopen("itemguid.txt", "wb");
        LOG_PROCESS_ERROR(pFile);

        nRetCode = fwrite(s_szMessage, 1, nMessaegSize, pFile);
        LOG_PROCESS_ERROR(nRetCode == nMessaegSize);

        fclose(pFile);
        pFile = NULL;
    }
    */
Exit0:

	nRetCode = g_UnInitGameWorldLib();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = UnInitMathEx();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = sqlmgr.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	WSACleanup();

	nRetCode = g_PacketAllocator.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CLog::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = g_ClosePakFolder();
	LOG_CHECK_ERROR(nRetCode);

    if (pFile)
        fclose(pFile);

	return 0;
}

