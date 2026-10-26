class MMOTorch extends Actor
	implements( ITimeEffectObj )
	placeable;

var( MMOTorch ) SkeletalMeshComponent   Stick           <DisplayName="Stick">;
var( MMOTorch ) PointLightComponent     SourceLight     <DisplayName="SourceLight">;
var( MMOTorch ) ParticleSystemComponent Effect          <DisplayName="Effect">;

var( MMOTorch ) name    LightSocket     <DisplayName="LightSocket",DynamicList="SocketList">;
var( MMOTorch ) name    EffectSocket    <DisplayName="EffectSocket",DynamicList="SocketList">;

var( MMOTorch ) int     TurnOnHour      <DisplayName="TurnOnHour">;
var( MMOTorch ) int     TurnOnMin       <DisplayName="TurnOnMin">;
var( MMOTorch ) float   BlendInTime     <DisplayName="BlendInTime">;
var( MMOTorch ) int     TurnOffHour     <DisplayName="TurnOffHour">;
var( MMOTorch ) int     TurnOffMin      <DisplayName="TurnOffMin">;
var( MMOTorch ) float   BlendOutTime    <DisplayName="BlendOutTime">;

var float   LightBrightnessMax;

var bool bFirstOnThanOff;

event PostBeginPlay( )
{
	if( Stick != none && SourceLight != none && Effect != none )
	{
		//AttachComponent( Stick );
		//AttachComponent( SourceLight );
		//AttachComponent( Effect );
		Stick.AttachComponentToSocket( SourceLight, LightSocket );
		Stick.AttachComponentToSocket( Effect, EffectSocket );
		Register( );

		if( TurnOnHour > TurnOffHour || ( TurnOnHour == TurnOffHour && TurnOnMin > TurnOffMin ) )
			bFirstOnThanOff = false;
		else
			bFirstOnThanOff = true;

		LightBrightnessMax = SourceLight.Brightness;
	}
}

event Destroyed()
{
	UnRegister();
}

//simulated function OnDestroy( SeqAct_Destroy Action )
//{
//	UnRegister( );
//}

function Register( )
{
	MMOGame(WorldInfo.Game).MyTimeManager.RegisterObject( self );
}

function UnRegister( )
{
	MMOGame(WorldInfo.Game).MyTimeManager.UnRegisterObject( self );
}

function UpdateByTime( int d, int h, float m )
{
}

state Off
{
	function UpdateByTime( int d, int h, float m )
	{
		if( h >= TurnOnHour && m > TurnOnMin )
		{
			if( bFirstOnThanOff )
			{
				if( h >= TurnOffHour && m > TurnOffMin )
					return;
			}
			GotoState( 'BlendIn' );
		}
	}

Begin:
	while( true )
	{
		Sleep( 1.f );
	}
}

state BlendIn
{
	function UpdateByTime( int d, int h, float m )
	{
		local int BlendTime;
		local float brightness;
		BlendTime = 60 * ( h - TurnOnHour ) + m - TurnOnMin;
		brightness = LightBrightnessMax * BlendTime / BlendInTime;
		SourceLight.SetLightProperties( brightness );
		if( BlendTime >= BlendInTime )
		{
			Effect.SetActive( true );
			GotoState( 'On' );
		}
	}

Begin:
	SourceLight.SetEnabled( true );
	while( true )
	{
		Sleep( 1.f );
	}
}

auto state On
{
	function UpdateByTime( int d, int h, float m )
	{
		if( h >= TurnOffHour && m > TurnOffMin )
		{
			if( !bFirstOnThanOff )
			{
				if( h >= TurnOnHour && m > TurnOnMin )
					return;
			}
			GotoState( 'BlendOut' );
		}
	}

Begin:
	while( true )
	{
		Sleep( 1.f );
	}
}

state BlendOut
{
	function UpdateByTime( int d, int h, float m )
	{
		local int BlendTime;
		local float brightness;
		BlendTime = 60 * ( h - TurnOffHour ) + m - TurnOffMin;
		brightness = LightBrightnessMax * ( 1.f - BlendTime / BlendOutTime );
		SourceLight.SetLightProperties( brightness );
		if( BlendTime >= BlendOutTime )
		{
			SourceLight.SetEnabled( false );
			Effect.SetActive( false );
			GotoState( 'Off' );
		}
	}

Begin:
	while( true )
	{
		Sleep( 1.f );
	}
}

DefaultProperties
{
	Begin Object Class=SpriteComponent Name=Sprite
		Sprite=Texture2D'EditorResources.S_NavP'
		HiddenGame=true
		HiddenEditor=false
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
	End Object
	Components.Add(Sprite)

	Begin Object Class=SkeletalMeshComponent Name=Stick1
	End Object
	Components.Add(Stick1)
	Stick=Stick1

	Begin Object Class=PointLightComponent Name=SourceLight1
	End Object
	Components.Add(SourceLight1)
	SourceLight=SourceLight1

	Begin Object Class=ParticleSystemComponent Name=Effect1
	End Object
	Components.Add(Effect1)
	Effect=Effect1

	LightSocket="LightSocket"
	EffectSocket="EffectSocket"
	TurnOnHour=19
	TurnOnMin=0
	BlendInTime=30
	TurnOffHour=5
	TurnOffMin=0
	BlendOutTime=30
}
