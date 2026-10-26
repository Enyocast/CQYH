
// 停止当前的场景中播放中的Matinee动画，条件：Matinee的'允许中断'属性在工具中被设为TRUE
// 停止后继续执行所有输出结点

class SeqEvent_PlayerMatineeStop extends SequenceEvent
	native;

cpptext
{
	virtual void Activated();
}

DefaultProperties
{
    MaxTriggerCount = 0;

	ObjName="Player Matinee Stop 'ESC'"
	ObjCategory="Player"
}
