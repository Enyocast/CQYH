#ifndef _H_LOGIC_H_
#define _H_LOGIC_H_



class CMyTreeWidgetItem;

const char *GetBaseDataName(INT32 nBaseType);
const char *GetSexString(INT32 nSexType);
const char *GetClassString(INT32 nClassType);
const char * gm_itoa(INT32 i, char *pBuffer);
const char * gm_itoa64(INT64 i, char *pBuffer);

const char *GetItemContainerString(INT32 nConSlot);
const char *GetItemTypeString(INT32 nType);

BOOL DisplayBaseInfoWidgetItem(CMyTreeWidgetItem *pTreeItem, INT32 nAreaId, INT32 nGroupID, UINT32 dwRoleID, 
    BOOL bIsOnline, const char *pcszSaveTime, UINT32 dwDeleteTime, const char *pcszRoleName, INT32 nSex, INT32 nClass, INT32 nLevel);


const char *ParseResult(INT32 nResult);


const char *GetMailAttachType(INT32 nAttachType);


BOOL FilterUtf8EnterKey(char *pcszStr);

#endif // !_H_LOGIC_H_
