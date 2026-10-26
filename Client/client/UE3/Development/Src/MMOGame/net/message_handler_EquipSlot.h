#ifndef __MESSAGE_HANDLER_EQUIPSLOT_H__
#define __MESSAGE_HANDLER_EQUIPSLOT_H__

public:
	void Send_Refine( UINT8 refineSlot, UINT8 hasConsume, UINT8 consumeConID,  UINT8 consumeSlotID );


	M_DECL_PARSE_FUN(g2c_sync_refine);
	M_DECL_PARSE_FUN(g2c_refine);
//private:



#endif