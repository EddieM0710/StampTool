
include( "${wxWidgets_USE_FILE}")

include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( GuiFiles SHARED
    StampToolFrame.cpp
    AppData.cpp
    StampToolPanel.cpp
    AlbumPanel.cpp 
    AlbumTreePanel.cpp 
    AlbumDetailsDialog.cpp
    AlbumImagePanel.cpp 
    CatalogPanel.cpp 
    CatalogTreeCtrl.cpp
    CharacteristicsPanel.cpp 
    ColDetailsDialog.cpp 
    DefinePeriodsPanel.cpp
    AlbumTreeCtrl.cpp 
    FileCreateDialog.cpp
    GenerateList.cpp
    GenerateListSettings.cpp
    GuiUtils.cpp
    IconDefs.cpp
    IdentificationPanel.cpp
    ImagePanel.cpp
    InventoryPanel.cpp
    LabeledTextBox.cpp
    NewStampDialog.cpp 
    PageDetailsDialog.cpp
    RemoveVolumeDialog.cpp    
    RowDetailsDialog.cpp 
    SettingsDialog.cpp
    SortOrderPanel.cpp
    StampDescriptionPanel.cpp 
    StampDetailsDialog.cpp
)


