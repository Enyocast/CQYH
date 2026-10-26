#include "SoundMatEditState_Footstep.h"
#include "../../Engine/Inc/EngineClasses.h"
#include "../../Engine/Inc/EngineMeshClasses.h"
#include "../../Engine/Inc/EngineAnimClasses.h"
#include "../../Engine/Inc/EngineAIClasses.h"
#include "../../GameFramework/Inc/GameFrameworkClasses.h"
#include "../../MMOGame/Inc/MMOGameClasses.h"

#include "SoundMatEditState_Footstep.h"
#include "UnLinkedObjDrawUtils.h"
#include "SoundMaterialMatrix.h"

SoundMatEditState_Footstep::SoundMatEditState_Footstep( SoundMaterialMatrix* ed )
: SoundMaterialEditState(ed)
{
	BodyEnumObj = FindObject<UEnum>(UPhysicalMaterialProperty::StaticClass(), TEXT("EBodyType"), TRUE);
	LandEnumObj = FindObject<UEnum>(UPhysicalMaterialProperty::StaticClass(), TEXT("EPhyMatType"), TRUE);

	HighlightObject = 0;
	SelectedObject = 0;
}
//------------------------------------------------------------------------
SoundMatEditState_Footstep::~SoundMatEditState_Footstep()
{

}
//------------------------------------------------------------------------
void SoundMatEditState_Footstep::DrawObjects( FViewport* Viewport, FCanvas* Canvas )
{
	if(!BodyEnumObj || !LandEnumObj)
	{
		return;
	}

	for (INT i = 0; i < LandEnumObj->NumEnums() - 1; ++i)
	{
		FLinkedObjDrawUtils::DrawTitleBar(Canvas, 
			FIntPoint(i * (DRAW_BLOCK_SIZE + DRAW_BLOCK_SPACE) + DRAW_X_OFFSET,
			DRAW_Y_OFFSET - DRAW_BLOCK_SIZE - DRAW_BLOCK_SPACE),
			FIntPoint(DRAW_BLOCK_SIZE, DRAW_BLOCK_SIZE), BorderColor,FColor(255,255,128 ), BkgColor,
			*GetEnumDisplayName(LandEnumObj, i), TArray<FString>());
	}

	for (INT i = 0; i < BodyEnumObj->NumEnums() - 1; ++i)
	{
		FLinkedObjDrawUtils::DrawTitleBar(Canvas, 
			FIntPoint(DRAW_X_OFFSET - DRAW_BLOCK_SIZE - DRAW_BLOCK_SPACE,
				i * (DRAW_BLOCK_SIZE + DRAW_BLOCK_SPACE) + DRAW_Y_OFFSET),
			FIntPoint(DRAW_BLOCK_SIZE, DRAW_BLOCK_SIZE), BorderColor, FColor(255,255,128),BkgColor,
			*GetEnumDisplayName(BodyEnumObj, i), TArray<FString>());
	}

	for (INT x = 0; x < EPMAT_MAX; ++x)
	{
		for (INT y = 0; y < EBDT_MAX; ++y)
		{
			INT idx = x * EBDT_MAX + y;

			UMMOFootstepMaterialEditObject* EditProxyObject = FootstepObjectList(idx);
			if(Canvas->IsHitTesting())
			{
				Canvas->SetHitProxy(new HAnyObjectProxy(EditProxyObject, (int)ETO_FootstepSounds, 0));
			}

			FColor tBorderColor = BorderColor;
			FColor tBkgColor = BkgColor;

			if(!EditProxyObject->EffectNode.Particle && !EditProxyObject->EffectNode.Sound)
			{
				tBkgColor = WhiteColor;
			}
			else if(EditProxyObject->EffectNode.Particle && EditProxyObject->EffectNode.Sound)
			{
				tBkgColor = GreenColor;
			}
			else if(EditProxyObject->EffectNode.Particle || EditProxyObject->EffectNode.Sound)
			{
				tBkgColor = YellowColor;
			}


			if((SelectedObject == EditProxyObject) || (HighlightObject == EditProxyObject))
			{
				tBorderColor = RedColor;
			}
			else
			{
				tBorderColor = BorderColor;
			}

			FLinkedObjDrawUtils::DrawTitleBar(Canvas,
				FIntPoint(DRAW_X_OFFSET + x * (DRAW_BLOCK_SIZE + DRAW_BLOCK_SPACE),
				DRAW_Y_OFFSET + y * (DRAW_BLOCK_SIZE + DRAW_BLOCK_SPACE)),
				FIntPoint(DRAW_BLOCK_SIZE, DRAW_BLOCK_SIZE),
				tBorderColor, FColor(255,255,128),tBkgColor, TEXT(""), TArray<FString>());

			if(Canvas->IsHitTesting())
			{
				Canvas->SetHitProxy(0);
			}

		}
	}


	Canvas->PushAbsoluteTransform(FMatrix::Identity);
	
	INT msX = SoundMaterialEditor->LinkedObjVC->OldMouseX;
	INT msY = SoundMaterialEditor->LinkedObjVC->OldMouseY;
	UINT szX = SoundMaterialEditor->LinkedObjVC->Viewport->GetSizeX();
	UINT szY = SoundMaterialEditor->LinkedObjVC->Viewport->GetSizeY();
	
	DrawLine2D(Canvas, FVector2D(0, msY), FVector2D(szX, msY), FLinearColor(0, 0, 128));
	DrawLine2D(Canvas, FVector2D(msX, 0), FVector2D(msX, szY), FLinearColor(0, 0, 128));

	if(HighlightObject)
	{
		FString tipMsg = FString::Printf( TEXT("%s -> %s"),
			*GetEnumDisplayName(BodyEnumObj, HighlightObject->ShapeType),
			*GetEnumDisplayName(LandEnumObj, HighlightObject->LandMatType));

		FLinkedObjDrawInfo drawInfo;
		drawInfo.ToolTips.AddItem(tipMsg);
		FLinkedObjDrawUtils::DrawToolTips(Canvas, drawInfo, FIntPoint(msX, msY), FIntPoint(100, 50));
	}

	Canvas->PopTransform();
}
//------------------------------------------------------------------------
void SoundMatEditState_Footstep::OnEnter()
{
	DestroyEditProxyObject();

	for (INT x = 0; x < EPMAT_MAX; ++x)
	{
		for (INT y = 0; y < EBDT_MAX; ++y)
		{
			UMMOFootstepMaterialEditObject* obj = Cast<UMMOFootstepMaterialEditObject>(
				UObject::StaticConstructObject(UMMOFootstepMaterialEditObject::StaticClass()));

			FFootstepEffectNode* node = FindEffectNodeObject(x, y);

			if(obj)
			{
				obj->ShapeType = y;
				obj->LandMatType = x;
				FootstepObjectList.AddItem(obj);

				if(node)
				{
					obj->EffectNode = node->EffectNode;
				}
			}
		}
	}
}
//------------------------------------------------------------------------
void SoundMatEditState_Footstep::OnExit()
{
	DestroyEditProxyObject();
}
//------------------------------------------------------------------------
void SoundMatEditState_Footstep::ClickedAnyObject( struct HAnyObjectProxy* proxy )
{
	if(proxy->ObjectTypeFlag == ETO_FootstepSounds)
	{
		SelectedObject = (UMMOFootstepMaterialEditObject*)proxy->AnyObject;
		if(SelectedObject)
		{
			SoundMaterialEditor->SetObjectToPropertyWindow(SelectedObject);

			FFootstepEffectNode* node = FindEffectNodeObject(SelectedObject->LandMatType, SelectedObject->ShapeType);

			// add new one if not found
			if(!node)				
			{
				FFootstepEffectNode NewNode(EC_EventParm);
				NewNode.ShapeType = SelectedObject->ShapeType;
				NewNode.LandMatType = SelectedObject->LandMatType;

				SoundMaterialEditor->GetDataManager()->FootstepEffectList.AddItem(NewNode);
				SoundMaterialEditor->MakePackageDirty();
			}
			else
			{
				if(SelectedObject->EffectNode.Particle || SelectedObject->EffectNode.Sound)
				{
					node->EffectNode = SelectedObject->EffectNode;
				}
				else
				{
					SelectedObject->EffectNode = node->EffectNode;
				}
			}
		}
	}
}
//------------------------------------------------------------------------
void SoundMatEditState_Footstep::HighlightAnyObject( struct HAnyObjectProxy* proxy )
{
	HighlightObject = 0;

	if(proxy && proxy->ObjectTypeFlag == ETO_FootstepSounds)
	{
		HighlightObject = (UMMOFootstepMaterialEditObject*)proxy->AnyObject;
	}
}
//------------------------------------------------------------------------
void SoundMatEditState_Footstep::DestroyEditProxyObject()
{
	FootstepObjectList.Empty();
}


//------------------------------------------------------------------------
void SoundMatEditState_Footstep::SaveData()
{
	SoundMaterialEditor->MakePackageDirty();
	for (INT x = 0; x < EPMAT_MAX; ++x)
	{
		for (INT y = 0; y < EBDT_MAX; ++y)
		{

			INT idx = x * EBDT_MAX + y;

			UMMOFootstepMaterialEditObject* obj = FootstepObjectList(idx);
			FFootstepEffectNode* targetObj = FindEffectNodeObject(x, y);
			check(obj);
			if(targetObj)
			{
				targetObj->EffectNode = obj->EffectNode;
			}
		}
	}
}

FString SoundMatEditState_Footstep::GetEnumDisplayName(UEnum* Obj, BYTE enumID )
{
	if (!Obj)
	{
		return FString(L"error");
	}

	FString EnumValueName = Obj->GetEnum(enumID).ToString();
	const FString& AlternateEnumValueName = Obj->GetMetaData( TEXT("DisplayName"), enumID );
	if ( AlternateEnumValueName.Len() == 0 )
	{
		FString LocalizedName = LocalizeProperty( *(Obj->GetName()), *(EnumValueName) );	

		if(LocalizedName.Len() > 0)
		{
			return LocalizedName;
		}
		else
		{
			return EnumValueName;
		}
	}
	else
	{
		FString LocalizedName = LocalizeProperty( *(Obj->GetName()), *(AlternateEnumValueName) );
		if(LocalizedName.Len() > 0)
		{
			return LocalizedName;
		}
		else
		{
			return AlternateEnumValueName;
		}
	}
}

FFootstepEffectNode* SoundMatEditState_Footstep::FindEffectNodeObject(BYTE LT, BYTE BT)
{
	UGamePlayDataManager* DataMgr = SoundMaterialEditor->GetDataManager();
	for (INT j = 0; j < DataMgr->FootstepEffectList.Num(); ++j)
	{
		FFootstepEffectNode& node = DataMgr->FootstepEffectList(j);
		if((node.ShapeType == BT) && (node.LandMatType == LT))
		{
			return &node;
		}
	}

	return 0;
}
