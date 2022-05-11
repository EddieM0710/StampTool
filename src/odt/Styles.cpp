/**
 * @file Styles.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-08
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/
#include "odt/Styles.h"
//#include "DocumentManager.h"
#include <iostream>
#include "Defs.h"
#include "odt/ODTDefs.h"
#include "utils/XMLUtilities.h"
 //***********************************

namespace ODT {

    Styles::Styles( )
    {
        m_styles = new wxXmlDocument( );
        wxString configDir = GetDocManager( )->GetConfigDirectory( );
        wxString stylesTemplate = configDir + "/template/styles.xml";
        if ( !m_styles->Load( stylesTemplate ) )
        {
            ReportError( "Styles::Styles", "Styles xml failed to load", true );
        }

        AddFrameStyles( );
        //     std::cout << "dump Styles input\n";
        //  dump(m_styles);
        // std::cout << "***********************************************\n";

    }

    //***********************************

    bool Styles::Save( )
    {
        wxString str = ODTDoc( )->MakeAbsolute( "styles.xml" );
        ::Save( m_styles, str );

        //     std::cout << "dump Styles output\n";
        //  dump(m_styles);
        // std::cout << "***********************************************\n";

        return true;
    }

    bool Styles::AddBorderStyle( wxString filename, wxString& width,
        wxString& height,
        wxString& topMargin,
        wxString& bottomMargin,
        wxString& rightMargin,
        wxString& leftMargin )
    {

        wxXmlNode* layoutProperties = FindAutomaticStylesLayoutProperties( );
        if ( !layoutProperties )
        {
            return false;
        }

        Utils::SetAttrStr( layoutProperties, "fo:page-width", width );
        Utils::SetAttrStr( layoutProperties, "fo:page-height", height );
        Utils::SetAttrStr( layoutProperties, "fo:margin-top", topMargin );
        Utils::SetAttrStr( layoutProperties, "fo:margin-bottom", bottomMargin );
        Utils::SetAttrStr( layoutProperties, "fo:margin-left", rightMargin );
        Utils::SetAttrStr( layoutProperties, "fo:margin-right", leftMargin );
       Utils:: SetAttrStr( layoutProperties, "fo:background-color", "transparent" );

        wxXmlNode* backgroundImage = Utils::AddNewNode( layoutProperties, wxXML_ELEMENT_NODE, "style:background-image" );
        Utils::SetAttrStr( backgroundImage, "xlink:href", filename );
        Utils::SetAttrStr( backgroundImage, "xlink:type", "simple" );
        Utils::SetAttrStr( backgroundImage, "xlink:actuate", "onLoad" );
        Utils::SetAttrStr( backgroundImage, "style:repeat", "stretch" );

    }

    //***********************************


    wxXmlNode* Styles::FindOfficeStylesDrawFillImage( )
    {
        wxXmlNode* test = m_styles->GetRoot( );
        wxXmlNode* styles = Utils::FirstChildElement( test, "office:styles" );
        if ( !styles )
        {
            ReportError( "Styles::FindOfficeStylesDrawFillImage", "get office:styles failed", true );
            return ( wxXmlNode* )0;
        }
        wxString name( "draw:name" );
        wxString value( "bkgnd" );
        wxXmlNode* drawFillImage = Utils::FindFirstChildWithPropertyofValue( styles, name, value );
        if ( !drawFillImage )
        {
            ReportError( "Styles::FindOfficeStylesDrawFillImage", "get draw:fill-image failed", true );
            return ( wxXmlNode* )0;
        }
        return drawFillImage;
    }

    //***********************************


    // drill down StylesDoc xml to find the layout properties
    wxXmlNode* Styles::FindAutomaticStylesLayoutProperties( )
    {
        // this 
        wxXmlNode* docStyles = m_styles->GetRoot( );
        if ( !docStyles )
        {
            ReportError( "Styles::FindAutomaticStylesLayoutProperties", "get office:document-styles failed", true );
            return ( wxXmlNode* )0;
        }
        wxXmlNode* autoStyles = Utils::FirstChildElement( docStyles, "office:automatic-styles" );
        if ( !autoStyles )
        {
            ReportError( "Styles::FindAutomaticStylesLayoutProperties", "get office:automatic-styles failed", true );
            return ( wxXmlNode* )0;
        }
        wxString name( "style:name" );
        wxString value( "Mpm1" );
        wxXmlNode* stylePageLayout = Utils::FindFirstChildWithPropertyofValue( autoStyles, name, value );
        if ( !stylePageLayout )
        {
            ReportError( "Styles::FindAutomaticStylesLayoutProperties", "get stylePageLayout failed", true );
            return ( wxXmlNode* )0;
        }
        wxXmlNode* stylePageLayoutProperties = Utils::FirstChildElement( stylePageLayout, "style:page-layout-properties" );
        if ( !stylePageLayoutProperties )
        {
            ReportError( "Styles::FindAutomaticStylesLayoutProperties", "get stylePageLayoutPropertiess failed", true );
            return ( wxXmlNode* )0;
        }
        return stylePageLayoutProperties;

    }

    // drill down StylesDoc xml to find the office:styles
    wxXmlNode* Styles::FindOfficeStyles( )
    {
        // this 
        wxXmlNode* docStyles = m_styles->GetRoot( );
        if ( !docStyles )
        {
            ReportError( "Styles::FindOfficeStyles", "get office:document-styles failed", true );
            return ( wxXmlNode* )0;
        }
        wxXmlNode* officeStyles = Utils::FirstChildElement( docStyles, "office:styles" );
        if ( !officeStyles )
        {
            ReportError( "Styles::FindOfficeStyless", "get office:styles failed", true );
            return ( wxXmlNode* )0;
        }
        return officeStyles;

    }

    bool Styles::AddFrameStyles( )
    {

        wxXmlNode* officeStyles = FindOfficeStyles( );
        if ( !officeStyles )
        {
            return false;
        }

        wxXmlNode* frame20Contents = Utils::AddNewNode( officeStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttrStr( frame20Contents, "style:name", "Frame_20_contents" );
        Utils::SetAttrStr( frame20Contents, "style:display-name", "Frame contents" );
        Utils::SetAttrStr( frame20Contents, "style:family", "paragraph" );
        Utils::SetAttrStr( frame20Contents, "style:parent-style-name", "Text_20_body" );
        Utils::SetAttrStr( frame20Contents, "style:class", "extra" );
        wxXmlNode* frame = Utils::AddNewNode( officeStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttrStr( frame, "style:name", "Frame" );
        Utils::SetAttrStr( frame, "style:family", "graphic" );
        wxXmlNode* graphicProperties = Utils::AddNewNode( frame, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        Utils::SetAttrStr( graphicProperties, "text:anchor-type", "paragraph" );
        Utils::SetAttrStr( graphicProperties, "svg:x", "0in" );
        Utils::SetAttrStr( graphicProperties, "svg:y", "0in" );
        Utils::SetAttrStr( graphicProperties, "fo:margin-left", "0.0in" );
        Utils::SetAttrStr( graphicProperties, "fo:margin-right", "0.0in" );
        Utils::SetAttrStr( graphicProperties, "fo:margin-top", "0.0in" );
        Utils::SetAttrStr( graphicProperties, "fo:margin-bottom", "0.0in" );
        Utils::SetAttrStr( graphicProperties, "style:wrap", "parallel" );
        Utils::SetAttrStr( graphicProperties, "style:number-wrapped-paragraphs", "no-limit" );
        Utils::SetAttrStr( graphicProperties, "style:wrap-contour", "false" );
        Utils::SetAttrStr( graphicProperties, "style:vertical-pos", "top" );
        Utils::SetAttrStr( graphicProperties, "style:vertical-rel", "paragraph-content" );
        Utils::SetAttrStr( graphicProperties, "style:horizontal-pos", "center" );
        Utils::SetAttrStr( graphicProperties, "style:horizontal-rel", "paragraph-content" );
        Utils::SetAttrStr( graphicProperties, "fo:padding", "0.0591in" );
        Utils::SetAttrStr( graphicProperties, "fo:border", "0.0008in solid #000000" );

        frame = Utils::AddNewNode( officeStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttrStr( frame, "style:name", "Graphics" );
        Utils::SetAttrStr( frame, "style:family", "graphic" );
        graphicProperties = Utils::AddNewNode( frame, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        Utils::SetAttrStr( graphicProperties, "text:anchor-type", "paragraph" );

        Utils::SetAttrStr( graphicProperties, "svg:x", "0in" );
        Utils::SetAttrStr( graphicProperties, "svg:y", "0in" );
        Utils::SetAttrStr( graphicProperties, "style:wrap", "none" );
        Utils::SetAttrStr( graphicProperties, "style:vertical-pos", "top" );
        Utils::SetAttrStr( graphicProperties, "style:vertical-rel", "paragraph" );
        Utils::SetAttrStr( graphicProperties, " style:horizontal-pos", "center" );
       Utils:: SetAttrStr( graphicProperties, "style:horizontal-rel", "paragraph" );


        //  <style:style style:name="Frame_20_contents" style:display-name="Frame contents" style:family="paragraph" style:parent-style-name="Text_20_body" style:class="extra"/>
        //   <style:style style:name="Frame" style:family="graphic">
        //    <style:graphic-properties text:anchor-type="paragraph" svg:x="0in" svg:y="0in" fo:margin-left="0.0791in" fo:margin-right="0.0791in" fo:margin-top="0.0791in" fo:margin-bottom="0.0791in" style:wrap="parallel" style:number-wrapped-paragraphs="no-limit" style:wrap-contour="false" style:vertical-pos="top" style:vertical-rel="paragraph-content" style:horizontal-pos="center" style:horizontal-rel="paragraph-content" fo:padding="0.0591in" fo:border="0.0008in solid #000000"/>
        //   </style:style>

        // <style:style style:name="Graphics" style:family="graphic">
        //     <style:graphic-properties text:anchor-type="paragraph" svg:x="0in" svg:y="0in" style:wrap="none" style:vertical-pos="top" style:vertical-rel="paragraph" style:horizontal-pos="center" style:horizontal-rel="paragraph"/>
        // </style:style>

        return true;
    }

}