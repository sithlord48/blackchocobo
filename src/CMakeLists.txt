find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core5Compat
    Gui
    Svg
    Quick
    Widgets
    Xml
)

find_package(ff7tk 0.82.00 REQUIRED NO_MODULE COMPONENTS
    ff7tk
    ff7tkWidgets
)

add_subdirectory(dialogs)
add_subdirectory(widgets)

if(WIN32)
    set(PLATFORM_EX_SRC ${CMAKE_BINARY_DIR}/deploy/blackchocobo.rc)
    if(CMAKE_COMPILER_IS_GNUCC)
        set (FF7TK_DEPENDS
            ${ff7tk_DIR}/../../../bin/libff7tk.dll
            ${ff7tk_DIR}/../../../bin/libff7tkQtWidgets.dll
            ${ff7tk_DIR}/../../../bin/libff7tkWidgets.dll
        )
    else()
        set (FF7TK_DEPENDS
            ${ff7tk_DIR}/../../../bin/ff7tk.dll
            ${ff7tk_DIR}/../../../bin/ff7tkQtWidgets.dll
            ${ff7tk_DIR}/../../../bin/ff7tkWidgets.dll
        )
    endif()
elseif(APPLE)
    set(PLATFORM_EX_SRC ${CMAKE_SOURCE_DIR}/deploy/blackchocobo.icns)
    set_source_files_properties(${PLATFORM_EX_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

add_executable(${BIN_NAME} WIN32 MACOSX_BUNDLE
      main.cpp
      blackchocobo.cpp blackchocobo.ui
      bcsettings.cpp
      ${PLATFORM_EX_SRC}
    )

target_link_libraries (${BIN_NAME} PUBLIC
        Qt::Core
        Qt::Xml
        Qt::Quick
        BCDIALOGS
        BCICONS
        BCWIDGETS
        QHEXEDIT
        ff7tk::ff7tk
        ff7tk::ff7tkWidgets
    )

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
    add_custom_command(
        TARGET ${BIN_NAME} POST_BUILD
        COMMAND ${PLATFORMDEPLOYQT} ${BIN_NAME}.app
    )
    install(TARGETS ${BIN_NAME} BUNDLE DESTINATION .)
elseif(UNIX AND NOT APPLE)
    install(TARGETS ${BIN_NAME} RUNTIME DESTINATION bin)
    install(FILES ${PROJECT_SOURCE_DIR}/COPYING.txt DESTINATION share/licenses/blackchocobo/ RENAME LICENSE)
elseif(WIN32)
    install(TARGETS ${BIN_NAME} RUNTIME DESTINATION .)
    install(FILES ${FF7TK_DEPENDS} DESTINATION .)
    install(FILES ${PROJECT_SOURCE_DIR}/COPYING.txt DESTINATION .)
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)
    set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
    include(InstallRequiredSystemLibraries)
    add_custom_command(
            TARGET ${BIN_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/qtDeploy
            COMMAND ${PLATFORMDEPLOYQT} --no-compiler-runtime --no-system-d3d-compiler --no-quick-import -xml -qml -network --dir ${CMAKE_BINARY_DIR}/qtDeploy $<TARGET_FILE:${BIN_NAME}>
    )
    install(
        DIRECTORY ${CMAKE_BINARY_DIR}/qtDeploy/
        DESTINATION .
        FILES_MATCHING PATTERN "*.*"
    )
endif()
