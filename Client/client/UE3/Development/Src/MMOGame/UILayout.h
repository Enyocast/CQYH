#ifndef _UILAYOUT_H_
#define _UILAYOUT_H_
#include "MMOUtil.h"

class IUILayout
{
public:

	virtual bool Layout(class UMMOUIBase* newPanel) = 0;
};

typedef std::vector<IUILayout*, M_UE3_STL_ALLOC(IUILayout*) > UILayoutList;
extern UILayoutList g_layoutList;


class UILayoutLeftRight : public IUILayout
{
public:

	UILayoutLeftRight(class UMMOUIBase* leftPanel, const FName& rightPanelName);
	virtual ~UILayoutLeftRight();
	virtual bool Layout(class UMMOUIBase* newPanel);

protected:

	class UMMOUIBase* _LeftPanel;
	FName _RightPanelName;
};

class UILayoutRightLeft : public IUILayout
{
public:

	UILayoutRightLeft(class UMMOUIBase* leftPanel, const FName& rightPanelName);
	virtual ~UILayoutRightLeft();
	virtual bool Layout(class UMMOUIBase* newPanel);

protected:

	class UMMOUIBase* _RightPanel;
	FName _LeftPanelName;
};

class UILayoutMidRight : public IUILayout
{
public:

	UILayoutMidRight(class UMMOUIBase* rightPanel,const FName& leftPanelName, const FName& MidPanelName);
	virtual ~UILayoutMidRight();
	virtual bool Layout(class UMMOUIBase* newPanel);

protected:

	class UMMOUIBase* _RightPanel;
	FName LeftPanelName;
	FName MidPanelName;
};

class UILayoutMidLeft : public IUILayout
{
public:

	UILayoutMidLeft(class UMMOUIBase* leftPanel,const FName& RightPanelName, const FName& MidPanelName);
	virtual ~UILayoutMidLeft();
	virtual bool Layout(class UMMOUIBase* newPanel);

protected:

	class UMMOUIBase* _LeftPanel;
	FName RightPanelName;
	FName MidPanelName;
};
#endif