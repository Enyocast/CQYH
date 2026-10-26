/********************************************************************
Created:2013/04/17
Filename: SkillTipData
file ext:as
Author:hemu@snda
Purpose:Tips系统View SkillTipData数据包
*********************************************************************/

package ActionScript3.Tips
{

	public class SkillTipData extends Object
	{
		public var Id:int;
		public var IsNext:Boolean;
		public var SkillName:String;
		public var SkillLevel:String;  //等级要颜色？没问题
		public var IconName:String;
		public var SkillCost:String;
		public var CDTime:String; 		//装备类型 Wired
		public var SkillUnlock:String;
		
		public var SkillDescribe:String;
		
		public var HasRune:Boolean;
		public var RuneId:int;
		//tf_RuneName
		public var RuneName:String;
		//tf_RuneDescribe
		public var RuneDescribe:String;
		public var RuneLev:String;
		
		public var SkillDamage:String;
		
		public var SkillAid:String;
 		public var HasUpLevNeed:Boolean;
		public var UpLevNeedSoul:String;
		public var UpLevNeedLev:String;
	}

}