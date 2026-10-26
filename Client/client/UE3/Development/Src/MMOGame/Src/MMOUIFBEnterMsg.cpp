#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "TeamManager.h"

IMPLEMENT_CLASS(UMMOUIFBEnterMsg)

void UMMOUIFBEnterMsg::NoticeFBEnter( const FString& mapName, INT linkID, INT iCurDiff )
{
	bool bDataChange = false;
	//save date
	FBEntranceLinkID	= linkID;
	FBEntranceMapName	= mapName;
	CurDiff				= iCurDiff;

	UpdateCurFBInfo();
	//
	UpdateMemberStatus();
}
//
void UMMOUIFBEnterMsg::UpdateCurFBInfo()
{

	FTeleportLink *pFBTelepLink = UGlobalMapInfo::GetSingleton()->FindLinkByMapAndID( FBEntranceMapName, FBEntranceLinkID );
	if( pFBTelepLink == NULL ){
		return;
	}
	//
	FExportMap FBToMapInfo = UGlobalMapInfo::GetSingleton()->FindMapInfoByName( pFBTelepLink->ToMapName );
	//
	tF_FBMsgMapName->SetText( FBToMapInfo.MapDisplayName );
	//
	tf_FBMsgCurrentDiff->SetText( appItoa( CurDiff ) );
	//
	tF_FBMsgLvRequired->SetText( appItoa( FBToMapInfo.MinPlayerLevel ) );
	//
	//tF_FBMsgRecmmend->SetText( FBToMapInfo.PlayerNum );
	//
	//tF_FBMsgDescrible->SetText( FBToMapInfo.MapDescript );
	////map background
	//FString strImg;
	//strImg = FString::Printf( TEXT("img://MMO_UIImg.%s_%s"), *FBEntranceMapName, *( pFBTelepLink->From.Name ) );
	//FBMsgImg_mc->SetString( "source", strImg );
	////FB boss image
	//if( FBToMapInfo.FinishTarget != NULL ){
	//	strImg = FString::Printf( TEXT("img://MMO_UIImg.Boss_%d"), FBToMapInfo.FinishTarget->GetTemplateID() );
	//	FBMsgMonsterImg_mc->SetString( "source", strImg );
	//}
}
//
void UMMOUIFBEnterMsg::UpdateTeamMate(INT UIPos, INT Pos )
{
	//if( IsVisible ){
	//	UpdateMemberStatus();
	//}
}
//
void UMMOUIFBEnterMsg::UpdateMemberStatus()
{
	
	if( TeamManager::getSingleton().HasTeam() == false){
		return;
	}
	INT iMemCnt = TeamManager::getSingleton().GetTeamMemberCount();
	INT showMemberIdx = 0;
	AMMOPlayer *pMe = MMOFacade::getSingleton().GetMainPlayer();
	if( pMe == NULL ){
		return;
	}

	for( int i = 0; i < iMemCnt && showMemberIdx < UCONST_FB_MEMBER_CNT; ++i )
	{
		MMOTeamMember* mem = TeamManager::getSingleton().GetTeamMember(i);
		if( mem == NULL || mem->ActorServerId == pMe->ServerID )
		{
			continue;
		}

		mc_FBMsgMember[showMemberIdx]->SetVisible( true );		
		mc_FBMsgMember[showMemberIdx]->GetObject( "tf_name" )->SetText( mem->ActorName );
		
		INT iPortrait = mem->ClassId;
		mc_FBMsgMember[showMemberIdx]->GetObject( "mc_portriat" )->GotoAndStopI( iPortrait );
		//
		INT iStatus = 2;
		INT iMemID = mem->ActorServerId;
		for( int j = 0; j < curPrepared; ++j )
		{
			if( prepareMemID[j] == iMemID )
			{
				iStatus = 1;
				break;
			}
		}
		iStatus = mem->Online ? iStatus : 3;
		mc_FBMsgMember[showMemberIdx]->GetObject( "mc_status" )->GotoAndStopI( iStatus );

		++showMemberIdx;
		/*
		INT iStatus = Player->TeamManager->TeamMemberList(i).bFBprepared ? 1 : 2;
		iStatus = Player->TeamManager->TeamMemberList(i).Online ? iStatus : 3;
		mc_FBMsgMember[i]->GetObject( "mc_status" )->GotoAndStopI( iStatus );
		*/
	}
	for( int i = showMemberIdx; i < UCONST_FB_MEMBER_CNT; ++i ){
		mc_FBMsgMember[i]->SetVisible( false );
	}
}
//------------------------------------------------------------------------
void UMMOUIFBEnterMsg::PrepareEnter()
{
	//CMessageHandler::GetInstance().Send_PrepareEnterFB();
}
//------------------------------------------------------------------------
void UMMOUIFBEnterMsg::CancelPrepare()
{
	//CMessageHandler::GetInstance().Send_CancelPrepareFB();
}
//------------------------------------------------------------------------
void UMMOUIFBEnterMsg::ResponsePrepareEnter()
{
	TogglePrepare();
}
//------------------------------------------------------------------------
void UMMOUIFBEnterMsg::ResponseCancelPrepare()
{
	TogglePrepare();
}
//
UBOOL UMMOUIFBEnterMsg::TogglePrepare()
{
	bPrepared = !bPrepared;
	btn_Prepare->SetBool( "enabled", !bPrepared );
	btn_CancelPrepare->SetBool( "enabled", bPrepared );
	return bPrepared;
}