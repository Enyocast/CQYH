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
    easEffective,       //Bidding in progress
    easCanceled,        //Canceled by seller
    easExpired,         //Auction ended without a sale
    easWaitForPayment,  //Auction succeeded; awaiting final payment
    easFinished,        //Auction succeeded; final payment received
    easPaymentExpired,  //Auction succeeded; final payment expired
    easError,           //Invalid listing
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
