class MMOUIDamageNumberLevel extends MMOUIBase
	native(UI);

var int LastExp;
var int LastMaxExp;

var int LastMoney;

var array<int> IsMoneyVisible;


event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
	
}

function InitWidget()
{
	InitInfo();
}

native function InitInfo();

event InitOnce()
{
	super.InitOnce();
	class'MMOUIManager'.static.SetShowAttackNumberDelegate(ShowAttackNumber);
	class'MMOUIManager'.static.SetShowAttackedNumberDelegate(ShowAttackedNumber);
	class'MMOUIManager'.static.SetShowDodgeDelegate(ShowDodge);
	class'MMOUIManager'.static.SetShowMissDelegate(ShowMiss);
	class'MMOUIManager'.static.SetShowParryDelegate(ShowParry);
	class'MMOUIManager'.static.SetShowImmunityDelegate(ShowImmunity);
	class'MMOUIManager'.static.SetShowCriticalNumberDelegate(ShowCriticalNumber);
	class'MMOUIManager'.static.SetShowCriticaledNumberDelegate(ShowCriticaledNumber);
	class'MMOUIManager'.static.SetShowBlockNumberDelegate(ShowBlockNumber);
	class'MMOUIManager'.static.SetShowExpNumberDelegate(ShowExpNumber);
	class'MMOUIManager'.static.SetShowHPRestoreDelegate(ShowHPRestore);
	class'MMOUIManager'.static.SetShowGetMoneyDelegate(ShowGetMoney);

}


event  CallUpdatePos(float DeltaTime)
{
	ActionScriptVoid("UpdatePos");
}


native function ShowAttackNumber( int PosX , int PosY , int Number, Vector Location );
native function ShowAttackedNumber( int PosX , int PosY , int Number, Vector Location); 
native function ShowDodge( int PosX , int PosY, int Number, Vector Location);
native function ShowMiss( int PosX , int PosY, Vector Location);
native function ShowParry( int PosX , int PosY, Vector Location);
native function ShowImmunity( int PosX , int PosY, Vector Location);
native function ShowCriticalNumber( int PosX , int PosY , int Number, Vector Location);
native function ShowCriticaledNumber( int PosX , int PosY , int Number, Vector Location);
native function ShowBlockNumber( int PosX , int PosY , int Number, Vector Location);
native function ShowExpNumber( int PosX , int PosY , int Number, Vector Location);
native function ShowHPRestore( int PosX , int PosY , int Number, Vector Location);
native function ShowGetMoney( int PosX , int PosY , int Number , int MoneyType , Vector Location);

native function SetDamageShowPara( String FunctionName , int PosX , int PosY , Vector Location);
native function SetValueDamageShowPara( String FunctionName , int PosX , int PosY , int Number , Vector Location);

native function PlayerExpChange( int CurrentExp, int MaxExp,INT ChangeExp );
native function PlayerMoneyChange( EMONEY_TYPE MoneyType, int DeltaMoney);


native function ASSetPos3DTo2D(GFxObject mc, float PosX, float PosY, float PosZ );
native function ASSetTweenData(GFxObject DataObj, string TweenName );
native function BeforeViewUpdate( float DeltaTime );

DefaultProperties
{
	DefaultVisible=true
	LastExp=0
	LastMaxExp=0
	LastMoney=0
	CloseOnEsc=false
}
