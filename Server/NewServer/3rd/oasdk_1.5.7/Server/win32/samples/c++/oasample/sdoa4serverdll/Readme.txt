osapdll files and directories:
osapdll
      --sdoa4server.ini			file: sample configuration; update the IP address and SDK log path
      
      --include				directory: headers required by sdoa4server
	--sndabase.h			file: common macros for consistent function definitions
	--sdoa4server.h 		file: SDK header containing authentication and billing interfaces
      
      --windows				directory: Windows SDK and COM components
	--COM				directory: COM component
	  --SDOA4ServerCOM.dll  	file: COM component
	
	--DLL				directory: DLL and corresponding library files
	  --SDOA4ServerDLL.dll		file: release DLL
	  --SDOA4ServerDLL.lib  	file: release DLL import library
	  --SDOA4ServerDLLd.dll 	file: debug DLL
	  --SDOA4ServerDLLd.lib 	file: debug DLL import library
     
     --linux				directory: Linux .so and .a files compiled with GCC 3.23
	
	--GCC3				directory: .so and .a files compiled with GCC 3.x
	  --libSDOA4Server.so   	file: shared library
	  --libSDOA4Serverlib.a 	file: static library
	
	--GCC4				directory: .so and .a files compiled with GCC 4.x
	  --libSDOA4Server.so   	file: shared library
	  --libSDOA4Serverlib.a 	file: static library
	
	--JAVA				directory: JAR package
	  --
	
	--PHP				directory: PHP extension
	  --


