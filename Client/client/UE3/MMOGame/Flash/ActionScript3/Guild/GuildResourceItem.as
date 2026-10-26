//
// 家族资源项
//
package ActionScript3.Guild
{
	import scaleform.clik.core.UIComponent;
	import flash.display.MovieClip;
	import scaleform.clik.controls.ListItemTreeRenderer;	
	import flash.text.TextField;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	
	public class GuildResourceItem extends UIComponent 
	{	
		public var guild_res_icon_mc:MovieClip;
		public var guild_res_name_tf:TextField;
		public var guild_res_num_tf:TextField;
		
		public function GuildResourceItem()
		{
			// constructor code
		}
		
		override protected function configUI():void
		{
			super.configUI();
			
			guild_res_icon_mc.source = null;
			guild_res_name_tf.text = "";
			guild_res_num_tf.text = "";
		}
	}
}
























