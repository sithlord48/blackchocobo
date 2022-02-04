#BUILD OUR ICON QRC FILE.
add_library(libICONS STATIC icons.qrc)
target_link_libraries(libICONS PUBLIC Qt::Svg)
