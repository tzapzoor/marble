PROJECT( Pn2Plugin )

INCLUDE_DIRECTORIES(
 ${CMAKE_BINARY_DIR}/src/plugins/runner/pn2
 ${QT_INCLUDE_DIR}
)
if( QT4BUILD )
  INCLUDE(${QT_USE_FILE})
endif()

set( pn2_SRCS Pn2Plugin.cpp Pn2Runner.cpp )

marble_add_plugin( Pn2Plugin ${pn2_SRCS} )
