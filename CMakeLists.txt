project( blackchocobo )
#version number
# The version number.
set(blackchocobo_VERSION_MAJOR 1)
set(blackchocobo_VERSION_MINOR 9)
set(blackchocobo_VERSION_PATCH 90)
cmake_minimum_required( VERSION 2.8.11 )
set ( CMAKE_BUILD_TYPE Release )
add_definitions( -c++17)
add_definitions ( -Wall )
add_definitions (-DEnableopenSSL)
find_package ( Qt5Widgets REQUIRED )
find_package ( Qt5Gui REQUIRED )
find_package ( Qt5Xml REQUIRED )
find_package (Qt5Core REQUIRED )

if(EnableOpenSSL)
    find_package ( OpenSSL REQUIRED )
    add_definitions(-DEnableOpenSSL)
endif()

find_package(Qt5LinguistTools)
#include ( ${QT_USE_FILE} )
include_directories (
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTXML_INCLUDE_DIR}
	)
set ( blackchocobo_HDRS
	version.h
	qhexedit/chunks.h
	qhexedit/commands.h
	qhexedit/qhexedit.h
	ff7tk/data/Type_FF7CHOCOBO.h
	ff7tk/data/FF7FieldItemList.h
	ff7tk/data/Type_materia.h
	ff7tk/data/Type_FF7CHAR.h
	ff7tk/data/FF7Save_Types.h
	ff7tk/data/FF7Save_Const.h
	ff7tk/data/FF7Materia.h
	ff7tk/data/FF7Location.h
	ff7tk/data/FF7Item.h
	ff7tk/data/FF7Char.h
	)

set ( blackchocobo_SRCS
	main.cpp
	mainwindow.cpp
	about.cpp
	options.cpp
	errbox.cpp
	achievementdialog.cpp
	qhexedit/chunks.cpp
	qhexedit/commands.cpp
	qhexedit/qhexedit.cpp
	ff7tk/data/SaveIcon.cpp
	ff7tk/data/FF7Text.cpp
	ff7tk/data/FF7Save.cpp
	ff7tk/data/FF7Materia.cpp
	ff7tk/data/FF7Location.cpp
	ff7tk/data/FF7Item.cpp
	ff7tk/data/FF7Char.cpp
	ff7tk/data/FF7FieldItemList.cpp
	ff7tk/widgets/SlotSelect.cpp
	ff7tk/widgets/SlotPreview.cpp
	ff7tk/widgets/MateriaEditor.cpp
	ff7tk/widgets/ItemPreview.cpp
	ff7tk/widgets/DialogPreview.cpp
	ff7tk/widgets/ChocoboEditor.cpp
	ff7tk/widgets/CharEditor.cpp
	ff7tk/widgets/ItemSelector.cpp
	ff7tk/widgets/ItemList.cpp
	ff7tk/widgets/MetadataCreator.cpp
	ff7tk/widgets/DoubleCheckBox.cpp
	ff7tk/widgets/MenuListWidget.cpp
	ff7tk/widgets/OptionsWidget.cpp
	ff7tk/widgets/ChocoboManager.cpp
	ff7tk/widgets/ChocoboLabel.cpp
	ff7tk/widgets/LocationViewer.cpp
	ff7tk/widgets/AchievementEditor.cpp
	ff7tk/widgets/PhsListWidget.cpp
	ff7tk/data/FF7Achievements.cpp
	)

set ( blackchocobo_UIS
	mainwindow.ui
	about.ui
	options.ui
	)
QT5_WRAP_UI(UIS ${blackchocobo_UIS})


set ( blackchocobo_RSCS
	images.qrc
	ff7tk/icons/achievements.qrc
	ff7tk/icons/characters.qrc
	ff7tk/icons/chocobo.qrc
	ff7tk/icons/common.qrc
	ff7tk/icons/items.qrc
	ff7tk/icons/locations.qrc
	ff7tk/icons/materia.qrc
	ff7tk/icons/psxButtons.qrc
	)
QT5_ADD_RESOURCES(RSCS ${blackchocobo_RSCS})
find_package(Qt5LinguistTools)

set( translatables
    ${blackchocobo_HDRS}
    ${blackchocobo_SRCS}
    ${blackchocobo_UIS}
    )

set ( blackchocobo_TRS
	lang/bchoco_en.ts
	lang/bchoco_es.ts
	lang/bchoco_fr.ts
	lang/bchoco_de.ts
	lang/bchoco_ja.ts
	lang/bchoco_re.ts
	)
#qt5_create_translation(TRS ${translatables} ${blackchocobo_TRS})

qt5_add_translation(TRS ${blackchocobo_TRS})
set ( blackchocobo_MOCS
	mainwindow.h
	about.h
	options.h
	errbox.h
        qhexedit/chunks.h
	qhexedit/qhexedit.h
        qhexedit/commands.h
	achievementdialog.h
	ff7tk/data/FF7Achievements.h
	ff7tk/data/SaveIcon.h
	ff7tk/data/FF7Text.h
	ff7tk/data/FF7Save.h
	ff7tk/widgets/ItemSelector.h
	ff7tk/widgets/ItemList.h
	ff7tk/widgets/MetadataCreator.h
	ff7tk/widgets/SlotSelect.h
	ff7tk/widgets/SlotPreview.h
	ff7tk/widgets/MateriaEditor.h
	ff7tk/widgets/ItemPreview.h
	ff7tk/widgets/DialogPreview.h
	ff7tk/widgets/ChocoboEditor.h
	ff7tk/widgets/CharEditor.h
	ff7tk/widgets/PhsListWidget.h
	ff7tk/widgets/DoubleCheckBox.h
	ff7tk/widgets/MenuListWidget.h
	ff7tk/widgets/OptionsWidget.h
	ff7tk/widgets/ChocoboManager.h
	ff7tk/widgets/ChocoboLabel.h
	ff7tk/widgets/LocationViewer.h
	ff7tk/widgets/AchievementEditor.h
	)
QT5_WRAP_CPP(MOCS ${blackchocobo_MOCS})

add_executable ( blackchocobo ${blackchocobo_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )
target_link_libraries ( blackchocobo  Qt5::Core Qt5::Gui Qt5::Xml Qt5::Widgets ${OPENSSL_LIBRARIES} )

#install stuff
INCLUDE (InstallRequiredSystemLibraries)

SET(CPACK_SOURCE_IGNORE_FILES build/*)

install(TARGETS blackchocobo RUNTIME DESTINATION bin ) 
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bchoco_re.qm DESTINATION share/blackchocobo/lang PERMISSIONS OWNER_WRITE OWNER_READ)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bchoco_es.qm DESTINATION share/blackchocobo/lang PERMISSIONS OWNER_WRITE OWNER_READ)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bchoco_ja.qm DESTINATION share/blackchocobo/lang PERMISSIONS OWNER_WRITE OWNER_READ)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bchoco_fr.qm DESTINATION share/blackchocobo/lang PERMISSIONS OWNER_WRITE OWNER_READ)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bchoco_en.qm DESTINATION share/blackchocobo/lang PERMISSIONS OWNER_WRITE OWNER_READ)

SET(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING.txt")
SET(CPACK_PACKAGE_NAME "blackchocobo")
SET(CPACK_PACKAGE_VERSION ${blackchocobo_VERSION_MAJOR}.${blackchocobo_VERSION_MINOR}.${blackchocobo_VERSION_PATCH})
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A Free Final Fantasy VII Save Editor")
SET(CPACK_STRIP_FILES blackchocobo)
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	#install generic files needed for linux package
	
	install( FILES ${PROJECT_SOURCE_DIR}/icon/Black_Chocobo.png DESTINATION share/pixmaps/ PERMISSIONS OWNER_WRITE OWNER_READ)
	install( FILES ${PROJECT_SOURCE_DIR}/Black_Chocobo.desktop DESTINATION share/applications/ PERMISSIONS OWNER_WRITE OWNER_READ)
	install( FILES ${PROJECT_SOURCE_DIR}/debian/menu DESTINATION share/menu/ RENAME blackchocobo PERMISSIONS OWNER_WRITE OWNER_READ)
	install( FILES ${PROJECT_SOURCE_DIR}/debian/blackchocobo.sharedmimeinfo DESTINATION share/mime/packages/ RENAME blackchocobo.xml PERMISSIONS OWNER_WRITE OWNER_READ)
	
	SET(CPACK_SOURCE_GENERATOR "TGZ;TZ")
	SET(CPACK_GENERATOR "TGZ")
	#detect Distro Family DEB , RPM 
	if(EXISTS "/etc/debian_release")
	    set(DistroType DEB)
	elseif(EXISTS "/etc/fedora-release")
	    set(DistroType RPM)
	endif()
	message(STATUS "Distro Detected: ${DistroType} ")

	if(DistroType MATCHES "DEB")
	  # Setup DEB package properties
	  MESSAGE(STATUS "DEB ADDED TO GENERATION LIST")
	  SET(CPACK_GENERATOR "${CPACK_GENERATOR};DEB")
	endif()
	if(EXISTS "/usr/bin/rpmbuild")
	  MESSAGE(STATUS "RPM ADDED TO GENERATION LIST")
	  SET(CPACK_GENERATOR "${CPACK_GENERATOR};RPM")
	endif()
	  SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Chris Rizzitello <sithlord48@gmail.com>")
	#Find out what architecture are we running on and set the package architecture 
	  EXECUTE_PROCESS(COMMAND dpkg --print-architecture OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE OUTPUT_STRIP_TRAILING_WHITESPACE)
	  MESSAGE (STATUS "Architecture: ${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
	  #set the name to be debian package like.
	  SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
	  SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-src")
	  SET(CPACK_DEBIAN_PACKAGE_SECTION games)
	  SET(CPACK_DEBIAN_PACKAGE_PRIORITY extra)
	  SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libqtcore5,libqtgui5,libqt5-xml,libqt5widgets, libssl1.0.0")

	  SET(CPACK_RPM_PACKAGE_SUMMARY CPACK_PACKAGE_DESCRIPTION_SUMMARY)
	  SET(CPACK_RPM_PACKAGE_NAME CPACK_PACKAGE_NAME)
	  SET(CPACK_RPM_PACKAGE_VERSION CPACK_PACKAGE_VERSION)
	  SET(CPACK_RPM_PACKAGE_RELEASE 1)
	  SET(CPACK_RPM_PACKAGE_LICENSE "GPLv3+")
	  SET(CPACK_RPM_PACKAGE_GROUP games)
	  SET(CPACK_RPM_PACKAGE_VENDOR)
	  SET(CPACK_RPM_PACKAGE_DESCRIPTION)
	  SET(CPACK_RPM_PACKAGE_REQUIRES "qt,openssl")
endif()

INCLUDE (CPack)
