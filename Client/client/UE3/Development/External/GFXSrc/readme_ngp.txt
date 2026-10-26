Autodesk Scaleform 4.0
NGP Compilation Instructions

Steps for using Visual Studio:
---------------------

1.  If you are a source customer, open the following solution:
    
	Projects\NGP\Msvc90\SDK\GFx 4.0 NGP SDK.sln
	
	If you are an eval/lib customer, open the following solution:
	
	Projects/NGP/Msvc90/Demos/GFx 4.0 NGP Demos.sln
	
2.  Select desired build configuration and build with Visual Studio


Steps for running the Scaleform demos
---------

The following sample players are included in both the Demo and Source solution:

  FxPlayerTiny        A simple reference for beginning an integration with Scaleform
  FxPlayerMobile      A more advanced player that includes a drop-down HUD

  The buttons on the FxPlayerMobile HUD are:
   Arrows                  - Change file (the initial file will be displayed out of rotation)
   Stopwatch               - Watch white: Show FPS; Arrows white: Fast forward
   Pause                   - Pauses or resumes the movie
   Status area:
     FPS                   - Frame rate if enabled
     Tri DP Mesh Mask      - Triangles, draw primitives, and masks
     Advance/Display       - Advance and display times
     Memory                - Memory allocated, used
   Rectangle with corners  - Toggle view clipping
   Two rectangles          - Batch profile mode
   Three rectangles        - Fill profiling mode
   
Place your content (SWFs, etc) in a folder named "FxPlayer" in the root of your executable directory.  For example:

Bin\NGP\Msvc90\FxPlayer

Make sure that one of your SWFs is named "flash.swf" as that is the default startup file that FxPlayerMobile looks for.  
Please note that if this is an evaluation package, place gfxlicense.txt in the "FxPlayer" directory as well.

Image Formats Supported
-----------------------

Here’s what we support:

								GXT File	DDS File	PVR File
DXT 1/3/5 (also called BC1/2/3)	Yes			No			No
PVR *image*						Yes			N/A			Yes
Uncompressed					Yes			Yes			Yes


Autodesk Scaleform Support
http://www.scaleform.com/support