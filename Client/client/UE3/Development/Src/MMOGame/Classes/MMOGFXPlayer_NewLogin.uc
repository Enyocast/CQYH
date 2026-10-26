class MMOGFXPlayer_NewLogin extends MMOGFXPlayer
	native(UI)
	config(MMOGame);


var MMOUILoginPanel            LoginPanel;
var MMOUISelectRolePanel       SelectPanel;
var MMOUICreateRolePanel       CreatePanel;
var MMOUILoginRevertRolePanel  RevertPanel;

// function ASRegisterLoginModule( MMOUILoginPanel mc )
// {        
// 	LoginPanel = mc;
// 	RegisterUI( mc, class'MMOUIManager'.default.Panel_Login_User);
// }
// 
// function ASRegisterSelectRoleModule( MMOUISelectRolePanel mc )
// {        
// 	SelectPanel = mc;
// 	RegisterUI( mc, class'MMOUIManager'.default.Panel_Login_Select);
// }
// 
// function ASRegisterCreateModule( MMOUICreateRolePanel mc )
// {        
// 	CreatePanel = mc;
// 	RegisterUI( mc, class'MMOUIManager'.default.Panel_Login_Create);
// }
// 
// function ASRegisterFindRoleModule(MMOUILoginRevertRolePanel mc)
// {
// 	RevertPanel = mc;
// 	RegisterUI( mc, class'MMOUIManager'.default.Panel_Login_Revert);
// }

function ASLogoEnd()
{        
	LoginPanel.ShowFreePkDlg();
}

//native final function ASRoleMove(int offX,int offY);

//  Panel_Login_User  = "User";
//  Panel_Login_Select  = "Select";
//  Panel_Login_Create  = "Create";

native function ASCheckFirst(GFxObject mc);

native function PostAdvance(float DeltaTime );
//--------------------------------------------------------------------------------------------------

native final function EnterCharactorSelect();

native final function ListWidgetMovieEnd();

native final function EnterCreateRole();

native final function CreateRoleCancel();

native final function GameEvent_LoginGameSuccess();
native final function GameEvent_CreateSuccess();
native final function GameEvent_EnterGameSuccess();
native final function GameEvent_EnterGameEnd();

native function bool NativeCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);
event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	if( NativeCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace) == false)
	{
		return false;
	}
	return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}


//login---------------------------------------------------------------------------------------------
function ASLoginGame(GFxObject loginData)
{
	LoginPanel.LoginGame(loginData);
}

native final function ASOpenSystemSetting();
native final function ASQuitGame();
//select---------------------------------------------------------------------------------------------
native final function ASRequestReturnLogin();
native final function ASRequestJump2CreateRole();
native final  function ASRequestFindRole();
native function ASRequestFindRoleID(int nRoleID);
native function ASRequestDelectRole(int nRoleID);

function ASDeleteRole()
{
	SelectPanel.DeleteRole();
}

function ASDirectSelectRole(int SelectRoleIndex) //双击人物选择框
{
	ASSelectRole(SelectRoleIndex);
	ASEnterGame(SelectRoleIndex);
}

function ASSelectRole( int SelectRoleIndex )
{
	SelectPanel.SelectRole(SelectRoleIndex);
}

function ASEnterGame(int SelectRoleIndex)
{
	SelectPanel.EnterGame(SelectRoleIndex);
}

//旋转按钮抬起 左手坐标系
function ASTurnBtnUp()
{
	SelectPanel.TurnBtnUp();
}

//选择角色面板 向右转 
function ASSelectTurnRightPress()
{
	SelectPanel.SelectTurnRightPress();	
}

//选择角色面板 向左转 
function ASSelectTurnLeftPress()
{
	SelectPanel.SelectTurnLeftPress();	
}

//Create--------------------------------------------------------------------------------------------------
function CreateRoleChanged(int RoleCareer)
{
	CreatePanel.CreateRoleChanged(RoleCareer);
}

function CreateSexChanged(int sex)
{
	CreatePanel.CreateSexChanged(sex);
}

function CreateRole(string createName)
{
	CreatePanel.CreateRole(createName);
}

function ASRequestReturnRoleList()
{
	CreatePanel.ASRequestReturnRoleList();
}

function ASReturnCreatePanel()
{
	CreatePanel.ASReturnCreatePanel();
}
//旋转按钮抬起 左手坐标系
function ASCreateTurnBtnUp()
{
	CreatePanel.CreateTurnBtnUp();
}

//选择角色面板 向右转 
function ASCreateTurnRightPress()
{
	CreatePanel.CreateTurnRightPress();	
}

//选择角色面板 向左转 
function ASCreateTurnLeftPress()
{
	CreatePanel.CreateTurnLeftPress();	
}

function ASOnCreateRoleNameInput( string roleName )
{
	CreatePanel.ASOnCreateRoleNameInput(roleName);
}

function ASCallUCGetAppearanceData()
{
	CreatePanel.ASGetAppearanceData();
}

function ASCallResetAll()
{
	CreatePanel.ASResetAll();
}

function ASCallRandomCreate(array<GfxObject> randomResult)
{
	CreatePanel.ASRandomCreate(randomResult);
}

function ASCallUpdateAppearance(int type, int id)
{
	CreatePanel.ASCallUpdateAppearance(type, id);
}

DefaultProperties
{
	MovieInfoStr="UI_Login.Login"
	//TurnButton=TBS_None
	Priority=5
}
