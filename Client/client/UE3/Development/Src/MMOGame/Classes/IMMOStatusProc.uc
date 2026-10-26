//
// 状态表现处理接口
//
interface IMMOStatusProc
	native;

event OnExecute(MMOActor actor);
native function Update(MMOActor actor);