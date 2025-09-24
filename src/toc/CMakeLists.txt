message ( "------Configuring TOC------" )

file(GLOB TOC_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(TOCFiles OBJECT ${TOC_SOURCES})

# inherit wx include dirs/defs/libs
target_link_libraries(TOCFiles PUBLIC project_wx stamp_includes project_pdfdoc )

