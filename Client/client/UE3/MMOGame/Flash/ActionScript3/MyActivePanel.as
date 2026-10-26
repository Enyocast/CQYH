package ActionScript3 {
	
import flash.display.MovieClip;
import scaleform.clik.core.UIComponent;
import scaleform.clik.controls.Label;
	import flash.events.Event;
	import flash.events.MouseEvent;

import flash.external.ExternalInterface;

	public class MyActivePanel extends UIComponent //ActionScript.MyPanel
	{
		var pause:Boolean = false;
		var Ownerlist:Array; // 拥有人控件，点击此，不会导致自己关闭
		
		override protected  function configUI():void {
			super.configUI();
			
			//trace("MyActivePanel"+name);
			Ownerlist = new Array;

			stage.addEventListener(MouseEvent.MOUSE_DOWN, handleStageClick, false, 0, true);
		}
		
		//增加拥有者，点击这个不会关闭自己
		public function AddOwner( Owner:Object )
		{
			trace("AddOwner"+name+Owner);
			
			if(Ownerlist)
			{
				Ownerlist.push(Owner);
			}
		}
		
		function handleStageClick( e:Event )	
		{
			
					
			if( !visible)
				return;

			if(  mouseX > 0 && mouseX < width && mouseY > 0 && mouseY < height )
			{
				
			}
			else
			{
				//var dt = this["root"].mouse_mc._droptarget;
				//var pos = dt.indexOf("MenuSwitch_mc");
				
				var i:int;
				var closeself:Boolean = true;
				for( i = 0 ; i < Ownerlist.length ;i ++ )
				{
					
					if( Ownerlist[i] == e.target )
					{
						//trace("skip");
						closeself = false;
						break;
					}				
					
				}
				if(closeself)
					visible = false;
			}
		}
	}

}