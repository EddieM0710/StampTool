cmake_minimum_required( VERSION 3.10 )

# set(CMAKE_VERBOSE_MAKEFILE ON)

# set the project name
project( AlbumGen VERSION 1.0 )

# specify the C++ standard
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( build_Directory "${CMAKE_CURRENT_SOURCE_DIR}/build" )
set( src_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src" )
set( AlbumGen_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src"  )
set( AlbumGen_ODTFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/odt"  )
set( AlbumGen_DesignFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/design"  )
set( AlbumGen_CatalogFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/catalog"  )
set( AlbumGen_GuiFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/gui"  )
set( AlbumGen_UtilsFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/utils"  )

set( WXWIN /sandbox/Applications/wxWidgets-3.2.0/gtk-build/lib )
include_directories( ${AlbumGen_Source_Directory} 
            ${AlbumGen_GuiFiles_Source_Directory} 
            ${AlbumGen_UtilsFiles_Source_Directory}
            ${AlbumGen_ODTFiles_Source_Directory}
            ${AlbumGen_DesignFiles_Source_Directory}
            ${AlbumGen_CatalogFiles_Source_Directory} ${WXWIN})

add_subdirectory (src)

