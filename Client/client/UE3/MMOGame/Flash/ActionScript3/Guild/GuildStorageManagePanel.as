//
// 家族总揽
//
package ActionScript3.Guild
{
	import flash.display.DisplayObject;
	import flash.external.ExternalInterface;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.getDefinitionByName;

	import scaleform.clik.core.UIComponent;
	import scaleform.clik.constants.InvalidationType;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollBar;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.controls.ListItemRenderer;
	import scaleform.clik.events.ButtonEvent;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.data.TreeDataProvider;
	import scaleform.clik.utils.Padding;
	import scaleform.clik.controls.DropdownMenu;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;

	public class GuildStorageManagePanel extends UIComponent
	{
		public var guild_bank_post_mc:DropdownMenu;
		
		public var guild_bank_input_0_mc:MovieClip;
		public var guild_bank_input_1_mc:MovieClip;
		public var guild_bank_input_2_mc:MovieClip;
		public var guild_bank_input_3_mc:MovieClip;
		public var guild_bank_input_4_mc:MovieClip;
		public var guild_bank_input_5_mc:MovieClip;
		
		public var guild_bank_output_0_mc:MovieClip;
		public var guild_bank_output_1_mc:MovieClip;
		public var guild_bank_output_2_mc:MovieClip;
		public var guild_bank_output_3_mc:MovieClip;
		public var guild_bank_output_4_mc:MovieClip;
		public var guild_bank_output_5_mc:MovieClip;
		
		public var guild_bank_all_mc:MovieClip;
		public var guild_bank_all_input_mc:MovieClip;
		public var guild_bank_all_output_mc:MovieClip;
		
		public var guild_bank_active_0_mc:TextField;
		public var guild_bank_active_1_mc:TextField;
		public var guild_bank_active_2_mc:TextField;
		public var guild_bank_active_3_mc:TextField;
		public var guild_bank_active_4_mc:TextField;
		public var guild_bank_active_5_mc:TextField;
		
		public var guild_bank_tips_tf:TextField;
		
		public var guild_post:int;
		
		override protected function configUI():void
		{
			super.configUI();

			guild_bank_post_mc.dataProvider = new DataProvider();
			guild_bank_post_mc.addEventListener(Event.CHANGE, onChangeSelect);
			guild_bank_post_mc.selectedIndex = 0;
			
			guild_bank_input_0_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			guild_bank_input_1_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			guild_bank_input_2_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			guild_bank_input_3_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			guild_bank_input_4_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			guild_bank_input_5_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			
			guild_bank_output_0_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			guild_bank_output_1_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			guild_bank_output_2_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			guild_bank_output_3_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			guild_bank_output_4_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			guild_bank_output_5_mc.addEventListener(ButtonEvent.CLICK, onToggleClick);
			
			guild_bank_all_mc.addEventListener(ButtonEvent.CLICK, onToggleClickAll);
			guild_bank_all_input_mc.addEventListener(ButtonEvent.CLICK, onToggleClickAllInput);
			guild_bank_all_output_mc.addEventListener(ButtonEvent.CLICK, onToggleClickAllOutput);
			
			guild_bank_post_mc.datastring = "会长=副会长=长老=监事=理事=执事=会员";
			guild_bank_post_mc.SplitData();
			guild_post = 0;
			
			guild_bank_tips_tf.text = "";

		}
		
		function onToggleClick()
		{
			guild_bank_all_mc.selected = false;
			guild_bank_all_input_mc.selected = false;
			guild_bank_all_output_mc.selected = false;
			
			modifyGuildStorageRights();
		}
		
		function onToggleClickAll()
		{
			guild_bank_all_mc.selected = true;
			guild_bank_all_input_mc.selected = false;
			guild_bank_all_output_mc.selected = false;
			
			guild_bank_input_0_mc.selected = true;
			guild_bank_input_1_mc.selected = true;
			guild_bank_input_2_mc.selected = true;
			guild_bank_input_3_mc.selected = true;
			guild_bank_input_4_mc.selected = true;
			guild_bank_input_5_mc.selected = true;
			
			guild_bank_output_0_mc.selected = true;
			guild_bank_output_1_mc.selected = true;
			guild_bank_output_2_mc.selected = true;
			guild_bank_output_3_mc.selected = true;
			guild_bank_output_4_mc.selected = true;
			guild_bank_output_5_mc.selected = true;
			
			modifyGuildStorageRights();
		}
		
		function onToggleClickAllInput()
		{
			guild_bank_all_mc.selected = false;
			guild_bank_all_input_mc.selected = true;
			guild_bank_all_output_mc.selected = false;
			
			guild_bank_input_0_mc.selected = true;
			guild_bank_input_1_mc.selected = true;
			guild_bank_input_2_mc.selected = true;
			guild_bank_input_3_mc.selected = true;
			guild_bank_input_4_mc.selected = true;
			guild_bank_input_5_mc.selected = true;
			
			guild_bank_output_0_mc.selected = false;
			guild_bank_output_1_mc.selected = false;
			guild_bank_output_2_mc.selected = false;
			guild_bank_output_3_mc.selected = false;
			guild_bank_output_4_mc.selected = false;
			guild_bank_output_5_mc.selected = false;
			
			modifyGuildStorageRights();
		}
		
		function onToggleClickAllOutput()
		{
			guild_bank_all_mc.selected = false;
			guild_bank_all_input_mc.selected = false;
			guild_bank_all_output_mc.selected = true;
			
			guild_bank_input_0_mc.selected = false;
			guild_bank_input_1_mc.selected = false;
			guild_bank_input_2_mc.selected = false;
			guild_bank_input_3_mc.selected = false;
			guild_bank_input_4_mc.selected = false;
			guild_bank_input_5_mc.selected = false;
			
			guild_bank_output_0_mc.selected = true;
			guild_bank_output_1_mc.selected = true;
			guild_bank_output_2_mc.selected = true;
			guild_bank_output_3_mc.selected = true;
			guild_bank_output_4_mc.selected = true;
			guild_bank_output_5_mc.selected = true;
			
			modifyGuildStorageRights();
		}
		
		function onChangeSelect(e:Event)
		{
			guild_post = guild_bank_post_mc.selectedIndex;
			ExternalInterface.call("ASUpdateGuildStorageRights", guild_post);
		}
		
		function modifyGuildStorageRights()
		{
			var storage_rights_data:GuildStorageData = new GuildStorageData;
			storage_rights_data.input0 = guild_bank_input_0_mc.selected;
			storage_rights_data.input1 = guild_bank_input_1_mc.selected;
			storage_rights_data.input2 = guild_bank_input_2_mc.selected;
			storage_rights_data.input3 = guild_bank_input_3_mc.selected;
			storage_rights_data.input4 = guild_bank_input_4_mc.selected;
			storage_rights_data.input5 = guild_bank_input_5_mc.selected;
			
			storage_rights_data.output0 = guild_bank_output_0_mc.selected;
			storage_rights_data.output1 = guild_bank_output_1_mc.selected;
			storage_rights_data.output2 = guild_bank_output_2_mc.selected;
			storage_rights_data.output3 = guild_bank_output_3_mc.selected;
			storage_rights_data.output4 = guild_bank_output_4_mc.selected;
			storage_rights_data.output5 = guild_bank_output_5_mc.selected;
			
			ExternalInterface.call("ASModifyGuildStorageRights", guild_post, storage_rights_data);
		}
		
		function updateGuildBaseInfo(data:Object)
		{
			guild_bank_all_mc.enabled = data.guild_rights_storage_right;
			guild_bank_all_input_mc.enabled = data.guild_rights_storage_right;
			guild_bank_all_output_mc.enabled = data.guild_rights_storage_right;
			
			guild_bank_input_0_mc.enabled = data.guild_rights_storage_right;
			guild_bank_input_1_mc.enabled = data.guild_rights_storage_right;
			guild_bank_input_2_mc.enabled = data.guild_rights_storage_right;
			guild_bank_input_3_mc.enabled = data.guild_rights_storage_right;
			guild_bank_input_4_mc.enabled = data.guild_rights_storage_right;
			guild_bank_input_5_mc.enabled = data.guild_rights_storage_right;
			
			guild_bank_output_0_mc.enabled = data.guild_rights_storage_right;
			guild_bank_output_1_mc.enabled = data.guild_rights_storage_right;
			guild_bank_output_2_mc.enabled = data.guild_rights_storage_right;
			guild_bank_output_3_mc.enabled = data.guild_rights_storage_right;
			guild_bank_output_4_mc.enabled = data.guild_rights_storage_right;
			guild_bank_output_5_mc.enabled = data.guild_rights_storage_right;
			
			guild_bank_post_mc.selectedIndex = data.guild_post - 1;
			guild_post = guild_bank_post_mc.selectedIndex;
			ExternalInterface.call("ASUpdateGuildStorageRights", guild_post);
		}
		
		function updateGuildStorageState(data:Object)
		{
			guild_bank_active_0_mc.htmlText = String(data.guild_storage_active_1);
			guild_bank_active_1_mc.htmlText = String(data.guild_storage_active_2);
			guild_bank_active_2_mc.htmlText = String(data.guild_storage_active_3);
			guild_bank_active_3_mc.htmlText = String(data.guild_storage_active_4);
			guild_bank_active_4_mc.htmlText = String(data.guild_storage_active_5);
			guild_bank_active_5_mc.htmlText = String(data.guild_storage_active_6);
		}
		
		function updateGuildStorageRights(data:GuildStorageData, tips:String)
		{
			guild_bank_input_0_mc.selected = data.input0;
			guild_bank_input_1_mc.selected = data.input1;
			guild_bank_input_2_mc.selected = data.input2;
			guild_bank_input_3_mc.selected = data.input3;
			guild_bank_input_4_mc.selected = data.input4;
			guild_bank_input_5_mc.selected = data.input5;
			
			guild_bank_output_0_mc.selected = data.output0;
			guild_bank_output_1_mc.selected = data.output1;
			guild_bank_output_2_mc.selected = data.output2;
			guild_bank_output_3_mc.selected = data.output3;
			guild_bank_output_4_mc.selected = data.output4;
			guild_bank_output_5_mc.selected = data.output5;
			
			guild_bank_tips_tf.text = tips;
		}
	}
}


























