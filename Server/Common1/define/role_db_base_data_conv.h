#ifndef _ROLE_DB_BASE_DATA_CONV_H_
#define _ROLE_DB_BASE_DATA_CONV_H_

#include "role_db_def.h"

BOOL ConvertToBaseDataCurrentVersion(ROLE_DB_BASE_DATA* base_data, const char* buff, UINT32 buflen);

#endif // _ROLE_DB_BASE_DATA_CONV_H_
