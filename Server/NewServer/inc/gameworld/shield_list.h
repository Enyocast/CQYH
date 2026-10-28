/********************************************************************
	created:	20:5:2013   18:17
	file:		shield_list.h
	author:		Allan Tao
	
	purpose:	Block list
*********************************************************************/


#ifndef _H_SHIELD_LIST_H_
#define _H_SHIELD_LIST_H_

#define MAX_SHIELD_NUM (40)

class CShieldList
{
public:
    CShieldList();
    ~CShieldList();

    BOOL Init();
    BOOL UnInit();

    BOOL Load_v_1(const char* pcData, UINT32 dwSize);
    BOOL Save(char* pcData, UINT32& rdwSize);

    void    ShieldRole(UINT32 dwRoleID);
    void    UnShieldRole(UINT32 dwRoleID);

    BOOL    IsShieldedListFull();

    BOOL    IsAlreadyShielded(UINT32 dwRoleID);

    UINT8   GetShieldCount() { return m_byShieldNum; }
    UINT32  FindShieldedRole(INT32 nIndex);

private:
    UINT8       m_byShieldNum;
    UINT32      m_arrRoleID[MAX_SHIELD_NUM];

};




#endif //_H_SHIELD_LIST_H_





