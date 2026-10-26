/********************************************************************
	created:	21:12:2013   22:22
	file:		executing.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#include "stdafx.h"
#include "executing.h"

//#include <QInputDialog>
//#include <QMainWindow>
#include <QtWidgets/QMessageBox>
//#include <qtablewidget.h>

//#include "session_mgr.h"
#include "cmd_manager.h"
//#include "svr_manager.h"

CExecuting::CExecuting(QWidget *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
    ui.setupUi(this);

    m_nTimeID = startTimer(500);
    //assert(m_nTimeID != 0);
}

CExecuting::~CExecuting()
{

}


void CExecuting::timerEvent(QTimerEvent* event)
{
    INT32       nRetCode = 0;

    //CMD_DATA_BASE    *pCmd = CCmdManager::GetInstance().GetCurrentCmd();
    //LOG_CHECK_ERROR(pCmd);

    //if (pCmd && CCmdManager::GetInstance().IsCompleteAll())
    {
        killTimer(m_nTimeID);

        //CResult     res;
        //res.exec();

        //CCmdManager::GetInstance().EndCmd();

        accept();
    }   

Exit0:
    return;
}










