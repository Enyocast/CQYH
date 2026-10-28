/********************************************************************
	created:	4:7:2013   18:35
	file:		loader.h
	author:		Allan Tao
	
	purpose:	登陆界面类
*********************************************************************/
#ifndef LOADER_H
#define LOADER_H

#include <QtWidgets/QMainWindow>
#include "ui_loader.h"

class loader : public QDialog
{
    Q_OBJECT

public:
    loader(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~loader();

    //virtual void timerEvent(QTimerEvent* event);

    BOOL VerifyUser(INT32 nResult, BOOL bLD);

public slots:
    void Login();
    void Exit();


private:
    INT32       m_nTimeID;
    Ui::loginDialog ui;
};

extern loader  g_loader;

#endif // LOADER_H