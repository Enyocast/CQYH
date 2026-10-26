#include "stdafx.h"
#include "MMOGameClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOBattleTemplate)

FBattleTemplate *UMMOBattleTemplate::FindBattleTemplateBy( INT battleID )
{
	INT cnt = BattleTemplateList.Num();
	//FBattleTemplate battleRtn;

	for( INT i = 0; i < cnt; ++i ){
		if( BattleTemplateList(i).ID == battleID ){
			//LastFindBattleIdx = i;
			return &BattleTemplateList(i);
		}
	}

	return NULL;
}
//------------------------------------------------------------------------------------
FBattleTemplate *UMMOBattleTemplate::GetBattleTemplateIn( INT idx )
{
	INT cnt = BattleTemplateList.Num();
	//FBattleTemplate battleRtn;

	if( idx >= 0 && idx < cnt ){
		return &BattleTemplateList( idx );
	}

	return NULL;
}
//------------------------------------------------------------------------------------
INT UMMOBattleTemplate::GetBattleTemplateCnt()
{
	INT cnt = BattleTemplateList.Num();

	return cnt;
}
//------------------------------------------------------------------------------------
void UMMOBattleTemplate::RevertSelected()
{
	INT cnt = BattleTemplateList.Num();
	//FBattleTemplate battleRtn;

	for( INT i = 0; i < cnt; ++i ){
		BattleTemplateList(i).IsSelected = FALSE;//TRUE;
	}
}
////
////
//void UMMOBattleTemplate::AddBattleTemplate( FBattleTemplate battle )
//{
//	BattleTemplateList.Push( battle );
//}
////
//void UMMOBattleTemplate::ClearBattleTemplates()
//{
//	BattleTemplateList.Empty();
//}