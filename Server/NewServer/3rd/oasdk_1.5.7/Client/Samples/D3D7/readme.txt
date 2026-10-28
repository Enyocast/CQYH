SDOA_Client_SDK_Sample_D3D7  Version 0.9.1.320

Completion date
===============
2010.03.02

Overview
----
This document describes the SDOA client SDK integration sample for the D3D7 graphics engine.


Directory contents
--------
|- 1.D3D7CppTest
|- 2.D3D7CppTest_LoadIGW
|- 3.D3D7CppTest_ShowIGW
|- 4.D3D7CppTest_ShowLoginDialog

Integration and configuration
--------------
ddraw.h and d3d.h are included with VS2003; VS2005 requires a separate D3D7 SDK download.

1.D3D7CppTest
Implements a basic D3D7 graphics environment. No integration code is included, to provide a baseline for comparison.

2.D3D7CppTest_LoadIGW
Adds code to load the IGW component to 1.D3D7CppTest.

3.D3D7CppTest_ShowIGW
Completes graphics integration on top of 2.D3D7CppTest_LoadIGW and displays IGW.

4.D3D7CppTest_ShowLoginDialog
Adds a login dialog to 3.D3D7CppTest_ShowIGW.

Version history
---------

