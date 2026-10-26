#include "stdafx.h"
#include "message_handler.h"
#include "MMOQuestManager.h"
#include "MMOFacade.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOWeatherManager.h"

using namespace ExternalMessage;

void CMessageHandler::Parse_g2c_update_weather(const char* buf, UINT32 size)
{
	G2C_UPDATE_WEATHER* msg = (G2C_UPDATE_WEATHER*)buf;
	MMOWeatherManager::getSingleton().StartWeather(msg->byWeather);
}