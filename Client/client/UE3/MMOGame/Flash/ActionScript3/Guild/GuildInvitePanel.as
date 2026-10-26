//
// 家族总揽
//
package ActionScript3.Guild
{
	import flash.external.ExternalInterface;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.text.TextField;
	import scaleform.clik.controls.TextInput;

	public class GuildInvitePanel extends BaseGuildInput
	{
		override protected function configUI():void
		{
			super.configUI();
			this.SetWindowTitle("招募会员");
			txt_name.textField.addEventListener(KeyboardEvent.KEY_UP, onInputOver, false, 0, true);
		}
		override protected function onBtClickOk(evt:MouseEvent):void
		{
			ExternalInterface.call("ASInviteMember", txt_name.text);
			onBtClickClose(null);
		}
		
		public function show():void
		{
			txt_name.textField.maxChars=12;
			updateTextFormat(true);
			txt_name.defaultText="(最多8个汉字)";
		}
		
		protected function onInputOver(event:KeyboardEvent):void 
		{            
            var control:TextInput = event.target.parent as TextInput;
			for (var i=0; i < control.text.length; ++ i)
			{
				var code:uint = control.text.charCodeAt(i);
				// 数字
				if (code >= 48 && code <= 57)
				{
					continue;
				}
			
				// 小写字母
				if (code >= 97 && code <= 122)
				{
					continue;
				}
			
				// 大写字母
				if (code >= 65 && code <= 90)
				{
					continue;
				}
			
				// 汉字
				if (code >= 19968 && code <= 40869)
				{
					continue;
				}
			
				if (code >= 63744 && code <= 64045)
				{
					continue;
				}
				
				ExternalInterface.call("ASInputError");
				control.text = control.text.substr(0, i);
				break;
			}
        }
	}
}


























