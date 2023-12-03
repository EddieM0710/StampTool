

include( "${wxWidgets_USE_FILE}")

#include_directories(  ${StampTool_Source_Directory} 
#${StampTool_GuiFiles_Source_Directory}
#${StampTool_UtilsFiles_Source_Directory}
#${StampTool_DesignFiles_Source_Directory}
#${StampTool_CatalogFiles_Source_Directory} )

message(" --- wxPdfDoc_Source  ${wxPdfDoc_Source}")
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_Directory} )
add_library( wxPdfDoc SHARED
    ${wxPdfDoc_Source}/pdfannotation.cpp  
    ${wxPdfDoc_Source}/pdfbarcode.cpp  
    ${wxPdfDoc_Source}/pdfcffdecoder.cpp  
    ${wxPdfDoc_Source}/pdfcffindex.cpp  
    ${wxPdfDoc_Source}/pdfcolour.cpp  
    ${wxPdfDoc_Source}/pdfdc.cpp  
    ${wxPdfDoc_Source}/pdfdecode.cpp  
    ${wxPdfDoc_Source}/pdfdocument.cpp  
    ${wxPdfDoc_Source}/pdfencoding.cpp  
    ${wxPdfDoc_Source}/pdfencrypt.cpp  
    ${wxPdfDoc_Source}/pdffont.cpp  
    ${wxPdfDoc_Source}/pdffontdata.cpp  
    ${wxPdfDoc_Source}/pdffontdatacore.cpp  
    ${wxPdfDoc_Source}/pdffontdataopentype.cpp  
    ${wxPdfDoc_Source}/pdffontdatatruetype.cpp  
    ${wxPdfDoc_Source}/pdffontdatatype0.cpp  
    ${wxPdfDoc_Source}/pdffontdatatype1.cpp  
    ${wxPdfDoc_Source}/pdffontdescription.cpp  
    ${wxPdfDoc_Source}/pdffontdetails.cpp  
    ${wxPdfDoc_Source}/pdffontextended.cpp  
    ${wxPdfDoc_Source}/pdffontmanager.cpp  
    ${wxPdfDoc_Source}/pdffontparser.cpp  
    ${wxPdfDoc_Source}/pdffontparsertruetype.cpp  
    ${wxPdfDoc_Source}/pdffontparsertype1.cpp  
    ${wxPdfDoc_Source}/pdffontsubsetcff.cpp  
    ${wxPdfDoc_Source}/pdffontsubsettruetype.cpp  
    ${wxPdfDoc_Source}/pdffontvolt.cpp  
    ${wxPdfDoc_Source}/pdfform.cpp  
    ${wxPdfDoc_Source}/pdfgradient.cpp  
    ${wxPdfDoc_Source}/pdfgraphics.cpp  
    ${wxPdfDoc_Source}/pdfimage.cpp  
    ${wxPdfDoc_Source}/pdfkernel.cpp  
    ${wxPdfDoc_Source}/pdflayer.cpp  
    ${wxPdfDoc_Source}/pdfobjects.cpp  
    ${wxPdfDoc_Source}/pdfocg.cpp  
    ${wxPdfDoc_Source}/pdfparser.cpp  
    ${wxPdfDoc_Source}/pdfpattern.cpp  
    ${wxPdfDoc_Source}/pdfprint.cpp  
    ${wxPdfDoc_Source}/pdfrijndael.cpp  
    ${wxPdfDoc_Source}/pdftemplate.cpp  
    ${wxPdfDoc_Source}/pdfutility.cpp  
    ${wxPdfDoc_Source}/pdfxml.cpp
    )
  
  

    

