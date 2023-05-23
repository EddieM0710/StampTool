
include( "${wxWidgets_USE_FILE}")
message( "---wxWidgets ${wxWidgets_USE_FILE}" )
include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( Utils SHARED
    CSV.cpp
    DebugString.cpp
#    ImageZip.cpp
    ImageRepository.cpp
    Project.cpp
    Settings.cpp 
    StampList.cpp 
    Font.cpp
    FontList.cpp
    FontNdx.cpp
    XMLUtilities.cpp 
)


