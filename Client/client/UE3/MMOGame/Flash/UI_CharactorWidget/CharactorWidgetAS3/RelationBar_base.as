package UI_CharactorWidget.CharactorWidgetAS3
{
	import scaleform.clik.core.UIComponent;
	import flash.text.TextField;

	public class RelationBar_base extends UIComponent
	{
		public var RelationBar_fill_mc:RelationBar_fill_base;
		public var Number_txt:TextField;
		
		override protected function configUI():void
		{
			super.configUI();
		}
		
		public function UpdateData(dat:Object)
		{
			if(RelationBar_fill_mc){
				RelationBar_fill_mc.UpdateData(dat);
				if(dat){
					Number_txt.text = (dat.curReputation-dat.minReputation)+"/"+(dat.maxReputation-dat.minReputation);
				}
				else
				{
					Number_txt.text = "";
				}
			}
		}
	}
}