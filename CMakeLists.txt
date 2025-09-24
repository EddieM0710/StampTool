cmake_minimum_required(VERSION 3.22 )

#set the project name
project( StampTool VERSION 1.0 LANGUAGES CXX)

# Print out the CMake version in use
message(STATUS "Configuring with CMake version ${CMAKE_VERSION}")

# specify the C++ standard
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set( src_Directory "${CMAKE_CURRENT_SOURCE_DIR}/src" )

option(STAMPTOOL_BUILD_SHARED "Build StampTool libs as DLLs" OFF)
if(STAMPTOOL_BUILD_SHARED)
  set(STAMP_LIBTYPE SHARED)
else()
  set(STAMP_LIBTYPE STATIC)
endif()

# project relative directories
set( StampTool_Source_Directory "${src_Directory}" )
set( StampTool_DesignFiles_Source_Directory "${src_Directory}/design"  )
set( StampTool_CatalogFiles_Source_Directory "${src_Directory}/catalog"  )
set( StampTool_MountFiles_Source_Directory "${src_Directory}/mount" )
set( StampTool_GuiFiles_Source_Directory "${src_Directory}/gui" )
set( StampTool_UtilsFiles_Source_Directory "${src_Directory}/utils" )
set( StampTool_CollectionFiles_Source_Directory "${src_Directory}/collection" )
set( StampTool_TOCFiles_Source_Directory "${src_Directory}/toc" )

set( WXPDF_FONTPATH "C:/mingw64/local-wx-debug-winlibs/lib/fonts" )

#set( wxWidgets_ROOT_DIR "C:/mingw64/local-wx-debug-winlibs" )

set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3 -ggdb -fno-omit-frame-pointer" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_DEBUG     "-O0 -g3 -ggdb -fno-omit-frame-pointer" CACHE STRING "" FORCE)
# Safety: never strip in Debug
set(CMAKE_EXE_LINKER_FLAGS_DEBUG    "" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "" CACHE STRING "" FORCE)

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
find_package(wxWidgets CONFIG REQUIRED COMPONENTS base core xml)
find_package(wxpdfdoc CONFIG REQUIRED)

get_target_property(_wx_core_incs wx::core INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "---wx::core include dirs = ${_wx_core_incs}")

# centralize project include dirs 
add_library(stamp_includes INTERFACE)
target_include_directories(stamp_includes INTERFACE
  ${StampTool_Source_Directory}
  ${StampTool_GuiFiles_Source_Directory}
  ${StampTool_UtilsFiles_Source_Directory}
  ${StampTool_DesignFiles_Source_Directory}
  ${StampTool_CatalogFiles_Source_Directory}
  ${StampTool_TOCFiles_Source_Directory}
  ${StampTool_CollectionFiles_Source_Directory}
)
add_library(project_wx INTERFACE)
target_link_libraries(project_wx INTERFACE wx::base wx::core wx::xml)

add_library(project_pdfdoc INTERFACE)
target_link_libraries(project_pdfdoc INTERFACE wxpdfdoc::wxpdfdoc)

add_subdirectory (src)

#Add install() Rules
install(TARGETS StampTool DESTINATION bin)
#install(DIRECTORY assets/ DESTINATION share/stamptool/assets) # if you use any resources

# Add CPack for Packaging
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "TGZ;DEB")
set(CPACK_PACKAGE_NAME "StampTool")
set(CPACK_PACKAGE_VERSION "1.0")
include(CPack)
