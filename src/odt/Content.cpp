#include "odt/Content.h"
#include "utils/Project.h"
#include "utils/Settings.h"
#include "utils/XMLUtilities.h"
#include <iostream>
#include "Defs.h"
#include "odt/ODTDefs.h"
#include "odt/Document.h"

#include "AutoStylesProp.h"
//***********************************

namespace ODT {

    Content::Content( )
    {
        m_content = new wxXmlDocument( );

        wxString configDir = GetProject()->GetSettings()->GetConfigurationDirectory();
        //GetDocManager( )->GetConfigDirectory( );
        wxString contentTemplate = configDir + "/template/content.xml";
        if ( !m_content->Load( contentTemplate ) )
        {
            // debug message
            ReportError( "Content::GetContent", "get Content failed", true );
        }

    }

    wxXmlNode* Content::FindOfficeBody( )
    {
        wxXmlNode* root = FindOfficeContentRoot( );
        if ( !root )
        {
            // No root!
            ReportError( "Content::FindOfficeBody", "No content root found.", true );
            return ( wxXmlNode* )0;
        }

        wxXmlNode* officeBody = Utils::FirstChildElement( root, "office:body" );
        if ( !officeBody )
        {
            // No Body!
            ReportError( "Content::FindOfficeBody", "No office:body found.", true );
            return ( wxXmlNode* )0;
        }
        return officeBody;
    }


    wxXmlNode* Content::FindOfficeContentRoot( )
    {
        if ( !m_content )
        {
            // Content doc not initialized
            ReportError( "Content::FindOfficeContentRoot", "Content doc not initialized", true );
            return ( wxXmlNode* )0;
        }

        wxXmlNode* root = m_content->GetRoot( );
        if ( !root )
        {
            // Content doc not initialized
            ReportError( "Content::FindOfficeContentRoot", "root not found", true );
            return ( wxXmlNode* )0;
        }
        return root;
    }

    wxXmlNode* Content::FindOfficAutomaticStyles( )
    {

        wxXmlNode* root = FindOfficeContentRoot( );

        wxXmlNode* automaticStyles = Utils::FirstChildElement( root, "office:automatic-styles" );
        if ( !automaticStyles )
        {
            // No Body!
            ReportError( "Content::FindOfficAutomaticStyles", "No office:automatic-styles found.", true );
            return ( wxXmlNode* )0;
        }
        return automaticStyles;
    }
    //***********************************
    bool Content::AddPageFrameStyles( )
    {
        AutoStylesProp* styles = new AutoStylesProp( );
        styles->DefinePrimaryTextStyles( );
        styles->WriteAll( );


        wxXmlNode* automaticStyles = FindOfficAutomaticStyles( );
        // // normal paragraph
        // wxXmlNode* P1 = AddNewNode( automaticStyles, wxXML_ELEMENT_NODE,  "style:style" );
        // SetAttribute( P1, "style:name", NormalTextStyle );
        // SetAttribute( P1, "style:family", "paragraph" );
        // SetAttribute( P1, "style:parent-style-name", "Standard" );
        // wxXmlNode* paragraphProperties = AddNewNode( P1, wxXML_ELEMENT_NODE, "style:paragraph-properties" );
        // paragraphProperties->SetAttribute( "fo:break-before", "page" );


        // //text hold 18pt
        // wxXmlNode* P2 = AddNewNode( automaticStyles, wxXML_ELEMENT_NODE,  "style:style" );
        // SetAttribute( P2, "style:name", Bold18PtTextStyle );
        // SetAttribute( P2, "style:family", "paragraph" );
        // SetAttribute( P2, "style:parent-style-name", Frame20Content );
        // wxXmlNode* paragraphProperties2 =  AddNewNode( P2, wxXML_ELEMENT_NODE,  "style:paragraph-properties" );
        // SetAttribute( paragraphProperties2, "fo:text-align", "center" );
        // SetAttribute( paragraphProperties2, "style:justify-single-word", "false" );
        // wxXmlNode* styleTextProperties2 =  AddNewNode( P2, wxXML_ELEMENT_NODE, "style:text-properties" );
        // SetAttribute( styleTextProperties2, "fo:font-size", "18pt" );
        // SetAttribute( styleTextProperties2, "fo:font-weight", "bold" ); 
        // SetAttribute( styleTextProperties2, "style:font-size-asian", "18pt"  );
        // SetAttribute( styleTextProperties2, "style:font-weight-asian", "bold" ); 
        // SetAttribute( styleTextProperties2, "style:font-size-complex", "18pt" ); 
        // SetAttribute( styleTextProperties2, "style:font-weight-complex", "bold" );



        // //text normal 8pt
        // P2 = AddNewNode( automaticStyles, wxXML_ELEMENT_NODE,  "style:style" );
        // SetAttribute( P2, "style:name", Normal8PtTextStyle );
        // SetAttribute( P2, "style:family", "paragraph" );
        // SetAttribute( P2, "style:parent-style-name", Frame20Content );
        //  paragraphProperties2 =  AddNewNode( P2, wxXML_ELEMENT_NODE,  "style:paragraph-properties" );
        // SetAttribute( paragraphProperties2, "fo:text-align", "center" );
        // SetAttribute( paragraphProperties2, "style:justify-single-word", "false" );
        // styleTextProperties2 =  AddNewNode( P2, wxXML_ELEMENT_NODE, "style:text-properties" );
        // SetAttribute( styleTextProperties2, "fo:font-size", "8pt" );
        // SetAttribute( styleTextProperties2, "style:font-size-asian", "8pt"  );
        // SetAttribute( styleTextProperties2, "style:font-size-complex", "8pt" ); 



        //fr1 is for frame with border
        wxXmlNode* fr1 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttribute( fr1, "style:name", FrameWithBorder );
        Utils::SetAttribute( fr1, "style:family", "graphic" );
        Utils::SetAttribute( fr1, "style:parent-style-name", "Frame" );
        wxXmlNode* graphicProperties = Utils::AddNewNode( fr1, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        Utils::SetAttribute( graphicProperties, "style:vertical-pos", "from-top" );
        Utils::SetAttribute( graphicProperties, "style:vertical-rel", "paragraph-content" );
        Utils::SetAttribute( graphicProperties, "style:horizontal-pos", "from-left" );
        Utils::SetAttribute( graphicProperties, "style:horizontal-rel", "paragraph-content" );
        Utils::SetAttribute( graphicProperties, "fo:padding", ".06in" );
        Utils::SetAttribute( graphicProperties, "fo:border", "0.0071in dashed #000000" );
        Utils::SetAttribute( graphicProperties, "style:shadow", "none" );

        //fr2 is no border
        wxXmlNode* fr2 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttribute( fr2, "style:name", FrameNoBorder );
        Utils::SetAttribute( fr2, "style:family", "graphic" );
        Utils::SetAttribute( fr2, "style:parent-style-name", "Frame" );
        wxXmlNode* graphicProperties2 = Utils::AddNewNode( fr2, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        Utils::SetAttribute( graphicProperties2, "style:vertical-pos", "from-top" );
        Utils::SetAttribute( graphicProperties2, "style:vertical-rel", "paragraph-content" );
        Utils::SetAttribute( graphicProperties2, "style:horizontal-pos", "from-left" );
        Utils::SetAttribute( graphicProperties2, "style:horizontal-rel", "paragraph-conten" );
        Utils::SetAttribute( graphicProperties2, "fo:padding", "0in" );
        Utils::SetAttribute( graphicProperties2, "fo:border", "none" );
        Utils::SetAttribute( graphicProperties2, "style:shadow", "none" );



        wxXmlNode* fr3 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttribute( fr3, "style:name", FrameWithImage );
        Utils::SetAttribute( fr3, "style:family", "graphic" );
        Utils::SetAttribute( fr3, "style:parent-style-name", "Graphics" );
        wxXmlNode* graphicProperties3 = Utils::AddNewNode( fr3, wxXML_ELEMENT_NODE, "style:graphic-properties" );

        Utils::SetAttribute( graphicProperties3, "style:vertical-pos", "center" );
        Utils::SetAttribute( graphicProperties3, "style:vertical-rel", "paragraph-content" );
        Utils::SetAttribute( graphicProperties3, "style:horizontal-pos", "center" );
        Utils::SetAttribute( graphicProperties3, "style:horizontal-rel", "paragraph-content" );
        // SetAttribute( graphicProperties3, "fo:background-color", "transparent" ); 
        // SetAttribute( graphicProperties3, "style:background-transparency", "100%" );
        // SetAttribute( graphicProperties3, "style:shadow", "none"  );
        Utils::SetAttribute( graphicProperties3, "style:mirror", "none" );
        Utils::SetAttribute( graphicProperties3, "fo:clip", "rect(0in, 0in, 0in, 0in)" );
        Utils::SetAttribute( graphicProperties3, "draw:luminance", "0%" );
        Utils::SetAttribute( graphicProperties3, "draw:contrast", "0%" );
        Utils::SetAttribute( graphicProperties3, "draw:red", "0%" );
        Utils::SetAttribute( graphicProperties3, "draw:green", "0%" );
        Utils::SetAttribute( graphicProperties3, "draw:blue", "0%" );
        Utils::SetAttribute( graphicProperties3, "draw:gamma", "100%" );
        Utils::SetAttribute( graphicProperties3, "draw:color-inversion", "false" );
        Utils::SetAttribute( graphicProperties3, "draw:image-opacity", "100%" );
        Utils::SetAttribute( graphicProperties3, "draw:color-mode", "standard" );


        //fr2 is centered at top with no border
        wxXmlNode* fr4 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttribute( fr4, "style:name", FrameCenteredAtTopNoBorder );
        Utils::SetAttribute( fr4, "style:family", "graphic" );
        Utils::SetAttribute( fr4, "style:parent-style-name", "Frame" );
        wxXmlNode* graphicProperties4 = Utils::AddNewNode( fr4, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        Utils::SetAttribute( graphicProperties4, "style:vertical-pos", "top" );
        Utils::SetAttribute( graphicProperties4, "style:vertical-rel", "paragraph-content" );
        Utils::SetAttribute( graphicProperties4, "style:horizontal-pos", "center" );
        Utils::SetAttribute( graphicProperties4, "style:horizontal-rel", "paragraph-conten" );
        Utils::SetAttribute( graphicProperties4, "fo:padding", "0in" );
        Utils::SetAttribute( graphicProperties4, "fo:border", "none" );
        Utils::SetAttribute( graphicProperties4, "style:shadow", "none" );

        wxXmlNode* fr5 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttribute( fr5, "style:name", FrameCenteredFromTopNoBorder );
        Utils::SetAttribute( fr5, "style:family", "graphic" );
        Utils::SetAttribute( fr5, "style:parent-style-name", "Frame" );
        wxXmlNode* graphicProperties5 =  Utils::AddNewNode( fr5, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        Utils::SetAttribute( graphicProperties5, "style:vertical-pos", "from-top" );
        Utils::SetAttribute( graphicProperties5, "style:vertical-rel", "paragraph-content" );
        Utils::SetAttribute( graphicProperties5, "style:horizontal-pos", "center" );
        Utils::SetAttribute( graphicProperties5, "style:horizontal-rel", "paragraph-conten" );
        Utils::SetAttribute( graphicProperties5, "fo:padding", "0in" );
        Utils::SetAttribute( graphicProperties5, "fo:border", "none" );
        Utils::SetAttribute( graphicProperties5, "style:shadow", "none" );


    }
    wxXmlNode* Content::FindOfficeText( )
    {
        wxXmlNode* officeBody = FindOfficeBody( );
        wxXmlNode* officeText = Utils::FirstChildElement( officeBody, "office:text" );
        if ( !officeText )
        {
            // NoBody
            ReportError( "Document::FindOfficeText", "No office:text found;", true );
        }
        return officeText;
    }
    //***********************************
    //<office:text text:use-soft-page-breaks="true">
    //***********************************

    bool Content::EnableSoftPageBreak( )
    {

        wxXmlNode* officeText = FindOfficeText( );
        Utils::SetAttribute( officeText, "text:use-soft-page-breaks", "true" );
        return true;
    }



    wxXmlNode* Content::AddNewPage( )
    {
        EnableSoftPageBreak( );
        wxXmlNode* officeText = FindOfficeText( );
        wxXmlNode* textP = Utils::AddNewNode( officeText, wxXML_ELEMENT_NODE, "text:p" );
        Utils::SetAttribute( textP, "text:style-name", NormalTextStyle );
        //    <text:p text:style-name="P1">
        return textP;
    }

    wxXmlNode* Content::FindFirstPage( )
    {
        wxXmlNode* officeText = FindOfficeText( );
        wxXmlNode* textP = Utils::FirstChildElement( officeText, "text:p" );
        return textP;
    }

    wxXmlNode* Content::WriteFrame( wxXmlNode* parent, double xPos,
        double yPos,
        double width,
        double height,
        const char* drawStyleName,  // fr1
        const char* textAnchorType,  // "page", "paragraph"
        const char* textStyleName )
    {

        char str[ 20 ];
        wxXmlNode* drawFrame = Utils::AddNewNode( parent, wxXML_ELEMENT_NODE, "draw:frame" );
        Utils::SetAttribute( drawFrame, "draw:style-name", drawStyleName );
        Utils::SetAttribute( drawFrame, "draw:name", Utils::GetFrameName( str ) );
        Utils::SetAttribute( drawFrame, "text:anchor-type", textAnchorType );
        Utils::SetAttribute( drawFrame, "svg:x", Utils::DoubleToInchString( str, xPos ) );
        Utils::SetAttribute( drawFrame, "svg:y", Utils::DoubleToInchString( str, yPos ) );
        Utils::SetAttribute( drawFrame, "svg:width", Utils::DoubleToInchString( str, width ) );
        Utils::SetAttribute( drawFrame, "draw:z-index", Utils::GetZIndex( str ) );

        wxXmlNode* drawTextBox = Utils::AddNewNode( drawFrame, wxXML_ELEMENT_NODE, "draw:text-box" );
        Utils::SetAttribute(drawTextBox, "fo:min-height", Utils::DoubleToInchString( str, height ) );

        wxXmlNode* drawTextBoxP = Utils::AddNewNode( drawTextBox, wxXML_ELEMENT_NODE, "text:p" );
        Utils::SetAttribute( drawTextBoxP,"text:style-name", textStyleName );
        // return child element for content
        return drawTextBoxP;
    }


    wxXmlNode* Content::WriteFrameFixedSize( wxXmlNode* parent, double xPos,
        double yPos,
        double width,
        double height,
        const char* drawStyleName,  // fr1
        const char* textAnchorType,  // "page", "paragraph"
        const char* textStyleName )
    {

        char str[ 20 ];
        wxXmlNode* drawFrame = Utils::AddNewNode( parent, wxXML_ELEMENT_NODE, "draw:frame" );
        Utils::SetAttribute( drawFrame, "draw:style-name", drawStyleName );
        Utils::SetAttribute( drawFrame, "draw:name", Utils::GetFrameName( str ) );
        Utils::SetAttribute( drawFrame, "text:anchor-type", textAnchorType );
        Utils::SetAttribute( drawFrame, "svg:x", Utils::DoubleToInchString( str, xPos ) );
        Utils::SetAttribute( drawFrame, "svg:y", Utils::DoubleToInchString( str, yPos ) );
        Utils::SetAttribute( drawFrame, "svg:width", Utils::DoubleToInchString( str, width ) );
        Utils::SetAttribute( drawFrame, "svg:height", Utils::DoubleToInchString( str, height ) );
        Utils::SetAttribute( drawFrame, "draw:z-index", Utils::GetZIndex( str ) );

        wxXmlNode* drawTextBox = Utils::AddNewNode( drawFrame, wxXML_ELEMENT_NODE, "draw:text-box" );

        wxXmlNode* drawTextBoxP = Utils::AddNewNode( drawTextBox, wxXML_ELEMENT_NODE, "text:p" );
        Utils::SetAttribute( drawTextBoxP, "text:style-name", textStyleName );
        // return child element for content
        return drawTextBoxP;
    }
    //***********************************


    wxXmlNode* Content::WriteImage( wxXmlNode* parent, double xPos,
        double yPos,
        double width,
        double height,
        wxString& drawStyleName,  // fr1
        wxString& textAnchorType, // "page", "paragraph"
        wxString& textStyleName,   // "P1"
        wxString& link )
    {
        char str[ 20 ];
        wxXmlNode* imageFrame = Utils::AddNewNode( parent, wxXML_ELEMENT_NODE, "draw:frame" );
        Utils::SetAttribute( imageFrame, "draw:style-name", drawStyleName );
        Utils::SetAttribute( imageFrame, "draw:name", Utils::GetImageName( str ) );
        Utils::SetAttribute( imageFrame, "text:anchor-type", textAnchorType );
        //    SetAttribute( imageFrame, "svg:x", DoubleToInchString( str, xPos ) );
        //    SetAttribute( imageFrame, "svg:y", DoubleToInchString( str, yPos ) );
        Utils::SetAttribute( imageFrame, "svg:width", Utils::DoubleToInchString( str, width ) );
        Utils::SetAttribute( imageFrame, "svg:height", Utils::DoubleToInchString( str, height ) );
        Utils::SetAttribute( imageFrame, "draw:z-index", Utils::GetZIndex( str ) );

        if ( !link.IsEmpty( ) )
        {
            wxXmlNode* image = Utils::AddNewNode( imageFrame, wxXML_ELEMENT_NODE, "draw:image " );

            wxString fullPath = ODT::ODTDoc( )->AddImageFile( link );
            Utils::SetAttribute( image, "xlink:href", fullPath );
            Utils::SetAttribute( image, "xlink:type", "simple" );
            Utils::SetAttribute( image, "xlink:show", "embed" );
            Utils::SetAttribute( image, "xlink:actuate", "onLoad" );
            Utils::SetAttribute( image, "loext:mime-type", Utils::GetMimeType( link ) );
        }
        return imageFrame;
    }

    //***********************************
    wxXmlNode* Content::WriteTextBox( wxXmlNode* parent, double xPos,
        double yPos,
        double width,
        double height,
        wxString& drawStyleName,  // fr1
        wxString& textAnchorType, // "page", "paragraph"
        wxString& textStyleName,
        wxString point,
        wxString text )
    {

        wxXmlNode* stampFrame = ContentDoc( )->WriteFrameFixedSize( parent,
            xPos, yPos,
            width, height,
            drawStyleName, textAnchorType, textStyleName );
        stampFrame->SetContent( text );

    }



    bool Content::Save( )
    {
        std::cout << "*************************************************\n";

        wxString str = ODT::ODTDoc( )->MakeAbsolute( "content.xml" );
        // if ( !
        ::Save( m_content, str );
        // {
        //     ReportError( "Content::SaveFiles", "Failed to save content xml" ,true) ;
        // }
        //     return true;
    }
}