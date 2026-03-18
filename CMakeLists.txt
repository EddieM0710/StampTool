cmake_minimum_required(VERSION 3.22 )

#set the project name
project( StampTool VERSION 0.8 LANGUAGES CXX)

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
find_package(wxWidgets CONFIG 
REQUIRED COMPONENTS base core xml net )
find_package(wxpdfdoc CONFIG REQUIRED)

get_target_property(_wx_core_incs wx::core INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "---wx::core include dirs = ${_wx_core_incs}")


find_package(CAPI_Interface CONFIG QUIET)
if(NOT CAPI_Interface_FOUND)
    # Build it from source in this repo
    message(STATUS "******CAPI_Interface not found; building from source")
#    add_subdirectory(image-fetch)
else()
    message(STATUS  "******Using pre-built CAPI_Interface library")
endif()

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
target_link_libraries(project_wx INTERFACE wx::base wx::core wx::xml wx::net bcrypt)

add_library(project_pdfdoc INTERFACE)
target_link_libraries(project_pdfdoc INTERFACE wxpdfdoc::wxpdfdoc)

add_library(project_CAPI_Interface INTERFACE)
target_link_libraries(project_CAPI_Interface INTERFACE CAPI_Interface::CAPI_Interface)

if(CAPI_Interface_FOUND)
  get_target_property(_if_includes CAPI_Interface::CAPI_Interface INTERFACE_INCLUDE_DIRECTORIES)
  message(STATUS "CAPI_Interface INTERFACE_INCLUDE_DIRECTORIES = ${_if_includes}")

  target_link_libraries(stamp_includes INTERFACE project_CAPI_Interface)

endif()

message( "--- begin src build")

add_subdirectory (src)

message( "--- finished src build")

# Add install() Rules
# --- Install the app ----------------------------------------------------------
# install the executable into bin/
install(TARGETS StampTool RUNTIME DESTINATION bin)

if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
  install(DIRECTORY "${CMAKE_SOURCE_DIR}/assets/"
          DESTINATION "bin/assets")
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/sample")
  install(DIRECTORY "${CMAKE_SOURCE_DIR}/sample/"
          DESTINATION "sample")
endif()

# ... your DLL bundling install(CODE ...) block ...

# --- CPack / NSIS -------------------------------------------------
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME        "StampTool")
set(CPACK_PACKAGE_VENDOR      "StampTool Project")
set(CPACK_PACKAGE_VERSION     "${PROJECT_VERSION}")
set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_PACKAGE_DIRECTORY "${PROJECT_SOURCE_DIR}/dist")

set(CPACK_PACKAGE_EXECUTABLES "StampTool" "StampTool")
set(CPACK_GENERATOR "ZIP;NSIS")
set(CPACK_NSIS_DISPLAY_NAME "StampTool")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
set(CPACK_CREATE_DESKTOP_LINKS StampTool)

# Offer PATH modification
set(CPACK_NSIS_MODIFY_PATH ON)

# Copy contents of $INSTDIR\sample to $DOCUMENTS\StampTool
set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS
  "SetShellVarContext current\n\
  CreateDirectory \\\"$DOCUMENTS\\\\StampTool\\\"  \n\
  CopyFiles /SILENT \\\"$INSTDIR\\\\sample\\\\projects\\\" \\\"$DOCUMENTS\\\\StampTool\\\"\n\
  CopyFiles /SILENT \\\"$INSTDIR\\\\sample\\\\art\\\" \\\"$DOCUMENTS\\\\StampTool\\\""
)

include(CPack)