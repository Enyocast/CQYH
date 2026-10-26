
enum EKeyFunction
{
    KF_BarSkill1 = 0,		// 快捷技能栏
    KF_BarSkill2,
    KF_BarSkill3,
    KF_BarSkill4,
    KF_BarSkill5,
    KF_BarSkill6,

	KF_BarSkill7,		// 快捷技能栏
	KF_BarSkill8,
	KF_BarSkill9,
	KF_BarSkill10,
	KF_BarSkill11,
	KF_BarSkill12,

	KF_Func_Begin = 12,
    KF_OpenRole = KF_Func_Begin,// 角色 C
    KF_OpenBag,             // 背包 B
	KF_OpenSkillUp,			// 技能修炼 Z
    KF_OpenHeaven,          // 境界/技能 V
    KF_OpenTask,            // 任务 L
	KF_OpenStoryQuest,		// 剧情任務 A
	
	//KF_OpenPlayerInfoView,    // 目标信息查看 E
//    KF_OpenIntensify,       // 体格强化 U
//    KF_OpenMount,           // 灵魂镶嵌 I
//    KF_OpenBaptize,         // 装备洗炼 R  
    KF_OpenGuild,           // 公会 G
	KF_OpenMaster,          // 师徒 X
    KF_OpenFriend,          // 好友 P
    KF_OpenTeam,            // 组队 T
    KF_OpenRide,            // 坐骑 N
//    KF_OpenHero,            // 英雄 H
	KF_OpenReputation,		// 声望
    KF_OpenAchieve,         // 成就 Y
	KF_OpenRank,			// 排行榜 O
	KF_OpenActivity,        // 活动日程 A
	KF_Mail,				//邮件
	KF_Mall,				//商城
	KF_GoldStore,			//金币交易行
	KF_QuickPick,           // 拾取 F
	KF_OpenMinimap,         // 地图 M
	KF_ToggleMinimapType,	// 小地图模式切换 Tab
	KF_Handbook,            // 百晓生
	KF_Assist,              // 游戏助手 F12
    
	KF_OpenOption,          // 设置 S
    //KF_OpenSkill,           // 技能装配 K
    //KF_OpenArena,           // 竞技场 J 
	KF_ChangePkMode,          // 切换pk模式

	KF_ChangeRole,			//更换角色
	KF_EnterGroup,			//快速组队
	KF_LeaveGroup,			//快速出队
	KF_AddAttention,		//加关注
	KF_AddEnemy,			//加仇人
	KF_AddBlackList,		//加黑名单
	KF_ShowHidePlayer,		//显示隐藏身边玩家
	KF_ChangePetAI,			//切换宠物AI
	KF_KeepRunning,			//KF_KeepRunning
	KF_AUCTION,				//拍卖行

	KF_Func_End,

	KF_Unknown = 0xff,		// 无效类型
};

enum EKeyFlag
{
	KNF_Version	= 1,		// 版本号

    KNF_None    = 0,		// 空标记
    KNF_Ctrl    = 1<<0,
    KNF_Alt     = 1<<1,
    KNF_Shift   = 1<<2,
	KNF_CtrlType_Mir2 = 1<<3,			//操控方式标志
	KNF_CtrlType_MirForever = 1<<4,		//操控方式标志

	KNF_Using	= 1<<7,		// 用来标识数据库的该记录是否有效，为0表示空的
};

#pragma pack(push,1)
struct KKeyworkd
{
	// 不要改变flag和code的顺序
	BYTE flag;      // EKeyFlag
	BYTE code;      // VK_[xxx]

	KKeyworkd()
		:flag(0)
		,code(0)
	{}
	KKeyworkd(BYTE f, BYTE c)
		:flag(f)
		,code(c)
	{}
	// 注意，需要将带组合键的快捷键排序在TMap的前面。
	inline UBOOL operator == (const KKeyworkd& n) const
	{
		return *(WORD*)this == *(WORD*)&n;
	}
};
#pragma pack(pop)


typedef TMap< KKeyworkd, EKeyFunction > MAP_KEYWORLD;
typedef TMap< EKeyFunction, FString > MAP_FUNCNAME;
typedef TMap< BYTE, FString > MAP_KEYNAME;

MAP_KEYWORLD vmKeyBind;						// 按键与功能的绑定关系
MAP_KEYWORLD vmKeyTemp;						// UI界面中的按键绑定关系（打开界面时从vmKeyBind中复制，保存时vmKeyTemp应用到vmKeyBind）
MAP_KEYNAME vmKeyNames;						// 键码与名字的对应关系，也是允许的键码表
MAP_FUNCNAME vmFuncNames;					// 功能名
EKeyFunction nKeyModifying;					// 正在修改中的功能
UBOOL		 nKeyModifyingKeyPressed;		// 用于输入修改的按键
INT			 nModfGCTType;					// 正在修改中的控制类型
BYTE		 nCurVersion;					// 当前客户端变量版本号

UMMOKeyManager();
static UMMOKeyManager* getSingleton();

void OnOpenUI();
void OnApplyByUI();
void MdfKeyBegin(EKeyFunction func);		// 启动修改某键
void MdfKeyEnd(BYTE key = 0);				// 正常结束，放弃修改取消
UBOOL DelKeyFunction(MAP_KEYWORLD& kmp, EKeyFunction func);// 从表中删除此功能的快捷键
UBOOL DoKeyPress(BYTE key, UBOOL down);		// 按下某键时
UBOOL DoFunction(EKeyFunction k, UBOOL down, UBOOL combo);	// 执行某个功能
UBOOL CanDoFunction(EKeyFunction k);
UBOOL GetFuncInfoByPanel(FString& panel, FString& tab_name, FString& key, FString& name);// 取得某个功能的快捷键信息
void SaveKeyword();							// 保存快捷键信息
UBOOL ExtractKey(BYTE* buf, UINT size);		// 提取数据
UBOOL RestoreKey(BYTE* buf, UINT size);		// 应用数据
KKeyworkd* FindKeyworld(EKeyFunction func, UBOOL mdf_config);	// 查询某个功能当前的快捷键
FString& KeyToString(KKeyworkd* key, FString& out, BYTE t = 0);	// 将快捷键转为字符串
FString& FuncToString(EKeyFunction func, FString& out);
void DefaultBarAllType(UBOOL mdf_config);
void DefaultBar(UBOOL mdf_config);			// 恢复默认快捷栏设置
void DefaultFunc(UBOOL mdf_config);			// 恢复默认功能键设置
void UMMOKeyManager::DoAltFunc( UBOOL isPressed );		//左右Alt键处理
UBOOL InputKey(INT ControllerId,FName Key,EInputEvent Event,FLOAT AmountDepressed,UBOOL bGamepad);	// Interaction 的输入事件通知
BYTE  GetClientVariablesVersion();