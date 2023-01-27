/**
 * @file GuiUtils.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-04-01
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
#include "wx/log.h"
#include "wx/wx.h"
#endif
#include "wx/filename.h"
#include "gui/GuiUtils.h"
#include "design/DesignDefs.h"
#include "gui/AlbumImagePanel.h"
#include "art/NotFound.xpm"


void DrawLabel( wxDC& dc, const wxString& text, 
    RealPoint pos, 
    RealSize size, 
    int  	alignment, 
    int  	indexAccel )
{ 
    // wxSize devicePos = LogicalToDeviceRel( dc, pos.x, pos.y );
    // wxSize deviceSize = LogicalToDeviceRel( dc, size.x, size.y );
    // double tx = pos.x * Design::PpMM.x;
    // double ty = pos.y * Design::PpMM.y;

    //wxRect rect( devicePos.x, devicePos.y , deviceSize.x, deviceSize.y );
    wxRect rect( pos.x * Design::PpMM.x, pos.y * Design::PpMM.y, size.x * Design::PpMM.x, size.y * Design::PpMM.y );
    dc.DrawLabel( text, rect, wxALIGN_CENTER_HORIZONTAL );
}

void DrawTitle( wxDC& dc, wxString title, RealPoint pos, RealSize size )
{ 
    wxString id;
    wxFont font( *wxNORMAL_FONT );
    font.SetPointSize( 10 );
    dc.SetFont( font );
    id = title;
    id.Trim( );
    id.Trim( false );
    GetAlbumImagePanel( )->MakeMultiLine( id, font, size.x );

    DrawLabel( dc, id, pos, size, wxALIGN_CENTER_HORIZONTAL );

}

wxSize LogicalToDeviceRel( wxDC& dc, double x, double y )
{ 
    wxPoint point( x, y );
    point = dc.LogicalToDevice( wxCoord( x ), wxCoord( y ) );
    wxSize size( point.x, point.y );
    return size;
}

void DrawRectangle( wxDC& dc, double x, double y, double width, double height )
{ 
    //wxPoint pt = dc.LogicalToDevice( x, y );
    //wxSize size = dc.LogicalToDeviceRel( width, height );
    //   wxSize devicePos = GetAlbumImagePanel( )->LogicalToDeviceRel( dc, x, y );
    //   wxSize deviceSize = GetAlbumImagePanel( )->LogicalToDeviceRel( dc, width, height );
    //   dc.DrawRectangle( devicePos.x, devicePos.y, deviceSize.x, deviceSize.y );
    // std::cout << "DrawRec pos( "<< x * Design::PpMM.x << ", " << y * Design::PpMM.y << " ) size ( "
    // << width * Design::PpMM.x << ", "<< height * Design::PpMM.y<<" )\n";
    dc.DrawRectangle( x * Design::PpMM.x, y * Design::PpMM.y, width * Design::PpMM.x, height * Design::PpMM.y );
    //dc.DrawRectangle( pt.x, pt.y, size.x, size.y );
};



    wxImage* GetImageFromFilename( wxString filename )
    { 
 
        wxFileName fn;
        wxImage* image;
        bool fileOK = false;

        fn.Assign( filename );
        wxString fullpath = fn.GetFullPath( );
        wxFileName fn3 = fn;
        fn3.MakeAbsolute( );
        wxString str = fn3.GetFullPath( );
        if ( fn.FileExists( ) )
        { 
            if ( image->CanRead( filename ) )
            { 
                fileOK = true;
            }
        }
        if ( fileOK )
        { 
            image = new wxImage( filename );
        }
        else
        { 
            image = new wxImage( NotFound );
        }

        return image;
    }

void DrawImage( wxDC& dc, wxString fileName, double x, double y, double w, double h )
{ 
    wxImage* image = GetImageFromFilename( fileName );
    if ( image && image->IsOk( ) )
    { 
        //Draw the stamp image

        if ( w <= 0.01 || h <= 0.01 )
        { 
            h = 10;
            w = 10;
        }

        image->Rescale( w * Design::PpMM.x, h * Design::PpMM.y );
        wxBitmap bitmap = *image;

        dc.DrawBitmap( bitmap, x * Design::PpMM.x, y * Design::PpMM.y, true );
        if ( image )
        { 
            delete image;
        }
    }

};