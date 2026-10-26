#include "stdafx.h"
#include "gmtool.h"
#include "loader.h"
#include "gm_manager.h"

extern loader  g_loader;
extern gmtool  g_gmtool;
INT32   g_State;
extern QApplication app;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
    INT32       nRetCode = 0;
    INT32       nResult  = 0;

    nRetCode = CGMManager::GetInstance().Init();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_gmtool.Init();
    LOG_PROCESS_ERROR(nRetCode);
    {
        g_State = 1;
        if (g_loader.exec() == QDialog::Accepted)
        {
            g_State = 2;
            return app.exec();
        }
    }
    

    return 0;
Exit0:
    return 1;
}
