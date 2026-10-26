#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOGuildManager.h"


IMPLEMENT_CLASS(UMMOGFXPlayer_GuildBase)

void UMMOGFXPlayer_GuildBase::PostAdvance(FLOAT dt)
{
	if (_GuildCreatePanel->IsVisible)
	{
		AMMOActor* selectActor = Cast<AMMOActor>(MMOFacade::getSingleton().GetMainController()->GetSelectTarget());
		if (!selectActor)
		{
			_GuildCreatePanel->Show(FALSE);
		}
	}
	
	if (_GuildViewPanel->IsVisible && _GuildViewPanel->_IsNpcCalled)
	{
		AMMOActor* selectActor = Cast<AMMOActor>(MMOFacade::getSingleton().GetMainController()->GetSelectTarget());
		if (!selectActor)
		{
			_GuildViewPanel->Show(FALSE);
		}
	}
	
	if (_GuildWarehouse->IsVisible)
	{
		AMMOActor* selectActor = Cast<AMMOActor>(MMOFacade::getSingleton().GetMainController()->GetSelectTarget());
		if (!selectActor)
		{
			_GuildWarehouse->Show(FALSE);
		}
	}

	if (_GuildInstructionPanel->IsVisible)
	{
		AMMOActor* selectActor = Cast<AMMOActor>(MMOFacade::getSingleton().GetMainController()->GetSelectTarget());
		if (!selectActor)
		{
			_GuildInstructionPanel->Show(FALSE);
		}
	}
}

void UMMOGFXPlayer_GuildBase::SetItemSlotData(class UGFxObject* mc,class UItem* tItem,BYTE SlotType,BYTE ContainerID/* =13 */,INT SlotID/* =-1 */,BYTE inISS/* =0 */)
{
	if (!mc)
	{
		return;
	}

	mc->SetBool("isSlotLocked", FALSE);
	mc->SetBool("isSlotUnusable", FALSE);

	//置于Loader之上
	if (ISS_ItemLocked == inISS || ISS_SlotLocked == inISS)
	{
		mc->SetBool("isSlotLocked", TRUE);
	}
	else if (ISS_Unusable == inISS)
	{
		mc->SetBool("isSlotUnusable", TRUE);
	}

	//直接替换Loader
	if (ISS_SlotLocked == inISS)
	{
		eventCallSetItemData(mc, 0, LockedSlotIconPath, -1, SlotType, TEXT(""), ITEMCOLOR_INVALID, ContainerID, SlotID);
		return;
	}
	else if (NULL == tItem)
	{
		eventCallSetItemData(mc, 0, TEXT(""), -1, SlotType, TEXT(""), ITEMCOLOR_INVALID, ContainerID, SlotID);
	}
	else
	{
		//有iteminfo为本地商品
		FClientItemInfo* itemInfo = MMOGuildData::getSingleton().GetWarehouseItem(_GuildWarehouse->_CurPage, SlotID);
		switch (tItem->ItemDuration)
		{
		case E_DURTYPE_STACK:
			{
				if (itemInfo)
				{
					//摆摊时 如果当前物品已经上架
					if (itemInfo->IsOnSale && ESPType_StallSetting == SlotType)
					{
						eventCallSetItemData(mc, itemInfo->OnSaleCount, MMOFacade::getSingleton().GetItemIconNamePersonalized(tItem), tItem->ItemId, SlotType, TEXT(""), tItem->ItemColor + 1, ContainerID, SlotID);
					}
					//灵魂被拖入灵魂融合界面
					else if (itemInfo->IsDragIntoOtherUI >= 0 && (ESPType_SoulEmbed == SlotType || ESPType_SoulLevelUp == SlotType || ESPType_SoulUnEmbed == SlotType))
					{
						eventCallSetItemData(mc, 1, MMOFacade::getSingleton().GetItemIconNamePersonalized(tItem), tItem->ItemId, SlotType, TEXT(""), tItem->ItemColor, ContainerID, SlotID);
					}
					//融灵时，则其他界面都不显示 
					else if (itemInfo->IsDragIntoOtherUI >= 0 && itemInfo->m_nCurDur <= 0) 
					{
						if (itemInfo->IsDragIntoOtherUI == ESPType_StallSetting)
						{// 摆摊时，背包里的图标不隐藏
							eventCallSetItemData(mc, itemInfo->m_nCurDur, MMOFacade::getSingleton().GetItemIconNamePersonalized(tItem), tItem->ItemId, SlotType, TEXT(""), tItem->ItemColor + 1, ContainerID, SlotID);
						}
						else
						{
							//显示空
							eventCallSetItemData(mc, 0, TEXT(""), -1, SlotType, TEXT(""), ITEMCOLOR_INVALID, ContainerID, SlotID);
						}
					}
					else
					{
						eventCallSetItemData(mc, itemInfo->m_nCurDur, MMOFacade::getSingleton().GetItemIconNamePersonalized(tItem), tItem->ItemId, SlotType, TEXT(""), tItem->ItemColor, ContainerID, SlotID);
					}
				}
				else
				{
					eventCallSetItemData(mc, tItem->DefaultDuration, MMOFacade::getSingleton().GetItemIconNamePersonalized(tItem), tItem->ItemId, SlotType, TEXT(""), tItem->ItemColor, ContainerID, SlotID);
				}
			}
			break;
		case E_DURTYPE_EQUIP:
		case E_DURTYPE_USE:
		case E_DURTYPE_NONE:
		case E_DURTYPE_DEPOSIT:
			eventCallSetItemData(mc, 1, MMOFacade::getSingleton().GetItemIconNamePersonalized(tItem), tItem->ItemId, SlotType, TEXT(""), tItem->ItemColor + 1, ContainerID, SlotID);
			break;
		}
	}
}

void UMMOGFXPlayer_GuildBase::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_GuildBase::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_GuildBase);

	MMOUI::GetUIManager()->SetShowGuildCreatePanelDelegate(FScriptDelegate(this, TEXT("ShowGuildCreatePanel")));
	MMOUI::GetUIManager()->SetShowGuildViewPanelDelegate(FScriptDelegate(this, TEXT("ShowGuildViewPanel")));

}

void UMMOGFXPlayer_GuildBase::UnInit()
{
	Super::UnInit();

	FScriptDelegate nullDelgate(EC_EventParm);

	MMOUI::GetUIManager()->SetShowGuildCreatePanelDelegate(nullDelgate);
	MMOUI::GetUIManager()->SetShowGuildViewPanelDelegate(nullDelgate);

	MMOUI::GetUIManager()->SetFreshWarehouseDelegate( nullDelgate );
	MMOUI::GetUIManager()->SetUpdateAccessInfoDelegate( nullDelgate );
}

void UMMOGFXPlayer_GuildBase::ShowGuildCreatePanel()
{
	_GuildCreatePanel->ShowGuildCreatePanel();
}

void UMMOGFXPlayer_GuildBase::ShowGuildViewPanel()
{
	_GuildViewPanel->ShowGuildViewPanel();
}

//void UMMOGFXPlayer_GuildBase::ShowGuildMainPanel()
//{
//	_GuildMainPanel->ShowGuildMainPanel();
//}

// 创建家族
void UMMOGFXPlayer_GuildBase::ASCreateGuild(const FString& guildName, const FString& guildAnnounce)
{
	_GuildCreatePanel->CreateGuild(guildName, guildAnnounce);
}

// 家族查看
void UMMOGFXPlayer_GuildBase::ASViewGuild()
{
	_GuildViewPanel->SetNpcCalled(FALSE);
	_GuildViewPanel->ShowGuildViewPanel();
	_GuildMainPanel->Show(FALSE);
}

void UMMOGFXPlayer_GuildBase::ASUpdateGuildViewInfo(INT id)
{
	_GuildViewPanel->UpdateGuildViewInfo(id);
	_GuildViewPanel->UpdateGuildBuildingList(id);
}

// 家族查找
void UMMOGFXPlayer_GuildBase::ASFindGuild(UBOOL isId, const FString& content)
{
	_GuildViewPanel->FindGuild(isId, content);
}

// 翻页
void UMMOGFXPlayer_GuildBase::ASPageUp()
{
	_GuildViewPanel->PageUp();
}

void UMMOGFXPlayer_GuildBase::ASPageDown()
{
	_GuildViewPanel->PageDown();
}

// 仓库
void UMMOGFXPlayer_GuildBase::ASGuildWarehouseMore()
{
	_GuildWarehouse->MoreInfo();
}

void UMMOGFXPlayer_GuildBase::ASGuildWarehouseUpdate()
{
	_GuildWarehouse->SendFreshWarehouse();
}

void UMMOGFXPlayer_GuildBase::ASGuildWarehouseTab(INT tabID)
{
	_GuildWarehouse->TabChange( tabID );
}

// 申请加入家族
void UMMOGFXPlayer_GuildBase::ASApplyForJoint(INT id)
{
	_GuildViewPanel->ApplyForJoint(id);
}

// 更新申请列表
void UMMOGFXPlayer_GuildBase::ASUpdateGuildPendingMemberList()
{
	_GuildMainPanel->UpdateGuildPendingMemberList();
}

// 同意加入家族
void UMMOGFXPlayer_GuildBase::ASAgreeToJoin(INT id)
{
	_GuildMainPanel->AgreeToJoin(id);
}

// 拒绝加入家族
void UMMOGFXPlayer_GuildBase::ASRefuseToJoin(INT id)
{
	_GuildMainPanel->RefuseToJoin(id);
}

// 资金捐献
void UMMOGFXPlayer_GuildBase::ASContribute(INT type, INT count)
{
	if (count == 0)
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage(TEXT("捐献数量不能为0"),MsgInfoType_Table,TEXT("捐献数量不能为0"));
		return;
	}

	// 判定资金是否已达上限
	UINT32 resMax = MMOGuildData::getSingleton().GetGuildTerritoryResMax(GUILD_ATTR_MONEY);
	UINT32 resCur = MMOGuildData::getSingleton().GetCurGuildTerritoryRes(GUILD_ATTR_MONEY);
	if (resCur >= resMax)
	{
		FString text = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Guild.MoneyStoreLimit"));		
		MMOUI::GetUIManager()->delegateAddScreenMessage(text,MsgInfoType_Table,TEXT("MMOGame.Guild.MoneyStoreLimit"));
		return;
	}

	// #15422
	if (resCur + count > resMax)
	{
		FString text = TEXT("捐献金额过大，无法捐献资金");		
		MMOUI::GetUIManager()->delegateAddScreenMessage(text,MsgInfoType_Table,TEXT("MMOGame.Guild.MoneyStoreLimit"));
		return;
	}

	CMessageHandler::GetInstance().Send_GuildContribute(GUILD_ATTR_MONEY, count);
}

// 更改通告
void UMMOGFXPlayer_GuildBase::ASChangeNotice(const FString& notice)
{
	_GuildMainPanel->ChangeGuildNotice(notice);
}

// 更改宣言
void UMMOGFXPlayer_GuildBase::ASChangeAnnounce(const FString& announce)
{
}

// 查看更多家族事件
void UMMOGFXPlayer_GuildBase::ASViewMoreEvents()
{
	CMessageHandler::GetInstance().Send_ViewMoreEvents();
}

// 招募成员
void UMMOGFXPlayer_GuildBase::ASInviteMember(const FString& roleName)
{
	_GuildMainPanel->InviteMember(roleName);
}

void UMMOGFXPlayer_GuildBase::ASSortMember(INT type, UBOOL isUp)
{
	_GuildMainPanel->SortMember(type, isUp);
}

// 驱逐成员
void UMMOGFXPlayer_GuildBase::ASExpelMember(INT id)
{
	_GuildMainPanel->ExpelMember(id);
}

// 更改职位
void UMMOGFXPlayer_GuildBase::ASChangePost(INT roleId, INT post)
{
	_GuildMainPanel->ChangePost(roleId, post);
}

// 是否显示在线成员
void UMMOGFXPlayer_GuildBase::ASShowOnlineMember(UBOOL isShow)
{
	_GuildMainPanel->ShowOnlineMember(isShow);
}

// 是否显示在线成员
void UMMOGFXPlayer_GuildBase::ASOnlineMemberNotify(UBOOL notify)
{
	MMOGuildManager::getSingleton().SetOnlineMemberNotify(notify);
}

// 族长禅位
void UMMOGFXPlayer_GuildBase::ASLeaderDemise(const FString& roleName)
{
	_GuildMainPanel->LeaderDemise(roleName);
}

// 家族解散
void UMMOGFXPlayer_GuildBase::ASDisbandGuild(const FString& text)
{
	_GuildMainPanel->DisbandGuild(text);
}

// 退出家族
void UMMOGFXPlayer_GuildBase::ASQuitGuild()
{
	_GuildMainPanel->QuitConfirm();
}

// 更新家族权限显示
void UMMOGFXPlayer_GuildBase::ASUpdateGuildRights(INT post)
{
	_GuildMainPanel->UpdateGuildRights(post + 1);
}

// 更新仓库权限显示
void UMMOGFXPlayer_GuildBase::ASModifyGuildStorageRights(INT post, UGFxObject* rights)
{
	_GuildMainPanel->ModifyGuildStorageRights(post + 1, rights);
}

void UMMOGFXPlayer_GuildBase::ASUpdateGuildStorageRights(INT post)
{
	_GuildMainPanel->UpdateGuildStorageRights(post + 1);
}

// 俸禄分配
void UMMOGFXPlayer_GuildBase::ASDistributeSalary(UGFxObject* percent)
{
	_GuildMainPanel->DistributeSalary(percent);
}

void UMMOGFXPlayer_GuildBase::ASApplyAlly(const FString& guildName, INT timeType)
{
	_GuildMainPanel->ApplyAlly(guildName, timeType);
}

void UMMOGFXPlayer_GuildBase::ASApplyEnemy(const FString& guildName, INT timeType)
{
	_GuildMainPanel->ApplyEnemy(guildName, timeType);
}

void UMMOGFXPlayer_GuildBase::ASAgreeAlly(INT id)
{
	_GuildMainPanel->AgreeAlly(id);
}

void UMMOGFXPlayer_GuildBase::ASRefuseAlly(INT id)
{
	_GuildMainPanel->RefuseAlly(id);
}

void UMMOGFXPlayer_GuildBase::ASFullMemberRightClick(INT posX, INT posY, INT roleId)
{
	_GuildMainPanel->FullMemberRightClick(posX, posY, roleId);
}

void UMMOGFXPlayer_GuildBase::ASForeignApplyDayType(int foreignType, int dayType)
{
	_GuildMainPanel->SetForeignApplyDayType(foreignType, dayType);
}

void UMMOGFXPlayer_GuildBase::ASChallenge(const FString& guildName)
{
	_GuildMainPanel->ChallengeConfirm(guildName);
}

void UMMOGFXPlayer_GuildBase::ASMatchChallenge(INT id)
{
	CMessageHandler::GetInstance().Send_MatchChallenge(id);
}

void UMMOGFXPlayer_GuildBase::ASChallengeConfirm(INT guildId)
{
}

// 家族匹配战
void UMMOGFXPlayer_GuildBase::ASSearchGuild()
{
	CMessageHandler::GetInstance().Send_Search();
}

void UMMOGFXPlayer_GuildBase::ASInputError()
{		
	MMOUI::GetUIManager()->delegateAddScreenMessage(TEXT("只能包含英文，中文，数字"), MsgInfoType_Table, TEXT(""));
}