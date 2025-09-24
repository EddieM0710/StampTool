message ( "------Configuring GUI------" )

file(GLOB GUI_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(GuiFiles OBJECT ${GUI_SOURCES})

# inherit wx include dirs/defs/libs
target_link_libraries(GuiFiles PUBLIC project_wx stamp_includes project_pdfdoc )
