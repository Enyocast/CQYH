SDOA_Client_SDK_Sample_D3D9  Version 0.9.1.320

Completion date
===============
2010.02.26

Overview
----
This document describes the SDOA client SDK integration sample for the D3D9 graphics engine.

Directory contents
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

Integration and configuration
--------------
Adapted from Microsoft DirectX SDK\Sample\C++\Direct3D\
Install Microsoft DirectX SDK 9.0 and verify the $(DXSDK_DIR) environment variable.
For example:
E:\Program Files\Microsoft DirectX SDK (April 2007)\

1.EmptyProject
Copied from Program Files\Microsoft DirectX SDK (April 2007)\Samples\C++\Direct3D\EmptyProject
No integration code is included, to provide a baseline for comparison.

2.EmptyProject_LoadIGW
Adds code to load the IGW component to 1.EmptyProject.

3.EmptyProject_ShowIGW
Completes graphics integration on top of 2.EmptyProject_LoadIGW and displays IGW.

4.EmptyProject_ShowLoginDialog
Adds a login dialog to 3.EmptyProject_ShowIGW.

4.EmptyProject_ShowLoginDialog_InstallHook
Uses hooks for graphics integration on top of 4.EmptyProject_ShowLoginDialog.

5.EmptyProject_GameAudio
Adds a game volume control callback to 4.EmptyProject_ShowLoginDialog.

5.EmptyProject_GameAudio_Cfg
Extends 5.EmptyProject_GameAudio to demonstrate adjusting UI effects with ISDOACfg.

6.EmptyProject_Balance
Adds balance queries to 5.EmptyProject_GameAudio.

7.Tut05_Textures_BackbufferRect
Demonstrates using part of the back buffer in windowed mode while keeping the integrated UI functional.

Version history
---------
2009-04-10	Released the SDK preview
2009-05-14  4.EmptyProject_ShowLoginDialog: added sample code that simulates passing character information.
2010-02-26  Added 4.EmptyProject_ShowLoginDialog_InstallHook
                5.EmptyProject_GameAudio_Cfg
                7.Tut05_Textures_BackbufferRect



