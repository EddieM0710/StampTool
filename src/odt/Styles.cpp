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
#include "DocumentManager.h"
#include <iostream>
#include "Defs.h"
#include "odt/ODTDefs.h"

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

        SetAttribute( layoutProperties, "fo:page-width", width );
        SetAttribute( layoutProperties, "fo:page-height", height );
        SetAttribute( layoutProperties, "fo:margin-top", topMargin );
        SetAttribute( layoutProperties, "fo:margin-bottom", bottomMargin );
        SetAttribute( layoutProperties, "fo:margin-left", rightMargin );
        SetAttribute( layoutProperties, "fo:margin-right", leftMargin );
        SetAttribute( layoutProperties, "fo:background-color", "transparent" );

        wxXmlNode* backgroundImage = AddNewNode( layoutProperties, wxXML_ELEMENT_NODE, "style:background-image" );
        SetAttribute( backgroundImage, "xlink:href", filename );
        SetAttribute( backgroundImage, "xlink:type", "simple" );
        SetAttribute( backgroundImage, "xlink:actuate", "onLoad" );
        SetAttribute( backgroundImage, "style:repeat", "stretch" );

    }

    //***********************************


    wxXmlNode* Styles::FindOfficeStylesDrawFillImage( )
    {
        wxXmlNode* test = m_styles->GetRoot( );
        wxXmlNode* styles = FirstChildElement( test, "office:styles" );
        if ( !styles )
        {
            ReportError( "Styles::FindOfficeStylesDrawFillImage", "get office:styles failed", true );
            return ( wxXmlNode* )0;
        }
        wxString name( "draw:name" );
        wxString value( "bkgnd" );
        wxXmlNode* drawFillImage = FindFirstChildWithPropertyofValue( styles, name, value );
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
        wxXmlNode* autoStyles = FirstChildElement( docStyles, "office:automatic-styles" );
        if ( !autoStyles )
        {
            ReportError( "Styles::FindAutomaticStylesLayoutProperties", "get office:automatic-styles failed", true );
            return ( wxXmlNode* )0;
        }
        wxString name( "style:name" );
        wxString value( "Mpm1" );
        wxXmlNode* stylePageLayout = FindFirstChildWithPropertyofValue( autoStyles, name, value );
        if ( !stylePageLayout )
        {
            ReportError( "Styles::FindAutomaticStylesLayoutProperties", "get stylePageLayout failed", true );
            return ( wxXmlNode* )0;
        }
        wxXmlNode* stylePageLayoutProperties = FirstChildElement( stylePageLayout, "style:page-layout-properties" );
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
        wxXmlNode* officeStyles = FirstChildElement( docStyles, "office:styles" );
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

        wxXmlNode* frame20Contents = AddNewNode( officeStyles, wxXML_ELEMENT_NODE, "style:style" );
        SetAttribute( frame20Contents, "style:name", "Frame_20_contents" );
        SetAttribute( frame20Contents, "style:display-name", "Frame contents" );
        SetAttribute( frame20Contents, "style:family", "paragraph" );
        SetAttribute( frame20Contents, "style:parent-style-name", "Text_20_body" );
        SetAttribute( frame20Contents, "style:class", "extra" );
        wxXmlNode* frame = AddNewNode( officeStyles, wxXML_ELEMENT_NODE, "style:style" );
        SetAttribute( frame, "style:name", "Frame" );
        SetAttribute( frame, "style:family", "graphic" );
        wxXmlNode* graphicProperties = AddNewNode( frame, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        SetAttribute( graphicProperties, "text:anchor-type", "paragraph" );
        SetAttribute( graphicProperties, "svg:x", "0in" );
        SetAttribute( graphicProperties, "svg:y", "0in" );
        SetAttribute( graphicProperties, "fo:margin-left", "0.0in" );
        SetAttribute( graphicProperties, "fo:margin-right", "0.0in" );
        SetAttribute( graphicProperties, "fo:margin-top", "0.0in" );
        SetAttribute( graphicProperties, "fo:margin-bottom", "0.0in" );
        SetAttribute( graphicProperties, "style:wrap", "parallel" );
        SetAttribute( graphicProperties, "style:number-wrapped-paragraphs", "no-limit" );
        SetAttribute( graphicProperties, "style:wrap-contour", "false" );
        SetAttribute( graphicProperties, "style:vertical-pos", "top" );
        SetAttribute( graphicProperties, "style:vertical-rel", "paragraph-content" );
        SetAttribute( graphicProperties, "style:horizontal-pos", "center" );
        SetAttribute( graphicProperties, "style:horizontal-rel", "paragraph-content" );
        SetAttribute( graphicProperties, "fo:padding", "0.0591in" );
        SetAttribute( graphicProperties, "fo:border", "0.0008in solid #000000" );

        frame = AddNewNode( officeStyles, wxXML_ELEMENT_NODE, "style:style" );
        SetAttribute( frame, "style:name", "Graphics" );
        SetAttribute( frame, "style:family", "graphic" );
        graphicProperties = AddNewNode( frame, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        SetAttribute( graphicProperties, "text:anchor-type", "paragraph" );

        SetAttribute( graphicProperties, "svg:x", "0in" );
        SetAttribute( graphicProperties, "svg:y", "0in" );
        SetAttribute( graphicProperties, "style:wrap", "none" );
        SetAttribute( graphicProperties, "style:vertical-pos", "top" );
        SetAttribute( graphicProperties, "style:vertical-rel", "paragraph" );
        SetAttribute( graphicProperties, " style:horizontal-pos", "center" );
        SetAttribute( graphicProperties, "style:horizontal-rel", "paragraph" );


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