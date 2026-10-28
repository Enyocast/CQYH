SDOA_Client_SDK_Sample_GDI  Version 0.9.1.320

Completion date
===============
2010.03.26

Overview
----
This document describes the SDOA client SDK integration sample for the GDI graphics engine.

Directory contents
--------
|- 1.NormalGDIWin
|- 2.NormalGDIWin_LoadIGW
|- 3.NormalGDIWin_ShowLoginDialog
|- 4.NormalGDIWin_LauncherGame
|- 5.Tut04_Lights_GameTestLoginDirect
|- 6.NormalGDIWin_HostLauncherGame


Integration and configuration
--------------
1.NormalGDIWin
A standard Windows window provided as a code comparison baseline.

2.NormalGDIWin_LoadIGW
Adds code to load the IGW component to 1.NormalGDIWin.

3.NormalGDIWin_ShowLoginDialog
Completes graphics integration on top of 2.NormalGDIWin_LoadIGW and displays IGW.

4.NormalGDIWin_LauncherGame
Adds game loading to 3.NormalGDIWin_ShowLoginDialog. Build 5.Tut04_Lights_GameTestLoginDirect first.

5.Tut04_Lights_GameTestLoginDirect
Demonstrates cross-process login: log in through GDI, then start the game without another login dialog.

6.NormalGDIWin_HostLauncherGame
Demonstrates drawing the IGW interface in a specified window.


Version history
---------
2010-03-26	Released the first version
