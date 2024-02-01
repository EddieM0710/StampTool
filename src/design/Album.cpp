/**
 * @file Album.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
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


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/gdicmn.h>
#include <wx/msgdlg.h>

#include "design/Album.h"
#include <wx/pdfdc.h>
#include <wx/cmndata.h>
#include "design/AlbumVolume.h"
#include "design/Page.h"
#include "utils/XMLUtilities.h"
#include "utils/FontList.h"
#include "utils/Settings.h"
#include "utils/Project.h"
#include "gui/AlbumTreeCtrl.h"


namespace Design {

    //----------------

    Album::Album( wxXmlNode* node ) : AlbumBase( node )
    {
        SetNodeType( AT_Album );
        SetDefaults( &m_pageDefaults );
        InitParameters( );
    }

    //----------------

    void Album::InitParameters( )
    {
    }

    //----------------

    wxString Album::DrawPDF( )
    {
        wxString docName = GetDocName( );
        docName += ".pdf";
        wxFileName outFile( docName );
        outFile.MakeAbsolute( );
        wxString fullPath = outFile.GetFullPath( );

        double width = GetAlbumAttributeDbl( AT_PaperWidth );
        double height = GetAlbumAttributeDbl( AT_PaperHeight );
        wxPdfDocument* doc = new wxPdfDocument( wxPORTRAIT, width, height );

        wxPdfDC pdfDC( doc, doc->GetPageWidth( ), doc->GetPageHeight( ) );

        // set wxPdfDC mapping mode style so
        // we can scale fonts and graphics
        // coords with a single setting
        pdfDC.SetMapModeStyle( wxPDF_MAPMODESTYLE_PDF );
        pdfDC.SetMapMode( wxMM_TEXT );
        wxSize pdfPPI = pdfDC.GetPPI( );
        PPMM.x = pdfPPI.x / 25.4;
        PPMM.y = pdfPPI.y / 25.4;
        pdfDC.SetUserScale( PPMM.x, PPMM.y );

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            int childType = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );

            // set the layout parameters into the child
            Page* page = ( Page* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            if ( Design::IsPortrait( page->Orientation( ) ) )
            {
                doc->AddPage( wxPORTRAIT, wxPAPER_A3 );
                page->DrawPDF( doc, width, height );
            }
            else
            {
                int offset = 0; ( GetAlbumAttributeDbl( AT_PaperWidth ) - GetAlbumAttributeDbl( AT_PageHeight ) ) / 2;
                std::cout << "PAPER " << GetAlbumAttributeDbl( AT_PaperWidth ) << "  " << GetAlbumAttributeDbl( AT_PaperHeight ) << "\n";
                std::cout << "PAGE " << GetAlbumAttributeDbl( AT_PageWidth ) << "  " << GetAlbumAttributeDbl( AT_PageHeight ) << "\n";
                std::cout << "Offset " << offset << "\n";
                doc->AddPage( wxPORTRAIT, wxPAPER_A3 );
                //doc->Rotate( -90, 20 + GetAlbumAttributeDbl( AT_PageWidth ) / 2, 4 + GetAlbumAttributeDbl( AT_PageHeight ) / 2 );
                doc->Rotate( 90, ( GetAlbumAttributeDbl( AT_PageHeight ) / 2 ) + 0, ( GetAlbumAttributeDbl( AT_PageWidth ) / 2 ) + 18 );
                //  doc->AddPage( wxLANDSCAPE, width, height );
                page->DrawPDF( doc, width, height );

            }

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        doc->SaveAsFile( fullPath );

        wxString txt = wxString::Format( "Generated %s.\n\n", fullPath );
        wxMessageDialog* dlg = new wxMessageDialog(
            ( wxWindow* ) GetFrame( ), txt,
            wxT( "Pdf Generated" ),
            wxOK | wxCENTER );
        int rsp = dlg->ShowModal( );
        return docName;
    }

    //----------------

    wxString Album::GetCatalog( ) {
        wxString cat = GetAlbumAttributeStr( AT_Catalog );
        if ( cat.IsEmpty( ) )
        {
            cat = GetProject( )->GetProjectCatalogCode( );
        }
        return cat;
    };

    //----------------

    wxColour Album::GetColor( FontUsageType fontType )
    {
        int ndx = GetFontNdx( fontType );
        if ( GetFontList( )->IsValidFontNdx( ndx ) )
        {
            return GetFontList( )->GetColor( ndx );
        }
        if ( GetNodeType( ) == AT_Album )
        {
            return GetFontList( )->GetColor( GetAlbum( )->GetFontNdxPreference( fontType ) );
        }
        else
        {
            return GetAlbum( )->GetColor( fontType );
        }
    }

    //----------------

    wxString Album::GetDocName( ) {
        return  GetAttrStr( "Name" );
    };

    //----------------

    wxFont Album::GetFont( FontUsageType fontType )
    {
        return GetFontList( )->GetFont( GetFontNdx( fontType ) );
    };

    //----------------

    int Album::GetFontNdx( FontUsageType fontType )
    {
        int ndx = DefaultFonts[ fontType ];
        if ( GetFontList( )->IsValidFontNdx( ndx ) )
        {
            return DefaultFonts[ fontType ];
        }
        else
        {
            return GetSettings( )->GetFontNdxPreference( fontType );
        }
    };

    //----------------

    int Album::GetFontNdxPreference( FontUsageType fontType )
    {
        return GetSettings( )->GetFontNdxPreference( fontType );
    }

    //----------------

    bool Album::IsDefaultFont( FontUsageType fontType, int ndx )
    {
        return ( ndx == GetFontNdx( fontType ) );
    }

    //----------------

    void Album::LoadFonts( wxXmlNode* node )
    {
        wxXmlNode* fonts = Utils::FirstChildElement( node, "Fonts" );
        if ( fonts )
        {
            Design::AlbumBaseType nodeType = GetNodeType( );

            DefaultFonts[ AT_NbrFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_NbrFontType );
            if ( DefaultFonts[ AT_NbrFontType ] < 0 )
            {
                if ( nodeType == AT_Album )
                {
                    DefaultFonts[ AT_NbrFontType ] = GetSettings( )->GetFontNdxPreference( AT_NbrFontType );
                }
            }

            DefaultFonts[ AT_NameFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_NameFontType );
            if ( DefaultFonts[ AT_NameFontType ] < 0 )
            {
                if ( IsNodeType( AT_Album ) )
                {
                    DefaultFonts[ AT_NameFontType ] = GetSettings( )->GetFontNdxPreference( AT_NameFontType );
                }
            }

            DefaultFonts[ AT_TextFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_TextFontType );
            if ( DefaultFonts[ AT_TextFontType ] < 0 )
            {
                if ( IsNodeType( AT_Album ) )
                {
                    DefaultFonts[ AT_TextFontType ] = GetSettings( )->GetFontNdxPreference( AT_TextFontType );
                }
            }

            DefaultFonts[ AT_TitleFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_TitleFontType );
            if ( DefaultFonts[ AT_TitleFontType ] < 0 )
            {
                if ( IsNodeType( AT_Album ) )
                {
                    DefaultFonts[ AT_TitleFontType ] = GetSettings( )->GetFontNdxPreference( Design::AT_TitleFontType );
                }
            }
        }
    }

    //----------------

    void Album::FixupNode( )
    {

        for ( int j = 0; j < AT_NbrAttrTypes; j++ )
        {
            AlbumAttrType i = ( AlbumAttrType ) j;
            wxString str = GetAttrStr( i );
            if ( !str.IsEmpty( ) )
            {
                if ( i == AT_PageWidth )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_PageHeight )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_TopPageMargin )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_BottomPageMargin )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_RightPageMargin )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_LeftPageMargin )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_BorderFileName )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_BorderSize )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_ShowBorder )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_ShowTitle )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_ShowSubTitle )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_ShowCatNbr )
                {
                    m_stampDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_ShowFrame )
                {
                    m_frameDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_ShowImage )
                {
                    m_stampDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_Orientation )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_GrayScaleImages )
                {
                    m_stampDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_TopContentMargin )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_BottomContentMargin )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_LeftContentMargin )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_RightContentMargin )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_CalculateSpacing )
                {
                    m_frameDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_FixedSpacingSize )
                {
                    m_frameDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_OverSizePaper )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_PaperHeight )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_PaperWidth )
                {
                    m_pageDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_SelvageHeight )
                {
                    m_stampDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_SelvageWidth )
                {
                    m_stampDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_MountAllowanceHeight )
                {
                    m_stampDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_MountAllowanceWidth )
                {
                    m_stampDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_StampNamePosition )
                {
                    m_stampDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_StampAlignmentMode )
                {
                    m_frameDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_StampMargin )
                {
                    m_stampDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
                else  if ( i == AT_Catalog )
                {
                    m_stampDefaults.SetAttrStr( i, str );
                    DeleteAttribute( AttrNameStrings[ i ] );
                }
            }
        }
    }

    //----------------

    void Album::LoadDefaults( wxXmlNode* node )
    {
        wxXmlNode* defaults = Utils::FirstChildElement( node, "Defaults" );
        if ( defaults )
        {
            wxXmlNode* child = defaults->GetChildren( );
            while ( child )
            {
                wxString name = child->GetName( );
                if ( !name.Cmp( "Default" ) )
                {
                    wxString layoutType = child->GetAttribute( "LayoutType" );
                    if ( !layoutType.Cmp( LayoutTypeStrings[ LT_Page ] ) )
                    {
                        wxXmlAttribute* attr = child->GetAttributes( );
                        while ( attr )
                        {
                            wxString attrName = attr->GetName( );

                            wxString attrVal = attr->GetValue( );
                            m_pageDefaults.SetAttrStr( attrName, attrVal );

                            attr = attr->GetNext( );
                        }
                    }
                    else  if ( !layoutType.Cmp( LayoutTypeStrings[ LT_Stamp ] ) )
                    {
                        wxXmlAttribute* attr = child->GetAttributes( );
                        while ( attr )
                        {
                            wxString attrName = attr->GetName( );

                            wxString attrVal = attr->GetValue( );
                            m_stampDefaults.SetAttrStr( attrName, attrVal );

                            attr = attr->GetNext( );
                        }
                    }
                    else  if ( !layoutType.Cmp( LayoutTypeStrings[ LT_Frame ] ) )
                    {
                        wxXmlAttribute* attr = child->GetAttributes( );
                        while ( attr )
                        {
                            wxString attrName = attr->GetName( );

                            wxString attrVal = attr->GetValue( );
                            m_frameDefaults.SetAttrStr( attrName, attrVal );
                            attr = attr->GetNext( );
                        }
                    }
                }
                child = child->GetNext( );
            }
        }
    }


    //----------------

    void Album::MakeAlbum( )
    {
        UpdateMinimumSize( );
        UpdateSizes( );
        UpdatePositions( );
    }

    //----------------

    void Album::MakeDefaultFont( FontUsageType fontType )
    {
        GetFontList( )->MakeDefault( DefaultFonts[ fontType ] );
    };

    //----------------

    void Album::MakePDFAlbum( )
    {
        MakeAlbum( );
        wxString outName = DrawPDF( );
    }

    //----------------

    void Album::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_OverSizePaper );
        SetAttribute( xmlNode, AT_PaperHeight );
        SetAttribute( xmlNode, AT_PaperWidth );
        SetAttribute( xmlNode, AT_PageWidth );
        SetAttribute( xmlNode, AT_PageHeight );
        SetAttribute( xmlNode, AT_TopPageMargin );
        SetAttribute( xmlNode, AT_BottomPageMargin );
        SetAttribute( xmlNode, AT_RightPageMargin );
        SetAttribute( xmlNode, AT_LeftPageMargin );
        SetAttribute( xmlNode, AT_BorderFileName );
        SetAttribute( xmlNode, AT_BorderSize );
        SetAttribute( xmlNode, AT_ShowCatNbr );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_ShowSubTitle );
        SetAttribute( xmlNode, AT_ShowSubTitle );
        SetAttribute( xmlNode, AT_GrayScaleImages );
        SetAttribute( xmlNode, AT_StampNamePosition );
        SetAttribute( xmlNode, AT_Orientation );
        SaveFonts( xmlNode );
        SaveDefaults( xmlNode );
    }

    //----------------
    void Album::SaveDefaults( wxXmlNode* parent )
    {
        wxXmlNode* defaults = Utils::NewNode( parent, "Defaults" );
        if ( defaults )
        {
            wxXmlNode* pageDefault = Utils::NewNode( defaults, "Default" );
            if ( pageDefault )
            {
                Utils::SetAttrStr( pageDefault, AttrNameStrings[ AT_LayoutType ], LayoutTypeStrings[ LT_Page ] );
                AlbumPageDefaults( )->Save( pageDefault );
            }

            wxXmlNode* frameDefault = Utils::NewNode( defaults, "Default" );
            if ( frameDefault )
            {
                Utils::SetAttrStr( frameDefault, AttrNameStrings[ AT_LayoutType ], LayoutTypeStrings[ LT_Frame ] );
                AlbumFrameDefaults( )->Save( frameDefault );
            }

            wxXmlNode* stampDefault = Utils::NewNode( defaults, "Default" );
            if ( stampDefault )
            {
                Utils::SetAttrStr( stampDefault, AttrNameStrings[ AT_LayoutType ], LayoutTypeStrings[ LT_Stamp ] );
                AlbumStampDefaults( )->Save( stampDefault );
            }
        }
    }

    //----------------

    void Album::SaveFonts( wxXmlNode* parent )
    {
        if ( DefaultFonts[ AT_NbrFontType ] >= 0
            || DefaultFonts[ AT_TextFontType ] >= 0
            || DefaultFonts[ AT_TitleFontType ] >= 0
            || DefaultFonts[ AT_SubTitleFontType ] >= 0
            || DefaultFonts[ AT_NameFontType ] >= 0 )
        {
            wxXmlNode* fonts = Utils::NewNode( parent, "Fonts" );
            if ( fonts )
            {
                if ( DefaultFonts[ AT_NbrFontType ] >= 0 )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_NbrFontType, GetFontNdx( AT_NbrFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, DefaultFonts[ AT_NbrFontType ], Design::AT_NbrFontType );
                    }
                }
                if ( DefaultFonts[ AT_NameFontType ] >= 0 )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_NameFontType, GetFontNdx( AT_NameFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, DefaultFonts[ AT_NameFontType ], Design::AT_NameFontType );
                    }
                }
                if ( DefaultFonts[ AT_TextFontType ] >= 0 )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_TextFontType, GetFontNdx( AT_TextFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, DefaultFonts[ AT_TextFontType ], Design::AT_TextFontType );
                    }
                }
                if ( DefaultFonts[ AT_TitleFontType ] >= 0 )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_TitleFontType, GetFontNdx( AT_TitleFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, DefaultFonts[ AT_TitleFontType ], Design::AT_TitleFontType );
                    }
                }
                if ( DefaultFonts[ AT_SubTitleFontType ] >= 0 )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_SubTitleFontType, GetFontNdx( AT_SubTitleFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, DefaultFonts[ AT_SubTitleFontType ], Design::AT_SubTitleFontType );
                    }
                }
            }
        }
    }

    //----------------

    void Album::SetCatalog( wxString str )
    {

        wxString currCat = GetCatalog( );
        if ( str.Cmp( currCat ) )
        {
            if ( currCat.IsEmpty( ) )
            {
                SetAttrStr( AT_Catalog, str );
                // now fix all the stamp entries to reflect the right catalog code
                GetAlbumTreeCtrl( )->UpdateAlbumStampEntries( GetAlbumTreeCtrl( )->GetRootItem( ) );
                return;
            }
            else
            {
                if ( !currCat.Cmp( str ) )
                {
                    return;
                }
                else
                {
                    SetAttrStr( AT_Catalog, str );
                    // now fix all the stamp entries to reflect the right catalog code
                    GetAlbumTreeCtrl( )->UpdateAlbumStampEntries( GetAlbumTreeCtrl( )->GetRootItem( ) );
                }
            }
        }
    };

    //----------------

    void Album::SetDocName( wxString str ) {
        SetAttrStr( AT_Name, str );
    };

    //----------------

    void Album::SetFont( FontUsageType fontType, wxFont font, wxColour color )
    {
        int ndx = GetFontList( )->AddNewFont( font, color );
        if ( IsDefaultFont( fontType, ndx ) && !IsNodeType( AT_Album ) )
        {
            SetFontNdx( fontType, -1 );
        }
        else
        {
            SetFontNdx( fontType, ndx );
        }
    }

    //----------------

    void Album::SetFontNdx( FontUsageType fontType, int ndx )
    {
        DefaultFonts[ fontType ] = ndx;
    };

    //----------------

    bool Album::UpdateMinimumSize( )
    {

        // set known child values
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            switch ( type )
            {
                case AT_Page:
                {
                    // set the layout parameters into the child
                    Page* page = ( Page* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

                    page->Init( );
                    page->SetBorderFilename( m_pageDefaults.BorderFilename( ) );
                    page->UpdateMinimumSize( );
                    break;
                }
                default:
                break;
            }
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        return true;
    }

    //----------------

    void Album::UpdatePositions( )
    {
        // go to the bottom of each child container object ( row, column, page )
        // and begin filling in position relative to the parent

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            child->UpdatePositions( );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    //----------------

    void Album::UpdateSizes( )
    {
        // go to the bottom of each child container object ( row, column, page )
        // and begin filling in position relative to the parent

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            //  call each childs Design function
            child->UpdateSizes( );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    //----------------

    NodeStatus Album::ValidateNode( )
    {
        NodeStatus status = AT_OK;
        if ( m_pageDefaults.PageHeight( ) <= 0.0 )
        {
            // "Must define the page height.\n";
            status = AT_FATAL;
        }
        if ( m_pageDefaults.PageWidth( ) <= 0.0 )
        {
            //   "Must define the page width.\n";
            status = AT_FATAL;
        }
        m_nodeValid = status;
        return status;
    }

    //----------------

}