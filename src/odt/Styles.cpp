/**
 * @file Styles.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-08
 *
 * @copyright Copyright (c) 2022
 *
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/
#include "odt/Styles.h"
 //#include "DocumentManager.h"
#include <iostream>
#include "Defs.h"
#include "odt/ODTDefs.h"
#include "odt/Document.h"
#include "utils/XMLUtilities.h"
#include "utils/Settings.h"
 //***********************************

namespace ODT {

    Styles::Styles( )
    {
        m_styles = new wxXmlDocument( );
        wxString configDir = GetSettings( )->GetConfigurationDirectory( );
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
        wxString str = ODTDoc( )->GetDocFilesDir( ) + "/styles.xml";
        m_styles->Save( str );

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
        Utils::SetAttrStr( layoutProperties, "fo:background-color", "transparent" );

        wxXmlNode* backgroundImage = Utils::AddNewNode( layoutProperties, wxXML_ELEMENT_NODE, "style:background-image" );
        Utils::SetAttrStr( backgroundImage, "xlink:href", filename );
        Utils::SetAttrStr( backgroundImage, "xlink:type", "simple" );
        Utils::SetAttrStr( backgroundImage, "xlink:actuate", "onLoad" );
        Utils::SetAttrStr( backgroundImage, "style:repeat", "stretch" );

    }

    //***********************************


    wxXmlNode* Styles::FindOfficeStylesDrawFillImage( wxString value )
    {
        wxXmlNode* test = m_styles->GetRoot( );
        wxXmlNode* styles = Utils::FirstChildElement( test, "office:styles" );
        if ( !styles )
        {
            ReportError( "Styles::FindOfficeStylesDrawFillImage", "get office:styles failed", true );
            return ( wxXmlNode* )0;
        }
        wxString name( "draw:name" );
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
            ReportError( "Styles::FindOfficeStyles", "get office:styles failed", true );
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
        Utils::SetAttrStr( frame20Contents, "style:parent-style-name", "Standard" );
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
        Utils::SetAttrStr( graphicProperties, "fo:padding", "1.5mm" );
        Utils::SetAttrStr( graphicProperties, "fo:border", "0.06mm solid #000000" );


        //     frame = Utils::AddNewNode( officeStyles, wxXML_ELEMENT_NODE, "style:style" );
        //     Utils::SetAttrStr( frame, "style:name", "Graphics" );
        //     Utils::SetAttrStr( frame, "style:family", "graphic" );
        //     graphicProperties = Utils::AddNewNode( frame, wxXML_ELEMENT_NODE, "style:graphic-properties" );
        //     Utils::SetAttrStr( graphicProperties, "text:anchor-type", "paragraph" );

        //     Utils::SetAttrStr( graphicProperties, "svg:x", "0in" );
        //     Utils::SetAttrStr( graphicProperties, "svg:y", "0in" );
        //     Utils::SetAttrStr( graphicProperties, "style:wrap", "none" );
        //     Utils::SetAttrStr( graphicProperties, "style:vertical-pos", "top" );
        //     Utils::SetAttrStr( graphicProperties, "style:vertical-rel", "paragraph" );
        //     Utils::SetAttrStr( graphicProperties, " style:horizontal-pos", "center" );
        //    Utils:: SetAttrStr( graphicProperties, "style:horizontal-rel", "paragraph" );



        return true;
    }
    wxString Styles::AddBackgroundImage( wxString link )
    {

        wxFileName inputImage( link );
        wxString str = inputImage.GetFullName();
        wxString drawName = inputImage.GetName( );
        wxFileName picImage( "Pictures", str );
        wxString  destFullPath = ODT::ODTDoc( )->GetPicturesDir( ) + str;

        bool state = wxCopyFile( inputImage.GetFullPath( ), destFullPath );
        ODT::StylesDoc( )->AddDrawFillImage( drawName, picImage.GetFullPath( ), "simple", "embed", "onLoad" );
        return drawName;
    }

    // AddDrawFillImage( "box2", "Pictures/box2.jpg", "simple", "embed", "onLoad");
    bool Styles::AddDrawFillImage( wxString drawName, wxString xlinkHref, wxString xlinkType, wxString xlinkShow, wxString xlinkActuate )
    {

        wxXmlNode* officeStyles = FindOfficeStyles( );
        if ( !officeStyles )
        {
            return false;
        }

        wxXmlNode* frame20Contents = Utils::AddNewNode( officeStyles, wxXML_ELEMENT_NODE, "draw:fill-image" );
        Utils::SetAttrStr( frame20Contents, "draw:name", drawName );
        Utils::SetAttrStr( frame20Contents, "xlink:href", xlinkHref );
        Utils::SetAttrStr( frame20Contents, "xlink:type", xlinkType );
        Utils::SetAttrStr( frame20Contents, "xlink:show", xlinkShow );
        Utils::SetAttrStr( frame20Contents, "xlink:actuate", xlinkActuate );
        return true;
    }
}