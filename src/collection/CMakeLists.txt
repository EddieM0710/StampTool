message ( "------Configuring Collection------" )

file(GLOB COLLECTION_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(CollectionFiles OBJECT ${COLLECTION_SOURCES})

# inherit wx include dirs/defs/libs
target_link_libraries(CollectionFiles PUBLIC project_wx stamp_includes project_pdfdoc )
