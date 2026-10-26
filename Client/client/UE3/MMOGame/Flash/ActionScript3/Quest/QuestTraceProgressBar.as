//
// 成就系统： 任务追踪进度条 
//
package  ActionScript3.Quest
{
	import flash.display.MovieClip;	
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	
	public class QuestTraceProgressBar extends UIComponent 
	{
		public var user_data:int;
		public var progress_mc:MovieClip;
		//public var progress_text_tf:TextField;
		public var progress_cur:int;
		public var progress_max:int;
		
		public function QuestTraceProgressBar()
		{
			// constructor code
			progress_cur = 0;
			progress_max = 1;
		}
		
		override protected  function configUI():void 
		{
			super.configUI();
			
			this.addEventListener("rollOver", onItemRollOver);
			this.addEventListener("rollOut", onItemRollOut);
		}
		
		public function setProgressPercent(type:int, cur:int, max:int)
		{					
			var fill_red_mc:MovieClip = progress_mc.getChildByName("fill_red_mc") as MovieClip;
			var fill_green_mc:MovieClip = progress_mc.getChildByName("fill_green_mc") as MovieClip;
			var mask_mc:MovieClip = progress_mc.getChildByName("mask_mc") as MovieClip;
			
			if (type == 0)
			{
				fill_red_mc.visible = false;
				fill_green_mc.visible = true;
			}
			else
			{
				fill_red_mc.visible = true;
				fill_green_mc.visible = false;
			}
			
		    progress_cur = cur;
		    progress_max = max;
			var percent:Number = cur / max;
			mask_mc.width = this.width * percent;
			
			//var per:int = percent * 100;
			//progress_text_tf.text = per.toString() + "%";
		}
		
		public function RemoveAll()
		{
			progress_mc = null;
			//progress_text_tf=null;
			this.removeEventListener("rollOver", onItemRollOver);
			this.removeEventListener("rollOut", onItemRollOut);
		}				
		
		public function onItemRollOver(e:Event)
		{
			var percent_text:String = progress_cur.toString() + "/" + progress_max.toString();
			ExternalInterface.call("ASShowTips_PlainText_WithString", this, percent_text);
		}
		
		public function onItemRollOut(e:Event)
		{
			ExternalInterface.call("ASHideTips_PlainText", this);
		}
	}
}
