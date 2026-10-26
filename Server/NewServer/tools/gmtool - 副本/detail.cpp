/********************************************************************
	created:	5:12:2013   10:25
	file:		result.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#include "stdafx.h"
#include "detail.h"
#include "my_tree_widget_item.h"
#include "ld_widget.h"
#include "message_handler.h"
#include <QtWidgets/QMessageBox>


CDetailDialog::CDetailDialog(INT32 nGroupID, QWidget *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
    m_nGroupID = nGroupID;
    ui.setupUi(this);

    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(Exit()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(CancelSystemOrder()));


}

CDetailDialog::~CDetailDialog()
{

}

BOOL CDetailDialog::ShowData(const char *pcszBuffer, INT32 nCount, EXCHANGE_COUNT_DATA *pData)
{
    LOG_PROCESS_ERROR(pcszBuffer);
    LOG_PROCESS_ERROR(pData);

    ui.label->setText(QString::fromLocal8Bit(pcszBuffer));


    for (INT32 i = 0; i < nCount; ++i)
    {
        CMyTreeWidgetItem   *pTreeWidgetItem = new CMyTreeWidgetItem;
        LOG_PROCESS_ERROR(pTreeWidgetItem);

        pTreeWidgetItem->Set64ID(pData[i].qwOrderID);

        pTreeWidgetItem->setText(0, QString::number(pData[i].qwOrderID));
        pTreeWidgetItem->setText(1, QString::fromUtf8(pData[i].szRoleName));
        pTreeWidgetItem->setText(2, QString::number(pData[i].nCount));

        if (pData[i].dwRoleID == 0)
        {
            pTreeWidgetItem->setTextColor(1, QColor(255,0,0));
        }

        ui.treeWidget->addTopLevelItem(pTreeWidgetItem);
    }


Exit0:
    return TRUE;
}

void CDetailDialog::CancelSystemOrder()
{
    INT32       nRetCode = 0;
    CMyTreeWidgetItem   *pItem = NULL;

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认取消订单？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    pItem = (CMyTreeWidgetItem *)ui.treeWidget->currentItem();
    LOG_PROCESS_ERROR(pItem);

    nRetCode = CMessageHandler::GetInstance().DoDelSystemOrder(m_nGroupID, pItem->Get64ID());
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return;
}

void CDetailDialog::Exit()
{
    done(0);
}




