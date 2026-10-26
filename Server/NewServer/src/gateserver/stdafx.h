#ifndef _STD_AFX_H_
#define _STD_AFX_H_

#include <winsock2.h>
#include <windows.h>
#include "std_type.h"


extern char* g_szS2CMessageName[];	//  "external_message_size.cpp"
extern char* g_szC2SMessageName[];	//  "external_message_size.cpp"

#include "baselib/asm.h"
#define _SCL_SECURE_INVALID_PARAMETER(expr) INT3()
#define _HAS_EXCEPTIONS 0
#include "process_error.h"
#include "string_ex.h"

#include "linux_compatible.h"

#endif  // _STD_AFX_H_
