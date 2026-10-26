
#ifndef _MMOAttributeAccountManager_H_
#define _MMOAttributeAccountManager_H_

#include "MMOSingleton.h"
#include "MMOUtil.h"
#include "MMOGameEvent.h"
#include "MMOGameUIClasses.h"

#include "MMOAttrListener.h"

//特殊公式
enum ESpecialAttributeInPanel
{
	SAIP_PKValue = catTotal, //pk值是特殊的
	SAIP_Fatigue, //疲劳度是特殊的
	SAIP_PhyDamageReduce, //物理伤害减免
	SAIP_MagDamageReduce,
	SAIP_CritRate, //暴击率
	SAIP_DodgeRate, //闪避率
	SAIP_HitRate, //命中率
	SAIP_AttSpeedAdd, //攻速加成
	SAIP_CritReduceRate, //暴击抵抗率
	SAIP_MpRecover,
};

enum EValueShowType
{
	EVST_Int, //整形
	EVST_Att, //攻击力是特殊的
	EVST_Decimal, //2位小数
	EVST_Rate, //2位小数%
	EVST_HP,
	EVST_MP,
	EVST_Bag,
	EVST_Weap,
	EVST_Armor,
	EVST_ExpEtra,
};

struct StructAttributeItem
{
	//按理应该是EPCT_Max，
	FString AttributeName[EPCT_MAX];
	FString TipsDesc[EPCT_MAX];

	//属性值，如果需要计算就为0
	INT AttributeValueType[EPCT_MAX];
	//特殊区间属性
	INT AttributeValueTypeB[EPCT_MAX];

	//关联属性
	INT AttributeTypeA[EPCT_MAX];
	INT AttributeTypeB[EPCT_MAX];

	//除以100
	FLOAT AttributeMulParaA[EPCT_MAX];
	FLOAT AttributeMulParaB[EPCT_MAX];

	UBOOL DifferName;
	UBOOL DifferValueType;
	UBOOL DifferTips;
	UBOOL DifferTipsValueType;
	UBOOL DifferTipsValuePara;
	EValueShowType ValueShowType;
	EValueShowType TipsValueShowType;
	
	StructAttributeItem()
	{
		Reset();
	}

	void Reset()
	{
		appMemzero( this , sizeof(StructAttributeItem) );
	}



};

struct StructAttributeGroup
{
	FString GroupName;
	TArray< StructAttributeItem > AttributeList;
};



typedef TArray< StructAttributeGroup > AttributeGroupArray;

class MMOAttributeAccountManager : public SingletonMeyers<MMOAttributeAccountManager>
{
public:

	MMOAttributeAccountManager();
	virtual ~MMOAttributeAccountManager();

	void Init();
	void Shutdown();
	AttributeGroupArray& GetAttributeGroupArray() { return AttributeGroupList; }

	const FString GetAttributeName( INT groupId , INT index ) const ;
	const FString GetAttributeValue( INT groupId , INT index ) const ;
	const FString GetAttributeDesc( INT groupId , INT index ) const ;

	void SetAttrOwnerMode( AttrListenerType type );

	//是否是属性界面里显示的属性
	UBOOL IsRelationAttribute( INT groupId , INT index , INT Attri );
	
	//是否是战斗/生命力计算的属性
	UBOOL IsBattleAttribute( INT Attri );


	FString GetDamagePoint();
	FString GetLifePoint();
	FString GetBattlePoint();

	void SetBattlePoint( INT bp ){ BattlePoint = bp; }

	INT GetOwnerAttribute( INT attriId , AttrListenerType type );

	INT GetAttributeById(INT attrId);

	void setExpEtra(INT exp);
	INT getExpEtra(){return expEtra;}

#define Attribute_GroupNum 4

protected:

	//
	UBOOL IsRelationSpecialAttribute( INT Special , INT Attri );

	void initBaseAttribute( INT groupId );
	void initAttAttribute( INT groupId );
	void initDefAttribute( INT groupId );
	void initMpAttribute( INT groupId );
	void initOtherAttribute( INT groupId );

	void initBaseAttributeByHighAndLow(CHAR_ATTR_TYPE typeHigh, CHAR_ATTR_TYPE typeLow,INT groupId = 0, INT pos = 0);

	//INT ClassId;
	INT BattlePoint;
	AttributeGroupArray AttributeGroupList;

	TArray<MMOAttrListener*> AttrOwnerTypeList;
	MMOAttrListener* CurAttrListener;

	INT expEtra;

};

#endif