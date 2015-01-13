project( blackchocobo )
#version number
# The version number.
set(blackchocobo_VERSION_MAJOR 1)
set(blackchocobo_VERSION_MINOR 9)
set(blackchocobo_VERSION_PATCH 83)
cmake_minimum_required( VERSION 2.6 )
set ( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
find_package ( Qt4 REQUIRED )
find_package ( OpenSSL REQUIRED )
include ( ${QT_USE_FILE} )
include_directories (
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTXML_INCLUDE_DIR}
	${OPENSSL_INCLUDE_DIR}
	)
set ( blackchocobo_HDRS
	version.h
	qhexedit/xbytearray.h
	qhexedit/commands.h
	FF7tk/data/Type_FF7CHOCOBO.h
	FF7tk/data/FF7FieldItemList.h
	FF7tk/data/Type_materia.h
	FF7tk/data/Type_FF7CHAR.h
	FF7tk/data/FF7Save_Types.h
	FF7tk/data/FF7Save_Const.h
	FF7tk/data/FF7Materia.h
	FF7tk/data/FF7Location.h
	FF7tk/data/FF7Item.h
	FF7tk/data/FF7Char.h
	)

set ( blackchocobo_SRCS
	main.cpp
	mainwindow.cpp
	about.cpp
	options.cpp
	errbox.cpp
	achievementdialog.cpp
	qhexedit/xbytearray.cpp
	qhexedit/qhexedit_p.cpp
	qhexedit/qhexedit.cpp
	qhexedit/commands.cpp
	FF7tk/data/SaveIcon.cpp
	FF7tk/data/FF7Text.cpp
	FF7tk/data/FF7Save.cpp
	FF7tk/data/FF7Materia.cpp
	FF7tk/data/FF7Location.cpp
	FF7tk/data/FF7Item.cpp
	FF7tk/data/FF7Char.cpp
	FF7tk/data/FF7FieldItemList.cpp
	FF7tk/widgets/SlotSelect.cpp
	FF7tk/widgets/SlotPreview.cpp
	FF7tk/widgets/MateriaEditor.cpp
	FF7tk/widgets/ItemPreview.cpp
	FF7tk/widgets/DialogPreview.cpp
	FF7tk/widgets/ChocoboEditor.cpp
	FF7tk/widgets/CharEditor.cpp
	FF7tk/widgets/ItemSelector.cpp
	FF7tk/widgets/ItemList.cpp
	FF7tk/widgets/MetadataCreator.cpp
	FF7tk/widgets/DoubleCheckBox.cpp
	FF7tk/widgets/MenuListWidget.cpp
	FF7tk/widgets/OptionsWidget.cpp
	FF7tk/widgets/ChocoboManager.cpp
	FF7tk/widgets/ChocoboLabel.cpp
	FF7tk/widgets/LocationViewer.cpp
	FF7tk/widgets/AchievementEditor.cpp
	FF7tk/widgets/PhsListWidget.cpp
	FF7tk/data/FF7Achievements.cpp
	)

set ( blackchocobo_UIS
	mainwindow.ui
	about.ui
	options.ui
	)
QT4_WRAP_UI(UIS ${blackchocobo_UIS})

set ( blackchocobo_RSCS
	images.qrc
	FF7tk/icons/achievements.qrc
	FF7tk/icons/characters.qrc
	FF7tk/icons/chocobo.qrc
	FF7tk/icons/common.qrc
	FF7tk/icons/items.qrc
	FF7tk/icons/locations.qrc
	FF7tk/icons/materia.qrc
	FF7tk/icons/psxButtons.qrc
	)
QT4_ADD_RESOURCES(RSCS ${blackchocobo_RSCS})

set ( blackchocobo_TRS
	lang/bchoco_en.ts
	lang/bchoco_es.ts
	lang/bchoco_fr.ts
	lang/bchoco_de.ts
	lang/bchoco_ja.ts
	lang/bchoco_re.ts
	)
QT4_ADD_TRANSLATION(TRS ${blackchocobo_TRS})

set ( blackchocobo_MOCS
	mainwindow.h
	about.h
	options.h
	errbox.h
	qhexedit/qhexedit_p.h
	qhexedit/qhexedit.h
	achievementdialog.h
	FF7tk/data/FF7Achievements.h
	FF7tk/data/SaveIcon.h
	FF7tk/data/FF7Text.h
	FF7tk/data/FF7Save.h
	FF7tk/widgets/ItemSelector.h
	FF7tk/widgets/ItemList.h
	FF7tk/widgets/MetadataCreator.h
	FF7tk/widgets/SlotSelect.h
	FF7tk/widgets/SlotPreview.h
	FF7tk/widgets/MateriaEditor.h
	FF7tk/widgets/ItemPreview.h
	FF7tk/widgets/DialogPreview.h
	FF7tk/widgets/ChocoboEditor.h
	FF7tk/widgets/CharEditor.h
	FF7tk/widgets/PhsListWidget.h
	FF7tk/widgets/DoubleCheckBox.h
	FF7tk/widgets/MenuListWidget.h
	FF7tk/widgets/OptionsWidget.h
	FF7tk/widgets/ChocoboManager.h
	FF7tk/widgets/ChocoboLabel.h
	FF7tk/widgets/LocationViewer.h
	FF7tk/widgets/AchievementEditor.h
	)
QT4_WRAP_CPP(MOCS ${blackchocobo_MOCS})

add_executable ( blackchocobo ${blackchocobo_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )
target_link_libraries ( blackchocobo  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTXML_LIBRARY} ${OPENSSL_LIBRARIES} )

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
	if(EXISTS "/etc/lsb-release")
	    set(DistroType DEB)
	elseif(EXISTS "/etc/debian_release")
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
	  SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libqtcore4,libqtgui4,libqt4-xml,libssl1.0.0")

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