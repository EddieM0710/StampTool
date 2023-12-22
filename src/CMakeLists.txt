
configure_file( StampToolConfig.h.in StampToolConfig.h )


set( wxWidgets_ROOT_DIR "$ENV{WXWIN}" )
set( wxWidgets_include "$ENV{WXWIN}/include" )
set( ENV{LD_LIBRARY_PATH} "/usr/local/lib" )
set( WXPDF_FONTPATH "$ENV{WXPDFDOC}/lib/fonts" )

find_library( myVar wx_gtk3u_core-3.2 )
message ( " --- ${myVar}")
find_package( wxWidgets COMPONENTS core base xml net  REQUIRED )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )

message( "wxWidgets_ROOT_DIR ${wxWidgets_ROOT_DIR}")
message( "wxWidgets_include ${wxWidgets_include}")

message( "LD_LIBRARY_PATH  $ENV{LD_LIBRARY_PATH}" )
message( "WXPDDOC $ENV{WXPDFDOC} ")
message( "WXPDF_FONTPATH ${WXPDF_FONTPATH} ")
message( "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}" )
message( "build_Directory ${build_Directory}" )
message( "src_Directory ${src_Directory}" )

find_package( wxWidgets COMPONENTS core base xml net REQUIRED )
message( "wxWidgets_LIBRARIES ${wxWidgets_LIBRARIES}")
message( "wxWidgets_USE_FILE ${wxWidgets_USE_FILE}")


include( "${wxWidgets_USE_FILE}" )

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
     wxPdfDoc
    ${wxWidgets_LIBRARIES}
    )

    
