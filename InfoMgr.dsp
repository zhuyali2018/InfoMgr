# Microsoft Developer Studio Project File - Name="InfoMgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=InfoMgr - Win32 Debug Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "InfoMgr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "InfoMgr.mak" CFG="InfoMgr - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "InfoMgr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "InfoMgr - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "InfoMgr - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE "InfoMgr - Win32 Release Unicode" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "InfoMgr - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zd /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /map /machine:I386 /MAPINFO:LINES /MAPINFO:EXPORTS
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "InfoMgr - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /GX /Zd /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /map /debug /machine:I386 /pdbtype:sept /MAPINFO:LINES /MAPINFO:EXPORTS
# SUBTRACT LINK32 /pdb:none /incremental:no

!ELSEIF  "$(CFG)" == "InfoMgr - Win32 Debug Unicode"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "InfoMgr___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "InfoMgr___Win32_Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "InfoMgr___Win32_Debug_Unicode"
# PROP Intermediate_Dir "InfoMgr___Win32_Debug_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /FD /GZ $(YCDBG) /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "InfoMgr - Win32 Release Unicode"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "InfoMgr___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "InfoMgr___Win32_Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "InfoMgr___Win32_Release_Unicode"
# PROP Intermediate_Dir "InfoMgr___Win32_Release_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zd /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /map /machine:I386 /out:"InfoMgr___Win32_Release_Unicode/InfoMgrU.exe" /MAPINFO:LINES /MAPINFO:EXPORTS
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "InfoMgr - Win32 Release"
# Name "InfoMgr - Win32 Debug"
# Name "InfoMgr - Win32 Debug Unicode"
# Name "InfoMgr - Win32 Release Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ContentView.cpp
# End Source File
# Begin Source File

SOURCE=.\DetailFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DetailObj.cpp
# End Source File
# Begin Source File

SOURCE=.\DropSrc.cpp
# End Source File
# Begin Source File

SOURCE=.\EditDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FindDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoMgr.rc
# End Source File
# Begin Source File

SOURCE=.\InfoMgrDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoMgrView.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\oleobject.cpp
# End Source File
# Begin Source File

SOURCE=.\oleobjects.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\Record.cpp
# End Source File
# Begin Source File

SOURCE=.\richtext.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\Subfunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\TMsgbox.cpp
# End Source File
# Begin Source File

SOURCE=.\UndoItem.cpp
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpcdrom.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpcdromcollection.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpclosedcaption.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpcontrols.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpdvd.cpp
# End Source File
# Begin Source File

SOURCE=.\wmperror.cpp
# End Source File
# Begin Source File

SOURCE=.\wmperroritem.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpmedia.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpmediacollection.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpnetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpplayer4.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpplayerapplication.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpplaylist.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpplaylistarray.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpplaylistcollection.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpsettings.cpp
# End Source File
# Begin Source File

SOURCE=.\wmpstringcollection.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ConstantDefs.h
# End Source File
# Begin Source File

SOURCE=.\ContentView.h
# End Source File
# Begin Source File

SOURCE=.\DetailFile.h
# End Source File
# Begin Source File

SOURCE=.\DetailObj.h
# End Source File
# Begin Source File

SOURCE=.\DropSrc.h
# End Source File
# Begin Source File

SOURCE=.\EditDialog.h
# End Source File
# Begin Source File

SOURCE=.\FindDialog.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\InfoMgr.h
# End Source File
# Begin Source File

SOURCE=.\InfoMgrDoc.h
# End Source File
# Begin Source File

SOURCE=.\InfoMgrView.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\oleobject.h
# End Source File
# Begin Source File

SOURCE=.\oleobjects.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\Record.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\richtext.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TMsgbox.h
# End Source File
# Begin Source File

SOURCE=.\UndoItem.h
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.h
# End Source File
# Begin Source File

SOURCE=.\wmpcdrom.h
# End Source File
# Begin Source File

SOURCE=.\wmpcdromcollection.h
# End Source File
# Begin Source File

SOURCE=.\wmpclosedcaption.h
# End Source File
# Begin Source File

SOURCE=.\wmpcontrols.h
# End Source File
# Begin Source File

SOURCE=.\wmpdvd.h
# End Source File
# Begin Source File

SOURCE=.\wmperror.h
# End Source File
# Begin Source File

SOURCE=.\wmperroritem.h
# End Source File
# Begin Source File

SOURCE=.\wmpmedia.h
# End Source File
# Begin Source File

SOURCE=.\wmpmediacollection.h
# End Source File
# Begin Source File

SOURCE=.\wmpnetwork.h
# End Source File
# Begin Source File

SOURCE=.\wmpplayer4.h
# End Source File
# Begin Source File

SOURCE=.\wmpplayerapplication.h
# End Source File
# Begin Source File

SOURCE=.\wmpplaylist.h
# End Source File
# Begin Source File

SOURCE=.\wmpplaylistarray.h
# End Source File
# Begin Source File

SOURCE=.\wmpplaylistcollection.h
# End Source File
# Begin Source File

SOURCE=.\wmpsettings.h
# End Source File
# Begin Source File

SOURCE=.\wmpstringcollection.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\Drives.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\InfoMgr.ico
# End Source File
# Begin Source File

SOURCE=.\res\InfoMgr.rc2
# End Source File
# Begin Source File

SOURCE=.\res\InfoMgrDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\toobar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\InfoMgr.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section InfoMgr : {8856F961-340A-11D0-A96B-00C04FD705A2}
# 	2:21:DefaultSinkHeaderFile:webbrowser2.h
# 	2:16:DefaultSinkClass:CWebBrowser2
# End Section
# Section InfoMgr : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section InfoMgr : {40897764-CEAB-47BE-AD4A-8E28537F9BBF}
# 	2:5:Class:CWMPPlayerApplication
# 	2:10:HeaderFile:wmpplayerapplication.h
# 	2:8:ImplFile:wmpplayerapplication.cpp
# End Section
# Section InfoMgr : {9104D1AB-80C9-4FED-ABF0-2E6417A6DF14}
# 	2:5:Class:CWMPSettings
# 	2:10:HeaderFile:wmpsettings.h
# 	2:8:ImplFile:wmpsettings.cpp
# End Section
# Section InfoMgr : {3B7C8860-D78F-101B-B9B5-04021C009402}
# 	2:21:DefaultSinkHeaderFile:richtext.h
# 	2:16:DefaultSinkClass:CRichText
# End Section
# Section InfoMgr : {6BF52A52-394A-11D3-B153-00C04F79FAA6}
# 	2:21:DefaultSinkHeaderFile:wmpplayer4.h
# 	2:16:DefaultSinkClass:CWMPPlayer4
# End Section
# Section InfoMgr : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section InfoMgr : {A12DCF7D-14AB-4C1B-A8CD-63909F06025B}
# 	2:5:Class:CWMPError
# 	2:10:HeaderFile:wmperror.h
# 	2:8:ImplFile:wmperror.cpp
# End Section
# Section InfoMgr : {4F2DF574-C588-11D3-9ED0-00C04FB6E937}
# 	2:5:Class:CWMPClosedCaption
# 	2:10:HeaderFile:wmpclosedcaption.h
# 	2:8:ImplFile:wmpclosedcaption.cpp
# End Section
# Section InfoMgr : {D5F0F4F1-130C-11D3-B14E-00C04F79FAA6}
# 	2:5:Class:CWMPPlaylist
# 	2:10:HeaderFile:wmpplaylist.h
# 	2:8:ImplFile:wmpplaylist.cpp
# End Section
# Section InfoMgr : {EE4C8FE2-34B2-11D3-A3BF-006097C9B344}
# 	2:5:Class:CWMPCdromCollection
# 	2:10:HeaderFile:wmpcdromcollection.h
# 	2:8:ImplFile:wmpcdromcollection.cpp
# End Section
# Section InfoMgr : {3614C646-3B3B-4DE7-A81E-930E3F2127B3}
# 	2:5:Class:CWMPErrorItem
# 	2:10:HeaderFile:wmperroritem.h
# 	2:8:ImplFile:wmperroritem.cpp
# End Section
# Section InfoMgr : {94D55E95-3FAC-11D3-B155-00C04F79FAA6}
# 	2:5:Class:CWMPMedia
# 	2:10:HeaderFile:wmpmedia.h
# 	2:8:ImplFile:wmpmedia.cpp
# End Section
# Section InfoMgr : {ED117630-4090-11CF-8981-00AA00688B10}
# 	2:5:Class:COLEObject
# 	2:10:HeaderFile:oleobject.h
# 	2:8:ImplFile:oleobject.cpp
# End Section
# Section InfoMgr : {EC21B779-EDEF-462D-BBA4-AD9DDE2B29A7}
# 	2:5:Class:CWMPNetwork
# 	2:10:HeaderFile:wmpnetwork.h
# 	2:8:ImplFile:wmpnetwork.cpp
# End Section
# Section InfoMgr : {4A976298-8C0D-11D3-B389-00C04F68574B}
# 	2:5:Class:CWMPStringCollection
# 	2:10:HeaderFile:wmpstringcollection.h
# 	2:8:ImplFile:wmpstringcollection.cpp
# End Section
# Section InfoMgr : {8363BC22-B4B4-4B19-989D-1CD765749DD1}
# 	2:5:Class:CWMPMediaCollection
# 	2:10:HeaderFile:wmpmediacollection.h
# 	2:8:ImplFile:wmpmediacollection.cpp
# End Section
# Section InfoMgr : {10A13217-23A7-439B-B1C0-D847C79B7774}
# 	2:5:Class:CWMPPlaylistCollection
# 	2:10:HeaderFile:wmpplaylistcollection.h
# 	2:8:ImplFile:wmpplaylistcollection.cpp
# End Section
# Section InfoMgr : {CFAB6E98-8730-11D3-B388-00C04F68574B}
# 	2:5:Class:CWMPCdrom
# 	2:10:HeaderFile:wmpcdrom.h
# 	2:8:ImplFile:wmpcdrom.cpp
# End Section
# Section InfoMgr : {679409C0-99F7-11D3-9FB7-00105AA620BB}
# 	2:5:Class:CWMPPlaylistArray
# 	2:10:HeaderFile:wmpplaylistarray.h
# 	2:8:ImplFile:wmpplaylistarray.cpp
# End Section
# Section InfoMgr : {74C09E02-F828-11D2-A74B-00A0C905F36E}
# 	2:5:Class:CWMPControls
# 	2:10:HeaderFile:wmpcontrols.h
# 	2:8:ImplFile:wmpcontrols.cpp
# End Section
# Section InfoMgr : {D30C1661-CDAF-11D0-8A3E-00C04FC9E26E}
# 	2:5:Class:CWebBrowser2
# 	2:10:HeaderFile:webbrowser2.h
# 	2:8:ImplFile:webbrowser2.cpp
# End Section
# Section InfoMgr : {E9A5593C-CAB0-11D1-8C0B-0000F8754DA1}
# 	2:5:Class:CRichText
# 	2:10:HeaderFile:richtext.h
# 	2:8:ImplFile:richtext.cpp
# End Section
# Section InfoMgr : {8DA61686-4668-4A5C-AE5D-803193293DBE}
# 	2:5:Class:CWMPDVD
# 	2:10:HeaderFile:wmpdvd.h
# 	2:8:ImplFile:wmpdvd.cpp
# End Section
# Section InfoMgr : {859321D0-3FD1-11CF-8981-00AA00688B10}
# 	2:5:Class:COLEObjects
# 	2:10:HeaderFile:oleobjects.h
# 	2:8:ImplFile:oleobjects.cpp
# End Section
# Section InfoMgr : {6C497D62-8919-413C-82DB-E935FB3EC584}
# 	2:5:Class:CWMPPlayer4
# 	2:10:HeaderFile:wmpplayer4.h
# 	2:8:ImplFile:wmpplayer4.cpp
# End Section
