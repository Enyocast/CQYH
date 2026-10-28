#ifndef _SENDITEMINFO_
#define _SENDITEMINFO_

#include "svccommoninfo.h"

#define SVCSENDITEM     "SVCSENDITEM"   /// Item message service

#define ITEMC2SREQ            0x00000001   /// Item send request
#define ITEMC2SRES            0x80000001   /// Item send response
#define ITEMS2CREQ            0x00000002   /// Item delivery request
#define ITEMS2CRES            0x80000002   /// Item delivery response

#pragma pack (push,4)  /// Set 4-byte alignment

typedef struct
{
    int  gameIdSrc                           ;
    int  areaIdSrc                           ;
    int  groupIdSrc                          ;
    int  hostIdSrc                           ;
    int  gameIdDest                          ;
    int  areaIdDest                          ;
    int  groupIdDest                         ;
	int  hostIdDest                          ;
	char orderId[MAX_ORDERID_LEN+1]          ;
	char batchId[MAX_BATCHID_LEN+1]          ;
	char endPointIp[IP_ADDRESS_LEN+1]        ;
	int  uidType                             ;
	char userId[MAX_ORDERID_LEN+1]           ;
	char roleName[MAX_ROLENAME_LEN+1]        ;
	char createTime[MAX_TIME_LEN+1]          ;
	int  itemKindCount                       ;
	int  itemInfoLen                         ;
	char itemInfo[1]                         ;
}ItemC2SReqDef;

typedef struct
{
    int  result;
	char desc[65];
    char orderId[MAX_ORDERID_LEN+1];
}ItemC2SResDef;

typedef struct
{
    int  gameId                              ;
    int  areaId                              ;
    int  groupId                             ;
    int  hostId                              ;
	char orderId[MAX_ORDERID_LEN+1]          ;
	char batchId[MAX_BATCHID_LEN+1]          ;
	int  uidType                             ;
	char userId[MAX_ORDERID_LEN+1]           ;
	char roleName[MAX_ROLENAME_LEN+1]        ;
	char createTime[MAX_TIME_LEN+1]          ;
	int  itemKindCount                       ;
	int  itemInfoLen                         ;
	char itemInfo[1]                         ;
}ItemS2CReqDef;

typedef struct
{
    int  result;
	char desc[65];
    char orderId[MAX_ORDERID_LEN+1];
}ItemS2CResDef;

typedef struct
{
	MsgHeadDef msgHead;
	ItemC2SReqDef msgBody;
}ItemC2SInfoReqDef;

typedef struct
{
	MsgHeadDef msgHead;
	ItemC2SResDef msgBody;
}ItemC2SInfoResDef;

typedef struct 
{
	MsgHeadDef msgHead;
	ItemS2CReqDef msgBody;
}ItemS2CInfoReqDef;

typedef struct
{
	MsgHeadDef msgHead;
	ItemS2CResDef msgBody;
}ItemS2CInfoResDef;

#pragma pack (pop)

#endif

