
configure_file( StampToolConfig.h.in StampToolConfig.h )

set( wxWidgets_ROOT_DIR "/sandbox/Applications/wx/wxWidgets-3.2.2.1" )
message (" $ENV{LD_LIBRARY_PATH}" )
#set( ENV{LD_LIBRARY_PATH} "/usr/local/lib:/sandbox/Applications/wx/wxpdfdoc-main/build-gtk" )
set( ENV{LD_LIBRARY_PATH} "/usr/local/lib" )
#set( ENV{WXPDF_FONTPATH} "/sandbox/Applications/wx/wxpdfdoc-main/lib/fonts" )
set( ENV{WXPDF_FONTPATH} "/sandbox/Applications/wx/wxpdfdoc-main/lib/fonts" )
message (" LD_LIBRARY_PATH  $ENV{LD_LIBRARY_PATH}" )
find_package( wxWidgets COMPONENTS core base xml net pdfdoc REQUIRED )

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


add_executable ( StampTool 
    StampToolApp.cpp
    Defs.cpp
)
message ("test-")

message ("---- wxWidgets_LIBRARIES ${wxWidgets_LIBRARIES}")

target_link_libraries (StampTool LINK_PUBLIC debug
     GuiFiles  
     DesignFiles
     CatalogFiles  
     CollectionFiles  
     TOCFiles
     Utils
    ${wxWidgets_LIBRARIES}
    )

    
