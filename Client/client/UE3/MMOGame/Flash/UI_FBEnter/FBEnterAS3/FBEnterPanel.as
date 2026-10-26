package UI_FBEnter.FBEnterAS3
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.RadioButton;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.UILoader;
	
	import flash.events.MouseEvent;
	import flash.events.Event;
	
	import ActionScript3.VerticalWords;
	//import UI_FBEnter.FBEnterAS3.LinkShowButton;
	import ActionScript3.LinkShowButton;
	
	public class FBEnterPanel extends MyPanel
	{
		public var FBBackgroundMc:UILoader;
		/*
		public var btn_FBBranch0:Button;
		public var btn_FBBranch1:Button;
		public var btn_FBBranch2:Button;
		public var btn_FBBranch3:Button;
		public var btn_FBBranch4:Button;
		*/
		//public var btn_close:Button;
		/*
		public var FBDiffBtn0:LinkShowButton;
		public var FBDiffBtn1:LinkShowButton;
		public var FBDiffBtn2:LinkShowButton;
		public var FBDiffBtn3:LinkShowButton;
		
		public var FBDiffHintBtn0:Button;
		public var FBDiffHintBtn1:Button;
		public var FBDiffHintBtn2:Button;
		public var FBDiffHintBtn3:Button;
		
		public var FBDiffMc0:MovieClip;
		public var FBDiffMc1:MovieClip;
		public var FBDiffMc2:MovieClip;
		public var FBDiffMc3:MovieClip;
		*/
		public var EnterFBBtn:Button;
		//
		//public var DiffcultyTitleTf:TextField;
		public var FBNameTf:TextField;
		public var FBVerticalDescribleMc:VerticalWords;
		//
		public var LevelRequiredTf:TextField;
		public var FrequencyRequiredTf:TextField;
		public var FrequencyRequiredTitleTf:TextField;
		public var PeopleRequiredTf:TextField;
		public var HuoLiRequiredTf:TextField;
		public var OpenTimeRequiredTf:TextField;
		public var OpenTimeRequiredTitleTf:TextField;
		
		override protected  function configUI():void 
		{
			super.configUI();
			//
			ExternalInterface.call( "RegisterFBEnter", this );
			/*
			btn_FBBranch0.addEventListener( "click", function _ChangeFBBrance(e:Event){ ChangeFBBrance(e,0);} );
			btn_FBBranch1.addEventListener( "click", function _ChangeFBBrance(e:Event){ ChangeFBBrance(e,1);} );
			btn_FBBranch2.addEventListener( "click", function _ChangeFBBrance(e:Event){ ChangeFBBrance(e,2);} );
			btn_FBBranch3.addEventListener( "click", function _ChangeFBBrance(e:Event){ ChangeFBBrance(e,3);} );
			btn_FBBranch4.addEventListener( "click", function _ChangeFBBrance(e:Event){ ChangeFBBrance(e,4);} );
			*/
			
			/*
			FBDiffBtn0.addEventListener( MouseEvent.CLICK, function _ChangeDifficulty(e:Event){ ChangeDifficulty(e,0);} );
			FBDiffBtn1.addEventListener( MouseEvent.CLICK, function _ChangeDifficulty(e:Event){ ChangeDifficulty(e,1);} );
			FBDiffBtn2.addEventListener( MouseEvent.CLICK, function _ChangeDifficulty(e:Event){ ChangeDifficulty(e,2);} );
			FBDiffBtn3.addEventListener( MouseEvent.CLICK, function _ChangeDifficulty(e:Event){ ChangeDifficulty(e,3);} );
			
			FBDiffBtn0.ShowMovieClip = FBDiffMc0;
			FBDiffBtn1.ShowMovieClip = FBDiffMc1;
			FBDiffBtn2.ShowMovieClip = FBDiffMc2;
			FBDiffBtn3.ShowMovieClip = FBDiffMc3;
			
			//
			FBDiffHintBtn0.visible = true;
			FBDiffHintBtn0.enabled = false;
			FBDiffHintBtn1.visible = true;
			FBDiffHintBtn1.enabled = false;
			FBDiffHintBtn2.visible = true;
			FBDiffHintBtn2.enabled = false;
			FBDiffHintBtn3.visible = true;
			FBDiffHintBtn3.enabled = false;
			*/
			
			//
			EnterFBBtn.addEventListener( MouseEvent.CLICK, clickEnterFB );
			
			//test
			//FBDescribleTf.htmlText = "掩埋在风沙之中的古老神殿，机关密布，异兽横行，似乎封尘着某些过去的秘密。墙壁上斑驳的文字，淡淡的诉说着那些被不愿提及的记忆—从踏入神殿开始，仿佛陷入了一段无法清醒的噩梦。";
			//SetFBDescription( "  掩埋在风沙之中的古老神殿，机关密布，异兽横行，似乎封尘着某些过去的秘密。墙壁上斑驳的文字，淡淡的诉说着那些被不愿提及的记忆—从踏入神殿开始，仿佛陷入了一段无法清醒的噩梦。");
		}
		//
		function ChangeFBBrance( e:Event, idx:int )
		{
			ExternalInterface.call( "UCFBBranchChange", idx );
		}
		//
		function ChangeDifficulty( e:Event, idx:int )
		{
			ExternalInterface.call( "UCMapDiffChange", idx );
		}
		
		function clickEnterFB( e:Event )
		{
			ExternalInterface.call("UCEnterMap");
		}
		
		//
		public function SetFBDescription( str:String )
		{
			FBVerticalDescribleMc.SetWorlds( str, 9, 50, 4 );
		}
	}
}