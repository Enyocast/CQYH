/********************************************************************
	created:	25:12:2013   16:12
	file:		role_info.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/



#ifndef _H_ROLE_INFO_H_
#define _H_ROLE_INFO_H_


#include <QtWidgets/QMainWindow>
#include <QCloseEvent>
#include <QtWidgets/QLabel>
#include "ui_role_info.h"
#include "gm_def.h"



class CItemTreeWidgetItem;
struct GM_ROLE_SLOT;

class CRoleInfo : public QDialog
{
    Q_OBJECT

public:
    CRoleInfo(UINT32 dwSessionID, UINT32 dwRoleID, BOOL bIsModify = FALSE, QWidget *parent = 0, Qt::WindowFlags flags = 0);

    ~CRoleInfo();

    virtual void timerEvent(QTimerEvent* event);

    void reject();

    char *GetReason(char *pszStr);



protected:
    void _Update();
    void _UpdateBaseData(GM_ROLE_SLOT *pSlot);

public slots:
    //void AddItem();

    void SetTargetRole();
    
    void DelItem();
    void DelQuest();
    void DelMail();
    void TakeItem();

    void ReturnPos();
    void EndModify();
    void Exit();

    void closeEvent(QCloseEvent *event);

    void BaseDataModify(QTreeWidgetItem * item, int column);
    void BaseDataChanged(QTreeWidgetItem * item, int column);

    void ShowItemInfo(QTreeWidgetItem * item, int column);


private:
#define MAX_ROLE_DISPLAY_ATTR_NUM   (26)
    int         m_nTimeID;
    //UINT32      m_dwSvrID;
    UINT32      m_dwRoleID;
    UINT32      m_dwTargetRoleID;

    QLabel      *m_pLabel[MAX_ROLE_DISPLAY_ATTR_NUM];
    QLineEdit   *m_pLineEdit[MAX_ROLE_DISPLAY_ATTR_NUM];


    Ui::RoleInfoDialog ui;

    BOOL        m_bIsModify;
    UINT32      m_dwSessionID;

    INT32       m_nLength;
    char        m_SaveList[1024 * 32];


    typedef std::map<UINT64, GM_ROLE_ITEM_SLOT> GM_ITEM_MAP;
    GM_ITEM_MAP     m_ItemMap;
};


extern CRoleInfo   *g_pRoleInfo;


#endif //_H_ROLE_INFO_H_












