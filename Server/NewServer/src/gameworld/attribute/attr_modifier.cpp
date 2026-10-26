#include "stdafx.h"
#include "attr_modifier.h"
#include "char_modifier.h"
#include "bullet_modifier.h"
#include "missile_modifier.h"
#include "attribute_def.h"

extern ModifierFunc g_CharModifier[];
extern ModifierFunc g_BulletModifier[];
extern ModifierFunc g_MissileModifier[];

ModifierFunc* g_GlobalFuncs[mttTotal] =
{
	g_CharModifier,
	g_BulletModifier,//g_BulletModifier,
	g_MissileModifier,
};

INT32 g_FuncSize[mttTotal] =
{
	cmiCount,
	bmiCount,
	mmiCount,
};

ModifierFunc* GetModifierFunction(INT32 eFuncTargetType, INT32 nKey)
{
	LOG_PROCESS_ERROR(eFuncTargetType > mttInvalid && eFuncTargetType < mttTotal);

	LOG_PROCESS_ERROR(nKey < g_FuncSize[eFuncTargetType]);

	return &g_GlobalFuncs[eFuncTargetType][nKey];

Exit0:
	return NULL;

}
