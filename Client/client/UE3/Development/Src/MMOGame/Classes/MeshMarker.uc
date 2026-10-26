//
// 模型标记
//
class MeshMarker extends Actor
	native;

// 实际的模型组件
// var() StaticMeshComponent Mesh;

var ParticleSystemComponent ParComp;

DefaultProperties
{
// 	Begin Object Class=StaticMeshComponent Name=MarkerMesh
// 		BlockActors=false
// 		CollideActors=false
// 		BlockRigidBody=false
// 		//模型文件
// 		StaticMesh=StaticMesh'MMO_Player.Mesh.TargetLocationMark'
// 		//Scale3D=(X=0.3,Y=0.3,Z=0.3)
// 		Rotation=(Pitch=16384, Yaw=0, Roll=0)
// 	End Object
// 	Mesh = MarkerMesh
// 	CollisionComponent=MarkerMesh
// 	Components.Add(MarkerMesh)


	Begin Object Class=ParticleSystemComponent Name=ParEffect0
		//bAutoActivate=true
		//bIsActive=true
		Template=ParticleSystem'Fx_MouseClick.01Par.P_Click_01'
	End Object
	Components.Add(ParEffect0)
	ParComp=ParEffect0
}