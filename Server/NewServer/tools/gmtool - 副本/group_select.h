/********************************************************************
	created:	5:7:2013   18:16
	file:		group_select.h
	author:		Allan Tao
	
	purpose:	GM 工具 区服选择界面
*********************************************************************/

#ifndef GROUP_SELECT_H_
#define GROUP_SELECT_H_

#include <QtWidgets/QMainWindow>
#include "ui_group_select.h"

class CGroupSelect : public QDialog
{
    Q_OBJECT

public:
    CGroupSelect(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CGroupSelect();


public slots:
    void Execute();
    void Exit();


private:
    Ui::groupSelectDialog ui;
};





#endif //GROUP_SELECT_H_





