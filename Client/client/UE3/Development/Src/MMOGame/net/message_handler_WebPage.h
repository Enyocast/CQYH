#ifndef __MESSAGE_HANDLER_WEBPAGE_H__
#define __MESSAGE_HANDLER_WEBPAGE_H__

public:
	void Send_WebSurveyPageAck();
private:

	M_DECL_PARSE_FUN( g2c_query_survey_path);

#define M_INIT_MSGHANDLER_WEBPAGE  \
    MREG_PARSE_FUN( g2c_query_survey_path);

#endif