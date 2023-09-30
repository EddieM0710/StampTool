
include( "${wxWidgets_USE_FILE}")

include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} 
${StampTool_TOCFiles_Source_Directory} 
${StampTool_CollectionFiles_Source_Directory} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( TOCFiles SHARED
TOCBase.cpp 
TOCDefs.cpp 
)