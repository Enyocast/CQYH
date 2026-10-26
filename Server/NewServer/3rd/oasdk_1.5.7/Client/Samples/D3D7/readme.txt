SDOA_Client_SDK_Sample_D3D7  Version 0.9.1.320

完成时间
===============
2010.03.02

概述
----
本文档为SDOA CS架构客户端接入SDK：D3D7图形引擎客户端接入源码示例


目录说明
--------
|- 1.D3D7CppTest
|- 2.D3D7CppTest_LoadIGW
|- 3.D3D7CppTest_ShowIGW
|- 4.D3D7CppTest_ShowLoginDialog

接入配置说明
--------------
由于ddraw.h、d3d.h只在vs2003中有，vs2005需要另下载d3d7的sdk相关

1.D3D7CppTest
实现一个基础的d3d7图形环境，未添加任何接入相关代码，用于方便做对比

2.D3D7CppTest_LoadIGW
在原1.D3D7CppTest基础上增加加载IGW组件代码

3.D3D7CppTest_ShowIGW
在2.D3D7CppTest_LoadIGW基础上，完成图形部分接入，可以正确显示IGW

4.D3D7CppTest_ShowLoginDialog
在3.D3D7CppTest_ShowIGW基础上增加显示登录对话框

版本历史
---------

