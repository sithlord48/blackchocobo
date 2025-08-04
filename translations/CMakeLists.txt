# SPDX-FileCopyrightText: Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: MIT
set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)
option(CLEAN_TRS "Clean Obsolete translations from tr files" OFF)
find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    LinguistTools
)

set ( blackchocobo_TRS
    blackchocobo_de.ts
    blackchocobo_en.ts
    blackchocobo_es.ts
    blackchocobo_fr.ts
    blackchocobo_it.ts
    blackchocobo_ja.ts
    blackchocobo_pl.ts
    blackchocobo_re.ts
    blackchocobo_zh.ts
)

if(WIN32 OR APPLE)
    file(REAL_PATH "${ff7tk_DIR}/../../../" ff7tk_ROOT )
    find_path(_ff7tk_I18N_PATH NAMES translations PATHS "${ff7tk_ROOT}" PATH_SUFFIXES "/share/ff7tk" NO_DEFAULT_PATH REQUIRED)
    file(REAL_PATH "${_ff7tk_I18N_PATH}/translations" ff7tk_I18N_PATH)

    set (FF7TK_TRS
        ${ff7tk_I18N_PATH}/ff7tk_de.qm
        ${ff7tk_I18N_PATH}/ff7tk_en.qm
        ${ff7tk_I18N_PATH}/ff7tk_es.qm
        ${ff7tk_I18N_PATH}/ff7tk_fr.qm
        ${ff7tk_I18N_PATH}/ff7tk_it.qm
        ${ff7tk_I18N_PATH}/ff7tk_ja.qm
        ${ff7tk_I18N_PATH}/ff7tk_pl.qm
        ${ff7tk_I18N_PATH}/ff7tk_re.qm
        ${ff7tk_I18N_PATH}/ff7tk_zh.qm
    )
endif()

if(CLEAN_TRS)
    set(CLEAN_OPTION "-no-obsolete")
else()
    set(CLEAN_OPTION "")
endif()

qt_create_translation(TRS ${CMAKE_SOURCE_DIR} ${blackchocobo_TRS} OPTIONS -no-ui-lines -locations none ${CLEAN_OPTION})
add_custom_target(app_translations ALL DEPENDS ${TRS})

if(UNIX AND NOT APPLE)
    install(FILES ${TRS} DESTINATION share/blackchocobo/translations)
elseif(WIN32)
    install(FILES ${TRS} DESTINATION translations)
    install(FILES ${FF7TK_TRS} DESTINATION translations)
elseif(APPLE)
    set(MAC_LANG_PATH Black_Chocobo.app/Contents/MacOS/translations)
    file(REAL_PATH "${_qt_bin_dir}/../" QT_ROOT_DIR)
    find_file(_QT_QM_FILE NAMES qtbase_de.qm PATHS ${QT_ROOT_DIR} PATH_SUFFIXES "translations" "share/qt/translations" REQUIRED)
    get_filename_component(MAC_QT_LANG_PATH "${_QT_QM_FILE}" DIRECTORY)
    install(FILES ${TRS} DESTINATION ${MAC_LANG_PATH})
    install(FILES ${FF7TK_TRS} DESTINATION ${MAC_LANG_PATH})
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_de.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_de.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_en.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_en.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_es.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_es.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_fr.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_fr.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_it.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_it.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_ja.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_ja.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_pl.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_pl.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_zh_CN.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_zh.qm)
endif()
