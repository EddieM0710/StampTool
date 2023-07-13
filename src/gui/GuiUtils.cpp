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
 */

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
#include "art/fleur_di_lis3.xpm"
#include <wx/dcmemory.h>
#include <wx/dcgraph.h>

wxPdfArrayDouble defaultDash;


void DrawLabelPDF( wxPdfDocument* doc, const wxString& text,
    RealPoint pos,
    RealSize size,
    int   	alignment,
    int  	border,
    bool fill )
{
    doc->SetXY( pos.x, pos.y );
    doc->Write( 2, text );
    //doc->Cell( size.x, size.y, text, border, 0, alignment, fill );

}

void DrawLabel( wxDC& dc, const wxString& text,
    RealPoint pos,
    RealSize size,
    int  	alignment,
    int  	indexAccel )
{
    // wxSize devicePos = LogicalToDeviceRel( dc, pos.x, pos.y );
    // wxSize deviceSize = LogicalToDeviceRel( dc, size.x, size.y );
    // double tx = pos.x * Design::DeviceUnitsPerMM.x;
    // double ty = pos.y * Design::DeviceUnitsPerMM.y;

    //wxRect rect( devicePos.x, devicePos.y , deviceSize.x, deviceSize.y );
    wxRect rect( pos.x * Design::DeviceUnitsPerMM.x, pos.y * Design::DeviceUnitsPerMM.y,
        size.x * Design::DeviceUnitsPerMM.x, size.y * Design::DeviceUnitsPerMM.y );
    //wxRect rect( pos.x, pos.y, size.x, size.y );
    dc.DrawLabel( text, rect, alignment, indexAccel );


}

void DrawTitle( wxDC& dc, wxString title, RealPoint pos, RealSize size )
{
    wxString id;
    wxFont font = dc.GetFont( );//( *wxNORMAL_FONT );
    //    font.SetPointSize( 10 );
    //    dc.SetFont( font );
    id = title;
    id.Trim( );
    id.Trim( false );

    GetAlbumImagePanel( )->MakeMultiLine( id, font, size.x );

    DrawLabel( dc, id, pos, size, wxALIGN_CENTER_HORIZONTAL );

}
double GetHeightChars( double pt )
{
    double height = 100;
    // Array matching character sizes and line heights
    static const int nTable = 10;
    static const double cTable[ nTable ] = { 6, 7,   8, 9, 10, 11, 12, 13, 14, 15 };
    static const double hTable[ nTable ] = { 2, 2.5, 3, 4,  5,  6,  7,  8,  9, 10 };
    int i;
    for ( i = 0; i < nTable; i++ )
    {
        if ( pt == cTable[ i ] )
        {
            height = hTable[ i ];
            break;
        }
    }
    return height;
}

double GetMultiLineTextHeight( wxString text, wxFont* font, double width )
{
    double lineHeight = GetHeightChars( font->GetPointSize( ) );
    text.Trim( );
    text.Trim( false );
    wxPdfDocument doc;
    doc.SetFont( *font );
    doc.SetXY( 0, 0 );
    doc.MultiCell( width, lineHeight, text, 0, wxPDF_ALIGN_CENTER );
    return doc.GetY( );
}

void DrawTitlePDF( wxPdfDocument* doc, wxString title, RealPoint pos, RealSize size )
{
    wxString id;
    wxFont font( *wxNORMAL_FONT );
    font.SetPointSize( 10 );
    doc->SetFont( font );
    id = title;
    id.Trim( );
    id.Trim( false );

    wxPdfFont pdfFont = doc->GetCurrentFont( );
    //   pdfFont.GetStringWidth{ id };

       //GetAlbumImagePanel( )->MakeMultiLine( id, font, size.x );
    doc->SetXY( pos.x, pos.y );

    double lineHeight = GetHeightChars( 10 );

    doc->MultiCell( size.x, lineHeight, id, 0, wxPDF_ALIGN_CENTER );
    //double y = doc->GetY( );
    //double x = doc->GetX( );
}

wxSize LogicalToDeviceRel( wxDC& dc, double x, double y )
{
    wxPoint point( x, y );
    point = dc.LogicalToDevice( wxCoord( x ), wxCoord( y ) );
    wxSize size( point.x, point.y );
    return size;
}

wxPen DCLineStyle( wxDC& dc, wxColour colour, double  width, wxPenStyle style )
{
    wxPen currStyle = dc.GetPen( );
    wxPen frameStyle( currStyle );
    frameStyle.SetColour( colour );
    frameStyle.SetStyle( style );
    frameStyle.SetWidth( width );

    return currStyle;
}

wxPdfLineStyle PDFLineStyle( wxPdfDocument* doc, wxColour colour, double  width, const wxPdfArrayDouble& dash )
{
    wxPdfLineStyle currStyle = doc->GetLineStyle( );
    wxPdfLineStyle frameStyle( currStyle );
    frameStyle.SetColour( wxPdfColour( colour ) );
    frameStyle.SetDash( dash );
    frameStyle.SetWidth( width );
    doc->SetLineStyle( frameStyle );
    return currStyle;
}

void DrawRectanglePDF( wxPdfDocument* doc, double x, double y, double width, double height )
{
    doc->Rect( x, y, width, height, wxPDF_STYLE_DRAW );
}

void DrawRectangle( wxDC& dc, double x, double y, double width, double height )
{
    dc.DrawRectangle( x * Design::DeviceUnitsPerMM.x, y * Design::DeviceUnitsPerMM.y, width * Design::DeviceUnitsPerMM.x, height * Design::DeviceUnitsPerMM.y );
    //dc.DrawRectangle( x, y, width, height );
};

wxImage GetImageFromFilename( wxString filename )
{

    wxFileName fn;
    wxImage image;
    bool fileOK = false;

    fn.Assign( filename );
    wxString fullpath = fn.GetFullPath( );
    wxFileName fn3 = fn;
    fn3.MakeAbsolute( );
    wxString str = fn3.GetFullPath( );
    if ( fn.FileExists( ) )
    {
        if ( image.CanRead( filename ) )
        {
            fileOK = true;
        }
    }
    if ( fileOK )
    {
        image = wxImage( filename );
    }
    else
    {
        image = wxImage( fleur_di_lis );
    }

    return image;
}

// void DrawImagePDF( wxPdfDocument* doc, wxImage image, double x, double y, double w, double h )
// {

//     // wxImage image = GetImageFromFilename( fileName );
//      // Draw jpeg image
//   //   doc->Image( fileName, x, y, w, h );
//     doc->Image( fileName, image, x, y, w, h );


void  BlitResize( wxDC& dc, wxImage image, double x, double y, double w, double h )
{
    wxBitmap bmpIn( image );

    bool antialiasing = true;
    wxSize sizeIn = bmpIn.GetSize( );

    wxSize pixels = dc.GetSize( );
    wxSize mm = dc.GetSizeMM( );
    RealSize dcPixelsPerMM;
    dcPixelsPerMM.x = pixels.x / mm.x;
    dcPixelsPerMM.y = pixels.y / mm.y;

    double scale = w * dcPixelsPerMM.x / sizeIn.x;

    wxSize sizeOut( ( int ) w * dcPixelsPerMM.x * GetAlbumImagePanel( )->GetZoom( ), ( int ) h * dcPixelsPerMM.y * GetAlbumImagePanel( )->GetZoom( ) );

    wxBitmap bmpOut;
    bmpOut.Create( sizeOut );   // the final size

    wxMemoryDC inDC( bmpIn );

    if ( antialiasing && scale < 0.4 )
    {
        wxGCDC outDC( bmpOut );
        outDC.StretchBlit( wxPoint( 0, 0 ), sizeOut, &inDC, wxPoint( 0, 0 ), sizeIn );
    }
    else
    {
        wxMemoryDC outDC( bmpOut );
        outDC.StretchBlit( wxPoint( 0, 0 ), sizeOut, &inDC, wxPoint( 0, 0 ), sizeIn );
        outDC.SelectObject( wxNullBitmap );
    }
    inDC.SelectObject( wxNullBitmap );

    dc.DrawBitmap( bmpOut, x, y, false );
}


void RescaleImage( wxDC& dc, wxImage image, double x, double y, double w, double h )
{
    wxBitmap bitmap( image.Scale( w, h, wxIMAGE_QUALITY_HIGH ) );
    dc.DrawBitmap( bitmap, x, y, false );
}

void Kluge( wxDC& dc, wxImage image, double x, double y, double w, double h )
{
    double xScale;
    double yScale;
    dc.GetUserScale( &xScale, &yScale );
    dc.SetUserScale( 1, 1 );

    wxSize size = image.GetSize( );

    double imageScaleX = ( w / size.x );
    double imageScaleY = ( h / size.y );

    double zoom = GetAlbumImagePanel( )->GetUserScale( );

    dc.SetUserScale( imageScaleX * zoom, imageScaleY * zoom );
    wxBitmap bitmap( image );

    dc.DrawBitmap( bitmap, x / imageScaleX, y / imageScaleY, false );
    dc.SetUserScale( xScale, yScale );

}

void DrawImage( wxDC& dc, wxImage image, double x, double y, double w, double h )
{
    if ( image.IsOk( ) )
    {
        //Draw the stamp image

        if ( w <= 0.01 || h <= 0.01 )
        {
            h = 10;
            w = 10;
        }


        // RescaleImage( dc, image, x * Design::DeviceUnitsPerMM.x, y * Design::DeviceUnitsPerMM.y, w * Design::DeviceUnitsPerMM.x, h * Design::DeviceUnitsPerMM.y );
        // BlitResize( dc, image, x * Design::DeviceUnitsPerMM.x, y * Design::DeviceUnitsPerMM.y, w * Design::DeviceUnitsPerMM.x, h * Design::DeviceUnitsPerMM.y );
        // Kluge( dc, image, x * Design::DeviceUnitsPerMM.x, y * Design::DeviceUnitsPerMM.y, w * Design::DeviceUnitsPerMM.x, h * Design::DeviceUnitsPerMM.y );

        image.Rescale( w * Design::DeviceUnitsPerMM.x, h * Design::DeviceUnitsPerMM.y );
        wxBitmap bitmap = image;

        dc.DrawBitmap( bitmap, x * Design::DeviceUnitsPerMM.x, y * Design::DeviceUnitsPerMM.y, true );


    }
};

int CompareID( wxString id1, wxString id2 )
{
    id1 = id1.Trim( );
    id1 = id1.Trim( false );

    int pos = id1.Find( ":" );
    wxString catalog1 = id1.Mid( 0, pos );
    id1 = id1.Mid( pos + 1 );
    pos = id1.Find( " " );
    wxString country1 = id1.Mid( 0, pos );
    wxString catCode1 = id1.Mid( pos + 1 );
    wxString prefix1 = "";
    wxString code1 = "";

    if ( pos > 0 )
    {
        prefix1 = catCode1.Mid( 0, pos - 1 );
        code1 = catCode1.Mid( pos );
    }
    else {
        code1 = catCode1;
    }

    id2 = id2.Trim( );
    id2 = id2.Trim( false );
    pos = id2.Find( ":" );
    wxString catalog2 = id2.Mid( 0, pos );
    id2 = id2.Mid( pos + 1 );
    pos = id2.Find( " " );
    wxString country2 = id2.Mid( 0, pos );
    wxString catCode2 = id2.Mid( pos + 1 );
    pos = catCode2.find_first_of( "0123456789" );

    wxString prefix2 = "";
    wxString code2 = "";

    if ( pos > 0 )
    {
        prefix2 = catCode2.Mid( 0, pos - 1 );
        code2 = catCode2.Mid( pos );
    }
    else
    {
        code2 = catCode2;
    }

    int stat = country1.Cmp( country2 );
    if ( !stat )
    {
        stat = catalog1.Cmp( catalog2 );
        if ( !stat )
        {
            stat = code1.Cmp( code2 );
            if ( !stat )
            {
                stat = prefix1.Cmp( prefix2 );
            }
        }
    }
    return stat;

}

ComparisonResultType CompareDates( wxString date1, wxString date2 )
{
    wxDateTime dt1;
    wxDateTime dt2;
    wxString::const_iterator end;
    if ( !dt1.ParseFormat( date1, "%Y-%m-%d", &end ) )
    {
        if ( !dt1.ParseFormat( date1, "%Y", &end ) )
        {
            if ( !dt1.ParseFormat( date1, "%Y-%m", &end ) )
            {
                return CompareInvalid;
            }
        }
    }
    if ( !dt2.ParseFormat( date2, "%Y-%m-%d", &end ) )
    {
        if ( !dt2.ParseFormat( date2, "%Y", &end ) )
        {
            if ( !dt2.ParseFormat( date2, "%Y-%m", &end ) )
            {
                return CompareInvalid;
            }
        }
    }
    if ( !dt1.IsValid( ) || !dt2.IsValid( ) )
    {
        return CompareInvalid;
    }

    if ( dt1.IsSameDate( dt2 ) )
    {
        return CompareEqual;
    }
    else if ( dt1.IsEarlierThan( dt2 ) )
    {
        return CompareLess;
    }
    else
    {
        return CompareGreater;
    }
}
