# /----------------------------------------------------------------------------/
# //    copyright 2010-2014 Chris Rizzitello <sithlord48@gmail.com>           //
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
QT += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	about.cpp \
	options.cpp \
	errbox.cpp \
	achievementdialog.cpp \
	qhexedit/xbytearray.cpp \
	qhexedit/qhexedit_p.cpp \
	qhexedit/qhexedit.cpp \
	qhexedit/commands.cpp \
	ff7tk/data/SaveIcon.cpp \
	ff7tk/data/FF7Text.cpp \
	ff7tk/data/FF7Save.cpp \
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
	options.h \
	errbox.h \
	version.h \
	qhexedit/xbytearray.h \
	qhexedit/qhexedit_p.h \
	qhexedit/qhexedit.h \
	qhexedit/commands.h \
	achievementdialog.h \
	ff7tk/data/Type_FF7CHOCOBO.h \
	ff7tk/data/FF7FieldItemList.h \
	ff7tk/data/FF7Achievements.h \
	ff7tk/data/Type_materia.h \
	ff7tk/data/Type_FF7CHAR.h \
	ff7tk/data/SaveIcon.h \
	ff7tk/data/FF7Text.h \
	ff7tk/data/FF7Save_Types.h \
	ff7tk/data/FF7Save_Const.h \
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
	#Set OpenSSL include & lib paths
	#THIS MUST BE CHANGED WITH YOUR OPENSSL PATHS OR YOUR BUILD WILL FAIL!!!
	INCLUDEPATH += C:/OpenSSL-Win32/include # Be Sure Path is openSSL
	LIBS += -L"C:/OpenSSL-Win32/lib" -llibeay32 #Be sure to update path to installed openSSL
	RC_FILE = bchoco.rc #program icon for windows
	TARGET = Black_Chocobo
}

#set up for mac os
macx:{
	LIBS += -lcrypto
	TARGET = Black_Chocobo
	ICON = icon/bchoco_icon_osx.icns     #set program icon
}
#system calls trigger with any OS
system (lrelease Black_Chocobo.pro)#release the .qm files

#set up for unix os
unix:!macx:!symbian:!android {
	LIBS += -lcrypto
	TARGET = blackchocobo
	target.path = /usr/bin #place our binary in /usr/bin
	INSTALLS +=target
}
android:{
	INCLUDEPATH += /home/chris/Downloads/openssl-1.0.1i/include
	#LIBS += -L "" -lcrypto
	TARGET = blackchocobo
	target.path = /usr/bin
	INSTALLS +=target
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
