/********************************************************************
	created:	26:4:2013   10:38
	file:		guild_storage.h
	author:		Allan Tao
	
	purpose:	∞Ô≈…≤÷ø‚
*********************************************************************/

#ifndef _H_MS_GUILD_STORAGE_H_
#define _H_MS_GUILD_STORAGE_H_

#include <map>
#include <set>

#include "base_list.h"
#include "guild_def.h"
#include "../gameworld/item.h"

#define MAX_ITEM_CONTAINER_TAG (6)

enum EN_STORAGE_ITEM_FLAG
{
    EN_STORAGE_NONE         = 0,
    EN_STORAGE_ITEM_VALID   = 1 << 0,
    EN_STORAGE_ITEM_LOCK    = 1 << 1,
};

struct MS_ROLE_DATA;
struct EVENT_DATA;
class CMsGuild;
struct STORAGE_EVENT_DATA;

struct GUILD_STORAGE_ITEM_DATA 
{
    UINT8       byConSlot;
    UINT8       byItemSlot;
    UINT8       byItemSize;
    char        szItemBuffer[GUILD_MAX_ITEM_BUFFER_LENGTH];
};

class CMsGuildStorage
{
public:
    CMsGuildStorage();
    ~CMsGuildStorage();

    BOOL        Init(CMsGuild *pMsGuild);
    BOOL        UnInit();

    INT32       PrePushItem(INT32 nConSlot, INT32 nItemSlot);
    INT32       UnPrePushItem(INT32 nConSlot, INT32 nItemSlot);
    INT32       PushItem(const MS_ROLE_DATA *pRoleData, INT32 nConSlot, INT32 nItemSlot, INT32 nBufferSize, const char *pBuffer);

    INT32       PrePopItem(INT32 nConSlot, INT32 nItemSlot);
    INT32       UnPrePopItem(INT32 nConSlot, INT32 nItemSlot);
    INT32       PopItem(const MS_ROLE_DATA *pRoleData, INT32 nConSlot, INT32 nItemSlot, INT32 &nBufferSize, char *pBuffer);
    
    INT32       MoveItem(INT32 nSourceConSlot, INT32 nSourceItemSlot, INT32 nTargetConSlot, INT32 nTargetItemSlot);

    STORAGE_EVENT_DATA *GetFirstStorageEventData();
    STORAGE_EVENT_DATA *GetNextStorageEventData(STORAGE_EVENT_DATA *pData);

    GUILD_STORAGE_ITEM_DATA   *GetFirstConSlotItem(INT32 nTag);
    GUILD_STORAGE_ITEM_DATA   *GetNextConSlotItem();

    BOOL        CheckCD();


    BOOL LoadStorage_v1(const char *pcData, UINT32 dwSize);
    BOOL LoadStorageHistory_v1(const char *pcData, UINT32 dwSize);
    BOOL SaveStorage(char *pData, UINT32 &dwSize);
    BOOL SaveStorageHistory(char *pData, UINT32 &dwSize);

protected:
    BOOL _AddStorageEvent(INT32 nType, UINT32 dwRoleID, INT32 nLength, const char *pcszItemBuffer);


private:
    GUILD_STORAGE_ITEM_DATA     m_aaItemBuffer[GUILD_STORAGE_MAX_TAG_NUM][GUILD_STORAGE_MAX_ITEM_NUM_PER_TAG];

    INT32               m_nHistoryNum;
    CBaseList           m_History;
    CMsGuild            *m_pOwnerGuild;
    INT32               m_nContainerCursor;
    INT32               m_nItemCursor;

    UINT32              m_nCD;
};






#endif //_H_MS_GUILD_STORAGE_H_



