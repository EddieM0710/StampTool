/**
 * @file AlbumImagePanel.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/


 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Defs.h"
#include "AlbumImagePanel.h"
#include "design/DesignData.h"
#include "design/Album.h"
#include "design/DesignDefs.h"
#include "design/LayoutBase.h"
#include "utils/Project.h"
#include "wx/file.h"
#include "wx/filename.h"
#include "wx/graphics.h"
#include "wx/image.h"
#include <wx/treectrl.h>

#include "art/NotFound.xpm"
#include "design/LayoutBase.h"
#include "gui/DesignTreeCtrl.h"

/*
 * AlbumImagePanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( AlbumImagePanel, wxPanel )
; // Formatting silly business; The above macro screws up the formatter but the semicolon fixes it

/*
 * AlbumImagePanel event table definition
 */

BEGIN_EVENT_TABLE( AlbumImagePanel, wxPanel )

// AlbumImagePanel event table entries
EVT_PAINT( AlbumImagePanel::OnPaint )
EVT_CONTEXT_MENU( AlbumImagePanel::OnContextMenu )
EVT_MENU( ID_RESIZE, AlbumImagePanel::OnResize )
EVT_MENU( wxID_ZOOM_IN, AlbumImagePanel::OnZoom )
EVT_MENU( wxID_ZOOM_OUT, AlbumImagePanel::OnZoom )
EVT_MENU( wxID_ZOOM_100, AlbumImagePanel::OnZoom )
END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

/*
 * AlbumImagePanel constructors
 *
 **************************************************/

AlbumImagePanel::AlbumImagePanel( )
{
    Init( );
}

/*
 * AlbumImagePanel constructors
 *
 **************************************************/

AlbumImagePanel::AlbumImagePanel( wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * AlbumImagePanel creator
 *
 **************************************************/

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

/*
 * AlbumImagePanel destructor
 *
 **************************************************/

AlbumImagePanel::~AlbumImagePanel( )
{
    // AlbumImagePanel destruction
    // AlbumImagePanel destruction
}

/*
 * Member initialisation
 *
 **************************************************/

void AlbumImagePanel::Init( )
{
    wxRect displayPixels = wxGetClientDisplayRect( );
    wxSize displayMM = wxGetDisplaySize( );
    m_pixelsPerIn = ( displayPixels.GetWidth( ) * 25.4 ) / displayMM.GetWidth( );

    //   this->SetScrollbars(10,10,1000,1000);
     // AlbumImagePanel member initialisation
     // AlbumImagePanel member initialisation
}

/*
 * Control creation for AlbumImagePanel
 *
 **************************************************/

void AlbumImagePanel::CreateControls( )
{

}

/*
 * Should we show tooltips?
 *
 **************************************************/

bool AlbumImagePanel::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 *
 **************************************************/

wxBitmap AlbumImagePanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
     // AlbumImagePanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // AlbumImagePanel bitmap retrieval
}

/*
 * Get icon resources
 *
 **************************************************/

wxIcon AlbumImagePanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
     // AlbumImagePanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // AlbumImagePanel icon retrieval
}

/*
 * SetBitmap
 *
 **************************************************/

void AlbumImagePanel::DrawBitmap( )
{
    Design::Album* album = GetDesignData( )->GetAlbum( );
    //album->GetAttrDbl( Design::AT_Width );
    //wxSize ppi = wxGetDisplayPPI();
    //
    double width = album->GetAttrDbl( Design::AT_PageWidth );
    double height = album->GetAttrDbl( Design::AT_PageHeight );

    std::cout << "Bitmap MM " << width << "  " << height << "\n";
  
    width = width*Design::PpMM.x * 2;
    height = height*Design::PpMM.y;
    
    std::cout << "Bitmap pixels " << width << "  " << height << "\n";

    wxBitmap* bitmap = new wxBitmap( width, height );
    m_bitmap = *bitmap;
    wxMemoryDC dc;
    DoPrepareDC( dc );
    //dc.SetMapMode( wxMM_METRIC );
    dc.SelectObject( m_bitmap );
    dc.Clear( );

    Design::LayoutBase* pageNode = Design::GetSelectedNodePage( );
    if ( pageNode )
    {
        pageNode->draw( dc, album->GetAttrDbl(Design::AT_LeftMargin), album->GetAttrDbl(Design::AT_TopMargin) );
    }

    dc.SelectObject(wxNullBitmap);
    m_bitmap.SaveFile( "Test.jpg",wxBITMAP_TYPE_JPEG );
    //    m_bitmap = image;
    m_zoom = .4;

    int w = bitmap->GetWidth( ) * 2;
    int h = bitmap->GetHeight( ) * 2;

    /* init scrolled area size, scrolling speed, etc. */
    SetScrollbars( 1, 1, w, h, 0, 0 );

    // SetClientSize(m_bitmap.GetWidth(), m_bitmap.GetHeight());
    Refresh( );
    Show( );
}

/*
 * OnResize
 *
 **************************************************/

void AlbumImagePanel::OnResize( wxCommandEvent& WXUNUSED( event ) )
{
    wxImage img( m_bitmap.ConvertToImage( ) );

    const wxSize size = GetClientSize( );
    img.Rescale( size.x, size.y, wxIMAGE_QUALITY_HIGH );
    m_bitmap = wxBitmap( img );
}

/*
 * SetZoom
 *
 **************************************************/

void AlbumImagePanel::SetZoom( double zoom )
{
    m_zoom = zoom;
    Refresh( );
}

/*
 * OnZoom
 *
 **************************************************/

void AlbumImagePanel::OnZoom( wxCommandEvent& event )
{
    if ( event.GetId( ) == wxID_ZOOM_IN )
        m_zoom *= 1.2;
    else if ( event.GetId( ) == wxID_ZOOM_OUT )
        m_zoom /= 1.2;
    else // wxID_ZOOM_100
        m_zoom = .4;
    Refresh( );
}

void AlbumImagePanel::Draw( wxDC& dc, Design::LayoutBase* node, wxPoint pt )
{
    wxPoint newPoint( pt.x + node->GetXPos( ), pt.y + node->GetYPos( ) );
    wxRect rect( pt.x, pt.y, node->GetWidth( ), node->GetHeight( ) );
    dc.DrawRectangle( rect );

    wxTreeItemIdValue cookie;
    wxTreeItemId nodeID = node->GetTreeItemId( );
    wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( nodeID, cookie );
    while ( childID.IsOk( ) )
    {
        Design::LayoutBase* child = ( Design::LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );
        Draw( dc, child, newPoint );
        childID = GetDesignTreeCtrl( )->GetNextChild( nodeID, cookie );
    }
}
/*
 * wxEVT_PAINT event handler for ID_ALBUMIMAGEPANEL
 *
 **************************************************/

void AlbumImagePanel::OnPaint( wxPaintEvent& event )
{
    wxPaintDC dc( this );
    DoPrepareDC( dc );
    dc.SetMapMode( wxMM_METRIC );
    dc.Clear( );


    int width = 8.5*25.4;
    int height = 11*25.4;


    /* init scrolled area size, scrolling speed, etc. */
 //   SetScrollbars( 1, 1, width*2, height*2, 0, 0 );

    const wxSize size = GetClientSize( );
    double scale = 1.;
    if ( m_bitmap.IsOk( ) )
    {
        int width = m_bitmap.GetWidth( );
        int height = m_bitmap.GetHeight( );
        if ( size.x < width )
        {
            scale = ( double )size.x / ( double )width;
        }
        if ( size.y < ( height * scale ) )
        {
            scale = ( double )size.y / ( ( double )height * scale ) * scale;
        }

        dc.SetUserScale( scale * m_zoom, scale * m_zoom );

        dc.DrawBitmap( m_bitmap, 0, 0,
            // dc.DeviceToLogicalX((size.x - m_zoom*scale *
            // m_bitmap.GetWidth()) / 2), dc.DeviceToLogicalY((size.y -
            // m_zoom*scale * m_bitmap.GetHeight()) / 2),
            true /* use mask */
        );
    }
}

wxRealPoint AlbumImagePanel::GetTextExtent( wxString text )
{
    wxClientDC dc( this );
    DoPrepareDC( dc );
    wxSize size = dc.GetTextExtent( text );
    wxRealPoint titleSize;
    titleSize.x = size.x/Design::PpMM.x;
    titleSize.y = size.y/Design::PpMM.y;
    return titleSize;
}
/*
 * wxEVT_CONTEXT_MENU event handler for ID_ALBUMIMAGEPANEL
 *
 **************************************************/

void AlbumImagePanel::OnContextMenu( wxContextMenuEvent& event )
{
    wxPoint screenpt = event.GetPosition( );
    wxPoint clientpt = ScreenToClient( clientpt );

    // wxLogMessage("OnItemMenu for item \"%s\" at screen coords (%i, %i)",
    //              item ? item->GetDesc() : wxString("unknown"), screenpt.x,
    //              screenpt.y);

    wxMenu menu( "Image Menu" );

    menu.Append( ID_RESIZE, "&Fit to window\tCtrl-F" );
    menu.Append( wxID_ZOOM_IN, "Zoom &in\tCtrl-+" );
    menu.Append( wxID_ZOOM_OUT, "Zoom &out\tCtrl--" );
    menu.Append( wxID_ZOOM_100, "Reset zoom to &100%\tCtrl-1" );
    menu.AppendSeparator( );
    menu.Append( ID_ROTATE_LEFT, "Rotate &left\tCtrl-L" );
    menu.Append( ID_ROTATE_RIGHT, "Rotate &right\tCtrl-R" );

    PopupMenu( &menu );
    event.Skip( );

    // wxEVT_CONTEXT_MENU event handler for ID_ALBUMIMAGEPANEL in AlbumImagePanel.
   // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_CONTEXT_MENU event handler for ID_ALBUMIMAGEPANEL in AlbumImagePanel.
}


