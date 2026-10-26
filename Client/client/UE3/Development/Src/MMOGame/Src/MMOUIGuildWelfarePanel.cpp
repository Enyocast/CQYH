#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOGuildManager.h"
#include "UITextParser.h"
#include <time.h>
#include "MMOVipManager.h"

IMPLEMENT_CLASS(UMMOUIGuildWelfarePanel)

void UMMOUIGuildWelfarePanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Guild);
	EventAdapter = new TGameEventAdapter<UMMOUIGuildWelfarePanel>(this, evts);
}

void UMMOUIGuildWelfarePanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
		_CurPageIndex = 1;
		eventCallSetWindowTitle(MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Guild.WelfarePanel")));

		UpdateGuildWelfarePurchasePage();
	}
}

void UMMOUIGuildWelfarePanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
{
	if (!IsVisible)
	{
		return;
	}

	if (gameEvent->GetEventType() != GameEvent_Guild)
	{
		return;
	}

	MMOGameEvent_Guild* guildEvent = (MMOGameEvent_Guild*)gameEvent;
	if (guildEvent == NULL)
	{
		return;
	}

	switch(guildEvent->_EventType)
	{
	case MMOGameEvent_Guild::EGET_UpdateGuildWelfareList:
		UpdateGuildWelfarePurchaseList();
		break;
	}
}

void UMMOUIGuildWelfarePanel::PageUp()
{
	if (_CurPageIndex > 1)
	{
		_CurPageIndex --;
		UpdateGuildWelfarePurchasePage();
	}
}

void UMMOUIGuildWelfarePanel::PageDown()
{
	UINT32 groupCount = MMOGuildData::getSingleton().GetGuildWelfareGroupCount();
	INT maxPage = appCeil((FLOAT)groupCount / (FLOAT)GUILD_WELFARE_GROUP_PER_PAGE);
	if (_CurPageIndex < maxPage)
	{
		_CurPageIndex ++;
		UpdateGuildWelfarePurchasePage();
	}
}

void UMMOUIGuildWelfarePanel::UpdateGuildWelfarePurchasePage()
{
	UpdateGuildWelfarePurchaseList();

	UINT32 groupCount = MMOGuildData::getSingleton().GetGuildWelfareGroupCount();
	INT maxPage = appCeil((FLOAT)groupCount / (FLOAT)GUILD_WELFARE_GROUP_PER_PAGE);
	eventCallSetGuildWelfarePage(_CurPageIndex, maxPage);
}

void UMMOUIGuildWelfarePanel::UpdateGuildWelfarePurchaseList()
{
	UGFxObject* dataArray = GFXPlayer->CreateArray();
	if (!dataArray)
	{
		return;
	}

	for (INT i = 0; i < GUILD_WELFARE_GROUP_PER_PAGE; ++ i)
	{
		UGFxObject* object = GFXPlayer->CreateObject(TEXT("Object"));
		if (object)
		{
			UGFxObject* welfareArray = GFXPlayer->CreateArray();
			if (welfareArray)
			{
				GuildWelfareInfoList guildWelfareInfoList;
				guildWelfareInfoList.clear();
				UINT32 groupIndex = (_CurPageIndex - 1) * GUILD_WELFARE_GROUP_PER_PAGE + (i + 1);
				MMOGuildData::getSingleton().GetGuildWelfareListByGroup(groupIndex, guildWelfareInfoList);

				int index = 0;
				GuildWelfareInfoList::iterator iter = guildWelfareInfoList.begin();
				for (; iter != guildWelfareInfoList.end(); ++ iter)
				{
					UINT32 welfareId = iter->WelfareId;
					UINT32 welfareLv = iter->WelfareLv;

					GuildWelfareData welfareData;
					if (!MMOGuildData::getSingleton().GetGuildWelfareData(welfareId, welfareLv, welfareData))
					{
						continue;
					}

					UBuff* buff = MMOFacade::getSingleton().FindBuffTemplate(welfareData.BuffId, 0);
					if (!buff)
					{
						continue;
					}

					UGFxObject* welfareObject = GFXPlayer->CreateObject(TEXT("Object"));
					if (welfareObject)
					{
						welfareObject->SetInt(TEXT("guild_wel_id"), welfareData.WelfareId);
						welfareObject->SetInt(TEXT("guild_wel_buff"), welfareData.BuffId);
						welfareObject->SetString(TEXT("guild_wel_name"), buff->BuffName.GetNameString());
						welfareObject->SetString(TEXT("guild_wel_icon_name"), buff->GetBuffIconName());
						welfareObject->SetInt(TEXT("guild_wel_level"), welfareLv);
						welfareObject->SetInt(TEXT("guild_wel_max_level"), welfareData.MaxLevel);

						FString levelReq = MMOUI::ParseLocalizedPropertyPath(TEXT("Properties.Item.RequireLevel")) + TEXT(": >=") + appItoa(welfareData.ExchangeLevelReq);
						welfareObject->SetString(TEXT("guild_wel_level_req"), levelReq);

						UINT8 exchangeTimes = welfareData.ExchangeMax;
						eVipType vipType = MMOVipManager::getSingleton().GetMyCurrentVipType();
						switch (vipType)
						{
						case eVIPTyp_None:
							exchangeTimes = welfareData.ExchangeMax;
							break;
						case eVIPTyp_LV1:
							exchangeTimes = welfareData.VipExchangeMax1;
							break;
						case eVIPTyp_LV2:
							exchangeTimes = welfareData.VipExchangeMax2;
							break;
						case eVIPTyp_LV3:
							exchangeTimes = welfareData.VipExchangeMax3;
							break;
						}

						FString leftTimes = appItoa(iter->AlreadyBuyTime) + TEXT("/") + appItoa(exchangeTimes);
						welfareObject->SetString(TEXT("guild_wel_left_time"), leftTimes);
						
						FString moneyReq1 = TEXT("");
						if (welfareData.ExchangeMoneyReq > 0)
						{
							moneyReq1 = UITextParser::HTMLMoneyIconString(MONEYTYPE_02, welfareData.ExchangeMoneyReq);
						}
				
						FString moneyReq2 = TEXT("");
						if (welfareData.ExchangeContributeReq > 0)
						{
							moneyReq2 = MMOUI::ParseLocalizedPropertyPath(TEXT("Properties.EMONEY_TYPE.E_MONEYTYPE_GUILD")) + TEXT(":") + appItoa(welfareData.ExchangeContributeReq);
						}

						welfareObject->SetString(TEXT("guild_wel_money_req"), moneyReq2 + TEXT(" ") + moneyReq1);

						welfareArray->SetElementObject(index, welfareObject);
						index ++;
					}
				}

				object->SetObject(TEXT("guild_wel_group"), welfareArray);
			}
		}

		dataArray->SetElementObject(i, object);
	}

	eventCallUpdateGuildWelfarePurchaseList(dataArray);
}

//////////////////////////////////////////////////////////////////////////

void UMMOUIGuildWelfarePanel::ASWelfarePageUp()
{
	PageUp();
}

void UMMOUIGuildWelfarePanel::ASWelfarePageDown()
{
	PageDown();
}

void UMMOUIGuildWelfarePanel::ASPurchaseWelfare(INT id)
{
	CMessageHandler::GetInstance().Send_PurchaseGuildWelfare(id);
}