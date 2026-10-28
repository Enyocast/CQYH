/********************************************************************
	created:	8:7:2013   16:15
	file:		application_mgr.h
	author:		Allan Tao
	
	purpose:	Application management(app_node nodes are currently managed externally
                    and may later be managed here with a factory)
*********************************************************************/

#ifndef _H_APPLICATION_MGR_H_
#define _H_APPLICATION_MGR_H_

#include "base_list.h"

#define HASH_TABLE_BUCKET_NUM (4096)

enum ENAPP_NODE_TYPE
{
    EN_GUILD_APPLICATION = 1,
    EN_DIPLOMAT_APPLICATION = 2,
};

struct APP_NODE;

typedef void (*fpAppTimeOutCallBack)(APP_NODE* pNode);

struct APP_NODE
{
    UINT32      dwID_1;
    UINT32      dwID_2;
    INT32       nType;
    UINT32      dwWashOutTime;
    BASE_LIST_NODE  HashTableNode1;
    BASE_LIST_NODE  HashTableNode2;
    BASE_LIST_NODE  TimeNode;
    fpAppTimeOutCallBack fp;
};




class CApplicationMgr
{
public:
    CApplicationMgr();
    static CApplicationMgr &GetInstance();
protected:
    ~CApplicationMgr();

public:
    BOOL Init();
    BOOL UnInit();
    BOOL MainLoop();

    BOOL InsertApplication(APP_NODE *pNode);
    BOOL RemoveApplication(APP_NODE *pNode);

    APP_NODE *Find(UINT32 dwID1, UINT32 dwID2);

    APP_NODE *FirstAppNodeByID1(UINT32 dwID1);
    APP_NODE *NextAppNodeByID1(APP_NODE *pNode);

    APP_NODE *FirstAppNodeByID2(UINT32 dwID2);
    APP_NODE *NextAppNodeByID2(APP_NODE *pNode);


protected:
    INT32 _GetHashValue(UINT32 dwID);

private:
    static CApplicationMgr  m_Instance;

private:
    CBaseList    m_HashTable1[HASH_TABLE_BUCKET_NUM];
    CBaseList    m_HashTable2[HASH_TABLE_BUCKET_NUM];
    CBaseList   m_TimeList;
};









#endif //_H_APPLICATION_MGR_H_


