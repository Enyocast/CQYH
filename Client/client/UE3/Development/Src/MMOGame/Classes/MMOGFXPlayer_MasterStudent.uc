class MMOGFXPlayer_MasterStudent extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIMasterStudentPanel _MasterStudent;
var MMOUIMasterCongratulationMain _MasterCongMain;
var MMOUIMasterCongratulationSub  _MasterCongSub;

var GFxObject ConfirmMsgBox;

function RegisterMasterStudent( MMOUIMasterStudentPanel mc )
{
	_MasterStudent = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_MasterStudent);
}

function RegisterMasterCongMain( MMOUIMasterCongratulationMain mc )
{
	_MasterCongMain = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_MasterCongMain);
}

function RegisterMasterCongSub( MMOUIMasterCongratulationSub mc )
{
	_MasterCongSub = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_MasterCongSub);
}

native function PostAdvance(float DeltaTime);//moved

native function ASSendCongratulation(int nType,int nRoleID,string strCon);//moved

native function ASClearMasterApplyList();//moved
native function ASAcceptMasterApplyList(int nID);//moved
native function ASDenyMasterApplyList(int nID);//moved
native function ASMasterApplyListNextPage();//moved
native function ASMasterApplyListPrevPage();//moved
native function ASSortMasterApplyList(int nType);//moved
native function ASSortMasterPosterList(int nType);//moved
native function ASSortStudentPosterList(int nType);//moved
native function ASSortStudentApplyList(int nType);//moved
native function ASMasterPosterListRefresh();//moved
native function ASApplyMasterPosterList(int nID);//moved
native function ASCancelMasterPosterList(int nID);//moved
native function ASMasterPosterListNextPage();//moved
native function ASMasterPosterListPrevPage();//moved
native function ASClickMasterPosterList(int nID);//moved
native function ASLeaveMaster();//moved
native function ASFireStudent(int nID);//moved
native function ASClickMasterInfoList(int nID);//moved
native function ASRightMenuMasterApplyList(int nID);//moved
native function ASRightMenuStudentPosterList(int nID);//moved
native function ASApplyStudentPosterList(int nID);//moved
native function ASCancelStudentPosterList(int nID);//moved
native function ASRefreshStudentPosterList();//moved
native function ASClickStudentPosterList(int nID);//moved
native function ASStudentPostListPage(int nPage);//moved
native function ASAcceptStudentApplyList(int nID);//moved
native function ASDenyStudentApplyList(int nID);//moved
native function ASClearStudentApplyList();//moved
native function ASClickStudentApplyList(int nID);//moved
native function ASRightMenuStudentApplyList(int nID);//moved
native function ASClickStartRecruit();//moved
native function ASClickStopRecruit();//moved
native function ASClickAcceptLeave(int nID);//moved
native function ASClickCongratulation(int nID);//moved
native function ASClickMasterTap(int nID);//moved

native function ASApplyGrad();//moved
native function ASForceGrad();//moved

native function OnLeaveMaster();//moved
native function ASRightMenuStudentDetailList(int nID);//moved
native function ASClickCongraluate(int nID);//moved
native function ASRightMenuMasterList(int nID);//moved
native function OnFireStudent(GFxObject mc);//moved
native function OnMasterCancel();//moved

native function ASShowTips_MasterGift(GFxObject mc,int nType);//moved
native function ASHideTips_MasterGift();//moved

native function HideMsgBox();
//end
//
DefaultProperties
{
	MovieInfoStr="UI_MasterWidget.MasterWidget"
	Priority=5
}
