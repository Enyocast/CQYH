class MMOVolume_DynamicBlocking extends MMOVolume_Interactable
	native;

var( MMOVolume) bool    BlockWhenEnable     <DisplayName="BlockWhenEnable">;

function EnableVolume( )
{
	super.EnableVolume( );
	if( BlockWhenEnable )
		SetCollision( true, true );
	else
		SetCollision( true, false );
}

function DisableVolume( )
{
	super.DisableVolume( );
	if( BlockWhenEnable )
		SetCollision( true, false );
	else
		SetCollision( true, true );
}

protected function UpdateImp( float DeltaTime )
{
}

DefaultProperties
{
	BlockWhenEnable=true;
}
