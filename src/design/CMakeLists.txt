
find_package( wxWidgets COMPONENTS core base xml REQUIRED )
include( "${wxWidgets_USE_FILE}")

include_directories(  ${AlbumGen_Source_Directory} 
${AlbumGen_GuiFiles_Source_Directory}
${AlbumGen_UtilsFiles_Source_Directory}
${AlbumGen_ODTFiles_Source_Directory}
${AlbumGen_DesignFiles_Source_Directory}
${AlbumGen_CatalogFiles_Source_Directory} ${WXWIN})

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( DesignFiles SHARED
    DesignData.cpp 
    DesignDefs.cpp 
    AlbumBase.cpp
    LayoutBase.cpp
    Album.cpp 
    Page.cpp 
    Font.cpp 
    Title.cpp 
    TitlePage.cpp
    Row.cpp 
    Column.cpp 
    Stamp.cpp
    Frame.cpp
)


