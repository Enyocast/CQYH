#ifndef _FORCE_TRY_H_
#define _FORCE_TRY_H_

#if SHIPPING_PC_GAME// !defined(_DEBUG) || 0

#	if _WINDOWS
#		include "MinWindows.h"
#	endif
extern INT CreateMiniDump( LPEXCEPTION_POINTERS ExceptionInfo );

#	define M_USE_FORCE_TRY 1
#else
#	define M_USE_FORCE_TRY 0
#endif



#	if M_USE_FORCE_TRY
#		define M_FORCE_TRY_BEGIN __try {
#		define M_FORCE_TRY_END(msg) }__except(CreateMiniDump( GetExceptionInformation() ), EXCEPTION_EXECUTE_HANDLER) \
{ \
	SET_WARN_COLOR(COLOR_PURPLE); \
	warnf(NAME_Log, TEXT("[TRY] - %s"), TEXT(msg)); \
	CLEAR_WARN_COLOR(); \
}
//appSubmitErrorReport( TEXT(msg), EErrorReportMode::Unattended );
#	else
#		define M_FORCE_TRY_BEGIN
#		define M_FORCE_TRY_END(msg)
#	endif

#endif