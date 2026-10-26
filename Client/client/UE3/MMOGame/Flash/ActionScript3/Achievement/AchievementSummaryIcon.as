//
//成就系统图标
//
package  ActionScript3.Achievement
{
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.MyIconConponent;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	
	public class AchievementSummaryIcon extends Button 
	{
		public var user_data:int;
		public var name_tf:TextField;
		public var date_tf:TextField;
		
		
		public function AchievementSummaryIcon() 
		{
			// constructor code
		}
		
		override protected function configUI():void 
		{			
			//trace(">>>>>>>>>>>>>> AchievementSummaryIcon::configUI");
			super.configUI();
			this.addEventListener(MouseEvent.CLICK, onClick);
			//trace("<<<<<<<<<<<<<< AchievementSummaryIcon::configUI");
		}
		
		public function onClick()
		{
		}
		
		public function setIconCaption(str:String)
		{
			name_tf && (name_tf.text = str);
		}
		
		public function setIconDate(str:String)
		{
			date_tf && (date_tf.text = str);
		}
		
		public function setIconImage(str:String)
		{
			var icon : UILoader = this.getChildByName("IconLoader_mc") as UILoader;
			
			icon.visible = true;
			if (str == "" || str == null)
			{
				icon.visible = false;
			}
			else
			{
				icon.source = str;
			}
		}
		
		override protected function handleMouseRollOver(event:MouseEvent):void {
			super.handleMouseRollOver(event);
			name_tf && (name_tf.textColor = 0xffcc73);
		}
		
		override protected function handleMouseRollOut(event:MouseEvent):void {
			super.handleMouseRollOut(event);
			name_tf && (name_tf.textColor = 0xfecb6f);
		}
	}
}
