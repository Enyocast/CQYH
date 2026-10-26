class MMOUIRemakeBook extends MMOUIBase
	config(MMOGame)
	native(UI);

var config int _ConsumptionIDForRemakeBook;
var config int _ConsumptionCntForRemakeBook;
//var int _FeeForRemakeBook;

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
//===============================================================================================================
final native function ASRemakeBookConfirm();
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//_ConsumptionIDForRemakeBook=111001
	//_FeeForRemakeBook=10
	//_ConsumptionCntForRemakeBook=10
}
