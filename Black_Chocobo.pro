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
		FF7tk/data/SaveIcon.cpp \
		FF7tk/data/FF7Text.cpp \
		FF7tk/data/FF7Save.cpp \
		FF7tk/data/FF7Materia.cpp \
		FF7tk/data/FF7Location.cpp \
		FF7tk/data/FF7Item.cpp \
		FF7tk/data/FF7Char.cpp \
		FF7tk/data/FF7FieldItemList.cpp \
	FF7tk/widgets/SlotSelect.cpp \
	FF7tk/widgets/SlotPreview.cpp \
	FF7tk/widgets/MateriaEditor.cpp \
	FF7tk/widgets/ItemPreview.cpp \
	FF7tk/widgets/DialogPreview.cpp \
	FF7tk/widgets/ChocoboEditor.cpp \
	FF7tk/widgets/CharEditor.cpp \
	FF7tk/widgets/ItemSelector.cpp \
	FF7tk/widgets/ItemList.cpp \
	FF7tk/widgets/MetadataCreator.cpp \
	FF7tk/widgets/DoubleCheckBox.cpp \
	FF7tk/widgets/MenuListWidget.cpp \
	FF7tk/widgets/OptionsWidget.cpp \
	FF7tk/widgets/ChocoboManager.cpp \
	FF7tk/widgets/ChocoboLabel.cpp \
	FF7tk/widgets/LocationViewer.cpp \
	FF7tk/widgets/AchievementEditor.cpp \
	FF7tk/widgets/PhsListWidget.cpp \
		FF7tk/data/FF7Achievements.cpp

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
		FF7tk/data/Type_FF7CHOCOBO.h \
		FF7tk/data/FF7FieldItemList.h \
		FF7tk/data/FF7Achievements.h \
		FF7tk/data/Type_materia.h \
		FF7tk/data/Type_FF7CHAR.h \
		FF7tk/data/SaveIcon.h \
		FF7tk/data/FF7Text.h \
		FF7tk/data/FF7Save_Types.h \
		FF7tk/data/FF7Save_Const.h \
		FF7tk/data/FF7Save.h \
		FF7tk/data/FF7Materia.h \
		FF7tk/data/FF7Location.h \
		FF7tk/data/FF7Item.h \
		FF7tk/data/FF7Char.h \
	FF7tk/widgets/ItemSelector.h \
	FF7tk/widgets/ItemList.h \
	FF7tk/widgets/MetadataCreator.h \
	FF7tk/widgets/SlotSelect.h \
	FF7tk/widgets/SlotPreview.h \
	FF7tk/widgets/MateriaEditor.h \
	FF7tk/widgets/ItemPreview.h \
	FF7tk/widgets/DialogPreview.h \
	FF7tk/widgets/ChocoboEditor.h \
	FF7tk/widgets/CharEditor.h \
	FF7tk/widgets/PhsListWidget.h \
	FF7tk/widgets/DoubleCheckBox.h \
	FF7tk/widgets/MenuListWidget.h \
	FF7tk/widgets/OptionsWidget.h \
	FF7tk/widgets/ChocoboManager.h \
	FF7tk/widgets/ChocoboLabel.h \
	FF7tk/widgets/LocationViewer.h \
	FF7tk/widgets/AchievementEditor.h

FORMS += \
	mainwindow.ui \
	about.ui \
	options.ui
RESOURCES += \
		images.qrc \
		FF7tk/icons/achievements.qrc\
		FF7tk/icons/characters.qrc \
		FF7tk/icons/chocobo.qrc \
		FF7tk/icons/common.qrc \
		FF7tk/icons/items.qrc \
		FF7tk/icons/locations.qrc \
		FF7tk/icons/materia.qrc \
		FF7tk/icons/psxButtons.qrc

TRANSLATIONS += \
	lang/bchoco_en.ts \
	lang/bchoco_es.ts \
	lang/bchoco_fr.ts \
	lang/bchoco_de.ts \
	lang/bchoco_ja.ts\
	lang/bchoco_re.ts #re translation to english

#Below Is OS Specific Stuff.
win32: {
	RC_FILE = bchoco.rc #program icon for windows
	TARGET = Black_Chocobo
}
macx:{
	TARGET = Black_Chocobo
	ICON = icon/bchoco_icon_osx.icns     #set program icon
}
#system calls trigger with any OS
system (lrelease Black_Chocobo.pro)#release the .qm files

unix:!macx:!symbian: {
	TARGET = blackchocobo
	target.path = /usr/bin #place our binary in /usr/bin
	INSTALLS +=target
}

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
