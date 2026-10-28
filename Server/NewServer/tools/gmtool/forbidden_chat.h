/********************************************************************
	created:	4:7:2013   18:35
	file:		forbidden_chat.h
	author:		Allan Tao
	
	purpose:	禁言界面类
*********************************************************************/

#ifndef FORBIDDEN_CHAT_H_
#define FORBIDDEN_CHAT_H_



#include <QtWidgets/QMainWindow>
#include "ui_forbidden_chat.h"

class CForbiddenChat : public QDialog
{
    Q_OBJECT

public:
    CForbiddenChat(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CForbiddenChat();


public slots:
    void Execute();
    void Exit();


private:
    Ui::forbidChatDialog ui;
};







#endif FORBIDDEN_CHAT_H_


