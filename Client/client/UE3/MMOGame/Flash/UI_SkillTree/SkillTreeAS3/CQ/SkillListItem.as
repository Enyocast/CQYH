package UI_SkillTree.SkillTreeAS3.CQ
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	
	import ActionScript3.Common.Utils.StyleType;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	import UI_SkillTree.SkillTreeAS3.ActiveSkillListItemSingleData;
	import UI_SkillTree.SkillTreeAS3.ActiveSkillsListItemInscription;
	
	import scaleform.clik.controls.ListItemRenderer;
	
	public class SkillListItem extends ListItemRenderer
	{
		public var skillName_tf:TextField;
		public var level_tf:TextField;
		public var exp_tf:TextField;
		public var skill_slot_mc:MyItemSlot;
		public var inscription_sign_mc:ActiveSkillsListItemInscription;
		
		public function SkillListItem()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			this.mouseEnabled = true;
			this.mouseChildren = true;
			skill_slot_mc.DisableDrag = false;
			inscription_sign_mc.visible = false;
			
			inscription_sign_mc.mouseEnabled = true;
			inscription_sign_mc.addEventListener(MouseEvent.ROLL_OVER, handleRollOverInscriptionSign);
			inscription_sign_mc.addEventListener(MouseEvent.ROLL_OUT, handleRollOutInscriptionSign);
		}
		
		override public function setData(data:Object):void
		{
			super.setData(data);
			var singleItemData:ActiveSkillListItemSingleData = data as ActiveSkillListItemSingleData;
			if(singleItemData != null){
				this.visible = true;
				skillName_tf.text = singleItemData.SkillName;
				level_tf.text = singleItemData.SkillLv.toString();
				exp_tf.text = singleItemData.SkillExp;
				skill_slot_mc.SlotType = singleItemData.SlotType;
				skill_slot_mc.SetData(0, singleItemData.SkillIconName, singleItemData.SkillID, "", 0, -1, -1);
				skill_slot_mc.DisableDrag = singleItemData.IsDisabled;
				//wph@2015-1-30: set SkillInscriptionType to "0" local, only show the fixed rune icon 
				inscription_sign_mc.updateData(singleItemData.RuneSkillID, "0");
				inscription_sign_mc.visible = (singleItemData.RuneSkillID != 0 && !singleItemData.IsDisabled);
				setItemGray(this, singleItemData.IsDisabled);
			}else{
				this.visible = false;
			}
		}
		
		public function setItemGray(mc:MovieClip, gray:Boolean):void
		{
			if (! mc)
			{
				return;
			}
			
			mc.filters = null;
			//update text color
			skillName_tf.textColor = level_tf.textColor = exp_tf.textColor = 0xffffff;
			if (gray)
			{
				mc.filters = [ StyleType.getInstance().getBlackFilter()];
				//update text color
				skillName_tf.textColor = level_tf.textColor = exp_tf.textColor = 0x9d9d9d;
			}
		}
		
		private function handleRollOverInscriptionSign(event:MouseEvent):void
		{
			ExternalInterface.call( "ASShowTips_SkillTreeRuneSkill", inscription_sign_mc);
		}
		
		
		private function handleRollOutInscriptionSign(event:MouseEvent):void
		{
			ExternalInterface.call("ASHideTips_SkillTreeRuneSkill" );
		}
	}
}