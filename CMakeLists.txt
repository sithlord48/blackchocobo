project( blackchocobo )
set(blackchocobo_VERSION_MAJOR 1)
set(blackchocobo_VERSION_MINOR 10)
set(blackchocobo_VERSION_PATCH 1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set ( CMAKE_BUILD_TYPE Release )
cmake_minimum_required( VERSION 3.8 )
set(REQUIRED_QT_VERSION "5.11.0")
add_definitions ( -Wall )

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

add_executable ( blackchocobo ${blackchocobo_SRCS} ${RESOURCES} ${TRS} )
target_link_libraries ( blackchocobo  Qt5::Core Qt5::Gui Qt5::Xml Qt5::Widgets Qt5::Quick )

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
