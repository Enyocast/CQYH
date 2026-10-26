package ActionScript3.Team{
	
	import ActionScript3.MyPanel;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import scaleform.gfx.MouseEventEx;
	import flash.external.ExternalInterface;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.text.TextField;
	
	public class TeamHint extends MyPanel
	{
		public var TeamAssign_tf:TextField;
		public var TeamMemberNum_tf:TextField;
		//public var TeamSize_tf:TextField;
		public var LeaveTeam_btn:Button;
		public var bg:MovieClip;
		public var btn_expand:Button;
		
		override protected  function configUI():void 
		{
			super.configUI();
			//ExternalInterface.call( "RegisterTeamHint", this );
			
			if(LeaveTeam_btn)
			{
				LeaveTeam_btn.addEventListener(MouseEvent.CLICK , clickLeave , false , 0 , true );
			}
			
			//HideWidget(true);
			//SetData( { teamAssignText:"组队拍卖" , teamMemberNumText:"1/5" , teamSizeText:"5人组队" } );
			
			btn_expand.addEventListener( MouseEvent.CLICK, onClickShowExpand );
			btn_expand.selected = true;
			layou();
			//ShowByExpand(true);
		}
		
		public function HideWidget( hide:Boolean ):void
		{
			//隐藏掉所有子
            var i:int=0;
			var l:int=this.numChildren;
			for(i;i<l;i++){
				this.getChildAt(i).visible=!hide;
			}
		}
		
		public function SetData( data:Object ):void
		{
			if(TeamAssign_tf)
			{
				TeamAssign_tf.htmlText = "("+data.teamAssignText+")";				
			}
			if(TeamMemberNum_tf)
			{
				TeamMemberNum_tf.htmlText = data.teamMemberNumText;
			}
/*			if( TeamSize_tf )
			{
				TeamSize_tf.htmlText = data.teamSizeText;
			}*/
			
		}
		
		function clickLeave(e:MouseEvent):void
		{
			ExternalInterface.call( "ASTeamHintLeave" );
		}
		
		
		public function onClickShowExpand(e:MouseEvent):void
		{
			btn_expand.selected = !btn_expand.selected;
			layou();
			ExternalInterface.call( "ASTeamExpand",btn_expand.selected);
		}
		
		private function layou():void
		{
			if(btn_expand.selected==true){
				btn_expand.x=212;
			}else{
				btn_expand.x=2;
			}
		}
		
		public function ShowByExpand(v:Boolean):void
		{
			//隐藏掉所有子
            var i:int=0;
			var l:int=this.numChildren;
			for(i;i<l;i++){
				if(this.getChildAt(i).name != "btn_expand")
					this.getChildAt(i).visible=v;
			}
		}
		
	}
}