message ( "------Configuring Design------" )


file(GLOB DESIGN_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(DesignFiles OBJECT ${DESIGN_SOURCES})

# inherit wx include dirs/defs/libs
target_link_libraries(DesignFiles PUBLIC project_wx stamp_includes project_pdfdoc )

