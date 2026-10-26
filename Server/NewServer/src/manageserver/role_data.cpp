#include "stdafx.h"
#include "role_data.h"

BOOL MS_ROLE_DATA::LoadBaseData(ROLE_DB_BASE_DATA* base_data)
{
    dwRoleID = base_data->dwRoleID;
    strxcpy(szRoleName, base_data->szRoleName, ROLE_NAME_LEN);
    strxcpy(szUserName, base_data->szUserName, USER_NAME_LEN);
    byLevel = base_data->byLevel;
    bySex = base_data->bySex;
    byClass = base_data->byClass;

    dwTeamID = 0;
    pSellingAuction = NULL;
    pBuyingAuction = NULL;
    eAuctionQueryStatus = MS_ROLE_DATA::eqsFree;

    dwGuildID = 0;
    dwJoinGuildCD = 0;
    byApplicationCount = 0;

    return TRUE;
}
