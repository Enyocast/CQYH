// oasample.cpp: Defines the console application entry point.
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
 
//Authentication class: authentication callback
int SNDACALLBACK  MyCallBackFuc(int nMsgType, unsigned long nUniqueId, ISDOAMsg *pMsg) 
{ 
    printf("Result1 is:%s\nResult2 is:%s\nReturn is:%d\nuniqueId is:%d\n",
 
            pMsg->GetValue("SNDAID"),    //Get the numeric account ID
 
            pMsg->GetValue("IDCARD"),    //Get the identity card number
 
            nMsgType,
 
            nUniqueId
 
          );
 
    return 0; 
} 

//Order handler: process in the callback
int SNDACALLBACK MsgHandle(int msgType, ISDOAMsg *req, ISDOAMsg *res) 
{ 
    static int i = 0; 
    //Message type
    switch (msgType) 
    { 
      //Notification message (item delivery, voucher consignment, voucher purchase, or player trade)
      case SDOA_ITEM_SEND_REQUEST: 
      { 
        //The notification has the following parameters; GetValue returns NULL for missing parameters
        printf("orderid=%s\n",    req->GetValue("orderId")); 
        printf("payStatus=%s\n",  req->GetValue("payStatus")); 
        printf("sendTimes=%s\n",  req->GetValue("sendTimes")); 
        printf("callTime=%s\n",   req->GetValue("callTime")); 
        printf("userId=%s\n",     req->GetValue("userId")); 
        printf("goodsNum=%s\n",   req->GetValue("goodsNum")); 
        printf("goodsInfo=%s\n",  req->GetValue("goodsInfo")); 
        printf("indication=%s\n", req->GetValue("indication")); 
        printf("payErrorMsg=%s\n",req->GetValue("payErrorMsg")); 
 
        //Game store server business logic
 
 
        //After processing, set the following response parameters
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
 
      //Recharge notification message
	
      case SDOA_DEPOSIT_REQUEST: 
      { 
        // GetValue returns NULL if a parameter is missing
        printf("appId=%s\n",     req->GetValue("appId")); 
        printf("areaId=%s\n",    req->GetValue("areaId")); 
        printf("groupId=%s\n",   req->GetValue("groupId")); 
        printf("depValue=%s\n",  req->GetValue("depValue")); 
        printf("orderId=%s\n",   req->GetValue("orderId")); 
        printf("userId=%s\n",    req->GetValue("userId")); 
        printf("callTime=%s\n",  req->GetValue("callTime")); 
        printf("indication=%s\n",req->GetValue("indication")); 
 
        //Game store server business logic
 
 
        //After processing, set the following response parameters
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
    int nMsgType = 1;		   //Component message type
	  int nOrderMsgType = 1;	   //Order message type, determined by the game server

	  //Authentication interface usage example
    if(nMsgType == 1) 
    { 
         
		// The game client sends this token to the game server, which validates it through the Shanda server component
        char szToken[] = "mhTmur5RDmybh7Cd2g9+oOUHuhzJWNTMI7ahrmMEwX1Tfr74XcD4c7dRDCRrzTb \
                          O67wboBJZT5DnbBqsNC42jf+PBDWDv7gHRU8BmLZ59egaA41YIctQw9TNgLXaM7kuNT\A0QjcwRjE1MkI5MUE1QThFMzBDNzc2MDQxRDI3OUY="; 
 
        //Create a login authentication object
        ISDOAUserInfoAuthen* ptr = sdoaCreateUserInfoAuthen(); 
        memset(g_szBuf,0,1024); 
 
        //Initialize the authentication interface
        ptr->Initialize("./sdoa4server.ini", MyCallBackFuc); 
 
        //Get the authentication result
        int b = ptr->AsyncGetUserInfo(szToken,"61.172.247.235",0); 
        if( b == 0 ) 
        { 

		    //Process the authentication result on the game server;
        } 
        else 
        { 
            printf("NOK"); 
			//Handle authentication failure on the game server
        } 
		::Sleep(20); 
        printf("sleep over"); 

		//Release resources
		ptr->Release(); 
    } 

	///Order handler usage example
    if(nMsgType == 2) 
	{
		//Create an order handler
		ISDOAOrderHandler* pOrderHandle = sdoaCreateOrderHandler(); 
	 
		//Initialize the QuanFuTong client
		pOrderHandle->Initialize("sdoa4server.ini", MsgHandle); 
	 
		//Generate a unique order number in the function; the game server must save it
		char szId[33]; 
		pOrderHandle->GetUniqueId(szId); 
		printf("qftGetUniqueId = %s\n", szId); 
	 
	 
		//Create order information
		ULONG obj = pOrderHandle->CreateOrderInfo(1); 
		if (obj == 0) 
			return false;

		//Some order parameters come from the client (such as item details); the server passes them to its functions and generates the order number through the server component.
	    switch(nOrderMsgType)
		{
			case 1: //Voucher item purchase: message types require different keys and values, mainly order details; see the documentation

				pOrderHandle->SetOrderInfoValue(obj , "orderId",   szId);                     //Order number; the server must save it
				pOrderHandle->SetOrderInfoValue(obj , "userId",    "98009999");				  //User ID
				pOrderHandle->SetOrderInfoValue(obj , "payType",   "3");                      //Paid currency type, e.g. Shanda vouchers: 3
				pOrderHandle->SetOrderInfoValue(obj , "amount",    "32");                     //Total payment
	

				pOrderHandle->SetOrderInfoValue(obj , "goodsNum",  "2");                      //Number of item types purchased
				pOrderHandle->SetOrderInfoValue(obj , "goodsInfo", "1098,1,10#1099,1,22");    //Item details (items used to exchange for vouchers)
			  pOrderHandle->SetOrderInfoValue(obj , "sessionId", "320000000000000000000000"); //Session ID, currently set to zero
				pOrderHandle->SetOrderInfoValue(obj , "indication","0"); 
				break;

			case 3: //Voucher consignment parameters; the game server must save the purchase information, especially the order number

				pOrderHandle->SetOrderInfoValue(obj , "orderId",   szId);                       //Order number; the server must save it
				pOrderHandle->SetOrderInfoValue(obj , "userId",    "98009999");                 //User ID
				pOrderHandle->SetOrderInfoValue(obj , "payType",   "3");						//Paid currency type, e.g. Shanda vouchers: 3
				pOrderHandle->SetOrderInfoValue(obj , "amount",    "30");                       //Total payment

				pOrderHandle->SetOrderInfoValue(obj , "confirm",   "1");                        //Consignment operation type
				pOrderHandle->SetOrderInfoValue(obj , "sessionId", "0");                        //Session ID, currently set to zero
				pOrderHandle->SetOrderInfoValue(obj , "goodsNum",  "1");						//Number of item types purchased
				pOrderHandle->SetOrderInfoValue(obj , "goodInfo",  "1,999999,30");              //Item details (consigned voucher information; itemid is 999999

				pOrderHandle->SetOrderInfoValue(obj , "indication","0");                        //Additional command
				break;		
		    
			case 4: //Voucher purchase parameters; the game server must save the purchase information, especially the order number

				pOrderHandle->SetOrderInfoValue(obj , "orderId",          szId);							  //Order number; the server must save it
				pOrderHandle->SetOrderInfoValue(obj ,  "userId",          "98009999");						  //User ID
				pOrderHandle->SetOrderInfoValue(obj ,  "payType",         "3");								  //Paid currency type, e.g. Shanda vouchers: 3
				pOrderHandle->SetOrderInfoValue(obj ,  "amount",          "60");							  //Total payment

				pOrderHandle->SetOrderInfoValue(obj ,  "sessionId",       "0");								  //Session ID, currently set to zero
				pOrderHandle->SetOrderInfoValue(obj ,  "goodsNum",        "1");                               //Number of item types purchased
				pOrderHandle->SetOrderInfoValue(obj ,  "goodInfo",        "1,109001,30#1,109002,30");         //Item details (items used to exchange for vouchers)
				pOrderHandle->SetOrderInfoValue(obj ,  "indication",      "0");                               //Additional command

				pOrderHandle->SetOrderInfoValue(obj ,  "orderidRelation", "1000020090312090000000000090999"); //Related order number (generated by the voucher consignment)
				pOrderHandle->SetOrderInfoValue(obj ,  "userIdDest",      "98006666");					      //Voucher buyer account
				pOrderHandle->SetOrderInfoValue(obj ,  "feeDest",         "1");								  //Fee paid by the voucher buyer
				pOrderHandle->SetOrderInfoValue(obj ,  "userIdSrc",       "98009999");                        //Voucher seller account

				pOrderHandle->SetOrderInfoValue(obj ,  "feeSrc",          "0");                               //Fee paid by the voucher seller
				break;
			
			case 5:  //Trade parameters; the game server must save the purchase information, especially the order number
				pOrderHandle->SetOrderInfoValue(obj , "orderId",   szId);                       //Order number; the server must save it
				pOrderHandle->SetOrderInfoValue(obj , "userId",    "98009999");                 //User ID
				pOrderHandle->SetOrderInfoValue(obj , "payType",   "3");						//Paid currency type, e.g. Shanda vouchers: 3
				pOrderHandle->SetOrderInfoValue(obj , "amount",    "30");						//Total payment

				pOrderHandle->SetOrderInfoValue(obj , "sessionId", "0");						//Currently set to zero
				pOrderHandle->SetOrderInfoValue(obj , "goodsNum",  "1");						//Number of item types purchased
				pOrderHandle->SetOrderInfoValue(obj , "goodInfo",  "1,999999,30");              //Item details (items for sale)
				pOrderHandle->SetOrderInfoValue(obj , "indication","0");						//Additional command
				                                     
				pOrderHandle->SetOrderInfoValue(obj , "userIdDest","98006666");                 //Voucher buyer account (the game account offering items)
				pOrderHandle->SetOrderInfoValue(obj , "feeDest",   "1");						//Voucher buyer fee (item seller transaction fee); charging rules are defined by the game
				pOrderHandle->SetOrderInfoValue(obj , "userIdSrc", "98009999");                 //Voucher seller account (the game account offering vouchers)
				pOrderHandle->SetOrderInfoValue(obj , "feeSrc",    "0");						//Voucher seller fee (item buyer transaction fee); charging rules are defined by the game
				break;
		}

		//Sign the data in BuildOrderUrl and generate a URL parameter string to send to the game client;
		char szUrl[2048]; 
		pOrderHandle->BuildOrderUrl(obj, szUrl); 

        /*
		*  Order information must be processed by the game provider
		*  The game server must store the order and perform related processing here; the signed string is sent to the game client,
		*  which forwards it through IWG to the billing gateway to complete the billing request.
		*/
	 
		//Destroy order information
		pOrderHandle->DestroyOrderInfo(obj); 
		while (1) 
		{ 
			#ifdef WIN32 
				::Sleep(1000); 
			#else 
				sleep(1); 
			#endif 
		} 
	 
		//Shut down the QuanFuTong client
		pOrderHandle->UnInitialize(); 
	 
		//Release resources
		pOrderHandle->Release(); 
		return 0; 
		
	}

    return 0; 

}

