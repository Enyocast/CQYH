package UI_BattleSummary.BattleSummaryAS3
{

	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import UI_BattleSummary.BattleSummaryAS3.BtlScoreListItemData;

	public class BtlScoreListItem extends MovieClip 
	{
		//public var bg_mc:MovieClip;
		public var PlayerIcon_mc:MovieClip;
		//public var PlayerClass_tf:TextField;
		public var PlayerName_tf:TextField;
		public var PlayerLv_tf:TextField;
		//public var Hunted_tf:TextField;
		//public var BeKilled_tf:TextField;
		public var HuntData_tf:TextField;
		public var Damages_tf:TextField;
		public var Heals_tf:TextField;
		public var BattleScore_tf:TextField;
		public var AwardPoints_tf:TextField;
		
		public var rowData:BtlScoreListItemData;

		//
		public function updateData(data:Object):void
		{
			rowData = data as BtlScoreListItemData;
			
			//trace("BtlScore::updateData", rowData.index, rowData.PlayerName );
			
			if( rowData ){				
				visible = true;
				//bg_mc.gotoAndStop( rowData.TeamID + 1 );
				
				PlayerIcon_mc.gotoAndStop(rowData.PlayerClassName);

				//PlayerClass_tf.text = rowData.PlayerClassName;

				PlayerName_tf.text = String( rowData.PlayerName );
				PlayerLv_tf.text = String( rowData.PlayerLv );
				//Hunted_tf.text = rowData.Hunted;
				//BeKilled_tf.text = rowData.BeKilled;
				HuntData_tf.text = rowData.Hunted + "/" + rowData.BeKilled;
				Damages_tf.text = String( rowData.Damages );
				Heals_tf.text = String( rowData.Heals);
				BattleScore_tf.text = String( rowData.BattleScore );
				if( rowData.AwardPoints < 0 ){
					AwardPoints_tf.text = "--";
				}
				else{
					AwardPoints_tf.text = String( rowData.AwardPoints );
				}
			}
			else{
				visible = false;
			}
		}
		//
	}

}