#ifndef _SVCPD_H_
#define _SVCPD_H_

#define SVCPD "SVCPD"
#define SVCPDMSGVERSION 1130927

/** 消息定义*/
#define SVCPDC2SREQ 0x00000001
#define SVCPDC2SRES 0x80000001
#define SVCPDC2SREQEX 0x00000002
#define SVCPDC2SRESEX 0x00000002


/**个性化接口方法*/
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

/** 消息结构定义*/
#pragma pack (push,1)  /// 指定按 1 字节对齐

typedef struct
{
    int  msgLen      ;  /// 整个消息包的字节长度，包括消息头和消息体                    
    int  msgType     ;  /// 消息类型，处理同一服务的各种来回消息的类型区分              
    char msgId[MAX_MSGID_LEN+1] ;  /// 消息包序列号,主动发送方提供，反馈消息与请求消息msgId保持一致
    int  callTime    ;  /// 发送时间                                                    
    int  version     ;  /// 消息协议的版本信息                    
}SotsPdMsgHeadDef;

typedef struct{
    int gameId; //游戏ID
    char idvMethod[MAX_METHOD_LEN+1];
    char userId[MAX_USERID_LEN+1]   ;  //玩家帐号
    //char roleId[MAX_ROLEID_LEN+1];
    char roleName[MAX_ROLENAME_LEN+1] ; //角色名
    char params[MAX_PARAM_LEN+1];//格式matrix_id=16&account=sayaye8
}PersonalDataC2SReqDef;

typedef struct{
    int result; //0: 成功；other: 失败
    char userId[MAX_USERID_LEN+1]   ;  //玩家帐号
    char roleName[MAX_ROLENAME_LEN+1]; //角色名
    char jasonRes[MAX_JASON_LEN+1];    //jason格式
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
    int gameId; //游戏ID
    int areaId;
    int groupId;
    //int hostId;
    char userId[MAX_USERID_LEN+1]   ;  //玩家帐号
    char roleId[MAX_ROLEID_LEN+1];  //角色ID
    char roleName[MAX_ROLENAME_LEN+1] ; //角色名
}GetIndividualTrendC2SReqDef;

typedef struct{
    SotsPdMsgHeadDef msgHead;
    GetIndividualTrendC2SReqDef msgBody;
}GetIndividualTrendC2SReq;
*/
#pragma pack (pop) /// 取消指定对齐，恢复缺省对齐

#endif  //_SVCPD_H_

