#include "stdafx.h"

#include <QtGui/QApplication>

#include "bt_config.h"
#include "bt_script.h"
#include "btree_file.h"
#include "bteditorwindow.h"
#include "script_mgr.h"

extern LUA_FUNC g_EditorScriptFuncTable[];
int sol_e_enum_open (lua_State* L);

int InitScript( const char* pszScriptPath )
{
	int nRetCode = 0;

	nRetCode = CLog::GetInstance().Init("bt_editor", lltAll, lotAll, FALSE, FALSE, TRUE);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CScriptMgr::GetInstance().Init( pszScriptPath );
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CScriptMgr::GetInstance().RegisterPackage("enum.pkg", sol_e_enum_open);

	nRetCode = CScriptMgr::GetInstance().RegisterFuncList(g_EditorScriptFuncTable);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

int main(int argc, char *argv[])
{
    int nRetCode = 0;
	QApplication app(argc, argv);
    app.setApplicationName(app.translate("main", "bt editor"));
    //app.setWindowIcon(QIcon(":/icon.png"));

    BTEditorWindow win;

    nRetCode = InitScript("commonconfig/script");
	LOG_PROCESS_ERROR(nRetCode);

    nRetCode = BTConfig::GetInstance().LoadConfigFile();
    LOG_PROCESS_ERROR(nRetCode);

	nRetCode = g_BTreeFile.Init();
	LOG_PROCESS_ERROR(nRetCode);

    const char* pcszFileName = NULL;
    if ( argc > 1 )
    {
        pcszFileName = argv[1]; //("script\\ai\\ImmolithBOSS02\\main.uh");
    }

	nRetCode = win.Init( pcszFileName );
	LOG_PROCESS_ERROR(nRetCode);

    win.showMaximized();

    app.exec();

Exit0:
	return 0;
}
