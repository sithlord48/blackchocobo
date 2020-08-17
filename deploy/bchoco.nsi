; bchoco.nsi
;
; This script is based on example2.nsi,
;
; It will install black chocobo into a directory make uninstall info,
; start menu entrys as well as file association for .ff7 files
;--------------------------------
!include "x64.nsh"
!include "FileAssociation.nsh"
 
; The name of the installer
Name "Black Chocobo"

; The file to write
OutFile "..\Black_Chocobo-continuous-win32-installer.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\Black_Chocobo"

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\Black_Chocobo" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

; Set License info
LicenseData "GPLV3.txt"
;--------------------------------

; Pages
Page license
Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------


; The stuff to install
Section "Black Chocobo(Required)"

  SectionIn RO
  SetOutPath $INSTDIR
  ; Set output path to the installation directory.
  File /r ..\Black_Chocobo-continuous-win32\*
  ; Put file there
  ;make menu entrys for main program else workpath is wrong?
  CreateDirectory "$SMPROGRAMS\Black_Chocobo"
  CreateShortCut "$SMPROGRAMS\Black_Chocobo\Black_Chocobo.lnk" "$INSTDIR\Black_Chocobo.exe" "" "$INSTDIR\Black_Chocobo.exe" 0  
  CreateShortCut "$SMPROGRAMS\Black_Chocobo\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0 
  ;set open with
  ${registerExtension} "$INSTDIR\Black_Chocobo.exe" ".ff7" "FF7 PC Savegame"
  ${registerExtension} "$INSTDIR\Black_Chocobo.exe" "ff7slot" "FF7 Switch Savegame"
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\Black_Chocobo "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Black_Chocobo" "DisplayName" "Black Chocobo"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Black_Chocobo" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Black_Chocobo" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Black_Chocobo" "NoRepair" 1
	
  WriteUninstaller "uninstall.exe"
  
  ;make menu entrys
 
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Black_Chocobo"
  DeleteRegKey HKLM "SOFTWARE\Black_Chocobo"
  DeleteRegKey HKCU "Software\blackchocobo"

  ; Remove files and uninstaller
  RMDir /r "$INSTDIR"
  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Black_Chocobo\*.*"

  ; Remove directories used
  ; remove open with
  ${unregisterExtension} ".ff7" "FF7 Savegame"

SectionEnd
