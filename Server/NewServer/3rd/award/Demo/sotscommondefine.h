/*
* Copyright (c) 2009, Shanghai Shanda Network SDG Accounting Department
* All rights reserved.
* 
* File name: SOTSCOMMONDEFINE.h
* Summary: Defines common SOTS information
* 
* Current version: 1.0
* Changes:
* Author:xhq
* Completed: March 10, 2009
*/

#ifndef SOTSCOMMONDEFINE_H
#define SOTSCOMMONDEFINE_H

#define SOTS_API_OK     				1			    /// Success

#define ERROR_INVALID_SOTS_RPC_HANDLE	0xFFFFFFFF		/// No free message-handling handle
#define ERROR_INVALID_SERVICE			0xFFFFFFFE   	/// The requested service is not enabled
#define ERROR_SOTS_API_NOT_INIT_FINISH  0xFFFFFFFD		/// The program has not finished starting
#define ERROR_INIT_CONFIG_FILE			-100002			/// Invalid initialization configuration file
#define ERROR_NOT_EXIT_SOTS_CLT_INFO	-100003			/// Invalid configuration information
#define ERROR_LEN_INFO				    -100004			/// Invalid length information
#define ERROR_OTHER_INFO				-199999			/// Other error

#define SotsMSGVERSION            		2090312  		// Message version
typedef struct
{
    int  msgLen      ;  /// Total message length in bytes, including header and body
    int  msgType     ;  /// Message type, distinguishing request and response types for the same service
	char msgId[32+1] ;  /// Message serial number supplied by the initiator; the response uses the request msgId
	int  callTime    ;  /// Send time
    int  version     ;  /// Message protocol version
}SotsMsgHeadDef;

#define SVCSOTSSYSTEM "SVCSOTSSYSTEM"
#define TYPESOTSCLIENTINFO            0x00000001   /// Client configuration information message

/*********************************************
Purpose: Record client attributes
	  Client IP, SERVICEID, AREAID, GROUPID, supported services, and related information
**********************************************/
typedef struct
{
	UINT32	clientId;			/// Unique client ID (configured by the server)
	UINT32	gameId;			    /// Game ID
	UINT32	areaId;				/// Area ID
	UINT32	groupId;			/// Group ID
	UINT32	hostId;				/// Host ID
	char	localIp[16];		/// Local client IP address
	UINT32	localPort;			/// Local client port
	char	serviceInfo[512];	/// Services handled, e.g. Author;Account;ServiceSendItem
	char    apiVersion[30];     /// API version
	int     bodyLen;            /// Message body length (reserved)
	char	*bodyInfo;  	    /// Message body pointer (reserved)
}SOTSCLIENTINFO;

typedef struct
{
	SotsMsgHeadDef msgHead;
	SOTSCLIENTINFO msgBody;
}SotsClientInfoDef;

#endif

