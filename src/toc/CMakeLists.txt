message ( "Building TOC" )
message ( "Source_Directory: ${StampTool_Source_Directory}")
message ( "Design dir: ${StampTool_DesignFiles_Source_Directory}")
message ( "Catalog dir: ${StampTool_CatalogFiles_Source_Directory}")
message ( "Mount dir: ${StampTool_MountFiles_Source_Directory}")
message ( "Gui dir: ${StampTool_CatalogFiles_Source_Directory}")
message ( "Catalog dir: ${StampTool_UtilsFiles_Source_Directory}")
message ( "Catalog dir: ${StampTool_CollectionFiles_Source_Directory}")
message ( "TOCFiles dir: ${StampTool_TOCFiles_Source_Directory}")
message ( " " )

include( "${wxWidgets_USE_FILE}")

include_directories(  ${StampTool_Source_Directory} 
					${StampTool_GuiFiles_Source_Directory}
					${StampTool_UtilsFiles_Source_Directory}
					${StampTool_DesignFiles_Source_Directory}
					${StampTool_CatalogFiles_Source_Directory} 
					${StampTool_TOCFiles_Source_Directory} 
					${StampTool_CollectionFiles_Source_Directory} )

add_library( TOCFiles SHARED
			TOCBase.cpp 
			TOCDefs.cpp 
)
