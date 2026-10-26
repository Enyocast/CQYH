/********************************************************************
	Created:	2013/03/27
	Filename: 	StudentDetailData
	file ext:	as
	Author:		hemu@snda
	Purpose:	师徒系统View StudentDetailData数据包
*********************************************************************/

package ActionScript3.Master{
	
	public class MasterInfoListItemData extends Object
	{
		public var Id:int;
		public var Name:String;
		public var Level:int;
		public var ProfessionId:int;
		public var Profession:String;
		public var CanCongratulate:Boolean;
		public var CongratulateType:String;
		public var bMaster:Boolean;
		public var congCount:int;
		public var exp:int;//奖励经验
		public var gold:int;//奖励金币
		public var MasterValue:int;//名师值
		//暂时留着 可用作以后的标记已经出师徒弟
		public var nState:int;//0是没有达到出师条件  1是达到了出师条件  2 申请出师
		public var bLeaveMaster:Boolean;
		public var bSelfReward:Boolean; //已经出师的徒弟变成了师傅
	}
}