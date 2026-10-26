class MMOVolume_PawnTracking extends MMOVolume_Interactable
	native;

var array< Pawn >   PawnArray;

simulated event PawnEnteredVolume( Pawn Other )
{
	PawnArray.AddItem( Other );
}

simulated event PawnLeavingVolume( Pawn Other )
{
	if( PawnArray.Find( Other ) != INDEX_NONE )
		PawnArray.RemoveItem( Other );
}

DefaultProperties
{
}
