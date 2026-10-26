#ifndef _READ_DATA_HELPER_H_
#define _READ_DATA_HELPER_H_

#include "lua_script.h"
#include "scene_def.h"

extern CLuaScript* g_pReadDataScript;
BOOL g_InitReadDataScript(const char* pcszConfigPath, const char* pcszScriptName);
BOOL g_UnInitReadDataScript(void);

#define ROUND_UP_FRM(__time__, __fps__) (((__time__) + (__fps__) - 1)/(__fps__))

// to unit: point, from unit: cm
#define CONVERT_LENGTH(__length__)  ((__length__) * POINT_PER_CM)
// to unit: point/ms, from unit: cm/s
#define CONVERT_SPEED(__speed__)    ((__speed__) * GAME_FPS / 1000)
// to unit: frame, from unit: ms
#define CONVERT_TIME(__time__)      ((INT32)(((INT64)(__time__)) * GAME_FPS / 1000))
// to unit: 1 / max_direction_count, from unit: degree
#define CONVERT_ANGLE(__angle__)    ((__angle__) * MAX_DIRECTION_COUNT / 360)

#define READ_START()                                                            \
    INT32 nRetCode = 0;                                                         \
    INT32 nValue = 0;                                                           \
    char szExprValue[256];

#define READ_INT(__field__, __var__)                                            \
    nRetCode = pTabConfig->ReadData(__field__, nRow, nValue);             \
    LOG_PROCESS_ERROR(nRetCode && __field__);                                   \
    pData->__var__ = nValue;

#define READ_STR(__field__, __var__)                                                                    \
    nRetCode = pTabConfig->ReadData(__field__, nRow, pData->__var__, sizeof(pData->__var__));     \
    LOG_PROCESS_ERROR(nRetCode && __field__);

#define READ_LENGTH(__field__, __var__)                                         \
    nRetCode = pTabConfig->ReadData(__field__, nRow, pData->__var__);     \
    LOG_PROCESS_ERROR(nRetCode && __field__);                                   \
    pData->__var__ = CONVERT_LENGTH(pData->__var__);

#define READ_TIME(__field__, __var__)                                           \
    nRetCode = pTabConfig->ReadData(__field__, nRow, pData->__var__);     \
    LOG_PROCESS_ERROR(nRetCode && __field__);                                   \
	if(pData->__var__ > 0 && pData->__var__ < 1000/GAME_FPS)					\
		pData->__var__ = 1000/GAME_FPS;											\
    pData->__var__ = CONVERT_TIME(pData->__var__);

#define READ_SPEED(__field__, __var__)                                          \
    nRetCode = pTabConfig->ReadData(__field__, nRow, pData->__var__);     \
    LOG_PROCESS_ERROR(nRetCode && __field__);                                   \
    pData->__var__ = CONVERT_SPEED(pData->__var__);

#define READ_ANGLE(__field__, __var__)                                          \
    nRetCode = pTabConfig->ReadData(__field__, nRow, pData->__var__);     \
    LOG_PROCESS_ERROR(nRetCode && __field__);                                   \
    pData->__var__ = CONVERT_ANGLE(pData->__var__);

#define READ_INT_EXPR(__field__, __var__)                                                                   \
    nRetCode = pTabConfig->ReadData(__field__, nRow, szExprValue, sizeof(szExprValue));						\
    LOG_PROCESS_ERROR(nRetCode && __field__);                                                               \
    if ( szExprValue[0] != '\0' ){                                                                          \
    	nRetCode = g_pReadDataScript->CallFunction("read_int_expr", "s:d", szExprValue, &(pData->__var__)); \
        LOG_PROCESS_ERROR(nRetCode);                                                                 	    \
    }else{                                                                                                  \
        (pData->__var__) = 0;                                                                               \
    }   

#define READ_BIT_MASK(__field__, __var__)                                                                   \
    nRetCode = pTabConfig->ReadData(__field__, nRow, szExprValue, sizeof(szExprValue));						\
    LOG_PROCESS_ERROR(nRetCode && __field__);                                                               \
    if ( szExprValue[0] != '\0' ){                                                                          \
    	nRetCode = g_pReadDataScript->CallFunction("read_bit_mask", "s:d", szExprValue, &(pData->__var__)); \
        LOG_PROCESS_ERROR(nRetCode);                                                                 	    \
    }else{                                                                                                  \
        (pData->__var__) = 0;                                                                               \
    }   

#define READ_QUEST_VAR(__field_type__, __field_index__, __var__)														\
	READ_INT_EXPR(__field_type__, __var__)																				\
	nRetCode = pTabConfig->ReadData(__field_index__, nRow, nValue);												\
	LOG_PROCESS_ERROR(nRetCode);																						\
	nRetCode = g_pReadDataScript->CallFunction("read_quest_var", "dd:d", pData->__var__, nValue, &(pData->__var__));	\
	LOG_PROCESS_ERROR(nRetCode);

#define READ_END(__key__)                                       \
    rnID = pData->__key__;                                      \
    return TRUE;                                                \
Exit0:                                                          \
    rnID = pData->__key__;                                      \
    return FALSE;

extern void g_AppendErrorMsg(const char* pcszErrorMessage, ...);


#endif  // _READ_DATA_HELPER_H_
