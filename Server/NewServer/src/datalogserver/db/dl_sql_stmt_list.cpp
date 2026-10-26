#include "stdafx.h"
#include "dl_sql_stmt_list.h"

SQL_STMT_DATA g_DLSqlStmtList[dsqlTotal] =
{
	{ -1, dsqlInsertLogin,							"INSERT INTO logdata_accountlogin (LogTime, AreaID, GroupID, SndaID, Action, IP) VALUES (FROM_UNIXTIME([d]), [h], [c], [s64], [s7], [s18])"},
	//{ -1, dsqlInsertChat,							"INSERT INTO logdata_chat(LogTime, AreaID, GroupID, SourceID, TargetID, ChatType, Message) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d], [s10], [b513])"},
 	//{ -1, dsqlInsertTeam,							"INSERT INTO logdata_team(LogTime, AreaID, GroupID, TeamID, RoleID, LeaderID, MemberCount, ActionType) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d], [d], [d], [s16])"},
 	{ -1, dsqlInsertItem,							"INSERT INTO logdata_item(LogTime, AreaID, GroupID, RoleID, ActionType, Guid, TemplateID, ItemCount, Reason, UserDefinedID) VALUES (FROM_UNIXTIME([d]), [h], [c], [ud], [s20], [ul], [d], [d], [s30], [ul])"},
  	{ -1, dsqlInsertQuest,							"INSERT INTO logdata_quest(LogTime, AreaID, GroupID, RoleID, QuestID, Action, Type, QuestName) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d], [s10], [s10], [s256])"},
	//{ -1, dsqlInsertLevelUp,						"INSERT INTO logdata_levelup(LogTime, AreaID, GroupID, RoleID, Level) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d])"},
	//{ -1, dsqlInsertScene,							"INSERT INTO logdata_scene(LogTime, AreaID, GroupID, SceneID, TemplateID, SceneLevel, SceneDifficulty, RoleID, ActionType) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d], [d], [d], [d], [s20])"},
	//{ -1, dsqlInsertConslot,						"INSERT INTO logdata_conslot(LogTime, AreaID, GroupID, RoleID, ConType, ConSize) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [s14], [d])"},
	{ -1, dsqlInsertMoney,							"INSERT INTO logdata_money(LogTime, AreaID, GroupID, SourceID, TargetID, Action, MoneyType, MoneyCount, Reason, Param) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d], [s4], [d], [d], [s32], [d])"},
	//{ -1, dsqlInserRolePosition,					"INSERT INTO logdata_role_position(LogTime, AreaID, GroupID, RoleID, SceneTempID, SceneID, X, Y, Z) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d], [d], [h], [h], [h])" },
	//{ -1, dsqlInsertMaster,							"INSERT INTO logdata_rolelogout_master(LogTime, AreaID, GroupID, RoleID, SndaID, Name, Student1, Student2, Student3, Student4, Student5) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [s32], [s21], [d], [d], [d], [d], [d])"},
	//{ -1, dsqlInsertDie,							"INSERT INTO logdata_die(LogTime, AreaID, GroupID, SceneTemplateID, SceneID, X, Y, Z, KillerID, KillerType, KillerName, KillerLevel, KillerClass, VicID, VicLevel, VicClass, VicName) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d], [d], [d], [d], [d], [s11], [s21], [c], [s8], [d], [c], [s8], [s21])"},
	{ -1, dsqlInsertRoleLogoutBasic,				"INSERT INTO logdata_rolelogout_basic(LogTime, AreaID, GroupID, RoleID, SndaID, SceneID, SceneTemplateID, Name, Class, Sex, Level, Experience, Money1, Money2, X, Y, Z) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [s32], [d], [d], [s24], [s16], [s16], [d], [d], [d], [d], [d], [d], [d])"},
	{ -1, dsqlInsertGm,								"INSERT INTO logdata_gm(LogTime, AreaID, GroupID, RoleID, RoleName, Command, Result) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [s24], [s128], [c])"},
	//{ -1, dsqlInsertServerMonitorRealMoney,			"INSERT INTO logdata_servermonitor_realmoney(LogTime, AreaID, GroupID, RealMoneyToMoney02, RealMoneyToItem) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d])"},
	//{ -1, dsqlInsertServerMonitorQuestComplete,		"INSERT INTO logdata_servermonitor_questcomplete(LogTime, AreaID, GroupID, CompleteCount) VALUES (FROM_UNIXTIME([d]), [h], [c], [d])"},
	//{ -1, dsqlInsertServerMonitorNpcDie,			"INSERT INTO logdata_servermonitor_npcdie(LogTime, AreaID, GroupID, NpcID, DieCount) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d])"},
	//{ -1, dsqlInsertServerMonitorMoney,				"INSERT INTO logdata_servermonitor_money(LogTime, AreaID, GroupID, ProduceMoney01, ProduceMoney02, DestroyMoney01, DestroyMoney02) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d], [d], [d])"},
	//{ -1, dsqlInsertServerMonitorMomentaryKillNpc,	"INSERT INTO logdata_servermonitor_momentarykillnpc(LogTime, AreaID, GroupID, Level5, Level6, Level7, Level8, Level9, Level10, Level11, Level12, Level13, Level14, Level15, Level16, Level17, Level18) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d])"},
	//  
	//{ -1, dsqlInsertServerMonitorConsecutiveKillNpc,"INSERT INTO logdata_servermonitor_consecutivekillnpc(LogTime, AreaID, GroupID, Level5_9, Level10_14, Level15_19, "\
	//												"Level20_24, Level25_29, Level30_34 ,Level35_39, Level40_44, Level45_49 ,Level50_54, Level55_59, Level60_64, "\
	//												"Level65_69, Level70_74, Level75_79, Level80_84, Level85_89, Level90_94, Level95_99) VALUES (FROM_UNIXTIME([d]), [h], [c], "\
	//												"[d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d])"},

    //{ -1, dsqlInsertServerMonitorItem,              "INSERT INTO logdata_servermonitor_item(LogTime, AreaID, GroupID, TemplateID, ProduceCount, DestroyCount) VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [l], [l])"},
                                                    //   { -1, dsqlInsertFriend,							"INSERT INTO logdata_rolelogout_friend(LogTime, AreaID, GroupID, RoleID, SndaID, Name, Friend1, Friend2, " \
	//												"Friend3, Friend4, Friend5, Friend6, Friend7, Friend8, Friend9, Friend10, Friend11, Friend12, Friend13," \
	//												"Friend14, Friend15, Friend16, Friend17, Friend18, Friend19, Friend20, Friend21, Friend22, Friend23," \
	//												"Friend24, Friend25, Friend26, Friend27, Friend28, Friend29, Friend30, Friend31, Friend32) VALUES " \
	//												"(FROM_UNIXTIME([d]), [h], [c], [d], [s32], [s21], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d], [d])" },
	//

	//{ -1, dsqlInsertRoleLogoutItembagDefault,		"INSERT INTO logdata_rolelogout_itembag_default(LogTime, AreaID, GroupID, RoleID, SndaID, Name, "\
 //													"Guid1,	 ID1,  Clr1,  Guid2,  ID2,  Clr2,  Guid3,	ID3,  Clr3,  Guid4,  ID4,  Clr4," \
	//												"Guid5,	 ID5,  Clr5,  Guid6,  ID6,  Clr6,  Guid7,	ID7,  Clr7,  Guid8,  ID8,  Clr8,  "\
	//												"Guid9,	 ID9,  Clr9,  Guid10, ID10, Clr10, Guid11,	ID11, Clr11, Guid12, ID12, Clr12, "\
	//												"Guid13, ID13, Clr13, Guid14, ID14, Clr14, Guid15,	ID15, Clr15, Guid16, ID16, Clr16, "\
	//												"Guid17, ID17, Clr17, Guid18, ID18, Clr18, Guid19,	ID19, Clr19, Guid20, ID20, Clr20, "\
	//												"Guid21, ID21, Clr21, Guid22, ID22, Clr22, Guid23,	ID23, Clr23, Guid24, ID24, Clr24, "\
	//												"Guid25, ID25, Clr25, Guid26, ID26, Clr26, Guid27,	ID27, Clr27, Guid28, ID28, Clr28, "\
	//												"Guid29, ID29, Clr29, Guid30, ID30, Clr30, Guid31,	ID31, Clr31, Guid32, ID32, Clr32, "\
	//												"Guid33, ID33, Clr33, Guid34, ID34, Clr34, Guid35,	ID35, Clr35, Guid36, ID36, Clr36, "\
	//												"Guid37, ID37, Clr37, Guid38, ID38, Clr38, Guid39,	ID39, Clr39, Guid40, ID40, Clr40, "\
	//												"Guid41, ID41, Clr41, Guid42, ID42, Clr42, Guid43,	ID43, Clr43, Guid44, ID44, Clr44, "\
	//												"Guid45, ID45, Clr45, Guid46, ID46, Clr46, Guid47,	ID47, Clr47, Guid48, ID48, Clr48, "\
	//												"Guid49, ID49, Clr49, Guid50, ID50, Clr50, Guid51,	ID51, Clr51, Guid52, ID52, Clr52, "\
	//												"Guid53, ID53, Clr53, Guid54, ID54, Clr54, Guid55,	ID55, Clr55, Guid56, ID56, Clr56, "\
	//												"Guid57, ID57, Clr57, Guid58, ID58, Clr58, Guid59,	ID59, Clr59, Guid60, ID60, Clr60, "\
	//												"Guid61, ID61, Clr61, Guid62, ID62, Clr62, Guid63,	ID63, Clr63, Guid64, ID64, Clr64) "\
	//												"VALUES (FROM_UNIXTIME([d]), [h], [c], [d], [s32], [s21], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
 //													"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
 //													"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
 //													"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
 //													"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c])"},

	//	{ -1, dsqlInsertRoleLogoutItembagEquipped,	"INSERT INTO logdata_rolelogout_itembag_equipped(LogTime, AreaID, "\
	//												"GroupID, RoleID, SndaID, Name, Guid1,  ID1,  Clr1,  Guid2,  ID2, "\
	//												"Clr2, Guid3,  ID3,  Clr3,  Guid4,  ID4,  Clr4, Guid5,  ID5,  Clr5, "\
	//												"Guid6,  ID6,  Clr6, Guid7,  ID7,  Clr7,  Guid8,  ID8,  Clr8, Guid9, "\
	//												"ID9,  Clr9,  Guid10, ID10, Clr10, Guid11, ID11, Clr11, Guid12, ID12, "\
	//												"Clr12, Guid13, ID13, Clr13, Guid14, ID14, Clr14, Guid15, ID15, Clr15) "\
	//												"VALUES(FROM_UNIXTIME([d]), [h], [c], [d], [s32], [s21], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], [l], [d], [c], "\
	//												"[l], [d], [c], [l], [d], [c], [l], [d], [c])"},
};
