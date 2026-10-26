/********************************************************************
	created:	13:2:2014   10:36
	file:		svr_tree_widget_item.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_SVR_TREE_WIDGET_ITEM_H_
#define _H_SVR_TREE_WIDGET_ITEM_H_


#include <QtWidgets/QTreeWidget>

class CSvrTreeWidgetItem : public QTreeWidgetItem
{
public:
    CSvrTreeWidgetItem();
    ~CSvrTreeWidgetItem();


    INT32   GetSessionID();
    void    SetSessionID(UINT32 dwSessionID);


private:
    UINT32  m_dwSessionID;
};



#endif //_H_SVR_TREE_WIDGET_ITEM_H_















