set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)

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
)

set (FF7TK_TRS
    ${ff7tk_DIR}/../../../share/ff7tk/translations/ff7tk_de.qm
    ${ff7tk_DIR}/../../../share/ff7tk/translations/ff7tk_en.qm
    ${ff7tk_DIR}/../../../share/ff7tk/translations/ff7tk_es.qm
    ${ff7tk_DIR}/../../../share/ff7tk/translations/ff7tk_fr.qm
    ${ff7tk_DIR}/../../../share/ff7tk/translations/ff7tk_it.qm
    ${ff7tk_DIR}/../../../share/ff7tk/translations/ff7tk_ja.qm
    ${ff7tk_DIR}/../../../share/ff7tk/translations/ff7tk_pl.qm
    ${ff7tk_DIR}/../../../share/ff7tk/translations/ff7tk_re.qm
)

qt_create_translation(TRS ${CMAKE_SOURCE_DIR} ${blackchocobo_TRS} OPTIONS -no-ui-lines -locations none)
add_custom_target(app_translations ALL DEPENDS ${TRS})

if(UNIX AND NOT APPLE)
    install(FILES ${TRS} DESTINATION share/blackchocobo/translations)
elseif(WIN32)
    install(FILES ${TRS} DESTINATION translations)
    install(FILES ${FF7TK_TRS} DESTINATION translations)
elseif(APPLE)
    set(MAC_LANG_PATH Black_Chocobo.app/Contents/MacOS/translations)
    set(MAC_QT_LANG_PATH ${Qt${QT_DEFAULT_MAJOR_VERSION}_DIR}/../../../translations)
    install(FILES ${TRS} DESTINATION ${MAC_LANG_PATH})
    install(FILES ${FF7TK_TRS} DESTINATION ${MAC_LANG_PATH})
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_de.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_de.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_en.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_en.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_es.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_es.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_fr.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_fr.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_it.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_it.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_ja.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_ja.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_pl.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_pl.qm)
endif()
