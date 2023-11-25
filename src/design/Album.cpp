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
 //#include "StampToolApp.h"

 //wxDECLARE_APP( StampToolApp );

namespace Design {

    Album::Album( wxXmlNode* node ) : AlbumBase( node )
    {
        SetNodeType( AT_Album );
        InitParameters( );

    }


    void Album::InitParameters( )
    {
        wxString orientation = GetDefaultOrientation( );
        if ( orientation.Cmp( OrientationStrings[ Design::AT_Portrait ] ) &&
            orientation.Cmp( OrientationStrings[ Design::AT_Landscape ] ) )
        {
            SetAttrStr( Design::AT_Orientation, OrientationStrings[ Design::AT_Portrait ] );
        }
        for ( int i = 0; i < Design::AT_NbrFontUsageTypes; i++ )
        {
            DefaultFonts[ i ] = -1;
        };
        if ( GetPaperWidth( ) <= 0 )
        {
            SetPaperWidth( "208.25" );
        }
        if ( GetPaperHeight( ) <= 0 )
        {
            SetPaperHeight( "269.5" );
        }

        if ( GetOverSizePaper( ) )
        {
            if ( GetPageWidth( ) <= 0 )
            {
                SetPageWidth( "208.25" );
            }
            if ( GetPageHeight( ) <= 0 )
            {
                SetPageHeight( "269.5" );
            }
        }
        if ( GetTopPageMargin( ) < 0 )
        {
            SetTopPageMargin( "12" );
        }
        if ( GetBottomPageMargin( ) < 0 )
        {
            SetBottomPageMargin( "12" );
        }
        if ( GetRightPageMargin( ) < 0 )
        {
            SetRightPageMargin( "12" );
        }
        if ( GetLeftPageMargin( ) < 0 )
        {
            SetLeftPageMargin( "12" );
        }


        if ( GetBorderFileName( ).IsEmpty( ) )
        {
            SetBorderFilename( "big_and_little_line.jpg" );
        }
        if ( GetBorderSize( ) < 0 )
        {
            SetBorderSize( "4" );
        }
        wxString location = GetStampNameLocation( );
        if ( location.Cmp( Design::StampNameLocationStrings[ AT_StampNameLocationTop ] ) &&
            location.Cmp( Design::StampNameLocationStrings[ AT_StampNameLocationBottom ] ) )
        {
            SetDefaultStampNameLocation( AT_StampNameLocationTop );
        }


    }
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

            // set the layout parameters into the child
            Page* page = ( Page* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            if ( Design::IsPortrait( page->GetOrientation( ) ) )
            {
                doc->AddPage( wxPORTRAIT );
                page->DrawPDF( doc, width, height );
            }
            else
            {
                doc->AddPage( wxLANDSCAPE, width, height );
                page->DrawPDF( doc, height, width );
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

    void Album::DumpFont( wxString Level )
    {

        int ndx = DefaultFonts[ AT_NbrFontType ];
        std::cout << Level << "CatNbr font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;

        ndx = DefaultFonts[ AT_TextFontType ];
        std::cout << Level << "Text font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;

        ndx = DefaultFonts[ AT_TitleFontType ];
        std::cout << Level << "Title font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;
    };

    void Album::DumpLayout( )
    {
        std::cout << "Album Parms w:" << GetAttrStr( AT_PageWidth )
            << " h:" << GetAttrStr( AT_PageHeight )
            << " tm:" << GetAttrStr( AT_TopPageMargin )
            << " bm:" << GetAttrStr( AT_BottomPageMargin )
            << " rm:" << GetAttrStr( AT_RightPageMargin )
            << " lm:" << GetAttrStr( AT_LeftPageMargin ) << "\n";

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

    double Album::GetBorderSize( ) {
        return GetAttrDbl( AT_BorderSize );
    };

    wxString Album::GetBorderSizeStr( ) {
        return GetAttrStr( AT_BorderSize );
    };

    wxString Album::GetBorderFileName( ) {
        return GetAttrStr( AT_BorderFileName );
    };

    double Album::GetBottomPageMargin( ) {
        return GetAttrDbl( AT_BottomPageMargin );
    };

    wxString Album::GetBottomPageMarginStr( ) {
        return GetAttrStr( AT_BottomPageMargin );
    };

    wxString Album::GetCatalog( ) {
        wxString cat = GetAttrStr( AT_Catalog );
        if ( cat.IsEmpty( ) )
        {
            cat = GetProject( )->GetProjectCatalogCode( );
        }
        return cat;
    };

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

    wxString Album::GetDefaultValStr( AlbumAttrType type )
    {
        if ( type == AT_SelvageHeight )
        {
            return  wxString::Format( "%4.1f", m_defaultSelvageHeight );
        }
        else if ( type == AT_SelvageWidth )
        {
            return   wxString::Format( "%4.1f", m_defaultSelvageWidth );
        }
        else if ( type == AT_MountAllowanceHeight )
        {
            return   wxString::Format( "%4.1f", m_defaultMountAllowanceHeight );
        }
        else if ( type == AT_MountAllowanceWidth )
        {
            return   wxString::Format( "%4.1f", m_defaultMountAllowanceWidth );
        }
        else if ( type == AT_Catalog )
        {
            return  GetCatalog( );
        }
        else
            return "";
    };

    double Album::GetDefaultVal( AlbumAttrType type )
    {
        if ( type == AT_SelvageHeight )
        {
            return m_defaultSelvageHeight;
        }
        else if ( type == AT_SelvageWidth )
        {
            return m_defaultSelvageWidth;
        }
        else if ( type == AT_MountAllowanceHeight )
        {
            return m_defaultMountAllowanceHeight;
        }
        else if ( type == AT_MountAllowanceWidth )
        {
            return m_defaultMountAllowanceWidth;
        }
        return 0;
    };


    wxString Album::GetDocName( ) {
        return  GetAttrStr( "Name" );
    };

    wxFont Album::GetFont( FontUsageType fontType )
    {
        return GetFontList( )->GetFont( GetFontNdx( fontType ) );
    };

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


    int Album::GetFontNdxPreference( FontUsageType fontType )
    {
        return GetSettings( )->GetFontNdxPreference( fontType );
    }


    double Album::GetLeftPageMargin( ) {
        return GetAttrDbl( AT_LeftPageMargin );
    };

    wxString Album::GetLeftPageMarginStr( ) {
        return GetAttrStr( AT_LeftPageMargin );
    };


    void Album::GetPageParameters( wxString& width,
        wxString& height,
        wxString& topPageMargin,
        wxString& bottomPageMargin,
        wxString& rightPageMargin,
        wxString& leftPageMargin )
    {
        width = GetAttrStr( AT_PageWidth );
        height = GetAttrStr( AT_PageHeight );
        topPageMargin = GetAttrStr( AT_TopPageMargin );
        bottomPageMargin = GetAttrStr( AT_BottomPageMargin );
        rightPageMargin = GetAttrStr( AT_RightPageMargin );
        leftPageMargin = GetAttrStr( AT_LeftPageMargin );
    };

    wxString Album::GetStampNameLocation( )
    {
        return GetAttrStr( AT_StampNameLocation );
    }

    StampNameLocation  Album::GetDefaultStampNameLocationType( )
    {
        StampNameLocation loc = FindStampLocationType( GetAttrStr( AT_StampNameLocation ) );
        if ( ( loc != AT_StampNameLocationBottom ) && ( loc != AT_StampNameLocationTop ) )
        {
            loc = AT_StampNameLocationTop;
            SetDefaultStampNameLocationType( loc );
        }
        return FindStampLocationType( GetAttrStr( AT_StampNameLocation ) );
    };


    // wxString Album::GetAlignmentMode( )
    // {
    //     return GetAttrStr( AT_StampAlignmentMode );
    // }


    Design::AlignmentMode  Album::GetAlignmentModeType( )
    {
        AlignmentMode loc = FindAlignmentModeType( GetAttrStr( AT_StampAlignmentMode ) );
        if ( ( loc != AlignBottom ) && ( loc != AlignMiddle ) && ( loc != AlignTop ) )
        {
            loc = AlignTop;
            SetAlignmentModeType( loc );
        }
        return FindAlignmentModeType( GetAttrStr( AT_StampAlignmentMode ) );
    };



    double Album::GetPageHeight( ) {
        return GetAttrDbl( AT_PageHeight );
    };

    double Album::GetHeight( ) {
        return GetPageHeight( );

    };
    wxString Album::GetPageHeightStr( ) {
        return GetAttrStr( AT_PageHeight );
    };

    double Album::GetPaperHeight( ) {
        return GetAttrDbl( AT_PaperHeight );
    };


    wxString Album::GetPaperHeightStr( ) {
        return GetAttrStr( AT_PaperHeight );
    };

    double Album::GetPaperWidth( ) {
        return GetAttrDbl( AT_PaperWidth );
    };

    wxString Album::GetPaperWidthStr( ) {
        return GetAttrStr( AT_PaperWidth );
    };


    double Album::GetPageWidth( ) {
        return GetAttrDbl( AT_PageWidth );
    };

    wxString Album::GetPageWidthStr( ) {
        return GetAttrStr( AT_PageWidth );
    };

    double Album::GetWidth( ) {
        return GetPageWidth( );
    };

    double Album::GetRightPageMargin( ) {
        return GetAttrDbl( AT_RightPageMargin );
    };

    wxString Album::GetRightPageMarginStr( ) {
        return GetAttrStr( AT_RightPageMargin );
    };

    double Album::GetTopPageMargin( ) {
        return GetAttrDbl( AT_TopPageMargin );
    };

    wxString Album::GetTopPageMarginStr( ) {
        return GetAttrStr( AT_TopPageMargin );
    };


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

    void Album::MakeAlbum( )
    {
        UpdateMinimumSize( );
        UpdateSizes( );
        UpdatePositions( );
    }

    void Album::MakeDefaultFont( FontUsageType fontType )
    {
        GetFontList( )->MakeDefault( DefaultFonts[ fontType ] );
    };

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
        SetAttribute( xmlNode, AT_TopPageMargin );
        SetAttribute( xmlNode, AT_BottomPageMargin );
        SetAttribute( xmlNode, AT_RightPageMargin );
        SetAttribute( xmlNode, AT_LeftPageMargin );
        SetAttribute( xmlNode, AT_BorderFileName );
        SetAttribute( xmlNode, AT_BorderSize );
        SetAttribute( xmlNode, AT_ShowCatNbr );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_SubTitle );
        SetAttribute( xmlNode, AT_GrayScaleImages );
        SetAttribute( xmlNode, AT_StampNameLocation );
        SetAttribute( xmlNode, AT_Orientation );
        SaveFonts( xmlNode );
    }

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

    void Album::SetBorderSize( wxString str ) {
        SetAttrStr( AT_BorderSize, str );
    };

    void Album::SetBorderFilename( wxString str ) {
        SetAttrStr( AT_BorderFileName, str );
    };

    void Album::SetBottomPageMargin( wxString str ) {
        SetAttrStr( AT_BottomPageMargin, str );
    };

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

    void Album::SetDocName( wxString str ) {
        SetAttrStr( AT_Name, str );
    };

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

    void Album::SetLeftPageMargin( wxString str ) {
        SetAttrStr( AT_LeftPageMargin, str );
    };

    void Album::SetPageHeight( wxString str ) {
        SetAttrStr( AT_PageHeight, str );
    };

    void Album::SetPageWidth( wxString str ) {
        SetAttrStr( AT_PageWidth, str );
    };

    void Album::SetPaperHeight( wxString str ) {
        SetAttrStr( AT_PaperHeight, str );
    };

    void Album::SetPaperWidth( wxString str ) {
        SetAttrStr( AT_PaperWidth, str );
    };


    void Album::SetRightPageMargin( wxString str ) {
        SetAttrStr( AT_RightPageMargin, str );
    };

    void Album::SetTopPageMargin( wxString str ) {
        SetAttrStr( AT_TopPageMargin, str );
    };

    void Album::SetDefaultStampNameLocation( StampNameLocation loc )
    {
        SetAttrStr( AT_StampNameLocation, StampNameLocationStrings[ loc ] );
    }
    void Album::SetDefaultStampNameLocationType( StampNameLocation loc )
    {
        if ( ( loc != AT_StampNameLocationBottom ) && ( loc != AT_StampNameLocationTop ) )
        {
            loc = AT_StampNameLocationTop;
        }
        SetAttrStr( AT_StampNameLocation, StampNameLocationStrings[ loc ] );
    };



    void Album::SetAlignmentMode( AlignmentMode loc )
    {
        SetAttrStr( AT_StampAlignmentMode, StampAlignmentModeStrings[ loc ] );
    }

    void Album::SetAlignmentModeType( AlignmentMode loc )
    {
        if ( ( loc != AlignBottom ) && ( loc != AlignTop ) )
        {
            loc = AlignTop;
        }
        SetAttrStr( AT_StampAlignmentMode, StampAlignmentModeStrings[ loc ] );
    };


    void Album::SetFontNdx( FontUsageType fontType, int ndx )
    {
        DefaultFonts[ fontType ] = ndx;
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

                    page->Init( );
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