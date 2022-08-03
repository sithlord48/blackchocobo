if(UNIX AND NOT APPLE)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/blackchocobo.png DESTINATION share/pixmaps/)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/org.sithlord48.blackchocobo.desktop DESTINATION share/applications/)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/blackchocobo.xml DESTINATION share/mime/packages/)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/blackchocobo.appdata.xml DESTINATION share/metainfo/)
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
if(NOT CPACK_PACKAGE_VERSION)
    set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
endif()
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${CMAKE_PROJECT_DESCRIPTION})

set(CPACK_DEBIAN_PACKAGE_NAME "blackchocobo")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "sithlord48@gmail.com")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libff7tk (>= ${REQUIRED_FF7TK_VERSION}) | libff7tk-all (>=${REQUIRED_FF7TK_VERSION})")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

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
    set(CPACK_GENERATOR "ZIP;NSIS")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-macos")
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
