package ActionScript3.SkillBar
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.Timer;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyScrollBar;
	import ActionScript3.MyTipButtonNew;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ScrollingView;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.motion.Tween;
	import scaleform.gfx.Extensions;

	public class NewSystemPanel extends UIComponent
	{
		public var loader_mc:UILoader;
		public var name_tf:TextField;
		//public var ok_mc:Button;
		public var new_system_bg_mc:MovieClip;
		public var title_mc:MovieClip;
		
		public var effect_timer:Timer = new Timer(33,0);
		public var effect_speed:Number = 0.020;
		public var effect_step:int = 0;

		public function NewSystemPanel()
		{
			// constructor code
		}

		override protected function configUI():void
		{
			super.configUI();	
			effect_timer.addEventListener(TimerEvent.TIMER, onEffectTimer);
		}
		
		public function startEffect():void
		{
			new_system_bg_mc.alpha = 0.3;
			title_mc.alpha = 0.3;
			name_tf.visible = true;
			MenuBar(parent).ok_mc.visible=false;
			effect_step = 0;
			effect_timer.start();
			//sound
			playSound("menu_Popup_unlock");
		}
		
		public function onEffectTimer(e:TimerEvent):void
		{
			if (effect_step == 0)
			{
				new_system_bg_mc.alpha += effect_speed;
				title_mc.alpha += effect_speed;
				
				if (new_system_bg_mc.alpha >= 1.0)
				{
					new_system_bg_mc.alpha = 1.0;
					title_mc.alpha = 1.0;
					//effect_step = 1;
					effect_step = 2;
					var lightFX_all_mc:MovieClip = new_system_bg_mc.getChildByName('lightFX_all_mc') as MovieClip;
					if(lightFX_all_mc){
						lightFX_all_mc.gotoAndPlay(2);
					}
				}
			}
			else if (effect_step == 1)
			{
				new_system_bg_mc.alpha -= effect_speed;
				title_mc.alpha -= effect_speed;
				
				if (new_system_bg_mc.alpha <= 0.0)
				{
					new_system_bg_mc.alpha = 0.0;
					title_mc.alpha = 0.0;
					effect_step = 2;
				}
			}
			else if (effect_step == 2)
			{
				if (effect_timer != null)
				{
					effect_timer.stop();
					MenuBar(parent).ok_mc.visible=true;
				}
			}
		}
	}
}