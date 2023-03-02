
configure_file( StampToolConfig.h.in StampToolConfig.h )
find_package( wxWidgets COMPONENTS core base xml pdfdoc REQUIRED )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )

include( "${wxWidgets_USE_FILE}" )
message ( "-------${wxWidgets_INCLUDE_DIRS}")
message("-----CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory}")

message( "${wxWidgets_LIBRARIES} ")
message ( "-------wxWidgets_LIBRARIES ${wxWidgets_LIBRARIES}")
message ( "-------WXPDFDOC  ${WXPDFDOC}" )
include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} ${WXWIN} )

add_subdirectory (utils)
add_subdirectory (gui)
add_subdirectory (catalog)
add_subdirectory (design)

add_executable ( StampTool 
    StampToolApp.cpp
    Defs.cpp
)

target_link_libraries (StampTool LINK_PUBLIC 
     GuiFiles  
    DesignFiles
    CatalogFiles  
    Utils
    ${wxWidgets_LIBRARIES}
    )

    