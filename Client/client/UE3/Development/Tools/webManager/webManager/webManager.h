
#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif


extern "C" DLL_EXPORT  HWND dllCreatWebWindow(HWND hnd);
extern "C" DLL_EXPORT  BOOL dllCreatWebWindowTitle(const TCHAR* szTitleName,const TCHAR* szTitleIcon,const TCHAR* szCloseIcon);
extern "C" DLL_EXPORT  void dllOpenUrl(const TCHAR*  szUrl);
extern "C" DLL_EXPORT  void dllReDrawWebWindow();
extern "C" DLL_EXPORT  void dllReleaseWeb();
