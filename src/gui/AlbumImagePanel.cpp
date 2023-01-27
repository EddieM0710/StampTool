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
#include "gui/GuiUtils.h"

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
EVT_LEFT_DOWN( AlbumImagePanel::OnLeftDown )
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

}

/*
 * Control creation for AlbumImagePanel
 *
 **************************************************/

void AlbumImagePanel::CreateControls( )
{ 
    m_once = false;
    m_zoom = .4;
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

//std::cout << "OnPaint\n";
    Design::DesignData* designData = GetDesignData( );
    if ( designData )
    { 
        wxPaintDC dc( this );
        DoPrepareDC( dc );
        dc.SetMapMode( wxMM_METRIC );
        dc.Clear( );
        Design::InitDesignDefs( );

        Design::Album* album = GetDesignData( )->GetAlbum( );
        if ( album )
        { 
            double width = album->GetAttrDbl( Design::AT_PageWidth ) * Design::PpMM.x;
            double height = album->GetAttrDbl( Design::AT_PageHeight ) * Design::PpMM.y;

            /* init scrolled area size, scrolling speed, etc. */
            if ( m_once == false )
            { 
                m_once = true;
                SetScrollbars( Design::PpMM.x, Design::PpMM.y, width * 2, height * 2, 0, 0 );
            }
            const wxSize size = GetClientSize( );
            double scale = 1.;

            if ( size.x < width )
            { 
                scale = ( double )size.x / ( double )width;
            }
            //double scaledHeight = 
            if ( size.y < ( height * scale ) )
            { 
                scale = ( double )size.y / ( ( ( double )height * scale ) * scale );
            }

            dc.SetUserScale( scale * m_zoom, scale * m_zoom );
            //  int xScroll = -1*GetScrollPos( wxHORIZONTAL );
            //  int yScroll = -1*GetScrollPos( wxVERTICAL );
            //  dc.SetDeviceOrigin( xScroll/scale, yScroll/scale );

            dc.DrawRectangle( 0, 0, width, height );

            Design::LayoutBase* pageNode = Design::GetSelectedNodePage( );
            if ( pageNode && pageNode->IsStatusOK( ) )
            { 
                //pageNode->draw( dc, album->GetAttrDbl( Design::AT_LeftMargin ), album->GetAttrDbl( Design::AT_TopMargin ) );
                pageNode->draw( dc, 0, 0 );
            }
        }
    }
}





/*
 * wxEVT_RIGHT_DOWN event handler for ID_IMAGEPANEL
 */

void AlbumImagePanel::OnLeftDown( wxMouseEvent& event )
{ 
    // screenpt = event.GetLogicalPosition( );
    wxPoint //screenpt 
    clientpt = event.GetPosition( );
    //wxPoint clientpt = ScreenToClient( screenpt );

    Design::LayoutBase* pageNode = Design::GetSelectedNodePage( );

    if ( pageNode )
    { 
        Design::LayoutBase* item = pageNode->FindObjectByPos( clientpt.x, clientpt.y );
        if( item )
        { 
            wxTreeItemId newID = item->GetTreeItemId( );
            GetDesignTreeCtrl( )->SelectItem( newID );
        }
    }
////@begin wxEVT_RIGHT_DOWN event handler for ID_IMAGEPANEL in ImagePanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
////@end wxEVT_RIGHT_DOWN event handler for ID_IMAGEPANEL in ImagePanel. 
}



/*
 * wxEVT_CONTEXT_MENU event handler for ID_ALBUMIMAGEPANEL
 *
 **************************************************/

void AlbumImagePanel::OnContextMenu( wxContextMenuEvent& event )
{ 

    wxPoint screenpt = event.GetPosition( );
    wxPoint clientpt = ScreenToClient( screenpt );
//wxPoint unscrolledPnt = CalcUnscrolledPosition( clientpt ) ;	

//    wxString str = wxString::Format( "point ( %i, %i )", unscrolledPnt.x, unscrolledPnt.y );


    Design::LayoutBase* pageNode = Design::GetSelectedNodePage( );

    wxString name = "";

    if ( pageNode )
    { 
 //       pageNode->DumpObjectLayout( );
        Design::LayoutBase* item = pageNode->FindObjectByPos( clientpt.x, clientpt.y );
        if( item )
        { 
            Design::AlbumBaseType type = item->GetNodeType( );
            name = Design::AlbumBaseNames[ type ];
 //           std::cout << "\n\nOnContextMenu Found Point in " << name << "\n";

            wxTreeItemId newID = item->GetTreeItemId( );
            GetDesignTreeCtrl( )->SelectItem( newID );
        }
    }
    wxMenu menu( name );

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



wxRealPoint AlbumImagePanel::GetLogicalTextExtent( wxString text, wxFont font )
{ 
    wxClientDC dc( this );
    dc.SetFont( font );
    dc.SetMapMode( wxMM_METRIC );
    DoPrepareDC( dc );
    

    wxSize size = dc.GetMultiLineTextExtent( text );

    wxRealPoint textSize;
    // convert the size from Device units to Metric
    textSize.x = size.x / Design::PpMM.x;
    textSize.y = size.y / Design::PpMM.y;
    return textSize;
}


void AlbumImagePanel::MakeMultiLine( wxString& text, wxFont font, double width )
{ 

    //adjust the with down just a bit to allow for text conversion
    width = width * .95;

    wxClientDC  dc( this );//= this->GetDC( );
    dc.SetMapMode( wxMM_METRIC );
    dc.SetFont( font );
    DoPrepareDC( dc );

    //SetUserScale( dc );

    text.Trim( );
    text.Trim( false );
    int len = text.length( );
    if ( len > 0 )
    { 
        wxSize ext = dc.GetTextExtent( text );
        wxSize logExt = dc.DeviceToLogicalRel( ext );
        if ( ext.x < width * Design::PpMM.x )
        { 
            // if it fits print it
            //all done
        }
        else
        { 
            // break the line up at word DoPrepareDC( dc ); breaks; look for a space
            int start = 0;
            int pos = start;
            int origPos = start;

            wxString currStr = text;
            wxString workingStr = text;

            pos = workingStr.find( ' ', pos );

            while ( len > 0 )
            { 
                if ( pos == wxNOT_FOUND )
                { 
                    // no space for break so print it.
                    len = 0;
                    // all done
                }
                else
                { 
                    // found a space so break into multiple lines
                    // Add words until length exceeded
                    workingStr = text.Mid( start, pos );

                    wxSize ext = dc.GetTextExtent( workingStr );
                    wxSize logExt = dc.DeviceToLogicalRel( ext );
                    if ( ext.x > width * Design::PpMM.x )
                    { 
                        // it won't fit; decide what to do
                        if ( start == origPos )
                        { 
                            // the distance to the first space was bigger than the size of the stamp so print it
                            // i.e., a really big word or little stamp
                            text.SetChar( pos, '\n' );
                            workingStr = text.Mid( pos + 1 );
                            workingStr.Trim( );
                            workingStr.Trim( false );
                            len = workingStr.length( );
                            start = pos + 1;
                            origPos = pos + 1;
                            pos = text.find( ' ', start );

                        }
                        else
                        { 
                            // backup to previous try
                            workingStr = workingStr.Mid( start, origPos );
                            pos = origPos;
                            text.SetChar( pos, '\n' );
                            workingStr = text.Mid( pos + 1 );
                            workingStr.Trim( );
                            workingStr.Trim( false );
                            len = workingStr.length( );
                            start = pos + 1;
                            origPos = pos + 1;
                            pos = text.find( ' ', start );

                        }
                    }
                    else
                    { 
                        // the word will fit; can another word fit?
                        origPos = pos;
                        pos = text.find( ' ', pos + 1 );
                        if ( pos == wxNOT_FOUND )
                        { 
                            // no space for break so print it.
                            text.SetChar( origPos, '\n' );
                            workingStr.Empty( );
                            len = 0;
                        }
                    }
                }
            }
        }
    }
}
