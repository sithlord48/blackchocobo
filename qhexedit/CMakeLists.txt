set(qhexedit_SRCS
    chunks.cpp
    commands.cpp
    qhexedit.cpp
)
add_library(QHEXEDIT STATIC ${qhexedit_SRCS})
target_link_libraries(QHEXEDIT Qt::Core Qt::Gui Qt::Widgets)
