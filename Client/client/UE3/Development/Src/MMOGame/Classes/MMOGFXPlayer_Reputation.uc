class MMOGFXPlayer_Reputation extends MMOGFXPlayer
	native(UI)
	config(MMOGame);


var MMOUIReputationPanel            ReputationPanel;

function RegisterReputation( MMOUIReputationPanel mc )
{
	ReputationPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Reputation);
}

function UpdateReputationData()
{
	ReputationPanel.UpdateReputationData();
}

function RefreshReputationSelected()
{
	ReputationPanel.CallRefreshReputationSelected();
}

//moved-------------
function ASChangeReputationType( int ID,int ReputationType )
{
	ReputationPanel.ChangeReputationType( ID, ReputationType );
}

function ASUpdateRewordSlot(GFxObject SlotObj)
{
	ReputationPanel.UpdateRewordSlot(SlotObj);
}

function ASAwardClick(int ForceID)
{
	ReputationPanel.AwardClick(ForceID);
}

//function ASShowTraceReputationInfoPanel()
//{
//	//Character.ShowTraceReputationInfoPanel();
//}




native function PostAdvance(float DeltaTime );


DefaultProperties
{
	MovieInfoStr="UI_Reputation.Reputation"
	Priority=5
}
