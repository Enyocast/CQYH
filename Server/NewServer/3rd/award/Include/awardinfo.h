#ifndef _AWARDINFO_
#define _AWARDINFO_

#include "svccommoninfo.h"

#define SVCAWARDITEM	"SVCAWARD"   /// 领奖消息服务  

#define AWARDAUTHENREQ            0x00000001   /// 领奖认证请求  
#define AWARDAUTHENRES            0x80000001   /// 领奖认证反馈  
#define AWARDACK                  0x00000002   /// 领奖确定  
#define GOLDAWARDAUTHENREQ        0x00000003   /// 金牌领奖认证请求  
#define GOLDAWARDAUTHENRES        0x80000003   /// 金牌领奖认证反馈 
#define GOLDAWARDACK              0x00000004   /// 金牌领奖确定			

#define	NO_AWARDITEM			0xffffffff
#define	PACKET_ERROR			0xfffffffe
#define ALREADY_AWARD			0xfffffffd

#define	MAX_DESC_LEN			  64

#pragma pack (push,4)  /// 指定按 4 字节对齐

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

