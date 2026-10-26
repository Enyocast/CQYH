SDOA_Client_SDK_Sample_DDraw  Version 0.9.1.320

完成时间
===============
2009.04.10

概述
----
本文档为SDOA CS架构客户端接入SDK：DDraw图形引擎客户端接入源码示例

目录说明
--------
|- 1.DDrawTest32Bit
|- 2.DDrawTest32Bit_LoadIGW
|- 3.DDrawTest32Bit_ShowIGW
|- 4.DDrawTest32Bit_ShowLoginDialog

接入配置说明
--------------
请安装Microsoft DirectX SDK并确保环境变量$(DXSDK_DIR)的正确、或者使之可正确找到ddraw.h
例如：
E:\Program Files\Microsoft DirectX SDK (April 2007)\

1.DDrawTest32Bit
未添加任何接入相关代码，用于方便做对比

2.DDrawTest32Bit_LoadIGW
在原1.DDrawTest32Bit基础上增加加载IGW组件代码

3.DDrawTest32Bit_ShowIGW
在2.DDrawTest32Bit_LoadIGW基础上，完成图形部分接入，可以正确显示IGW

4.DDrawTest32Bit_ShowLoginDialog
在3.DDrawTest32Bit_ShowIGW基础上增加显示登录对话框

版本历史
---------
2009-04-10	发布SDK preview版本
2009-05-14  4.DDrawTest32Bit_ShowLoginDialog 增加模拟传入角色信息演示代码


