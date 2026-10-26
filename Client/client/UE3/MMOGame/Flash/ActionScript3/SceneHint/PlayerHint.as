package ActionScript3.SceneHint
{
	import ActionScript3.MyBubbleText;
	import ActionScript3.SceneHint.HPProgressBar;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.controls.Button;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import scaleform.clik.controls.UILoader;
	import flash.external.ExternalInterface;
	import ActionScript3.SceneHint.StallHint;
	import scaleform.clik.events.ComponentEvent;
	import ActionScript3.Common.Utils.StyleType;
	import scaleform.clik.events.ButtonEvent;

	public class PlayerHint extends UIComponent
	{
		public var offsetY:int;
		public var serverID:int;
		public var HP_mc:HPProgressBar;
		public var typeicon_mc:MovieClip;
		public var TitleLoader_mc:UILoader;
		public var chatbubble_mc:MyBubbleText;
		public var stall_mc:StallHint;
        public var mc_guildleader:GuildLeaderName;
		public var mc_Npc_Status:MovieClip;
		public var mc_Name:MovieClip;
		public var mc_Monster_Status:MovieClip;
		public var mc_NpctypeIcon:MovieClip;
		public var mc_Guild:MovieClip;
		public var mc_Title:MovieClip;
		public var strIconName1:String;
		public var strIconName2:String;
		public var btn_Selected:Button;
        public var mc_vip:MovieClip;
		public var mc_enemy:MovieClip;
		public var mc_quest:MovieClip;
		public var mc_shabake:MovieClip;
        public var vipLevel:int;
		protected var VisibleTypeLast:int;
		override protected function configUI():void
		{
			super.configUI();
			offsetY= 3;//两行文字缩进像素值
			VisibleTypeLast=0;
			HP_mc.visible = false;
			typeicon_mc.visible= false;
			mc_NpctypeIcon.visible=false;
			TitleLoader_mc.visible = false;
			chatbubble_mc.visible = false;
			mc_shabake.mouseChildren=false;
			mc_shabake.mouseEnabled=false;
			mc_enemy.mouseChildren=false;
			mc_enemy.mouseEnabled=false;
			mc_vip.gotoAndStop(1);
			mc_vip.mouseChildren=false;
			mc_vip.mouseEnabled=false;
			mc_Name.mouseEnabled = false;
			mc_Name.enabled= false;
			mc_guildleader.clear();
			strIconName1= "";
			strIconName2= "";
			SetAllVisible(false);
			btn_Selected.addEventListener(ButtonEvent.CLICK,handleMouseClick, false, 0, true);
			mc_NpctypeIcon.addEventListener(MouseEvent.CLICK,clickHandler, false, 0, true);
			mc_NpctypeIcon.addEventListener(MouseEvent.MOUSE_OVER,overHandler, false, 0, true);
			mc_NpctypeIcon.addEventListener(MouseEvent.MOUSE_OUT,outHandler, false, 0, true);
			this.addEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
			//MaskUI = false;

			//SetHpInfo(this,50,100,2, 1);

			//SetTxtInfo(this,"[铁匠]","一个名字","[大Boss]","斧头帮","千人斩");

			//SetStallTxtInfo(this,"xx的摊"," 欢迎惠顾");

			//SetPlayerTxt(this,300,0,"大大dsdsdsdsddddd大大","无敌战士","万人斩","dfdg","");
			//setShabake(this,true);
			//this.setVipStatus(this,1);
			//this.setEnemy(this,true);
			//SetBubbleText(this,"EEEEEEEEEEEEWWWWWWWWWWWWWWWWWWWWWEEEEEEEEEEEEEEEDDDDDDDDDDDE");
			//SetStallTxtInfo(this,"tanming","gagaga");
			//SetBubbleTextEx(this,"hello");
			//SetIconInfo(this,"2.tga","1.png");
			//SetNpcTxt(this, 3,true,"王药师","药店","","#fffff");
		}
		
		private function overHandler(evt:MouseEvent):void
		{
            this.mc_NpctypeIcon.filters= [StyleType.getInstance().getGlow()];
		}
		
		private function outHandler(evt:MouseEvent):void
		{
			this.mc_NpctypeIcon.filters=null;
		}

		public function onRmoved(e:Event):void
		{
			btn_Selected.removeEventListener(ButtonEvent.CLICK,handleMouseClick);
			this.removeEventListener(Event.REMOVED_FROM_STAGE, onRmoved );
		}

		public function handleMouseClick(event:ButtonEvent):void
		{
			ExternalInterface.call( "ASRightClickTargetInfo" , root.mouseX , root.mouseY , serverID );
		}
		
		public function clickHandler(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASRightClickNpcInfo" , root.mouseX , root.mouseY , serverID );
		}

		public function SetAllVisible(Visible:Boolean):void
		{
			stall_mc.visible= Visible;
			mc_Npc_Status.visible= Visible;
			mc_vip.visible=Visible;
			mc_Name.visible= Visible;
			mc_Monster_Status.visible = Visible;
			mc_Guild.visible = Visible;
			mc_Title.visible= Visible;
			btn_Selected.visible = Visible;
			mc_quest.visible = Visible;
			mc_enemy.visible=Visible;
			mc_shabake.visible=Visible;
		}
		
		public function UCSetAllVisible(ThisObj:Object, Visible:Boolean):void
		{
			SetAllVisible(Visible);
		}

		public function SetSelectButton(ThisObj:Object, Visible:Boolean):void
		{
			if (btn_Selected.label && btn_Selected.label.length > 0)
			{
				btn_Selected.visible = Visible;
				if(btn_Selected.hasEventListener(ButtonEvent.CLICK)==false)
				{
					btn_Selected.addEventListener(ButtonEvent.CLICK,handleMouseClick);
				}
			}
			else
			{
				btn_Selected.visible = false;
			}
		}
        //设置公会沙巴克领导
		public function SetGuildLeader(ThisObj:Object, playName:String, GuildName:String, bl:Boolean):void
		{
			if(bl==true)
			{
				mc_guildleader.updateData(playName,GuildName);
			}
			else
			{
				mc_guildleader.clear();
			}
		}
		
		public function SetPlayerTxt_Name(ThisObj:Object, Frame:String, Name:String, nameColor:String):void
		{
			if (Name.length > 0)
			{
				mc_Name.gotoAndStop(Frame);
				var tF2:TextField = mc_Name.getChildByName("tF_name") as TextField;
				if (tF2)
				{
					if(nameColor.length > 0)
					{
						tF2.htmlText = "<font color='" + nameColor + "'>" + Name + "</font>";
					}
					else
					{
						tF2.htmlText = Name;
					}
				}
				if(Frame=="Player1"){
					btn_Selected.label = "";
				}else{
					btn_Selected.label = Name;
				}
				mc_Name.visible = true;
				
			}
			else
			{
				mc_Name.visible = false;
			}
			UpdateSelect();
			updateVip();
		}
		
		public function updateVip():void
		{
			if(this.vipLevel>0 && this.mc_vip.visible==true){
				var tF1:TextField = mc_Name.getChildByName("tF_name") as TextField;
				//mc_vip.x= -tF1.textWidth>>1 -104-mc_vip.width;
				mc_vip.x= -(tF1.textWidth>>1)-mc_vip.width;
				mc_vip.y=tF1.y+3;
			}
		}

		public function SetPlayerTxt_Guild(ThisObj:Object, Frame:String, Guild:String ):void
		{
			if (Guild.length > 0)
			{
				mc_Guild.gotoAndStop(Frame);
				var tF2:TextField = mc_Guild.getChildByName("tF_name") as TextField;
				if (tF2)
				{
					tF2.text = Guild;
				}
				mc_Guild.visible = true;
			}
			else
			{
				mc_Guild.visible = false;
			}
		}
		public function SetPlayerTxt_Title(ThisObj:Object, Frame:String, Title:String, TitleIcon:String ):void
		{
			if (TitleIcon.length > 0)
			{
				TitleLoader_mc.source = TitleIcon;
			}
			else
			{
				TitleLoader_mc.source = null;
			}

			if(TitleLoader_mc.source!=null){
				TitleLoader_mc.visible = true;
				mc_Title.visible = false;
			}
			else
			{
				TitleLoader_mc.visible = false;
				
				if (Title.length > 0)
				{
					mc_Title.gotoAndStop(Frame);
					var tF2:TextField = mc_Title.getChildByName("tF_name") as TextField;
					if (tF2)
					{
						tF2.text = Title;
					}
					mc_Title.visible = true;
				}
				else
				{
					mc_Title.visible = false;
				}
			}
		}
		public function SetPlayerTxt_Status(ThisObj:Object, Frame:String, Status:String ):void
		{
			if (Status.length > 0)
			{
				mc_Npc_Status.gotoAndStop(Frame);
				var tF2:TextField = mc_Npc_Status.getChildByName("tF_name") as TextField;
				if (tF2)
				{
					tF2.text = Status;
				}
				mc_Npc_Status.visible = true;
			}
			else
			{
				mc_Npc_Status.visible = false;
			}
		}
		
		public function SetPlayerTxt_Group(ThisObj:Object, PkValue:int,GroupType:int ):void
		{
			var Frame:String = "Player1";
			if (PkValue<100)
			{
				Frame = "Player3";
			}
			else if (PkValue<300)
			{
				Frame = "Player4";
			}
			else if (PkValue<500)
			{
				Frame = "Player5";
			}
            else if (PkValue>=500)
			{
				Frame = "Player6";
			}
			if (GroupType==1)
			{
				Frame = "Group1";
			}
			else if (GroupType==2)
			{
				Frame = "Group2";
			}
			else if (GroupType==3)
			{
				Frame = "Group3";
			}
			else if (GroupType==4)
			{
				Frame = "Group4";
			}
			else if (GroupType==5)
			{
				Frame = "Group5";

			}
			mc_Name.gotoAndStop(Frame);
		}		


		public function SetPlayerTxt(ThisObj:Object, PkValue:int,GroupType:int, Name:String, Guild:String, Title:String, TitleIcon:String, Status:String):void
		{
			var Frame:String = "Player1";
			if (PkValue<100)
			{
				Frame = "Player3";
			}
			else if (PkValue<300)
			{
				Frame = "Player4";
			}
			else if (PkValue<500)
			{
				Frame = "Player5";
			}
            else if (PkValue>=500)
			{
				Frame = "Player6";
			}
			if (GroupType==1)
			{
				Frame = "Group1";
			}
			else if (GroupType==2)
			{
				Frame = "Group2";
			}
			else if (GroupType==3)
			{
				Frame = "Group3";
			}
			else if (GroupType==4)
			{
				Frame = "Group4";
			}
			else if (GroupType==5)
			{
				Frame = "Group5";
			}
			SetAllVisible(false);
			mc_Name.gotoAndStop(Frame);
			mc_Name.visible = true;
			var tF1:TextField = mc_Name.getChildByName("tF_name") as TextField;
			if (tF1)
			{
				tF1.text = Name;
			}
			if(Frame == "Player1"){
				btn_Selected.label = "";
			}else{
				btn_Selected.label = Name;
			}
			UpdateSelect();

			if (Guild.length > 0)
			{
				mc_Guild.visible = true;
				var tF2:TextField = mc_Guild.getChildByName("tF_name") as TextField;
				if (tF2)
				{
					tF2.text = Guild;
				}
			}

			if (TitleIcon.length > 0)
			{
				TitleLoader_mc.source = TitleIcon;
				TitleLoader_mc.visible = true;
				mc_Title.visible = false;
			}
			else
			{
				TitleLoader_mc.visible = false;
				
				if (Title.length > 0)
				{
					mc_Title.gotoAndStop("Title");
					var tF3:TextField = mc_Title.getChildByName("tF_name") as TextField;
					if (tF3)
					{
						tF3.text = Title;
					}
					mc_Title.visible = true;
				}
				else
				{
					mc_Title.visible = false;
				}
			}
			
			if (Status.length > 0)
			{
				mc_Npc_Status.gotoAndStop("NpcType");
				mc_Npc_Status.visible = true;
				var tF4:TextField = mc_Npc_Status.getChildByName("tF_name") as TextField;
				if (tF4)
				{
					tF4.text = Status;
				}
			}
			//UpdateDisplay();
            updateVip();
		}
		
		public function setShabake(ThisObj:Object,dat:Boolean):void
		{
			if(dat==false){
				this.mc_shabake.visible=false;
				mc_Guild.x=0;
			}else{
				this.mc_shabake.visible=true;
				var tF1:TextField = mc_Guild.getChildByName("tF_name") as TextField;
				mc_Guild.x=+22;
                mc_shabake.x = -(tF1.textWidth>>1) - mc_shabake.width+22;
			}
		}
		
		public function setEnemy(ThisObj:Object,dat:Boolean):void{
			if(dat==false){
				this.mc_enemy.visible=false;
			}else{
				this.mc_enemy.visible=true;
				var tF1:TextField = mc_Name.getChildByName("tF_name") as TextField;
				if(this.mc_vip.visible===true){
					this.mc_enemy.x=this.mc_vip.x-this.mc_enemy.width;
				}else{
					//mc_enemy.x=(mc_Name.width-tF1.textWidth>>1)-104-mc_enemy.width;
					mc_enemy.x = -(tF1.textWidth>>1) - mc_enemy.width;
				}
			}
		}
		
		public function setVipStatus(ThisObj:Object,vip:int):void
		{
			this.vipLevel=vip;
			if(vip>0 && vip<4){
				var tF1:TextField = mc_Name.getChildByName("tF_name") as TextField;
				if(tF1){
					mc_vip.visible=true;
				    //mc_vip.x=(mc_Name.width-tF1.textWidth>>1)-104-mc_vip.width;
					//mc_vip.x=mc_Name.width-tF1.textWidth/2-mc_vip.width;
					mc_vip.x= -(tF1.textWidth>>1) -mc_vip.width;
					mc_vip.y=tF1.y+3;
				    mc_vip.gotoAndStop(vip);
				}
			}else{
				mc_vip.visible=false;
			}
		}

		public function SetNpcTxt(ThisObj:Object, NpcType:int, Attackble:Boolean, Name:String, Status:String, FrameEx:String, nameColor:String):void
		{
			var Frame:String = "Npc1";
			if (NpcType==1)
			{
				Frame = "Npc1";
			}
			else if (NpcType==2)
			{
				Frame = "Npc2";
			}
			else if (NpcType==3)
			{
				Frame = "Npc3";
			}
			else if (NpcType==4)
			{
				Frame = "Npc4";
			}
			if (Attackble)
			{
				Frame = "Group4";
			}
			if (FrameEx.length>0)
			{
				Frame = FrameEx;
			}
			SetAllVisible(false);

			mc_Name.gotoAndStop(Frame);
			mc_Name.visible = true;
			var tF1:TextField = mc_Name.getChildByName("tF_name") as TextField;
			if (tF1)
			{
				if(nameColor.length > 0)
				{
					tF1.text = "";
					tF1.htmlText = "<font color='" + nameColor + "'>" + Name + "</font>";
				}
				else
				{
					tF1.htmlText = "";
					tF1.text = Name;
				}
			}
			UpdateSelect();

			if (Status.length > 0)
			{
				mc_Npc_Status.gotoAndStop("NpcType");
				mc_Npc_Status.visible = true;
				var tF2:TextField = mc_Npc_Status.getChildByName("tF_name") as TextField;
				if (tF2)
				{
					tF2.text = Status;
				}
			}

			//UpdateDisplay();

		}

		public function SetMonsterTxt(ThisObj:Object, MonsterType:int, Name:String, Status:String, quest_icon:String, FrameEx:String, nameColor:String):void
		{
			var Frame:String = "Monster1";
			if (MonsterType==1)
			{
				Frame = "Monster1";
			}
			else if (MonsterType==2)
			{
				Frame = "Monster1";
			}
			else if (MonsterType==3)
			{
				Frame = "Monster1";
			}
			else if (MonsterType==4)
			{
				Frame = "Monster1";
			}
			else if (MonsterType==5)
			{
				Frame = "Monster1";
			}
			else if (MonsterType==6)
			{
				Frame = "Monster4";//精英
			}
			else if (MonsterType==7)
			{
				Frame = "Monster5";//稀有
			}
			else if (MonsterType==8)
			{
				Frame = "Monster6";
			}//boss
			
			if (FrameEx.length>0)
			{
				Frame = FrameEx;
			}

			SetAllVisible(false);

			mc_Name.gotoAndStop(Frame);
			mc_Name.visible = true;
			var tF1:TextField = mc_Name.getChildByName("tF_name") as TextField;
			if (tF1)
			{
				if(nameColor.length > 0 && MonsterType!=6 && MonsterType!=7 && MonsterType!=8 )
				{
					tF1.text = "";
					tF1.htmlText = "<font color='" + nameColor + "'>" + Name + "</font>";;
				}
				else
				{
					tF1.htmlText = "";
					tF1.text = Name;
				}
			}
			UpdateSelect();

			if (Status.length > 0)
			{
				mc_Monster_Status.gotoAndStop("NpcType");
				mc_Monster_Status.visible = true;
				var tF2:TextField = mc_Monster_Status.getChildByName("tF_name") as TextField;
				if (tF2)
				{
					tF2.text = Status;
				}
			}

			if (quest_icon.length > 0)
			{
				mc_quest.visible = true;
				mc_quest.source = quest_icon;
				mc_quest.x = mc_Name.x - tF1.textWidth / 2 - mc_quest.width;
			}
			else
			{
				mc_quest.visible = false;
			}
			
			//UpdateDisplay();

		}

		public function SetBossTxt(ThisObj:Object, Name:String, Status:String ):void
		{
			var Frame:String = "Monster6";

			SetAllVisible(false);

			mc_Name.gotoAndStop(Frame);
			mc_Name.visible = true;
			var tF1:TextField = mc_Name.getChildByName("tF_name") as TextField;
			if (tF1)
			{
				tF1.text = Name;
			}
			UpdateSelect();

			mc_Monster_Status.gotoAndStop("NpcType");
			if (Status.length > 0)
			{
				mc_Monster_Status.visible = true;
			}
			var tF2:TextField = mc_Monster_Status.getChildByName("tF_name") as TextField;
			if (tF2)
			{
				tF2.text = Status;
			}

			//UpdateDisplay();
		}

		public function SetStallTxtInfo( ThisObj:Object,palyerName:String, stallName:String,attention:Boolean ):void
		{
			if (stallName.length > 0)
			{
				if(stall_mc.visible == false)
				{
					SetAllVisible(false);
					HP_mc.visible = false;
					stall_mc.visible = true;
				}
				stall_mc.SetStallText(palyerName,stallName, attention);
				//UpdateDisplay();
			}
			else if(stall_mc.visible)
			{
				stall_mc.visible = false;
				//UpdateDisplay();
			}
			
		}

		public function SetIconInfo( ThisObj:Object, IconName1:String,iconName2:String)
		{
			if (IconName1.length > 0)
			{
				strIconName1 = IconName1;
				typeicon_mc.IdenIcon.source = IconName1;
				typeicon_mc.visible = true;
				typeicon_mc.IdenIcon.visible = true;
			}
			else
			{
				typeicon_mc.visible = false;
			}
			if(iconName2.length>0)
			{
				strIconName2 = iconName2;
				mc_NpctypeIcon.IdenIcon.source = iconName2;
				mc_NpctypeIcon.visible = true;
			}
			else
			{
				mc_NpctypeIcon.visible=false;
			}
			//UpdateDisplay();
		}

		public function RefreshIconInfo( ThisObj:Object)
		{
			SetIconInfo( ThisObj, strIconName1,strIconName2);
		}

		public function SetHpInfo( ThisObj:Object, Hp:int,HpMax:int,State:int, VisibleType:int ):void
		{
			var Visible:Boolean = false;
			var isTxt:Boolean=true;
			
			if (VisibleType>0)
			{
				Visible = true;
			}
			if(VisibleType==2)
			{//约定不显示其他玩家文本
				isTxt=false;
			}
			if (HpMax<Hp)
			{
				HpMax = Hp;
			}
			if (Visible)
			{
				HP_mc.SetStateByFrame(State);
				HP_mc.SetDivide(Hp,HpMax,isTxt);
				
//				if (HpMax==Hp && VisibleType!=1)
//				{
//					Visible = false;
//				}
				if (Hp==0)
				{
					Visible = false;
				}
			}
			else
			{
				HP_mc.SetDivide(100,100,false);
			}

			if (HP_mc.visible != Visible)
			{
				HP_mc.visible = Visible;
				VisibleTypeLast =VisibleType;
				UpdateDisplay();
			}
			else if (VisibleTypeLast !=VisibleType )
			{
				VisibleTypeLast =VisibleType;
				UpdateDisplay();
			}
		}

		public function CloseBubbleText(ThisObj:Object)
		{
			chatbubble_mc.visible = false;
		}

		public function SetBubbleTextEx( ThisObj:Object, bubbleText:String ):void
		{
			var PreVisible:Boolean = chatbubble_mc.visible;
			chatbubble_mc.visible = true;
			chatbubble_mc.ShowBubble(bubbleText);
			if (! PreVisible)
			{
				UpdateDisplay();
			}
		}

		public function SetBubbleText( ThisObj:Object, bubbleText:String ):void
		{
			var PreVisible:Boolean = chatbubble_mc.visible;
			chatbubble_mc.visible = true;
			chatbubble_mc.BeginToShowBubble( bubbleText );
			if (! PreVisible)
			{
				UpdateDisplay();
			}
		}

		public function UpdateSelect():void
		{
			mc_Name.enabled = false;
			mc_Name.mouseEnabled = false;
		}

		public function UpdateDisplay():void
		{
			//血条位置
			var y :int= HP_mc.y - HP_mc.getHeight() - offsetY -2;
			//trace(y);
			//摆摊显示
			if (stall_mc.visible)
			{
				y = stall_mc.y;// - stall_mc.height;
			}
			//各种文字显示
			var mc:Array = [mc_Npc_Status,mc_Name,mc_Monster_Status,mc_Guild,mc_Title];
			//叠加hint
			for (var i=0; i<mc.length; i++)
			{
				if (mc[i].visible)
				{
					mc[i].y = y;//Math.round(y);
					if(mc[i]==mc_Guild){
						mc[i].y += 6;
					}
					y -=  mc[i].height - offsetY;
				}
			}
			if(mc_quest.visible==true)
			{
				mc_quest.y=mc_Name.y-24;
			}
			btn_Selected.y = mc_Name.y;// - btn_Selected.height;
			if(mc_enemy && mc_enemy.visible==true)
			{
				mc_enemy.y=mc_Name.y-22;
			}
			if(mc_shabake && mc_shabake.visible)
			{
				mc_shabake.y=mc_Guild.y-28;
			}
			//title显示
			if(TitleLoader_mc.visible)
			{
				y -= 30;
				TitleLoader_mc.y = y;
			}
			//图标显示
			if(mc_NpctypeIcon.visible)
			{
				mc_NpctypeIcon.y=y+15;
				y=y-mc_NpctypeIcon.height;
				mc_NpctypeIcon.x=0;
				if(typeicon_mc.visible)
				{
					typeicon_mc.y = mc_NpctypeIcon.y-10;
					typeicon_mc.x=-28;
					mc_NpctypeIcon.x=0;
				}
			}
			else 
			{
				if(typeicon_mc.visible)
				{
					typeicon_mc.x=0;
					typeicon_mc.y = y;
				    y = y - typeicon_mc.height;
				}
			}
			//泡泡显示
			chatbubble_mc.y = y;
		}

	}
}