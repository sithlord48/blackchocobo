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

QT       += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp \
    mainwindow.cpp \
    about.cpp \
    options.cpp \
    errbox.cpp \
    FF7tk/widgets/SlotSelect.cpp \
    FF7tk/widgets/SlotPreview.cpp \
    FF7tk/widgets/MateriaEditor.cpp \
    FF7tk/widgets/ItemPreview.cpp \
    FF7tk/widgets/DialogPreview.cpp \
    FF7tk/widgets/ChocoboEditor.cpp \
    FF7tk/widgets/CharEditor.cpp \
    FF7tk/static_data/SaveIcon.cpp \
    FF7tk/static_data/FF7Text.cpp \
    FF7tk/static_data/FF7Save.cpp \
    FF7tk/static_data/FF7Materia.cpp \
    FF7tk/static_data/FF7Location.cpp \
    FF7tk/static_data/FF7Item.cpp \
    FF7tk/static_data/FF7Char.cpp \
    FF7tk/widgets/ItemSelector.cpp \
    FF7tk/widgets/ItemList.cpp \
    FF7tk/widgets/MetadataCreator.cpp \
    qhexedit/xbytearray.cpp \
    qhexedit/qhexedit_p.cpp \
    qhexedit/qhexedit.cpp \
    qhexedit/commands.cpp \
    FF7tk/widgets/PhsListWidget.cpp \
    FF7tk/widgets/DoubleCheckBox.cpp \
    FF7tk/widgets/MenuListWidget.cpp \
    FF7tk/widgets/OptionsWidget.cpp
HEADERS += mainwindow.h \
    about.h \
    options.h \
    errbox.h \
    version.h \
    FF7tk/widgets/ItemSelector.h \
    FF7tk/widgets/ItemList.h \
    FF7tk/widgets/MetadataCreator.h \
    FF7tk/static_data/Type_materia.h \
    FF7tk/static_data/Type_FF7CHAR.h \
    FF7tk/static_data/SaveIcon.h \
    FF7tk/static_data/FF7Text.h \
    FF7tk/static_data/FF7Save_Types.h \
    FF7tk/static_data/FF7Save_Const.h \
    FF7tk/static_data/FF7Save.h \
    FF7tk/static_data/FF7Materia.h \
    FF7tk/static_data/FF7Location.h \
    FF7tk/static_data/FF7Item.h \
    FF7tk/static_data/FF7Char.h \
    FF7tk/widgets/SlotSelect.h \
    FF7tk/widgets/SlotPreview.h \
    FF7tk/widgets/MateriaEditor.h \
    FF7tk/widgets/ItemPreview.h \
    FF7tk/widgets/DialogPreview.h \
    FF7tk/widgets/ChocoboEditor.h \
    FF7tk/widgets/CharEditor.h \
    qhexedit/xbytearray.h \
    qhexedit/qhexedit_p.h \
    qhexedit/qhexedit.h \
    qhexedit/commands.h \
    FF7tk/widgets/PhsListWidget.h \
    FF7tk/widgets/DoubleCheckBox.h \
    FF7tk/widgets/MenuListWidget.h \
    FF7tk/widgets/OptionsWidget.h

FORMS += mainwindow.ui \
    about.ui \
    options.ui
RESOURCES += images.qrc
TRANSLATIONS += lang/bchoco_en.ts \
    lang/bchoco_es.ts \
    lang/bchoco_fr.ts \
    lang/bchoco_de.ts \
    lang/bchoco_ja.ts


static:{ # everything below takes effect with CONFIG += static
    CONFIG += static
    CONFIG += staticlib # this is needed if you create a static library, not a static executable
    QTPLUGIN += qcncodecs qjpcodecs qtwcodecs qkrcodecs
    DEFINES += STATIC
    message("Static Build") # this is for information, that the static build is done
    TARGET = $$join(TARGET,,,-static) #this adds an s in the end, so you can seperate static build from non static build
}
# change the name of the binary, if it is build in debug mode
CONFIG(debug, debug|release) {TARGET = $$join(TARGET,,,-debug)}

#Below Is OS Specific Stuff.
win32: {RC_FILE = bchoco.rc} #program icon for windows
macx:{
    ICON = icon/bchoco_icon_osx.icns     #set program icon
    CONFIG += x86_64 x86 #Build for use on 32 and 64 bit mac os.
}
#system calls trigger with any OS
system (lrelease Black_Chocobo.pro)#release the .qm files
system (rcc -binary locations.qrc -o locations.rcc) #make locations resource

unix:!macx:!symbian: {
#all other *nix (except for symbian and mac os)
#base for setting up deb packages(rpm too?).
#Below Will Become 'install' in the makefile
    target.path = /opt/blackchocobo #set the path to deploy the build target.
    lang.path = /opt/blackchocobo/lang #set path for lang folder
    lang.files = lang/*.qm  #grab All qm files

    locationPreview.path=/opt/blackchocobo/
    locationPreview.files= locations.rcc

    icon.path = /usr/share/pixmaps       #system path icon.
    icon.files = icon/Black_Chocobo.png

    desktop.path =/usr/share/applications/ #system path app dir
    desktop.files = Black_Chocobo.desktop  #

    INSTALLS += target \
        lang  \
        locationPreview \
        icon  \
        desktop
}
