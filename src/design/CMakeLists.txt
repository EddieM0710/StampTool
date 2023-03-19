
include( "${wxWidgets_USE_FILE}")

include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( DesignFiles SHARED
    DesignData.cpp 
    DesignDefs.cpp 
    XMLBase.cpp
    AlbumBase.cpp
    LayoutBase.cpp
    Album.cpp 
    Page.cpp 
    Title.cpp 
    TitlePage.cpp
    Row.cpp 
    Column.cpp 
    Stamp.cpp
    Frame.cpp
)


