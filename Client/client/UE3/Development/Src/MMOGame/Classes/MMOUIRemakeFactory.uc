class MMOUIRemakeFactory extends MMOUIBase
	config(MMOGame)
	native(UI);

enum RemakeType
{
	EReMkTp_Invalid,
	EReMkTp_Equip,
	EReMkTp_Book,
	EReMkTp_Medicine
};

var RemakeType _CurRemakeType;
var int _ConsumptionIDForRemake;
var int _ConsumptionCntForRemake;

var config int _ConsumptionIDForRemakeMedicine;
var config int _ConsumptionCntForRemakeMedicine;

var config int _ConsumptionIDForRemakeBook;
var config int _ConsumptionCntForRemakeBook;
//var int _FeeForRemake;

//
native function NativeInitLoad();

native function BagSlotChange( int bagId, int slotId );
//native function PlayerMoneyChange( EMONEY_TYPE MoneyType, int DeltaMoney);
//
native function UpdatePanel();
//
event CallAsSetRemakeConsumptionInfo( string iconName, int itemID, int colorIdx, int curConsumptionCnt, int needConsumptionCnt )
{
	ActionScriptVoid( "UCSetRemakeConsumptionInfo" );
}
event CallAsSetRemakeResult( bool isSuccess, string iconName, string itemName, bool isBonus )
{
	ActionScriptVoid( "UCSetRemakeResult" );
}
event CallAsSetRemakeMoney( string moneyStr )
{
	ActionScriptVoid( "UCSetRemakeMoney" );
}
//===============================================================================================================
event CallAsChangeMode( int remakeMode )
{
	ActionScriptVoid( "UCChangeMode" );
}
//===============================================================================================================
//===============================================================================================================
final native function ASRemakeConfirm();
final native function ChangeMode( INT newMode, bool isFromAS );
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	_CurRemakeType=EReMkTp_Medicine
	//_ConsumptionIDForRemakeBook=111001
	//_FeeForRemakeBook=10
	//_ConsumptionCntForRemakeBook=10
}
