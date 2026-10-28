// this cpp source file is generated automatically by tools, please do not manually modify.
#include "stdafx.h"
#include "errdef.h"

// @brief
// You may see this phenomenon :
// variables with "STR_" as their prifix, maybe have a suffix
// the suffix means which format output symbols have appeared in function like printf
// Sample :  "%s" turns to be "_S"
namespace  ERR_ENTER_GS
{
    const INT32 ID_NOERROR = 0;
    const TCHAR* STR_NOERROR = _SDTSource2T("GBK", "操作成功");

    const INT32 ID_ENTERGAMEFAILED = 1;
    const TCHAR* STR_ENTERGAMEFAILED = _SDTSource2T("GBK", "进入游戏失败");

    const INT32 ID_EXISTEDINGAMESERVER = 2;
    const TCHAR* STR_EXISTEDINGAMESERVER = _SDTSource2T("GBK", "已在游戏中");

    const INT32 ID_TASKLOADSTATUSFAILD = 3;
    const TCHAR* STR_TASKLOADSTATUSFAILD = _SDTSource2T("GBK", "加载任务信息失败");
}

namespace  ERR_MOVE
{
    const INT32 ID_NOERROR = 0;
    const TCHAR* STR_NOERROR = _SDTSource2T("GBK", "操作成功");

    const INT32 ID_TIMEOUT = 1;
    const TCHAR* STR_TIMEOUT = _SDTSource2T("GBK", "超时");

    const INT32 ID_MOREPKG = 2;
    const TCHAR* STR_MOREPKG = _SDTSource2T("GBK", "发包过多");

    const INT32 ID_DIRERR = 3;
    const TCHAR* STR_DIRERR = _SDTSource2T("GBK", "方向值范围错误");

    const INT32 ID_MOVEERR = 4;
    const TCHAR* STR_MOVEERR = _SDTSource2T("GBK", "移动错误");

    const INT32 ID_GETOBJERR = 5;
    const TCHAR* STR_GETOBJERR = _SDTSource2T("GBK", "OBJID错误");

    const INT32 ID_MOVETRYERR = 6;
    const TCHAR* STR_MOVETRYERR = _SDTSource2T("GBK", "移动类型错误");

    const INT32 ID_NOTACTIVE = 7;
    const TCHAR* STR_NOTACTIVE = _SDTSource2T("GBK", "角色当前不可活动");
}

namespace  ERR_CHANGE_DIR
{
    const INT32 ID_NOERROR = 0;
    const TCHAR* STR_NOERROR = _SDTSource2T("GBK", "操作成功");

    const INT32 ID_OUTOFMAX = 1;
    const TCHAR* STR_OUTOFMAX = _SDTSource2T("GBK", "方向超出最大范围");
}

namespace  ERR_DRESS
{
    const INT32 ID_NOERROR = 0;
    const TCHAR* STR_NOERROR = _SDTSource2T("GBK", "操作成功");

    const INT32 ID_UNVALIDITEM = 1;
    const TCHAR* STR_UNVALIDITEM = _SDTSource2T("GBK", "请求装备无效");

    const INT32 ID_NOTMATCHTYPE = 2;
    const TCHAR* STR_NOTMATCHTYPE = _SDTSource2T("GBK", "请求装备类型不匹配");

    const INT32 ID_SRCPOSNOITEM = 3;
    const TCHAR* STR_SRCPOSNOITEM = _SDTSource2T("GBK", "源位置无装备");

    const INT32 ID_TARGETPOSHAVEITEM = 4;
    const TCHAR* STR_TARGETPOSHAVEITEM = _SDTSource2T("GBK", "目标位置有装备，无法装备");

    const INT32 ID_POSNOTCHANGE = 5;
    const TCHAR* STR_POSNOTCHANGE = _SDTSource2T("GBK", "位置没有修改");

    const INT32 ID_NOTMATCHOBJID = 6;
    const TCHAR* STR_NOTMATCHOBJID = _SDTSource2T("GBK", "OBJID不匹配");

    const INT32 ID_SPACENOTENOUGH = 7;
    const TCHAR* STR_SPACENOTENOUGH = _SDTSource2T("GBK", "包裹空间不足");

    const INT32 ID_SERVERCHECKINVALID = 8;
    const TCHAR* STR_SERVERCHECKINVALID = _SDTSource2T("GBK", "服务器检查包裹不合法");
}

namespace  ERR_SKILL_ATTACK
{
    const INT32 ID_NOERROR = 0;
    const TCHAR* STR_NOERROR = _SDTSource2T("GBK", "操作成功");

    const INT32 ID_USE_SKILL_FAILED = 1;
    const TCHAR* STR_USE_SKILL_FAILED = _SDTSource2T("GBK", "技能使用错误");
}

namespace  ERR_NPC_TALK
{
    const INT32 ID_NOERROR = 0;
    const TCHAR* STR_NOERROR = _SDTSource2T("GBK", "操作成功");
}

namespace  ERR_SYNC_TIME
{
    const INT32 ID_NOERROR = 0;
    const TCHAR* STR_NOERROR = _SDTSource2T("GBK", "操作成功");
}

namespace  ERR_TASK_OPERATE
{
    const INT32 ID_NOERROR = 0;
    const TCHAR* STR_NOERROR = _SDTSource2T("GBK", "任务操作成功");

    const INT32 ID_OPERATE_FAILED = 1;
    const TCHAR* STR_OPERATE_FAILED = _SDTSource2T("GBK", "任务操作错误");

    const INT32 ID_INSTANCE_TASK_FAILED = 2;
    const TCHAR* STR_INSTANCE_TASK_FAILED = _SDTSource2T("GBK", "副本任务错误");
}

namespace  ERR_ITEM_SMITHING
{
    const INT32 ID_NOERROR = 0;
    const TCHAR* STR_NOERROR = _SDTSource2T("GBK", "操作成功");

    const INT32 ID_NOCHANGE = 1;
    const TCHAR* STR_NOCHANGE = _SDTSource2T("GBK", "失败，属性不变");

    const INT32 ID_OVERFLOW = 2;
    const TCHAR* STR_OVERFLOW = _SDTSource2T("GBK", "失败，已达到最大锻造次数");

    const INT32 ID_DESTROY = 3;
    const TCHAR* STR_DESTROY = _SDTSource2T("GBK", "失败，且该道具已被销毁");
}

namespace  ERR_ITEM_USE
{
    const INT32 ID_NOERROR = 0;
    const TCHAR* STR_NOERROR = _SDTSource2T("GBK", "操作成功");

    const INT32 ID_DESTROY = 1;
    const TCHAR* STR_DESTROY = _SDTSource2T("GBK", "操作成功，且该道具已被销毁");

    const INT32 ID_INVALIDPARA = 2;
    const TCHAR* STR_INVALIDPARA = _SDTSource2T("GBK", "失败，非法参数");

    const INT32 ID_UNUSED = 3;
    const TCHAR* STR_UNUSED = _SDTSource2T("GBK", "失败，道具不可使用");
}

namespace  ERR_TRAP
{
    const INT32 ID_NOERROR = 0;
    const TCHAR* STR_NOERROR = _SDTSource2T("GBK", "操作成功");

    const INT32 ID_INTERNEL_ERROR = 1;
    const TCHAR* STR_INTERNEL_ERROR = _SDTSource2T("GBK", "内部错误");

    const INT32 ID_BAD_TRAP_ID = 2;
    const TCHAR* STR_BAD_TRAP_ID = _SDTSource2T("GBK", "机关ID错误");

    const INT32 ID_NOT_ONTIME = 3;
    const TCHAR* STR_NOT_ONTIME = _SDTSource2T("GBK", "触发时间错误");

    const INT32 ID_PLAYER_CAN_NOT_OPEN = 4;
    const TCHAR* STR_PLAYER_CAN_NOT_OPEN = _SDTSource2T("GBK", "玩家不能开启该机关");

    const INT32 ID_BAD_TRAP_STATUS = 4;
    const TCHAR* STR_BAD_TRAP_STATUS = _SDTSource2T("GBK", "机关目前不能开启");
}

