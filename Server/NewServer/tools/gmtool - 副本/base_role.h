/********************************************************************
	created:	21:12:2013   17:10
	file:		base_role.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_BASE_ROLE_H_
#define _H_BASE_ROLE_H_




struct TL_ROLE_BASE_INFO 
{
    UINT32          dwRoleID;
    char            szRoleName[ROLE_NAME_LEN];
    UINT32          dwSvrID;
    UINT8			byGroup;
    UINT8           byLevel;
    UINT8           bySex;
    UINT8           byClass;
};












#endif //_H_BASE_ROLE_H_






















