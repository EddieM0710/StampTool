

include( "${wxWidgets_USE_FILE}")

include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_AlbumFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( CatalogFiles SHARED
CatalogCode.cpp
CatalogBase.cpp
CatalogSectionData.cpp
CatalogData.cpp
CatalogDefs.cpp
Classification.cpp 
Entry.cpp
Specimen.cpp
)


