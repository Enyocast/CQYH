#ifndef _AWARD_DEF_H_
#define _AWARD_DEF_H_

enum EAeward_Action_Type
{
	eratInvalid = -1,

	eratAwardReq_Survey,			// 通过批次号领奖
	eratAwardReq_AwardNumber,		// 通过推广码领奖

	eratAwardAck,

	eratAwardTotal,
};

#endif // _AWARD_DEF_H_


