package ActionScript3.Master 
{
	import ActionScript3.MyPanel;
	import scaleform.clik.controls.TextArea;
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	
	public class CongratulatePanel extends MyPanel
	{
		public var present0:CongratulateComponet;
		public var present1:CongratulateComponet;
		public var present2:CongratulateComponet;
		public var congratulation_content:TextArea;
		public var tF_ConHint:TextField;
		public var  aimRoleID:int = 0;
		
		override protected function configUI():void
		{
			ShowMode="BC";
			super.configUI();
			present0.congratulation_mc.addEventListener(MouseEvent.CLICK, onConfirmCongratulation1 );
			present1.congratulation_mc.addEventListener(MouseEvent.CLICK, onConfirmCongratulation2 );
			present2.congratulation_mc.addEventListener(MouseEvent.CLICK, onConfirmCongratulation3 );
		}
		
		private function onConfirmCongratulation1(evt:MouseEvent):void
		{
			 ExternalInterface.call("ASSendCongratulation",present0.dataCong.nType,aimRoleID,congratulation_content.text);
		}
		private function onConfirmCongratulation2(evt:MouseEvent):void
		{
			 ExternalInterface.call("ASSendCongratulation",present1.dataCong.nType,aimRoleID,congratulation_content.text);
		}
		private function onConfirmCongratulation3(evt:MouseEvent):void
		{
			 ExternalInterface.call("ASSendCongratulation",present2.dataCong.nType,aimRoleID,congratulation_content.text);
		}
		
		public function UCSetTargetName(strTarget:String,strCong:String):void
		{
			congratulation_content.text = strCong;
			tF_ConHint.text = strTarget;
		}
		public function UCSetWindowContent(dat:Array,nRoleID:int):void
		{
			if(dat != null)
			{
				aimRoleID = nRoleID;
				for(var n:int = 0; n < 3&&n < dat.length; ++n)
				{
					if(n == 0)
						present0.SetData(dat[n]);
					else if(n == 1)
						present1.SetData(dat[n]);
					else
						present2.SetData(dat[n]);
				}
			}
		}
	}
}
