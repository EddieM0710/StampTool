

#include "odt/ODTDefs.h"
#include "odt/Document.h"
#include "odt/Mimetype.h"
#include "odt/Manifest.h"
#include "odt/Content.h"
#include "odt/Meta.h"
#include "odt/Settings.h"
#include "odt/Styles.h"
#include <iostream>

namespace ODT {

    wxString Frame20Content = "Frame_20_contents";
    wxString NormalTextStyle;
    wxString Bold18PtTextStyle;
    wxString Normal8PtTextStyle;
    wxString Normal10PtTextStyle;
    wxString FrameWithBorder = "fr1";
    wxString FrameNoBorder = "fr2";
    wxString FrameWithImage = "fr3";
    wxString FrameCenteredAtTopNoBorder = "fr4";
    wxString FrameCenteredFromTopNoBorder = "fr5";
    wxString TextAnchorParagraph = "paragraph";
    wxString TextAnchorPage = "page";

    const char* wxXmlNodeTypeString[ 14 ] = {
        "",
      "wxXML_ELEMENT_NODE",
      "wxXML_ATTRIBUTE_NODE",
      "wxXML_TEXT_NODE",
      "wxXML_CDATA_SECTION_NODE",
      "wxXML_ENTITY_REF_NODE",
      "wxXML_ENTITY_NODE",
      "wxXML_PI_NODE",
      "wxXML_COMMENT_NODE",
      "wxXML_DOCUMENT_NODE",
     "wxXML_DOCUMENT_TYPE_NODE",
      "wxXML_DOCUMENT_FRAG_NODE",
      "wxXML_NOTATION_NODE",
      "wxXML_HTML_DOCUMENT_NODE" };
      
    Document* ODTDoc(){ return GetProject()->GetODTDocument(); };
    void SetODTDocument( Document* doc ){ GetProject()->SetODTDocument( doc ); };

    wxXmlDocument* ContentXML( ) { return ODTDoc( )->ContentXML( ); };
    wxXmlDocument* SettingsXML( ) { return ODTDoc( )->SettingsXML( ); };
    wxXmlDocument* StylesXML( ) { return ODTDoc( )->StylesXML( ); };
    wxXmlDocument* ManifestXML( ) { return ODTDoc( )->ManifestXML( ); };
    wxXmlDocument* MetaXML( ) { return ODTDoc( )->MetaXML( ); };

    Content* ContentDoc( ) { return ODTDoc( )->ContentDoc( ); };
    Settings* SettingsDoc( ) { return ODTDoc( )->SettingsDoc( ); };
    Styles* StylesDoc( ) { return ODTDoc( )->StylesDoc( ); };
    Manifest* ManifestDoc( ) { return ODTDoc( )->ManifestDoc( ); };
    Meta* MetaDoc( ) { return ODTDoc( )->MetaDoc( ); };

}