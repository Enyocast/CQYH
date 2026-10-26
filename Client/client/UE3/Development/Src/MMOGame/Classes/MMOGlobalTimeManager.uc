class MMOGlobalTimeManager extends Actor;

var array< ITimeEffectObj > RegisteredObjects;
var int Year;
var int Day;
var int Hour;
var float Min;

var float DemoDilation;

function RegisterObject( ITimeEffectObj obj )
{
	RegisteredObjects.AddItem( obj );
}

function UnRegisterObject( ITimeEffectObj obj )
{
	RegisteredObjects.RemoveItem( obj );
}

event Tick( float DeltaTime )
{
	local ITimeEffectObj obj;
	Min += DeltaTime * DemoDilation;
	if( Min >= 60 )
	{
		Min -= 60;
		++Hour;
		if( Hour >= 24 )
		{
			Hour -= 24;
			++Day;
			if( Day >= 365 )
			{
				Day -= 365;
				++Year;
			}
		}
	}

	foreach RegisteredObjects( obj )
	{
		obj.UpdateByTime( Day, Hour, Min );
	}
}

DefaultProperties
{
	DemoDilation=20.f
}
