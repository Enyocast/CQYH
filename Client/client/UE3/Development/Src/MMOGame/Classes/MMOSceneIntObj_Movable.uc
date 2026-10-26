class MMOSceneIntObj_Movable extends SkeletalMeshActor
	placeable
	ClassGroup(__MMO__);

var(MMOSceneObj) SplineActor MovePath <DisplayName="MovePath">;
var(MMOSceneObj) SplineActor MovePathLast <DisplayName="MovePathLast">;

// 不循环就是往返运动
var(MMOSceneObj) bool LoopPath <DisplayName="LoopPath">;

var(MMOSceneObj) bool AlignPathNormal <DisplayName="AlignPathNormal">;
var(MMOSceneObj) bool AlignPathDirection <DisplayName="AlignPathDirection">;

var(MMOSceneObj) float StartPosOffsetPct <DisplayName="StartPosOffsetPct">;
var(MMOSceneObj) float MoveSpeed <DisplayName="MoveSpeed">;

// 当前移动方向
var(MMOSceneObj) bool CurrentMoveForward;

// 当前路径点对象
var SplineActor CurrentTargetPathNode;

// 上一个或是下一个有效的节点
var SplineActor LastValidNode;

// 当前路径点索引
var int CurrentTargetPathNodeIdx;

simulated event PostBeginPlay()
{
	super.PostBeginPlay();
}

function vector GetMeshWorldPosition()
{
	return Location;
}

function SetMeshWorldPosition(Vector pos)
{
	SetLocation(pos);
}

state InActive
{
	event BeginState(Name PreviousStateName)
	{
		// PlayAnimation("InActive");
	}

	event EndState(Name NextStateName)
	{
	}

Begin:
}

state Activate
{
	event BeginState(Name PreviousStateName)
	{
		//`log("______ Movable Active");
		CurrentTargetPathNode = MovePath;
		CurrentTargetPathNodeIdx = 0;
	}

	event EndState(Name NextStateName)
	{
	}

	function vector UpdateForward(float deltaTime)
	{
		local Vector moveDir;
		//local SplineActor prevNode;

		if(CurrentTargetPathNode != none)
		{
			// 先保存是一个节点
			if(CurrentTargetPathNode.LinksFrom.Length > 0)
			{
				LastValidNode = CurrentTargetPathNode.LinksFrom[0];
			}

			if(VSize(CurrentTargetPathNode.Location - GetMeshWorldPosition()) < 60)
			{
				// 如果还有下一个节点就继续，否则返回
				if(CurrentTargetPathNode.Connections.Length > 0)
				{
					CurrentTargetPathNode = CurrentTargetPathNode.Connections[0].ConnectTo;
				}
				else
				{
					CurrentTargetPathNode = none;
				}
			}

			if(CurrentTargetPathNode != none)
			{
				moveDir = Normal(CurrentTargetPathNode.Location - GetMeshWorldPosition());
			}
			
			if(CurrentTargetPathNode == none)
			{
				// 切换到往回移动
				CurrentMoveForward = false;
				CurrentTargetPathNode = LastValidNode;
			}
		}

		return moveDir;


		//`log("______ CurrentMoveForward" @VSize(EndNode.Location - curPos));
	}

	function vector UpdateBackward(float deltaTime)
	{
		local Vector moveDir;
		//local SplineActor nextNode;

		if(CurrentTargetPathNode != none)
		{
			// 先保存下一个节点
			if(CurrentTargetPathNode.Connections.Length > 0)
			{
				LastValidNode = CurrentTargetPathNode.Connections[0].ConnectTo;
			}

			if(VSize(CurrentTargetPathNode.Location - GetMeshWorldPosition()) < 60)
			{
				// 如果前面还有节点就继续往回移动
				if(CurrentTargetPathNode.LinksFrom.Length > 0)
				{
					CurrentTargetPathNode = CurrentTargetPathNode.LinksFrom[0];
				}
				else
				{
					CurrentTargetPathNode = none;
				}
			}

			if(CurrentTargetPathNode != none)
			{
				moveDir = Normal(CurrentTargetPathNode.Location - GetMeshWorldPosition());
			}
			
			if(CurrentTargetPathNode == none)
			{
				// 切换到往前移动
				CurrentMoveForward = true;
				CurrentTargetPathNode = LastValidNode;
			}
		}
		
		return moveDir;
	}

	// 往返移动，返回前进方向
	function vector UpdateCruiseMovement(float deltaTime)
	{
		// 先判定方向
		if(CurrentMoveForward)
		{
			return UpdateForward(deltaTime);
		}
		else
		{
			return UpdateBackward(deltaTime);
		}
	}

	// 循环移动，返回前进方向
	function vector UpdateLoopMovement(float deltaTime)
	{
		// 先判定方向
		if(CurrentMoveForward)
		{
			return UpdateLoopForward(deltaTime);
		}
		else
		{
			return UpdateLoopBackward(deltaTime);
		}
	}

	function vector UpdateLoopForward(float deltaTime)
	{
		local Vector moveDir;

		if(CurrentTargetPathNode != none)
		{
			if(VSize(CurrentTargetPathNode.Location - GetMeshWorldPosition()) < 60)
			{
				// 如果还有下一个节点就继续，否则返回
				if(CurrentTargetPathNode.Connections.Length > 0)
				{
					CurrentTargetPathNode = CurrentTargetPathNode.Connections[0].ConnectTo;
				}
				else
				{
					CurrentTargetPathNode = none;
				}
			}

			if(CurrentTargetPathNode != none)
			{
				moveDir = Normal(CurrentTargetPathNode.Location - GetMeshWorldPosition());
			}
			
			if(CurrentTargetPathNode == none)
			{
				CurrentTargetPathNode = MovePath;
			}
		}

		return moveDir;
	}

	function vector UpdateLoopBackward(float deltaTime)
	{
		local Vector moveDir;

		if(CurrentTargetPathNode != none)
		{
			if(VSize(CurrentTargetPathNode.Location - GetMeshWorldPosition()) < 60)
			{
				// 如果前面还有节点就继续往回移动
				if(CurrentTargetPathNode.LinksFrom.Length > 0)
				{
					CurrentTargetPathNode = CurrentTargetPathNode.LinksFrom[0];
				}
				else
				{
					CurrentTargetPathNode = none;
				}
			}

			if(CurrentTargetPathNode != none)
			{
				moveDir = Normal(CurrentTargetPathNode.Location - GetMeshWorldPosition());
			}
			
			if(CurrentTargetPathNode == none)
			{
				CurrentTargetPathNode = MovePathLast;
			}
		}
		
		return moveDir;
	}

	simulated event Tick(float deltaTime)
	{		
		local Vector curPos, moveDir;//, curDir;
		curPos = GetMeshWorldPosition();

		if(LoopPath)
		{
			moveDir = UpdateLoopMovement(deltaTime);
		}
		else
		{
			moveDir = UpdateCruiseMovement(deltaTime);
		}
	
		if(AlignPathDirection)
		{
			//curDir = vector(Rotation);
			//curDir = moveDir - curDir; 
			//SetRotation(Rotation + Rotator(curDir * deltaTime));
			SetRotation(Rotator(moveDir));
		}

		curPos += moveDir * MoveSpeed * deltaTime;
		
		SetMeshWorldPosition(curPos);

		//`log("______ Movable Tick" @CurrentMoveForward);
	}

Begin:
	//Sleep( PlayAnimation( AnimNamePrepare ) );
}

auto state Prepare
{
	event BeginState(Name PreviousStateName)
	{
		//SetMeshWorldPosition(StartNode.Location + (EndNode.Location - StartNode.Location) * StartPosOffsetPct);
	}

	event EndState(Name NextStateName)
	{
	}


	event Tick( float DeltaTime )
	{
		//if( RefVolume != none )
		//	RefVolume.Update( DeltaTime );
	}

Begin:
	//if( RefVolume != none )
	//	RefVolume.EnableVolume( );
	//Sleep( PlayAnimation( AnimNameActivate ) );
	GotoState( 'Activate' );
}

state ResetAll
{
Begin:
	GotoState( 'InActive' );
}

state Dead
{

}

DefaultProperties
{
	Begin Object Name=SkeletalMeshComponent0
		SkeletalMesh=SkeletalMesh'EditorMeshes.SkeletalMesh.DefaultSkeletalMesh'
	End Object

	//Begin Object Class=CylinderComponent Name=CollisionCylinder
	//	CollisionRadius=+0034.000000
	//	CollisionHeight=+0078.000000
	//	BlockNonZeroExtent=true
	//	BlockZeroExtent=true
	//	BlockActors=true
	//	CollideActors=true
	//End Object
	//CollisionComponent=CollisionCylinder
	//CylinderComponent=CollisionCylinder
	//Components.Add(CollisionCylinder)

	MoveSpeed=500
	AlignPathNormal=true
	AlignPathDirection=false
	CurrentMoveForward=true
	LoopPath=false

	bStatic=false
	bCollideActors=True
	bBlockActors=True
	bMovable=true
	//bAlwaysRelevant=true
	//bReplicateMovement=true
	//bOnlyDirtyReplication=true
	RemoteRole=ROLE_None
	bWorldGeometry=false
}
