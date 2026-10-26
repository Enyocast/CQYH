#ifndef MAINTAINTOOL_H
#define MAINTAINTOOL_H
#include "stdafx.h"

#include <QtWidgets/QMainWindow>
#include "ui_maintaintool.h"

#include "mt_config.h"
#include "string_ex.h"
#include "server_def.h"

#include <list>
static const UINT32 G_FILE_SEND_BLOCK = 32*1024;

enum E_MT_CONNECT_STATE
{
	emctUnConnect = 0,
	emctConnecting,
	emctConnected,
	emctNormal,
	emctTotal
};

struct SRemoteGuardSession;
struct stProcessStatisInfo;
struct stStatisProcess;
struct SProcessInfo;

class MaintainTool : public QMainWindow
{
	Q_OBJECT

public:
	static MaintainTool& GetInstance(void);
	BOOL Cleanup(void);

	virtual void timerEvent(QTimerEvent* event);
	static void LogOutput(INT32 eLogLevel, const char* pcszMessage, INT32 nMessageSize);

	BOOL SetAreaVersion(INT32 nAreaID, const char* pcszVersion);
	BOOL DeployVersionResultByIp(INT32 nAreaID, UINT32 dwIp, const char* pcszVersion, INT32 nErrorCode);
	BOOL HotUpdatePatchResultByIp(INT32 nAreaID, UINT32 dwIp, const char* pcszVersion, INT32 nErrorCode);
public:
	MaintainTool(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~MaintainTool();

	BOOL Init();
	BOOL UnInit();

    BOOL CheckAreaExpanded(INT32 nIndex);
	//BOOL GetAreaIpList(UINT32 dwAreaID, UINT32& nMaxCount, UINT32* dwIplst);

	BOOL UpdateGuardConnectInfo(SRemoteGuardSession* pGuardSession, INT32 nState, UINT8* pCountArray);
	BOOL UpdateGuardSendProgress(INT32 nAreaID, UINT32 dwIp, INT32 nPercent);

	BOOL AddGuardProcessesInfobyIp(INT32 nAreaID, UINT32 dwIp);
	BOOL UpdateGuardProcessesInfo();

	BOOL UpdateGuardStatisInfoByIp(INT32 nAreaID, UINT32 dwIp, UINT32 dwPID);
	BOOL UpdateGuardStatisInfo(UINT32 dwAreaID, UINT32 dwIP);
	BOOL SnapShootGuardStatisInfoByIp(INT32 nAreaID, UINT32 dwIp, UINT32 dwPID, char* pszOutStr);
	BOOL SnapShootGuardStatisInfo();
	BOOL SnapShootGuardStatisInfoCurrentByIp(INT32 nAreaID, UINT32 dwIp, UINT32 dwPID, char* pszOutStr);
	BOOL SnapShootGuardStatisInfoCurrent();
	BOOL BeginHibernateGuardStatisInfoByIp(INT32 nAreaID, UINT32 dwIp, UINT32 dwPID, UINT8 byType, UINT32 dwSessionID);
	BOOL ProcessHibernateGuardStatisInfoByIp(stStatisProcess* pStatisInfo, SProcessInfo* poInfo);
	BOOL EndHibernateGuardStatisInfoByIp();
	BOOL HibernateGuardStatisInfo();
    BOOL InitGuardStatisInfo(void);

	BOOL ExecCmd(const char* pcszCmd);
	BOOL UpdateCmdResult(UINT32 dwRemoteIP, INT32 nErrorCode, const char* szResult);
	BOOL UpdateNotifyInfo(UINT32 dwRemoteIP, UINT8 bySvrType, UINT8 bySvrID, UINT8 byLevel, INT32 nErrorCode, const char* szResult);
	BOOL UpdateNotifyInfo(QString str);


	const char* GetUserName(){return m_szUserName;}
	const char* GetPassword(){return m_szPassword;}

	BOOL GetSelectVersion(char* pName);
	BOOL GetSelectPatch(char* pName);
	QList<QTreeWidgetItem*> GetSelectedIpItems(BOOL bSameParent = FALSE);

    BOOL RefreshCanvas(void);

private:
	Ui::MaintainToolClass ui;

	char	            m_szUserName[32];
	char	            m_szPassword[32];
	BOOL	            m_bLogin;

	char	            m_szCurCmd[64];
	INT32	            m_nWaitCmdCount;
	BOOL	            m_bCmdResult;
	char	            m_szVersionPath[256];
	char	            m_szPatchPath[256];
    QGraphicsScene*     m_pGraphicsScene;

	static MaintainTool MaintainTool::ms_Instance;

private:
	BOOL _ReloadAreaConfig();

	BOOL _RefreshAreaInfo();
	BOOL _RefreshServerVersion();
	BOOL _RefreshServerPatch();

	BOOL _CheckGuardStateByIp(INT32 nAreaID, UINT32 dwIp);
	QTreeWidgetItem* _GetGuardWidget(INT32 nAreaID, UINT32 dwIp);
	QTreeWidgetItem* _GetAreaWidget(INT32 nAreaID);
	BOOL _HasUpdatedWholeArea(INT32 nAreaID, UINT32 dwIp, const char* pcszVersion);
    void _UpdateMonitor(QGraphicsScene* pGraphicsScene, stProcessStatisInfo* poInfo, INT32 nProcessIndex, INT32 nStatisIndex);

public slots:
	void Login(void);
	void Logout(void);
	void SnapShoot(void);
	void Hibernate(void);

	void OnAreaTreeClick(QTreeWidgetItem *, int);
	void OnStatisInfoItemDoubleClicked(QTreeWidgetItem * item, int column);
	void OnAreaItemDoubleClicked(QTreeWidgetItem *, int);
	void OnVesionWidgetDoubleClicked(const QModelIndex &);
	void OnPatchWidgetDoubleClicked(const QModelIndex &);
	void OnLogDoubleClicked(QListWidgetItem *);

	void Start(void);
	void Open(void);
	void Stop(void);
	void Close(void);
	void ExecuteCmd(void);

	void VersionRefresh(void);

	BOOL _GenerateGMSecurityFile(const char* szSrcPath, const char* szDstPath);
	void SendConfig(void);

	void SendVersion(void);
    void DeployVersion(void);

	void SendPatch(void);
	void HotUpdatePatch(void);

	void CleanLog(void);
	void LogFilter(const QString& text);

	void CleanAlert(void);
	void AlertFilter(const QString& text);

};

#endif // MAINTAINTOOL_H
