SET (TARGET pntreplace)
PROJECT (${TARGET})

include_directories(
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 ${QT_INCLUDE_DIR}
)
if( QT4BUILD )
  include( ${QT_USE_FILE} )
endif()

set( ${TARGET}_SRC pntreplace.cpp svgxmlhandler.cpp )
add_executable( ${TARGET} ${${TARGET}_SRC} )

if (QT4BUILD)
  target_link_libraries( ${TARGET} ${QT_QTCORE_LIBRARY} ${QT_QTMAIN_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSVG_LIBRARY} ${QT_QTXML_LIBRARY} )
else()
  target_link_libraries( ${TARGET} ${Qt5Core_LIBRARIES} ${Qt5Xml_LIBRARIES} ${Qt5Widgets_LIBRARIES} )
endif()
