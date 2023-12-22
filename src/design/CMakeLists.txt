
include( "${wxWidgets_USE_FILE}")

include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )

add_library( DesignFiles SHARED
    AlbumVolume.cpp 
    AlbumList.cpp 
    DesignDefs.cpp 
    AlbumData.cpp 
    XMLBase.cpp
    AlbumBase.cpp
    LayoutBase.cpp
    Album.cpp 
    Page.cpp 
    Defaults.cpp 
    PageDefaults.cpp 
    FrameDefaults.cpp 
    StampDefaults.cpp 
    LabelFrame.cpp 
    TextBox.cpp
    TitleFrame.cpp
    Row.cpp 
    Column.cpp 
    Stamp.cpp
    Frame.cpp
)


