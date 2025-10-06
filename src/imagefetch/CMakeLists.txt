message ( "------Configuring ImageFetch------" )

file(GLOB IMAGEFETCH_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(ImageFetchFiles OBJECT ${IMAGEFETCH_SOURCES})

# inherit wx include dirs/defs/libs
target_link_libraries(ImageFetchFiles PUBLIC project_wx stamp_includes project_pdfdoc )

