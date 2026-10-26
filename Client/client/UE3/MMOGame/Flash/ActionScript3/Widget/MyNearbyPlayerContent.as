package ActionScript3.Widget
{
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import flash.external.ExternalInterface;
	import scaleform.gfx.Extensions;
	import flash.geom.Point;
	import flash.text.TextField;
	import scaleform.gfx.MouseEventEx;
	
	public class MyNearbyPlayerContent extends UIComponent
	{
/*		public var TeamContentPrePageButton:Button;
		public var TeamContentNextPageButton:Button;*/
		public static var ItemMaxLine:int = 12;
		public var InvitePlayer:Button;
		
		public var tabTitle:MovieClip;
		public var _page:MovieClip;
		public var TeamContentCurPage_txt:TextField;
		override protected  function configUI():void {
			super.configUI();
			TeamContentCurPage_txt=_page.tF_pageNum;
			Extensions.enabled = true;
			var i:int;
			for( i = 0 ; i < ItemMaxLine ;i++ )
			{
				var item:RadioButton = this.getChildByName( "TeamContentItem"+i ) as RadioButton;
				if(item)
				{
					item.itemid = i;
					item.addEventListener( MouseEvent.CLICK , SelectPlayer );
				}
			}
			
			if( InvitePlayer)
				InvitePlayer.addEventListener(MouseEvent.CLICK , ClickInvitePlayer);
			
			if( _page.btn_prev)
				 _page.btn_prev.addEventListener( MouseEvent.CLICK , ClickPrePage );
			if( _page.btn_next )
				 _page.btn_next.addEventListener( MouseEvent.CLICK , ClickNextPage );
		}
		
		private function SelectPlayer(evt:MouseEvent):void
		{
			if( evt.target is RadioButton )
			{
				var Item = evt.target as RadioButton;
				ExternalInterface.call( "ASTeamSelectNearbyPlayer" , Item.itemid );
								
				if( (evt is MouseEventEx) && (evt as MouseEventEx).buttonIdx == 1)
				{
					var pos:Point = new Point;
					pos.x = Item.x + Item.width;
					pos.y = Item.y ;
					pos = Item.parent.localToGlobal( pos);
						//var NameText:TextField = Item.getChildByName( "tF_playerName" ) as TextField ;
					ExternalInterface.call( "ASTeamNearbyPlayerRightClick",pos.x, pos.y, Item.itemid );
				}
			}
		}
		
		private function ClickInvitePlayer(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamInviteNearbyPlayer" );
		}
		
				
		private function ClickPrePage(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamNearbyPlayerPrePage" );
		}
		
		private function ClickNextPage(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamNearbyPlayerNextPage" );
		}
	}
}