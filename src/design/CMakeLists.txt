message ( "Building Design" )


include( "${wxWidgets_USE_FILE}")

message ( "Source_Directory: ${StampTool_Source_Directory}")
message ( "Design dir: ${StampTool_DesignFiles_Source_Directory}")
message ( "Catalog dir: ${StampTool_CatalogFiles_Source_Directory}")
message ( "Mount dir: ${StampTool_MountFiles_Source_Directory}")
message ( "Gui dir: ${StampTool_CatalogFiles_Source_Directory}")
message ( "Catalog dir: ${StampTool_UtilsFiles_Source_Directory}")
message ( "Catalog dir: ${StampTool_CollectionFiles_Source_Directory}")
message ( "TOCFiles dir: ${StampTool_TOCFiles_Source_Directory}")
message ( " " )

include_directories(   ${StampTool_Source_Directory} 
					${StampTool_GuiFiles_Source_Directory}
					${StampTool_UtilsFiles_Source_Directory}
					${StampTool_DesignFiles_Source_Directory}
					${StampTool_CatalogFiles_Source_Directory} 
					${StampTool_TOCFiles_Source_Directory} 
					${StampTool_CollectionFiles_Source_Directory} )
					
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


