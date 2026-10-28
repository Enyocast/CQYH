#ifndef _AURA_DEF_H_
#define _AURA_DEF_H_

///@file aura_def.h
/// no lua package file
#define MAX_AURA_EX_EVT	(2)

///@enum AURA_CATEGORY
enum AURA_CATEGORY
{
	acInvalid = -1,		///< @line

	acNone,				///< @line
	acPositive,			///< @line
	acNegative,			///< @line

	acTotal				///< @line
};

///@enum AURA_EFFECT_TYPE
enum AURA_EFFECT_TYPE
{
	auetInvalid = -1,		///< @line

	auetNone,				///< @line
	auetType01,
	auetType02,
	auetType03,
	auetType04,
	auetType05,
	auetType06,
	auetType07,
	auetType08,
	auetType09,
	auetType10,
	auetType11,
	auetType12,
	auetType13,
	auetType14,
	auetType15,
	auetType16,
	auetType17,
	auetType18,
	auetType19,
	auetType20,
	auetType21,
	auetType22,
	auetType23,
	auetType24,

	auetTotal				///< @line
};

///@enum AURA_STACK_TYPE
enum AURA_STACK_TYPE
{
	austInvalid = -1,		///< @line

	austNone,				///< @line
	austSubstitute,			///< @line
	austStack,				///< @line
	austCoexist,			///< @line

	austTotal				///< @line
};

enum AURA_DISPLAY_GROUP
{
	adgInvalid = -1,

	adgBegin,
	adgGroupA = adgBegin,
	adgGroupB,
	adgGroupC,
	adgGroupD,
	adgGroupE,

	adgTotal,
};

enum AURA_RESIST_TYPE
{
	aurtNone = 0,

	aurtPoison,
	aurtDazzy,
	aurtFreeze,
	aurtBurn,
	aurtRepel,

	aurtTotal
};

#endif // _AURA_DEF_H__


