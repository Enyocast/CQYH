#ifndef _ERROR_DEF_H_
#define _ERROR_DEF_H_

// tolua_begin

/// @enum ERROR_CODE_DEF
enum ERROR_CODE_DEF
{
    errUnknownError = 0,
	errSuccess = 1,   
    errCritical,
    errDatabase,

    errLoginBegin = 0x100,

    errLoginAuthFailed,             ///< 登录验证失败
    errLoginUnknownError,           ///< 未知登录错误
    errLoginServerNotReady,         ///< 服务器未就绪
    errLoginRepeat,                 ///< 账号重复登录
	errLoginRepeatKicked,           ///< 账号重复登录被踢下线
	errLoginErrorUserNameOrPassword,///< 错误的用户名或密码
	errLoginTooManyOnlineRole,		///< 在线玩家超过上限
	errLoginLocked,					///< 玩家被锁定，请稍后再试
	errLoginPrecreate,				///< 预创建阶段，不允许进游戏
	errLoginErrorVersion,			///< 游戏版本错误

	errLoginCreateRoleTooMany,      ///< 创建角色数量超过上限
    errLoginCreateRoleDupeName,     ///< 角色名重复(异常)
    errLoginCreateRoleCensoredWord, ///< 角色名含敏感词
    errLoginCreateRoleNameLength,   ///< 角色名超长
    errLoginCreateRoleNameServerNotConnected,   ///< 无法连接名字服务
    errLoginCreateRoleNsDupeName,   ///< 角色名重复
    errLoginCreateRoleNsDbSysErr,   ///< 名字数据库错误

    errLoginDeleteRoleNotFound,     ///< 删除角色未找到
    errLoginDeleteRoleDeleted,      ///< 删除角色失败，已被删除
    errLoginDeleteRoleMaster,       ///< 师傅不能删号
    errLoginDeleteRoleGuild,        ///< 有工会不能删号
    errLoginDeleteRoleAuction,      ///< 拍卖或者竞标中不能删号
    errLoginDeleteRoleExchange,     ///< 交易行下单中不能删号
    errLoginUnDeleteRoleNotFound,   ///< 恢复角色未找到
    errLoginRoleBusy,               ///< 读取角色数据失败
    errLoginRoleFrozen,             ///< 角色被冻结
    errLoginTimeUnknown,            ///< 游戏时间余额未知
    errLogoutNotPermit,				///< 不允许退出
	errLoginTooManyUser,			///< 注册用户数达上限

    errLoginWrongServer,            ///< 未激活此服务器，不许登录
    errLoginCreateRoleForeverDelete,///< 不允许永久删除角色
    errLoginNeedDynamicPassword,    ///< 需要验证动态密码
    errLoginDynamicPasswordSuccess, ///< 动态密码验证成功
    errLoginDynamicPasswordFailed,  ///< 动态密码验证失败
    errLoginDynamicPasswordVerified,///< 动态密码已验证，不需要再次验证
    errLoginDynamicPasswordTooOften,///< 动态密码验证太频繁，请稍候再试

	errLoginEnd,

	errMoveBegin = 0x200,
    errMoveFail,                    ///< 移动失败，一般是状态不对
	errMineFail,					///< 挖矿失败
	errMoveEnd,

	errJumpBegin = 0x300,
    errJumpWrongState,              ///< 状态错误无法跳转场景
    errJumpCasting,                 ///< 施法中无法跳转场景
    errJumpInCombat,                ///< 战斗中无法跳转场景
    errJumpStallOpen,               ///< 摆摊中无法跳转场景
    errJumpTrading,                 ///< 交易中无法跳转场景
	errJumpWrongItem,				///< 使用跳转卷轴失败
	errJumpWrongPos,				///< 无法跳转到指定位置
	errJumpSceneFobidden,			///< 当前场景禁止跳转
	errJumpDead,					///< 死亡中无法跳转场景
	errJumpArrest,					///< 囚禁中无法跳转场景
	errJumpChangeLineBreak,			///< 切线中断
    errJumpEnd,

	errReviveBegin = 0x400,
	errReviveStillAlive,			///< 无法复活：还活着
	errReviveLackOfItem,			///< 缺少复活必要的道具
	errReviveInProgress,			///< 复活进行中
	errReviveNoGraveyard,			///< 复活失败：无复活点数据
	errReviveForbidden,				///
	errReviveNotReady,				///
	errReviveUnknown,				///
	errReviveEnd,

	errSpellBegin = 0x500,
	errSpellCasting,		        ///< 有技能正在释放
	errSpellDisabled,		        ///< 禁止释放技能
	errSpellWeaponTypeError,        ///< 武器类型错误
	errSpellNotExists,		        ///< 技能不存在
	errSpellNoTarget,		        ///< 目标不存在
	errSpellErrorType,		        ///< 技能类型错误
	errSpellConditionError,	        ///< 技能条件不满足
	errSpellCasterCCLimitBitsError,	///< 控制状态不能释放
	errSpellCastNoMove,				///< 移动中不能释放
	errSpellCastNoMount,			///< 坐骑中不能释放
	errSpellCastNoDead,				///< 死亡时不能释放
	errSpellCastNoLive,				///< 存活时不能释放
	errSpellCastNoStiff,			///< 受击硬直时不能释放
	errSpellCasterCheckNodeFailed,	///< 额外释放条件检测失败

	errSpellInValidTargetRoleState, ///< 无效目标
	errSpellInValidTargetNodeError, ///< 无效目标
	errSpellInValidTargetDead,		///< 无效目标
	errSpellInValidTargetStance,	///< 无效目标
	errSpellInValidTargetRelationship, ///< 无效目标
	errSpellInValidTargetObjType,   ///< 无效目标
	errSpellInValidTargetNeverBeHit, ///< 无效目标

	errSpellInvalidDirection,		///< 方向错误
	errSpellOutOfRange,		        ///< 目标超出射程
	errSpellObstacled,		        ///< 视线受阻
	errSpellOutOfMana,		        ///< 资源不足
	errSpellNotReady,		        ///< 技能未准备好
	errSpellInHardTime,		        ///< 收招硬直状态无法施放技能
	errSpellLackOfItem,		        ///< 缺少必须的物品
	errSpellEquipDisabled,	        ///< 没有达到装备该技能需求的条件
	errSpellCannotBeEquipped,	    ///< 技能不能被装备
	errSpellEquipBindSlot,	        ///< 技能必须被装备在绑定的栏位
	errSpellEquipPassiveSlotError,  ///< 被动技能必须装在被动技能栏
	errSpellSlotError,		        ///< 技能槽不存在
	errSpellSlotLocked,		        ///< 技能槽未解锁
	errSpellSlotNoDuplicate,		///< 技能槽不可重复
	errSpellLearningClassError,		///< 技能学习失败：职业错误
	errSpellLearningLevelError,		///< 技能学习失败：等级不满足
	errSpellLearnt,					///< 技能学习失败：已经学会了
	errRuneEquipError,		        ///< 装备符文错误
	errRuneEquipClassError,		    ///< 装备符文错误
	errRuneNotExists,		        ///< 符文不存在
	errRuneNotActivated,	        ///< 符文未激活
	errPracticeOutOfPts,			///< 技能升级：点数不够
	errPracticeInProgress,			///< 修炼进行中
	errPracticeLevelTooLow,			///< 修炼角色等级不够
	errPracticeAlreadyMax,			///< 技能已达最高等级
	errSpellEquipNotReady,	        ///< 技能冷却中，无法被装备
	errSpellSceneLimit,		        ///< 場景難度限制
	errSpellUnknown,		        ///< 技能模块的未知错误
	errSpellEnd,

	errAuraBegin = 0x600,
	errAuraCannotCancel,
	errAuraResisted,
	errAuraNotExist,
	errAuraConfigError,
	errAuraAppendFailed,
	errAuraEnd,

	errItemBegin = 0x700,
    errItemBagFull,                 ///< 包裹已满
    errItemInvalidPos,              ///< 非法的物品位置（例如包裹只有16格，那么使用第18格位置的物品会产生此错误，客户端应阻止此种情况发生）
    errItemTypeMismatch,            ///< 非法的物品类型（例如将装备类物品放入材料包会产生此错误，客户端应阻止此种情况发生）
    errItemEquipMismatch,           ///< 非法的装备类型（例如将鞋子装备在头上，客户端应阻止此种情况发生）
    errItemUnsatisfied,             ///< 不满足物品的等级/职业/性别等限制（客户端应阻止此种情况发生）
    errItemCannotDestroy,           ///< 不可摧毁（客户端应阻止此种情况发生）
    errItemDropTooMany,             ///< 当前格子物品太多不可摧毁
    errItemCannotUnEquip,           ///< 装备不可卸下（客户端应阻止此种情况发生）
    errItemCannotSell,              ///< 不可卖给NPC（客户端应阻止此种情况发生）
    errItemNotFound,                ///< 物品不存在
    errItemNotEnough,               ///< 物品数量不足
    errItemBinded,                  ///< 物品已绑定（不可交易/邮寄，客户端应阻止此种情况发生）
    errItemCannotSplit,             ///< 物品不可拆分，或者请求拆分的数量大于原有的堆叠数量（客户端应阻止此种情况发生）
    errItemCannotUse,               ///< 物品不可使用（客户端应阻止此种情况发生）
    errItemFull,                    ///< 储值类物品已满
    errItemNotFull,                 ///< 储值类物品未满，不可使用
    errItemExpBottleMaxTimes,       ///< 经验瓶使用次数达到上限
    errItemWrongCombatState,        ///< 战斗中使用非战斗物品，或者反之
    errItemCannotUseInArena,        ///< 竞技场中不可使用此物品
    errItemNoNeedRepair,            ///< 物品无需修理
    errItemCannotRepair,            ///< 物品不可修理
    errItemMaxRefineLevel,          ///< 已达到最大强化等级（客户端应阻止此种情况发生）
    errItemRefineError,             ///< 强化材料不足（客户端应阻止此种情况发生）
    errItemStall,                   ///< 摆摊中，不能进行相关物品操作（客户端应阻止此种情况发生）
    errItemTrading,                 ///< 交易中，不能进行相关物品操作（客户端应阻止此种情况发生）
    errItemNotEnoughExp,            ///< 经验不足
    errItemNotEnoughMoneytype01,    ///< 绑金不足
    errItemNotEnoughMoneytype02,    ///< 金币不足
    errItemNotEnoughMoney,          ///< 货币不足
    errItemNotEnoughReputation,     ///< 声望不足
    errItemNotEnoughBuildingLevel,  ///< 建筑等级不足
    errItemNotReady,                ///< 物品未准备好
    errItemScriptUseFail,           ///< 脚本使用失败
    errItemCannotFindScript,        ///< 未发现指定脚本
    errItemCannotUpgradeSoul,       ///< 该物品不能灵魂升级
    errItemUpgradeSoulLimit,        ///< 该灵魂已升到最高级
    errItemCannotAddSoul,           ///< 该物品不能融灵
    errItemAlreadySocketed,         ///< 该插槽已插入灵魂
    errItemSocketNotMatch,          ///< 灵魂插槽颜色不匹配
    errItemNotSocketed,             ///< 没有灵魂，不能拆除
    errItemRuneError,               ///< 该物品不能使用铭文相关功能
    errItemRuneNotEnoughMaterial,   ///< 铭文石不足
    errItemComposeError,            ///< 合成装备材料不足
    errItemRoleDead,                ///< 角色处于死亡状态中
    errItemRoleCombat,              ///< 角色处于战斗状态中
    errItemEquipped,                ///< 此操作不能对已装备的物品进行（客户端应阻止此种情况发生）
    errItemDailyMoneyExceeded,      ///< 货币溢出（日上限）
    errItemWeekMoneyExceeded,       ///< 货币溢出（周上限）
    errItemTotalMoneyExceeded,      ///< 货币溢出（最大携带上限）
    errItemMaxLuck,                 ///< 武器幸运值达到最大的情况下使用祝福油（客户端最好阻止此种情况发生）
    errItemNotIdentified,           ///< 物品未鉴定
    errItemAlreadyIdentified,       ///< 物品已鉴定
    errItemCannotSign,              ///< 物品不能签名（客户端应阻止此种情况发生）
    errItemNotSigned,               ///< 物品未签名（客户端应阻止此种情况发生）
    errItemAlreadySigned,           ///< 物品已签名（客户端应阻止此种情况发生）
    errItemOthersSigned,            ///< 他人签名物品，不可装备（客户端应阻止此种情况发生）
    errItemSelfSigned,              ///< 自己签名物品，不可拍卖（客户端应阻止此种情况发生）
    errItemCannotAuction,           ///< 不可拍卖（客户端应阻止此种情况发生）
    errItemNotEnoughPkValue,        ///< 赎罪符专用错误代码：没有足够的pk值
    errItemCannotLevelup,           ///< 不可升级
    errItemLevelUpInProcess,        ///< 炼刀中
    errItemLevelUpNotFinished,      ///< 炼刀未结束
    errItemDurLow,                  ///< 耐久度过低
    errItemWeaponNotTried,          ///< 武器未试刀
    errItemNotEnoughBlackIron,      ///< 没有黑铁
    errItemLevelupError,            ///< 错误的装备升级材料
    errItemNoLevelUp,               ///< 没有正在炼刀的武器
    errItemWeaponTooHeavy,          ///< 超过武器重量限制
    errItemArmorTooHeavy,           ///< 超过防具重量限制
    errItemBagTooHeavy,             ///< 超过背包重量限制
    errItemOpenPackageEarly,        ///< 未到规定时间打开礼包
    errItemOpenPackageTooMany,      ///< 打开礼包次数过多
    errItemRoleNotFound,			///< 未知角色名
    errItemNotSabacGuild,			///< 不是沙巴克公会成员
    errItemBlackMarketItemNotFound, ///< 黑市物品未找到
    errItemBlackMarketNotFound,     ///< 黑市商店未找到
    errItemBlackMarketSold,         ///< 黑市物品已售完
    errItemBlackMarketCooldown,     ///< 黑市物品冷却中
    errItemMaterialWeaopn,          ///< 未装备洗矿武器或耐久不足
    errItemNoExerciseTime,          ///< 无可领取的锻造经验
    errItemExerciseTimeNotEmpty,    ///< 剩余锻造经验不为0
    errItemCannotDecompose,         ///< 无法分解（客户端应阻止此种情况发生）
    errItemUnknown,                 ///< 道具模块的未知错误
    errItemWeaponLevelUpTakeoutImmediatelyTooLate,///< 武器升级立即取回但是已经超时可以普通取回
	errItemTooLowLevel,				///< 等级太低无法使用
	errItemNoConsumeUse,			///< 使用后不消耗
    errItemNotDoubleRune,           ///< 不是双铭文，不可进行高级铭文洗练
    errItemNewbieRune,              ///< 新手铭文，不可进行高级铭文洗练
	errItemEnd,

	errMountBegin = 0x800,
	errMountOutOfItem,				///< 激活坐骑材料不足
	errMountAlreadyExists,			///< 坐骑已经存在
	errMountLevelLimited,			///< 激活坐骑等级不够
	errMountNotExist,				///< 未激活坐骑
	errMountAuraError,				///< 坐骑buff出错
	errMountEnd,

	errDropBegin = 0x900,
    errDropNotFound,                ///< 掉落不存在
    errDropFaraway,                 ///< 太远了，够不着
    errDropProtected,               ///< 他人掉落，无权拾取
	errDropOtherStand,				///< 其他人站在道具上无法拾取
    errDropFast,                    ///< 离上一次成功拾取未超过指定时间
    errDropBindied,                 ///< 他人绑定物品，无法拾取
    errDropIsBidding,               ///< 上一件物品拍卖未结束
    errDropFcm,                     ///< 防沉迷状态
	errDropEnd,

	errShopBegin = 0xA00,
    errNotEnoughMoney,              ///< 没有足够的货币
    errShopNotFound,                ///< 商店未找到
    errShopItemNotFound,            ///< 商品未找到
    errShopTooMany,                 ///< 一次购买数量超过一组（客户端应阻止此种情况发生）
    errShopTypeSell,                ///< 该商店不收购该物品（客户端应阻止此种情况发生）
    errVipShopNotFound,             ///< 无vip商店
	errShopEnd,

	errStallBegin = 0xB00,
    errStallWrongState,             ///< 错误的摊位状态
    errStallForbid,                 ///< 此地点不允许摆摊
    errStallOthersOpen,             ///< 此地点已有他人摆摊
    errStallWrongMoveState,         ///< 错误的移动状态，必须站定才能摆摊
    errStallTrading,                ///< 交易状态下不许摆摊
    errStallInvalidSlot,            ///< 错误的slot
    errStallSlotExist,              ///< 此slot已有物品
    errStallSlotNotExist,           ///< 此Slot没有物品
    errStallAlreadyInStall,         ///< 物品已经上架
    errStallItemCountError,         ///< 上架数量超过拥有数量
    errStallMoneyExceeded,          ///< 上架物品导致货币溢出
    errStallNotFound,               ///< 摊位未找到
    errStallFaraway,                ///< 摊位太远了
    errStallNotEnoughItems,         ///< 欲购买的数量超过摊主出售的数量
    errStallItemExpired,            ///< 欲购买的物品已发生变化
	errStallEnd,
	
	errQuestBegin = 0xC00,
    errQuestAlreadyAccepted,        ///<  任务已经被接受
    errQuestAlreadyCompleted,       ///<  任务已完成
    errQuestLogFull,                ///<  任务日志已满
    errQuestNotCompletePreQuest,    ///<  未完成前置任务
	errQuestTalkNpcTooFar,			///<  离对话Npc太远
	errQuestTalkNotCompleted,		///<  对话未完成
    errQuestNpcTooFar,              ///<  离任务Npc太远
    errQuestSex,                    ///<  接任务性别检查错误
    errQuestClass,                  ///<  接任务职业检查错误
    errQuestBuffNotFound,           ///<  未找到所需BUFF
    errQuestLowReputation,          ///<  声望太低
    errQuestHighReputation,         ///<  声望太高
    errQuestTime,                   ///<  接任务时间错误
    errQuestLevel,                  ///<  等级不满足
    errQuestNotEnoughItem,          ///<  任务物品不足
    errQuestLimitVar,               ///<  接任务变量检查错误
    errQuestNotEnoughMoney,         ///<  接任务金钱不足
    errQuestMaxCompleted,           ///<  任务最大完成次数达到
    errQuestNotEnoughKill,          ///<  任务杀怪数不足
    errQuestTooMuchMoney,           ///<  钱包已满
    errQuestCanNotAbandon,          ///<  任务不可放弃
	errQuestShareUnavailable,		///<  任务共享失败
	errQuestNoShareTeam,			///<  找不到共享队伍
	errQuestNoSharer,				///<  找不到共享发起者
	errQuestShareNotSameScene,		///<  共享者与被共享者不在同一张地图
	errQuestCannotShare,			///<  任务不能共享
	errQuestCannotFindScript,		///<  任务找不到脚本
    errQuestScriptUseFail,          ///<  脚本使用失败
	errQuestItemBagFull,			///<  包裹满导致任务物品添加失败
	errQuestTimeLimit,				///<  限时任务超时
	errQuestZone,					///<  区域无绑定任务
	errQuestGrid,					///<  格子无绑定任务
	errQuestExplore,				///<  探索未完成
	errQuestVarIndex,				///<  任务index配置错误
	errQuestSelectItemClass,		///<  可选奖励的适合职业不对
	errQuestCheckLevel,				///<  完成任务等级未达到
	errQuestDailyCompleteFull,		///<  每日任务完成达到上限
	errQuestDailyBrushCDTime,		///<  每日任务cd时间没有到
	errQuestDailyCompleteTimeOut,	///<  每日任务次数用完
	errQuestCircleDailyComplete,	///<  环任务今日已经完成
	errQuestRewardQuestComplete,	///<  悬赏任务今日完成次数达到上限
	errQuestRewardBoughtTimeUp,		///<  悬赏任务今日突破上限购买次数达到上限	
	errQuestRecycle,				///<  身上无此物品回收任务，物品回收失败
	errQuestNoMaster,				///<  任务无法接取，没有师傅
	errQuestTeamMaster,				///<  任务无法接取，队伍里有人并非师徒关系
	errQuestCoolDown,				///<  任务无法接取, 地图的cd时间没到
	errQuestKillPlayer,				///<  任务无法完成, 杀死玩家数量不够 
	errQuestInCombat,				///<  任务无法接取完成，在战斗中
	errQuestKillBufPlayer,			///<  任务无法完成, 未杀死指定buf玩家
	errQuestDoodad,					///<  任务无法完成, 未采集足够doodad
	errQuestCheckItem,				///<  任务无法完成, 物品不足
	errAcceptQuestScriptUseFail,	///<  任务无法接取 
	errCompleteQuestScriptUseFail,	///<  任务无法完成 
	errQuestUnknownError,			///<  任务未知错误
	errQuestEnd,

	errNpcBegin = 0xD00,
    errNpcNotFound,                 ///<  NPC未找到
    errNpcTooFar,                   ///<  玩家与NPC距离太远
    errNpcOpponentTarget,           ///<  无法与敌对方交互
    errNpcDataNil,                  ///<  位置npc错误
    errNpcDialogTimeout,            ///<  Npc对话超时
    errNpcNoSuchFunction,           ///<  Npc没有此功能
    errNpcInCombat,                 ///<  Npc在战斗中无法对话
	errNpcEnd,

	errDoodadBegin = 0xE00,
    errDoodadNotExist,              ///<  Doodad不存在
    errDoodadOutOfRange,            ///<  Doodad太远
    errDoodadCannotOperate,         ///<  不符合条件，无法操作Doodad
    errDoodadSpellCasting,          ///<  正在是放技能，无法操作doodad
	errDoodadEnd,

	errTeamBegin = 0xF00,
	errTeamInvitationSent,			///<  邀请已发送给目标玩家
	errTeamApplicationSent,			///<  申请已发送给目标玩家
	errTeamFailed,					///<  组队失败
    errTeamOffLine,					///<  队伍离线
	errTeamInBattleQueue,			///<  队伍在战场队列中
	errTeamInArenaQueue,			///<  队伍在竞技场队列中
    errTeamAlreadyInTeam,			///<  已经在队伍中
    errTeamFull,					///<  队伍满员
    errTeamRefuse,					///<  拒绝加入队伍 
    errTeamNotLeader,				///<  你丫不是队长
    errTeamNameError,				///<  队伍名称不合法
    errTeamNotPermit,				///<  队伍操作无权限
    errTeamNotInTeam,				///<  没有组队
    errTeamNotExist,				///<  队伍不存在
    errTeamRefusedInvitation,   	///<  拒绝了邀请
    errTeamInvitationRefused,       ///<  邀请被拒绝
    errTeamRefusedApplication,		///<  拒绝了申请
    errTeamApplicationRefused,      ///<  申请被拒绝
	errTeamAssignedTypeError,		///<  分配方式错误
    errTeamRequestNotAvailable,     ///<  申请已无效
	errTeamAuctionBidTooLow,		///<  出价过低
	errTeamAuctionNotEnoughMoney,	///<  钱不够了
	errTeamAuctionNotBegin,			///<  拍卖未开始
	errAdjacentDataTimeLimit,
	errTeamNoKickInAuction,			///<  拍卖期间禁止踢人
	errTeamSceneForbidden,			///<  当前场景禁止组队
    errTeamEnd,

	errArenaBegin = 0x1000,
    errArenaGetRewardSucc,          ///< 领取竞技场宝箱成功
    errArenaNotInRewardTime,        ///< 不在领奖时间
    errArenaNoReward,               ///< 您没有可以领取的奖励
    errArenaNotLucky,               ///< 对不起，您没有中奖
    errArenaCannotUseItem,          ///< 您没有使用物品的权限
    errArenaUseItemLimit,           ///< 您已超过使用次数限制
    errArenaMatchTimeout,           ///< 竞技场排队超时，未匹配到
    errArenaLucky,                  ///< 恭喜您中奖
    errArenaMatchFailed,            ///< 匹配失败
	errArenaEnd,

	errBattleBegin = 0x1100,
	errBattleQueueNow,				///< 已经在战场队列中
	errBattleNotQueue,				///< 没有在战场队列中
	errBattleConfirmTimeout,		///< 确认超时
	errBattleEnd,

	errSceneBegin = 0x1200,
    errSceneTooFarFromTeleport,     ///< 离传送点太远
	errSceneTooFarFromTeleportPlatform,///< 离传送平台太远
    errSceneNotTeamLeader,          ///< 不是队长，无法传送
    errSceneNotTeamMember,          ///< 队伍成员数量过多，无法传送
    errSceneErrorDungeonLevel,      ///< 错误的地下城副本等级
    errSceneErrorDungeonDifficulty, ///< 错误的地下城副本难度
    errSceneNoEnterRight,           ///< 没有进入副本的权限
    errSceneNoEnterMaxRole,         ///< 超过场景最大人数限制
    errSceneNotExist,               ///< 进入的副本不存在
    errSceneCreateSceneFailed,      ///< 创建副本失败
    errSceneDestroySceneFailed,     ///< 销毁副本失败
    errScenePreEnterFailed,         ///< 预进场景失败
    errSceneNoFatigue,              ///< 活力值不够进入场景
    errSceneEnterCountLimit,        ///< 每日进入次数达上限
    errSceneNoLevel,                ///< 不满足进入场景的等级限制
	errSceneTooLowLevel,			///< 等级过低不能进入场景
	errSceneTooHighLevel,			///< 等级过高不能进入场景
	errSceneEnd,

	errChatBegin = 0x1300,
	errChatCountOut,			///< 全服聊天次数用完
	errChatTooFrequent,			///< 聊天速度过快
	errChatServiceUnavaible,	///< 聊天服务异常
	errChatTargetNotFound,		///< 聊天目标未找到
	errGroupChatWithItem,		///< 千里传音道具未找到
    errChatForbidden,           ///< 您已被禁言
	errChatSceneForbidden,		///< 当前场景禁止此聊天功能
	errChatLevelTooLow,		    ///< 不满足聊天等级限制
	errChatMoneyNotEnough,	    ///< 聊天金币费用不足
	errChatSafeAreaForbidden,	///< 安全区禁止"附近"聊天
	errChatEnd,

	errFriendBegin = 0x1400,
    errFriendNotFound,          ///< 好友未找到
    errFriendAlreadyExists,     ///< 已经是好友了
    errFriendNotMutual,         ///< 不是双向好友
    errFriendNotOnline,         ///< 好友不在线
	errFriendFull,              ///< 好友列表已满
    errEnemyNotFind,            ///< 仇人未找到
	errFriendEnd,

	errTitleBegin = 0x1500,
    errTitleNotFind,            ///< 称号不存在
    errTitleCondNotSatisfy,     ///< 不满足装备称号的条件
	errTitleEnd,

	errTradeBegin = 0x1600,
	errTradeAskSent,			///< 交易请求发送给目标玩家
	errTradeWrongState,         ///< 错误的交易状态
    errTradeTargetNotFound,     ///< 交易对象未找到
    errTradeTargetFaraway,      ///< 交易对象距离太远
    errTradeTargetBusy,         ///< 交易对象正忙
    errTradeDifferentGroup,     ///< 交易对象非同一服务器组（例如在跨服战场中交易）
    errTradeBagFull,            ///< 包裹满
    errTradeUnknown,            ///< 交易模块的未知错误
	errTradeSceneFobidden,		///< 当前场景禁止交易
    errTradeChangeNotAllowed,   ///< 已提交物品和金钱不许撤销和修改
    errTradeNeedIntimacy,       ///< 友好度不够不能交易
    errTradeOverWeight,         ///< 包裹超重
	errTradeEnd,

    // master
	errMasterBegin = 0x1700,
    errMstFailed,
    errMasterNotMaster,         ///<  不是师傅
    errMasterStudFull,          ///<  徒弟满
    errMasterTeacherNotOnline,  ///<  师傅不在线
    errMasterStudentNotOnline,  ///<
    errMasterStudHighLevel,     ///<  徒弟等级过高
    errMasterStudhasMasterAlready, ///<  徒弟已有师傅
    errMasterStudAppFull,
    errMasterTargetStudAppFull,
    errMasterNoStudApp,         ///<  
    errMasterNoTeacherApp,
    errMstApplyFull,            ///<  可申请满
    errMstApplyerFull,          ///<  申请者已满
    errMasterAlreadyApply,      ///<  已经申请该师傅
    errMstRefuseApply,          ///<  拒绝申请
    errMasterStudNotOnline,     ///<  徒弟不在线
    errMasterApplayMstCD,       ///<  刚离开师傅，不能再拜师
    errMasterFireStudentCD,     ///<  开除徒弟cd
    errMasterTargetFireStudCD,  ///<  目标有开除徒弟cd
    errMasterNoMaster,          ///<  没有师傅
    errMasterAlreadyGrad,       ///<  已经毕业
    errMstCannotCZ,             ///<  不是师傅,不能恭喜
	errMstHaveNoStu,			///<  没有徒弟
    errMstMissApplication,      ///<  找不到申请记录
    errMasterRoleNotExist,      ///<  无角色
    errMasterAddExpFailed,
    errMasterHighLevel,         ///< 超出拜师等级
    errMasterOpFast,            ///< 操作过于频繁
    errMasterNotCZLevel,        ///< 不是可恭喜等级
    errMasterNeedGetRewardExp,  ///< 有未领取的师徒奖励经验
	errMasterEnd,

	errMailBegin = 0x1800,
    errMailUnknown,
    errMailReceiverNotFound,    ///< 收件人未找到
    errMailReceiverFull,        ///< 收件人邮箱已满
    errMailNotFound,            ///< 指定邮件未找到
    errMailCostNotEnough,       ///< 邮资不足
    errMailAttachNotFound,      ///< 邮件没有附件
    errMailSendTooFast,         ///< 发送邮件频率过快
    errMailAttachCDTime,        ///< 附件CD中不能领取
	errMailSceneForbidden,		///< 当前场景禁止收发邮件
	errMailEnd,

	errAchievementBegin = 0x1900,
	errAchievementLevel,									///<  成就无法完成，未达到指定等级
	errAchievementExperience,								///<  成就无法完成，未达到经验总数
	errAchievementPkValue,									///<  成就无法完成，未达到指定善恶值
	errAchievementForceReputation,							///<  成就无法完成，指定阵营声望未达指定值
	errAchievementVariousForceCount,						///<  成就无法完成，未达到开启不同阵营数
	errAchievementEquip,									///<  成就无法完成，未获得指定装备
	errAchievementEquipColor,								///<  成就无法完成，未获得指定品质装备
	errAchievementEquipBodyColor,							///<  成就无法完成，指定部位未获得指定品质装备
	errAchievementSet,										///<  成就无法完成，未获得指定外装
	errAchievementSetCount,									///<  成就无法完成，未达到外装总数
	errAchievementEquipSet,									///<  成就无法完成，未穿上指定外装
	errAchievementBankSlotCount,							///<  成就无法完成，仓库未达到指定格数
	errAchievementTotalSlotCount,							///<  成就无法完成，总格数达到指定格数
	errAchievementItemBagSlotCount,							///<  成就无法完成，物品背包格未达到指定格数
	errAchievementEquipBagSlotCount,						///<  成就无法完成，道具背包格未达到指定格数
	errAchievementMaterialBagSlotCount,						///<  成就无法完成，材料背包格未达到指定格数
	errAchievementTotalMoneyType,							///<  成就无法完成，未达到拥有的金币类型总数
	errAchievementKillPlayerTotalCount,						///<  成就无法完成，未达到杀死玩家总数
	errAchievementEnterScene,								///<  成就无法完成，未进入指定ID的地图
	errAchievementCompleteQuest,							///<  成就无法完成，未完成完成指定任务
	errAchievementCompleteQuestCount,						///<  成就无法完成，未达到完成任务总数
	errAchievementCompleteTypeQuest,						///<  成就无法完成，未完成指定类型任务数
	errAchievementSpellLevelSpecified,						///<  成就无法完成，指定技能未达到指定等级
	errAchievementSpellLevel,								///<  成就无法完成，未有技能未达到指定等级
	errAchievementLearnSpell,								///<  成就无法完成，未学会指定技能
	errAchievementSpellCount,								///<  成就无法完成，未达到拥有的技能总数
	errAchievementActiveSpellCount,							///<  成就无法完成，未达到拥有的主动技能总数
	errAchievementRuneCount,								///<  成就无法完成，未达到技能符文注入总数
	errAchievementEquipPassiveSpellCount,					///<  成就无法完成，未达到装备被动技能数量
	errAchievementEquipPassiveSpellIDCount,					///<  成就无法完成，未装备指定被动技能
	errAchievementAchievement,								///<  成就无法完成，未获得指定成就
	errAchievementAchievementCount,							///<  成就无法完成，未达到获得成就总数
	errAchievementGetItem,									///<  成就无法完成，未获得指定道具
	errAchievementItemLuck,									///<  成就无法完成，未有道具达到指定幸运值	
	errAchievementItemRefine,								///<  成就无法完成，未有道具达到强化等级
	errAchievementTitle,									///<  成就无法完成，未拥有指定称号
	errAchievementTitleCount,								///<  成就无法完成，未拥有称号总数
	errAchievementFriendCount,								///<  成就无法完成，未达到拥有指定数量好友
	errAchievementLeaveStudentCount,						///<  成就无法完成，未达到指定数量徒弟出师
	errAchievementLeaveMaster,								///<  成就无法完成，未作为徒弟出师成功
	errAchievementCreateTime,								///<  成就无法完成，未达到建号时间
	errAchievementDailyCompleteQuestCount,					///<  成就无法完成，未达到每日完成任务数
	errAchievementMainCompleteQuestCount,					///<  成就无法完成，未达到主线任务完成数
	errAchievementSubCompleteQuestCount,					///<  成就无法完成，未达到支线任务完成数
	errAchievementHiddenCompleteQuestCount,					///<  成就无法完成，未达到隐藏任务完成数
	errAchievementUseTypeItemCount,							///<  成就无法完成，未达到使用指定类型的道具数（技能书）
	errAchievementUseItem101Count,							///<  成就无法完成，未达到使用指定ID101的道具次数
	errAchievementKillWithNoGuilty,							///<  成就无法完成，未完成一次无PK值的pvp
	errAchievementVariableCheckError,						///<  成就无法完成，检测人物变量失败	
	errAchievementSpiritLevel,								///<  成就无法完成，境界等级未达到
	errAchievementPlayerNotFound,							///<  成就无法完成，比较成就时,找不到玩家
	errAchievementPlayerNotInSameScene,						///<  成就无法完成，比较成就时,比较的玩家不在同一地图
	errAchievementPlayerTooFar,								///<  比较成就时,比较的玩家距离过大
	errAchievementRewarded,									///<  已经领取过奖励，不能领取奖励
    errAchievementNotCompleted,								///<  成就未完成，不能领取奖励
	errAchievementAlreadyCompleted,							///<  成就已完成
	errAchievementMount,									///<  拥有坐骑未达到个数
	errAchievementHero,										///<  英雄非指定职业，未达到指定等级
	errAchievementRewardBagFull,							///<  包裹满，无法领取奖励
	errAchievementSpiritBuyAirBagSlotCount,					///<  未获得指定数量气田解锁格子数(包裹)
	errAchievementSpiritBuyAirStallSlotCount,				///<  未获得指定数量气海解锁格子数(仓库)
	errAchievementSpiritBuyAirEquipSlotCount,				///<  未获得指定数量气脉解锁格子数(装备)
	errAchievementSpiritBloodPageCount,						///<  未达到灵性（分页页签）开启数量
	errAchievementSpiritBloodPageCompleteCount,				///<  未达到灵性指定完成度
	errAchievementSpiritBloodPageLevel,						///<  未达到任意灵环达到指定等级
	errAchievementTotalRefineTime,							///<  未达到进行体格强化次数
	errAchievementTeamAuctionCount,							///<  未达到指定拍卖物品次数
	errAchievementVip,										///<  成就无法完成，非vip
	errAchievementColorItemComposeCount,					///<  成就无法完成，未合成指定品质的装备达到指定数量
	errAchievementItemComposeCount,							///<  成就无法完成，未合成指定数量的装备
	errAchievementColorItemDeComposeCount,					///<  成就无法完成，未分解指定品质的装备达到指定数量
	errAchievementItemDeComposeCount,						///<  成就无法完成，未分解指定数量的装备
	errAchievementRuneWeaponCount,							///<  成就无法完成，未获得指定铭文武器数量
	errAchievementExplore,									///<  成就无法完成，未进入指定地图

	errAchievementEnd,

    // guild
	errGuildBegin = 0x1A00,
    errGuildFailed,
    errGuildInternalError,
    errGuildMsgError,
    errGuildSqlError,
    errGuildClientParamError,
    errGuildNumLimit,                       ///<  最大公会创建数量限制
    errGuildQueryFailed,
    errGuildCreateFailed,                   ///<  创建公会失败
    errGuildSendTVMsgError,                 ///<  发送电视机公告失败
    errGuildSendMailFailed,                 ///<  邮件发送失败
    errGuildViewGuildFailed,                ///<  查询失败，未能拉取公会列表
    errGuildNoGuild,                        ///<  未加入帮派
    errGuildNotFind,                        ///<  帮派未找到
    errGuildLeaderNotExist,                 ///<  族长不存在
    errGuildNotMember,                      ///<  您不是帮派成员
    errGuildCannotFindMember,               ///<  找不到帮派成员
    errGuildAddMemberFailed,                ///<  添加帮派成员失败
    errGuildAddEventFailed,                 ///<  记入公会事件失败
    errGuildAddChestEventFailed,            ///<  添加资金纪录失败
    errGuildDeleteGuildAppFailed,           ///<  删除公会申请记录失败
    errGuildDestoryFailed,                  ///<  帮派删除失败
    errGuildNoticeSizeError,                ///<  帮派消息长度
    errGuildAnnounceSizeError,              ///<
    errGuildSetChatFlagError,               ///<  设置是否可聊天标记失败
    errGuildCannotSetSelfPosition,          ///<  不能设置自己的职位
    errGuildSetPositionFailed,              ///<  设置职位失败
    errGuildSubRoleMoneyFailed,             ///<  扣除角色金币失败
    errGuildSubMoneyFailed,                 ///<  扣除公会资金失败
    errGuildAddMoneyFailed,                 ///<  添加公会资金失败
    errGuildDonateLimit,                    ///<  捐赠上限
    errGuildAddWoodFailed,                  ///<  添加木材失败
    errGuildAddHerbFailed,                  ///<  添加草药失败
    errGuildAddCrystalFailed,               ///<  添加水晶失败
    errGuildAddSilverFailed,                ///<  添加秘银失败
    errGuildSubResFailed,                   ///<  扣除资源失败
    errGuildAddAllianceAppFailed,           ///<  添加公会结盟申请失败
    errGuildAddEnemyFailed,                 ///<  添加公会敌对公会失败
    errGuildCannotAddYourself,              ///<  不能添加自己公会
    errGuildAllianceAppNotExist,            ///<  公会联盟申请不存在
    errGuildAllianceAppTimeTypeError,       ///<  公会联盟申请的事件类型错误
    errGuildSameName,                       ///<  名字重复
    errGuildCensoredWord,                   ///<  帮会名含敏感词
    errGuildLowerLevel,                     ///<  等级过低
    errGuildNotEnoughMoney,                 ///<  金钱不足
    errGuildNotEnoughContribution,          ///<  帮贡不足
    errGuildNoItem,                         ///<  缺少道具
    errGuildApplyGuildFailed,               ///<  公会申请失败
    errGuildPositionError,                  ///<  公会职位错误
    errGuildAppFull,                        ///<  公会申请达到上限
    errGuildCannotDemiseMyself,             ///<  不能传位给本人
    errGuildAlreadyJoin,                    ///<  已经有帮派
    errGuildAlreadyApply,                   ///<  已经申请
    errGuildNoRight,                        ///<  无操作权限
    errGuildMemberCountFull,                ///<  人数已满
    errGuildTargetNotOnline,                ///<  目标不在线
    errGuildGuildHighLevel,                 ///<  帮派等级过高
    errGuildInviteSuccessfully,             ///<  招募消息发送成功，等待对方回应
    errGuildJoinGuildLevelLimit,            ///<  等级过低，不能加入公会
    
    errGuildSamePosition,                   ///<  同样的职位
    errGuildPositionLow,                    ///<  您的无权操作更高职位玩家
    errGuildPosHumanFull,                   ///<  该职位人数已满
    errGuildPosLeader,                      ///<  您是族长，不能退位
    errGuildNotLeader,                      ///<  不是族长
    errGuildDrawSalaryFailed,               ///<  领取薪水失败
    errGuildNoSalary,                       ///<  没有薪水
    errGuildDrawSalaryAlready,              ///<  已经领取过薪水
    errGuildDiplomatTimeError,              ///<  外交时间类型错误
    errGuildMoneyLack,                      ///<  缺少家族资金
    errGuildAllianceFull,                   ///<  盟友满了
    errGuildIsEnemy,                        ///<  是敌对家族
    errGuildIsAlliance,                     ///<  是联盟家族
    errGuildNotAlliance,                    ///< 
	errGuildAllianceAppAlreadyDel,          ///<  联盟申请记录已删除
    errGuildAllianceAppAlready,             ///<  已申请联盟
    errGuildAppNotExist,                    ///<  家族申请不存在
    errGuildRoleNotExist,                   ///<  角色不存在
    errGuildJoinCD,                         ///<  入帮cd
    errGuildTargetJoinCD,                   ///<  对方有入帮cd
    errGuildStorageTargetSlotError,         ///<  目标格子错误
    errGuildStorageSlotUsed,                ///<  格子已被使用
    errGuildStorageItemNotExist,            ///<  目标格子物品不存在
    errGuildStorageSlotUsing,               ///<  格子正在被使用
    errGuildDelHaveAlliance,                ///<  您有联盟，不能删除公会
    errGuildDelHaveEnemy,                   ///<  您有敌对帮派，不能删除公会
    errGuildLeaderCannotDelRole,            ///<  族长不能删号
    errGuildNoMoreHistory,                  ///<  没有更多的帮派事件
    errGuildNoMoreChest,                    ///<  没有更多的资金纪录
    errGuildConfigError,                    ///<  配置错误
    errGuildContributionLimit,              ///<  达到贡献获得上限

    errGuildStorageCD,                      ///<  帮派操作cd
    errGuildChangeAnnounceSucc,             ///<  更改宣言成功

    // guild welfare
    errGuildWarTime,                        ///<  公会战期间不能升级
    errGuildWelfareNeedUpgrade,             ///<  福利buffer未升级
    errGuildWelfareAuraIDError,             ///<  福利id错误
    errGuildBuildingLevelLower,             ///<  建筑等级不够
    errGuildNoMoreGuildMoney,               ///<  帮派金币不够
    errGuildNoMoreWood,                     ///<  木材不足
    errGuildNoMoreHerb,                     ///<  草药不足
    errGuildNoMoreCrystal,                  ///<  水晶不足
    errGuildNoMoreSilver,                   ///<  银子不足
    errGuildMaxLevel,                       ///<  已经最大等级
    errGuildWelfareBufferNotExist,          ///<  福利buffer不存在
    errGuildBuyAuraFailed,                  ///<  兑换buffer失败
    errGuildAuraPurchaseLimit,              ///<  购买上限
    errGuildWelfareUpgrading,               ///<  福利正在升级中
    errGuildUpgradingCountLimit,            ///<  同时升级最大数量

    errGuildBuildingIDError,                ///<  建筑ID错误
    errGuildBuildingNpcIDError,             ///<  基础npcid错误
    errGuildBuildingConfigError,            ///<  建筑配置错误
    errGuildBuildingAlreadyExist,           ///<  已有其他建筑
    errGuildBuildingNotExist,               ///<  该位置没有建筑，不能升级
    errGuildBuildingUpgrading,              ///<  建筑正在升级
    errGuildBuildingUpgradeError,           ///<  建筑升级错误
    errGuildBuildingDead,                   ///<  建筑死亡
    errGuildErrorBuildingTypeForNpc,        ///<  npc不支持该建筑类型
    errGuildBuildingMaxLevel,               ///<  已到建筑最高等级
    errGuildBTypeNotMatch,                  ///<  建筑类型不匹配
    errGuildBMaxNum,                        ///<  建筑达到最大数量
    errGuildCannotDel,                      ///<  建筑不能被拆
    errGuildCannotCreate,                   ///<  建筑不能被建造
    errGuildBaseBuildingFailed,             ///<  前置建筑不满足条件
    errGuildUpgradeDataNotExist,            ///<  建筑升级数据不存在

    errGuildEnterSceneFailed,               ///<  跳转属地地图失败
    errGuildWeatherAlreadyBeChanged,        ///<  天气已经改变
    errGuildWrongMap,                       ///<  错误的地图，该地图天气不可变更。
    errGuildWelfareBeFrozen,                ///<  福利被冻结
    errGuildAlreadyOpenDungeon,             ///<  此副本已被开启
    errGuildOpenDungeonFailed,              ///<  开启副本失败
    errGuildEnterDungeonFailed,             ///<  进入副本失败
    errGuildCannotFindDungeon,              ///<  未发现被开启的副本
    errGuildNotDungeonLeader,               ///<  不是老板指定的队长
    errGuildDeclareFailed,                  ///<  宣战失败
    errGuildCannotDeclaredYourself,         ///<  不能对自己宣战
    errGuildWarLevelLimit,                  ///<  公会等级过低，无法宣战
    errGuildInProtectionTime,               ///<  该公会目前处于免战保护状态，无法宣战
    errGuildAttackCD,                       ///<  公会战宣战cd
    errGuildAllianceCannotBeDeclared,       ///<  结盟帮派不能被宣战
    errGuildInDeclareTime,                  ///<  不在宣战时间段
    errGuildDungeonMapClosing,              ///<  副本正在关闭
    errGuildMatchGuildFailed,               ///<  匹配公会失败
    errGuildMatchWarCountLimit,             ///<  匹配公会战次数限制
    errGuildInWar,                          ///<  公会战进行中...
    errGuildNotWarTime,                     ///<  不再公会战时间内
    errGuildBeFightingToday,                ///<  不能对当天进行公会战的公会宣战

    // guild achievement
    errGuildAchiAlreadyReward,              ///< 公会成就奖励已领取
    errGuildAchiNotComplete,                ///< 公会成就未达成
    errGuildAchiRewardSucc,                 ///< 成功领取公会成就奖励

    // guild activity
    errGuildActivityConfigError,            ///< 公会活动配置错误
    errGuildAcAlreadyOpen,                  ///< 工会活动已开启

	// guild escort
	errGuildTodayAlreadyAcceptEscort,		///<  今天已经押过镖
	errGuildTodayNotOpenEscort,             ///<  公会未开启押镖
	errGuildEscortCarBeenKilled,            ///<  镖车已被击毁
	errGuildEscortCarTimeOut,               ///<  镖车时间到消失了

    // alliance
    errGuildDelAllianceSuccess,             ///< 删除公会结盟成功
    
    errGuildDeclearWarMustEnemy,            ///< 不是敌对公会不能宣战
    errGuildCannotLeaveGuildInCombat,       ///< 战斗中不能退出公会
    errGuildCannotBanishTargetInCombat,     ///< 对方在战斗中，不能逐出公会
	errGuildEscortLevelNotEnough,			///< 护送任务等级不够

    errGuildPageEnd,                        ///< 到达最后一页
    errGuildCannotLeaveInWar,               ///< 公会战期间不能离开公会
    errGuildCannotDisbandInWar,             ///< 工会战期间不能解散公会
    errGuildNotActivityTime,                ///< 不在活动时间内
    errGuildWarTargetLevelLimit,            ///< 对方公会等级过低
    errGuildWarTargetAlreadyBeDeclared,     ///< 对方已经被宣战
    errGuildWarClose,                       ///< 本服未开启公会战

	errGuildEnd,

	errSpiritBegin = 0x1B00,
	errSpiritNotOpen,						///<  境界尚未开启
	errSpiritDailyChangeCount,				///<  转换次数到达上限
	errSpiritMoneyNotEnough,				///<  转换魂不够
	errSpiritPtsNotEnough,					///<  修炼点不够
	errSpiritChangeCDTime,					///<  转换时间间隔不够
	errSpiritLevel,							///<  等级不够
	errSpiritProductLevel,					///<  练气等级不够
	errSpiritUpExpNotEnough,				///<  升级经验不足
	errSpiritUpLevelMax,					///<  升级等级达到最大值
	errSpiritAirSeaBagFull,					///<  气海包裹满
	errSpiritExchangeMoney,					///<  兑换万法之气金钱不足
	errSpiritAirSlotNotEmpty,				///<  气格子非空
	errSpiritAirSlotEmpty,					///<  气格子为空
	errSpiritAirEquipSameGroup,				///<  被装备的气已经有同种类的存在
	errSpiritDailyExp2PtsOut,				///<  当日魂转修炼点一键完成金币消耗达到上限
	errSpiritExp2PtsMoneyOut,				///<  当日魂转修炼点一键完成金币不够
	errSpiritBloodAlreadyOpen,				///<  此页已经开启
	errSpiritRoleLevelLimit,				///<  未达到境界开放等级
	errSpiritBloodSlotNumber,				///<  此孔的值已经达到最大值
	errSpiritBloodNotOpen,					///<  此页还未开启
	errSpiritBloodSlotLevel,				///<  此孔需要的境界等级没有达到
	errSpiritSpellPts,						///<  修炼点不足
	errSpiritExp2PtsMaxCount,				///<  魂转修炼点达到每日转化次数上限
	errSpiritEnd,

	errHeroBegin = 0x1C00,
	errHeroInvalid,							///<  英雄无效
	errHeroAlreadyExist,					///<  英雄已经存在
	errHeroNotExist,						///<  英雄不存在
	errHeroSummonFailed,					///<  英雄召唤失败
	errHeroNotReady,						///<  英雄冷却中
	errHeroContainerNotEmpty,				///<  英雄包裹非空
	errHeroAiInvalid,    				    ///<  英雄AI类型无效
	errHeroAlreadyHaveName,    			    ///<  英雄已经有名字了
	errHeroAlreadySummoned,					///<  英雄已经被召唤过了
	errHeroAlreadyRecalled,					///<  英雄已经被收回了
	errHeroEnd,

    // shield list
	errShieldBegin = 0x1D00,
    errNotFindTargetRole,                   ///<  未找到目标角色
    errAlreadyShield,                       ///<  已在屏蔽列表中
    errNotFindInShieldList,                 ///<  屏蔽列表中未找到
    errShieldedListFull,                    ///<  屏蔽列表已满
    errCannotShieldYourself,                ///<  不能屏蔽自己
	errShieldEnd,

    // auction
	errAuctionBegin = 0x1E00,
    errAuctionItemNotFound,                 ///<  拍卖物品未找到
    errAuctionSellingFull,                  ///<  卖出物品已达到最大数量
    errAuctionBuyingFull,                   ///<  竞拍物品已达到最大数量
    errAuctionQuerying,                     ///<  拍卖服务器忙
    errAuctionSellingPriceLow,              ///<  底价太低
    errAuctionBuyingPriceLow,               ///<  竞标价格太低
    errAuctionSellerCannotBuy,              ///<  自己就是卖出者，不可竞标
    errAuctionBuyerCannotBuy,               ///<  当前的最高出价就是自己，不可竞标
    errAuctionOnBid,                        ///<  拍卖物品正在竞标中
    errAuctionNotOpen,                      ///<  拍卖行功能未开放
    errAuctionUnknown,
	errAuctionEnd,

    // exchange
	errExchangeBegin = 0x1F00,
    errExchangeOrderFull,                   ///<  订单数量超过上限
    errExchangeOrderNotFound,               ///<  订单未找到
    errExchangeQuerying,                    ///<  交易行服务器忙
    errExchangeSceneForbidden,				///<  当前场景禁止使用金币交易行
	errExchangeEnd,

	// activity
	errActivityBegin = 0x2000,
	errLackofActivity,						///<  活跃度不够
	errActivityRewardAccepted,				///<  已经领取过活跃度礼包
	errActivityEnd,

    // real money shop
	errRMShopBegin = 0x2100,
    errRealMoneyShopNotOpen,                ///<  商城未开放
    errCannotConnectSndaServer,             ///<  与盛大计费平台通信失败
    errRealMoneyBuyNotEnoughMoney,          ///<  元宝不足
    errRealMoneyShopItemNotFound,           ///<  商品未找到
    errRealMoneyShopFriendNotFound,         ///<  赠送对象未找到
    errRealMoneyShopCrcFailed,              ///<  商城CRC校验失败
    errBillingSystemError,                  ///<  计费平台传回的未知原因失败
    errTimeBillingNotOpen,                  ///<  点卡计费系统未开放
    errTimeBillingNotEnough,                ///<  剩余点卡时间不足
    errTimeBillBusy,                        ///<  剩余点卡查询中
	errRMShopEnd,

	// ranklist
	errRankListBegin = 0x2200,
	errRoleNotOnline,						///< 玩家不在线
	errRankListEnd,

	// sabac
	errSabacBegin = 0x2300,
	errSabacNotGuildLeader,					///<  不是工会会长
	errSabacNotEnoughMoney,					///<  报名费不足
	errSabacNotEnoughItem,					///<  报名道具不足
	errSabacEnrolled,						///<  已报名
	errSabacOccupied,						///<  已占领
	errSabacFighting,						///<  开战中不能报名
	errSabacErectStatue,					///<  只有占领沙巴克的公会会长才能竖雕像
	errSabacErectNotEnoughMoney,			///<  竖雕像钱不够
	errSabacEnd,

	// reputation award
	errReputationBegin = 0x2400,
	errRepReceiveAwardSuccess,				///<  成功获取奖励
	errRepAlreadyReceived,					///<  已经获取过奖励了
	errRepNotEnoughReputation,				///<  声望值不够
	errReputationEnd,

    // pet
	errPetBegin = 0x2500,
    errPetChangeStateSuccess,               ///<  成功切换宠物状态
    errPetStateSame,                        ///<  已经是该状态
	errPetEnd,

	// checkin
	errCheckInBegin = 0x2600,
	errCheckInNotExist,
	errCheckInAlreadyDid,
	errCheckInLevelLimit,
	errCheckInClosed,
	errCheckInEnd,

    // award
	errAwardBegin = 0x2700,
    errAwardNotEnabled,
    errAwardReqSentFailed,
    errAwardFailed,
	errAwardFailed_1,
	errAwardFailed_2,
	errAwardFailed_3,
	errAwardFailed_4,
	errAwardFailed_5,
	errAwardFailed_6,
	errAwardFailed_7,
	errAwardFailed_8,
	errAwardFailed_9,
	errAwardEnd,


	// anti-cheat
	errAntiCheatBegin = 0x2800,
	errAntiCheatSuccess,
	errAntiCheatError,
	errAntiCheatErrorKick,
	errAntiCheatErrorTimeoutReturn,
	errAntiCheatExit,
	errAntiCheatNotReady,
	errAntiCheatEnd,

    // gm
	errGMBegin = 0x2900,
	errGMNoRight,
	errGMGSExecute,
	errGMNotExecute,
	errGMNoCommand,
    errGMExecuteFailed,
    errGMCannotConnectGMSvr,
    errGMKickYou,

    // gm  仅服务器内部使用，客户端不用解析
    errGMUnknownError,
    errGMVersionError,
    errGMConnectERROR,
    errGMPwdError,
    errGMRelogin,
    errGMCannotExecuteNewCmd,
    errGMNotExecutePermission,
    errGMGetPermissionError,
    errGMUserNotFind,
    errGMDBError,
    errGMTimeout,
    errGMSendMsgToMSError,
    errGMLostTLUser,
    errGMCannotFindRole,
    errGMLostCmd,
    errGMMSNotOnline,
    errGMMSExecuteCmdFailed,
    errGMSaveRoleDataFailed,
    errGMModifyRoleTypeError,
    errGMRoleOnline,
    errGMQueryZeroRoleData,
    errGMRoleNotFreeze,
    errGMRoleFreezeLessOneHour,
    errGMAnnounceNotExist,
    errGMRoleBeOp,
    errGMRoleLockedByOther,

    errGMStrCommandFailed,
    errGMStrCmdExeFailed,					///< 指令执行失败
    errGMCmdExecuting,

	errGMEnd,

	// NOTE: ADD NEW SECTION BEFORE THIS LINE

	errMiscBegin = 0x10000,

	errDisconnectTimeOut,
	errFreeMode,							///< 体验模式，部分游戏功能被禁止
	errRoleLowLevel,						///< 角色等级太低，部分游戏功能被禁止
	errArrestRoleOffline,					///< 要抓的人不在线
	errArrestClosed,						///< 不符合监狱人数条件，暂不抓人
	errArrestSceneNoPunish,					///< 所在场景没有开放GPK抓人
	errGpkAuthKick,							///< GPK认证失败踢人

	errMiscEnd,
};

enum NS_ERROR_CODE_DEF
{
    errNsUnknownError = 0,
	errNsSuccess = 1,   

    errNsNameDuplicated,					///< 重名
    errNsNameDBSysErr,						///< 名字数据库错误
    errNsNameUnknown,				        ///< 未知错误 
	errNsTooManyUser,						///< 用户数达上限
};

// tolua_end

#endif // _ERROR_DEF_H_
