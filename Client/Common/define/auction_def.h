#ifndef _AUCTION_DEF_H_
#define _AUCTION_DEF_H_

#define AUCTION_SEARCH_RESULT_ITEMS_PER_PAGE (50)

enum EAuctionSearchResultSortBy
{
    esbTotalPrice,
    esbBuyoutPrice,
    esbFinishTime,
    esbTotal
};

enum EAuctionStatus
{
    easInvalid,
    easEffective,       //竞拍中
    easCanceled,        //主动取消
    easExpired,         //流拍
    easWaitForPayment,  //拍卖成功，等待付尾款
    easFinished,        //拍卖成功，尾款已付清
    easPaymentExpired,  //拍卖成功，尾款超时
    easError,           //错误单
    easTotal
};

enum EAuctionBuyType
{
    eabInvalid,
    eabtBuyout,
    eabtBid,
};

static const UINT8 MAX_AUCTION_TYPE = 5;
static const UINT8 MAX_AUCTION_SUBTYPE = 5;

static const INT32 MAX_AUCTION_TIME_INTERVAL_TYPE = 3;

#endif // _AUCTION_DEF_H_
