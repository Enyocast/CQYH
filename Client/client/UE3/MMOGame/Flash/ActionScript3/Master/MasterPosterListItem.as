package ActionScript3.Master
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.controls.StateUIComponent;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.MouseEventEx;


	public class MasterPosterListItem extends ListItemTreeRenderer
	{
		private static const TEXT_COLOR_GREEN:uint = 0x84ec60;
		private static const TEXT_COLOR_WHITE:uint = 0xFFFFFF;
		private static const NORMAL_STATE_TEXT:String = "可申请";
		public var tF_name_master:TextField;
		//public var tF_level:TextField;
		public var tF_profession:TextField;
		public var tF_score:TextField;
		public var tf_status:TextField;
		
		//public var mask_btn_mc:Button;

		public var Master_data:MasterData;

		public function MasterListItem()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();
			visible = false;
			
			this.mouseEnabled = true;
			addEventListener(MouseEvent.CLICK, onRightMenuClick);

			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack( updateData );
		}
		
		function onRightMenuClick(e:Event)
		{
			if(1 == (e as MouseEventEx).buttonIdx)
			{
				ExternalInterface.call("ASRightMenuMasterList", Master_data.Id);
			}
		}

		function updateData(data:Object):void
		{
			Master_data = data as MasterData;
			if (Master_data)
			{
				visible = true;
				tF_name_master.text = Master_data.Name;
				//tF_level.text = String( Master_data.Level );
				tF_profession.text = Master_data.Profession;
				tF_score.text = String( Master_data.Score );
				tf_status.text = Master_data.Status;
				if(Master_data.Status != NORMAL_STATE_TEXT)
				{
					tf_status.textColor = TEXT_COLOR_GREEN;
				}
				else
				{
					tf_status.textColor = TEXT_COLOR_WHITE;
				}
				//this.selected = Master_data.IsSelected;
			}
			else
			{
				visible = false;
			}
		}
	}
}