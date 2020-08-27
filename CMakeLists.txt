cmake_minimum_required( VERSION 3.8 )
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(REQUIRED_QT_VERSION "5.12.0")

project( blackchocobo VERSION 1.10.3 DESCRIPTION "Final Fantasy 7 Save Editor")
# Get the version from git if it's a git repository
set(BC_VERSION ${CMAKE_PROJECT_VERSION})
IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
  FIND_PACKAGE(Git)
  IF(GIT_FOUND)
    EXECUTE_PROCESS(
      COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE "GIT_VERSION"
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    MESSAGE( STATUS "Git Commit: ${GIT_VERSION}" )
    string(APPEND BC_VERSION "-${GIT_VERSION}")
  ENDIF(GIT_FOUND)
  ELSE()
ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
add_definitions(-DBC_VERSION="${BC_VERSION}")

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

#set( translatables
#    ${blackchocobo_HDRS}
#    ${blackchocobo_SRCS}
#    ${blackchocobo_UIS}
#    )
#qt5_create_translation(TRS ${translatables} ${blackchocobo_TRS})

set ( blackchocobo_TRS
    lang/bchoco_en.ts
    lang/bchoco_es.ts
    lang/bchoco_fr.ts
    lang/bchoco_de.ts
    lang/bchoco_ja.ts
    lang/bchoco_re.ts
    )
qt5_add_translation(TRS ${blackchocobo_TRS})

if(UNIX AND NOT APPLE)
    add_executable (blackchocobo ff7tk/about.h ${blackchocobo_SRCS} ${RESOURCES} ${TRS})
    target_link_libraries ( blackchocobo  Qt5::Core Qt5::Gui Qt5::Xml Qt5::Widgets Qt5::Quick)
    install(TARGETS blackchocobo RUNTIME DESTINATION bin)
    install(FILES ${TRS} DESTINATION share/blackchocobo/lang)
    install(FILES ${PROJECT_SOURCE_DIR}/deploy/Black_Chocobo.png DESTINATION share/pixmaps/)
    install(FILES ${PROJECT_SOURCE_DIR}/deploy/Black_Chocobo.desktop DESTINATION share/applications/)
    install(FILES ${PROJECT_SOURCE_DIR}/deploy/blackchocobo.xml DESTINATION share/mime/packages/)
    install(FILES ${PROJECT_SOURCE_DIR}/deploy/Black_Chocobo.appdata.xml DESTINATION share/metadata/)
    install(FILES ${PROJECT_SOURCE_DIR}/deploy/blackchocobo DESTINATION share/menu/)
    install(FILES ${PROJECT_SOURCE_DIR}/COPYING.txt DESTINATION licenses/blackchocobo/ RENAME LICENSE)
elseif(WIN32)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/deploy/blackchocobo.rc.in ${CMAKE_CURRENT_BINARY_DIR}/blackchocobo.rc @ONLY)
    add_executable (Black_Chocobo WIN32 ff7tk/about.h ${blackchocobo_SRCS} ${RESOURCES} ${TRS} ${CMAKE_CURRENT_BINARY_DIR}/blackchocobo.rc)
    if(CMAKE_COMPILER_IS_GNUCC)
        #Prevent ms padding on spacked structures on gcc compiler
        target_compile_options(Black_Chocobo PRIVATE -mno-ms-bitfields)
    endif()
    target_link_libraries (Black_Chocobo Qt5::Core Qt5::Gui Qt5::Xml Qt5::Widgets Qt5::Quick)
    install(TARGETS Black_Chocobo RUNTIME DESTINATION .)
    install(FILES ${TRS} DESTINATION lang)
    install(FILES ${PROJECT_SOURCE_DIR}/COPYING.txt DESTINATION .)
elseif(APPLE)
    set(MACOSX_BUNDLE_BUNDLE_NAME "Black Chocobo")
    set(MACOSX_BUNDLE_DISPLAY_NAME "Black_Chocobo")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.sithlord48.blackchocobo")
    set(MACOSX_BUNDLE_ICON_FILE bchoco_icon_osx.icns)
    set(MACOSX_BUNDLE_INFO_STRING "${CMAKE_PROJECT_DESCRIPTION}")
    set(MACOSX_BUNDLE_COPYRIGHT "2010-2020 Chris Rizzitello")
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${BC_VERSION})
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${BC_VERSION})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${BC_VERSION})
    set(APPICON ${CMAKE_CURRENT_SOURCE_DIR}/deploy/bchoco_icon_osx.icns)
    set_source_files_properties(${APPICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    set_source_files_properties(${TRS} PROPERTIES MACOSX_PACKAGE_LOCATION "MacOS/lang")
    add_executable(Black_Chocobo MACOSX_BUNDLE ff7tk/about.h ${blackchocobo_SRCS} ${RESOURCES} ${TRS} ${APPICON})
    target_compile_options(Black_Chocobo PRIVATE -stdlib=libc++)
    target_link_libraries (Black_Chocobo Qt5::Core Qt5::Gui Qt5::Xml Qt5::Widgets Qt5::Quick)
    install(TARGETS Black_Chocobo BUNDLE DESTINATION .)
endif()

##CPACK
set(CPACK_STRIP_FILES blackchocobo)
get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING.txt")
set(CPACK_PACKAGE_NAME "Black_Chocobo")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/sithlord48/blackchocobo")
set(CPACK_PACKAGE_VERSION ${BC_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${CMAKE_PROJECT_DESCRIPTION})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    #install generic files needed for linux package
    set(CPACK_GENERATOR "TXZ")
    EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-linux-${ARCHITECTURE}")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "Black_Chocobo")
    set(CPACK_NSIS_DISPLAY_NAME ${CMAKE_PACKAGE_NAME})
    set(CPACK_NSIS_COMPRESSOR lzma)
    set(CPACK_NSIS_MUI_ICON "${PROJECT_SOURCE_DIR}/deploy/bchoco_icon_win.ico")
    set(CPACK_NSIS_INSTALLED_ICON_NAME Black_Chocobo.exe)
    set(CPACK_NSIS_MENU_LINKS "Black_Chocobo.exe" "Black Chocobo")
    set(CPACK_NSIS_EXTRA_PREINSTALL_COMMANDS "!include \\\"${PROJECT_SOURCE_DIR}\\\\deploy\\\\FileAssociation.nsh\\\"")
    set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "\\\${RegisterExtension} '$INSTDIR\\\\Black_Chocobo.exe' '.ff7' 'FF7 PC Save File'")
    set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS 
        "\\\${UnRegisterExtension} '.ff7' 'FF7 PC Save File'"
        "RMDir /r '$INSTDIR'"
    )
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)
    set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
    include(InstallRequiredSystemLibraries)
    find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(
        TARGET Black_Chocobo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/qtDeploy
        COMMAND ${WINDEPLOYQT} --no-compiler-runtime --no-system-d3d-compiler --no-angle --no-webkit2 --no-quick-import --no-translations --dir ${CMAKE_BINARY_DIR}/qtDeploy $<TARGET_FILE:Black_Chocobo>
    )
    install(
        DIRECTORY ${CMAKE_BINARY_DIR}/qtDeploy/
        DESTINATION .
        FILES_MATCHING PATTERN "*.*"
    )
    set(CPACK_GENERATOR "ZIP;NSIS")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    find_program(MACDEPLOYQT macdeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(
        TARGET Black_Chocobo POST_BUILD
        COMMAND ${MACDEPLOYQT} Black_Chocobo.app
    )
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-macos")
    set(CPACK_DMG_BACKGROUND_IMAGE "${PROJECT_SOURCE_DIR}/deploy/dmg_background.png")
    set(CPACK_DMG_DS_STORE "${PROJECT_SOURCE_DIR}/deploy/dmg_ds_store")
    set(CPACK_DMG_VOLUME_NAME "Black_Chocobo")
    set(CPACK_GENERATOR "DragNDrop")
endif()

set(CPACK_SOURCE_IGNORE_FILES build/* .git/* .directory CMakeLists.txt.user *.yml)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-src")
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")
INCLUDE (CPack)
