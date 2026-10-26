/********************************************************************
	created:	25:12:2013   17:01
	file:		item_tree_widget_item.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_ITEM_TREE_WIDGET_ITEM_H_
#define _H_ITEM_TREE_WIDGET_ITEM_H_

#include <QtWidgets/QTreeWidget>


//class CRole;

class CItemTreeWidgetItem : public QTreeWidgetItem
{
public:
    CItemTreeWidgetItem();
    ~CItemTreeWidgetItem();

    void    SetParam1(UINT32 dwParam1)              { m_dwParam1 = dwParam1; }
    void    SetParam2(UINT32 dwParam2)              { m_dwParam2 = dwParam2; }
    void    SetParam3(UINT32 dwParam3)              { m_dwParam3 = dwParam3; }
    void    SetParam4(UINT32 dwParam4)              { m_dwParam4 = dwParam4; }
    void    SetParam5(UINT32 dwParam5)              { m_dwParam5 = dwParam5; }

    UINT32  GetParam1()                 { return m_dwParam1; }
    UINT32  GetParam2()                 { return m_dwParam2; }
    UINT32  GetParam3()                 { return m_dwParam3; }
    UINT32  GetParam4()                 { return m_dwParam4; }
    UINT32  GetParam5()                 { return m_dwParam5; }


private:
    UINT32      m_dwParam1;
    UINT32      m_dwParam2;
    UINT32      m_dwParam3;
    UINT32      m_dwParam4;
    UINT32      m_dwParam5;
};




#endif //_H_ITEM_TREE_WIDGET_ITEM_H_










