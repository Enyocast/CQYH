package UI_EquipLevelUp.AS3
{
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	
	import ActionScript3.MyPanel;
	
	import scaleform.clik.managers.PopUpManager;
	
	public class MessageBox_Upgrade extends MyPanel
	{
		public var message_box_text:MessageBox_Text;
		public var message_box_list:MessageBox_List;
		
		private static const RESULT_TYPE_SUCCESS:int = 0;
		private static const RESULT_TYPE_FAILURE:int = 1;
		private static const RESULT_TYPE_BROKEN:int  = 2;
		
		private var _resultData:UpgradeResultData;
		
		public function MessageBox_Upgrade()
		{
			super();
		}
		
		override protected function configUI():void
		{
			super.configUI();
			message_box_text.visible = false;
			message_box_list.visible = false;
			message_box_text.btn_confirm.addEventListener(MouseEvent.CLICK, onConfirmMessage);
			message_box_list.btn_confirm.addEventListener(MouseEvent.CLICK, onConfirmMessage);
			
			ExternalInterface.call( "RegisteMutiLineMsgBox", this );
		}
		
		override public function OnFocusGained():void
		{
			super.OnFocusGained();
			//(parent as MoviePlayer_WeaponUpgrade).setPanelToTop(this);
		}
		
		private function onConfirmMessage(evt:MouseEvent)
		{
			message_box_text.visible = false;
			message_box_list.visible = false;
			ExternalInterface.call("ASConfirmMessage");
		}
		
		public function UCSetUpgradeResultData(data:UpgradeResultData = null):void
		{
			_resultData = data;
			if(_resultData == null){
				return;
				//test
				//_resultData = getTestUpgradeResultData();
			}
			var resultType:int = _resultData.resultType;
			switch(resultType)
			{
				case RESULT_TYPE_SUCCESS:
				case RESULT_TYPE_FAILURE:
				{
					message_box_text.visible = true;
					message_box_list.visible = false;
					message_box_text.setData(_resultData);
					break;
				}
				case RESULT_TYPE_BROKEN:
				{
					message_box_text.visible = false;
					message_box_list.visible = true;
					message_box_list.setData(_resultData);
					break;
				}
				default:
				{
					break;
				}
			}
		}
		
		//--------------test
		private function getTestUpgradeResultData():UpgradeResultData
		{
			var resultData:UpgradeResultData = new UpgradeResultData();
			resultData.resultType = int(Math.random() * 3);
			switch(resultData.resultType)
			{
				case RESULT_TYPE_SUCCESS:
				{
					resultData.messageTitle = "升级成功";
					resultData.messageContent = "雪饮狂刀+1\n武器攻击+99\n武器耐久-2\n幸运+1"
					break;
				}
				case RESULT_TYPE_FAILURE:
				{
					resultData.messageTitle = "升级失败";
					resultData.messageContent = "没有发生任何变化"
					break;
				}
				case RESULT_TYPE_BROKEN:
				{
					resultData.messageTitle = "武器碎裂";
					resultData.compensationMaterialList = new Array();
					var itemData:UpgradeCompensationItemData;
					for(var i:int = 0; i < 5; i++)
					{
						itemData = new UpgradeCompensationItemData();
						itemData.materialInfo = "低级装备精华 x 3";
						itemData.materialSrc = "0.tga";
						resultData.compensationMaterialList.push(itemData);
					}
					break;
				}
				default:
				{
					break;
				}
			}
			return resultData;
		}
	}
}