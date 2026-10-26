/********************************************************************
	created:	7:1:2014   17:23
	file:		view_friend.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_VIEW_FRIEND_H_
#define _H_VIEW_FRIEND_H_

#include <QtWidgets/QMainWindow>
#include "ui_view_friend.h"

class CViewFriend : public QDialog
{
    Q_OBJECT

public:
    CViewFriend(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CViewFriend();



private:
    INT32       m_nTimeID;
    Ui::viewFriendDialog ui;
};

#endif // _H_VIEW_FRIEND_H_





