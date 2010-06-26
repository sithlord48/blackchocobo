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
    loadsave.cpp
HEADERS += mainwindow.h \
    FF7SAVE.h \
    slotselect.h \
    globals.h \
    globals.h \
    about.h \
    loadsave.h
FORMS += mainwindow.ui \
    slotselect.ui \
    about.ui
RESOURCES += images.qrc
TRANSLATIONS += lang/bchoco_en.ts \
    lang/bchoco_es.ts \
    lang/bchoco_fr.ts
