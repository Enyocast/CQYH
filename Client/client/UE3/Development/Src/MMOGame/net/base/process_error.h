#ifndef _PROCESS_ERROR_H_
#define _PROCESS_ERROR_H_

#define PROCESS_ERROR(__condition__)								\
	do																\
	{																\
		if (!(__condition__))										\
		{															\
			goto Exit0;												\
		}															\
	} while (0)

#define PROCESS_SUCCESS(__condition__)								\
	do																\
	{																\
		if (__condition__)											\
		{															\
			goto Exit1;												\
		}															\
	} while (0)

#define LOG_PROCESS_ERROR(__condition__)							\
	do																\
	{																\
		if (!(__condition__))										\
		{															\
            warnf(NAME_Error, TEXT("LOG_PROCESS_ERROR(")TEXT(#__condition__)TEXT(") at line %d in function %s() file \"%s\""), \
                __LINE__, ANSI_TO_TCHAR(__FUNCTION__), ANSI_TO_TCHAR(__FILE__));                  \
				appDebugBreak(); \
			goto Exit0;												\
		}															\
	} while (0)

#define LOG_CHECK_ERROR(__condition__)								\
	do																\
	{																\
		if (!(__condition__))										\
		{															\
        warnf(NAME_Error, TEXT("LOG_CHECK_ERROR(")TEXT(#__condition__)TEXT(") at line %d in function %s() file \"%s\""), \
                __LINE__, ANSI_TO_TCHAR(__FUNCTION__), ANSI_TO_TCHAR(__FILE__));                  \
		}															\
	} while (0)

#define PROCESS_ERROR_RET_CODE(__condition__, __result__)			\
	do																\
	{																\
		if (!(__condition__))										\
		{															\
			nResult = __result__;									\
			goto Exit0;												\
		}															\
	} while (0)

#define LOG_PROCESS_ERROR_RET_CODE(__condition__, __result__)		\
	do																\
	{																\
		if (!(__condition__))										\
		{															\
			nResult = __result__;									\
            warnf(NAME_Error, TEXT("LOG_PROCESS_ERROR_RET_CODE(")TEXT(#__condition__)TEXT(") at line %d in function %s() file \"%s\""), \
                __LINE__, ANSI_TO_TCHAR(__FUNCTION__), ANSI_TO_TCHAR(__FILE__));                  \
			goto Exit0;												\
		}															\
	} while (0)

		

#define ASSERT_CHECK_ERROR_0_RETURN(__condition__)								\
	do																\
	{																\
	if (!(__condition__))										\
		{															\
		warnf(NAME_Error, TEXT("LOG_CHECK_ERROR(")TEXT(#__condition__)TEXT(") at line %d in function %s() file \"%s\""), \
		__LINE__, ANSI_TO_TCHAR(__FUNCTION__), ANSI_TO_TCHAR(__FILE__));                  \
		check(__condition__);	\
		return 0;\
		}															\
	} while (0)

#define ASSERT_CHECK_ERROR_RETURN(__condition__)								\
	do																\
	{																\
	if (!(__condition__))										\
		{															\
		check(__condition__);	\
		warnf(NAME_Error, TEXT("LOG_CHECK_ERROR(")TEXT(#__condition__)TEXT(") at line %d in function %s() file \"%s\""), \
		__LINE__, ANSI_TO_TCHAR(__FUNCTION__), ANSI_TO_TCHAR(__FILE__));                  \
		return ;\
		}															\
	} while (0)


#define SAFE_DELETE(__pointer__)				\
	do											\
	{											\
		if (__pointer__)						\
		{										\
			delete (__pointer__);				\
			(__pointer__) = NULL;				\
		}										\
	} while (0);

#define SAFE_DELETE_ARRAY(__pointer__)			\
	do											\
	{											\
		if (__pointer__)						\
		{										\
			delete [] (__pointer__);			\
			(__pointer__) = NULL;				\
		}										\
	} while (0);


#ifndef ASSERT
    #define ASSERT LOG_CHECK_ERROR
#endif  // ASSERT

#endif	// _PROCESS_ERROR_H_

