/********************************************************************
	created:	5:7:2013   13:26
	file:		view_guild.h
	author:		Allan Tao
	
	purpose:	GM 工具 查看帮派
*********************************************************************/

#ifndef VIEW_GUILD_H_
#define VIEW_GUILD_H_


#include <QtWidgets/QMainWindow>
#include "ui_view_guild.h"


class CViewGuild : public QDialog
{
    Q_OBJECT

public:
    CViewGuild(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CViewGuild();


public slots:
    void Execute();
    void Exit();


private:
    Ui::viewGuildDialog ui;
};





#endif //VIEW_GUILD_H_











