/********************************************************************
Created:2013/04/18
Filename: SkillTip
file ext:as
Author:hemu@snda
Purpose:Tips系统View SkillTip控件
*********************************************************************/

package ActionScript3.Tips
{

	import ActionScript3.MyPanel;

	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;

	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.TextFieldEx;
	import ActionScript3.Tips.SkillTipData;
	import scaleform.clik.controls.UILoader;
	import ActionScript3.Common.Utils.StyleType;

	public class SkillTip extends MyPanel
	{
		public var tf_NextLevel:TextField;
		public var tf_SkillName:TextField;
		public var tf_SkillLevel:TextField;
		public var mc_Loader:UILoader;
		public var tf_SkillCost:TextField;
		//public var tf_SkillCd:TextField;
		public var tf_SkillCD:TextField;
		public var tf_SkillUnlock:TextField;
		public var tf_SkilDescribe:TextField;
		public var tf_NextDescribeTitle:TextField;
		public var mc_SkillRune:MovieClip;
		public var mc_SkillDamage:MovieClip;
		public var mc_UpLevNeed:MovieClip;
		public var mc_SkillAid:MovieClip;
		public var mc_Bg:MovieClip;
		public var mc_Line0:MovieClip;
		public var mc_Line1:MovieClip;
		public var mc_Line2:MovieClip;
		public var mc_Line3:MovieClip;
		public var TipData:SkillTipData;
		
		public var tf_RuneName:TextField;
		public var tf_RuneLevel:TextField;
		public var tf_RuneDesc:TextField;
		
		public var tf_MainSpeciality:TextField;
		public var tf_SecondSpeciality:TextField;
		public var tf_ThirdSpeciality:TextField;
		public var tf_DescriptiveWords:TextField;
		public var tf_UseMethod:TextField;
		public var tf_AttackRange:TextField;
		public var tf_EffectRange:TextField;
		
		public var EffectRangeTexMc:UILoader;
		public var tf_show:TextField;
		public var tf_CombineLevel:TextField;
           
		public var TipHeight:int;
		public var TipWidth:int;
		
		//
		var count:int;
		var Mode:int;
		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren=false;
			this.mouseEnabled=false;
//			if (tf_NextLevel)
//			{
//				tf_NextLevel.htmlText = "<font color='#FF0000'>下一级</font>";
//			}
			TipWidth = mc_Bg.width;
			
			if (tf_MainSpeciality)
			{
				tf_MainSpeciality.autoSize = flash.text.TextFieldAutoSize.LEFT;
				tf_MainSpeciality.wordWrap = true;
			}
			if (tf_SecondSpeciality)
			{
				tf_SecondSpeciality.autoSize = flash.text.TextFieldAutoSize.LEFT;
				tf_SecondSpeciality.wordWrap = true;
			}
			if (tf_ThirdSpeciality)
			{
				tf_ThirdSpeciality.autoSize = flash.text.TextFieldAutoSize.LEFT;
				tf_ThirdSpeciality.wordWrap = true;
			}
			
			if (tf_SkilDescribe)
			{
				tf_SkilDescribe.autoSize = flash.text.TextFieldAutoSize.LEFT;
				tf_SkilDescribe.wordWrap = true;
			}
			
			if (tf_DescriptiveWords)
			{
				tf_DescriptiveWords.autoSize = flash.text.TextFieldAutoSize.LEFT;
				tf_DescriptiveWords.wordWrap = true;
			}
			if (mc_Line0)
			{
				mc_Line0.visible = false;
			}
			
			if (mc_Line2)
			{
				mc_Line2.visible = false;
			}
			
			if (mc_Line3)
			{
				mc_Line3.visible = false;
			}
			
			if (mc_SkillDamage)
			{
				mc_SkillDamage.tf_SkillDamage.autoSize = flash.text.TextFieldAutoSize.LEFT;
				mc_SkillDamage.tf_SkillDamage.wordWrap = true;
			}

			if (mc_SkillRune)
			{
				mc_SkillRune.tf_RuneDescribe.autoSize = flash.text.TextFieldAutoSize.LEFT;
				mc_SkillRune.tf_RuneDescribe.wordWrap = true;
			}

			if (tf_RuneDesc)
			{
				tf_RuneDesc.autoSize = flash.text.TextFieldAutoSize.LEFT;
				tf_RuneDesc.wordWrap = true;
			}
			
			tf_RuneLevel.visible = false;
			tf_RuneLevel.htmlText = "";
			//
			tf_SkillLevel.visible = false;
			tf_SkillLevel.htmlText = "";
			tf_SkillCost.visible = false;
			tf_SkillCost.htmlText = "";
			tf_SkillCD.visible = false;
			tf_SkillCD.htmlText = "";
			tf_UseMethod.visible = false;
			tf_UseMethod.htmlText = "";
			tf_AttackRange.visible = false;
			tf_AttackRange.htmlText = "";
			tf_EffectRange.visible = false;
			tf_EffectRange.htmlText = "";
			EffectRangeTexMc.visible = false;
			tf_show.visible = false;
			tf_MainSpeciality.visible=false;
			tf_MainSpeciality.text="";
			tf_SecondSpeciality.visible = false;
			tf_SecondSpeciality.text="";
			tf_ThirdSpeciality.visible = false;
			tf_ThirdSpeciality.text="";
			tf_DescriptiveWords.visible = false;
			tf_DescriptiveWords.htmlText = "";
			
			if (0)
			{
				count = 3;
				Mode = 0;
				//this.addEventListener(MouseEvent.CLICK, TestMode);
				//Test();
			}
		}

/*		function Test()
		{
			var i:int;
			var skillData:Object = new Object  ;

			skillData.Id = 1;
			skillData.CombineLevel = "21级";
			skillData.NextLevel = "<font color='#FF0000'>下一级</font>";
			skillData.SkillName = "魂斩";
			skillData.IconName = "1.tga";

			skillData.SkillDescribe = "";
			for (i = 0; i < count; ++ i)
			{
				skillData.SkillDescribe +=  " 对前方目标发动强力挥砍,有20%几率将目标击退或导致其硬直!";
			}

			skillData.MainSpeciality = "我是主特性";
			skillData.SecondSpeciality = "我是二特性，二特性较长较二较长较二较长较二";
			skillData.ThirdSpeciality = "我是三特性";
			

			skillData.HasRune = false;
			skillData.RuneName = "愤恨";
			skillData.RuneLev = "铭文等级： 2级";
			skillData.RuneDescribe = "符文技能描述，怎么说呢，这。。。。我要换行，支持html，起码撑到2行吧"
			
			skillData.SkillLevel = "";//"5级";
			skillData.SkillCost = "";//"消耗怒气：8点 ";
			skillData.CDTime = "";//"冷却时间：10秒 ";
			skillData.SkillUnlock = "";//"解锁于人物等级9级 ";
			skillData.UseMethod = "释放方式：点击释放";
			skillData.AttackRange = "";//"技能距离：原地";
			skillData.EffectRange = "";//"技能范围：3米";
			skillData.EffectRangeTexPath = "";//"img://MMO_UIIcon.icon.blank";
			skillData.DescriptiveWords = "我是简短描述";
			
			skillData.HasUpLevNeed = true;
			skillData.UpLevNeedSoul = "<p><font color='#FF0000'>需要魂 12222</p>";
			skillData.UpLevNeedLev = "<p><font color='#FF0000'>需要等级 3333</p>";

			updateData( skillData );
		}*/


		public function updateData( TipData:Object ):void
		{
			if (! TipData)
			{
				visible = false;
				return;
			}
			visible = true;

			tf_NextLevel.htmlText = TipData.NextLevel;
			if( TipData.HasRune )
			{
				//tf_SkillName.htmlText = "[" + TipData.SkillName + "]" + TipData.RuneName;
				tf_SkillName.htmlText = TipData.SkillName + "[" + TipData.RuneName + "]";
			}
			else
			{
				tf_SkillName.htmlText = TipData.SkillName;
			}

			if (TipData.IconName != "")
			{
				var str:String=TipData.IconName;
				var l:int=str.length;
				var bl:Boolean=false;
				var ls:String=str.substr(l-2,l-1);
				if(ls=="_g")
				{
					bl=true;
					str=str.substr(0,l-2);
				}
				mc_Loader.source ="img://" + str;//"1.tga";
				if(bl==true)
				{
					mc_Loader.filters=[StyleType.getInstance().getBlackFilter()];
				}
				mc_Loader.visible = true;
			}
			else
			{
				mc_Loader.source = "img://MMO_UIIcon.icon.blank";
			}
			
			if(tf_CombineLevel)
			{
				tf_CombineLevel.htmlText = TipData.CombineLevel;
			}
			
			//第一块
			if( TipData.MainSpeciality.length > 0 ){
				tf_MainSpeciality.visible = true;
				tf_MainSpeciality.htmlText = TipData.MainSpeciality;
			}
			else{
				tf_MainSpeciality.visible = false;
			}
			
			if( TipData.SecondSpeciality.length > 0 ){
				tf_SecondSpeciality.visible = true;
				tf_SecondSpeciality.htmlText = TipData.SecondSpeciality;
			}
			else{
				tf_SecondSpeciality.visible = false;
			}
			
			if( TipData.ThirdSpeciality.length > 0 ){
				tf_ThirdSpeciality.visible = true;
				tf_ThirdSpeciality.htmlText = TipData.ThirdSpeciality;
			}
			else{
				tf_ThirdSpeciality.visible = false;
			}
			
			var isShowDividingLine1:Boolean = false;
			if( TipData.SkillDescribe.length > 0 ){
				tf_SkilDescribe.visible = true;
				tf_SkilDescribe.htmlText = TipData.SkillDescribe;
				isShowDividingLine1 = true;
			}
			else{
				tf_SkilDescribe.visible = false;
			}
			mc_Line1.visible = isShowDividingLine1;
			
//			if (null == TipData.SkillUnlock || TipData.SkillUnlock == "")
//			{
//				tf_SkillLevel.htmlText = TipData.SkillLevel;
//				tf_SkillLevel.visible = true;
//				tf_SkillUnlock.visible = false;
//			}
//			else
//			{
//				tf_SkillUnlock.text = TipData.SkillUnlock;
//				tf_SkillLevel.visible = false;
//				tf_SkillUnlock.visible = true;
//			}
			
			//第二块
			//符文技能
			if( TipData.HasRune ){
				if( tf_RuneName  ){
					tf_RuneName.visible = true;
					tf_RuneName.htmlText = "[" + TipData.RuneName + "]";
				}
				/*
				if( tf_RuneLevel ){
					tf_RuneLevel.visible = true;
					tf_RuneLevel.htmlText = TipData.RuneLev;
				}
				*/
				if( tf_RuneDesc ){
					tf_RuneDesc.visible = true;
					tf_RuneDesc.htmlText = TipData.RuneDescribe;
				}
			}
			else{
				if( tf_RuneName  ){
					tf_RuneName.visible = false;
				}
				if( tf_RuneLevel  ){
					tf_RuneLevel.visible = false;
				}
				if( tf_RuneDesc  ){
					tf_RuneDesc.visible = false;
				}
			}
			
			//第三块
			/*
			var isShowDividingLine2:Boolean = false;
			if( TipData.SkillLevel.length > 0 ){
				tf_SkillLevel.visible = true;
				tf_SkillLevel.htmlText = TipData.SkillLevel;
				isShowDividingLine2 = true;
			}
			else{
				tf_SkillLevel.visible = false;
			}
			
			if( TipData.SkillCost.length > 0 ){
				tf_SkillCost.visible = true;
				tf_SkillCost.htmlText = TipData.SkillCost;
				isShowDividingLine2 = true;
			}
			else{
				tf_SkillCost.visible = false;
			}
			
			if( TipData.CDTime.length > 0 ){
				tf_SkillCD.visible = true;
				tf_SkillCD.htmlText = TipData.CDTime;
				isShowDividingLine2 = true;
			}
			else{
				tf_SkillCD.visible = false;
			}
			
			if( TipData.UseMethod.length > 0 ){
				tf_UseMethod.visible = true;
				tf_UseMethod.htmlText = TipData.UseMethod;
				isShowDividingLine2 = true;
			}
			else{
				tf_UseMethod.visible = false;
			}
			
			if( TipData.AttackRange.length > 0 ){
				tf_AttackRange.visible = true;
				tf_AttackRange.htmlText = TipData.AttackRange;
				isShowDividingLine2 = true;
			}
			else{
				tf_AttackRange.visible = false;
			}
			
			if( TipData.EffectRange.length > 0 ){
				tf_EffectRange.visible = true;
				tf_EffectRange.htmlText = TipData.EffectRange;
				isShowDividingLine2 = true;
			}
			else{
				tf_EffectRange.visible = false;
			}
			
			if (TipData.EffectRangeTexPath != "")
			{
				EffectRangeTexMc.source = "img://" + String(TipData.EffectRangeTexPath);
				EffectRangeTexMc.visible=true;
				tf_show.visible=true;
				isShowDividingLine2 = true;
			}
			else
			{
				EffectRangeTexMc.source = "img://MMO_UIIcon.icon.blank";
				EffectRangeTexMc.visible=false;
				tf_show.visible=false;
			}
			
			mc_Line2.visible = isShowDividingLine2;
			*/
			
			//
			mc_UpLevNeed.visible = TipData.HasUpLevNeed;
			if (mc_UpLevNeed.visible){
				mc_UpLevNeed.tf_NeedSoul.htmlText = TipData.UpLevNeedSoul;
				mc_UpLevNeed.tf_NeedLev.htmlText = TipData.UpLevNeedLev;
			}
			
			/*
			//
			if( TipData.DescriptiveWords.length > 0 ){
				tf_DescriptiveWords.visible = true;
				tf_DescriptiveWords.htmlText = TipData.DescriptiveWords;
				mc_Line3 = true;
			}
			else{
				tf_DescriptiveWords.visible = false;
				mc_Line3 = false;
			}
			*/
			
			Resize();
		}

		public function Resize():void
		{
			
			var nY:int;
			var nSpace:int = 8;
			var line:int=6;
       
			if(tf_MainSpeciality.visible)
			{
				nY = tf_MainSpeciality.y + tf_MainSpeciality.textHeight + nSpace;
			}
			if( tf_SecondSpeciality.visible )
			{
				tf_SecondSpeciality.y = nY;
				nY = tf_SecondSpeciality.y + tf_SecondSpeciality.textHeight + nSpace;
			}
			if( tf_ThirdSpeciality.visible )
			{
				tf_ThirdSpeciality.y = nY;
				nY = tf_ThirdSpeciality.y + tf_ThirdSpeciality.textHeight + nSpace;
			}
			nY = Math.max( 128 , nY );
//			if( mc_Line0 )
//			{
//				mc_Line0.y = nY + line;
//				nY = mc_Line0.y + mc_Line0.height + nSpace;
//			}
			if( mc_Line1 && mc_Line1.visible==true)
			{
				mc_Line1.y = nY + line;
				nY = mc_Line1.y + mc_Line1.height + nSpace;
			}
			
			if( tf_SkilDescribe.visible )
			{
				tf_SkilDescribe.y = nY;
				nY = nY + tf_SkilDescribe.textHeight + nSpace;
			}
			
			//铭文
			var hasRuneInfo:Boolean = false;
			if( tf_RuneName && tf_RuneLevel )
			{
				if( tf_RuneName.visible || tf_RuneLevel.visible )
				{
					hasRuneInfo = true;
					tf_RuneName.y = nY;
					tf_RuneLevel.y = nY;
					nY += tf_RuneName.textHeight + nSpace;
				}
			}
			
			if( tf_RuneDesc )
			{
				if( tf_RuneDesc.visible )
				{
					hasRuneInfo = true;
					tf_RuneDesc.y = nY;
					nY = nY + tf_RuneDesc.textHeight + nSpace;
				}
			}
			
			//
			if( mc_Line2.visible )
			{
				mc_Line2.y = nY + line;
				nY = mc_Line2.y + mc_Line2.height + nSpace;
			}
			
			if( tf_SkillCD.visible || tf_SkillLevel.visible )
			{
				tf_SkillCD.y = nY;
				tf_SkillLevel.y = nY;
				nY += tf_SkillCD.textHeight + nSpace;
			}
			if( tf_SkillCost.visible )
			{
				tf_SkillCost.y = nY;
				nY += tf_SkillCost.textHeight + nSpace;
			}
			
			if( tf_UseMethod.visible)
			{
				tf_UseMethod.y = nY;
				nY += tf_UseMethod.textHeight + nSpace;
			}
			if(tf_AttackRange.visible)
			{
				tf_AttackRange.y = nY;
				nY += tf_AttackRange.textHeight + nSpace;
			}
			
			if(tf_EffectRange.visible)
			{
				tf_EffectRange.y = nY;
				nY += tf_EffectRange.textHeight + nSpace;
			}
			
			if(EffectRangeTexMc.visible==true)
			{
				EffectRangeTexMc.y=nY;
				tf_show.y=nY+24;
				nY+=EffectRangeTexMc.height+nSpace;
				tf_show.visible=true;
			}
			else
			{
				tf_show.visible=false;
			}
			
			//
			if(mc_UpLevNeed.visible)
			{
				mc_UpLevNeed.y = nY;
				nY += mc_UpLevNeed.height + nSpace;
			}
			
			//
			if( mc_Line3.visible )
			{
				mc_Line3.y = nY+line ;
				nY = mc_Line3.y + mc_Line3.height + nSpace;
			}
			
			if( tf_DescriptiveWords.visible )
			{
				tf_DescriptiveWords.y = nY;
				nY += tf_DescriptiveWords.textHeight + nSpace;
			}
			
			//
			TipWidth = mc_Bg.width;
			if((nY - mc_Bg.y + nSpace+14)<165){
				mc_Bg.height = 165;
			}else{
				mc_Bg.height = nY - mc_Bg.y + nSpace+14;
			}
			
			TipHeight = mc_Bg.height;

		}
	}

}