/********************************************************************
	Created:	2012/06
	Filename: 	MMOUISkillPanel
	file ext:	cpp
	Author:		hemu@snda
	Purpose:	MMOUISkillPanel 技能界面，包含以下4块  
				-Console 技能总览
				-Active  主动技能
				  -Rune 符文充能、激活
				  -SkillUp 技能熟练度升级：心练、魂练
				-Passive 被动技能
				-Avarta  Avarta技能
*********************************************************************/

#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "attribute_def.h"
#include "MMOChatManager.h"
#include "MMOMsgBoxManager.h"
#include <deque>
#include "MMOSkillManager.h"


IMPLEMENT_CLASS(UMMOUISkillPanel)

struct sSpellChange
{
	int SlotId;
	int AbilityId;
};

typedef std::deque<sSpellChange, M_UE3_STL_ALLOC(sSpellChange) > SpellChangeDeque;
#if 0
void UMMOUISkillPanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_MainPlayerDataChange);
	EventAdapter = new TGameEventAdapter<UMMOUISkillPanel>(this, evts);
}

//显示的时候做些数据更新
void UMMOUISkillPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	if(v)
	{
		MMOFacade::getSingleton().PlayUISound(TEXT("menu_skillbook_op"));
		//如果可见 则刷新界面显示
		eventIniData();
		eventRefreshData();
	}
	else
	{
		MMOFacade::getSingleton().PlayUISound(TEXT("menu_skillbook_cls"));
	}
}

int UMMOUISkillPanel::GetRealActiveRealSlotId(int activeSlotId )
{
    int realSlotId = 0;
    if( activeSlotId >= 0 && activeSlotId < ActiveRealSlotList.Num() )
    {
        realSlotId = ActiveRealSlotList( activeSlotId ); 
    }
    return realSlotId;
}

void UMMOUISkillPanel::NativeInitOnce()
{
	StrTimeLeft = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Common.TimeLeft") );

	if(!Validate())
		return;


	UGFxObject* obj = GetObject( TEXT("ActiveModify.btn_confirm.textField.textField") );
	if( obj )
	{
		obj->SetText( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Common.Ok") ) );
	}
	
	obj = GetObject( TEXT("ActiveModify.btn_cancel.textField.textField") );
	if( obj )
	{
		obj->SetText( MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Common.Cancel") ) );
	}
	

	EnableSkillUp( true );
}

//发送Slot切换请求 
void UMMOUISkillPanel::SendEquipActive(int activeSlotId,int abilityId )
{
	int realSlotId = GetRealActiveRealSlotId( activeSlotId );
	CMessageHandler::GetInstance().Send_EquipSpell( realSlotId, abilityId ) ; 
}

//发送Passive Slot切换请求
void UMMOUISkillPanel::SendEquipPassive(int passiveSlotId,int abilityId )
{
	//3~5
	CMessageHandler::GetInstance().Send_EquipSpell( passiveSlotId + ECK_Passive1, abilityId ) ; 
}
 

//发送Avarta Slot切换请求
void UMMOUISkillPanel::SendEquipAvarta(int avartaSlotId,int abilityId )
{
	//0~2
	CMessageHandler::GetInstance().Send_EquipSpell( avartaSlotId + ECK_QTE1 , abilityId ) ; 
}

//激活符文
void UMMOUISkillPanel::SendActivateRune( int inSpellId, int runeSlotId)
{
	CMessageHandler::GetInstance().Send_ActivateRune( inSpellId, runeSlotId ) ; 
}

//装配Active符文
void UMMOUISkillPanel::SendEquipActiveRune( int activeSlotId, int runeSlotId )
{
	int realSlotId = GetRealActiveRealSlotId( activeSlotId );
	CMessageHandler::GetInstance().Send_EquipRune( realSlotId, runeSlotId ) ; 
}

//装配Avarta符文
void UMMOUISkillPanel::SendEquipAvartaRune( int avartaSlotId, int runeSlotId)
{
	CMessageHandler::GetInstance().Send_EquipRune( avartaSlotId + ECK_QTE1, runeSlotId ) ; 
}

//同步符文耐久数据
void UMMOUISkillPanel::RuneDurSync( int wSpellID, int byRuneSlot, int byDurabilityType, int nDurability )
{
	/*UMMOAbility* tMainActive = MainPlayer->GetMainAbilityById( wSpellID );
	if ( !tMainActive )
		return;
	UMMOAbility* tRune=NULL;

	if( byRuneSlot <=0 || byRuneSlot > tMainActive->SubRuneList.Num() )
		return;
	tRune = tMainActive->SubRuneList( byRuneSlot-1 );
	if( tRune )
	{
		tRune->RuneDurabilityType = byDurabilityType;
		tRune->RuneDurability = nDurability;
	}*/
}

//激活符文响应 需要UI响应
void UMMOUISkillPanel::RuneActivate( int wSpellID, int byRuneSlot, int byDurabilityType, int nDurability )
{
	/*RuneDurSync(wSpellID,byRuneSlot,byDurabilityType,nDurability);
	OnSelecteActiveChanged( CurrentSelectedActiveId );*/
}

//装配符文响应
void UMMOUISkillPanel::RuneEquip( int bySlot, int wSpellID, int byRuneSlot )
{
/*
	if(	IsVisible )
	{
		if( byRuneSlot == 0 )
		{
			TArray<struct FASValue> Arguments0;
			if( GetObject("ActiveModify") )
				GetObject("ActiveModify")->Invoke("UnselecteAllRune", Arguments0 );
		}
		RefreshAll();
	}*/
}

//==================================================Total()====================================================== 
UBOOL UMMOUISkillPanel::Validate()
{
	if( MainPlayer == NULL)
	{
		return false;
	}
	if( PC == NULL)
	{
		return false;
	}
	if( KeyMapManager == NULL)
	{
		return false;
	}

	return true;
}

//void UMMOUISkillPanel::Open()
//{
//	ToogleVisible();
//}
//
//void UMMOUISkillPanel::OnOpen()
//{
//	eventIniData();
//	//如果可见 则刷新界面显示
//	eventRefreshData();
//}

//重新登录后 重置状态
void UMMOUISkillPanel::EnterLogin( )
{
	//状态清理
	NetStopSkillPractice( NowNormalPracticeActiveId );
	NetStopSkillPractice( NowFastPracticeActiveId );

	//重登后 祥光数据清零
	CurPageType = 0;

	NowActivePageNum = 0;
	NowPassivePageNum = 0;
	NowAvartaPageNum = 0;
	NowAvartaRunePageNum = 0;

	TotalActivePageNum = 0;
	TotalPassivePageNum = 0;
	TotalAvartaPageNum = 0;
	TotalAvartaRunePageNum = 0;

	CurrentActiveSlot = 0;
	CurrentSelectedActiveSlot = 0;
	CurrentSelectedActiveId = 0;
	CurrentSelectedActiveRuneSlot = 0;

	CurrentSelectedAvartaSlot = 0;
	CurrentSelectedAvartaId = 0;
	CurrentSelectedAvartaRuneSlot = 0;

	NowRequestNormalPracticeActiveId = 0;
	NowNormalPracticeActiveId = 0;
	NowNormalPracticeType = 0;
	NowNormalPracticeProgress = 0;

	NowRequestFastPracticeActiveId = 0;
	NowFastPracticeActiveId = 0;
	NowFastPracticeType = 0;
	NowFastPracticeProgress = 0;
	NowPracticeType = 0;
	IsInFastPractice = false;

	StrTimeLeft = "";

	IsRequestCloseNormalSkillPractice = false;
	IsRequestCloseFastSkillPractice = false;
	HasAskStopSkillPractice = false;
}

//SlotChange
void UMMOUISkillPanel::SkillSlotChange()
{
	if( IsVisible )
		RefreshAll();
}

//刷新
void UMMOUISkillPanel::RefreshAll()
{
	if( ! Validate() )
		return;
	RefreshCurrentPage();
	RefreshPage( ESkill_Console );
}

//装备有发生改变
void UMMOUISkillPanel::BagSlotChange(INT BagId,INT SlotId)
{
	if( !IsVisible )
		return;
	//符文碎片有改变时刷新
	if( CurPageType == ESkill_Active )
	{
		if( BagId != E_CONSLOT_DEFAULT )
			return;
		ItemInfo* pItemInfo = NULL;
		pItemInfo = MMOFacade::getSingleton().FindItem( E_CONSLOT_DEFAULT, SlotId );
		if( pItemInfo == NULL )
			return;
		INT iNewItemID = pItemInfo->m_nTemplateID;

		const TArray<INT> *pVecRuneDebrisIds = MMOSkillManager::getSingleton().GetRuneDebrisIds();
		if( !pVecRuneDebrisIds )
			return;
		for ( int i =0 ;i < pVecRuneDebrisIds->Num(); ++i )
		{
			if(  (*pVecRuneDebrisIds)(i) == iNewItemID )
			{
				RefreshCurrentPage();
				return;
			}
		}
	}
}

//刷新当前页面
void UMMOUISkillPanel::RefreshCurrentPage( )
{
	RefreshPage( CurPageType );
}

//刷新页面
void UMMOUISkillPanel::RefreshPage( BYTE tSPT )
{
	if( !IsVisible )
		return;
	switch( tSPT ) 
	{
	case ESkill_Console:
		RefreshCurrentSpell();
		break;
	case ESkill_Active:
		RefreshActiveModify();
		break;
	case ESkill_Passive:
		RefreshPassiveModify();
		break;
	case ESkill_Avarta:
		RefreshAvartaModify();
		break;
	}
}

//页面跳转
void UMMOUISkillPanel::PageJump( BYTE tSPT )
{
	int i;
	if( tSPT == CurPageType)
		return;
	CurPageType = tSPT;
	switch( CurPageType ) 
	{
	case ESkill_Console:
		break;
	case ESkill_Active:
		CurrentActiveSlot = -1;
		for( i = 0; i < CurrentActives.Num() ; ++i )
		{
			CurrentActives( i ).ActiveId = RealActives( i ).ActiveId ;
			CurrentActives( i ).IsChanged = false;
		}
		break;
	case ESkill_Passive:
		CurrentPassiveSlot = -1;
		for( i = 0; i < CurrentPassives.Num() ; ++i )
		{
			CurrentPassives( i ).PassiveId = RealPassives( i ).PassiveId ;
			CurrentPassives( i ).IsChanged = false;
		}
		break;
	case ESkill_Avarta:
		CurrentAvartaSlot = -1;
		for( i = 0; i < CurrentAvartas.Num() ; ++i )
		{
			CurrentAvartas( i ).AvartaId = RealAvartas( i ).AvartaId ;
			CurrentAvartas( i ).IsChanged = false;
		}
		break;
	}
}

void UMMOUISkillPanel::SetLockedState( int slotId, UGFxObject* tObj, int uiSlot )
{
    if( ! Validate() )
        return;
    if( !tObj || !GFXPlayer )
        return;
    UBOOL  isLocked =   KeyMapManager->IsSlotLocked( slotId );
    if( tObj->GetObject("ItemSlot") )
    {
        tObj->GetObject("ItemSlot")->SetBool( "isSlotLocked", isLocked );
    }
    tObj->SetBool("enabled",!isLocked );
   
}

//刷新整体面板
void UMMOUISkillPanel::RefreshCurrentSpell()
{
	if( ! Validate() )
		return;
	int j;
	int CmdSlotId;
	int abilityId;
    UGFxObject* tObj;

	//`log("===========================================RefreshCurrentSpell ()=======================================");

	//---------------------------1 当前技能面板 ---------------------------------------------------------
	
    //1
	//加载当前快捷键装备的主动技能
	for( j = 0; j< 6;j++ )
	{
        int realSlotId = GetRealActiveRealSlotId( j );
		tObj = GetObject("SpellConsole")->GetObject( FString::Printf(TEXT("ActiveSkill%d"),j ) );
		if( tObj == NULL )
		{
			break;
		}
		abilityId = KeyMapManager->GetCmdIDBySlotID( realSlotId );
		
        //根据ActiveId设置Btn
		SetSpellBtnByActiveId( tObj, j, abilityId );
		RealActives( j ).ActiveId = abilityId;
        SetLockedState( realSlotId,  tObj, j );
	}	

	//2
	//加载当前装备的被动技能 
	for( j = 0; j< 3;j++)
	{
		tObj = GetObject("SpellConsole")->GetObject( FString::Printf(TEXT("PassiveSkill%d"),j ) );
		if( tObj == NULL )
		{
			break;
		}
		CmdSlotId = ECK_Passive1 + j;
		abilityId = KeyMapManager->GetCmdIDBySlotID( CmdSlotId );
		SetSpellBtnByPassiveId( tObj, j, abilityId );
		//预留一份真正的数据
		RealPassives( j ).PassiveId = abilityId;
        SetLockedState( CmdSlotId,  tObj, j  );
	}	

	//3
	//加载当前装备的战术技能 
	for( j = 0; j< 3;j++)
	{
		tObj = GetObject("SpellConsole")->GetObject( FString::Printf(TEXT("AvartaSkill%d"),j ) );
		if( tObj == NULL )
		{
			break;
		}
		CmdSlotId = ECK_QTE1 + j;
		abilityId = KeyMapManager->GetCmdIDBySlotID( CmdSlotId );
		SetSpellBtnByAvartaId( tObj,j , abilityId );
		RealAvartas( j ).AvartaId = abilityId;
        SetLockedState( CmdSlotId,  tObj, j  );
	}

    //显示当前技能点
    if(  GetObject("SpellConsole") && GetObject("SpellConsole")->GetObject("tF_spellPoint") )
        GetObject("SpellConsole")->GetObject("tF_spellPoint")->SetText( appItoa( PC->SkillPoint ) );

}
//==================================================RefreshActiveModify()====================================================== 

//设置ActiveBtn
void UMMOUISkillPanel::SetSpellBtnByActiveId(class UGFxObject* tObj,INT SlotId,INT abilityId,UBOOL isSubCtrl)
{
#if M_TEMP_ENABLE_UI_Skill_CODE
	UMMOAbility*  ability;
	if( tObj == NULL )
	{
		return;
	}
	//根据ActiveId设置Btn
	ability = MainPlayer->GetMainAbilityById( abilityId );

	//`log("CurrentSpell Active Add Active ()"@tObj@tObj->GetObject("ItemSlot")@"ActiveId::"@abilityId );
	if( ability != NULL && ability->eventGetAbilityId() >=0  )
	{
		tObj->SetVisible(true);
		tObj->SetBool("enabled",true);
		if( tObj->GetObject("ItemSlot") )
		{
// 			UGFxObject* tItem = tObj->GetObject("ItemSlot") ;
// 			FString iconName = ability->GetAbilityIconName();
// 			FString itemType = TEXT("skill");
			//eventSetItem(tItem ,0 , iconName, abilityId, itemType );
			GFXPlayer->eventCallSetItemData( tObj->GetObject("ItemSlot") , 0 , ability->GetAbilityIconName() , ability->eventGetAbilityId() , ESPType_SkillPanel,TEXT("") );
			//GFXPlayer->eventASSetSlotShowData(tObj->GetObject("ItemSlot") ,0 ,ability->GetAbilityIconName() ,ability->eventGetAbilityId());
			tObj->GetObject("ItemSlot")->SetInt( "SlotType" , ESPType_SkillPanel );
		}
		//tF_SpellName 技能名称
		if( tObj->GetObject("tF_SpellName") )
			tObj->GetObject("tF_SpellName")->SetText( ability->ClientCommonAttribute.AbilityName );
		
		//tF_RuneName 使用的符文
		INT RuneId = ability->GetRuneSlot() ;
		TArray<struct FASValue> Arguments0;
		FASValue ASValue0(EC_EventParm);
		//Icon'
		ASValue0.I = 0;
		ASValue0.Type = AS_Int;
		Arguments0.AddItem(ASValue0);
		//AbilityName
		ASValue0.S = "";
		ASValue0.Type = AS_String;
		Arguments0.AddItem(ASValue0);
		if( RuneId > 0 && ability->SubRuneList.Num() >0 && RuneId <= ability->SubRuneList.Num() )
		{
			UMMOAbility* tRune = ability->SubRuneList( RuneId-1 );
			if( tRune )
			{
				Arguments0(0).I = tRune->GetSkillGuiRuneID(); 
				Arguments0(1).S = tRune->eventGetAbilityName(); 
			}
		}
		tObj->Invoke("SetRuneIcon", Arguments0 );

		//tF_level  等级 
		if( tObj->GetObject("tF_level") )
			tObj->GetObject("tF_level")->SetText( FString::Printf( TEXT("Lv %d"), ability->SpellCommonAttribute.Level ) );

		if( isSubCtrl )
		{
			tObj->SetBool("selected",false);
			//如果这个技能已经装备，则
			if( tObj->GetObject("EquipedCheck") )
			{
				if( IsActiveAlreadyEquiped( abilityId ) >= 0 )
					tObj->GetObject("EquipedCheck")->SetVisible( true );
				else
					tObj->GetObject("EquipedCheck")->SetVisible( false );
			}
			//默认对应的Main技能被选择
			if( abilityId ==  CurrentSelectedActiveId )
				tObj->SetBool("selected",true);
			//记录下对应的abilityId
			tObj->SetInt("ActiveId",abilityId );
			if( tObj->GetObject("lock_mc") )
				tObj->GetObject("lock_mc")->SetVisible( false );
			//如果这个技能不允许被左键装备 
			if( CurrentActiveSlot==0 && ! ability->ClientCommonAttribute.CanLMouseEquip )
			{
				tObj->SetBool("enabled",false);
				if( tObj->GetObject("EquipedCheck") )
					tObj->GetObject("EquipedCheck")->SetVisible( false );
				if( tObj->GetObject("lock_mc") )
					tObj->GetObject("lock_mc")->SetVisible( true );
			}
		}
	}
	else
	{
		if( tObj->GetObject("ItemSlot") )
			eventSetItem(tObj->GetObject("ItemSlot") ,0,"",-1 );
		//tF_SpellName 技能名称
		if( tObj->GetObject("tF_SpellName") )
			tObj->GetObject("tF_SpellName")->SetText( "" );
		//tF_RuneName 使用的符文
		TArray<struct FASValue> Arguments0;
		FASValue ASValue0(EC_EventParm);
		//Icon'
		ASValue0.S = "";
		ASValue0.Type = AS_String;
		Arguments0.AddItem(ASValue0);
		//AbilityName
		ASValue0.S = "";
		ASValue0.Type = AS_String;
		Arguments0.AddItem(ASValue0);
		tObj->Invoke("SetRuneIcon", Arguments0 );

		//tF_level  等级 
		if( tObj->GetObject("tF_level") )
			tObj->GetObject("tF_level")->SetText("");
		if( isSubCtrl )
		{
			tObj->SetBool("selected",false);
			tObj->SetBool("enabled",false);
			if( tObj->GetObject("EquipedCheck") )
				tObj->GetObject("EquipedCheck")->SetVisible( false );
			if( tObj->GetObject("lock_mc") )
				tObj->GetObject("lock_mc")->SetVisible( true );
		}
		else
		{
			if( tObj->GetObject("lock_mc") )
				tObj->GetObject("lock_mc")->SetVisible( false );
		}
	}

#endif
}

//选择当前CurrentActiveSlot
void UMMOUISkillPanel::SetCurrentActive( int activeSlotId )
{
	UGFxObject*  tObj = NULL;
	PageJump( ESkill_Active );
	
	if( activeSlotId >=0 && activeSlotId < CurrentActives.Num() )
	{
		CurrentActiveSlot = activeSlotId;
		if(  GetObject("ActiveModify") )
		{
			//当前装备Active技能
			tObj = GetObject("ActiveModify")->GetObject( TEXT("CurrentSpellSlot") );
			SetSpellBtnByActiveId( tObj,0 , CurrentActives( CurrentActiveSlot ).ActiveId ,false );
			//不可以进行切换
			if( tObj )
				tObj->SetBool( "enabled", false );
		}
		//先主动刷新一遍符文 
		SelectActive( CurrentActiveSlot, CurrentActives( CurrentActiveSlot ).ActiveId );
		RefreshActiveModify();
	}
}

//RefreshActiveModify
void UMMOUISkillPanel::RefreshActiveModify()
{
	int j,k;
	int abilityId;
	int iTotalAbilitiesNum;
	UGFxObject*  tObj = NULL;
	UMMOAbility*  ability;

	//`log("==============================RefreshActiveModify() Opended=================================================");
	if( !Validate() )
		return;
	//--------------------------- 选择技能面板 ---------------------------------------------------------

	if( ! GetObject("ActiveModify") )
		return;
	//当前职业玩家所有学会的Active技能
	k = 0;

	iTotalAbilitiesNum = MainPlayer->Abilities.Num() ;
	//刷新当前页码
	TotalActivePageNum = iTotalAbilitiesNum / MaxActiveModifyCount;
	if( iTotalAbilitiesNum % MaxActiveModifyCount > 0 )
		++TotalActivePageNum;

	TArray<struct FASValue> Arguments0;
	FASValue ASValue0(EC_EventParm);
	ASValue0.I = NowActivePageNum+1;
	ASValue0.Type = AS_Int;
	Arguments0.AddItem(ASValue0);
	ASValue0.I = TotalActivePageNum ; 
	ASValue0.Type = AS_Int;
	Arguments0.AddItem(ASValue0);
	//Invoke
	GetObject("ActiveModify")->Invoke("SetActivePageNum", Arguments0 );

    int currentActiveSlot = GetRealActiveRealSlotId( CurrentSelectedActiveSlot );
	//算出实际显示那些技能
	int iOffset = NowActivePageNum  * MaxActiveModifyCount;
    int activeSlot = 0;;
	for ( j = 0 ;   j < iTotalAbilitiesNum ; ++j )
	{
		ability = MainPlayer->Abilities(j);
		if( ability == NULL )
		{
			continue;
		}

		abilityId = ability->eventGetAbilityId();
		if( abilityId >=0 )
		{
			if(  ( ability->SpellCommonAttribute.CastType == E_spct_Active )
                /*&& ( ability->SpellCommonAttribute.BindSlot == currentActiveSlot )*/
				&& ( ability->SpellCommonAttribute.QTEType == E_spqte_None ) 
                && (  ability->ClientCommonAttribute.ShowOnUI == true ) )
			{
                if( k >= iOffset  &&
                     activeSlot < MaxActiveModifyCount )
                {
                    tObj = GetObject("ActiveModify")->GetObject( FString::Printf(TEXT("spell%d"), activeSlot )  );
                    SetSpellBtnByActiveId( tObj, activeSlot, abilityId, true );
                    ++activeSlot;
                }
                ++k;
			}	
		}
	}
	while( activeSlot < MaxActiveModifyCount )
	{
		tObj = GetObject("ActiveModify")->GetObject( FString::Printf(TEXT("spell%d"), activeSlot ) );
		SetSpellBtnByActiveId( tObj, activeSlot, 0 , true );
		++activeSlot;
	}
	//刷一遍符文
	OnSelecteActiveChanged( CurrentSelectedActiveId );

}

//选择CurrentActiveSlot 切换成的对应 AllActives( abilityId ) 的 ActiveId
void UMMOUISkillPanel::SelectActive( int tSlotId,int abilityId )
{
	if( CurrentSelectedActiveSlot != tSlotId || CurrentSelectedActiveId != abilityId )
	{
		CurrentSelectedActiveSlot = tSlotId;
		CurrentSelectedActiveId = abilityId;
		OnSelecteActiveChanged( CurrentSelectedActiveId );
	}
}

//符文,技能点等刷新显示
void UMMOUISkillPanel::OnSelecteActiveChanged( int abilityId )
{
	//面板都挂了 啥也不干
	if( !GetObject("ActiveModify") )
		return;
	//心练面板如果打开 也刷新一遍
	UGFxObject* tNormalPractice = GetObject("ActiveModify")->GetObject("NormalPractice");
	UGFxObject* tFastPractice = GetObject("ActiveModify")->GetObject("FastPractice");
	if( tNormalPractice && tNormalPractice->GetBool("visible") )
		ASClickNormalPractice( false );
	else if( tFastPractice && tFastPractice->GetBool("visible") && ! IsInFastPractice )
		ASClickFastPractice( false );
	//刷新abilityId对应的所有符文
	int iRune = 0;
	//UINT Key = MMO::Facade::CombinateID( abilityId, level ,0 );
	//UMMOAbility* pAbility = MMOSkillManager::getSingleton().FindAbilityTemplate(Key);
	UMMOAbility* tMainActive = MainPlayer->GetMainAbilityById( abilityId );
	//当前如果装配的已经是符文技能 则选择其主技能 
	if( tMainActive )
	{
		//确定装备的符文
		CurrentSelectedActiveRuneSlot = tMainActive->GetRuneSlot();
	}
	else
		CurrentSelectedActiveRuneSlot = 0;

	//清理选择的符文栏
	TArray<struct FASValue> Arguments0;
	GetObject("ActiveModify")->Invoke("UnselecteAllRune", Arguments0 );

	//设置当前技能点数 及技能升级进度
	TArray<struct FASValue> Arguments2;
	FASValue ASValue0(EC_EventParm);
	//Icon'
	ASValue0.I = PC->SkillPoint;
	ASValue0.Type = AS_Int;
	Arguments2.AddItem(ASValue0);
	if( tMainActive )
		ASValue0.I = tMainActive->SkillPracticeProgress;
	else
		ASValue0.I = 0;
	ASValue0.Type = AS_Int;

	Arguments2.AddItem(ASValue0);
	GetObject("ActiveModify")->Invoke("SetSkillPoint", Arguments2 );

	UMMOAbility* tRune=NULL;
	//显示当前技能所有的符文 
	int byRuneSlot = 0;
	if( tMainActive )
		byRuneSlot = tMainActive->GetRuneSlot();
	if( byRuneSlot <= 0 )
	{
		TArray<struct FASValue> Arguments0;
		GetObject("ActiveModify")->Invoke("UnselecteAllRune", Arguments0 );
	}

	while( tMainActive && iRune < tMainActive->SubRuneList.Num() ) 
	{
		tRune = tMainActive->SubRuneList( iRune );
		SetRuneBtnByAbility( tRune,iRune );
		++iRune;
	} 
	//剩下不显示 
	while( iRune < ActiveRuneCount )
	{
		SetRuneBtnByAbility( NULL, iRune );
        ++iRune;
	}

    //如果选择了一个空技能 则清空符文按钮也不显示
    UGFxObject* btnClear = GetObject("ActiveModify")->GetObject("btn_clear");
    if( !tMainActive && btnClear )
    {
        btnClear->SetVisible( false );
    }
    else if( btnClear )
    {
        btnClear->SetVisible( true );
    }

	//当前符文碎片数量
	const TArray<INT> *pVecRuneDebrisIds = MMOSkillManager::getSingleton().GetRuneDebrisIds();
	if( pVecRuneDebrisIds )
	{
		for ( int i =0 ;i < pVecRuneDebrisIds->Num(); ++i )
		{
			UGFxObject* tObj = GetObject("ActiveModify")->GetObject( FString::Printf(TEXT("tF_runeCost%d"),i )  );
			if( !tObj )
				continue;
			UItem* item;
			item = NULL;
			if( MainPlayer->ItemManager != NULL)
				item = MainPlayer->ItemManager->GetItemById( (*pVecRuneDebrisIds)(i),E_CONSLOT_DEFAULT);
			//如果有这个碎片，则显示当前拥有的数量
			if( item )
				tObj->SetText( appItoa( item->DefaultDuration ) );
			else
				tObj->SetText( appItoa( 0 ) );
		}
	}
}

//判断当前符文是否能被激活
UBOOL UMMOUISkillPanel::CanActiveRune( UMMOAbility* tRune )
{
	//耐久为满 不需要激活
	if( tRune->RuneDurability >= tRune->RuneDurMax )
		return FALSE;
	//当前符文碎片数量
	const TArray<INT> *pVecRuneDebrisIds = MMOSkillManager::getSingleton().GetRuneDebrisIds();
	UItem* item;
	if(  MainPlayer->ItemManager == NULL )
		return FALSE;
	if( !pVecRuneDebrisIds )
		return FALSE;
	for ( int i =0 ;i < pVecRuneDebrisIds->Num(); ++i )
	{
		if( tRune->vecRuneDebris(i).ItemCount > 0)
		{
			item = MainPlayer->ItemManager->GetItemById( (*pVecRuneDebrisIds)(i),E_CONSLOT_DEFAULT);
			//如果有这个碎片，则显示当前拥有的数量
			if( item && i < tRune->vecRuneDebris.Num() )
			{
				//当前碎片拥有量小于当前符文所需最小激活量
				if( item->DefaultDuration < tRune->vecRuneDebris(i).ItemCount )
					return FALSE;
			}
			else
				return FALSE;
		}	
	}
	return TRUE;
}

//设置RuneBtn
void UMMOUISkillPanel::SetRuneBtnByAbility( UMMOAbility* tRune,int iRuneSlot )
{
	UGFxObject* tObj = GetObject("ActiveModify")->GetObject( FString::Printf(TEXT("btn_rune%d"),iRuneSlot )  );
	//UGFxObject* tObj = GetObject("ActiveModify")->GetObject( FString::Printf(TEXT("spell%d"),iRuneSlot )  );

	UGFxObject* tActiveBtn = GetObject("ActiveModify")->GetObject( FString::Printf(TEXT("btn_active%d"),iRuneSlot )  );
	if( !tObj  )
		return;
	if( tRune != NULL )
	{
		tObj->SetVisible( true );

        if( CurrentSelectedActiveRuneSlot == iRuneSlot+1 )
            tObj->SetBool("selected",TRUE );  
        else
            tObj->SetBool("selected",FALSE );  
		//tObj->SetString("RuneIconName",tRune->GetRuneIconName() );

		TArray<struct FASValue> Arguments0;
		FASValue ASValue0(EC_EventParm);
		//Icon'
		ASValue0.I = tRune->GetSkillGuiRuneID() ; //"img://MMO_UIIcon.Rune.2003_Rune2_"
		ASValue0.Type = AS_Int;
		Arguments0.AddItem(ASValue0);
		//AbilityName
		ASValue0.S = tRune->eventGetAbilityName() ; 
		ASValue0.Type = AS_String;
		Arguments0.AddItem(ASValue0);
		//Invoke
		tObj->Invoke("SetRuneIcon", Arguments0 );
	
		TArray<struct FASValue> Arguments;
		FASValue ASValue(EC_EventParm);
		//ActiveID
		ASValue.I = tRune->eventGetAbilityId();
		ASValue.Type = AS_Int;
		Arguments.AddItem(ASValue);
		//RuneDurability
		ASValue.I = tRune->RuneDurability;
		ASValue.Type = AS_Int;
		Arguments.AddItem(ASValue);
		//RuneDurMax
		ASValue.I = tRune->RuneDurMax;
		ASValue.Type = AS_Int;
		Arguments.AddItem(ASValue);
		//CanActiveRune
		ASValue.B = CanActiveRune( tRune );
		ASValue.Type = AS_Boolean;
		Arguments.AddItem(ASValue);
		//Invoke
		tObj->Invoke("SetCurDur", Arguments );
	}
	else
	{
		tObj->SetVisible( false );
		if( tObj->GetObject("tF_runeName") )
			tObj->GetObject("tF_runeName")->SetText( "" );
		tActiveBtn->SetVisible( false );
	}
}

//点击装配符文
void UMMOUISkillPanel::EquipRune( int runeSlotId)
{
	/*UMMOAbility* tMainActive = MainPlayer->GetMainAbilityById( CurrentActives( CurrentSelectedActiveSlot ).ActiveId );
	if ( !tMainActive )
		return;
	UMMOAbility* tRune=NULL;
	//显示当前技能所有的符文 
	if( runeSlotId < tMainActive->SubRuneList.Num() ) 
		tRune = tMainActive->SubRuneList( runeSlotId );

	if( CanActiveRune( tRune ) )*/
	CurrentSelectedActiveRuneSlot = runeSlotId +1 ;
	//确定之后再予发送消息
	//SendEquipActiveRune( CurrentSelectedActiveSlot,runeSlotId );
}

//点击激活符文 0~4 
void UMMOUISkillPanel::ActivateRune( int runeSlotId)
{
	/*int iOffset = NowActivePageNum  * MaxActiveModifyCount;
	if(  CurrentSelectedActiveSlot + iOffset >= MainPlayer->Abilities.Num() )
		return;*/

	UMMOAbility* tMainActive = MainPlayer->GetMainAbilityById( CurrentSelectedActiveId );
	if ( !tMainActive )
		return;
	UMMOAbility* tRune=NULL;
	//显示当前技能所有的符文 
	if( runeSlotId >= 0 && runeSlotId < tMainActive->SubRuneList.Num() ) 
		tRune = tMainActive->SubRuneList( runeSlotId );
	if( !tRune )
		return;
	//本地Rune的索引是0~4 服务器是按1~5
	if( CanActiveRune( tRune ) )
		SendActivateRune( CurrentSelectedActiveId, runeSlotId +1  );
}

//取消符文装配
void UMMOUISkillPanel::CleanRune( )
{
	SendEquipActiveRune( CurrentSelectedActiveSlot, 0 );
}

//Active是否已经被装备
int UMMOUISkillPanel::IsActiveAlreadyEquiped( int abilityId )
{
	int i;
	for( i = 0; i < CurrentActives.Num() ; ++i )
	{
		if( CurrentActives( i ).ActiveId ==  abilityId )
			return i;
	}
	return -1;
}

//Tab键直接切换左右键技能
void UMMOUISkillPanel::ReplaceHotSkill( )
{
    //技能与Slot绑定，Tab切换功能取消
    return;

	/*if( Validate() && MMO::GetCurrentGameState() == EGameState_InGame )
	{
		int FirsabilityId  =  KeyMapManager->GetCmdIDBySlotID( GetRealActiveRealSlotId(0) );
		int SecondActiveId =  KeyMapManager->GetCmdIDBySlotID( GetRealActiveRealSlotId(1) );
        
        //会出现EmptyCmd 
        if( FirsabilityId < 0 )
        {
            FirsabilityId = 0;
        }

        if( SecondActiveId < 0 )
        {
            SecondActiveId = 0;
        }

        //切换技能 
        SendEquipActive( 0,  0 );
        SendEquipActive( 1,  FirsabilityId );
        SendEquipActive( 0,  SecondActiveId );
	}*/
}


//技能升级---------------------------------------------------------------------------------------start

//中止技能升级确认
void UMMOUISkillPanel::StopSkillPracticeOk(UGFxObject* mc)
{
	HasAskStopSkillPractice = false;
	if( mc != NULL )
	{
		INT ActiveId = mc->GetInt("iteminfoid");
		if( NowNormalPracticeActiveId == ActiveId )
			IsRequestCloseNormalSkillPractice = TRUE;
		else if(  NowFastPracticeActiveId == ActiveId )
			IsRequestCloseFastSkillPractice = TRUE;
		ASStopPractice(ActiveId);
	}
}

//中止技能升级取消
void UMMOUISkillPanel::StopSkillPracticeCancel(UGFxObject* mc)
{
	HasAskStopSkillPractice = false;
}

//设置心练面板
void UMMOUISkillPanel::ASClickNormalPractice(UBOOL IsToggle  )
{
	if( !GetObject("ActiveModify") )
		return;
	UGFxObject* tObj = GetObject("ActiveModify")->GetObject("NormalPractice");
	if( !tObj )
		return;
	UMMOAbility*  ability;
	ability = MainPlayer->GetMainAbilityById( CurrentSelectedActiveId );
	if( !ability  )
		return;
	//当前是否在魂炼 且是当前选择的技能
	if( ability->SkillPracticeType == SkillPT_Fast  )
	{
		if( !HasAskStopSkillPractice )
		{
			//提示是否取消之前的魂练状态
			FString sMsg = FString::Printf(*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Skill.StopSkillPracticeFast") ),
				*(ability->ClientCommonAttribute.AbilityName) );

			FScriptDelegate funcOk(EC_EventParm);
			funcOk.FunctionName = "StopSkillPracticeOk";
			funcOk.Object = this;
			FScriptDelegate funcCancel(EC_EventParm);
			funcCancel.FunctionName = "StopSkillPracticeCancel";
			funcCancel.Object = this;
			MMOMsgBoxManager::getSingleton().AddMessageBox( sMsg , ability->eventGetAbilityId() ,funcOk,  funcCancel );
		}
		return;
	}
	//不在魂练 但是魂练面板已经打开 且是当前的技能 则直接将其关闭
	if( NowRequestFastPracticeActiveId == CurrentSelectedActiveId && GetObject("ActiveModify")->GetObject("FastPractice") )
		GetObject("ActiveModify")->GetObject("FastPractice")->SetVisible( false );

	//重复点击 Toogle
	if( CurrentSelectedActiveId == NowRequestNormalPracticeActiveId && IsToggle && tObj->GetBool("visible") )
	{
		TArray<struct FASValue> Arguments;
		FASValue ASValue(EC_EventParm);
		Arguments.AddItem(ASValue);
		tObj->Invoke("Close", Arguments );
	}
	
	NowRequestNormalPracticeActiveId = CurrentSelectedActiveId;
	//设置心练面板

	//设置ItemSlot
	if( tObj->GetObject("ActiveSlot") )
	{
		GFXPlayer->eventCallSetItemData( tObj->GetObject("ActiveSlot") , 0 , ability->GetAbilityIconName() , ability->eventGetAbilityId() , ESPType_SkillPanel,TEXT("") );
		tObj->GetObject("ActiveSlot")->SetInt( "SlotType" , ESPType_SkillPanel );
	}
	/*
	SetFastPracticeData
	( 
	inActiveId:int,
	HasFastPracticing:Boolean,
	TimeLeft:String,
	inPercent:int,
	inType:int,
	IsPracticing:Boolean 
	)
	*/
	TArray<struct FASValue> Arguments2;
	FASValue ASValue0(EC_EventParm);
	//inActiveId 技能ID
	ASValue0.I = ability->eventGetAbilityId();
	ASValue0.Type = AS_Int;
	Arguments2.AddItem(ASValue0);
	//HasFastPracticing 是否有其他魂练在进行
	ASValue0.B = NowFastPracticeActiveId ?true:false;
	ASValue0.Type = AS_Boolean;
	Arguments2.AddItem(ASValue0);
	//TimeLeft 升级剩余时间 Tick中开始刷新显示
	ASValue0.S = StrTimeLeft +  "";  //StrTimeLeft + MMOFacade::getSingleton().TimeDisplay( (DWORD)ability->SkillPracticeEndTime );
	ASValue0.Type = AS_String;
	Arguments2.AddItem(ASValue0);
	//inPercent 技能熟练度
	ASValue0.I = ability->SkillPracticeProgress;
	ASValue0.Type = AS_Int;
	Arguments2.AddItem(ASValue0);
	//inType 修炼Type
	ASValue0.I = ability->SkillPracticeCostType > 0 ? ability->SkillPracticeCostType : 1 ;
	ASValue0.Type = AS_Int;
	Arguments2.AddItem(ASValue0);
	//IsPracticing 是否在修炼
	ASValue0.B = ability->SkillPracticeCostType > 0 ? true:false;
	ASValue0.Type = AS_Boolean;
	Arguments2.AddItem(ASValue0);
	tObj->Invoke("SetNormalPracticeData", Arguments2 );

	//刷入状态 可能没有开始 但是之前已经有熟练度 
	NowNormalPracticeActiveId = CurrentSelectedActiveId;
	NetSkillProgressChange( CurrentSelectedActiveId,ability->SkillPracticeProgress );

}

//设置魂练面板
void UMMOUISkillPanel::ASClickFastPractice(UBOOL IsToggle  )
{
	if( !GetObject("ActiveModify") )
		return;
	UGFxObject* tObj = GetObject("ActiveModify")->GetObject("FastPractice");
	if( !tObj )
		return;
	UMMOAbility*  ability;
	ability = MainPlayer->GetMainAbilityById( CurrentSelectedActiveId );
	if( !ability )
		return;
	//当前是否在魂炼 且是当前选择的技能
	if(  ability->SkillPracticeType == SkillPT_Fast  )
	{
		//提示是否取消之前的魂练状态
		if( !HasAskStopSkillPractice )
		{
			//提示是否取消之前的魂练状态
			FString sMsg = FString::Printf(*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Skill.StopSkillPracticeFast") ),
				*(ability->ClientCommonAttribute.AbilityName ) );
			FScriptDelegate funcOk(EC_EventParm);
			funcOk.FunctionName = "StopSkillPracticeOk";
			funcOk.Object = this;
			FScriptDelegate funcCancel(EC_EventParm);
			funcCancel.FunctionName = "StopSkillPracticeCancel";
			funcCancel.Object = this;
			MMOMsgBoxManager::getSingleton().AddMessageBox( sMsg , ability->eventGetAbilityId() ,funcOk,  funcCancel );
		}
		return;
	}
	//如果在心练
	if( ability->SkillPracticeType == SkillPT_Noraml )
	{
		//提示是否取消之前的心练状态
		if( !HasAskStopSkillPractice )
		{
			FString sMsg = FString::Printf(*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Skill.StopSkillPracticeNormal") ),
				*(ability->ClientCommonAttribute.AbilityName ) );
			FScriptDelegate funcOk(EC_EventParm);
			funcOk.FunctionName = "StopSkillPracticeOk";
			funcOk.Object = this;
			FScriptDelegate funcCancel(EC_EventParm);
			funcCancel.FunctionName = "StopSkillPracticeCancel";
			funcCancel.Object = this;
			MMOMsgBoxManager::getSingleton().AddMessageBox( sMsg , ability->eventGetAbilityId() ,funcOk,  funcCancel );
		}
		return;
	}
	//不在心练 但是心练面板已经打开 且是当前的技能 则直接将其关闭
	if( NowRequestNormalPracticeActiveId == CurrentSelectedActiveId && GetObject("ActiveModify")->GetObject("NormalPractice") )
		GetObject("ActiveModify")->GetObject("NormalPractice")->SetVisible( false );
	
	//重复点击 Toogle
	if( CurrentSelectedActiveId == NowRequestFastPracticeActiveId && IsToggle && tObj->GetBool("visible") )
	{
		TArray<struct FASValue> Arguments;
		FASValue ASValue(EC_EventParm);
		Arguments.AddItem(ASValue);
		tObj->Invoke("Close", Arguments );
	}

	NowRequestFastPracticeActiveId = CurrentSelectedActiveId;

	if( tObj->GetObject("ActiveSlot") )
	{
		GFXPlayer->eventCallSetItemData( tObj->GetObject("ActiveSlot") , 0 , ability->GetAbilityIconName() , ability->eventGetAbilityId() , ESPType_SkillPanel,TEXT("") );
		tObj->GetObject("ActiveSlot")->SetInt( "SlotType" , ESPType_SkillPanel );
	}
	TArray<struct FASValue> Arguments2;
	FASValue ASValue0(EC_EventParm);
	//inActiveId 技能ID
	ASValue0.I = ability->eventGetAbilityId();
	ASValue0.Type = AS_Int;
	Arguments2.AddItem(ASValue0);
	//inPercent 技能熟练度
	ASValue0.I = ability->SkillPracticeProgress;
	ASValue0.Type = AS_Int;
	Arguments2.AddItem(ASValue0);
	tObj->Invoke("SetFastPracticeData", Arguments2 );

	//刷入状态
	NowFastPracticeActiveId = CurrentSelectedActiveId;
	NetSkillProgressChange( CurrentSelectedActiveId,ability->SkillPracticeProgress );
	
}

//选择心练类型
void UMMOUISkillPanel::ASChooseNormalParcticeType( int NPType )
{
	NowNormalPracticeType = NPType;
}

//选择魂练类型
void UMMOUISkillPanel::ASChooseFastPracticeType( int FPType )
{
    NowFastPracticeType = FPType;
}

//开始心练
void UMMOUISkillPanel::ASStartNormalPractice()
{
	if( !Validate() )
		return;
	UMMOAbility*  ability;
	ability = MainPlayer->GetMainAbilityById( NowRequestNormalPracticeActiveId );
	if( ability )
	{
		//@Todo 最大技能等级宏
		if( 0 == ability->LvUpRequirePoints && ability->SpellCommonAttribute.Level >= 5 )
		{
			//LvUpRequirePoints 则说当前技能升到了最高级别 不需要要再升级
			//提示是否取消之前的魂练状态
			FString sMsg = FString::Printf(*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Skill.SkillAlreadyMax") ),
				*(ability->ClientCommonAttribute.AbilityName) );
			FScriptDelegate funcNULL(EC_EventParm);
			MMOMsgBoxManager::getSingleton().AddMessageBox( sMsg , ability->eventGetAbilityId() ,funcNULL,  funcNULL );
			return;
		}
		CMessageHandler::GetInstance().Send_StartNormalPractice( NowNormalPracticeType ,NowRequestNormalPracticeActiveId ) ; 
	}
}

//开始魂练
void UMMOUISkillPanel::ASStartFastPractice( )
{
	if( !Validate() )
		return;
	UMMOAbility*  ability;
	ability = MainPlayer->GetMainAbilityById( NowRequestFastPracticeActiveId );
	if( ability )
	{
		//@Todo 最大技能等级宏
		if( 0 == ability->LvUpRequirePoints && ability->SpellCommonAttribute.Level >= 5 )
		{
			//LvUpRequirePoints 则说当前技能升到了最高级别 不需要要再升级
			//提示是否取消之前的魂练状态
			FString sMsg = FString::Printf(*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Skill.SkillAlreadyMax") ),
				*(ability->ClientCommonAttribute.AbilityName) );
			FScriptDelegate funcNULL(EC_EventParm);
			MMOMsgBoxManager::getSingleton().AddMessageBox( sMsg , ability->eventGetAbilityId() ,funcNULL,  funcNULL );
			return;
		}
		CMessageHandler::GetInstance().Send_StartFastPractice(  NowFastPracticeType ,NowRequestFastPracticeActiveId ) ; 
	}
}

//魂练用药
void UMMOUISkillPanel::ASUseFastPracticeItem( int FPItem )
{
	//开始心练
	CMessageHandler::GetInstance().Send_SpeedUpFastPractice( FPItem ,NowFastPracticeActiveId ) ; 
}

//中止当前正在修炼的技能
void UMMOUISkillPanel::ASStopPractice( INT inActiveId )
{
	CMessageHandler::GetInstance().Send_StopPractice( inActiveId  ) ; 
}

//中止并关闭技能升级面板
void UMMOUISkillPanel::ASStopPracticeAndClose( int inActiveId,BYTE spt )
{
	if( spt == SkillPT_Noraml )
		IsRequestCloseNormalSkillPractice = TRUE;
	else if(  spt == SkillPT_Fast )
		IsRequestCloseFastSkillPractice = TRUE;
	ASStopPractice( inActiveId );
}

//开始技能升级
void UMMOUISkillPanel::NetStartSkillPractice(int inActiveId,int byPracticeType,int	nInterval,int nEndTime )
{
	if( !GetObject("ActiveModify") )
		return;
	UMMOAbility*  ability;
	ability = MainPlayer->GetMainAbilityById( inActiveId );
	if( ability )
	{
		//ability->SkillProgress = ;
		ability->SkillPracticeType = byPracticeType; 
		ability->SkillPracticeEndTime = (DWORD)nEndTime ;

	}

	TArray<struct FASValue> Arguments2;
	FASValue ASValue0(EC_EventParm);
	//是否开始
	ASValue0.B = true;
	ASValue0.Type = AS_Boolean;
	Arguments2.AddItem(ASValue0);

	NowPracticeType = byPracticeType;
	if( SkillPT_Noraml == NowPracticeType )
	{
		
		NowNormalPracticeActiveId = inActiveId;
		UGFxObject* tObj = GetObject("ActiveModify")->GetObject("NormalPractice");
		if( tObj )
		{
			tObj->Invoke("SetStarted", Arguments2 );
		}

		if( ability )
			ability->SkillPracticeCostType = NowNormalPracticeType; //刚才选择的最后类型 

	}
	else if( SkillPT_Fast == NowPracticeType )
	{
		IsInFastPractice = true;
		NowFastPracticeActiveId = inActiveId;

		UGFxObject* tObj = GetObject("ActiveModify")->GetObject("FastPractice");
		if( tObj )
		{
			tObj->Invoke("SetStarted", Arguments2 );
		}

		if( ability )
			ability->SkillPracticeCostType = NowFastPracticeType; //刚才选择的最后类型 

	}
}

//结束技能升级
void UMMOUISkillPanel::NetStopSkillPractice(int inActiveId)
{
    if( !Validate() )
        return;
	if( !GetObject("ActiveModify") )
		return;

	UMMOAbility*  ability = MainPlayer->GetMainAbilityById( inActiveId );
	if( ability )
	{
        ability->SkillPracticeType = 0;
		ability->SkillPracticeCostType = 0;
	}

	TArray<struct FASValue> Arguments2;
	FASValue ASValue0(EC_EventParm);
	ASValue0.B = false;
	ASValue0.Type = AS_Boolean;
	Arguments2.AddItem(ASValue0);

	if( inActiveId == NowNormalPracticeActiveId )
	{
		NowNormalPracticeActiveId = 0;
		UGFxObject* tObj = GetObject("ActiveModify")->GetObject("NormalPractice");
		if( tObj )
		{
			tObj->Invoke("SetStarted", Arguments2 );

			if( IsRequestCloseNormalSkillPractice )
			{
				tObj->Invoke("ClosePanel", Arguments2 );
				IsRequestCloseNormalSkillPractice = FALSE;
			}
		}
	}
	else if( inActiveId == NowFastPracticeActiveId )
	{
		IsInFastPractice = false;
		NowFastPracticeActiveId = 0;
		UGFxObject* tObj = GetObject("ActiveModify")->GetObject("FastPractice");
		if( tObj )
		{
			tObj->Invoke("SetStarted", Arguments2 );

			if( IsRequestCloseFastSkillPractice )
			{
				tObj->Invoke("ClosePanel", Arguments2 );
				IsRequestCloseFastSkillPractice = FALSE;
			}
		}
	}
}

//更新心练面板
void UMMOUISkillPanel::UpdateNormalPractice( )
{
	if( !GetObject("ActiveModify") )
		return;
	UGFxObject* tObj = GetObject("ActiveModify")->GetObject("NormalPractice");
	if( !tObj )
		return;
	if( !tObj->GetBool("visible") )
		return;
	if( !tObj->GetObject("timeLeft_mc") || ! tObj->GetObject("timeLeft_mc")->GetObject("tF_timeLeft") )
		return;
	UGFxObject* tTimeLeft = tObj->GetObject("timeLeft_mc")->GetObject("tF_timeLeft");
	UMMOAbility*  ability;
	ability = MainPlayer->GetMainAbilityById( CurrentSelectedActiveId );
	if( !ability  )
		return;
	int NowTime = time(NULL);
	int TimeLeft = ability->SkillPracticeEndTime - NowTime;
	//计算剩余时间 
	if( TimeLeft <= 0 )
	{
		TimeLeft = 0;
		//ability->SkillPracticeEndTime = 0;
	}
	FString sSkillPracticeLeftTime =  StrTimeLeft + MMOFacade::getSingleton().TimeDisplay( (DWORD)TimeLeft );
	tTimeLeft->SetText( sSkillPracticeLeftTime  );

}

//PostAdvance
void UMMOUISkillPanel::PostAdvance(float DeltaTime)
{
	ElapsedTime += DeltaTime;
	if( ElapsedTime > UpdateInterval  && MainPlayer )
	{
		UMMOAbility*  ability;
		ability = MainPlayer->GetMainAbilityById( CurrentSelectedActiveId );
		if( !ability  )
			return;
		if( SkillPT_Noraml == ability->SkillPracticeType && ability->SkillPracticeEndTime > 0 )
		{
			UpdateNormalPractice( );
		}
		ElapsedTime = 0;
	}
}

//技能熟练度提醒
void UMMOUISkillPanel::NetSkillProgressChange( int inActiveId,int nProgress )
{
	if( !Validate() )
		return;
	if( !GetObject("ActiveModify") )
		return;
	UMMOAbility*  ability = MainPlayer->GetMainAbilityById( inActiveId );
	if( !ability )
		return;
	ability->SkillPracticeProgress = nProgress;

	//刷新升级进度显示
	TArray<struct FASValue> Arguments2;
	FASValue ASValue0(EC_EventParm);
	ASValue0.I = ability->SpellCommonAttribute.Level;
	ASValue0.Type = AS_Int;
	Arguments2.AddItem(ASValue0);

	ASValue0.I = ability->SkillPracticeProgress ;
	ASValue0.Type = AS_Int;
	Arguments2.AddItem(ASValue0);

	ASValue0.I = ability->LvUpRequirePoints ;
	ASValue0.Type = AS_Int;
	Arguments2.AddItem(ASValue0);

	//在心练时 可以收到其他技能的成长 并不要刷当前面板 
	if(  inActiveId == NowNormalPracticeActiveId )
	{
		UGFxObject* tObj = GetObject("ActiveModify")->GetObject("NormalPractice");
		if( tObj )
		{
			tObj->Invoke("SetPercent", Arguments2 );
		}
	}
	if(  inActiveId == NowFastPracticeActiveId  )
	{
		UGFxObject* tObj = GetObject("ActiveModify")->GetObject("FastPractice");
		if( tObj )
		{
			tObj->Invoke("SetPercent", Arguments2 );
		}
	}
}

//MoneyChange 技能点现在也是一种货币 
void UMMOUISkillPanel::PlayerMoneyChange(BYTE MoneyType, INT DeltaMoney)
{
    if ( MONEYTYPE_SOUL_PTS == MoneyType )
    {
        PC->SkillPoint = MMOFacade::getSingleton().GetPlayerMoney(MoneyType);
        NetSkillPointChangeNotify( );
    }
}

//技能升级提示
void UMMOUISkillPanel::NetSkillPointChangeNotify( )
{
	if( !Validate() )
		return;
	if( IsVisible && PC )
	{
		//显示当前技能点
		if(  GetObject("SpellConsole") && GetObject("SpellConsole")->GetObject("tF_spellPoint") )
			GetObject("SpellConsole")->GetObject("tF_spellPoint")->SetText( appItoa( PC->SkillPoint ) );

		UMMOAbility*  ability = MainPlayer->GetMainAbilityById( CurrentSelectedActiveId );
		if( ability )
		{
			//设置当前技能点数 及技能升级进度
			TArray<struct FASValue> Arguments2;
			FASValue ASValue0(EC_EventParm);
			ASValue0.I = PC->SkillPoint;
			ASValue0.Type = AS_Int;
			Arguments2.AddItem(ASValue0);
			ASValue0.I = ability->SkillPracticeProgress;
			ASValue0.Type = AS_Int;
			Arguments2.AddItem(ASValue0);
			GetObject("ActiveModify")->Invoke("SetSkillPoint", Arguments2 );

		}
	}
}

//技能升级功能开启
void UMMOUISkillPanel::EnableSkillUp( UBOOL isEnable )
{
    if( !GetObject("ActiveModify") )
    {
        return;
    }
    TArray<struct FASValue> Arguments;
    FASValue ASValue0(EC_EventParm);
    ASValue0.B = isEnable;
    ASValue0.Type = AS_Boolean;

    Arguments.AddItem(ASValue0);
    GetObject("ActiveModify")->Invoke("UcEnableSkillUp", Arguments );
}

//技能升级提示
void UMMOUISkillPanel::NetSkillLevelUp( int inActiveId,int byLevel )
{
	if( !GetObject("ActiveModify") )
		return;

	//UMMOAbility*  ability = MainPlayer->GetMainAbilityById( inActiveId );

	//if( !ability )
	//	return;

 //   //先刷对当前等级
	//ability->SpellCommonAttribute.Level = byLevel;

	////相关的系统提示
	//FString sMsg = FString::Printf(*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Skill.SkillLvUpNotify") ),
	//	*(ability->ClientCommonAttribute.AbilityName), byLevel );
	//MMOUI::GetUIManager()->delegateAddScreenMessage( sMsg );
	//MMOChatManager::getSingleton().AddSystemMessage( sMsg );

    //刷新当前技能等级
    //NetSkillProgressChange( inActiveId, ability->LvUpRequirePoints );

	//并停止升级状态显示 
	TArray<struct FASValue> Arguments2;
	FASValue ASValue0(EC_EventParm);

	//是否开始
	ASValue0.B = false;
	ASValue0.Type = AS_Boolean;
	Arguments2.AddItem(ASValue0);

	if( inActiveId == NowNormalPracticeActiveId )
	{
		UGFxObject* tObj = GetObject("ActiveModify")->GetObject("NormalPractice");
		if( tObj )
		{
			tObj->Invoke("SetStarted", Arguments2 );
		}
	}
	else if( inActiveId == NowFastPracticeActiveId )
	{
		UGFxObject* tObj = GetObject("ActiveModify")->GetObject("FastPractice");
		if( tObj )
		{
			tObj->Invoke("SetStarted", Arguments2 );
		}
	}

}
//技能升级---------------------------------------------------------------------------------------end


//确认提交Modify
void UMMOUISkillPanel::ConfirmActive( )
{
	UGFxObject*  tObj = NULL;
	int OtherRef;
	if( CurrentActives( CurrentActiveSlot ).ActiveId != CurrentSelectedActiveId )
	{
		OtherRef = IsActiveAlreadyEquiped( CurrentSelectedActiveId ) ;
		if( OtherRef >= 0 )
		{
			// 则对应的勾也会被冲掉
			CurrentActives( OtherRef ).IsChanged = true; 
			CurrentActives( OtherRef ).ActiveId = 0;
		}
		CurrentActives( CurrentActiveSlot ).ActiveId = CurrentSelectedActiveId; 
		CurrentActives( CurrentActiveSlot ).IsChanged = true; 
		//RefreshActiveModify();
	}

/*
	int i;
	for( i = 0; i < CurrentActives.Num() ; ++i )
	{
		if( CurrentActives( i ).ActiveId != RealActives( i ).ActiveId  )
			SendEquipActive( i, CurrentActives( i ).ActiveId );
	}*/

	sSpellChange tSC;

	SpellChangeDeque tChangeMsg;
	SpellChangeDeque::iterator tIter;
	int i;
	for( i = 0; i < CurrentActives.Num() ; ++i )
	{
		if( CurrentActives( i ).ActiveId != RealActives( i ).ActiveId  )
		{
			tSC.SlotId = i;
			tSC.AbilityId = CurrentActives( i ).ActiveId  ;
			if( tSC.AbilityId == 0 )
				tChangeMsg.push_front( tSC );
			else
				tChangeMsg.push_back( tSC );
		}
	}
	for( tIter = tChangeMsg.begin(); tIter != tChangeMsg.end() ; ++ tIter )
	{
		/*//如果选择过符文
		if( tIter->AbilityId == CurrentSelectedActiveId && CurrentSelectedActiveRuneSlot > 0 )
		{
			SendEquipActiveRune( CurrentSelectedActiveSlot,CurrentSelectedActiveRuneSlot  );
			continue;
		}*/
		SendEquipActive( tIter->SlotId,  tIter->AbilityId );
	}
	
	//如果选择过符文
	if( CurrentSelectedActiveRuneSlot > 0 )
		SendEquipActiveRune( CurrentActiveSlot,CurrentSelectedActiveRuneSlot   ); //本地Rune的索引是0~4 服务器是按1~5
	
}

void UMMOUISkillPanel::ActiveLastPage( )
{
	if( NowActivePageNum > 0 )
	{
		--NowActivePageNum;
		RefreshActiveModify();
	}	
}

void UMMOUISkillPanel::ActiveNextPage( )
{
	if( NowActivePageNum < TotalActivePageNum -1 )
	{
		++NowActivePageNum;
		RefreshActiveModify();
	}
}

//==================================================RefreshPassiveModify()====================================================== 


//设置PassiveBtn
void UMMOUISkillPanel::SetSpellBtnByPassiveId(class UGFxObject* tObj,INT SlotId,INT abilityId,UBOOL isSubCtrl)
{
#if M_TEMP_ENABLE_UI_Skill_CODE

	UMMOAbility*  ability;
	if( tObj == NULL )
	{
		//`log("CurrentSpell Passive Active PassiveSkill"$SlotId@"can't found");
		return;
	}
	//根据PassiveId设置Btn
	ability = MainPlayer->GetAbilityById( abilityId );
	//`log("CurrentSpell Passive Add Passive ()"@tObj@tObj->GetObject("ItemSlot")@"PassiveId::"@abilityId );
	if( ability != NULL && ability->eventGetAbilityId() >=0  && ( ability->SpellCommonAttribute.CastType == E_spct_Passive ) )
	{
		tObj->SetVisible(true);
		tObj->SetBool("enabled",true);
		if( tObj->GetObject("ItemSlot") )
		{
			//FString cs = TEXT("skill");
			//eventSetItem(tObj->GetObject("ItemSlot") ,0 ,ability->GetAbilityIconName() ,ability->eventGetAbilityId() ,FString( TEXT("skill") ) );
			GFXPlayer->eventCallSetItemData( tObj->GetObject("ItemSlot") , 0 , ability->GetAbilityIconName() , ability->eventGetAbilityId() , ESPType_SkillPanel,TEXT("") );
			//GFXPlayer->eventASSetSlotShowData(tObj->GetObject("ItemSlot") ,0 ,ability->GetAbilityIconName() ,ability->eventGetAbilityId() );
			tObj->GetObject("ItemSlot")->SetInt( "SlotType" , ESPType_SkillPanel );
		}
			//tF_SpellName 技能名称
		if( tObj->GetObject("tF_SpellName") )
			tObj->GetObject("tF_SpellName")->SetText( ability->ClientCommonAttribute.AbilityName );
		if( tObj->GetObject("lock_mc") )
			tObj->GetObject("lock_mc")->SetVisible( false );
		//`log("CurrentSpell Passive set SpellSlotId:"@SlotId );
		if( isSubCtrl )
		{
			//如果这个技能已经装备，则
			if( tObj->GetObject("EquipedCheck") )
			{
				if( IsPassiveAlreadyEquiped( abilityId ) >= 0 )
					tObj->GetObject("EquipedCheck")->SetVisible( true );
				else
					tObj->GetObject("EquipedCheck")->SetVisible( false );
			}
			//记录下对应的abilityId
			tObj->SetInt("PassiveId",abilityId );
		}
// 		else if( SlotId > 0 && SlotId < CurrentPassives.Num() )
// 			CurrentPassives(SlotId).PassiveId = abilityId;
	}
	else
	{
		//`log("CurrentSpell Passive Active  is NULL()"@tObj@tObj->GetObject("ItemSlot")@SlotId );
		//tObj->SetVisible(false);
		//tObj->SetBool("enabled",false);
		if( tObj->GetObject("ItemSlot") )
			eventSetItem(tObj->GetObject("ItemSlot") ,0,"",-1 );
		//tF_SpellName 技能名称
		if( tObj->GetObject("tF_SpellName") )
			tObj->GetObject("tF_SpellName")->SetText( "" );
		if( isSubCtrl )
		{
			tObj->SetBool("enabled",false);
			if( tObj->GetObject("EquipedCheck") )
				tObj->GetObject("EquipedCheck")->SetVisible( false );
			if( tObj->GetObject("lock_mc") )
				tObj->GetObject("lock_mc")->SetVisible( true );
		}
		else
		{
			if( tObj->GetObject("lock_mc") )
				tObj->GetObject("lock_mc")->SetVisible( false );
		}
	}
#endif
}

//选择当前CurrentPassiveSlot
void UMMOUISkillPanel::SetCurrentPassive( int passiveSlotId )
{
	PageJump( ESkill_Passive );
	if( CurrentPassiveSlot != passiveSlotId )
	{
		CurrentPassiveSlot = passiveSlotId;
		RefreshPassiveModify();
	}
}

//RefreshPassiveModify
void UMMOUISkillPanel::RefreshPassiveModify()
{
	int j,k;
	int abilityId;
	UGFxObject*  tObj = NULL;
	UMMOAbility*  ability;

	//`log("==============================RefreshPassiveModify() Opended=================================================");
	if( !Validate() )
		return;
	//--------------------------- 选择技能面板 ---------------------------------------------------------

	if( ! GetObject("PassiveModify") )
		return;

	//当前装备Passive技能
	for( int i =0 ;i < CurrentPassives.Num(); ++i )
	{
		tObj = GetObject("PassiveModify")->GetObject( FString::Printf(TEXT("CurrentSpellSlot%d"),i ) );
		SetSpellBtnByPassiveId( tObj,i , CurrentPassives(i).PassiveId ,false );
	}

	//当前职业玩家所有学会的Passive技能
	k = 0;
	for ( j = 0;   j < MainPlayer->Abilities.Num()  ; ++j )
	{
		ability = MainPlayer->Abilities(j);
		if( ability != NULL ){
			continue;
		}

		abilityId = ability->eventGetAbilityId();
		if( abilityId >=0 )
		{
			if( ( k < MaxPassiveModifyCount ) && ( ability->SpellCommonAttribute.CastType == E_spct_Passive )
				&& (  ability->ClientCommonAttribute.ShowOnUI == true ) )
			{
				tObj = GetObject("PassiveModify")->GetObject( FString::Printf(TEXT("spell%d"),k )  );
				SetSpellBtnByPassiveId( tObj,k,abilityId,true );
				++k;
			}	
		}
	}
	while( k< MaxPassiveModifyCount )
	{
		tObj = GetObject("PassiveModify")->GetObject( FString::Printf(TEXT("spell%d"),k ) );
		SetSpellBtnByPassiveId( tObj,k,0 ,true );
		++k;
	}
}

//选择CurrentPassiveSlot 切换成的对应 AllPassives( abilityId ) 的 PassiveId
void UMMOUISkillPanel::SelectPassive( int tSlotId,int abilityId )
{
	UGFxObject*  tObj = NULL;
	int OtherRef;
	if( CurrentPassives( CurrentPassiveSlot ).PassiveId != abilityId )
	{
		OtherRef = IsPassiveAlreadyEquiped( abilityId ) ;
		if( OtherRef >= 0 )
		{
			// 则对应的勾也会被冲掉
			CurrentPassives( OtherRef ).IsChanged = true; 
			CurrentPassives( OtherRef ).PassiveId = 0;
		}
		CurrentPassives( CurrentPassiveSlot ).PassiveId = abilityId; 
		CurrentPassives( CurrentPassiveSlot ).IsChanged = true; 
		RefreshPassiveModify();
	}
}

//Passive是否已经被装备
int UMMOUISkillPanel::IsPassiveAlreadyEquiped( int abilityId )
{
	int i;
	for( i = 0; i < CurrentPassives.Num() ; ++i )
	{
		if( CurrentPassives( i ).PassiveId ==  abilityId )
			return i;
	}
	return -1;
}

//确认提交Modify
void UMMOUISkillPanel::ConfirmPassive( )
{
/*
	int i;
	for( i = 0; i < CurrentPassives.Num() ; ++i )
	{
		if( CurrentPassives( i ).PassiveId != RealPassives( i ).PassiveId  )
			SendEquipPassive( i, CurrentPassives( i ).PassiveId );
	}*/
	sSpellChange tSC;
	SpellChangeDeque tChangeMsg;
	SpellChangeDeque::iterator tIter;
	int i;
	for( i = 0; i < CurrentPassives.Num() ; ++i )
	{
		if( CurrentPassives( i ).PassiveId != RealPassives( i ).PassiveId  )
		{
			tSC.SlotId = i;
			tSC.AbilityId = CurrentPassives( i ).PassiveId  ;
			if( tSC.AbilityId == 0 )
				tChangeMsg.push_front( tSC );
			else
				tChangeMsg.push_back( tSC );
		}
	}
	for( tIter = tChangeMsg.begin(); tIter != tChangeMsg.end() ; ++ tIter )
	{
		SendEquipPassive( tIter->SlotId,  tIter->AbilityId );
	}
}

//==================================================RefreshAvartaModify()====================================================== 


//设置AvartaBtn
void UMMOUISkillPanel::SetSpellBtnByAvartaId(class UGFxObject* tObj,INT SlotId,INT abilityId,UBOOL isSubCtrl)
{
	UMMOAbility*  ability;
	//根据AvartaId设置Btn
	ability = MainPlayer->GetAbilityById( abilityId );
	SetSpellBtnByAvarta( tObj,SlotId, ability,isSubCtrl);
}

//设置AvartaBtn
void UMMOUISkillPanel::SetSpellBtnByAvarta(class UGFxObject* tObj,INT SlotId, UMMOAbility*  ability,UBOOL isSubCtrl,UBOOL isRuneCtrl )
{
	if( tObj == NULL )
	{
		//`log("CurrentSpell Avarta Active AvartaSkill"$SlotId@"can't found");
		return;
	}
	//Avarta技能是主动技能中一种 
	if( ability != NULL && ability->eventGetAbilityId() >=0  )
	{
		INT abilityId = ability->eventGetAbilityId();
		tObj->SetVisible(true);
		tObj->SetBool("enabled",true);
		if( tObj->GetObject("ItemSlot") )
		{
			//FString cs = TEXT("skill");
			//eventSetItem(tObj->GetObject("ItemSlot") ,0 ,ability->GetAbilityIconName() ,ability->eventGetAbilityId() ,FString( TEXT("skill") ) );
			GFXPlayer->eventCallSetItemData( tObj->GetObject("ItemSlot") , 0 , ability->GetAbilityIconName() , ability->eventGetAbilityId() , ESPType_SkillPanel,TEXT("") );
			//GFXPlayer->eventASSetSlotShowData(tObj->GetObject("ItemSlot") ,0 ,ability->GetAbilityIconName() ,ability->eventGetAbilityId()/* ,cs*/);
			tObj->GetObject("ItemSlot")->SetInt( "SlotType" , ESPType_SkillPanel );
		}
			//tF_SpellName 技能名称
		if( tObj->GetObject("tF_SpellName") )
		{
			tObj->GetObject("tF_SpellName")->SetVisible( true );
			tObj->GetObject("tF_SpellName")->SetText( ability->ClientCommonAttribute.AbilityName );
		}
		//`log("CurrentSpell Avarta set SpellSlotId:"@SlotId );
		if( tObj->GetObject("lock_mc") )
			tObj->GetObject("lock_mc")->SetVisible( false );
		if( isSubCtrl )
		{
			//如果这个技能已经装备，则显示已经装备 （符文不显示）
			if( tObj->GetObject("EquipedCheck") && !isRuneCtrl )
			{
				if( IsAvartaAlreadyEquiped( abilityId ) >= 0 )
					tObj->GetObject("EquipedCheck")->SetVisible( true );
				else
					tObj->GetObject("EquipedCheck")->SetVisible( false );
			}
			//记录下对应的abilityId
			tObj->SetInt("AvartaId",abilityId );

			//标记被选择的按钮
			if( isRuneCtrl )
			{
				if( SlotId == CurrentSelectedAvartaRuneSlot )
					tObj->SetBool("selected",true);
				else
					tObj->SetBool("selected",false);
			}
			else
			{
				if( abilityId == CurrentSelectedAvartaId )
					tObj->SetBool("selected",true);
				else
					tObj->SetBool("selected",false);
			}
		}
		// 		else if( SlotId > 0 && SlotId < CurrentAvartas.Num() )
		// 			CurrentAvartas(SlotId).AvartaId = abilityId;
	}
	else
	{
		//`log("CurrentSpell Avarta Active  is NULL()"@tObj@tObj->GetObject("ItemSlot")@SlotId );
		//tObj->SetVisible(false);
		//tObj->SetBool("enabled",false);
		if( tObj->GetObject("ItemSlot") )
			eventSetItem(tObj->GetObject("ItemSlot") ,0,"",-1 );
		//tF_SpellName 技能名称
		if( tObj->GetObject("tF_SpellName") )
		{
			tObj->GetObject("tF_SpellName")->SetVisible( false );
			//tObj->GetObject("tF_SpellName")->SetText( "" );
		}
		if( isSubCtrl )
		{
			tObj->SetBool("enabled",false);
			if( tObj->GetObject("EquipedCheck") && !isRuneCtrl )
				tObj->GetObject("EquipedCheck")->SetVisible( false );
			if( tObj->GetObject("lock_mc") )
				tObj->GetObject("lock_mc")->SetVisible( true );
		}
		else
		{
			if( tObj->GetObject("lock_mc") )
				tObj->GetObject("lock_mc")->SetVisible( false );
		}
		//选择状态取消
		tObj->SetBool("selected",false);
	}
}

//选择当前CurrentAvartaSlot
void UMMOUISkillPanel::SetCurrentAvarta( int avartaSlotId )
{
	PageJump( ESkill_Avarta );
	if( CurrentAvartaSlot != avartaSlotId )
	{
		CurrentAvartaSlot = avartaSlotId;
		//切换后 重新确定选定的Avarta技能
		CurrentSelectedAvartaId = CurrentAvartas( CurrentAvartaSlot ).AvartaId; 
		RefreshAvartaModify();
	}
}

//RefreshAvartaModify
void UMMOUISkillPanel::RefreshAvartaModify()
{
	int j,k;
	int abilityId;
	UGFxObject*  tObj = NULL;
	UMMOAbility*  ability;

	//`log("==============================RefreshAvartaModify() Opended=================================================");
	if( !Validate() )
		return;
	//--------------------------- 选择技能面板 ---------------------------------------------------------

	if( ! GetObject("AvartaModify") )
		return;

	UINT Key = MMOSkillManager::CombinateAbilityID( CurrentSelectedAvartaId, 1 ,0 );
	UMMOAbility* tMainAvarta = MMOSkillManager::getSingleton().FindAbilityTemplate(Key);
	if( tMainAvarta )
	{
		//确定装备的符文
		CurrentSelectedAvartaRuneSlot = tMainAvarta->GetRuneSlot();
	}
	else
		CurrentSelectedAvartaRuneSlot = 0;

	//当前装备Avarta技能
	for( int i =0 ;i < CurrentAvartas.Num(); ++i )
	{
		tObj = GetObject("AvartaModify")->GetObject( FString::Printf(TEXT("CurrentSpellSlot%d"),i ) );
		SetSpellBtnByAvartaId( tObj,i , CurrentAvartas(i).AvartaId ,false );
	}

	//当前职业玩家所有学会的Avarta技能
	k = 0;
	
	if( GetObject("AvartaModify")->GetObject("NowAvarta") )
	{
		static UEnum* InEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESpell_QTEType"), TRUE);
		if (InEnum)
		{
			FString EnumValueName= InEnum->GetEnum(CurrentAvartaSlot  ).ToString();
			FString LocalizedName = LocalizeProperty( *(InEnum->GetName()), *(EnumValueName) );	
			GetObject("AvartaModify")->GetObject("NowAvarta")->SetText( LocalizedName );
		}
	}

/*
	int iTotalAbilitiesNum = MainPlayer->Abilities.Num() ;
	//刷新当前页码
	TotalActivePageNum = iTotalAbilitiesNum / MaxActiveModifyCount;
	if( iTotalAbilitiesNum % MaxActiveModifyCount > 0 )
		++TotalActivePageNum;
	//算出实际显示那些技能
	int iOffset = NowActivePageNum  * MaxActiveModifyCount;
	for ( j = iOffset ;   j < iTotalAbilitiesNum ; ++j )*/
	for ( j = 0;   j < MainPlayer->Abilities.Num()  ; ++j )
	{
		ability = MainPlayer->Abilities(j);
		if( ability != NULL ){
			continue;
		}

		abilityId = ability->eventGetAbilityId();
		if( abilityId >=0 )
		{
			if( ( k < MaxAvartaModifyCount ) && ( ability->SpellCommonAttribute.CastType == E_spct_Active )
				&& ( ability->SpellCommonAttribute.QTEType == CurrentAvartaSlot+1 ) && (  ability->ClientCommonAttribute.ShowOnUI == true ) )
			{
				tObj = GetObject("AvartaModify")->GetObject( FString::Printf(TEXT("spell%d"),k )  );
				SetSpellBtnByAvartaId( tObj,k,abilityId,true );
				++k;
			}	
		}
	}
	while( k< MaxAvartaModifyCount )
	{
		tObj = GetObject("AvartaModify")->GetObject( FString::Printf(TEXT("spell%d"),k ) );
		SetSpellBtnByAvartaId( tObj,k,0 ,true );
		++k;
	}
	//刷一遍符文
	OnSelecteAvartaChanged( CurrentSelectedAvartaId );
}

//选择CurrentAvartaSlot 切换成的对应 AllAvartas( abilityId ) 的 AvartaId
void UMMOUISkillPanel::SelectAvarta( int tSlotId,int abilityId )
{
	UGFxObject*  tObj = NULL;
	int OtherRef;
	if( CurrentAvartas( CurrentAvartaSlot ).AvartaId != abilityId )
	{
		CurrentSelectedAvartaSlot = tSlotId;
		CurrentSelectedAvartaId = abilityId;
		OtherRef = IsAvartaAlreadyEquiped( abilityId ) ;
		if( OtherRef >= 0 )
		{
			// 则对应的勾也会被冲掉
			CurrentAvartas( OtherRef ).IsChanged = true; 
			CurrentAvartas( OtherRef ).AvartaId = 0;
		}
		CurrentAvartas( CurrentAvartaSlot ).AvartaId = abilityId; 
		CurrentAvartas( CurrentAvartaSlot ).IsChanged = true; 
		RefreshAvartaModify();
	}
}

//刷一遍符文
void UMMOUISkillPanel::OnSelecteAvartaChanged( int  abilityId )
{
	if( !GetObject("AvartaModify") )
		return;

	//刷新abilityId对应的所有符文
	int iRune = 0;
	UINT Key = MMOSkillManager::CombinateAbilityID( CurrentSelectedAvartaId, 1 ,0 );
	UMMOAbility* tMainAvarta = MMOSkillManager::getSingleton().FindAbilityTemplate(Key);
	UMMOAbility* tRune = NULL;
	UGFxObject* tObj = NULL;
	//显示当前技能所有的符文 
	int byRuneSlot = 0;
	while( tMainAvarta && iRune < tMainAvarta->SubRuneList.Num() ) 
	{
		tRune = tMainAvarta->SubRuneList( iRune );
		tObj = GetObject("AvartaModify")->GetObject( FString::Printf(TEXT("avarta%d"),iRune) );
		//直接当成Main处理
		SetSpellBtnByAvarta( tObj ,iRune ,tRune ,true , true );
		++iRune;
	} 
	//剩下不显示 
	while( iRune < AvartaRuneCount )
	{
		tObj = GetObject("AvartaModify")->GetObject( FString::Printf(TEXT("avarta%d"),iRune ) );
		SetSpellBtnByAvarta( tObj ,iRune ,NULL ,true , true );
		++iRune;
	}
}

//abilityId 号技能装配了第 tSlotId 个符文
void UMMOUISkillPanel::SelectAvartaRune( int tSlotId,int abilityId )
{
	CurrentSelectedAvartaRuneSlot = tSlotId;
	OnSelecteAvartaChanged( CurrentSelectedAvartaId );
}

//Avarta是否已经被装备
int UMMOUISkillPanel::IsAvartaAlreadyEquiped( int abilityId )
{
	int i;
	for( i = 0; i < CurrentAvartas.Num() ; ++i )
	{
		if( CurrentAvartas( i ).AvartaId ==  abilityId )
			return i;
	}
	return -1;
}

//确认提交Modify
void UMMOUISkillPanel::ConfirmAvarta( )
{
	sSpellChange tSC;
	SpellChangeDeque tChangeMsg;
	SpellChangeDeque::iterator tIter;

	for( int i = 0; i < CurrentAvartas.Num() ; ++i )
	{
		if( CurrentAvartas( i ).AvartaId != RealAvartas( i ).AvartaId  )
		{
			tSC.SlotId = i;
			tSC.AbilityId = CurrentAvartas( i ).AvartaId  ;
			if( tSC.AbilityId == 0 )
				tChangeMsg.push_front( tSC );
			else
				tChangeMsg.push_back( tSC );
		}
	}

	for( tIter = tChangeMsg.begin(); tIter != tChangeMsg.end() ; ++ tIter )
	{
		SendEquipAvarta( tIter->SlotId,  tIter->AbilityId );
	}
	//如果选择过符文 
    //本地Rune的索引是0~4 服务器是按1~5
	if( CurrentSelectedAvartaRuneSlot > 0 )
		SendEquipAvartaRune( CurrentSelectedAvartaSlot, CurrentSelectedAvartaRuneSlot  );
}

//翻页
void UMMOUISkillPanel::AvartaLastPage( )
{
	if( NowAvartaPageNum > 0 )
	{
		--NowAvartaPageNum;
		RefreshAvartaModify();
	}	
}

void UMMOUISkillPanel::AvartaNextPage( )
{
	if( NowAvartaPageNum < TotalAvartaPageNum -1 )
	{
		++NowAvartaPageNum;
		RefreshAvartaModify();
	}
}

void UMMOUISkillPanel::AvartaRuneLastPage( )
{
	if( NowAvartaRunePageNum > 0 )
	{
		--NowAvartaRunePageNum;
		OnSelecteAvartaChanged( CurrentSelectedAvartaId );
	}	
}

void UMMOUISkillPanel::AvartaRuneNextPage( )
{
	if( NowAvartaRunePageNum < TotalAvartaRunePageNum -1 )
	{
		++NowAvartaRunePageNum;
		OnSelecteAvartaChanged( CurrentSelectedAvartaId );
	}
}
#endif