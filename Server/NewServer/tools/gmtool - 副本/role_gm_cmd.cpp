#include "stdafx.h"
#include "role_gm_cmd.h"
#include <QtWidgets/QMessageBox>
#include "gm_manager.h"

CRoleGMCmd::CRoleGMCmd(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    ui.setupUi(this);

    memset(m_Buffer, 0, sizeof(m_Buffer));
    memset(m_Reason, 0, sizeof(m_Reason));
    m_bExe = FALSE;

    connect(ui.okButton, SIGNAL(clicked()), this, SLOT(OK()));
    connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(Exit()));



}

CRoleGMCmd::~CRoleGMCmd()
{

}


void CRoleGMCmd::OK()
{
    INT32       nRetCode = 0;

    QMessageBox::StandardButton  nCheckEnum = QMessageBox::question(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("确认执行该GM指令？"));
    if (nCheckEnum != QMessageBox::Yes)
        return;

    if (ui.textEdit->toPlainText().toUtf8().length() < 2 || ui.textEdit_2->toPlainText().toUtf8().length() < 2)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("内容不能为空!"));
        return;
    }

    if (ui.textEdit_2->toPlainText().toUtf8().length() > GM_REASON_LEN - 1)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("原因过长!"));
        return;
    }

    strncpy(m_Buffer, ui.textEdit->toPlainText().toUtf8(), sizeof(m_Buffer) - 1);
    strncpy(m_Reason, ui.textEdit_2->toPlainText().toUtf8(), sizeof(m_Reason) - 1);

    //m_Buffer[sizeof(m_Buffer) - 1] = '\0';

    m_bExe = TRUE;

    done(0);
}

void CRoleGMCmd::Exit()
{
    done(0);
}


void CRoleGMCmd::timerEvent(QTimerEvent* event)
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



