#include "stdafx.h"

void AMMOVolume_AmbientMusic::PlayTrack()
{
	AWorldInfo *WorldInfo = GWorld->GetWorldInfo();
	if (WorldInfo != NULL)
	{
		WorldInfo->UpdateMusicTrack(MusicTrack);
	}
}

void AMMOVolume_AmbientMusic::StopPlayTrack()
{
	AWorldInfo *WorldInfo = GWorld->GetWorldInfo();
	if (WorldInfo != NULL && WorldInfo->MusicComp != NULL)
	{
		// 只能停止与自己一样的，不一样的话应该是被其它Volume或是KISMET重载掉了
		if(WorldInfo->MusicComp->SoundCue == MusicTrack.TheSoundCue)
		{
			WorldInfo->MusicComp->FadeOut(0.5f, 0);
		}
	}
	//AWorldInfo *WorldInfo = GWorld->GetWorldInfo();
	//if (WorldInfo != NULL && MusicTrack.TheSoundCue)
	//{
	//	FString SoundCueName;
	//	MusicTrack.TheSoundCue->GetName(SoundCueName);
	//	WorldInfo->ClearAcrossLevelMusicByCueName(SoundCueName);
	//}
}