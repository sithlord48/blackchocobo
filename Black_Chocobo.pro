# /----------------------------------------------------------------------------/
# //    copyright 2010 Chris Rizzitello <sithlord48@gmail.com>                //
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
    SaveIcon.cpp \
    errbox.cpp
HEADERS += mainwindow.h \
    FF7SAVE.h \
    slotselect.h \
    about.h \
    globals.h \
    options.h \
    SaveIcon.h \
    errbox.h
FORMS += mainwindow.ui \
    slotselect.ui \
    about.ui \
    options.ui \
    errbox.ui
RESOURCES += images.qrc
TRANSLATIONS += lang/bchoco_en.ts \
    lang/bchoco_es.ts \
    lang/bchoco_fr.ts
macx:ICON = icon/bchoco_icon_osx.icns
win32:RC_FILE = bchoco.rc

unix:!macx:!symbian {
system(lrelease Black_Chocobo.pro)
target.path = /usr/bin/blackchocobo
INSTALLS += target
save0.path = /usr/bin/blackchocobo
save0.files = save0
INSTALLS += save0
lang.path = /usr/bin/blackchocobo/lang
lang.files = lang/*.qm
INSTALLS += lang
icon.path = /usr/share/pixmaps
icon.files = icon/Black_Chocobo.png
INSTALLS += icon
desktop.path =/usr/share/applications/
desktop.files = Black_Chocobo.desktop
INSTALLS += desktop
}
