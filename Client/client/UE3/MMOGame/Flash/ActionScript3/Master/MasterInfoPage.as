
package ActionScript3.Master{
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.TextArea;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.gfx.TextFieldEx;
	import scaleform.clik.events.ComponentEvent;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.events.ButtonEvent;
	
	public class MasterInfoPage extends UIComponent
	{
		public var btn_Congratulation:Button;	//升级祝贺
		public var btn_AcceptLeave:Button;		//同意出师
		public var btn_LeaveMaster:Button;		//背叛师门
		public var btn_FireStudent:Button;		//逐出师门
		public var btn_gradApply:Button;		//申请出师
		public var btn_gradForce:Button;		//强制出师
		public var btn_MasterExp:Button;        //领取奖励
		
		public var _master:MovieClip;//有徒弟有师傅
		public var _no_master:MovieClip;//无徒弟 //无师傅
		public var chk_notice:CheckBox;//徒弟推送
		
		public var tabTitle:MovieClip;
 		public var masterInfoList_mc:MasterListControl;
		
		public var MasterState:int = 0 ;
		public var nSelectedID:int = 0;
		public var bSelfReward:Boolean = false;
		
		override protected  function configUI():void 
		{			
			super.configUI();			

			btn_LeaveMaster.visible = false;
			btn_gradApply.visible = false;
			btn_gradForce.visible = false;
			btn_MasterExp.visible = false;
			
			RefreshControlState();

			btn_LeaveMaster.addEventListener( MouseEvent.CLICK, onLeaveMaster );
			btn_FireStudent.addEventListener( MouseEvent.CLICK, onFireStudent );
			
			btn_AcceptLeave.addEventListener( MouseEvent.CLICK, onAcceptLeave );
			btn_Congratulation.addEventListener( MouseEvent.CLICK, onCongratulation );
			
			btn_gradApply.addEventListener( MouseEvent.CLICK, onApplyGrad );
			btn_gradForce.addEventListener( MouseEvent.CLICK, onForceGrad );
			chk_notice.addEventListener(ButtonEvent.CLICK,onClcikHandler);
			btn_MasterExp.addEventListener(MouseEvent.CLICK, onMasterExp);
			
			masterInfoList_mc.addEventListener(ListEvent.ITEM_CLICK, onClickItem);

			// @Test;
/*			if (1)
			{
				var itemsData:Array = new Array();
				for (var i:int = 1; i < 6; i++)
				{
					var tStudentDetailData:MasterInfoListItemData = new MasterInfoListItemData  ;
					tStudentDetailData.Id = i*3;
					tStudentDetailData.bMaster = (i == 1);
					tStudentDetailData.Name = String( "Panda" + i );
					tStudentDetailData.ProfessionId = i % 4;
					tStudentDetailData.Profession = "法师";
					tStudentDetailData.Level = i % 4;
					tStudentDetailData.CanCongratulate = Boolean( i % 2 );
					tStudentDetailData.CongratulateType = "恭喜升级";
					itemsData.push(tStudentDetailData);
				}
				updateData( itemsData );
			}*/
		}
		
		public function setMasterInfoCheckBox(bl:Boolean,isshow:Boolean):void
		{
			chk_notice.selected=bl;
			chk_notice.visible=isshow;
		}
		
		private function onClcikHandler(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASMasterInfoClick",chk_notice.selected);
		}
		public function UpdateMasterState(nMasterState:int,nSelfState:int)
		{
			MasterState = nMasterState;
			
			if(MasterState == 1)
			{
				btn_LeaveMaster.visible = (nSelfState == 0);
				//btn_gradApply.visible = (nSelfState == 1);;
				if(nSelfState == 1 || nSelfState == 2)
					btn_gradForce.visible = true;
				else
					btn_gradForce.visible = false;
			}
			else
			{
				btn_LeaveMaster.visible = false;
				//btn_gradApply.visible = false;
				btn_gradForce.visible = false;
			}
		}
		
		//刷新初始数据
		private function RefreshControlState():void
		{
			nSelectedID = 0;
			bSelfReward = false;
			btn_Congratulation.visible = false;
			btn_AcceptLeave.visible = false;
			btn_FireStudent.visible = false;
			btn_MasterExp.visible = false;
			this._no_master.visible=true;
			this._master.visible=false;
		}
		
		public function onApplyGrad()
		{
			ExternalInterface.call("ASApplyGrad" );
		}
		
		public function onForceGrad()
		{
			ExternalInterface.call("ASForceGrad" );
		}
		
		public function onLeaveMaster()
		{
			ExternalInterface.call("ASLeaveMaster" );
		}
		
		public function onFireStudent()
		{
			ExternalInterface.call("ASFireStudent",nSelectedID);
		}
		
		public function onAcceptLeave()
		{
			ExternalInterface.call("ASClickAcceptLeave",nSelectedID);
		}
		public function onCongratulation()
		{
			ExternalInterface.call("ASClickCongratulation",nSelectedID);
		}
		public function onMasterExp()
		{
			ExternalInterface.call("ASClickMasterExp",nSelectedID,bSelfReward);
		}
		
		public function UpdateBtnState(dat:MasterInfoListItemData):void
		{
			RefreshControlState();
			if(dat != null)
			{
				nSelectedID = dat.Id;
				bSelfReward = dat.bSelfReward;
				
				if(dat.bMaster)
				{
					
				}
				else
				{
					if(MasterState == 2)
					{
						if(dat.nState == 2)
						{
							btn_AcceptLeave.visible = true;
						}
						btn_FireStudent.visible = true;
					}
				}
				
				//if(btn_AcceptLeave.visible)
				//{
					//btn_Congratulation.visible = false;
					//btn_FireStudent.visible = false;
				//}
				if(dat.bLeaveMaster)
				{//整条置灰
					
					btn_Congratulation.visible = false;
					btn_MasterExp.visible = true;
					btn_MasterExp.enabled = true;
					btn_FireStudent.visible = false;
				}
				else
				{
					if(dat.congCount > 0)
					{
						btn_Congratulation.visible = true;
						btn_MasterExp.visible = false;
					}
					else
					{
						btn_Congratulation.visible = false;
						btn_MasterExp.visible = true;
						btn_MasterExp.enabled = false;
					}
					
				}
				updateInfo(dat.Name,dat.exp,dat.gold,dat.MasterValue,dat.bMaster,dat.bSelfReward);
			}
		}
		public function updateData( data:Array ):void
		{
			var nIndex = 0;//masterInfoList_mc.selectedIndex;
			
			masterInfoList_mc.dataProvider = new DataProvider(data);
			masterInfoList_mc.validateNow();
			masterInfoList_mc.invalidateData();
			
			if(nIndex >= data.length)
				nIndex = data.length - 1;
				
			if(nIndex >= 0 && nIndex < data.length)
			{
				masterInfoList_mc.selectedIndex = nIndex;
				UpdateBtnState(data[nIndex]);
			}
			else
			{
				RefreshControlState();
			}
		}
		
		private function onClickItem(e:ListEvent):void
		{
			var item:MasterInfoListItem = e.itemRenderer as MasterInfoListItem;
			ExternalInterface.call("ASClickMasterInfoList", item.StudentDetail_data.Id);
			UpdateBtnState(item.StudentDetail_data);
		}
		
		//更新获得奖励和经验
		private function updateInfo(playerName:String,exp:int,gold:int,num:int,bMaster:Boolean,bSelfReward:Boolean):void
		{
			_master.visible=true;
			_no_master.visible=false;
			
			
			if(MasterState == 1)//我自己是徒弟
			{
				if(bMaster) //师傅
				{
					showStudentReward(playerName,exp,gold,num); // 没有名师值
				}
				else //同盟看不到奖励
				{
					_master.visible=false;
					_no_master.visible=true;
				}
			}
			else //自己是师傅
			{
				if(bSelfReward) //上一个师傅留下的奖励
				{
					showStudentReward(playerName,exp,gold,num);
				}
				else
				{
					showTeacherReward(playerName,exp,gold,num); //显示获得的名师值
				}
				
			}
		}
		
		public function showStudentReward(playerName:String,exp:int,gold:int,num:int)
		{
			var txt_num:TextField=this._master.getChildByName("txt_numText") as TextField;
			var tf_num:TextField=this._master.getChildByName("tf_num") as TextField;
			var txt_exp:TextField=(_master.getChildByName("txt_exp") as TextField);
			var tf_exp:TextField=(_master.getChildByName("tf_exp") as TextField);
			var txt_gold:TextField=(_master.getChildByName("txt_goldText") as TextField);
			var tf_gold:TextField=(_master.getChildByName("tf_gold") as TextField);
			var tf_name:TextField=(_master.getChildByName("tf_name") as TextField);
			
			txt_exp.x=74;
			tf_exp.x=txt_exp.x+32;
			txt_gold.x=206;
			tf_gold.x=txt_gold.x+32;
			txt_num.visible = false;
			tf_num.visible = false;
			tf_name.htmlText=playerName+"<font color='#FFEDC5'>    出师累计奖励</font>";
			
			tf_exp.text=exp.toString();
			tf_gold.text=gold.toString();
			tf_num.text=num.toString();
			
		}
		public function showTeacherReward(playerName:String,exp:int,gold:int,num:int)
		{
			var txt_num:TextField=this._master.getChildByName("txt_numText") as TextField;
			var tf_num:TextField=this._master.getChildByName("tf_num") as TextField;
			var txt_exp:TextField=(_master.getChildByName("txt_exp") as TextField);
			var tf_exp:TextField=(_master.getChildByName("tf_exp") as TextField);
			var txt_gold:TextField=(_master.getChildByName("txt_goldText") as TextField);
			var tf_gold:TextField=(_master.getChildByName("tf_gold") as TextField);
			var tf_name:TextField=(_master.getChildByName("tf_name") as TextField);
			
			txt_num.visible = true;
			tf_num.visible = true;
			txt_exp.x=41;
			tf_exp.x=txt_exp.x+32;
			txt_gold.x=136;
			tf_gold.x=txt_gold.x+32;
			tf_name.htmlText=playerName+"<font color='#FFEDC5'>    累计奖励</font>";
			
			tf_exp.text=exp.toString();
			tf_gold.text=gold.toString();
			tf_num.text=num.toString();
		}
	}
}