Autodesk Scaleform 4.0
Nintendo WiiU

Cygwin and GNU make version 3.81 are required for building the samples as well as the latest version of the following Cygwin packages:

binutils
gcc-g++

1) If necessary, create a Makeconfig file (from Makeconfig_example) in the top level GFx directory, containing:

   If the GHS installer did not set GHS_ROOT correctly, you must set that (either in the environment
   or in Makeconfig). CAFE_ROOT must also be set.

   These paths must be in posix format, with forward slashes and no drive letters
   with colons. Use /cygdrive/<drive letter>/...
   For example, if CAFE_SDK is installed to c:/CAFE_SDK: "CAFE_ROOT := /cygdrive/c/CAFE_SDK".

2) Store Flash content to be displayed in the sample player(s) to a folder named FxPlayer in the content directory.  For example:

   "cafe_sdk\data\disc\content\FxPlayer"

   Store Flash content to be displayed in the Kits (MenuKit and HudKit) to a folder named Kits in the content directory.  For example:
   
   "cafe_sdk\data\disc\content\Kits"
   
   Store Flash content to be displayed in the WiiU Demo to a folder named WiiUDemo in the content directory.  For example:

   cafe_sdk\data\disc\content\WiiUDemo

   If this is an Evaluation release, place the gfxlicense.txt file in the FxPlayer folder as well.

3) Build the libs and samples:
   $ make P=WiiU

4) Run Bin/WiiU/FxPlayer.rpx (or one with a Debug suffix if desired).

Most samples display on the TV only, but the touch screen can be used for input. Press +, -, L, and R
to switch Flash files. FxPlayerTiny displays two files if a DRC is connected (two commandline arguments).


Included Renderer support
-------------------------

The renderer source is in Src/Render/WiiU. Since there is no special region of memory for graphics, the
default WiiU::MemoryManager can be used which just allocates from the default GFx heap.

The compiled shaders are built into libgfxrender_wiiu.a.


GTX Support
-------------------------

GTX support is provided in our WiiU integration.  To use GTX files, first generate DDS images with gfxexport.  
Then run the DDS image files through “TexConv2.exe” (an executable that resides in the CAFE SDK).  Please note that
the newly created GTX images must have a DDS extension for the Scaleform players to properly load them.


Autodesk Scaleform Support
http://www.scaleform.com/support
