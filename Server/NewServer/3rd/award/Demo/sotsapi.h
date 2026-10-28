/*
* Copyright (c) 2008, Shanghai Shanda Network SDG Accounting Department
* All rights reserved.
* 
* File name: SotsAPI.h
* Summary: Defines the Sots API interface
* 
* Current version: 1.0
* Changes:
* Author:xionghq
* Completed: November 10, 2008
*/

#ifndef SotsAPI_H
#define SotsAPI_H

#include "sdtype.h"
#include "sotscommondefine.h"

/// Declare API functions
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
Purpose: pSotsMsgHandler callback handle, used primarily for:
	1. Responses to asynchronous calls;
	2. Messages initiated by the server;
	3. Push messages from other clients calling SotsNotify
Parameters: ULONG asynchronous call return value (valid only for asynchronous responses)
	  char* SERVICENAME of the callback message
	  char* callback message
	  INT32 callback message size
**********************************************/
typedef void (* pSotsMsgHandler)(ULONG,char *,char*,INT32);

	
#ifdef __cplusplus
extern "C" 
{
#endif

/*********************************************
Purpose: Initialize the interface, using the supplied configuration file to fetch client configuration from the configuration server
		Specify the callback function handle for asynchronous calls
Parameters: configFileName configuration file information
		handler callback handle; optional for synchronous calls, defaults to NULL
Returns: 1 on success; other values indicate failure
**********************************************/
DECLSOTSAPI INT32 SotsInitialize(const char *configFileName,pSotsMsgHandler handler = NULL) ;

/*********************************************
Purpose: Terminate the interface
Parameters: none
Returns: 1 on success; other values indicate failure
**********************************************/
DECLSOTSAPI INT32 SotsTerminate() ;


/*********************************************
Purpose: Send an asynchronous message; the returned handle matches the callback handle
Parameters: const char *serviceName message service name
		const void* data outgoing message
		INT32 dataLen outgoing message length
		UINT32 flags: 0 normal, 1 no response, 4 guaranteed delivery, 5 guaranteed delivery without response (1 | 4)
Returns: ERROR_INVALID_SOTS_RPC_HANDLE on failure;
		otherwise returns the call handle, which is passed to the callback
**********************************************/
DECLSOTSAPI ULONG SotsAsynCall(const char *serviceName, 
						const void *data, INT32 dataLen, UINT32 flags) ;


/*********************************************
Purpose: Send a synchronous message
Parameters: const char *serviceName message service name
		const void* inData outgoing message
		INT32 inDataLen outgoing message length
		const void* outData response message
		INT32 inDataLen response message length
		UINT32 flags: 0 normal, 1 no response, 4 guaranteed delivery, 5 guaranteed delivery without response (1 | 4)
Returns: outData response length; nonnegative indicates success, other values indicate failure
**********************************************/
DECLSOTSAPI INT32 SotsCall(const char *serviceName, 
						const void *inData, INT32 inDataLen, 
						void *outData, INT32 outDataLen, UINT32 flags) ;


/*********************************************
Purpose: Send client-to-client messages without going through SERVICE.
Parameters: UINT32 gsId client GAMESERVER ID (configured by the server)
		const char *serviceName message service name
		const void* data outgoing message
		INT32 dataLen outgoing message length
		UINT32 flags: 0 normal, 1 no response, 4 guaranteed delivery, 5 guaranteed delivery without response (1 | 4)
Returns: 1 on success; other values indicate failure.
**********************************************/
DECLSOTSAPI INT32 SotsNotify(UINT32 gsId, const char *serviceName,const void* data, INT32 dataLen, UINT32 flags);


/*********************************************
Purpose: Obtain a unique string so clients use a consistent identifier
Parameters: char *orderId output string
		INT32 len length of the orderId string
Returns: 1 on success; other values indicate failure
**********************************************/
DECLSOTSAPI INT32 GetSotsUniqueId(char *orderId,INT32 len) ;


#ifdef __cplusplus
}
#endif

#endif

