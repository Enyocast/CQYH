// 用于切换客户端发送移动协议给服务器
// 处理在船上、或是其它静止状态下的移动模拟

class SeqAct_SendPlayerHackMove extends SequenceAction;

event Activated()
{	
	if( InputLinks[0].bHasImpulse )
		class'WorldInfo'.static.GetWorldInfo().GetALocalPlayerController().PushState('HackMove');
	else
		class'WorldInfo'.static.GetWorldInfo().GetALocalPlayerController().PopState();
	
	ActivateOutputLink(0);
}

DefaultProperties
{
	ObjName="Send Player Hack Move"
	ObjCategory="MMO Server Old"
	
	InputLinks.Empty
	InputLinks(0)=(LinkDesc="Start")
	InputLinks(1)=(LinkDesc="Stop")

	OutputLinks.Empty
	OutputLinks(0)=( LinkDesc="Out" )

	VariableLinks.Empty
}
