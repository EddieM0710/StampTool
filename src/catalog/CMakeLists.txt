

include( "${wxWidgets_USE_FILE}")

include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( CatalogFiles SHARED
CatalogBase.cpp
CatalogCode.cpp
CatalogData.cpp
CatalogVolume.cpp
CatalogList.cpp
CatalogDefs.cpp
CatalogDetailsDialog.cpp
Entry.cpp
InventoryItem.cpp
StampMount.cpp 
MountCSV.cpp 
MergeList.cpp 
)


