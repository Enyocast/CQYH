#ifndef _STATISTIC_H_
#define _STATISTIC_H_

class CRole;
class CNpc;
class CCharacter;
class CSpell;
struct Item;
struct QUEST_DATA;

class  CStatistic
{
public:
	CStatistic();
	~CStatistic();

	BOOL Init(void);
	BOOL UnInit(void);

	static CStatistic& GetInstance(void);

private:

	static CStatistic m_Instance;

public:
	void OnCompareMaxValue(CRole* poRole, INT32 nCompareType, INT32 Value);

	void OnAddMoney(CRole* poRole, INT32 nAddType, INT32 nMoneyType, INT32 nMoneyCount);
	void OnKillNpc(CRole* poRole, CNpc* poNpc);
	void OnKilledByNpc(CRole* poRole, CNpc* poNpc);
	void OnKilledByPlayer(CRole* poKiller, CRole* poVictim);
	void OnCompleteQuest(CRole* poRole, const QUEST_DATA* pQuest);
	void OnHurt(CRole* poVictim, CCharacter* poDealer, INT32 nEffectValue);
	void OnUseItem(CRole* poRole, Item* pItem);
	void OnRevive(CRole* poRole, INT32 nMoneyType, INT32 nMoneyCount);
	void OnKillWithNoGuilty(CRole* poRole);
	void OnComposeItem(CRole* poRole, INT32 nColor, INT32 nCount);
	void OnDecomposeItem(CRole* poRole, INT32 nColor, INT32 nCount);
	void OnRealShopMoney(CRole* poRole, INT32 nItemID, INT32 nStackCount, INT32 nItemCount, INT32 nOrginalPrice);
};

#endif // _STATISTIC_H_