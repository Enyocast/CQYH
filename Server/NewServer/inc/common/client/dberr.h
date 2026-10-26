// this headfile is generated automatically by tools, please do not manually modify.
#ifndef __DBERR_H__
#define __DBERR_H__

#include <sdtype.h>
#include <sdstring.h>

using namespace SGDP;

// @brief
// You may see this phenomenon :
// variables with "STR_" as their prifix, maybe have a suffix
// the suffix means which format output symbols have appeared in function like printf
// Sample :  "%s" turns to be "_S"
namespace  ERR_CREATEROLE_DB
{
    extern const INT32 ID_NOERROR/* = 0*/;
    extern const TCHAR* STR_NOERROR/* = _SDTSource2T("GBK", "操作成功")*/;

    extern const INT32 ID_TOOMUCHROLE/* = 1*/;
    extern const TCHAR* STR_TOOMUCHROLE/* = _SDTSource2T("GBK", "角色创建过多")*/;

    extern const INT32 ID_PARAMERROR/* = 2*/;
    extern const TCHAR* STR_PARAMERROR/* = _SDTSource2T("GBK", "参数不正确")*/;

    extern const INT32 ID_UNKNOWERROR/* = 3*/;
    extern const TCHAR* STR_UNKNOWERROR/* = _SDTSource2T("GBK", "角色名重复或数据库错误")*/;
}

#endif
