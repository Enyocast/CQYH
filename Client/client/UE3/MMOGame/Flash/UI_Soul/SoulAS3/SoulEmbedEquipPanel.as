package UI_Soul.SoulAS3
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.filters.ColorMatrixFilter;
	import flash.geom.ColorTransform;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import UI_Soul.SoulAS3.SoulEmbedPanel;
	import UI_Soul.SoulAS3.SoulLevelUpPanel;
	import UI_Soul.SoulAS3.SoulUnEmbedPanel;
	
	import fl.motion.ColorMatrix;
	
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.RadioButton;
	
	public class SoulEmbedEquipPanel extends MyPanel
	{
		public var EmbedTabBtn:RadioButton;
		public var UnEmbedTabBtn:RadioButton;
		public var LevelUpTabBtn:RadioButton;
		
		public var EmbedSoulPanel:SoulEmbedPanel;
		public var UnEmbedSoulPanel:SoulUnEmbedPanel;
		public var LevelUpSoulPanel:SoulLevelUpPanel;
		
		override protected function configUI():void
		{
			super.configUI();
			
			//EmbedTabBtn.icon_mc.gotoAndStop( EmbedTabBtn.TabType );
			//EmbedTabBtn.icon_mc.loader_mc.source = "img://MMO_UIImg.img_tab_soul_0";
			EmbedTabBtn.addEventListener( MouseEvent.CLICK, function _onClickTabChangeContent(e:Event){ onClickTabChangeContent( 0 );} );
			
			//UnEmbedTabBtn.icon_mc.gotoAndStop( UnEmbedTabBtn.TabType );
			//UnEmbedTabBtn.icon_mc.loader_mc.source = "img://MMO_UIImg.img_tab_soul_1";
			UnEmbedTabBtn.addEventListener( MouseEvent.CLICK, function _onClickTabChangeContent(e:Event){ onClickTabChangeContent( 1 );} );
			
			LevelUpTabBtn.addEventListener( MouseEvent.CLICK, function _onClickTabChangeContent(e:Event){ onClickTabChangeContent( 2 );} );
			
			EmbedSoulPanel.visible = true;
			UnEmbedSoulPanel.visible = false;
			LevelUpSoulPanel.visible = false;
			
			//ExternalInterface.call( "RegisterSoulEmbed", this );
			//trace( "======================XXXX:", super.UCGetWidth(), UCGetWidth() );
		}
		
		//
		function onClickTabChangeContent( idx:int )
		{
			//
			EmbedSoulPanel.visible = false;
			UnEmbedSoulPanel.visible = false;
			LevelUpSoulPanel.visible = false;
			
			if( idx == 1){
				UnEmbedSoulPanel.visible = true;
			}
			else if( idx == 0){
				EmbedSoulPanel.visible = true;
			}
			else if( idx == 2){
				LevelUpSoulPanel.visible = true;
			}
			//
			
			ExternalInterface.call( "ASOnEmbedPanelTabBtnClick", idx );
		}
		//
		override public function UCGetWidth():int
		{
			var modifiedWidth:int;
			if( MyWindowsFrame_mc ){
				modifiedWidth = MyWindowsFrame_mc.width;//( super.UCGetWidth() - 22 );
			}
			
			return modifiedWidth;//剪掉的是TabBtn出0点的宽度
		}
		//
		public function UCGraySlot( mc:MovieClip , gray:Boolean )
		{
			if (! mc)
			{
				return;
			}

			if (gray)
			{
				var matrix:Array = new Array  ;

				var colorMatrix:ColorMatrix = new ColorMatrix;

				matrix = matrix.concat([0.3086,0.6094,0.082,0,0]);
				matrix = matrix.concat([0.3086,0.6094,0.082,0,0]);
				matrix = matrix.concat([0.3086,0.6094,0.082,0,0]);
				matrix = matrix.concat([0,0,0,1,0]);

				var filter:ColorMatrixFilter = new ColorMatrixFilter(matrix);


				//var filters:Array = new Array  ;
				//filters.push( filter );
				mc.filters = [ filter ];

				//mc.alpha = 0.2;
			}
			else
			{
				//mc.alpha = 1;
				mc.filters = null;
			}
		}
		
		public function UCSetEmbedResult(value:int):void
		{
			EmbedSoulPanel.UCSetEmbedResult(value);
		}
		
		public function UCSetUnEmbedResult(value:int):void
		{
			UnEmbedSoulPanel.UCSetUnEmbedResult(value);
		}
	}
}