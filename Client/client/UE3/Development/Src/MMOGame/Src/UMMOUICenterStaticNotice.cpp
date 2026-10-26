#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOUICenterStaticNotice)

void UMMOUICenterStaticNotice::PostOnShow( UBOOL v )
{
	Super::PostOnShow(v);
	if( v ){
	}
}

void UMMOUICenterStaticNotice::OnNativeGameEvent( struct MMOGameEvent* gameEvent )
{
}

UBOOL UMMOUICenterStaticNotice::SkipCaptureInputKey( const FString &key, BYTE eIE, const FString &strHoverControllerName, FVector2D ClickPosInMovieSpace )
{
	if( IsVisible ){
		if(	strHoverControllerName==TEXT("tf_content") ){
			return TRUE;
		}
	}

	return Super::SkipCaptureInputKey( key, eIE, strHoverControllerName, ClickPosInMovieSpace );
}

void UMMOUICenterStaticNotice::Init()
{
	Super::Init();
}