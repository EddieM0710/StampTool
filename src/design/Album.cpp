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
 **************************************************/

 
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

#include "design/DesignData.h"
#include "design/TitlePage.h"
#include "design/Page.h"
#include "utils/XMLUtilities.h"
#include "utils/FontList.h"
#include "gui/DesignTreeCtrl.h"
#include "StampToolApp.h"


wxDECLARE_APP( StampToolApp );

namespace Design { 

    bool Album::UpdateMinimumSize( )
    { 

        // set known child values
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        { 
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            switch ( type )
            { 
            case AT_Page:
            { 
                // set the layout parameters into the child
                Page* page = ( Page* )GetDesignTreeCtrl( )->GetItemNode( childID );
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
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        return true;
    }

    void Album::UpdateSizes( )
    { 
        // go to the bottom of each child container object ( row, column, page )
        // and begin filling in position relative to the parent

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        { 
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );

            //  call each childs Design function
            child->UpdateSizes( );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }

    }

    void Album::UpdatePositions( )
    { 
        // go to the bottom of each child container object ( row, column, page )
        // and begin filling in position relative to the parent

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        { 
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );

            child->UpdatePositions( );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
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

    double Album::GetWidth( ) {  return GetAttrDbl( AT_PageWidth ); };
    double Album::GetPageWidth( ) {  return GetAttrDbl( AT_PageWidth ); };
    wxString Album::GetPageWidthStr( ) {  return GetAttrStr( AT_PageWidth ); };
    void Album::SetPageWidth( wxString str ) {  return SetAttrStr( AT_PageWidth, str ); };
    
    double Album::GetHeight( ) { return GetAttrDbl( AT_PageHeight ); };
    double Album::GetPageHeight( ) {   return GetAttrDbl( AT_PageHeight ); };
    wxString Album::GetPageHeightStr( ) {  return GetAttrStr( AT_PageHeight ); };
    void Album::SetPageHeight( wxString str ) {   return SetAttrStr( AT_PageHeight, str );  };

    double Album::GetTopMargin( ) {  return GetAttrDbl( AT_TopMargin ); };
    wxString Album::GetTopMarginStr( ) {  return GetAttrStr( AT_TopMargin ); };
    void Album::SetTopMargin( wxString str ) {  return SetAttrStr( AT_TopMargin, str );  };

    double Album::GetBottomMargin( ) {  return GetAttrDbl( AT_BottomMargin );  };
    wxString Album::GetBottomMarginStr( ) { return GetAttrStr( AT_BottomMargin ); };
    void Album::SetBottomMargin( wxString str ) {  return SetAttrStr( AT_BottomMargin, str ); };

    double Album::GetRightMargin( ) {  return GetAttrDbl( AT_RightMargin ); };
    wxString Album::GetRightMarginStr( ) {  return GetAttrStr( AT_RightMargin ); };
    void Album::SetRightMargin( wxString str ) {   return SetAttrStr( AT_RightMargin, str ); };

    double Album::GetLeftMargin( ) { return GetAttrDbl( AT_LeftMargin ); };
    wxString Album::GetLeftMarginStr( ) {  return GetAttrStr( AT_LeftMargin ); };
    void Album::SetLeftMargin( wxString str ) { return SetAttrStr( AT_LeftMargin, str ); };

    double Album::GetBorderSize( ) {return GetAttrDbl( AT_BorderSize ); };
    wxString Album::GetBorderSizeStr( ) {  return GetAttrStr( AT_BorderSize ); };
    void Album::SetBorderSize( wxString str ) {  return SetAttrStr( AT_BorderSize, str ); };
    
    wxString  Album::GetBorderFileName( ) { return GetAttrStr( AT_BorderFileName ); };

    wxString Album::GetDocName( ) { return  GetAttrStr( "Name" ); };
    void Album::SetDocName( wxString str ) {  return SetAttrStr( AT_Name, str ); };
    int Album::GetAppPrefTitleFontNdx ( ) { return GetSettings()->GetAppPrefTitleFontNdx( ); };
    int Album::GetAppPrefCatNbrFontNdx ( ) {  return GetSettings()->GetAppPrefCatNbrFontNdx( ); }
    int Album::GetAppPrefTextFontNdx ( ) { return GetSettings()->GetAppPrefTextFontNdx( ); }

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


    wxString Album::DrawPDF(  )
    {
         Design::InitDesignDefs( Design::DD_PDF );
        // The text:p, i.e., content holder, for this Page
        double width = GetAttrDbl( AT_PageWidth );
        double height = GetAttrDbl( AT_PageHeight );
        wxPdfDocument* pdfDoc = new wxPdfDocument( wxPORTRAIT, width, height);

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        { 
            int childType = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );

            pdfDoc->AddPage();
            // set the layout parameters into the child
            Page* page = ( Page* )GetDesignTreeCtrl( )->GetItemNode( childID );
            page->DrawPDF( pdfDoc, width, height );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie ); 
        }
 
        wxString docName = GetDocName();
        docName += ".pdf"; 
        wxFileName outFile( docName );
        outFile.MakeAbsolute();
        wxString fullPath = outFile.GetFullPath( );
        pdfDoc->SaveAsFile( fullPath );
        wxString txt = wxString::Format( "Generated %s.\n\n", fullPath );
        wxMessageDialog* dlg = new wxMessageDialog( 
                    wxGetApp( ).GetFrame( ), txt, 
                    wxT( "Pdf Generated" ), 
                    wxOK | wxCENTER );
                int rsp = dlg->ShowModal( );
        return docName;
    }
    
    void Album::MakeAlbum( )
    { 

        UpdateMinimumSize( );
        UpdateSizes( );
        UpdatePositions( );
    }

    void Album::MakePDFAlbum( )
    { 
        MakeAlbum();
        wxString outName = DrawPDF( );
    }

    void Album::Save( wxXmlNode* xmlNode )
    { 
        SetAttribute( xmlNode, AT_Name );
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
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        { 
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );

            child->DumpLayout( 0, 0 );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }
}