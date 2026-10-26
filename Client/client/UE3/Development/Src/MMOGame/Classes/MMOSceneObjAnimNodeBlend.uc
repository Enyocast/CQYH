class MMOSceneObjAnimNodeBlend extends AnimNodeBlendList;

function bool IsPlayingAnim( )
{
	local AnimNodeSequence animNode;
	animNode = AnimNodeSequence( Children[ActiveChildIndex].Anim );
	return( animNode.GetTimeLeft( ) >= 0.01f );
}

function float GetAnimLength( int idx )
{
	if( idx < 0 || idx >= Children.Length )
		return 0.f;
	return AnimNodeSequence( Children[idx].Anim ).GetAnimPlaybackLength( );
}

DefaultProperties
{
	Children(0)=(Name="Idle")
	Children(1)=(Name="Prepare")
	Children(2)=(Name="Activated")
	Children(3)=(Name="Stand")
	Children(4)=(Name="Back")

	bFixNumChildren=TRUE
	CategoryDesc="MMO"
	NodeName="SceneObjAnimBlend"
}
