/**
 * @file ImagePanel.cpp
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
#include "ImagePanel.h"
//#include "Persistent.h"
#include "wx/file.h"
#include "wx/filename.h"
#include "wx/graphics.h"
#include "wx/image.h"
#include "art/NotFound.xpm"

/*
 * ImagePanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( ImagePanel, wxPanel )
; // Formatting silly business; The above macro screws up the formatter but the semicolon fixes it

/*
 * ImagePanel event table definition
 */

BEGIN_EVENT_TABLE( ImagePanel, wxPanel )

// ImagePanel event table entries
EVT_PAINT( ImagePanel::OnPaint )
EVT_CONTEXT_MENU( ImagePanel::OnContextMenu )
EVT_MENU( ID_RESIZE, ImagePanel::OnResize )
EVT_MENU( wxID_ZOOM_IN, ImagePanel::OnZoom )
EVT_MENU( wxID_ZOOM_OUT, ImagePanel::OnZoom )
EVT_MENU( wxID_ZOOM_100, ImagePanel::OnZoom )
END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

/*
 * ImagePanel constructors
 *
 **************************************************/

ImagePanel::ImagePanel( )
{
    Init( );
}

/*
 * ImagePanel constructors
 *
 **************************************************/

ImagePanel::ImagePanel( wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * ImagePanel creator
 *
 **************************************************/

bool ImagePanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style )
{
    // ImagePanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxScrolledWindow::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
    // ImagePanel creation
    return true;
}

/*
 * ImagePanel destructor
 *
 **************************************************/

ImagePanel::~ImagePanel( )
{
    // ImagePanel destruction
    // ImagePanel destruction
}

/*
 * Member initialisation
 *
 **************************************************/

void ImagePanel::Init( )
{
    //   this->SetScrollbars(10,10,1000,1000);
     // ImagePanel member initialisation
     // ImagePanel member initialisation
}

/*
 * Control creation for ImagePanel
 *
 **************************************************/

void ImagePanel::CreateControls( )
{

}

/*
 * Should we show tooltips?
 *
 **************************************************/

bool ImagePanel::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 *
 **************************************************/

wxBitmap ImagePanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
     // ImagePanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // ImagePanel bitmap retrieval
}

/*
 * Get icon resources
 *
 **************************************************/

wxIcon ImagePanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
     // ImagePanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // ImagePanel icon retrieval
}

/*
 * SetBitmap
 *
 **************************************************/

void ImagePanel::SetBitmap( wxString filename )
{
    wxImage image;
    if ( filename.IsEmpty( ) )
    {
        image = wxImage( NotFound );
    }
    else
    {
        wxFileName fn( filename );
        if ( !fn.FileExists( ) )
        {
            image = wxImage( NotFound );
        }
        else
        {
            if ( !image.CanRead( filename ) )
            {
                image = wxImage( NotFound );
            }
            else
            {
                image = wxImage(filename);
            }
        }
    }

    m_bitmap = image;
    m_zoom = .9;

    int w = image.GetWidth( )*2;
    int h = image.GetHeight( )*2;

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

void ImagePanel::OnResize( wxCommandEvent& WXUNUSED( event ) )
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

void ImagePanel::SetZoom( double zoom )
{
    m_zoom = zoom;
    Refresh( );
}

/*
 * OnZoom
 *
 **************************************************/

void ImagePanel::OnZoom( wxCommandEvent& event )
{
    if ( event.GetId( ) == wxID_ZOOM_IN )
        m_zoom *= 1.2;
    else if ( event.GetId( ) == wxID_ZOOM_OUT )
        m_zoom /= 1.2;
    else // wxID_ZOOM_100
        m_zoom = .9;
    Refresh( );
}


/*
 * wxEVT_PAINT event handler for ID_IMAGEPANEL
 *
 **************************************************/

void ImagePanel::OnPaint( wxPaintEvent& event )
{
    wxPaintDC dc( this );
    DoPrepareDC( dc );

    dc.Clear( );

    const wxSize size = GetClientSize( );
    double scale = 1.;
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


/*
 * wxEVT_CONTEXT_MENU event handler for ID_IMAGEPANEL
 *
 **************************************************/

void ImagePanel::OnContextMenu( wxContextMenuEvent& event )
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

    // wxEVT_CONTEXT_MENU event handler for ID_IMAGEPANEL in ImagePanel.
   // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_CONTEXT_MENU event handler for ID_IMAGEPANEL in ImagePanel.
}


