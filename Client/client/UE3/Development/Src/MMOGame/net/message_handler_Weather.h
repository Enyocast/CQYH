#ifndef __MESSAGE_HANDLER_WEATHER_H__
#define __MESSAGE_HANDLER_WEATHER_H__

M_DECL_PARSE_FUN(g2c_update_weather);

#define M_INIT_MSGHANDLER_WEATHER \
	MREG_PARSE_FUN(g2c_update_weather);

#endif