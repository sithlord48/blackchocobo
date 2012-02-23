# /----------------------------------------------------------------------------/
# //    copyright 2010-2012 Chris Rizzitello <sithlord48@gmail.com>           //
# //                                                                          //
# //    This file is part of Black Chocobo.                                   //
# //                                                                          //
# //    Black Chocobo is free software: you can redistribute it and/or modify //
# //    it under the terms of the GNU General Public License as published by  //
# //    the Free Software Foundation, either version 3 of the License, or     //
# //    (at your option) any later version.                                   //
# //                                                                          //
# //    Black Chocobo is distributed in the hope that it will be useful,      //
# //    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
# //   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
# //    GNU General Public License for more details.                          //
# /----------------------------------------------------------------------------/
# -------------------------------------------------
# Project created by QtCreator 2010-03-14T14:53:13
# -------------------------------------------------
TARGET = Black_Chocobo

TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    slotselect.cpp \
    globals.cpp \
    about.cpp \
    options.cpp \
    errbox.cpp \
    SaveIcon.cpp \
    static_data/FF7Text.cpp \
    static_data/FF7Item.cpp \
    static_data/FF7Materia.cpp \
    static_data/FF7Location.cpp \
    widgets/ItemPreview.cpp \
    widgets/DialogPreview.cpp
HEADERS += mainwindow.h \
    FF7SAVE.h \
    slotselect.h \
    about.h \
    globals.h \
    options.h \
    errbox.h \
    SaveIcon.h \
    static_data/FF7Text.h \
    static_data/FF7Item.h \
    static_data/FF7Materia.h \
    static_data/FF7Location.h \
    widgets/ItemPreview.h \
    widgets/DialogPreview.h
FORMS += mainwindow.ui \
    slotselect.ui \
    about.ui \
    options.ui \
    errbox.ui
RESOURCES += images.qrc
TRANSLATIONS += lang/bchoco_en.ts \
    lang/bchoco_es.ts \
    lang/bchoco_fr.ts \
    lang/bchoco_de.ts \
    lang/bchoco_ja.ts

#Below Is OS Specific Stuff.

#set up for mac os
macx:{
    #set program icon on mac os
    ICON = icon/bchoco_icon_osx.icns
    DEFINES += SVNVERSION=\"'\\"\\"'\"
}

#set up for windows
win32:{
    #set up icon for windows
    RC_FILE = bchoco.rc
    system(SubWCRev $$PWD svnversion.hmake svnversion.h)
}

#all other *nix (except for symbian)
#base for setting up deb packages(rpm too?).
#becomes 'make install' when qmake generates the makefile
unix:!macx:!symbian {
VERS = $$system(svn info -r HEAD . | grep '"Changed Rev"' | cut -b 19-)
{
DEFINES += SVNVERSION=\"'\\"$${VERS}\\"'\"
}
system(lrelease Black_Chocobo.pro) #call lrelease to make the qm files.
target.path = /opt/blackchocobo #set the play to deploy the build target.

save0.path = /opt/blackchocobo
save0.files = save0

lang.path = /opt/blackchocobo/lang
lang.files = lang/*.qm

icon.path = /usr/share/pixmaps
icon.files = icon/Black_Chocobo.png

desktop.path =/usr/share/applications/
desktop.files = Black_Chocobo.desktop

INSTALLS += target \
    save0 \
    lang  \
    icon  \
    desktop
}
