
include( "${wxWidgets_USE_FILE}")

include_directories( $ ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_ODTFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( ODTFiles SHARED
    ODTDefs.cpp
    Content.cpp
    Manifest.cpp
    Meta.cpp 
    Mimetype.cpp
    Document.cpp
    Settings.cpp 
    Styles.cpp 
    AutoStylesProp.cpp 
    Template.cpp 
)


