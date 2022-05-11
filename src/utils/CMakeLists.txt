
find_package( wxWidgets COMPONENTS core base REQUIRED )
include( "${wxWidgets_USE_FILE}")

include_directories(  ${AlbumGen_Source_Directory} 
${AlbumGen_GuiFiles_Source_Directory}
${AlbumGen_UtilsFiles_Source_Directory}
${AlbumGen_ODTFiles_Source_Directory}
${AlbumGen_AlbumFiles_Source_Directory}
${AlbumGen_CatalogFiles_Source_Directory} ${WXWIN} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( Utils SHARED
    CSV.cpp
    Project.cpp
    Settings.cpp 
    XMLUtilities.cpp 
)


