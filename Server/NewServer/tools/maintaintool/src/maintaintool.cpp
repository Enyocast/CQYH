#include "stdafx.h"
#include "maintaintool.h"
#include "net.h"
#include "dir.h"
#include "ifile.h"
#include "math_ex.h"
#include "time_ex.h"
#include "server_def.h"
#include "process_option.h"
#include "session_mgr.h"
#include "message_handler.h"
#include "statis_info.h"
#include "mt_config.h"
#include "transmit_file_mgr.h"
#include "maintain_tool_version.h"

#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qtreewidget.h>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QDialogButtonBox>
#include <QProcess>
#include <QDir>

#include <string>
//#include "sdfile.h"
//#include "sddir.h"
//using namespace SGDP;

extern INet* g_pNet;

char* g_szStatFieldName[statTotal] = {
    "",
    "MemUsage",
    "CpuUsage",
    "InternalPacketIncome",
    "InternalPacketOutgoing",
    "InternalNetflowIncome",
    "InternalNetflowOutgoing",
    "ExternalPacketIncome",
    "ExternalPacketOutgoing",
    "ExternalNetflowIncome",
    "ExternalNetflowOutgoing",
    "FindPathCount",
    "FindPathSamePolyReturnCount",
    "FindPathNormalReturnCount",
    "IsObstacledCount",
    "RoleCount",
    "NpcCount",
    "DoodadCount",
    "MissileCount",
    "SceneCount",
    "DropCount",
    "ItemCount",
};

#define MAX_MONITOR_COUNT   (9)

struct MONITOR_DATA
{
    QGraphicsView*  pGraphicsView;
    QGraphicsScene* pGraphicsScene;
    QLabel*         pLabel;
    UINT32          dwIp;
    UINT32          dwProcess;
    INT32           nIndex;
};

MONITOR_DATA    g_MonitorList[MAX_MONITOR_COUNT] = {0};
INT32           g_nLastSetMonitor = 0;

static const char* g_pcszConStr[emctTotal] = {
	"unconnect",
	"connecting",
	"connected",
	"normal",
};

enum enumAreaTextColumnIndex
{
	enumAreaTextColumnName = 0,
	enumAreaTextColumnAddress = 1,
	enumAreaTextColumnState,
	enumAreaTextColumnConfig,
	enumAreaTextColumnProgress,
};

enum enumDataUserRoleIndex
{
	enumDataUserRoleAreaID = 0,
	enumDataUserRoleVersion,
	enumDataUserRoleAreaName,
	enumDataUserRoleIP,
	enumDataUserRolePID,
	enumDataUserRoleType,
	enumDataUserRoleSessionID,
};

enum enumProcessTextColumnIndex
{
	enumProcessTextColumnPID = 0,
	enumProcessTextColumnType,
	enumProcessTextColumnState,
	enumProcessTextColumnMode,
};

QApplication app(__argc, __argv);
MaintainTool MaintainTool::ms_Instance;

//MaintainTool//
//*******************************************************************
MaintainTool::MaintainTool(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	startTimer(100);
	ui.setupUi(this);
	setWindowTitle(QString("MaintainTool msg %1 ver %2").arg(MAINTAIN_TOOLS_MSG_VERSION).arg(MAINTAIN_TOOLS_BUILD_VERSION));

    m_pGraphicsScene = new QGraphicsScene;
    ui.graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    ui.graphicsView->setInteractive(false);
    ui.graphicsView->setScene(m_pGraphicsScene);

    g_MonitorList[0].pGraphicsView = ui.monitor_1;
    g_MonitorList[1].pGraphicsView = ui.monitor_2;
    g_MonitorList[2].pGraphicsView = ui.monitor_3;
    g_MonitorList[3].pGraphicsView = ui.monitor_4;
    g_MonitorList[4].pGraphicsView = ui.monitor_5;
    g_MonitorList[5].pGraphicsView = ui.monitor_6;
    g_MonitorList[6].pGraphicsView = ui.monitor_7;
    g_MonitorList[7].pGraphicsView = ui.monitor_8;
    g_MonitorList[8].pGraphicsView = ui.monitor_9;

    g_MonitorList[0].pLabel = ui.label_1;
    g_MonitorList[1].pLabel = ui.label_2;
    g_MonitorList[2].pLabel = ui.label_3;
    g_MonitorList[3].pLabel = ui.label_4;
    g_MonitorList[4].pLabel = ui.label_5;
    g_MonitorList[5].pLabel = ui.label_6;
    g_MonitorList[6].pLabel = ui.label_7;
    g_MonitorList[7].pLabel = ui.label_8;
    g_MonitorList[8].pLabel = ui.label_9;

    for (INT32 i = 0; i < MAX_MONITOR_COUNT; i++)
    {
        g_MonitorList[i].pGraphicsScene = new QGraphicsScene;
        g_MonitorList[i].pGraphicsView->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
        g_MonitorList[i].pGraphicsView->setInteractive(false);
        g_MonitorList[i].pGraphicsView->setScene(g_MonitorList[i].pGraphicsScene);
    }

	//ui.treeArea->setColumnWidth(enumAreaTextColumnName, 100);
	//ui.treeArea->setColumnWidth(enumAreaTextColumnAddress, 100);
	//ui.treeArea->setColumnWidth(enumAreaTextColumnState, 100);
	//ui.treeArea->setColumnWidth(enumAreaTextColumnConfig, 200);
	//ui.treeArea->setColumnWidth(enumAreaTextColumnProgress, 100);// sending progress

	ui.treeGuardProcesses->setColumnWidth(enumProcessTextColumnPID, 160);
	ui.treeGuardProcesses->setColumnWidth(enumProcessTextColumnType, 80);
	ui.treeGuardProcesses->setColumnWidth(enumProcessTextColumnState, 80);
	ui.treeGuardProcesses->setColumnWidth(enumProcessTextColumnMode, 80);

    ui.treeStatisInfo->setColumnWidth(0,150);
    ui.treeStatisInfo->setColumnWidth(1,60);
    ui.treeStatisInfo->setColumnWidth(2,60);
    ui.treeStatisInfo->setColumnWidth(3,60);
    ui.treeStatisInfo->setColumnWidth(4,60);
    ui.treeStatisInfo->setColumnWidth(5,60);

	QObject::connect(ui.actionLogin, SIGNAL(triggered()), this, SLOT(Login()));
	QObject::connect(ui.actionLogout, SIGNAL(triggered()), this, SLOT(Logout()));
	QObject::connect(ui.actionSnapShoot, SIGNAL(triggered()), this, SLOT(SnapShoot()));
	QObject::connect(ui.actionHibernate, SIGNAL(triggered()), this, SLOT(Hibernate()));

	QPushButton::connect(ui.listLog->model(), SIGNAL(rowsInserted(const QModelIndex&, int, int)), ui.listLog, SLOT(scrollToBottom()));
	QPushButton::connect(ui.listAlert->model(), SIGNAL(rowsInserted(const QModelIndex&, int, int)), ui.listAlert, SLOT(scrollToBottom()));
	QPushButton::connect(ui.ButtonClearLog, SIGNAL(clicked()), this, SLOT(CleanLog()));
	QPushButton::connect(ui.ButtonClearAlert, SIGNAL(clicked()), this, SLOT(CleanAlert()));
	QObject::connect(ui.editFliter, SIGNAL(textChanged(const QString&)), this, SLOT(LogFilter(const QString&)));
	QObject::connect(ui.editAlertFliter, SIGNAL(textChanged(const QString&)), this, SLOT(AlertFilter(const QString&)));

	QPushButton::connect(ui.buttonStart, SIGNAL(clicked()), this, SLOT(Start()));
	QPushButton::connect(ui.buttonOpen, SIGNAL(clicked()), this, SLOT(Open()));
	QPushButton::connect(ui.buttonStop, SIGNAL(clicked()), this, SLOT(Stop()));
	QPushButton::connect(ui.buttonClose, SIGNAL(clicked()), this, SLOT(Close()));
	QPushButton::connect(ui.buttonEnter, SIGNAL(clicked()), this, SLOT(ExecuteCmd()));

	QPushButton::connect(ui.ButtonLoadVersion, SIGNAL(clicked()), this, SLOT(VersionRefresh()));
	QPushButton::connect(ui.buttonSendConfig, SIGNAL(clicked()), this, SLOT(SendConfig()));
	QPushButton::connect(ui.buttonSendVersion, SIGNAL(clicked()), this, SLOT(SendVersion()));
	QPushButton::connect(ui.buttonDeployVersion, SIGNAL(clicked()), this, SLOT(DeployVersion()));
	QPushButton::connect(ui.buttonSendPatch, SIGNAL(clicked()), this, SLOT(SendPatch()));
	QPushButton::connect(ui.buttonHotUpdatePatch, SIGNAL(clicked()), this, SLOT(HotUpdatePatch()));

	QObject::connect(ui.treeStatisInfo, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this, SLOT(OnStatisInfoItemDoubleClicked(QTreeWidgetItem *, int)));
	QObject::connect(ui.treeArea, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(OnAreaTreeClick(QTreeWidgetItem *, int)));
	QObject::connect(ui.treeArea, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(OnAreaItemDoubleClicked(QTreeWidgetItem *, int)));
	QObject::connect(ui.listVersion, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(OnVesionWidgetDoubleClicked(const QModelIndex &)));
	QObject::connect(ui.listPatch, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(OnPatchWidgetDoubleClicked(const QModelIndex &)));
	QObject::connect(ui.listLog, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(OnLogDoubleClicked(QListWidgetItem *)));
}

MaintainTool::~MaintainTool()
{

}

BOOL MaintainTool::Init()
{
	INT32 nRetCode = 0;

	m_nWaitCmdCount = 0;
	memset(m_szCurCmd, 0, sizeof(m_szCurCmd));
	m_bCmdResult = TRUE;
	
	//ui.frameMain->hide();
	m_bLogin = FALSE;
	//ui.frameMain->show();
	//Login();

	nRetCode = _RefreshAreaInfo();
	LOG_PROCESS_ERROR(nRetCode);

    nRetCode = InitGuardStatisInfo();
    LOG_PROCESS_ERROR(nRetCode);

	memset(m_szVersionPath, 0, sizeof(m_szVersionPath));
	memset(m_szPatchPath, 0, sizeof(m_szPatchPath));

	char szWorkPath[PATH_LEN] = { 0 };
	nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
	LOG_PROCESS_ERROR(nRetCode > 0);

	sprintf(m_szVersionPath, "%s\\%s", szWorkPath, g_MTConfig.szVersionPath);
	sprintf(m_szPatchPath, "%s\\%s", szWorkPath, g_MTConfig.szPatchPath);

	nRetCode = _RefreshServerVersion();
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = _RefreshServerPatch();
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL MaintainTool::UnInit()
{
	return TRUE;
}

MaintainTool& MaintainTool::GetInstance(void)
{
	return ms_Instance;
}

BOOL MaintainTool::Cleanup(void)
{
	return TRUE;
}

void MaintainTool::timerEvent(QTimerEvent* event)
{
	INT32 nRetCode = 0;

	if(m_bLogin)
	{
		nRetCode = CSessionMgr::GetInstance().MainLoop();
		LOG_CHECK_ERROR(nRetCode);

        nRetCode = CTransmitFileMgr::GetInstance().MainLoop();
        LOG_PROCESS_ERROR(nRetCode);
    }

	nRetCode = g_pNet->MainLoop();
	LOG_PROCESS_ERROR(nRetCode);

Exit0:
	return;
}

void MaintainTool::LogOutput(INT32 eLogLevel, const char* pcszMessage, INT32 nMessageSize)
{
	QListWidgetItem* pItem = NULL;
	QString str = QString::fromUtf8(pcszMessage);
	str.remove(QChar('\r'));
	str.remove(QChar('\n'));
	str.replace(QChar('\t'), QString::fromUtf8("  "));
	pItem = new QListWidgetItem(str);
	LOG_PROCESS_ERROR(pItem);

	//pItem->setSizeHint(QSize(0, 20));

	switch (eLogLevel)
	{
	case lltSDU:
	case lltDebug:
	case lltMove:
		pItem->setTextColor(Qt::black);
		break;
	case lltInfo:
		pItem->setTextColor(Qt::darkGreen);
		break;
	case lltWarning:
		pItem->setTextColor(Qt::darkYellow);
		break;
	case lltCritical:
		pItem->setTextColor(Qt::red);
		break;
	case lltError:
		pItem->setTextColor(Qt::darkRed);
		break;
	case lltLua:
		pItem->setTextColor(Qt::blue);
		break;
	default:
		break;
	}

	QListWidget * pListLog = MaintainTool::GetInstance().ui.listLog;
	const int MAX_LOG_LIST_ITEMS = 1024;
	if (pListLog->count() > MAX_LOG_LIST_ITEMS && pListLog->count() > 0)
	{
		delete(pListLog->item(0));
	}
	pListLog->addItem(pItem);
Exit0:
	return;
}

struct CCheckIPDirectory
{
	char m_szAreaPath[PATH_LEN];

	INT32 m_nAreaIndex;
	INT32 m_nGuardIndex;

	BOOL RequireDirectory(void);
	BOOL operator()(const char* szIPDirectoryName);
};

BOOL CCheckIPDirectory::RequireDirectory()
{
	return TRUE;
}
BOOL CCheckIPDirectory::operator() (const char* szIPDirectoryName)
{
	BOOL nRetCode = FALSE;

	LOG_PROCESS_ERROR(m_nGuardIndex < MAX_GUARD_COUNT_PER_AREA - 1);
	//for (INT32 i=0; i<nGuardIndex; ++i)
	//{
	//    LOG_PROCESS_ERROR( strcmp(rConfig.guardList[i], szFileName) != 0 );
	//}

	//char szDirName[MAX_PATH] = { 0 };
	//nRetCode = sscanf(szIPDirectoryName, "%[0-9.]", szDirName);
	//if (nRetCode != 1 || 
	//	szDirName[strlen(szDirName)-1] == '.' ||
	//	strlen(szDirName) != strlen(szIPDirectoryName))
	//{
	//	INF("invalid guard folder name %s\\%s", m_szAreaPath, szIPDirectoryName);
	//	LOG_PROCESS_ERROR(FALSE);
	//}

	INT32 nIPpart[4] = { 0 };
	char szRest[MAX_PATH] = { 0 };
	nRetCode = sscanf(szIPDirectoryName, "%d.%d.%d.%d%s", &nIPpart[0], &nIPpart[1], &nIPpart[2], &nIPpart[3], szRest);
	if (nRetCode < 4 || strlen(szRest) > 0) // >= 0 && <= 255
	{
		INF("invalid guard folder name %s\\%s", m_szAreaPath, szIPDirectoryName);
		LOG_PROCESS_ERROR(FALSE);
	}

	LOG_PROCESS_ERROR(m_nAreaIndex < MAX_AREA_COUNT);
	LOG_PROCESS_ERROR(m_nGuardIndex < MAX_GUARD_COUNT_PER_AREA);

	MAINTAIN_CONFIG::SAreaConfig& rConfig = g_MTConfig.AreaConfig[m_nAreaIndex];
	MAINTAIN_CONFIG::SAreaConfig::SRemoteGuard& rGuard = rConfig.guardList[m_nGuardIndex];
	strxcpy(rGuard.szAddress, szIPDirectoryName, sizeof(rGuard.szAddress));
	rGuard.nPort = 8810;

	++m_nGuardIndex;
Exit0:
	return TRUE;
}

struct CCheckAreaDirectory
{
	INT32 m_nAreaIndex;
	char m_szRootPath[PATH_LEN];

	BOOL RequireDirectory(void);
	BOOL operator()(const char* szAreaDirectoryName);
};

BOOL CCheckAreaDirectory::RequireDirectory()
{
	return TRUE;
}

BOOL CCheckAreaDirectory::operator() (const char* szAreaDirectoryName)
{
	BOOL nRetCode = FALSE;
	INT32 nAreaIndex = 0;
	char szAreaName[COMMON_NAME_LEN] = { 0 };

	// check 1
	nRetCode = sscanf(szAreaDirectoryName, "%d_%s", &nAreaIndex, szAreaName);
	if (nRetCode != 2)
	{
		INF("invalid area %s, skip", szAreaDirectoryName);
		LOG_PROCESS_ERROR(FALSE);
	}

	// check 2
	LOG_PROCESS_ERROR(nAreaIndex < MAX_AREA_COUNT);
	m_nAreaIndex = nAreaIndex;

	MAINTAIN_CONFIG::SAreaConfig& rConfig = g_MTConfig.AreaConfig[nAreaIndex];
	// check 3
	if (rConfig.szAreaFolderName[0] != '\0')
	{
		CRI("area %d duplicated! %s", nAreaIndex, rConfig.szAreaFolderName);
		LOG_PROCESS_ERROR(FALSE);
	}

	// set
	rConfig.areaID = nAreaIndex;
	strxcpy(rConfig.szAreaName, szAreaName, sizeof(rConfig.szAreaName));
	strxcpy(rConfig.szAreaFolderName, szAreaDirectoryName, sizeof(rConfig.szAreaFolderName));

	// traverse
	CCheckIPDirectory stGuardChecker;
	stGuardChecker.m_nAreaIndex = m_nAreaIndex;
	stGuardChecker.m_nGuardIndex = 1; //skip 0
	snprintf(stGuardChecker.m_szAreaPath, sizeof(stGuardChecker.m_szAreaPath),
		"%s\\%s", m_szRootPath, szAreaDirectoryName);

	nRetCode = g_DirectoryTraverse(stGuardChecker.m_szAreaPath, stGuardChecker);
	LOG_PROCESS_ERROR(nRetCode);

Exit0:
	return TRUE;
}


BOOL MaintainTool::_ReloadAreaConfig()
{
	BOOL nRetCode = FALSE;

	memset(&g_MTConfig.AreaConfig, 0, sizeof(g_MTConfig.AreaConfig));

	char szWorkPath[PATH_LEN] = { 0 };
	nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
	LOG_PROCESS_ERROR(nRetCode > 0);

	// traverse
	CCheckAreaDirectory stAreaChecker;
	stAreaChecker.m_nAreaIndex = 0;
	snprintf(stAreaChecker.m_szRootPath, sizeof(stAreaChecker.m_szRootPath),
		"%s\\%s", szWorkPath, g_MTConfig.szAreaConfigPath);

	nRetCode = g_DirectoryTraverse(stAreaChecker.m_szRootPath, stAreaChecker);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	CRI("failed to load area files");
	return FALSE;
}

BOOL MaintainTool::_RefreshAreaInfo()
{
	INT32 nRetCode = 0;
	char szAreaName[256] = { 0 };
	QString strAreaInfo;

	INF("start to _RefreshAreaInfo");

	nRetCode = _ReloadAreaConfig();
	LOG_PROCESS_ERROR(nRetCode);

	ui.treeArea->clear();
	for (INT32 i = 1; i < MAX_AREA_COUNT; ++i)
	{
		QTreeWidgetItem *pNewArea = NULL;
		if (g_MTConfig.AreaConfig[i].areaID > 0)
		{
			pNewArea = new QTreeWidgetItem();
			sprintf(szAreaName, "%d_%s:", g_MTConfig.AreaConfig[i].areaID, g_MTConfig.AreaConfig[i].szAreaName);
			strAreaInfo = QString::fromLocal8Bit(szAreaName) + g_MTConfig.AreaConfig[i].szVersion;

			pNewArea->setText(enumAreaTextColumnName, strAreaInfo);
			pNewArea->setData(enumDataUserRoleAreaID, Qt::UserRole, g_MTConfig.AreaConfig[i].areaID);
			pNewArea->setData(enumDataUserRoleVersion, Qt::UserRole, g_MTConfig.AreaConfig[i].szVersion);
			pNewArea->setData(enumDataUserRoleAreaName, Qt::UserRole, QString::fromLocal8Bit(szAreaName));

			for (INT32 j = 1; j < MAX_GUARD_COUNT_PER_AREA; ++j)
			{
				if (g_MTConfig.AreaConfig[i].guardList[j].szAddress[0] != 0)
				{
					QTreeWidgetItem * pNewGuard = new QTreeWidgetItem();
					pNewGuard->setText(enumAreaTextColumnAddress, g_MTConfig.AreaConfig[i].guardList[j].szAddress);
					pNewGuard->setText(enumAreaTextColumnState, g_pcszConStr[emctUnConnect]); // "unconnect");
					pNewGuard->setText(enumAreaTextColumnConfig, "");
					pNewGuard->setText(enumAreaTextColumnProgress, "0/0");// sending progress

					pNewGuard->setData(enumDataUserRoleAreaName, Qt::UserRole, QString::fromLocal8Bit(szAreaName));
					pNewGuard->setData(enumDataUserRoleAreaID, Qt::UserRole, QVariant(g_MTConfig.AreaConfig[i].areaID));
					pNewGuard->setData(enumDataUserRoleIP, Qt::UserRole, QVariant((UINT32)inet_addr(g_MTConfig.AreaConfig[i].guardList[j].szAddress)));

					if (strnicmp(g_MTConfig.AreaConfig[i].szVersion,
						g_MTConfig.AreaConfig[i].guardList[j].szGuardVersion,
						sizeof(g_MTConfig.AreaConfig[i].guardList[j].szGuardVersion)) != 0)
					{
						pNewArea->setTextColor(0, Qt::red);
					}

					pNewArea->addChild(pNewGuard);
				}
			}

			ui.treeArea->addTopLevelItem(pNewArea);
		}
	}

Exit0:
	return nRetCode;
}

struct CEntriesCollector
{
	std::vector<std::string> m_Entries;

	BOOL RequireDirectory()	{ return FALSE; }

	BOOL operator()(const char* szVersionEntryName)
	{
		m_Entries.push_back(szVersionEntryName);
		return TRUE;
	}
};

BOOL MaintainTool::_RefreshServerVersion()
{
	INT32 nRetCode = 0;
	QListWidgetItem* pItem = NULL;

	CEntriesCollector stChecker;
	stChecker.m_Entries.clear();

	LOG_PROCESS_ERROR(m_szVersionPath[0]);
	nRetCode = g_DirectoryExists(m_szVersionPath);
	if (!nRetCode)
	{
		g_CreateDirectory(m_szVersionPath,TRUE);
	}
	LOG_PROCESS_ERROR(g_DirectoryExists(m_szVersionPath));

	nRetCode = g_DirectoryTraverse(m_szVersionPath, stChecker);
	LOG_PROCESS_ERROR( nRetCode );

	ui.listVersion->clear();
	for (std::vector<std::string>::iterator it = stChecker.m_Entries.begin();
		it != stChecker.m_Entries.end(); ++it )
	{
		std::string strFileName = *it;
		if (strFileName.find(".zip") == -1)
			continue;

		QString strFileVersion;
		strFileVersion.sprintf("%s", strFileName.c_str());

		pItem = new QListWidgetItem(strFileVersion);
		LOG_PROCESS_ERROR(pItem);

		ui.listVersion->addItem(pItem);
	} 
	ui.listVersion->sortItems(Qt::DescendingOrder);

	return TRUE;
Exit0:
	return FALSE;
}	

BOOL MaintainTool::_RefreshServerPatch()
{
	INT32 nRetCode = 0;
	QListWidgetItem* pItem = NULL;

	CEntriesCollector stChecker;
	stChecker.m_Entries.clear();

	LOG_PROCESS_ERROR(m_szPatchPath[0]);
	nRetCode = g_DirectoryExists(m_szPatchPath);
	if (!nRetCode)
	{
		g_CreateDirectory(m_szPatchPath,TRUE);
	}
	LOG_PROCESS_ERROR(g_DirectoryExists(m_szPatchPath));

	nRetCode = g_DirectoryTraverse(m_szPatchPath, stChecker);
	LOG_PROCESS_ERROR(nRetCode);

	ui.listPatch->clear();
	for (std::vector<std::string>::iterator it = stChecker.m_Entries.begin();
		it != stChecker.m_Entries.end(); ++it)
	{
		std::string strFileName = *it;
		if (strFileName.find(".pak") == -1)
			continue;

		QString strFileVersion;
		strFileVersion.sprintf("%s", strFileName.c_str());

		pItem = new QListWidgetItem(strFileVersion);
		LOG_PROCESS_ERROR(pItem);

		ui.listPatch->addItem(pItem);
	}
	ui.listPatch->sortItems(Qt::DescendingOrder);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL MaintainTool::UpdateGuardConnectInfo(SRemoteGuardSession* pGuardSession, INT32 nState, UINT8* pCountArray )
{
	INT32 nRetCode = 0;
	QTreeWidgetItem* pAreaItem = NULL;
	QTreeWidgetItem* pGuardItem = NULL;
	INT32 nAreaCount = ui.treeArea->topLevelItemCount();
	INT32 nGuardCount = 0;
	LOG_PROCESS_ERROR(pGuardSession);
    LOG_PROCESS_ERROR( nState >= 0 && nState < emctTotal );

    char pcszGuardConfig[256] = {0};
    if ( pCountArray != NULL )
    {
        for(INT32 i = stMS; i <= stDL; ++i)
        {		
            if(pCountArray[i] > 0)
            {
                snprintf(pcszGuardConfig+strlen(pcszGuardConfig), sizeof(pcszGuardConfig)-strlen(pcszGuardConfig), 
					" [%s:%d]", GetServerShortName(i), pCountArray[i]);
            }
        }
    }

	pGuardItem = _GetGuardWidget(pGuardSession->dwArea, pGuardSession->dwIp);
	LOG_PROCESS_ERROR( pGuardItem );
	pGuardItem->setText(enumAreaTextColumnState, g_pcszConStr[nState]);
	pGuardItem->setText(enumAreaTextColumnConfig, pcszGuardConfig);
	pGuardItem->setText(enumAreaTextColumnProgress, "");

	return TRUE;
Exit0:
	return FALSE;
}

BOOL MaintainTool::UpdateGuardSendProgress(INT32 nAreaID, UINT32 dwIp, INT32 nPercent)
{
    INT32 nRetCode = 0;
    QTreeWidgetItem* pGuardItem = NULL;

	char szProgress[128] = { 0 };

	pGuardItem = _GetGuardWidget(nAreaID, dwIp);
	LOG_PROCESS_ERROR(pGuardItem);

	if (nPercent == -1)
	{
		sprintf(szProgress, "send files error");
	}
	else if (nPercent == -2)
	{
		sprintf(szProgress, "overwrite version config error");
	}
	else if (nPercent == -3)
	{
		sprintf(szProgress, "direct move config error");
	}
	else if (nPercent > 100)
	{
		sprintf(szProgress, "send all ok");
	}
	else if (nPercent < 0)
	{
		sprintf(szProgress, "some error after sent");
	}
	else
	{
		sprintf(szProgress, "%d%%", nPercent);
	}
	pGuardItem->setText(4, szProgress);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL MaintainTool::AddGuardProcessesInfobyIp(INT32 nAreaID, UINT32 dwIp)
{
	INT32 nRetCode = 0;
	SRemoteGuardSession* pGuardSession = NULL;
	pGuardSession = CSessionMgr::GetInstance().GetRemoteGDSession(nAreaID, dwIp);
	LOG_PROCESS_ERROR(pGuardSession);

	for(INT32 i = 0; i < MAX_REMOTE_SESSION_COUNT; ++i)
	{
		if(pGuardSession->lstProcess[i].dwProcessID > 0)
		{
			QTreeWidgetItem* pItem = NULL;
			QString str;

			pItem = new QTreeWidgetItem();
			LOG_PROCESS_ERROR(pItem);

			struct in_addr addr;
			addr.s_addr = dwIp;
			str.sprintf("%s-%d", inet_ntoa(addr), pGuardSession->lstProcess[i].dwProcessID);
			//str.sprintf("%d", pGuardSession->lstRemoteSession[i].dwProcessID);
			pItem->setText(enumProcessTextColumnPID, str);

			str.sprintf("%s-%.2d", GetServerShortName(pGuardSession->lstProcess[i].byType), 
				pGuardSession->lstProcess[i].dwSessionID);
			//str.sprintf("%s", GetServerShortName(pGuardSession->lstRemoteSession[i].byType));
			pItem->setText(enumProcessTextColumnType, str);

			str.sprintf("%s", pGuardSession->lstProcess[i].nState == InternalMessage::epsUnonnect ? "unonnect" : "normal");
			pItem->setText(enumProcessTextColumnState, str);

			str.sprintf("%s", pGuardSession->lstProcess[i].bAuto ? "Auto" : "manul");
			pItem->setText(enumProcessTextColumnMode, str);

			pItem->setData(enumDataUserRoleAreaID, Qt::UserRole, nAreaID);
			pItem->setData(enumDataUserRoleIP, Qt::UserRole, dwIp);
			pItem->setData(enumDataUserRolePID, Qt::UserRole, pGuardSession->lstProcess[i].dwProcessID);
			pItem->setData(enumDataUserRoleType, Qt::UserRole, pGuardSession->lstProcess[i].byType);
			pItem->setData(enumDataUserRoleSessionID, Qt::UserRole, pGuardSession->lstProcess[i].dwSessionID);

			ui.treeGuardProcesses->addTopLevelItem(pItem);
		}
	}

	return TRUE;
Exit0:
	return FALSE;
}


BOOL MaintainTool::UpdateGuardProcessesInfo()
{
	INT32 nRetCode = 0;
	QTreeWidgetItem* pItem = NULL;
	QList<QTreeWidgetItem*> lstSelectItem;

	//lstSelectItem = ui.treeArea->selectedItems();
	//LOG_PROCESS_ERROR(lstSelectItem.count() == 1);

	BOOL bRequireSameParent = TRUE;
	lstSelectItem = GetSelectedIpItems(bRequireSameParent);
	PROCESS_ERROR(lstSelectItem.count() > 0);

    ui.treeGuardProcesses->clear();	
	for(QList<QTreeWidgetItem*>::iterator itr = lstSelectItem.begin(); itr != lstSelectItem.end(); ++itr)
    {		
        INT32 nChildCount = (*itr)->childCount();

		LOG_PROCESS_ERROR( nChildCount == 0 );
		//if(nChildCount == 0) // ip
		{
			INT32 nAreaID = (*itr)->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
			UINT32 dwIp = (*itr)->data(enumDataUserRoleIP, Qt::UserRole).toInt();

			AddGuardProcessesInfobyIp(nAreaID, dwIp);
		}
	}

	ui.treeGuardProcesses->sortItems(enumProcessTextColumnType, Qt::AscendingOrder);
Exit0:
	return TRUE;
}

void MaintainTool::_UpdateMonitor(QGraphicsScene* pGraphicsScene, 
                                  stProcessStatisInfo* poInfo, INT32 nProcessIndex, INT32 nStatisIndex)
{
    UINT64 qwMax = 0;

    for (INT32 i = 1; i < ACCUMU_MAX_TIMES; i++)
    {
        if (poInfo->oAccumuStatis[i].ProcessInfo[nProcessIndex].qwStatisEntry[nStatisIndex] > qwMax)
            qwMax = poInfo->oAccumuStatis[i].ProcessInfo[nProcessIndex].qwStatisEntry[nStatisIndex];
    }

    pGraphicsScene->clear();
    pGraphicsScene->addSimpleText(QString("%1").arg(qwMax));

    for (INT32 i = 1; i < ACCUMU_MAX_TIMES; i++)
    {
        INT32 nPreValue = poInfo->oAccumuStatis[i-1].ProcessInfo[nProcessIndex].qwStatisEntry[nStatisIndex];
        INT32 nValue = poInfo->oAccumuStatis[i].ProcessInfo[nProcessIndex].qwStatisEntry[nStatisIndex];
        INT32 nPrePercent = 0;
        INT32 nPercent = 0;
        if (qwMax > 0)
        {
            nPrePercent = nPreValue * 100 / qwMax;
            nPercent = nValue * 100 / qwMax;
        }

        if ((i + 1) % ACCUMU_MAX_TIMES == poInfo->nAccumuIndex)
        {
            pGraphicsScene->addLine(i*4+40, (100-nPrePercent)*2+20, i*4+40+4, (100-nPercent)*2+20, 
                QPen(QBrush(Qt::red), 2));
        }
        else
            pGraphicsScene->addLine(i*4+40, (100-nPrePercent)*2+20, i*4+40+4, (100-nPercent)*2+20, 
            QPen(Qt::black));
    }

    return;
}

BOOL MaintainTool::SnapShootGuardStatisInfoByIp(INT32 nAreaID, UINT32 dwIp, UINT32 dwPID, char* pszOutStr)
{
	INT32 nRetCode = 0;
	stProcessStatisInfo* poInfo = NULL;

	SRemoteGuardSession* pGuardSession = CSessionMgr::GetInstance().GetRemoteGDSession(nAreaID, dwIp);
	LOG_PROCESS_ERROR(pGuardSession);
	LOG_PROCESS_ERROR(pGuardSession->bConnected);

	poInfo = pGuardSession->poStatisInfo;
	LOG_PROCESS_ERROR(poInfo);

	sprintf(pszOutStr, "%s\t%s\t%s\t%s\t%s\n", "name", "current", "average", "min", "max");
	for (INT32 nProcessIndex = 0; nProcessIndex < MAX_STATIS_PROCESS_COUNT; ++nProcessIndex)
	{
		if (poInfo->ProcessInfo[nProcessIndex].bUsed && dwPID == poInfo->ProcessInfo[nProcessIndex].dwProcessID)
		{
			for (INT32 nStatEntryIndex = 0; nStatEntryIndex < statTotal; nStatEntryIndex++)
			{
				if (g_szStatFieldName[nStatEntryIndex] == NULL || g_szStatFieldName[nStatEntryIndex][0] == 0)
					continue;

				INT64 llAccumulate = 0LL;
				for (INT32 t = 0; t < ACCUMU_MAX_TIMES; ++t)
				{
					if (poInfo->oAccumuStatis[nStatEntryIndex].ProcessInfo[nProcessIndex].dwProcessID != dwPID)
						continue;
					llAccumulate += poInfo->oAccumuStatis[t].ProcessInfo[nProcessIndex].qwStatisEntry[nStatEntryIndex];
				}

				sprintf(pszOutStr+strlen(pszOutStr), "%s\t%lld\t%lld\t%lld\t%lld\n", g_szStatFieldName[nStatEntryIndex],
					poInfo->ProcessInfo[nProcessIndex].qwStatisEntry[nStatEntryIndex],
					llAccumulate / ACCUMU_MAX_TIMES,
					poInfo->StatDataList[nProcessIndex][nStatEntryIndex].qwMin,
					poInfo->StatDataList[nProcessIndex][nStatEntryIndex].qwMax);
			}
			break;
		}
	}


	return TRUE;
Exit0:
	return FALSE;
}

BOOL MaintainTool::SnapShootGuardStatisInfoCurrentByIp(INT32 nAreaID, UINT32 dwIp, UINT32 dwPID, char* pszOutStr)
{
	INT32 nRetCode = 0;
	stProcessStatisInfo* poInfo = NULL;

	SRemoteGuardSession* pGuardSession = CSessionMgr::GetInstance().GetRemoteGDSession(nAreaID, dwIp);
	LOG_PROCESS_ERROR(pGuardSession);
	LOG_PROCESS_ERROR(pGuardSession->bConnected);

	poInfo = pGuardSession->poStatisInfo;
	LOG_PROCESS_ERROR(poInfo);

	//sprintf(pszOutStr, "%s\t%s\t%s\t%s\t%s\n", "name", "current", "average", "min", "max");
	for (INT32 nProcessIndex = 0; nProcessIndex < MAX_STATIS_PROCESS_COUNT; ++nProcessIndex)
	{
		if (poInfo->ProcessInfo[nProcessIndex].bUsed && dwPID == poInfo->ProcessInfo[nProcessIndex].dwProcessID)
		{
			for (INT32 nStatEntryIndex = statInvalid + 1; nStatEntryIndex < statTotal; nStatEntryIndex++)
			{
				if (g_szStatFieldName[nStatEntryIndex] == NULL)
					continue;

				sprintf(pszOutStr + strlen(pszOutStr), "\t%lld", poInfo->ProcessInfo[nProcessIndex].qwStatisEntry[nStatEntryIndex]);
			}
			break;
		}
	}


	return TRUE;
Exit0:
	return FALSE;
}

BOOL MaintainTool::EndHibernateGuardStatisInfoByIp()
{
	QTreeWidgetItemIterator it(ui.treeGuardProcesses);
	while (*it)
	{
		INT32 nAreaID = (*it)->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
		UINT32 dwIp = (*it)->data(enumDataUserRoleIP, Qt::UserRole).toInt();

		SRemoteGuardSession* pGuardSession = CSessionMgr::GetInstance().GetRemoteGDSession(nAreaID, dwIp);
		PROCESS_ERROR(pGuardSession);
		PROCESS_ERROR(pGuardSession->bConnected);

		for (INT32 i = 0; i < MAX_REMOTE_SESSION_COUNT; ++i)
		{
			if (pGuardSession->lstProcess[i].poHibernateStatisFileHandle)
			{
				fclose(pGuardSession->lstProcess[i].poHibernateStatisFileHandle);
				pGuardSession->lstProcess[i].poHibernateStatisFileHandle = NULL;
			}
		}

		++it;
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL MaintainTool::ProcessHibernateGuardStatisInfoByIp(stStatisProcess* pStatisInfo, SProcessInfo* poSessionInfo)
{
	INT32 nRetCode = 0;

	char szContent[1024] = { 0 };
	INT32 nContentLen = 0;
	const tm_ex* pNow = NULL;
	char szTimeStamp[PATH_LEN] = { 0 };

	LOG_PROCESS_ERROR(poSessionInfo);

	pNow = localtime_ex();
	snprintf(szTimeStamp, sizeof(szTimeStamp), "%04d-%02d-%02d %02d:%02d:%02d.%03d",
		pNow->tm_year, pNow->tm_mon, pNow->tm_mday,
		pNow->tm_hour, pNow->tm_min, pNow->tm_sec, pNow->tm_msec);

	//content	
	szContent[0] = '\0';
	sprintf(szContent + strlen(szContent), "%s\t", szTimeStamp);
	for (INT32 nStatEntryIndex = 0; nStatEntryIndex < statTotal; nStatEntryIndex++)
	{
		if (g_szStatFieldName[nStatEntryIndex] == NULL || g_szStatFieldName[nStatEntryIndex][0] == 0)
			continue;

		sprintf(szContent + strlen(szContent), "%lld\t", pStatisInfo->qwStatisEntry[nStatEntryIndex]);
	}

	szContent[strlen(szContent) - 1] = '\n';
	nContentLen = strlen(szContent);
	nRetCode = fwrite(szContent, 1, nContentLen, poSessionInfo->poHibernateStatisFileHandle);
	LOG_PROCESS_ERROR(nRetCode == nContentLen);
	//
	fflush(poSessionInfo->poHibernateStatisFileHandle);

	return TRUE;
Exit0:
	if (poSessionInfo && poSessionInfo->poHibernateStatisFileHandle)
	{
		fclose(poSessionInfo->poHibernateStatisFileHandle);
		poSessionInfo->poHibernateStatisFileHandle = NULL;
	}
	return FALSE;
}

BOOL MaintainTool::BeginHibernateGuardStatisInfoByIp(INT32 nAreaID, UINT32 dwIp, UINT32 dwPID, UINT8 byType, UINT32 dwSessionID )
{
	INT32 nRetCode = 0;
	stProcessStatisInfo* poInfo = NULL;
	char szContent[1024] = { 0 };
	INT32 nContentLen = 0;
	const tm_ex* pNow = NULL;
	char szTimeStamp[PATH_LEN] = { 0 };

	SRemoteGuardSession* pGuardSession = CSessionMgr::GetInstance().GetRemoteGDSession(nAreaID, dwIp);
	LOG_PROCESS_ERROR(pGuardSession);
	LOG_PROCESS_ERROR(pGuardSession->bConnected);

	poInfo = pGuardSession->poStatisInfo;
	LOG_PROCESS_ERROR(poInfo);

	pNow = localtime_ex();
	snprintf(szTimeStamp, sizeof(szTimeStamp), "%04d_%02d_%02d_%02d_%02d_%02d_%03d",
		pNow->tm_year, pNow->tm_mon, pNow->tm_mday,
		pNow->tm_hour, pNow->tm_min, pNow->tm_sec, pNow->tm_msec);

	INT32 nProcessIndex = -1;
	for (INT32 i = 0; i < MAX_STATIS_PROCESS_COUNT; ++i)
	{
		if (dwPID == pGuardSession->lstProcess[i].dwProcessID)
		{
			nProcessIndex = i;
			break;
		}
	}
	PROCESS_ERROR(nProcessIndex > -1);

	LOG_PROCESS_ERROR(pGuardSession->lstProcess[nProcessIndex].poHibernateStatisFileHandle == NULL);

	{
		char szFilePath[PATH_LEN] = { 0 };
		char szWorkPath[PATH_LEN] = { 0 };
		nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
		LOG_PROCESS_ERROR(nRetCode > 0);

		struct in_addr addr;
		addr.s_addr = dwIp;
		snprintf(szFilePath, sizeof(szFilePath), "%s\\log\\hibernate_%s-%d=%d@%s_%s.tsv", szWorkPath,
			GetServerShortName(byType), dwSessionID, dwPID, inet_ntoa(addr), szTimeStamp);

		INF("hibernate open file %s", szFilePath);

		pGuardSession->lstProcess[nProcessIndex].poHibernateStatisFileHandle = fopen(szFilePath, "wb+");
		LOG_PROCESS_ERROR(pGuardSession->lstProcess[nProcessIndex].poHibernateStatisFileHandle);

		// write head
		szContent[0] = '\0';
		sprintf(szContent + strlen(szContent), "%s\t", "time");
		for (INT32 nStatEntryIndex = statInvalid + 1; nStatEntryIndex < statTotal; ++nStatEntryIndex)
		{
			if (g_szStatFieldName[nStatEntryIndex] == NULL || g_szStatFieldName[nStatEntryIndex][0] == 0)
				continue;
			sprintf(szContent + strlen(szContent), "%s\t", g_szStatFieldName[nStatEntryIndex]);
		}
		szContent[strlen(szContent)-1] = '\n';
		nContentLen = strlen(szContent);
		nRetCode = fwrite(szContent, 1, nContentLen, pGuardSession->lstProcess[nProcessIndex].poHibernateStatisFileHandle);
		LOG_PROCESS_ERROR(nRetCode == nContentLen);

		fflush(pGuardSession->lstProcess[nProcessIndex].poHibernateStatisFileHandle);
	}


	return TRUE;
Exit0:
	if (pGuardSession && nProcessIndex > -1 && pGuardSession->lstProcess[nProcessIndex].poHibernateStatisFileHandle)
	{
		fclose(pGuardSession->lstProcess[nProcessIndex].poHibernateStatisFileHandle);
		pGuardSession->lstProcess[nProcessIndex].poHibernateStatisFileHandle = NULL;
	}
	return FALSE;
}

BOOL MaintainTool::UpdateGuardStatisInfoByIp(INT32 nAreaID, UINT32 dwIp, UINT32 dwPID)
{
    INT32 nRetCode = 0;
    QTreeWidgetItem* pItem = NULL;
    QString str;

	SRemoteGuardSession* pGuardSession = CSessionMgr::GetInstance().GetRemoteGDSession(nAreaID, dwIp);
	LOG_PROCESS_ERROR(pGuardSession);
	LOG_PROCESS_ERROR(pGuardSession->bConnected);

    stProcessStatisInfo* poInfo = pGuardSession->poStatisInfo;
    LOG_PROCESS_ERROR( poInfo );

    INT32 nProcessIndex = -1;
    for ( INT32 i=0; i<MAX_STATIS_PROCESS_COUNT; ++i )
    {
		if (poInfo->ProcessInfo[i].bUsed && dwPID == poInfo->ProcessInfo[i].dwProcessID)
        {
			if (nProcessIndex < 0)
			{
				nProcessIndex = i;
			}
			else
			{
				CRI("duplicated process! pid = %d, index = %d", dwPID, nProcessIndex);
			}
        }
        for (INT32 j = 0; j < statTotal; j++)
        {
            if (g_szStatFieldName[j] == NULL || g_szStatFieldName[j][0] == 0)
                continue;

            if (poInfo->ProcessInfo[i].qwStatisEntry[j] < poInfo->StatDataList[i][j].qwMin)
                poInfo->StatDataList[i][j].qwMin = poInfo->ProcessInfo[i].qwStatisEntry[j];

            if (poInfo->ProcessInfo[i].qwStatisEntry[j] > poInfo->StatDataList[i][j].qwMax)
                poInfo->StatDataList[i][j].qwMax = poInfo->ProcessInfo[i].qwStatisEntry[j];

            poInfo->StatDataList[i][j].qwTotal += poInfo->ProcessInfo[i].qwStatisEntry[j];
        }

        for (INT32 j = 0; j < MAX_MONITOR_COUNT; j++)
        {
            if (dwIp == g_MonitorList[j].dwIp &&
                poInfo->ProcessInfo[i].dwProcessID == g_MonitorList[j].dwProcess)
            {
                INT32 nStatisIndex = g_MonitorList[j].nIndex;

                _UpdateMonitor(g_MonitorList[j].pGraphicsScene, poInfo, i, nStatisIndex);
            }
        }
    }
    PROCESS_ERROR( nProcessIndex >= 0 );

    for ( INT32 i=0; i<statTotal; ++i )
    {
        if (g_szStatFieldName[i] == NULL || g_szStatFieldName[i][0] == 0)
            continue;
        pItem = ui.treeStatisInfo->findItems(g_szStatFieldName[i], Qt::MatchExactly).front();
        LOG_PROCESS_ERROR(pItem);

        pItem->setText(1, QString("%1").arg(poInfo->ProcessInfo[nProcessIndex].qwStatisEntry[i]));

        // column 2
        INT64 llAccumulate = 0LL;
        for (INT32 j=0; j<ACCUMU_MAX_TIMES; ++j)
        {
            if ( poInfo->oAccumuStatis[j].ProcessInfo[nProcessIndex].dwProcessID != dwPID )
                continue;
            llAccumulate += poInfo->oAccumuStatis[j].ProcessInfo[nProcessIndex].qwStatisEntry[i];
        }
		pItem->setText(2, QString("%1").arg(llAccumulate / ACCUMU_MAX_TIMES));

        pItem->setText(3, QString("%1").arg(poInfo->StatDataList[nProcessIndex][i].qwMin));
        pItem->setText(4, QString("%1").arg(poInfo->StatDataList[nProcessIndex][i].qwMax));
        pItem->setText(5, QString("%1").arg(poInfo->StatDataList[nProcessIndex][i].qwTotal));

        if (pItem->isSelected())
        {
            _UpdateMonitor(m_pGraphicsScene, poInfo, nProcessIndex, i);
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL MaintainTool::InitGuardStatisInfo(void)
{
    INT32 nRetCode = 0;
    QTreeWidgetItem* pItem = NULL;

    ui.treeStatisInfo->clear();  

    for ( INT32 i=0; i<statTotal; ++i )
    {
        if (g_szStatFieldName[i] == NULL || g_szStatFieldName[i][0] == 0)
            continue;

        pItem = new QTreeWidgetItem();
        LOG_PROCESS_ERROR(pItem);

        pItem->setText(0, g_szStatFieldName[i]);
        pItem->setText(3, "999999999");
        pItem->setText(4, "0");
        pItem->setText(5, "0");
        pItem->setData(0, Qt::UserRole, i);

        ui.treeStatisInfo->addTopLevelItem(pItem);
    }

Exit0:
    return TRUE;  
}
BOOL MaintainTool::UpdateGuardStatisInfo(UINT32 dwAreaID, UINT32 dwIP )
{
    INT32 nRetCode = 0;
    QTreeWidgetItem* pItem = NULL;
    QString str;
    QList<QTreeWidgetItem*> lstSelectProcess;

	//lstSelectIp = GetSelectedIpItems();
	//PROCESS_ERROR(lstSelectIp.count() > 0 );

    lstSelectProcess = ui.treeGuardProcesses->selectedItems();
    PROCESS_ERROR( lstSelectProcess.count() == 1 );// statis tree widget shows only for one process

	for (QList<QTreeWidgetItem*>::iterator itProcess = lstSelectProcess.begin();
		itProcess != lstSelectProcess.end(); ++itProcess)
	{
		INT32 nItemAreaID = (*itProcess)->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
		UINT32 dwItemIp = (*itProcess)->data(enumDataUserRoleIP, Qt::UserRole).toInt();
		UINT32 dwProcessID = (*itProcess)->data(enumDataUserRolePID, Qt::UserRole).toInt();

		if (dwAreaID == nItemAreaID && dwItemIp == dwIP)
		{
			UpdateGuardStatisInfoByIp(dwAreaID, dwIP, dwProcessID);
			break;
		}
	}

    //ui.treeStatisInfo->sortItems(1, Qt::AscendingOrder);
Exit0:
    return TRUE;
}

BOOL MaintainTool::SnapShootGuardStatisInfo()
{
	INT32 nRetCode = 0;
	char szContent[16*1024] = {0};
	INT32 nContentLen = 0;

	FILE* pFileHandle = NULL;
	QTreeWidgetItem* pItem = NULL;
	QString str;
	QList<QTreeWidgetItem*> lstSelectProcess;

	lstSelectProcess = ui.treeGuardProcesses->selectedItems();

	char szTimeStamp[PATH_LEN] = { 0 };
	char szFilePath[PATH_LEN] = { 0 };
	char szWorkPath[PATH_LEN] = { 0 };
	nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
	LOG_PROCESS_ERROR(nRetCode > 0);
	const tm_ex* pNow = localtime_ex();

	snprintf(szTimeStamp, sizeof(szTimeStamp), "%04d_%02d_%02d_%02d_%02d_%02d_%02d",
		pNow->tm_year, pNow->tm_mon, pNow->tm_mday,
		pNow->tm_hour, pNow->tm_min, pNow->tm_sec, pNow->tm_msec);

	snprintf(szFilePath, sizeof(szFilePath), "%s\\log\\snapshoot_%s.tsv", szWorkPath, szTimeStamp);

	pFileHandle = fopen(szFilePath, "wb");
	LOG_PROCESS_ERROR(pFileHandle);

	//
	sprintf(szContent, "%s\n", szTimeStamp);
	nContentLen = strlen(szContent);
	nRetCode = fwrite(szContent, 1, nContentLen, pFileHandle);
	LOG_PROCESS_ERROR(nRetCode == nContentLen);

	for (QList<QTreeWidgetItem*>::iterator itProcess = lstSelectProcess.begin();
		itProcess != lstSelectProcess.end(); ++itProcess)
	{
		INT32 nAreaID = (*itProcess)->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
		UINT32 dwIp = (*itProcess)->data(enumDataUserRoleIP, Qt::UserRole).toInt();
		UINT32 dwPID = (*itProcess)->data(enumDataUserRolePID, Qt::UserRole).toInt();

		UINT32 dwSessionID = (*itProcess)->data(enumDataUserRoleSessionID, Qt::UserRole).toInt();
		UINT8 byType = (*itProcess)->data(enumDataUserRoleType, Qt::UserRole).toInt();
		LOG_PROCESS_ERROR(byType >= stMS && byType < stClient);

		//
		struct in_addr addr;
		addr.s_addr = dwIp;
		sprintf(szContent, "%s-%d:%d@%s\n", GetServerShortName(byType), dwSessionID, dwPID, inet_ntoa(addr) );
		nContentLen = strlen(szContent);
		nRetCode = fwrite(szContent, 1, nContentLen, pFileHandle);
		LOG_PROCESS_ERROR(nRetCode == nContentLen);

		INF("SnapShoot %s", szContent);
		//
		SnapShootGuardStatisInfoByIp(nAreaID, dwIp, dwPID, szContent);
		nContentLen = strlen(szContent);
		nRetCode = fwrite(szContent, 1, nContentLen, pFileHandle);
		LOG_PROCESS_ERROR(nRetCode == nContentLen);
		//
		nRetCode = fwrite("\n", 1, 1, pFileHandle);
		LOG_PROCESS_ERROR(nRetCode == 1);
	}

	//ui.treeStatisInfo->sortItems(1, Qt::AscendingOrder);
Exit0:
	if (pFileHandle)
	{
		fflush(pFileHandle);
		fclose(pFileHandle);
	}
	return TRUE;
}

BOOL MaintainTool::SnapShootGuardStatisInfoCurrent()
{
	INT32 nRetCode = 0;
	char szContent[16 * 1024] = { 0 };
	INT32 nContentLen = 0;

	FILE* pFileHandle = NULL;
	QTreeWidgetItem* pItem = NULL;
	QString str;
	QList<QTreeWidgetItem*> lstSelectProcess;

	lstSelectProcess = ui.treeGuardProcesses->selectedItems();

	char szTimeStamp[PATH_LEN] = { 0 };
	char szFilePath[PATH_LEN] = { 0 };
	char szWorkPath[PATH_LEN] = { 0 };
	nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
	LOG_PROCESS_ERROR(nRetCode > 0);
	const tm_ex* pNow = localtime_ex();

	snprintf(szTimeStamp, sizeof(szTimeStamp), "%04d_%02d_%02d_%02d_%02d_%02d_%02d",
		pNow->tm_year, pNow->tm_mon, pNow->tm_mday,
		pNow->tm_hour, pNow->tm_min, pNow->tm_sec, pNow->tm_msec);

	snprintf(szFilePath, sizeof(szFilePath), "%s\\log\\snapshoot_%s.tsv", szWorkPath, szTimeStamp);

	pFileHandle = fopen(szFilePath, "wb");
	LOG_PROCESS_ERROR(pFileHandle);

	//
	//sprintf(szContent, "%s\n", szTimeStamp);
	//nContentLen = strlen(szContent);
	//nRetCode = fwrite(szContent, 1, nContentLen, pFileHandle);
	//LOG_PROCESS_ERROR(nRetCode == nContentLen);

	// title line
	sprintf(szContent, "name");
	for (INT32 nStatEntryIndex = statInvalid + 1; nStatEntryIndex < statTotal; nStatEntryIndex++)
	{
		if (g_szStatFieldName[nStatEntryIndex] == NULL)
			continue;

		sprintf(szContent + strlen(szContent), "\t%s", g_szStatFieldName[nStatEntryIndex]);
	}
	szContent[strlen(szContent)] = '\n';
	nContentLen = strlen(szContent);
	nRetCode = fwrite(szContent, 1, nContentLen, pFileHandle);
	LOG_PROCESS_ERROR(nRetCode == nContentLen);
	INF("%s", szContent);
	szContent[0] = '\0';

	for (QList<QTreeWidgetItem*>::iterator itProcess = lstSelectProcess.begin();
		itProcess != lstSelectProcess.end(); ++itProcess)
	{
		INT32 nAreaID = (*itProcess)->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
		UINT32 dwIp = (*itProcess)->data(enumDataUserRoleIP, Qt::UserRole).toInt();
		UINT32 dwPID = (*itProcess)->data(enumDataUserRolePID, Qt::UserRole).toInt();

		UINT32 dwSessionID = (*itProcess)->data(enumDataUserRoleSessionID, Qt::UserRole).toInt();
		UINT8 byType = (*itProcess)->data(enumDataUserRoleType, Qt::UserRole).toInt();
		LOG_PROCESS_ERROR(byType >= stMS && byType < stClient);

		//
		struct in_addr addr;
		addr.s_addr = dwIp;
		sprintf(szContent, "%s-%d:%d@%s", GetServerShortName(byType), dwSessionID, dwPID, inet_ntoa(addr));

		INF("SnapShoot %s", szContent);
		//
		SnapShootGuardStatisInfoCurrentByIp(nAreaID, dwIp, dwPID, szContent + strlen(szContent));
		nContentLen = strlen(szContent);
		nRetCode = fwrite(szContent, 1, nContentLen, pFileHandle);
		LOG_PROCESS_ERROR(nRetCode == nContentLen);
		//
		nRetCode = fwrite("\n", 1, 1, pFileHandle);
		LOG_PROCESS_ERROR(nRetCode == 1);
	}

	//ui.treeStatisInfo->sortItems(1, Qt::AscendingOrder);
Exit0:
	if (pFileHandle)
	{
		fflush(pFileHandle);
		fclose(pFileHandle);
	}
	return TRUE;
}

BOOL MaintainTool::HibernateGuardStatisInfo()
{
	INT32 nRetCode = 0;
	QTreeWidgetItem* pItem = NULL;
	QString str;

	if (ui.actionHibernate->isChecked())
	{
		QList<QTreeWidgetItem*> lstSelectProcess;
		lstSelectProcess = ui.treeGuardProcesses->selectedItems();

		for (QList<QTreeWidgetItem*>::iterator itProcess = lstSelectProcess.begin();
			itProcess != lstSelectProcess.end(); ++itProcess)
		{
			INT32 nAreaID = (*itProcess)->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
			UINT32 dwIp = (*itProcess)->data(enumDataUserRoleIP, Qt::UserRole).toInt();
			UINT32 dwPID = (*itProcess)->data(enumDataUserRolePID, Qt::UserRole).toInt();

			UINT32 dwSessionID = (*itProcess)->data(enumDataUserRoleSessionID, Qt::UserRole).toInt();
			UINT8 byType = (*itProcess)->data(enumDataUserRoleType, Qt::UserRole).toInt();
			LOG_PROCESS_ERROR(byType >= stMS && byType < stClient);

			//
			BeginHibernateGuardStatisInfoByIp(nAreaID, dwIp, dwPID, byType, dwSessionID);
		}
	}
	else
	{
		EndHibernateGuardStatisInfoByIp();
	}

Exit0:
	return TRUE;
}

void MaintainTool::Login(void)
{
	INT32 nRetCode = 0;
	QString strUserName;
	QString strPassword;

	//QInputDialog InputDialog;
	//InputDialog.setLabelText("UserName: ");
	//InputDialog.exec();
	//strUserName = InputDialog.textValue();
	//
	//InputDialog.setLabelText("Password: ");
	//InputDialog.exec();
	//strPassword = InputDialog.textValue();

	//strUserName = "gmjy_yw";
	//strPassword = "asdQWE!@#";

	QDialog dialog(this);
	QFormLayout formLayout( &dialog );

	QLineEdit *nameLineEdit = new QLineEdit();
	formLayout.addRow(tr("&User:"), nameLineEdit);

	QLineEdit *passLineEdit = new QLineEdit();
	passLineEdit->setEchoMode(QLineEdit::Password);
	formLayout.addRow(tr("&Password:"), passLineEdit);

	QDialogButtonBox buttonbox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
	QObject::connect(&buttonbox, SIGNAL(accepted()), &dialog, SLOT(accept()));
	QObject::connect(&buttonbox, SIGNAL(rejected()), &dialog, SLOT(reject()));
	formLayout.addRow(&buttonbox);
		
	if ( dialog.exec() == QDialog::Accepted )
	{
		m_bLogin = TRUE;

		strxcpy(m_szUserName, nameLineEdit->text().toUtf8().data(), sizeof(m_szUserName));
		strxcpy(m_szPassword, passLineEdit->text().toUtf8().data(), sizeof(m_szPassword));

		ui.frameMain->show();
	}

	//strxcpy(m_szUserName, "gmjy_yw", 32);
	//strxcpy(m_szPassword, "asdQWE!@#", 32);
	return;
}

void MaintainTool::Logout(void)
{
	CSessionMgr::GetInstance().CloseAllSession();
	ui.frameMain->hide();
	m_bLogin = FALSE;
	m_szUserName[0] = 0;
	m_szPassword[0] = 0;
}

void MaintainTool::SnapShoot(void)
{
	//SnapShootGuardStatisInfo();
	SnapShootGuardStatisInfoCurrent();
}

void MaintainTool::Hibernate(void)
{
	HibernateGuardStatisInfo();
}

void MaintainTool::OnAreaTreeClick(QTreeWidgetItem*, int)
{
	INT32 nRetCode = 0;
	
	nRetCode = UpdateGuardProcessesInfo();
	LOG_PROCESS_ERROR(nRetCode);

Exit0:
	return;
}

void MaintainTool::OnAreaItemDoubleClicked(QTreeWidgetItem* item, int)
{
	INT32 nRetCode = 0;
	char szTargetPath[COMMON_NAME_LEN] = {0};
	char szIP[32] = {0};
	QString str;

	UINT32 dwAreaID = item->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
	UINT32 dwIp = item->data(enumDataUserRoleIP, Qt::UserRole).toInt();

	PROCESS_ERROR(item->parent() != NULL);

	if ( dwIp > 0 )
	{
		struct in_addr addr;
		addr.s_addr = dwIp;
		snprintf(szIP, sizeof(szIP), "%s", inet_ntoa(addr));
	}

	char szWorkPath[PATH_LEN] = { 0 };
	nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
	LOG_PROCESS_ERROR(nRetCode > 0);
	//QString path = QDir::currentPath();

	snprintf(szTargetPath, sizeof(szTargetPath), "explorer %s/%s/%s/%s", 
		szWorkPath, g_MTConfig.szAreaConfigPath, g_MTConfig.AreaConfig[dwAreaID].szAreaFolderName, szIP);

	str = QString::fromLocal8Bit(szTargetPath);
	str.replace( QChar('/'), QChar('\\') );

	QProcess::startDetached(str);

Exit0:
	return;
}

void MaintainTool::OnVesionWidgetDoubleClicked(const QModelIndex &)
{
	INT32 nRetCode = 0;
	char szTargetPath[COMMON_NAME_LEN] = { 0 };
	QString str;

	char szWorkPath[PATH_LEN] = { 0 };
	nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
	LOG_PROCESS_ERROR(nRetCode > 0);
	//QString path = QDir::currentPath();

	snprintf(szTargetPath, sizeof(szTargetPath), "explorer %s/%s", szWorkPath, g_MTConfig.szVersionPath);

	str = QString::fromLocal8Bit(szTargetPath);
	str.replace(QChar('/'), QChar('\\'));

	QProcess::startDetached(str);

Exit0:
	return;
}

void MaintainTool::OnPatchWidgetDoubleClicked(const QModelIndex &)
{
	INT32 nRetCode = 0;
	char szTargetPath[COMMON_NAME_LEN] = { 0 };
	QString str;

	char szWorkPath[PATH_LEN] = { 0 };
	nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
	LOG_PROCESS_ERROR(nRetCode > 0);
	//QString path = QDir::currentPath();

	snprintf(szTargetPath, sizeof(szTargetPath), "explorer %s/%s", szWorkPath, g_MTConfig.szPatchPath);

	str = QString::fromLocal8Bit(szTargetPath);
	str.replace(QChar('/'), QChar('\\'));

	QProcess::startDetached(str);

Exit0:
	return;
}

void MaintainTool::OnLogDoubleClicked(QListWidgetItem *)
{
	INT32 nRetCode = 0;
	char szTargetPath[COMMON_NAME_LEN] = { 0 };
	QString str;

	char szWorkPath[PATH_LEN] = { 0 };
	nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
	LOG_PROCESS_ERROR(nRetCode > 0);
	//QString path = QDir::currentPath();

	//snprintf(szTargetPath, sizeof(szTargetPath), "explorer %s/%s", szWorkPath, CLog::GetInstance().GetLogFileFolder());
	//str = QString::fromLocal8Bit(szTargetPath);
	//str.replace(QChar('/'), QChar('\\'));
	//QProcess::startDetached(str);

	snprintf(szTargetPath, sizeof(szTargetPath), "explorer %s/%s", szWorkPath, CLog::GetInstance().GetLogFilePath());
	str = QString::fromLocal8Bit(szTargetPath);
	str.replace(QChar('/'), QChar('\\'));
	QProcess::startDetached(str);
Exit0:
	return;
}

BOOL MaintainTool::ExecCmd(const char* pcszCmd)
{
	INT32 nRetCode = 0;
	QList<QTreeWidgetItem*> lstSelectItem;
	lstSelectItem = GetSelectedIpItems();    //ui.treeArea->selectedItems();

	for(QList<QTreeWidgetItem*>::iterator itr = lstSelectItem.begin(); itr != lstSelectItem.end(); ++itr)
    {		
        INT32 nChildCount = (*itr)->childCount();
		LOG_PROCESS_ERROR(nChildCount == 0);
		//if(nChildCount == 0)// guard
		{
			INT32 nAreaID = (*itr)->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
			UINT32 dwIp = (*itr)->data(enumDataUserRoleIP, Qt::UserRole).toInt();

			nRetCode = CMTMessageHandler::GetInstance().DoGDExecCmd(nAreaID, dwIp, pcszCmd);
			if(nRetCode)
				m_nWaitCmdCount++;
		}
	}
	
	PROCESS_ERROR(m_nWaitCmdCount > 0);
	strxcpy(m_szCurCmd, pcszCmd, sizeof(m_szCurCmd));
	m_bCmdResult = TRUE;

	//setDisabled(TRUE);
	return TRUE;
Exit0:
	m_nWaitCmdCount = 0;
	return FALSE;
}

BOOL MaintainTool::UpdateNotifyInfo(QString str)
{
	QListWidgetItem* pItem = NULL;
	pItem = new QListWidgetItem(str);
	LOG_PROCESS_ERROR(pItem);

	pItem->setTextColor(Qt::red);

	QListWidget * listAlert = MaintainTool::GetInstance().ui.listAlert;
	const int MAX_LOG_LIST_ITEMS = 1024;
	if (listAlert->count() > MAX_LOG_LIST_ITEMS && listAlert->count() > 0)
	{
		delete(listAlert->item(0));
	}
	MaintainTool::GetInstance().ui.listAlert->addItem(pItem);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL MaintainTool::UpdateNotifyInfo(UINT32 dwRemoteIP, UINT8 bySvrType, UINT8 bySvrID, UINT8 byLevel, INT32 nErrorCode, const char* szInfo)
{
	INT32 nRetCode = 0;
	QString str;

	char szLocation[MAX_PATH] = {0};
	in_addr addr;
	addr.s_addr = dwRemoteIP;
	snprintf(szLocation, sizeof(szLocation), "%s ", inet_ntoa(addr));

	if (bySvrType == stGD)
	{
		INF("NOTIFY_%d [%s:%d]@%s: %s", byLevel,
			"GD", 0, szLocation, szInfo);
	} 
	else
	{
		INF("NOTIFY_%d [%s:%d]@%s: %s", byLevel,
			GetServerShortName(bySvrType), bySvrID, szLocation, szInfo);
	}
	PROCESS_SUCCESS(nErrorCode == errSuccess);	// no news is good news

	str = QString::fromUtf8(szLocation);
	str += QString::fromUtf8(szInfo);
	str.remove(QChar('\r'));
	str.remove(QChar('\n'));
	str.replace(QChar('\t'), QString::fromUtf8("  "));

	nRetCode = UpdateNotifyInfo(str);
	LOG_PROCESS_ERROR(nRetCode);
Exit1:
	return TRUE;
Exit0:
	return FALSE;
}

BOOL MaintainTool::UpdateCmdResult(UINT32 dwRemoteIP, INT32 nErrorCode, const char* szResult)
{
	char    *pszIP = NULL;
	in_addr addr;
	addr.s_addr = dwRemoteIP;
	pszIP = inet_ntoa(addr);
	LOG_PROCESS_ERROR(pszIP);

	m_nWaitCmdCount--;
	if(m_nWaitCmdCount < 0)
		m_nWaitCmdCount = 0;

	if( nErrorCode != errSuccess )
		m_bCmdResult = FALSE;

	INF("ip %s UpdateCmdResult cmd [%s] result: %s", pszIP, m_szCurCmd, szResult);
	if(m_nWaitCmdCount == 0)
	{
		//INF("cmd %s exec %s: %s", m_szCurCmd, m_bCmdResult ? "success" : "failed", szResult);

		memset(m_szCurCmd, 0, sizeof(m_szCurCmd));
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL MaintainTool::CheckAreaExpanded(INT32 nAreaID)
{
    QTreeWidgetItem *pAreaItem = NULL;

	pAreaItem = _GetAreaWidget(nAreaID);
	PROCESS_ERROR( pAreaItem );

    return pAreaItem->isExpanded() ? TRUE : FALSE;
Exit0:
    return FALSE;
}
//
//BOOL MaintainTool::GetAreaIpList(UINT32 dwAreaID, UINT32& nMaxCount, UINT32* dwIplst)
//{
//	INT32 nRetCode = 0;
//	QTreeWidgetItem *pAreaItem = NULL;
//	QTreeWidgetItem *pGuardItem = NULL;
//	QVariant qValue;
//	INT32 nCountlimit = nMaxCount;
//	nMaxCount = 0;
//
//	INT32 nAreaCount = ui.treeArea->topLevelItemCount();
//	for(INT32 i = 0; i < nAreaCount; ++i)
//	{
//		INT32 nGuardCount = 0;
//		pAreaItem = ui.treeArea->topLevelItem(i);
//		LOG_PROCESS_ERROR(pAreaItem);
//
//		if(pAreaItem->data(enumAreaDataUserRoleAreaID, Qt::UserRole) == dwAreaID)
//		{
//			nGuardCount = pAreaItem->childCount();
//			for(INT32 j = 0; j < nGuardCount; ++j)
//			{
//				pGuardItem = pAreaItem->child(j);
//				LOG_PROCESS_ERROR(pGuardItem);
//
//				qValue = pGuardItem->data(enumAreaDataUserRoleAreaID, Qt::UserRole);
//				dwIplst[nMaxCount++] = qValue.toInt();
//
//				if(nMaxCount >= nCountlimit)
//					break;
//			}
//			break;
//		}
//	}
//
//	return TRUE;
//Exit0:
//	return FALSE;
//}

BOOL MaintainTool::_CheckGuardStateByIp(INT32 nAreaID, UINT32 dwIp)
{
	INT32 nRetCode = 0;

	SRemoteGuardSession* pGuardSession = CSessionMgr::GetInstance().GetRemoteGDSession(nAreaID, dwIp);
	PROCESS_ERROR(pGuardSession);
	PROCESS_ERROR(pGuardSession->pSocketSession);
	PROCESS_ERROR(pGuardSession->bConnected);

	return TRUE;
Exit0:
	return FALSE;
}

void MaintainTool::Start(void)
{
	INT32 nRetCode = 0;
	const char* pcszCmd = "start -apr";
	
	//bool ok;
	//QString text = QInputDialog::getText(this, tr("confirm"),
	//	tr("Are you sure? please input \'yes\'"), QLineEdit::Normal, tr("no"), &ok);
	//if (ok && !text.isEmpty() && text == "yes" )
	{
		nRetCode = ExecCmd(pcszCmd);
		LOG_PROCESS_ERROR(nRetCode);
	}


Exit0:
	return;
}

void MaintainTool::Open(void)
{
	INT32 nRetCode = 0;
	INT32 nGroupID = -1;
	QString strCmd;

	QInputDialog InputDialog;
	InputDialog.setLabelText("GroupID: ");
	InputDialog.exec();
	nGroupID = InputDialog.textValue().toInt();

	LOG_PROCESS_ERROR(nGroupID > -1);
	strCmd.sprintf(".switch %d 1", nGroupID);

	//QString text;
	//bool ok;
	//text = QInputDialog::getText(this, tr("confirm"),
	//	tr("Are you sure? please input \'yes\'"), QLineEdit::Normal, tr("no"), &ok);
	//if (ok && !text.isEmpty() && text == "yes")
	{
		nRetCode = ExecCmd(strCmd.toUtf8().data());
		LOG_PROCESS_ERROR(nRetCode);
	}

	ui.editCmd->clear();
Exit0:
	return;
}

void MaintainTool::Stop(void)
{
	INT32 nRetCode = 0;
	const char* pcszCmd = "stop -f";
	bool ok;
	QString reply;

	QString strAreaInfo;

	QList<QTreeWidgetItem*> lstSelectItem;
	lstSelectItem = GetSelectedIpItems();    //ui.treeArea->selectedItems();

	strAreaInfo.clear();
	for (QList<QTreeWidgetItem*>::iterator itr = lstSelectItem.begin(); itr != lstSelectItem.end(); ++itr)
	{
		INT32 nChildCount = (*itr)->childCount();
		LOG_PROCESS_ERROR(nChildCount == 0);
		//if(nChildCount == 0)// guard
		{
			INT32 nAreaID = (*itr)->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
			UINT32 dwIp = (*itr)->data(enumDataUserRoleIP, Qt::UserRole).toInt();

			QString strIp;
			struct in_addr addr;
			addr.s_addr = dwIp;
			strIp.sprintf("%s", inet_ntoa(addr));

			strAreaInfo += "\t" + strIp + " @ " + (*itr)->data(enumDataUserRoleAreaName, Qt::UserRole).toString() + "\n";
		}
	}

	reply = QInputDialog::getText(this, tr("confirm"),
		QString(" Are you sure to stop these? \n%1 Please input \'yes\'").arg(strAreaInfo), QLineEdit::Normal, tr("no"), &ok);
	if (ok && !reply.isEmpty() && reply == "yes")
	{
		nRetCode = ExecCmd(pcszCmd);
		LOG_PROCESS_ERROR(nRetCode);
	}
Exit0:
	return;
}

void MaintainTool::Close(void)
{
	INT32 nRetCode = 0;
	const char* pcszCmd = "close";
	bool ok;
	QString reply;

	QString strAreaInfo;

	QList<QTreeWidgetItem*> lstSelectItem;
	lstSelectItem = GetSelectedIpItems();    //ui.treeArea->selectedItems();

	strAreaInfo.clear();
	for (QList<QTreeWidgetItem*>::iterator itr = lstSelectItem.begin(); itr != lstSelectItem.end(); ++itr)
	{
		INT32 nChildCount = (*itr)->childCount();
		LOG_PROCESS_ERROR(nChildCount == 0);
		//if(nChildCount == 0)// guard
		{
			INT32 nAreaID = (*itr)->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
			UINT32 dwIp = (*itr)->data(enumDataUserRoleIP, Qt::UserRole).toInt();
			
			QString strIp;
			struct in_addr addr;
			addr.s_addr = dwIp;
			strIp.sprintf("%s", inet_ntoa(addr));

			strAreaInfo += "\t" + strIp + " @ " + (*itr)->data(enumDataUserRoleAreaName, Qt::UserRole).toString() + "\n";
		}
	}

	reply = QInputDialog::getText(this, tr("confirm"),
		QString(" Are you sure to close these? \n%1 Please input \'yes\'").arg(strAreaInfo), QLineEdit::Normal, tr("no"), &ok);
	if (ok && !reply.isEmpty() && reply == "yes")
	{
		nRetCode = ExecCmd(pcszCmd);
		LOG_PROCESS_ERROR(nRetCode);
	}

Exit0:
	return;
}

void MaintainTool::ExecuteCmd(void)
{
	INT32 nRetCode = 0;
	QString strCmd;
	bool ok;
	QString reply;
	QString strAreaInfo;
	QList<QTreeWidgetItem*> lstSelectItem;

	strCmd = ui.editCmd->text();
	PROCESS_ERROR(strCmd.size() > 0);

	lstSelectItem = GetSelectedIpItems();    //ui.treeArea->selectedItems();

	strAreaInfo.clear();
	for (QList<QTreeWidgetItem*>::iterator itr = lstSelectItem.begin(); itr != lstSelectItem.end(); ++itr)
	{
		INT32 nChildCount = (*itr)->childCount();
		LOG_PROCESS_ERROR(nChildCount == 0);
		//if(nChildCount == 0)// guard
		{
			INT32 nAreaID = (*itr)->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
			UINT32 dwIp = (*itr)->data(enumDataUserRoleIP, Qt::UserRole).toInt();

			QString strIp;
			struct in_addr addr;
			addr.s_addr = dwIp;
			strIp.sprintf("%s", inet_ntoa(addr));

			strAreaInfo += "\t" + strIp + " @ " + (*itr)->data(enumDataUserRoleAreaName, Qt::UserRole).toString() + "\n";
		}
	}

	reply = QInputDialog::getText(this, tr("confirm"),
		QString(" Are you sure send cmd \'%1\' to these? \n%2 Please input \'yes\'").arg(strCmd.toUtf8().data(), strAreaInfo), QLineEdit::Normal, tr("no"), &ok);
	if (ok && !reply.isEmpty() && reply == "yes")
	{
		nRetCode = ExecCmd(strCmd.toUtf8().data());
		LOG_PROCESS_ERROR(nRetCode);
	}

	ui.editCmd->clear();
Exit0:
	return;
}

void MaintainTool::VersionRefresh(void)
{
	INT32 nRetCode = 0;

	nRetCode = _RefreshAreaInfo();
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CSessionMgr::GetInstance().Reload();
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CTransmitFileMgr::GetInstance().Reload();
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = _RefreshServerVersion();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = _RefreshServerPatch();
	LOG_CHECK_ERROR(nRetCode);
Exit0:
	return;
}

BOOL MaintainTool::GetSelectVersion( char* pName )
{	
    QListWidgetItem * pItem = ui.listVersion->currentItem();
    if ( NULL == pItem )
    {
        return FALSE;
    }

    strxcpy( pName, pItem->text().toLatin1().data(), COMMON_NAME_LEN);
    return TRUE;
}

BOOL MaintainTool::GetSelectPatch(char* pName)
{
	QListWidgetItem * pItem = ui.listPatch->currentItem();
	if (NULL == pItem)
	{
		return FALSE;
	}

	strxcpy(pName, pItem->text().toLatin1().data(), COMMON_NAME_LEN);
	return TRUE;
}

QList<QTreeWidgetItem*> MaintainTool::GetSelectedIpItems(BOOL bRequireSameParent)
{
	BOOL nRetCode = FALSE;
	INT32 nItemChildCount = 0;
    QList<QTreeWidgetItem*> lstResult = ui.treeArea->selectedItems();
    QList<QTreeWidgetItem*> lstParents;

    for(QList<QTreeWidgetItem*>::iterator itr = lstResult.begin(); itr != lstResult.end();)
    {
        QTreeWidgetItem* pItem = *itr;
        LOG_PROCESS_ERROR(pItem);
		nItemChildCount = pItem->childCount();
        if(nItemChildCount > 0)
        {
            bool bChooseWithChild = false;
            for(int i=0; i<nItemChildCount; ++i)
            {
                bChooseWithChild = lstResult.contains( pItem->child(i) );
                if( bChooseWithChild )
                {
                    break;
                }
            }

            if ( !bChooseWithChild )
            {
                lstParents.append( pItem );
            }
            itr = lstResult.erase(itr);
        }
        else
        {
            ++itr;
        }
    }

	if ( bRequireSameParent )
	{
		QList<QTreeWidgetItem*> lstDumpParents(lstParents);
		for (QList<QTreeWidgetItem*>::iterator itr = lstResult.begin(); itr != lstResult.end(); ++itr)
		{
			LOG_PROCESS_ERROR(*itr);
			QTreeWidgetItem* pParentItem = (*itr)->parent();
			LOG_PROCESS_ERROR(pParentItem);
			if ( !lstDumpParents.contains(pParentItem) )
			{
				lstDumpParents.append(pParentItem);
			}
		}
		if (lstDumpParents.count() > 1)
		{
			CRI( "all selected guard items must in the same area" );
			LOG_PROCESS_ERROR(FALSE);
		}
	}

    for(QList<QTreeWidgetItem*>::iterator itr = lstParents.begin(); itr != lstParents.end(); ++itr)
    {
        QTreeWidgetItem* pItem = *itr;
        LOG_PROCESS_ERROR(pItem);

		nItemChildCount = pItem->childCount();
		for (int i = 0; i < nItemChildCount; ++i)
        {
            lstResult.append( pItem->child(i));
        }
    }

	return lstResult;
Exit0:
	return QList<QTreeWidgetItem*>();
}

BOOL MaintainTool::_GenerateGMSecurityFile(const char* szSrcPath, const char* szDstPath)
{
	BOOL bResult = FALSE;
	INT32 nRetCode = 0;
	char* pBegin = NULL;
	char* pEnd = NULL;
	FILE *pSrcFile = fopen(szSrcPath, "r");
	LOG_PROCESS_ERROR(pSrcFile);

	FILE *pDstFile = fopen(szDstPath, "w");
	LOG_PROCESS_ERROR(pDstFile);

	char szBuff[1024] = {0};
	while (fgets(szBuff, sizeof(szBuff), pSrcFile) != NULL)
	{
		char* pBegin = strstr(szBuff, "szPwd");
		if (pBegin)
		{
			pBegin = strchr(pBegin, '=');
			if (pBegin)
			{
				pBegin = strchr(pBegin, '\"');
				pBegin += 1;

				pEnd = strchr(pBegin, '\"');
				if (pEnd)
				{
					bResult = SimpleEncrypt(pBegin, pEnd - pBegin);
					if (!bResult)
					{
						CRI("gmsecurity invalid character in passwd %s", pBegin);
						LOG_PROCESS_ERROR(FALSE);
					}
				}	
			}
		} 
	
		nRetCode = fputs(szBuff, pDstFile);
		LOG_PROCESS_ERROR(nRetCode >= 0);
	}

Exit0:
	if (pSrcFile)
	{
		fclose(pSrcFile);
		pSrcFile = NULL;
	}
	if (pDstFile)
	{
		fclose(pDstFile);
		pDstFile = NULL;
	}
	return bResult;
}

void MaintainTool::SendVersion(void)
{
	INT32 nRetCode = 0;
	const INT32 MAX_SEND_FILES_NUM = 4;
	QList<QTreeWidgetItem*> lstGuardSelectItem;
	QTreeWidgetItem* pItem = NULL;

    char szVersionFile[COMMON_NAME_LEN] = {0}; 
	char szAreaFile[COMMON_NAME_LEN] = { 0 };
	char szGuardAreaFile[COMMON_NAME_LEN] = { 0 };
	char szGMSecurityConfigFile[COMMON_NAME_LEN] = { 0 };

    char szBasePakPath[COMMON_NAME_LEN] = {0}; 
	char szAreaFilePath[COMMON_NAME_LEN] = { 0 };
	char szGuardAreaFilePath[COMMON_NAME_LEN] = { 0 };
	char szGMSecurityConfigPath[COMMON_NAME_LEN] = { 0 };
	char szGMSecurityConfigOriPath[COMMON_NAME_LEN] = { 0 };
	
	const char* szFiles[MAX_SEND_FILES_NUM] = { NULL };
	szFiles[0] = szVersionFile;
	szFiles[1] = szGuardAreaFile;
	szFiles[2] = szAreaFile;
	szFiles[3] = szGMSecurityConfigFile;

	const char* szFilePaths[MAX_SEND_FILES_NUM] = { NULL };
	szFilePaths[0] = szBasePakPath;
	szFilePaths[1] = szGuardAreaFilePath;
    szFilePaths[2] = szAreaFilePath;
	szFilePaths[3] = szGMSecurityConfigPath;

    char szVersionName[COMMON_NAME_LEN] = {0}; 
    nRetCode = GetSelectVersion( szVersionName );
    LOG_PROCESS_ERROR( nRetCode && szVersionName[0] != '\0' );

	// get work path
	char szWorkPath[PATH_LEN] = { 0 };
	nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
	LOG_PROCESS_ERROR(nRetCode > 0);

	// send every ip
    lstGuardSelectItem = GetSelectedIpItems();//get select guard
    for(QList<QTreeWidgetItem*>::iterator itr = lstGuardSelectItem.begin(); itr != lstGuardSelectItem.end(); ++itr)
    {
        pItem = *itr;
        LOG_PROCESS_ERROR( pItem );

		UINT32 dwIp = pItem->data(enumDataUserRoleIP, Qt::UserRole).toUInt();
		LOG_PROCESS_ERROR(dwIp > 0);
		struct in_addr addr;
		addr.s_addr = dwIp;

		INT32 nAreaID = pItem->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
        LOG_PROCESS_ERROR( nAreaID > 0 && nAreaID < MAX_AREA_COUNT );

        nRetCode = _CheckGuardStateByIp(nAreaID, dwIp);
        LOG_PROCESS_ERROR(nRetCode);

        snprintf(szVersionFile, sizeof(szVersionFile), "%s", szVersionName );
		snprintf(szAreaFile, sizeof(szAreaFile), "%s-area_config.lua", szVersionName);
		snprintf(szGuardAreaFile, sizeof(szGuardAreaFile), "%s-guard_area_config.lua", szVersionName);
		snprintf(szGMSecurityConfigFile, sizeof(szGMSecurityConfigFile), "%s-gmsecurityconfig.lua", szVersionName);

		char szAreaFolderPath[PATH_LEN] = { 0 };
		sprintf(szAreaFolderPath, "%s\\area_config\\%s", szWorkPath, g_MTConfig.AreaConfig[nAreaID].szAreaFolderName);
		char szIpFolderPath[PATH_LEN] = { 0 };
		sprintf(szIpFolderPath, "%s\\%s", szAreaFolderPath, inet_ntoa(addr));

		//const char* szTargetLuacFile = "area_config_compiled.lua";
		//// luac compiled szTargetLuacFile
		//{
		//	char szParam[PATH_LEN] = { 0 };
		//	sprintf(szParam, "-o %s\\%s %s\\%s", szIpFolderPath, szTargetLuacFile, szIpFolderPath, "area_config.lua");
		//	nRetCode = (INT32)ShellExecute(NULL, "open", "luac64.exe", szParam, NULL, SW_HIDE);// _getcwd(NULL, 0)
		//	LOG_PROCESS_ERROR(nRetCode > 32);
		//}

		snprintf(szBasePakPath, sizeof(szBasePakPath), "%s\\%s", m_szVersionPath, szVersionName);
		snprintf(szAreaFilePath, sizeof(szAreaFilePath), "%s\\area_config.lua", szAreaFolderPath);
		snprintf(szGuardAreaFilePath, sizeof(szGuardAreaFilePath), "%s\\guard_area_config.lua", szIpFolderPath);

		snprintf(szGMSecurityConfigPath, sizeof(szGMSecurityConfigPath), "%s\\area_config\\gmsecurityconfig-encrypted.lua", szWorkPath);
		snprintf(szGMSecurityConfigOriPath, sizeof(szGMSecurityConfigOriPath), "%s\\area_config\\gmsecurityconfig.lua", szWorkPath);
		nRetCode = _GenerateGMSecurityFile(szGMSecurityConfigOriPath, szGMSecurityConfigPath);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CTransmitFileMgr::GetInstance().StartSending(nAreaID, dwIp, 4, szFiles, szFilePaths, InternalMessage::etftVersion);
        LOG_PROCESS_ERROR(nRetCode);
    }

	INF("sending version %s, wait please", szVersionName);
	return;
Exit0:
	INF("sending version %s failed", szVersionName);
	return;
}

void MaintainTool::SendConfig(void)
{
	INT32 nRetCode = 0; 
	QString strVersionName;
	const INT32 MAX_SEND_FILES_NUM = 4;
	QList<QTreeWidgetItem*> lstGuardSelectItem;
	QTreeWidgetItem* pItem = NULL;

	char szAreaFile[COMMON_NAME_LEN] = { 0 };
	char szGuardAreaFile[COMMON_NAME_LEN] = { 0 };
	char szGMSecurityConfigFile[COMMON_NAME_LEN] = { 0 };

	char szAreaFilePath[COMMON_NAME_LEN] = { 0 };
	char szGuardAreaFilePath[COMMON_NAME_LEN] = { 0 };
	char szGMSecurityConfigPath[COMMON_NAME_LEN] = { 0 };
	char szGMSecurityConfigOriPath[COMMON_NAME_LEN] = { 0 };

	const char* szFiles[MAX_SEND_FILES_NUM] = { NULL };
	szFiles[0] = szGuardAreaFile;
	szFiles[1] = szAreaFile;
	szFiles[2] = szGMSecurityConfigFile;

	const char* szFilePaths[MAX_SEND_FILES_NUM] = { NULL };
	szFilePaths[0] = szGuardAreaFilePath;
	szFilePaths[1] = szAreaFilePath;
	szFilePaths[2] = szGMSecurityConfigPath;

	// get work path
	char szWorkPath[PATH_LEN] = { 0 };
	nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
	LOG_PROCESS_ERROR(nRetCode > 0);

	// send every ip
	lstGuardSelectItem = GetSelectedIpItems();//get select guard
	for (QList<QTreeWidgetItem*>::iterator itr = lstGuardSelectItem.begin(); itr != lstGuardSelectItem.end(); ++itr)
	{
		pItem = *itr;
		LOG_PROCESS_ERROR(pItem);

		UINT32 dwIp = pItem->data(enumDataUserRoleIP, Qt::UserRole).toUInt();
		LOG_PROCESS_ERROR(dwIp > 0);
		struct in_addr addr;
		addr.s_addr = dwIp;

		INT32 nAreaID = pItem->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
		LOG_PROCESS_ERROR(nAreaID > 0 && nAreaID < MAX_AREA_COUNT);

		char szVersionName[COMMON_NAME_LEN] = { 0 };
		//nRetCode = GetSelectVersion(szVersionName);
		//if (szVersionName[0] == '\0')
		{
			QTreeWidgetItem* pParentItem = pItem->parent();
			strVersionName = pParentItem->data(enumDataUserRoleVersion, Qt::UserRole).toString(); // current version config
			LOG_PROCESS_ERROR(!strVersionName.isEmpty());
			strxcpy(szVersionName, strVersionName.toLatin1().data(), sizeof(szVersionName));
		} 
		LOG_PROCESS_ERROR(szVersionName[0] != '\0');

		nRetCode = _CheckGuardStateByIp(nAreaID, dwIp);
		LOG_PROCESS_ERROR(nRetCode);

		snprintf(szAreaFile, sizeof(szAreaFile), "area_config.lua");
		snprintf(szGMSecurityConfigFile, sizeof(szGMSecurityConfigFile), "gmsecurityconfig.lua");
		snprintf(szGuardAreaFile, sizeof(szGuardAreaFile), "guard_area_config.lua", szVersionName);

		char szAreaFolderPath[PATH_LEN] = { 0 };
		sprintf(szAreaFolderPath, "%s\\area_config\\%s", szWorkPath, g_MTConfig.AreaConfig[nAreaID].szAreaFolderName);
		char szIpFolderPath[PATH_LEN] = { 0 };
		sprintf(szIpFolderPath, "%s\\area_config\\%s\\%s", szWorkPath, g_MTConfig.AreaConfig[nAreaID].szAreaFolderName, inet_ntoa(addr));

		snprintf(szAreaFilePath, sizeof(szAreaFilePath), "%s\\area_config.lua", szAreaFolderPath);
		snprintf(szGuardAreaFilePath, sizeof(szGuardAreaFilePath), "%s\\guard_area_config.lua", szIpFolderPath);

		snprintf(szGMSecurityConfigPath, sizeof(szGMSecurityConfigPath), "%s\\area_config\\gmsecurityconfig-encrypted.lua", szWorkPath);
		snprintf(szGMSecurityConfigOriPath, sizeof(szGMSecurityConfigOriPath), "%s\\area_config\\gmsecurityconfig.lua", szWorkPath);
		nRetCode = _GenerateGMSecurityFile(szGMSecurityConfigOriPath, szGMSecurityConfigPath);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CTransmitFileMgr::GetInstance().StartSending(nAreaID, dwIp, 3, szFiles, szFilePaths, InternalMessage::etftConfig);
		LOG_PROCESS_ERROR(nRetCode);
	}

	INF("sending config , wait please");
	return;
Exit0:
	INF("sending config failed");
	return;
}

void MaintainTool::SendPatch()
{
    INT32 nRetCode = 0;
    QList<QTreeWidgetItem*> lstGuardSelectItem;
    QTreeWidgetItem* pItem = NULL;

    char szFileName[COMMON_NAME_LEN] = {0}; 
    char szFilePath[COMMON_NAME_LEN] = {0}; 

    nRetCode = GetSelectPatch( szFileName );
    LOG_PROCESS_ERROR( nRetCode && szFileName[0] );

	char szWorkPath[PATH_LEN] = { 0 };
	nRetCode = GetCurrentDirectory(sizeof(szWorkPath), szWorkPath);
	LOG_PROCESS_ERROR(nRetCode > 0);
    //strncat(szFileName, ".pak", sizeof(szFileName) );
	snprintf(szFilePath, sizeof(szFilePath), "%s\\%s", m_szPatchPath, szFileName);

    lstGuardSelectItem = GetSelectedIpItems(); //get select guard
    for(QList<QTreeWidgetItem*>::iterator itr = lstGuardSelectItem.begin(); itr != lstGuardSelectItem.end(); ++itr)
    {
        pItem = *itr;
        LOG_PROCESS_ERROR( pItem );

		UINT32 dwIp = pItem->data(enumDataUserRoleIP, Qt::UserRole).toUInt();
		LOG_PROCESS_ERROR(dwIp > 0);
		INT32 nAreaID = pItem->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
		LOG_PROCESS_ERROR(nAreaID > 0 && nAreaID < MAX_AREA_COUNT);

        nRetCode = _CheckGuardStateByIp(nAreaID, dwIp);
        LOG_PROCESS_ERROR(nRetCode);

        const char* szFiles[4] = {0};
        szFiles[0] = szFileName;
        const char* szFilePaths[4] = {0};
        szFilePaths[0] = szFilePath;

		nRetCode = CTransmitFileMgr::GetInstance().StartSending(nAreaID, dwIp, 1, szFiles, szFilePaths, InternalMessage::etftPatch);
        LOG_PROCESS_ERROR(nRetCode);
    }

    INF("sending patch %s, wait please", szFileName );
    return;
Exit0:
    INF("sending patch %s failed", szFileName );
    return;
}

void MaintainTool::DeployVersion(void)
{
	INT32 nRetCode = 0;
	QList<QTreeWidgetItem*> lstGuardSelectItem;
	QTreeWidgetItem* pItem = NULL;

    char szFileName[COMMON_NAME_LEN] = {0}; 
    nRetCode = GetSelectVersion( szFileName );
	if (!nRetCode || szFileName[0] == '\0')
	{
		CRI("please select a version first");
		PROCESS_ERROR(FALSE);
	}

	lstGuardSelectItem = GetSelectedIpItems(); //ui.treeArea->selectedItems();
	if(lstGuardSelectItem.count() == 0)
	{
		CRI("please select area or guard");
		PROCESS_ERROR(FALSE);
	}

	for(QList<QTreeWidgetItem*>::iterator itr = lstGuardSelectItem.begin(); itr != lstGuardSelectItem.end(); ++itr)
	{
		pItem = *itr;
        LOG_PROCESS_ERROR( pItem && pItem->childCount() == 0 );

		UINT32 dwIp = pItem->data(enumDataUserRoleIP, Qt::UserRole).toUInt();
		LOG_PROCESS_ERROR(dwIp > 0);
		INT32 nAreaID = pItem->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
		LOG_PROCESS_ERROR(nAreaID > 0 && nAreaID < MAX_AREA_COUNT);

        nRetCode = _CheckGuardStateByIp(nAreaID, dwIp);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = CMTMessageHandler::GetInstance().DoGDDeployServerVersion(nAreaID, dwIp, szFileName );
        LOG_PROCESS_ERROR(nRetCode);
	}

	INF("deploy version:%s, please wait", szFileName );
	//ui.frameMain->setEnabled(false);

	return;
Exit0:
	INF("deploy version:%s failed", szFileName );

	return;
}

void MaintainTool::HotUpdatePatch(void)
{
	INT32 nRetCode = 0;
	QList<QTreeWidgetItem*> lstGuardSelectItem;
	QTreeWidgetItem* pItem = NULL;

	char szFileName[COMMON_NAME_LEN] = { 0 };
	nRetCode = GetSelectPatch(szFileName);
	LOG_PROCESS_ERROR(nRetCode && szFileName[0]);
	//strncat( szFileName, ".pak", sizeof(szFileName) );

	lstGuardSelectItem = GetSelectedIpItems(); //ui.treeArea->selectedItems();
	if (lstGuardSelectItem.count() == 0)
	{
		CRI("please select area or guard");
		PROCESS_ERROR(FALSE);
	}

	for (QList<QTreeWidgetItem*>::iterator itr = lstGuardSelectItem.begin(); itr != lstGuardSelectItem.end(); ++itr)
	{
		pItem = *itr;
		LOG_PROCESS_ERROR(pItem && pItem->childCount() == 0);

		UINT32 dwIp = pItem->data(enumDataUserRoleIP, Qt::UserRole).toUInt();
		LOG_PROCESS_ERROR(dwIp > 0);
		INT32 nAreaID = pItem->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
		LOG_PROCESS_ERROR(nAreaID > 0 && nAreaID < MAX_AREA_COUNT);

		nRetCode = _CheckGuardStateByIp(nAreaID, dwIp);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = CMTMessageHandler::GetInstance().DoGDHotUpdatePatch(nAreaID, dwIp, szFileName);
		LOG_PROCESS_ERROR(nRetCode);
	}

	INF("hot update patch:%s, please wait", szFileName);
	//ui.frameMain->setEnabled(false);

	return;
Exit0:
	INF("hot update patch:%s failed", szFileName);

	return;
}

BOOL MaintainTool::SetAreaVersion(INT32 nAreaID, const char* pcszVersion)
{
	QTreeWidgetItem* pAreaItem = NULL;
	QVariant AreaName;
	QString strAreaInfo;

    LOG_PROCESS_ERROR(pcszVersion);
	
	pAreaItem = _GetAreaWidget(nAreaID);
	LOG_PROCESS_ERROR(pAreaItem);

	AreaName = pAreaItem->data(enumDataUserRoleAreaName, Qt::UserRole);
	strAreaInfo = AreaName.toString() + pcszVersion;

	pAreaItem->setText(enumAreaTextColumnName, strAreaInfo);
	pAreaItem->setTextColor(enumAreaTextColumnName, Qt::black);

	pAreaItem->setData(enumDataUserRoleVersion, Qt::UserRole, pcszVersion);

    return TRUE;
Exit0:
    return FALSE;
}

QTreeWidgetItem* MaintainTool::_GetGuardWidget(INT32 nAreaID, UINT32 dwIp)
{
	INT32 nRetCode = 0;
	INT32 nAreaCount = ui.treeArea->topLevelItemCount();
	QTreeWidgetItem* pResult = NULL;

	LOG_PROCESS_ERROR(nAreaID < MAX_AREA_COUNT);

	// get target
	for (INT32 i = 0; i < nAreaCount; ++i)
	{
		QTreeWidgetItem* pAreaItem = ui.treeArea->topLevelItem(i);
		if (pAreaItem && pAreaItem->data(enumDataUserRoleAreaID, Qt::UserRole) == nAreaID)
		{
			INT32 nGuardCount = pAreaItem->childCount();
			for (INT32 j = 0; j < nGuardCount; ++j)
			{
				QTreeWidgetItem* pGuardItem = pAreaItem->child(j);
				if (pGuardItem->data(enumDataUserRoleIP, Qt::UserRole) == dwIp)
				{
					pResult = pGuardItem;
					break;
				}
			}
			break;
		}
	}
	LOG_PROCESS_ERROR(pResult);
Exit0:
	return pResult;
}

QTreeWidgetItem* MaintainTool::_GetAreaWidget(INT32 nAreaID)
{
	INT32 nRetCode = 0;
	INT32 nAreaCount = ui.treeArea->topLevelItemCount();
	QTreeWidgetItem* pResult = NULL;

	LOG_PROCESS_ERROR(nAreaID < MAX_AREA_COUNT);

	// get target
	for (INT32 i = 0; i < nAreaCount; ++i)
	{
		QTreeWidgetItem* pAreaItem = ui.treeArea->topLevelItem(i);
		if (pAreaItem && pAreaItem->data(enumDataUserRoleAreaID, Qt::UserRole) == nAreaID)
		{
			pResult = pAreaItem;
			break;
		}
	}
	LOG_PROCESS_ERROR(pResult);
Exit0:
	return pResult;
}

BOOL MaintainTool::_HasUpdatedWholeArea(INT32 nAreaID, UINT32 dwIp, const char* pcszVersion)
{
	BOOL bHasUpdateWholeArea = TRUE;

	//check and update config
	for (INT32 i = 1; i < MAX_AREA_COUNT; ++i)
	{
		if (g_MTConfig.AreaConfig[i].areaID == nAreaID)
		{
			for (INT32 j = 1; j < MAX_GUARD_COUNT_PER_AREA; ++j)
			{
				if (g_MTConfig.AreaConfig[i].guardList[j].szAddress[0] != 0)
				{
					INT32 dwCurAddr = inet_addr(g_MTConfig.AreaConfig[i].guardList[j].szAddress);
					if (dwCurAddr == dwIp)
					{
						strxcpy(g_MTConfig.AreaConfig[i].guardList[j].szGuardVersion,
							pcszVersion, sizeof(g_MTConfig.AreaConfig[i].guardList[j].szGuardVersion));
					}
					else if (strnicmp(g_MTConfig.AreaConfig[i].guardList[j].szGuardVersion,
						pcszVersion, sizeof(g_MTConfig.AreaConfig[i].guardList[j].szGuardVersion)) != 0)
					{
						bHasUpdateWholeArea = FALSE;
					}
				}
			}

			if (bHasUpdateWholeArea)
			{
				strxcpy(g_MTConfig.AreaConfig[i].szVersion, pcszVersion, sizeof(g_MTConfig.AreaConfig[i].szVersion));
			}
			break;
		}
	}
	return bHasUpdateWholeArea;
}

BOOL MaintainTool::DeployVersionResultByIp(INT32 nAreaID, UINT32 dwIp, const char* pcszVersion, INT32 nErrorCode)
{
	INT32 nRetCode = 0;

    QTreeWidgetItem* pTargetAreaItem = NULL;
    QTreeWidgetItem* pTargetGuardItem = NULL;
	BOOL bHasDeployWholeArea = TRUE;

	struct in_addr addr = {};
	addr.s_addr = dwIp;

	pTargetGuardItem = _GetGuardWidget(nAreaID, dwIp);
	LOG_PROCESS_ERROR(pTargetGuardItem);

	PROCESS_ERROR(nErrorCode == errSuccess);

    INF("ip:%s deploy version:%s success", inet_ntoa(addr), pcszVersion);

	bHasDeployWholeArea = _HasUpdatedWholeArea(nAreaID, dwIp, pcszVersion);
	if(bHasDeployWholeArea)
	{
		pTargetAreaItem = _GetAreaWidget(nAreaID);
		LOG_PROCESS_ERROR(pTargetAreaItem);

		QVariant AreaName = pTargetAreaItem->data(enumDataUserRoleAreaName, Qt::UserRole);
		QString strAreaInfo = AreaName.toString() + pcszVersion;

        pTargetAreaItem->setText(0, strAreaInfo);
        pTargetAreaItem->setData(1, Qt::UserRole, pcszVersion);
        pTargetAreaItem->setTextColor(0, Qt::black);

		INF("Area:%d deploy version:%s success", nAreaID, pcszVersion);
	}

    if( pTargetGuardItem )
    {
        char szText[128] = {0};
        sprintf(szText, "deploy ok: %s", pcszVersion);
        pTargetGuardItem->setText(4, szText );
    }

	return TRUE;

Exit0:
    CRI("Area:%d IP:%s deploy version:%s failed", nAreaID, inet_ntoa(addr), pcszVersion);
	//ui.frameMain->setEnabled(true);

    if ( pTargetGuardItem )
    {
        char szProgress[128] = {0};
        sprintf(szProgress, "deploy error: %d, details see log", nErrorCode);
        pTargetGuardItem->setText(4, szProgress );
    }

	return FALSE;
}

BOOL MaintainTool::HotUpdatePatchResultByIp(INT32 nAreaID, UINT32 dwIp, const char* pcszVersion, INT32 nErrorCode)
{
	INT32 nRetCode = 0;

	QTreeWidgetItem* pTargetAreaItem = NULL;
	QTreeWidgetItem* pTargetGuardItem = NULL;
	BOOL bHasDeployWholeArea = TRUE;

	struct in_addr addr;
	addr.s_addr = dwIp;

	pTargetGuardItem = _GetGuardWidget(nAreaID, dwIp);
	LOG_PROCESS_ERROR(pTargetGuardItem);

	PROCESS_ERROR(nErrorCode == errSuccess);

	INF("ip:%s hot patch:%s success", inet_ntoa(addr), pcszVersion);

	bHasDeployWholeArea = _HasUpdatedWholeArea(nAreaID, dwIp, pcszVersion);
	if (bHasDeployWholeArea)
	{
		pTargetAreaItem = _GetAreaWidget(nAreaID);
		LOG_PROCESS_ERROR(pTargetAreaItem);

		QVariant AreaName = pTargetAreaItem->data(enumDataUserRoleAreaName, Qt::UserRole);
		QString strAreaInfo = AreaName.toString() + pcszVersion;

		pTargetAreaItem->setText(0, strAreaInfo);
		pTargetAreaItem->setData(1, Qt::UserRole, pcszVersion);
		pTargetAreaItem->setTextColor(0, Qt::black);

		INF("Area:%d hot patch:%s success", nAreaID, pcszVersion);
	}

	if (pTargetGuardItem)
	{
		char szText[128] = { 0 };
		sprintf(szText, "hot patch ok: %s", pcszVersion);
		pTargetGuardItem->setText(4, szText);
	}

	return TRUE;

Exit0:
	CRI("Area:%d IP:%s hot patch:%s failed, error code = %d", nAreaID, inet_ntoa(addr), pcszVersion, nErrorCode);
	//ui.frameMain->setEnabled(true);

	if (pTargetGuardItem)
	{
		char szProgress[128] = { 0 };
		sprintf(szProgress, "hot patch error: %d", nErrorCode);
		pTargetGuardItem->setText(4, szProgress);
	}

	return FALSE;
}

void MaintainTool::CleanLog(void)
{
	ui.listLog->clear();
}

void MaintainTool::CleanAlert(void)
{
	ui.listAlert->clear();
}

void MaintainTool::LogFilter(const QString& text)
{
	for (INT32 nIndex = 0; nIndex < ui.listLog->count(); nIndex++)
	{
		QListWidgetItem* pItem = ui.listLog->item(nIndex);
		LOG_PROCESS_ERROR(pItem);

		if (pItem->text().contains(text, Qt::CaseInsensitive))
			pItem->setHidden(false);
		else
			pItem->setHidden(true);
	}

Exit0:
	return;
}

void MaintainTool::AlertFilter(const QString& text)
{
	for (INT32 nIndex = 0; nIndex < ui.listAlert->count(); nIndex++)
	{
		QListWidgetItem* pItem = ui.listAlert->item(nIndex);
		LOG_PROCESS_ERROR(pItem);

		if (pItem->text().contains(text, Qt::CaseInsensitive))
			pItem->setHidden(false);
		else
			pItem->setHidden(true);
	}

Exit0:
	return;
}

void MaintainTool::OnStatisInfoItemDoubleClicked(QTreeWidgetItem * item, int column)
{
  //  QTreeWidgetItem* pAreaItem = ui.treeArea->selectedItems().front();
  //  if (pAreaItem && pAreaItem->childCount() == 0)
  //  {
  //	  QVariant qValue = pAreaItem->data(enumAreaDataUserRoleIP, Qt::UserRole);
  //      UINT32 dwIp = qValue.toInt();

	QList<QTreeWidgetItem*> lstSelectProcess;
	lstSelectProcess = ui.treeGuardProcesses->selectedItems();
	PROCESS_ERROR(lstSelectProcess.count() == 1);

	QTreeWidgetItem* pProcessItem = lstSelectProcess.front();
		INT32 nAreaID = pProcessItem->data(enumDataUserRoleAreaID, Qt::UserRole).toInt();
		UINT32 dwIp = pProcessItem->data(enumDataUserRoleIP, Qt::UserRole).toInt();
        if (pProcessItem)
        {
			UINT32 dwProcess = pProcessItem->data(enumDataUserRolePID, Qt::UserRole).toInt();

            if (item)
            {
                INT32 nStatisIndex = item->data(0, Qt::UserRole).toInt();

                g_MonitorList[g_nLastSetMonitor].dwIp = dwIp;
                g_MonitorList[g_nLastSetMonitor].dwProcess = dwProcess;
                g_MonitorList[g_nLastSetMonitor].nIndex = nStatisIndex;

				QString strArea, strProcess;
				strArea.sprintf("Area %d", nAreaID);
				strProcess.sprintf("%s [%s]", pProcessItem->text(1), pProcessItem->text(0).toUtf8().data() );
                g_MonitorList[g_nLastSetMonitor].pLabel->setText(
					QString("%1 %2 %3").arg(strArea).arg(strProcess).arg(g_szStatFieldName[nStatisIndex]));
                g_nLastSetMonitor = (g_nLastSetMonitor + 1) % MAX_MONITOR_COUNT;
            }
        }
  //  }
Exit0:
		return;
}
