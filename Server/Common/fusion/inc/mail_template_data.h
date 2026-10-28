#ifndef _MAIL_TEMPLATE_DATA_H_
#define _MAIL_TEMPLATE_DATA_H_

#include "string_def.h"
#include "data_manager.h"
struct MAIL_TEMPLATE_DATA
{
    INT32 m_nTemplateID;
    char m_szMailSubject[MAIL_SUBJECT_LEN];
    char m_szMailContent[MAIL_CONTENT_LEN];
    INT32 m_nItemID;
    INT32 m_nItemCount;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, MAIL_TEMPLATE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

enum MAIL_TEMPLATE_ID
{
    mtiInvalid,

    mtiAward,
    mtiSend,
    mtiDungeonFinshReward,

    mtiGuildBeBanished = 2000,
    mtiGuildApplyFailed,
    mtiGuildApplyAllianceFailed,
    mtiGuildDrawSalary,
    mtiGuildDungeonAward,
    mtiGuildDungeonNoAward,
    mtiGuildNoMoneyToMaintenance,
    mtiGuildDisband,
    mtiGuildWarAttackSucc,
    mtiGuildWarDefenceFailed,
    mtiGuildWarAttackFailed,
    mtiGuildWarDefenceSucc,
    mtiDeclaredGuildWarMailToAttack,
    mtiDeclaredGuildWarMailToDefence,
    mtiGuildAlliance,
    mtiGuildEnemy,
    mtiGuildWarDeclaredToAttack,
    mtiGuildWarDeclaredToDefence,

    mtiRealMoneyShop = 3000,
    mtiRealMoneyShopGive,
    mtiBagFullItem,

    mtiAuctionSuccessSeller = 3100,
    mtiAuctionSuccessBuyer,
    mtiAuctionFailSellerExpire,
    mtiAuctionFailBuyer,
    mtiAuctionLeftMoneyExpireReturnItem,
    mtiAuctionLeftMoneyExpireReturnDeposit,
    mtiAuctionOverBid,
    mtiAuctionBidSuccess,
    mtiAuctionSellSuccessTemp,
    mtiAuctionBuySuccessTemp,
    mtiAuctionLeftMoneyExpireBuyer,
    mtiAuctionFailSellerCancel,

    mtiExchangeBuySuccess = 3200,
    mtiExchangeSellSuccess,
    mtiExchangeBuyFailed,
    mtiExchangeSellFailed,
    mtiExchangeBuyError,
    mtiExchangeSellError,

    mtiWeaponLevelUpFinish = 3300,

    mtiMasterCZStudent = 4000,
    mtiMasterCZMaster,
    mtiMstCZS2TStudent,
    mtiMstCZS2TTeacher,
    mtiMstCZT2SStudent,
    mtiMstCZT2STeacher,
    mtiMstCZC2CSelf,
    mtiMstCZC2CTarget,

	mtiTeamAuctionSendItemtoLeader = 5000,
	mtiTeamAuctionSendItemtoWinner,
	mtiTeamAuctionSendBonus,
	mtiTeamAuctionReturnDeposite,
};
#endif // _MAIL_TEMPLATE_DATA_H_
