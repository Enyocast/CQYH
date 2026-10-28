SDOA_Client_SDK_Sample_DDraw  Version 0.9.1.320

Completion date
===============
2009.04.10

Overview
----
This document describes the SDOA client SDK integration sample for the DDraw graphics engine.

Directory contents
--------
|- 1.DDrawTest32Bit
|- 2.DDrawTest32Bit_LoadIGW
|- 3.DDrawTest32Bit_ShowIGW
|- 4.DDrawTest32Bit_ShowLoginDialog

Integration and configuration
--------------
Install the Microsoft DirectX SDK and verify $(DXSDK_DIR), or otherwise make ddraw.h available.
For example:
E:\Program Files\Microsoft DirectX SDK (April 2007)\

1.DDrawTest32Bit
No integration code is included, to provide a baseline for comparison.

2.DDrawTest32Bit_LoadIGW
Adds code to load the IGW component to 1.DDrawTest32Bit.

3.DDrawTest32Bit_ShowIGW
Completes graphics integration on top of 2.DDrawTest32Bit_LoadIGW and displays IGW.

4.DDrawTest32Bit_ShowLoginDialog
Adds a login dialog to 3.DDrawTest32Bit_ShowIGW.

Version history
---------
2009-04-10	Released the SDK preview
2009-05-14  4.DDrawTest32Bit_ShowLoginDialog: added sample code that simulates passing character information.


