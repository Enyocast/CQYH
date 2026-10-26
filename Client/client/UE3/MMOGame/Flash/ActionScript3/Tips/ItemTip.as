/********************************************************************
Created:2013/04/18
Filename: ItemTip
file ext:as
Author:hemu@snda
Purpose:Tips系统View ItemTip控件
*********************************************************************/

package ActionScript3.Tips
{

	import ActionScript3.MyPanel;
	import ActionScript3.Tips.SuitAttribute;
	import flash.external.ExternalInterface;

	public class ItemTip extends MyPanel
	{
		public var mainItem:MainItem;
		public var suitAdd:SuitAttribute;
		public var TipData:ItemTipData;
        //public var testItem:BaseTips;
		public var TipHeight:int = 0;
		public var TipWidth:int = 0;

		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren=false;
			this.mouseEnabled=false;
			//Test();
			//Test2();
		}
		
/*		private function TestItem():void
		{
			var itemData:ItemTipData = new ItemTipData  ;
			itemData.Id = 1;
			itemData.ItemName = "匕首";
			itemData.IconName = "MMO_Weapons_Z_Icon.W_Z_2h_l01";
			itemData.PartName = "手部";
			itemData.ItemLevel = " <font color = '#00ff00'>10</font>";
			itemData.RequireLevel = "<font color = '#ffffff'>物品等级：20</font>";
			itemData.AddParameter = "我是说明物品的";
			mainItem.updateData( itemData );
		}
		*/
/*		private function Test():void
		{
			var itemData:ItemTipData = new ItemTipData  ;
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
			mainItem.updateData( itemData );
			//testItem.updateData(itemData);
		}*/
		
/*		private function Test2()
		{
			var itemData:ItemTipData = new ItemTipData  ;
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

			itemData.ShowSkill = false;
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
			mainItem.updateData( itemData );
			//testItem.updateData(itemData);
		}*/
		
		public function updateData( itemData:Object ):void
		{
			TipData = itemData as ItemTipData;
			if (null != TipData)
			{
				visible = true;
				mainItem.updateData(itemData);
				var res:int = mainItem.GetAddSuitStartY(suitAdd.GetHeight());
				if (! TipData.IsCompare && res > 0)
				{
					suitAdd.SetData(TipData.SuitParameter);
					suitAdd.y = res;
				}
				else
				{
					suitAdd.visible = false;
				}

				TipHeight = mainItem.TipHeight;
				TipWidth = suitAdd.visible ? suitAdd.TipWidth + mainItem.TipWidth:mainItem.TipWidth;
				ExternalInterface.call( "ASTrace", "TipData suitAdd.TipWidth:"+suitAdd.TipWidth + "TipData MainItem.TipWidth" + mainItem.TipWidth
									   + "TipWidth:" + TipWidth);
			}
			else
			{
				visible = false;
			}
		}
	}
}