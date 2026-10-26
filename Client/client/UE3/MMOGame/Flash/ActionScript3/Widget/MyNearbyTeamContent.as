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
	import flash.text.TextField;
	
	public class MyNearbyTeamContent extends UIComponent
	{
		public static const ItemMaxLine:int = 12 ;
		public var EnterTeam:Button;
		public var _page:MovieClip;
		public var tabTitle:MovieClip;
		public var TeamContentCurPage_txt:TextField;
		
		override protected  function configUI():void 
		{
			super.configUI();
			TeamContentCurPage_txt=_page.tF_pageNum;
			Extensions.enabled=true;
			var i:int;
			for( i = 0 ; i < ItemMaxLine ;i++ )
			{
				var item:RadioButton = this.getChildByName( "TeamContentItem"+i ) as RadioButton;
				if(item)
				{
					item.itemid = i;
					item.addEventListener( MouseEvent.CLICK , SelectTeam );
				}
			}
			if( EnterTeam)
				EnterTeam.addEventListener(MouseEvent.CLICK , ClickEnterTeam);
			
			if( _page.btn_prev)
				 _page.btn_prev.addEventListener( MouseEvent.CLICK , ClickPrePage );
			if( _page.btn_next )
				 _page.btn_next.addEventListener( MouseEvent.CLICK , ClickNextPage );
		}
		
		private function ClickEnterTeam(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamEnterNearbyTeam" );
		}
		
		private function SelectTeam( e:MouseEvent):void
		{
			if( e.target is RadioButton )
			{
				var Item:RadioButton =  e.target as RadioButton;
				ExternalInterface.call( "ASTeamSelectNearbyTeam" ,Item.itemid );
			}
		}
		
		private function ClickPrePage(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamNearbyTeamPrePage" );
		}
		
		private function ClickNextPage(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamNearbyTeamNextPage" );
		}
	}
}