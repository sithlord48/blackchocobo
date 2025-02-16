# SPDX-FileCopyrightText: 2020, 2025 Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: MIT

# Get OS INFO
macro (SET_OS_INFO)
    if (APPLE)
        set(OS_STRING "macos")
    elseif(WIN32)
        if(CMAKE_SYSTEM_PROCESSOR MATCHES AMD64)
            set(OS_STRING "win64")
        elseif(CMAKE_SYSTEM_PROCESSOR MATCHES ARM64)
            set(OS_STRING "win-arm64")
        else()
            set(OS_STRING "win-${CMAKE_SYSTEM_PROCESSOR}")
        endif()
    elseif(UNIX AND NOT APPLE)
        if(EXISTS "/etc/os-release")
            FILE(STRINGS "/etc/os-release" RELEASE_FILE_CONTENTS)
        else()
            message(FATAL_ERROR "Unable to read file /etc/os-release")
        endif()
        foreach(LINE IN LISTS RELEASE_FILE_CONTENTS)
            if( "${LINE}" MATCHES "^ID=")
                string(REGEX REPLACE "^ID=" "" DISTRO_NAME ${LINE})
                string(REGEX REPLACE "\"" "" DISTRO_NAME ${DISTRO_NAME})
                message(DEBUG "Distro Name :${DISTRO_NAME}")
            elseif( "${LINE}" MATCHES "^ID_LIKE=")
                string(REGEX REPLACE "^ID_LIKE=" "" DISTRO_LIKE "${LINE}")
                string(REGEX REPLACE "\"" "" DISTRO_LIKE ${DISTRO_LIKE})
                message(DEBUG "Distro Like :${DISTRO_LIKE}")
            elseif( "${LINE}" MATCHES "^VERSION_CODENAME=")
                string(REGEX REPLACE "^VERSION_CODENAME=" "" DISTRO_CODENAME "${LINE}")
                string(REGEX REPLACE "\"" "" DISTRO_CODENAME "${DISTRO_CODENAME}")
                message(DEBUG "Distro Codename:${DISTRO_CODENAME}")
            elseif( "${LINE}" MATCHES "^VERSION_ID=")
                string(REGEX REPLACE "^VERSION_ID=" "" DISTRO_VERSION_ID "${LINE}")
                string(REGEX REPLACE "\"" "" DISTRO_VERSION_ID "${DISTRO_VERSION_ID}")
                message(DEBUG "Distro VersionID:${DISTRO_VERSION_ID}")
            endif()
        endforeach()

        # Check if Debian-link
        string(REGEX MATCH debian|buntu DEBTYPE "${DISTRO_LIKE}")
        string(REGEX MATCH debian|deepin|uos DEBNAME "${DISTRO_NAME}")
        if((NOT ("${DEBTYPE}" STREQUAL "")) OR (NOT ("${DEBNAME}" STREQUAL "")))
            list(APPEND CPACK_GENERATOR "DEB")
        endif()
        # Check if Rpm-like
        string(REGEX MATCH suse|fedora|rhel RPMTYPE "${DISTRO_LIKE}")
        string(REGEX MATCH fedora|suse|rhel RPMNAME "${DISTRO_NAME}")
        if((NOT ("${RPMTYPE}" STREQUAL "")) OR (NOT ("${RPMNAME}" STREQUAL "")))
            list(APPEND CPACK_GENERATOR "RPM")
        endif()

        # Disto specific name adjustments
        if("${DISTRO_NAME}" STREQUAL "opensuse-tumbleweed")
            set(DISTRO_NAME "opensuse")
            set(DISTRO_CODENAME "tumbleweed")
        elseif("${DISTRO_NAME}" STREQUAL "arch")
            # Arch linux is rolling the version id reported is the date of last iso.
            set(DISTRO_VERSION_ID "")
        endif()
        # Determain the code name to be used if any
        if(NOT "${DISTRO_VERSION_ID}" STREQUAL "")
            set(CN_STRING "${DISTRO_VERSION_ID}-")
        endif()

        if(NOT "${DISTRO_CODENAME}" STREQUAL "")
            set(CN_STRING "${DISTRO_CODENAME}-")
        endif()

        if("${DISTRO_NAME}" STREQUAL "")
            if(${CMAKE_SYSTEM_NAME} MATCHES "|.*BSD")
                set(DISTRO_NAME ${CMAKE_SYSTEM_NAME})
            else()
                set(DISTRO_NAME "linux")
            endif()
        endif()
        set(OS_STRING "${DISTRO_NAME}-${CN_STRING}${CMAKE_SYSTEM_PROCESSOR}")
    endif()
endmacro()

if(UNIX AND NOT APPLE)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/blackchocobo.png DESTINATION share/icons/hicolor/512x512/apps/ RENAME io.github.sithlord48.blackchocobo.png)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/io.github.sithlord48.blackchocobo.desktop DESTINATION share/applications/)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/io.github.sithlord48.blackchocobo.xml DESTINATION share/mime/packages/)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/io.github.sithlord48.blackchocobo.metainfo.xml DESTINATION share/metainfo/)
elseif(WIN32)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/blackchocobo.rc.in ${CMAKE_CURRENT_BINARY_DIR}/blackchocobo.rc @ONLY)
endif()

##CPACK
find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/preBuildCPack.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/preBuildCPack.cmake @ONLY)
set(CPACK_PRE_BUILD_SCRIPTS ${CMAKE_CURRENT_BINARY_DIR}/preBuildCPack.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cpackOptions.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/cpackOptions.cmake @ONLY)
set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/cpackOptions.cmake)

set(CPACK_STRIP_FILES TRUE)
#Qt Info to get deploy app

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING.txt")
set(CPACK_PACKAGE_NAME "Black_Chocobo")
set(CPACK_PACKAGE_VENDOR "sithlord48")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/sithlord48/blackchocobo")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${CMAKE_PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})

if(NOT PACKAGE_VERSION_LABEL)
    set (PACKAGE_VERSION_LABEL "${CPACK_PACKAGE_VERSION}")
endif()

SET_OS_INFO()
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PACKAGE_VERSION_LABEL}-${OS_STRING}")

set(CPACK_DEBIAN_PACKAGE_NAME "blackchocobo")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "sithlord48@gmail.com")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libff7tk (>= ${REQUIRED_FF7TK_VERSION}) | libff7tk-all (>=${REQUIRED_FF7TK_VERSION}), qt6-qpa-plugins")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    #install generic files needed for linux package
    set(CPACK_GENERATOR "TXZ")
    EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)
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
    set(CPACK_GENERATOR "ZIP;NSIS")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(CPACK_PACKAGE_ICON "${PROJECT_SOURCE_DIR}/deploy/dmg_icon.icns")
    set(CPACK_DMG_BACKGROUND_IMAGE "${PROJECT_SOURCE_DIR}/deploy/dmg_background.png")
    set(CPACK_DMG_DS_STORE_SETUP_SCRIPT "${PROJECT_SOURCE_DIR}/deploy/generate_ds_store.applescript")
    set(CPACK_DMG_VOLUME_NAME "${BIN_NAME}")
    set(CPACK_GENERATOR "DragNDrop")
endif()

set(CPACK_SOURCE_IGNORE_FILES build/* .git/* .directory CMakeLists.txt.user *.yml *.github/*)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-src")
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")
INCLUDE (CPack)
