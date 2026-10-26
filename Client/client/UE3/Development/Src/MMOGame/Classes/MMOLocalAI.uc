

/** 自动化本地AI处理，模拟玩家进行常规操作 */

class MMOLocalAI extends Object
    config(MMOLocalAI)
	native
	dependson(TypeDefine);

// 单条任务
struct native LOCAL_AI_TASK
{
    var ELocalAICheckType check_type;
    var int task_id;
};

// 登陆名和密码（如果有值表示启动此功能，否则关闭此功能）
var config string UserName;
var config string Password;
var config string ConnectIP;
// 强制新建一个角色进行测试
var config bool NewPlayer;
// 强制从指定主线任务开始做起
var config int TaskStartID;
// 做几个任务
var config int TaskDoCount;
// 是否是详细任务模式
var config bool TaskDetailMode;

// 本应用是否运行中
var bool AIWorking;
// 任务列表
var array< LOCAL_AI_TASK > WorkTask;

native function Run();                      // 事务处理逻辑
native function OnNetClose();               // 网络关闭的时候
native function OnLogoEnd();                // 启动LOGO播放结束
native function OnLoginResult(bool ret);    // 登陆结果
native function OnCreateRole();             // 创建角色
native function OnMapLoaded();              // 地图加载结束
native function OnTaskState();              // 任务状态发生变化

cpptext
{
	static class UMMOLocalAI* Instance();
}

DefaultProperties
{
    AIWorking = false;
}
