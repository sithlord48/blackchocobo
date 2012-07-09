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
    about.cpp \
    options.cpp \
    errbox.cpp \
    static_data/SaveIcon.cpp \
    static_data/FF7Save.cpp \
    static_data/FF7Text.cpp \
    static_data/FF7Item.cpp \
    static_data/FF7Materia.cpp \
    static_data/FF7Location.cpp \
    widgets/ItemPreview.cpp \
    widgets/DialogPreview.cpp \
    widgets/MateriaEditor.cpp \
    widgets/SlotSelect.cpp\
    widgets/SlotPreview.cpp\
    static_data/FF7Char.cpp \
    widgets/ChocoboEditor.cpp \
    widgets/CharEditor.cpp
HEADERS += mainwindow.h \
    about.h \
    options.h \
    errbox.h \
    static_data/SaveIcon.h \
    static_data/FF7Save.h \
    static_data/FF7Text.h \
    static_data/FF7Item.h \
    static_data/FF7Materia.h \
    static_data/FF7Location.h \
    widgets/ItemPreview.h \
    widgets/DialogPreview.h \
    version.h \
    static_data/FF7Save_Const.h \
    static_data/FF7Save_Types.h \
    widgets/MateriaEditor.h \
    widgets/SlotSelect.h\
    widgets/SlotPreview.h\
    static_data/FF7Char.h \
    static_data/Type_materia.h \
    static_data/Type_FF7CHAR.h \
    widgets/ChocoboEditor.h \
    widgets/CharEditor.h
FORMS += mainwindow.ui \
    about.ui \
    options.ui \
    errbox.ui
RESOURCES += images.qrc
TRANSLATIONS += lang/bchoco_en.ts \
    lang/bchoco_es.ts \
    lang/bchoco_fr.ts \
    lang/bchoco_de.ts \
    lang/bchoco_ja.ts

static { # everything below takes effect with CONFIG += static
    CONFIG += static
    CONFIG += staticlib # this is needed if you create a static library, not a static executable
    QTPLUGIN += qcncodecs qjpcodecs qtwcodecs qkrcodecs
    DEFINES += STATIC
    message("Static Build") # this is for information, that the static build is done
    TARGET = $$join(TARGET,,,-static) #this adds an s in the end, so you can seperate static build from non static build
}

# change the name of the binary, if it is build in debug mode
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,-debug)
}

#Below Is OS Specific Stuff.

#set up for mac os
macx:{
    #set program icon on mac os
    ICON = icon/bchoco_icon_osx.icns
    CONFIG += x86_64 x86
}
#all non symbian unix-like
unix:!symbian{
    VERS = $$system(svn info -r HEAD . | grep '"Changed Rev"' | cut -b 19-)
    {
    DEFINES += SVNVERSION=\"$${VERS}\"# svn rev was found set to its value
    message("Using Svn Revision:$${VERS}")
    }
    system(lrelease Black_Chocobo.pro)#release the .qm files
}

#set up for windows
win32:{
    #set up icon for windows
    RC_FILE = bchoco.rc
    VERS = $$system(svnrev $$PWD)
    {
    DEFINES += SVNVERSION=\"$${VERS}\"# svn rev was found set to its value
    message("Using Svn Revision:$${VERS}")
    }
}

#all other *nix (except for symbian)
unix:!macx:!symbian {
#base for setting up deb packages(rpm too?).
#becomes 'make install' when qmake generates the makefile
target.path = /opt/blackchocobo #set the path to deploy the build target.

lang.path = /opt/blackchocobo/lang #set path for lang folder
lang.files = lang/*.qm  #grab All qm files

icon.path = /usr/share/pixmaps       #system path icon.
icon.files = icon/Black_Chocobo.png

desktop.path =/usr/share/applications/ #system path app dir
desktop.files = Black_Chocobo.desktop  #

INSTALLS += target \
    lang  \
    icon  \
    desktop
}
