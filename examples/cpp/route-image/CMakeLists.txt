SET (TARGET route-image)
PROJECT (${TARGET})

include_directories(
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 ${QT_INCLUDE_DIR}
)
if( QT4BUILD )
  include( ${QT_USE_FILE} )
endif()

set( ${TARGET}_SRC main.cpp)
add_executable( ${TARGET} ${${TARGET}_SRC} )

target_link_libraries( ${TARGET} ${MARBLEWIDGET} )
if (QT4BUILD)
  target_link_libraries( ${TARGET} ${QT_QTCORE_LIBRARY} ${QT_QTMAIN_LIBRARY} )
else()
  target_link_libraries( ${TARGET} ${Qt5Core_LIBRARIES} )
endif()

install( TARGETS ${TARGET} RUNTIME DESTINATION bin )
