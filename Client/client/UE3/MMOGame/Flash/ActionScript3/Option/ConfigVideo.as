package ActionScript3.Option
{
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.Dictionary;
	
	import ActionScript3.Common.Utils.ConfigConstants;
	import ActionScript3.Option.AdvancedVideo.AdvancedPanel;
	import ActionScript3.Option.AdvancedVideo.OptionItemData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.DropdownMenu;
	import scaleform.clik.controls.Slider;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.InputEvent;
	import scaleform.clik.events.SliderEvent;
	
	public class ConfigVideo extends UIComponent
	{
		public var default_mc:Button;
		public var confirm_mc:Button;
		public var cancel_mc:Button;
		public var apply_mc:Button;
		public var advanced_mc:Button;
		
		public var check_auto_adjust_perf:Button;
		public var check_notice_auto_adjust:Button;
		public var slider_interval_check:SliderSound;
		public var slider_FPS_check:SliderSound;
		//public var slider_backend_FPS_limit:SliderSound;
		//public var slider_CPU_usage_limit:SliderSound;
		
		public var txt_level_recommand:TextField;
		public var txt_value_check_interval:TextField;
		public var txt_value_check_FPS:TextField;
		//public var txt_value_FPS_limit:TextField;
		//public var txt_value_CPU_limit:TextField;
		//TODO:delete--------------------------------------------------------------
		public var check_msaa:Button;
		public var check_sync:Button;
		public var check_matinee:Button;
		public var check_cover:Button;
		public var check_role_phys:Button;
		public var check_dof:Button;
		public var check_hdr:Button;
		public var check_blur:Button;
		public var check_frange:Button;
		
		public var draw_effect_level:SliderSound;
		public var texture_level:SliderSound;
		public var shadow_level:SliderSound;
		public var water_level:SliderSound;
		public var particle_level:SliderSound;
		public var players_level:SliderSound;
		public var material_level:SliderSound;
		//--------------------------------------------------------------	
		public var gpu_drop_list:DropdownMenu;
		public var window_mode:DropdownMenu;
		public var window_size:DropdownMenu;
		
		public var advanced_panel:AdvancedPanel;
		
		public var lock_change:Boolean;
		
		private var _advOptiondata:Array;
		
		override protected function configUI():void
		{
			super.configUI();
			
			lock_change = false;
			default_mc.addEventListener("click",OnDefault);
			confirm_mc.addEventListener("click",OnOK);
			cancel_mc.addEventListener("click",OnCancel);
			apply_mc.addEventListener("click",OnApply);

			draw_effect_level.addEventListener( SliderEvent.VALUE_CHANGE, draw_effect_change, false, 0, true );
			//--------------------------------------------------------------TODO:delete
			texture_level.addEventListener( SliderEvent.VALUE_CHANGE, draw_effect_level_to_zero, false, 0, true );
			shadow_level.addEventListener( SliderEvent.VALUE_CHANGE, draw_effect_level_to_zero, false, 0, true );
			water_level.addEventListener( SliderEvent.VALUE_CHANGE, draw_effect_level_to_zero, false, 0, true );
			particle_level.addEventListener( SliderEvent.VALUE_CHANGE, draw_effect_level_to_zero, false, 0, true );
			players_level.addEventListener( SliderEvent.VALUE_CHANGE, draw_effect_level_to_zero, false, 0, true );
			material_level.addEventListener( SliderEvent.VALUE_CHANGE, draw_effect_level_to_zero, false, 0, true );
			check_msaa.addEventListener("click", draw_effect_level_to_zero_ck);
			check_sync.addEventListener("click", draw_effect_level_to_zero_ck);
			check_matinee.addEventListener("click", draw_effect_level_to_zero_ck);
			check_cover.addEventListener("click", draw_effect_level_to_zero_ck);
			check_role_phys.addEventListener("click", draw_effect_level_to_zero_ck);
			check_dof.addEventListener("click", draw_effect_level_to_zero_ck);
			//check_hdr.addEventListener("click", draw_effect_level_to_zero_ck);
			check_blur.addEventListener("click", draw_effect_level_to_zero_ck);
			check_frange.addEventListener("click", draw_effect_level_to_zero_ck);
			//particle_level.enabled = false;
			//material_level.enabled = false;
			//--------------------------------------------------------------
			check_auto_adjust_perf.addEventListener("click", OnCheckAutoAdjust, false, 0, true);
			/// check_notice_auto_adjust.addEventListener("click", draw_effect_level_to_zero_ck, false, 0, true);
			
			///slider_interval_check.addEventListener( SliderEvent.VALUE_CHANGE, draw_effect_level_to_zero_ck, false, 0, true );
			///slider_FPS_check.addEventListener( SliderEvent.VALUE_CHANGE, draw_effect_level_to_zero_ck, false, 0, true );
			
			//slider_backend_FPS_limit.addEventListener( SliderEvent.VALUE_CHANGE, draw_effect_level_to_zero_ck, false, 0, true );
			//slider_CPU_usage_limit.addEventListener( SliderEvent.VALUE_CHANGE, draw_effect_level_to_zero_ck, false, 0, true );
			
			advanced_panel.list_option.addEventListener(Event.CHANGE, onAdvancedPanelChange);
			advanced_panel.visible = false;
			
			txt_level_recommand.visible = false;
			
			DefaultValue();
		}
		
		private function OnCheckAutoAdjust():void
		{
		///	draw_effect_level_to_zero_ck();
			var ifEnable:Boolean = check_auto_adjust_perf.selected;
			check_notice_auto_adjust.enabled = ifEnable;
			slider_interval_check.enabled = ifEnable;
			slider_FPS_check.enabled = ifEnable;
		}
		
		public function EnableAllUIControl(enable:Boolean)
		{
			check_msaa.enabled = enable;
			check_sync.enabled = enable;
			check_matinee.enabled = enable;
			check_cover.enabled = enable;
			check_role_phys.enabled = enable;
			check_dof.enabled = enable;
			check_hdr.enabled = false;
			check_blur.enabled = enable;
			check_frange.enabled = enable;
			
			draw_effect_level.enabled = enable;
			texture_level.enabled = enable;
			shadow_level.enabled = enable;
			//water_level.enabled = enable;
			particle_level.enabled = enable;
			//players_level.enabled = enable;
			//material_level.enabled = enable;
		}	
		
		
		public function draw_effect_level_to_zero(event:SliderEvent)
		{
			draw_effect_level_to_zero_ck();
		}
		
		private function onAdvancedPanelChange(evt:Event):void
		{
			draw_effect_level_to_zero_ck();
		}
		
		public function draw_effect_level_to_zero_ck()
		{
			if (lock_change)
				return;
			lock_change = true;
			if (draw_effect_level.value != 0)
				draw_effect_level.value = 0;
			lock_change = false;
			
			//EnableAllUIControl(!check_auto_adjust_perf.selected);
		}
		public function draw_effect_change()
		{
			if (!lock_change){
				ExternalInterface.call("ASConfigVideoReq", draw_effect_level.value);
			}
			reset(draw_effect_level.value);	
		}
		
		public function DefaultValue()
		{
			lock_change = true;
			
			check_auto_adjust_perf.selected = true;
			check_msaa.selected = true;
			check_sync.selected = true;
			check_matinee.selected = true;
			check_cover.selected = true;
			check_role_phys.selected = true;
			check_dof.selected = true;
			check_hdr.selected = false;
			check_hdr.enabled = false;
			check_blur.selected = true;
			check_frange.selected = true;
			
			draw_effect_level.value = 4;
			
			check_matinee.enabled = false;
			check_cover.enabled = false;
			check_role_phys.enabled = false;
			//check_frange.enabled = false;
			
			DefaultLevel();
			
			//auto adjust
			check_auto_adjust_perf.enabled = true;
			check_notice_auto_adjust.enabled = true;
			slider_interval_check.enabled = true;
			slider_FPS_check.enabled = true;
			check_auto_adjust_perf.selected = true;
			check_notice_auto_adjust.selected = true;
			slider_interval_check.defaultValue();
			slider_FPS_check.defaultValue();
			//slider_backend_FPS_limit.defaultValue();
			//slider_CPU_usage_limit.defaultValue();
			
			//advanced
			advanced_panel.defaultValue();
			
			lock_change = false;
			
			//EnableAllUIControl(!check_auto_adjust_perf.selected);
		}
		public function DefaultLevel()
		{
			water_level.enabled = true;
			players_level.enabled = true;
			texture_level.value = draw_effect_level.value;
			shadow_level.value = draw_effect_level.value;
			water_level.value = draw_effect_level.value;
			particle_level.value = draw_effect_level.value;
			players_level.value = draw_effect_level.value;
			material_level.value = draw_effect_level.value;
			water_level.enabled = false;
			//players_level.enabled = false;
		}
		
		private function reset(id:int):void
		{
			trace("reset++++++");
			var i:int=0;
			for (i; i < 6; i++) 
			{
				var txt:TextField=this["txt_dec"+i] as TextField;
				if(id==i){
					txt.textColor=0xfbd671;
				}else{
					txt.textColor=0xFFFFFF;
				}
			}
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
			
			dat.video_enable = true;
			
			dat.GPU_List_Selected_Idx = gpu_drop_list.selectedIndex;
			dat.WndFullscreen = window_mode.selectedIndex;
			dat.WndSizeIdx = window_size.selectedIndex;
			dat.WndSizeFixed = !(window_size.enabled);
			
			//auto adjust
			dat.auto_adjust_perf = check_auto_adjust_perf.selected;
			dat.notice_auto_adjust = check_notice_auto_adjust.selected;
			dat.adjust_interval_check = slider_interval_check.value;
			dat.adjust_FPS_check = slider_FPS_check.value;
			//dat.backend_FPS_limit = slider_backend_FPS_limit.value;
			//dat.CPU_usage_limit = slider_CPU_usage_limit.value;
			
			dat.MSAA = check_msaa.selected;
			dat.VerticalSync = check_sync.selected;
			dat.EnableMatinee = check_matinee.selected;
			dat.CoverTransparent = check_cover.selected;
			dat.RolePhys = check_role_phys.selected;
			dat.EnvDOF = check_dof.selected;
			dat.HDR = false;//check_hdr.selected;
			dat.MotionBlur = check_blur.selected;
			dat.Stroke = check_frange.selected;
			
			dat.DrawEffectLevel = draw_effect_level.value;
			dat.TextureLevel = texture_level.value;
			dat.ShadowLevel = shadow_level.value;
			dat.WaterLeval = water_level.value;
			dat.PlayersLevel = players_level.value;
			dat.ParticleLevel = particle_level.value;
			
			dat.MaterialLevel = material_level.value;
			
			dat.advancedOptionData = advanced_panel.listData as Array;
			
			ExternalInterface.call("ASApplyConfig", dat);
		}
		
		public function closeDropList():void
		{
			if(gpu_drop_list && gpu_drop_list.selected==true)
			{
				gpu_drop_list.close();
			}
		}
		
		public function FillToUI(dat:OptionData)
		{
			if (!dat.video_enable)
				return;

			lock_change = true;
			
			//set gpu_drop_list data
			if(dat.GPU_List){
				gpu_drop_list.dataList = dat.GPU_List;
				gpu_drop_list.SplitData();
				gpu_drop_list.menuRowCount = dat.GPU_List.length;
				gpu_drop_list.selectedIndex = dat.GPU_List_Selected_Idx;
			}
				
			window_mode.datastring = "窗口=全屏";
			window_mode.SplitData();
			window_mode.selectedIndex = dat.WndFullscreen;
			
			var size_str:String = "";
			for(var i:int = 0; i < dat.WndSize.length; ++i)
			{
				size_str += dat.WndSize[i];
				if (i < dat.WndSize.length - 1)
					size_str += "=";
			}
			window_size.datastring = size_str;
			window_size.SplitData();
			window_size.selectedIndex = dat.WndSizeIdx;
			
			window_size.enabled = !dat.WndSizeFixed;
			
			VideoLevelReq(dat);
			//advanced list data
			_advOptiondata = dat.advancedOptionData;
			if(_advOptiondata){
				advanced_panel.UCSetOptionListData(_advOptiondata);
			}
			
			lock_change = false;
			
			//EnableAllUIControl(!dat.auto_adjust_perf);
		}
		public function VideoAdvanceLevel(dataList:Array)
		{
			_advOptiondata = dataList;
			if(_advOptiondata){
				advanced_panel.UCSetOptionListData(_advOptiondata);
			}
		}
		public function VideoLevelReq(dat:OptionData)
		{
			lock_change = true;
			
			//auto adjust
			check_auto_adjust_perf.selected = dat.auto_adjust_perf;
			check_notice_auto_adjust.selected = dat.notice_auto_adjust;
			
			if(dat.adjust_interval_check_Max > 0.0001)
			{
				slider_interval_check.minimum = dat.adjust_interval_check_Min;
				slider_interval_check.maximum = dat.adjust_interval_check_Max;
				if(dat.adjust_interval_check_Step > 0.0001)
					slider_interval_check.snapInterval = dat.adjust_interval_check_Step;
			}
			if(dat.adjust_FPS_check_Max > 0.0001)
			{
				slider_FPS_check.minimum = dat.adjust_FPS_check_Min;
				slider_FPS_check.maximum = dat.adjust_FPS_check_Max;
				if(dat.adjust_FPS_check_Step > 0.0001)
					slider_FPS_check.snapInterval = dat.adjust_FPS_check_Step;
			}
//			if(dat.backend_FPS_limit_Max > 0.0001)
//			{
//				slider_backend_FPS_limit.minimum = dat.backend_FPS_limit_Min;
//				slider_backend_FPS_limit.maximum = dat.backend_FPS_limit_Max;
//				if(dat.backend_FPS_limit_Step > 0.0001)
//					slider_backend_FPS_limit.snapInterval = dat.backend_FPS_limit_Step;
//			}
//			if(dat.CPU_usage_limit_Max > 0.0001)
//			{
//				slider_CPU_usage_limit.minimum = dat.CPU_usage_limit_Min;
//				slider_CPU_usage_limit.maximum = dat.CPU_usage_limit_Max;
//				if(dat.CPU_usage_limit_Step > 0.0001)
//					slider_CPU_usage_limit.snapInterval = dat.CPU_usage_limit_Step;
//			}
			slider_interval_check.value = dat.adjust_interval_check;
			slider_FPS_check.value = dat.adjust_FPS_check;
			//slider_backend_FPS_limit.value = dat.backend_FPS_limit;
			//slider_CPU_usage_limit.value = dat.CPU_usage_limit;
			//check_msaa.selected = dat.MSAA;
			//check_sync.selected = dat.VerticalSync;
			//check_matinee.selected = dat.EnableMatinee;
			//check_cover.selected = dat.CoverTransparent;
			//check_role_phys.selected = dat.RolePhys;
			//check_dof.selected = dat.EnvDOF;
			//check_hdr.selected = dat.HDR;
			//check_blur.selected = dat.MotionBlur;
			//check_frange.selected = dat.Stroke;
			
			texture_level.value = dat.TextureLevel;
			shadow_level.value = dat.ShadowLevel;
			water_level.enabled=true;
            water_level.value = dat.WaterLeval;
			water_level.enabled=false;
			players_level.enabled=true;
			players_level.value = dat.PlayersLevel;
			//players_level.enabled=false;
			
			particle_level.value = dat.ParticleLevel;

			material_level.value = dat.MaterialLevel;
			
			draw_effect_level.value = dat.DrawEffectLevel;
			
			if(dat.RecommandLevel > 0 && dat.RecommandLevel <= 5){
				//edit by wph@2014-12-24 for OB_1130
				//txt_level_recommand.visible = true;
				txt_level_recommand.x = (this["txt_dec" + dat.RecommandLevel] as TextField).x;
			}
			
			lock_change = false;
			
			//EnableAllUIControl(!dat.auto_adjust_perf);
		}
		
		public function setDropdownMenuDisplayPriority(priority:int):void
		{
			gpu_drop_list.displayPriority = window_mode.displayPriority = window_size.displayPriority = priority;
		}
	}
}
