cmake_minimum_required( VERSION 3.8 )
project( blackchocobo VERSION 1.10.3 DESCRIPTION "Final Fantasy 7 Save Editor")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set( CMAKE_BUILD_TYPE Release )
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(REQUIRED_QT_VERSION "5.12.0")

if(WIN32)
    if(CMAKE_COMPILER_IS_GNUCC)
        #Prevent ms padding on packed structures on gcc compiler
        add_definitions(-mno-ms-bitfields)
    endif()
elseif(APPLE)
    add_definitions(-stdlib=libc++)
endif()

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Widgets
    Gui
    Xml
    Quick
)
find_package(Qt5LinguistTools)

set ( blackchocobo_HDRS
    ff7tk/data/Type_FF7CHOCOBO.h
    ff7tk/data/FF7FieldItemList.h
    ff7tk/data/Type_materia.h
    ff7tk/data/Type_FF7CHAR.h
    ff7tk/data/FF7Save_Types.h
    ff7tk/data/FF7Save_Const.h
    )

set ( blackchocobo_SRCS
    src/main.cpp
    src/mainwindow.cpp
    src/about.cpp
    src/options.cpp
    src/errbox.cpp
    src/achievementdialog.cpp
    src/bcdialog.cpp
    src/bcsettings.cpp
    qhexedit/chunks.cpp
    qhexedit/commands.cpp
    qhexedit/qhexedit.cpp
    ff7tk/data/crypto/aes.c
    ff7tk/data/SaveIcon.cpp
    ff7tk/data/FF7Text.cpp
    ff7tk/data/FF7Save.cpp
    ff7tk/data/FF7SaveInfo.cpp
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
    src/mainwindow.ui
    src/about.ui
    src/options.ui
    )


set ( RESOURCES
    icon/images.qrc
    ff7tk/icons/achievements.qrc
    ff7tk/icons/characters.qrc
    ff7tk/icons/chocobo.qrc
    ff7tk/icons/common.qrc
    ff7tk/icons/items.qrc
    ff7tk/icons/locations.qrc
    ff7tk/icons/materia.qrc
    ff7tk/icons/psxButtons.qrc
    )

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

if(NOT APPLE)
    add_executable ( blackchocobo ff7tk/about.h ${blackchocobo_SRCS} ${RESOURCES} ${TRS})
    target_link_libraries ( blackchocobo  Qt5::Core Qt5::Gui Qt5::Xml Qt5::Widgets Qt5::Quick)
    install(TARGETS blackchocobo RUNTIME DESTINATION bin)
else()
    set(MACOSX_BUNDLE_DISPLAY_NAME "Black Chocobo")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.sithlord48.blackchocobo")
    set(MACOSX_BUNDLE_BUNDLE_NAME "Black_Chocobo")
    set(MACOSX_BUNDLE_DISPLAY_NAME "Black_Chocobo")
    set(MACOSX_BUNDLE_ICON_FILE deploy/bchoco_icon_osx.icns)
    set(MACOSX_BUNDLE_INFO_STRING "Black Chocobo")
    set(MACOSX_BUNDLE_COPYRIGHT "2010-2020 Chris Rizzitello")
    set(APPICON ${CMAKE_CURRENT_SOURCE_DIR}/deploy/bchoco_icon_osx.icns)
    set_source_files_properties(${APPICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(Black_Chocobo MACOSX_BUNDLE ff7tk/about.h ${blackchocobo_SRCS} ${RESOURCES} ${TRS} ${APPICON})
    install(TARGETS Black_Chocobo BUNDLE DESTINATION bin)
    install(FILES ${TRS} DESTINATION Black_Chocobo.app/Contents/MacOS/)
endif()

if(UNIX AND NOT APPLE)
    install(FILES ${TRS} DESTINATION share/blackchocobo/lang)
    install( FILES ${PROJECT_SOURCE_DIR}/deploy/Black_Chocobo.png DESTINATION share/pixmaps/)
    install( FILES ${PROJECT_SOURCE_DIR}/deploy/Black_Chocobo.desktop DESTINATION share/applications/)
    install( FILES ${PROJECT_SOURCE_DIR}/deploy/blackchocobo.xml DESTINATION share/mime/packages/ )
    install( FILES ${PROJECT_SOURCE_DIR}/deploy/Black_Chocobo.appdata.xml DESTINATION share/metadata/)
    install( FILES ${PROJECT_SOURCE_DIR}/deploy/blackchocobo DESTINATION share/menu/)
elseif(WIN32)
    install(FILES ${TRS} DESTINATION bin)
endif()

#install stuff
INCLUDE (InstallRequiredSystemLibraries)

SET(CPACK_SOURCE_IGNORE_FILES build/*)

SET(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING.txt")
SET(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
SET(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${CMAKE_PROJECT_DESCRIPTION})
SET(CPACK_STRIP_FILES blackchocobo)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    #install generic files needed for linux package

    SET(CPACK_SOURCE_GENERATOR "TGZ;TZ")
    SET(CPACK_GENERATOR "STGZ;TGZ")
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
      SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
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
      SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-src")
      SET(CPACK_DEBIAN_PACKAGE_SECTION games)
      SET(CPACK_DEBIAN_PACKAGE_PRIORITY extra)
      SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libqtcore5,libqtgui5,libqt5-xml,libqt5widgets")

      SET(CPACK_RPM_PACKAGE_SUMMARY CPACK_PACKAGE_DESCRIPTION_SUMMARY)
      SET(CPACK_RPM_PACKAGE_NAME CPACK_PACKAGE_NAME)
      SET(CPACK_RPM_PACKAGE_VERSION CPACK_PACKAGE_VERSION)
      SET(CPACK_RPM_PACKAGE_RELEASE 1)
      SET(CPACK_RPM_PACKAGE_LICENSE "GPLv3+")
      SET(CPACK_RPM_PACKAGE_GROUP games)
      SET(CPACK_RPM_PACKAGE_VENDOR)
      SET(CPACK_RPM_PACKAGE_DESCRIPTION)
      SET(CPACK_RPM_PACKAGE_REQUIRES "qt")
endif()

INCLUDE (CPack)
