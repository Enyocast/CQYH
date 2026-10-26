package ActionScript3.RankList {
	
	public class BaseRankItemData {

		public var Id:int;//角色ID
		public var RankIndex:String;// 角色排名
		public var OnLine:Boolean;//是否在线
		public var RoleName:String;//角色名称
		public var Job:String;//角色职业
		public var GuildName:String;//公会名称
		public var Level:String;//玩家等级
		public var Ranking:int; // 0无变化 1下降 2上升 排名变化
		public var IsPlayer:Boolean=false;//是否自己

	}
	
}
