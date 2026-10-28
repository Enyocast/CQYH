/********************************************************************
	created:	5:7:2013   11:09
	file:		delete_item.h
	author:		Allan Tao
	
	purpose:	GM command: delete item
*********************************************************************/


#ifndef DELETE_ITEM_H_
#define DELETE_ITEM_H_

#include <QtWidgets/QMainWindow>
#include "ui_delete_item.h"



class CDeleteItem : public QDialog
{
    Q_OBJECT

public:
    CDeleteItem(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CDeleteItem();


public slots:
    void Execute();
    void Exit();
    void OnSelectDeleteItemType(const QString &);


private:
    Ui::deleteItemDialog ui;
};





#endif //DELETE_ITEM_H_






