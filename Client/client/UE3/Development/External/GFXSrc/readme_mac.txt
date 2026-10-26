Autodesk Scaleform 
Compilation Instructions for MacOS X (10.5 and 10.6)

This package includes Scaleform libs, and a sample player for MacOS using
Cocoa and GL.

zlib is expected to be provided by the system.

Note: Some versions of MacOS ship with a buggy make. Build & install
GNU make 3.81 or use the included make (Bin/MacOS/make).


To build GFx (and samples) for both powerpc and x86:
   $ make P=MacOS

Executables are placed in Bin/MacOS.

To build GFx (and samples) for a single cpu:
   $ make P=MacOS/powerpc
or
   $ make P=MacOS/i686

Executables are placed in Bin/MacOS-powerpc or Bin/MacOS-i686.
See readme_make.txt for more information about the Scaleform build system.

The included sample player can be run from the Finder or the command line.
From the command line:
   $ Bin/MacOS/FxPlayer.app/Contents/MacOS/FxPlayer <swf file>

From the Finder, drag a swf file to the Dock icon, the executable, or the
player's window.


Evaluation Versions

If this is an evaluation version, place the license key in "gfxlicense.txt"
in the current or home directory.


Autodesk Scaleform Support
http://www.scaleform.com/support