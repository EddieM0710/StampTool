/**
 * @file ImagePanel.cpp
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

#include "Defs.h"
#include "design/DesignDefs.h"
 //#include "gui/AppData.h"
#include "gui/ImagePanel.h"
#include "art/NotFound.xpm"
#include "catalog/CatalogVolume.h"
#include "utils/Project.h"

#include "wx/wfstream.h"
#include <wx/datstrm.h>
#include <wx/mstream.h>
#include <wx/log.h>


IMPLEMENT_DYNAMIC_CLASS( ImagePanel, wxPanel )


BEGIN_EVENT_TABLE( ImagePanel, wxPanel )

// ImagePanel event table entries
EVT_PAINT( ImagePanel::OnPaint )
EVT_CONTEXT_MENU( ImagePanel::OnContextMenu )
EVT_MENU( wxID_ZOOM_IN, ImagePanel::OnZoom )
EVT_MENU( wxID_ZOOM_OUT, ImagePanel::OnZoom )
EVT_MENU( wxID_ZOOM_100, ImagePanel::OnZoom )
END_EVENT_TABLE( )

//-------

ImagePanel::ImagePanel( )
{
    Init( );
}

//-------

ImagePanel::ImagePanel( wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

//----------------

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

//-------

ImagePanel::~ImagePanel( )
{

}

//-------

void ImagePanel::Clear( )
{
    m_zoom = .9;
}

//-------

void ImagePanel::Init( )
{

}

//-------

void ImagePanel::CreateControls( )
{

}

//-------

bool ImagePanel::ShowToolTips( )
{
    return true;
}

//-------

void ImagePanel::SetBitmap( wxString filename )
{
    wxImage image;
    if ( filename.IsEmpty( ) )
    {
        image = wxImage( NotFound );
    }
    else
    {
        //wxFileName fn( filename );
        wxString str = GetProject( )->GetImageFullPath( filename );

        if ( !GetProject( )->ImageExists( str ) )
        {
            image = wxImage( NotFound );
        }
        else
        {
            image = wxImage( str );

            if ( !image.IsOk( ) )
            {
                image = wxImage( NotFound );
            }
        }
    }

    m_bitmap = image;
    m_zoom = .9;

    int w = image.GetWidth( ) * 2;
    int h = image.GetHeight( ) * 2;

    /* init scrolled area size, scrolling speed, etc. */
    SetScrollbars( 1, 1, w, h, 0, 0 );

    // SetClientSize( m_bitmap.GetWidth( ), m_bitmap.GetHeight( ) );
    Refresh( );
    Show( );
}

//-------

void ImagePanel::OnResize( wxCommandEvent& WXUNUSED( event ) )
{
    wxImage img( m_bitmap.ConvertToImage( ) );

    const wxSize size = GetClientSize( );
    img.Rescale( size.x, size.y, wxIMAGE_QUALITY_HIGH );
    m_bitmap = wxBitmap( img );
}

//-------

void ImagePanel::SetZoom( double zoom )
{
    m_zoom = zoom;
    Refresh( );
}

//-------


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

//-------


void ImagePanel::OnPaint( wxPaintEvent& event )
{
    wxPaintDC dc( this );
    DoPrepareDC( dc );

    dc.Clear( );

    Design::InitDesignDefs( Design::DD_Display );

    const wxSize size = GetClientSize( );
    double scale = 1.;
    int width = m_bitmap.GetWidth( );
    int height = m_bitmap.GetHeight( );
    if ( size.x < width )
    {
        scale = ( double ) size.x / ( double ) width;
    }
    if ( size.y < ( height * scale ) )
    {
        scale = ( double ) size.y / ( ( double ) height * scale ) * scale;
    }

    dc.SetUserScale( scale * m_zoom, scale * m_zoom );
    // GetAlbumImagePanel( )->Refresh( );

    dc.DrawBitmap( m_bitmap, 0, 0,
        // dc.DeviceToLogicalX( ( size.x - m_zoom*scale *
        // m_bitmap.GetWidth( ) ) / 2 ), dc.DeviceToLogicalY( ( size.y -
        // m_zoom*scale * m_bitmap.GetHeight( ) ) / 2 ), 
        true /* use mask */
    );


}

//-------


void ImagePanel::OnContextMenu( wxContextMenuEvent& event )
{
    wxPoint screenpt = event.GetPosition( );
    wxPoint clientpt = ScreenToClient( clientpt );


    wxMenu menu( "Image Menu" );

    //menu.Append( ID_RESIZE, "&Fit to window\tCtrl-F" );
    menu.Append( wxID_ZOOM_IN, "Zoom &in\tCtrl-+" );
    menu.Append( wxID_ZOOM_OUT, "Zoom &out\tCtrl--" );
    menu.Append( wxID_ZOOM_100, "Reset zoom to &100%\tCtrl-1" );
    menu.AppendSeparator( );
    //menu.Append( ID_ROTATE_LEFT, "Rotate &left\tCtrl-L" );
    //menu.Append( ID_ROTATE_RIGHT, "Rotate &right\tCtrl-R" );

    PopupMenu( &menu );
    event.Skip( );
}

//-------
