#ifndef _SVCPD_H_
#define _SVCPD_H_

#define SVCPD "SVCPD"
#define SVCPDMSGVERSION 1130927

/** Message definitions */
#define SVCPDC2SREQ 0x00000001
#define SVCPDC2SRES 0x80000001
#define SVCPDC2SREQEX 0x00000002
#define SVCPDC2SRESEX 0x00000002


/** Personalized interface methods */
#define GETINDIVIDUALTREND "analysis.getIndividualTrend"
#define GETCHARACTERTREND "analysis.getCharacterTrend"
#define GETPLATFORMTREND "analysis.getPtIndexInfo"
#define GETDAILYTREND "getDnFeedback"
#define GETRECOMMENDITEM "getRecommendItem"


/** string len*/
#define MAX_ORDERID_LEN 32
#define MAX_ROLENAME_LEN 32
#define MAX_ROLEID_LEN 32
#define MAX_ROLEID_LEN 32
#define MAX_USERID_LEN 32
#define MAX_MSGID_LEN 32
#define MAX_METHOD_LEN 32
#define MAX_JASON_LEN 1024
#define MAX_PARAM_LEN 1024

/** Message structure definitions */
#pragma pack (push,1)  /// Set 1-byte alignment

typedef struct
{
    int  msgLen      ;  /// Total message length in bytes, including header and body
    int  msgType     ;  /// Message type, distinguishing request and response types for the same service
    char msgId[MAX_MSGID_LEN+1] ;  /// Message serial number supplied by the initiator; the response uses the request msgId
    int  callTime    ;  /// Send time
    int  version     ;  /// Message protocol version
}SotsPdMsgHeadDef;

typedef struct{
    int gameId; //Game ID
    char idvMethod[MAX_METHOD_LEN+1];
    char userId[MAX_USERID_LEN+1]   ;  //Player account
    //char roleId[MAX_ROLEID_LEN+1];
    char roleName[MAX_ROLENAME_LEN+1] ; //Character name
    char params[MAX_PARAM_LEN+1];//Format: matrix_id=16&account=sayaye8
}PersonalDataC2SReqDef;

typedef struct{
    int result; //0: success; other: failure
    char userId[MAX_USERID_LEN+1]   ;  //Player account
    char roleName[MAX_ROLENAME_LEN+1]; //Character name
    char jasonRes[MAX_JASON_LEN+1];    //jason format
}PersonalDataC2SResDef;

typedef struct{
    SotsPdMsgHeadDef msgHead;
    PersonalDataC2SReqDef msgBody;
}SvcpdC2SReq;

typedef struct{
    SotsPdMsgHeadDef msgHead;
    PersonalDataC2SResDef msgBody;
}SvcpdC2SRes;

/*typedef struct{
    int gameId; //Game ID
    int areaId;
    int groupId;
    //int hostId;
    char userId[MAX_USERID_LEN+1]   ;  //Player account
    char roleId[MAX_ROLEID_LEN+1];  //Character ID
    char roleName[MAX_ROLENAME_LEN+1] ; //Character name
}GetIndividualTrendC2SReqDef;

typedef struct{
    SotsPdMsgHeadDef msgHead;
    GetIndividualTrendC2SReqDef msgBody;
}GetIndividualTrendC2SReq;
*/
#pragma pack (pop) /// Restore default alignment

#endif  //_SVCPD_H_

