find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Gui
    Widgets
)

add_library(QHEXEDIT STATIC
    chunks.cpp
    commands.cpp
    qhexedit.cpp
)

target_include_directories(QHEXEDIT PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(QHEXEDIT Qt::Core Qt::Gui Qt::Widgets)
