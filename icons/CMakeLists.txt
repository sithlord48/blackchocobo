#BUILD OUR ICON QRC FILE.
find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    Svg
)
add_library(BCICONS STATIC icons.qrc)
target_link_libraries(BCICONS PUBLIC Qt::Svg)
