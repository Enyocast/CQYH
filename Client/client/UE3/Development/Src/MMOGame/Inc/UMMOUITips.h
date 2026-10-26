virtual void Init();

virtual void UnInit();

void FitTipsForScreen( UGFxObject &itemTips, FIntPoint &tipPos, INT actualWidth, INT actualHeight );
void GetCurrentTipsSize();
//void FitSkillTipsForScreen( UGFxObject &itemTips, FIntPoint &tipPos, INT ActualWidth, INT ScreenSizeX );
void SetPosAnchoredByCurMousePos();
void SetTextLinkTipsPos();
//void SetAnchoredTipsAutoHideByMousePos( UBOOL isToSet );