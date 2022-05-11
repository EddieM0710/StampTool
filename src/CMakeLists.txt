
configure_file( AlbumGenConfig.h.in AlbumGenConfig.h )
find_package( wxWidgets COMPONENTS core base xml REQUIRED )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )

include( "${wxWidgets_USE_FILE}" )

include_directories( ${AlbumGen_Source_Directory} 
            ${AlbumGen_GuiFiles_Source_Directory}
            ${AlbumGen_DocFiles_Source_Directory}
            ${AlbumGen_LayoutFiles_Source_Directory} ${WXWIN})

add_subdirectory (GuiFiles)

add_executable (AlbumGenerator 
    AlbumGeneratorApp.cpp
    Defs.cpp
    Settings.cpp
    Classification.cpp 
    Stamp.cpp
    Specimen.cpp
    ManageCatalogData.cpp 
    CatalogCode.cpp
    CatalogData.cpp
    XMLUtilities.cpp
    CSV.cpp 
    MakeList.cpp 
    ArrayWrapper.cpp 
    ManageAECmdData.cpp 
)

#link_directories( /sandbox/Applications/TinyXML2/build )

target_link_libraries (AlbumGenerator LINK_PUBLIC 
    GuiFiles    
    curl
    ${wxWidgets_LIBRARIES}
    )
