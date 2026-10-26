SDOA_Client_SDK_Sample_D3D9  Version 0.9.1.320

完成时间
===============
2010.02.26

概述
----
本文档为SDOA CS架构客户端接入SDK：D3D9图形引擎客户端接入源码示例

目录说明
--------
|- 1.EmptyProject
|- 2.EmptyProject_LoadIGW
|- 3.EmptyProject_ShowIGW
|- 4.EmptyProject_ShowLoginDialog
|- 4.EmptyProject_ShowLoginDialog_InstallHook
|- 5.EmptyProject_GameAudio
|- 5.EmptyProject_GameAudio_Cfg
|- 6.EmptyProject_Balance
|- 7.Tut05_Textures_BackbufferRect

接入配置说明
--------------
修改自Microsoft DirectX SDK\Sample\C++\Direct3D\
请安装Microsoft DirectX SDK9.0并确保环境变量$(DXSDK_DIR)的正确
例如：
E:\Program Files\Microsoft DirectX SDK (April 2007)\

1.EmptyProject	
从Program Files\Microsoft DirectX SDK (April 2007)\Samples\C++\Direct3D\EmptyProject 
直接复制而来，未添加任何接入相关代码，用于方便做对比

2.EmptyProject_LoadIGW
在原1.EmptyProject基础上增加加载IGW组件代码

3.EmptyProject_ShowIGW
在2.EmptyProject_LoadIGW基础上，完成图形部分接入，可以正确显示IGW

4.EmptyProject_ShowLoginDialog
在3.EmptyProject_ShowIGW基础上增加显示登录对话框

4.EmptyProject_ShowLoginDialog_InstallHook
在4.EmptyProject_ShowLoginDialog的基础上使用Hook方式替换图形接入

5.EmptyProject_GameAudio
在4.EmptyProject_ShowLoginDialog的基础上增加了接入控制游戏音量的回调

5.EmptyProject_GameAudio_Cfg
在5.EmptyProject_GameAudio的基础上增加演示如何使用ISDOACfg接口调整UI效果

6.EmptyProject_Balance
在5.EmptyProject_GameAudio的基础上增加查询余额功能

7.Tut05_Textures_BackbufferRect
演示在窗口模式下仅使用部分背景缓冲区域的图形处理方案，使接入后UI显示操作正常

版本历史
---------
2009-04-10	发布SDK preview版本
2009-05-14  4.EmptyProject_ShowLoginDialog 增加模拟传入角色信息演示代码
2010-02-26  增加4.EmptyProject_ShowLoginDialog_InstallHook
                5.EmptyProject_GameAudio_Cfg
                7.Tut05_Textures_BackbufferRect



