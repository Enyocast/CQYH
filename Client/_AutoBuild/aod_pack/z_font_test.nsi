#脚本版本 1.0.3


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

!macro InstallMyOTFFont FontFile MyFontName
  Push $0  
  Push $R0
  Push $R1
  Push $R2
  
  !define Index 'Line${__LINE__}'
  
; Get the Font's File name
  ${GetFileName} ${FontFile} $0
  !define FontFileName $0
  
  SetOutPath "$FONTS"
  #SetOutPath $FONT_DIR
  IfFileExists "$FONT_DIR\${FontFileName}" ${Index}
	#MessageBox MB_OK '${FontFile}'
    File '${FontFile}'

${Index}:
  ReadRegStr $R0 HKLM "SOFTWARE\Microsoft\Windows NT\CurrentVersion" "CurrentVersion"
  IfErrors "${Index}-9x" "${Index}-NT"

"${Index}-NT:"
  StrCpy $R1 "Software\Microsoft\Windows NT\CurrentVersion\Fonts"
  goto "${Index}-GO"

"${Index}-9x:"
  StrCpy $R1 "Software\Microsoft\Windows\CurrentVersion\Fonts"
  goto "${Index}-GO"

"${Index}-GO:"
  ClearErrors
  #!insertmacro FontName "$FONT_DIR\${FontFileName}"
  StrCpy $R2 "${MyFontName}"
  #pop $R2s
  #IfErrors 0 "${Index}-Add"
  #  MessageBox MB_OK "$R2"
  #  goto "${Index}-End"
    
#"${Index}-Add:"
#  StrCpy $R2 "$R2 (TrueType)"
#  ClearErrors
  ReadRegStr $R0 HKLM "$R1" "$R2"
  IfErrors 0 "${Index}-End"
    System::Call "GDI32::AddFontResourceA(t) i ('${FontFileName}') .s"
    WriteRegStr HKLM "$R1" "$R2" "${FontFileName}"
    goto "${Index}-End"

"${Index}-End:"

  !undef Index
  !undef FontFileName
  
  pop $R2
  pop $R1
  Pop $R0 
  Pop $0
!macroend


Section "CQYHFonts"
  ;MessageBox MB_OK "$INSTDIR"
  
  #File "msyh.ttf"
  #File "SourceHanSansCN-Medium.otf"

  
  SetOverwrite ifnewer
  SetOutPath "$FONTS"
  #File "*.*"
  #StrCpy $FONT_DIR $FONTS
  #!insertmacro FontNameVer
  #!insertmacro InstallTTFFont "AgeOfDawn.ttf"
  #!insertmacro InstallTTF "方正兰亭中黑_GBK.ttf"
  #!insertmacro InstallTTF "方正兰亭准黑_GBK.ttf"
  #!insertmacro InstallTTFFont "方正粗圆_GBK.ttf"
  #!insertmacro InstallTTFFont "方正隶二_GBK.ttf"
  #!insertmacro InstallTTFFont "方正隶变_GBK.ttf"
  #!insertmacro InstallTTFFont "方正魏碑_GBK.ttf"
  #!insertmacro InstallTTF "msyh.ttf"
  #!insertmacro InstallTTF "SourceHanSansCN-Medium.otf"
  
  !insertmacro InstallMyOTFFont "CQYH_Number.ttf" "CQYH_Number"
  #!insertmacro InstallTTF "方正兰亭中黑_GBK.ttf"
  #!insertmacro InstallTTF "方正兰亭准黑_GBK.ttf"
  #!insertmacro InstallMyOTFFont "方正粗圆_GBK.ttf" "方正粗圆_GBK (TrueType)"
  #!insertmacro InstallMyOTFFont "方正隶二_GBK.ttf" "方正隶二_GBK (TrueType)"
  #!insertmacro InstallMyOTFFont "方正隶变_GBK.ttf" "方正隶变_GBK (TrueType)"
  !insertmacro InstallMyOTFFont "方正隶二_GBK.ttf" "FZLiShu II-S06"
  !insertmacro InstallMyOTFFont "方正魏碑_GBK.ttf" "方正魏碑_GBK"
  
  #!insertmacro FontNameVer
  #!insertmacro FontName "msyh.ttf"
  #!insertmacro InstallTTFFont "msyh.ttf"
  #!insertmacro InstallMyOTFFont "msyh.ttf" "Microsoft YaHei (TrueType)"
  
  #!insertmacro FontName "SourceHanSansCN-Medium.otf"
  #!insertmacro InstallOTFFont "SourceHanSansCN-Medium.otf"
  !insertmacro InstallMyOTFFont "SourceHanSansCN-Medium.otf" "Source Han Sans CN Medium"
  
  #!insertmacro InstallFONFont "msyh.ttf" ${FontName}
  #!insertmacro InstallFONFont "SourceHanSansCN-Medium.otf"  ${FontName}
  
SectionEnd
