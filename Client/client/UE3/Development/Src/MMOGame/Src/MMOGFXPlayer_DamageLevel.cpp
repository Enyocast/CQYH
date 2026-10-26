#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_DamageLevel)



void UMMOGFXPlayer_DamageLevel::Init()
{
	Super::Init();

	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_DamageLevel);
}

void UMMOGFXPlayer_DamageLevel::PostAdvance ( FLOAT DeltaTime )
{
	UGFxMoviePlayer::PostAdvance(DeltaTime);

	//if(DamageLevel){
	//	DamageLevel->eventCallUpdatePos(DeltaTime);
	//}
}

//--------------------------------------------------------------------------------------------------------

//void UMMOGFXPlayer_DamageLevel::ASSetPos3DTo2D(class UGFxObject* mc, FLOAT PosX, FLOAT PosY, FLOAT PosZ )
//{
//	if(mc){
//		FVector2D ScreenPos;
//		UBOOL suc = MMOFacade::getSingleton().GetScreenPixelFromWorld( FVector(PosX,PosY,PosZ) , ScreenPos );
//		if(suc){
//			//FLOAT dynamicX = mc->GetFloat(TEXT("dynamicX"));//  >SetInt(TEXT("x"),INT(ScreenPos.X+0.5));
//
//			mc->SetInt(TEXT("x"),INT(ScreenPos.X+0.5));
//			mc->SetInt(TEXT("y"),INT(ScreenPos.Y+0.5));
//		}
//	}
//}

//
//void UMMOGFXPlayer_DamageLevel::FormatTweenData(class UGFxObject* DataObj, struct TweenData* pTweenData )
//{
//	if(DataObj && pTweenData){
//		
//		DataObj->SetBool("isEnable",TRUE);
//
//		DataObj->SetFloat("sx",pTweenData->sx);
//		DataObj->SetFloat("sy",pTweenData->sy);
//		DataObj->SetFloat("sz",pTweenData->sz);
//	
//		DataObj->SetFloat("vx",pTweenData->vx);
//		DataObj->SetFloat("vy",pTweenData->vy);
//		DataObj->SetFloat("vz",pTweenData->vz);
//
//		DataObj->SetFloat("ax",pTweenData->ax);
//		DataObj->SetFloat("ay",pTweenData->ay);
//		DataObj->SetFloat("az",pTweenData->az);
//
//		DataObj->SetFloat("sxRange",pTweenData->sxRange);
//		DataObj->SetFloat("syRange",pTweenData->syRange);
//		DataObj->SetFloat("szRange",pTweenData->szRange);
//
//		DataObj->SetFloat("vxRange",pTweenData->vxRange);
//		DataObj->SetFloat("vyRange",pTweenData->vyRange);
//		DataObj->SetFloat("vzRange",pTweenData->vzRange);
//
//		DataObj->SetFloat("axRange",pTweenData->axRange);
//		DataObj->SetFloat("ayRange",pTweenData->ayRange);
//		DataObj->SetFloat("azRange",pTweenData->azRange);
//
//		DataObj->SetFloat("scaleStart"	,pTweenData->scaleStart);
//		DataObj->SetFloat("scaleBomb"	,pTweenData->scaleBomb);
//		DataObj->SetFloat("scaleEnd"	,pTweenData->scaleEnd);
//
//		DataObj->SetFloat("scaleStartRange"	,pTweenData->scaleStartRange);
//		DataObj->SetFloat("scaleBombRange"	,pTweenData->scaleBombRange);
//		DataObj->SetFloat("scaleEndRange"	,pTweenData->scaleEndRange);
//
//		DataObj->SetFloat("durTime"		,pTweenData->durTime);
//		DataObj->SetFloat("bombTime"	,pTweenData->bombTime);
//		
//		DataObj->SetFloat("dumping"		,pTweenData->dumping);
//
//		DataObj->SetFloat("alphaStart"	,pTweenData->alphaStart);
//		DataObj->SetFloat("alphaBomb"	,pTweenData->alphaBomb);
//		DataObj->SetFloat("alphaEnd"	,pTweenData->alphaEnd);
//		DataObj->SetFloat("alphaPow"	,pTweenData->alphaPow);
//		DataObj->SetFloat("isVisible"	,pTweenData->isVisible);
//
//		TArray<	FASValue> val;
//		DataObj->Invoke("InitData", val);
//	}
//}
//void UMMOGFXPlayer_DamageLevel::ASSetTweenData(class UGFxObject* DataObj, const FString& TweenName )
//{
//	if(DataObj){
//		TweenData* pTweenData = MMOFacade::getSingleton().GetTweenData(TweenName);
//		FormatTweenData(DataObj,pTweenData);
//	}
//}
