#ifndef __EQUIPSLOTMANAGER_H__
#define __EQUIPSLOTMANAGER_H__

#include "MMOGameEvent.h"
#include "common.h"
#include "MMOUtil.h"

//强化需要消耗材料的最大种类
#define ENHANCE_CONSUME_COUNT 3
//装备部位的最大个数
#define EQUIP_SLOT_COUNT 13
//强化后可增加的属性的个数
#define ENHANCE_EFFECT_COUNT 5
//最大强化等级，方便预分配vector的个数，以免反复重分配和拷贝
#define MAX_ENHANCE_LEVEL 150

//最大激活等级
#define MAX_ACTIVE_LEVEL 10


enum EnhanceStatus
{
	EES_NONE = 0x00000000,
	EES_INCONFIRM = 0x00000001,
	EES_MAX = 0xf0000000,
};

typedef TMap< UINT, struct EquipSlotEnhancePropCfgData > EquipSlotEnhancePropMap;
typedef TMap< UINT, struct EquipSlotEnhanceCfgData > EquipSlotEnhanceMap;


struct EquipSlotEnhancePropCfgData
{
	INT RefineLv;
	INT ClassId;
	INT EquipSlotId;

	INT EffectProperties[ENHANCE_EFFECT_COUNT];
};

//
struct EquipSlotEnhanceCfgData
{
	INT RefineLv;
	INT PlayerRequireLv;
	INT MoneyCost;
	
	INT BaseSuccessRate;
	UINT SuccessRateFactor;

	UBOOL IsSysTip;
};

struct EquipSlotProperties
{
	EquipSlotProperties(){
		CurEnhanceLevel = 0;
		MaxEnhanceLevel = 0;
	}
	UINT CurEnhanceLevel;     //当前强化等级
	UINT MaxEnhanceLevel;
};


//强化激活配置表格数据结构
struct EquipSlotEnhanceActiveTemplate
{
	typedef struct
	{
		INT EType; //0加成数值，1添加技能等等
		INT AttributeId; //增加属性id
		INT Value; //加成数值，或者技能id
		
	}EffectData;

	INT level;

	TArray<EffectData> ActiveEffectList;
};

/*class EquipSlotData
{
public:

public:
	EquipSlotProperties m_EquipSlot
};*/


struct MMOGameEvent_EquipSlotEnhanceResult : public MMOGameEvent
{
public:

	MMOGameEvent_EquipSlotEnhanceResult( INT slotID, UBOOL isSuccess, INT NewEnhanceLv )
		: EnhanceSlotID(slotID),
		  IsSuccess(isSuccess),
		  NewEnhanceLv(NewEnhanceLv)
	{

	}

	virtual EGameEvent GetEventType() const
	{
		return GameEvent_EquipSlotEnhanceLvUp;
	}

	INT EnhanceSlotID;
	UBOOL IsSuccess;
	INT NewEnhanceLv;
};

class EquipSlotManager : public SingletonMeyers<EquipSlotManager>, public INativeGameEventHandler
{
public:
	EquipSlotManager();
	virtual ~EquipSlotManager();

	void Init();
	void Shutdown();
	void Clear();

public:
	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
	void SyncEquipSlotLevel(UINT16 level[NES_TOTAL]);

public:
	//
	void ReadEnhancePropConfig();
	const EquipSlotEnhancePropCfgData *FindEnhancePropCfg( INT classID, INT partID, INT refineLv );

	//
	void DecomposeRefineKey(UINT refineKey, UINT &outClassID, UINT &outPartID,UINT &outRefineLv )
	{
		outClassID = refineKey >> 24;
		outPartID = ( ( refineKey & 0x00ff0000 ) >> 16 );
		outRefineLv = refineKey & 0x0000ffff;
	}

	//
	void ReadEquipSlotEnhanceConfig();
	const EquipSlotEnhanceCfgData *FindEnhanceConsumeCfg( INT refineLv );

	//自己的强化数据
	EquipSlotProperties *GetCurMySlotEnhanceState( INT slotID )
	{
		if( slotID < 0 || slotID >= NES_TOTAL )
		{
			return NULL;
		}

		return &_MyEquipSlotProperties[slotID];
	}

	UBOOL IsMaxSlotEnhanceLevel( INT enhanceClassID, INT slotID, INT enhanceLv );
	void CvtEnhanceLevel( INT enhanceLv, INT &ehcMajorLevel, INT &ehcMinorLevel, INT &ehcMinorMinorLv );
	
	//
	EquipSlotProperties* GetMyEquipSlotProperty(INT slotID);
	INT GetMyEquipSlotLevel(INT slotID);
	INT GetCurEnhanceHoleLv();

	UBOOL CheckEnhanceConsume( INT containerID, INT slotID, INT checkSlotID );
	UBOOL CheckEnhanceConsume( UEquip *pEquip, INT checkSlotID );
	//UBOOL CheckMyMaterialCondition(INT slotId);

	//强化阶段等级
	const TArray<INT> &GetSortedEnhanceExtrPropLvIdx( INT classID )
	{
		check( classID >= 0 && classID < EPCT_MAX );
		return _RefineExtrPropLvIdx[classID];
	}

	//获得显示文字
	FString GetEquipPropertyNameById(INT id);
	FString GetEquipSlotNameById(INT id);

	//发送消息
	void SendEnhanceEquipSlot( INT refineSlot, INT consumeConID, INT consumeSlotID );

	//弹出框状态
	FORCEINLINE void SetFlag(EnhanceStatus es)
	{
		m_iEnhanceFlag |= es;
	}

	FORCEINLINE INT CheckFlag(EnhanceStatus es) const
	{
		return m_iEnhanceFlag & es;
	}

	FORCEINLINE void ClearFlag(EnhanceStatus es)
	{
		m_iEnhanceFlag &= (~es);
	}

	//-----------------------------------------
	void ApplyEnhancePropertyToEquip();
	INT GetEnhanceActiveLevel() const;
	EquipSlotEnhanceActiveTemplate& GetEquipSlotEnhanceActiveTemplate(INT lv);

private:
	//
	UINT CombineRefineKey( INT classID, INT partID, INT refineLv )
	{
		INT ret = ( classID << 24 & 0xff000000 );
		ret |= ( partID << 16 & 0x00ff0000 );
		ret |= refineLv & 0x0000ffff;
		return (UINT)ret;
	}
	
private:
	EquipSlotEnhancePropMap _EnhancePropCfg;
	EquipSlotEnhanceMap _EnhanceEquipSlotCfg;

	TArray<INT> _RefineExtrPropLvIdx[EPCT_MAX];

private:
	EquipSlotProperties _MyEquipSlotProperties[EQUIP_SLOT_COUNT];
	INT m_iEnhanceFlag;

private:
	EquipSlotEnhanceActiveTemplate m_EquipSlotEnhanceActiveData[MAX_ACTIVE_LEVEL];

};

#endif