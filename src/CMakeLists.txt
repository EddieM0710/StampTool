
configure_file( StampToolConfig.h.in StampToolConfig.h )


find_package( wxWidgets COMPONENTS core base xml net pdfdoc webview stc ribbon REQUIRED )


find_package(CURL REQUIRED) 
include_directories(${CURL_INCLUDE_DIR})

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )

include( "${wxWidgets_USE_FILE}" )

include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} 
/sandbox/Applications/wxWidgets-3.2.2.1/
${WXWIN} )
 
 message( "------- wxWidgets_LIBRARIES ${INCLUDE_DIRECTORIES}")
add_subdirectory (utils)
add_subdirectory (gui)
add_subdirectory (catalog)
add_subdirectory (design)

add_executable ( StampTool 
    StampToolApp.cpp
    Defs.cpp
)

target_link_libraries (StampTool LINK_PUBLIC debug
     GuiFiles  
    DesignFiles
    CatalogFiles  
    Utils
    ${CURL_LIBRARIES}
    ${wxWidgets_LIBRARIES}
    )

    