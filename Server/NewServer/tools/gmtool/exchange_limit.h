
#ifndef _H_EXCHANGE_LIMIT_H_
#define _H_EXCHANGE_LIMIT_H_


#include <QtWidgets/QMainWindow>
#include "ui_exchange_limit.h"

class CExchangeLimit : public QDialog
{
    Q_OBJECT

public:
    CExchangeLimit(INT32 nGroup, QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CExchangeLimit();


    BOOL ShowExchangeLimit(INT32 nPriceHigh, INT32 nPriceLow, INT32 nSingleOrderLimit, INT32 nDailyOrderLimit);


public slots:
    void Modify();
    void Exit();


private:
    INT32   m_nGroup;

    Ui::exchangeLimitDialog ui;
};




#endif //_H_EXCHANGE_LIMIT_H_




























