#ifndef _AWARD_DEF_H_
#define _AWARD_DEF_H_

enum EAeward_Action_Type
{
	eratInvalid = -1,

	eratAwardReq_Survey,			// Claim reward using batch number
	eratAwardReq_AwardNumber,		// Claim reward using promotional code

	eratAwardAck,

	eratAwardTotal,
};

#endif // _AWARD_DEF_H_


