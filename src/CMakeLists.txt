
configure_file( AlbumGenConfig.h.in AlbumGenConfig.h )
find_package( wxWidgets COMPONENTS core base xml REQUIRED )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )

include( "${wxWidgets_USE_FILE}" )

include_directories(  ${AlbumGen_Source_Directory} 
${AlbumGen_GuiFiles_Source_Directory}
${AlbumGen_UtilsFiles_Source_Directory}
${AlbumGen_ODTFiles_Source_Directory}
${AlbumGen_AlbumFiles_Source_Directory}
${AlbumGen_CatalogFiles_Source_Directory} ${WXWIN} )

add_subdirectory (utils)
add_subdirectory (gui)
add_subdirectory (catalog)
add_subdirectory (album)
add_subdirectory (odt)

add_executable (AlbumGenerator 
    AlbumGenApp.cpp
    Defs.cpp
    Node.cpp 
)

#link_directories( /sandbox/Applications/TinyXML2/build )

target_link_libraries (AlbumGenerator LINK_PUBLIC 
    Utils
    GuiFiles  
    AlbumFiles
    CatalogFiles  
    ODTFiles
    curl
    ${wxWidgets_LIBRARIES}
    )
