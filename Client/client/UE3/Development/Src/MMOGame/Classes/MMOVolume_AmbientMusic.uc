//
// 环境音乐体积
// 进入体积后播放相应音乐
//

class MMOVolume_AmbientMusic extends Volume
	native
	placeable;

var() bool StopWhenUnTouch <DisplayName="出框后停止播放">;

var() MusicTrackStruct MusicTrack;
native final function PlayTrack();
native final function StopPlayTrack();

simulated event Touch( Actor Other, PrimitiveComponent OtherComp, vector HitLocation, vector HitNormal )
{
	Super.Touch(Other, OtherComp, HitLocation, HitNormal);

	if(class'Engine'.static.IsEditor() || (MMOActor(Other) != none && MMOActor(Other).IsMainPlayer()))
	{
		PlayTrack();
	}
}

event UnTouch(Actor Other)
{
	super.UnTouch(Other);
	
	if(StopWhenUnTouch && Pawn(Other) != none && MMOActor(Other).IsMainPlayer())
	{
		StopPlayTrack();
		//OnActive(Pawn(Other), false);
	}
}

defaultproperties
{
	bStatic=False
}

/*
//var(MMO) AudioComponent AmbientAudioComponent <DisplayName="音乐播放组件">;
//var(MMO) float FadeInDuration <DisplayName="淡入音乐时间(秒)">;
//var(MMO) float FadeOutDuration <DisplayName="淡出音乐时间(秒)">;
//var(MMO) float FadeInVolumeLevel <DisplayName="淡入音量百分比">;
//var(MMO) float FadeOutVolumeLevel <DisplayName="淡出音量百分比">;

//var(MMO) array< AudioComponent >    AlterAudioComps <DisplayName="动态音效列表">;

//var      AudioComponent             CurrAudioComp;

simulated event PawnEnteredVolume(Pawn P)
{
	super.PawnEnteredVolume(P);
	PlayTrack();
	//StartPlaying();
}

simulated event PawnLeavingVolume(Pawn P)
{	
	super.PawnLeavingVolume(P);
	//StopPlaying();
}

simulated event PhysicsChangedFor(Actor Other)
{
	//`log("@@@@@@@@@@@@@ PhysicsChangedFor == " @Other.Physics);
	super.PhysicsChangedFor(Other);
}


simulated function StartPlaying()
{
// 	AmbientAudioComponent.FadeIn( FadeInDuration, FadeInVolumeLevel );	
// 	CurrAudioComp = AmbientAudioComponent;
}

simulated function StopPlaying()
{
// 	CurrAudioComp.FadeOut( FadeOutDuration, FadeOutVolumeLevel );
// 	CurrAudioComp = none;
}

event ChangeAudio( int Idx, float FadeOutTime, float FadeInTime )
{
// 	if( idx < -1 || idx >= AlterAudioComps.Length )
// 	{
// 		`Log( "[MMO Error] Audio index out of range." );
// 		return;
// 	}
// 	if( CurrAudioComp != none )
// 	{
// 		CurrAudioComp.FadeOut( fadeOutTime, 0.f );
// 	}
// 	if( idx == -1 )
// 		CurrAudioComp = AmbientAudioComponent;
// 	else
// 		CurrAudioComp = AlterAudioComps[idx];
// 	CurrAudioComp.FadeIn( fadeInTime, 1.f );
}

defaultproperties
{
// 	Begin Object Class=AudioComponent Name=AudioComponent0
// 	End Object
// 	Components.Add(AudioComponent0)
// 	AmbientAudioComponent=AudioComponent0
// 
// 	FadeInDuration=3
// 	FadeOutDuration=3
// 	FadeInVolumeLevel=1.f
// 	FadeOutVolumeLevel=0.f

}

*/