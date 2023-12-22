/**
 * @file AlbumImagePanel.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
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

#include "wx/file.h"
#include "wx/filename.h"
#include "wx/graphics.h"
#include "wx/image.h"
#include <wx/treectrl.h>
#include <wx/pdfdc.h>
#include <wx/pdfdocument.h>

#include "Defs.h"
#include "AlbumImagePanel.h"
#include "design/AlbumVolume.h"
#include "design/Album.h"
#include "design/Page.h"
#include "design/DesignDefs.h"
#include "design/LayoutBase.h"
#include "design/LayoutBase.h"
#include "utils/Project.h"

#include "art/NotFound.xpm"
#include "gui/AlbumTreeCtrl.h"
#include "gui/GuiUtils.h"
#include <wx/tokenzr.h>
#include <wx/display.h>
IMPLEMENT_DYNAMIC_CLASS( AlbumImagePanel, wxPanel )

BEGIN_EVENT_TABLE( AlbumImagePanel, wxPanel )
EVT_PAINT( AlbumImagePanel::OnPaint )
EVT_LEFT_DOWN( AlbumImagePanel::OnLeftDown )
EVT_CONTEXT_MENU( AlbumImagePanel::OnContextMenu )
//EVT_MENU( ID_RESIZE, AlbumImagePanel::OnResize )
// EVT_MENU( wxID_ZOOM_IN, AlbumImagePanel::OnZoom )
// EVT_MENU( wxID_ZOOM_OUT, AlbumImagePanel::OnZoom )
// EVT_MENU( wxID_ZOOM_100, AlbumImagePanel::OnZoom )
// EVT_MENU( AlbumImagePanel_DeleteItem, AlbumImagePanel::OnDeleteItem )
// EVT_MENU( AlbumImagePanel_EditDetails, AlbumImagePanel::OnEditDetails )
END_EVENT_TABLE( )

//--------------

AlbumImagePanel::AlbumImagePanel( )
{
    Init( );
}

//--------------

AlbumImagePanel::AlbumImagePanel( wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

//--------------

AlbumImagePanel::~AlbumImagePanel( )
{
}

//--------------

void AlbumImagePanel::Clear( )
{
}

//--------------

bool AlbumImagePanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style )
{
    // AlbumImagePanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxScrolledWindow::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
    // AlbumImagePanel creation
    return true;
}

//--------------

void AlbumImagePanel::CreateControls( )
{
    m_once = false;
    m_zoom = .4;
    EnableScrolling( true, true );
    Refresh( );
}

//--------------

// void AlbumImagePanel::Draw( wxDC& dc, Design::LayoutBase* node, wxPoint pt )
// {
//     wxPoint newPoint( pt.x + node->GetXPos( ), pt.y + node->GetYPos( ) );
//     wxRect rect( pt.x, pt.y, node->GetWidth( ), node->GetHeight( ) );
//     dc.DrawRectangle( rect );
//     wxTreeItemIdValue cookie;
//     wxTreeItemId nodeID = node->GetTreeItemId( );
//     wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( nodeID, cookie );
//     while ( childID.IsOk( ) )
//     {
//         Design::LayoutBase* child = ( Design::LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
//         Draw( dc, child, newPoint );
//         childID = GetAlbumTreeCtrl( )->GetNextChild( nodeID, cookie );
//     }
// }

//--------------

wxSize AlbumImagePanel::GetLogicalTextExtent( wxString text, wxFont font )
{
    wxClientDC dc( this );
    dc.SetMapMode( wxMM_TEXT );
    DoPrepareDC( dc );
    dc.SetUserScale( m_userScale, m_userScale );
    dc.SetFont( font );
    wxSize size = dc.GetMultiLineTextExtent( text );

    return size;
}

//--------------

void AlbumImagePanel::Init( )
{
}

//--------------

wxSize  AlbumImagePanel::MakeMultiLine( wxString& text, wxFont font, double width )
{
    wxClientDC  dc( this );
    //DoPrepareDC( dc );
    dc.SetMapMode( wxMM_METRIC );
    int point = font.GetPointSize( );
    //dc.SetUserScale( m_userScale, m_userScale );
    dc.SetFont( font );
    wxString str = text;
    wxSize sizea = dc.GetSize( );
    wxSize sizeb = dc.GetSizeMM( );
    double scaleb = ( double ) sizea.y / ( double ) sizeb.y;

    //adjust the width down just a bit to allow for text conversion
    wxDisplay display( this );
    wxSize scale = display.GetPPI( ) / 25.4;
    double widthDev = dc.LogicalToDeviceXRel( width );
    // width = ( double ) width * scaleb;
    str.Trim( );
    str.Trim( false );
    int len = str.length( );
    wxArrayString words = wxStringTokenize( str, " ", wxTOKEN_RET_DELIMS );

    wxCoord w, h;
    wxArrayString lines;
    lines.Add( "" );
    int currWidth = 0;
    int currLine = 0;
    for ( size_t k = 0; k < words.GetCount( ); k++ )
    {
        dc.GetTextExtent( words[ k ], &w, &h );
        int newWidth = currWidth + w;
        // if over runs width
        if ( newWidth > widthDev )
        {
            if ( currWidth <= 0 )
            {
                // currently nothing in this line
                // add this word to it
                lines[ currLine ] = words[ k ];

                // close this line and go to next
                lines.Add( "" );
                currLine++;
                currWidth = 0;
                newWidth = 0;
            }
            else
            {
                // we over ran length so close out the line
                lines.Add( "" );
                currLine++;
                currWidth = 0;
                // and add the word to the next       
                lines[ currLine ] = lines[ currLine ] + words[ k ];
                currWidth = w;
            }
        }
        else
        {
            // didn't over run so just add the word to the line and keep going
            lines[ currLine ] = lines[ currLine ] + words[ k ];
            currWidth = newWidth;
        }
    }
    wxString output;
    output = lines[ 0 ];
    for ( size_t k = 1; k < lines.GetCount( ); k++ )
    {
        int lastChar = output.Length( );
        output.SetChar( lastChar - 1, '\n' );
        output += lines[ k ];
    }
    text = output;
    wxSize outSize = dc.GetMultiLineTextExtent( text );
    outSize = dc.DeviceToLogicalRel( outSize );
    return outSize;

}

//--------------

void AlbumImagePanel::OnContextMenu( wxContextMenuEvent& event )
{
    wxPoint screenpt = event.GetPosition( );
    wxPoint clientpt = ScreenToClient( screenpt );

    Design::LayoutBase* pageNode = Design::GetSelectedNodePage( );

    wxString name = "";
    Design::AlbumBaseType type;
    wxTreeItemId newID = 0;
    if ( pageNode )
    {
        Design::LayoutBase* item = pageNode->FindObjectByPos( clientpt.x, clientpt.y );
        if ( item )
        {
            type = item->GetNodeType( );
            name = Design::AlbumBaseNames[ type ];

            newID = item->GetTreeItemId( );
            GetAlbumTreeCtrl( )->SelectItem( newID );
        }
    }
    wxMenu menu( name );

    //menu.Append( ID_RESIZE, "&Fit to window\tCtrl-F" );
    menu.Append( wxID_ZOOM_IN, "Zoom &in\tCtrl-+" );
    menu.Append( wxID_ZOOM_OUT, "Zoom &out\tCtrl--" );
    menu.Append( wxID_ZOOM_100, "Reset zoom to &100%\tCtrl-1" );
    menu.AppendSeparator( );
    menu.Append( AlbumImagePanel_DeleteItem, "    Delete Item" );
    menu.Append( AlbumImagePanel_EditDetails, "    Edit Details" );

    // PopupMenu( &menu );


    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {
        case wxID_ZOOM_IN:
        {
            m_zoom *= 1.2;
            Refresh( );
            break;
        }
        case wxID_ZOOM_OUT:
        {
            m_zoom /= 1.2;
            Refresh( );
            break;
        }
        case wxID_ZOOM_100:
        {

            m_zoom = .4;
            Refresh( );
            break;
        }
        case AlbumImagePanel_DeleteItem:
        {
            GetAlbumTreeCtrl( )->OnDeleteItem( newID );
            break;
        }

        // case AlbumImagePanel_EditDetails:
        // {
        //     if ( newID && ( type == Design::AT_Stamp ) )
        //     {
        //         GetAlbumTreeCtrl( )->ShowStampDetails( newID );
        //         GetAlbumVolume( )->MakePage( ( Design::LayoutBase* ) pageNode );
        //     }
        //     else if ( type == Design::AT_Row )
        //     {
        //         GetAlbumTreeCtrl( )->ShowRowDetails( newID, pageNode );
        //         GetAlbumVolume( )->MakePage( ( Design::LayoutBase* ) pageNode );
        //     }
        //     else if ( type == Design::AT_Col )
        //     {
        //         GetAlbumTreeCtrl( )->ShowColDetails( newID, pageNode );
        //         GetAlbumVolume( )->MakePage( ( Design::LayoutBase* ) pageNode );
        //     }
        //     else if ( type == Design::AT_Page )
        //     {
        //         GetAlbumTreeCtrl( )->ShowPageDetails( newID, pageNode );
        //         GetAlbumVolume( )->MakePage( ( Design::LayoutBase* ) pageNode );
        //     }
        //     else if ( type == Design::AT_Album )
        //     {
        //         GetAlbumTreeCtrl( )->ShowAlbumDetails( newID, pageNode );
        //         GetAlbumVolume( )->MakePage( ( Design::LayoutBase* ) pageNode );
        //     }
        //     break;
        //     break;
        // }
    }
    event.Skip( );

}

//--------------

void AlbumImagePanel::OnDeleteItem( )
{
}

//--------------

void AlbumImagePanel::OnEditDetails( )
{
    //     wxPoint clientpt = event.;

   //  Design::LayoutBase* pageNode = Design::GetSelectedNodePage( );

}

//--------------

void AlbumImagePanel::OnLeftDown( wxMouseEvent& event )
{
    wxPoint clientpt = event.GetPosition( );

    Design::LayoutBase* pageNode = Design::GetSelectedNodePage( );

    if ( pageNode )
    {
        Design::LayoutBase* item = pageNode->FindObjectByPos( clientpt.x, clientpt.y );
        if ( item )
        {
            wxTreeItemId newID = item->GetTreeItemId( );
            GetAlbumTreeCtrl( )->SelectItem( newID );
        }
    }

    event.Skip( );

}

//--------------

void AlbumImagePanel::OnPaint( wxPaintEvent& event )
{
    Design::AlbumVolume* albumVolume = GetAlbumVolume( );
    if ( albumVolume )
    {
        wxPaintDC dc( this );
        DoPrepareDC( dc );
        dc.SetMapMode( wxMM_METRIC );
        dc.Clear( );

        Design::Album* album = GetAlbumVolume( )->GetAlbum( );
        if ( album )
        {

            Design::Page* pageNode = ( Design::Page* ) Design::GetSelectedNodePage( );
            if ( pageNode && pageNode->IsStatusOK( ) )
            {

                double width;
                double height;
                if ( Design::IsPortrait( pageNode->Orientation( ) ) )
                {
                    width = album->AlbumPageDefaults( )->GetWidth( );
                    height = album->AlbumPageDefaults( )->GetHeight( );
                }
                else
                {
                    height = album->AlbumPageDefaults( )->GetWidth( );
                    width = album->AlbumPageDefaults( )->GetHeight( );
                }

                m_userScale = ( .5 - ( .4 - m_zoom ) );
                wxSize PPI = dc.GetPPI( );
                dc.SetUserScale( m_userScale, m_userScale );

                /* init scrolled area size, scrolling speed, etc. */
                if ( m_once == false )
                {
                    m_once = true;
                    SetScrollbars( 1, 1, 2 * width / m_userScale, 2 * height / m_userScale, 0, 0 );
                    EnableScrolling( true, true );
                }

                dc.SetPen( *wxRED_PEN );

                DrawRectangle( dc, 0, 0, width, height );

                dc.SetPen( *wxBLACK_PEN );
                // DrawRectangle( dc, 10, 10, 10, 10 );

                pageNode->Draw( dc, 0, 0 );
            }
        }
    }



}

//--------------

void AlbumImagePanel::OnResize( wxCommandEvent& WXUNUSED( event ) )
{
    wxImage img( m_bitmap.ConvertToImage( ) );

    const wxSize size = GetClientSize( );

    img.Rescale( size.x * Design::DeviceUnitsPerMM.x, size.y * Design::DeviceUnitsPerMM.y, wxIMAGE_QUALITY_HIGH );
    m_bitmap = wxBitmap( img );
}

//--------------

void AlbumImagePanel::SetZoom( double zoom )
{
    m_zoom = zoom;
    Refresh( );
}

//--------------

bool AlbumImagePanel::ShowToolTips( )
{
    return true;
}
