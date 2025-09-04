message ( "Building GUI" )

include( "${wxWidgets_USE_FILE}")

message ( "Source_Directory: ${StampTool_Source_Directory}")
message ( "Design dir: ${StampTool_DesignFiles_Source_Directory}")
message ( "Catalog dir: ${StampTool_CatalogFiles_Source_Directory}")
message ( "Mount dir: ${StampTool_MountFiles_Source_Directory}")
message ( "Gui dir: ${StampTool_CatalogFiles_Source_Directory}")
message ( "Catalog dir: ${StampTool_UtilsFiles_Source_Directory}")
message ( "Catalog dir: ${StampTool_CollectionFiles_Source_Directory}")
message ( "TOCFiles dir: ${StampTool_TOCFiles_Source_Directory}")
message ( " " )

include_directories(  ${StampTool_Source_Directory} 
					${StampTool_GuiFiles_Source_Directory}
					${StampTool_UtilsFiles_Source_Directory}
					${StampTool_DesignFiles_Source_Directory}
					${StampTool_CatalogFiles_Source_Directory} 
					${StampTool_TOCFiles_Source_Directory} 
					${StampTool_CollectionFiles_Source_Directory} )

add_library( GuiFiles SHARED
    StampToolFrame.cpp
    AppData.cpp
    StampToolPanel.cpp
    ExportDialog.cpp 
    ExportPanel.cpp 
    AlbumPanel.cpp 
    AlbumTreePanel.cpp 
    AlbumDetailsPanel.cpp
    AlbumImagePanel.cpp 
    CatalogPanel.cpp 
    CatalogTreeCtrl.cpp
    CompareTreeCtrl.cpp
    CharacteristicsPanel.cpp 
    ColDetailsPanel.cpp
    DefinePeriodsPanel.cpp
    EditProjectDetails.cpp 
    AlbumTreeCtrl.cpp 
    FileCreateDialog.cpp
    FontDefaultsPanel.cpp
    GenerateList.cpp
    GenerateListSettings.cpp
    GuiUtils.cpp
    IconDefs.cpp
    IdentificationPanel.cpp
    ImagePanel.cpp
    ImageGalleryPanel.cpp
    InventoryPanel.cpp
    LabeledTextBox.cpp
    NewStampDialog.cpp 
    HelperPanel.cpp
    RemoveVolumeDialog.cpp    
    PreferencesDialog.cpp
    SortOrderPanel.cpp
    StampDescriptionPanel.cpp 
    StampDetailsPanel.cpp
    StampDefaultsPanel.cpp
    RowDetailsPanel.cpp
    FrameDefaultsPanel.cpp
    PageDetailsPanel.cpp
    PageDefaultsPanel.cpp
    TOCTreeCtrl.cpp
    AlbumTOCTreeCtrl.cpp
    CatalogTOCTreeCtrl.cpp
    CompEntry.cpp 
    ComparePanel.cpp 
)


