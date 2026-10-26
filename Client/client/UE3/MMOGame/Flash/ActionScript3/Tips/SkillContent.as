package ActionScript3.Tips
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.UILoader;
	import flash.external.ExternalInterface;

	import flash.filters.ColorMatrixFilter;
	import fl.motion.ColorMatrix;
	import flash.geom.ColorTransform;
	import ActionScript3.Common.Utils.StyleType;
	
	public class SkillContent extends MovieClip
	{
		public var tF_skillName:TextField;
		public var mc_skillLoad:UILoader;
		public var TipHeight:int = 0;
		public var tf_skillDec:TextField;

		public function SkillContent()
		{
			tf_skillDec.visible=false;
		}

		public function ReSize(startY:int):int
		{
			y = startY;
			return y + height;
		}
		
		//设置铭文数据
		public function setSkillData(skillIconType:String,skillName:String,  skillDec:String):void
		{
			clear();
			if (null == skillIconType || skillIconType == "")
			{
				visible = false;
			}
			else
			{
				tf_skillDec.y=24;
				tf_skillDec.visible=true;
				tf_skillDec.htmlText=skillDec;
				tf_skillDec.height=tf_skillDec.textHeight+4;
				tF_skillName.htmlText = (skillName == null) ? "":skillName;
				mc_skillLoad.gotoAndStop(1);
				var mc_Loader:UILoader = mc_skillLoad.getChildByName("mc_Loader") as UILoader;
				if (null != mc_Loader){
					if( skillIconType.length > 0 )
					{
						mc_Loader.source = "img://" + skillIconType;
						mc_Loader.visible = true;
					}
					else
					{
						mc_Loader.visible = false;
					}
				}
			}
		}
		public function SetData(skillIconType:String, skillName:String, iconName:String):void
		{
			clear();
			if (null == skillIconType || skillIconType == "")
			{
				visible = false;
			}
			else
			{
				visible = true;
				tF_skillName.htmlText = (skillName == null) ? "":skillName;
				mc_skillLoad.gotoAndStop(skillIconType);
				var mc_Loader:UILoader = mc_skillLoad.getChildByName("mc_Loader") as UILoader;
				if (null != mc_Loader)
				{
					if( iconName.length > 0 )
					{
						var grayStrIdx:int = iconName.lastIndexOf( "_g" );
						var isGray:Boolean = ( grayStrIdx >= 0 && ( grayStrIdx == iconName.length - 2 ) );
						if( isGray )
						{
							var realIconName:String = iconName.substr( 0, grayStrIdx );
							ExternalInterface.call("ASTrace", "skillIconName Gray" + realIconName);
							mc_Loader.source = "img://" + realIconName;
						}
						else
						{
							mc_Loader.source = "img://" + String(iconName);
						}
						mc_Loader.visible = true;
					
						SetToGray( mc_Loader, isGray );
					}
					else
					{
						mc_Loader.visible = false;
					}
				}
			}
		}
		
		
		
		private function clear():void
		{
			tf_skillDec.text="";
			tf_skillDec.y=0;
			tf_skillDec.height=24;
		}
		//
		public function SetToGray( mc:MovieClip, gray:Boolean )
		{
			if (! mc)
			{
				return;
			}
			if (gray)
			{
				mc.filters = [ StyleType.getInstance().getBlackFilter() ];
			}
			else
			{
				mc.filters = null;
			}
		}
	}

}