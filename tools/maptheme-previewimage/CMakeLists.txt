SET (TARGET maptheme-previewimage)
PROJECT (${TARGET})

include_directories(
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 ${QT_INCLUDE_DIR}
)
if( QT4BUILD )
  include( ${QT_USE_FILE} )
endif()

set( ${TARGET}_SRC main.cpp )
QT_ADD_RESOURCES( RESOURCES canvas.qrc )
add_definitions( -DMAKE_MARBLE_LIB )
add_executable( ${TARGET} ${${TARGET}_SRC} ${RESOURCES} )

if (QT4BUILD)
  target_link_libraries( ${TARGET} ${QT_QTCORE_LIBRARY} ${QT_QTMAIN_LIBRARY} marblewidget )
else()
  target_link_libraries( ${TARGET} ${Qt5Core_LIBRARIES} marblewidget-qt5 )
endif()
