#include "stdafx.h"
#include "message_handler.h"
#include "MMOFacade.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOJigsawManager.h"


void CMessageHandler::Send_JigsawAnswer(UINT8 byAns)
{
	C2G_JIGSAW_ANSWER msg;
	msg.wMsg = c2g_jigsaw_answer;

	msg.byIndex = byAns;

	_Send(&msg,sizeof(msg));
}

void CMessageHandler::Parse_g2c_jigsaw(const char* buf, UINT32 size)
{
	G2C_JIGSAW* msg = (G2C_JIGSAW*)buf;
	MMOJigsawManager::getSingleton().CopyTargetTextureData(msg->cImageData);
	INT i;
	for (i=0;i<JIGSAW_ANSWER_COUNT;i++)
	{
		MMOJigsawManager::getSingleton().CopyAnswerTextureData(msg->AnswerData[i].cAnswerData, i );
	}

	MMOJigsawManager::getSingleton().SetDeadLineTime(MMOFacade::getSingleton().GetRealClientUTCTime() + msg->dwTimeoutInterval);

	MMOJigsawManager::getSingleton().SetBlockOffset(msg->byBlockX,msg->byBlockY);

	MMOJigsawManager::getSingleton().OnRecieveJigsawMsg();
}
