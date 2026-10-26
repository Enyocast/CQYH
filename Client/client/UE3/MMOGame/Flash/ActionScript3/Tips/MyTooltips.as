package ActionScript3.Tips
{
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import flash.external.ExternalInterface;
	import ActionScript3.Tips.ItemTip;
	import ActionScript3.Tips.SkillTip;
	import ActionScript3.Tips.CommonTip;
	import ActionScript3.Tips.MountTip;
	import flash.utils.getDefinitionByName;
	import scaleform.clik.managers.PopUpManager;
	import scaleform.clik.events.ComponentEvent;
	import scaleform.clik.managers.FocusHandler;

	public class MyTooltips extends UIComponent
	{
		public var itemTip:ItemTip;
		public var skillTip:SkillTip;
		public var mountTip:MountTip;
		public var commonTip:CommonTip;
		public var ExtraItemTips:Array;
		var MaxExtraItemTipsCnt:int = 2;
		public var nextSkillTip:SkillTip;
		
		public var CurPriority:int=0;
		
		public function UCShow(v:Boolean, priority:int):void
		{
			if(v)
			{
				PopUpManager.show(this, -1, -1, null, priority);
			}
			else
			{
				if(this.parent)
				{
					this.parent.removeChild(this);
				}
			}
		}

		override protected function configUI():void
		{
			super.configUI();
			itemTip.visible = false;
			skillTip.visible = false;
			commonTip.visible = false;
			mountTip.visible = false;
			this.mouseEnabled=this.mouseChildren=false;
			ExtraItemTips = new Array;
			
			if (null == nextSkillTip)
			{
				nextSkillTip = new Tips_Skill  ;
				if (null != nextSkillTip)
				{
					addChild(nextSkillTip);
					nextSkillTip.name = "nextSkillTip";
					nextSkillTip.x = skillTip.x + skillTip.TipWidth;
					nextSkillTip.y = skillTip.y;
					nextSkillTip.visible = false;
				}
			}
		}

		public function CloseAll():void
		{
			if (itemTip)
			{
				itemTip.visible = false;
			}
			if (skillTip)
			{
				skillTip.visible = false;
			}
			if (mountTip)
			{
				mountTip.visible = false;
			}
			if (commonTip)
			{
				commonTip.visible = false;
			}
			//
			var extraItemTip:ItemTip;
			for( var i = 0; i < MaxExtraItemTipsCnt; ++i )
			{
				extraItemTip = ExtraItemTips[i] as ItemTip;
				if( extraItemTip ){
					extraItemTip.visible = false;
				}
			}
			
			if (nextSkillTip)
			{
				nextSkillTip.visible = false;
			}
		}

		public function ShowTips( Item:MovieClip , TipsType:int , TipsIdx:int ):void
		{
			//全部关闭显示 调用到哪个再自行显示 
			CloseAll();
			if (Item.parent)
			{
				var pos:Point = new Point  ;
				pos.x = Item.x + Item.width;
				pos.y = Item.y;
				pos = Item.parent.localToGlobal(pos);
				x = pos.x;
				y = pos.y;
			}
			visible = true;
			//ExternalInterface.call("ShowTips",TipsType,TipsIdx ,Item );
		}
		
		//额外物品tips
		public function UpdateExtraItemTips( idx:int, itemData:Object ):void
		{
			if( idx < 0 || idx >= MaxExtraItemTipsCnt ){
				return;
			}
			
			var extraItemTip:ItemTip = ExtraItemTips[idx] as ItemTip;
			
			if (null == extraItemTip)
			{
				extraItemTip = new Tips_item();
				if ( extraItemTip == null )
				{
					ExternalInterface.call( "ASTrace", "MyTooltips::configUI could't create ExtraItemTips" );
					return;
				}
				else
				{
					addChild( extraItemTip );
					extraItemTip.name = "extraItemTip"+ idx;
					extraItemTip.x = itemTip.x + itemTip.TipWidth;
					extraItemTip.y = itemTip.y;
					extraItemTip.visible = false;
				}
				
				ExtraItemTips[idx] = extraItemTip;
			}
			
			extraItemTip.updateData( itemData );
		}
		public function SetExtraItemTipsPosX( posX:int ):void
		{
			var curPos:int = posX;

			var extraItemTip:ItemTip;
			for( var i = 0; i < MaxExtraItemTipsCnt; ++i )
			{
				extraItemTip = ExtraItemTips[i] as ItemTip;
				if( extraItemTip ){
					extraItemTip.x = curPos;
					curPos += extraItemTip.TipWidth;
				}
			}
		}
		public function SetExtraItemTipsPosY( posY:int ):void
		{
			var extraItemTip:ItemTip;
			for( var i = 0; i < MaxExtraItemTipsCnt; ++i )
			{
				extraItemTip = ExtraItemTips[i] as ItemTip;
				if( extraItemTip ){
					extraItemTip.y = posY;
				}
			}
		}
		public function GetExtraItemTipsWidth():int
		{
			var maxWidtht:int = 0;
			
			var extraItemTip:ItemTip;
			for( var i = 0; i < MaxExtraItemTipsCnt; ++i )
			{
				extraItemTip = ExtraItemTips[i] as ItemTip;
				if( extraItemTip && extraItemTip.visible ){
					maxWidtht += extraItemTip.TipWidth;
				}
			}
			
			return maxWidtht;
		}
		public function GetExtraItemTipsHeight():int
		{
			var maxHeight:int = 0;
			
			var extraItemTip:ItemTip;
			for( var i = 0; i < MaxExtraItemTipsCnt; ++i )
			{
				extraItemTip = ExtraItemTips[i] as ItemTip;
				if( extraItemTip && extraItemTip.visible ){
					maxHeight = ( maxHeight > extraItemTip.TipHeight ? maxHeight :  extraItemTip.TipHeight );
				}
			}
			
			return maxHeight;
		}
		//
		private function TestCompare()
		{var itemData:ItemTipData = new ItemTipData  ;
			itemData.Id = 1;
			itemData.ItemName = "匕首";
			itemData.IconName = "MMO_Weapons_Z_Icon.W_Z_2h_l01";
			itemData.PartName = "手部";
			itemData.IsEquiped = true;
			itemData.Bind="已绑定";
			itemData.ColorName = "lv3";
			itemData.Profession = "刺客";
			itemData.Power = "50000";
			itemData.ItemLevel = " <font color = '#00ff00'>10</font>";
			itemData.RequireLevel = "<font color = '#ffffff'>物品等级：20</font>";

			itemData.MainParameter = "<p><font>最小物理攻击：90-99</font></p>";
			itemData.MainParameter +=  "<p><font>力量：99</font></p>";
			itemData.MainParameter +=  "<p><font>速度：99</font></p>";
			itemData.MainParameter +=  "<p><font>耐力：99</font></p>";
			itemData.bUnIdentified = true;
			/*itemData.RandomParameter = "<p><font>随机属性</font></p>";
			itemData.RandomParameter +=  "<p><font>随机属性</font></p>";
			itemData.RandomParameter +=  "<p><font>随机属性</font></p>";*/
			itemData.EnhanceParameter = "<p><font>速度+5</font></p>";
			itemData.EnhanceParameter +=  "<p><font>力量+5</font></p>";
			itemData.EnhanceParameter +=  "<p><font>攻击+5</font></p>";
			itemData.EnhanceParameter +=  "<p><font>防御+5</font></p>";
			itemData.EnhanceParameter +=  "<p><font>强化+5</font></p>";
			itemData.EnhanceParameter +=  "<p><font>智力+5</font></p>";
			itemData.WeightParameter="<p><font>负重+5</font></p>";
			itemData.LuckyParameter = "<font >幸运+1</font>";
			itemData.bShowSuit = false;
			itemData.SuitParameter = "<p><font  >6件：最大物理攻击 200%</font></p><p><font  >牛</font></p><p><font  >牛B铠甲</font></p><p><font  >牛护腿</font></p><p><font  >牛护手</font></p><p><font  >牛拖鞋</font></p>";
			itemData.SuitParameter +=  "<p><font  >2件套装：牛A +100</font></p><p><font  >3件套装：牛B +200</font></p><p><font  >5件套装：牛C +300</font></p>";

			//itemData.SoulParameter = "<font >毁天灭地</font>";
			//itemData.SoulIconName = "img://MMO_UIIcon.icon.blank";
			//itemData.GemParameter = "<font >毁天灭地1</font>";
			//itemData.GemIconName = "img://MMO_UIIcon.icon.blank";
			itemData.ShowSkill = true;
			//itemData.SkillSlotCnt = "<p><font>铭文孔数：</font><font color = '#00ff00'>1/5</font></p>";
			itemData.SkillName = new Array();
			itemData.SkillName.push("惊天动地");
			itemData.SkillIconName = new Array();
			itemData.SkillIconName.push("0.TGA");
			itemData.SkillDesc = new Array();
			itemData.SkillDesc.push("铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述铭文描述");
			
			itemData.ShowSoul = false;
			itemData.SoulName = new Array();
			itemData.SoulName.push("<font color = '#ffff00'>力量+100</font>");
			itemData.SoulName.push("<font color = '#ff0000'>未镶嵌的红色孔</font>");
			itemData.SoulIconType = new Array();
			itemData.SoulIconType.push("soul2");
			itemData.SoulIconType.push("soul1");
			itemData.SoulIconName = new Array();
			//itemData.SoulIconName.push("1.TGA");
			itemData.SoulIconName.push("");
			itemData.SoulIconName.push("");
			
			itemData.WeatherParameter = "打雷了";
			itemData.AddParameter = "我是说明物品的";
			itemData.SignParameter = "<font >已被<font color = '#00ff00'>犀利哥</font>签名</font>";
			itemData.Duration = "<font  >99/100</font>";
			//itemData.Price = "9999";
			itemData.ExpireTime = "1987-10-19";
			itemData.Damage = 1000;
			itemData.Life = 5000;
			itemData.ForbidSell="";
			//itemData.MoneType = "gold";
			itemData.Money = "1<IMG  SRC='img://MMO_UIIcon.MoneyIcon.MoneyGold_S'>";
			itemData.ForbidDecompose = "<font color = '#ff0000'>禁止分解</font>";
			itemData.ForbidTrade = "<font color = '#ff0000'>禁止交易</font>";
			itemData.bShowItemEffect = false;
			itemData.ReputationText = "omg\nomg";
			
			UpdateExtraItemTips( 0, itemData );
			SetExtraItemTipsPosX( itemTip.x + itemTip.TipWidth );
			//testItem.updateData(itemData);
		}
		public function TestMainItemTip():void
		{var itemData:ItemTipData = new ItemTipData  ;
			itemData.IsCompare = false;
			itemData.Id = 1;
			itemData.ItemName = "奔雷头盔";
			itemData.IconName = "0.TAG";
			itemData.PartName = "<font color='#fff9f2' >头盔</font>";
			itemData.IsEquiped = false;
			itemData.IsEquip = true;
			itemData.Bind="";
			itemData.ColorName = "lv3";
			itemData.Profession = "<p>战士 </p>";
			itemData.Power = "92";
			itemData.ItemLevel = "<p align='left'><font color='#9d9d9d' >物品等级:25级</font></p>"
			itemData.RequireLevel = "需要等级:36级";

			itemData.MainParameter = "<font color='#ffffff' ><p>魔法防御力 25</p></font>";
			itemData.bUnIdentified = false;
			itemData.RandomParameter = "<p align='left'><font color='#1eff00' >生命上限+24</font></p><p align='left'><font color='#1eff00' >体质+40</font></p>";
			itemData.EnhanceParameter = "<p align='left'><font color='#C7B377' >强化等级: </font><font color='#1eff00' >神龙纹+10</font></p><font color='#71d5ff' >生命上限+15%</p><br></p></font>";
			itemData.LuckyParameter = "";
			
			itemData.bShowSuit = true;
			itemData.SuitParameter = "<p align='left'><font color='#ffd100' >战士意志( 2/7 )</font></p><p align='left'><font color='#fff468' >奔雷头盔</font></p><p align='left'><font color='#fff468' >暗金肩甲</font></p><p align='left'><font color='#9d9d9d' >屠魔战甲</font></p><p align='left'><font color='#9d9d9d' >龙鳞腿甲</font></p><p align='left'><font color='#9d9d9d' >破魂腰带</font></p><p align='left'><font color='#9d9d9d' >雷霆腕甲</font></p><p align='left'><font color='#9d9d9d' >风雷战靴</font></p><p align='left'><font color='#fff468' >2件:生命上限+120</font></p><p align='left'><font color='#9d9d9d' >4件:物理暴击率+3%</font></p><p align='left'><font color='#9d9d9d' >7件:暴击伤害倍率+20%</font></p>";

			//itemData.SoulParameter = "<font >毁天灭地</font>";
			//itemData.SoulIconName = "img://MMO_UIIcon.icon.blank";
			//itemData.GemParameter = "<font >毁天灭地1</font>";
			//itemData.GemIconName = "img://MMO_UIIcon.icon.blank";
			itemData.ShowSkill = false;/*
			itemData.SkillSlotCnt = "<p><font>铭文孔数：</font><font color = '#00ff00'>1/5</font></p>";
			itemData.SkillName = new Array();
			itemData.SkillName.push("惊天动地");
			itemData.SkillIconType = new Array();
			itemData.SkillIconType.push("Slot0");
			itemData.SkillIconName = new Array();
			itemData.SkillIconName.push("0.TGA");
			*/
			itemData.ShowSoul = true;
			itemData.SoulName = new Array();
			itemData.SoulName.push("<font color = '#ffff00'>力量+100</font>");
			itemData.SoulName.push("<font color = '#ff0000'>未镶嵌的红色孔</font>");
			itemData.SoulIconType = new Array();
			itemData.SoulIconType.push("soul2");
			itemData.SoulIconType.push("soul1");
			itemData.SoulIconName = new Array();
			//itemData.SoulIconName.push("1.TGA");
			itemData.SoulIconName.push("");
			itemData.SoulIconName.push("");
			
			itemData.WeatherParameter = "";
			itemData.AddParameter = "<font color='#ffffff' >以英雄之名，予你强者的护持。大匠师倾力打造的圣盔，如天魔临世，势不可挡。</p><br></p>";
			itemData.SignParameter = "";
			itemData.Duration = "<font color='#ffe599' >耐久:</font><p align='left'><font color='#ffe599' >21/150</font></p>";
			itemData.ExpireTime = "";
			itemData.Damage = 0;
			itemData.Life = 0;
			itemData.ForbidSell="";
			itemData.Money = "<font color='#ffe599' >回收价:</font>2160<IMG  SRC='img://MMO_UIIcon.MoneyIcon.MoneyGold_S'/>";
			itemData.ForbidDecompose = "";
			itemData.ForbidTrade = "";
			itemData.bShowItemEffect = false;
			itemData.ReputationText = "";
			
			itemTip.updateData( itemData );
			//testItem.updateData(itemData);
		}
	}
}//代码里把tips.visible设true