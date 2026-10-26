class SeqAct_Guide extends SequenceAction;

event Activated()
{	
	/*
	local MMOUIGuide guidePanel;
	local SeqVar_String guideName;
	local SeqVar_Int guideDelay;
	local bool guideVisible;

	if (InputLinks[0].bHasImpulse)
	{
		guideVisible = true;
	}
	else if (InputLinks[1].bHasImpulse)
	{
		guideVisible = false;
	}

	//add by JimZHang@snda.com
	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_Guide,guideVisible,"");

	guidePanel = MMOUIGuide(class'MMOUIManager'.static.FindUIPanel( class'MMOUIManager'.default.Panel_Guide));
	if(guidePanel != none)
	{
		if (guideVisible == true)
		{
			foreach LinkedVariables(class'SeqVar_String', guideName, "Name")
			{
				if(guideName.StrValue != "")
				{
					break;
				}
			}

			foreach LinkedVariables(class'SeqVar_Int', guideDelay, "Delay")
			{
				if(guideDelay.IntValue != 0)
				{
					break;
				}
			}
			
			//guidePanel.ShowGuide(guideName.StrValue, guideDelay.IntValue);
		}
		else
		{
			//guidePanel.HideGuidePanel();
		}
	}
	*/
}

DefaultProperties
{
	ObjName="Show Guide"
	ObjCategory="MMO UI"

	InputLinks.Empty
	InputLinks(0) = (LinkDesc = "Show")
	InputLinks(1) = (LinkDesc = "Hide")

	OutputLinks.Empty
	OutputLinks(0) = (LinkDesc="Out")

	VariableLinks.Empty
	VariableLinks(0)=(ExpectedType=class'SeqVar_String', LinkDesc="Name")
	VariableLinks(1)=(ExpectedType=class'SeqVar_Int', LinkDesc="Delay")
}

