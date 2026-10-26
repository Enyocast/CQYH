package ActionScript3.Achievement  
{
	import flash.display.ActionScriptVersion;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.geom.Rectangle;
	import flash.text.StaticText;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	
	import flashx.textLayout.formats.Float;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.TextInput;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ComponentEvent;
	import scaleform.clik.managers.PopUpManager;
	
	public class AchievementHintPanel extends MyPanel
	{	
		private static const HIT_AREA_RECT:Rectangle = new Rectangle(-178, 38, 360, 92);
		//public var achievement_icon_mc:AchievementIcon;
		//public var achievement_name_mc:TextField;
		//public var achievement_point_mc:TextField;
		public var achievement_id:int;
//		private static const FRAME_NUMBER_OF_TOUCH_ENABLE:int = 20;
		private var _achievement_hit_area_mc:AchievementHintHitArea;
		private var _isPlaying:Boolean = false;
		
		
		public function AchievementHintPanel()
		{
			// constructor code
			achievement_id = 0;
		}
		
		override protected  function configUI():void 
		{			
			super.configUI();
			//ExternalInterface.call( "ASRegisterAchievementHintPanel", this);
			//ShowMode只适用于没有位置，大小改变的动画并且基点在Panel左上角的情况,这里不适用
			achievement_id = 0;
			this.addFrameScript(this.totalFrames - 1,  OnPlayEnd);
			this.mouseChildren = this.mouseEnabled = false;
			
			_achievement_hit_area_mc = new AchievementHintHitArea();
		}
		
		public function onClickAnimation(event:ButtonEvent)
		{
			var control:MovieClip = event.target as MovieClip;
			if (control != null)
			{
				if (achievement_id > 0)
				{
					ExternalInterface.call("ASShowAchievementPanelById", achievement_id);
				}
			}
		}
		
		public function UCSetNewAchievementData(ach_id:int, icon_name:String, name:String, point:int)
		{
			achievement_id = ach_id;
			var animation:MovieClip = getChildByName("achievement_obtain_animation_mc") as MovieClip;
			//ach_icon.setIconImage(icon_name);
			var real_icon:UILoader = animation.getChildByName("IconLoader_mc") as UILoader;
			
			real_icon.visible = true;
			if (icon_name == "" || icon_name == null)
			{
				real_icon.visible = false;
			}
			else
			{
				real_icon.source = icon_name;
			}
			
			animation.achievement_name_mc.text = name;
			animation.achievement_point_mc.text = String(point);
			if(!_isPlaying)
			{
				//pop up the hit area in order to avoid overlap on other ui
				_achievement_hit_area_mc.visible = true;
				_achievement_hit_area_mc.enabled = true;
				PopUpManager.show(_achievement_hit_area_mc, this.x + HIT_AREA_RECT.x, this.y + HIT_AREA_RECT.y, null, _displayPriority);
				if(!_achievement_hit_area_mc.hasEventListener(ButtonEvent.CLICK))
				{
					_achievement_hit_area_mc.addEventListener(ButtonEvent.CLICK, onClickAnimation);
				}
			}
			gotoAndPlay(1);
			_isPlaying = true;
			visible = _isPlaying;
			//sound
			playSound("menu_Popup_unlock");
		}
		
		public function OnPlayEnd()
		{
			achievement_id = 0;
			stop();
			ExternalInterface.call("ASPlayAchievementHintEnd");
			if(_isPlaying)
			{
				_achievement_hit_area_mc.visible = false;
				_achievement_hit_area_mc.enabled = false;
				this.addChild(_achievement_hit_area_mc);
				_isPlaying = false;
			}
		}
		
		
		override public function UCShow(v:Boolean, priority:int):void
		{
			visible = _isPlaying;
			if(!v)
			{
				if(_isPlaying)
				{
					_achievement_hit_area_mc.visible = false;
					_achievement_hit_area_mc.enabled = false;
					this.addChild(_achievement_hit_area_mc);
					_isPlaying = false;
				}
			}
			super.UCShow(v, priority);
		}
		
		override public function set visible(value:Boolean):void {
			super.visible = value && _isPlaying;//避免在播放完成后显示
		}
	}
}
