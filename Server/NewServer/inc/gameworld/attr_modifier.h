#ifndef _ATTR_MODIFIER_H_
#define _ATTR_MODIFIER_H_

#include "modifier_def.h"

class CCharacter;

typedef INT32 (*ModifierFuncImpl)(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* poExParam);

struct ModifierFunc
{
	ModifierFuncImpl	ImplFunc;
	BOOL				Rollback;
};

ModifierFunc* GetModifierFunction(INT32 eFuncTargetType, INT32 nKey);

#endif	// _ATTR_MODIFIER_H_