message ( "------Configuring Catalog------" )

file(GLOB CATALOG_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(CatalogFiles OBJECT ${CATALOG_SOURCES})

# inherit wx include dirs/defs/libs
target_link_libraries(CatalogFiles PUBLIC project_wx stamp_includes project_pdfdoc )



