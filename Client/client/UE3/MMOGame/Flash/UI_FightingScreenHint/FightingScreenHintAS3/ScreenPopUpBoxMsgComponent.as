package UI_FightingScreenHint.FightingScreenHintAS3
{
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	//import flash.utils.getTimer;
	
	public class ScreenPopUpBoxMsgComponent extends UIComponent
	{
		public var Title_mc:MovieClip;
		var TitleString:String = "";
		
		public var Detail_mc:MovieClip;
		var DetailString:String = "";
		
		public var Icon_mc:MovieClip;
		var IconImgString:String = "";
		
		public var InfoType:int;
		
		protected var _title_text_mc:MovieClip;
		protected var _title_tf:TextField;
		
		override protected function configUI():void
		{
			super.configUI();
			if(Title_mc){
				_title_text_mc = Title_mc.getChildByName('title_text_mc') as MovieClip;
				_title_tf 	   = Title_mc.getChildByName('tF_Text') as TextField;
				if(_title_text_mc){
					_title_text_mc.visible = false;
				}
			}
			stop();
		}
		
		public function useImageText(typeIndex:int):void
		{
			if(_title_text_mc){
				_title_text_mc.visible = true;
				_title_text_mc.gotoAndStop("type_" + typeIndex);
			}
			if(_title_tf){
				_title_tf.visible = false;
			}
		}
		
		public function SetInfo( titleStr:String, detailStr:String, iconName: String )
		{
			gotoAndPlay(1);
			this.visible = true;
			
			TitleString = titleStr;
			DetailString = detailStr;
			IconImgString = iconName;
			
			UpdateMsgContent();
		}
		
		public function OnPLayEnd()
		{
			this.visible = false;
			stop();
			ExternalInterface.call( "ASScreenPopUpBoxMsgPlayEnd");
			//trace( "----------------End Time:", getTimer() );
		}
		
		//
		public function UpdateMsgContent()
		{
			Title_mc = ( getChildByName( "Title_mc" ) as MovieClip );
			if( Title_mc != null){
				if(Title_mc.tF_Text && Title_mc.tF_Text.visible){
					Title_mc.tF_Text.text = TitleString;
				}
			}
			
			Detail_mc = ( getChildByName( "Detail_mc" ) as MovieClip );
			if( Detail_mc != null ){
				Detail_mc.tF_Text.text = DetailString;
			}
			
			Icon_mc = ( getChildByName( "Icon_mc" ) as MovieClip );
			if( Icon_mc != null ){
				if( "" != IconImgString && IconImgString.length != 0 ){
					var iconUILoader:UILoader = ( Icon_mc.getChildByName( "IconUILoader" ) as UILoader );
					if( iconUILoader != null ){
						iconUILoader.source = "img://" + IconImgString;
					}
					
					Icon_mc.visible = true;
					//trace("============================IconLoader", iconUILoader.source);
				}
				else{
					Icon_mc.visible = false;
				}
			}
		}
	}
}