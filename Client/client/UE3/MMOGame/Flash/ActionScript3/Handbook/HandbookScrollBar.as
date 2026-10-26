package ActionScript3.Handbook
{
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	
	public class HandbookScrollBar extends ScrollBar
	{
		public var btn_arrow:Button;
		
		public function HandbookScrollBar()
		{
			super();
		}
		
		override protected function configUI():void 
		{						
			super.configUI();
			btn_arrow.mouseChildren=false;
			btn_arrow.mouseEnabled=false;
		}
		
		override protected function drawLayout():void {
			// NFM: Reset the y position of the thumb so that the _height is valid when the constraints are updated.
			thumb.y = track.y - offsetTop;
			btn_arrow.y=thumb.y+((thumb.height-btn_arrow.height)>>1);
			if (isHorizontal) {
				constraints.update(_width, _height);
			} else {
				constraints.update(_width, _height);
			}
			if (isHorizontal && actualWidth != width) {
				var yScaleFix:Number = width / actualWidth;
				scaleY = yScaleFix;
			}
		}
		
		override protected function updateThumbPosition():void {
			var percent:Number = (_position - _minPosition) / (_maxPosition - _minPosition);
			var top:Number = track.y - offsetTop;
			var yPos:Number = Math.round(percent * availableHeight + top);
			
			thumb.y = Math.max(top, Math.min(track.y + track.height - thumb.height + offsetBottom, yPos));
			thumb.visible = !(isNaN(percent) || isNaN(_pageSize) || _maxPosition <= 0 || _maxPosition == Infinity);
			btn_arrow.y=thumb.y+((thumb.height-8)>>1);
			btn_arrow.visible=thumb.visible;
			
			var showThumb:Boolean = thumb.visible && enabled;
			if (upArrow) {
				upArrow.enabled = showThumb && (_position > _minPosition);
				upArrow.validateNow();
			}
			if (downArrow) {
				downArrow.enabled = showThumb && (_position < _maxPosition);
				downArrow.validateNow();
			}
			track.enabled = track.mouseEnabled = showThumb;
		}
	}
}