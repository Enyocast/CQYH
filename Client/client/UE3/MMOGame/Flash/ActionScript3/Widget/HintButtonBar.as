package ActionScript3.Widget{


	import ActionScript3.MyPanel;
	import ActionScript3.MyActivePanel;
	import flash.external.ExternalInterface;
	
	
	import scaleform.clik.controls.Button;
	import scaleform.clik.core.UIComponent;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	import scaleform.clik.controls.UILoader;
	
	import flash.utils.getTimer;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	


	public class HintButtonBar extends MyPanel
	{	
		const TimeFrame:Number = 200;//时间侦听间隔
		const ButtonNum:int = 6;
		
		
		var timerCountDown:Timer = new Timer(TimeFrame);
		var LastTime:uint = 0;
		var ButtonList:Array;
		
		var Used:int = 0;

		
		var ButtonInfoList:Array;

		override protected  function configUI():void 
		{
			
			
			ButtonInfoList = new Array(ButtonNum);
			
			ButtonList = new Array;
			super.configUI();
			
			ExternalInterface.call( "RegisterHintButtonBar" , this );
      
			for( var i:int = 0 ; i < ButtonNum ; i++ )
			{
				var item:Button = this.getChildByName("HintButton"+i) as Button;
				item.itemid = i;
				item.addEventListener(MouseEvent.CLICK,clickHintButton , false, 0 ,true ); 
				
				item.visible = false;
				ButtonList.push( item );
			}
			
			//test
			//addNewButton( "aaa" , 40 , true );
			//addNewButton( "bbb" , 30 , false );
			//removeButton(1);
			
			
			timerCountDown.addEventListener(TimerEvent.TIMER, timeUpHandle);
			timerCountDown.start();
			
			LastTime = getTimer();
			
			
		}
		
		function clickHintButton( e:Event )
		{
			if( e.target is Button )
			{
				ExternalInterface.call( "ASHintButtonClick" , ( e.target as Button ).itemid );
			}
		}
		
		function timeUpHandle( e:TimerEvent )
		{
			var CurrentTime:Number = getTimer();
			var DeltaTime:int = CurrentTime - LastTime;
			LastTime = CurrentTime;
			
			for( var i:int = 0 ; i < Used ; i++ )
			{
				var item:Button = ButtonList[i] as Button;
				
				if( item )
				{
					var time_tf:TextField = item.textField;
					
					//trace(ButtonInfoList[i].ad);
					if( ButtonInfoList[i].isAdd )
					{
						ButtonInfoList[i].time += DeltaTime;
					}
					else
					{
						ButtonInfoList[i].time -= DeltaTime;
					}
					
					if( time_tf )
					{
						time_tf.text = getTimeString( ButtonInfoList[i].time );
					}
				}
			}
		}
		
		override public function UpdatePos( stageW:Number , stageH:Number )
		{
			this.x = stageW - 250;
		}
		
		public function addNewButton( iconResouce:String , time:int , ad:Boolean ):int
		{
			time = time*1000;
			
			if( Used < ButtonNum )
			{
				var item:Button = ButtonList[Used] as Button;
				
				
				if( item )
				{
					
					var icon:UILoader = item.getChildByName("itemIconLoader_mc") as UILoader;
										
					if(icon)
					{
						icon.source = iconResouce;						
					}
					var time_tf:TextField = item.textField;
					
					if( time_tf )
					{
						time_tf.text = getTimeString( time );
					}
					item.visible = true;
					
					
					ButtonInfoList[Used] = { iconName:iconResouce , time:time , isAdd:ad  };
					Used++;	
					return ( Used - 1 );
				}
				
			}
			
			return -1;
		}
		
		
		function getTimeString( time:int ):String
		{
			var unit:String;
			var val:int;
			
			time = time/1000;
			
			if( time > 86400 )
			{
				unit = "d";
				val = time/86400;
			}
			else if( time > 3600 )
			{
				unit = "h";
				val = time/3600;
			}
			else if( time > 60)
			{
				unit = "m";
				val = time/60;
			}
			else if( time > 0 )
			{
				unit = "s";
				val = time;
			}
			else
			{
				unit = "s";
				val = 0;
			}
			
			return String(val) + unit;
		}
		
		public function removeButton( pos:int )
		{
			
			ButtonInfoList.splice( pos , 1 );
			Used--;
			updateButton();
		}

		function updateButton()
		{
			for( var i:int = 0 ; i < ButtonNum ; i++ )
			{
				var item:Button = ButtonList[i] as Button;				
								
				if( item )
				{
					if( i >= Used )
					{
						
						item.visible = false;
					}
					else
					{
						var icon:UILoader = item.getChildByName("itemIconLoader_mc") as UILoader;
										
						if(icon)
						{
							icon.source = ButtonInfoList[i].iconName;						
						}
						var time_tf:TextField = item.textField;
					
						if( time_tf )
						{
							time_tf.text = getTimeString(  ButtonInfoList[i].time );
						}
						item.visible = true;					
					}

					
				}
			}
		}
		
	}

}