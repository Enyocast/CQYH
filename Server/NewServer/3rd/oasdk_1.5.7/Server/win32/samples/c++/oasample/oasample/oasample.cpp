// oasample.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "sdoa4server.h" 
 
#include <string.h> 
 
#include <stdio.h> 
 
#ifdef WIN32 
 
#include <windows.h> 
 
#else 
 
#include <unistd.h> 
 
#endif 
 
char g_szBuf[1024]; 
 
//认证类----认证回调函数 
int SNDACALLBACK  MyCallBackFuc(int nMsgType, unsigned long nUniqueId, ISDOAMsg *pMsg) 
{ 
    printf("Result1 is:%s\nResult2 is:%s\nReturn is:%d\nuniqueId is:%d\n",
 
            pMsg->GetValue("SNDAID"),    //获得数字帐号
 
            pMsg->GetValue("IDCARD"),    //获得身份证号码
 
            nMsgType,
 
            nUniqueId
 
          );
 
    return 0; 
} 

//订单处理类---回调函数体内处理 
int SNDACALLBACK MsgHandle(int msgType, ISDOAMsg *req, ISDOAMsg *res) 
{ 
    static int i = 0; 
    //消息类型 
    switch (msgType) 
    { 
      //通知消息(包含道具发货消息,点券寄售消息, 点券购买消息,玩家交易消息) 
      case SDOA_ITEM_SEND_REQUEST: 
      { 
        //通知消息含有以下参数： 如果参数不存在，则GetValue返回NULL 
        printf("orderid=%s\n",    req->GetValue("orderId")); 
        printf("payStatus=%s\n",  req->GetValue("payStatus")); 
        printf("sendTimes=%s\n",  req->GetValue("sendTimes")); 
        printf("callTime=%s\n",   req->GetValue("callTime")); 
        printf("userId=%s\n",     req->GetValue("userId")); 
        printf("goodsNum=%s\n",   req->GetValue("goodsNum")); 
        printf("goodsInfo=%s\n",  req->GetValue("goodsInfo")); 
        printf("indication=%s\n", req->GetValue("indication")); 
        printf("payErrorMsg=%s\n",req->GetValue("payErrorMsg")); 
 
        //游戏商城服务器业务处理代码 
 
 
        //业务处理完成后，响应消息必须设置以下参数 
        i++; 
        char descMsg[256], appendix[256]; 
        printf(descMsg,  "descMsg-%d",  i); 
        printf(appendix, "appendix-%d", i); 
 
        res->SetValue("result", "0"); 
        res->SetValue("orderId", req->GetValue("orderId")); 
        res->SetValue("descMsg", descMsg); 
        res->SetValue("appendix",appendix); 
      } 
      break; 
 
      //充值通知消息 
	
      case SDOA_DEPOSIT_REQUEST: 
      { 
        // 如果参数不存在，则GetValue返回NULL 
        printf("appId=%s\n",     req->GetValue("appId")); 
        printf("areaId=%s\n",    req->GetValue("areaId")); 
        printf("groupId=%s\n",   req->GetValue("groupId")); 
        printf("depValue=%s\n",  req->GetValue("depValue")); 
        printf("orderId=%s\n",   req->GetValue("orderId")); 
        printf("userId=%s\n",    req->GetValue("userId")); 
        printf("callTime=%s\n",  req->GetValue("callTime")); 
        printf("indication=%s\n",req->GetValue("indication")); 
 
        //游戏商城服务器业务处理代码 
 
 
        //业务处理完成后，响应消息必须设置以下参数 
        i++; 
        char descMsg[256], appendix[256]; 
        printf(descMsg,  "descMsg-%d",  i); 
        printf(appendix, "appendix-%d", i); 
 
        res->SetValue("result", "0"); 
        res->SetValue("orderId", req->GetValue("orderId")); 
        res->SetValue("descMsg", descMsg); 
        res->SetValue("appendix",appendix); 
      } 
      break; 
    } 
    return 0; 
} 
 



int main(int argc, char* argv[])
{
    int nMsgType = 1;		   //组件消息类型
	  int nOrderMsgType = 1;	   //订单消息类型，具体订单消息类型，游戏服务端判断

	  //认证接口使用范例代码
    if(nMsgType == 1) 
    { 
         
		// 此token是由游戏客户端传给游戏服务器, 游戏服务端将调用盛大服务端组件接口对token进行验证
        char szToken[] = "mhTmur5RDmybh7Cd2g9+oOUHuhzJWNTMI7ahrmMEwX1Tfr74XcD4c7dRDCRrzTb \
                          O67wboBJZT5DnbBqsNC42jf+PBDWDv7gHRU8BmLZ59egaA41YIctQw9TNgLXaM7kuNT\A0QjcwRjE1MkI5MUE1QThFMzBDNzc2MDQxRDI3OUY="; 
 
        //创建登陆认证对象实例 
        ISDOAUserInfoAuthen* ptr = sdoaCreateUserInfoAuthen(); 
        memset(g_szBuf,0,1024); 
 
        //认证接口初始化 
        ptr->Initialize("./sdoa4server.ini", MyCallBackFuc); 
 
        //获取认证结果 
        int b = ptr->AsyncGetUserInfo(szToken,"61.172.247.235",0); 
        if( b == 0 ) 
        { 

		    //游戏服务器端处理认证结果；
        } 
        else 
        { 
            printf("NOK"); 
			//游戏服务器端处理认证失败情况
        } 
		::Sleep(20); 
        printf("sleep over"); 

		//释放资源 
		ptr->Release(); 
    } 

	///订单处理类使用范例代码 
    if(nMsgType == 2) 
	{
		//创建订单处理对象实例 
		ISDOAOrderHandler* pOrderHandle = sdoaCreateOrderHandler(); 
	 
		//初始化全付通客户端/ 
		pOrderHandle->Initialize("sdoa4server.ini", MsgHandle); 
	 
		//生成唯一订单号码 函数内生成 ,订单号码游戏服务端需要保存
		char szId[33]; 
		pOrderHandle->GetUniqueId(szId); 
		printf("qftGetUniqueId = %s\n", szId); 
	 
	 
		//创建订单信息 
		ULONG obj = pOrderHandle->CreateOrderInfo(1); 
		if (obj == 0) 
			return false;

		//订单消息的参数值有部分由客户端转入(如道具相关信息),服务端获取并传递给服务端的功能函数；订单号码则由服务端程序调用服务端组件生成。
	    switch(nOrderMsgType)
		{
			case 1: //点券购买道具消息，不同消息类型，需要传入不同的关键字，以及键值(主要为订单的相关信息)，具体参看说明文档

				pOrderHandle->SetOrderInfoValue(obj , "orderId",   szId);                     //定单号 服务端需要保存下来
				pOrderHandle->SetOrderInfoValue(obj , "userId",    "98009999");				  //用户id
				pOrderHandle->SetOrderInfoValue(obj , "payType",   "3");                      //付费游戏币类型 比如盛大点券 3
				pOrderHandle->SetOrderInfoValue(obj , "amount",    "32");                     //支付的总额
	

				pOrderHandle->SetOrderInfoValue(obj , "goodsNum",  "2");                      //购买道具种类
				pOrderHandle->SetOrderInfoValue(obj , "goodsInfo", "1098,1,10#1099,1,22");    //道具详细信息(填写用来兑换点券的道具信息)
			  pOrderHandle->SetOrderInfoValue(obj , "sessionId", "320000000000000000000000"); //会话id 目前填零
				pOrderHandle->SetOrderInfoValue(obj , "indication","0"); 
				break;

			case 3: //寄售点券  需要传入的参数列表,这些购买信息游戏服务器端需要保存，尤其是订单号码

				pOrderHandle->SetOrderInfoValue(obj , "orderId",   szId);                       //定单号 服务端需要保存下来
				pOrderHandle->SetOrderInfoValue(obj , "userId",    "98009999");                 //用户id
				pOrderHandle->SetOrderInfoValue(obj , "payType",   "3");						//付费游戏币类型 比如盛大点券 3
				pOrderHandle->SetOrderInfoValue(obj , "amount",    "30");                       //支付的总额

				pOrderHandle->SetOrderInfoValue(obj , "confirm",   "1");                        //寄售操作类型
				pOrderHandle->SetOrderInfoValue(obj , "sessionId", "0");                        //会话id 目前填零
				pOrderHandle->SetOrderInfoValue(obj , "goodsNum",  "1");						//购买道具种类
				pOrderHandle->SetOrderInfoValue(obj , "goodInfo",  "1,999999,30");              //道具详细信息(填写寄售的点券信息 itemid为999999

				pOrderHandle->SetOrderInfoValue(obj , "indication","0");                        //附加指令
				break;		
		    
			case 4: //购买点券  需要传入的参数列表,这些购买信息游戏服务器端需要保存，尤其是订单号码

				pOrderHandle->SetOrderInfoValue(obj , "orderId",          szId);							  //定单号 服务端需要保存下来
				pOrderHandle->SetOrderInfoValue(obj ,  "userId",          "98009999");						  //用户id
				pOrderHandle->SetOrderInfoValue(obj ,  "payType",         "3");								  //付费游戏币类型 比如盛大点券 3
				pOrderHandle->SetOrderInfoValue(obj ,  "amount",          "60");							  //支付的总额

				pOrderHandle->SetOrderInfoValue(obj ,  "sessionId",       "0");								  //会话id 目前填零
				pOrderHandle->SetOrderInfoValue(obj ,  "goodsNum",        "1");                               //购买道具种类
				pOrderHandle->SetOrderInfoValue(obj ,  "goodInfo",        "1,109001,30#1,109002,30");         //道具详细信息(填写用来兑换点券的道具信息)
				pOrderHandle->SetOrderInfoValue(obj ,  "indication",      "0");                               //附加指令

				pOrderHandle->SetOrderInfoValue(obj ,  "orderidRelation", "1000020090312090000000000090999"); //关联订单号码(填写寄售点券生成的订单号码)
				pOrderHandle->SetOrderInfoValue(obj ,  "userIdDest",      "98006666");					      //购买点券的帐号
				pOrderHandle->SetOrderInfoValue(obj ,  "feeDest",         "1");								  //购买点券玩家支付的缴费数目
				pOrderHandle->SetOrderInfoValue(obj ,  "userIdSrc",       "98009999");                        //出售点券账号

				pOrderHandle->SetOrderInfoValue(obj ,  "feeSrc",          "0");                               //出售点券玩家支付的收费费用
				break;
			
			case 5:  //交易信息 需要传入的参数列表,这些购买信息游戏服务器端需要保存，尤其是订单号码
				pOrderHandle->SetOrderInfoValue(obj , "orderId",   szId);                       //定单号 服务端需要保存下来
				pOrderHandle->SetOrderInfoValue(obj , "userId",    "98009999");                 //用户id
				pOrderHandle->SetOrderInfoValue(obj , "payType",   "3");						//付费游戏币类型 比如盛大点券 3
				pOrderHandle->SetOrderInfoValue(obj , "amount",    "30");						//支付的总额

				pOrderHandle->SetOrderInfoValue(obj , "sessionId", "0");						//目前填零
				pOrderHandle->SetOrderInfoValue(obj , "goodsNum",  "1");						//购买道具种类
				pOrderHandle->SetOrderInfoValue(obj , "goodInfo",  "1,999999,30");              //道具详细信息(出售的道具信息)
				pOrderHandle->SetOrderInfoValue(obj , "indication","0");						//附加指令
				                                     
				pOrderHandle->SetOrderInfoValue(obj , "userIdDest","98006666");                 //购买点券的帐号(出道具的游戏账号)
				pOrderHandle->SetOrderInfoValue(obj , "feeDest",   "1");						//购买点券玩家支付的缴费数目(交易消息卖出道具所支付手续费数目) 费用收取规则由游戏方定义
				pOrderHandle->SetOrderInfoValue(obj , "userIdSrc", "98009999");                 //出售点券账号(出点券的游戏账号)
				pOrderHandle->SetOrderInfoValue(obj , "feeSrc",    "0");						//出售点券玩家支付的收费费用(交易消息购买道具所支付的手续费数目) 费用收取规则由游戏方定义				
				break;
		}

		//对数据签名(签名过程在BuildOrderUrl函数类完成)并生成URL参数串，此字符串需要传给游戏客户端；
		char szUrl[2048]; 
		pOrderHandle->BuildOrderUrl(obj, szUrl); 

        /*
		*  订单信息必须由游戏方进行处理
		*  游戏服务端需要在这里将该笔订单消息入库，同时进行相关的业务处理；同时签名完的字符串将发送给游戏客户端，
		*  游戏客户端收到此签名串后，通过IWG转发给计费网关进行处理，完成本次计费请求。
		*/
	 
		//销毁订单信息 
		pOrderHandle->DestroyOrderInfo(obj); 
		while (1) 
		{ 
			#ifdef WIN32 
				::Sleep(1000); 
			#else 
				sleep(1); 
			#endif 
		} 
	 
		//全付通客户端卸载 
		pOrderHandle->UnInitialize(); 
	 
		//释放资源 
		pOrderHandle->Release(); 
		return 0; 
		
	}

    return 0; 

}

