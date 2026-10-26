package ActionScript3.Widget
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import flash.events.Event;
	import scaleform.gfx.TextEventEx;
	import flash.events.TextEvent;
	import flash.text.TextField;

	public class DialogContent extends UIComponent 
	{
		public var PlayerAnswer0:Button;
		public var PlayerAnswer1:Button;
		public var PlayerAnswer2:Button;
		public var yesButton_mc:Button;
		public var noButton_mc:Button;
		public var btn_dialogContinue:Button;
		public var DialogText_mc:MovieClip;
		
		override protected function configUI():void {
			super.configUI();
			
			var i:int;
			for( i = 0 ; i < 6 ; i++)
			{
				var Item:Button = this.getChildByName("PlayerAnswer"+i) as Button;
				if( Item )
				{
					Item.itemid = i; //这个似乎无所谓……值是特殊的
					addEventListener( "click",clickAnswer );
				}
			}

			if( yesButton_mc )
				yesButton_mc.addEventListener("click",clickOk);
			if( noButton_mc )
				noButton_mc.addEventListener("click", clickNo);
			if( btn_dialogContinue )
				btn_dialogContinue.addEventListener( "click" , clickNext );
				
			var descTxt:TextField = DialogText_mc.getChildByName("textField") as TextField;
			descTxt.addEventListener(TextEvent.LINK, onLinkCallBack);
			descTxt.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OVER , onLinkOverCallBack);
			descTxt.addEventListener(scaleform.gfx.TextEventEx.LINK_MOUSE_OUT, onLinkOutCallBack);
			if(0)
			{
				descTxt.htmlText = "<a href='event:1,2,3'><U>TestURL</U></a>";
			}
		}
		
		function onLinkOverCallBack(e:TextEventEx)
		{
			trace("+++++++++++onLinkOverCallBack");
		}
		
		function onLinkOutCallBack(e:TextEventEx)
		{
			trace("-----------onLinkOverCallBack");
		}

		function onLinkCallBack(e:TextEvent)
		{
			trace("-----------onLinkCallBack");
			var commandParameter:Array = e.text.split(","); //获取event:后面的内容的数组
			ExternalInterface.call( "ASLinkCallBack", commandParameter);
		}

		function clickNext()
		{
			ExternalInterface.call( "ASNPCDialogNextPage" );
		}

		function clickAnswer( e:Event )
		{
			if( e.target is Button )
			{
				ExternalInterface.call("ASNPCDialogAnswer",(e.target as Button).itemid);
			}
		}

		


		function clickOk()
		{
			ExternalInterface.call("ASAcceptQuest");
			parent.visible = false;
		}
		
		function clickNo()
		{
			parent.visible = false;
		}
	}

}