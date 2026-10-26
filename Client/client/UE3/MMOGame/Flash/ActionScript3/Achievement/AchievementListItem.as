
package ActionScript3.Achievement
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.filters.BlurFilter;
	import flash.filters.ColorMatrixFilter;
	import flash.geom.ColorTransform;
	import flash.text.TextField;
	
	import ActionScript3.MyIconConponent;
	import ActionScript3.MyPanel;
	import ActionScript3.Common.Utils.StyleType;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import fl.motion.ColorMatrix;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.CheckBox;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;

	public class AchievementListItem extends UIComponent
	{
		public var achievement_item_bg_mc:MovieClip;
		public var achievement_item_bg_gray_mc:MovieClip;
		public var achievement_icon_lock_mc:MovieClip;
		public var achievement_icon_mc:MovieClip;
		public var achievement_name_tf:TextField;
		public var achievement_desc_tf:TextField;
		public var achievement_detail_mc:Button;
		public var achievement_point_mc:MovieClip;
		public var achievement_trace_checkbox:CheckBox;
		
		public var achievement_date_tf:TextField;
		public var achievement_reward_tf:TextField;
		public var achievement_reward_item_icon_mc:MyItemSlot;
		public var achievement_reward_item_get_mc:MovieClip;
		public var achievement_reward_title_tf:TextField;
		public var achievement_reward_exp_tf:TextField;

		public var achievement_progress_mc:AchievementProgressBar;
		public var achievement_condition_0_mc:MovieClip;
		public var achievement_condition_1_mc:MovieClip;
		public var achievement_condition_2_mc:MovieClip;
		public var achievement_condition_3_mc:MovieClip;
		public var achievement_condition_4_mc:MovieClip;
		public var achievement_condition_5_mc:MovieClip;
		
		public var achievement_devide_up_mc:MovieClip;
		public var achievement_devide_down_mc:MovieClip;
		
		public var achievement_score_bg_mc:MovieClip;
		public var achievement_score_bg_gray_mc:MovieClip;
		public var achievement_tf_amount:TextField;
		
		protected var _point_tf:TextField;

		public var achievement_item_data:Object;
		public var achievement_item_expand:Boolean;
		public var achievement_item_parent:Object;
		
		public static const achievement_item_bg_down_y = 43;
		//public static const achievement_item_bg_height = 101;
		
		private static const ICON_FRAME_LABLE_NORMAL:String = "normal";
		private static const ICON_FRAME_LABLE_LOCKED:String = "locked";
		
		private static const DESCRIPTION_TF_ONE_LINE_POS_Y:Number = 45;
		private static const DESCIPTION_TF_MULT_LINE_POS_Y:Number = 35.5;
		
		private var _grayFilter:ColorMatrixFilter;
		private var _achievement_is_obtain:Boolean = false;
		private var _detailDataUpdated:Boolean;

		public function AchievementListItem()
		{

		}

		override protected function configUI():void
		{
			super.configUI();
			_grayFilter = StyleType.getInstance().getGrayFilter();
		//	trace(">>>>>>>>>>>>>>> AchievementListItem::configUI");
			
			achievement_item_expand = false;

			achievement_progress_mc.visible = false;
			achievement_progress_mc.mouseEnabled = false;
			
			achievement_condition_0_mc.visible = false;
			achievement_condition_1_mc.visible = false;
			achievement_condition_2_mc.visible = false;
			achievement_condition_3_mc.visible = false;
			achievement_condition_4_mc.visible = false;
			achievement_condition_5_mc.visible = false;
			achievement_condition_0_mc.mouseEnabled = false;
			achievement_condition_1_mc.mouseEnabled = false;
			achievement_condition_2_mc.mouseEnabled = false;
			achievement_condition_3_mc.mouseEnabled = false;
			achievement_condition_4_mc.mouseEnabled = false;
			achievement_condition_5_mc.mouseEnabled = false;

			achievement_detail_mc.addEventListener(MouseEvent.CLICK, onBtClickDetail);
			achievement_reward_item_get_mc.addEventListener(MouseEvent.CLICK, onBtClickGetReward);

			achievement_reward_tf.y = achievement_desc_tf.y + achievement_desc_tf.height;
			achievement_reward_item_icon_mc.y = achievement_reward_tf.y;
			achievement_reward_item_get_mc.y = achievement_reward_tf.y;
			achievement_reward_title_tf.y = achievement_reward_tf.y;
			achievement_reward_exp_tf.y = achievement_reward_tf.y;
			achievement_reward_tf.visible = false;
			achievement_reward_title_tf.visible = false;
			achievement_reward_exp_tf.visible = false;
			achievement_reward_item_icon_mc.visible = false;
			achievement_reward_item_get_mc.visible = false;
			achievement_tf_amount.mouseEnabled = false;
			
			var middle_mc:MovieClip = achievement_item_bg_mc['middle_mc'] as MovieClip;
			middle_mc.height = 0;
			
			middle_mc = achievement_item_bg_gray_mc['middle_mc'] as MovieClip;
			middle_mc.height = 0;
			
			var down_mc:MovieClip = achievement_item_bg_mc['down_mc'] as MovieClip;
			down_mc.y = achievement_item_bg_down_y;
			
			down_mc = achievement_item_bg_gray_mc['down_mc'] as MovieClip;
			down_mc.y = achievement_item_bg_down_y;
			
		 	achievement_devide_up_mc.visible = false;
			achievement_devide_up_mc.y = 0;
			achievement_devide_down_mc.visible = false;
			achievement_devide_down_mc.y = 0;
			
			_point_tf = achievement_point_mc['point_tf'] as TextField;
			
			//updateViewAsObtain(false);
			achievement_score_bg_mc.visible = achievement_item_bg_mc.visible = false;
			achievement_icon_lock_mc.visible = achievement_score_bg_gray_mc.visible = achievement_item_bg_gray_mc.visible = true;
			
			achievement_point_mc.addEventListener("rollOver", function _showTips(e:Event){ showTips(e);});
			achievement_point_mc.addEventListener("rollOut", onItemRollOut);
			
			achievement_trace_checkbox.addEventListener(ButtonEvent.CLICK, onCheckBoxClick);
			achievement_trace_checkbox.addEventListener(MouseEvent.ROLL_OVER, onShowTraceTips);
			achievement_trace_checkbox.addEventListener("rollOut", onItemRollOut);
			
			achievement_item_parent = null;
			trace("<<<<<<<<<<<<<<< AchievementListItem::configUI");
		}
		
		function showTips(e:Event)
		{
			ExternalInterface.call("ASShowTips_PlainText_WithString", this, "成就点数");
		}
		
		public function onItemRollOut(e:Event)
		{
			ExternalInterface.call("ASRollOutItemSlot", this);
		}
		
		private function onCheckBoxClick(evt:ButtonEvent):void
		{
			ExternalInterface.call("ASTriggerAchievementTrace", achievement_item_data.achievement_id, achievement_trace_checkbox.selected);
		}
		
		private function onShowTraceTips(evt:MouseEvent):void
		{
			ExternalInterface.call("ASShowTips_PlainText_WithString", this, "成就追踪");
		}
		
		public function onBtClickDetail():void
		{
			switchItemExpandState();
			updateListLayout(false);
		}
		
		public function updateListLayout(resetPosition:Boolean):void
		{
			// 刷新列表布局
			var list_panel:AchievementList = achievement_item_parent as AchievementList;
			list_panel.updateListLayout(achievement_item_data.achievement_id, resetPosition);
		}
		
		public function switchItemExpandState():void
		{
			achievement_detail_mc.selected = !achievement_detail_mc.selected;
			achievement_item_expand = !achievement_item_expand;
			
			achievement_devide_up_mc.visible = achievement_item_expand;
			achievement_devide_down_mc.visible = achievement_item_expand;
			
			if (achievement_item_expand)
			{
				updateDetailAndRewardData(achievement_item_data);
				var devide_space:int = 2;
				achievement_devide_up_mc.y = achievement_date_tf.y + achievement_date_tf.height + devide_space;
				if (achievement_item_data.achievement_detail == 1)
				{
					var count:int = 0;
					var offset:int = achievement_devide_up_mc.y + achievement_devide_up_mc.height + devide_space;
					var control_height:int = 0;
					for (var i:int = 0; i < 6; i ++)
					{
						var control:MovieClip = this["achievement_condition_" + i + "_mc"] as MovieClip;
						control.visible = true;
						control_height = control.height;
						
						if (control.label != String(""))
						{
							control.y = offset;
							if (i % 2 == 1)
							{
								offset = control.y + control_height;
							}
							count ++;
						}
						else
						{
							control.visible = false;
						}
					}
					
					if (count % 2 == 0)
					{
						achievement_devide_down_mc.y = offset + devide_space;
					}
					else
					{
						achievement_devide_down_mc.y = offset + control_height + devide_space;
					}
				}
				else if (achievement_item_data.achievement_detail == 2)
				{
					achievement_progress_mc.visible = true;
					achievement_progress_mc.y = achievement_devide_up_mc.y + achievement_devide_up_mc.height + devide_space;
					achievement_devide_down_mc.y = achievement_progress_mc.y + achievement_progress_mc.height + devide_space;
				}
				else if (achievement_item_data.achievement_reward_type > 0)
				{
					achievement_devide_down_mc.y = achievement_devide_up_mc.y;
					//achievement_devide_down_mc.visible = false;
				}
				
				achievement_devide_down_mc.visible = achievement_item_data.achievement_reward_type > 0;
				achievement_reward_tf.visible = achievement_item_data.achievement_reward_type > 0;
				achievement_reward_title_tf.visible = achievement_item_data.achievement_reward_type == 1;
				achievement_reward_item_icon_mc.visible = achievement_item_data.achievement_reward_type == 2;
				achievement_reward_exp_tf.visible = achievement_item_data.achievement_reward_type == 3;
				achievement_reward_item_get_mc.visible = achievement_item_data.achievement_reward_type > 0 && !achievement_item_data.achievement_is_get_reward;
				
				achievement_reward_tf.y = achievement_devide_down_mc.y + achievement_devide_down_mc.height + devide_space;
				achievement_reward_title_tf.y = achievement_devide_down_mc.y + achievement_devide_down_mc.height + devide_space;
				achievement_reward_exp_tf.y = achievement_devide_down_mc.y + achievement_devide_down_mc.height + devide_space;
				achievement_reward_item_icon_mc.y = achievement_devide_down_mc.y + achievement_devide_down_mc.height + devide_space;
				achievement_reward_item_get_mc.y = achievement_devide_down_mc.y + achievement_devide_down_mc.height + devide_space;
				
				var offset_if_have_button:Number;
				if (achievement_item_data.achievement_detail == 1){
					if(achievement_reward_tf.visible){
						offset_if_have_button = 10;
					}else{
						if(count == 0){
							offset_if_have_button = 10;
						}else{
							offset_if_have_button = -8;
						}
					}
				}else if(achievement_item_data.achievement_detail == 2){
					if(achievement_reward_tf.visible){
						offset_if_have_button = 10;
					}else{
						offset_if_have_button = -13;
					}
				}
				else if (achievement_item_data.achievement_reward_type > 0)
				{
					if(achievement_reward_tf.visible){
						offset_if_have_button = 10;
					}else{
						offset_if_have_button = -13;
					}
				}
				
				var middle_mc:MovieClip = achievement_item_bg_mc['middle_mc'] as MovieClip;
				var down_mc:MovieClip = achievement_item_bg_mc['down_mc'] as MovieClip;
				down_mc.y = achievement_item_bg_down_y;
				var down_offset:int = achievement_devide_down_mc.y - achievement_item_bg_down_y + offset_if_have_button;
				if (down_offset > 0)
				{
					middle_mc.height = down_offset + 1;
					down_mc.y += down_offset;
				}
				
				middle_mc = achievement_item_bg_gray_mc['middle_mc'] as MovieClip;
				down_mc = achievement_item_bg_gray_mc['down_mc'] as MovieClip;
				down_mc.y = achievement_item_bg_down_y;
				down_offset = achievement_devide_down_mc.y - achievement_item_bg_down_y + offset_if_have_button;
				if (down_offset > 0)
				{
					middle_mc.height = down_offset + 1;
					down_mc.y += down_offset;
				}
			}
			else
			{
				achievement_progress_mc.visible = false;
				
				achievement_condition_0_mc.visible = false;
				achievement_condition_1_mc.visible = false;
				achievement_condition_2_mc.visible = false;
				achievement_condition_3_mc.visible = false;
				achievement_condition_4_mc.visible = false;
				achievement_condition_5_mc.visible = false;
				
				achievement_reward_tf.y = achievement_desc_tf.y + achievement_desc_tf.height;
				
				middle_mc = achievement_item_bg_mc['middle_mc'] as MovieClip;
				middle_mc.height = 0;
				down_mc = achievement_item_bg_mc['down_mc'] as MovieClip;
				down_mc.y = achievement_item_bg_down_y;
				
				middle_mc = achievement_item_bg_gray_mc['middle_mc'] as MovieClip;
				middle_mc.height = 0;
				down_mc = achievement_item_bg_gray_mc['down_mc'] as MovieClip;
				down_mc.y = achievement_item_bg_down_y;
				
				achievement_reward_tf.visible = false;
				achievement_reward_title_tf.visible = false;
				achievement_reward_exp_tf.visible = false;
				achievement_reward_item_icon_mc.visible = false;
				achievement_reward_item_get_mc.visible = false;
			}
		}
		
		public function get canExpand():Boolean
		{
			if(achievement_item_data == null)
			{
				return false;
			}
			return achievement_item_data.achievement_detail == 1 
				|| achievement_item_data.achievement_detail == 2 
				|| achievement_item_data.achievement_reward_type > 0;
		}
		
		public function onBtClickGetReward()
		{
			if (achievement_item_data != null)
			{
				ExternalInterface.call("ASObtainRewardItem", achievement_item_data.achievement_id);
				onBtClickDetail();
			}
		}
		
		public function setIconGray(mc:MovieClip, gray:Boolean)
		{
			if (!mc)
			{
				return;
			}

			if (gray)
			{
				mc.filters = [ _grayFilter ];
			}
			else
			{
				mc.filters = null;
			}
		}
		
		public function updateItemData(data:Object):void
		{
			if (data != null)
			{
				achievement_item_data = data;
				_detailDataUpdated = false;
				visible = data.achievement_is_pre_obtain;
				var icon_loader:UILoader = achievement_icon_mc["IconLoader_mc"] as UILoader;
				icon_loader.source = String(data.achievement_icon);
				//setIconGray(icon_loader, !data.achievement_is_obtain);
				
				achievement_name_tf.text = data.achievement_name;
				achievement_desc_tf.text = data.achievement_desc;
				//adjust positon
				if(achievement_desc_tf.numLines == 1){
					achievement_desc_tf.y = DESCRIPTION_TF_ONE_LINE_POS_Y;
				}else{
					achievement_desc_tf.y = DESCIPTION_TF_MULT_LINE_POS_Y;
				}

				_point_tf.text = data.achievement_point;
				achievement_date_tf.text = data.achievement_date;
				if (canExpand)
				{
					achievement_detail_mc.visible = !data.achievement_is_compare;
				}
				else
				{
					achievement_detail_mc.visible = false;
				}
				//update detail and reward data if item is expand
				if(achievement_item_expand)
				{
					updateDetailAndRewardData(data);
				}
				//update element if obtain state changed
				if(data.achievement_is_obtain != _achievement_is_obtain)
				{
					updateViewAsObtain(data.achievement_is_obtain);
				}
				//traced achievement item
				achievement_trace_checkbox.selected = data.achievement_is_trace;
				if(int(data.achievement_require_amount) > 0)
				{
					achievement_tf_amount.visible = true;
					achievement_tf_amount.text = "x" + data.achievement_require_amount;
				}
				else
				{
					achievement_tf_amount.visible = false;
				}
			}
			else
			{
				visible = false;
			}
		}
		
		protected function updateDetailAndRewardData(data:Object):void
		{
			if(data == null || _detailDataUpdated)
			{
				return;
			}
			// 细节
			if (data.achievement_detail == 1)
			{
				achievement_condition_0_mc.label = data.achievement_condition_name0;
				achievement_condition_1_mc.label = data.achievement_condition_name1;
				achievement_condition_2_mc.label = data.achievement_condition_name2;
				achievement_condition_3_mc.label = data.achievement_condition_name3;
				achievement_condition_4_mc.label = data.achievement_condition_name4;
				achievement_condition_5_mc.label = data.achievement_condition_name5;
				
				achievement_condition_0_mc.selected = data.achievement_condition_complete0;
				achievement_condition_1_mc.selected = data.achievement_condition_complete1;
				achievement_condition_2_mc.selected = data.achievement_condition_complete2;
				achievement_condition_3_mc.selected = data.achievement_condition_complete3;
				achievement_condition_4_mc.selected = data.achievement_condition_complete4;
				achievement_condition_5_mc.selected = data.achievement_condition_complete5;
			}
			else if (data.achievement_detail == 2)
			{
				achievement_detail_mc.visible = !data.achievement_is_compare;
				achievement_progress_mc.setScore(data.achievement_progress_cur, data.achievement_progress_max);
				var percent:Number = data.achievement_progress_cur / data.achievement_progress_max;
				achievement_progress_mc.setProgressPercent(percent);
			}
			
			// 奖励
			achievement_reward_title_tf.text = String("");
			achievement_reward_exp_tf.text = String("");
			if (data.achievement_reward_type == 1)
			{
				achievement_reward_title_tf.text = String(data.achievement_reward_title);
			}
			else if (data.achievement_reward_type == 2)
			{
				achievement_reward_item_icon_mc.SetSlotType(19);
				achievement_reward_item_icon_mc.SetData(1, data.achievement_reward_icon, data.achievement_reward_id, "", 0, -1, -1);
			}
			if (data.achievement_reward_type == 3)
			{
				achievement_reward_exp_tf.text = String(data.achievement_reward_exp);
			}
			//achievement reward can be get in journey trace panel, update button when data changed.
			achievement_reward_item_get_mc.visible = achievement_item_data.achievement_reward_type > 0 && !achievement_item_data.achievement_is_get_reward;
			achievement_reward_item_get_mc.enabled = achievement_item_data.achievement_is_obtain && !achievement_item_data.achievement_is_get_reward;
			
			_detailDataUpdated = true;
		}
		
		//set component gray out
		protected function updateViewAsObtain(isObtain:Boolean):void
		{
			_achievement_is_obtain = isObtain;
			achievement_score_bg_mc.visible = achievement_item_bg_mc.visible = isObtain;
			achievement_icon_lock_mc.visible = achievement_score_bg_gray_mc.visible = achievement_item_bg_gray_mc.visible = !isObtain;
			var iconFrame:MovieClip = achievement_icon_mc['achievement_item_frame'] as MovieClip;
			if(iconFrame){
				iconFrame.gotoAndStop(isObtain?ICON_FRAME_LABLE_NORMAL:ICON_FRAME_LABLE_LOCKED);
			}
		//	setIconGray(achievement_detail_mc,!isObtain);
			if(isObtain){
				achievement_name_tf.textColor = 0xFECB6F;
				achievement_desc_tf.textColor = 0xFFFFFF;
				_point_tf.textColor = 0xFFD895;
				
			}else{
				achievement_name_tf.textColor = 0x878988;
				achievement_desc_tf.textColor = 0xB2B2B0;
				_point_tf.textColor = 0x9DA0A4;
			}
		}
		

		public function getItemWidth():int
		{
			return this.width;
		}

		public function getItemHeight():int
		{
			return (achievement_item_bg_mc.height + 4);
		}
	}
}