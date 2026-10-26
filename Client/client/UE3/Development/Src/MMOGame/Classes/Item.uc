/*
 * base class for equip
 * */

class Item extends Object implements(IExcelable,IReferenceID)
	hidecategories(Object)
	dependson(TypeDefine)
	native
	hidecategories(Object,Debug,Advanced,Physics,CollisionChanged,Attachment,DisplayDebug,Display,Movement,Collision);

var(Item)   int             ItemId				<ExportExcel="0"|DisplayName="ItemId">;
var(Item)   private{private} Texture2D	    DisplayIcon			<ExportExcel="24"|DisplayName="DisplayIcon">;
var(Item)   private{private} Texture2D	    DisplayLargeIcon			<ExportExcel="33"|DisplayName="DisplayLargeIcon">;
var(Item)   private{private} Texture2D	    DisplayLargeIconFemale		<ExportExcel="34"|DisplayName="DisplayLargeIconFemale">;

var string DisplayIcon_Str;
var string DisplayLargeIcon_Str;
var string DisplayLargeIconFemale_Str;

//var         int             InstanceID			<DisplayName="InstanceID">;
var(Item)   string     ItemName			<ExportExcel="1"|DisplayName="ItemName">;
var(Item)   int             ItemLevel           <ExportExcel="31"|DisplayName="ItemLevel">;
var(Item)   string          Description			<ExportExcel="25"|DisplayName="Description">;
var(Item)   int             MaxStackNum			<ExportExcel="26"|DisplayName="MaxStackNum">;  // min 1: can't overlap; numbers below 1 has no meaning

var(Item)  private{private} StaticMesh  DropMesh					<ExportExcel="27"|DisplayName="DropMesh">;
var string DropMesh_Str;

var transient ParticleSystemComponent   EmitterComponent;
var transient MMOActor Owner;


// 道具类型
var(Item) string ItemType					<ExportExcel="2"|DynamicList="ItemType">;

// 道具子类型(导出时指定即可)
//var (Item)EItemSubType ItemSubType				<ExportExcel="3"|DisplayName="ItemSubType">;
var(Item) string ItemSubType					<ExportExcel="3"|DynamicList="ItemSubType">;

var(Item) int RequireLevel						<ExportExcel="4"|DisplayName="RequireLevel">;

var(Item) Spell_ClassType RequireClass			<ExportExcel="5" |Merger="0"|DisplayName="RequireClass">;//EPlayerClass 
var(Item) EGenderType RequireGender				<ExportExcel="6"|DisplayName="RequireGender">;
var(Item) int MaxEquip							<ExportExcel="7"|DisplayName="MaxEquip">;
var(Item) int MaxOwn							<ExportExcel="8"|DisplayName="MaxOwn">;

// 道具颜色
var(Item) EItemColor ItemColor					<ExportExcel="9"|DisplayName="ItemColor">;
// 道具绑定类型
var(Item) EBIND_TYPE ItemBindType			<ExportExcel="10"|DisplayName="ItemBindType">;
// 道具耐久
var(Item) EDUR_TYPE ItemDuration		<ExportExcel="11"|DisplayName="ItemDuration">;
// 当前耐久
var(Item) int DefaultDuration					<ExportExcel="12"|DisplayName="DefaultDuration">;
//放到摊位中后，会被拆分，服务器只做引用，而客户需要作出实际移动的假象 这里记录原始耐久
//var int OriDuration;


//道具引用的技能
var(Item) protected{protected} MMOAbility ToUseAbility				<ExportExcel="13"|DisplayName="ToUseAbility">;
var transient int ToUseAbility_SpellID;

var(Item) int SpellLevel						<ExportExcel="14"|DisplayName="SpellLevel">;

//使用道具冷却
var(Item) float SelfCoolDown					<ExportExcel="15"|Convert="1000"|DisplayName="SelfCoolDown">;
var(Item) string GroupCoolDown					<ExportExcel="16"|DisplayName="GroupCoolDown">;

//装备子子类型
var(Item) string ItemSubSubType					<ExportExcel="17"|DynamicList="ItemSubSubType">;

var init array<INT> AttributeList; //by york，属性都在这里，不用其他的属性
//出售价格 这里是指道具出售给系统的价格 可否贩卖 该道具是否可以贩卖给商店
var(Item) int SellPrice							<ExportExcel="18"|DisplayName="SellPrice">;
//使用状态 该道具在何种状态下可以使用，只按最大层次的状态做区分
var(Item) EITEM_COMBAT_TYPE UsedStatus			<ExportExcel="19"|DisplayName="UsedStatus">;
//是否丢弃 是否可以丢弃该物品
var(Item) bool Drop								<ExportExcel="20"|DisplayName="Drop">;
////可否贩卖 该道具是否可以贩卖给商店
//var(Item) int	Shell <ExportExcel="21">;
//可否交易 是指玩家可以否交易该道具，只有非绑定道具才可以交易
//var(Item) bool Trade							<ExportExcel="21"|DisplayName="Trade">;
//可否存储 该物品是否可放入仓库之类的存储空间中
var(Item) bool Storage							<ExportExcel="22"|DisplayName="Storage">;

var(Item) bool CanSell							<ExportExcel="32"|DisplayName="CanSell">;
var(Item) bool Expensive						<ExportExcel="38"|DisplayName="Expensive">;
var(Item) bool CanDecompose                     <ExportExcel="39"|DisplayName="CanDecompose">;

var(Item) string Script					<ExportExcel="23"|DisplayName="Script">;

var int byPrefixLevel;

var(Item) int LimitDuration <ExportExcel="35"|DisplayName="LimitDuration">;
var(Item) int LimitCount <ExportExcel="36"|DisplayName="LimitCount">;
var(Item) bool RecordTradeLog <ExportExcel="37"|DisplayName="RecordTradeLog">;

var(Item) bool Auction;
var(Item) int AuctionFee1<ClampMin=0 | ClampMax=1000000000>;
var(Item) int AuctionFee2<ClampMin=0 | ClampMax=1000000000>;
var(Item) int AuctionFee3<ClampMin=0 | ClampMax=1000000000>;
var(Item) byte AuctionType;
var(Item) byte AuctionSubType;
var(Item) int AuctionDefaultPrice;
var(Item) int Weight;
var(Item) int ItemPack;
var(Item) int ItemPack2;
var(Item) int ShopTypeSell;
var(Item) bool TradeNeedIntimacy;

var(Item) bool CanResource;
//---------------------------------------------------------------
// 音效配置
//---------------------------------------------------------------
// only for sound effect
var(SoundFX) EItemMaterialType SoundMaterialType		<ExportExcel="28"|DisplayName="SoundMaterialType">;
var(SoundFX) EItemActionSoundType SoundActionType		<ExportExcel="29"|DisplayName="SoundActionType">;

//var(SoundFX) array<SoundCue> Sound_Use;
//var(SoundFX) array<SoundCue> Sound_Get;
//var(SoundFX) array<SoundCue> Sound_Fall;
//var(SoundFX) array<SoundCue> Sound_Land;

//var(SoundFX) array<SoundCue> Sound_Attack				<DisplayName="Sound_Attack">;
//var(SoundFX) array<SoundCue> Sound_CriticalAttack		<DisplayName="Sound_CriticalAttack">;
var(SoundFX) EClothNoiseType ClothNoiseType             <ExportExcel="30"|DisplayName="ClothNoiseType">;

//native function PlayRandomSound(array<SoundCue> soundList);

native function Init( EPlayerClass pc, EGenderType gt, bool useAdvancedApperance );
// 物品被丢弃(可能需要放在地上)
//native function bool OnDrop(DropItemActor Target, bool bNew,Vector DorpLocation,Rotator DropRotation);
native function bool IsUseblForActor( MMOActor actor);
//native function String GetLargeIconName();

native function bool IsWeapon();
native function bool IsEquip();

// 当此物品被使用,装备上时,会调用OnTakeOn函数,Target为作用对象,一般在这函数里处理跟这个装备相关的内容,比如因为装备上本物品,会给目标加多少属性什么的
//event bool OnTakeOn(MMOActor Target)
//{
//	return true;
//}

native function bool OnTakeOn(MMOActor Target, bool UseAdvancedAppearence);
native function bool OnTakeOff(MMOActor Target);

//event bool OnTakeOff(MMOActor Target)
//{
//	return true;
//}

event OnPickUp(MMOActor Target);

function AttachDropEmitter()
{
	//EmitterComponent = new class'ParticleSystemComponent';
	//EmitterComponent.SetTemplate( ParticleSystem (DynamicLoadObject( "FX_Scene.Interaction.WuPingDiaoLuo",class'ParticleSystem')  )  );
	//EmitterComponent.SetTranslation(RelativeLocation);
	//EmitterComponent.SetRotation(RelativeRotation);
	//AttachComponent( EmitterComponent );
}
function DetachDropEmitter()
{
	//DetachComponent(EmitterComponent);
	
}



function SetEmissiveColor(LinearColor c);

function SetOpacity(float percent);

native function bool IsNeedArchetype();

function Tick( float DeltaTime )
{
}

//nState使用约定
native function String GetIconName(int nState = 0);

//-------------------------------------------------------
// 导出到Excel
//-------------------------------------------------------

// 导出表头,先调用脚本函数，再调用native函数
event ScriptExportExcelHeaders(out array<string> Header, out array<string> DefaultValues)
{


}

// 导出每行数据,先调用脚本函数，再调用native函数
event ScriptDataToExcel(out array<string> Row)
{	
}

native function ExportExcelHeaders(out array<string> Header, out array<string> DefaultValues);
native function DataToExcel(out array<string> Row);
native function ImportFromExcel(array<string> values);
event ScriptImportFromExcel(array<string> Values)
{
	//local string val;

	//val = values[0];
	//ItemId = int(val);
}
native function InitDataToExcel();

event string GetDetailedDescription( int InIndex )
{
	local string locDescription;
	switch( InIndex )
	{
	case 0:
		locDescription = string(ItemId);
		break;
	case 1:
		locDescription = ItemName;
		break;
	case 2:
		locDescription = Description;
		break;

	default:
		break;
	}

	return locDescription;
}

native function int GetTemplateID() const;
native final function string GetDisplayName() const;

DefaultProperties
{
}
