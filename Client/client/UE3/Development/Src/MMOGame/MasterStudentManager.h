#ifndef _MASTERSTUDENTMANAGER_H_
#define _MASTERSTUDENTMANAGER_H_

#include "MMOSingleton.h"
#include "MMOUtil.h"
#include "m2c_message.h"
#include "MMOFacade.h"
#include "MMODataManager.h"

using namespace ExternalMessage;

#define MAX_ROW_MASTERLIST					14

/*
	1.师门信息:师傅数据 和同门数据
		{
			MasterDetailInfo masterInfo;
			StudentList		listStudent;
		}
	2.系统推荐的备选师傅列表\系统推荐的备选徒弟列表
		{
			SystemPosterList listSystemPoster;	
		}
	3.申请拜你为师的徒弟列表 \ 申请收你为徒的师傅列表
		{
			ApllicantsList  listApllicants;
		}
*/

#define Student_DesireGrad 2

//师徒奖励经验
struct Teacher_RewardExp
{
	UINT32          nRoleID;
	INT32			nExp;
	INT32			nMasterExp;
	INT32           nMoney;
	BOOL            bSelfReward;
	Teacher_RewardExp()
	{
		nRoleID = 0;
		nExp = 0;
		nMasterExp = 0;
		nMoney = 0;
		bSelfReward = FALSE;
	}
};

//师傅信息
struct MasterDetailInfo
{
	INT			 nRoleID;
	INT			 nLevel;
	INT			 nClass;
	INT			 nCZLevel;
	INT			 nStudentNum;
	FString      masterName;

	Teacher_RewardExp reward;
};
//同门数据
struct StudentListData
{
	UINT32               nRoleID;
	INT               nClass;
	UINT8               nLevel;
	UINT8               nCZLevel;
	UINT8               nState;//0是没有达到出师条件 1是达到出师条件  2是申请出师 
	FString           RoleName;
	BOOL              bLeaveMaster;//是否出师

	Teacher_RewardExp reward;

	StudentListData()
	{
		nRoleID = 0;
		nClass = 0;
		nLevel = 0;
		nCZLevel = 0;
		nState = 0;
		bLeaveMaster = FALSE;
	}
};
//申请者列表项数据 请求拜师和请求收徒通用
struct ApplicantsListData
{
	INT               nRoleID;
	INT               nClass;
	INT               nLevel;
	FString           RoleName;
	INT               nMasterExp;
};

// 系统推送 推荐拜师和推荐收徒通用
struct SystemPosterListData
{
	INT               nRoleID;
	INT               nClass;
	INT               nLevel;
	INT               nMasterExp;
	bool			  bCanApply;
	bool			  bSelect;
	bool			  bValid;
	FString           RoleName;
};

struct CongratulationGiftData 
{
	INT nTargetLevel;
	INT nType0Consume;
	INT nType1Consume;
	INT nType2Consume;

	INT nType0MailID1;
	INT nType0MailID2;
	INT nType0MailID3;

	INT nType1MailID1;
	INT nType1MailID2;
	INT nType1MailID3;

	INT nType2MailID1;
	INT nType2MailID2;
	INT nType2MailID3;

};

struct TwitterInfo
{
	UINT32 roleID;
	UINT8  level;
	INT32 masterExp;
	BOOL bApply;
};

enum MasterSortType
{
	EMST_MAS_NAME = 0,
	EMST_MAS_CLASS,
	EMST_MAS_LEVEL,
	EMST_MAS_EXP,
	EMST_MAS_STATE
};

enum StudentSortType
{
	EMST_STU_NAME = 0,
	EMST_STU_CLASS ,
	EMST_STU_LEVEL ,
};

enum EMasterStudentType
{
	EMST_MasterInfo,				//师门信息
	EMST_MasterSystemPosterList,	//系统推荐的师傅列表
	EMST_StudentSystemPosterList,	//系统推荐的徒弟列表
	EMST_MasterApplicantsList,		//申请收你为徒的师傅列表
	EMST_StudentApplicantsList,		//申请拜你为师的徒弟列表
	EMST_RecruitStatus,				//是否是收徒状态中
	EMST_MasterStateChange,			//状态变化
	EMST_CDTime,					//开除CD时间
	EMST_ChangeValue,				//名师值改变
	EMST_DesireGradAck,				//毕业申请发送成功
	EMST_DesireGradNtf,				//收到毕业申请
	EMST_StudentGrad,				//毕业成功
	EMST_OnClickMasterStudent,      // 点击消息球相关
	EMST_MasterTwitterType,         //师傅推送状态
	EMST_HelloTeacher,              //给师傅推送徒弟
	EMST_HelloStudent,              //给徒弟推送师傅
	EMST_MasterEnterGame,
	EMST_PlayerExpChange,
	
};


struct MMOGameEvent_MasterStudent : public MMOGameEvent
{
public:
	MMOGameEvent_MasterStudent(EMasterStudentType eventType, UINT32 id = 0)
		: EventType(eventType),
		ID(id)
	{
	}

	virtual EGameEvent GetEventType() const
	{
		return GameEvent_MasterStudent;
	}

	EMasterStudentType EventType;
	UINT32 ID;
	UINT8 level;
	INT32 masterExp;
};

struct GiftDetailData
{
	INT nGiftID;

	INT nItemID[3];
	INT nItemCount[3];
	INT nMoneyType[2];
	INT nMoneyNum[2];
	INT nAddExp;
	FString strGiftName;
	FString strGiftTips;
};
//活动配置表读取
struct GiftDetailDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("gift_detail.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}

	static GiftDetailData* CreateDataObject(INT templateID, bool& needAddToMap);

	static void DestroyDataObject(GiftDetailData* obj);

	static void ParseData(GiftDetailData* obj, class CTabFile* dataRow, int rowIdx);


	static FString GetTemplateIDName()
	{
		return TEXT("GiftID");
	}

	static FString FormatAsString(GiftDetailData* obj)
	{
		return "";
	}

	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(GiftDetailData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};


typedef TDataManger< GiftDetailData, GiftDetailDataProcessor >   GiftDetailDataManager;

struct MailTemplateData
{
	INT nMailID;
	INT nItemID;
};
//活动配置表读取
struct MailTemplateDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("mail_template.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}

	static MailTemplateData* CreateDataObject(INT templateID, bool& needAddToMap);

	static void DestroyDataObject(MailTemplateData* obj);

	static void ParseData(MailTemplateData* obj, class CTabFile* dataRow, int rowIdx);


	static FString GetTemplateIDName()
	{
		return TEXT("TemplateID");
	}

	static FString FormatAsString(MailTemplateData* obj)
	{
		return "";
	}

	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(MailTemplateData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};


typedef TDataManger< MailTemplateData, MailTemplateDataProcessor >   MailTemplateDataManager;

//礼包配置
//活动配置表读取
struct CongratulationGiftDataProcessor
{
	static const TCHAR* GetName()
	{
		return TEXT("master_gift.txt");
	}

	static INT ParseID(const FString& idStr)
	{
		return appAtoi(*idStr);
	}

	static CongratulationGiftData* CreateDataObject(INT templateID, bool& needAddToMap);

	static void DestroyDataObject(CongratulationGiftData* obj);

	static void ParseData(CongratulationGiftData* obj, class CTabFile* dataRow, int rowIdx);


	static FString GetTemplateIDName()
	{
		return TEXT("ID");
	}

	static FString FormatAsString(CongratulationGiftData* obj)
	{
		return "";
	}

	static void PostInitData();

#if WITH_EDITOR
	static void CollectReferencedResourceFromDataTable(CongratulationGiftData* obj, TSet<FString>& outResList)
	{
		//_CollectReferencedResource(obj, outResList);
	}
#endif
};
typedef TDataManger< CongratulationGiftData, CongratulationGiftDataProcessor >   CongratulationGiftDataManager;

typedef std::list<StudentListData,			M_UE3_STL_ALLOC(StudentListData) >				StudentList;
typedef std::list<ApplicantsListData,		M_UE3_STL_ALLOC(ApplicantsListData) >			ApllicantsList;
typedef std::list<SystemPosterListData,		M_UE3_STL_ALLOC(SystemPosterListData) >			SystemPosterList;
typedef std::map<INT32,CongratulationGiftData,	M_UE3_STL_ALLOC_MAP(INT32,CongratulationGiftData) >		GiftConfigDataMap;
typedef std::list<GiftDetailData,			M_UE3_STL_ALLOC(GiftDetailData) >				GiftDetailDataList;
typedef std::list<MailTemplateData,			M_UE3_STL_ALLOC(MailTemplateData) >				MailTemplateDataList;

class MasterStudentManager:public SingletonMeyers<MasterStudentManager>
{
public:
	MasterStudentManager();
	virtual ~MasterStudentManager();

	void Init();
	void Shutdown();
	void Clear();

	const StudentListData*		GetStudentDataByID(INT nRoleID);
	const ApplicantsListData*   GetApplicantsDataByID(INT nRoleID);
	const SystemPosterListData* GetSystemPosterDataByID(INT nRoleID);
	const MasterDetailInfo&		GetMasterDetailInfo()		const;
	UBOOL UpdateMasterInfoForCompletion( UBOOL isForceRequire = FALSE );
	const CongratulationGiftData* GetGiftConfigData(INT nLevel) const;
	const GiftDetailData*		  GetGiftDeatilData(INT nGiftID) const;
	const MailTemplateData*		  GetMailTemplateData(INT nMailID) const;
	INT GetCongratulationLevel(INT lastLeve, INT currentLevel);
	INT GetCongratulationCount(INT lastLeve, INT currentLevel);

	const StudentList&			GetStudentList()			const;
	const ApllicantsList&		GetStudentApllyList()		const;
	const ApllicantsList&		GetMasterApllyList()		const;
	const SystemPosterList&		GetMasterSystemList()	    const;
	const SystemPosterList&		GetStudentSystemList()	    const;

	BOOL						IsMasterRelation(INT nRoleID);

	void						AddGiftConfigData(const CongratulationGiftData& data);
	void						AddGiftDetailConfigData(const GiftDetailData& data);
	void						AddMailTemplateConfigData(const MailTemplateData& data);

	StudentListData* 			AddorUpdateStudent(const MASTER_STUDENT_INFO* pkInfo);
	StudentListData* 			AddorUpdateStudent(const M2C_MASTER_ADD_STUDENT_NTF* pkInfo);
	UBOOL						UpdateAllStudentInfoForCompletion( UBOOL isForceRequire = FALSE );

	void						AddorUpdateApplicants(const M2C_MASTER_STUD_SUBMIT_APP_NTF* pkInfo);
	void						AddorUpdateApplicants(const M2C_MASTER_TEACHER_SUBMIT_APP_NTF* pkInfo);
	UBOOL						UpdateAllApllicantsInfoForCompletion( UBOOL isForceRequire = FALSE );

	void						AddorUpdateSystemPoster(const M2C_MASTER_RECRUIT_LIST::RECRUIT_MASTER_INFO* pkInfo);	
	void						AddorUpdateSystemPoster(const M2C_MASTER_GET_SOLO_LIST_ACK::MASTER_SOLO_INFO* pkInfo);
	UBOOL						UpdateAllSystemPosterInfoForCompletion( UBOOL isForceRequire = FALSE );

	void						DeleteStudentByID(INT nRoleID);
	void						DeleteSystemPosterByID(INT nRoleID);
	void						DeleteApplicantsByID(INT nRoleID);
	void						SetApplyCurPage(INT nPage);
	void						SetSystemPosterPage(INT nPage);
	INT							GetApplyCurPage();
	INT							GetSystemPosterCurPage();
	INT							GetApplyMaxPage();
	INT							GetSystemPosterMaxPage();
	INT							GetSudentNum();
	INT							GetSelfState();
	void						SortStudentMembers(INT type);
	void						SortMasterMembers(INT type);
	void						MarkSystemPosterList();
	void						RemoveInvalidSystemPoster();
	void						ClearAll();
	void						ClearMasterInfo();
	void						ClearApplicants();
	void						ClearSystemPoster();
	INT							GetCDTime();
	void						SetMasterRecruitStatus(EMST_SUCCESS_RSP_TYPE bValue);
	EMST_SUCCESS_RSP_TYPE		GetMasterRecruitStatus();
	EMASTER_STATE				GetMasterStudentState();
	void						SetMasterStudentState(EMASTER_STATE val);
	void						SetOpenMasterStudentPanelDelegate(FScriptDelegate fun);
	void						SetOpenCongUpLevelPanelDelegate(FScriptDelegate fun);
	
	void						NotifyEnterGame();
	void						NotifyLevelChange(INT nLevel);

	void						OpenHelloStudentPanel();
	void						OpenHelloTeacherPanel();
	/*
		跟服务端的协议保持语义一致  
		Ack 后缀的都是返回自己的回馈消息
		Ntf 都是通知对方的
	*/
	void  NotifyUpdateMasterList(const M2C_MASTER_RECRUIT_LIST*msg);
	void  NotifyUpdateMasterSoloListAck(const M2C_MASTER_GET_SOLO_LIST_ACK* msg);
	void  NotifyUpdateRecruitAck(INT nState);

	void  NotifySubmitStudentApplyAck(INT nRoleID);
	void  NotifySubmitStudentApplyNtf(const M2C_MASTER_STUD_SUBMIT_APP_NTF* msg);
	void  NotifyAgreeStudentApplyAck(INT nRoleID);
	void  NotifyRefuseStudentApplyAck(INT nRoleID);
	void  NotifyRefuseStudentApplyNtf(INT nRoleID);
	void  NotifyCacelStudentApplyAck(INT nRoleID);
	void  NotifyCacelStudentApplyNtf(INT nRoleID);

	void  NotifySubmitMasterApplyAck(INT nRoleID);
	void  NotifySubmitMasterApplyNtf(const M2C_MASTER_TEACHER_SUBMIT_APP_NTF* msg);
	void  NotifyAgreeMasterApplyAck(INT nRoleID);
	void  NotifyRefuseMasterApplyAck(INT nRoleID);
	void  NotifyRefuseMasterApplyNtf(INT nRoleID);
	void  NotifyCacelMasterApplyAck(INT nRoleID);
	void  NotifyCacelMasterApplyNtf(INT nRoleID);

	void  NotifyLeaveMasterAck();
	void  NotifyLeaveMasterNtf(INT nRoleID);
	void  NotifyFireStudentAck(INT nRoleID);
	void  NotifyFireStudentNtf(INT nRoleID);
	void  NotifyAddStudentNtf(const M2C_MASTER_ADD_STUDENT_NTF* msg);
	void  NotifyDelStudentNtf(INT nRoleID);
	void  NotifyClearInfo();
	void  NotifyMasterInfo(const M2C_MASTER_INFO* msg);
	void  NotifyCongratulationCount(INT nRoleID,INT nCount);
	void  NotifyCongratulationTarget(INT nRoleID);
	void  NotifyMasterValueChange(INT Money , INT OldMoney);
	void  NotifyCDTimeChange(INT nCDTime);
	void  NotifyLevelUp(INT nRoleID,INT nLevel);
	void  NotifyDesireGradAck();
	void  NotifyDesireGradNtf(INT nRoleID);
	void  NotifyStudentGrad(INT nRoleID);
	void  NotifyHelloTeacher(UINT32 nRoleId,UINT8 level);
	void  NotifyHelloStudent(UINT32 nRoleId,UINT8 level);
	void  NotifyRewardAck(UINT8 success);

	void SetLeaveTeacher(BOOL v = TRUE){isLeaveTeacher = v;}

	INT GetMasterExpRatio(){return masterExp;}

	UINT8 GetMasterTwitter(){return masterTwitter;}
	void SetMasterTwitter(UINT8 t){masterTwitter = t;}

	void NotifyUpdateMasterTwitter(UINT8 twitter);
	void NotifyUpdateMasterReward(G2C_SYNC_MASTER_REWARD_EXP* msg);

	BOOL GetIsShowTwitterStudentInfo(){return bShowTwitterStudentInfo;}
	void SetIsShowTwitterStudentInfo(BOOL v){bShowTwitterStudentInfo = v;}

	BOOL GetIsShowTwitterMasterInfo(){return bShowTwitterMasterInfo;}
	void SetIsShowTwitterMasterInfo(BOOL v){bShowTwitterMasterInfo = v;}

	TwitterInfo GetMasterTwitterInfo(){return masterTwitterInfo;}
	TwitterInfo GetStudentTwitterInfo(){return studentTwitterInfo;}
	void ClearStudentTwitterInfo(UINT32 id);

	void SetMasterTwitterInfo(TwitterInfo info){masterTwitterInfo = info;}
	void SetStudentTwitterInfo(TwitterInfo info){studentTwitterInfo = info;}
	void AddOrUpdateMasterRewardExp(Teacher_RewardExp& reward,EMASTER_STATE state = E_MASTER_STUDENT );

	INT32 GetMasterExpByRatio(INT32 masterExp);
	
	void AddHelloStudentBtnBall();

	INT GetMasterStudentNum(INT32 masterExp );

	void ClearStudentList();

	void UpdateSTudentAppleState(UINT32 id);

private:
	ApplicantsListData*   _GetApplicantsDataByID(INT nRoleID);
	StudentListData*	  _GetStudentDataByID(INT nRoleID);
	SystemPosterListData* _GetSystemPosterDataByID(INT nRoleID);

private:
	MasterDetailInfo	masterInfo;
	StudentList			listStudent;
	SystemPosterList	listSystemPoster;	
	ApllicantsList		listApllicants;
	INT					curApplyPage;
	INT					curSystemPosterPage;
	INT					cdTime;
	/*
		-1是无效  0是没有达到出师条件  1是达到出师条件  2是已申请出师
	*/
	INT					selfState;			
	EMST_SUCCESS_RSP_TYPE _MasterRecruitStatus;				//师父申请招募，或者取消招募的返回值
	EMASTER_STATE		_MasterStudentStatus;			//当前角色的状态
	FScriptDelegate		_OpenMasterStudentPanelDelegate;
	FScriptDelegate		_OpenCongUpLevelPanelDelegate;

	GiftConfigDataMap	listGiftConfig;
	GiftDetailDataList  listGiftDetailConfig;
	MailTemplateDataList listMailTemplateConfig;

	BOOL isLeaveTeacher;

	INT masterExp;

	UINT8 masterTwitter;

	BOOL bShowTwitterMasterInfo;
	BOOL bShowTwitterStudentInfo;

	TwitterInfo masterTwitterInfo;
	TwitterInfo studentTwitterInfo;

	INT masterExp1;
	INT masterExp2;


};
#endif