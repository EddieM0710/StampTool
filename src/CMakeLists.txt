
configure_file( StampToolConfig.h.in StampToolConfig.h )


find_package( wxWidgets COMPONENTS core base xml net  REQUIRED )


set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )

include( "${wxWidgets_USE_FILE}" )
message( "wxWidgets_USE_FILE ${wxWidgets_USE_FILE}")

include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} 
${StampTool_MountFiles_Source_Directory} 
${StampTool_CollectionFiles_Source_Directory} 
${StampTool_TOCFiles_Source_Directory} 
"/usr/local/include"
)
 
add_subdirectory (utils)
add_subdirectory (gui)
add_subdirectory (catalog)
add_subdirectory (design)
add_subdirectory (collection)
add_subdirectory (toc)
add_subdirectory (thirdparty)

add_executable ( StampTool 
    StampToolApp.cpp
    Defs.cpp
)
message ("test-")
message ("${wxWidgets_LIBRARIES}")

target_link_libraries (StampTool LINK_PUBLIC debug
     GuiFiles  
     DesignFiles
     CatalogFiles  
     CollectionFiles  
     TOCFiles
     Utils
     wxPdfDoc
    ${wxWidgets_LIBRARIES}
    )

    
