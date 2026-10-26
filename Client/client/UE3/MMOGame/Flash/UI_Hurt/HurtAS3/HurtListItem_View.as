package UI_Hurt.HurtAS3 {
	
	import scaleform.clik.controls.ListItemTreeRenderer;
	import UI_Hurt.HurtAS3.HurtItemData;
	import flash.text.TextField;
	
	
	public class HurtListItem_View extends ListItemTreeRenderer {
		
		public var txt_skill_name:TextField;
		public var txt_skill_hurt:TextField;
		public var txt_value:TextField;
		
		public function HurtListItem_View() {
			
		}
		
		override protected function configUI():void
		{
			super.configUI();

			setUpdateDataCallBack(updateData);
		}
		
		function updateData(data:Object):void
		{	
		    var itemData:HurtItemData = data as HurtItemData;
			if(itemData != null)
			{
				visible = true;
				txt_skill_name.text = itemData.RankID+"    "+itemData.SkillName;
				txt_skill_hurt.text = itemData.SkillHurt.toString();
				txt_value.text = itemData.SkillHurtValue;
			}
			else
			{
				visible = false;
			}
			
		}	
	}
	
}
