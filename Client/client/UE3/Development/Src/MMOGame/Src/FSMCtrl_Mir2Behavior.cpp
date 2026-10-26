


#include "StdAfx.h"
#include "FSMState.h"
#include "FSMCtrl_Mir2Behavior.h"
#include "MMOGameClasses.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "AbilityProcessor.h"
#include "MMONavigationManager.h"
#include "ScaleformEngine.h"
#include "UITextParser.h"
#include "FSMIO.h"

using namespace FSM;

//FSM控制类注册--------------------------------------------------------------------------------------------------
//ADD_FSM_CTRL(FSMCtrl_Mir2_PlayerClassA_Attack)

extern UBOOL g_PreMovetoPoint;
extern INT g_TotalFrameNum;
////shift键原地使用技能---------------------------------------------------------------------------------------------
//UBOOL FSMCtrl_Mir2_PlayerClassA_Attack::Update(FLOAT DelTime)//战士
//{
//	if( FSM::Char.MainPlayer		&&
//		FSM::Char.Controller		&&
//		FSM::Char.MainPlayer->GetClassId()==EPCT_PlayerClassA )
//	{
//		//主键攻击
//		if(FSM::Ctrl.KeyType==KT_PRIMARY)
//		{
//
//		}
//
//
//
//
//
//	}
//}
//void FSMCtrl_Mir2_PlayerClassA_Attack::Action()
//{
//
//}
//
//	switch(MMOFacade::getSingleton().GetMainActor()->GetClassId())
//	{
//	case EPCT_PlayerClassA://战士
//		_ActivateGuide(2019);
//		break;
//	case EPCT_PlayerClassB://法师
//	case EPCT_PlayerClassC://刺客
//	case EPCT_PlayerClassD://弓手
//	case EPCT_PlayerClassE://道士
//
//
//
//
//	if( FSM::Input.ShiftDown		&&
//		FSM::Char.MainPlayer		&&
//		FSM::Char.Controller		&&
//		FSM::Ability.UsableAbility	&&
//		FSM::Ability.AbilityEnable  &&
//		(FSM::Char.MainPlayer->isMoving == FALSE || FSM::Ability.UsableAbility->SpellCommonAttribute.CanMoveInPrepare )&&
//		FSM::Ctrl.KeyType!=KT_NONE &&
//		FSM::Ctrl.KeyType!=KT_SECONDARY &&
//		FSM::Char.IsDead==FALSE	)
//	{
//		//if(FSM::Target.DesireMMOActor && FSM::Target.DesireAttackble && FSM::Ability.PickTarget==TRUE)return FALSE;
//		if(FSM::Target.DesireMMOActor && FSM::Ability.PickTarget==TRUE)return FALSE;
//		return TRUE ;
//	}
//
//
//	////按住shift进行强行有目标的攻击的暂停
//	//if(	FSM::Input.ShiftDown==FALSE	&&
//	//	FSM::Input.ShiftDown_Last==TRUE&&
//	//	FSM::Target.DesireMMOActor &&
//	//	FSM::Target.DesireAttackble &&
//	//	FSM::Char.MainPlayer		&&
//	//	FSM::Char.Controller		&&
//	//	FSM::Ability.PickTarget==TRUE &&
//	//	FSM::Char.IsDead==FALSE)
//	//{
//	//	FSM::Ctrl.state_Attack = FALSE;
//	//	FSM::Ctrl.state_Switching_Flag = FALSE;
//	//	FSM::Char.Controller->eventClearAllCmd();
//	//}
//
//	return FALSE;
//}
//
//void FSMCtrl_ShiftAbility::Action()
//{
//	//直接施放技能
//	if(FSM::Char.Controller){
//		//这是一个奇葩的分支，shift按住攻击目标的时候要能释放开关类技能
//		if(FSM::Ability.UsableAbility->SpellCommonAttribute.CanMoveInPrepare)
//		{
//			if(FSM::Ctrl.state_Switching_Flag)
//			{
//				FSM::Ctrl.state_Switching_Flag = FALSE;
//				INT ServerID = FSM::Target.DesireMMOActor?FSM::Target.DesireMMOActor->ServerID:0 ;
//				FVector vec = FSM::Char.MainPlayer->Rotation.Vector().SafeNormal();
//				FSM::Char.Controller->RequestUseAbility(ServerID, FSM::Ability.UsableAbility->SlotHotKeyID, FSM::Ability.UsableAbility->SpellCommonAttribute.Level, FSM::Char.MainPlayer->ServerLocation+vec*512.0, FALSE );
//			}
//		}
//		else{
//			FSM::Char.Controller->eventClearAllCmd();
//			if(FSM::Target.CurTargetMMOActor){
//				FSM::Char.Controller->eventAddCmdUseAbility(FSM::Ability.UsableAbility,	FSM::Target.CurTargetMMOActor,	FSM::Target.CurTargetMMOActor->Location);
//			}
//			else
//			{
//				FSM::Char.Controller->eventAddCmdUseAbility(FSM::Ability.UsableAbility,NULL, FSM::Char.Controller->MouseHitWorldLocation);
//			}
//		}
//	}
//}
//
//
