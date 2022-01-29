#BUILD OUR ICON QRC FILE.
find_package(Qt${QT_DEFAULT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Svg
)
add_library(libICONS STATIC icons.qrc)
target_link_libraries(libICONS PUBLIC Qt::Svg)
