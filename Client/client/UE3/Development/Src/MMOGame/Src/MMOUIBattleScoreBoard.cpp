#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOBattleManager.h"

IMPLEMENT_CLASS(UMMOUIBattleScoreBoard)

void UMMOUIBattleScoreBoard::PostOnShow(UBOOL show)
{
	Super::PostOnShow(show);
}

//
void UMMOUIBattleScoreBoard::UpdateScore( BYTE teamID )
{
	enumBattleTeamSide teamSide = (enumBattleTeamSide)teamID;

	if( teamID >= EBTLTMS_MAX ){
		return;
	}

	MMOBattleManager *pBattleMgr = &MMOBattleManager::getSingleton();
	INT score = pBattleMgr->GetBattleTeamScore( teamID );
	//INT totalScore = pBattleMgr->GetEnteredBattle()->ScoreDesc.ScoreToWin;

	//FString strScore;
	//strScore = FString::Printf( TEXT("%d / %d"), score, totalScore );
	//TeamScoreTf[teamSide]->SetText( strScore );
	//TeamScoreMc[teamSide]->SetText( appItoa( score ) );

	eventUCSetScore( teamID, score );
}

//
void UMMOUIBattleScoreBoard::ResetShow()
{
	//TeamScoreMc[EBTLTMS_Team0]->SetText( TEXT("") );
	//TeamScoreMc[EBTLTMS_Team1]->SetText( TEXT("") );
	eventUCSetScore( EBTLTMS_Team1, 0 );
	eventUCSetScore( EBTLTMS_Team2, 0 );

	BattleTimeMC->SetVisible( FALSE );
}

//
UBOOL UMMOUIBattleScoreBoard::IsTimeCountDown()
{
	UBOOL isCountingDown = FALSE;// = this->GetBool( TEXT("IsInitTime") );
	if( BattleTimeMC != NULL ){
		isCountingDown = isCountingDown && BattleTimeMC->GetBool( TEXT("visible") );
	}
	return isCountingDown;
}
//
void UMMOUIBattleScoreBoard::Init()
{
	Super::Init();

	InitMc();

	ResetShow();
}

void UMMOUIBattleScoreBoard::InitMc()
{	
	//TeamScoreMc[EBTLTMS_Team1] = GetObject( "TeamScore_mc1" );
	//TeamScoreMc[EBTLTMS_Team2] = GetObject( "TeamScore_mc2" );

	BattleTimeMC = GetObject( TEXT("BattleTime_mc") );
}

//===============================================================================================================
//===============================================================================================================
UBOOL UMMOUIBattleScoreBoard::SkipCaptureInputKey(const FString& key,BYTE eIE,const FString& strHoverControllerName,FVector2D ClickPosInMovieSpace)
{
	if( IsVisible && (strHoverControllerName == TEXT("BtlScoreBoardPanel_mc") || strHoverControllerName == TEXT("minute_mc") 
		|| strHoverControllerName == TEXT("second_mc") || strHoverControllerName == TEXT("timeGap_mc") ) ){
			return TRUE;
	}

	return Super::SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}
//===============================================================================================================
//===============================================================================================================