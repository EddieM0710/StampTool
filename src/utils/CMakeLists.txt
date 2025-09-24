message ( "------Configuring Utils------" )

file(GLOB UTIL_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(UtilityFiles OBJECT ${UTIL_SOURCES})

# inherit wx include dirs/defs/libs
target_link_libraries(UtilityFiles PUBLIC project_wx stamp_includes project_pdfdoc )
