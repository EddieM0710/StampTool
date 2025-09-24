message ( "------Configuring Mount------" )

file(GLOB MOUNT_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(MountFiles OBJECT ${MOUNT_SOURCES})

# inherit wx include dirs/defs/libs
target_link_libraries(MountFiles PUBLIC project_wx stamp_includes project_pdfdoc )
