add_library(BCDIALOGS STATIC
    about.cpp about.ui
    bcdialog.cpp
    errbox.cpp
    options.cpp options.ui
)
target_include_directories(BCDIALOGS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(BCDIALOGS
    PUBLIC
      Qt::Core5Compat
      Qt::Core
      Qt::Gui
      Qt::Widgets
      ff7tk::ff7tk
      ff7tk::ff7tkWidgets
)

