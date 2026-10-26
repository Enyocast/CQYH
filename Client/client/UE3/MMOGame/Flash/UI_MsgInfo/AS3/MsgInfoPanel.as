package UI_MsgInfo.AS3 {
	
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Events.ParamEvent;
	import flash.text.TextField;
	import scaleform.clik.managers.PopUpManager;
	import flash.events.MouseEvent;
	import flash.display.DisplayObject;
	import scaleform.clik.core.UIComponent;
	
	public class MsgInfoPanel extends MyPanel {
		
		public var message0:MovieClip;
		public var message1:MovieClip;
		public var message2:MovieClip;
		public var message3:MovieClip;

		override protected function configUI():void
		{
			ShowMode="TC";//顶部居中
			super.configUI();
			this.mouseChildren=false;
			this.enabled=false;
			var i:int=0;
			for(i=0;i<4;i++)
			{
				var mc:MovieClip=this.getChildByName("message"+i) as MovieClip;
				mc.mouseChildren=false;
				mc.mouseEnabled=false;
			}
			stageChangeHandler(null);
			//SetFilter( {  textField:message0.Msg_TextField , type:1 , textColor:"0xff0000" } );
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{ 
			super.stageChangeHandler(evt);
			this.x=(cavasWidth-600>>1)+300;
		}
	
		public function SetFilter( data:Object  )
		{
			var tf:TextField = data.textField;
			if( tf )
			{
				var mc:MovieClip=(tf.parent as MovieClip);
				if(mc)
				{
					var i:int=0;
					var l:int=mc.numChildren;
					for(i;i<l;i++)
					{
						var dis:DisplayObject=mc.getChildAt(i);
						if(dis is MovieClip)
						{
							
						}
					}
				}
				mc._bg.width=tf.textWidth+16;
				mc._bg.x=-mc._bg.width/2;
				if(data.type!=null){
					if(data.type==0){
						(mc._bg as MovieClip).gotoAndStop(1);
						tf.textColor = 0xff0000;
					}else{
						(mc._bg as MovieClip).gotoAndStop(2);
						tf.textColor=0x00f4FF;
					}
				}
			}
		}
	}
	
}
