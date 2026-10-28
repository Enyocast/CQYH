#ifndef _SVCCOMMONINFO_
#define _SVCCOMMONINFO_

#define MAX_ROLENAME_LEN            32  // Character name length
#define MAX_ORDERID_LEN             32  // Order ID or user information length
#define IP_ADDRESS_LEN              15  // IP address length, e.g. 61.172.252.37
#define MAX_TIME_LEN                19  // Time length, format: YYYY-MM-DD HH24:MI:SS
#define MAX_DATE_LEN                8   // Date length, format: YYYYMMDD
#define MAX_BATCHID_LEN             10  // Batch ID length, format: CQ007
#define MAX_ITEMNAME_LEN            20  // Item name length
#define	MAX_PROFESSION_LEN				16  // Maximum user class name length

#define MSGVERSION            1090113  // Message version

#pragma pack (push,4)  /// Set 4-byte alignment

typedef struct
{
    int  msgLen                   ;  /// Total message length in bytes, including header and body
    int  msgType                  ;  /// Message type, distinguishing request and response types for the same service
	char msgId[MAX_ORDERID_LEN+1] ;  /// Message serial number supplied by the initiator; the response uses the request msgId
	int  callTime                 ;  /// Send time
    int  version                  ;  /// Message protocol version
}MsgHeadDef;

typedef struct
{
    char itemId[MAX_ITEMNAME_LEN+1] ;  /// Item ID or name
    int  itemNum              		;  /// Item count
	char validDate[MAX_DATE_LEN+1]  ;  /// Item validity start date, to the day, e.g. 20081212
	char expireDate[MAX_DATE_LEN+1] ;  /// Item expiration date, to the day, e.g. 20081212
    int  itemAttrLen          		;  /// Length of the variable-length itemAttr string
	char itemAttr[1]          		;  /// Item attributes, variable-length string of at most 60 characters
}ItemInfoDef;

#pragma pack (pop)

#endif

