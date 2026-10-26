/********************************************************************
	created:	19:8:2013   15:35
	file:		my_tree_widget_item.h
	author:		Allan Tao
	
	purpose:	¼Ì³Ð×ÔQTreeWidgetItem
*********************************************************************/

#ifndef _H_MY_TREE_WIDGET_ITEM_H_
#define _H_MY_TREE_WIDGET_ITEM_H_

#include <QtWidgets/QTreeWidget>


//class CRole;

class CMyTreeWidgetItem : public QTreeWidgetItem
{
public:
    CMyTreeWidgetItem();
    ~CMyTreeWidgetItem();


    INT32   GetSvrID();
    //CRole*  GetRoleDataPtr();

    //void    SetSvrID(INT32 nSvrID);
    //void    SetCRolePtr(CRole *poRole);

    //void    SetRoleID(UINT32 dwRoleID);
    //UINT32  GetRoleID();

    void    Set64ID(INT64 qwID)     { m_qwID = qwID; }
    INT64   Get64ID()               { return m_qwID; }

    void    SetID(INT32 dwID)       { m_dwID = dwID; }
    INT32   GetID()                 { return m_dwID; }

    void    SetRoleType(INT32 nType)        { m_nRoleType = nType; }
    INT32   GetRoleType()           { return m_nRoleType; }

    void    SetBaseDataType(INT32 nType)    { m_nBaseType = nType; }
    INT32   GetBaseDataType()       { return m_nBaseType; }


private:
    //CRole   *m_poRole;
    INT32   m_nSvrID;
    //UINT32  m_dwRoleID;

    INT64   m_qwID;
    INT32   m_dwID;

    INT32   m_nRoleType;
    INT32   m_nBaseType;

};




#endif //_H_MY_TREE_WIDGET_ITEM_H_







