/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
class WindPointSourceComponent extends WindDirectionalSourceComponent
	native
	collapsecategories
	hidecategories(Object)
	editinlinenew;

var const DrawSphereComponent PreviewRadiusComponent;

var() interp float Radius;

// [ming@snda
var() bool	IsInteractive;
var() bool	IsBlast;

var float	InteractPower;
var float	PowerReduceRate;
var vector	OwnerLastLocation;
var vector	MoveDirection;
// ming@snda]

cpptext
{
protected:
	void UpdatePreviewRadius();
	// UActorComponent interface.
	virtual void Attach();
	virtual void UpdateTransform();
public:
	/**
	 * Creates a proxy to represent the wind source to the scene manager in the rendering thread.
	 * @return The proxy object.
	 */
	 virtual class FWindSourceSceneProxy* CreateSceneProxy() const;

	 // [ming@snda
	 void SetInteractive( UBOOL bInteractive );

	 void UpdateProxy( const FVector& InLocation, const FVector& InMoveDir, FLOAT InInteractPower );

	 virtual void Tick( FLOAT DeltaTime );

	 void TriggerBlast( FLOAT Strength = 1.f );
	 // ming@snda]
}

defaultproperties
{
	Radius=1024.0
	// [ming@snda
	IsInteractive=FALSE
	IsBlast=FALSE
	InteractPower=0.0
	PowerReduceRate=1.0
	OwnerLastLocation=(x=0,y=0,z=0)
	MoveDirection=(x=0,y=0,z=0)
	// ming@snda]
}
