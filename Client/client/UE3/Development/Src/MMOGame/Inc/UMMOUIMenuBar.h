

virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

virtual void Init();
virtual void UnInit();
void UpdateMenuButton( TArrayNoInit<struct FMenuInfo>& menuInfo , UBOOL left , INT lastLv , INT newLv );
void ClickMenu( INT menuId,INT menuType );
void ClickMenuChild( INT menuId, INT menuType, INT childMenuId, INT childMenuType );

void UpdateMenuButtonMaxCount( INT type , INT count , UBOOL left );
void SetMenuButtonNewCount( INT type , INT count , UBOOL left );

FMenuInfo* FindMenuInfoByType( INT menuIdx , INT menuType );
FMenuInfo* GetLastShowChildMenu( FMenuInfo* menuInfo );
INT GetMenuIdxByMenuType( INT type , UBOOL left );
UBOOL IsInLeftMenuBar( INT type );
FMenuInfo* FindChildMenuInfoByType( FMenuInfo* menuInfo , INT childMenuIdx , INT childMenuType );
// add by zhangrui05
UBOOL IsMenuActivated(INT childMenuType);

// 新系统开启
void ShowNewSystem(INT systemType);
void ActivateNewSystem(INT systemType);
//
void OpenGameServiceWnd();

BOOL CheckClientOption(INT childMenuType);