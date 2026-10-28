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

#define ERROR_INVALID_SOTS_RPC_HANDLE	-1			/// No free message-handling handle
#define ERROR_INVALID_SERVICE			-2   		/// The requested service is not enabled
#define ERROR_SOTS_API_NOT_INIT_FINISH  -3			/// The program has not finished starting
#define ERROR_INIT_CONFIG_FILE			-4   		/// Invalid initialization configuration file
#define ERROR_LEN_INFO				    -5  		/// Invalid length information
#define ERROR_DATA_INFO				    -6  		/// Invalid information
#define ERROR_OTHER_INFO				-999999  	/// Other error

#define SotsMSGVERSION            		2090312  		// Message version
#define SotsMSGMAXLENGTH            	1536  			// Maximum message length: 1024 + 512

#pragma pack (push,4)  /// Set 4-byte alignment

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
	int 	clientId;			/// Unique client ID (configured by the server)
	int 	gameId;			    /// Game ID
	int 	areaId;				/// Area ID
	int 	groupId;			/// Group ID
	int 	hostId;				/// Host ID
	char	localIp[16];		/// Local client IP address
	int 	localPort;			/// Local client port
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

#pragma pack (pop) /// Restore default alignment

#endif

