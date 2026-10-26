package ActionScript3.Battle
{
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.ListItemRenderer;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.gfx.MouseEventEx;
	import flash.geom.Point;
	
	public class BattleTeamMemberListItem extends ListItemTreeRenderer 
	{	
		public var MemberName:TextField;
		public var MemberClass:TextField;
		public var MemberBattleCount:TextField;
		public var MemberGrade:TextField;
		public var MemberRate:TextField;
		public var TeamLeadIcon:MovieClip;
		
		public var MemberRoleId:int;
		
		public function BattleTeamMemberListItem()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			MemberRoleId = -1;
			
			this.addEventListener( MouseEvent.CLICK , rightClickItem , false , 0 , true );
			setUpdateDataCallBack(updateItemData);
		}
		
		public function rightClickItem( e:Event )
		{
			if( ( e as MouseEventEx ).buttonIdx == 1 )
			{
				var pos:Point = new Point  ;
				pos.x = x + width;

				pos.y = y;

				pos = parent.localToGlobal(pos);
				
				ExternalInterface.call( "ASBattleTeamRightClickMember" , MemberRoleId , pos.x , pos.y );
			}
			
		}
		
		public function updateItemData(data:Object):void
		{
			//trace( "ok:"+ data );
			if (data != null)
			{
				visible = true;
				
				MemberName.text = data.MemberName;
				MemberClass.text = data.MemberClass;
				MemberBattleCount.text = data.MemberBattleCount;
				MemberGrade.text = data.MemberGrade;
				MemberRate.text = data.MemberRate;
				MemberRoleId = data.MemberRoleId;
				TeamLeadIcon.visible = data.IsLeader;
			}
			else
			{
				visible = false;
			}	
		}
	}
}