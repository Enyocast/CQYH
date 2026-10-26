#ifndef _H_GUILD_DB_DEF_H_
#define _H_GUILD_DB_DEF_H_

#define GUILD_DB_CURRENT_VERSION    (5)

#if defined(WIN32) | defined(WIN64)
    #pragma warning(disable:4200)
#endif  // WIN32

#include "guild_db_def_v_1.h"
#include "guild_db_def_v_2.h"
#include "guild_db_def_v_3.h"
#include "guild_db_def_v_4.h"
#include "guild_db_def_v_5.h"

using namespace GUILD_DEF_VER_5;

#endif //_H_GUILD_DB_DEF_H_
