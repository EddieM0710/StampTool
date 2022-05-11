
configure_file( AlbumGeneratorConfig.h.in AlbumGeneratorConfig.h )
find_package( wxWidgets COMPONENTS core base xml REQUIRED )


set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )

include( "${wxWidgets_USE_FILE}" )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_executable (AlbumGenerator 
    AlbumGeneratorApp.cpp
    AlbumGeneratorFrame.cpp
    AlbumGeneratorPanel.cpp
    AlbumSplitterWindow.cpp 
    Defs.cpp
    Persistent.cpp 
    Settings.cpp
    SettingsDialog.cpp
    SortOrderDialog.cpp
    DefinePeriodsDialog.cpp
    LabeledTextBox.cpp
    StaticItem.cpp 
    Classification.cpp 
    Stamp.cpp
    Specimen.cpp
    ManageCatalogData.cpp 
    CatalogDataTreeCtrl.cpp
    CatalogCode.cpp
    CatalogData.cpp
    XMLUtilities.cpp
    CSV.cpp 
    MakeList.cpp 
    ArrayWrapper.cpp 
    ManageAECmdData.cpp 
    AlbumTreeCtrl.cpp 
)

#link_directories( /sandbox/Applications/TinyXML2/build )

target_link_libraries (AlbumGenerator LINK_PUBLIC 
    curl
    ${wxWidgets_LIBRARIES}
    )
