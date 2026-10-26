package UI_HintCombat.HintCombatAS3
{

	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import UI_HintCombat.HintCombatAS3.CounterBarFill;
	import UI_HintCombat.HintCombatAS3.CounterDown;

	public class HintCombatPanel extends MyPanel
	{

		public var CounterBarFill_mc:CounterBarFill;
		public var CounterDown_mc:CounterDown;

		override protected function configUI():void
		{
			super.configUI();
			ExternalInterface.call( "RegisterBossQTE", this );
			//UpdateQte(4, 8);
			//UpdateQte(0, 8);
		}
		
		public function UpdateQte(CounterNum:int, CounterDownNum:int):void
		{
			if(CounterDownNum>=0){
				if(CounterDownNum>9)CounterDownNum=9;
				CounterDown_mc.SetCounterDown(CounterDownNum);
			}
			if(CounterNum>=0){
				CounterBarFill_mc.SetCounterBar(CounterNum);
			}
		}

	}
}