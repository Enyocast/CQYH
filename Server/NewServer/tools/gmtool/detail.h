/********************************************************************
	created:	5:12:2013   10:22
	file:		result.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_DETAIL_H_
#define _H_DETAIL_H_


#include <QtWidgets/QMainWindow>
#include "ui_detail.h"

struct EXCHANGE_COUNT_DATA;

class CDetailDialog : public QDialog
{
    Q_OBJECT

public:
    CDetailDialog(INT32 nGroupID, QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CDetailDialog();

    BOOL    ShowData(const char *pcszBuffer, INT32 nCount, EXCHANGE_COUNT_DATA *pData);

public slots:
        void CancelSystemOrder();
        void Exit();


private:
    INT32   m_nTimeID;
    INT32   m_nGroupID;

    Ui::detailDialog ui;
};




#endif //_H_DETAIL_H_

