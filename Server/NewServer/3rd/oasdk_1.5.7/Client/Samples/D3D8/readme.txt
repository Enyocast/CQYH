SDOA_Client_SDK_Sample_D3D8  Version 0.9.1.320

Completion date
===============
2010.02.26

Overview
----
This document describes the SDOA client SDK integration sample for the D3D8 graphics engine.

Directory contents
--------
|- 1.Tut04_Lights
|- 2.Tut04_Lights_LoadIGW
|- 3.Tut04_Lights_ShowIGW
|- 4.Tut04_Lights_ShowLoginDialog
|- 4.Tut04_Lights_ShowLoginDialog_InstallHook


Integration and configuration
--------------
Adapted from \Samples\C++\Direct3D\Tutorials\Tut04_Lights
Install Microsoft DirectX SDK 8.1 and verify the $(DXSDK81_DIR) environment variable.
For example:
D:\ClearSoft\dx81

1.Tut04_Lights
Adapted from \Samples\C++\Direct3D\Tutorials\Tut04_Lights
Adds device loss handling. No integration code is included, to provide a baseline for comparison.

2.Tut04_Lights_LoadIGW
Adds code to load the IGW component to 1.Tut04_Lights.

3.Tut04_Lights_ShowIGW
Completes graphics integration on top of 2.Tut04_Lights_LoadIGW and displays IGW.

4.Tut04_Lights_ShowLoginDialog
Adds a login dialog to 3.Tut04_Lights_ShowIGW.

4.Tut04_Lights_ShowLoginDialog_InstallHook
Uses hooks for graphics integration on top of 4.Tut04_Lights_ShowLoginDialog.

Version history
---------
2009-04-10	Released the SDK preview
2009-05-14  4.Tut04_Lights_ShowLoginDialog: added sample code that simulates passing character information.
2010-02-26	Added 4.Tut04_Lights_ShowLoginDialog_InstallHook to demonstrate graphics integration using hooks.


