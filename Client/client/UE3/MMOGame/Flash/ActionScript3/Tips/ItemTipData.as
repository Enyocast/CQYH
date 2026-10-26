/********************************************************************
Created:2013/04/17
Filename: ItemTipData
file ext:as
Author:hemu@snda
Purpose:Tips系统View ItemTipData数据包
*********************************************************************/

package ActionScript3.Tips
{

	public class ItemTipData extends Object
	{
		public var Id:int;
		public var IsEquip:Boolean;
		public var ItemName:String;
		public var IconName:String;
		public var PartName:String; 		//装备类型 Wired
		public var ItemLevel:String;
		public var RequireLevel:String;
		public var IsEquiped:Boolean;
		public var RepairState:String;
		public var ColorName:String;
		public var Profession:String; 
		public var Power:String;
		public var Bind:String;
		public var Gender:String;
		public var IsCompare:Boolean;
		
		public var MainParameter:String;
		public var RandomParameter:String; 			//随机属性
		public var EnhanceParameter:String; 		//强化属性
		public var LuckyParameter:String; 			//幸运值属性
		public var AddParameter:String;
		public var WeightParameter:String;//负重属性
		public var PurityParameter:String="";//纯度（矿石特有）
		public var ShowSkill:Boolean;
		//public var SkillSlotCnt:String;				//铭文
		public var SkillDesc:Array=[];	//铭文描述
		public var SkillIconName:Array=[];//铭文图片
		public var SkillName:Array=[];//铭文名称
		public var ShowSoul:Boolean;
		public var SoulIconName:Array;				//容灵数据
		public var SoulIconType:Array;
		public var SoulName:Array;
		public var bShowSuit:Boolean;
		public var SuitParameter:String;			//套装
		public var WeatherParameter:String;         //天气
		public var SignParameter:String;			//签名
		public var ReputationText:String;			//商店出售时信息
		public var bUnIdentified:Boolean;

		public var Duration:String;
		//public var Price:String;
		public var ExpireTime:String;
		public var Damage:int;
		public var Life:int;
		public var Money:String;
		public var ForbidTrade:String;
		public var ForbidSell:String;
		public var ForbidDecompose:String;
		public var bShowItemEffect:Boolean;
		
		public var unIdentifiedText:String;
		
		public var LevelUpPoint:String="";//升级点数
		public var IsGotten:String="";//是否学习该技能
	}

}