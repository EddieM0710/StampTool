
find_package( wxWidgets COMPONENTS core base REQUIRED )
include( "${wxWidgets_USE_FILE}")

include_directories( ${AlbumGen_Source_Directory} 
            ${AlbumGen_GuiFiles_Source_Directory}
            ${AlbumGen_DocFiles_Source_Directory}
            ${AlbumGen_LayoutFiles_Source_Directory} ${WXWIN} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( GuiFiles SHARED
    AlbumGeneratorFrame.cpp
    AlbumGeneratorPanel.cpp
    AlbumSplitterWindow.cpp 
    SettingsDialog.cpp
    SortOrderDialog.cpp
    DefinePeriodsDialog.cpp
    LabeledTextBox.cpp
    StaticItem.cpp 
    AlbumTreeCtrl.cpp 
    CatalogDataTreeCtrl.cpp
)


