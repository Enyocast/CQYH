#ifndef __MESSAGE_HANDLER_EQUIPDECOMPOSE_H__
#define __MESSAGE_HANDLER_EQUIPDECOMPOSE_H__

public:
	void Send_Decompose(UINT8 byConSlot, UINT8 byItemSlot);
	void Send_Compose(UINT32 iFomulaId);

	M_DECL_PARSE_FUN(g2c_decompose);
	M_DECL_PARSE_FUN(g2c_compose);
#endif