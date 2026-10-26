package ActionScript3.Option
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.Slider;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.SliderEvent;
	import flash.events.MouseEvent;
	
	public class ConfigAudio extends UIComponent
	{
		public var default_mc:Button;
		public var confirm_mc:Button;
		public var cancel_mc:Button;
		public var apply_mc:Button;
		
/*		public var snd_all:Button;
		public var snd_back:Button;
		public var snd_env:Button;
		public var snd_input:Button;
		public var snd_other:Button;*/
		public var chk_all:CheckBox;
		public var chk_1:CheckBox;
		public var chk_2:CheckBox;
		public var chk_3:CheckBox;
		public var chk_4:CheckBox;
		
		public var snd_all_lv:SliderSound;
		public var snd_back_lv:SliderSound;
		public var snd_env_lv:SliderSound;
		public var snd_input_lv:SliderSound;
		public var snd_other_lv:SliderSound;
		
		public var txt_dec1:TextField;
		public var txt_dec2:TextField;
		public var txt_dec3:TextField;
		public var txt_dec4:TextField;
		public var txt_dec5:TextField;
		
		override protected function configUI():void
		{
			super.configUI();
			
			default_mc.addEventListener(MouseEvent.CLICK,OnDefault);
			confirm_mc.addEventListener(MouseEvent.CLICK,OnOK);
			cancel_mc.addEventListener(MouseEvent.CLICK,OnCancel);
			apply_mc.addEventListener(MouseEvent.CLICK,OnApply);
			snd_all_lv.addEventListener(SliderEvent.VALUE_CHANGE,allChange);
			snd_back_lv.addEventListener(SliderEvent.VALUE_CHANGE,backChange);
			snd_env_lv.addEventListener(SliderEvent.VALUE_CHANGE,envChange);
			snd_input_lv.addEventListener(SliderEvent.VALUE_CHANGE,inputChange);
			snd_other_lv.addEventListener(SliderEvent.VALUE_CHANGE,otherChange);
			chk_all.addEventListener(Event.SELECT, OpAll);
			chk_1.addEventListener(Event.SELECT, OpBack);
			chk_2.addEventListener(Event.SELECT, OpEnv);
			chk_3.addEventListener(Event.SELECT, OpInput);
			chk_4.addEventListener(Event.SELECT, OpOther);
			
			DefaultValue();
			
			chk_2.visible = snd_env_lv.visible = txt_dec3.visible = false;//#23873 removed wph@2016-01-19
		}
		
		private function allChange(evt:SliderEvent):void
		{
			txt_dec1.text=int(snd_all_lv.value)+"%";
		}
		private function backChange(evt:SliderEvent):void
		{
			txt_dec2.text=int(snd_back_lv.value)+"%";
		}
		private function envChange(evt:SliderEvent):void
		{
			txt_dec3.text=int(snd_env_lv.value)+"%";
		}
		private function inputChange(evt:SliderEvent):void
		{
			txt_dec4.text=int(snd_input_lv.value)+"%";
		}
		private function otherChange(evt:SliderEvent):void
		{
			txt_dec5.text=int(snd_other_lv.value)+"%";
		}
		public function OpAll(){ snd_all_lv.enabled = chk_all.selected; }
		public function OpBack(){ snd_back_lv.enabled = chk_1.selected; }
		public function OpEnv(){ snd_env_lv.enabled = chk_2.selected; }
		public function OpInput(){ snd_input_lv.enabled = chk_3.selected; }
		public function OpOther(){ snd_other_lv.enabled = chk_4.selected; }
		public function DefaultValue()
		{
			chk_all.selected = true;
			chk_1.selected = true;
			chk_2.selected = true;
			chk_3.selected = true;
			chk_4.selected = true;
			
			snd_all_lv.value = 30;
			snd_back_lv.value = 30;
			snd_env_lv.value = 30;
			snd_input_lv.value = 30;
			snd_other_lv.value = 30;
		}
		public function OnDefault()
		{
			DefaultValue();
		}
		public function OnOK()
		{
			OnApply();
			OnCancel();	
		}
		public function OnCancel()
		{
			ExternalInterface.call("ASConfigClose", this);
		}
		public function OnApply()
		{
			var dat:OptionData = new OptionData;
			
			dat.sound_enable = true;
			
			dat.SoundAll = chk_all.selected;
			dat.SoundBack = chk_1.selected;
			dat.SoundEnv = chk_2.selected;
			dat.SoundVoice = chk_3.selected;
			dat.SoundSfx = chk_4.selected;
			
			dat.SoundAllVL = snd_all_lv.value;
			dat.SoundBackVL = snd_back_lv.value;
			dat.SoundEnvVL = snd_env_lv.value;
			dat.SoundVoiceVL = snd_input_lv.value;
			dat.SoundSfxVL = snd_other_lv.value;
			
			ExternalInterface.call("ASApplyConfig", dat);
		}
		public function FillToUI(dat:OptionData)
		{
			if (!dat.sound_enable)
				return;
				
			chk_all.selected = dat.SoundAll;
			chk_1.selected = dat.SoundBack;
			chk_2.selected = dat.SoundEnv;
			chk_3.selected = dat.SoundVoice;
			chk_4.selected = dat.SoundSfx;
			
			snd_all_lv.value = dat.SoundAllVL;
			snd_back_lv.value = dat.SoundBackVL;
			snd_env_lv.value = dat.SoundEnvVL;
			if(snd_input_lv.enabled==false)
			{
				snd_input_lv.enabled=true;
				snd_input_lv.value = dat.SoundVoiceVL;
				snd_input_lv.enabled=false;
			}
			else
			{
				snd_input_lv.value = dat.SoundVoiceVL;
			}
			if(snd_other_lv.enabled==false)
			{
				snd_other_lv.enabled==true
				snd_other_lv.value = dat.SoundSfxVL;
				snd_other_lv.enabled=false
			}
			else
			{
				snd_other_lv.value = dat.SoundSfxVL;
			}
			
		}
	}
}
