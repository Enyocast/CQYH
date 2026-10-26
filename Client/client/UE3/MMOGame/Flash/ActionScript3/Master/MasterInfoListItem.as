package ActionScript3.Master
{

	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.MouseEventEx;
	import scaleform.gfx.TextFieldEx;

	public class MasterInfoListItem extends ListItemTreeRenderer
	{
		private static const PREFIX_LEVEL_ADDED:String = "+";
		public var master_icon_mc:MovieClip;
		public var tF_name_master:TextField;
		public var tF_level:TextField;
		public var tF_profession:TextField;
		public var tF_Count:TextField;
		
		//public var mc_Congratulate:Button;

		public var StudentDetail_data:MasterInfoListItemData;

		override protected function configUI():void
		{
			super.configUI();
			visible = false;
			this.mouseEnabled = true;
			addEventListener(MouseEvent.CLICK, onRightMenuClick);
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateData);
			//mc_Congratulate.addEventListener(MouseEvent.CLICK, OnClickCongraluate );

			tF_Count.visible = false;
			master_icon_mc.visible = false;
		}

/*		function OnClickCongraluate(e:MouseEvent)
		{
			if (0 == (e as MouseEventEx).buttonIdx)
			{
				mc_Congratulate.selected = ! mc_Congratulate.selected;
				ExternalInterface.call("ASClickCongraluate", StudentDetail_data.Id );
			}
		}*/

		function onRightMenuClick(e:Event)
		{
			if (1 == (e as MouseEventEx).buttonIdx)
			{
				ExternalInterface.call("ASRightMenuStudentDetailList", StudentDetail_data.Id);
			}
		}

		function updateData(data:Object):void
		{
			StudentDetail_data = data as MasterInfoListItemData;
			if (StudentDetail_data)
			{
				visible = true;
				tF_name_master.text = StudentDetail_data.Name;
				
				tF_profession.text = String(StudentDetail_data.Profession);
				if(StudentDetail_data.bLeaveMaster)
				{
					tF_name_master.textColor=0xb2b2b2;
					tF_level.textColor=0xb2b2b2;
					tF_profession.textColor=0xb2b2b2;
					tF_level.text = "已离师";
				}
				else
				{
					tF_level.text = String(StudentDetail_data.Level);
					tF_name_master.textColor=0xFFFFFF;
					tF_level.textColor=0xFFFFFF;
					tF_profession.textColor=0xFFFFFF;
				}
/*				if(StudentDetail_data.CanCongratulate){
					mc_Congratulate.visible = true;
					//mc_Congratulate['tf_Text'].text = StudentDetail_data.CongratulateType;
					mc_Congratulate.label = StudentDetail_data.CongratulateType;
				}else{
					mc_Congratulate.visible = false;
				}*/
				
				if(StudentDetail_data.congCount > 0)
				{
					tF_Count.visible = true;
					tF_Count.text = PREFIX_LEVEL_ADDED + StudentDetail_data.congCount.toString();
				}
				else{
					tF_Count.visible = false;
				}
				master_icon_mc.visible = StudentDetail_data.bMaster;
			}
			else
			{
				visible = false;
			}
		}
	}
}