/********************************************************************
	created:	25:12:2013   16:14
	file:		role_info.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#include "stdafx.h"
#include "role_info.h"

//#include <QInputDialog>
//#include <QMainWindow>
#include <QtWidgets/QMessageBox>

#include "session_mgr.h"
#include "cmd_manager.h"
#include "gm_manager.h"
#include "item_tree_widget_item.h"
#include "my_tree_widget_item.h"
#include "gmtool.h"
#include "message_handler.h"

#include "data_mgr.h"
#include "string_ex.h"
#include "gm_log.h"
#include "logic.h"
#include "server_mgr.h"
#include "gm_item_info.h"

CRoleInfo   *g_pRoleInfo;

CRoleInfo::CRoleInfo(UINT32 dwSessionID, UINT32 dwRoleID, BOOL bIsModify, QWidget *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
    ui.setupUi(this);

    m_bIsModify = bIsModify;
    m_dwSessionID = dwSessionID;

    memset(m_pLabel, 0, sizeof(m_pLabel));
    memset(m_pLineEdit, 0, sizeof(m_pLineEdit));

    connect(ui.baseDataTreeWidget, &QTreeWidget::itemDoubleClicked, this, &CRoleInfo::BaseDataModify);
    connect(ui.baseDataTreeWidget, &QTreeWidget::itemChanged, this, &CRoleInfo::BaseDataChanged);
    
    connect(ui.itemWidget, &QTreeWidget::itemDoubleClicked, this, &CRoleInfo::ShowItemInfo);

    connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(Exit()));
    connect(ui.OkButton, SIGNAL(clicked()), this, SLOT(EndModify())); 
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ReturnPos()));
    connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(SetTargetRole()));

    connect(ui.takeItemButton, SIGNAL(clicked()), this, SLOT(TakeItem()));
    connect(ui.delQuestButton, SIGNAL(clicked()), this, SLOT(DelQuest()));
    connect(ui.delItemButton, SIGNAL(clicked()), this, SLOT(DelItem()));
    connect(ui.delMailButton, SIGNAL(clicked()), this, SLOT(DelMail()));

    m_dwRoleID = dwRoleID;
    m_dwTargetRoleID = 0;

    m_nLength = 0;
    memset(m_SaveList, 0, sizeof(m_SaveList));

    m_ItemMap.clear();

    _Update();

Exit0:
    return;
}

CRoleInfo::~CRoleInfo()
{

}

char* CRoleInfo::GetReason(char *pszStr)
{
    LOG_PROCESS_ERROR(pszStr);
    strxcpy(pszStr, ui.modifyRoleReasonEdit->toPlainText().toUtf8(), COMMON_NAME_LEN);
    if (strlen(pszStr) <= 0)
    {
        QMessageBox::critical(this, "critical", "请填写修改原因!", QMessageBox::Yes);
        return NULL;
    }

    return pszStr;
Exit0:
    return NULL;
}

void CRoleInfo::ReturnPos()
{
    GM_ROLE_SLOT    *pSlot = NULL;

    if (m_bIsModify == FALSE)
        return;

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认修改数据？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    pSlot = (GM_ROLE_SLOT*)(m_SaveList + m_nLength);
    pSlot->wRoleType = GM_ROLE_BASE_DATA;
    pSlot->wBaseDataType = GM_RBD_MAP_ID;

    pSlot->wLength = 0;
    pSlot->wLength += sizeof(GM_ROLE_SLOT);
    m_nLength += pSlot->wLength;

    ui.pushButton->setDisabled(true);

}

void CRoleInfo::EndModify()
{
    INT32       nRetCode = 0;
    UINT32      dwLength = 0;

    if (m_bIsModify == TRUE)
    {
        if (m_nLength != 0)
        {
            nRetCode = CCmdManager::GetInstance().IsCmdExecuting(TRUE);
            LOG_PROCESS_ERROR(nRetCode);

            QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认修改数据并退出修改窗口？"));
            if (nCheckEnum == QMessageBox::Yes)
            {
                nRetCode = CServerMgr::GetInstance().IsSingleSelected();
                LOG_PROCESS_ERROR(nRetCode);

                if (ui.modifyRoleReasonEdit->toPlainText().toUtf8().length() <= 0)
                {
                    QMessageBox::critical(this, "critical", QString::fromLocal8Bit("请填写修改原因!"), QMessageBox::Yes);
                    return;
                }

                if (ui.modifyRoleReasonEdit->toPlainText().toUtf8().length() > GM_REASON_LEN - 1)
                {
                    QMessageBox::critical(this, "critical", QString::fromLocal8Bit("原因过长!"), QMessageBox::Yes);
                    return;
                }

                nRetCode = CCmdManager::GetInstance().ModifyRole(m_dwRoleID, m_dwTargetRoleID, m_nLength, m_SaveList, ui.modifyRoleReasonEdit->toPlainText().toUtf8());
                if (nRetCode == FALSE)
                {
                    QMessageBox::critical(this, "critical", QString::fromLocal8Bit("发送命令失败"), QMessageBox::Yes);
                    return;
                }
            }
            else
            {
                return;
            }
        }
        else
        {
            nRetCode = CMessageHandler::GetInstance().DoReleaseRole(m_dwSessionID, m_dwRoleID);
        }

        GM_ROLE_DATA    *pRole = CDataMgr::GetInstance().FindRole(m_dwRoleID);
        if (pRole != NULL)
            CDataMgr::GetInstance().DeleteRole(pRole);
        
    }

    g_pRoleInfo = NULL;

    done(0);
    
Exit0:
    return;
}

void CRoleInfo::Exit()
{
    INT32       nRetCode = 0;
    UINT32      dwLength = 0;

    if (m_bIsModify == TRUE)
    {
        nRetCode = CMessageHandler::GetInstance().DoReleaseRole(m_dwSessionID, m_dwRoleID);

        GM_ROLE_DATA    *pRole = CDataMgr::GetInstance().FindRole(m_dwRoleID);
        if (pRole != NULL)
            CDataMgr::GetInstance().DeleteRole(pRole);
    }

    g_pRoleInfo = NULL;
    done(0);
}

void CRoleInfo::SetTargetRole()
{
    if (m_bIsModify == FALSE)
        return;

    m_dwTargetRoleID = ui.lineEdit->text().toULong();

    ui.lineEdit->setDisabled(true);

}

void CRoleInfo::DelItem()
{
    GM_ROLE_SLOT    *pSlot = NULL;
    UINT32          *pValue = NULL;

    if (m_bIsModify == FALSE)
        return;

    CMyTreeWidgetItem*pTreeItem = (CMyTreeWidgetItem*)ui.itemWidget->currentItem();
    LOG_PROCESS_ERROR(pTreeItem);

    if (pTreeItem->isDisabled() == TRUE)
        return;

    pSlot = (GM_ROLE_SLOT*)(m_SaveList + m_nLength);
    pSlot->wRoleType = pTreeItem->GetRoleType();
    pValue = (UINT32 *)pSlot->szData;
    *pValue = pTreeItem->GetID();

    pSlot->wLength = sizeof(UINT32);

    pSlot->wLength += sizeof(GM_ROLE_SLOT);
    m_nLength += pSlot->wLength;

    // ui
    pTreeItem->setDisabled(TRUE);

    ui.itemWidget->setItemSelected(pTreeItem, false);

Exit0:
    return;
}

void CRoleInfo::DelQuest()
{
    GM_ROLE_SLOT    *pSlot = NULL;
    UINT32          *pQuestID = NULL;

    if (m_bIsModify == FALSE)
        return;

    CMyTreeWidgetItem*pTreeItem = (CMyTreeWidgetItem*)ui.questWidget->currentItem();
    LOG_PROCESS_ERROR(pTreeItem);

    if (pTreeItem->isDisabled() == TRUE)
        return;

    pSlot = (GM_ROLE_SLOT*)(m_SaveList + m_nLength);
    pSlot->wRoleType = pTreeItem->GetRoleType();

    pQuestID = (UINT32 *)pSlot->szData;
    *pQuestID = pTreeItem->GetID();
    pSlot->wLength = sizeof(UINT32);

    pSlot->wLength += sizeof(GM_ROLE_SLOT);
    m_nLength += pSlot->wLength;

    // ui
    pTreeItem->setDisabled(TRUE);

    ui.questWidget->setItemSelected(pTreeItem, false);

Exit0:
    return;
}

void CRoleInfo::DelMail()
{
    GM_ROLE_SLOT    *pSlot = NULL;
    UINT32          *pMailID = NULL;

    if (m_bIsModify == FALSE)
        return;

    CMyTreeWidgetItem*pTreeItem = (CMyTreeWidgetItem*)ui.mailTreeWidget->currentItem();
    LOG_PROCESS_ERROR(pTreeItem);

    if (pTreeItem->isDisabled() == TRUE)
        return;

    pSlot = (GM_ROLE_SLOT*)(m_SaveList + m_nLength);
    pSlot->wRoleType = pTreeItem->GetRoleType();
    pMailID = (UINT32 *)pSlot->szData;

    *pMailID = pTreeItem->GetID();
    pSlot->wLength = sizeof(UINT32);

    pSlot->wLength += sizeof(GM_ROLE_SLOT);
    m_nLength += pSlot->wLength;

    // ui
    pTreeItem->setDisabled(TRUE);

    ui.mailTreeWidget->setItemSelected(pTreeItem, false);

Exit0:
    return;
}

void CRoleInfo::TakeItem()
{
    GM_ROLE_SLOT            *pSlot = NULL;
    INT32       *pValue = NULL;
    INT64       *pllValue = NULL;

    if (m_bIsModify == FALSE)
        return;

    if (m_dwTargetRoleID == 0)
        return;

    CMyTreeWidgetItem*pTreeItem = (CMyTreeWidgetItem*)ui.itemWidget->currentItem();
    LOG_PROCESS_ERROR(pTreeItem);

    if (pTreeItem->isDisabled() == TRUE)
        return;

    pSlot = (GM_ROLE_SLOT*)(m_SaveList + m_nLength);
    pSlot->wRoleType = GM_ROLE_TAKE_ITEM;

    pValue = (INT32 *)pSlot->szData;
    *pValue = pTreeItem->GetID();

    pllValue = (INT64 *)(pSlot->szData + sizeof(INT32));
    *pllValue = pTreeItem->Get64ID();

    pSlot->wLength = sizeof(INT32);
    pSlot->wLength += sizeof(INT64);
    pSlot->wLength += sizeof(GM_ROLE_SLOT);

    m_nLength += pSlot->wLength;

    // ui
    pTreeItem->setDisabled(TRUE);

    ui.itemWidget->setItemSelected(pTreeItem, false);

Exit0:
    return;
}

void CRoleInfo::timerEvent(QTimerEvent* event)
{
    INT32       nRetCode = 0;

    nRetCode = CGMManager::GetInstance().MainLoop();
    if (!nRetCode)
    {
        nRetCode = CGMManager::GetInstance().UnInit();
        LOG_CHECK_ERROR(nRetCode);
        QMessageBox::critical(this, "critical", "Application error, will exit!", QMessageBox::Yes);
        close();
    }
}

void CRoleInfo::reject()
{
    close();
}

void CRoleInfo::closeEvent(QCloseEvent *event)
{
    Exit();

    return ;
}

void CRoleInfo::BaseDataModify(QTreeWidgetItem * item, int column)
{
    if (m_bIsModify == FALSE)
        return;
    if (column == 0)
    {
        item->setFlags(item->flags() & ~(Qt::ItemIsEditable));
    }
    else if (column == 1)
    {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }
}

void CRoleInfo::BaseDataChanged(QTreeWidgetItem * item, int column)
{
    CMyTreeWidgetItem   *pTreeItem = (CMyTreeWidgetItem*)item;
    if (column != 1)
        return;

    if (m_bIsModify == FALSE)
        return;

    switch (pTreeItem->GetRoleType())
    {
    case GM_ROLE_BASE_DATA:
    {
        GM_ROLE_SLOT    *pSlot = (GM_ROLE_SLOT*)(m_SaveList + m_nLength);
        pSlot->wRoleType = pTreeItem->GetRoleType();
        pSlot->wBaseDataType = pTreeItem->GetBaseDataType();

        switch (pSlot->wBaseDataType)
        {
        case GM_RBD_ID:
        case GM_RBD_NAME:
        case GM_RBD_GROUPID:
        case GM_RBD_DELETETIME:
        case GM_RBD_LAST_LOGOUT_TIME:
        case GM_RBD_FORBIDDEND_CHAT_TIME:
        case GM_RBD_FREEZE_ROLE_TIME:
        case GM_RBD_FREEZE_CHEAT_ROLE:
        case GM_RBD_CLASS:
        case GM_RBD_SEX:
            break;
        case GM_RBD_LEVEL:
        {
            INT32 * pLevel = (INT32*)pSlot->szData;
            *pLevel = pTreeItem->text(column).toInt();
            pSlot->wLength = sizeof(INT32);
        }
            break;
        case GM_RBD_EXP:
        {
            UINT32 * pExp = (UINT32*)pSlot->szData;
            *pExp = pTreeItem->text(column).toUInt();
            pSlot->wLength = sizeof(UINT32);
        }
            break;
        case GM_RBD_PKVALUE:
        {
            UINT32 * pPKValue = (UINT32*)pSlot->szData;
            *pPKValue = pTreeItem->text(column).toUInt();
            pSlot->wLength = sizeof(UINT32);
        }
            break;
        case GM_RBD_GMLEVEL:
        {
            INT32 * pGMLevel = (INT32*)pSlot->szData;
            *pGMLevel = pTreeItem->text(column).toInt();
            pSlot->wLength = sizeof(INT32);
        }
            break;
        case GM_RBD_MAP_ID:
        case GM_RBD_X:
        case GM_RBD_Y:
        case GM_RBD_Z:
            break;
        case GM_RBD_MONEY_1:
            break;
        case GM_RBD_MONEY_2:
        case GM_RBD_MONEY_3:
        case GM_RBD_MONEY_4:
        case GM_RBD_MONEY_5:
        case GM_RBD_MONEY_6:
        case GM_RBD_MONEY_7:
        case GM_RBD_MONEY_8:
        case GM_RBD_MONEY_9:
        case GM_RBD_MONEY_10:
        case GM_RBD_MONEY_11:
        case GM_RBD_MONEY_12:
        case GM_RBD_MONEY_13:
        case GM_RBD_MONEY_14:
        {
            INT32 * pMoney = (INT32*)pSlot->szData;
            *pMoney = pTreeItem->text(column).toInt();
            pSlot->wLength = sizeof(INT32);
        }
            break;
        default:
            break;
        }
        pSlot->wLength += sizeof(GM_ROLE_SLOT);

        m_nLength += pSlot->wLength;
    }
        break;
    case GM_ROLE_TITLE:
    case GM_ROLE_SPELL:
    case GM_ROLE_ITEM:
    case GM_ROLE_QUEST:
    case GM_ROLE_MAIL:
    default:
        LOG_PROCESS_ERROR(FALSE);
        break;
    }

Exit0:
    return;
}

void CRoleInfo::ShowItemInfo(QTreeWidgetItem * item, int column)
{
    GM_ITEM_MAP::iterator iter;
    CMyTreeWidgetItem   *pTreeItem = (CMyTreeWidgetItem*)item;
    LOG_PROCESS_ERROR(pTreeItem);

    iter = m_ItemMap.find(pTreeItem->Get64ID());
    LOG_PROCESS_ERROR(iter != m_ItemMap.end());

    INT32   nLength = 0;
    const   INT32 BUFFER_LENGTH = 1024 * 20;
    char    *pBuffer = new char[BUFFER_LENGTH];
    LOG_PROCESS_ERROR(pBuffer);

    memset(pBuffer, 0, BUFFER_LENGTH);

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "物品类型ID", iter->second.dwItemID);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%llu\n", "物品ID", iter->second.qwGuid);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "包裹", iter->second.wConSlot);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "包裹位置", iter->second.wItemSlot);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "道具类型", iter->second.nType);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "道具子类型", iter->second.nSubType);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "数量", iter->second.nNum);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "绑定类型", iter->second.byBindType);

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "鉴定类型", iter->second.byIdentified);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "随机属性1", iter->second.wRandomAttrID[0]);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "随机属性2", iter->second.wRandomAttrID[1]);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "随机属性3", iter->second.wRandomAttrID[2]);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "随机属性4", iter->second.wRandomAttrID[3]);

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "签名", iter->second.dwRoleID);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "已消费金币", iter->second.dwCostMoney);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%d\n", "幸运值", iter->second.byLuck);

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "武器升级次数", iter->second.byLevelupTimes);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "武器升级物理点数", iter->second.byLevelupPhyPoint);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "武器升级魔法点数", iter->second.byLevelupMagPoint);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "武器升级道术点数", iter->second.byLevelupTaoPoint);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "武器隐藏类型", iter->second.byLevelupTypeHidden);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "武器隐藏点数", iter->second.byLevelupPointHidden);

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "铸魂1", iter->second.wRune[0]);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "铸魂2", iter->second.wRune[1]);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "铸魂3", iter->second.wRune[2]);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "铸魂4", iter->second.wRune[3]);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "铸魂5", iter->second.wRune[4]);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "铸魂6", iter->second.wRune[5]);

    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%u\n", "插槽类型", iter->second.dwSocketCombination);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%d\n", "宝石ID1", iter->second.nSoulID[0]);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%d\n", "宝石ID2", iter->second.nSoulID[1]);
    nLength += snprintf(pBuffer + nLength, BUFFER_LENGTH - nLength, "%s\t%d\n", "宝石ID3", iter->second.nSoulID[2]);


    CGMItemInfo *pItemInfo = new CGMItemInfo(this);

    LOG_PROCESS_ERROR(pItemInfo);

    pItemInfo->ShowInfo(pBuffer, FALSE);

    pItemInfo->show();   

Exit0:
    if (pBuffer)
    {
        delete[] pBuffer;
    }
    
    return;
}

void CRoleInfo::_UpdateBaseData(GM_ROLE_SLOT *pSlot)
{
    LOG_PROCESS_ERROR(pSlot);

    switch (pSlot->wBaseDataType)
    {
    case GM_RBD_ID:
    {
        CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;

        pTreeItem->SetRoleType(pSlot->wRoleType);
        pTreeItem->SetBaseDataType(pSlot->wBaseDataType);
        pTreeItem->setText(0, QString::fromLocal8Bit(GetBaseDataName(pSlot->wBaseDataType)));
        pTreeItem->setText(1, QString::number(*(UINT32*)(pSlot->szData)));
        pTreeItem->setDisabled(true);
        ui.baseDataTreeWidget->addTopLevelItem(pTreeItem);
    }
        break;
    case GM_RBD_PKVALUE:
    {
        CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;

        pTreeItem->SetRoleType(pSlot->wRoleType);
        pTreeItem->SetBaseDataType(pSlot->wBaseDataType);
        pTreeItem->setText(0, QString::fromLocal8Bit(GetBaseDataName(pSlot->wBaseDataType)));
        pTreeItem->setText(1, QString::number(*(UINT32*)(pSlot->szData)));
        ui.baseDataTreeWidget->addTopLevelItem(pTreeItem);
    }
        break;
    case GM_RBD_GMLEVEL:
    {
        CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;

        pTreeItem->SetRoleType(pSlot->wRoleType);
        pTreeItem->SetBaseDataType(pSlot->wBaseDataType);
        pTreeItem->setText(0, QString::fromLocal8Bit(GetBaseDataName(pSlot->wBaseDataType)));
        pTreeItem->setText(1, QString::number(*(INT32*)(pSlot->szData)));
        ui.baseDataTreeWidget->addTopLevelItem(pTreeItem);
    }
        break;
    case GM_RBD_DELETETIME:
    {
        CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;
        UINT32      dwDeleteTime = 0;

        pTreeItem->SetRoleType(pSlot->wRoleType);
        pTreeItem->SetBaseDataType(pSlot->wBaseDataType);

        dwDeleteTime = *(UINT32*)(pSlot->szData);

        QTimeZone   qtz(28800);

        QDateTime   qdt;
        qdt.setTime_t(dwDeleteTime);
        qdt.setTimeZone(qtz);

        pTreeItem->setText(0, QString::fromLocal8Bit(GetBaseDataName(pSlot->wBaseDataType)));
        if (dwDeleteTime > 0)
            pTreeItem->setText(1, qdt.toString("yyyy-MM-dd hh:mm:ss"));
        else
            pTreeItem->setText(1, "0");
        pTreeItem->setDisabled(true);
        ui.baseDataTreeWidget->addTopLevelItem(pTreeItem);
    }
        break;
    case GM_RBD_LAST_LOGOUT_TIME:
    case GM_RBD_FORBIDDEND_CHAT_TIME:
    case GM_RBD_FREEZE_ROLE_TIME:
    case GM_RBD_FREEZE_CHEAT_ROLE:
    {
        CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;

        pTreeItem->SetRoleType(pSlot->wRoleType);
        pTreeItem->SetBaseDataType(pSlot->wBaseDataType);

        pTreeItem->setText(0, QString::fromLocal8Bit(GetBaseDataName(pSlot->wBaseDataType)));
        pTreeItem->setText(1, pSlot->szData);
        pTreeItem->setDisabled(true);
        ui.baseDataTreeWidget->addTopLevelItem(pTreeItem);
    }
        break;
    case GM_RBD_NAME:
    {
        CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;

        pTreeItem->SetRoleType(pSlot->wRoleType);
        pTreeItem->SetBaseDataType(pSlot->wBaseDataType);
        pTreeItem->setText(0, QString::fromLocal8Bit(GetBaseDataName(pSlot->wBaseDataType)));
        pTreeItem->setText(1, QString::fromUtf8(pSlot->szData));
        pTreeItem->setDisabled(true);
        ui.baseDataTreeWidget->addTopLevelItem(pTreeItem);
    }
        break;
    case GM_RBD_GROUPID:
    case GM_RBD_CLASS:
    case GM_RBD_SEX:
    case GM_RBD_LEVEL:
    case GM_RBD_EXP:
    case GM_RBD_MAP_ID:
    {
        CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;

        pTreeItem->SetRoleType(pSlot->wRoleType);
        pTreeItem->SetBaseDataType(pSlot->wBaseDataType);
        pTreeItem->setText(0, QString::fromLocal8Bit(GetBaseDataName(pSlot->wBaseDataType)));
        pTreeItem->setText(1, QString::number(*(INT32*)(pSlot->szData)));
        ui.baseDataTreeWidget->addTopLevelItem(pTreeItem);
    }
        break;
    case GM_RBD_MONEY_1:
        {
            CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;

            pTreeItem->SetRoleType(pSlot->wRoleType);
            pTreeItem->SetBaseDataType(pSlot->wBaseDataType);
            pTreeItem->setText(0, QString::fromLocal8Bit(GetBaseDataName(pSlot->wBaseDataType)));
            pTreeItem->setText(1, QString::number(*(INT32*)(pSlot->szData)));
            pTreeItem->setDisabled(true);
            ui.baseDataTreeWidget->addTopLevelItem(pTreeItem);
        }
        break;
    case GM_RBD_MAP_SERIAL_ID:
    case GM_RBD_MONEY_2:
    case GM_RBD_MONEY_3:
    case GM_RBD_MONEY_4:
    case GM_RBD_MONEY_5:
    case GM_RBD_MONEY_6:
    case GM_RBD_MONEY_7:
    case GM_RBD_MONEY_8:
    case GM_RBD_MONEY_9:
    case GM_RBD_MONEY_10:
    case GM_RBD_MONEY_11:
    case GM_RBD_MONEY_12:
    case GM_RBD_MONEY_13:
    case GM_RBD_MONEY_14:
    {
        CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;

        pTreeItem->SetRoleType(pSlot->wRoleType);
        pTreeItem->SetBaseDataType(pSlot->wBaseDataType);
        pTreeItem->setText(0, QString::fromLocal8Bit(GetBaseDataName(pSlot->wBaseDataType)));
        pTreeItem->setText(1, QString::number(*(INT32*)(pSlot->szData)));
        ui.baseDataTreeWidget->addTopLevelItem(pTreeItem);
    }
        break;
    case GM_RBD_X:
    case GM_RBD_Y:
    case GM_RBD_Z:
        break;

        default:
            break;
    }

Exit0:
    return ;
}

void CRoleInfo::_Update()
{
    INT32           nRoleType = GM_ROLE_NONE;
    INT32           nBaseDataType = GM_RBD_NONE;

    char            szKey[128] = { 0 };
    char            szValue[256] = { 0 };
    char            szNum[32] = { 0 };

    UINT32          dwQuestID = 0;


    GM_ROLE_DATA    *pRole = CDataMgr::GetInstance().FindRole(m_dwRoleID);
    if (!pRole)
        return;

    ui.baseDataTreeWidget->clear();
    ui.questWidget->clear();
    ui.itemWidget->clear();
    ui.mailTreeWidget->clear();

    for (INT32 i = 0; i < pRole->nLength;)
    {
        GM_ROLE_SLOT   *pData = (GM_ROLE_SLOT*)(pRole->szData + i);

        switch (pData->wRoleType)
        {
        case GM_ROLE_BASE_DATA:
        {
            _UpdateBaseData(pData);
        }
            break;
        case GM_ROLE_SPELL:
        {
            GM_ROLE_SPELL_SLOT  *pSpellSlot = (GM_ROLE_SPELL_SLOT*)pData->szData;
            CMyTreeWidgetItem   *pTreeItem = new CMyTreeWidgetItem;

            pTreeItem->SetRoleType(pData->wRoleType);
            pTreeItem->SetID(pSpellSlot->nSpellID);
            pTreeItem->Set64ID(pSpellSlot->nRuneID);

            pTreeItem->setText(0, QString::fromUtf8(pSpellSlot->szName));
            if (pSpellSlot->nEquipedIndex >= qssActiveBegin)
            {
                memset(szNum, 0, sizeof(szNum));
                pTreeItem->setText(1, QString::fromLocal8Bit(gm_itoa(pSpellSlot->nEquipedIndex - qssActiveBegin + 1, szNum)));
            }

            ui.spellTreeWidget->addTopLevelItem(pTreeItem);
        }
            break;
        case GM_ROLE_TITLE:
        {
            GM_ROLE_TITLE_SLOT  *pTitleSlot = (GM_ROLE_TITLE_SLOT*)pData->szData;
            CMyTreeWidgetItem   *pTreeItem = new CMyTreeWidgetItem;

            pTreeItem->SetRoleType(pData->wRoleType);
            pTreeItem->SetID(pTitleSlot->nTemplateID);
            
            pTreeItem->setText(0, QString::fromUtf8(pTitleSlot->szName));
            memset(szNum, 0, sizeof(szNum));
            pTreeItem->setText(1, QString::fromLocal8Bit(gm_itoa(pTitleSlot->dwExpireTime, szNum)));
            
            ui.titleTreeWidget->addTopLevelItem(pTreeItem);
        }
            break;
        case GM_ROLE_ITEM:
        {
            GM_ROLE_ITEM_SLOT   *pItemSlot = (GM_ROLE_ITEM_SLOT*)pData->szData;

            CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;

            pTreeItem->SetRoleType(pData->wRoleType);
            pTreeItem->Set64ID(pItemSlot->qwGuid);
            pTreeItem->SetID( (((UINT32)pItemSlot->wConSlot) << 16) + pItemSlot->wItemSlot);

            memset(szNum, 0, sizeof(szNum));
            pTreeItem->setText(0, QString::fromLocal8Bit(gm_itoa(pItemSlot->dwItemID, szNum)));
            memset(szNum, 0, sizeof(szNum));
            pTreeItem->setText(1, QString::fromLocal8Bit(gm_itoa64(pItemSlot->qwGuid, szNum)));
            pTreeItem->setText(2, QString::fromUtf8(pItemSlot->szData));
            pTreeItem->setText(3, QString::fromLocal8Bit(GetItemContainerString(pItemSlot->wConSlot)));
            pTreeItem->setText(4, QString::fromLocal8Bit(GetItemTypeString(pItemSlot->nType)));
            memset(szNum, 0, sizeof(szNum));
            pTreeItem->setText(5, QString::fromLocal8Bit(gm_itoa64(pItemSlot->nNum, szNum)));

            ui.itemWidget->addTopLevelItem(pTreeItem);

            m_ItemMap.insert(std::make_pair(pItemSlot->qwGuid, *pItemSlot));
        }
            break;
        case GM_ROLE_QUEST:
        {
            CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;
            
            dwQuestID = *((UINT32*)pData->szData);

            pTreeItem->SetRoleType(pData->wRoleType);
            pTreeItem->SetID(dwQuestID);

            memset(szNum, 0, sizeof(szNum));
            pTreeItem->setText(0, QString::fromLocal8Bit(gm_itoa(dwQuestID, szNum)));
            pTreeItem->setText(1, QString::fromUtf8(pData->szData + sizeof(UINT32)));

            ui.questWidget->addTopLevelItem(pTreeItem);
        }
            break;
        case GM_ROLE_MAIL:
        {
            CMyTreeWidgetItem *pTreeItem = new CMyTreeWidgetItem;
            GM_ROLE_MAIL_SLOT *pMailSlot = (GM_ROLE_MAIL_SLOT*)pData->szData;  

            pTreeItem->SetRoleType(pData->wRoleType);
            pTreeItem->SetID(pMailSlot->dwMailID);

            pTreeItem->setText(0, QString::fromUtf8(pMailSlot->szData));
            pTreeItem->setText(1, QString::fromLocal8Bit(cszMailTypeName[pMailSlot->nMailType]));
            pTreeItem->setText(2, QString::fromLocal8Bit(cszMailIsNewName[pMailSlot->nState]));

            pTreeItem->setText(3, QString::fromLocal8Bit(GetMailAttachType(pMailSlot->nAttachType)));

            if (pMailSlot->nAttachType != 0)
            {
                QString n;
                pTreeItem->setText(4, n.setNum(pMailSlot->nItemID));
                pTreeItem->setText(5, n.setNum(pMailSlot->nItemCount));
            }

            ui.mailTreeWidget->addTopLevelItem(pTreeItem);
        }
            break;
        default:
            break;
        }
        
        i += pData->wLength;
    }

    if (m_bIsModify == FALSE)
    {
        ui.delQuestButton->setDisabled(true);
        ui.delItemButton->setDisabled(true);
        ui.delMailButton->setDisabled(true);
        ui.pushButton->setDisabled(true);
    }

    return;
}




