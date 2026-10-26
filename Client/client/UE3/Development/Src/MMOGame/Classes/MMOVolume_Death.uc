class MMOVolume_Death extends PhysicsVolume
	native;

simulated event PawnEnteredVolume( Pawn Other )
{
	local MMOActor p;
	p = MMOActor( Other );
	if( p != none && p.ActorAttributes.GetCurHp() >= 0 )
	{
		p.TakeDamage( 100000, none, vect(0,0,0), vect(0,0,0), class'DmgType_Fell' );
		`Log( "[MMO_Debug]Kill actor: "@Other );
	}
}

DefaultProperties
{
}
