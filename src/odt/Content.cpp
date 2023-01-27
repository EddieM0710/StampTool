/* 
 * @file Content.cpp
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright ( c ) 2022
 * 
 * This file is part of StampTool.
 *
 * StampTool is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 * 
 */

#include <wx/sstream.h>

#include "utils/Project.h"
#include "utils/Settings.h"
#include "utils/XMLUtilities.h"
#include <iostream>
#include "Defs.h"
#include "odt/ODTDefs.h"
#include "odt/Document.h"

#include "AutoStylesProp.h"
#include "odt/Template.h"

//***********************************
namespace ODT { 

    Content::Content( )
    { 
        m_content = new wxXmlDocument( );
        wxStringInputStream textStream( ODT::ContentTemplate );

        //wxString configDir = GetSettings( )->GetConfigurationDirectory( );
        //GetDocManager( )->GetConfigDirectory( );
        //wxString contentTemplate = configDir + "/template/content.xml";
        if ( !m_content->Load( textStream ) )
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
    
    bool Content::AddPageBackgroundFrameStyles( wxString drawName )
    { 
        wxXmlNode* automaticStyles = FindOfficAutomaticStyles( );
       Utils::AddComment( automaticStyles, BackgroundFrame, "BackgroundFrame" );


        //fr1 BackgroundFrame
        wxXmlNode* fr1 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
            Utils::SetAttrStr( fr1, "style:name", BackgroundFrame );
            Utils::SetAttrStr( fr1, "style:family", "graphic" );
            Utils::SetAttrStr( fr1, "style:parent-style-name", "Frame" );
        wxXmlNode* graphicProperties1 = Utils::AddNewNode( fr1, wxXML_ELEMENT_NODE, "style:graphic-properties" );
            Utils::SetAttrStr( graphicProperties1, "style:wrap", "parallel" ); 
            Utils::SetAttrStr( graphicProperties1, "style:number-wrapped-paragraphs", "no-limit" ); 
            Utils::SetAttrStr( graphicProperties1, "style:vertical-pos", "from-top" );
            Utils::SetAttrStr( graphicProperties1, "style:vertical-rel", "paragraph-content" );
            Utils::SetAttrStr( graphicProperties1, "style:horizontal-pos", "from-left" );
            Utils::SetAttrStr( graphicProperties1, "style:horizontal-rel", "paragraph-content" );

        wxXmlNode* backgroundImageNode = StylesDoc( )->FindOfficeStylesDrawFillImage( drawName );
        char emptyString[ 12 ] = "";
        wxString link = backgroundImageNode->GetAttribute( "xlink:href" );


       Utils::AddComment( automaticStyles, FrameWithBackgroundImage, "FrameWithBackgroundImage" );
        wxXmlNode* fr2 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
            Utils::SetAttrStr( fr2, "style:name", FrameWithBackgroundImage );
            Utils::SetAttrStr( fr2, "style:family", "graphic" );
            Utils::SetAttrStr( fr2, "style:parent-style-name", "Frame" );

        wxXmlNode* graphicProperties2 = Utils::AddNewNode( fr2, wxXML_ELEMENT_NODE, "style:graphic-properties" );
            Utils::SetAttrStr( graphicProperties2, "style:wrap", "parallel" );
            Utils::SetAttrStr( graphicProperties2, "fo:margin-left", "0mm" ); 
            Utils::SetAttrStr( graphicProperties2, "fo:margin-right", "0mm" ); 
            Utils::SetAttrStr( graphicProperties2, "fo:margin-top", "0mm" ); 
            Utils::SetAttrStr( graphicProperties2, "fo:margin-bottom", "0mm" ); 
            Utils::SetAttrStr( graphicProperties2, "style:wrap", "run-through" ); 
            Utils::SetAttrStr( graphicProperties2, "style:number-wrapped-paragraphs", "no-limit"  );
            Utils::SetAttrStr( graphicProperties2, "style:vertical-pos", "from-top"  );
            Utils::SetAttrStr( graphicProperties2, "style:vertical-rel", "paragraph-content"  );
            Utils::SetAttrStr( graphicProperties2, "style:horizontal-pos", "from-left"  );
            Utils::SetAttrStr( graphicProperties2, "style:horizontal-rel", "paragraph-content"  );
            Utils::SetAttrStr( graphicProperties2, "draw:fill", "bitmap"  );
            Utils::SetAttrStr( graphicProperties2, "draw:fill-image-name", drawName  );
            Utils::SetAttrStr( graphicProperties2, "style:repeat", "stretch"  );
            Utils::SetAttrStr( graphicProperties2, "draw:fill-image-ref-point-x", "0%" ); 
            Utils::SetAttrStr( graphicProperties2, "draw:fill-image-ref-point-y", "0%" ); 
            Utils::SetAttrStr( graphicProperties2, "draw:fill-image-ref-point", "center" );
            Utils::SetAttrStr( graphicProperties2, "fo:padding", "0mm" ); 
            Utils::SetAttrStr( graphicProperties2, "fo:border", "none" ); 
            Utils::SetAttrStr( graphicProperties2, "draw:wrap-influence-on-position", "once-concurrent" ); 
            Utils::SetAttrStr( graphicProperties2, "loext:allow-overlap", "true" );
            //Utils::SetAttrStr( graphicProperties2, "loext:rel-width-rel", "paragraph"  );
            //Utils::SetAttrStr( graphicProperties2, "loext:rel-height-rel", "paragraph" );

        wxXmlNode* backgroundImage2 = Utils::AddNewNode( graphicProperties2, wxXML_ELEMENT_NODE, "style:background-image" );
                Utils::SetAttrStr( backgroundImage2, "xlink:href", link  );
                Utils::SetAttrStr( backgroundImage2, "xlink:type", "simple"  );
                Utils::SetAttrStr( backgroundImage2, "xlink:actuate", "onLoad"  );
                Utils::SetAttrStr( backgroundImage2, "style:repeat", "stretch" );
       return true;

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
        // SetAttrStr( P1, "style:name", NormalTextStyle );
        // SetAttrStr( P1, "style:family", "paragraph" );
        // SetAttrStr( P1, "style:parent-style-name", "Standard" );
        // wxXmlNode* paragraphProperties = AddNewNode( P1, wxXML_ELEMENT_NODE, "style:paragraph-properties" );
        // paragraphProperties->SetAttrStr( "fo:break-before", "page" );


        // //text hold 18pt
        // wxXmlNode* P2 = AddNewNode( automaticStyles, wxXML_ELEMENT_NODE,  "style:style" );
        // SetAttrStr( P2, "style:name", Bold18PtTextStyle );
        // SetAttrStr( P2, "style:family", "paragraph" );
        // SetAttrStr( P2, "style:parent-style-name", Frame20Content );
        // wxXmlNode* paragraphProperties2 =  AddNewNode( P2, wxXML_ELEMENT_NODE,  "style:paragraph-properties" );
        // SetAttrStr( paragraphProperties2, "fo:text-align", "center" );
        // SetAttrStr( paragraphProperties2, "style:justify-single-word", "false" );
        // wxXmlNode* styleTextProperties2 =  AddNewNode( P2, wxXML_ELEMENT_NODE, "style:text-properties" );
        // SetAttrStr( styleTextProperties2, "fo:font-size", "18pt" );
        // SetAttrStr( styleTextProperties2, "fo:font-weight", "bold" ); 
        // SetAttrStr( styleTextProperties2, "style:font-size-asian", "18pt"  );
        // SetAttrStr( styleTextProperties2, "style:font-weight-asian", "bold" ); 
        // SetAttrStr( styleTextProperties2, "style:font-size-complex", "18pt" ); 
        // SetAttrStr( styleTextProperties2, "style:font-weight-complex", "bold" );



        // //text normal 8pt
        // P2 = AddNewNode( automaticStyles, wxXML_ELEMENT_NODE,  "style:style" );
        // SetAttrStr( P2, "style:name", Normal8PtTextStyle );
        // SetAttrStr( P2, "style:family", "paragraph" );
        // SetAttrStr( P2, "style:parent-style-name", Frame20Content );
        //  paragraphProperties2 =  AddNewNode( P2, wxXML_ELEMENT_NODE,  "style:paragraph-properties" );
        // SetAttrStr( paragraphProperties2, "fo:text-align", "center" );
        // SetAttrStr( paragraphProperties2, "style:justify-single-word", "false" );
        // styleTextProperties2 =  AddNewNode( P2, wxXML_ELEMENT_NODE, "style:text-properties" );
        // SetAttrStr( styleTextProperties2, "fo:font-size", "8pt" );
        // SetAttrStr( styleTextProperties2, "style:font-size-asian", "8pt"  );
        // SetAttrStr( styleTextProperties2, "style:font-size-complex", "8pt" ); 

        // <style:style style:name = "fr2" style:family = "graphic" style:parent-style-name = "Frame">
        //     <style:graphic-properties style:wrap = "parallel" 
        //     style:number-wrapped-paragraphs = "no-limit" 
        //     style:vertical-pos = "from-top" 
        //     style:vertical-rel = "paragraph" 
        //     style:horizontal-pos = "from-left" 
        //     style:horizontal-rel = "paragraph"/>
        // </style:style>
        // <style:style style:name = "fr1" style:family = "graphic" style:parent-style-name = "Frame">
        //     <style:graphic-properties style:wrap = "parallel" style:number-wrapped-paragraphs = "no-limit" style:vertical-pos = "from-top" style:vertical-rel = "paragraph" style:horizontal-pos = "from-left" style:horizontal-rel = "paragraph" draw:fill = "bitmap" draw:fill-image-name = "box2" style:repeat = "stretch" draw:fill-image-ref-point-x = "0%" draw:fill-image-ref-point-y = "0%" draw:fill-image-ref-point = "center">
        //         <style:background-image xlink:href = "Pictures/1000000000000258000003584C04905AFB17BB5E.jpg" xlink:type = "simple" xlink:actuate = "onLoad" style:repeat = "stretch"/>
        //     </style:graphic-properties>
        // </style:style>

         
       Utils::AddComment( automaticStyles, FrameWithBorder, "FrameWithBorder" );

        //fr6 is for frame with border
        wxXmlNode* fr6 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttrStr( fr6, "style:name", FrameWithBorder );
        Utils::SetAttrStr( fr6, "style:family", "graphic" );
        Utils::SetAttrStr( fr6, "style:parent-style-name", "Frame" );
        wxXmlNode* graphicProperties6 = Utils::AddNewNode( fr6, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        Utils::SetAttrStr( graphicProperties6, "style:vertical-pos", "from-top" );
        Utils::SetAttrStr( graphicProperties6, "style:vertical-rel", "paragraph-content" );
        Utils::SetAttrStr( graphicProperties6, "style:horizontal-pos", "from-left" );
        Utils::SetAttrStr( graphicProperties6, "style:horizontal-rel", "paragraph-content" );
        //Utils::SetAttrStr( graphicProperties6, "draw:opacity", "0%" ); 
        Utils::SetAttrStr( graphicProperties6, "fo:padding", ".06in" );
        Utils::SetAttrStr( graphicProperties6, "fo:border", "0.0071in solid #000000" );
        Utils::SetAttrStr( graphicProperties6, "style:shadow", "none" );
        Utils::SetAttrStr( graphicProperties6, "draw:shadow-opacity", "100%" );

        // Utils::AddComment( automaticStyles, "fr3", "FrameWithImage" );

        // wxXmlNode* fr3 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
        // Utils::SetAttrStr( fr3, "style:name", FrameWithImage );
        // Utils::SetAttrStr( fr3, "style:family", "graphic" );
        // Utils::SetAttrStr( fr3, "style:parent-style-name", "Graphics" );
        // wxXmlNode* graphicProperties3 = Utils::AddNewNode( fr3, wxXML_ELEMENT_NODE, "style:graphic-properties" );

        // Utils::SetAttrStr( graphicProperties3, "style:vertical-pos", "from-top" );
        // Utils::SetAttrStr( graphicProperties3, "style:vertical-rel", "paragraph-content" );
        // Utils::SetAttrStr( graphicProperties3, "style:horizontal-pos", "from-left" );
        // Utils::SetAttrStr( graphicProperties3, "style:horizontal-rel", "paragraph-content" );
        // // SetAttrStr( graphicProperties3, "fo:background-color", "transparent" ); 
        // // SetAttrStr( graphicProperties3, "style:background-transparency", "100%" );
        // // SetAttrStr( graphicProperties3, "style:shadow", "none"  );
        // Utils::SetAttrStr( graphicProperties3, "style:mirror", "none" );
        // Utils::SetAttrStr( graphicProperties3, "fo:clip", "rect( 0in, 0in, 0in, 0in )" );
        // Utils::SetAttrStr( graphicProperties3, "draw:luminance", "0%" );
        // Utils::SetAttrStr( graphicProperties3, "draw:contrast", "0%" );
        // Utils::SetAttrStr( graphicProperties3, "draw:red", "0%" );
        // Utils::SetAttrStr( graphicProperties3, "draw:green", "0%" );
        // Utils::SetAttrStr( graphicProperties3, "draw:blue", "0%" );
        // Utils::SetAttrStr( graphicProperties3, "draw:gamma", "100%" );
        // Utils::SetAttrStr( graphicProperties3, "draw:color-inversion", "false" );
        // Utils::SetAttrStr( graphicProperties3, "draw:image-opacity", "100%" );
        // Utils::SetAttrStr( graphicProperties3, "draw:color-mode", "standard" );

        Utils::AddComment( automaticStyles, FrameCenteredAtTopNoBorder, "FrameCenteredAtTopNoBorder" );

        //fr4 is centered at top with no border
        wxXmlNode* fr4 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttrStr( fr4, "style:name", FrameCenteredAtTopNoBorder );
        Utils::SetAttrStr( fr4, "style:family", "graphic" );
        Utils::SetAttrStr( fr4, "style:parent-style-name", "Frame" );
        wxXmlNode* graphicProperties4 = Utils::AddNewNode( fr4, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        Utils::SetAttrStr( graphicProperties4, "style:vertical-pos", "top" );
        Utils::SetAttrStr( graphicProperties4, "style:vertical-rel", "paragraph-content" );
        Utils::SetAttrStr( graphicProperties4, "style:horizontal-pos", "center" );
        Utils::SetAttrStr( graphicProperties4, "style:horizontal-rel", "paragraph-content" );
        Utils::SetAttrStr( graphicProperties4, "fo:padding", "0in" );
        Utils::SetAttrStr( graphicProperties4, "fo:border", "none" );
        Utils::SetAttrStr( graphicProperties4, "style:shadow", "none" );
        Utils::SetAttrStr( graphicProperties4, "draw:shadow-opacity", "100%" );

        Utils::AddComment( automaticStyles, FrameNoBorder, "FrameNoBorder" );

        wxXmlNode* fr5 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttrStr( fr5, "style:name", FrameNoBorder );
        Utils::SetAttrStr( fr5, "style:family", "graphic" );
        Utils::SetAttrStr( fr5, "style:parent-style-name", "Frame" );
        wxXmlNode* graphicProperties5 =  Utils::AddNewNode( fr5, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        Utils::SetAttrStr( graphicProperties5, "style:vertical-pos", "from-top" );
        Utils::SetAttrStr( graphicProperties5, "style:vertical-rel", "paragraph-content" );
        Utils::SetAttrStr( graphicProperties5, "style:horizontal-pos", "from-left" );
        Utils::SetAttrStr( graphicProperties5, "style:horizontal-rel", "paragraph-content" );
        Utils::SetAttrStr( graphicProperties5, "fo:padding", "0in" );
        Utils::SetAttrStr( graphicProperties5, "fo:border", "none" );
        Utils::SetAttrStr( graphicProperties5, "style:shadow", "none" );

        // <style:style style:name = "fr2" style:family = "graphic" style:parent-style-name = "Frame">
        //     <style:graphic-properties 
        //     style:wrap = "parallel" 
        //     style:number-wrapped-paragraphs = "no-limit" 
        //     style:vertical-pos = "from-top" 
        //     style:vertical-rel = "paragraph-content" 
        //     style:horizontal-pos = "from-left" 
        //     style:horizontal-rel = "paragraph-content" 
        //     draw:fill = "bitmap" 
        //     draw:fill-image-name = "box2" 
        //     style:repeat = "stretch" 
        //     draw:fill-image-ref-point-x = "0%" 
        //     draw:fill-image-ref-point-y = "0%" 
        //     draw:fill-image-ref-point = "center" 
        //     loext:rel-width-rel = "paragraph" 
        //     loext:rel-height-rel = "paragraph">
        //  <style:background-image xlink:href = "Pictures/1000000000000258000003584C04905AFB17BB5E.jpg" 
        //         xlink:type = "simple" 
        //         xlink:actuate = "onLoad" 
        //         style:repeat = "stretch"/>
        //fr2 is a frame with a background image

        // //fr7 is a frame with a background image
        // wxXmlNode* fr7 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
        //     Utils::SetAttrStr( fr7, "style:name", PageFrame );
        //     Utils::SetAttrStr( fr7, "style:family", "graphic" );
        //     Utils::SetAttrStr( fr7, "style:parent-style-name", "Frame" );
        // wxXmlNode* graphicProperties7 = Utils::AddNewNode( fr7, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        //     Utils::SetAttrStr( graphicProperties7, "style:wrap", "parallel" );
        //     Utils::SetAttrStr( graphicProperties7, "style:wrap", "parallel" ); 
        //     Utils::SetAttrStr( graphicProperties7, "style:number-wrapped-paragraphs", "no-limit" ); 
        //     Utils::SetAttrStr( graphicProperties7, "style:vertical-pos", "from-top" ); 
        //     Utils::SetAttrStr( graphicProperties7, "style:vertical-rel", "paragraph" ); 
        //     Utils::SetAttrStr( graphicProperties7, "style:horizontal-pos", "from-left" ); 
        //     Utils::SetAttrStr( graphicProperties7, "style:horizontal-rel", "paragraph" );

    return true;
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
    //<office:text text:use-soft-page-breaks = "true">
    //***********************************

    bool Content::EnableSoftPageBreak( )
    { 

        wxXmlNode* officeText = FindOfficeText( );
        Utils::SetAttrStr( officeText, "text:use-soft-page-breaks", "true" );
        return true;
    }



    wxXmlNode* Content::AddNewPage( )
    { 
        EnableSoftPageBreak( );
        wxXmlNode* officeText = FindOfficeText( );
        wxXmlNode* textP = Utils::AddNewNode( officeText, wxXML_ELEMENT_NODE, "text:p" );
        Utils::SetAttrStr( textP, "text:style-name", NormalTextStyle );
        //    <text:p text:style-name = "P1">
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
        const char* drawStyleName,  // fr2
        const char* textAnchorType,  // "page", "paragraph"
        const char* textStyleName )
    { 

        char str[ 20 ];
        wxXmlNode* drawFrame = Utils::AddNewNode( parent, wxXML_ELEMENT_NODE, "draw:frame" );
        Utils::SetAttrStr( drawFrame, "draw:style-name", drawStyleName );
        Utils::SetAttrStr( drawFrame, "draw:name", Utils::GetFrameName( str ) );
        Utils::SetAttrStr( drawFrame, "text:anchor-type", textAnchorType );
        Utils::SetAttrStr( drawFrame, "svg:x", Utils::DoubleToMMString( str, xPos ) );
        Utils::SetAttrStr( drawFrame, "svg:y", Utils::DoubleToMMString( str, yPos ) );
        Utils::SetAttrStr( drawFrame, "svg:width", Utils::DoubleToMMString( str, width ) );
        Utils::SetAttrStr( drawFrame, "draw:z-index", Utils::GetZIndex( str ) );

        wxXmlNode* drawTextBox = Utils::AddNewNode( drawFrame, wxXML_ELEMENT_NODE, "draw:text-box" );
        Utils::SetAttrStr( drawTextBox, "fo:min-height", Utils::DoubleToMMString( str, height ) );

        wxXmlNode* drawTextBoxP = Utils::AddNewNode( drawTextBox, wxXML_ELEMENT_NODE, "text:p" );
        Utils::SetAttrStr( drawTextBoxP, "text:style-name", textStyleName );
        // return child element for content
        return drawTextBoxP;
    }


    wxXmlNode* Content::WriteFrameFixedSize( wxXmlNode* parent, double xPos, 
        double yPos, 
        double width, 
        double height, 
        const char* drawStyleName,  // fr2
        const char* textAnchorType,  // "page", "paragraph"
        const char* textStyleName )
    { 

        char str[ 20 ];
        wxXmlNode* drawFrame = Utils::AddNewNode( parent, wxXML_ELEMENT_NODE, "draw:frame" );
        Utils::SetAttrStr( drawFrame, "draw:style-name", drawStyleName );
        Utils::SetAttrStr( drawFrame, "draw:name", Utils::GetFrameName( str ) );
        Utils::SetAttrStr( drawFrame, "text:anchor-type", textAnchorType );
        Utils::SetAttrStr( drawFrame, "svg:x", Utils::DoubleToMMString( str, xPos ) );
        Utils::SetAttrStr( drawFrame, "svg:y", Utils::DoubleToMMString( str, yPos ) );
        Utils::SetAttrStr( drawFrame, "svg:width", Utils::DoubleToMMString( str, width ) );
        Utils::SetAttrStr( drawFrame, "svg:height", Utils::DoubleToMMString( str, height ) );
        Utils::SetAttrStr( drawFrame, "draw:z-index", Utils::GetZIndex( str ) );

        wxXmlNode* drawTextBox = Utils::AddNewNode( drawFrame, wxXML_ELEMENT_NODE, "draw:text-box" );

        wxXmlNode* drawTextBoxP = Utils::AddNewNode( drawTextBox, wxXML_ELEMENT_NODE, "text:p" );
        Utils::SetAttrStr( drawTextBoxP, "text:style-name", textStyleName );
        // return child element for content
        return drawTextBoxP;
    }
    //***********************************


    wxXmlNode* Content::WriteImage( wxXmlNode* parent, double xPos, 
        double yPos, 
        double width, 
        double height, 
        wxString& drawStyleName,  // fr2
        wxString& textAnchorType, // "page", "paragraph"
        wxString& textStyleName,   // "P1"
        wxString& link )
    { 
        char str[ 20 ];
        wxXmlNode* imageFrame = Utils::AddNewNode( parent, wxXML_ELEMENT_NODE, "draw:frame" );
        Utils::SetAttrStr( imageFrame, "draw:style-name", drawStyleName );
        Utils::SetAttrStr( imageFrame, "draw:name", Utils::GetImageName( str ) );
        Utils::SetAttrStr( imageFrame, "text:anchor-type", textAnchorType );
        //    SetAttrStr( imageFrame, "svg:x", DoubleToMMString( str, xPos ) );
        //    SetAttrStr( imageFrame, "svg:y", DoubleToMMString( str, yPos ) );
        Utils::SetAttrStr( imageFrame, "svg:width", Utils::DoubleToMMString( str, width ) );
        Utils::SetAttrStr( imageFrame, "svg:height", Utils::DoubleToMMString( str, height ) );
        Utils::SetAttrStr( imageFrame, "draw:z-index", Utils::GetZIndex( str ) );

        if ( !link.IsEmpty( ) )
        { 
            wxXmlNode* image = Utils::AddNewNode( imageFrame, wxXML_ELEMENT_NODE, "draw:image " );

            wxString fullPath = ODT::ODTDoc( )->AddImageFile( link );
            Utils::SetAttrStr( image, "xlink:href", fullPath );
            Utils::SetAttrStr( image, "xlink:type", "simple" );
            Utils::SetAttrStr( image, "xlink:show", "embed" );
            Utils::SetAttrStr( image, "xlink:actuate", "onLoad" );
            Utils::SetAttrStr( image, "draw:mime-type", ODT::GetMimeType( link ) );
        }
        return imageFrame;
    }

    //***********************************
    wxXmlNode* Content::WriteTextBox( wxXmlNode* parent, double xPos, 
        double yPos, 
        double width, 
        double height, 
        wxString& drawStyleName,  // fr2
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
        return stampFrame;
    }



    bool Content::Save( )
    { 
        std::cout << "*************************************************\n";

        wxString str = ODT::ODTDoc( )->GetDocFilesDir( )+"/content.xml" ;
        // if ( !
        Utils::Save( m_content, str );
        // { 
        //     ReportError( "Content::SaveFiles", "Failed to save content xml" , true ) ;
        // }
        return true;
    }
}