#½Å±¾°æ±¾ 1.0.3


#SetCompressor ${PRODUCT_COMPRESS_TYPE}
Name "setup_font"
OutFile "Setupfont.exe"
CRCCHECK force
XPStyle on
SetDatablockOptimize on

RequestExecutionLevel admin

!include "FontName.nsh"
!include "FontReg.nsh"
!include "WinMessages.nsh"
;!include "FontRegAdv.nsh"

Section "CQYHFonts"
  ;MessageBox MB_OK "$INSTDIR"

  ;SetOverwrite ifnewer
  
  File "msyh.ttf"
  File "SourceHanSansCN-Medium.otf"
;  File "SourceHanSansCN-Normal.otf"
;  File "Sourcemsyh.ttf"
;  File "Sourceygy.ttf"
;  File "Sourceygysf.ttf"
    
  StrCpy $FONT_DIR $FONTS
  SetOutPath "$FONTS"
  
  #!insertmacro FontNameVer
  #!insertmacro FontName "msyh.ttf"
  #MessageBox MB_OK ${FontName}
  ;CopyFiles /SILENT /FILESONLY $INSTDIR\msyh.ttf $FONTS
  ;!insertmacro InstallTTFFont "msyh.ttf"

  !insertmacro InstallTTFFont "msyh.ttf"
  
  !insertmacro FontNameVer
  !insertmacro FontName "SourceHanSansCN-Medium.otf"
  !insertmacro InstallOTFFont "SourceHanSansCN-Medium.otf"
  ;!insertmacro FontNameVer
  ;!insertmacro FontName "SourceHanSansCN-Normal.otf"
;  !insertmacro InstallOTFFont "SourceHanSansCN-Normal.otf"

  	;StrCmp $LANGUAGE ${LANG_TRADCHINESE} 0 +2
		;MessageBox MB_OK "Installing Traditional Chinese stuff"
	;StrCmp $LANGUAGE ${LANG_SIMPCHINESE} 0 +2
		;MessageBox MB_OK "Installing Simplified Chinese stuff"

;  !insertmacro InstallTTFFont "Sourcemsyh.ttf"
;  !insertmacro InstallTTFFont "Sourceygy.ttf"
;  !insertmacro InstallTTFFont "Sourceygysf.ttf"
  
  #MessageBox MB_OK $FONTS
  #!insertmacro FontName "SourceHanSansCN-Medium.otf"
  ;MessageBox MB_OK "$INSTDIR\SourceHanSansCN-Medium.otf"
  ;CopyFiles /SILENT /FILESONLY "$INSTDIR\SourceHanSansCN-Medium.otf" "$FONTS"
   ;CopyFiles /SILENT /FILESONLY "$EXEDIR\SourceHanSansCN-Medium.otf" "$FONTS"
  ;CopyFiles /SILENT /FILESONLY "E:\lixiaolong.bruce\08.Prog\font_pack\SourceHanSansCN-Medium.otf" "C:\Windows\Fonts"
  ;MessageBox MB_OK "$INSTDIR\SourceHanSansCN-Medium.otf"

  ;MessageBox MB_OK "$EXEDIR\SourceHanSansCN-Medium.otf"
  ;IfFileExists "$FONTS\SourceHanSansCN-Medium.otf" 0 +2
 	 ;MessageBox MB_OK "$FONTS\SourceHanSansCN-Medium.otf"
	;ExecShell "open" "$FONTS\SourceHanSansCN-Medium.otf"
	;ExecShell "open" "$INSTDIR\readme.txt"
	;Exec '"$FONTS\SourceHanSansCN-Medium.otf"'
	;ExecWait '"$FONTS\SourceHanSansCN-Medium.otf"' $0
	;!system '"%WINDIR%\notepad.exe" "${NSISDIR}\license.txt"'
;!system '"$FONTS\SourceHanSansCN-Medium.otf"'


;File "$FONTS\SourceHanSansCN-Medium.otf"

  ;FileOpen $0 "$FONTS\SourceHanSansCN-Medium.otf" r


  #SendMessage ${HWND_BROADCAST} ${WM_FONTCHANGE} 0 0 /TIMEOUT=5000
SectionEnd
