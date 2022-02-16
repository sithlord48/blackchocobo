cmake_minimum_required( VERSION 3.21 )

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(REQUIRED_QT_VERSION "5.15.0")

cmake_policy(SET CMP0010 NEW)

project( blackchocobo VERSION 1.10.5 DESCRIPTION "Final Fantasy 7 Save Editor")
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

if(NOT QT_DEFAULT_MAJOR_VERSION)
    set(QT_DEFAULT_MAJOR_VERSION 5 CACHE STRING "" FORCE)
endif()

if (${QT_DEFAULT_MAJOR_VERSION} MATCHES "5")
    set(REQUIRED_QT_VERSION 5.15.2)
elseif (${QT_DEFAULT_MAJOR_VERSION} MATCHES "6")
    set(REQUIRED_QT_VERSION 6.2.0)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()


find_package(Qt${QT_DEFAULT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Gui
    Svg
    Quick
    Widgets
    Xml
)

if(${QT_DEFAULT_MAJOR_VERSION} MATCHES "6")
    find_package(Qt6 COMPONENTS Core5Compat REQUIRED)
endif()

find_package(ff7tk 0.80.22 REQUIRED NO_MODULE COMPONENTS
    ff7tk
    ff7tkWidgets
)

add_subdirectory(deploy)
add_subdirectory(icons)
add_subdirectory(lang)
add_subdirectory(qhexedit)

if(WIN32)
    set(PLATFORM_EX_SRC ${CMAKE_BINARY_DIR}/deploy/blackchocobo.rc)
    set(BIN_NAME "Black_Chocobo")
    if(CMAKE_COMPILER_IS_GNUCC)
        set (FF7TK_DEPENDS
            ${ff7tk_DIR}/../../../bin/libff7tk.dll
            ${ff7tk_DIR}/../../../bin/libff7tkWidgets.dll
        )
    else()
        set (FF7TK_DEPENDS
            ${ff7tk_DIR}/../../../bin/ff7tk.dll
            ${ff7tk_DIR}/../../../bin/ff7tkWidgets.dll
        )
    endif()
elseif(APPLE)
    set(PLATFORM_EX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/deploy/blackchocobo.icns)
    set_source_files_properties(${PLATFORM_EX_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    set(BIN_NAME "Black_Chocobo")
else()
    set(BIN_NAME "blackchocobo")
endif()

add_executable(${BIN_NAME} WIN32 MACOSX_BUNDLE
      src/main.cpp
      src/mainwindow.cpp
      src/about.cpp
      src/options.cpp
      src/errbox.cpp
      src/achievementdialog.cpp
      src/bcdialog.cpp
      src/bcsettings.cpp
      ${PLATFORM_EX_SRC}
    )

target_link_libraries (${BIN_NAME} PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Xml
        Qt::Quick
        QHEXEDIT
        libICONS
        ff7tk::ff7tk
        ff7tk::ff7tkWidgets
    )

if(${QT_DEFAULT_MAJOR_VERSION} EQUAL "6")
    target_link_libraries(${BIN_NAME} PUBLIC Qt6::Core5Compat)
endif()

if(APPLE)
    set_target_properties(${BIN_NAME} PROPERTIES
      INSTALL_NAME_DIR "@executable_path/../Frameworks @loader_path/../Frameworks"
      BUILD_WITH_INSTALL_NAME_DIR TRUE
      MACOSX_BUNDLE_BUNDLE_NAME "Black Chocobo"
      MACOSX_BUNDLE_DISPLAY_NAME "Black_Chocobo"
      MACOSX_BUNDLE_GUI_IDENTIFIER "org.sithlord48.blackchocobo"
      MACOSX_BUNDLE_ICON_FILE blackchocobo.icns
      MACOSX_BUNDLE_INFO_STRING "${CMAKE_PROJECT_DESCRIPTION}"
      MACOSX_BUNDLE_COPYRIGHT "2010-2020 Chris Rizzitello"
      MACOSX_BUNDLE_BUNDLE_VERSION ${BC_VERSION}
      MACOSX_BUNDLE_LONG_VERSION_STRING ${BC_VERSION}
      MACOSX_BUNDLE_SHORT_VERSION_STRING ${BC_VERSION}
    )
    target_compile_options(${BIN_NAME} PRIVATE -stdlib=libc++)
    install(TARGETS ${BIN_NAME} BUNDLE DESTINATION .)
elseif(UNIX AND NOT APPLE)
    install(TARGETS ${BIN_NAME} RUNTIME DESTINATION bin)
    install(FILES ${PROJECT_SOURCE_DIR}/COPYING.txt DESTINATION share/licenses/blackchocobo/ RENAME LICENSE)
elseif(WIN32)
    install(TARGETS ${BIN_NAME} RUNTIME DESTINATION .)
    install(FILES ${FF7TK_DEPENDS} DESTINATION .)
    install(FILES ${PROJECT_SOURCE_DIR}/COPYING.txt DESTINATION .)
endif()

##CPACK
set(CPACK_STRIP_FILES ${BIN_NAME})
get_target_property(_qmake_executable Qt${QT_DEFAULT_MAJOR_VERSION}::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING.txt")
set(CPACK_PACKAGE_NAME "Black_Chocobo")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/sithlord48/blackchocobo")
if(NOT CPACK_PACKAGE_VERSION)
    set(CPACK_PACKAGE_VERSION ${BC_VERSION})
endif()
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
    set(CPACK_NSIS_MUI_ICON "${PROJECT_SOURCE_DIR}/deploy/blackchocobo.ico")
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

    if(${QT_DEFAULT_MAJOR_VERSION} EQUAL "6")
        add_custom_command(
            TARGET ${BIN_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/qtDeploy
            COMMAND ${WINDEPLOYQT} --no-compiler-runtime --no-system-d3d-compiler --no-quick-import -xml -qml -network --dir ${CMAKE_BINARY_DIR}/qtDeploy $<TARGET_FILE:${BIN_NAME}>
        )
    else()
        add_custom_command(
            TARGET ${BIN_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/qtDeploy
            COMMAND ${WINDEPLOYQT} --no-compiler-runtime --no-system-d3d-compiler --no-angle --no-webkit2 --no-quick-import -xml -qml -network --dir ${CMAKE_BINARY_DIR}/qtDeploy $<TARGET_FILE:${BIN_NAME}>
        )
    endif()

    install(
        DIRECTORY ${CMAKE_BINARY_DIR}/qtDeploy/
        DESTINATION .
        FILES_MATCHING PATTERN "*.*"
    )
    set(CPACK_GENERATOR "ZIP;NSIS")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    find_program(MACDEPLOYQT macdeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(
        TARGET ${BIN_NAME} POST_BUILD
        COMMAND ${MACDEPLOYQT} ${BIN_NAME}.app
    )
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-macos")
    set(CPACK_DMG_BACKGROUND_IMAGE "${PROJECT_SOURCE_DIR}/deploy/dmg_background.png")
    set(CPACK_DMG_DS_STORE "${PROJECT_SOURCE_DIR}/deploy/dmg_ds_store")
    set(CPACK_DMG_VOLUME_NAME "${BIN_NAME}")
    set(CPACK_GENERATOR "DragNDrop")
endif()

set(CPACK_SOURCE_IGNORE_FILES build/* .git/* .directory CMakeLists.txt.user *.yml *.github/*)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-src")
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")
INCLUDE (CPack)
