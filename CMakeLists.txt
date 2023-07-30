cmake_minimum_required( VERSION 3.10 )

set(CMAKE_VERBOSE_MAKEFILE ON)

# set the project name
project( StampTool VERSION 1.0 )

# specify the C++ standard
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( build_Directory "${CMAKE_CURRENT_SOURCE_DIR}/build" )
set( src_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src" )
set( StampTool_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src"  )
set( StampTool_DesignFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/design"  )
set( StampTool_CatalogFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/catalog"  )
set( StampTool_MountFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/mount" )
set( StampTool_GuiFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/gui" )
set( StampTool_UtilsFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/utils" )
set( StampTool_CollectionFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/collection" )

include_directories( ${StampTool_Source_Directory} 
            ${StampTool_GuiFiles_Source_Directory} 
            ${StampTool_UtilsFiles_Source_Directory}
            ${StampTool_DesignFiles_Source_Directory}
            ${StampTool_MountFiles_Source_Directory}
            ${StampTool_CatalogFiles_Source_Directory}
            ${StampTool_CollectionFiles_Source_Directory} )

add_subdirectory (src)

