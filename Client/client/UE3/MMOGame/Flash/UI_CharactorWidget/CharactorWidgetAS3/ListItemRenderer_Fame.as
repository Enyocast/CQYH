package UI_CharactorWidget.CharactorWidgetAS3
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	import ActionScript3.Charactor.FamePanel;
	
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.events.ListEvent;
	
	public class ListItemRenderer_Fame extends ListItemTreeRenderer
	{
		public var titleStar_mc:MovieClip;
	//	public var current_mc:MovieClip;
		public var new_mc:MovieClip;
	//	public var titleName:TextField;
		public var fameImgLoader_mc:UILoader;
		
		protected var _rendererData:Object;
		
		public function ListItemRenderer_Fame()
		{
			super();
		}
		
		override protected function configUI():void
		{
			// TODO Auto Generated method stub
			super.configUI();
			//增加赋值回调
			if (this && this.updateDataCallBack == null)
			{
				this.updateDataCallBack = updateData;
			}
		}
		
		public function getRendererData():Object
		{
			return _rendererData;
		}
		
		public function handleListItemClick(TitleTabIndex:int):void
		{
			//hide new_mc;
			if(TitleTabIndex == 1 && _rendererData != null)
			{
				new_mc.visible =  _rendererData.isNew = false;
			}
		}
		
		public function handleListItemRollOver(event:ListEvent):void
		{
			//super.handleMouseRollOver(event);
		}
		
		public function handleListItemRollOut(event:ListEvent):void
		{
			//super.handleMouseRollOut(event);
		}

		//var tf:TextFormat =  titleName.getTextFormat();
		//	tf.align = TextFormatAlign.CENTER ;
		//	titleName.defaultTextFormat = tf;
		
		protected function updateData(data:Object):void
		{
			_rendererData = data;
			if(_rendererData)
			{
				visible = true;
				titleStar_mc.gotoAndStop(_rendererData.numStar);
			//	current_mc.visible 	= _rendererData.isCurrent;
				new_mc.visible	   	= _rendererData.isNew;
			//	titleName.text 		= _rendererData.label;
				
				fameImgLoader_mc.source = _rendererData.IconName;
				if (fameImgLoader_mc.source != null){
					fameImgLoader_mc.visible = true;
				}else{
					fameImgLoader_mc.visible = false;
				}
			}
			else
			{
				visible = false;
			}
		}
	}
}