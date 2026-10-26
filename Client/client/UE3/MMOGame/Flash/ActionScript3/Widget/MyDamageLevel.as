package ActionScript3.Widget
{
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.geom.Rectangle;
	import flash.text.Font;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.utils.Timer;
	import flash.utils.getDefinitionByName;
	import ActionScript3.MyDamageNumber;

	import scaleform.clik.core.UIComponent;
	import UI_DamageLevel.DamageLevelAS3.MyAttackDamage;

	public class MyDamageLevel extends UIComponent
	{
		//var _CommonNumberClass:Class;
		var _AttackClass:Class;
		//var _AttackedClass:Class;
		var _DodgeClass:Class;
		var _MissClass:Class;
		var _ImmunityClass:Class;
		var _ParryClass:Class;
		var _CriticalClass:Class;
		var _CriticaledClass:Class;
		var _BlockClass:Class;
		//var _ExpClass:Class;
		//var _MoneyClass:Class;
		//var _RestoreClass:Class;
		//var _MoneyExClass:Class;

		var _AttackPool:Array = [];
		var _AttackPoolMax:int = 20;
		var _AttackPoolIndex:int = 0;
		var _ExpPoolMax:int = 15;

		var _ExpPool:Array = [];
		var _ExpPoolIndex:int = 0;
		var _AllCDTime:Number = -1;
		//var _FontName:FontName = new FontName();

		//public var sprite:Sprite;
		/*public function addStringToField( tField:TextField, txtString:String, txtFormat:TextFormat):void
		{
		var index = tField.length;
		tField.appendText(txtString);
		tField.setTextFormat(txtFormat,index,tField.length);
		}*/

		override protected function configUI():void
		{
			super.configUI();
			_AttackClass = getDefinitionByName("Attack") as Class;//白色数字
			//_AttackedClass = getDefinitionByName("Attacked") as Class;//红色数字
			_CriticalClass = getDefinitionByName("Critical") as Class;//黄色数字
			_CriticaledClass = getDefinitionByName("Criticaled") as Class;//红色数字
			_DodgeClass = getDefinitionByName("Dodge") as Class;//闪避
			_MissClass = getDefinitionByName("Miss") as Class;//未命中
			_ImmunityClass = getDefinitionByName("Immunity") as Class;//免疫
			_ParryClass = getDefinitionByName("Parry") as Class;//招架
			_BlockClass = getDefinitionByName("Block") as Class;//格挡
			//_ExpClass = getDefinitionByName("XpGet") as Class;//经验值获得
			//_MoneyClass = getDefinitionByName("GlodGet") as Class;//金币获得
			//_RestoreClass = getDefinitionByName("HpGet") as Class;//加血

			//_MoneyExClass = getDefinitionByName("MoneyEx") as Class;//金币获得
			var i:uint = 0;
			var tempMc:MyAttackDamage;
			var tempExp:MyDamageNumber;
			for (i=0; i<_AttackPoolMax; i++)
			{//伤害数组
				tempMc = new _AttackClass   as MyAttackDamage;
				tempMc.removeEnable = false;
				tempMc.visible = false;
				this.addChild( tempMc );
				_AttackPool.push(tempMc);
			}
			for (i=0; i<_ExpPoolMax; i++)
			{//经验数组
				tempExp = new _CriticalClass   as MyDamageNumber;
				tempExp.removeEnable = false;
				tempExp.visible = false;
				this.addChild( tempExp );
				_ExpPool.push(tempExp);
			}
			tempMc = null;
			tempExp = null;
			this.mouseChildren = false;
			this.mouseEnabled = false;
			//AddNewDodge(0,0,0,0,0,0);
			//AddNewExp(0,0,100,1,1,1);
			//AddNewAttack(0,0,23456,0,0,0);
			//this.AddMoneyEx(1,0,0,1000,"绑金",1,1,1);
			//AddNewCritical(0,0,123,0,0,0);
		}

		public function UpdatePos(DeltaTime:Number)
		{
			var child:MyDamageNumber = null;
			if (_AllCDTime>0)
			{
				_AllCDTime -=  DeltaTime;

				for (var i:uint=0; i<numChildren; i++)
				{
					child = (getChildAt(i) as MyDamageNumber);
					if (child && child.UpdatePos(DeltaTime) == false)
					{
						child.RemoveAll(this);
					}
				}
			}
		}

		public function AddLevel( tempMc:MyDamageNumber , Posx:int , Posy:int ,X:Number,Y:Number,Z:Number)
		{
			tempMc.posX = X;
			tempMc.posY = Y;
			tempMc.posZ = Z;
			tempMc.MaskUI = false;
			tempMc.StartShow(this);
			tempMc.bNeedUpdate = true;
			_AllCDTime = 1.5;
		}


		/*public function AddEjectLevel( tempMc:MyEjectNumber , Posx:int , Posy:int ,X:Number,Y:Number,Z:Number)
		{
		tempMc.posX = X;
		tempMc.posY = Y;
		tempMc.posZ = Z;
		tempMc.MaskUI = false;
		tempMc.StartShow(this);
		tempMc.bNeedUpdate = true;
		
		tempMc.visible = true;
		}*/

		public function AddNewAttack( Posx:int , Posy:int , value:int , X:Number , Y:Number , Z:Number)
		{
			var tempMc:MyDamageNumber = getAttackIndex();
			if (tempMc)
			{
				tempMc.count = value;
				tempMc.NumType = 1;
				tempMc.TxtType = 0;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "AddNewAttack" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		public function AddNewAttacked( Posx:int , Posy:int , value:int , X:Number , Y:Number , Z:Number)
		{
			var tempMc:MyDamageNumber = getExpIndex();
			if (tempMc)
			{
				tempMc.count = value;
				tempMc.NumType = 2;
				tempMc.TxtType = 0;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "AddNewAttacked" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		public function AddNewDodge( Posx:int , Posy:int , value:int , X:Number , Y:Number , Z:Number)
		{
			if ( _DodgeClass == null )
			{
				return;
			}
			var tempMc:MyDamageNumber = new _DodgeClass   as MyDamageNumber;

			if (tempMc)
			{
				tempMc.count = value;
				tempMc.TxtType = 5;//闪避
				tempMc.NumType = 0;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "Dodge" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		public function AddNewMiss( Posx:int , Posy:int  , X:Number , Y:Number , Z:Number)
		{
			if ( _MissClass == null )
			{
				return;
			}
			var tempMc:MyDamageNumber = new _MissClass   as MyDamageNumber;

			if (tempMc)
			{
				tempMc.TxtType = 0;
				tempMc.NumType = 0;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "Miss" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		public function AddNewParry( Posx:int , Posy:int  , X:Number , Y:Number , Z:Number)
		{
			if ( _ParryClass == null )
			{
				return;
			}
			var tempMc:MyDamageNumber = new _ParryClass   as MyDamageNumber;

			if (tempMc)
			{
				tempMc.TxtType = 0;
				tempMc.NumType = 0;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "Parry" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		public function AddNewImmunity( Posx:int , Posy:int  , X:Number , Y:Number , Z:Number)
		{
			if ( _ImmunityClass == null )
			{
				return;
			}
			var tempMc:MyDamageNumber = new _ImmunityClass   as MyDamageNumber;

			if (tempMc)
			{
				tempMc.TxtType = 0;
				tempMc.NumType = 0;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "Immunity" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		public function AddNewBlock( Posx:int , Posy:int , value:int , X:Number , Y:Number , Z:Number)
		{
			if ( _BlockClass == null )
			{
				return;
			}
			var tempMc:MyDamageNumber = new _BlockClass   as MyDamageNumber;

			if (tempMc)
			{
				tempMc.count = value;
				tempMc.TxtType = 0;
				tempMc.NumType = 0;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "Block" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		public function AddNewCritical( Posx:int , Posy:int , value:int , X:Number , Y:Number , Z:Number)
		{
			var tempMc:MyDamageNumber = getExpIndex();
			if (tempMc)
			{
				tempMc.count = value;
				tempMc.TxtType = 0;
				tempMc.NumType = 0;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "Critical" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		public function AddNewCriticaled( Posx:int , Posy:int , value:int , X:Number , Y:Number , Z:Number)
		{
			var tempMc:MyDamageNumber = getExpIndex();
			if (tempMc)
			{
				tempMc.count = value;
				tempMc.NumType = 2;
				tempMc.TxtType = 0;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "Criticaled" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		public function AddNewExp( Posx:int , Posy:int , value:int , X:Number , Y:Number , Z:Number)
		{
			var tempMc:MyDamageNumber = getExpIndex();
			if (tempMc)
			{
				tempMc.count = value;
				tempMc.NumType = 3;
				tempMc.TxtType = 1;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "XpGet" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		public function AddNewMoney( Posx:int , Posy:int , value:int , moneyName:String, X:Number , Y:Number , Z:Number)
		{
			var tempMc:MyDamageNumber = getExpIndex();
			if (tempMc)
			{
				tempMc.count = value;
				tempMc.NumType = 3;
				tempMc.TxtType = 2;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "GlodGet" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		public function AddNewRestore( Posx:int , Posy:int , value:int , X:Number , Y:Number , Z:Number)
		{
			var tempMc:MyDamageNumber = getExpIndex();

			if (tempMc)
			{
				tempMc.count = value;
				tempMc.TxtType = 0;
				tempMc.NumType = 5;
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "HpGet" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		public function AddMoneyEx( moneyType:int, Posx:int , Posy:int , value:int , moneyName:String, X:Number , Y:Number , Z:Number)
		{
			var tempMc:MyDamageNumber = getExpIndex();

			if (tempMc)
			{
				tempMc.count = value;
				tempMc.NumType = 3;
				if (moneyName=="成就点")
				{
					tempMc.TxtType = 3;
				}
				else if (moneyName=="道义值")
				{
					tempMc.TxtType = 4;
					tempMc.NumType = 4;
				}
				else if(moneyName=="公会贡献")
				{
					tempMc.TxtType = 9;
					tempMc.NumType = 4;
				}
				else if (moneyName=="名师值")
				{
					tempMc.TxtType = 8;
					tempMc.NumType = 4;
				}
				else if (moneyName=="经验值")
				{
					tempMc.TxtType = 1;
				}
				else
				{
					tempMc.TxtType = 2;
				}
				ExternalInterface.call( "ASSetTweenData", tempMc.gObj, "GlodGet" );
				AddLevel( tempMc , Posx , Posy ,X,Y,Z);
			}
		}

		private function getAttackIndex():MyDamageNumber
		{
			if (_AttackPool==null)
			{
				return null;
			}
			var tempMc:MyDamageNumber = _AttackPool[_AttackPoolIndex];//  new _AttackedClass as MyDamageNumber;
			_AttackPoolIndex++;
			if (_AttackPoolIndex>=_AttackPoolMax)
			{
				_AttackPoolIndex = 0;
			}
			return tempMc;
		}

		private function getExpIndex():MyDamageNumber
		{
			if ( _ExpPool == null )
			{
				return null;
			}
			var tempMc:MyDamageNumber = _ExpPool[_ExpPoolIndex];
			_ExpPoolIndex++;
			if (_ExpPoolIndex>=_ExpPoolMax)
			{
				_ExpPoolIndex = 0;
			}
			return tempMc;
		}
	}
}