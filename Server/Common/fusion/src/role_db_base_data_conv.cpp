#include "stdafx.h"
#include "role_db_base_data_conv.h"
#include "read_data_helper.h"
#include "game_world_config.h"
#include "server_config.h"

BOOL ConvertToBaseDataCurrentVersion(ROLE_DB_BASE_DATA* base_data, const char* buff, UINT32 buflen)
{
    memset(base_data, 0, sizeof(ROLE_DB_BASE_DATA));

    UINT8 base_data_version = *(UINT8*)buff;

    switch (base_data_version)
    {
    case 1:
        LOG_PROCESS_ERROR(buflen == sizeof(ROLE_DB_DEF_V_1::ROLE_DB_BASE_DATA));
        memcpy(base_data, buff, sizeof(ROLE_DB_DEF_V_1::ROLE_DB_BASE_DATA));
        break;
    default:
        LOG_PROCESS_ERROR(FALSE);
    }

    return TRUE;

Exit0:
    return FALSE;
}