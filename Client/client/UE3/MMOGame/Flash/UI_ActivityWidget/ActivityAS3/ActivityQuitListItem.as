
package UI_ActivityWidget.ActivityAS3
{

	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import scaleform.gfx.TextFieldEx;
	import scaleform.gfx.TextEventEx;
	import flash.events.TextEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.StyleSheet;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;

	public class ActivityQuitListItem extends ListItemTreeRenderer
	{

		public var Item_Name:TextField;
		public var Item_State:TextField;
		public var Item_Complete:TextField;
		public var Item_Posion:TextField;
		public var Item_huoyue:TextField;
		
		public var actitityData:ActivityData;

		override protected function configUI():void
		{
			super.configUI();

			//Item_Posion.styleSheet = new StyleSheet  ;
			Item_Posion.addEventListener(TextEvent.LINK, onLinkCallBack);
			Item_Posion.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER, onLinkOverCallBack);
			Item_Posion.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack( updateData );
			visible = false;
		}


		function onLinkOverCallBack(e:TextEventEx)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASTrace", "ASLinkOverCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOverCallBack", commandParameter);
		}

		function onLinkOutCallBack(e:TextEventEx)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASTrace", "ASLinkOutCallBack:" + commandParameter.toString());
			ExternalInterface.call( "ASLinkOutCallBack", commandParameter);
		}

		function onLinkCallBack(e:TextEvent)
		{
			var commandParameter:Array = e.text.split(",");//获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}
		
		function updateData(data:Object):void
		{
			actitityData = data as ActivityData;
			if (actitityData)
			{
				visible = true;
				Item_Name.text = actitityData.Name;
				Item_huoyue.text = String(actitityData.Activity);
				Item_State.text = actitityData.State;
				Item_Complete.text = actitityData.CompleteState;
				
				//Item_Posion.autoSize 	= 			flash.text.TextFieldAutoSize.LEFT;
				//Item_Posion.wordWrap 	= 			true;
				Item_Posion.htmlText 	= 			actitityData.Position;
				//Item_Posion.height 		= 			Item_Posion.textHeight;
			}
			else
			{
				visible = false;
			}
		}
	}

}