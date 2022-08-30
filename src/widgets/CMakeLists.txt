add_library(BCWIDGETS STATIC
    partytab.cpp
    partytab.h
)
target_include_directories(BCWIDGETS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(BCWIDGETS PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    ff7tk::ff7tk
    ff7tk::ff7tkData
    ff7tk::ff7tkQtWidgets
    ff7tk::ff7tkWidgets
)
