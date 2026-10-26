package UI_DamageLevel.DamageLevelAS3 {
	
	import ActionScript3.MyDamageNumber;
	import flash.utils.getDefinitionByName;
	import flash.display.MovieClip;
	import scaleform.clik.core.UIComponent;

	public class MyAttackDamage extends MyDamageNumber {

		override public function RemoveAll( Parent:UIComponent):void
		{
			if (removeEnable)
			{
				if (gObj)
				{
					gObj.uiObj = null;
				}
				clearNumber();
				NumType=0;
				TxtType=0;
				gObj = null;
				Parent.removeChild(this);
			}
			else
			{
				visible = false;
				isVisible=false;
			}
		}
		
	    override public function clearNumber():void
		{
			if(attack_mc)
			{
				attack_mc.x=0;
				var l:int=attack_mc.numChildren;
				for each(var i:MovieClip in attack_mc)
				{
					i.visible=false;
				}
			}
		}
	}
	
}
