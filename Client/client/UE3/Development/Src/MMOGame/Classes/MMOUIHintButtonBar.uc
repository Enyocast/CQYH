class MMOUIHintButtonBar extends MMOUIBase	
	native(UI);


event InitOnce()
{

	super.InitOnce();
	class'MMOUIManager'.static.SetAddNewHintButtonDelegate(AddNewButton);
	class'MMOUIManager'.static.SetRemoveHintButtonDelegate(RemoveButton);
}

native function int AddNewButton( string iconResouce , int time , bool add );
native function RemoveButton( int pos );

native function ASHintButtonClick( int id );

DefaultProperties
{
	CloseOnEsc=false
}
