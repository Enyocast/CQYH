#include <WinSock2.h>
#include "stdio.h"
#include "GPKitClt.h"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"GPKitClt.lib")
int port=27015;
char szIp[255]="127.0.0.1";

using namespace SGPK;

PUCHAR	DynCode = NULL;
IGPKCltDynCode *pCltDynCode = NULL;

BOOLEAN
RecvDynCodeFromServer(
	IN SOCKET ServerSocket
	)
{
	int bytesRecv;

	bytesRecv = recv(ServerSocket, (char *)DynCode, 32*1024, 0);
	if (bytesRecv > 0)
	{
		pCltDynCode->SetDynCode(DynCode, bytesRecv);

		return TRUE;
	}

	return FALSE;
}

void GPK_API SendToServer(void *socket,unsigned char *lpData,unsigned long nLen)
{
	send(*(SOCKET*)socket,(char*)lpData,nLen,0);
}
int main()
{
	SOCKET client;
	WSADATA wsa;
	sockaddr_in addr;
	int ret;
	char	szBuff[512];
	
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0)
		printf("WSAStartup error!\n");

	pCltDynCode = GPKStart("http://127.0.0.1/gpk/", "gpkdemo");
	if(pCltDynCode == NULL)
	{
		printf("Create IGPKCltDynCode failed!\n");
		return 0;
	};

	client=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(szIp);
	if(connect(client,(struct sockaddr *)&addr,sizeof(addr))!=0)
		printf("connect error\n");
	
	DynCode = (PUCHAR)VirtualAlloc(NULL, 32*1024, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	if (!RecvDynCodeFromServer(client))
		goto __end;
	while(1)
	{
		ret = recv(client,szBuff,512,0); 
		printf("recv len: %d\n",ret);
		ret = pCltDynCode->ProcessAuth(NULL,NULL,(unsigned char *)szBuff,ret);
		ret = send(client,szBuff,ret,0);
		printf("send len: %d\n",ret);

		if ( ret <= 0 || ret == WSAECONNRESET )
		{
			printf( "Connection Closed.\n");
			closesocket(client);
			goto __end;
		}
	}

__end:

	if (pCltDynCode != NULL)
		pCltDynCode->Release();

	WSACleanup();

	return 0;
}