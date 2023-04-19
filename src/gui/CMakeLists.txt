
include( "${wxWidgets_USE_FILE}")

include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( GuiFiles SHARED
    StampToolFrame.cpp
    StampToolPanel.cpp
    AlbumDesignPanel.cpp 
    AlbumDesignTreePanel.cpp 
    AlbumDetailsDialog.cpp
    AlbumImagePanel.cpp 
    CatalogCodePanel.cpp 
    CatalogPanel.cpp 
    CatalogTreeCtrl.cpp
    CharacteristicsPanel.cpp 
    ColDetailsDialog.cpp 
    DefinePeriodsPanel.cpp
    DesignTreeCtrl.cpp 
    FileCreateDialog.cpp
    GenerateList.cpp
    GenerateListSettings.cpp
    GuiUtils.cpp
    IconDefs.cpp
    IdentificationPanel.cpp
    ImagePanel.cpp
    InventoryPanel.cpp
    LabeledTextBox.cpp
    MiscellaneousDataPanel.cpp
    NewStampDialog.cpp 
    PageDetailsDialog.cpp
    RowDetailsDialog.cpp 
    CatalogDetailsDialog.cpp
    SettingsDialog.cpp
    SortOrderPanel.cpp
    StampDescriptionPanel.cpp 
    StampDetailsDialog.cpp
    ToolData.cpp


)


