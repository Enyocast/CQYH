#include "windows.h"
#include "max.h"
#include "bmmlib.h"
#include "guplib.h"
#include "notify.h"
#include "resource.h"
#include "MaxIcon.h"
//#include "ActionTable.h" // This is for the keyboard shortcut APIs
//#include "imacroscript.h" // This is to use methods of MacroDir and MacroEntry


TCHAR *GetStrings(int id);
ClassDesc* GetSaveVerificationDesc();
extern ClassDesc* GetCUITestDesc();

#define TBITEM(type, pIcon, cmd) \
	ToolButtonItem(type,pIcon,GetCUIFrameMgr()->GetImageSize(),GetCUIFrameMgr()->GetImageSize(),GetCUIFrameMgr()->GetButtonWidth(),GetCUIFrameMgr()->GetButtonHeight(),cmd,0)
#define TBMACRO(md) \
	ToolMacroItem(0, GetCUIFrameMgr()->GetButtonHeight(), md)

#define ID_TB_00 1000
#define ID_TB_0 10000
#define ID_TB_1 10001
#define ID_TB_2 10002
#define ID_TB_3 10003
#define ID_TB_4 10004
#define ID_TB_5 10005
#define ID_TB_6 10006
#define ID_TB_7 10007
#define ID_TB_8 10008
#define ID_TB_9 10009
#define ID_TB_10 10010
#define ID_TB_11 10011
#define ID_TB_12 10012

class SaveVerificationGUP : public GUP {
	public:
		SaveVerificationGUP();
		~SaveVerificationGUP();
	    ICUIFrame* GetICUIFrame();
	
		DWORD	Start();
		void	Stop();
		DWORD_PTR	Control(DWORD parameter);
		void	DeleteThis();

		void	ValidateFile(const TSTR& filename);
		bool	ValidateStreams(const TSTR& filename);
		bool	HasStream(IStorage* storage, TSTR stream);

		static void	PostSaveCallback(void* param, NotifyInfo*);

	    Interface *ip;

		HIMAGELIST hImageTB;
	
		//HWND hToolbarWnd; // CUIFrameWindow handle
};

static SaveVerificationGUP theCUITest;