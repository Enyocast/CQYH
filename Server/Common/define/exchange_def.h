#ifndef _EXCHANGE_DEF_H_
#define _EXCHANGE_DEF_H_

enum EOrderType
{
	eotInvalid,
	eotBuy,
	eotSell
};

enum EOrderStatus
{
	eosInvalid,
	eosEffective,   //Active order
	eosCanceled,    //Canceled by user
	eosExpired,     //Canceled after timeout
	eosFinished,    //Fully filled
	eosError,       //Invalid order
	eosTotal,
};

#define MAX_ORDER_DETAIL_NUM      (512)

#endif	// _EXCHANGE_DEF_H_