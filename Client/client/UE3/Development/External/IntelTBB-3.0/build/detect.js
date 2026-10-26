// Copyright 2005-2011 Intel Corporation.  All Rights Reserved.
//
// The source code contained or described herein and all documents related
// to the source code ("Material") are owned by Intel Corporation or its
// suppliers or licensors.  Title to the Material remains with Intel
// Corporation or its suppliers and licensors.  The Material is protected
// by worldwide copyright laws and treaty provisions.  No part of the
// Material may be used, copied, reproduced, modified, published, uploaded,
// posted, transmitted, distributed, or disclosed in any way without
// Intel's prior express written permission.
//
// No license under any patent, copyright, trade secret or other
// intellectual property right is granted to or conferred upon you by
// disclosure or delivery of the Materials, either expressly, by
// implication, inducement, estoppel or otherwise.  Any license under such
// intellectual property rights must be express and approved by Intel in
// writing.

function doWork() {
		var WshShell = WScript.CreateObject("WScript.Shell");

		var fso = new ActiveXObject("Scripting.FileSystemObject");

		var tmpExec;
		tmpExec = WshShell.Run("cmd /c echo int main(){return 0;} >detect.c", 0, true);

		// The next block deals with GCC (MinGW)
		if ( WScript.Arguments.Count() > 1 && WScript.Arguments(1) == "gcc" ) {
			if ( WScript.Arguments(0) == "/arch" ) {
				// Get predefined macros
				tmpExec = WshShell.Run("cmd /C gcc -dM -E detect.c > detect.map", 0, true);
				var file = fso.OpenTextFile("detect.map", 1, 0);
				var defs = file.readAll();
				file.Close();

				//detect target architecture
				var intel64=/x86_64|amd64/mgi;
				var ia32=/i386/mgi;
				if ( defs.match(intel64) ) {
					WScript.Echo( "intel64" );
				} else if ( defs.match(ia32) ) {
					WScript.Echo( "ia32" );
				} else {
					WScript.Echo( "unknown" );
				}
			}
			else if ( WScript.Arguments(0) == "/runtime" ) {
				tmpExec = WshShell.Exec("gcc -dumpversion");
				WScript.Echo( "mingw"+tmpExec.StdOut.ReadLine() );
			}
			return;
		}

		//Compile binary
		tmpExec = WshShell.Exec("cl /MD detect.c /link /MAP");
		while ( tmpExec.Status == 0 ) {
			WScript.Sleep(100);
		}

		if ( WScript.Arguments(0) == "/arch" ) {
			//read compiler banner
			var clVersion = tmpExec.StdErr.ReadAll();
			
			//detect target architecture
			var intel64=/AMD64|EM64T|x64/mgi;
			var ia64=/IA-64|Itanium/mgi;
			var ia32=/80x86/mgi;
			if ( clVersion.match(intel64) ) {
				WScript.Echo( "intel64" );
			} else if ( clVersion.match(ia64) ) {
				WScript.Echo( "ia64" );
			} else if ( clVersion.match(ia32) ) {
				WScript.Echo( "ia32" );
			} else {
				WScript.Echo( "unknown" );
			}
		}

		if ( WScript.Arguments(0) == "/runtime" ) {
			//read map-file
			var map = fso.OpenTextFile("detect.map", 1, 0);
			var mapContext = map.readAll();
			map.Close();
			
			//detect runtime
			var vc71=/MSVCR71\.DLL/mgi;
			var vc80=/MSVCR80\.DLL/mgi;
			var vc90=/MSVCR90\.DLL/mgi;
			var vc100=/MSVCR100\.DLL/mgi;
			var psdk=/MSVCRT\.DLL/mgi;
			if ( mapContext.match(vc71) ) {
				WScript.Echo( "vc7.1" );
			} else if ( mapContext.match(vc80) ) {
				WScript.Echo( "vc8" );
			} else if ( mapContext.match(vc90) ) {
				WScript.Echo( "vc9" );
			} else if ( mapContext.match(vc100) ) {
				WScript.Echo( "vc10" );
			} else if ( mapContext.match(psdk) ) {
				// Our current naming convention assumes vc7.1 for 64-bit Windows PSDK
				WScript.Echo( "vc7.1" ); 
			} else {
				WScript.Echo( "unknown" );
			}
		}
}

function doClean() {
		var fso = new ActiveXObject("Scripting.FileSystemObject");
		// delete intermediate files
		if ( fso.FileExists("detect.c") )
			fso.DeleteFile ("detect.c", false);
		if ( fso.FileExists("detect.obj") )
			fso.DeleteFile ("detect.obj", false);
		if ( fso.FileExists("detect.map") )
			fso.DeleteFile ("detect.map", false);
		if ( fso.FileExists("detect.exe") )
			fso.DeleteFile ("detect.exe", false);
		if ( fso.FileExists("detect.exe.manifest") )
			fso.DeleteFile ("detect.exe.manifest", false);
}

if ( WScript.Arguments.Count() > 0 ) {
	
	try {
		doWork();
	} catch( error ) {
		WScript.Echo( "unknown" );
	}
	doClean();

} else {

	WScript.Echo( "/arch or /runtime should be set" );
}

