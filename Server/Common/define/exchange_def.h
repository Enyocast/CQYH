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
	eosEffective,   //有效单
	eosCanceled,    //主动撤单
	eosExpired,     //超时撤单
	eosFinished,    //完全成交
	eosError,       //错误单
	eosTotal,
};

#define MAX_ORDER_DETAIL_NUM      (512)

#endif	// _EXCHANGE_DEF_H_