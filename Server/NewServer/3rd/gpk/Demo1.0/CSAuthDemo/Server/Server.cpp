#ifndef _WIN32_WINNT		
#define _WIN32_WINNT 0x0501	
#endif	

#include"winsock2.h"  

#include<stdio.h>  
#include<stdlib.h>  


#include "GPKitSvr.h"

#pragma comment(lib,"GPKitSvr.lib")
#pragma comment(lib,"ws2_32.lib")

using namespace SGPK;

IGPKSvrDynCode *pSvrDynCode = NULL;

#define   DEFAULT_PORT     27015 
#define   DEFAULT_COUNT   25  
#define   DEFAULT_BUFFER   512   



int   iPort   =   DEFAULT_PORT   ;    
BOOL   bInterface   =   FALSE,   
bRecvOnly   =   FALSE;      
char   szAddress[128];              


struct myListenSocket
{
	char clientIp[255];
	int port;
	SOCKET conSocket;
	IGPKCSAuth *p_gpkAuthObject;
};

BOOLEAN
SendDynCodeToClient(
	IN myListenSocket *sock
	)
{
	int bytesSent;

	const unsigned char *pCode = NULL;
	
	int nCodeLen = sock->p_gpkAuthObject->GetCSAuthDynCode(&pCode);
	
	if(nCodeLen < 0)
		return FALSE;

	bytesSent = send( sock->conSocket, (const char*)pCode, nCodeLen, 0 );
	while (bytesSent != SOCKET_ERROR && bytesSent < nCodeLen)
	{
		Sleep(20);
		nCodeLen -= bytesSent;
		bytesSent = send( sock->conSocket, (const char*)pCode + bytesSent, nCodeLen, 0);
	}

	if (bytesSent == SOCKET_ERROR)
	{
		printf("Send DynCode to Client Failed.\n");
		return FALSE;
	}

	return TRUE;
}
 
DWORD WINAPI ClientThread(LPVOID lpParam)  
{  
	myListenSocket *sock	= (myListenSocket*)lpParam;  
	char	szBuff[DEFAULT_BUFFER];  
	int		ret;
	int		CheckAuthReplyRet;

	SendDynCodeToClient(sock);

	Sleep(200);
	while(1)  
	{  
		const unsigned char *p = NULL;
		int len = sock->p_gpkAuthObject->GetAuthData(&p,NULL,NULL);

		send(sock->conSocket,(const char *)p,len,0);
		
		ret = recv(sock->conSocket,szBuff,DEFAULT_BUFFER,0);  
		if ( ret <= 0 || ret == WSAECONNRESET )
		{
			printf( "[%x]Connection Closed.\n",sock);
			closesocket(sock->conSocket);
			break;
		}

		CheckAuthReplyRet = sock->p_gpkAuthObject->CheckAuthReply(&p,(unsigned char*)szBuff,ret);

		if( CheckAuthReplyRet != CHECK_SUCCEED )
		{
			//log hack
			if( CheckAuthReplyRet == CHECK_FIND_CHEAT_NEED_KICK )
			{
				PCHEAT_INFO CheatInfo = (PCHEAT_INFO)p;
				if( CheatInfo->CHEAT_INFO_TYPE == TYPE_IDS )
				{
					printf("[%x kicked]CheckAuthReply CHECK_FIND_CHEAT_NEED_KICK: (%08X ,%08X ,%08X ,%08X ,%08X)\n",
						sock,
						CheatInfo->CHEATTYPE.CHEAT_IDS[0],
						CheatInfo->CHEATTYPE.CHEAT_IDS[1],
						CheatInfo->CHEATTYPE.CHEAT_IDS[2],
						CheatInfo->CHEATTYPE.CHEAT_IDS[3],
						CheatInfo->CHEATTYPE.CHEAT_IDS[4]);
				}
				else if( CheatInfo->CHEAT_INFO_TYPE == TYPE_DETAIL )
				{
					printf("[%x kicked]CheckAuthReply CHECK_FIND_CHEAT_NEED_KICK: %08X-%s\n",
						sock,
						CheatInfo->CHEATTYPE.CHEAT_DETAIL.CHEAT_ID,
						CheatInfo->CHEATTYPE.CHEAT_DETAIL.DetailString);
				}
				closesocket(sock->conSocket);
			}
			else if( CheckAuthReplyRet == CHECK_FIND_CHEAT_ONLY_LOG )
			{
				PCHEAT_INFO CheatInfo = (PCHEAT_INFO)p;
				if( CheatInfo->CHEAT_INFO_TYPE == TYPE_IDS )
				{
					printf("[%x nokick]CheckAuthReply CHECK_FIND_CHEAT_ONLY_LOG: (%08X ,%08X ,%08X ,%08X ,%08X)\n",
						sock,
						CheatInfo->CHEATTYPE.CHEAT_IDS[0],
						CheatInfo->CHEATTYPE.CHEAT_IDS[1],
						CheatInfo->CHEATTYPE.CHEAT_IDS[2],
						CheatInfo->CHEATTYPE.CHEAT_IDS[3],
						CheatInfo->CHEATTYPE.CHEAT_IDS[4]);
				}
				else if( CheatInfo->CHEAT_INFO_TYPE == TYPE_DETAIL )
				{
					printf("[%x nokick]CheckAuthReply CHECK_FIND_CHEAT_ONLY_LOG: %08X-%s\n",
						sock,
						CheatInfo->CHEATTYPE.CHEAT_DETAIL.CHEAT_ID,
						CheatInfo->CHEATTYPE.CHEAT_DETAIL.DetailString);
				}
			}
			else
			{
				printf("[%x kicked]CheckAuthReply result: %d\n",sock,CheckAuthReplyRet);
				closesocket(sock->conSocket);
			}
		}
		else
		{
			printf("[%x]CheckAuthReply ok!!!\n",sock);
		}

		Sleep(5000);   //根据需要设置检查间隔，一般设置为3-5分钟
	}  

	sock->p_gpkAuthObject->Release();
	delete sock;
	return 0;  
}

const char * GetRootPath(void)
{
	static char szPath[MAX_PATH];
	static bool bFirstTime = true;

	if(bFirstTime)
	{
		bFirstTime = false;
		GetModuleFileName(NULL, szPath, sizeof(szPath));
		char *p = strrchr(szPath, '\\');
		*p = '\0';
	}

	return szPath;
}

BOOLEAN
InitGPKServer(
	VOID
	)
{
	char szSvrDir[MAX_PATH];
	char szCltDir[MAX_PATH];

	pSvrDynCode = GPKCreateSvrDynCode();

	if(NULL == pSvrDynCode)
	{
		printf("Create SvrDynCode component failed\n");
		return FALSE;
	}

#ifdef BIT64
	sprintf(szSvrDir, "%s\\DynCodeBin\\Server64", GetRootPath());
#else
	sprintf(szSvrDir, "%s\\DynCodeBin\\Server", GetRootPath());
#endif

	sprintf(szCltDir, "%s\\DynCodeBin\\Client", GetRootPath());

	int nBinCount = pSvrDynCode->LoadBinary(szSvrDir, szCltDir);
	printf("Load Binary: %d binary are loaded\n", nBinCount);

	if(0 == nBinCount)
	{
		printf("Load DynCode failed.\n");
		return FALSE;
	}

	return TRUE;
}
 
int main(int argc,char **argv)  
{  
	WSADATA	wsd;  
	SOCKET	sListen,sClient;  
	int		iAddrSize;  
	HANDLE	hThread;  
	DWORD	dwThreadId;  
	struct sockaddr_in	local,client;   


	if ( !InitGPKServer() )
		return 1;	

	if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)  
	{  
		printf("Failed to load Winsock!\n");  
		return 1;  
	}  
	
	sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);  
	if(sListen == SOCKET_ERROR)  
	{  
		printf("socket() failed:%d\n",WSAGetLastError());  
		return 1;  
	}  
	
	local.sin_addr.s_addr = htonl(INADDR_ANY);  
	local.sin_family = AF_INET;  
	local.sin_port = htons(iPort);  

	if(bind(sListen,(struct sockaddr *)&local,sizeof(local)) == SOCKET_ERROR)  
	{  
		printf("bind() failed:%d\n",WSAGetLastError());      
		return 1;  
	}  
	listen(sListen,8);  

	while(1)  
	{  
		iAddrSize = sizeof(client);  
		sClient = accept(sListen,(struct sockaddr *)&client,&iAddrSize);  
		if(sClient == INVALID_SOCKET)  
		{  
			break;  
		}  

		struct myListenSocket* mls=new myListenSocket();
		strcpy(mls->clientIp,inet_ntoa(client.sin_addr));
		mls->port=ntohs(client.sin_port);
		mls->conSocket=sClient;
		mls->p_gpkAuthObject = pSvrDynCode->AllocAuthObject();;
		hThread = CreateThread(NULL,0,ClientThread,(LPVOID)mls,0,&dwThreadId);  
		if(hThread == NULL)  
		{  
			printf("CreateThread() failed:%d\n",WSAGetLastError());  
			break;  
		}  
		CloseHandle(hThread);  
	}  
	closesocket(sListen);  
	WSACleanup();  
	return 0;  
}   
