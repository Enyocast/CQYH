package UI_KillRecord.killrecordAS
{
	import scaleform.clik.core.UIComponent;
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.utils.getDefinitionByName;
	
	public class NumberTitle extends UIComponent
	{
		var _NumberClass0:Class;
		var _NumberClass1:Class;
		var _NumberClass2:Class;
		var _NumberClass3:Class;
		var _NumberClass4:Class;
		var _NumberClass5:Class;
		var _NumberClass6:Class;
		var _NumberClass7:Class;
		var _NumberClass8:Class;
		var _NumberClass9:Class;
		
		var _KillTitle0:Class;
		var _KillTitle1:Class;
		var _KillTitle2:Class;
		var _KillTitle3:Class;
		var _KillTitle4:Class;
		var _KillTitle5:Class;
		var _KillTitle6:Class;
		
		public var number_mc:TextField;
		public var killMore_mc:MovieClip;
		public var justKill_mc:MovieClip;
		
		var mcTitle:MovieClip = null;
		var mcNumHun:MovieClip = null;
		var mcNumTen:MovieClip = null;
		var mcNumBer:MovieClip = null;
		
		override protected function configUI():void
		{
			//
			super.configUI();

			_NumberClass0 = getDefinitionByName("number0") as Class;
			_NumberClass1 = getDefinitionByName("number1") as Class;
			_NumberClass2 = getDefinitionByName("number2") as Class;
			_NumberClass3 = getDefinitionByName("number3") as Class;
			_NumberClass4 = getDefinitionByName("number4") as Class;
			_NumberClass5 = getDefinitionByName("number5") as Class;
			_NumberClass6 = getDefinitionByName("number6") as Class;
			_NumberClass7 = getDefinitionByName("number7") as Class;
			_NumberClass8 = getDefinitionByName("number8") as Class;
			_NumberClass9 = getDefinitionByName("number9") as Class;
			
			_KillTitle0 = getDefinitionByName("killtitle0") as Class;
			_KillTitle1 = getDefinitionByName("killtitle1") as Class;
			_KillTitle2 = getDefinitionByName("killtitle2") as Class;
			_KillTitle3 = getDefinitionByName("killtitle3") as Class;
			_KillTitle4 = getDefinitionByName("killtitle4") as Class;
			_KillTitle5 = getDefinitionByName("killtitle5") as Class;
			_KillTitle6 = getDefinitionByName("killtitle6") as Class;
		}
		
		public function SetNewKillCount(nType:int,nCount:int)
		{
			killMore_mc.visible = false;
			justKill_mc.visible = false;
			clearClip();
				
			//连斩
			if(nType == 0)
			{
				GenerateNumber(nCount);
				killMore_mc.visible = true;
			}
			//瞬间击杀
			else if(nType == 1)
			{
				GenerateNumber(nCount);
				justKill_mc.visible = true;
			}
			//大杀特杀 
			else if(nType == 2)
			{
				if(nCount < 3 )
					nCount = 3;
				if(nCount > 9)
					nCount = 9;
				nCount -= 3;
				
				mcTitle = AddNewTitle(mcTitle,nCount);
			}
		}
		
		function clearClip()
		{
			trace("GenerateNumber mcNumHun = 1",mcNumHun);
			if(mcNumHun != null)
			{
				trace("GenerateNumber mcNumHun = ",mcNumHun.visible);
				mcNumHun.visible = false;
				removeChild(mcNumHun);
				mcNumHun = null;
			}
			if(mcNumTen != null)
			{
				trace("GenerateNumber mcNumTen = ",mcNumTen.visible);
				mcNumTen.visible = false;
				removeChild(mcNumTen);
				mcNumTen = null;
			}
			if(mcNumBer != null)
			{
				trace("GenerateNumber mcNumBer = ",mcNumBer.visible);
				mcNumBer.visible = false;
				removeChild(mcNumBer);
				mcNumBer = null;
			}
			trace("SetNewKillCount mcTitle = 2",mcTitle);
			if(mcTitle != null)
			{
				mcTitle.visible = false;
				removeChild(mcTitle);
			}
		}
		function GenerateNumber(nCount:int)
		{
			var nHun:int = nCount/100;
			var nTen:int = (nCount%100)/10;
			var nNum:int = nCount%10;
			
			var nPosx:int = number_mc.x + number_mc.width;
			var nPosy:int = number_mc.y;
			if(nHun > 0)
			{
				mcNumHun = AddNewNumber(mcNumHun,nHun,nPosx - 57,nPosy);
			}
			
			if(nTen > 0 || nHun > 0)
			{
				mcNumTen = AddNewNumber(mcNumTen,nTen,nPosx - 38,nPosy);
			}
			
			if(nNum > 0 || nTen > 0 || nHun > 0)
			{
				mcNumBer = AddNewNumber(mcNumBer,nNum,nPosx - 19,nPosy);
			}
		}
		function AddNewTitle(mcNumClip:MovieClip,nNum:int):MovieClip
		{
			if(nNum == 0)
				mcNumClip = new _KillTitle0 as MovieClip;
			else if(nNum == 1)
				mcNumClip = new _KillTitle1 as MovieClip;
			else if(nNum == 2)
				mcNumClip = new _KillTitle2 as MovieClip;
			else if(nNum == 3)
				mcNumClip = new _KillTitle3 as MovieClip;
			else if(nNum == 4)
				mcNumClip = new _KillTitle4 as MovieClip;
			else if(nNum == 5)
				mcNumClip = new _KillTitle5 as MovieClip;
			else if(nNum == 6)
				mcNumClip = new _KillTitle6 as MovieClip;
			if(mcNumClip != null)
			{
				addChild(mcNumClip);
				mcNumClip.x = number_mc.x + 20;
				mcNumClip.y = number_mc.y;
				mcNumClip.visible = true;
				
				return mcNumClip;
			}
			return null;
		}
		
		function AddNewNumber(mcNumClip:MovieClip,nNum:int,nPosX:int,nPosY:int):MovieClip
		{
			if(nNum == 0)
				mcNumClip = new _NumberClass0 as MovieClip;
			else if(nNum == 1)
				mcNumClip = new _NumberClass1 as MovieClip;
			else if(nNum == 2)
				mcNumClip = new _NumberClass2 as MovieClip;
			else if(nNum == 3)
				mcNumClip = new _NumberClass3 as MovieClip;
			else if(nNum == 4)
				mcNumClip = new _NumberClass4 as MovieClip;
			else if(nNum == 5)
				mcNumClip = new _NumberClass5 as MovieClip;
			else if(nNum == 6)
				mcNumClip = new _NumberClass6 as MovieClip;
			else if(nNum == 7)
				mcNumClip = new _NumberClass7 as MovieClip;
			else if(nNum == 8)
				mcNumClip = new _NumberClass8 as MovieClip;
			else if(nNum == 9)
				mcNumClip = new _NumberClass9 as MovieClip;
			
			if(mcNumClip != null)
			{
				addChild(mcNumClip);
				mcNumClip.x = nPosX;
				mcNumClip.y = nPosY;
				mcNumClip.visible = true;
				return mcNumClip;
			}
			return null;
		}
	}
}