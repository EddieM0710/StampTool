
include( "${wxWidgets_USE_FILE}")

include_directories(  ${StampTool_Source_Directory} 
${StampTool_GuiFiles_Source_Directory}
${StampTool_UtilsFiles_Source_Directory}
${StampTool_ODTFiles_Source_Directory}
${StampTool_DesignFiles_Source_Directory}
${StampTool_CatalogFiles_Source_Directory} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( GuiFiles SHARED
    StampToolFrame.cpp
    StampToolPanel.cpp
    AlbumDesignPanel.cpp 
    SettingsDialog.cpp
    DesignTreeCtrl.cpp 
    AlbumDesignTreePanel.cpp 
    AlbumImagePanel.cpp 
    CatalogPanel.cpp 
    CatalogTreeCtrl.cpp
    CatalogCodePanel.cpp 
    CharacteristicsPanel.cpp 
    GuiUtils.cpp
    IdentificationPanel.cpp
    ImagePanel.cpp
    InventoryPanel.cpp
    MiscellaneousDataPanel.cpp
    SortOrderDialog.cpp
    DefinePeriodsDialog.cpp
    StampDescriptionPanel.cpp 
    IconDefs.cpp
    ToolData.cpp
    GenerateList.cpp
    GenerateListSettings.cpp
    LabeledTextBox.cpp
    StaticItem.cpp 
    StampDetailsDialog.cpp
    AlbumDetailsDialog.cpp
    PageDetailsDialog.cpp
    RowDetailsDialog.cpp 
    SectionDetailsDialog.cpp
    ColDetailsDialog.cpp 
    FileCreateDialog.cpp
    NewStampDialog.cpp 
)


