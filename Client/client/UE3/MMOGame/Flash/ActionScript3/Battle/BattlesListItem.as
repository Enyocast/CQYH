package ActionScript3.Battle
{

	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.CheckBox;

	public class BattlesListItem extends ListItemTreeRenderer
	{
		public var listBattleName_mc:TextField;
		public var listBattleIcon_mc:MovieClip;
		public var listBattleSelect_mc:MovieClip;
		
		public var battleData:BattlesListItemData;

		override protected function configUI():void
		{
			trace("------BattlesListItem  super.configUI:");
			super.configUI();
			
			this.addEventListener(MouseEvent.ROLL_OVER, onRollOverBattle);
			this.addEventListener(MouseEvent.ROLL_OUT, onRollOutBattle);			
			//this.addEventListener( MouseEvent.CLICK, onSelectBattle );
			
			// 这里一定要注意设置回调处理函数
			setUpdateDataCallBack(updateData);
		}

		function updateData(data:Object):void
		{
			battleData = data as BattlesListItemData;
			
			//trace("MailListItem::updateData", data , mail_data);
			
			if( battleData ){				
				visible = true;
				
				listBattleIcon_mc.gotoAndStop(battleData.BattleIconIdx);
				listBattleName_mc.text = battleData.BattleName;
				listBattleSelect_mc.gotoAndStop(battleData.BattleSelected ? "unChk" : "chkBegin");
			}
			else{
				visible = false;
			}
		}
		function onRollOverBattle()
		{
			this.gotoAndPlay("over");
		}

		function onRollOutBattle()
		{
			this.gotoAndPlay("up");
		}
	}

}