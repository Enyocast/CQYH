package ActionScript3.Master
{
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import scaleform.gfx.MouseEventEx;
	import ActionScript3.controls.StateUIComponent;


	public class MasterApplyListItem extends ListItemTreeRenderer
	{
		public var tF_name_master:TextField;
		public var tF_profession:TextField;
		public var tF_score:TextField;
		
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
				tF_profession.text = Master_data.Profession;
				tF_score.text = String( Master_data.Score );
				//this.selected = Master_data.IsSelected;
			}
			else
			{
				visible = false;
			}
		}
	}
}