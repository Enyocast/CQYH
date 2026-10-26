/********************************************************************
created:	7:29:2014   10:22
file:		role_gm_cmd.h
author:		Allan Tao

purpose:
*********************************************************************/

#ifndef _H_ROLE_GM_CMD_H_
#define _H_ROLE_GM_CMD_H_


#include <QtWidgets/QMainWindow>
#include "ui_role_gm_cmd.h"
#include "string_def.h"

class CRoleGMCmd : public QDialog
{
    Q_OBJECT

public:
    CRoleGMCmd(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CRoleGMCmd();

    char *GetBuffer()   { return m_Buffer; }
    char *GetReason()   { return m_Reason; }
    BOOL IsExeCmd()     { return m_bExe; }

    virtual void timerEvent(QTimerEvent* event);

public slots:
void OK();
void Exit();


private:

    char    m_Buffer[MAX_GM_COMMAND_LEN];
    char    m_Reason[GM_REASON_LEN];
    BOOL    m_bExe;

    Ui::roleGMDialog ui;
};




#endif //_H_ROLE_GM_CMD_H_

