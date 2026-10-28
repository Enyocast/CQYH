#ifndef _MODIFIER_DEF_H_
#define _MODIFIER_DEF_H_

#define MODIFIER_PARAM_COUNT		(3)

enum MODIFIER_X_TYPE
{
	mxtUseNone = 0,

	mxtUseX1,
	mxtUseX2,
	mxtUseX3,
	mxtUseX4,

	mxtTotal,
};

enum MODIFIER_TARGET_TYPE
{
	mttInvalid = -1,

	mttCharacter,
	mttBullet,
	mttMissile,

	mttTotal
};

enum MODIFIER_RET_CODE
{
	mrcError = -1,

	mrcFalse,
	mrcTrue,
	mrcTrueAndBreak,
};

enum MODIFIER_EVENT_OCCASION
{
	meoInvalid = -1,

	meoBulletEventBegin,
	meoOnBulletCreate = meoBulletEventBegin,
	meoBeforeRoll,
	meoAfterRollAsCaster,
	meoAfterRollAsTarget,
	meoOnBulletHitAsCaster,
	meoOnBulletHitAsTarget,
	meoAfterApplyDefenceAsCaster,
	meoAfterApplyDefenceAsTarget,
	meoBeforeDamageEnhancedAsCaster,
	meoBeforeDamageEnhancedAsTarget,
	meoAfterDamageAsCaster,
	meoAfterDamageAsTarget,
	meoBeforeApplyDamageAsTarget,
	meoBulletEventEnd,

	meoCharEventBegin = meoBulletEventEnd,
	meoOnCharCast = meoCharEventBegin,
	meoOnCharCastSuccess,
	meoOnCharPreCast1,
	meoOnCharPreCast2,
	meoOnCharPreCast3,
	meoOnCharPreCast4,
	meoOnCharPreCast5,
	meoOnTimeup,
	meoOnAppendAura,
	meoOnRemoveAura,
	meoOnEquipItem,
	meoOnAuraTimeup,
	meoOnAuraEffect,
	meoOnAppendAuraAsCaster,
	meoOnDying,
	meoCharEventEnd,

	meoTotal = meoCharEventEnd
};

enum CHAR_MODIFIER_INDEX
{
	cmiInvalid = 0,

	cmi_A,			///< @line		改变自身的走路或者跑步速度 1参为改变的类型(具体数值)
	cmi_B,			///< @line		改变自身的一些属性(具体数值)
	cmi_003,		///< @line		改变自身的一些属性(百分比)  通过光环的 GetEffectPct() 函数获得百分比数值
	cmi_004,		///< @line		改变自身的走路或者跑步速度 1参为改变的类型(百分比) 通过光环的 GetEffectPct() 函数获得百分比数值
	cmi_005,		///< @line		GenerateSingleBullet,							生成单发子弹（单体攻击）
	cmi_006,		///< @line		GenerateMultiBullet,							生成多发子弹（散射/多重射击）
	cmi_007,		///< @line		GenerateMissile,								生成飞行投射物（火球、箭矢等）
	cmi_008,		///< @line		Charge,											冲锋（直线位移+伤害）
	cmi_009,		///< @line		SingleAura,										单体状态效果（如单体Buff）
	cmi_010,		///< @line		MultiAura,										群体状态效果（如团队Buff）
	cmi_011,		///< @line		Stun,											眩晕（硬控）
	cmi_012,		///< @line		EnableAttribute,								开启属性
	cmi_013,		///< @line		MutiBulletWithAvgDamage,						均摊伤害的多发子弹（如霰弹枪）
	cmi_014,		///< @line		AuraRegisterEvent,								状态效果注册事件（如触发条件）
	cmi_015,		///< @line		______NotImplemented_No15,						
	cmi_016,		///< @line		LeapToTargetPos,								跳跃至目标位置（突进）
	cmi_017,		///< @line		SpellRegisterEventOnEquip,						装备时注册技能事件（如触发特效）
	cmi_018,		///< @line		Fear,											恐惧（软控，目标逃跑）
	cmi_019,		///< @line		ModifyAttackWithDefense,						根据防御力修正攻击（破甲机制）
	cmi_020,		///< @line		DirectlyAddSpell,								直接添加技能
	cmi_021,		///< @line		CircleSearchEnemyAndCastSubSpell,				圆形搜索敌人并施放子技能
	cmi_022,		///< @line		ReduceCurrentAuraStackCount,					减少当前光环层数
	cmi_023,		///< @line		ModifyPendingSpell,								修改待生效技能（动态调整）
	cmi_024,		///< @line		SetDamageAbsorb,								设置伤害吸收（护盾值）
	cmi_025,		///< @line		AuraCheckDamageAbsorb,							状态检查伤害吸收（如护盾）
	cmi_026,		///< @line		SpellRegisterTimerEvent,						技能定时事件（延迟触发）
	cmi_027,		///< @line		DirectlyCastSubSpell,							直接释放子技能
	cmi_028,		///< @line		TeleportToLockedTarget,							传送至锁定目标（闪现）
	cmi_029,		///< @line		CharInvincible,									角色无敌（短暂免伤）
	cmi_030,		///< @line		ChargeToTarget,									向目标冲锋
	cmi_031,		///< @line		GenerateSingleHealBullet,						生成单体治疗子弹（如治疗箭）
	cmi_032,		///< @line		GenerateMultiHealBullet,						生成群体治疗子弹（范围治疗）
	cmi_033,		///< @line		GenerateTeamHealBullet,							生成队伍治疗子弹（团队回血）
	cmi_034,		///< @line		AdjustSpellDirectionWithFaceDirection,			根据角色朝向调整技能方向
	cmi_035,		///< @line		RecoveryHp,										恢复HP
	cmi_036,		///< @line		CheckItem,										检查物品（消耗品/装备需求）
	cmi_037,		///< @line		CheckAccumulateTime,							检查累积时间（如充能机制）
	cmi_038,		///< @line		SetCharFlagBit,									设置角色标志位
	cmi_039,		///< @line		Random,											随机
	cmi_040,		///< @line		ClearNextTarget,								清除下一个目标
	cmi_041,		///< @line		CheckMpByPercent,								按百分比检查MP
	cmi_042,		///< @line		CheckMpByValue,									按固定值检查MP
	cmi_043,		///< @line		ReviveTarget,									复活目标
	cmi_044,		///< @line		TeleportToNearestGraveyard,						传送至最近墓地（死亡复活）
	cmi_045,		///< @line		CheckAndConsumeMoney,							检查并且消耗货币
	cmi_046,		///< @line		CheckTargetCount,								检查目标数量
	cmi_047,		///< @line		LockNearestTargetInSector,						锁定扇形内最近目标
	cmi_048,		///< @line		LockNearestTarget,								锁定最近目标
	cmi_049,		///< @line		KnockBack,										击退
	cmi_050,		///< @line		ModifierCost,									修改技能花费
	cmi_051,		///< @line		SummonNpc,										召唤NPC（宠物/图腾）
	cmi_052,		///< @line		RotateTargetPt,									旋转目标角度
	cmi_053,		///< @line		CheckIntervalAndCastSubSpell,					检查间隔并施放子技能（周期性效果）
	cmi_054,		///< @line		RotateSelf,										旋转自己
	cmi_055,		///< @line		CheckMultiAccumulateTime,						检查多重累积时间
	cmi_056,		///< @line		CheckHpByPct,									按百分比检查HP
	cmi_057,		///< @line		CheckHpByValue,									按固定值检查HP
	cmi_058,		///< @line		CheckExFlag,									检查Ex标志 (技能?)
	cmi_059,		///< @line		SetExFlag,										设置Ex标志 (技能?)
	cmi_060,		///< @line		RemoveAura,										移除光环
	cmi_061,		///< @line		CastSubSpellByAuraCaster,						根据光环施法者触发子技能
	cmi_062,		///< @line		CheckCurrentWeaponType,							检查当前武器类型
	cmi_063,		///< @line		AuraTimeupEffect,								状态结束时的效果（如爆炸/回血）
	cmi_064,		///< @line		AuraKnockBack,									状态附带击退（如光环爆炸）
	cmi_065,		///< @line		GenerateDivergentMissile,						生成分叉投射物（如分裂弹）
	cmi_066,		///< @line		GenerateRandomTargetPt,							生成随机目标点（如范围轰炸）
	cmi_067,		///< @line		FindAura,										查找状态效果（检查是否存在）
	cmi_068,		///< @line		SubstituteNextSpell,							替换下一个技能
	cmi_069,		///< @line		AddAuraToCaster,								给施法者添加状态（自我增益）
	cmi_070,		///< @line		ScanTarget,										扫描目标（范围内索敌）
	cmi_071,		///< @line		Silence,										沉默（禁止施法）
	cmi_072,		///< @line		CheckCurrentAura,								检查当前光环
	cmi_073,		///< @line		GhostStep,										鬼步（瞬移残影）
	cmi_074,		///< @line		LeapAndMissile,									跳跃和导弹?
	cmi_075,		///< @line		DispelAuraByID,									按ID驱散状态
	cmi_076,		///< @line		DispelAuraByType,								按类型驱散状态（如驱散所有Debuff）
	cmi_077,		///< @line		DispelAuraBySubType,							根据子类型消除光环
	cmi_078,		///< @line		BatchDispelAuraByType,							批量驱散同类状态
	cmi_079,		///< @line		CheckLockTarget,								检查锁定目标
	cmi_080,		///< @line		BreakCast,										停止触发
	cmi_081,		///< @line		ChargeToNextTarget,								冲锋到下一个目标
	cmi_082,		///< @line		ModifyParamX,									修改参数X（通用数值调整）
	cmi_083,		///< @line		CheckCurrentSpell,								检查当前技能
	cmi_084,		///< @line		Freeze,											冻结（定身+冰伤）
	cmi_085,		///< @line		CheckObjType,									检查对象类型（玩家/NPC/陷阱等）
	cmi_086,		///< @line		SetStance,										设置姿态（战斗/非战斗状态）
	cmi_087,		///< @line		DragByAura,										被状态效果拖动（如黑洞吸引）
	cmi_088,		///< @line		SyncFlagPos,									同步标志位置
	cmi_089,		///< @line		Thrown,											投掷（强制位移，如抓取抛投）
	cmi_090,		///< @line		CheckThrown,									检查投掷
	cmi_091,		///< @line		RotateToLockedTarget,							旋转到锁定目标
	cmi_092,		///< @line		DirectlySummonNpc,								直接召唤NPC（无延迟）
	cmi_093,		///< @line		ResetScanner,									重置扫描
	cmi_094,		///< @line		CheckChangedWeaponType,							检查切换后的武器类型
	cmi_095,		///< @line		Suicide,										自杀（自爆技能）
	cmi_096,		///< @line		ModifyCanbeThrown,								修改可以投掷
	cmi_097,		///< @line		CheckPass,										检查通过条件
	cmi_098,		///< @line		LockNearestTargetInRect,						锁定矩形内最近目标
	cmi_099,		///< @line		ScanTargetAndExcludeLocked,						扫描目标并排除已锁定
	cmi_100,		///< @line		NpcCopySelf,									NPC复制自身（镜像分身）
	cmi_101,		///< @line		ClientShowTime,									客户端显示时间（如倒计时UI）
	cmi_102,		///< @line		JumpToAuraCaster,								跳跃到光环施法者
	cmi_103,		///< @line		BreakAuraCasterSpell,							打断状态施法者的施法(光环)
	cmi_104,		///< @line		SingleBulletToNextLoopedTarget,					子弹循环攻击下一个目标（弹射机制）
	cmi_105,		///< @line		ChargeCertainDistance,							固定距离冲锋
	cmi_106,		///< @line		CheckDistanceBetweenCasterAndTarget,			检查施法者与目标之间的距离
	cmi_107,		///< @line		GenerateMissileFromCaster,						从施法者生成投射物
	cmi_108,		///< @line		ModifyParam1WithTargetDistance,					根据目标距离修改参数1（如远程衰减）
	cmi_109,		///< @line		ModifySpellEffectAccordingToAccumulateParam,    根据累积参数修改技能效果
	cmi_110,		///< @line		ReduceAuraStackCount,							减少状态效果的叠加层数
	cmi_111,		///< @line		CastingSpellRegisterEvent,						施法时注册事件（如读条回调）
	cmi_112,		///< @line		GenerateBlock,									生成格挡效果
	cmi_113,		///< @line		RefreshSlotCD,									刷新技能槽CD
	cmi_114,		///< @line		CheckHpInCircle,								检查圆形区域内目标的HP
	cmi_115,		///< @line		RemoveTargetAura,								移除目标光环
	cmi_116,		///< @line		CheckWeather,									检查天气（如雨天增强雷电技能）
	cmi_117,		///< @line		CheckAuraCasterLive,							检查光环施法者是否存活
	cmi_118,		///< @line		RemovePendingAura,								移除待生效的状态效果
	cmi_119,		///< @line		AddPendingSpellAttr,							添加待生效的技能属性
	cmi_120,		///< @line		AddMaxHpAndCurrentHp,							增加最大HP和当前HP
	cmi_121,		///< @line		CheckIsBoss,									检查目标是否为BOSS
	cmi_122,		///< @line		CheckIsDaytime,									检查是否为白天
	cmi_123,		///< @line		AddParamX,										增加ParamX
	cmi_124,		///< @line		AuraLoadTransformSpell,							状态效果加载变形技能
	cmi_125,		///< @line		CastSubSpellToAuraCaster,						对状态施法者触发子技能
	cmi_126,		///< @line		Seduced,										魅惑（目标暂时叛变）
	cmi_127,		///< @line		CheckIsMoving,									检查是否在移动
	cmi_128,		///< @line		Like 063,										[状态结束时的效果（如爆炸/回血）] ?
	cmi_129,		///< @line		ModifyAuraAttr,									修改状态属性（如延长持续时间）
	cmi_130,		///< @line		ThrownFromCurrentPos,							从当前位置投掷
	cmi_131,		///< @line		Leap,											跳跃
	cmi_132,		///< @line		LeapToLockedTarget,								跳跃至锁定目标（如猛扑）
	cmi_133,		///< @line		SuperMassiveBlackHole,							超级黑洞（大范围牵引效果）
	cmi_134,		///< @line		ShareDamageWithAuraCaster,						与状态施法者分摊伤害（生命链接）
	cmi_135,		///< @line		TriggerEventRootSpellCD,						触发关联技能的冷却事件
	cmi_136,		///< @line		IgnoreDynamicBlock,								忽略动态阻挡（穿墙技能）
	cmi_AllNpcSpecies,	///< @line	AllNpcSpeciesDamage,							对某类NPC造成特定伤害（种族克制）
	cmi_138,		///< @line		SetSpellFlag,									设置技能标记（如“不可打断”）
	cmi_139,		///< @line		RemoveAllDebuff,								移除所有负面状态（净化）
	cmi_140,		///< @line		ChangeWeather,									改变天气（技能触发环境变化）
	cmi_141,		///< @line		SubstituteMainSpellID,							替换主技能ID
	cmi_142,		///< @line		CheckSlotSpellID,								检查技能槽中的技能ID
	cmi_143,		///< @line		,
	cmi_144,		///< @line		,
	cmi_145,		///< @line		,
	cmi_146,		///< @line		,
	cmi_147,		///< @line		,
	cmi_148,		///< @line		,
	cmi_149,		///< @line		,
	cmi_150,		///< @line		,
	cmi_151,		///< @line		,
	cmi_152,		///< @line		,
	cmi_153,		///< @line		,
	cmi_154,		///< @line		,
	cmi_155,		///< @line		,
	cmi_156,		///< @line		,
	cmi_157,		///< @line		,
	cmi_158,		///< @line		,
	cmi_159,		///< @line		,
	cmi_160,		///< @line		,
	cmi_161,		///< @line		,
	cmi_162,		///< @line		,
	cmi_163,		///< @line		,
	cmi_164,		///< @line		,
	cmi_165,		///< @line		,
	cmi_166,		///< @line		,
	cmi_167,		///< @line		,
	cmi_168,		///< @line		,
	cmi_169,		///< @line		,
	cmi_170,		///< @line		,
	cmi_171,		///< @line		,
	cmi_172,		///< @line		,
	cmi_173,		///< @line		,
	cmi_174,		///< @line		,
	cmi_175,		///< @line		,
	cmi_176,		///< @line		,
	cmi_177,		///< @line		,
	cmi_178,		///< @line		,
	cmi_179,		///< @line		,
	cmi_180,		///< @line		,
	cmi_181,		///< @line		,
	cmi_182,		///< @line		,
	cmi_183,		///< @line		,
	cmi_184,		///< @line		,
	cmi_185,		///< @line		,
	cmi_186,		///< @line		,
	cmi_187,		///< @line		,
	cmi_188,		///< @line		,
	cmi_189,		///< @line		,
	cmi_190,		///< @line		,
	cmi_191,		///< @line		,
	cmi_192,		///< @line		,
	cmi_193,		///< @line		,
	cmi_194,		///< @line		,
	cmi_195,		///< @line		,
	cmi_196,		///< @line		,
	cmi_197,		///< @line		,
	cmi_198,		///< @line		,
	cmi_199,		///< @line		,
	cmi_200,		///< @line		,
	cmi_201,		///< @line		,
	cmi_202,		///< @line		,
	cmi_203,		///< @line		,
	cmi_204,		///< @line		,
	cmi_205,		///< @line		,
	cmi_206,		///< @line		,
	cmi_207,		///< @line		,
	cmi_208,		///< @line		,
	cmi_209,		///< @line		,
	cmi_210,		///< @line		护身戒指/麻痹戒指/超负载戒指/复活戒指/隐身戒指/虹魔戒指/项链/手镯/红宝石戒指/思贝儿手镯/龙之手镯/逍遥扇/龙之戒指/心灵手镯/恶魔铃铛/铂金戒指/骑士手镯
	cmi_211,		///< @line		集合令
	cmi_212,		///< @line		侦测项链
	cmi_213,		///< @line		传送戒指
	cmi_214,		///< @line		,
	cmi_215,		///< @line		,
	cmi_216,		///< @line		,
	cmi_217,		///< @line		,
	cmi_218,		///< @line		,
	cmi_219,		///< @line		,
	cmi_220,		///< @line		,
	cmi_221,		///< @line		,
	cmi_222,		///< @line		,
	cmi_223,		///< @line		魔血戒指/项链/手镯/魔血转换
	cmi_224,		///< @line		,
	cmi_225,		///< @line		,
	cmi_226,		///< @line		,
	cmi_227,		///< @line		,
	cmi_228,		///< @line		,
	cmi_229,		///< @line		,
	cmi_230,		///< @line		,
	cmi_231,		///< @line		,
	cmi_232,		///< @line		,
	cmi_233,		///< @line		,
	cmi_234,		///< @line		,
	cmi_235,		///< @line		,
	cmi_236,		///< @line		,
	cmi_237,		///< @line		,
	cmi_238,		///< @line		,
	cmi_239,		///< @line		,
	cmi_240,		///< @line		,
	cmi_241,		///< @line		,
	cmi_242,		///< @line		,
	cmi_243,		///< @line		,
	cmi_244,		///< @line		,
	cmi_245,		///< @line		,
	cmi_246,		///< @line		,
	cmi_247,		///< @line		,
	cmi_248,		///< @line		,
	cmi_249,		///< @line		,
	cmi_250,		///< @line		,
	cmi_251,		///< @line		,
	cmi_252,		///< @line		,
	cmi_253,		///< @line		,
	cmi_254,		///< @line		,
	cmi_255,		///< @line		,
	cmi_256,		///< @line		,
	cmi_257,		///< @line		,
	cmi_258,		///< @line		,
	cmi_259,		///< @line		,
	cmi_260,		///< @line		,
	cmi_261,		///< @line		,
	cmi_262,		///< @line		,
	cmi_263,		///< @line		,

	cmiCount
};

#endif // _modifier_def_h__

