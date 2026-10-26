#ifndef _MESSAGEHANDLER_RANKLIST_H__
#define _MESSAGEHANDLER_RANKLIST_H__

public:
	void Send_QueryRanklist(INT ranklistID, INT pageNum);

private:
	M_DECL_PARSE_FUN(m2c_query_ranklist);

#define M_INIT_MSGHANDLER_RANKLIST \
	MREG_PARSE_FUN(m2c_query_ranklist);\


#endif