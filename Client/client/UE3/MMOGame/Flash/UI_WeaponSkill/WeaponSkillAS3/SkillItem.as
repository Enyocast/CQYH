package UI_WeaponSkill.WeaponSkillAS3 {
	
	import flash.display.MovieClip;
	import flash.text.TextField;
	import ActionScript3.ItemSlot.MyItemSlot;
	
	
	public class SkillItem extends MovieClip {
		
		public var txt_name:TextField;
		public var txt_dec:TextField;
		public var slot:MyItemSlot;

		public var count:int=50;
		public var isEffect:Boolean=false;
		public function SkillItem() {
			slot.DisableDrag = true;
		}
		
		public function setData(dat:WeaponSkillData):void
		{
			//onComplete();
			txt_name.text=dat.skillName;
			txt_dec.condenseWhite=true;
			txt_dec.htmlText=dat.skillDec;
			if(txt_dec.numLines>1)
			{
				txt_dec.y=20;
			}
			else
			{
				txt_dec.y=38;
			}
			slot.SetSlotType(dat.tipsType);
			slot.SetData(0,dat.iconName,dat.skillID,"",1,-1,-1);
		}
		
	}
	
}
