package UI_SkillTree.SkillTreeAS3
{
	import flash.display.MovieClip;
	
	import scaleform.clik.core.UIComponent;

	public class AllActiveSkillsListView extends UIComponent
	{
		public var scrollingBg_mc:MovieClip;
		private const GROUP_MARGIN_Y:Number = 18;
		private var _skillsItemGroup:Vector.<ActiveSkillListItem>;
		private var _data:Array;
		private var _origPosY:Number;
		private var _prevHeight:Number;
		
		public function AllActiveSkillsListView()
		{
			super();
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			_origPosY = this.y;
		}
		
		internal function resetPosition():Boolean
		{
			if(_prevHeight != height){
				this.y = _origPosY;
				return true;
			}
			return false;
		}
		
		internal function updateData(data:Array):void
		{
			_prevHeight = height;
			_data = data;
			if(_data == null){
				visible = false;
				return;
			}
			visible = true;
			var dataLen:int = _data.length;
			validItemGroupInstance(dataLen);
			var listItemData:ActiveSkillListItemData;
			var posY:Number = GROUP_MARGIN_Y * 0.5;
			for(var i:int = 0; i < dataLen; i++)
			{
				listItemData = data[i] as ActiveSkillListItemData;
				_skillsItemGroup[i].updateData(listItemData);
				_skillsItemGroup[i].y = posY;
				posY += _skillsItemGroup[i].height + GROUP_MARGIN_Y;
			}
			scrollingBg_mc.height =  height = posY - GROUP_MARGIN_Y * 0.5;
		}
		
		private function validItemGroupInstance(dataLen:int):void
		{
			if(_skillsItemGroup == null){
				_skillsItemGroup = new Vector.<ActiveSkillListItem>();
			}
			var numOfGroup:int = _skillsItemGroup.length;
			if(numOfGroup < dataLen){
				_skillsItemGroup.length = numOfGroup;
				for(var i:int = numOfGroup; i < dataLen; i++)
				{
					_skillsItemGroup[i] = new ActiveSkillListItem();
					addChild(_skillsItemGroup[i]);
				}
			}else if(numOfGroup > dataLen){
				for(i = dataLen; i < numOfGroup; i++)
				{
					_skillsItemGroup[i].visible = false;
				}
			}
		}
		
	}
}