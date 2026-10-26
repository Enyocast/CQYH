package ActionScript3.Battle
{


	import ActionScript3.MyPanel;
	import ActionScript3.MyActivePanel;
	import flash.external.ExternalInterface;

	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import flash.display.Stage;


	public class ArenaScore extends MyPanel
	{

		const MaxSidePlayerNum:int = 5;
		public var WinnerItem:Array;
		public var LoserItem:Array;
		public var LeaveButton:Button;

		public var Title:TextField;
		public var WinTeam:TextField;
		public var LoseTeam:TextField;

		override protected function configUI():void
		{

			super.configUI();

			WinnerItem = new Array  ;
			LoserItem = new Array  ;


			for (var i:int = 0; i < MaxSidePlayerNum; i++)
			{
				var wItem = this.getChildByName( "Winner"+i ) as MovieClip;
				WinnerItem.push( wItem );
			}

			for (var j:int = 0; j < MaxSidePlayerNum; j++)
			{
				var lItem = this.getChildByName( "Loser"+j ) as MovieClip;
				LoserItem.push( lItem );
			}

			ExternalInterface.call( "RegisterArenaScore" , this );

			if (LeaveButton)
			{
				LeaveButton.addEventListener( MouseEvent.CLICK , LeaveArena );
			}

			//var player = {IsMale:true,PlayerName:"dd",ClassId:0,ClassName:"武当",Alive:"alive",Lv:21,Kill:2,Score:"100",Damage:7777};
			//var player2 = {IsMale:false,PlayerName:"dd",ClassId:1,ClassName:"武当",Alive:"alive",Lv:21,Kill:2,Score:"100",Damage:7777};
			//SetScoreData( { Title:"t" , WinTeam:"w" , LoseTeam:"L" , WinList:[player,player2,player2] , LoseList:[player,player] } );
		}

		public function SetPanelText( data:Object )
		{

		}

		public function LeaveArena()
		{
			ExternalInterface.call( "ASArenaLeave" );
		}

		public function SetScoreData( data:Object )
		{
			if (Title)
			{
				Title.text = data.Title;
			}
			if (WinTeam)
			{
				WinTeam.text = data.WinTeam;
			}
			if (LoseTeam)
			{
				LoseTeam.text = data.LoseTeam;
			}

			var winList:Array = data.WinList as Array;
			if (winList)
			{
				var winIdx:int = 0;

				SetWinnerNum(winList.length);

				for (winIdx = 0; winIdx < winList.length; winIdx++)
				{
					var winner = winList[winIdx];
					SetData( WinnerItem[winIdx] , winner.IsMale , winner.PlayerName , winner.ClassId , 
					winner.ClassName , winner.Alive , winner.Lv ,winner.Kill , 
					winner.Score , winner.Damage );
				}
			}

			var loseList:Array = data.LoseList as Array;
			if (loseList)
			{
				var loseIdx:int = 0;

				SetLoserNum( loseList.length );

				for (loseIdx = 0; loseIdx < loseList.length; loseIdx++)
				{
					var loser = loseList[loseIdx];
					SetData( LoserItem[loseIdx] , loser.IsMale , loser.PlayerName ,loser.ClassId , 
					loser.ClassName , loser.Alive , loser.Lv , loser.Kill , 
					loser.Score , loser.Damage );
				}
			}
		}




		public function SetLoserNum( num:int )
		{
			for (var i:int = 0; i < LoserItem.length; i++)
			{
				if ( i < num && LoserItem[i])
				{
					LoserItem[i].visible = true;
				}
				else if ( LoserItem[i] )
				{
					LoserItem[i].visible = false;
				}
			}
		}

		public function SetWinnerNum( num:int )
		{
			for (var i:int = 0; i < WinnerItem.length; i++)
			{
				if ( i < num && WinnerItem[i])
				{
					WinnerItem[i].visible = true;
				}
				else if ( WinnerItem[i] )
				{
					WinnerItem[i].visible = false;
				}
			}
		}

		//public function SetWinnerData( index:int , male:Boolean , playername:String , classId:int , className:String , alive:Boolean , lv:int , kill:int , score:String )
		//{
		//if ( index >= WinnerItem.length )
		//{
		//return;
		//}
		//
		//SetData( WinnerItem[index] , male , playername , classId , className , alive , lv , kill , score );
		//
		//}
		//
		//public function SetLoserData( index:int , male:Boolean , playername:String , classId:int , className:String , alive:Boolean ,lv:int , kill:int , score:String )
		//{
		//if ( index >= LoserItem.length )
		//{
		//return;
		//}
		//SetData( LoserItem[index] , male , playername , classId , className , alive , lv , kill , score );
		//}

		function SetData( mc:MovieClip , male:Boolean , playername:String , classId:int , className:String , alive:Boolean  , lv:int , kill:int , score:String , damage:int )
		{
			var name_tf:TextField = mc.getChildByName("name_tf") as TextField;
			if (name_tf)
			{
				name_tf.text = playername;
			}
			var class_tf:TextField = mc.getChildByName("class_tf") as TextField;
			if (class_tf)
			{
				class_tf.text = className;
			}
			var lv_tf:TextField = mc.getChildByName("lv_tf") as TextField;
			if (lv_tf)
			{
				lv_tf.text = String(lv);
			}
			var kill_tf:TextField = mc.getChildByName("kill_tf") as TextField;
			if (kill_tf)
			{
				kill_tf.text = String(kill);
			}
			var score_tf:TextField = mc.getChildByName("score_tf") as TextField;
			if (score_tf)
			{
				score_tf.text = score;
			}
			var damage_tf:TextField = mc.getChildByName("damage_tf") as TextField;
			if (damage_tf)
			{
				damage_tf.text = String(damage);
			}


			var roleHead_mc:MovieClip = mc.getChildByName("roleHead_mc") as MovieClip;


			if (roleHead_mc)
			{
				var iconId:int = classId*20 + (male?0:10) + 10;
				trace("iconId:"+iconId);
				roleHead_mc.gotoAndStop( iconId );
			}

			var alive_mc:MovieClip = mc.getChildByName("alive") as MovieClip;
			if (alive_mc)
			{
				if (alive)
				{
					alive_mc.gotoAndStop("alive");
				}
				else
				{
					alive_mc.gotoAndStop("dead");
				}

			}

		}

	}

}