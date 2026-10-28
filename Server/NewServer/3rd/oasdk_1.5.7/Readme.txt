SDOA_SDK  Version SDOA_SDK_CSO.1.5.7.20100407.VSL
(2010-04-12)
===============
Overview
-------------
This Shanda Online product provides services including Quanquan, authentication, and billing. The SDK includes components, samples, demonstrations, and documentation for integrating applications.
 
Directory contents
-------------
 |-  Client               //Client components
 |   |-  bin              // IGW client program files
 |   |-  Samples          //IGW integration examples for different rendering technologies
 |   |-  SDK              //Header files
 |   |-  Tools		  //Tools
 |-  Server               //Server components
 |   |-  linux            //Linux components
 |   |   |-  bin          //Program files
 |   |   |-  samples      //Module integration examples
 |   |-  win32            //Windows components
 |   |   |-  bin          //Program files
 |   |   |-  samples       //Module integration examples
 |-  DEMO                  //Demo
 |   |-  GameClient(IGW)   // IGW demo

 Integration and configuration
-------------
1 Running the SDK demo requires Internet access, including at least these IP addresses: 210.51.30.84, 210.51.31.208,210.51.31.209;
2 Before integration development, register at http://open.sdo.com to obtain an SPID and register the application to obtain an AppID;
3 Before debugging integration code, register server details on the development platform at http://open.sdo.com.
4 When debugging or testing integration, ensure Internet access to at least these IP addresses: 210.51.30.84, 210.51.31.208,210.51.31.209;
5 Before launching the application, register server details on the operations platform at http://open.sdo.com.

 
Version history
-------------
Version:SDOA_SDK_CSO.1.5.7.20100407.VSL
Release date:2010-04-12
Fixes
Server components:
Server component version:sdoa4serverdll_REL_1_3_7_20100122

Client components:
Updated IGW from 0.9.1.248 to 0.9.1.330
(1). Special accounts could not purchase items (present in version 272).
(2). The bank security control download URL was invalid in full-screen games (present in version 272 and production).
(3). The bank-card top-up plugin failed to open correctly (present in version 272).


Version:SDOA_SDK_CSO.1.5.7.20100326.VSL
Release date:2010-03-26
New features:
Server components:
None

Client components:
None

Fixes
Server components:
None

Client components:
1. Replaced iAgent.exe with a new version.
   The original failed Trend Micro antivirus checks; potentially problematic code was removed before recompiling and signing.
2. Changed the help link in GameWidget.xml.
   The link now points to the new Quanquan website.
3. Repackaged with an updated VerInfo.xml version information file.


Version:SDOA_SDK_CS.1.3.7.20100122.VSL
Release date:2010-02-03
New features:
Server components:
SDOA4SERVER now writes daily authentication success statistics to AUTHENSTAT*.log.
The fields are time, authentication count, successes, failures, and success rate.
Counts accumulate from the start of the day to the recorded time.

Client components:
None

Fixes
Server components:
(1).Fixed an sdoa4server crash when Release was called immediately after initialize;
(2) Fixed order case handling on Linux.

Client components:
None


Version:SDOA_SDK_CS.1.3.6.0828.002.VSW
Release date:2009-11-25
Fixes
Server components:
(1). Fixed negative oas_key values on network connection errors.

Client components:
None

Documentation:
None


Version:SDOA_SDK_CS.1.3.7.1124.VSL
Release date:2009-11-24
Fixes
Server components:
1. Switched to the unified configuration server.
The OA unified configuration system provides flexible configuration for OA components. Its server exposes an HTTP service, and its C++ client is wrapped in sdoa4server for transparent use by game servers.
Because it only supplies configuration and contains no business logic, it can be used by any system that dynamically retrieves XML configuration.

Client components:
None

Documentation:SDOA_CS_API_Manual_1.3.7.0924.chm
Changes:
1. Added an asynchronous response callback.
2. Added IGW automatic update instructions and precautions.
3. Documented the cross-process client login interface.
4. Documented the IGW GDI interface.
5. Added error code tables for client functions and server return values.
6. Made sample code more realistic and instructive and improved its comments.
7. Added IGW interface customization instructions.


Version:SDOA_SDK_CS.1.3.6.0828
Release date:2009-08-28
Fixes
Client components:
1. Added a login dialog that posts a message to the main game window when the login button is clicked.
2. Fixed remembering a different account after an account was already saved.
3. Fixed the Quanquan interface failing to display under D3D8 on some low-specification systems, mainly those with weaker graphics cards (specific graphics drivers may be required).
4. Fixed a process hang when switching input methods in some circumstances.
5. Changed tooltips to remain hidden when the window is unavailable.
6. Updated the authentication component to 1.0.4.0 (UDP authentication timeout changed to 10 seconds).


Version:SDOA_SDK_CS.1.3.6.0827
Release date:2009-08-27
Fixes
Client components:
1. Disabled the nonfunctional context menu on the fixed bar.
2. Fixed loading the local default configuration when the fixed bar cannot read server configuration.
3 Fixed client refresh after application ordering changes published by the backend (outside the fixed bar).
4. Fixed errors on exit after updates in some games.
5. Fixed refresh of pinned sidebar items under certain conditions.
6. Added left-button dragging to move the update window.
7. Integrated recent DDraw optimizations, improving overall performance by about 5%.


Version:SDOA_SDK_CS.1.3.5.0814
Release date:2009-08-14
New features:
Server components:
1 Added an interface for asynchronous response callbacks.
Client components:
1.IGW automatic updates
2.IGW full-screen input method
3.Application encryption
4.Backend ordering of applications in the fixed bar
5.SDG advertising data collection
Client improvements:
1.Adjusted configuration loading to allow multiple login methods in games such as Legend and World of Legend.
2.DDraw optimizations
3.Updated password recovery and change flows for greater security and convenience.
4.Updated account registration for a faster, easier process.

Fixes:
Server components:
1 Fixed a timer in the authentication module causing 100% CPU usage.
2 Fixed a core dump on FreeBSD startup.
3 Fixed slow authentication shutdown.
4 Fixed a destruction error after unsuccessful initialization.
5 Formatted message logs for database ingestion.
6 Fixed heartbeat issues.
Client components:
1.Fixed images failing to display in some applications.
2.Fixed operation of ICBC U-Shield devices.
3.Fixed issues caused by frequent switching between minimized and normal mode in Kung Fu Kid.


Documentation:SDOA_CS_API_Manual_1.3.5.0814 SDOA_CS_API_Manual_English_1.3.2.0723.chm


Version:SDOA_SDK_1.1.1.0618
Release date:2009-06-18
New features:
Server components:
None
Client components:
1 Added a property allowing scripts to control focus easily.
2 Added the SDOAInfo property to IGW objects for the SDOATest widget to display integration information.
3 Added support for CAS script navigation.

Fixes:
Server components:
None
Client components:
1 Fixed lost messages when quickly dragging the minimized Quanquan icon.
2 Fixed ModifyAppInfo failing to update game region and server information.
3 Fixed focus not returning to the game after using Back in a full-screen IE window.
4 Fixed incorrect display when switching full-screen mode after changing themes.
5 Fixed text inputs responding twice to Enter; for example, registration could succeed while reporting an incorrect verification code.
6 Fixed the web window not resizing with the game window in windowed mode (set the default type in the theme's FullScrWebBrowser.xml to TScriptFullIEForm).
7 Fixed missing objects and compatibility problems in some default windows.
8 Fixed five registration bugs:
（1） The registration page's friend referral feature failed.
（2） Password guidance on the registration page was incorrect.
（3） The friend referral selection box behaved incorrectly.
（4） Friend referrals could register with invalid email addresses.
（5） The registration password help tooltip displayed incorrectly.
Fixed release bugs:
（1） Tab did not work when the SDO homepage was opened full-screen from windowed mode.
（2） Some SDO sites had compatibility issues when opened in a window from full-screen mode.
（3） Opening the SDO homepage in a window failed in the IGW version test application.
（4） Drop-down controls behaved incorrectly in the IGW version test application.
Documentation:SDOA_CS_API_Manual_1.1.1.0618.chm


Version:SDOA_SDK_1.1.0.0603
Release date:2009-06-03
New features:
Server components:
1 Added an include directory and sdoa4server.ini under server.
2 Added the returned error code to configuration retrieval failure logs.
3 Added a multi-currency billing order type.
4 Added sample code showing the important step of passing character information.
5 Added revision histories to all sample readme.txt files.
6 Added binaries built with GCC 3.4.
Client components:
1 Added a mechanism for games to customize login dialog prompts.
2 Added configuration to make selected windows non-draggable.
3 Added configuration to hide the Quanquan toolbar before login (which the backend can enforce).
4 Added support for USB security tokens.
5 Added support for the new SDOA authentication method.
6 Added color adjustment for non-system themes.
7 Adjusted the login screen and added advertising images.
8 Expanded brightness and saturation settings to allow more colors.
9 Restricted URLs opened with OpenWindow; production defaults to allowing only *.sdo.com sites.
10 Added an adult indicator to client results using the existing LoginResult.IDCard field (0 for a minor, 1 for an adult).
11 The interface remains compatible with older versions and can be used by replacing the old release.

Fixes:
Server components:
1 Changed the authentication client to asynchronous operation to improve throughput.
2 Fixed encryption and decryption of long orders.
3 Adjusted the INI file for integrators.
4 Standardized release version numbering.
5 Fixed misaligned data in the authentication module.
6 Fixed encryption and decryption failures for some long orders and increased the signature data limit to 4,000 bytes.
7 Fixed a scheduled task causing 100% CPU usage.
8 Fixed the authorization server returning only some matching GSINFO messages.
9 Changed the configuration file passed by the C++ sample oasample.cpp from ConfClt.conf to sdoa4server.ini.
Client components:
1 Fixed windows potentially failing to close after an onCloseQuery event.
2 Fixed the certificate selection dialog failing to appear when required by the server (online banking support).
3 Allowed confirmation dialogs on full-screen IE pages (online banking support).
4 Fixed an OpenWindow call failure reported by Kingsoft.
5 Fixed interface font sizes being affected by system DPI settings.
6 Fixed several bank-card issues in the top-up application.
7 Fixed a token verification dialog remaining open after login failure and causing subsequent verification to fail.
8 Updated the prompt for random-number token verification.
9 Fixed several errors in the SDOA 1.0 API.
10 Fixed heartbeat and server configuration retrieval issues under certain conditions.
11 Fixed the login dialog failing to open under certain conditions.
12 Fixed IGW failing to load because of directory permissions.
13 Fixed inaccurate TaskBar positioning.


Version:SDOA_SDK_1.0RC
Release date:2009-04-30
New features:
None (initial release)
Fixes:
None (initial release)

