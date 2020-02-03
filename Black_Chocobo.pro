# /----------------------------------------------------------------------------/
# //    copyright 2010-2020 Chris Rizzitello <sithlord48@gmail.com>           //
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
TEMPLATE = app
CONFIG += c++1z
QT += core gui xml widgets qml

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	about.cpp \
	bcdialog.cpp \
	options.cpp \
	errbox.cpp \
	achievementdialog.cpp \
	qhexedit/chunks.cpp \
	qhexedit/qhexedit.cpp \
	qhexedit/commands.cpp \
	ff7tk/data/crypto/aes.c \
	ff7tk/data/SaveIcon.cpp \
	ff7tk/data/FF7Text.cpp \
	ff7tk/data/FF7Save.cpp \
	ff7tk/data/FF7SaveInfo.cpp \
	ff7tk/data/FF7Materia.cpp \
	ff7tk/data/FF7Location.cpp \
	ff7tk/data/FF7Item.cpp \
	ff7tk/data/FF7Char.cpp \
	ff7tk/data/FF7FieldItemList.cpp \
	ff7tk/widgets/SlotSelect.cpp \
	ff7tk/widgets/SlotPreview.cpp \
	ff7tk/widgets/MateriaEditor.cpp \
	ff7tk/widgets/ItemPreview.cpp \
	ff7tk/widgets/DialogPreview.cpp \
	ff7tk/widgets/ChocoboEditor.cpp \
	ff7tk/widgets/CharEditor.cpp \
	ff7tk/widgets/ItemSelector.cpp \
	ff7tk/widgets/ItemList.cpp \
	ff7tk/widgets/MetadataCreator.cpp \
	ff7tk/widgets/DoubleCheckBox.cpp \
	ff7tk/widgets/MenuListWidget.cpp \
	ff7tk/widgets/OptionsWidget.cpp \
	ff7tk/widgets/ChocoboManager.cpp \
	ff7tk/widgets/ChocoboLabel.cpp \
	ff7tk/widgets/LocationViewer.cpp \
	ff7tk/widgets/AchievementEditor.cpp \
	ff7tk/widgets/PhsListWidget.cpp \
	ff7tk/data/FF7Achievements.cpp

HEADERS += \
	mainwindow.h \
	about.h \
        bcdialog.h \
	options.h \
	errbox.h \
	qhexedit/chunks.h \
	qhexedit/qhexedit.h \
	qhexedit/commands.h \
	achievementdialog.h \
    ff7tk/data/crypto/aes.h \
	ff7tk/data/Type_FF7CHOCOBO.h \
	ff7tk/data/FF7FieldItemList.h \
	ff7tk/data/FF7Achievements.h \
	ff7tk/data/Type_materia.h \
	ff7tk/data/Type_FF7CHAR.h \
	ff7tk/data/SaveIcon.h \
	ff7tk/data/FF7Text.h \
	ff7tk/data/FF7SaveInfo.h \
	ff7tk/data/FF7Save_Types.h \
	ff7tk/data/FF7Save.h \
	ff7tk/data/FF7Materia.h \
	ff7tk/data/FF7Location.h \
	ff7tk/data/FF7Item.h \
	ff7tk/data/FF7Char.h \
	ff7tk/widgets/ItemSelector.h \
	ff7tk/widgets/ItemList.h \
	ff7tk/widgets/MetadataCreator.h \
	ff7tk/widgets/SlotSelect.h \
	ff7tk/widgets/SlotPreview.h \
	ff7tk/widgets/MateriaEditor.h \
	ff7tk/widgets/ItemPreview.h \
	ff7tk/widgets/DialogPreview.h \
	ff7tk/widgets/ChocoboEditor.h \
	ff7tk/widgets/CharEditor.h \
	ff7tk/widgets/PhsListWidget.h \
	ff7tk/widgets/DoubleCheckBox.h \
	ff7tk/widgets/MenuListWidget.h \
	ff7tk/widgets/OptionsWidget.h \
	ff7tk/widgets/ChocoboManager.h \
	ff7tk/widgets/ChocoboLabel.h \
	ff7tk/widgets/LocationViewer.h \
	ff7tk/widgets/AchievementEditor.h

FORMS += \
	mainwindow.ui \
	about.ui \
	options.ui
RESOURCES += \
	images.qrc \
	ff7tk/icons/achievements.qrc\
	ff7tk/icons/characters.qrc \
	ff7tk/icons/chocobo.qrc \
	ff7tk/icons/common.qrc \
	ff7tk/icons/items.qrc \
	ff7tk/icons/locations.qrc \
	ff7tk/icons/materia.qrc \
	ff7tk/icons/psxButtons.qrc

TRANSLATIONS += \
	lang/bchoco_en.ts \
	lang/bchoco_es.ts \
	lang/bchoco_fr.ts \
	lang/bchoco_de.ts \
	lang/bchoco_ja.ts\
	lang/bchoco_re.ts #re translation to english

#Below Is OS Specific Stuff.
#set up for windows
win32: {
	TARGET = Black_Chocobo
	#Prevent ms padding on packed structures on gcc compiler
	contains(QMAKE_COMPILER, gcc) {
	QMAKE_CXXFLAGS += -mno-ms-bitfields
	}
	#Windows RC Info Below
	VERSION = 1.9.96
	QMAKE_TARGET_COMPANY = Black Chocobo Devs
	QMAKE_TARGET_DESCRIPTION = Final Fantasy 7 Save Editor
	QMAKE_TARGET_COPYRIGHT = 2010 - 2020 Chris Rizzitello
	QMAKE_TARGET_PRODUCT = Black_Chocobo
	RC_ICONS = icon/bchoco_icon_win.ico
}

#set up for mac os
macx:{
    TARGET = Black_Chocobo
	ICON = icon/bchoco_icon_osx.icns     #set program icon
	QMAKE_CXXFLAGS += -stdlib=libc++
}
#system calls trigger with any OS
system (lrelease Black_Chocobo.pro)#release the .qm files

#set up for unix os
unix:!macx:!symbian:!android {
	#remember to ship debian/menu and debian/blackchocobo.sharedmimeinfo

    TARGET = blackchocobo
    target.path = /usr/bin

    langfiles.files= lang/*.qm
    langfiles.path= /usr/share/blackchocobo/lang

    icon.files = icon/Black_Chocobo.png
    icon.path = /usr/share/pixmaps
	desktop.files =Black_Chocobo.desktop
	desktop.path = /usr/share/applications
	
	INSTALLS += target langfiles icon desktop
}
android:{
	TARGET = blackchocobo
	target.path = /usr/bin

    langfiles.files= lang/*.qm
    langfiles.path= /usr/share/blackchocobo/lang

    icon.files = icon/Black_Chocobo.png
    icon.path = /usr/share/pixmaps

    INSTALLS +=target langfiles icon
}
static:{ # everything below takes effect with CONFIG += static
	CONFIG += static
	CONFIG += staticlib # this is needed if you create a static library, not a static executable
	lessThan(QT_MAJOR_VERSION, 5): QTPLUGIN += qcncodecs qjpcodecs qtwcodecs qkrcodecs
	DEFINES += STATIC
	message("Static Build") # this is for information, that the static build is done
	TARGET = $$join(TARGET,,,-static) #this adds an s in the end, so you can seperate static build from non static build
}
# change the name of the binary, if it is build in debug mode
CONFIG(debug, debug|release) {TARGET = $$join(TARGET,,,-debug)}
