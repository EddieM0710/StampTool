cmake_minimum_required( VERSION 3.10 )

#set(CMAKE_VERBOSE_MAKEFILE ON)

# set the project name
project( AlbumGen VERSION 1.0 )

# specify the C++ standard
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( build_Directory "${CMAKE_CURRENT_SOURCE_DIR}/build" )
set( src_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src" )
set( AlbumGen_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src"  )
set( AlbumGen_DocFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/DocFiles"  )
set( AlbumGen_LayoutFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/LayoutFiles"  )
set( AlbumGen_GuiFiles_Source_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/GuiFiles"  )

set( WXWIN /sandbox/Applications/wxWidgets-3.1.4 )
include_directories( ${AlbumGen_Source_Directory} 
            ${AlbumGen_GuiFiles_Source_Directory}
            ${AlbumGen_DocFiles_Source_Directory}
            ${AlbumGen_LayoutFiles_Source_Directory} ${WXWIN})

add_subdirectory (src)

