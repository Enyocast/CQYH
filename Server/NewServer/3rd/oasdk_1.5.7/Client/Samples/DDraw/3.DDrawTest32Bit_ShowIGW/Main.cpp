#include <Windows.h>
#include "Application.h"

#define WIN32_LEAN_AND_MEAN

int WINAPI WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nShowCmd )
{
    CApplication app( hInstance );
    if ( app.Initialize() )
        app.Run();
    return 0;
}