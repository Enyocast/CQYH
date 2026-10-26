/*
* Copyright (c) 2009,上海盛大网络SDG账务部
* All rights reserved.
* 
* 文件名称： SOTSCOMMONDEFINE.h
* 摘    要： 定义了SOTS的通用信息
* 
* 当前版本： 1.0
* 修改内容：
* 作    者：xhq
* 完成日期： 2009年3月10日
*/

#ifndef SOTSCOMMONDEFINE_H
#define SOTSCOMMONDEFINE_H

#define SOTS_API_OK     				1			    /// 成功

#define ERROR_INVALID_SOTS_RPC_HANDLE	0xFFFFFFFF		/// 没有空闲处理消息句柄
#define ERROR_INVALID_SERVICE			0xFFFFFFFE   	/// 调用的业务没有开通
#define ERROR_SOTS_API_NOT_INIT_FINISH  0xFFFFFFFD		/// 程序还没有完成启动
#define ERROR_INIT_CONFIG_FILE			-100002			/// 错误的初始化配置文件
#define ERROR_NOT_EXIT_SOTS_CLT_INFO	-100003			/// 无效的配置信息
#define ERROR_LEN_INFO				    -100004			/// 无效的长度信息
#define ERROR_OTHER_INFO				-199999			/// 其他错误

#define SotsMSGVERSION            		2090312  		// 消息的版本信息
typedef struct
{
    int  msgLen      ;  /// 整个消息包的字节长度，包括消息头和消息体                    
    int  msgType     ;  /// 消息类型，处理同一服务的各种来回消息的类型区分              
	char msgId[32+1] ;  /// 消息包序列号,主动发送方提供，反馈消息与请求消息msgId保持一致
	int  callTime    ;  /// 发送时间                                                    
    int  version     ;  /// 消息协议的版本信息                    
}SotsMsgHeadDef;

#define SVCSOTSSYSTEM "SVCSOTSSYSTEM"
#define TYPESOTSCLIENTINFO            0x00000001   /// 客户端的配置信息消息

/*********************************************
功能：记录客户端的属性 
	  客户端的IP,SERVICEID,AREAID,GROUPID,能处理的业务等信息
**********************************************/
typedef struct
{
	UINT32	clientId;			/// 客户端的ID号 唯一(由服务器来配置)
	UINT32	gameId;			    /// 游戏ID
	UINT32	areaId;				/// 区ID
	UINT32	groupId;			/// 组ID
	UINT32	hostId;				/// 机器ID
	char	localIp[16];		/// 本地客户端的IP地址
	UINT32	localPort;			/// 本地客户端的端口号
	char	serviceInfo[512];	/// 处理的业务信息如：Author;Account;ServiceSendItem
	char    apiVersion[30];     /// API 的版本信息
	int     bodyLen;            /// 消息体信息长度 （保留使用）
	char	*bodyInfo;  	    /// 消息体信息指针（保留使用）
}SOTSCLIENTINFO;

typedef struct
{
	SotsMsgHeadDef msgHead;
	SOTSCLIENTINFO msgBody;
}SotsClientInfoDef;

#endif

