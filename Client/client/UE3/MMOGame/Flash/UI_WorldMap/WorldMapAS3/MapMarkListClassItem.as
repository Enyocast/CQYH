package UI_WorldMap.WorldMapAS3
{
	import flash.display.MovieClip;	
	import flash.text.TextField;
	import ActionScript3.TreeListData;
	import ActionScript3.controls.StateUIComponent;
	
	public class MapMarkListClassItem extends StateUIComponent 
	{
		public var className_tf:TextField;
		//public var unfold_mc:MovieClip;
		
		public var listClassData:TreeListData;
		override protected function configUI():void
		{
			super.configUI();	
		}
		public function updateData(data:Object):void
		{
			listClassData = data as TreeListData;
			
			if( listClassData ){
				visible = true;
				className_tf.text = listClassData.label;
				if (data.type == TreeListData.C_Type_Branch_Closed)
				{
					this.selected = false;
				}
				else
				{
					this.selected = true;
				}
			}
		}
	}
}

