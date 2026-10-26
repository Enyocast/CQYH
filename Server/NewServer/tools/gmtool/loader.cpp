#include "stdafx.h"
#include "loader.h"

//#include <QInputDialog>
//#include <QMainWindow>
#include <QtWidgets/QMessageBox>
#include "tl_config.h"
#include "gm_manager.h"
#include "session_mgr.h"
#include "message_handler.h"
#include "cmd_manager.h"

#include "gmtool.h"
#include "server_list.h"
#include "gm_version.h"
#include "logic.h"

loader  g_loader;

loader::loader(QWidget *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
    ui.setupUi(this);

    connect(ui.loginButton, SIGNAL(clicked()), this, SLOT(Login()));
    connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(Exit()));

    ui.label_3->hide();

    ui.userNameEdit->setFocus();


    char        szNum[32] = { 0 };
    char        szSubVersion[32] = { 0 };

    setWindowTitle(QString::fromLocal8Bit("GM工具: ") + QString::fromLocal8Bit("    版本号: ") + QString::fromLocal8Bit(gm_itoa(GM_MAJOR_VERSION, szNum))
        + QString::fromLocal8Bit("---") + QString::fromLocal8Bit(gm_itoa(GM_MINOR_VERSION, szSubVersion)));

    //m_nTimeID = startTimer(125);
    //assert(m_nTimeID != 0);
}

loader::~loader()
{

}

//void loader::timerEvent(QTimerEvent* event)
//{
//    if ( GM_SVR_STATE_LOGIN_SUCC == CSvrManager::GetInstance().GetGMState() )
//    {
//        killTimer(m_nTimeID);
//        accept();
//    }
//}

void loader::Login()
{
    QString nameString = ui.userNameEdit->text();
    QString pwdString = ui.userPwdEdit->text();
    INT32   nRetCode = 0;
    //CMD_DATA    *pCmdData = NULL;

    CGMManager::GetInstance().SetUserName(nameString.toUtf8());
    CGMManager::GetInstance().SetUserPwd(pwdString.toUtf8());

    for (UINT32 dwSessionID = 0; dwSessionID < MAX_GM_SESSION_COUNT; ++dwSessionID)
    {
        GM_SESSION *pGMSession = CSessionMgr::GetInstance().GetGMSession(dwSessionID);
        if (pGMSession && pGMSession->dwType == stGM && pGMSession->nConnectState == SESSION_CONNECTED)
        {
            nRetCode = CMessageHandler::GetInstance().DoVerify(pGMSession->dwSessionID, CGMManager::GetInstance().GetUserName(), CGMManager::GetInstance().GetUserPwd());
            LOG_PROCESS_ERROR(nRetCode);

            PROCESS_SUCCESS(TRUE);
        }
    }

    LOG_PROCESS_ERROR(FALSE);

Exit1:
    ui.label_3->show();
    return ;
Exit0:
    QMessageBox::critical(this, "critical", QString::fromLocal8Bit("没有服务器启动中，不能完成登录"), QMessageBox::Yes);
    return ;
}

void loader::Exit()
{
    done(0);
}

BOOL loader::VerifyUser(INT32 nResult, BOOL bLD)
{
    if (errSuccess == nResult)
    {
        accept();

        if (bLD == TRUE)
            g_gmtool.SetLDMode();

        g_gmtool.show();
    }

    return TRUE;
}









