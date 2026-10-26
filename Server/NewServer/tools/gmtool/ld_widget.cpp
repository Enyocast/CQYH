/********************************************************************
	created:	21:9:2015   15:33
	file:		ld_widget.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#include "stdafx.h"
#include "ld_widget.h"
#include "my_tree_widget_item.h"
#include "message_handler.h"
#include "server_mgr.h"
#include <QtWidgets/QMessageBox>
#include "gm_def.h"
#include "gm_item_info.h"
#include "string_ex.h"
#include "time.h"
#include "detail.h"
#include "time_ex.h"
#include "tl_config.h"

CLDWidget::CLDWidget(QWidget *parent, Qt::WindowFlags flags)
: QWidget(parent, flags)
{
    m_nGroupID = 0;
    m_nCurrentTime = 0;

    ui.setupUi(this);

    ui.treeWidget->setColumnWidth(0, 46);
    ui.treeWidget->setColumnWidth(1, 55);
    ui.treeWidget->setColumnWidth(2, 50);

    ui.treeWidget_2->setColumnWidth(0, 46);
    ui.treeWidget_2->setColumnWidth(1, 55);
    ui.treeWidget_2->setColumnWidth(2, 50);


    ui.treeWidget_3->setColumnWidth(0, 136);
    ui.treeWidget_3->setColumnWidth(1, 50);
    ui.treeWidget_3->setColumnWidth(2, 40);
    ui.treeWidget_3->setColumnWidth(3, 20);
    ui.treeWidget_3->setFrameShape(QTreeWidget::NoFrame);
    ui.gridLayout_5->setMargin(0);

    ui.treeWidget_4->setColumnWidth(0, 136);
    ui.treeWidget_4->setColumnWidth(1, 50);
    ui.treeWidget_4->setColumnWidth(2, 40);
    ui.treeWidget_4->setColumnWidth(3, 20);
    ui.treeWidget_4->setFrameShape(QTreeWidget::NoFrame);
    ui.gridLayout_6->setMargin(0);

    ui.treeWidget_5->setColumnWidth(0, 136);
    ui.treeWidget_5->setColumnWidth(1, 50);
    ui.treeWidget_5->setColumnWidth(2, 40);
    ui.treeWidget_5->setColumnWidth(3, 20);
    ui.treeWidget_5->setFrameShape(QTreeWidget::NoFrame);
    ui.gridLayout_7->setMargin(0);

    

    connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(ChangeGroup()));
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(MoreTradeInfo()));
    connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(ExportTradeInfo()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(AddOrder()));

    connect(ui.treeWidget, &QTreeWidget::itemClicked, this, &CLDWidget::OrderSelected);
    connect(ui.treeWidget, &QTreeWidget::itemDoubleClicked, this, &CLDWidget::OrderDetail);
    connect(ui.treeWidget_2, &QTreeWidget::itemClicked, this, &CLDWidget::OrderSelected_2);
    connect(ui.treeWidget_2, &QTreeWidget::itemDoubleClicked, this, &CLDWidget::OrderDetail_2);

    connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(SetExchangeLimit()));

    QDateTime   qDataTime;
    qDataTime.setTime_t(time(NULL));
    ui.dateTimeEdit->setDateTime(qDataTime);
    ui.dateTimeEdit_2->setDateTime(qDataTime);

    show();

    m_pExchangeLimit = NULL;
}

CLDWidget::~CLDWidget()
{

}

BOOL CLDWidget::Init()
{
    UnInit();
    return TRUE;
}

BOOL CLDWidget::UnInit()
{
    m_nGroupID = 0;
    ui.label_6->clear();
    ui.comboBox->clear();

    ui.treeWidget->clear();
    ui.treeWidget_2->clear();
    ui.treeWidget_3->clear();
    ui.treeWidget_4->clear();
    ui.treeWidget_5->clear();

    ui.label->clear();

    ui.doubleSpinBox->clear();
    ui.lineEdit->clear();

    ui.label_8->UnInit();
    //ui.label_8->clear();

    return TRUE;
}

BOOL CLDWidget::ServerLogin(INT32 nSvrID)
{
    INT32       nServerListIndex = 0;

    ui.label_6->clear();
    ui.comboBox->clear();

    for (; nServerListIndex < GM_MAX_SERVER_COUNT; ++nServerListIndex)
    {
        if (g_TLConfig.ServerList.arrGMList[nServerListIndex].nSvrID == nSvrID)
            break;
    }
    LOG_PROCESS_ERROR(GM_MAX_SERVER_COUNT != nServerListIndex);

    ui.comboBox->insertItem(0, "");
    for (INT32 nIndex = 1; nIndex < MAX_SERVER_GROUP_COUNT; ++nIndex)
    {
        QString a;
        a = QString::number(nIndex) + QString::fromLocal8Bit(" - ");
        if (0 == strlen(g_TLConfig.ServerList.arrGMList[nServerListIndex].groupList[nIndex].szGroupName))
        {
            ui.comboBox->insertItem(nIndex, a);
        }
        else
        {
            ui.comboBox->insertItem(nIndex, a + QString::fromUtf8(g_TLConfig.ServerList.arrGMList[nServerListIndex].groupList[nIndex].szGroupName));
        }
    }


    return TRUE;
Exit0:
    return FALSE;
}

BOOL CLDWidget::MainLoop()
{
    INT32       nRetCode = 0;
    INT32       nCurrTime = time(NULL);

    if (m_nCurrentTime != nCurrTime && m_nGroupID > 0)
    {
        nRetCode = CMessageHandler::GetInstance().DoQueryExchangeLog(m_nGroupID);
        LOG_CHECK_ERROR(nRetCode);

        if (m_nCurrentTime % 3 == 0)
        {
            nRetCode = CMessageHandler::GetInstance().DoQueryExchangeHistory(m_nGroupID);
            LOG_CHECK_ERROR(nRetCode);
        }

        if (m_nCurrentTime % 5 == 0)
        {
            UINT32      dwBeginTime = nCurrTime / 86400;
            dwBeginTime *= 86400;
            UINT32      dwEndTime = dwBeginTime + 86400;

            UINT32      dwBeginHour = nCurrTime / 3600;
            dwBeginHour *= 3600;
            UINT32      dwEndHour = dwBeginHour + 3600;

            nRetCode = CMessageHandler::GetInstance().DoQuerySysExchangeInfo(m_nGroupID, 1, dwBeginTime, dwEndTime, dwBeginHour, dwEndHour);
            LOG_CHECK_ERROR(nRetCode);
        }


        m_nCurrentTime = nCurrTime;
    }

    return TRUE;
}


BOOL CLDWidget::SetGroupID(INT32 nGroupID)
{
    ui.comboBox->setCurrentIndex(nGroupID);
    ui.label_6->setText(ui.comboBox->currentText());
    QPalette    qpa;
    qpa.setColor(QPalette::WindowText, Qt::red);
    ui.label_6->setPalette(qpa);
    m_nGroupID = nGroupID;

    return TRUE;
}

BOOL CLDWidget::UpdatePrice(INT32 nGroupID, INT32 nSellNum, INT32 nBuyNum, PRICE_DATA *pData)
{
    double  lfPrice = 0.0;
    ui.treeWidget->clear();
    ui.treeWidget_2->clear();

    if (nGroupID != m_nGroupID)
        return FALSE;

    LOG_PROCESS_ERROR(pData);

    for (INT32 i = nSellNum - 1; i >= 0; --i)
    {
        CMyTreeWidgetItem   *pTreeWidgetItem = new CMyTreeWidgetItem;
        LOG_PROCESS_ERROR(pTreeWidgetItem);

        pTreeWidgetItem->SetID(pData[i].nPrice);

        QString n;
        n.setNum(i+1);
        QString s = QString::fromLocal8Bit("卖") + n;
        pTreeWidgetItem->setText(0, s);
        lfPrice = pData[i].nPrice;
        lfPrice /= 100;
        pTreeWidgetItem->setText(1, QString::number(lfPrice));
        pTreeWidgetItem->setText(2, QString::number(pData[i].nCount));
        //pTreeWidgetItem->setText(1, QString::number(*(UINT32*)(pSlot->szData)));

        ui.treeWidget->addTopLevelItem(pTreeWidgetItem);
    }

    INT32   show_i = 1;
    for (INT32 i = nSellNum; i < nSellNum + nBuyNum; ++i, show_i++)
    {
        CMyTreeWidgetItem   *pTreeWidgetItem = new CMyTreeWidgetItem;
        LOG_PROCESS_ERROR(pTreeWidgetItem);

        pTreeWidgetItem->SetID(pData[i].nPrice);

        QString n;
        n.setNum(show_i);
        QString s = QString::fromLocal8Bit("买") + n;
        pTreeWidgetItem->setText(0, s);
        lfPrice = pData[i].nPrice;
        lfPrice /= 100;
        pTreeWidgetItem->setText(1, QString::number(lfPrice));
        pTreeWidgetItem->setText(2, QString::number(pData[i].nCount));
        //pTreeWidgetItem->setText(1, QString::number(*(UINT32*)(pSlot->szData)));

        ui.treeWidget_2->addTopLevelItem(pTreeWidgetItem);
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CLDWidget::UpdateExchangeLog(INT32 nGroupID, INT32 nCount, BOOL bClear, const char *pcData)
{
    INT32       nRetCode = 0;
    double      lfPrice = 0.0;
    GM_EXCHANGE_PRICE_LOG   *pElog = NULL;

    if (nGroupID != m_nGroupID)
        return FALSE;

    LOG_PROCESS_ERROR(pcData);

    if (bClear == TRUE)
    {
        ui.treeWidget_3->clear();
        ui.treeWidget_4->clear();
        ui.treeWidget_5->clear();
    }

    LOG_PROCESS_ERROR(pcData);

    pElog = (GM_EXCHANGE_PRICE_LOG *)pcData;

    //for (INT32 i = nCount - 1; i >= 0; --i)
    for (INT32 i = 0; i < nCount; ++i)
    {
        CMyTreeWidgetItem   *pTreeWidgetItem = new CMyTreeWidgetItem;
        LOG_PROCESS_ERROR(pTreeWidgetItem);

        pTreeWidgetItem->setText(0, QString(pElog[i].szExchangeTime /*+ 11*/));
        lfPrice = pElog[i].nPrice;
        lfPrice /= 100;
        pTreeWidgetItem->setText(1, QString::number(lfPrice));
        pTreeWidgetItem->setText(2, QString::number(pElog[i].nCount));
        if (pElog[i].dwSellerID == 0 )
            pTreeWidgetItem->setText(3, QString("S"));
        else
            pTreeWidgetItem->setText(3, QString("P"));

        ui.treeWidget_3->addTopLevelItem(pTreeWidgetItem);

        if (pElog[i].dwSellerID == 0)
        {
            CMyTreeWidgetItem   *pT = new CMyTreeWidgetItem;
            LOG_PROCESS_ERROR(pT);

            pT->setText(0, QString(pElog[i].szExchangeTime /*+ 11*/));
            lfPrice = pElog[i].nPrice;
            lfPrice /= 100;
            pT->setText(1, QString::number(lfPrice));
            pT->setText(2, QString::number(pElog[i].nCount));
            if (pElog[i].dwSellerID == 0)
                pT->setText(3, QString("S"));
            else
                pT->setText(3, QString("P"));
            ui.treeWidget_4->addTopLevelItem(pT);
        }
        else
        {
            CMyTreeWidgetItem   *pT = new CMyTreeWidgetItem;
            LOG_PROCESS_ERROR(pT);

            pT->setText(0, QString(pElog[i].szExchangeTime /*+ 11*/));
            lfPrice = pElog[i].nPrice;
            lfPrice /= 100;
            pT->setText(1, QString::number(lfPrice));
            pT->setText(2, QString::number(pElog[i].nCount));
            if (pElog[i].dwSellerID == 0)
                pT->setText(3, QString("S"));
            else
                pT->setText(3, QString("P"));
            ui.treeWidget_5->addTopLevelItem(pT);
        }

    }



    return TRUE;
Exit0:
    return FALSE;
}

BOOL CLDWidget::UpdateExchangeHistory(INT32 nGroupID, INT32 nCount, BOOL bClear, const char *pcData)
{
    if (nGroupID == m_nGroupID)
    {
        ui.label_8->SetData(nCount, pcData);
    }
    
    return TRUE;
}

BOOL CLDWidget::UpdateOrderDetail(INT32 nGroupID, INT32 nOrderType, INT32 nPrice, INT32 nCount, EXCHANGE_COUNT_DATA *pData)
{
    INT32   nLength = 0;
    double  lfPrice = 0.0;
    const   INT32 BUFFER_LENGTH = 1024 * 20;
    char    *pBuffer = NULL;

    LOG_PROCESS_ERROR(pData);

    pBuffer = new char[BUFFER_LENGTH];
    LOG_PROCESS_ERROR(pBuffer);

    memset(pBuffer, 0, BUFFER_LENGTH);

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%d\n", "区组", nGroupID);
    if (nOrderType == 2)
        nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\n", "卖单");
    else
        nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\n", "买单");

    lfPrice = nPrice;
    lfPrice /= 100;
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf\n", "价格", lfPrice);
    

    m_pDetailDialog = new CDetailDialog(m_nGroupID, this);
    LOG_PROCESS_ERROR(m_pDetailDialog);

    m_pDetailDialog->ShowData(pBuffer, nCount, pData);
    m_pDetailDialog->show();

    if (pBuffer)
        delete[] pBuffer;
    return TRUE;
Exit0:
    if (pBuffer)
        delete[] pBuffer;
    if (m_pDetailDialog)
    {
        delete m_pDetailDialog;
        m_pDetailDialog = NULL;
    }
    return FALSE;
}

BOOL CLDWidget::ShowTodayStat(INT32 nGroupID, 
    INT64 llSysTotalMoney, INT64 llTotalMoney,
    INT64 llSysTotalExchangeMoney, INT64 llTotalExchangeMoney,
    INT64 llSysExchangeRMB, INT64 llExchangeRMB,
    INT32 nAveragePriceToday, INT32 nAveragePriceLastHour)
{
    INT32   nLength = 0;
    const   INT32 BUFFER_LENGTH = 1024 * 20;
    char    *pBuffer = NULL;
    double  lfExchangeRMB = 0.0;
    double  lfTotalMoney = 0.0;
    double  lfTotalExchangeMoney = 0.0;

    double  lfSysExchangeRMB = 0.0;
    double  lfSysTotalMoney = 0.0;
    double  lfSysTotalExchangeMoney = 0.0;

    if (m_nGroupID != nGroupID)
        return FALSE;

    m_llSysTotalMoney = llSysTotalMoney;
    m_llSysTotalExchangeMoney = llSysTotalExchangeMoney;
    m_llSysExchangeRMB = llSysExchangeRMB;

    m_llTotalMoney = llTotalMoney;
    m_llTotalExchangeMoney = llTotalExchangeMoney;
    m_llExchangeRMB = llExchangeRMB;

    m_lfAveragePriceToday = nAveragePriceToday;
    m_lfAveragePriceToday /= 100;
    m_lfAveragePriceLastHour = nAveragePriceLastHour;
    m_lfAveragePriceLastHour /= 100;

    pBuffer = new char[BUFFER_LENGTH];
    LOG_PROCESS_ERROR(pBuffer);

    memset(pBuffer, 0, BUFFER_LENGTH);

    lfSysTotalMoney = m_llSysTotalMoney / 10000;
    lfSysTotalExchangeMoney = m_llSysTotalExchangeMoney / 10000;
    lfSysExchangeRMB = (double)m_llSysExchangeRMB / 100;
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf 万\n", "系统投放量", lfSysTotalMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf 万\n", "系统成交量", lfSysTotalExchangeMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf\n", "系统成交元宝", lfSysExchangeRMB);

    lfTotalMoney = m_llTotalMoney / 10000;
    lfTotalExchangeMoney = m_llTotalExchangeMoney / 10000;
    lfExchangeRMB = (double)m_llExchangeRMB / 100;
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "\n%s\t%.2lf 万\n", "玩家投放量", lfTotalMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf 万\n", "玩家成交量", lfTotalExchangeMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf\n\n", "玩家成交元宝", lfExchangeRMB);

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf\n", "当日平均价", m_lfAveragePriceToday);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf\n\n", "前1小时平均价", m_lfAveragePriceLastHour);

    ui.label->setText(QString::fromLocal8Bit(pBuffer));

    if (pBuffer)
        delete[] pBuffer;
    return TRUE;
Exit0:
    if (pBuffer)
        delete[] pBuffer;
    return FALSE;
}

BOOL CLDWidget::ShowYesterdayStat(INT32 nGroupID, 
    INT64 llSysYesTotalMoney, INT64 llYesTotalMoney,
    INT64 llSysYesTotalExchangeMoney, INT64 llYesTotalExchangeMoney,
    INT64 llSysYesExchangeRMB, INT64 llYesExchangeRMB,
    INT32 nAveragePriceToday, INT32 nAveragePriceLastHour)
{
    INT32   nLength = 0;
    const   INT32 BUFFER_LENGTH = 1024 * 20;
    char    *pBuffer = NULL;
    CGMItemInfo *pItemInfo = NULL;
    
    double  lfSysExchangeRMB = 0.0;
    double  lfSysTotalMoney = 0.0;
    double  lfSysTotalExchangeMoney = 0.0;

    double  lfExchangeRMB = 0.0;
    double  lfTotalMoney = 0.0;
    double  lfTotalExchangeMoney = 0.0;

    double  lfSysYesExchangeRMB = 0.0;
    double  lfSysYesTotalMoney = 0.0;
    double  lfSysYesTotalExchangeMoney = 0.0;

    double  lfYesExchangeRMB = 0.0;
    double  lfYesTotalMoney = 0.0;
    double  lfYesTotalExchangeMoney = 0.0;

    if (m_nGroupID != nGroupID)
        return FALSE;

    pBuffer = new char[BUFFER_LENGTH];
    LOG_PROCESS_ERROR(pBuffer);

    memset(pBuffer, 0, BUFFER_LENGTH);

    lfSysTotalMoney = m_llSysTotalMoney / 10000;
    lfSysTotalExchangeMoney = m_llSysTotalExchangeMoney / 10000;
    lfSysExchangeRMB = (double)m_llSysExchangeRMB / 100;
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf 万\n", "系统投放量", lfSysTotalMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf 万\n", "系统成交量", lfSysTotalExchangeMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf\n\n", "系统成交元宝", lfSysExchangeRMB);

    lfTotalMoney = m_llTotalMoney / 10000;
    lfTotalExchangeMoney = m_llTotalExchangeMoney / 10000;
    lfExchangeRMB = (double)m_llExchangeRMB / 100;
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf 万\n", "玩家投放量", lfTotalMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf 万\n", "玩家成交量", lfTotalExchangeMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf\n\n", "玩家成交元宝", lfExchangeRMB);

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf\n\n", "当日平均价", m_lfAveragePriceToday);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf\n\n\n\n", "前1小时平均价", m_lfAveragePriceLastHour);


    // yesterday
    lfSysYesTotalMoney = llSysYesTotalMoney / 10000;
    lfSysYesTotalExchangeMoney = llSysYesTotalExchangeMoney / 10000;
    lfSysYesExchangeRMB = (double)llSysYesExchangeRMB / 100;
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf 万\n", "昨日系统投放量", lfSysYesTotalMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf 万\n", "昨日系统成交量", lfSysYesTotalExchangeMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf\n\n", "昨日系统成交元宝", lfSysYesExchangeRMB);

    lfYesTotalMoney = llYesTotalMoney / 10000;
    lfYesTotalExchangeMoney = llYesTotalExchangeMoney / 10000;
    lfYesExchangeRMB = (double)llYesExchangeRMB / 100;
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf 万\n", "昨日玩家投放量", lfYesTotalMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf 万\n", "昨日玩家成交量", lfYesTotalExchangeMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%.2lf\n\n", "昨日玩家成交元宝", lfYesExchangeRMB);

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%d\n\n", "昨日平均价", nAveragePriceToday);

    
    pItemInfo = new CGMItemInfo(this);
    LOG_PROCESS_ERROR(pItemInfo);

    pItemInfo->ShowInfo(pBuffer, TRUE);
    pItemInfo->show();

    if (pBuffer)
        delete[] pBuffer;
    return TRUE;
Exit0:
    if (pBuffer)
        delete[] pBuffer;
    return FALSE;
}

BOOL CLDWidget::OutputStatToFile(UINT32 dwBeginTime, UINT32 dwEndTime, INT32 nGroupID,
    INT64 llSysTotalMoney, INT64 llTotalMoney,
    INT64 llSysTotalExchangeMoney, INT64 llTotalExchangeMoney,
    INT64 llSysExchangeRMB, INT64 llExchangeRMB,
    INT32 nAveragePriceToday, INT32 nAveragePriceLastHour)
{
    INT32   nLength = 0;
    const   INT32 BUFFER_LENGTH = 1024 * 20;
    char    *pBuffer = NULL;

    double  lfSysExchangeRMB = 0.0;
    double  lfSysTotalMoney = 0.0;
    double  lfSysTotalExchangeMoney = 0.0;

    double  lfExchangeRMB = 0.0;
    double  lfTotalMoney = 0.0;
    double  lfTotalExchangeMoney = 0.0;

    time_t  tTime = 0;
    struct tm *pTMBegin = NULL;
    struct tm *pTMEnd = NULL;

    if (m_nGroupID != nGroupID)
        return FALSE;

    pBuffer = new char[BUFFER_LENGTH];
    LOG_PROCESS_ERROR(pBuffer);

    memset(pBuffer, 0, BUFFER_LENGTH);

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, 
        "开始时间\t结束时间\t系统投放量\t系统成交量\t系统成交元宝\t玩家投放量\t玩家成交量\t玩家成交元宝\t平均价\n");

    tTime = dwBeginTime;
    pTMBegin = localtime(&tTime);
    LOG_PROCESS_ERROR(pTMBegin);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%d-%d-%d %d:%d\t", pTMBegin->tm_year + 1900, pTMBegin->tm_mon + 1, pTMBegin->tm_mday, pTMBegin->tm_hour, pTMBegin->tm_min);

    tTime = dwEndTime;
    pTMEnd = localtime(&tTime);
    LOG_PROCESS_ERROR(pTMEnd);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%d-%d-%d %d:%d\t", pTMEnd->tm_year + 1900, pTMEnd->tm_mon + 1, pTMEnd->tm_mday, pTMEnd->tm_hour, pTMEnd->tm_min);

    // 
    lfSysTotalMoney = llSysTotalMoney / 10000;
    lfSysTotalExchangeMoney = llSysTotalExchangeMoney / 10000;
    lfSysExchangeRMB = (double)llSysExchangeRMB / 100;

    lfTotalMoney = llTotalMoney / 10000;
    lfTotalExchangeMoney = llTotalExchangeMoney / 10000;
    lfExchangeRMB = (double)llExchangeRMB / 100;

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%d\n", 
        lfSysTotalMoney, lfSysTotalExchangeMoney, 
        lfSysExchangeRMB, lfTotalMoney, lfTotalExchangeMoney, lfExchangeRMB, nAveragePriceToday);

    {
        INT32       nFileLength = 0;
        char        szFileName[128] = { 0 };

        tTime = dwBeginTime;
        pTMBegin = localtime(&tTime);
        LOG_PROCESS_ERROR(pTMBegin);
        nFileLength += snprintf(szFileName + nFileLength, 128 - nFileLength, "../%d-%d_", pTMBegin->tm_mon + 1, pTMBegin->tm_mday);

        tTime = dwEndTime;
        pTMEnd = localtime(&tTime);
        LOG_PROCESS_ERROR(pTMEnd);
        nFileLength += snprintf(szFileName + nFileLength, 128 - nFileLength, "%d-%d.txt", pTMEnd->tm_mon + 1, pTMEnd->tm_mday);

        FILE    *pFile = fopen(szFileName, "w");
        LOG_PROCESS_ERROR(pFile);

        fwrite(pBuffer, 1, nLength, pFile);

        fclose(pFile);
    }
    
    if (pBuffer)
        delete[] pBuffer;
    return TRUE;
Exit0:
    if (pBuffer)
        delete[] pBuffer;
    return FALSE;
}

BOOL CLDWidget::DelDetail()
{
    if (m_pDetailDialog)
    {
        m_pDetailDialog->Exit();
        m_pDetailDialog = NULL;
    }

    return TRUE;
}

BOOL CLDWidget::ShowExchangeLimit(INT32 nPriceHigh, INT32 nPriceLow, INT32 nSingleOrderLimit, INT32 nDailyOrderLimit)
{
    if (m_pExchangeLimit == NULL)
    {
        m_pExchangeLimit = new CExchangeLimit(m_nGroupID, this);
        
    }

    m_pExchangeLimit->ShowExchangeLimit(nPriceHigh, nPriceLow, nSingleOrderLimit, nDailyOrderLimit);
    m_pExchangeLimit->show();

    return TRUE;
}

void CLDWidget::ClearExchangeLimit()
{
    if (m_pExchangeLimit)
    {
        delete m_pExchangeLimit;
        m_pExchangeLimit = NULL;
    }
}

void CLDWidget::ChangeGroup()
{
    INT32       nRetCode = 0;
    INT32       nGroupID = 0;

    nGroupID = ui.comboBox->currentIndex();

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    nRetCode = CMessageHandler::GetInstance().DoSelectGroup( nGroupID);
    LOG_PROCESS_ERROR(nRetCode);

    ui.treeWidget->clear();
    ui.treeWidget_2->clear();

Exit0:
    return;
}

void CLDWidget::MoreTradeInfo()
{
    INT32       nRetCode = 0;
    INT32       nCurrTime = time(NULL) + get_time_zone();
    UINT32      dwBeginTime = nCurrTime / 86400;
    --dwBeginTime;
    dwBeginTime *= 86400;
    UINT32      dwEndTime = dwBeginTime + 86400;

    if (m_nGroupID < 1 || m_nGroupID > (MAX_SERVER_GROUP_COUNT - 1))
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("服务器区组不对"), QMessageBox::Yes);
        return;
    }

    nRetCode = CMessageHandler::GetInstance().DoQuerySysExchangeInfo(m_nGroupID, 0, dwBeginTime, dwEndTime, 0, 0);
    LOG_CHECK_ERROR(nRetCode);

    return;
}

void CLDWidget::ExportTradeInfo()
{
    INT32       nRetCode = 0;
    UINT32      dwBeginTime = 0;
    UINT32      dwEndTime = 0;

    dwBeginTime = ui.dateTimeEdit->dateTime().toTime_t();
    dwEndTime = ui.dateTimeEdit_2->dateTime().toTime_t();

    if (m_nGroupID < 1 || m_nGroupID >(MAX_SERVER_GROUP_COUNT - 1))
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("服务器区组不对"), QMessageBox::Yes);
        return;
    }

    nRetCode = CMessageHandler::GetInstance().DoQuerySysExchangeInfo(m_nGroupID, 3, dwBeginTime, dwEndTime, 0, 0);
    LOG_CHECK_ERROR(nRetCode);

    return;
}

void CLDWidget::AddOrder()
{
    INT32       nRetCode = 0;
    INT32       nGroupID = 0;
    double      lfPrice = 0.0;
    INT32       nPrice = 0;
    INT32       nCount = 0;

    nGroupID = m_nGroupID;
    lfPrice = ui.doubleSpinBox->text().toDouble();
    nCount = ui.lineEdit->text().toInt();
    nPrice = lfPrice * 100;

    if (nGroupID < 1 || nGroupID > (MAX_SERVER_GROUP_COUNT - 1))
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("服务器区组不对"), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("是否确定单价加单"));
    if (nCheckEnum == QMessageBox::Yes)
    {
        nRetCode = CMessageHandler::GetInstance().DoAddSystemOrder(nGroupID, nPrice, nCount);
        LOG_PROCESS_ERROR(nRetCode);
    }

Exit0:
    return;
}

void CLDWidget::OrderSelected(QTreeWidgetItem * item, int column)
{
    LOG_PROCESS_ERROR(item);

    ui.treeWidget->setItemSelected(item, true);
    //item->setSelected(true);

Exit0:
    return;
}

void CLDWidget::OrderSelected_2(QTreeWidgetItem * item, int column)
{

}

void CLDWidget::OrderDetail(QTreeWidgetItem * item, int column)
{
    INT32       nRetCode = 0;
    INT32       nPrice = 0;
    INT32       nCount = 0;

    LOG_PROCESS_ERROR(item);

    nPrice = ((CMyTreeWidgetItem*)item)->GetID();

    if (m_nGroupID < 1 || m_nGroupID >(MAX_SERVER_GROUP_COUNT - 1))
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("服务器区组不对"), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    nRetCode = CMessageHandler::GetInstance().DoQueryOrderDetail(m_nGroupID, 2, nPrice);
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return;

}

void CLDWidget::OrderDetail_2(QTreeWidgetItem * item, int column)
{
    INT32       nRetCode = 0;
    INT32       nPrice = 0;
    INT32       nCount = 0;

    LOG_PROCESS_ERROR(item);

    nPrice = ((CMyTreeWidgetItem*)item)->GetID();

    if (m_nGroupID < 1 || m_nGroupID >(MAX_SERVER_GROUP_COUNT - 1))
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("服务器区组不对"), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    nRetCode = CMessageHandler::GetInstance().DoQueryOrderDetail(m_nGroupID, 1, nPrice);
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return;
}

void CLDWidget::SetExchangeLimit()
{
    INT32       nRetCode = 0;

    if (m_nGroupID < 1 || m_nGroupID >(MAX_SERVER_GROUP_COUNT - 1))
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("服务器区组不对"), QMessageBox::Yes);
        return;
    }

    nRetCode = CServerMgr::GetInstance().IsSingleSelected();
    if (nRetCode == FALSE)
    {
        QMessageBox::critical(this, "critical", QString::fromLocal8Bit("一次只能执行一个区服"), QMessageBox::Yes);
        return;
    }

    nRetCode = CMessageHandler::GetInstance().DoQueryExchangeLimit(m_nGroupID);
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return;
}



//void CLDWidget::paintEvent(QPaintEvent *event)
//{
//    ui.label_8->paintEvent(event);
//    //QPainter    painter;
//    //QBrush      brush;
//
//    //brush.setColor(QColor(255, 255, 0));
//    //painter.setBrush(brush);
//
//    //painter.drawRect(QRect(0, 0, 2000, 2000));
//
//    //painter.end();
//
//    QWidget::paintEvent(event);
//}
