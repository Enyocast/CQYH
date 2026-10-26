class MMOVolume_Interactable extends PhysicsVolume
	dependson( MMOSceneInteractableObj )
	native;

var bool    m_bIsVolumeEnabled;

function EnableVolume( )
{
	m_bIsVolumeEnabled = true;
}

function DisableVolume( )
{
	m_bIsVolumeEnabled = false;
}

function Update( float DeltaTime )
{
	if( m_bIsVolumeEnabled )
	{
		UpdateImp( DeltaTime );
	}
}

protected function UpdateImp( float DeltaTime )
{
}

DefaultProperties
{
	//bCollideActors=false
	m_bIsVolumeEnabled=false
}
