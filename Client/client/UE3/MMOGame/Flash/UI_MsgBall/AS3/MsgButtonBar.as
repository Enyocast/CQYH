package UI_MsgBall.AS3 {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.getDefinitionByName;
	
	import ActionScript3.MyPanel;
	import ActionScript3.MySeriesButton;
	
	import fl.transitions.easing.Strong;
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.ScrollingList;
	import scaleform.clik.data.DataProvider;
	import scaleform.clik.events.ListEvent;
	import scaleform.clik.motion.Tween;
	import ActionScript3.Common.Events.ParamEvent;
	import ActionScript3.GameDispathcher;
	import flash.display.DisplayObject;
	
	
	public class MsgButtonBar extends MyPanel {
		
		const ButtonNum:int = 5;
		const _movieLenght:int = 100; //新按钮动画漂移距离
		const _movieTime:int = 1500;
		
		var ButtonList:Array;

		public var MsgScrollingList:ScrollingList;
        public var _msgbarBg:MovieClip;
		var _curMsgListType = -1;
		var _hintClass:Class;
	    public var testeffect:MovieClip;
		override protected  function configUI():void 
		{
			ShowMode="MsgBar";
			_hintClass = getDefinitionByName( "HintTipsBG") as Class;
			ButtonList = [];
			super.configUI();
			if(testeffect){
				this.removeChild(testeffect);
			    testeffect=null;
			}
			MsgScrollingList.addEventListener(ListEvent.ITEM_CLICK, handleListItemClick, false, 0, true);
			hide();
			_msgbarBg.mouseEnabled=false;
			_msgbarBg.mouseChildren=false;
			stageChangeHandler(null);
			//addNewButton({type:5,num:1,tips:"邮件"});
			//addNewButton({type:1,num:1,tips:"公会"});
		}
		
		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			this.x=cavasWidth-680;
			this.y=cavasHeight-150;
		}

		private function handleListItemClick( event:ListEvent ):void
		{
			hide();
			ExternalInterface.call( "ASMsgListClick" , event.index , _curMsgListType );
		}
		
		private function hide():void
		{
			MsgScrollingList.visible = false;
			_msgbarBg.visible=false;
		}
		
		public function toggleMsgScrolingList( type:int ):void
		{
			if( MsgScrollingList )
			{
				_curMsgListType = type;
			}
		}
		
		public function updateMsgScrolingList( data:Object ):void
		{
			if( !data || !MsgScrollingList )
			{
				return;
			}
			var type = data.type;
			var nameList:Array = data.nameList;
			var nameLenth:int = nameList.length;
			var btnL:int=ButtonList.length;
			if( type != _curMsgListType  || nameLenth == 0 || btnL==0)
			{
				hide();
				return;
			}
			var foundIndex:int = -1;
			for( var j:int = 0 ; j < btnL ; j++ )
			{
				if( ButtonList[j].type == type )
				{					
					foundIndex = j;
					break;
				}
			}
			var list:Array = [];
			for( var i:int = 0 ; i < nameLenth ; i++ )
			{
				list.push( { label:nameList[i] , index:i } );
			}
			MsgScrollingList.dataProvider = new DataProvider( list );
			MsgScrollingList.height = 26*nameLenth + 6;			
			MsgScrollingList.x = ButtonList[foundIndex].widget.x + 6;
			MsgScrollingList.y = ButtonList[foundIndex].widget.y - MsgScrollingList.height+5;
			_msgbarBg.x=MsgScrollingList.x-6;
			_msgbarBg.y=MsgScrollingList.y-5;
			_msgbarBg.height=MsgScrollingList.height+5;
			ButtonList[foundIndex].union.addChild(_msgbarBg);
			ButtonList[foundIndex].union.addChild(MsgScrollingList);
			if(nameLenth>0)
			{
				MsgScrollingList.visible = true;
			    _msgbarBg.visible=true;
			}
		}
		
		private function clickHintButton( e:MouseEvent ):void
		{
			var btn:HintInfoAlert=e.target as HintInfoAlert;
			if(btn)
			{
				var _type:int=btn.itemid;
				if(_type==_curMsgListType && MsgScrollingList.visible==true)
				{
					hide();//如果单击同一个按钮
				}
				else
				{
					hide();
					ExternalInterface.call( "ASMsgButtonClick" ,_type);
				}
			}
		}
		
		
		private function overHintButton( e:MouseEvent ):void
		{
			if( e.target is HintInfoAlert && ( e.target as HintInfoAlert ).parent)
			{   
				var hint:DisplayObject = ( e.target as HintInfoAlert ).parent.getChildByName("hint");
				if(hint )
					hint.visible = true;
			}
		}
		
		private function outHintButton( e:MouseEvent ):void
		{
			if( e.target is HintInfoAlert && ( e.target as HintInfoAlert ).parent)
			{
				var hint:DisplayObject = ( e.target as HintInfoAlert ).parent.getChildByName("hint");
				if(hint )
					hint.visible = false;
			}
		}
		
		public function addNewButton( dat:Object ):void
		{
			if(dat )
			{
				for( var i:int = 0 ; i < ButtonList.length ; i++ )
				{
					if( ButtonList[i].type == dat.type )
					{
						//新加的重复，就更新下数量，可以补个闪
						//原来要求角标是1就不显示，但这时在tween中改visible有时会无效，我估计和tween有关。暂时先不搞这个
						if( dat.num <= 0 )
						{
							ButtonList[i].widget.msgNumBg.vislble = false;
							ButtonList[i].widget.numTF.vislble = false;
							
						}
						else
						{
							ButtonList[i].widget.msgNumBg.vislble = true;
							ButtonList[i].widget.numTF.vislble = true;
							ButtonList[i].widget.numTF.text = dat.num;
						}
						return;
					}
				}
				//用个容器装button和那个列表，这样就能一起动了
				var union:MovieClip = new MovieClip();
				var curType:int=dat.type;
				if(curType==0 || curType==6){
					curType=5;
				}
				var butt:HintInfoAlert =new ( getDefinitionByName( "HintInfo"+curType) as Class);
				if( butt && union )
				{
					var targetPosX:int = ButtonNum * butt.width ;
					union.x = -660;
					union.y = 0;
					butt.itemid = dat.type;
					var effect:MovieClip=new ( getDefinitionByName("MsgEffect") as Class);
					effect.x=-1;
					effect.y=-3;
					effect.mouseChildren=false;
					effect.mouseEnabled=false;
					butt.addChildAt(effect,1);
					if( butt.numTF )
					{
						if(dat.num <=0)
						{
							butt.msgNumBg.visible = false;
							butt.numTF.visible = false;
							
						}
						else
						{
							butt.msgNumBg.visible = true;
							butt.numTF.visible = true;
							butt.numTF.text = dat.num;
							
						}
					}
					butt.addEventListener( MouseEvent.CLICK , clickHintButton);
					butt.addEventListener( MouseEvent.ROLL_OVER , overHintButton);
					butt.addEventListener( MouseEvent.ROLL_OUT , outHintButton);
					
					var buttonTween:Tween = new Tween( _movieTime ,union ,{ x:targetPosX} , {paused:true,ease:Strong.easeOut,onComplete:null,loop:false});
					
					
					ButtonList.push( { union:union , widget:butt , tw:buttonTween , isNew:true , type:dat.type } );
					
					
					buttonTween.reset();
					buttonTween.paused = false;
					
					union.addChild( butt );
					
					var hint:MovieClip = new _hintClass as MovieClip;
					if( hint )
					{
						hint.mouseChildren=false;
						hint.mouseEnabled=false;
						var title:TextField = hint.getChildByName("title") as TextField;
						if(title)
						{
							title.text = dat.tips;
						}
						hint.name = "hint";
						hint.y = 56;
						hint.visible = false;
						union.addChild( hint );
					}
					
					this.addChild( union );
					updateButton();
					//sound
					if(curType == 9)//仇人
					{
						playSound("Gem_Set_Reg_Cue");
					}
					else//TODO:临时方案，需要区分细化
					{
						playSound("iMessage");
					}
				}
			}
		}
		
		
		public function removeButton( type:int ):void
		{
			for( var i:int = 0 ; i < ButtonList.length ; i++ )
			{
				
				if( ButtonList[i].type == type )
				{
					if( MsgScrollingList && MsgScrollingList.parent == ButtonList[i].union )
					{
						this.addChild(_msgbarBg);
						this.addChild(MsgScrollingList);
					}
					if( MsgScrollingList )
					{
						MsgScrollingList.visible = false;
						_curMsgListType = -1;
					}
					
					this.removeChild( ButtonList[i].union );
					ButtonList.splice( i , 1 );
					
					updateButton();
					break;
				}
				
			}
			
		}
		
		private function updateButton():void
		{
			var useNum = ButtonList.length;
			
			for( var i:int = 0 ; i < useNum ; i++ )
			{
				var item:HintInfoAlert = ButtonList[i].widget as HintInfoAlert;	
				var tw:Tween = ButtonList[i].tw as Tween;
				
				if( item && tw )
				{
					if( ButtonList[i].isNew )
					{
						ButtonList[i].isNew = false;
					}
					else
					{
						var targetX:int = ( ButtonNum - useNum + 1 + i )*item.width;
						tw.quickSet( { duration:_movieTime , props:{ x:targetX } } );
						tw.reset();
						
						tw.paused = false;
					}
					
				}
			}
		}
	}
	
}
