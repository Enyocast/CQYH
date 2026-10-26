package UI_EquipEnhance.EquipEnhanceAS3{
	
	public class EquipSlotPropertyData extends Object
	{
		//当前等级
		public var CurLevel:int;
		public var LevelDesc:String;
		public var ShotDesc:String;
		public var Quality:int;
		//最高等级
		public var MaxLevel:int;
		//图标文件路径
		public var IconPath:String;
		//装备部位名称
		public var EquipSlotName:String;
		//5个属性名
		public var EquipEnhanceProperty0_0:String;
		public var EquipEnhanceProperty0_1:String;
		public var EquipEnhanceProperty0_2:String;
		public var EquipEnhanceProperty0_3:String;
		public var EquipEnhanceProperty0_4:String;
		//当前等级属性增强的数值
		public var EquipEnhanceEffect_0_0:String;
		public var EquipEnhanceEffect_0_1:String;
		public var EquipEnhanceEffect_0_2:String;
		public var EquipEnhanceEffect_0_3:String;
		public var EquipEnhanceEffect_0_4:String;
		//是否还可以升级
		public var CanEnhance:Boolean;
		//下一级属性增强的数值
		public var EquipEnhanceProperty1_0:String;
		public var EquipEnhanceProperty1_1:String;
		public var EquipEnhanceProperty1_2:String;
		public var EquipEnhanceProperty1_3:String;
		public var EquipEnhanceProperty1_4:String;
		
		public var EquipEnhanceEffect_1_0:String;
		public var EquipEnhanceEffect_1_1:String;
		public var EquipEnhanceEffect_1_2:String;
		public var EquipEnhanceEffect_1_3:String;
		public var EquipEnhanceEffect_1_4:String;
		//升到顶级的文字描述
		public var EnhanceDesc:String;
		//深渊币
		//public var MoneyCost_0:int;
		//金币
		//public var MoneyCost_1:int;
		
		//public var MoneyType:int;
		public var MoneyCostHtml:String;
		
		public var MoneyDescText:String;
		public var NextEnhcLevelHint:String="";
		
		public var EnhcClass:int;

		public function EquipSlotPropertyData() {
			// constructor code
		}
		
		
		public function GetCurrentDescExt_0():String
		{
			var Ret:String = "";
			if( EquipEnhanceProperty0_0 != null && EquipEnhanceProperty0_0 != "" )
			{
				Ret = EquipEnhanceProperty0_0;
			}
			return Ret;
		}
		
		public function GetCurrentDescExt_1():String
		{
			var Ret:String = "";
			if( EquipEnhanceProperty0_1 != null && EquipEnhanceProperty0_1 != "" )
			{
				Ret = EquipEnhanceProperty0_1;
			}
			return Ret;
		}
		
		public function GetCurrentDescExt_2():String
		{
			var Ret:String = "";
			if( EquipEnhanceProperty0_2 != null && EquipEnhanceProperty0_2 != "" )
			{
				Ret = EquipEnhanceProperty0_2;
			}
			return Ret;
		}
		
		public function GetNextDescExt_0():String
		{
			var Ret:String = "";
			if( EquipEnhanceProperty1_0 != null && EquipEnhanceProperty1_0 != "" )
			{
				Ret = EquipEnhanceProperty1_0;
			}
			return Ret;
		}
		
		public function GetNextDescExt_1():String
		{
			var Ret:String = "";
			if( EquipEnhanceProperty1_1 != null && EquipEnhanceProperty1_1 != "" )
			{
				Ret = EquipEnhanceProperty1_1;
			}
			return Ret;
		}
		
		public function GetNextDescExt_2():String
		{
			var Ret:String = "";
			if( EquipEnhanceProperty1_2 != null && EquipEnhanceProperty1_2 != "" )
			{
				Ret = EquipEnhanceProperty1_2;
			}
			return Ret;
		}
		

	}
	
}
