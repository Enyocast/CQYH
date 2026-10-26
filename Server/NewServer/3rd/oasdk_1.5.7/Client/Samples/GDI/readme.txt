SDOA_Client_SDK_Sample_GDI  Version 0.9.1.320

完成时间
===============
2010.03.26

概述
----
本文档为SDOA CS架构客户端接入SDK：GDI图形引擎客户端接入源码示例

目录说明
--------
|- 1.NormalGDIWin
|- 2.NormalGDIWin_LoadIGW
|- 3.NormalGDIWin_ShowLoginDialog
|- 4.NormalGDIWin_LauncherGame
|- 5.Tut04_Lights_GameTestLoginDirect
|- 6.NormalGDIWin_HostLauncherGame


接入配置说明
--------------
1.NormalGDIWin
正常的Windows窗口，用于代码对比用。

2.NormalGDIWin_LoadIGW
在原1.NormalGDIWin基础上增加加载IGW组件代码

3.NormalGDIWin_ShowLoginDialog
在2.NormalGDIWin_LoadIGW基础上，完成图形部分接入，可以正确显示IGW

4.NormalGDIWin_LauncherGame
在3.NormalGDIWin_ShowLoginDialog基础上增加加载游戏代码，注意需要提前编译5.Tut04_Lights_GameTestLoginDirect

5.Tut04_Lights_GameTestLoginDirect
演示如何通过GDI模式登录，然后游戏实现无登录框的方式登录，即跨进程登录演示。

6.NormalGDIWin_HostLauncherGame
演示了如何将IGW界面绘制到指定窗口上


版本历史
---------
2010-03-26	发布第一个版本
