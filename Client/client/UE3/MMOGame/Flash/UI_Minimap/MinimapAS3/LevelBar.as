package UI_Minimap.MinimapAS3
{
	import scaleform.clik.core.UIComponent;
	import flash.external.ExternalInterface;
	import flash.display.DisplayObject;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;


	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.Button;


	public class LevelBar extends UIComponent
	{
		public var ProcessBar_fill:MovieClip;
		public var textName:TextField;
		public var ProcesBarMask:MovieClip;
		public var dataObj:Object;
		public var mouseOverFlag:Boolean = false;
		
		public var textNum:TextField;
		public var TipsObj:Object = {title:"object", text:"objectTips" };
		
		public var isTrace:Boolean = false;
		public var isExpand:Boolean = true;

		override protected function configUI():void
		{
			super.configUI();
			this.addEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
			addEventListener(MouseEvent.CLICK, handleClick);
			//addEventListener(MouseEvent.ROLL_OVER, handleListItemRollOver);
			//addEventListener(MouseEvent.ROLL_OUT, handleListItemRollOut);

		}

		
		public function onRmoved(e:Event):void
		{
			this.removeEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
			removeEventListener(MouseEvent.CLICK, handleClick);
			//removeEventListener(MouseEvent.ROLL_OVER, handleListItemRollOver);
			//removeEventListener(MouseEvent.ROLL_OUT, handleListItemRollOut);						
		}		
		
		public function updateData(data:Object):void
		{
			if (data==null)
			{
				return;
			}
			
			isTrace = data.visible;
			if (isTrace == false)
			{
				visible = false;
				return;
			}

			dataObj = data;
			TipsObj.title 	= data.label;
			TipsObj.text  	= data.tips;		
	
			ProcesBarMask.width = ProcessBar_fill.width*(dataObj.curReputation-dataObj.minReputation)/(dataObj.maxReputation-dataObj.minReputation);
			if(dataObj.curReputation>=dataObj.maxReputation){
				ProcessBar_fill.gotoAndStop(2);
			}else{
				ProcessBar_fill.gotoAndStop(1);
			}
            textNum.text = (dataObj.curReputation-dataObj.minReputation)+"/"+(dataObj.maxReputation-dataObj.minReputation);
			textName.text = data.label;// + "  " + dataObj.txtReputation;
/*			if (mouseOverFlag)
			{
				textName.text = (dataObj.curReputation-dataObj.minReputation)+"/"+(dataObj.maxReputation-dataObj.minReputation);
			}
			else
			{
				textName.text = data.label + "  " + dataObj.txtReputation;
			}*/
			
			visible = isTrace && isExpand;
		}

		function handleClick(e:MouseEvent):void
		{
			ExternalInterface.call( "ASShowReputionPanel", true );
		}
		
		function handleListItemRollOver():void
		{
			mouseOverFlag = true;
			updateData(dataObj);
			ExternalInterface.call( "ASShowTips_Text",TipsObj );
		}

		function handleListItemRollOut():void
		{
			mouseOverFlag = false;
			updateData(dataObj);
			ExternalInterface.call( "ASHideTips_Text",TipsObj );
		}

		public function setExpand(expand:Boolean)
		{
			isExpand = expand;
			visible = isTrace && isExpand;
		}
	}
}