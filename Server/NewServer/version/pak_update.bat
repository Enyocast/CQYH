cd ..\version
 
copy ..\bin\pak.exe .\
pak extract bin.pak

copy globalconfig.pak .\bin_%1\data				/Y
xcopy .\bin_%1 .\bin_test_test					/E/I/R/Y				