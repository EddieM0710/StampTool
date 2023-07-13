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
#include "gui/AlbumTreeCtrl.h"
 //#include "StampToolApp.h"

 //wxDECLARE_APP( StampToolApp );

namespace Design {



    wxString Album::DrawPDF( )
    {

        wxString docName = GetDocName( );
        docName += ".pdf";
        wxFileName outFile( docName );
        outFile.MakeAbsolute( );
        wxString fullPath = outFile.GetFullPath( );

        double width = GetAttrDbl( AT_PaperWidth );
        double height = GetAttrDbl( AT_PaperHeight );
        wxPdfDocument* doc = new wxPdfDocument( wxPORTRAIT, width, height );

        wxPdfDC pdfDC( doc, doc->GetPageWidth( ), doc->GetPageHeight( ) );

        // set wxPdfDC mapping mode style so
        // we can scale fonts and graphics
        // coords with a single setting
        pdfDC.SetMapModeStyle( wxPDF_MAPMODESTYLE_PDF );
        pdfDC.SetMapMode( wxMM_POINTS );
        wxSize pdfPPI = pdfDC.GetPPI( );
        DeviceUnitsPerMM.x = pdfPPI.x / 25.4;
        DeviceUnitsPerMM.y = pdfPPI.y / 25.4;
        pdfDC.SetUserScale( DeviceUnitsPerMM.x, DeviceUnitsPerMM.y );

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            int childType = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );

            doc->AddPage( );

            // set the layout parameters into the child
            Page* page = ( Page* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            page->DrawPDF( doc, width, height );

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

    void Album::DumpFont( wxString Level )
    {

        int ndx = DefaultFonts[ AT_NbrFontType ].Get( );
        std::cout << Level << "CatNbr font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;

        ndx = DefaultFonts[ AT_TextFontType ].Get( );
        std::cout << Level << "Text font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;

        ndx = DefaultFonts[ AT_TitleFontType ].Get( );
        std::cout << Level << "Title font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;
    };

    void Album::DumpLayout( )
    {
        std::cout << "Album Parms w:" << GetAttrStr( AT_PageWidth )
            << " h:" << GetAttrStr( AT_PageHeight )
            << " tm:" << GetAttrStr( AT_TopMargin )
            << " bm:" << GetAttrStr( AT_BottomMargin )
            << " rm:" << GetAttrStr( AT_RightMargin )
            << " lm:" << GetAttrStr( AT_LeftMargin ) << "\n";

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            child->DumpLayout( 0, 0 );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    double Album::GetBorderSize( ) { return GetAttrDbl( AT_BorderSize ); };

    wxString Album::GetBorderSizeStr( ) { return GetAttrStr( AT_BorderSize ); };

    wxString Album::GetBorderFileName( ) { return GetAttrStr( AT_BorderFileName ); };

    double Album::GetBottomMargin( ) { return GetAttrDbl( AT_BottomMargin ); };

    wxString Album::GetBottomMarginStr( ) { return GetAttrStr( AT_BottomMargin ); };

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

    wxString Album::GetDocName( ) { return  GetAttrStr( "Name" ); };

    wxFont Album::GetFont( FontUsageType fontType )
    {
        return GetFontList( )->GetFont( GetFontNdx( fontType ) );
    };

    int Album::GetFontNdx( FontUsageType fontType )
    {
        int ndx = DefaultFonts[ fontType ].Get( );
        if ( GetFontList( )->IsValidFontNdx( ndx ) )
        {
            return DefaultFonts[ fontType ].Get( );
        }
        else
        {
            return GetSettings( )->GetFontNdxPreference( fontType );
        }
    };


    int Album::GetFontNdxPreference( FontUsageType fontType )
    {
        return GetSettings( )->GetFontNdxPreference( fontType );
    }

    double Album::GetHeight( ) { return GetAttrDbl( AT_PageHeight ); };

    double Album::GetLeftMargin( ) { return GetAttrDbl( AT_LeftMargin ); };

    wxString Album::GetLeftMarginStr( ) { return GetAttrStr( AT_LeftMargin ); };

    double Album::GetPageHeight( ) { return GetAttrDbl( AT_PageHeight ); };

    wxString Album::GetPageHeightStr( ) { return GetAttrStr( AT_PageHeight ); };
    wxString Album::GetPaperHeightStr( ) { return GetAttrStr( AT_PaperHeight ); };

    void Album::GetPageParameters( wxString& width,
        wxString& height,
        wxString& topMargin,
        wxString& bottomMargin,
        wxString& rightMargin,
        wxString& leftMargin )
    {
        width = GetAttrStr( AT_PageWidth );
        height = GetAttrStr( AT_PageHeight );
        topMargin = GetAttrStr( AT_TopMargin );
        bottomMargin = GetAttrStr( AT_BottomMargin );
        rightMargin = GetAttrStr( AT_RightMargin );
        leftMargin = GetAttrStr( AT_LeftMargin );
    };

    double Album::GetPaperWidth( ) { return GetAttrDbl( AT_PaperWidth ); };

    double Album::GetPaperHeight( ) { return GetAttrDbl( AT_PaperHeight ); };

    wxString Album::GetPaperWidthStr( ) { return GetAttrStr( AT_PaperWidth ); };

    double Album::GetPageWidth( ) { return GetAttrDbl( AT_PageWidth ); };

    wxString Album::GetPageWidthStr( ) { return GetAttrStr( AT_PageWidth ); };

    double Album::GetRightMargin( ) { return GetAttrDbl( AT_RightMargin ); };

    wxString Album::GetRightMarginStr( ) { return GetAttrStr( AT_RightMargin ); };

    double Album::GetTopMargin( ) { return GetAttrDbl( AT_TopMargin ); };

    wxString Album::GetTopMarginStr( ) { return GetAttrStr( AT_TopMargin ); };

    double Album::GetWidth( ) { return GetAttrDbl( AT_PageWidth ); };

    bool Album::IsDefaultFont( FontUsageType fontType, int ndx )
    {
        return ( ndx == GetFontNdx( fontType ) );
    }

    void Album::LoadFonts( wxXmlNode* node )
    {

        wxXmlNode* fonts = Utils::FirstChildElement( node, "Fonts" );
        if ( fonts )
        {

            Design::AlbumBaseType nodeType = GetNodeType( );

            DefaultFonts[ AT_NbrFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_NbrFontType );
            if ( !DefaultFonts[ AT_NbrFontType ].IsOk( ) )
            {
                if ( nodeType == AT_Album )
                {
                    DefaultFonts[ AT_NbrFontType ].Set( GetSettings( )->GetFontNdxPreference( AT_NbrFontType ) );
                }
            }

            DefaultFonts[ AT_NameFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_NameFontType );
            if ( DefaultFonts[ AT_NameFontType ].IsOk( ) )
            {
                if ( IsNodeType( AT_Album ) )
                {
                    DefaultFonts[ AT_NameFontType ].Set( GetSettings( )->GetFontNdxPreference( AT_TextFontType ) );
                }
            }

            DefaultFonts[ AT_TextFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_TextFontType );
            if ( !DefaultFonts[ AT_TextFontType ].IsOk( ) )
            {
                if ( IsNodeType( AT_Album ) )
                {
                    DefaultFonts[ AT_TextFontType ].Set( GetSettings( )->GetFontNdxPreference( AT_TextFontType ) );
                }
            }

            DefaultFonts[ AT_TitleFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_TitleFontType );
            if ( !DefaultFonts[ AT_TitleFontType ].IsOk( ) )
            {
                if ( IsNodeType( AT_Album ) )
                {
                    DefaultFonts[ AT_TitleFontType ].Set( GetSettings( )->GetFontNdxPreference( Design::AT_TitleFontType ) );
                }
            }
        }
    }

    void Album::MakeAlbum( )
    {

        UpdateMinimumSize( );
        UpdateSizes( );
        UpdatePositions( );
    }

    void Album::MakePDFAlbum( )
    {
        MakeAlbum( );
        wxString outName = DrawPDF( );
    }

    void Album::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_OverSizePaper );
        SetAttribute( xmlNode, AT_PaperHeight );
        SetAttribute( xmlNode, AT_PaperWidth );
        SetAttribute( xmlNode, AT_PageWidth );
        SetAttribute( xmlNode, AT_PageHeight );
        SetAttribute( xmlNode, AT_TopMargin );
        SetAttribute( xmlNode, AT_BottomMargin );
        SetAttribute( xmlNode, AT_RightMargin );
        SetAttribute( xmlNode, AT_LeftMargin );
        SetAttribute( xmlNode, AT_BorderFileName );
        SetAttribute( xmlNode, AT_BorderSize );
        SetAttribute( xmlNode, AT_FontType );
        SetAttribute( xmlNode, AT_NativeFontString );
        SetAttribute( xmlNode, AT_FontColor );

        SaveFonts( xmlNode );
    }

    void Album::SaveFonts( wxXmlNode* parent )
    {
        if ( DefaultFonts[ AT_NbrFontType ].IsOk( ) || DefaultFonts[ AT_TextFontType ].IsOk( ) || DefaultFonts[ AT_TitleFontType ].IsOk( ) || DefaultFonts[ AT_NameFontType ].IsOk( ) )
        {
            wxXmlNode* fonts = Utils::NewNode( parent, "Fonts" );
            if ( fonts )
            {
                if ( DefaultFonts[ AT_NbrFontType ].IsOk( ) )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_NbrFontType, GetFontNdx( AT_NbrFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, DefaultFonts[ AT_NbrFontType ], Design::AT_NbrFontType );
                    }
                }
                if ( DefaultFonts[ AT_NameFontType ].IsOk( ) )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_NameFontType, GetFontNdx( AT_NameFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, DefaultFonts[ AT_NameFontType ], Design::AT_NameFontType );
                    }
                }
                if ( DefaultFonts[ AT_TextFontType ].IsOk( ) )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_TextFontType, GetFontNdx( AT_TextFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, DefaultFonts[ AT_TextFontType ], Design::AT_TextFontType );
                    }
                }
                if ( DefaultFonts[ AT_TitleFontType ].IsOk( ) )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_TitleFontType, GetFontNdx( AT_TitleFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, DefaultFonts[ AT_TitleFontType ], Design::AT_TitleFontType );
                    }
                }
            }
        }
    }

    void Album::SetBorderSize( wxString str ) { return SetAttrStr( AT_BorderSize, str ); };

    void Album::SetBorderFilename( wxString str ) { return SetAttrStr( AT_BorderFileName, str ); };

    void Album::SetBottomMargin( wxString str ) { return SetAttrStr( AT_BottomMargin, str ); };

    void Album::SetDocName( wxString str ) { return SetAttrStr( AT_Name, str ); };

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

    void Album::SetLeftMargin( wxString str ) { return SetAttrStr( AT_LeftMargin, str ); };

    void Album::SetPageHeight( wxString str ) { return SetAttrStr( AT_PageHeight, str ); };

    void Album::SetPageWidth( wxString str ) { return SetAttrStr( AT_PageWidth, str ); };

    void Album::SetPaperHeight( wxString str ) { return SetAttrStr( AT_PaperHeight, str ); };

    void Album::SetPaperWidth( wxString str ) { return SetAttrStr( AT_PaperWidth, str ); };


    void Album::SetRightMargin( wxString str ) { return SetAttrStr( AT_RightMargin, str ); };

    void Album::SetTopMargin( wxString str ) { return SetAttrStr( AT_TopMargin, str ); };

    void Album::SetFontNdx( FontUsageType fontType, int ndx )
    {
        DefaultFonts[ fontType ].Set( ndx );
    };


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
                    //page->SetBorder( m_border );
                    // the page frame takes into account the margins, the border is within this
                    page->SetXPos( GetLeftMargin( ) );
                    page->SetYPos( GetTopMargin( ) );
                    page->SetWidth( GetWidth( ) - GetRightMargin( ) - GetLeftMargin( ) );
                    page->SetHeight( GetHeight( ) - GetTopMargin( ) - GetBottomMargin( ) );
                    page->SetTopMargin( GetTopMargin( ) );
                    page->SetBottomMargin( GetBottomMargin( ) );
                    page->SetRightMargin( GetRightMargin( ) );
                    page->SetLeftMargin( GetLeftMargin( ) );
                    page->SetBorderSize( GetBorderSize( ) );
                    page->SetBorderFilename( GetBorderFileName( ) );
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

    NodeStatus Album::ValidateNode( )
    {
        NodeStatus status = AT_OK;
        if ( GetPageHeight( ) <= 0.0 )
        {
            // "Must define the page height.\n";
            status = AT_FATAL;
        }
        if ( GetPageWidth( ) <= 0.0 )
        {
            //   "Must define the page width.\n";
            status = AT_FATAL;
        }
        m_nodeValid = status;
        return status;
    }


}