/********************************************************************
	created:	5:7:2013   10:15
	file:		mail.h
	author:		Allan Tao
	
	purpose:	GM command: send mail
*********************************************************************/

#ifndef MAIL_H_
#define MAIL_H_


#include <QtWidgets/QMainWindow>
#include "ui_mail.h"

class CMail : public QDialog
{
    Q_OBJECT

public:
    CMail(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CMail();


public slots:
    void Execute();
    void Exit();


private:
    Ui::mailDialog ui;
};



#endif //MAIL_H_










