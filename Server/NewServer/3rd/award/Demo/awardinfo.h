#ifndef _AWARDINFO_
#define _AWARDINFO_

#include "svccommoninfo.h"

#define SVCAWARDITEM	"SVCAWARD"   /// Reward claim message service

#define AWARDAUTHENREQ            0x00000001   /// Reward claim authentication request
#define AWARDAUTHENRES            0x80000001   /// Reward claim authentication response
#define AWARDACK                  0x00000002   /// Reward claim confirmation
#define GOLDAWARDAUTHENREQ        0x00000003   /// Gold reward claim authentication request
#define GOLDAWARDAUTHENRES        0x80000003   /// Gold reward claim authentication response
#define GOLDAWARDACK              0x00000004   /// Gold reward claim confirmation

#define	NO_AWARDITEM			0xffffffff
#define	PACKET_ERROR			0xfffffffe
#define ALREADY_AWARD			0xfffffffd

#define	MAX_DESC_LEN			  64

#pragma pack (push,4)  /// Set 4-byte alignment

typedef struct
{
        int gameId;
        int areaId;
        int groupId;
        int hostId;
        int awardType;
        int uidType;
        char userId[MAX_ORDERID_LEN+1];
        char authenTime[MAX_TIME_LEN+1];
        char orderId[MAX_ORDERID_LEN+1];
        char roleName[MAX_ORDERID_LEN+1];
        char roleProperty[MAX_PROFESSION_LEN+1];
        char batchId[MAX_BATCHID_LEN+1];
        char awardNum[MAX_ORDERID_LEN+1];
        char endpointIp[IP_ADDRESS_LEN+1];
        int userGrade;
        int awardGrade;
} GoldAwardAuthenReqDef;

typedef struct
{
	int result;
	char description[MAX_DESC_LEN+1];
	int uidType;
	char userId[MAX_ORDERID_LEN+1];
	char orderId[MAX_ORDERID_LEN+1];
	char awardNum[MAX_ORDERID_LEN+1];
	char roleName[MAX_ORDERID_LEN+1];
	char pkgName[MAX_DESC_LEN+1];
	int itemKindCount;
	int itemInfoLen;
	char itemInfo[1];
} GoldAwardAuthenResDef;

typedef struct
{
	int confirm;
	char description[MAX_DESC_LEN+1];
	int uidType;
	char userId[MAX_ORDERID_LEN+1];
	char orderId[MAX_ORDERID_LEN+1];
	int itemKindCount;
	int itemInfoLen;
	char itemInfo[1];
} GoldAwardAckDef;

typedef struct
{
	MsgHeadDef msgHead;
	GoldAwardAuthenReqDef msgBody;
} GoldAwardAuthenInfoReqDef;

typedef struct
{
	MsgHeadDef msgHead;
	GoldAwardAuthenResDef msgBody;
} GoldAwardAuthenInfoResDef;

typedef struct 
{
	MsgHeadDef msgHead;
	GoldAwardAckDef msgBody;
} GoldAwardAckInfoDef;

#pragma pack (pop)

#endif

