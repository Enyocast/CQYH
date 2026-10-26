#ifndef _H_TITLE_H_
#define _H_TITLE_H_

#include <map>
#include "title_def.h"
#include "title_data.h"

class CRole;

struct TITLE
{
    UINT8       m_nTemplateID;
    INT32       m_nExpireTime;

public:
    TITLE();

public:
    BOOL    OnEquip(CRole* role);
    BOOL    OnUnEquip(CRole* role);
    BOOL    IsExpire();
};



class CTitle
{
public:
    CTitle();
    ~CTitle();

    BOOL    Init(CRole* role);
    BOOL    clear();

    void SetOwner(CRole* role);

    BOOL    Load_v_1(const char* pcData, UINT32 dwSize);
    BOOL    Save(const char* pcData, UINT32& rdwSize);

    void    fill(void* pData, UINT8 &nTitleCount);

    UINT8   GetEquipedTitleID()     { return m_nEquipedTitleID; }

    BOOL    AddTitle(UINT8 titleTemplateID);
    BOOL    DeleteTitle(UINT8 titleTemplateID, UINT8 nDelType);
    INT32   EquipTile(UINT8 titleTemplateID);
    BOOL    UnEquipTitle();
	
	BOOL	IsTitleExist(UINT8 wTitleTemplateID);
	INT32	GetTitleCount();

    INT32   GetPow();

    void    MainLoop(void);

    TITLE   *First();
    TITLE   *Next();

#ifdef _ROBOT
    void OnAddTitle(UINT8 titleTemplateID, UINT32 nExpireTime);
    void OnDelTitle(UINT8 titleTemplateID, UINT8 nDelType);
    void OnEquipTitle(UINT8 titleID);
    
#endif

private:
    BOOL    PreCheckEquipTitle(UINT8 titleID);
    BOOL    PreCheckEquipTitle_i(UINT16 nType, UINT16 nValue);

private:
    CRole*          m_pOwner;
    UINT8           m_nEquipedTitleID;
    typedef std::map<UINT8, TITLE> TITLE_MAP;
    TITLE_MAP       m_Title_Map;
    TITLE_MAP::iterator     m_TitleMapCursor;
};


#endif //_H_TITLE_H_


