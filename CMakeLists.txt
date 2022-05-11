cmake_minimum_required( VERSION 3.10 )

#set(CMAKE_VERBOSE_MAKEFILE ON)

# set the project name
project( StampManager VERSION 1.0 )

# specify the C++ standard
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( build_Directory "${CMAKE_CURRENT_SOURCE_DIR}/build" )
set( GUI_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/gui" )
set( Data_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src/data" )
set( src_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src" )

set( WXWIN /sandbox/Applications/wxWidgets-3.1.4 )
include_directories(   ${GUI_Directory}  ${Data_Directory}  )

add_subdirectory (src)

