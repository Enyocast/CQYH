//
// 新手引导
//
package ActionScript3.Guide
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.getDefinitionByName;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.utils.Padding;

	public class GuidePanel extends MyPanel
	{
		public static const c_guide_type_illustrate = 1;
		public static const c_guide_type_tip_lt = 2;
		public static const c_guide_type_tip_rt = 3;
		public static const c_guide_type_tip_lb = 4;
		public static const c_guide_type_tip_rb = 5;
		public static const c_guide_type_arrow_t = 6;
		public static const c_guide_type_arrow_b = 7;
		public static const c_guide_type_arrow_l = 8;
		public static const c_guide_type_arrow_r = 9;
		public static const c_guide_type_dialog = 10;
	
		public static const c_tip_max_text_length = 6;
		//public static const c_tip_text_top_y = -62.5;
		//public static const c_tip_text_bottom_y = 50.5;
		public static const c_tip_text_height = 19;
		public static const c_tip_bg_height = 93;
		public static const c_tip_text_space = 3;
		public static const c_tip_close_top_offset = 19;
		public static const c_tip_close_bottom_offset = 25;
		
		override protected function configUI():void
		{
			super.configUI();
			trace(">>>>>>>>>>>>>>> GuidePanel::configUI");
			
			// test
			var desc:String = "MouseL点击<font color='#FF0000'>下划线文字</font>自动寻路";
			
			//setTipText(guide_tip_lt_mc,text,0);
			//setTipText(guide_tip_rt_mc,text,1);
			//setTipText(guide_tip_lb_mc,text,2);
			//setTipText(guide_tip_rb_mc,text,3);
			
		
			//addGuideElement(0, 6, "", "", 0, 0, true, 0, 0, 44, 44, 1, 1);
			//addGuideElement(0, 7, "", "", 0, 0, true, 0, 0, 44, 44, 1, 1);
			//addGuideElement(0, 8, "", "", 0, 0, true, 0, 0, 44, 44, 1, 1);
			//addGuideElement(0, 9, "", "", 0, 0, true, 0, 0, 44, 44, 1, 1);
			//removeGuideElement(3);
			
			trace("<<<<<<<<<<<<<<< GuidePanel::configUI");
		}
		
		public function setTipText(tip_mc:MovieClip, content:String, dir:int)
		{
			var desc_tf:TextField = tip_mc.getChildByName("desc_tf") as TextField;
			var bg_mc:MovieClip = tip_mc.getChildByName("bg_mc") as MovieClip;
			var close_mc:MovieClip = tip_mc.getChildByName("close_mc") as MovieClip;
			
			//desc_tf.height = c_tip_text_height;
			bg_mc.height = c_tip_bg_height;
			desc_tf.autoSize=TextFieldAutoSize.LEFT;
			desc_tf.multiline=true;
			desc_tf.wordWrap=true;
			desc_tf.htmlText = content;
			//var lines:int = int(desc_tf.textHeight / c_tip_text_height + 1);
			if((desc_tf.y+ desc_tf.textHeight+10)>93){
				bg_mc.height =desc_tf.y+ desc_tf.textHeight+10;
			}
			if (dir == 0 || dir == 1)
			{
				//close_mc.y = bg_mc.y - bg_mc.height + c_tip_close_top_offset;
			}
			else
			{
				//close_mc.y = bg_mc.y + c_tip_close_bottom_offset;
			}
			
			//desc_tf.y = close_mc.y + close_mc.height;
		}
		
		public function addGuideElement(guide_id:int,
										guide_type:int, 
										guide_desc:String, 
										guide_illustrate:String, 
										guide_offset_x:int,
										guide_offset_y:int,
										guide_with_box:Boolean,
										guide_box_x:int,
										guide_box_y:int,
										guide_box_width:int,
										guide_box_height:int,
										guide_box_type:int,
										guide_img_type:int)
		{
			if (guide_type == c_guide_type_illustrate)
			{
				var guide_illustrate_mc:GuideIllustrate = new GuideIllustrate();
				addChild(guide_illustrate_mc);
				guide_illustrate_mc.visible = true;
				guide_illustrate_mc.x = guide_offset_x;
				guide_illustrate_mc.y = guide_offset_y;
				guide_illustrate_mc.cur_guide_id = guide_id;
				guide_illustrate_mc.setIllustrate(guide_desc, guide_illustrate);
			}
			else if (guide_type == c_guide_type_tip_lt)
			{
				var guide_tip_lt_mc:GuideTipLT = new GuideTipLT();
				addChild(guide_tip_lt_mc);
				guide_tip_lt_mc.name = "guide_arrow_mc";
		 		guide_tip_lt_mc.visible = true;
				guide_tip_lt_mc.x = guide_offset_x;
				guide_tip_lt_mc.y = guide_offset_y;
				guide_tip_lt_mc.cur_guide_id = guide_id;
				setTipText(guide_tip_lt_mc, guide_desc, 0);
				
				var box_mc:MovieClip = guide_tip_lt_mc.getChildByName("guide_box_mc") as MovieClip; 
				box_mc.visible = guide_with_box;
				box_mc.x = guide_box_x;
				box_mc.y = guide_box_y;
				box_mc.scaleX = guide_box_width/30;
				box_mc.scaleY = guide_box_height/30;
			}
			else if (guide_type == c_guide_type_tip_rt)
			{
				var guide_tip_rt_mc:GuideTipRT = new GuideTipRT();
				addChild(guide_tip_rt_mc);
				guide_tip_rt_mc.name = "guide_arrow_mc";
				guide_tip_rt_mc.visible = true;
				guide_tip_rt_mc.x = guide_offset_x;
				guide_tip_rt_mc.y = guide_offset_y;
				guide_tip_rt_mc.cur_guide_id = guide_id;
				setTipText(guide_tip_rt_mc, guide_desc, 1);
				
				box_mc = guide_tip_rt_mc.getChildByName("guide_box_mc") as MovieClip; 
				box_mc.visible = guide_with_box;
				box_mc.x = guide_box_x;
				box_mc.y = guide_box_y;
				box_mc.scaleX = guide_box_width/30;
				box_mc.scaleY = guide_box_height/30;
			}
			else if (guide_type == c_guide_type_tip_lb)
			{
				var guide_tip_lb_mc:GuideTipLB = new GuideTipLB();
				addChild(guide_tip_lb_mc);
				guide_tip_lb_mc.name = "guide_arrow_mc";
				guide_tip_lb_mc.visible = true;
				guide_tip_lb_mc.x = guide_offset_x;
				guide_tip_lb_mc.y = guide_offset_y;
				guide_tip_lb_mc.cur_guide_id = guide_id;
				setTipText(guide_tip_lb_mc, guide_desc, 2);
				
				box_mc = guide_tip_lb_mc.getChildByName("guide_box_mc") as MovieClip; 
				box_mc.visible = guide_with_box;
				box_mc.x = guide_box_x;
				box_mc.y = guide_box_y;
				box_mc.scaleX = guide_box_width/30;
				box_mc.scaleY = guide_box_height/30;
			}
			else if (guide_type == c_guide_type_tip_rb)
			{
				var guide_tip_rb_mc:GuideTipRB = new GuideTipRB();
				addChild(guide_tip_rb_mc);
				guide_tip_rb_mc.name = "guide_arrow_mc";
		 		guide_tip_rb_mc.visible = true;
				guide_tip_rb_mc.x = guide_offset_x;
				guide_tip_rb_mc.y = guide_offset_y;
				guide_tip_rb_mc.cur_guide_id = guide_id;
				setTipText(guide_tip_rb_mc, guide_desc, 3);
				
				box_mc = guide_tip_rb_mc.getChildByName("guide_box_mc") as MovieClip; 
				box_mc.visible = guide_with_box;
				box_mc.x = guide_box_x;
				box_mc.y = guide_box_y;
				box_mc.scaleX = guide_box_width/30;
				box_mc.scaleY = guide_box_height/30;
			}
			else if (guide_type == c_guide_type_arrow_t)
			{
				var guide_arrow_t_mc:GuideArrowT = new GuideArrowT();
				addChild(guide_arrow_t_mc);
				guide_arrow_t_mc.name = "guide_arrow_mc";
		 		guide_arrow_t_mc.visible = true;
				guide_arrow_t_mc.x = guide_offset_x;
				guide_arrow_t_mc.y = guide_offset_y;
				guide_arrow_t_mc.mouseChildren=false;
			    guide_arrow_t_mc.mouseEnabled=false;
					
				if (guide_img_type > 0)
				{
					var bit:BitmapData = new (getDefinitionByName("ImgText" + guide_img_type) as Class);
					var bitmap_mc:Bitmap = new Bitmap(bit);
					bitmap_mc.x = -30;
					bitmap_mc.y = guide_arrow_t_mc.height + 10;
					guide_arrow_t_mc.addChild(bitmap_mc);
				}
				
				if (guide_box_type > 0)
				{
					var effect_mc:MovieClip = new (getDefinitionByName("GuideLight" + guide_box_type) as Class);
					effect_mc.name = "guide_box_mc";
					effect_mc.x = guide_box_x;
					effect_mc.y = guide_box_y;
					effect_mc.width = guide_box_width;
					effect_mc.height = guide_box_height;
					guide_arrow_t_mc.addChildAt(effect_mc,0);
				}
			}
			else if (guide_type == c_guide_type_arrow_b)
			{
				var guide_arrow_b_mc:GuideArrowB = new GuideArrowB();
				addChild(guide_arrow_b_mc);
				guide_arrow_b_mc.name = "guide_arrow_mc";
		 		guide_arrow_b_mc.visible = true;
				guide_arrow_b_mc.x = guide_offset_x;
				guide_arrow_b_mc.y = guide_offset_y;
				guide_arrow_b_mc.mouseChildren=false;
			    guide_arrow_b_mc.mouseEnabled=false;
				
				if (guide_img_type > 0)
				{
					bit = new (getDefinitionByName("ImgText" + guide_img_type) as Class);
					bitmap_mc = new Bitmap(bit);
					bitmap_mc.x = -70;
					bitmap_mc.y = -guide_arrow_b_mc.height - bitmap_mc.height - 10;
					guide_arrow_b_mc.addChild(bitmap_mc);
				}
				
				if (guide_box_type > 0)
				{
					effect_mc = new (getDefinitionByName("GuideLight" + guide_box_type) as Class);
					effect_mc.name = "guide_box_mc";
					effect_mc.x = guide_box_x;
					effect_mc.y = guide_box_y;
					effect_mc.width = guide_box_width;
					effect_mc.height = guide_box_height;
					guide_arrow_b_mc.addChildAt(effect_mc,0);
				}
			}
			else if (guide_type == c_guide_type_arrow_l)
			{
				var guide_arrow_l_mc:GuideArrowL = new GuideArrowL();
				addChild(guide_arrow_l_mc);
				guide_arrow_l_mc.name = "guide_arrow_mc";
		 		guide_arrow_l_mc.visible = true;
				guide_arrow_l_mc.x = guide_offset_x;
				guide_arrow_l_mc.y = guide_offset_y;
				guide_arrow_l_mc.mouseChildren=false;
			    guide_arrow_l_mc.mouseEnabled=false;
				if (guide_img_type > 0)
				{
					bit = new (getDefinitionByName("ImgText" + guide_img_type) as Class);
					bitmap_mc = new Bitmap(bit);
					bitmap_mc.x = guide_arrow_l_mc.width + 10;
					bitmap_mc.y = -bitmap_mc.height;
					guide_arrow_l_mc.addChild(bitmap_mc);
				}
				
				if (guide_box_type > 0)
				{
					effect_mc = new (getDefinitionByName("GuideLight" + guide_box_type) as Class);
					effect_mc.name = "guide_box_mc";
					effect_mc.x = guide_box_x;
					effect_mc.y = guide_box_y;
					effect_mc.width = guide_box_width;
					effect_mc.height = guide_box_height;
					guide_arrow_l_mc.addChildAt(effect_mc,0);
				}
			}
			else if (guide_type == c_guide_type_arrow_r)
			{
				var guide_arrow_r_mc:GuideArrowR = new GuideArrowR();
				addChild(guide_arrow_r_mc);
				guide_arrow_r_mc.name = "guide_arrow_mc";
		 		guide_arrow_r_mc.visible = true;
				guide_arrow_r_mc.x = guide_offset_x;
				guide_arrow_r_mc.y = guide_offset_y;
				guide_arrow_r_mc.mouseChildren=false;
			    guide_arrow_r_mc.mouseEnabled=false;
				if (guide_img_type > 0)
				{
					bit = new (getDefinitionByName("ImgText" + guide_img_type) as Class);
					bitmap_mc = new Bitmap(bit);
					bitmap_mc.x = -guide_arrow_r_mc.width - bitmap_mc.width - 10;
					bitmap_mc.y = 0;
					guide_arrow_r_mc.addChild(bitmap_mc);
				}
				
				if (guide_box_type > 0)
				{
					effect_mc = new (getDefinitionByName("GuideLight" + guide_box_type) as Class);
					effect_mc.name = "guide_box_mc";
					effect_mc.x = guide_box_x;
					effect_mc.y = guide_box_y;
					effect_mc.width = guide_box_width;
					effect_mc.height = guide_box_height;
					guide_arrow_r_mc.addChildAt(effect_mc,0);
				}
			}
		}
		
		public function removeGuideElement(guide_type:int)
		{
			while (this.numChildren > 0)
			{
				this.removeChildAt(0);
			}
		}
	}
}


























