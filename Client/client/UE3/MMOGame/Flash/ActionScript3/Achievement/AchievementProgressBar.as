//
// 成就系统：个人成就总结分类进度条 
//
package  ActionScript3.Achievement {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	
	public class AchievementProgressBar extends Button 
	{
		public var user_index:int;
		public var progress_mask_mc:MovieClip;
		public var progress_bar_indicator_mc:MovieClip;
		public var name_tf:TextField;
		public var score_tf:TextField;
		
		private var _progress_mask_width:int;
		
		public function AchievementProgressBar()
		{
			_progress_mask_width = progress_mask_mc.width;
		}
		
		override protected  function configUI():void 
		{
			super.configUI();
			if(progress_bar_indicator_mc){
				progress_bar_indicator_mc.mouseEnabled = false;
			}
		}
		
		public function setTitle(title:String)
		{
			name_tf.text = title;
		}
		
		public function setScore(minPoint:int, maxPoint:int)
		{
			//score_tf.text = minPoint.toString() + "/" + maxPoint.toString();
			score_tf.text = minPoint.toString();
		}
		
		public function setProgressPercent(percent:Number)
		{		
			progress_mask_mc.width = Math.round(_progress_mask_width * percent);
			if(progress_bar_indicator_mc){
				if(percent <= 0){
					progress_bar_indicator_mc.visible = false;
				}else{
					progress_bar_indicator_mc.x = progress_mask_mc.width;
					progress_bar_indicator_mc.visible = true;
				}
			}
		}
		
		override protected function handleMouseRollOver(event:MouseEvent):void {
			super.handleMouseRollOver(event);
			name_tf && (name_tf.textColor = 0xecdcb1);
		}
		
		override protected function handleMouseRollOut(event:MouseEvent):void {
			super.handleMouseRollOut(event);
			name_tf && (name_tf.textColor = 0xcfc19b);
			if(progress_bar_indicator_mc && progress_bar_indicator_mc.totalFrames > 1){
				progress_bar_indicator_mc.gotoAndStop('up');
			}
		}
		
		override protected function handleMousePress(event:MouseEvent):void {
			super.handleMousePress(event);
			name_tf && (name_tf.textColor = 0xb0a485);
			score_tf && (score_tf.textColor = 0xc6c6c6);
			if(progress_bar_indicator_mc && progress_bar_indicator_mc.totalFrames > 1){
				progress_bar_indicator_mc.gotoAndStop('down');
			}
		}
	}
}
