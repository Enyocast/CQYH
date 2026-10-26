/*
* Copyright (c) 2008,上海盛大网络SDG账务部
* All rights reserved.
* 
* 文件名称： SotsAPI.h
* 摘    要： 定义了Sots的API接口
* 
* 当前版本： 1.0
* 修改内容：
* 作    者：xionghq
* 完成日期： 2008年11月10日
*/

#ifndef SotsAPI_H
#define SotsAPI_H

#include "sdtype.h"
#include "sotscommondefine.h"

/// 申明API函数
#ifdef WIN32
#ifdef RPCCLT_EXPORTS
#define DECLSOTSAPI __declspec(dllexport)
#else
#define DECLSOTSAPI __declspec(dllimport)
#endif
#else
#define DECLSOTSAPI
#endif

/*********************************************
功能：pSotsMsgHandler回调类句柄，主要用于如下情况：
	1、异步调用的返回消息包;
	2、服务器主动发送的消息包;
	3、其他客户端调用SotsNotify接口的推送消息包 
参数：ULONG  异步调用时返回值（用于异步调用的返回消息包，其他情况无效）
	  char*  回调的消息包的 SERVICENAME
	  char*  回调的消息包
	  INT32  回调消息包的大小
**********************************************/
typedef void (* pSotsMsgHandler)(ULONG,char *,char*,INT32);

	
#ifdef __cplusplus
extern "C" 
{
#endif

/*********************************************
功能:	注册接口初始化函数 传入配置文件通过该配置文件从配置服务端获取客户端的配置信息
		指定异步调用的回调函数句柄 传入回调函数句柄
参数: 	configFileName 配置文件信息 
		handler 回调函数句柄 如果是同步调用可以不传入 默认为NULL
返回值: 1 成功 , 其他失败
**********************************************/
DECLSOTSAPI INT32 SotsInitialize(const char *configFileName,pSotsMsgHandler handler = NULL) ;

/*********************************************
功能:	注销函数
参数: 	无
返回值: 1 成功 , 其他失败
**********************************************/
DECLSOTSAPI INT32 SotsTerminate() ;


/*********************************************
功能:	异步调用函数 传入发送消息包信息,返回值为句柄号与回调的句柄号匹配
参数: 	const char *serviceName 消息服务名
		const void* data 发送消息包
		INT32 dataLen 发送消息包的长度
		UINT32 flags 发送消息包的类型: 0 普通消息包,1 消息包不需要反馈,4 消息必达,5 必达且不需要反馈（1和4的组合）
返回值: 大于0 成功,返回调用的句柄号,该句柄号在回调时传出 
		其他失败
**********************************************/
DECLSOTSAPI ULONG SotsAsynCall(const char *serviceName, 
						const void *data, INT32 dataLen, UINT32 flags) ;


/*********************************************
功能:	同步调用函数 传入发送消息包信息
参数: 	const char *serviceName 消息服务名
		const void* inData 发送消息包
		INT32 inDataLen 发送消息包的长度
		const void* outData 反馈消息包
		INT32 inDataLen 反馈消息包的长度
		UINT32 flags 发送消息包的类型: 0 普通消息包,1 消息包不需要反馈,4 消息必达,5 必达且不需要反馈（1和4的组合）
返回值: 反馈消息包outData长度,大于等于0 成功 , 其他失败
**********************************************/
DECLSOTSAPI INT32 SotsCall(const char *serviceName, 
						const void *inData, INT32 inDataLen, 
						void *outData, INT32 outDataLen, UINT32 flags) ;


/*********************************************
功能:	客户端到客户端的发送接口，不需要通过SERVICE。
参数: 	UINT32 gsId 客户端的GAMESERVER ID 号（由服务器配置）
		const char *serviceName 消息服务名
		const void* data 发送消息包
		INT32 dataLen 发送消息包的长度
		UINT32 flags 发送消息包的类型: 0 普通消息包,1 消息包不需要反馈,4 消息必达,5 必达且不需要反馈（1和4的组合）
返回值: 1 成功 , 其他失败。 
**********************************************/
DECLSOTSAPI INT32 SotsNotify(UINT32 gsId, const char *serviceName,const void* data, INT32 dataLen, UINT32 flags);


/*********************************************
功能:	获取唯一字符串函数 主要是为了统一各客户端使用统一的识别码
参数: 	char *orderId 输出字符串
		INT32 len 字符串orderid的长度	
返回值: 1 成功 , 其他失败
**********************************************/
DECLSOTSAPI INT32 GetSotsUniqueId(char *orderId,INT32 len) ;


/*********************************************
功能:	获取客户端的配置信息
参数: 	SOTSCLIENTINFO *info 客户端信息
返回值: 1 成功 , 其他失败
**********************************************/
DECLSOTSAPI INT32 GetSotsClientInfo(SOTSCLIENTINFO *info) ;


#ifdef __cplusplus
}
#endif

#endif

