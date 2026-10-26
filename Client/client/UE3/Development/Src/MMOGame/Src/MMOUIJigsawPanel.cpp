#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOStats.h"
#include "UMMOUIJigsawPanel.h"
#include "MMOMsgBoxManager.h"
#include "MMOJigsawManager.h"

IMPLEMENT_CLASS(UMMOUIJigsawPanel)

void UMMOUIJigsawPanel::Init()
{

}

void UMMOUIJigsawPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	if (v && GFXPlayer)
	{
		UTexture2D *tex = NULL;
		TCHAR szTemp[64]=TEXT("");
		tex = MMOJigsawManager::getSingleton().GetJigsawTexture();
		if (tex)
		{
			GFXPlayer->SetExternalTexture("Jigsaw_Source_alpha__nopack",tex);
		}

		INT i;
		for (i=0;i<JIGSAW_ANSWER_COUNT;i++)
		{
			tex = MMOJigsawManager::getSingleton().GetAnswerTexture(i);
			if (tex)
			{
				appSprintf(szTemp , TEXT("Jigsaw_Part_%d__nopack"),i+1);
				GFXPlayer->SetExternalTexture(szTemp , tex);
			}
		}

		UINT32 countingDownTime = MMOJigsawManager::getSingleton().GetDeadLineTime() - MMOFacade::getSingleton().GetRealClientUTCTime();
		countingDownTime = countingDownTime < 0 ? 0: countingDownTime;
		eventCallSetJigsawCountingDown(countingDownTime);

		UINT8 blockx,blocky;
		MMOJigsawManager::getSingleton().GetBlockOffset(blockx,blocky);
		eventCallSetJigsawBlockOffSet(blocky * 4 *2  , blockx * 4 * 2 );//change x y.

		MMOJigsawManager::getSingleton().RemoveMessageButtionBar();
	}
}

 void UMMOUIJigsawPanel::ASOnConfirmSelectedPart(INT answer)
 {
	 MMOJigsawManager::getSingleton().OnSelectAnswer((UINT8)answer); 
	 MMOUI::GetUIManager()->ShowPanelEx( MMOUI::GetUIManager()->Panel_Jigsaw , FALSE, "" );
 }
