/********************************************************************
	created:	5:7:2013   10:18
	file:		move_position.h
	author:		Allan Tao
	
	purpose:	GM √¸¡Ó£¨“∆∂ØŒª÷√
*********************************************************************/

#ifndef MOVE_POSITION_H_
#define MOVE_POSITION_H_

#include <QtWidgets/QMainWindow>
#include "ui_move_position.h"


class CMovePosition : public QDialog
{
    Q_OBJECT

public:
    CMovePosition(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CMovePosition();


public slots:
    void Execute();
    void Exit();


private:
    Ui::movePositionDialog ui;
};






#endif //MOVE_POSITION_H_

