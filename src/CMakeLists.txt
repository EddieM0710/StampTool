
configure_file( AlbumGeneratorConfig.h.in AlbumGeneratorConfig.h )
find_package( wxWidgets COMPONENTS core base REQUIRED )


set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )

include( "${wxWidgets_USE_FILE}" )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}
/sandbox/Applications/TinyXML2 )

add_executable (AlbumGenerator 
    AlbumGeneratorApp.cpp
    AlbumGeneratorFrame.cpp
    AlbumGeneratorPanel.cpp
    SortOrderDialog.cpp
    LabeledTextBox.cpp
    CSV.cpp 
    Classification.cpp 
    Stamp.cpp
    Specimen.cpp
    CatalogCode.cpp
    CatalogData.cpp
    AECmdData.cpp
    StampTreeCtrl.cpp
    Persistent.cpp 
    Settings.cpp
    SettingsDialog.cpp
    Defs.cpp
    XMLUtilities.cpp
    DefinePeriodsDialog.cpp
    MakeList.cpp 
    AlbumGeneratorDialog.cpp 
    AlbumSplitterWindow.cpp 
    AlbumTreeCtrl.cpp 
    StaticItem.cpp 
    ArrayWrapper.cpp 
    ReadAlbumEasyFile.cpp 
    ManageCatalogData.cpp 
    ManageAECmdData.cpp 
)

#link_directories( /sandbox/Applications/TinyXML2/build )

target_link_libraries (AlbumGenerator LINK_PUBLIC 
/sandbox/Applications/TinyXML2/build/libtinyxml2d.so
    tinyxml2d
    curl
    ${wxWidgets_LIBRARIES}
    )
