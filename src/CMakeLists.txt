configure_file( StampToolConfig.h.in StampToolConfig.h )

#target_include_directories(StampTool PRIVATE  ${StampTool_Source_Directory} 
#                ${StampTool_GuiFiles_Source_Directory}
#                ${StampTool_UtilsFiles_Source_Directory}
#                ${StampTool_DesignFiles_Source_Directory}
#                ${StampTool_CatalogFiles_Source_Directory} 
#                ${StampTool_CollectionFiles_Source_Directory} 
#                ${StampTool_TOCFiles_Source_Directory} 
#)
 
# build libraries
add_subdirectory (utils)
add_subdirectory (gui)
add_subdirectory (catalog)
add_subdirectory (design)
add_subdirectory (collection)
add_subdirectory (toc)

include_directories(  ${StampTool_Source_Directory} )

#build exe
add_executable(StampTool )
target_sources(StampTool PRIVATE StampToolApp.cpp Defs.cpp)

target_link_libraries (StampTool PRIVATE
#LINK_PUBLIC debug
     GuiFiles  
     DesignFiles
     CatalogFiles  
     CollectionFiles  
     TOCFiles
     Utils
     ${wxWidgets_LIBRARIES}
    )

    
