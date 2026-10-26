// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef stdafx_h__
#define stdafx_h__

#include <winsock2.h>
#include <windows.h>
#include "std_type.h"

#include "baselib/asm.h"
#define _SCL_SECURE_INVALID_PARAMETER(expr) INT3()

#include <time.h>
#include <map>
#include <list>
#include <set>

#include "process_error.h"
#include "string_ex.h"
#include "linux_compatible.h"

#include "common.h"

// TODO: reference additional headers your program requires here

#endif // stdafx_h__