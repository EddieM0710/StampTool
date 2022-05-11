
find_package( wxWidgets COMPONENTS core base REQUIRED )
include( "${wxWidgets_USE_FILE}")

include_directories(  ${AlbumGen_Source_Directory} 
${AlbumGen_GuiFiles_Source_Directory}
${AlbumGen_UtilsFiles_Source_Directory}
${AlbumGen_ODTFiles_Source_Directory}
${AlbumGen_AlbumFiles_Source_Directory}
${AlbumGen_CatalogFiles_Source_Directory} ${WXWIN} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( GuiFiles SHARED
    AlbumGenFrame.cpp
    AlbumGenPanel.cpp
    AlbumSplitterWindow.cpp 
    SettingsDialog.cpp
    AlbumTreeCtrl.cpp 
    AlbumPanel.cpp 
    CatalogPanel.cpp 
    CatalogTreeCtrl.cpp
    SortOrderDialog.cpp
    DefinePeriodsDialog.cpp
    LabeledTextBox.cpp
    StaticItem.cpp 
)


