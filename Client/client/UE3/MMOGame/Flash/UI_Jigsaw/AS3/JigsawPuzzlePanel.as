package UI_Jigsaw.AS3
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObject;
	import flash.display.DisplayObjectContainer;
	import flash.display.MovieClip;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.utils.Timer;
	import flash.utils.getQualifiedClassName;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.Common.Utils.ConfigConstants;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ComponentEvent;
	
	public class JigsawPuzzlePanel extends MyPanel
	{
		public var Jigsaw_Part_mc_1:MovieClip;
		public var Jigsaw_Part_mc_2:MovieClip;
		public var Jigsaw_Part_mc_3:MovieClip;
		public var Jigsaw_Part_mc_4:MovieClip;
		public var dragPart_mc:MovieClip;
		
		public var radioBtn_part_1:RadioButton;
		public var radioBtn_part_2:RadioButton;
		public var radioBtn_part_3:RadioButton;
		public var radioBtn_part_4:RadioButton;
		
		public var txt_Hint:TextField;
		public var txt_time_left:TextField;
		public var button_confirm:Button;
		
		private static const NUMBER_OF_JIGSAW_PART:int = 4;
		private static const PANEL_SHOW_MAX_TIME:int = 20;
		private static const JIGSAW_SOURCE_TOP_LEFT_POSITON:Point = new Point(72,79);
		
		private static const ENABLE_DRAG:Boolean = false;
		
		private var _partIndex:int = 0;
		private var _selectedIndex:int = -1;
		
		private var _leftSecond:int = 0;
		private var _countDownTimer:Timer;
		
		
		public function JigsawPuzzlePanel()
		{
			super();
		}
		
		override protected function configUI():void
		{
		//	ShowMode = ConfigConstants.PANEL_SHOW_MODE_BC;
			super.configUI();
			SetWindowTitle("拼图");
			
			dragPart_mc.visible = dragPart_mc.mouseChildren = dragPart_mc.mouseEnabled = false;
			
			Jigsaw_Part_mc_1.x = Jigsaw_Part_mc_1.y = 0;
			Jigsaw_Part_mc_2.x = Jigsaw_Part_mc_2.y = 0;
			Jigsaw_Part_mc_3.x = Jigsaw_Part_mc_3.y = 0;
			Jigsaw_Part_mc_4.x = Jigsaw_Part_mc_4.y = 0;
			(radioBtn_part_1['image_holder_mc'] as MovieClip).addChild(Jigsaw_Part_mc_1);
			(radioBtn_part_2['image_holder_mc'] as MovieClip).addChild(Jigsaw_Part_mc_2);
			(radioBtn_part_3['image_holder_mc'] as MovieClip).addChild(Jigsaw_Part_mc_3);
			(radioBtn_part_4['image_holder_mc'] as MovieClip).addChild(Jigsaw_Part_mc_4);
			
			if(ENABLE_DRAG)
			{
				radioBtn_part_1.addEventListener(MouseEvent.MOUSE_DOWN, onStartDragPart1);
				radioBtn_part_2.addEventListener(MouseEvent.MOUSE_DOWN, onStartDragPart2);
				radioBtn_part_3.addEventListener(MouseEvent.MOUSE_DOWN, onStartDragPart3);
				radioBtn_part_4.addEventListener(MouseEvent.MOUSE_DOWN, onStartDragPart4);
				txt_Hint.text = "可以拖拽选项进行对比";
			}
			
			radioBtn_part_1.addEventListener(ButtonEvent.CLICK, onSelectAnswerPart1);
			radioBtn_part_2.addEventListener(ButtonEvent.CLICK, onSelectAnswerPart2);
			radioBtn_part_3.addEventListener(ButtonEvent.CLICK, onSelectAnswerPart3);
			radioBtn_part_4.addEventListener(ButtonEvent.CLICK, onSelectAnswerPart4);
			
			button_confirm.addEventListener(ButtonEvent.CLICK, onConfirmSelectedPart);
			
			_countDownTimer = new Timer(1000);
			_countDownTimer.addEventListener(TimerEvent.TIMER, onCountDown);
			
			//UCSetJigsawCountingDown(PANEL_SHOW_MAX_TIME);
			//UCShow(true, 0);
			this.addEventListener(ComponentEvent.HIDE, onComponentEventHide);
		}
		
//		private function analysisParent(info = ""):void
//		{
//			var _parent:DisplayObjectContainer = parent;
//			var depth:int = 1;
//			while(_parent)
//			{
//				trace("structure: ", info, depth, _parent, flash.utils.getQualifiedClassName(_parent).toString());
//				_parent = _parent.parent;
//				depth++;
//			}
//		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			this.cavasWidth = root.stage.stageWidth;
			this.cavasHeight = root.stage.stageHeight;
			this.x = this.cavasWidth + _offsetH - MyWindowsFrame_mc.width;
			this.y = Math.max(0, this.cavasHeight + _offsetV - MyWindowsFrame_mc.height);
		}
		
		private function onStartDragPart1(evt:MouseEvent):void
		{
			_partIndex = 1;
			onStartDragPart();
		}
		
		private function onStartDragPart2(evt:MouseEvent):void
		{
			_partIndex = 2;
			onStartDragPart();
		}
		
		private function onStartDragPart3(evt:MouseEvent):void
		{
			_partIndex = 3;
			onStartDragPart();
		}
		
		private function onStartDragPart4(evt:MouseEvent):void
		{
			_partIndex = 4;
			onStartDragPart();
		}
		
		private function onStartDragPart():void
		{
			var radioBtn_part:RadioButton = this["radioBtn_part_" + _partIndex] as RadioButton; 
			if(radioBtn_part)
			{
				dragPart_mc.gotoAndStop(_partIndex);
				dragPart_mc.visible = true;
				dragPart_mc.x = radioBtn_part.x + (radioBtn_part['image_holder_mc'] as MovieClip).x;
				dragPart_mc.y = radioBtn_part.y + (radioBtn_part['image_holder_mc'] as MovieClip).y;
				dragPart_mc.startDrag();
				(radioBtn_part['image_holder_mc'] as MovieClip).alpha = 0.5;
				root.stage.addEventListener(MouseEvent.MOUSE_UP, onStopDarg);
			}
		}
		
		private function onStopDarg(evt:MouseEvent):void
		{
			root.stage.removeEventListener(MouseEvent.MOUSE_UP, onStopDarg);
			dragPart_mc.stopDrag();
			(this["radioBtn_part_" + _partIndex]['image_holder_mc'] as MovieClip).alpha = 1;
			dragPart_mc.x = dragPart_mc.y = 0;
			dragPart_mc.visible = false;
		}
		
		private function onSelectAnswerPart1(evt:ButtonEvent):void
		{
			_partIndex = 1;
			onSelectAnswerPart();
		}
		
		private function onSelectAnswerPart2(evt:ButtonEvent):void
		{
			_partIndex = 2;
			onSelectAnswerPart();
		}
		
		private function onSelectAnswerPart3(evt:ButtonEvent):void
		{
			_partIndex = 3;
			onSelectAnswerPart();
		}
		
		private function onSelectAnswerPart4(evt:ButtonEvent):void
		{
			_partIndex = 4;
			onSelectAnswerPart();
		}
		
		private function onSelectAnswerPart():void
		{
			dragPart_mc.gotoAndStop(_partIndex);
			dragPart_mc.visible = true;
		}
		
		public function UCSetJigsawCountingDown(leftSecond:int):void
		{
			_leftSecond = leftSecond;
			txt_time_left.text = _leftSecond.toString() + "秒";
			_countDownTimer.reset();
			_countDownTimer.start();
		}
		
		public function UCSetJigsawBlockOffSet(OffsetX:int, OffsetY:int):void
		{
			dragPart_mc.x = JIGSAW_SOURCE_TOP_LEFT_POSITON.x + OffsetX;
			dragPart_mc.y = JIGSAW_SOURCE_TOP_LEFT_POSITON.y + OffsetY;
		}
		
		private function onComponentEventHide(evt:Event):void
		{
			dragPart_mc.x = dragPart_mc.y = 0;
			dragPart_mc.visible = false;
		}
		
		private function onCountDown(evt:TimerEvent):void
		{
			--_leftSecond;
			txt_time_left.text = _leftSecond.toString() + "秒";
			if(_leftSecond<= 0)
			{
				_countDownTimer.stop();
				ExternalInterface.call( "ASOnPanelClose" , PanelName );
			}
		}
		
		private function onConfirmSelectedPart(evt:ButtonEvent):void
		{
			if (radioBtn_part_1.selected) _selectedIndex = 0;
			else if (radioBtn_part_2.selected) _selectedIndex = 1;
			else if (radioBtn_part_3.selected) _selectedIndex = 2;
			else if (radioBtn_part_4.selected) _selectedIndex = 3;
			
			ExternalInterface.call("ASOnConfirmSelectedPart", _selectedIndex);
		}
	}
}