/**
 * @file ImageGalleryPanel.cpp
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
#include <wx/dcbuffer.h>

#include "Defs.h"
#include "design/DesignDefs.h"
 //#include "gui/AppData.h"
#include "gui/ImageGalleryPanel.h"
#include "art/NotFound.xpm"
#include "catalog/CatalogVolume.h"
#include "gui/CatalogTreeCtrl.h"
#include "utils/Project.h"

#include "wx/wfstream.h"
#include <wx/datstrm.h>
#include <wx/mstream.h>
#include <wx/log.h>


IMPLEMENT_DYNAMIC_CLASS( ImageGalleryPanel, wxScrolledWindow )


BEGIN_EVENT_TABLE( ImageGalleryPanel, wxScrolledWindow )

// ImageGalleryPanel event table entries
//EVT_PAINT( ImageGalleryPanel::OnPaint )
EVT_CONTEXT_MENU( ImageGalleryPanel::OnContextMenu )
EVT_MENU( wxID_ZOOM_IN, ImageGalleryPanel::OnZoom )
EVT_MENU( wxID_ZOOM_OUT, ImageGalleryPanel::OnZoom )
EVT_MENU( wxID_ZOOM_100, ImageGalleryPanel::OnZoom )
END_EVENT_TABLE( )



bool once = true;
//-------

ImageGalleryPanel::ImageGalleryPanel( )
{
    Init( );
}

//-------

ImageGalleryPanel::ImageGalleryPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style )
{
    Init( );
    m_scrolledId = id;
    Create( parent, id, pos, size, style );
}

//----------------

bool ImageGalleryPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style )
{
    // ImageGalleryPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxScrolledWindow::Create( parent, id, pos, size, style );
    SetBackgroundStyle( wxBG_STYLE_PAINT );
    CreateControls( );
    Centre( );
    // ImageGalleryPanel creation
    return true;
}

//-------

ImageGalleryPanel::~ImageGalleryPanel( )
{

}

//-------

void ImageGalleryPanel::Clear( )
{
    m_zoom = .9;
}

//-------

void ImageGalleryPanel::Init( )
{

}

//-------

void ImageGalleryPanel::CreateControls( )
{
    ImageGalleryPanel* thePanel = this;


    // wxBoxSizer* verticalSizer = new wxBoxSizer( wxVERTICAL );
    // thePanel->SetSizer( verticalSizer );

     // wxBoxSizer* horizontalSizer = new wxBoxSizer( wxHORIZONTAL );
     // verticalSizer->Add( horizontalSizer, 1, wxGROW | wxALL, 5 );

    m_scrolledPanel = this;
    // new wxScrolledWindow( thePanel,
    //     ID_IMAGEALLERYPANEL, wxDefaultPosition,
    //     wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL | wxHSCROLL | wxVSCROLL | wxALWAYS_SHOW_SB );
    // horizontalSizer->Add( m_scrolledPanel, 1, wxGROW | wxALL, 5 );
    // //  m_scrolledPanel->SetClientSize( 8000, 8000 );
    SetScrollbars( 10, 10, 20, 20 );
    Connect( m_scrolledId, wxEVT_PAINT, wxPaintEventHandler( ImageGalleryPanel::OnPaint ), NULL, this );
}

//-------

bool ImageGalleryPanel::ShowToolTips( )
{
    return true;
}

//-------

void ImageGalleryPanel::SetBitmap( wxDC& dc, wxString filename, int& row, int& col )
{
    wxImage image;
    if ( filename.IsEmpty( ) )
    {
        return;
        //image = wxImage( NotFound );
    }
    else
    {
        //wxFileName fn( filename );
        wxString str = GetProject( )->GetImageFullPath( filename );

        if ( !GetProject( )->ImageExists( str ) )
        {
            return;
            //image = wxImage( NotFound );
        }
        else
        {
            image = wxImage( str );

            if ( !image.IsOk( ) )
            {
                return;
                //image = wxImage( NotFound );
            }
        }
    }

    // m_bitmap = image;
    m_zoom = .9;

    double cellWidth = 1.5 * 25.4;
    double cellHeight = 1.5 * 25.4;

    double scale = 1;
    if ( image.GetWidth( ) > image.GetHeight( ) )
    {
        scale = cellWidth / image.GetWidth( );
    }
    else
    {
        scale = cellHeight / image.GetHeight( );
    }

    DrawImage( dc, image,
        col * cellWidth * m_zoom, row * cellHeight * m_zoom,
        image.GetWidth( ) * scale * m_zoom, image.GetHeight( ) * scale * m_zoom );

    col++;
    if ( col > 7 )
    {
        col = 0;
        row++;
    }

}

//-------

void ImageGalleryPanel::OnResize( wxCommandEvent& WXUNUSED( event ) )
{
    wxImage img( m_bitmap.ConvertToImage( ) );

    const wxSize size = GetClientSize( );
    img.Rescale( size.x, size.y, wxIMAGE_QUALITY_HIGH );
    m_bitmap = wxBitmap( img );
}

//-------

void ImageGalleryPanel::SetZoom( double zoom )
{
    m_zoom = zoom;
    Refresh( );
}

//-------


void ImageGalleryPanel::OnZoom( wxCommandEvent& event )
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


void ImageGalleryPanel::OnPaint( wxPaintEvent& event )
{
    // if ( m_galleryBmp )
    // {
    wxPaintDC dc( this );//wxDynamicCast( event.GetEventObject( ), wxWindow ) );
    // wxPaintDC dc( m_scrolledPanel );
    DoPrepareDC( dc );

    dc.Clear( );

    const wxSize size = GetClientSize( );

    Design::InitDesignDefs( Design::DD_Display );

    dc.SetUserScale( m_zoom, m_zoom );
    if ( once )
    {
        //  m_scrolledPanel->SetClientSize( 10 * 1.5 * 25.4, 10 * 1.5 * 25.4 );
        m_scrolledPanel->SetScrollbars( 10, 10, 600, 600 );
        once = false;
        // 
    }
    //dc.DrawBitmap( *m_galleryBmp, wxPoint( 0, 0 ) );
    DrawGallery( dc );
    // }
}

void ImageGalleryPanel::DrawBitmap( )
{
    wxBitmap bmp;

    if ( m_galleryBmp )
    {
        delete m_galleryBmp;
    }
    m_galleryBmp = new wxBitmap( );
    int nbrEntryTypes = GetCatalogData( )->GetCatalogTreeCtrl( )->GetNbrEntryTypes( );

    double nbrRows = nbrEntryTypes / 8.;
    nbrRows = ceil( nbrRows );

    double cellWidth = 1.5 * 25.4;
    double cellHeight = 1.5 * 25.4;

    wxSize size( cellWidth * 8 * GetDPIScaleFactor( ), cellHeight * nbrRows * GetDPIScaleFactor( ) );
    m_galleryBmp->CreateWithDIPSize( size, GetDPIScaleFactor( ) );
    {
        wxMemoryDC memdc( *m_galleryBmp );
        DrawGallery( memdc );
    }
}


void ImageGalleryPanel::DrawStamp( wxDC& dc, wxTreeItemId child, int& row, int& col )
{
    CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetCatalogData( )->GetCatalogTreeCtrl( )->GetItemData( child );
    Catalog::CatalogBaseType type = data->GetType( );
    // std::cout << Catalog::CatalogBaseNames[ type ] << " \n";
    if ( type == Catalog::NT_Entry )
    {
        wxXmlNode* node = data->GetNodeElement( );
        Catalog::Entry stamp( node );
        wxString imageFile = stamp.FindImageName( );
        SetBitmap( dc, imageFile, row, col );

    }
}
//-------
void ImageGalleryPanel::DrawGallery( wxDC& dc, wxTreeItemId node, int& row, int& col )
{
    // std::cout << "DrawGallery child " << row << " " << col << "\n";
    DrawStamp( dc, node, row, col );

    if ( row > 8 )return;
    wxTreeItemIdValue cookie;
    int count = 0;
    wxTreeItemId child = GetCatalogData( )->GetCatalogTreeCtrl( )->GetFirstChild( node, cookie );
    while ( child.IsOk( ) )
    {
        count++;
        //     std::cout << count << "\n";

        DrawGallery( dc, child, row, col );
        if ( row > 8 )return;
        child = GetCatalogData( )->GetCatalogTreeCtrl( )->GetNextChild( node, cookie );
    }


}
//-------
void ImageGalleryPanel::DrawGallery( wxDC& dc )
{
    //  std::cout << "DrawGallery Root\n";

    wxTreeItemId child = GetCatalogData( )->GetCatalogTreeCtrl( )->GetRootItem( );
    int row = 0;
    int col = 0;
    DrawGallery( dc, child, row, col );
    //  SetScrollbars( 1, 1, row * 1.5 * 25.4, col * 1.5 * 25.4, 0, 0 );

    //  SetClientSize( row * 1.5 * 25.4, col * 1.5 * 25.4 );
      //Refresh( );
        //  Show( );
}
//-------


void ImageGalleryPanel::OnContextMenu( wxContextMenuEvent& event )
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
