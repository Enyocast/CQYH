1. Programming

1、 Include these three files when building
	sotsapi.h Header for client development
    sotscommondefine.h Header containing common client information
	sdtype.h  Header defining character types
	
2、For client development, consult the Unified Message Platform client C/C++ interface document (“统一消息平台_客户端C-C++调用接口.doc”).
	Programming sequence:
	First call SotsInitialize to connect to the server.
	Then typically call SotsAsynCall to send the reward claim asynchronously (see the item push and reward claim protocol document “道具推送与领奖消息协议定义_V1.2_44.doc”).
	Receive responses through the registered pSotsMsgHandler callback.
	Call SotsTerminate when the program exits.

2. Running the program (dynamic loading)

1、Place RpcClt.dll, sotsapi.dll and ToolsGetConf.exe in the runtime directory.

2、Place the sotsconf configuration directory in the parent of the runtime directory.

3. Change history

20090617 Fixed slow connections
20090806 Added deletion of logs older than two months
20090924 Upgraded to version 2.0, distinct from the old accounting system (added svcname to the callback)
20091210 Fixed handling when the runtime and storage directories differ
20091211 Aligned GD message bodies to 1 byte and other structures to 4 bytes (item delivery and reward claim interfaces remain 4-byte aligned)
20091228 Fixed one-month log retention and logging of log-level changes
20100309 Changed guaranteed-delivery and send logging to debug level
20100325 Changed guaranteed-delivery processing to scan every 10 minutes
20101028 1、Changed the client connection timeout from 5s to 60s,2、Changed GetSotsUniqueId; orderid is at most 32 characters
20110310 1、Replaced sprintf with snprintf ,2、Fixed a client exception caused by network errors,3、Added exception handling at thread startup

