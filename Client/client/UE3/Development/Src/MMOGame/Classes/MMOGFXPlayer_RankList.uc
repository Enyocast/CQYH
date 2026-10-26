class MMOGFXPlayer_RankList extends MMOGFXPlayer
	native(UI)
	config(MMOGame);
var MMOUIRankListPanel _RankListPanel;
var MMOUIRankConfigPanel _RankConfigPanel;
function RegisterRankList( MMOUIRankListPanel mc )
{
	_RankListPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_RankList);
}

function RegisterConfigPanel(MMOUIRankConfigPanel mc)
{
	_RankConfigPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_RankConfig);
}

function ASPersonTreeItemClick(int index)//moved
{
	_RankListPanel.OnPersonTreeItemClick(index);
}

function ASGuildTreeItemClick(int index)//moved
{
	_RankListPanel.OnGuildTreeItemClick(index);
}

function ASTournamentTreeItemClick(int index)//moved
{
	_RankListPanel.OnTournamentTreeItemClick(index);
}

function ASPowerTreeItemClick(int index)//moved
{
	_RankListPanel.OnPowerTreeItemClick(index);
}

function ASPersonTabClick()//moved
{
	_RankListPanel.OnPersonTabClick();
}

function ASGuildTabClick()//moved
{
	_RankListPanel.OnGuildTabClick();
}

function ASTournamentTabClick()//moved
{
	_RankListPanel.OnTournamentTabClick();
}

function ASPowerTabClick()//moved
{
	_RankListPanel.OnPowerTabClick();
}

function ASRangeClick(int index)//moved
{
	_RankListPanel.OnRangeClick(index);
}

function ASCategoryClick(int index)//moved
{
	_RankListPanel.OnCategoryClick(index);
}

function ASRightClick1Menu(int Id)//moved
{
	_RankListPanel.OnRightClick1Menu(Id);
}

function ASRightClick2Menu(int Id)//moved
{
	_RankListPanel.OnRightClick2Menu(Id);
}

function ASTournamentConfigClick(int Id)//moved
{
	_RankConfigPanel.OnTournamentConfigClick(Id);
}

function ASPersonMasterClick(int Id)//moved
{
	_RankListPanel.OnPeronMasterClick(Id);
}

function ASPrevPageClick()//moved
{
	_RankListPanel.OnPrevPageClick();
}

function ASNextPageClick()//moved
{
	_RankListPanel.OnNextPageClick();
}

DefaultProperties
{
	MovieInfoStr="UI_RankUIWidget.RankUIWidget"
	Priority=3
}
