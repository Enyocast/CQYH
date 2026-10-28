/********************************************************************
	created:	5:7:2013   10:11
	file:		kick_user.h
	author:		Allan Tao
	
	purpose:	GM command: kick player and ban account
*********************************************************************/

#ifndef KICK_USER_H_
#define KICK_USER_H_

#include <QtWidgets/QMainWindow>
#include "ui_kick_user.h"

class CKickUser : public QDialog
{
    Q_OBJECT

public:
    CKickUser(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CKickUser();


public slots:
    void Execute();
    void Exit();


private:
    Ui::kickUserDialog ui;
};





#endif KICK_USER_H_



