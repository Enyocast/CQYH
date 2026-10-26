#ifndef _SVCCOMMONINFO_
#define _SVCCOMMONINFO_

#define MAX_ROLENAME_LEN            32  // 角色名字符长度
#define MAX_ORDERID_LEN             32  // 订单号或者用户信息字符长度
#define IP_ADDRESS_LEN              15  // ip地址长， 如：61.172.252.37
#define MAX_TIME_LEN                19  // 时间长， 格式为：YYYY-MM-DD HH24:MI:SS
#define MAX_DATE_LEN                8   // 时间长， 格式为：YYYYMMDD
#define MAX_BATCHID_LEN             10  // 批次号长， 格式为：CQ007
#define MAX_ITEMNAME_LEN            20  // 道具名称长
#define	MAX_PROFESSION_LEN			16  // 用户职业名称最大长度

#define MSGVERSION            1081225  // 消息的版本信息

typedef struct
{
    int  msgLen                   ;  /// 整个消息包的字节长度，包括消息头和消息体                    
    int  msgType                  ;  /// 消息类型，处理同一服务的各种来回消息的类型区分              
	char msgId[MAX_ORDERID_LEN+1] ;  /// 消息包序列号,主动发送方提供，反馈消息与请求消息msgId保持一致
	int  callTime                 ;  /// 发送时间                                                    
    int  version                  ;  /// 消息协议的版本信息                    
}MsgHeadDef;

typedef struct
{
    char itemId[MAX_ITEMNAME_LEN+1] ;  /// 道具ID或者道具名称
    int  itemNum              		;  /// 道具数量                           
	char validDate[MAX_DATE_LEN+1]  ;  /// 道具有效开始时间,精确到天,如:20081212
	char expireDate[MAX_DATE_LEN+1] ;  /// 道具失效时间,精确到天,如:20081212    
    int  itemAttrLen          		;  /// 变长字符窜itemAttr 的长度                    
	char itemAttr[1]          		;  /// 道具属性,变长字符窜,小于等于60
}ItemInfoDef;

#endif

