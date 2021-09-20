set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)
find_package(Qt5LinguistTools)

set ( blackchocobo_TRS
    bchoco_en.ts
    bchoco_es.ts
    bchoco_fr.ts
    bchoco_de.ts
    bchoco_ja.ts
    bchoco_re.ts
    bchoco_pl.ts
    )

set (FF7TK_TRS
    ${ff7tk_DIR}/../../../share/ff7tk/lang/ff7tk_en.qm
    ${ff7tk_DIR}/../../../share/ff7tk/lang/ff7tk_es.qm
    ${ff7tk_DIR}/../../../share/ff7tk/lang/ff7tk_fr.qm
    ${ff7tk_DIR}/../../../share/ff7tk/lang/ff7tk_de.qm
    ${ff7tk_DIR}/../../../share/ff7tk/lang/ff7tk_ja.qm
    ${ff7tk_DIR}/../../../share/ff7tk/lang/ff7tk_re.qm
    ${ff7tk_DIR}/../../../share/ff7tk/lang/ff7tk_pl.qm
)

qt5_create_translation(TRS ${CMAKE_SOURCE_DIR} ${blackchocobo_TRS})
add_custom_target(app_translations ALL DEPENDS ${TRS})

if(UNIX AND NOT APPLE)
    install(FILES ${TRS} DESTINATION share/blackchocobo/lang)
elseif(WIN32)
    install(FILES ${TRS} DESTINATION lang)
    install(FILES ${FF7TK_TRS} DESTINATION lang)
elseif(APPLE)
    set(MAC_LANG_PATH Black_Chocobo.app/Contents/MacOS/lang)
    set(MAC_QT_LANG_PATH ${Qt5_DIR}/../../../translations)
    install(FILES ${TRS} DESTINATION ${MAC_LANG_PATH})
    install(FILES ${FF7TK_TRS} DESTINATION ${MAC_LANG_PATH})
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_en.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_en.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_de.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_de.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_es.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_es.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_fr.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_fr.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_ja.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_ja.qm)
    install(FILES ${MAC_QT_LANG_PATH}/qtbase_pl.qm DESTINATION ${MAC_LANG_PATH} RENAME qt_pl.qm)
endif()
