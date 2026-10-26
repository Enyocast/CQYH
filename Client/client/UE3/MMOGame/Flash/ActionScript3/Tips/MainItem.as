package ActionScript3.Tips
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;

	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ListItemTreeRenderer;
	import scaleform.clik.core.UIComponent;
	import scaleform.gfx.TextFieldEx;
	import ActionScript3.Tips.ItemTipData;
	import scaleform.clik.controls.UILoader;
	import flash.text.TextFormat;
	import flash.filters.GlowFilter;
	import flash.filters.BevelFilter;
	import ActionScript3.Common.Utils.StyleType;
	import ActionScript3.MyPanel;
	import AS3.BaseDynamicTip;
	import flash.text.StyleSheet;
	import ActionScript3.Tips.AddAttribute;


	public class MainItem extends BaseDynamicTip
	{
		public var mc_Loader:UILoader;
		public var mc_SlotColorBg:MovieClip;
		public var mc_IsEquiped:MovieClip;
		public var tF_Part:TextField;
		public var tF_Profession:TextField;
		public var tF_RequireLevel:TextField;
	    public var tF_sex:TextField;
		//public var tF_ItemLevel:TextField;
		public var tF_Bind:TextField;
		public var mc_Bg:MovieClip;
		public var mc_Power:TextField;
		public var mc_PowerTitle:TextField;
		public var tF_IsGotten:TextField;

		public var mc_MainParameter:AddAttribute;
		public var mc_Random:AddAttribute;
		public var mc_UnIdentified:AddAttribute;
		public var mc_Enhance:AddAttribute;
		public var mc_Lucky:AddAttribute;
		public var mc_AddParameter:AddAttribute;
		public var mc_SuitMiddle:AddAttribute;
		public var mc_Weather:AddAttribute;
		public var mc_Sign:AddAttribute;
		public var mc_Reputation:AddAttribute;
		public var mc_Foot:ItemTipFoot;
		public var mc_Compare:ItemCompare;
		public var mc_SkillLine:MovieClip;
		public var mc_WeightParameter:AddAttribute;
		public var mc_LevelUpPoint:AddAttribute;
		public var TipData:ItemTipData;
		private var count:int;

		public var TipHeight:int = 0;
		public var TipWidth:int = 0;
		public var Spacing:int = 5;
		private const STARTY:int = 128;

		public const MAX_SKILL:int = 6;
		private var skillArray:Array;
		private const minHeight:int=228;
		public function MainItem()
		{
			InitData();
		}

		private function InitData():void
		{
			skillArray = [];
			for (var index:int = 0; index < MAX_SKILL; index++)
			{
				skillArray.push(new Skill_Content());
				addChild(skillArray[index]);
				skillArray[index].name = "Skill_Content" + index.toString();
				skillArray[index].y = y + 20 * index;
				skillArray[index].x = x;
				skillArray[index].width = 234;
				skillArray[index].height = 24;
				skillArray[index].visible = false;
			}
		}

		public function updateData( itemData:Object ):void
		{
			if (itemData)
			{
				TipData = itemData as ItemTipData;
			}
			if (TipData)
			{
				visible = true;
                setTxt(TipData.ColorName,TipData.ItemName);
				if (itemData.IconName != "")
				{
					mc_Loader.source = "img://" + String(TipData.IconName);
				}
				else
				{
					mc_Loader.source = "img://MMO_UIIcon.icon.blank";
				}
				mc_Loader.visible = true;
				mc_Power.text = TipData.Power;
				if (null == TipData.Power || TipData.Power == "")
				{
					mc_PowerTitle.visible = false;
					mc_Power.visible=false;
				}
				else
				{
					mc_Power.visible=true;
					mc_PowerTitle.visible = true;
				}
				tF_RequireLevel.htmlText =TipData.RequireLevel;
				//tF_ItemLevel.htmlText = TipData.ItemLevel;
				mc_IsEquiped.visible = TipData.IsEquiped;
				tF_Part.htmlText = TipData.PartName;
				if(TipData.Bind!="")
				{
					tF_Bind.htmlText = TipData.Bind+"  "+TipData.RepairState;
				}
				else
				{
					tF_Bind.htmlText = TipData.RepairState;
				}
				
				tF_Profession.htmlText = TipData.Profession;
				mc_SlotColorBg.gotoAndStop( TipData.ColorName );
				tF_sex.htmlText=TipData.Gender;
				tF_sex.autoSize=TextFieldAutoSize.RIGHT;
				mc_MainParameter.SetData(TipData.MainParameter);
				if(mc_WeightParameter && TipData.WeightParameter){
					mc_WeightParameter.visible=true;
					mc_WeightParameter.SetData(TipData.WeightParameter+TipData.PurityParameter);
			    }else{
					mc_WeightParameter.visible=false;
				}
				if(TipData.IsGotten!="")
				{
					tF_IsGotten.visible=true;
					tF_IsGotten.htmlText=TipData.IsGotten;
				}
				else
				{
					tF_IsGotten.visible=false;
				}
				if(TipData.LevelUpPoint!="")
				{
					mc_LevelUpPoint.visible=true;
					mc_LevelUpPoint.SetData(TipData.LevelUpPoint);
				}
				else
				{
					mc_LevelUpPoint.visible=false;
				}
				mc_UnIdentified.visible = false;
				if( mc_UnIdentified.visible )
				{
					mc_UnIdentified.SetData( TipData.unIdentifiedText );
				}
				mc_Random.SetData(TipData.RandomParameter);
				mc_Enhance.SetData(TipData.EnhanceParameter);
				mc_Lucky.SetData(TipData.LuckyParameter);
				mc_SkillLine.visible = (TipData.ShowSkill || TipData.ShowSoul);
				//mc_SkillSlotCnt.SetData( TipData.SkillSlotCnt );
				var i:int = 0;
                var l:int=skillArray.length;
				//var index:int=0;
				if (TipData.ShowSkill)
				{
					var ll:int=TipData.SkillName.length;
					
					for (i = 0; i < MAX_SKILL; i++)
					{
						if (i<ll)
						{
							skillArray[i].visible = true;
							skillArray[i].setSkillData(TipData.SkillIconName[i],TipData.SkillName[i],TipData.SkillDesc[i]);
						}
						else
						{
							skillArray[i].visible = false;
						}
					}
				}
				else if (TipData.ShowSoul)
				{
					i = 0;
					var soulDataCnt:int = TipData.SoulIconType.length < TipData.SoulName.length ? TipData.SoulIconType.length : TipData.SoulName.length;
					soulDataCnt = soulDataCnt < TipData.SoulIconName.length ? soulDataCnt : TipData.SoulIconName.length;
					for (i = 0; i < MAX_SKILL; i ++)
					{
						if (i < l && i < soulDataCnt)
						{
							skillArray[i].SetData(TipData.SoulIconType[i],TipData.SoulName[i],TipData.SoulIconName[i]);
						}
						else
						{
							skillArray[i].visible = false;
						}
					}
				}
				else
				{
					for (i = 0; i < l; i++)
					{
						skillArray[i].visible = false;
					}
				}

				mc_SuitMiddle.visible = TipData.bShowSuit;
				if (TipData.bShowSuit)
				{
					mc_SuitMiddle.SetData(TipData.SuitParameter);
				}
				mc_Weather.SetData(TipData.WeatherParameter);
				var format:TextFormat=mc_AddParameter.tf_Text.defaultTextFormat;
				format.leading=0;
				mc_AddParameter.SetData(TipData.AddParameter);
				mc_AddParameter.tf_Text.defaultTextFormat=format;
				mc_AddParameter.tf_Text.setTextFormat(format);
				mc_Sign.SetData(TipData.SignParameter);
				mc_Reputation.SetData( TipData.ReputationText );				
				mc_Foot.SetData(TipData);
				mc_Compare.visible = TipData.bShowItemEffect;
				if (TipData.bShowItemEffect)
				{
					mc_Compare.SetData(TipData.Damage, TipData.Life);
				}
				Resize();
			}
			else
			{
				visible = false;
			}
		}

		public function GetAddSuitStartY(suitAddHeight:int):int
		{
			if (TipData.bShowSuit && ! mc_SuitMiddle.visible)
			{
				if (TipHeight - STARTY >= suitAddHeight)
				{
					return STARTY;
				}
				else
				{
					return TipHeight - suitAddHeight;
				}
			}
			else
			{
				return -1;
			}

		}

		public function Resize():void
		{
			if(mc_PowerTitle.visible==false && mc_Power.visible==false){
				tF_RequireLevel.y=tF_Part.y;
				tF_Bind.y=tF_RequireLevel.y+tF_RequireLevel.height;
			}else{
				tF_RequireLevel.y=84;
				tF_Bind.y=102;
			}
			var curY:int = STARTY;
			if (mc_MainParameter.visible)
			{
				curY=layou(mc_MainParameter,curY,12);
			}
			if (mc_Random.visible)
			{
				curY=layou(mc_Random,curY,8);
			}
			if (mc_UnIdentified.visible)
			{
				curY=layou(mc_UnIdentified,curY,30);
			}
			if (mc_Enhance.visible)
			{
				curY=layou(mc_Enhance,curY,8);
			}
			if (mc_Lucky.visible)
			{
				curY=layou(mc_Lucky,curY,8);
			}
			if (mc_WeightParameter && mc_WeightParameter.visible)
			{
				curY =layou(mc_WeightParameter,curY,8); 
				trace("mc_WeightParameter.visible");
			}
			if(tF_IsGotten.visible)
			{
				tF_IsGotten.y=mc_WeightParameter.y+6;
			}
			if(mc_LevelUpPoint.visible)
			{
				curY =layou(mc_LevelUpPoint,curY,8); 
			}
			if (mc_SkillLine.visible)
			{
				curY=layou(mc_SkillLine,curY,6);
			}
/*			if (mc_SkillSlotCnt.visible)
			{
				curY=layou(mc_SkillSlotCnt,curY,8);
			}*/
			for (var index:int = 0; index < MAX_SKILL; index ++)
			{
				var skillContent:SkillContent=skillArray[index];
				if (skillContent && skillContent.visible)
				{
					curY = layou(skillContent,curY,0);
				}
			}
            if(skillArray[0] && skillArray[0].visible){
				curY+=6;
			}
			if (TipData.bShowSuit)
			{
				PreCalculateSize();

				if (TipHeight > root.stage.stageHeight)
				{
					mc_SuitMiddle.visible = false;
				}
				else
				{
					mc_SuitMiddle.visible = true;
				}
			}
			
			if (mc_SuitMiddle.visible)
			{
				curY = layou(mc_SuitMiddle,curY,12);
			}
			if (mc_Weather.visible)
			{
				curY =layou(mc_Weather,curY,12); 
			}
			if (mc_AddParameter.visible)
			{
				curY = layou(mc_AddParameter,curY,12);  
			}
			if (mc_Sign.visible)
			{
				curY =layou(mc_Sign,curY,12); 
			}
			if( mc_Reputation.visible )
			{
				curY =layou(mc_Reputation,curY,12); 
			}
			if (mc_Foot.visible)
			{
				curY =mc_Foot.ReSize(curY,12); 
			}
			if (mc_Compare.visible)
			{
				curY = layou(mc_Compare,curY,12);
			}
			curY+=20;
			TipHeight = curY - mc_Bg.y;
			if(TipHeight<minHeight){
                TipHeight=minHeight;
			}
			mc_Bg.height = TipHeight;
			TipWidth = mc_Bg.width;
		}
		
		
		private function layou(mc:MovieClip,curY:int,spance:int):int
		{
			mc.y=curY;
			curY+=mc.height;
			curY+=spance;
			return curY;
		}

		public function PreCalculateSize():void
		{
			var curY:int = STARTY;
			if (mc_MainParameter.visible)
			{
				curY=layou(mc_MainParameter,curY,12);
				//curY = mc_MainParameter.ReSize(curY,12);
			}
			if (mc_Random.visible)
			{
				curY=layou(mc_Random,curY,8);
				//curY = mc_Random.ReSize(curY,8);
			}
			if (mc_UnIdentified.visible)
			{
				curY=layou(mc_UnIdentified,curY,30);
				//curY = mc_UnIdentified.ReSize(curY,30);
			}
			if (mc_Enhance.visible)
			{
				curY=layou(mc_Enhance,curY,8);
				//curY = mc_Enhance.ReSize(curY,8);
			}
			if (mc_Lucky.visible)
			{
				curY=layou(mc_Lucky,curY,8);
				//curY = mc_Lucky.ReSize(curY,8);
			}
			if (mc_WeightParameter && mc_WeightParameter.visible)
			{
				curY=layou(mc_WeightParameter,curY,8);
			}
			if(tF_IsGotten.visible)
			{
				tF_IsGotten.y=mc_WeightParameter.y+6;
			}
			if (mc_LevelUpPoint.visible)
			{
				curY=layou(mc_LevelUpPoint,curY,8);
			}
			if (mc_SkillLine.visible)
			{
				curY=layou(mc_SkillLine,curY,6);
				//mc_SkillLine.y = curY;
				//curY +=  6;
			}
			for (var index:int = 0; index < MAX_SKILL; index ++)
			{
				var skillContent:SkillContent=skillArray[index];
				if (skillContent && skillContent.visible)
				{
					curY = layou(skillContent,curY,0);
				}
			}
			if(skillArray[0] && skillArray[0].visible){
				curY+=6;
			}
			if (mc_SuitMiddle.visible)
			{
				curY = layou(mc_SuitMiddle,curY,12);
			}
			if (mc_Weather.visible)
			{
				curY =layou(mc_Weather,curY,12); 
			}
			if (mc_AddParameter.visible)
			{
				curY = layou(mc_AddParameter,curY,12);  
			}
			if (mc_Sign.visible)
			{
				curY =layou(mc_Sign,curY,12); 
			}
			if( mc_Reputation.visible)
			{
				curY =layou(mc_Reputation,curY,12); 
			}
			if (mc_Foot.visible)
			{
				curY =mc_Foot.ReSize(curY,12); //layou(mc_Foot,curY,20); 
			}
			if (mc_Compare.visible)
			{
				curY = layou(mc_Compare,curY,12);
			}
			curY+=20;
			TipHeight = curY - mc_Bg.y;
			mc_Bg.height = TipHeight;
		}

	}

}