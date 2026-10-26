#ifndef _STD_AFX_H_
#define _STD_AFX_H_

#include <windows.h>

#include "std_type.h"
#include "baselib/asm.h"
#define _SCL_SECURE_INVALID_PARAMETER(expr) INT3()
#define _HAS_EXCEPTIONS 0
#include <stdio.h>

#include "process_error.h"

#endif  // _STD_AFX_H_