/********************************************************************
Created:2014/04/11
Filename: MountTip
file ext:as
Author:JimZhang@snda
Purpose:Tips系统View MountTip控件
*********************************************************************/

package ActionScript3.Tips
{

	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.filters.GlowFilter;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFormat;
	
	import AS3.BaseDynamicTip;
	
	import ActionScript3.MyPanel;
	import ActionScript3.Tips.MountTipData;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.TextFieldEx;

	public class MountTip extends BaseDynamicTip
	{
		public var tF_MountDescribe:TextField;
		public var mc_Loader:UILoader;
		public var mc_SlotColorBg:MovieClip;
		//public var mc_NameBg:MovieClip;
		public var TipData:SkillTipData;
		//public var tF_ItemName:TextField;
		public var mc_Bg:MovieClip;
		
		public var TipHeight:int;
		public var TipWidth:int;
		
		public function MountTip()
		{

		}

		override protected function configUI():void
		{
			super.configUI();
			TipWidth = mc_Bg.width;
			TipWidth = mc_Bg.height;
			//Test();
		}

		function Test()
		{
			var mountData:MountTipData = new MountTipData  ;
			mountData.Id = 0;
			mountData.MountName = "超级无敌坐骑";
			mountData.ColorName = "lv3";
			mountData.MountDescribe = "解锁于人物等级9级 ";
			mountData.IconName = "img_Unidentify.png";
			updateData( mountData );
		}


		public function updateData( TipData:Object ):void
		{
			if (! TipData)
			{
				visible = false;
				return;
			}
			visible = true;
            setTxt(TipData.ColorName,TipData.MountName);
			 /*
			 			mc_NameBg.gotoAndStop( TipData.ColorName );
									var ItemName:TextField  =  (mc_NameBg.getChildByName("tF_ItemName") as TextField);
			if (ItemName)
			{
				ItemName.htmlText = TipData.MountName;
			}
			else
			{
				//ExternalInterface.call( "ASTrace", "TipData ItemName is null");
			}
			 */
			if (TipData.IconName != "")
			{
				mc_Loader.source = "img://" + String(TipData.IconName);
			}
			else
			{
				mc_Loader.source = "img://MMO_UIIcon.icon.blank";
			}
			mc_Loader.visible = true;
			mc_SlotColorBg.gotoAndStop( TipData.ColorName );

			tF_MountDescribe.htmlText = TipData.MountDescribe;
		}

	}

}