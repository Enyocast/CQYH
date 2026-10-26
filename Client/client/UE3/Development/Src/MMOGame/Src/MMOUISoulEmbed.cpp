#include "MMOFacade.h"
#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "net/message_handler.h"
#include "ClientActionConditionCheck.h"
#include "MMOEquipManager.h"
#include "item_def.h"
#include "UITextParser.h"
#include "UILayout.h"
#include "MMOQuestManager.h"
#include "MMOGuideManager.h"
#include "MMOClientVariableManager.h"

IMPLEMENT_CLASS(UMMOUISoulEmbed)

void UMMOUISoulEmbed::PreOnShow(UBOOL show)
{
	Super::PreOnShow( show );

	if( IsInitialized == FALSE ){
		return;
	}

	//
	GrayAllInBagNoNeed( show );
	//
	if( show ){
		MMOGameEvent_Guide evtGuide(EGUET_ShowGemPanel);
		MMOUI::PostGameEvent(&evtGuide);
	}
	else{
		ResetUI();
	}
}

//========================================================================================
void UMMOUISoulEmbed::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if(evt == NULL){
		return;
	}

	switch(evt->GetEventType())
	{
	case GameEvent_SoulEmbed:
		{
			MMOGameEvent_OneInt *soulEmbedEvt = (MMOGameEvent_OneInt*)evt;

			if( IsVisible ){
				OnNotifySoulEmbed( soulEmbedEvt->IntData );
			}
		}
		break;
	case GameEvent_SoulUnEmbed:
		{
			MMOGameEvent_OneInt *soulUnEmbedEvt = (MMOGameEvent_OneInt*)evt;

			if( IsVisible ){
				OnNotifySoulUnEmbed( soulUnEmbedEvt->IntData );
			}
		}
		break;
	case GameEvent_Item_Delete:
		{
			MMOGameEvent_Item *itemDelEvt = (MMOGameEvent_Item*)evt;
			BagSlotChange( itemDelEvt->ContainerIdx, itemDelEvt->SlotIdx );
		}
		break;
	case GameEvent_BagSortEnd:
		{
			if( IsVisible ){
				GrayAllInBagNoNeed( TRUE );
			}
		}
		break;
	}
}

//========================================================================================================================================
void UMMOUISoulEmbed::GrayAllInBagNoNeed( UBOOL isToGray )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	if( Player == NULL ){
		return;
	}

	//
	//ESlotGrayMark markGrayType;
	switch( _CurType )
	{
	case ESOLPT_Embed:
		{
			GrayAllInBagNoNeedForSoulEmbed( isToGray );
		}
		break;
	case ESOLPT_Unembed:
		{
			GrayAllInBagNoNeedForSoulUnEmbed( isToGray );
		}
		break;
	case ESOLPT_LevelUp:
		{
			GrayAllInBagNoNeedForSoulLevelUp( isToGray );
		}
		break;
	default:
		return;
	}
}

//========================================================================================================================================
void UMMOUISoulEmbed::BagSlotChange( INT bagId, INT slotId )
{
	if( !IsVisible ){
		return;
	}

	switch( _CurType )
	{
	case ESOLPT_Embed:
		{
			BagSlotChangeOnSoulEmbed( bagId, slotId );
		}
		break;
	case ESOLPT_Unembed:
		{
			BagSlotChangeOnSoulUnEmbed( bagId, slotId );
		}
		break;
	case ESOLPT_LevelUp:
		{
			BagSlotChangeOnSoulLvUp( bagId, slotId );
		}
		break;
	default:
		warnf(NAME_Error, TEXT("======!!!!======= [BagSlotChange _CurType is WRONG]") );
		return;
	}

}

//========================================================================================================================================
void UMMOUISoulEmbed::ClearUI()
{

}

//========================================================================================================================================
void UMMOUISoulEmbed::PlayerMoneyChange(BYTE MoneyType, INT DeltaMoney)
{
	if( IsVisible && _CurType == ESOLPT_Unembed ){
		UpdateSoulUnEmbedFee();
	}
}
//========================================================================================================================================
//
UBOOL UMMOUISoulEmbed::OnLeftMousePress(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault) 
{ 
	if(bDefault)return FALSE;
	return FALSE; 
} 

UBOOL UMMOUISoulEmbed::OnLeftMouseClick(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault)
{
	if(bDefault)return FALSE;
	return FALSE;
}

UBOOL UMMOUISoulEmbed::OnRightMouseClick(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault)
{
	if(bDefault)return FALSE;

	UBOOL rtn = FALSE;
	switch( _CurType )
	{
	case ESOLPT_Embed:
		{
			rtn = OnRightMouseClickEmbed( mc, SlotType, ContainerID, SlotID, bDefault );
		}
		break;
	case ESOLPT_Unembed:
		{
			rtn = OnRightMouseClickUnEmbed( mc, SlotType, ContainerID, SlotID, bDefault );
		}
		break;
	case ESOLPT_LevelUp:
		{
			rtn = OnRightMouseClickLvUp( mc, SlotType, ContainerID, SlotID, bDefault );
		}
		break;
	}

	return rtn;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
UBOOL UMMOUISoulEmbed::OnDragDrop( class UGFxObject* srcSlotMC,class UGFxObject* destSlotMC,
									BYTE srcSlotType, BYTE srcContainerID, INT srcSlotID,
									BYTE destSlotType, BYTE destContainerID, INT destSlotID )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	if( destSlotMC == NULL || srcSlotMC == NULL ){
		return FALSE;
	}

	UBOOL rtn = FALSE;
	//从背包到融灵
	if( srcSlotType == ESPType_Bag ){
		//
		if( destSlotType == ESPType_SoulEmbed ){
			rtn = OnDragDropEmbed( srcSlotMC, destSlotMC, srcSlotType, srcContainerID, srcSlotID, destSlotType, destContainerID, destSlotID );
		}
		else if( destSlotType == ESPType_SoulUnEmbed ){
			rtn = OnDragDropUnEmbed( srcSlotMC, destSlotMC, srcSlotType, srcContainerID, srcSlotID, destSlotType, destContainerID, destSlotID );
		}
		else if( destSlotType == ESPType_SoulLevelUp ){
			rtn = OnDragDropLvUp( srcSlotMC, destSlotMC, srcSlotType, srcContainerID, srcSlotID, destSlotType, destContainerID, destSlotID );
		}
		else{
			rtn = FALSE;
		}

		return rtn;
	}
	else if( destSlotType == ESPType_Bag ){
		//拖回包裹，因为本来就没有真正的移动，所以不提供拖放到原始位置
		if( srcSlotType == ESPType_SoulEmbed ){
			rtn = OnDragDropEmbed( srcSlotMC, destSlotMC, srcSlotType, srcContainerID, srcSlotID, destSlotType, destContainerID, destSlotID );
		}
		else if( srcSlotType == ESPType_SoulUnEmbed ){
			rtn = OnDragDropUnEmbed( srcSlotMC, destSlotMC, srcSlotType, srcContainerID, srcSlotID, destSlotType, destContainerID, destSlotID );
		}
		else if( srcSlotType == ESPType_SoulLevelUp ){
			rtn = OnDragDropLvUp( srcSlotMC, destSlotMC, srcSlotType, srcContainerID, srcSlotID, destSlotType, destContainerID, destSlotID );
		}

		return rtn;
	}

	return FALSE;
}

//
void UMMOUISoulEmbed::ResetSoulEmbed()
{
	for( INT i = 0; i < MAX_EmbedSoul; ++i ){
		if( _ToEmbedSoul[i]._ConID >=0 || _ToEmbedSoul[i]._SlotID >= 0 ){
			UnSetSoulToEmbeInEquip( i );
		}
	}
	//
	SetSoulEmbedEquip( -1, -1 );

	////
	//_EmbedEquipPropSoulAdd.Empty();
	//_EmbedEquipPropBase.Empty();
	//_ToEmbeSoulPropAdd.Empty();
}


//
void UMMOUISoulEmbed::OnTabBtnClick( INT tabIdx )
{
	if( tabIdx == _CurType ){
		return;
	}

	//
	ResetPanel( _CurType );
	GrayAllInBagNoNeed( FALSE );

	//new
	_CurType = tabIdx;
	UpdatePanel();
	GrayAllInBagNoNeed( TRUE );
}

//=============================================================================================================================
void UMMOUISoulEmbed::UpdatePanel()
{
	_EmbedSoulPanel->SetVisible( FALSE );
	_UnEmbedSoulPanel->SetVisible( FALSE );
	_LvUpSoulPanel->SetVisible( FALSE );

	switch( _CurType )
	{
	case ESOLPT_Embed:
		{
			UpdateSoulEmbed();
			_EmbedSoulPanel->SetVisible( TRUE );
		}
		break;
	case ESOLPT_Unembed:
		{
			UpdateSoulUnEmbed();
			_UnEmbedSoulPanel->SetVisible( TRUE );
		}
		break;
	case ESOLPT_LevelUp:
		{
			UpdateSoulLevelUp();
			_LvUpSoulPanel->SetVisible( TRUE );
		}
		break;
	default:
		break;
	}

	//
	SetTitleName();
}

//---------------------------------------------------------
void UMMOUISoulEmbed::UpdatePanelTab()
{
	_EmbedSoulPanel->SetVisible( FALSE );
	_UnEmbedSoulPanel->SetVisible( FALSE );

	switch( _CurType )
	{
	case ESOLPT_Embed:
		{
			if( _EmbedTabBtn != NULL ){
				_EmbedTabBtn->SetBool( TEXT("selected"), TRUE );
			}
		}
		break;
	case ESOLPT_Unembed:
		{
			if( _UnEmbedTabBtn != NULL ){
				_UnEmbedTabBtn->SetBool( TEXT("selected"), TRUE );
			}
		}
		break;
	case ESOLPT_LevelUp:
		{
			if( _LvUpSoulPanel != NULL ){
				_LvUpSoulPanel->SetBool( TEXT("selected"), TRUE );
			}
		}
		break;
	default:
		break;
	}
}

//---------------------------------------------------------
void UMMOUISoulEmbed::ResetUI()
{
	//ClearSoulEmbedData();
	ResetSoulEmbed();
	ResetSoulUnEmbed();
	ResetSoulLevelUp();
	//
	_CurType = ESOLPT_Embed;
	UpdatePanelTab();
	UpdatePanel();
}
//---------------------------------------------------------
void UMMOUISoulEmbed::ResetPanel( INT tabIdx )
{
	switch( tabIdx )
	{
	case ESOLPT_Embed:
		{
			ResetSoulEmbed();
		}
		break;
	case ESOLPT_Unembed:
		{
			ResetSoulUnEmbed();
		}
		break;
	case ESOLPT_LevelUp:
		{
			ResetSoulLevelUp();
		}
		break;
	default:
		break;
	}
}
//=============================================================================================================================
//soul embed
void UMMOUISoulEmbed::GrayAllInBagNoNeedForSoulEmbed( UBOOL isToGray )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();
	if( Player == NULL ){
		return;
	}

	//
	UINT bagCapability = Player->ItemManager->CurCapacity( E_CONSLOT_DEFAULT );
	for( UINT j = 0; j < bagCapability; ++j){
		if( isToGray == FALSE ){
			mmoFacade.GrayItem( ESGMark_SoulEmbed, E_CONSLOT_DEFAULT, j, FALSE );
			continue;
		}

		//需要打灰
		const FClientItemInfo *pItemInfo = mmoFacade.FindItem( E_CONSLOT_DEFAULT, j );
		if( pItemInfo == NULL ){
			continue;
		}

		UItem *pItemInBag = mmoFacade.FindItemTemplate( pItemInfo->m_nTemplateID );
		if( pItemInBag == NULL ){
			continue;
		}


		UBOOL isNeedToGray = IsNeedToGrayOnSoulEmbed( pItemInBag, pItemInfo );
		mmoFacade.GrayItem( ESGMark_SoulEmbed, E_CONSLOT_DEFAULT, j, isNeedToGray );
	}
}

//
UBOOL UMMOUISoulEmbed::IsNeedToGrayOnSoulEmbed( UItem *pItemInBag, const FClientItemInfo *pItemInfo )
{
	if( pItemInBag == NULL || pItemInfo == NULL ){
		return FALSE;
	}

	//
	UBOOL noNeedToGray = FALSE;
	//是否是灵石
	const SoulInfo *pSoulInfo = MMOEquipManager::getSingleton().FindSoulInfoByItemTemplateID( pItemInfo->m_nTemplateID );
	noNeedToGray = ( pSoulInfo != NULL );
	//是否是有孔装备
	if( noNeedToGray != TRUE ){
		UEquip *pEmbedEquip = Cast<UEquip>( pItemInBag );
		if( pEmbedEquip != NULL ){
			//检查孔洞
			bool hasHole = false;
			//UINT8 *pSocketType = (UINT8 *)SOCKET_COMBINATION[pItemInfo->m_bySocketCombination];
			for(INT i = 0; i < MAX_SOCKET_COUNT; i++){
				if(pItemInfo->GetSocketType(i) != SOCKET_NONE){
					noNeedToGray = TRUE;
					break;
				}
			}
		}
	}

	return (!noNeedToGray);
}

//
UBOOL UMMOUISoulEmbed::OnRightMouseClickEmbed(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault)
{
	if(bDefault)return FALSE;

	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	//UBOOL rst = FALSE;

	switch( SlotType )
	{
	case ESPType_Bag:
		{
			//put in from bag
			FClientItemInfo *pItemInfo = mmoFacade.FindItem( ContainerID, SlotID );
			if( pItemInfo == NULL ){
				return TRUE;
			}

			//
			ClientActionCondition_SoulEmbedOrUnEmbed checker;

			FClientActionConditionContex contex;
			contex.Item = pItemInfo;

			if( !checker.CheckClientActionCondition(contex) ){
				return TRUE;
			}

			////检查是否在界面中(本界面或是其他操作界面)
			//if( pItemInfo->IsDragIntoOtherUI >= 0  ){
			//	MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOErrorInfo.EClientActionConditionCheckType.ECACCT_Item_CheckInPanelUsing") ) );
			//	return TRUE;
			//}

			//是否是装备
			UItem *pEmbedItem = mmoFacade.FindItemTemplate( pItemInfo->m_nTemplateID );
			UEquip *pEmbedEquip = Cast<UEquip>( pEmbedItem );
			if( pEmbedEquip != NULL ){
				SetSoulEmbedEquip( ContainerID, SlotID );
			}
			else{
				AutoSetSoulToEmbeInEquip( ContainerID, SlotID );
			}

			return TRUE;
		}
		break;
	case ESPType_SoulEmbed:
		{
			INT panelSlotID = (INT)mc->GetFloat( TEXT("EquipID") ); 
			//put back to bag
			switch( panelSlotID )
			{
			case ESolEbd_EquipToEmbed:
				UnSetSoulEmbedEquip();
				break;
			case ESolEbd_EmbedSoul1:
				UnSetSoulToEmbeInEquip( 0 );
				break;
			case ESolEbd_EmbedSoul2:
				UnSetSoulToEmbeInEquip( 1 );
				break;
			case ESolEbd_EmbedSoul3:
				UnSetSoulToEmbeInEquip( 2 );
				break;
			}
			
			return TRUE;
		}
		break;
	}
	
	return FALSE;
}

//----------------------------------------------------------------------------------------
UBOOL UMMOUISoulEmbed::OnDragDropEmbed( class UGFxObject* srcSlotMC,class UGFxObject* destSlotMC,
										BYTE srcSlotType, BYTE srcContainerID, INT srcSlotID,
										BYTE destSlotType, BYTE destContainerID, INT destSlotID )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	if( destSlotMC == NULL || srcSlotMC == NULL ){
		return FALSE;
	}
	
	if( srcSlotType == ESPType_Bag && destSlotType == ESPType_SoulEmbed ){
		//从背包到融灵
		FClientItemInfo *pItemInfo = mmoFacade.FindItem( srcContainerID, srcSlotID );
		if( pItemInfo == NULL ){
			return TRUE;
		}

		//检查是否在界面中(本界面或是其他操作界面)
		//
		ClientActionCondition_SoulEmbedOrUnEmbed checker;

		FClientActionConditionContex contex;
		contex.Item = pItemInfo;

		if( !checker.CheckClientActionCondition(contex) ){
			return TRUE;
		}
		//if( pItemInfo->IsDragIntoOtherUI >= 0  ){
		//	MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOErrorInfo.EClientActionConditionCheckType.ECACCT_Item_CheckInPanelUsing") ) );
		//	return TRUE;
		//}

		//
		INT panelSlotID = (INT)destSlotMC->GetFloat( TEXT("EquipID") );
		switch( panelSlotID )
		{
		case ESolEbd_EquipToEmbed:
			SetSoulEmbedEquip( srcContainerID, srcSlotID );
			break;
		case ESolEbd_EmbedSoul1:
			SetSoulToEmbeInEquip( srcContainerID, srcSlotID, 0 );
			break;
		case ESolEbd_EmbedSoul2:
			SetSoulToEmbeInEquip( srcContainerID, srcSlotID, 1 );
			break;
		case ESolEbd_EmbedSoul3:
			SetSoulToEmbeInEquip( srcContainerID, srcSlotID, 2 );
			break;
		}

		return TRUE;
	}
	
	if( srcSlotType == ESPType_SoulEmbed && destSlotType == ESPType_Bag ){
		//拖回包裹，因为本来就没有真正的移动，所以不提供拖放到原始位置
		INT panelSlotID = (INT)srcSlotMC->GetFloat( "EquipID" );
		switch( panelSlotID )
		{
		case ESolEbd_EquipToEmbed:
			UnSetSoulEmbedEquip();
			break;
		case ESolEbd_EmbedSoul1:
			UnSetSoulToEmbeInEquip( 0 );
			break;
		case ESolEbd_EmbedSoul2:
			UnSetSoulToEmbeInEquip( 1 );
			break;
		case ESolEbd_EmbedSoul3:
			UnSetSoulToEmbeInEquip( 2 );
			break;
		}

		return TRUE;
	}

	return FALSE;
}
//=====================================================================================================================
void UMMOUISoulEmbed::BagSlotChangeOnSoulEmbed( INT bagId, INT slotId )
{
	if( !IsVisible ){
		return;
	}

	FClientItemInfo *pItemInfo = MMOFacade::getSingleton().FindItem( bagId, slotId );

	if( _ToEmbedEquip._ConID == bagId && _ToEmbedEquip._SlotID == slotId ){
		//融灵的装备变化
		if( pItemInfo == NULL ){
			UnSetSoulEmbedEquip();
		}
		else{
			//刷新灵插槽
			UpdateEquipSoulSlot();
			//刷新属性
			UpdateSoulEmbedProp();
		}
	}
	else{
		//融灵使用的灵发生变化
		for( INT i = 0; i < MAX_EmbedSoul; ++i ){
			if( _ToEmbedSoul[i]._ConID == bagId && _ToEmbedSoul[i]._SlotID == slotId ){
				if( pItemInfo == NULL ){
					UnSetSoulToEmbeInEquip( i );
				}
				else{

				}
				break;
			}
		}
	}

	//
	if( E_CONSLOT_DEFAULT == bagId ){
		MMOFacade &mmoFacade = MMOFacade::getSingleton();

		UItem *pItemInBag = NULL;
		if( pItemInfo != NULL ){
			UItem *pItemInBag = mmoFacade.FindItemTemplate( pItemInfo->m_nTemplateID );
			UBOOL isNeedToGray = IsNeedToGrayOnSoulEmbed( pItemInBag, pItemInfo );
			mmoFacade.GrayItem( ESGMark_SoulEmbed, E_CONSLOT_DEFAULT, slotId, isNeedToGray );
		}
	}
}
//=====================================================================================================================
void UMMOUISoulEmbed::UpdateSoulEmbed()
{
	SetSoulEmbedEquip( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID );
}

//=============================================================================================================================
INT UMMOUISoulEmbed::UpdateEquipSoulSlot()
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	FClientItemInfo *pEquipItemInfo = mmoFacade.FindItem( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID );

	for( INT i = 0; i < MAX_SOCKET_COUNT; ++i ){
		if( _ToEmbedSoul[i]._ConID >= 0 || _ToEmbedSoul[i]._SlotID >= 0 ){
			//强制解锁放入界面中的灵石
			SetSoulToEmbeInEquip( -1, -1, i );
		}
		_ToEmbedSoul[i]._ConID = -1;
		_ToEmbedSoul[i]._SlotID = -1;
		_ToEmbedSoul[i]._IsValid = FALSE;
	}

	if( pEquipItemInfo == NULL ){
		for( INT i = 0; i < MAX_SOCKET_COUNT; ++i ){
			_EmbedSoulMc[i]._Slot->SetVisible( FALSE );
			//eventCallUCGraySlot( _EmbedSoulMc[i]._Slot, FALSE );
			_EmbedSoulMc[i]._Bg->SetVisible( FALSE );
		}

		return 0;
	}

	//UINT8 *pSocketType = (UINT8 *)SOCKET_COMBINATION[pEquipItemInfo->m_bySocketCombination];
	INT slotIdx = 0;
	for( INT i = 0; i < MAX_SOCKET_COUNT; ++i ){
		if( pEquipItemInfo->GetSocketType(i) == SOCKET_NONE ){
			_EmbedSoulMc[i]._Slot->SetVisible( FALSE );
			//eventCallUCGraySlot( _EmbedSoulMc[i]._Slot, FALSE );
			_EmbedSoulMc[i]._Bg->SetVisible( FALSE );
			continue;
		}

		++slotIdx;

		//
		_EmbedSoulMc[i]._Slot->SetVisible( TRUE );
		_EmbedSoulMc[i]._Bg->SetVisible( TRUE );
		//SOCKET_RED,SOCKET_YELLOW,SOCKET_BLUE,SOCKET_COLORFUL
		if( _EmbedSoulMc[i]._Bg != NULL ){
			FString frameName = TEXT("SOCKET");
			frameName += appItoa( pEquipItemInfo->GetSocketType(i) );
			_EmbedSoulMc[i]._Bg->GotoAndStop( frameName );
		}
		
		//
		UGFxObject *pSoulSlot = _EmbedSoulMc[i]._Slot;
		UGFxObject *pSoulSlotBg = _EmbedSoulMc[i]._Bg;
		if( pEquipItemInfo->m_nSoulID[i] > 0 ){
			UItem *pEmbededSoul = mmoFacade.FindItemTemplate( pEquipItemInfo->m_nSoulID[i] );
			//GFXPlayer->SetItemSlotData( pSoulSlot, pEmbededSoul, ESPType_SoulEmbed, -1, -1 );
			if( pEmbededSoul != NULL ){
				GFXPlayer->eventCallSetItemData( pSoulSlot, 1, MMOFacade::getSingleton().GetItemIconNamePersonalized( pEmbededSoul, pEquipItemInfo ), pEmbededSoul->ItemId, ESPType_SoulEmbed, TEXT(""), pEmbededSoul->ItemColor+1, -1, -1 );
			}
			else{
				warnf(NAME_Error, TEXT("======!!!!======= [UpdateEquipSoulSlot soul item[%d] Not FOUND]"), pEquipItemInfo->m_nSoulID[i] );
				GFXPlayer->eventCallSetItemData( pSoulSlot, 1, TEXT(""), pEquipItemInfo->m_nSoulID[i], ESPType_SoulEmbed, TEXT(""), ITEMCOLOR_INVALID, -1, -1 );
			}

			eventCallUCGraySlot( pSoulSlotBg, TRUE );
		}
		else{
			//GFXPlayer->SetItemSlotData( pSoulSlot, NULL, ESPType_SoulEmbed, -1, -1 );
			GFXPlayer->eventCallSetItemData( pSoulSlot , 0 , TEXT("") , -1, ESPType_SoulEmbed, TEXT("") , ITEMCOLOR_INVALID, -1, -1 );
			eventCallUCGraySlot( pSoulSlotBg, FALSE );

			_ToEmbedSoul[i]._IsValid = TRUE;
		}
	}

	return slotIdx;
}

//=============================================================================================================================
void UMMOUISoulEmbed::UpdateSoulEmbedProp()
{
	//刷新属性
	UpdateEquipPropData( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID );
	UpdateToEmbedSoulPropData();
	//刷新界面
	UpdateEquipOrigSoulProp();
	UpdateEquipSoulResultProp();
	//UpdateEquipSoulTotalProp();
}
//=============================================================================================================================
void UMMOUISoulEmbed::UpdateEquipPropData( INT conID, INT slotID )
{
	//MMOFacade &mmoFacade = MMOFacade::getSingleton();
	//MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	////当前是否有待融灵的装备
	//FClientItemInfo *pEquipInfo = mmoFacade.FindItem( conID, slotID );
	//if( pEquipInfo == NULL )
	//{
	//	_EmbedEquipPropSoulAdd.Empty();
	//	_EmbedEquipPropBase.Empty();
	//	return;
	//}

	////soul prop
	//_EmbedEquipPropSoulAdd.Empty();
	//for(INT i = 0; i < MAX_SOCKET_COUNT; i++)
	//{
	//	if( pEquipInfo->m_nSoulID[i] <= 0 )
	//	{
	//		continue;
	//	}

	//	const SoulInfo *pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pEquipInfo->m_nSoulID[i] );
	//	if( pSoulInfo == NULL )
	//	{
	//		continue;
	//	}

	//	//
	//	const ItemRandomAttr* propAttr = mmoFacade.GetRandomAttributById( pSoulInfo->_AttrID );
	//	if( propAttr == NULL ){
	//		warnf(NAME_Error, TEXT("======!!!!======= [UpdateEquipPropData ItemAttr in SoulInfo Not FOUND]") );
	//		continue;
	//	}


	//	INT *pAttrValue = _EmbedEquipPropSoulAdd.Find( propAttr->attrType );
	//	if( pAttrValue == NULL ){
	//		pAttrValue = &_EmbedEquipPropSoulAdd.FindOrAdd( propAttr->attrType );
	//		*pAttrValue = propAttr->value;
	//	}
	//	else{
	//		*pAttrValue = *pAttrValue + propAttr->value;
	//	}
	//}
}

//=============================================================================================================================
void UMMOUISoulEmbed::UpdateToEmbedSoulPropData()
{
	//MMOFacade &mmoFacade = MMOFacade::getSingleton();
	//MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	////
	//_ToEmbeSoulPropAdd.Empty();

	////loop all soul to embed
	//for( INT i = 0; i < MAX_SOCKET_COUNT; ++i ){
	//	FOperationItemBagPos &toEmbedSoulPos = _ToEmbedSoul[i];
	//	if( toEmbedSoulPos._ConID < 0 || toEmbedSoulPos._SlotID < 0 || toEmbedSoulPos._IsValid != TRUE ){
	//		continue;
	//	}

	//	//找到要融灵到装备的灵
	//	FClientItemInfo *pSoulItemInfo = mmoFacade.FindItem( toEmbedSoulPos._ConID, toEmbedSoulPos._SlotID );
	//	if( pSoulItemInfo == NULL ){
	//		continue;
	//	}

	//	const SoulInfo *pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pSoulItemInfo->m_nTemplateID );
	//	if( pSoulInfo == NULL ){
	//		continue;
	//	}

	//	//找到属性
	//	const ItemRandomAttr* propAttr = mmoFacade.GetRandomAttributById( pSoulInfo->_AttrID );
	//	if( propAttr == NULL ){
	//		warnf(NAME_Error, TEXT("======!!!!======= [UpdateToEmbedSoulPropData ItemAttr Not FOUND]") );
	//		continue;
	//	}

	//	//记录属性
	//	INT *pAttrValue = _ToEmbeSoulPropAdd.Find( propAttr->attrType );
	//	if( pAttrValue == NULL ){
	//		pAttrValue = &_ToEmbeSoulPropAdd.FindOrAdd( propAttr->attrType );
	//		*pAttrValue = propAttr->value;
	//	}
	//	else{
	//		*pAttrValue = *pAttrValue + propAttr->value;
	//	}
	//}//end of for
}

//=============================================================================================================================
void UMMOUISoulEmbed::UpdateEquipOrigSoulProp()
{
	FString equipPropText = FormatEquipOrigSoulProp();
	//
	_OriginalPropTf->SetString( TEXT("htmlText"), equipPropText );
}
//---------------------------------------------------------------------------------------------------------------------------
FString UMMOUISoulEmbed::FormatEquipOrigSoulProp()
{
	FString equipPropText;
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	//当前是否有待融灵的装备
	FClientItemInfo *pEquipInfo = NULL;
	if( _CurType == ESOLPT_Embed ){
		pEquipInfo = mmoFacade.FindItem( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID );
	}
	else if( _CurType == ESOLPT_Unembed ){
		pEquipInfo = mmoFacade.FindItem( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID );
	}
	if( pEquipInfo == NULL ){
		return equipPropText;
	}

	equipPropText = UITextParser::HTMLBeginFont( UITextParser::GetTipsColor(TEXT("NormalContentColor")));
	//soul prop
	for(INT i = 0; i < MAX_SOCKET_COUNT; i++){
		if( pEquipInfo->m_nSoulID[i] <= 0 ){
			continue;
		}

		const SoulInfo *pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pEquipInfo->m_nSoulID[i] );
		if( pSoulInfo == NULL ){
			continue;
		}

		const ItemRandomAttr* propAttr = mmoFacade.GetRandomAttributById( pSoulInfo->_AttrID );
		if( propAttr == NULL ){
			warnf(NAME_Error, TEXT("======!!!!======= [UpdateEquipPropData ItemAttr in SoulInfo Not FOUND]") );
			continue;
		}

		equipPropText += UITextParser::HTMLBeginParagraph();
		equipPropText += propAttr->strText;
		equipPropText += UITextParser::HTMLEndParagraph();
	}
	equipPropText += UITextParser::HTMLEndFont();

	//FString equipPropText = UITextParser::HTMLBeginFont( UITextParser::GetTipsColor(TEXT("NormalContentColor")));
	//for( TMap<FString, INT>::TIterator itor( _EmbedEquipPropSoulAdd ); itor; ++itor ){
	//	FString propType = itor.Key();
	//	INT propValue = itor.Value();

	//	FString propStr = MMOUI::ParseLocalizedPropertyPath( FString(TEXT("MMOGame.CHARACTERATTRTEXT.")) + propType );
	//	//
	//	equipPropText += UITextParser::HTMLBeginParagraph();
	//	equipPropText += propStr;
	//	if( propValue > 0 ){
	//		equipPropText += TEXT("+");
	//		equipPropText += appItoa( propValue );
	//	}
	//	//
	//	equipPropText += UITextParser::HTMLEndParagraph();
	//}
	//equipPropText += UITextParser::HTMLEndFont();

	//
	return equipPropText;
}
//=============================================================================================================================
void UMMOUISoulEmbed::UpdateEquipSoulResultProp()
{
	FString totalPropText = FormatEquipSoulResultProp();
	//
	_ResultPropTf->SetString( TEXT("htmlText"), totalPropText );
}
//------------------------------------------------------------------------------------------------------------------------------
FString UMMOUISoulEmbed::FormatEquipSoulResultProp()
{
	FString totalPropText;
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	//当前装备融灵情况，有拔除融灵则标红
	FClientItemInfo *pEquipInfo = NULL;
	if( _CurType == ESOLPT_Embed ){
		pEquipInfo = mmoFacade.FindItem( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID );
	}
	else if( _CurType == ESOLPT_Unembed ){
		pEquipInfo = mmoFacade.FindItem( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID );
	}
	if( pEquipInfo == NULL ){
		return totalPropText;
	}

	if( _CurType == ESOLPT_Unembed ){
		for(INT i = 0; i < MAX_SOCKET_COUNT; i++){
			if( pEquipInfo->m_nSoulID[i] <= 0 ){
				continue;
			}

			const SoulInfo *pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pEquipInfo->m_nSoulID[i] );
			if( pSoulInfo == NULL ){
				continue;
			}

			const ItemRandomAttr* propAttr = mmoFacade.GetRandomAttributById( pSoulInfo->_AttrID );
			if( propAttr == NULL ){
				warnf(NAME_Error, TEXT("======!!!!======= [UpdateEquipPropData ItemAttr in SoulInfo Not FOUND]") );
				continue;
			}

			//输出属性
			if( _ToUnEmbedSoulIdx == i && _CurType == ESOLPT_Unembed){
				totalPropText += UITextParser::HTMLBeginParagraph();
				totalPropText += UITextParser::HTMLBeginFont( UITextParser::GetTipsColor(TEXT("AlertColor")) );
			}
			else{
				continue;
				//totalPropText += UITextParser::HTMLBeginFont( UITextParser::GetTipsColor(TEXT("NormalContentColor")) );
			}

			totalPropText += propAttr->strText;
			totalPropText += UITextParser::HTMLEndFont();
			totalPropText += UITextParser::HTMLEndParagraph();
		}
	}
	//是否有新的融灵
	FString addAttributeColor;
	GConfig->GetString(TEXT("TextColor"), TEXT("AddAttributeColor"), addAttributeColor, GUIColorIni);
	if( _CurType == ESOLPT_Embed ){
		for( INT i = 0; i < MAX_SOCKET_COUNT; ++i ){
			FOperationItemBagPos &toEmbedSoulPos = _ToEmbedSoul[i];
			if( toEmbedSoulPos._ConID < 0 || toEmbedSoulPos._SlotID < 0 || toEmbedSoulPos._IsValid != TRUE ){
				continue;
			}

			//找到要融灵到装备的灵
			FClientItemInfo *pSoulItemInfo = mmoFacade.FindItem( toEmbedSoulPos._ConID, toEmbedSoulPos._SlotID );
			if( pSoulItemInfo == NULL ){
				continue;
			}

			const SoulInfo *pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pSoulItemInfo->m_nTemplateID );
			if( pSoulInfo == NULL ){
				continue;
			}

			//找到属性
			const ItemRandomAttr* propAttr = mmoFacade.GetRandomAttributById( pSoulInfo->_AttrID );
			if( propAttr == NULL ){
				warnf(NAME_Error, TEXT("======!!!!======= [UpdateToEmbedSoulPropData ItemAttr Not FOUND]") );
				continue;
			}

			//输出属性
			totalPropText += UITextParser::HTMLBeginParagraph();
			 
			totalPropText += UITextParser::HTMLBeginFont( addAttributeColor );
			totalPropText += propAttr->strText;
			totalPropText += UITextParser::HTMLEndFont();
			totalPropText += UITextParser::HTMLEndParagraph();
		}//end of for
	}

	//FString totalPropText = TEXT("");
	////
	//for( TMap<FString, INT>::TIterator itor( _ToEmbeSoulPropAdd ); itor; ++itor )
	//{
	//	FString propType = itor.Key();
	//	INT propValue = itor.Value();

	//	FString propStr = MMOUI::ParseLocalizedPropertyPath( FString(TEXT("MMOGame.CHARACTERATTRTEXT.")) + propType );
	//	//
	//	totalPropText += UITextParser::HTMLBeginParagraph();
	//	FString color = UITextParser::GetTipsColor(TEXT("NormalContentColor"));

	//	if( propValue > 0 )
	//	{
	//		color = UITextParser::GetTipsColor(TEXT("EnhanceColor"));
	//	}
	//	else if( propValue < 0 )
	//	{
	//		color = UITextParser::GetTipsColor(TEXT("AlertColor"));
	//	}

	//	//组合文字
	//	totalPropText += UITextParser::HTMLBeginFont( color );
	//	//
	//	totalPropText += propStr;
	//	if( propValue > 0 )
	//	{
	//		totalPropText += TEXT("+");
	//	}
	//	totalPropText += appItoa( propValue );
	//	//
	//	totalPropText += UITextParser::HTMLEndFont();
	//	totalPropText += UITextParser::HTMLEndParagraph();
	//}

	return totalPropText;
}
//=============================================================================================================================
void UMMOUISoulEmbed::UpdateEquipSoulTotalProp()
{
	//物品已带的灵属性和准备加上的灵属性
	TMap<FString, INT> totalSoulProp = _EmbedEquipPropSoulAdd;
	for( TMap<FString, INT>::TIterator itor( _ToEmbeSoulPropAdd ); itor; ++itor )
	{
		INT *pAttrValue = totalSoulProp.Find( itor.Key() );
		if( pAttrValue == NULL )
		{
			pAttrValue = &totalSoulProp.FindOrAdd( itor.Key() );
			*pAttrValue = itor.Value();
		}
		else
		{
			*pAttrValue = *pAttrValue + itor.Value();
		}
	}

	//
	FString soulTotalPropText = TEXT("");
	for( TMap<FString, INT>::TIterator itor( totalSoulProp ); itor; ++itor )
	{
		FString propType = itor.Key();
		INT propValue = itor.Value();
		
		FString propStr = MMOUI::ParseLocalizedPropertyPath(FString(TEXT("MMOGame.CHARACTERATTRTEXT.")) + propType);
		//
		soulTotalPropText += UITextParser::HTMLBeginParagraph();
		FString color = UITextParser::GetTipsColor(TEXT("NormalContentColor")) ;
		if( _ToEmbeSoulPropAdd.Find( propType ) != NULL )
		{
			color = UITextParser::GetTipsColor(TEXT("EnhanceColor")) ;
		}
		soulTotalPropText += UITextParser::HTMLBeginFont( color );
		//
		soulTotalPropText += propStr;
		if( propValue > 0 )
		{
			soulTotalPropText += TEXT("+");
			soulTotalPropText += appItoa( propValue );
		}
		//
		soulTotalPropText += UITextParser::HTMLEndFont();
		soulTotalPropText += UITextParser::HTMLEndParagraph();
	}

	//
	_TotalSoulPropTf->SetString( TEXT("htmlText"), soulTotalPropText );
}
//=============================================================================================================================
UBOOL UMMOUISoulEmbed::UnSetSoulEmbedEquip()
{
	return SetSoulEmbedEquip( -1, -1 );
}

//=============================================================================================================================
UBOOL UMMOUISoulEmbed::SetSoulEmbedEquip( INT containerID, INT slotID )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	//MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	//UMMOUIBag *pBagPanel = (UMMOUIBag*)MMOUI::FindUIPanel( MMOUI::GetUIManager()->Panel_Bag );
	if( containerID < 0 || slotID < 0 ){
		if( _ToEmbedEquip._ConID >= 0 && _ToEmbedEquip._SlotID >= 0 ){
			//清空，取下灵
			//if( pBagPanel != NULL && _ToEmbedEquip._ConID == E_CONSLOT_DEFAULT ){
				MMOFacade::getSingleton().LockItem( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID, -1 );
			//}

			//GFXPlayer->SetItemSlotData( _ToEmbedEquipMc, NULL, ESPType_SoulEmbed, -1, -1 );
			GFXPlayer->eventCallSetItemData( _ToEmbedEquipMc , 0 , TEXT("") , -1, ESPType_SoulEmbed, TEXT("") , ITEMCOLOR_INVALID, -1, -1 );
		}

		//
		_ToEmbedEquip._ConID = -1;
		_ToEmbedEquip._SlotID = -1;

		//刷新灵插槽
		UpdateEquipSoulSlot();
		for(INT i = 0; i < MAX_SOCKET_COUNT; i++){
			SetSoulToEmbeInEquip( -1, -1, i );
		}

		//刷新属性
		UpdateSoulEmbedProp();

		return TRUE;
	}

	//设置需融灵的装备
	FClientItemInfo *pInfo = mmoFacade.FindItem( containerID, slotID );
	if( pInfo == NULL ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND") );
		return FALSE;
	}


	//是否是装备
	UItem *pEmbedItem = mmoFacade.FindItemTemplate( pInfo->m_nTemplateID );
	UEquip *pEmbedEquip = Cast<UEquip>( pEmbedItem );
	if( pEmbedEquip == NULL ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_NOT_A_EQUIP") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_NOT_A_EQUIP") );
		return FALSE;
	}

	//检查空洞
	bool hasHole = false;
	//UINT8 *pSocketType = (UINT8 *)SOCKET_COMBINATION[pInfo->m_bySocketCombination];
	for(INT i = 0; i < MAX_SOCKET_COUNT; i++){
		if(pInfo->GetSocketType(i) != SOCKET_NONE){
			hasHole = true;
			break;
		}
	}

	if( !hasHole ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_EQUIP_NO_HOLE") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_EQUIP_NO_HOLE")  );
		return FALSE;
	}

	//解锁背包内原先放置的灵
	if( _ToEmbedEquip._ConID >= 0 && _ToEmbedEquip._SlotID >= 0 ){
		//if( pBagPanel != NULL && _ToEmbedEquip._ConID == E_CONSLOT_DEFAULT ){
			MMOFacade::getSingleton().LockItem( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID, -1 );
		//}
	}

	_ToEmbedEquip._ConID = containerID;
	_ToEmbedEquip._SlotID = slotID;

	//设置界面ItemSlot
	//GFXPlayer->SetItemSlotData( _ToEmbedEquipMc, pEmbedItem, ESPType_SoulEmbed, _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID );
	GFXPlayer->eventCallSetItemData( _ToEmbedEquipMc, 1, MMOFacade::getSingleton().GetItemIconNamePersonalized( pEmbedItem ), pEmbedItem->ItemId, ESPType_SoulEmbed, TEXT(""), pEmbedItem->ItemColor+1, _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID );

	//锁住背包内原先放置的灵
	//if( pBagPanel != NULL && _ToEmbedEquip._ConID == E_CONSLOT_DEFAULT ){
		MMOFacade::getSingleton().LockItem( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID, ESPType_SoulEmbed );
	//}

	//刷新灵插槽
	UpdateEquipSoulSlot();

	//刷新属性
	UpdateSoulEmbedProp();


	MMOGameEvent_Guide evtGuide(EGUET_GemPanelWithEquip);
	MMOUI::PostGameEvent(&evtGuide);

	return TRUE;
}

//=============================================================================================================================
UBOOL UMMOUISoulEmbed::UnSetSoulToEmbeInEquip( INT targetSlotID )
{
	//当前是否有待融灵的装备
	FClientItemInfo *pEquipInfo = MMOFacade::getSingleton().FindItem( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID );
	if( pEquipInfo == NULL ){
		return FALSE;
	}

	if( targetSlotID < 0 || targetSlotID >= MAX_SOCKET_COUNT ){
		return FALSE;
	}
	//检查此洞是否已经融灵过
	if( pEquipInfo->m_nSoulID[targetSlotID] > 0 ){
		return FALSE;
	}

	//
	UBOOL isSuccess = SetSoulToEmbeInEquip( -1, -1, targetSlotID );
	return isSuccess;
}

//=============================================================================================================================
INT UMMOUISoulEmbed::AutoSetSoulToEmbeInEquip( int containerID, int slotID )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	FClientItemInfo *pSoulItemInfo = mmoFacade.FindItem( containerID, slotID );
	if( pSoulItemInfo == NULL ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND") ) ,MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND"));
		return -1;
	}

	UItem *pSoulItem = mmoFacade.FindItemTemplate( pSoulItemInfo->m_nTemplateID );
	if( pSoulItem == NULL ){
		warnf(NAME_Error, TEXT("======!!!!======= [AutoSetSoulToEmbeInEquip soul Template Not FOUND]") );
		return -1;
	}

	const SoulInfo* pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pSoulItemInfo->m_nTemplateID );
	if( pSoulInfo == NULL ){
		//放入的不是灵物品
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_NOT_A_SOUL") ) ,MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_NOT_A_SOUL") );
		return -1;
	}

	//当前是否有待融灵的装备
	FClientItemInfo *pEquipInfo = mmoFacade.FindItem( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID );
	if( pEquipInfo == NULL ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_EMBED_EQUIP_NOT_PUTTED") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_EMBED_EQUIP_NOT_PUTTED") );
		return -1;
	}

	//
	INT idx = 0;
	UBOOL hasUnfitSlot = FALSE;
	for( ; idx < MAX_SOCKET_COUNT; ++idx ){
		//检查此洞是否已经融灵过
		if( pEquipInfo->m_nSoulID[idx] > 0 ){
			continue;
		}

		//检查此洞是否已放入待融灵的灵或无法再次放入
		if( ( _ToEmbedSoul[idx]._ConID >= 0 && _ToEmbedSoul[idx]._SlotID >= 0 ) || _ToEmbedSoul[idx]._IsValid != TRUE ){
			continue;
		}

		//检查此洞是否适合此灵灵
		//UINT8 *pSocketType = (UINT8 *)SOCKET_COMBINATION[pEquipInfo->m_bySocketCombination];
		if( pEquipInfo->GetSocketType(idx) != pSoulInfo->_MatchSocket && pEquipInfo->GetSocketType(idx) != SOCKET_COLORFUL ){
			hasUnfitSlot = TRUE;
			continue;
		}

		break;
	}

	//
	if( idx >= MAX_SOCKET_COUNT ){
		if( hasUnfitSlot ){
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_SOUL_UNFIT") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_SOUL_UNFIT") );
		}
		else{
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_SOUL_EMBED_FULL") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_SOUL_EMBED_FULL") );
		}

		idx = -1;
	}
	else{
		UBOOL isSuccess = SetSoulToEmbeInEquip( containerID, slotID, idx );
		if( isSuccess != TRUE ){
			idx = -1;
		}
	}

	return idx;
}

//=============================================================================================================================
UBOOL UMMOUISoulEmbed::SetSoulToEmbeInEquip( INT containerID, INT slotID, INT targetSlotID )
{
	if( targetSlotID < 0 || targetSlotID >= MAX_SOCKET_COUNT ){
		return FALSE;
	}

	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	//
	FClientItemInfo *pSoulItemInfo = NULL;
	UItem *pSoulItem = NULL;
	const SoulInfo* pSoulInfo = NULL;
	//位置值是否合法，不合法是为取下灵
	if( containerID >= 0 && slotID >= 0 ){
		//当前是否有待融灵的装备
		FClientItemInfo *pEquipInfo = mmoFacade.FindItem( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID );
		if( pEquipInfo == NULL ){
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_EMBED_EQUIP_NOT_PUTTED") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_EMBED_EQUIP_NOT_PUTTED") );
			return FALSE;
		}
		//找到要融灵到装备的灵
		pSoulItemInfo = mmoFacade.FindItem( containerID, slotID );
		if( pSoulItemInfo == NULL ){
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND") );
			return FALSE;
		}

		pSoulItem = mmoFacade.FindItemTemplate( pSoulItemInfo->m_nTemplateID );
		if( pSoulItem == NULL ){
			warnf(NAME_Error, TEXT("======!!!!======= [SetSoulToEmbeInEquip soul Template Not FOUND]") );
			return FALSE;
		}

		pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pSoulItemInfo->m_nTemplateID );
		if( pSoulInfo == NULL ){
			//放入的不是灵物品
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_NOT_A_SOUL") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_NOT_A_SOUL") );
			return FALSE;
		}

		//检查此洞是否已经融灵过
		if( pEquipInfo->m_nSoulID[targetSlotID] > 0 ){
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_ALREADY_HAS_SOUL") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_ALREADY_HAS_SOUL") );
			return FALSE;
		}

		//检查此洞是否适合此灵
		//UINT8 *pSocketType = (UINT8 *)SOCKET_COMBINATION[pEquipInfo->m_bySocketCombination];
		if( pEquipInfo->GetSocketType(targetSlotID) != pSoulInfo->_MatchSocket && pEquipInfo->GetSocketType(targetSlotID) != SOCKET_COLORFUL ){
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_SOUL_UNFIT") ) ,MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_SOUL_UNFIT"));
			return FALSE;
		}

		////检查宝石使用等级限制,装备等级高于宝石等级
		//UItem *pEquipItem = mmoFacade.FindItemTemplate( pEquipInfo->m_nTemplateID );
		//if( pEquipItem != NULL && pEquipItem->RequireLevel < pSoulInfo->_SoulLevel ){
		//	MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_EMBED_LEVEL_TOO_HIGHT") ) ,MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_EMBED_LEVEL_TOO_HIGHT"));
		//	return FALSE;
		//}
	}

	//解锁背包内原先放置的灵
	//UMMOUIBag *pBagPanel = (UMMOUIBag*)MMOUI::FindUIPanel( MMOUI::GetUIManager()->Panel_Bag );
	FOperationItemBagPos &toEmbedSoulPos = _ToEmbedSoul[targetSlotID];
	if( toEmbedSoulPos._ConID >= 0 && toEmbedSoulPos._SlotID >= 0 ){
		//if( pBagPanel != NULL && toEmbedSoulPos._ConID == E_CONSLOT_DEFAULT ){
			MMOFacade::getSingleton().LockItem( toEmbedSoulPos._ConID, toEmbedSoulPos._SlotID, -1 );
		//}
	}

	//是否是取下准备融灵的灵
	UGFxObject *pSlotMc = _EmbedSoulMc[targetSlotID]._Slot;
	//if( ( pSoulItemInfo == NULL ) && ( toEmbedSoulPos._ConID >= 0 && toEmbedSoulPos._SlotID >= 0 ) ){
	if( pSoulItemInfo == NULL ){
		//
		toEmbedSoulPos._ConID = -1;
		toEmbedSoulPos._SlotID = -1;

		//
		//GFXPlayer->SetItemSlotData( pSlotMc, NULL, ESPType_SoulEmbed, -1, -1 );
		GFXPlayer->eventCallSetItemData( pSlotMc , 0 , TEXT("") , -1, ESPType_SoulEmbed, TEXT("") , ITEMCOLOR_INVALID, -1, -1 );

		//刷新信息
		UpdateToEmbedSoulPropData();
		//刷新界面
		UpdateEquipSoulResultProp();
		//UpdateEquipSoulTotalProp();

		//
		return TRUE;
	}

	//设置要融灵的灵
	toEmbedSoulPos._ConID = containerID;
	toEmbedSoulPos._SlotID = slotID;

	//设置界面ItemSlot
	//GFXPlayer->SetItemSlotData( pSlotMc, pSoulItem, ESPType_SoulEmbed, toEmbedSoulPos._ConID, toEmbedSoulPos._SlotID );
	GFXPlayer->eventCallSetItemData( pSlotMc, 1, MMOFacade::getSingleton().GetItemIconNamePersonalized( pSoulItem ), pSoulItem->ItemId, ESPType_SoulEmbed, TEXT(""), pSoulItem->ItemColor+1, toEmbedSoulPos._ConID, toEmbedSoulPos._SlotID );

	//锁住背包内原先放置的灵
	//if( pBagPanel != NULL && toEmbedSoulPos._ConID == E_CONSLOT_DEFAULT ){
		MMOFacade::getSingleton().LockItem( toEmbedSoulPos._ConID, toEmbedSoulPos._SlotID, ESPType_SoulEmbed );
	//}

	//刷新信息
	UpdateToEmbedSoulPropData();
	//刷新界面
	UpdateEquipSoulResultProp();
	//UpdateEquipSoulTotalProp();

	MMOGameEvent_Guide evtGuide(EGUET_GemPanelWithGem);
	MMOUI::PostGameEvent(&evtGuide);

	return TRUE;
}

//=============================================================================================================================
void UMMOUISoulEmbed::ConfirmSoulEmbed()
{
	//if( !IsEquipPuttedInCanOp() ){
	//	//此界面被锁定了，无法进行操作
	//	return;
	//}
	//没有需要融灵的装备
	if( _ToEmbedEquip._ConID < 0 || _ToEmbedEquip._SlotID < 0 ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ERROR_SOUL_EMBED_EQUIP_NOT_FOUND") ) ,MsgInfoType_Table, TEXT("MMOGame.SoulEmbed.ERROR_SOUL_EMBED_EQUIP_NOT_FOUND"));
		return;
	}

	//
	UBOOL hasSendEmbed = FALSE;
	INT animiMask = 0;
	for( INT i = 0; i < MAX_EmbedSoul; ++i ){
		if( _ToEmbedSoul[i]._ConID < 0 || _ToEmbedSoul[i]._SlotID < 0 ){
			continue;
		}
		//
		CMessageHandler::GetInstance().Send_AddSoul( _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID, i, _ToEmbedSoul[i]._ConID, _ToEmbedSoul[i]._SlotID );
		hasSendEmbed = TRUE;

		_IsWaitReult = TRUE;

		animiMask |= ( 1 << i );
	}

	if( hasSendEmbed ){
		eventCallASSoulEmbedSuccessAnim( animiMask );
	}
	
	//没有放入融灵的灵
	if( hasSendEmbed == FALSE ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ERROR_SOUL_TO_EMBED_NOT_FOUND") ) ,MsgInfoType_Table,TEXT("MMOGame.SoulEmbed.ERROR_SOUL_TO_EMBED_NOT_FOUND"));
		return;
	}
}

void UMMOUISoulEmbed::OnNotifySoulEmbed( INT result )
{
	if( result != FALSE ){
		//成功，有BagSlot通知，哪里把刷新做掉了
		if( _IsWaitReult ){
			//为了只显示一次成功消息
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ERROR_SOUL_EMBED_SUCCEED") ) ,MsgInfoType_Table,TEXT("MMOGame.SoulEmbed.ERROR_SOUL_EMBED_SUCCEED"));
			_IsWaitReult = FALSE;
		}

		//一个灵镶嵌成功，一个通知
		for( INT i = 0; i < MAX_EmbedSoul; ++i ){
			//清理镶嵌数据
			if( _ToEmbedSoul[i]._ConID >= 0 || _ToEmbedSoul[i]._SlotID >= 0 ){
				//强制解锁放入界面中的灵石
				SetSoulToEmbeInEquip( -1, -1, i );
				//
				_ToEmbedSoul[i]._ConID = 0;
				_ToEmbedSoul[i]._SlotID = 0;
				break;
			}
		}

		//  引导任务
		MMOQuestManager::getSingleton().UpdateClientVariable(ECVT_Quest, GQT_EmbedEquip);

		MMOGameEvent_Guide evtGuide(EGUET_GemEmbed);
		MMOUI::PostGameEvent(&evtGuide);
	}
	else{
		//失败
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ERROR_SOUL_EMBED_FAILED") ),MsgInfoType_Table,TEXT("MMOGame.SoulEmbed.ERROR_SOUL_EMBED_FAILED") );

		_IsWaitReult = FALSE;
	}
}

//================================================================================================================================
//UnEmbed
void UMMOUISoulEmbed::ResetSoulUnEmbed()
{
	SelectSoulToUnEmbed( -1 );
	UnSetSoulUnEmbedEquip();
}

//
void UMMOUISoulEmbed::GrayAllInBagNoNeedForSoulUnEmbed( UBOOL isToGray )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();
	if( Player == NULL ){
		return;
	}

	//
	UINT bagCapability = Player->ItemManager->CurCapacity( E_CONSLOT_DEFAULT );
	for( UINT j = 0; j < bagCapability; ++j){
		if( isToGray == FALSE ){
			mmoFacade.GrayItem( ESGMark_SoulUnEmbed, E_CONSLOT_DEFAULT, j, FALSE );
			continue;
		}

		//需要打灰
		const FClientItemInfo *pItemInfo = mmoFacade.FindItem( E_CONSLOT_DEFAULT, j );
		if( pItemInfo == NULL ){
			continue;
		}

		UItem *pItemInBag = mmoFacade.FindItemTemplate( pItemInfo->m_nTemplateID );
		if( pItemInBag == NULL ){
			continue;
		}

		UBOOL isNeedToGray = IsNeedToGrayOnSoulUnEmbed( pItemInBag, pItemInfo );
		mmoFacade.GrayItem( ESGMark_SoulUnEmbed, E_CONSLOT_DEFAULT, j, isNeedToGray );
	}
}

//
UBOOL UMMOUISoulEmbed::IsNeedToGrayOnSoulUnEmbed( UItem *pItemInBag, const FClientItemInfo *pItemInfo )
{
	if( pItemInBag == NULL || pItemInfo == NULL ){
		return FALSE;
	}

	UBOOL noNeedToGray = FALSE;
	//是否是有孔装备
	UEquip *pEmbedEquip = Cast<UEquip>( pItemInBag );
	if( pEmbedEquip != NULL ){
		//检查嵌有灵石的孔洞
		//UINT8 *pSocketType = (UINT8 *)SOCKET_COMBINATION[pItemInfo->m_bySocketCombination];
		for(INT i = 0; i < MAX_SOCKET_COUNT; ++i){
			//检查嵌有灵石的孔洞
			if( pItemInfo->m_nSoulID[i] > 0 ){
				noNeedToGray = TRUE;
				break;
			}
		}
	}

	return (!noNeedToGray);
}
//=============================================================================================================================
UBOOL UMMOUISoulEmbed::OnRightMouseClickUnEmbed(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault)
{
	if(bDefault)return FALSE;

	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	//UBOOL rst = FALSE;

	switch( SlotType )
	{
	case ESPType_Bag:
		{
			//put in from bag
			FClientItemInfo *pItemInfo = mmoFacade.FindItem( ContainerID, SlotID );
			if( pItemInfo == NULL ){
				return TRUE;
			}

			//
			ClientActionCondition_SoulEmbedOrUnEmbed checker;

			FClientActionConditionContex contex;
			contex.Item = pItemInfo;

			if( !checker.CheckClientActionCondition(contex) ){
				return TRUE;
			}

			////检查是否在界面中(本界面或是其他操作界面)
			//if( pItemInfo->IsDragIntoOtherUI >= 0  ){
			//	MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOErrorInfo.EClientActionConditionCheckType.ECACCT_Item_CheckInPanelUsing") ) );
			//	return TRUE;
			//}

			//是否是装备
			UItem *pEmbedItem = mmoFacade.FindItemTemplate( pItemInfo->m_nTemplateID );
			UEquip *pEmbedEquip = Cast<UEquip>( pEmbedItem );
			if( pEmbedEquip != NULL ){
				SetSoulUnEmbedEquip( ContainerID, SlotID );
			}

			return TRUE;
		}
		break;
	case ESPType_SoulUnEmbed:
		{
			INT panelSlotID = (INT)mc->GetFloat( TEXT("EquipID") ); 
			switch( panelSlotID )
			{
			case ESolEbd_EquipToUnEmbed:
				{
					SelectSoulToUnEmbed( -1 );

					UnSetSoulUnEmbedEquip();
				}
				break;
			}

			return TRUE;
		}
		break;
	}

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
UBOOL UMMOUISoulEmbed::OnDragDropUnEmbed( class UGFxObject* srcSlotMC,class UGFxObject* destSlotMC,
											BYTE srcSlotType, BYTE srcContainerID, INT srcSlotID,
											BYTE destSlotType, BYTE destContainerID, INT destSlotID )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	if( destSlotMC == NULL || srcSlotMC == NULL ){
		return FALSE;
	}

	if( srcSlotType == ESPType_Bag && destSlotType == ESPType_SoulUnEmbed ){
		//从背包到融灵
		FClientItemInfo *pItemInfo = mmoFacade.FindItem( srcContainerID, srcSlotID );
		if( pItemInfo == NULL ){
			return TRUE;
		}

		//检查是否在界面中(本界面或是其他操作界面)
		//
		ClientActionCondition_SoulEmbedOrUnEmbed checker;

		FClientActionConditionContex contex;
		contex.Item = pItemInfo;

		if( !checker.CheckClientActionCondition(contex) ){
			return TRUE;
		}
		//if( pItemInfo->IsDragIntoOtherUI >= 0  ){
		//	MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOErrorInfo.EClientActionConditionCheckType.ECACCT_Item_CheckInPanelUsing") ) );
		//	return TRUE;
		//}

		//
		INT panelSlotID = (INT)destSlotMC->GetFloat( TEXT("EquipID") );
		switch( panelSlotID )
		{
		case ESolEbd_EquipToUnEmbed:
			{
				SetSoulUnEmbedEquip( srcContainerID, srcSlotID );
			}
			break;
		}

		return TRUE;
	}

	if( srcSlotType == ESPType_SoulUnEmbed && destSlotType == ESPType_Bag ){
		//拖回包裹，因为本来就没有真正的移动，所以不提供拖放到原始位置
		INT panelSlotID = (INT)srcSlotMC->GetFloat( "EquipID" );
		switch( panelSlotID )
		{
		case ESolEbd_EquipToUnEmbed:
			{
				SelectSoulToUnEmbed( -1 );

				UnSetSoulUnEmbedEquip();
			}
			break;
		}

		return TRUE;
	}

	return FALSE;
}
//========================================================================================================================================
void UMMOUISoulEmbed::BagSlotChangeOnSoulUnEmbed( INT bagId, INT slotId )
{
	if( !IsVisible ){
		return;
	}

	FClientItemInfo *pItemInfo = MMOFacade::getSingleton().FindItem( bagId, slotId );

	if( _ToUnEmbedEquip._ConID == bagId && _ToUnEmbedEquip._SlotID == slotId ){
		//融灵的装备变化
		if( pItemInfo == NULL ){
			SelectSoulToUnEmbed( -1 );
			UnSetSoulUnEmbedEquip();
		}
		else{
			//刷新灵插槽
			UpdateUnEmbedSlot();
			//刷新属性
			UpdateSoulEmbedPropInUnEmbed();
		}
	}

	//
	if( E_CONSLOT_DEFAULT == bagId ){
		MMOFacade &mmoFacade = MMOFacade::getSingleton();

		UItem *pItemInBag = NULL;
		if( pItemInfo != NULL ){
			UItem *pItemInBag = mmoFacade.FindItemTemplate( pItemInfo->m_nTemplateID );
			UBOOL isNeedToGray = IsNeedToGrayOnSoulUnEmbed( pItemInBag, pItemInfo );
			mmoFacade.GrayItem( ESGMark_SoulUnEmbed, E_CONSLOT_DEFAULT, slotId, isNeedToGray );
		}
	}
}
//==================================================================================================================
void UMMOUISoulEmbed::UpdateSoulUnEmbed()
{
	SetSoulUnEmbedEquip( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID );
}

//================================================================================================================================
void UMMOUISoulEmbed::SelectSoulToUnEmbed( INT idx )
{
	FClientItemInfo *pEquipItemInfo = MMOFacade::getSingleton().FindItem( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID );
	if( pEquipItemInfo == NULL ){
		return;
	}

	if( idx < MAX_SOCKET_COUNT && idx >= 0 && pEquipItemInfo->m_nSoulID[idx] <= 0 ){
		idx = -1;
	}

	//
	_ToUnEmbedSoulIdx = idx;

	//
	UpdateSoulEmbedPropInUnEmbed();

	//
	for( INT i = 0; i < MAX_SOCKET_COUNT; ++i ){
		UGFxObject *pSelectedMc = _UnEmbedSoulMc[i]._Slot->GetObject( TEXT("_select_border") );
		if( pSelectedMc != NULL ){
			pSelectedMc->SetVisible( i == _ToUnEmbedSoulIdx );
		}
		//_UnEmbedSoulMc[i]._Slot->SetBool( TEXT("selected"),  ( i == _ToUnEmbedSoulIdx ) );
	}
}

//================================================================================================================================
void UMMOUISoulEmbed::UpdateSoulEmbedPropInUnEmbed()
{
	//刷新属性
	UpdateEquipPropData( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID );
	UpdateToUnEmbedSoulPropData();
	//刷新界面
	UpdateSoulUnEmbedFee();
	UpdateEquipOrigSoulPropInUnEmbed();
	UpdateEquipResultPropInUnEmbed();
}

//================================================================================================================================
void UMMOUISoulEmbed::UpdateToUnEmbedSoulPropData()
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	//
	_ToEmbeSoulPropAdd.Empty();
	FClientItemInfo *pEquipInfo = MMOFacade::getSingleton().FindItem( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID );
	if( pEquipInfo == NULL ){
		return;
	}

	if( _ToUnEmbedSoulIdx < 0 || _ToUnEmbedSoulIdx >= MAX_SOCKET_COUNT || pEquipInfo->m_nSoulID[_ToUnEmbedSoulIdx] <= 0 ){
		return;
	}

	const SoulInfo *pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pEquipInfo->m_nSoulID[_ToUnEmbedSoulIdx] );
	if( pSoulInfo == NULL ){
		return;
	}

	//找到属性
	const ItemRandomAttr* propAttr = mmoFacade.GetRandomAttributById( pSoulInfo->_AttrID );
	if( propAttr == NULL ){
		warnf(NAME_Error, TEXT("======!!!!======= [UpdateToEmbedSoulPropData ItemAttr Not FOUND]") );
		return;
	}

	//记录属性
	INT *pAttrValue = _ToEmbeSoulPropAdd.Find( propAttr->attrType );
	if( pAttrValue == NULL )
	{
		pAttrValue = &_ToEmbeSoulPropAdd.FindOrAdd( propAttr->attrType );
		*pAttrValue = - propAttr->value;
	}
	else{
		*pAttrValue = *pAttrValue - propAttr->value;
	}
}
//=============================================================================================================================
void UMMOUISoulEmbed::UpdateEquipOrigSoulPropInUnEmbed()
{
	FString equipPropText = FormatEquipOrigSoulProp();
	//
	_OriginalPropInUnEmbedTf->SetString( TEXT("htmlText"), equipPropText );
}
//=============================================================================================================================
void UMMOUISoulEmbed::UpdateEquipResultPropInUnEmbed()
{
	FString totalPropText = FormatEquipSoulResultProp();
	//
	_ResultPropInUnEmbedTf->SetString( TEXT("htmlText"), totalPropText );
}

//=============================================================================================================================
UBOOL UMMOUISoulEmbed::UpdateSoulUnEmbedFee()
{
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	FClientItemInfo *pEquipInfo = MMOFacade::getSingleton().FindItem( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID );
	if( pEquipInfo == NULL ){
		_UnEmbedFeeTf->SetString( TEXT("text"), TEXT("") );
		return TRUE;
	}

	if( _ToUnEmbedSoulIdx < 0 || _ToUnEmbedSoulIdx >= MAX_SOCKET_COUNT || pEquipInfo->m_nSoulID[_ToUnEmbedSoulIdx] <= 0 ){
		_UnEmbedFeeTf->SetString( TEXT("text"), TEXT("") );
		return TRUE;
	}

	const SoulInfo *pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pEquipInfo->m_nSoulID[_ToUnEmbedSoulIdx] );
	if( pSoulInfo == NULL ){
		_UnEmbedFeeTf->SetString( TEXT("text"), TEXT("") );
		return TRUE;
	}

	INT curMoney = MMOFacade::getSingleton().GetPlayerMoney( E_MONEYTYPE_02 );
	UBOOL isMoneyOk = ( curMoney >= pSoulInfo->_DetouchPrice ? TRUE : FALSE );
	//
	FString moneyStr;
	FString moneyColor;
	if( isMoneyOk ){
		moneyColor = TEXT("0xFFFFE0A6");
	}
	else{
		moneyColor = UITextParser::GetTipsColor( TEXT("AlertColor") );
	}
	moneyStr = UITextParser::HTMLMoneyIconString( MONEYTYPE_02, pSoulInfo->_DetouchPrice, moneyColor );

	_UnEmbedFeeTf->SetString( TEXT("htmlText"), moneyStr );

	return isMoneyOk;
}

//=============================================================================================================================
UBOOL UMMOUISoulEmbed::UnSetSoulUnEmbedEquip()
{
	return SetSoulUnEmbedEquip( -1, -1 );
}

//=============================================================================================================================
UBOOL UMMOUISoulEmbed::SetSoulUnEmbedEquip( INT containerID, INT slotID )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	//MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	//UMMOUIBag *pBagPanel = (UMMOUIBag*)MMOUI::FindUIPanel( MMOUI::GetUIManager()->Panel_Bag );
	if( containerID < 0 || slotID < 0 ){
		if( _ToUnEmbedEquip._ConID >= 0 && _ToUnEmbedEquip._SlotID >= 0 ){
			//清空，取下灵
			//if( pBagPanel != NULL && _ToUnEmbedEquip._ConID == E_CONSLOT_DEFAULT ){
				MMOFacade::getSingleton().LockItem( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID, -1 );
			//}

			//GFXPlayer->SetItemSlotData( _ToEmbedEquipMc, NULL, ESPType_SoulEmbed, -1, -1 );
			GFXPlayer->eventCallSetItemData( _ToUnEmbedEquipMc , 0 , TEXT("") , -1, ESPType_SoulUnEmbed, TEXT("") , ITEMCOLOR_INVALID, -1, -1 );
		}

		//
		_ToUnEmbedEquip._ConID = -1;
		_ToUnEmbedEquip._SlotID = -1;

		//刷灵插槽
		UpdateUnEmbedSlot();
		//刷新属性
		UpdateSoulEmbedPropInUnEmbed();

		return TRUE;
	}

	//设置需融灵的装备
	FClientItemInfo *pInfo = mmoFacade.FindItem( containerID, slotID );
	if( pInfo == NULL ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND") );
		return FALSE;
	}


	//是否是装备
	UItem *pEmbedItem = mmoFacade.FindItemTemplate( pInfo->m_nTemplateID );
	UEquip *pEmbedEquip = Cast<UEquip>( pEmbedItem );
	if( pEmbedEquip == NULL ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_NOT_A_EQUIP") ) ,MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_NOT_A_EQUIP"));
		return FALSE;
	}

	//检查空洞
	bool hasHole = false;
	//UINT8 *pSocketType = (UINT8 *)SOCKET_COMBINATION[pInfo->m_bySocketCombination];
	for(INT i = 0; i < MAX_SOCKET_COUNT; i++){
		if(pInfo->GetSocketType(i) != SOCKET_NONE){
			hasHole = true;
			break;
		}
	}

	if( !hasHole ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_EQUIP_NO_HOLE") ) ,MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_EQUIP_NO_HOLE"));
		return FALSE;
	}

	//解锁背包内原先放置的灵
	if( _ToUnEmbedEquip._ConID >= 0 && _ToUnEmbedEquip._SlotID >= 0 ){
		//if( pBagPanel != NULL && _ToUnEmbedEquip._ConID == E_CONSLOT_DEFAULT ){
			MMOFacade::getSingleton().LockItem( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID, -1 );
		//}
	}

	_ToUnEmbedEquip._ConID = containerID;
	_ToUnEmbedEquip._SlotID = slotID;

	//设置界面ItemSlot
	//GFXPlayer->SetItemSlotData( _ToEmbedEquipMc, pEmbedItem, ESPType_SoulEmbed, _ToEmbedEquip._ConID, _ToEmbedEquip._SlotID );
	GFXPlayer->eventCallSetItemData( _ToUnEmbedEquipMc, 1, MMOFacade::getSingleton().GetItemIconNamePersonalized( pEmbedItem ), pEmbedItem->ItemId, ESPType_SoulUnEmbed, TEXT(""), pEmbedItem->ItemColor+1, _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID );

	//锁住背包内原先放置的灵
	//if( pBagPanel != NULL && _ToUnEmbedEquip._ConID == E_CONSLOT_DEFAULT ){
		MMOFacade::getSingleton().LockItem( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID, ESPType_SoulUnEmbed );
	//}

	//刷灵插槽
	UpdateUnEmbedSlot();

	//刷新属性
	UpdateSoulEmbedPropInUnEmbed();

	return TRUE;
}

//
void UMMOUISoulEmbed::UpdateUnEmbedSlot()
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	FClientItemInfo *pEquipItemInfo = mmoFacade.FindItem( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID );

	for( INT i = 0; i < MAX_SOCKET_COUNT; ++i ){
		_UnEmbedSoulMc[i]._Slot->SetVisible( FALSE );
		_UnEmbedSoulMc[i]._Bg->SetVisible( FALSE );
	}

	//
	if( pEquipItemInfo == NULL ){
		return;
	}

	//
	INT slotIdx = 0;
	//UINT8 *pSocketType = (UINT8 *)SOCKET_COMBINATION[pEquipItemInfo->m_bySocketCombination];
	for( INT i = 0; i < MAX_SOCKET_COUNT; ++i ){
		//if( pEquipItemInfo->GetSocketType(i) == SOCKET_NONE || pEquipItemInfo->m_nSoulID[i] <= 0){
		if( pEquipItemInfo->GetSocketType(i) == SOCKET_NONE ){
			continue;
		}

		++slotIdx;

		//
		_UnEmbedSoulMc[i]._Slot->SetVisible( TRUE );
		_UnEmbedSoulMc[i]._Bg->SetVisible( TRUE );
		//SOCKET_RED,SOCKET_YELLOW,SOCKET_BLUE,SOCKET_COLORFUL
		if( _UnEmbedSoulMc[i]._Bg != NULL ){
			FString frameName = TEXT("SOCKET");
			frameName += appItoa( pEquipItemInfo->GetSocketType(i) );
			_UnEmbedSoulMc[i]._Bg->GotoAndStop( frameName );
		}

		//
		UGFxObject *pSoulSlot = _UnEmbedSoulMc[i]._Slot;
		if( pEquipItemInfo->m_nSoulID[i] > 0 ){
			UItem *pEmbededSoul = mmoFacade.FindItemTemplate( pEquipItemInfo->m_nSoulID[i] );
			//GFXPlayer->SetItemSlotData( pSoulSlot, pEmbededSoul, ESPType_SoulEmbed, -1, -1 );
			if( pEmbededSoul != NULL ){
				GFXPlayer->eventCallSetItemData( pSoulSlot, 1, MMOFacade::getSingleton().GetItemIconNamePersonalized( pEmbededSoul ), pEmbededSoul->ItemId, ESPType_SoulEmbed, TEXT(""), pEmbededSoul->ItemColor+1, -1, -1 );
			}
			else{
				warnf(NAME_Error, TEXT("======!!!!======= [UpdateUnEmbedSlot soul item[%d] Not FOUND]"), pEquipItemInfo->m_nSoulID[i] );
				GFXPlayer->eventCallSetItemData( pSoulSlot, 1, TEXT(""), pEquipItemInfo->m_nSoulID[i], ESPType_SoulEmbed, TEXT(""), ITEMCOLOR_INVALID, -1, -1 );
			}
		}
		else{
			GFXPlayer->eventCallSetItemData( pSoulSlot, 0, TEXT(""), -1, ESPType_SoulEmbed, TEXT(""), ITEMCOLOR_INVALID, -1, -1 );
		}
	}
}

//=============================================================================================================================
void UMMOUISoulEmbed::ConfirmSoulUnEmbed()
{
	//if( !IsEquipPuttedInCanOp() ){
	//	//此界面被锁定了，无法进行操作
	//	return;
	//}

	//没有需要融灵的装备
	if( _ToUnEmbedEquip._ConID < 0 || _ToUnEmbedEquip._SlotID < 0 ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ERROR_SOUL_TO_UNEMBED_NOT_FOUND") ),MsgInfoType_Table,TEXT("MMOGame.SoulEmbed.ERROR_SOUL_TO_UNEMBED_NOT_FOUND") );
		return;
	}

	//没有选定需要拔除的灵
	if( _ToUnEmbedSoulIdx < 0 || _ToUnEmbedSoulIdx >= MAX_EmbedSoul ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ERROR_SOUL_TO_UNEMBED_SOUL_NOT_SELECTED") ) ,MsgInfoType_Table,TEXT("MMOGame.SoulEmbed.ERROR_SOUL_TO_UNEMBED_SOUL_NOT_SELECTED"));
		return;
	}

	//没有足够的钱
	UBOOL isMoneyOK = UpdateSoulUnEmbedFee();
	if( isMoneyOK == FALSE ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ERROR_SOUL_TO_UNEMBED_NOT_ENOUGH_MONEY") ),MsgInfoType_Table,TEXT("MMOGame.SoulEmbed.ERROR_SOUL_TO_UNEMBED_NOT_ENOUGH_MONEY") );
		return;
	}

	eventCallASSoulUnEmbedAnim( TRUE );
	//
	CMessageHandler::GetInstance().Send_RemoveSoul( _ToUnEmbedEquip._ConID, _ToUnEmbedEquip._SlotID, _ToUnEmbedSoulIdx );
}

//=============================================================================================================================
void UMMOUISoulEmbed::OnNotifySoulUnEmbed( INT result )
{
	if( result != FALSE ){
		//成功
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ERROR_SOUL_UNEMBED_SUCCEED") ),MsgInfoType_Table,TEXT("MMOGame.SoulEmbed.ERROR_SOUL_UNEMBED_SUCCEED") );

		//  引导任务
		MMOQuestManager::getSingleton().UpdateClientVariable(ECVT_Quest, GQT_PickEquip);
	}
	else{
		//失败
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ERROR_SOUL_UNEMBED_FAILED") ),MsgInfoType_Table,TEXT("MMOGame.SoulEmbed.ERROR_SOUL_UNEMBED_FAILED") );
	}

	//
	UpdateSoulUnEmbed();

	//UpdateToUnEmbedSoulPropData();
	//UpdateSoulUnEmbedFee();
	SelectSoulToUnEmbed( -1 );
}

//================================================================================================================================
//Soul Level up
//soul embed
void UMMOUISoulEmbed::GrayAllInBagNoNeedForSoulLevelUp( UBOOL isToGray )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();
	if( Player == NULL ){
		return;
	}

	//
	UINT bagCapability = Player->ItemManager->CurCapacity( E_CONSLOT_DEFAULT );
	for( UINT j = 0; j < bagCapability; ++j){
		if( isToGray == FALSE ){
			mmoFacade.GrayItem( ESGMark_SoulLevelUp, E_CONSLOT_DEFAULT, j, FALSE );
			continue;
		}

		//需要打灰
		const FClientItemInfo *pItemInfo = mmoFacade.FindItem( E_CONSLOT_DEFAULT, j );
		if( pItemInfo == NULL ){
			continue;
		}

		UItem *pItemInBag = mmoFacade.FindItemTemplate( pItemInfo->m_nTemplateID );
		if( pItemInBag == NULL ){
			continue;
		}

		UBOOL isNeedToGray = IsNeedToGrayOnSoulLvUp( pItemInBag, pItemInfo );
		mmoFacade.GrayItem( ESGMark_SoulLevelUp, E_CONSLOT_DEFAULT, j, isNeedToGray );
	}
}

//
UBOOL UMMOUISoulEmbed::IsNeedToGrayOnSoulLvUp( UItem *pItemInBag, const FClientItemInfo *pItemInfo )
{
	if( pItemInfo == NULL ){
		return FALSE;
	}

	//
	UBOOL noNeedToGray = FALSE;
	//是否是灵石
	const SoulInfo *pSoulInfo = MMOEquipManager::getSingleton().FindSoulInfoByItemTemplateID( pItemInfo->m_nTemplateID );
	noNeedToGray = ( pSoulInfo != NULL );

	return (!noNeedToGray);
}
//================================================================================================================================
void UMMOUISoulEmbed::BagSlotChangeOnSoulLvUp( INT bagId, INT slotId )
{
	if( !IsVisible ){
		return;
	}

	//
	FClientItemInfo *pItemInfo = MMOFacade::getSingleton().FindItem( bagId, slotId );

	if( _ToLvUpSoul._ConID == bagId && _ToLvUpSoul._SlotID == slotId ){
		//需升级的魂
		if( pItemInfo == NULL ){
			UnSetLevelUpSoul();
		}
		else{
			SetLevelUpSoul( bagId, slotId );
		}
	}
	else if( _HelpLvUpSoulItem._ConID == bagId && _HelpLvUpSoulItem._SlotID == slotId ){
		//提升升级成功率的物品
	}
	else{
		//升级吸收的魂
		for( INT i = 0; i < MAX_SacrificeSoul; ++i ){
			if( _SacrificeSoul[i]._ConID == bagId && _SacrificeSoul[i]._SlotID == slotId ){
				if( pItemInfo == NULL ){
					UnSetLevelUpSoulSacrifice( i );
				}
				else{
					INT unSetCnt = AutoUnSetPackedSoulScrifice( bagId, slotId );
					if( unSetCnt > 0 ){
						//放入的灵堆叠数量不够
						MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_NOT_ENOUGH_SOUL") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_NOT_ENOUGH_SOUL") );
					}
					break;
				}
			}
		}
	}//end of if else

	//
	if( E_CONSLOT_DEFAULT == bagId ){
		MMOFacade &mmoFacade = MMOFacade::getSingleton();

		UItem *pItemInBag = NULL;
		if( pItemInfo != NULL ){
			UItem *pItemInBag = mmoFacade.FindItemTemplate( pItemInfo->m_nTemplateID );
			UBOOL isNeedToGray = IsNeedToGrayOnSoulLvUp( pItemInBag, pItemInfo );
			mmoFacade.GrayItem( ESGMark_SoulLevelUp, E_CONSLOT_DEFAULT, slotId, isNeedToGray );
		}
	}
}

//========================================================================================================================================
UBOOL UMMOUISoulEmbed::OnRightMouseClickLvUp(class UGFxObject* mc,BYTE SlotType,BYTE ContainerID,INT SlotID,UBOOL bDefault)
{
	if(bDefault)return FALSE;

	MMOFacade &mmoFacade = MMOFacade::getSingleton();

	if( SlotType == ESPType_Bag ){
		//put in from bag
		FClientItemInfo *pItemInfo = mmoFacade.FindItem( ContainerID, SlotID );
		if( pItemInfo == NULL ){
			return TRUE;
		}

		//
		ClientActionCondition_SoulLevelUp checker;

		FClientActionConditionContex contex;
		contex.Item = pItemInfo;

		if( !checker.CheckClientActionCondition(contex) ){
			return TRUE;
		}

		//
		AutoSetLevelUpSoulSacrifice( ContainerID, SlotID );

		return TRUE;
	}
	else{
		INT panelSlotID = (INT)mc->GetFloat( TEXT("EquipID") ); 
		//put back to bag
		if( SlotType == ESPType_SoulLevelUp ){
			switch( panelSlotID )
			{
			case ESOLPST_LvUpSoul:
				UnSetLevelUpSoul();
				break;
			case ESOLPST_LvUpScrificSoul1:
				UnSetLevelUpSoulSacrifice( 0 );
				break;
			case ESOLPST_LvUpScrificSoul2:
				UnSetLevelUpSoulSacrifice( 1 );
				break;
			case ESOLPST_LvUpScrificSoul3:
				UnSetLevelUpSoulSacrifice( 2 );
				break;
			case ESOLPST_LvUpScrificSoul4:
				UnSetLevelUpSoulSacrifice( 3 );
				break;
			case ESOLPST_LvUpScrificSoul5:
				UnSetLevelUpSoulSacrifice( 4 );
				break;
			case ESOLPST_LvUpHelpItem:
				UnSetLevelUpSoulSuccessHelp();
				break;
			}

			return TRUE;
		}

		return FALSE;
	}

	return FALSE;
}

//
UBOOL UMMOUISoulEmbed::OnDragDropLvUp( class UGFxObject* srcSlotMC,class UGFxObject* destSlotMC,
	BYTE srcSlotType, BYTE srcContainerID, INT srcSlotID,
	BYTE destSlotType, BYTE destContainerID, INT destSlotID )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	if( destSlotMC == NULL || srcSlotMC == NULL ){
		return FALSE;
	}

	//从背包到融灵
	if( srcSlotType == ESPType_Bag ){
		FClientItemInfo *pItemInfo = mmoFacade.FindItem( srcContainerID, srcSlotID );
		if( pItemInfo == NULL ){
			return TRUE;
		}

		//
		ClientActionCondition_SoulLevelUp checker;

		FClientActionConditionContex contex;
		contex.Item = pItemInfo;

		if( !checker.CheckClientActionCondition(contex) ){
			return TRUE;
		}

		//
		INT panelSlotID = (INT)destSlotMC->GetFloat( TEXT("EquipID") );
		if( destSlotType == ESPType_SoulLevelUp ){
			switch( panelSlotID )
			{
			case ESOLPST_LvUpSoul:
				SetLevelUpSoul( srcContainerID, srcSlotID );
				break;
			case ESOLPST_LvUpScrificSoul1:
				SetLevelUpSoulSacrifice( srcContainerID, srcSlotID, 0 );
				break;
			case ESOLPST_LvUpScrificSoul2:
				SetLevelUpSoulSacrifice( srcContainerID, srcSlotID, 1 );
				break;
			case ESOLPST_LvUpScrificSoul3:
				SetLevelUpSoulSacrifice( srcContainerID, srcSlotID, 2 );
				break;
			case ESOLPST_LvUpScrificSoul4:
				SetLevelUpSoulSacrifice( srcContainerID, srcSlotID, 3 );
				break;
			case ESOLPST_LvUpScrificSoul5:
				SetLevelUpSoulSacrifice( srcContainerID, srcSlotID, 4 );
				break;
			case ESOLPST_LvUpHelpItem:
				SetLevelUpSoulSuccessHelp( srcContainerID, srcSlotID );
				break;
			}
		}

		return TRUE;
	}
	else if( destSlotType == ESPType_Bag ){
		//拖回包裹，因为本来就没有真正的移动，所以不提供拖放到原始位置
		INT panelSlotID = (INT)srcSlotMC->GetFloat( TEXT("EquipID") );
		if( srcSlotType == ESPType_SoulLevelUp ){
			switch( panelSlotID )
			{
			case ESOLPST_LvUpSoul:
				UnSetLevelUpSoul();
				break;
			case ESOLPST_LvUpScrificSoul1:
				UnSetLevelUpSoulSacrifice( 0 );
				break;
			case ESOLPST_LvUpScrificSoul2:
				UnSetLevelUpSoulSacrifice( 1 );
				break;
			case ESOLPST_LvUpScrificSoul3:
				UnSetLevelUpSoulSacrifice( 2 );
				break;
			case ESOLPST_LvUpScrificSoul4:
				UnSetLevelUpSoulSacrifice( 3 );
				break;
			case ESOLPST_LvUpScrificSoul5:
				UnSetLevelUpSoulSacrifice( 4 );
				break;
			case ESOLPST_LvUpHelpItem:
				UnSetLevelUpSoulSuccessHelp();
				break;
			}
		}

		return TRUE;
	}

	return FALSE;
}

//=============================================================================================================================
void UMMOUISoulEmbed::UpdateSoulLevelUp()
{
	//待升级的灵
	SetLevelUpSoul( _ToLvUpSoul._ConID, _ToLvUpSoul._SlotID );
	//吸收的灵
	for( INT i = 0; i < MAX_SacrificeSoul; ++i ){
		if( _SacrificeSoul[i]._ConID >= 0 ){
			FClientItemInfo *pItemInfo = MMOFacade::getSingleton().FindItem( _SacrificeSoul[i]._ConID, _SacrificeSoul[i]._SlotID );
			if( pItemInfo == NULL ){
				UnSetLevelUpSoulSacrifice( i );
			}
			else{
				SetLevelUpSoulSacrifice( _SacrificeSoul[i]._ConID, _SacrificeSoul[i]._SlotID, i );
			}
		}
		else{
			UnSetLevelUpSoulSacrifice( i );
		}
	}
}

//=============================================================================================================================
void UMMOUISoulEmbed::UpdateSoulInfo()
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	if( _NextLevelSoulPropTf == NULL || _CurLevelSoulPropTf == NULL ){
		return;
	}
	_NextLevelSoulPropTf->SetString( TEXT("htmlText"), TEXT("") );
	_CurLevelSoulPropTf->SetString( TEXT("htmlText"), TEXT("") );

	FClientItemInfo *pInfo = mmoFacade.FindItem( _ToLvUpSoul._ConID, _ToLvUpSoul._SlotID );
	if( pInfo == NULL ){
		//warnf(NAME_Error, TEXT("======!!!!======= [UpdateSoulInfo soul FClientItemInfo Not FOUND]") );
		return;
	}

	const SoulInfo* pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pInfo->m_nTemplateID );
	if( pSoulInfo == NULL ){
		warnf(NAME_Error, TEXT("======!!!!======= [UpdateSoulInfo soul SoulInfo Not FOUND]") );
		return;
	}

	////
	//UEnum* enumClass = equipMgr.GetAttrEnumClass();
	//if( enumClass == NULL ){
	//	warnf(NAME_Error, TEXT("======!!!!======= [UpdateSoulInfo enumClass Not FOUND]") );
	//	return;
	//}

	//current soul property
	const ItemRandomAttr* propAttr = mmoFacade.GetRandomAttributById( pSoulInfo->_AttrID );
	if( propAttr == NULL ){
		warnf(NAME_Error, TEXT("======!!!!======= [UpdateSoulInfo ItemAttr Not FOUND]") );
		return;
	}
	_CurLevelSoulPropTf->SetString( TEXT("htmlText"), propAttr->strText );

	//next level prop
	const SoulInfo* pSoulInfoNextLv = equipMgr.FindSoulInfoByItemTemplateID( pSoulInfo->_UpgradeSoulID );
	if( pSoulInfoNextLv == NULL ){
		//highest level
		return;
	}

	propAttr = mmoFacade.GetRandomAttributById( pSoulInfoNextLv->_AttrID );
	if( propAttr == NULL ){
		warnf(NAME_Error, TEXT("======!!!!======= [UpdateSoulInfo ItemAttr Not FOUND]") );
		return;
	}
	_NextLevelSoulPropTf->SetString( TEXT("htmlText"), propAttr->strText );
}

//=============================================================================================================================
INT UMMOUISoulEmbed::UpdateSuccessRatio()
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	//get soul information
	FClientItemInfo *pLvUpSoulItemInfo = mmoFacade.FindItem( _ToLvUpSoul._ConID, _ToLvUpSoul._SlotID );
	if( pLvUpSoulItemInfo == NULL ){
		//warnf(NAME_Error, TEXT("======!!!!======= [UpdateSuccessRatio FClientItemInfo Not FOUND]") );
		_SuccessRitoTf->SetText( TEXT("") );
		return 0;
	}

	const SoulInfo* pLvUpSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pLvUpSoulItemInfo->m_nTemplateID );
	if( pLvUpSoulInfo == NULL ){
		warnf(NAME_Error, TEXT("======!!!!======= [UpdateSuccessRatio SoulInfo Not FOUND]") );
		return 0;
	}

	//get next level soul information
	const SoulInfo* pNextLvSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pLvUpSoulInfo->_UpgradeSoulID );
	if( pNextLvSoulInfo == NULL ){
		//就认为是最高级了
		_SuccessRitoTf->SetText( TEXT("") );
		return 0;
	}

	INT curValue = 0;
	//吸收的灵魂
	for( INT i = 0; i < MAX_SacrificeSoul; ++i ){
		if( _SacrificeSoul[i]._ConID < 0 || _SacrificeSoul[i]._SlotID < 0 ){
			continue;
		}

		//
		FClientItemInfo *pInfo = mmoFacade.FindItem( _SacrificeSoul[i]._ConID, _SacrificeSoul[i]._SlotID );
		if( pInfo == NULL ){
			warnf(NAME_Error, TEXT("======!!!!======= [UpdateSuccessRatio FClientItemInfo Not FOUND]") );
			continue;
		}

		const SoulInfo* pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pInfo->m_nTemplateID );
		if( pSoulInfo == NULL ){
			warnf(NAME_Error, TEXT("======!!!!======= [UpdateSuccessRatio SoulInfo Not FOUND]") );
			continue;
		}

		//
		curValue += pSoulInfo->_PriceValue;
	}

	//
	INT totalValue = pNextLvSoulInfo->_PriceValue;
	if( totalValue == 0 ){
		warnf(NAME_Error, TEXT("======!!!!======= [SoulInfo data%d ERROR in PriceValue]"), pNextLvSoulInfo->_ItemID );
		totalValue = 1;
	}
	INT rate = curValue * 100 / totalValue;
	if( rate > 100 ){
		rate = 100;
	}

	//提升成功率道具成功率加成
	_HelpLvUpSoulItem;

	//
	FString ritoText = appItoa( rate );
	ritoText += TEXT("%");
	_SuccessRitoTf->SetText( ritoText );

	return rate;
}

//=============================================================================================================================
UBOOL UMMOUISoulEmbed::UnSetLevelUpSoul()
{
	return SetLevelUpSoul( -1, -1 );
}

//=============================================================================================================================
UBOOL UMMOUISoulEmbed::SetLevelUpSoul( INT containerID, INT slotID )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	//设置待升级的魂
	FClientItemInfo *pSoulItemInfo = NULL;
	UItem *pSoulItem = NULL;
	const SoulInfo* pSoulInfo = NULL;
	if( containerID >= 0 && slotID >= 0 ){
		pSoulItemInfo = mmoFacade.FindItem( containerID, slotID );
		if( pSoulItemInfo == NULL ){
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND") ) ,MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND"));
			return FALSE;
		}

		//
		pSoulItem = mmoFacade.FindItemTemplate( pSoulItemInfo->m_nTemplateID );
		if( pSoulItem == NULL ){
			warnf(NAME_Error, TEXT("======!!!!======= [SetLevelUpSoul soul Template Not FOUND]") );
			return FALSE;
		}

		//
		pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pSoulItemInfo->m_nTemplateID );
		if( pSoulInfo == NULL ){
			//放入的不是灵物品
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_NOT_A_SOUL") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_NOT_A_SOUL") );
			return FALSE;
		}

		//
		UBOOL isAlreadyInUse = pSoulItemInfo->IsDragIntoOtherUI > -1;
		if( isAlreadyInUse && ( _ToLvUpSoul._ConID != containerID && _ToLvUpSoul._SlotID != slotID ) ){
			//正在被使用（应该是在灵吸收栏中或是交易中）
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_ITEM_IN_USE") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_ITEM_IN_USE") );
			return FALSE;
		}
	}


	//解锁背包内原先放置的魂
	//UMMOUIBag *pBagPanel = (UMMOUIBag*)MMOUI::FindUIPanel( MMOUI::GetUIManager()->Panel_Bag );
	if( _ToLvUpSoul._ConID >= 0 && _ToLvUpSoul._SlotID >= 0 ){
		//if( pBagPanel != NULL && _ToLvUpSoul._ConID == E_CONSLOT_DEFAULT ){
		MMOFacade::getSingleton().LockItem( _ToLvUpSoul._ConID, _ToLvUpSoul._SlotID, -1 );
		//}
	}

	//清空，取下魂
	if( ( pSoulItemInfo == NULL ) && ( _ToLvUpSoul._ConID >= 0 && _ToLvUpSoul._SlotID >= 0 ) ){
		//if( pBagPanel != NULL && _ToLvUpSoul._ConID == E_CONSLOT_DEFAULT ){
		MMOFacade::getSingleton().LockItem( _ToLvUpSoul._ConID, _ToLvUpSoul._SlotID, -1 );
		//}

		//GFXPlayer->SetItemSlotData( _ToLvUpSoulMc, NULL, ESPType_SoulLevelUp, -1, -1 );
		GFXPlayer->eventCallSetItemData( _ToLvUpSoulMc , 0 , TEXT("") , -1, ESPType_SoulLevelUp, TEXT("") , ITEMCOLOR_INVALID, -1, -1 );

		//
		_ToLvUpSoul._ConID = -1;
		_ToLvUpSoul._SlotID = -1;

		//刷新信息
		UpdateSoulInfo();

		//成功率刷新
		UpdateSuccessRatio();

		return TRUE;
	}

	//
	_ToLvUpSoul._ConID = containerID;
	_ToLvUpSoul._SlotID = slotID;

	//设置界面ItemSlot
	//GFXPlayer->SetItemSlotData( _ToLvUpSoulMc, pSoulItem, ESPType_SoulLevelUp, _ToLvUpSoul._ConID, _ToLvUpSoul._SlotID );
	if( pSoulItem != NULL ){
		GFXPlayer->eventCallSetItemData( _ToLvUpSoulMc, 1, MMOFacade::getSingleton().GetItemIconNamePersonalized( pSoulItem ), pSoulItem->ItemId, ESPType_SoulLevelUp, TEXT(""), pSoulItem->ItemColor+1, _ToLvUpSoul._ConID, _ToLvUpSoul._SlotID );
	}
	else{
		GFXPlayer->eventCallSetItemData( _ToLvUpSoulMc , 0 , TEXT("") , -1, ESPType_SoulLevelUp, TEXT("") , ITEMCOLOR_INVALID, -1, -1 );
	}

	//锁住背包内原先放置的魂
	//if( pBagPanel != NULL && _ToLvUpSoul._ConID == E_CONSLOT_DEFAULT ){
	MMOFacade::getSingleton().LockItem( _ToLvUpSoul._ConID, _ToLvUpSoul._SlotID, ESPType_SoulLevelUp );
	//}

	//刷新信息
	UpdateSoulInfo();

	//成功率刷新
	UpdateSuccessRatio();

	return TRUE;
}

//=============================================================================================================================
UBOOL UMMOUISoulEmbed::UnSetLevelUpSoulSacrifice( INT targetSlotID )
{
	return SetLevelUpSoulSacrifice( -1, -1, targetSlotID );
}

//=============================================================================================================================
INT UMMOUISoulEmbed::AutoSetLevelUpSoulSacrifice( int containerID, int slotID )
{
	INT idx = 0;
	for( ; idx < MAX_SacrificeSoul; ++idx ){
		if( _SacrificeSoul[idx]._ConID < 0 ){
			break;
		}
	}

	//
	if( idx < MAX_SacrificeSoul ){
		UBOOL isSuccess = SetLevelUpSoulSacrifice( containerID, slotID, idx );
		if( isSuccess != TRUE ){
			idx = -1;
		}
	}
	else{
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_SOUL_SACRIFICE_FULL") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_SOUL_SACRIFICE_FULL") );
		idx = -1;
	}

	return idx;
}

//=============================================================================================================================
UBOOL UMMOUISoulEmbed::SetLevelUpSoulSacrifice( INT containerID, INT slotID, INT targetSlotID )
{
	MMOFacade &mmoFacade = MMOFacade::getSingleton();
	MMOEquipManager &equipMgr = MMOEquipManager::getSingleton();

	//
	if( targetSlotID < 0 || targetSlotID >= MAX_SacrificeSoul ){
		return FALSE;
	}
	UGFxObject *pSlotMc = _SacrificeSoulMc[targetSlotID];
	FOperationItemBagPos &toSacrifySoulPos = _SacrificeSoul[targetSlotID];

	//设置吸收的魂
	FClientItemInfo *pSoulItemInfo = NULL;
	UItem *pSoulItem = NULL;
	const SoulInfo* pSoulInfo = NULL;
	if( containerID >= 0 && slotID >= 0 ){
		pSoulItemInfo = mmoFacade.FindItem( containerID, slotID );
		if( pSoulItemInfo == NULL ){
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_ITEM_NOT_FOUND") );
			return FALSE;
		}

		//
		pSoulItem = mmoFacade.FindItemTemplate( pSoulItemInfo->m_nTemplateID );
		if( pSoulItem == NULL ){
			warnf(NAME_Error, TEXT("======!!!!======= [SetLevelUpSoul soul Template Not FOUND]") );
			return FALSE;
		}

		//
		pSoulInfo = equipMgr.FindSoulInfoByItemTemplateID( pSoulItemInfo->m_nTemplateID );
		if( pSoulInfo == NULL ){
			//放入的不是灵物品
			MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_NOT_A_SOUL") ) ,MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_NOT_A_SOUL"));
			return FALSE;
		}

		//
		UBOOL isAlreadyInUse = pSoulItemInfo->IsDragIntoOtherUI > -1;
		if( isAlreadyInUse ){
			//
			UBOOL isInLevelUpSlot = IsInLevelUpSoulSlot( containerID, slotID );
			if( pSoulItemInfo->IsDragIntoOtherUI == ESPType_SoulLevelUp && !isInLevelUpSlot ){
				UBOOL isEnough = IsEnoughSoulsCanAddMoreScrifice( containerID, slotID );
				if( !isEnough ){
					//放入的灵堆叠数量不够
					MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_NOT_ENOUGH_SOUL") ),MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_NOT_ENOUGH_SOUL") );
					return FALSE;
				}
			}
			else{
				//正在被使用（应该是在灵升级栏中或是交易中）
				MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Soul.ERROR_ITEM_IN_USE") ) ,MsgInfoType_Table,TEXT("MMOGame.Soul.ERROR_ITEM_IN_USE"));
				return FALSE;
			}
		}
	}


	//解锁背包内原先放置的魂
	//UMMOUIBag *pBagPanel = (UMMOUIBag*)MMOUI::FindUIPanel( MMOUI::GetUIManager()->Panel_Bag );
	if( ( pSoulItemInfo == NULL ) && ( toSacrifySoulPos._ConID >= 0 && toSacrifySoulPos._SlotID >= 0 ) ){
		//清空，取下魂
		//if( pBagPanel != NULL && toSacrifySoulPos._ConID == E_CONSLOT_DEFAULT ){
		INT puttedCnt = 0;
		for( INT i = 0; i < MAX_SacrificeSoul; ++i ){
			if( _SacrificeSoul[i]._ConID == toSacrifySoulPos._ConID && _SacrificeSoul[i]._SlotID == toSacrifySoulPos._SlotID ){
				++puttedCnt;
			}
		}

		if( puttedCnt <= 1 ){
			MMOFacade::getSingleton().LockItem( toSacrifySoulPos._ConID, toSacrifySoulPos._SlotID, -1 );
		}	
		//}

		//GFXPlayer->SetItemSlotData( pSlotMc, NULL, ESPType_SoulLevelUp, -1, -1 );
		GFXPlayer->eventCallSetItemData( pSlotMc , 0 , TEXT("") , -1, ESPType_SoulLevelUp, TEXT("") , ITEMCOLOR_INVALID, -1, -1 );

		//
		toSacrifySoulPos._ConID = -1;
		toSacrifySoulPos._SlotID = -1;

		//成功率刷新
		UpdateSuccessRatio();

		return TRUE;
	}

	//
	toSacrifySoulPos._ConID = containerID;
	toSacrifySoulPos._SlotID = slotID;

	//设置界面ItemSlot
	//GFXPlayer->SetItemSlotData( pSlotMc, pSoulItem, ESPType_SoulLevelUp, toSacrifySoulPos._ConID, toSacrifySoulPos._SlotID );
	if( pSoulItem != NULL ){
		GFXPlayer->eventCallSetItemData( pSlotMc, 1, MMOFacade::getSingleton().GetItemIconNamePersonalized( pSoulItem ), pSoulItem->ItemId, ESPType_SoulLevelUp, TEXT(""), pSoulItem->ItemColor+1, toSacrifySoulPos._ConID, toSacrifySoulPos._SlotID );
	}
	else{
		GFXPlayer->eventCallSetItemData( pSlotMc , 0 , TEXT("") , -1, ESPType_SoulLevelUp, TEXT("") , ITEMCOLOR_INVALID, -1, -1 );
	}

	//锁住背包内原先放置的魂
	//if( pBagPanel != NULL && toSacrifySoulPos._ConID == E_CONSLOT_DEFAULT ){
	MMOFacade::getSingleton().LockItem( toSacrifySoulPos._ConID, toSacrifySoulPos._SlotID, ESPType_SoulLevelUp );
	//}

	//成功率刷新
	UpdateSuccessRatio();

	return TRUE;
}

//
UBOOL UMMOUISoulEmbed::UnSetLevelUpSoulSuccessHelp()
{
	return SetLevelUpSoulSuccessHelp( -1, -1 );
}

UBOOL UMMOUISoulEmbed::SetLevelUpSoulSuccessHelp( INT containerID, INT slotID )
{
	return TRUE;
}

//=============================================================================================================================
void UMMOUISoulEmbed::ConfirmSoulLevelUp()
{
	//if( !IsEquipPuttedInCanOp() ){
	//	//此界面被锁定了，无法进行操作
	//	return;
	//}

	//没有需要升级的灵
	if( _ToLvUpSoul._ConID < 0 || _ToLvUpSoul._SlotID < 0 ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulLevelUp.ERROR_SOUL_NOT_INPUT") ) ,MsgInfoType_Table,TEXT("MMOGame.SoulLevelUp.ERROR_SOUL_NOT_INPUT"));
		return;
	}

	STLIntVector scarificeSoulContVector;
	STLIntVector scarificeSoulSlotVector;
	for( INT i = 0; i < MAX_SacrificeSoul; ++i ){
		if( _SacrificeSoul[i]._ConID < 0 || _SacrificeSoul[i]._SlotID < 0 ){
			continue;
		}
		//
		scarificeSoulContVector.push_back( _SacrificeSoul[i]._ConID );
		scarificeSoulSlotVector.push_back( _SacrificeSoul[i]._SlotID );
	}

	//没有吸收的灵，不可能升级成功
	if( scarificeSoulContVector.empty() ){
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulLevelUp.ERROR_NEED_SACRIFICE_SOUL") ),MsgInfoType_Table,TEXT("MMOGame.SoulLevelUp.ERROR_NEED_SACRIFICE_SOUL") );
		return;
	}
	//
	UINT scarificeSoulCnt = scarificeSoulContVector.size();
	CMessageHandler::GetInstance().Send_UpgradeSoul( _ToLvUpSoul._ConID, _ToLvUpSoul._SlotID, scarificeSoulCnt, scarificeSoulContVector, scarificeSoulSlotVector );
}

//=============================================================================================================================
void UMMOUISoulEmbed::OnNotifySoulLevelUpResult( int result )
{
	if( result != FALSE ){
		//成功，有BagSlotChange通知，那里把刷新做掉了
		//不支持连续升级，这里就置空了
		UnSetLevelUpSoul();

		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulLevelUp.ERROR_SOUL_LEVELUP_SUCCEED") ) ,MsgInfoType_Table,TEXT("MMOGame.SoulLevelUp.ERROR_SOUL_LEVELUP_SUCCEED"));
	}
	else{
		//失败
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulLevelUp.ERROR_SOUL_LEVELUP_FAILED") ) ,MsgInfoType_Table,TEXT("MMOGame.SoulLevelUp.ERROR_SOUL_LEVELUP_FAILED"));
	}
}
//=============================================================================================================================
void UMMOUISoulEmbed::ResetSoulLevelUp()
{
	for( INT i = 0; i < MAX_SacrificeSoul; ++i ){
		if( _SacrificeSoul[i]._ConID >= 0 && _SacrificeSoul[i]._SlotID >= 0 ){
			UnSetLevelUpSoulSacrifice( i );
		}
	}
	//
	UnSetLevelUpSoul();
}
//=============================================================================================================================
UBOOL UMMOUISoulEmbed::IsInLevelUpSoulSlot( INT conID, INT slotID )
{
	return ( _ToLvUpSoul._ConID == conID && _ToLvUpSoul._SlotID == slotID );
}
//
UBOOL UMMOUISoulEmbed::IsInScrificeSoulSlot( INT conID, INT slotID )
{
	UBOOL isIn = FALSE;
	for( INT i = 0; i < MAX_SacrificeSoul; ++i ){
		if( _SacrificeSoul[i]._ConID == conID && _SacrificeSoul[i]._SlotID == slotID ){
			isIn = TRUE;
			break;
		}
	}

	return isIn;
}
//=============================================================================================================================
UBOOL UMMOUISoulEmbed::IsEnoughSoulsCanAddMoreScrifice( INT conID, INT slotID )
{
	if( conID < 0 || slotID < 0 ){
		return FALSE;
	}

	FClientItemInfo *pItemInfo = MMOFacade::getSingleton().FindItem( conID, slotID );
	if( pItemInfo == NULL ){
		return FALSE;
	}

	UINT thisSoulAddCnt = 0;
	for( INT i = 0; i < MAX_SacrificeSoul; ++i ){
		if( _SacrificeSoul[i]._ConID == conID && _SacrificeSoul[i]._SlotID == slotID ){
			++thisSoulAddCnt;
		}
	}

	//
	if( thisSoulAddCnt >= (UINT)pItemInfo->m_nCurDur ){
		return FALSE;
	}

	return TRUE;
}
//=============================================================================================================================
INT UMMOUISoulEmbed::AutoUnSetPackedSoulScrifice( INT conID, INT slotID )
{
	if( conID < 0 || slotID < 0 ){
		return 0;
	}

	FClientItemInfo *pItemInfo = MMOFacade::getSingleton().FindItem( conID, slotID );
	if( pItemInfo == NULL ){
		return 0;
	}

	UINT thisSoulAddCnt = 0;
	UINT allSoulCnt = (UINT)pItemInfo->m_nCurDur;
	for( INT i = 0; i < MAX_SacrificeSoul; ++i ){
		if( _SacrificeSoul[i]._ConID == conID && _SacrificeSoul[i]._SlotID == slotID ){
			++thisSoulAddCnt;
		}
		//
		if( thisSoulAddCnt > allSoulCnt ){
			UnSetLevelUpSoulSacrifice( i );
		}
	}

	INT resultCnt = (thisSoulAddCnt > allSoulCnt ? thisSoulAddCnt - allSoulCnt : 0);

	return resultCnt;
}
//=============================================================================================================================
UBOOL UMMOUISoulEmbed::IsEquipPuttedInCanOp( INT containerID, INT slotID )
{
	UBOOL canOperate = FALSE;
	if( containerID == E_CONSLOT_DEFAULT ){
		canOperate = TRUE;
	}

	return canOperate;
}
//=============================================================================================================================
void UMMOUISoulEmbed::InitSoulLevelUpMc()
{
	_LvUpSoulPanel = GetObject( TEXT("LevelUpSoulPanel") );
	if( _LvUpSoulPanel == NULL ){
		warnf(NAME_Error, TEXT("======!!!!======= [InitSoulLevelUpMc LevelUpSoulPanel in flash not found]") );
		return;
	}
	_ToLvUpSoulMc = _LvUpSoulPanel->GetObject( TEXT("ToLvUpSoulMc") );
	_ToLvUpSoulMc->SetInt( TEXT("EquipID"), ESOLPST_LvUpSoul );
	_ToLvUpSoulMc->SetInt( TEXT("SlotType"), ESPType_SoulLevelUp );

	for( INT i = 0; i < MAX_SacrificeSoul; ++i ){
		FString objName = TEXT("SacrificeSoulMc");
		objName += appItoa( i );
		_SacrificeSoulMc[i] = _LvUpSoulPanel->GetObject( objName );

		_SacrificeSoulMc[i]->SetInt( TEXT("EquipID"), ESOLPST_LvUpScrificSoul1 + i );
		_SacrificeSoulMc[i]->SetInt( TEXT("SlotType"), ESPType_SoulLevelUp );
	}

	_HelpLvUpSoulItemMc = _LvUpSoulPanel->GetObject( TEXT("HelpLvUpSoulItemMc") );
	_HelpLvUpSoulItemMc->SetInt( TEXT("EquipID"), ESOLPST_LvUpHelpItem );
	_HelpLvUpSoulItemMc->SetInt( TEXT("SlotType"), ESPType_SoulLevelUp );
	_HelpLvUpSoulItemMc->SetVisible( FALSE );

	_SuccessRitoTf = _LvUpSoulPanel->GetObject( TEXT("SuccessRitoTf") );
	_CurLevelSoulPropTf = _LvUpSoulPanel->GetObject( TEXT("CurLevelSoulPropTf") );
	_NextLevelSoulPropTf = _LvUpSoulPanel->GetObject( TEXT("NextLevelSoulPropTf") );


	_ConfirmLevelUpBtn = _LvUpSoulPanel->GetObject( TEXT("ConfirmLevelUpBtn") );
	_ConfirmLevelUpBtn->SetString( TEXT("label"), MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulLevelUp.ConfirmLevelUpBtnText") ) );

	_ResetLevelUpBtn = _LvUpSoulPanel->GetObject( TEXT("ResetLevelUpBtn") );
	_ResetLevelUpBtn->SetString( TEXT("label"), MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulLevelUp.ResetBtnText") ) );
}

//=============================================================================================================================
void UMMOUISoulEmbed::Init()
{
	Super::Init();
	//
	UGFxObject *tabBtn = GetObject( TEXT("EmbedTabBtn") );
	if( tabBtn != NULL ){
		tabBtn->SetString( TEXT("label"), MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ConfirmEmbedBtnText") ) );

		TArray<struct FASValue> asFunArgs;
		FASValue asIconPath(EC_EventParm);
		asIconPath.Type = AS_String;
		asIconPath.S = TEXT( "img://MMO_UIImg.img_tab_soul_0" );
		asFunArgs.AddItem( asIconPath );
		tabBtn->Invoke( TEXT("loadPic"), asFunArgs );
	}

	tabBtn = GetObject( TEXT("UnEmbedTabBtn") );
	if( tabBtn != NULL ){
		tabBtn->SetString( TEXT("label"), MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ConfirmUnEmbedBtnText") ) );

		TArray<struct FASValue> asFunArgs;
		FASValue asIconPath(EC_EventParm);
		asIconPath.Type = AS_String;
		asIconPath.S = TEXT( "img://MMO_UIImg.img_tab_soul_1" );
		asFunArgs.AddItem( asIconPath );
		tabBtn->Invoke( TEXT("loadPic"), asFunArgs );
	}

	tabBtn = GetObject( TEXT("LevelUpTabBtn") );
	if( tabBtn != NULL ){
		tabBtn->SetString( TEXT("label"), MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulLevelUp.ConfirmLevelUpBtnText") ) );

		TArray<struct FASValue> asFunArgs;
		FASValue asIconPath(EC_EventParm);
		asIconPath.Type = AS_String;
		asIconPath.S = TEXT( "img://MMO_UIImg.img_tab_soul_2" );
		asFunArgs.AddItem( asIconPath );
		tabBtn->Invoke( TEXT("loadPic"), asFunArgs );
	}

	InitSoulEmbedMc();
	InitSoulUnEmbedMc();
	InitSoulLevelUpMc();
	//
	ResetUI();

	//
	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_SoulEmbed);
	evts.AddItem(GameEvent_SoulUnEmbed);
	evts.AddItem(GameEvent_Item_Delete);
	evts.AddItem(GameEvent_BagSortEnd);
	EventAdapter = new TGameEventAdapter<UMMOUISoulEmbed>(this, evts);
}

void UMMOUISoulEmbed::SetTitleName()
{
	//
	TArray<struct FASValue> asFunArgs;
	FASValue asTitleName(EC_EventParm);
	asTitleName.Type = AS_String;

	switch( _CurType )
	{
	case ESOLPT_Embed:
		{
			asTitleName.S = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.UITitleName") );
		}
		break;
	case ESOLPT_Unembed:
		{
			asTitleName.S = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulUnEmbed.UITitleName") );
		}
		break;
	case ESOLPT_LevelUp:
		{
			asTitleName.S = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulLevelUp.UITitleName") );
		}
		break;
	default:
		break;
	}

	
	asFunArgs.AddItem( asTitleName );
	this->Invoke( TEXT("SetWindowTitle"), asFunArgs );
}
//=============================================================================================================================
void UMMOUISoulEmbed::InitSoulEmbedMc()
{
	if( MAX_SOCKET_COUNT != MAX_EmbedSoul ){
		warnf(NAME_Error, TEXT("======!!!!======= [MAX_SOCKET_COUNT and UCONST_MAX_EmbedSoul Not EQUIE]") );
	}

	_EmbedTabBtn = GetObject( TEXT("EmbedTabBtn") );
	_EmbedSoulPanel = GetObject( TEXT("EmbedSoulPanel") );
	_ToEmbedEquipMc = _EmbedSoulPanel->GetObject( TEXT("ToEmbedEquipMc") );
	_ToEmbedEquipMc->SetInt( TEXT("EquipID"), ESolEbd_EquipToEmbed );
	_ToEmbedEquipMc->SetInt( TEXT("SlotType"), ESPType_SoulEmbed );

	for( INT i = 0; i < MAX_EmbedSoul; ++i ){
		FString objName = TEXT("EmbedSoulSlot");
		objName += appItoa( i );
		_EmbedSoulMc[i]._Slot = _EmbedSoulPanel->GetObject( objName );

		_EmbedSoulMc[i]._Slot->SetInt( TEXT("EquipID"), ESolEbd_EmbedSoul1 + i );
		_EmbedSoulMc[i]._Slot->SetInt( TEXT("SlotType"), ESPType_SoulEmbed );

		FString bgObjName = TEXT("EmbedSoulBgMc");
		bgObjName += appItoa( i );
		_EmbedSoulMc[i]._Bg = _EmbedSoulPanel->GetObject( bgObjName );
	}

	_OriginalPropTf = _EmbedSoulPanel->GetObject( TEXT("OriginalPropTf") );
	_ResultPropTf = _EmbedSoulPanel->GetObject( TEXT("ResultPropTf") );
	_TotalSoulPropTf = _EmbedSoulPanel->GetObject( TEXT("TotalSoulPropTf") );

	_SoulEmbedHintTf = _EmbedSoulPanel->GetObject( TEXT("SoulEmbedHintTf") );
	if( _SoulEmbedHintTf != NULL ){
		_SoulEmbedHintTf->SetString( TEXT("htmlText"), MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.EmbedPanelHint") ) );
	}

	_ConfirmBtn = _EmbedSoulPanel->GetObject( TEXT("ConfirmBtn") );
	_ConfirmBtn->SetString( TEXT("label"), MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ConfirmEmbedBtnText") ) );

	_ResetBtn = _EmbedSoulPanel->GetObject( TEXT("ResetBtn") );
	_ResetBtn->SetString( TEXT("label"), MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ResetBtnText") ) );
}

//=============================================================================================================================
void UMMOUISoulEmbed::InitSoulUnEmbedMc()
{
	if( MAX_SOCKET_COUNT != MAX_EmbedSoul ){
		warnf(NAME_Error, TEXT("======!!!!======= [MAX_SOCKET_COUNT and UCONST_MAX_EmbedSoul Not EQUIE]") );
	}

	_UnEmbedTabBtn = GetObject( TEXT("UnEmbedTabBtn") );
	_UnEmbedSoulPanel = GetObject( TEXT("UnEmbedSoulPanel") );
	_ToUnEmbedEquipMc = _UnEmbedSoulPanel->GetObject( TEXT("ToUnEmbedEquipMC") );
	_ToUnEmbedEquipMc->SetInt( TEXT("EquipID"), ESolEbd_EquipToUnEmbed );
	_ToUnEmbedEquipMc->SetInt( TEXT("SlotType"), ESPType_SoulUnEmbed );

	for( INT i = 0; i < MAX_EmbedSoul; ++i ){
		FString objName = TEXT("UnEmbedSoulSlot");
		objName += appItoa( i );
		_UnEmbedSoulMc[i]._Slot = _UnEmbedSoulPanel->GetObject( objName );

		_UnEmbedSoulMc[i]._Slot->SetInt( TEXT("EquipID"), ESolEbd_UnEmbedSoul1 + i );
		_UnEmbedSoulMc[i]._Slot->SetInt( TEXT("SlotType"), ESPType_SoulUnEmbed );

		FString bgObjName = TEXT("UnEmbedSoulBgMc");
		bgObjName += appItoa( i );
		_UnEmbedSoulMc[i]._Bg = _UnEmbedSoulPanel->GetObject( bgObjName );
	}

	_OriginalPropInUnEmbedTf = _UnEmbedSoulPanel->GetObject( TEXT("OriginalPropInUnEmbedTf") );
	_ResultPropInUnEmbedTf = _UnEmbedSoulPanel->GetObject( TEXT("ResultPropInUnEmbedTf") );
	_TotalSoulPropInUnEmbedTf = _UnEmbedSoulPanel->GetObject( TEXT("TotalSoulPropInUnEmbedTf") );


	_UnEmbedConfirmBtn = _UnEmbedSoulPanel->GetObject( TEXT("UnEmbedConfirmBtn") );
	_UnEmbedConfirmBtn->SetString( TEXT("label"), MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ConfirmUnEmbedBtnText") ) );

	_UnEmbedCancelBtn = _UnEmbedSoulPanel->GetObject( TEXT("UnEmbedCancelBtn") );
	_UnEmbedCancelBtn->SetString( TEXT("label"), MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.SoulEmbed.ResetBtnText") ) );

	_UnEmbedFeeTf = _UnEmbedSoulPanel->GetObject( TEXT("UnEmbedFeeTf") );
}
//============================================================================================================
void UMMOUISoulEmbed::NativeInitLoad()
{	
	Super::NativeInitLoad();

	g_layoutList.push_back(new UILayoutLeftRight(this, MMOUI::GetUIManager()->Panel_Bag));
}
//===============================================================================================================
//===============================================================================================================
//soul embed
void UMMOUISoulEmbed::ASConfirmSoulEmbed()
{
	ConfirmSoulEmbed();
}

//===============================================================================================================
void UMMOUISoulEmbed::ASResetSoulEmbed()
{
	ResetSoulEmbed();
}

//===============================================================================================================
void UMMOUISoulEmbed::ASOnEmbedPanelTabBtnClick( int tabIdx )
{
	OnTabBtnClick( tabIdx );
}

//===============================================================================================================
void UMMOUISoulEmbed::ASConfirmUnEmbed()
{
	ConfirmSoulUnEmbed();
}

//===============================================================================================================
void UMMOUISoulEmbed::ASCancelUnEmbed()
{
	ResetSoulUnEmbed();
}

//===============================================================================================================
void UMMOUISoulEmbed::ASSelectUnEmbedSoul( int idx )
{
	SelectSoulToUnEmbed( idx );
}

//===============================================================================================================
//soul level up
void UMMOUISoulEmbed::ASConfirmSoulLevelUp()
{
	ConfirmSoulLevelUp();
}

//===============================================================================================================
void UMMOUISoulEmbed::ASResetSoulLevelUp()
{
	ResetSoulLevelUp();
}
//===============================================================================================================
//===============================================================================================================