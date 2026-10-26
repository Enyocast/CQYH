#ifndef __MESSAGE_HANDLER_H5_H__
#define __MESSAGE_HANDLER_H5_H__

public:
	M_DECL_PARSE_FUN(m2c_h5_url);

private:

#define M_INIT_MSGHANDLER_H5 \
	MREG_PARSE_FUN(m2c_h5_url);\

#endif