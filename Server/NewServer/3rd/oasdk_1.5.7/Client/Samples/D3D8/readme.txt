SDOA_Client_SDK_Sample_D3D8  Version 0.9.1.320

完成时间
===============
2010.02.26

概述
----
本文档为SDOA CS架构客户端接入SDK：D3D8图形引擎客户端接入源码示例

目录说明
--------
|- 1.Tut04_Lights
|- 2.Tut04_Lights_LoadIGW
|- 3.Tut04_Lights_ShowIGW
|- 4.Tut04_Lights_ShowLoginDialog
|- 4.Tut04_Lights_ShowLoginDialog_InstallHook


接入配置说明
--------------
修改自\Samples\C++\Direct3D\Tutorials\Tut04_Lights
请安装Microsoft DirectX SDK8.1并确保环境变量$(DXSDK81_DIR)的正确
例如：
D:\ClearSoft\dx81

1.Tut04_Lights
修改自\Samples\C++\Direct3D\Tutorials\Tut04_Lights
并增加设备丢失的处理代码，未添加任何接入相关代码，用于方便做对比

2.Tut04_Lights_LoadIGW
在原1.Tut04_Lights基础上增加加载IGW组件代码

3.Tut04_Lights_ShowIGW
在2.Tut04_Lights_LoadIGW基础上，完成图形部分接入，可以正确显示IGW

4.Tut04_Lights_ShowLoginDialog
在3.Tut04_Lights_ShowIGW基础上增加显示登录对话框

4.Tut04_Lights_ShowLoginDialog_InstallHook
在4.Tut04_Lights_ShowLoginDialog基础上使用Hook方式替换图形接入

版本历史
---------
2009-04-10	发布SDK preview版本
2009-05-14  4.Tut04_Lights_ShowLoginDialog 增加模拟传入角色信息演示代码
2010-02-26	增加4.Tut04_Lights_ShowLoginDialog_InstallHook演示通过hook方式接入图形部分


