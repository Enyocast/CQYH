
#include "stdafx.h"
#include "exchange_limit.h"
#include "message_handler.h"
#include "gmtool.h"
#include "ld_widget.h"

CExchangeLimit::CExchangeLimit(INT32 nGroup, QWidget *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
    ui.setupUi(this);

    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(Modify()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(Exit()));


    m_nGroup = nGroup;


}

CExchangeLimit::~CExchangeLimit()
{

}

BOOL CExchangeLimit::ShowExchangeLimit(INT32 nPriceHigh, INT32 nPriceLow, INT32 nSingleOrderLimit, INT32 nDailyOrderLimit)
{
    double  lfPriceHigh = (double)nPriceHigh / 100;
    double  lfPriceLow = (double)nPriceLow / 100;

    ui.label_5->setText(QString::number(lfPriceHigh));
    ui.label_6->setText(QString::number(lfPriceLow));
    ui.label_7->setText(QString::number(nSingleOrderLimit));
    ui.label_8->setText(QString::number(nDailyOrderLimit));

    return TRUE;
}


void CExchangeLimit::Exit()
{
    //g_gmtool.GetLDWidget()->ClearExchangeLimit();

Exit0:
    done(0);
}

void CExchangeLimit::Modify()
{
    INT32       nRetCode = 0;

    nRetCode = CMessageHandler::GetInstance().DoSetExchangeLimit(m_nGroup,
        ui.doubleSpinBox->text().toDouble() * 100,
        ui.doubleSpinBox_2->text().toDouble() * 100,
        ui.spinBox->text().toInt(),
        ui.spinBox_2->text().toInt());

Exit0:
    done(0);
    return;
}













