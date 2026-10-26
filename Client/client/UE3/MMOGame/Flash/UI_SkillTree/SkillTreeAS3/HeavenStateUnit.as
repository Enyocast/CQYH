package UI_SkillTree.SkillTreeAS3
{
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.display.MovieClip;

	public class HeavenStateUnit extends UIComponent
	{
		//public var nowTag:MovieClip;
		public var stateText:MovieClip;
		public var levelStar0:MovieClip;
		public var levelStar1:MovieClip;
		public var levelStar2:MovieClip;
		public var levelStar3:MovieClip;
		public var levelStar4:MovieClip;
		
	    public var Statedata : HeavenStateData;
		
		public var keyFrame:Array = new Array();
		
		override protected function configUI():void
		{
			super.configUI();
			
			keyFrame[0] = "1_1";
			keyFrame[1] = "1_2";
			keyFrame[2] = "1_3";
			keyFrame[3] = "2_1";
			keyFrame[4] = "2_2";
			keyFrame[5] = "2_3";
			keyFrame[6] = "3_1";
			keyFrame[7] = "3_2";
			keyFrame[8] = "3_3";
			keyFrame[9] = "4_1";
			keyFrame[10] = "4_2";
			keyFrame[11] = "4_3";
			keyFrame[12] = "4_4";
			keyFrame[13] = "4_5";
			
			this.addEventListener(MouseEvent.ROLL_OVER, onRollOverHeavenLevelSlot);
			this.addEventListener(MouseEvent.ROLL_OUT, onRollOutHeavenLevelSlot);
		}

		function UpdateData(data:Object):void
		{
			Statedata = data as HeavenStateData;
			
			if(!Statedata )
			{
				visible = false;
				return;
			}
			visible = true;
			/*
			if(Statedata.IsNowState)
				nowTag.visible = true;
			else
				nowTag.visible = false;
*/
			Statedata.nStarNum >= 1? levelStar0.gotoAndStop("on"):levelStar0.gotoAndStop("off");
			Statedata.nStarNum >= 2? levelStar1.gotoAndStop("on"):levelStar1.gotoAndStop("off");
			Statedata.nStarNum >= 3? levelStar2.gotoAndStop("on"):levelStar2.gotoAndStop("off");
			Statedata.nStarNum >= 4? levelStar3.gotoAndStop("on"):levelStar3.gotoAndStop("off");
			Statedata.nStarNum >= 5? levelStar4.gotoAndStop("on"):levelStar4.gotoAndStop("off");
			
			if(Statedata.nStateIndex <= 13)
			{
				visible = true;
				stateText.gotoAndStop(keyFrame[Statedata.nStateIndex]);
			}
			else
				visible = false;
		}
		
		function onRollOverHeavenLevelSlot( e:Event )
		{
			trace("***onRollOverHeavenLevelSlot");
			if(Statedata != null){
				ExternalInterface.call("ASShowTips_HeavenLevel",this,Statedata.nStateIndex);
			}
		}

		function onRollOutHeavenLevelSlot( e:Event )
		{
			trace("***onRollOutHeavenLevelSlot");
			//
			ExternalInterface.call("ASHideTips_HeavenLevel" );
		}
	}
}