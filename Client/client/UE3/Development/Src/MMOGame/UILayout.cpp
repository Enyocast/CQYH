#include "stdafx.h"
#include "UILayout.h"
#include "MMOFacade.h"

UILayoutList g_layoutList;

//------------------------------------------------------------------------
// UILayoutLeftRight
//------------------------------------------------------------------------
UILayoutLeftRight::UILayoutLeftRight( class UMMOUIBase* leftPanel, const FName& rightPanelName )
	: _LeftPanel(leftPanel)
	, _RightPanelName(rightPanelName)
{

}

UILayoutLeftRight::~UILayoutLeftRight()
{

}

bool UILayoutLeftRight::Layout( class UMMOUIBase* newPanel )
{
	if(newPanel != _LeftPanel)
	{
		return false;
	}


	FVector2D scrSz = MMOFacade::GetScreenSize();

	INT leftW = _LeftPanel->eventGetWidth();
	INT leftH = _LeftPanel->eventGetHeight();

	UMMOUIBase* rightPanel = MMOUI::FindUIPanel(_RightPanelName);
	if(!rightPanel )
	{
		return false;
	}
	if (!rightPanel->IsVisible)
	{
		return false;
	}

	INT rightW = rightPanel->eventGetWidth();
	INT rightH = rightPanel->eventGetHeight();

	INT panelX = (scrSz.X - leftW - rightW) / 2;
	INT panelY = (scrSz.Y - Max(leftH, rightH)) / 2;

	_LeftPanel->SetPosition(panelX, panelY);
	rightPanel->SetPosition(panelX + leftW, panelY);

	return true;
}

//------------------------------------------------------------------------
// UILayoutRightLeft
//------------------------------------------------------------------------
UILayoutRightLeft::UILayoutRightLeft( class UMMOUIBase* rightPanel, const FName& leftPanelName )
	: _RightPanel(rightPanel)
	, _LeftPanelName(leftPanelName)
{

}

UILayoutRightLeft::~UILayoutRightLeft()
{

}

bool UILayoutRightLeft::Layout( class UMMOUIBase* newPanel )
{
	if(newPanel != _RightPanel)
	{
		return false;
	}


	FVector2D scrSz = MMOFacade::GetScreenSize();

	INT rightW = _RightPanel->eventGetWidth();
	INT rightH = _RightPanel->eventGetHeight();

	UMMOUIBase* leftPanel = MMOUI::FindUIPanel(_LeftPanelName);
	if(!leftPanel)
	{
		return false;
	}
	if (!leftPanel->IsVisible)
	{
		return false;
	}

	INT leftW = leftPanel->eventGetWidth();
	INT leftH = leftPanel->eventGetHeight();

	INT panelX = (scrSz.X - leftW - rightW) / 2;
	INT panelY = (scrSz.Y - Max(leftH, rightH)) / 2;

	leftPanel->SetPosition(panelX, panelY);
	_RightPanel->SetPosition(panelX + leftW, panelY);

	return true;
}

//------------------------------------------------------------------------
//UILayoutMidRight
//------------------------------------------------------------------------

UILayoutMidRight::UILayoutMidRight(class UMMOUIBase* rightPanel,const FName& leftPanelName, const FName& MidPanelName)
	: _RightPanel(rightPanel)
	, LeftPanelName(leftPanelName)
	, MidPanelName(MidPanelName)
{

}

UILayoutMidRight::~UILayoutMidRight()
{

}

bool UILayoutMidRight::Layout( class UMMOUIBase* newPanel )
{
	if(newPanel != _RightPanel)
	{
		return false;
	}


	FVector2D scrSz = MMOFacade::GetScreenSize();

	UMMOUIBase* leftPanel = MMOUI::FindUIPanel(LeftPanelName);
	UMMOUIBase* midPanel = MMOUI::FindUIPanel(MidPanelName);

	if(!leftPanel || !midPanel)
	{
		return false;
	}
	if (!leftPanel->IsVisible && !midPanel->IsVisible)
	{
		return false;
	}

	INT rightW = _RightPanel->eventGetWidth();
	INT rightH = _RightPanel->eventGetHeight();

	if (!leftPanel->IsVisible && midPanel->IsVisible)
	{
		INT leftW = midPanel->eventGetWidth();
		INT leftH = midPanel->eventGetHeight();

		INT panelX = (scrSz.X - leftW - rightW) / 2;
		INT panelY = (scrSz.Y - Max(leftH, rightH)) / 2;

		midPanel->SetPosition(panelX, panelY);
		_RightPanel->SetPosition(panelX + leftW, panelY);
	}
	else if(leftPanel->IsVisible && midPanel->IsVisible)
	{
		INT leftW = leftPanel->eventGetWidth();
		INT leftH = leftPanel->eventGetHeight();

		INT midW = midPanel->eventGetWidth();
		INT midH = midPanel->eventGetHeight();

		INT panelX = (scrSz.X - leftW - rightW - midW) / 3;
		INT panelY = (scrSz.Y - Max(leftH, rightH)) / 2;

		leftPanel->SetPosition(panelX, panelY);
		midPanel->SetPosition(panelX + leftW, panelY);
		_RightPanel->SetPosition(panelX + leftW + midW, panelY);
	}
	

	return true;
}

//------------------------------------------------------------------------
//UILayoutMidLeft
//------------------------------------------------------------------------

UILayoutMidLeft::UILayoutMidLeft(class UMMOUIBase* leftPanel,const FName& RightPanelName, const FName& MidPanelName)
: _LeftPanel(leftPanel)
	, RightPanelName(RightPanelName)
	, MidPanelName(MidPanelName)
{

}

UILayoutMidLeft::~UILayoutMidLeft()
{

}

bool UILayoutMidLeft::Layout( class UMMOUIBase* newPanel )
{
	if(newPanel != _LeftPanel)
	{
		return false;
	}


	FVector2D scrSz = MMOFacade::GetScreenSize();

	UMMOUIBase* rightPanel = MMOUI::FindUIPanel(RightPanelName);
	UMMOUIBase* midPanel = MMOUI::FindUIPanel(MidPanelName);

	if(!rightPanel || !midPanel)
	{
		return false;
	}
	if (!rightPanel->IsVisible && !midPanel->IsVisible)
	{
		return false;
	}

	INT rightW = rightPanel->eventGetWidth();
	INT rightH = rightPanel->eventGetHeight();

	if (!rightPanel->IsVisible && midPanel->IsVisible)
	{
		INT leftW = midPanel->eventGetWidth();
		INT leftH = midPanel->eventGetHeight();

		INT panelX = (scrSz.X - leftW - rightW) / 2;
		INT panelY = (scrSz.Y - Max(leftH, rightH)) / 2;

		midPanel->SetPosition(panelX, panelY);
		_LeftPanel->SetPosition(panelX + leftW, panelY);
	}
	else if(rightPanel->IsVisible && midPanel->IsVisible)
	{
		INT leftW = _LeftPanel->eventGetWidth();
		INT leftH = _LeftPanel->eventGetHeight();

		INT midW = midPanel->eventGetWidth();
		INT midH = midPanel->eventGetHeight();

		INT panelX = (scrSz.X - leftW - rightW - midW) / 3;
		INT panelY = (scrSz.Y - Max(leftH, rightH)) / 2;

		_LeftPanel->SetPosition(panelX, panelY);
		midPanel->SetPosition(panelX + leftW, panelY);
		rightPanel->SetPosition(panelX + leftW + midW, panelY);
	}


	return true;
}

