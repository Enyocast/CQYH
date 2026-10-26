#ifndef __MESSAGE_HANDLER_JIGSAW_H__
#define __MESSAGE_HANDLER_JIGSAW_H__
public:
	void Send_JigsawAnswer(UINT8 byAns);
	M_DECL_PARSE_FUN(g2c_jigsaw);

private:

#define  M_INIT_MSGHANDLER_JIGSAW \
	MREG_PARSE_FUN(g2c_jigsaw); \

#endif