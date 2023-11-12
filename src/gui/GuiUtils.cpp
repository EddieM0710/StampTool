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
#include "utils/Project.h"
#include "gui/AlbumImagePanel.h"
#include "art/NotFound.xpm"
#include "art/fleur_di_lis3.xpm"
#include <wx/dcmemory.h>
#include <wx/dcgraph.h>
#include <wx/tokenzr.h>

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


void DrawText( wxDC& dc, wxString& str, wxRect& rect, bool draw ) {
    wxCoord w, h;
    // rect.x = rect.x * ScaleX;
    // rect.y = rect.y * ScaleY;
    // rect.width = rect.width * ScaleX;
    // rect.height = rect.height * ScaleY;
    rect.x = dc.LogicalToDeviceX( rect.x );
    rect.y = dc.LogicalToDeviceY( rect.y );
    rect.width = dc.LogicalToDeviceXRel( rect.width );;
    rect.height = dc.LogicalToDeviceXRel( rect.height );;
    wxCoord x = rect.x,
        y = rect.y;

    // zeroing height, in which the new height of the whole will be returned
    rect.height = 0;

    wxArrayString lines = wxStringTokenize( str, "\n" );

    size_t size = lines.GetCount( );
    for ( size_t i = 0; i < size; i++ )
    {

        wxString line;
        wxCoord width = 0;

        wxArrayString words = wxStringTokenize( lines[ i ], " ", wxTOKEN_RET_DELIMS );

        for ( size_t k = 0; k < words.GetCount( ); k++ )
        {

            dc.GetTextExtent( words[ k ], &w, &h );

            if ( ( width += w ) > rect.width )
            {
                // if larger, paint lines (text without the last word)
                if ( draw )
                    dc.DrawText( line, x, y );

                // Increase the height and position to the next line
                y += h;
                rect.height += h;

                line = "";

                // the width of the last word later attached to the line
                width = w;
            }

            // a word larger than the entire line
            if ( w > rect.width )
            {
                wxString s;
                int a = 0;
                int len = words[ k ].Length( );

                for ( int i = 0; i < len; i++ )
                {

                    dc.GetTextExtent( words[ k ][ i ], &w, &h );

                    if ( ( a += w ) > rect.width )
                    {

                        if ( draw )
                            dc.DrawText( s, x, y );

                        y += h;
                        rect.height += h;

                        s = "";
                        a = w;
                    }

                    s << words[ k ][ i ];
                }

                words[ k ] = s;   // The word is the remnant
                width = a;      // the width of this residue
            }

            line << words[ k ];

        } // end for()

        // If there is something left (smaller than the line - the remnant) then namluj
        if ( line != "" )
        {
            if ( draw )
                dc.DrawText( line, x, y );

            y += h;
            rect.height += h;
        }

    } // end for()
}

void DrawLabel( wxDC& dc, const wxString& text,
    RealPoint pos,
    RealSize size,
    int  	alignment,
    int  	indexAccel )
{
    wxPoint posDevice = dc.LogicalToDevice( pos );
    wxSize sizeDevice = dc.LogicalToDeviceRel( wxSize( size.x, size.y ) );

    // wxRect rect ( pos.x * ScaleX, pos.y * ScaleY, size.x * ScaleX, size.y * ScaleY );
    dc.DrawLabel( text, wxRect( posDevice, sizeDevice ), alignment, indexAccel );
}

void DrawTitle( wxDC& dc, wxString title, RealPoint pos, RealSize size )
{
    wxString id;
    wxFont font = dc.GetFont( );//( *wxNORMAL_FONT );

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
    static const double cTable[ nTable ] = { 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    static const double hTable[ nTable ] = { 2, 2.5, 3, 4, 5, 6, 7, 8, 9, 10 };
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
    doc->SetXY( pos.x, pos.y );

    double lineHeight = GetHeightChars( 10 );

    doc->MultiCell( size.x, lineHeight, id, 0, wxPDF_ALIGN_CENTER );
}

// wxSize LogicalToDeviceRel( wxDC& dc, double x, double y )
// {
//     wxPoint point( x, y );
//     point = dc.LogicalToDevice( wxCoord( x ), wxCoord( y ) );
//     wxSize size( point.x, point.y );
//     return size;
// }

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

// inputs are in mm
void DrawRectangle( wxDC& dc, double x, double y, double width, double height )
{
    wxPoint posDevice = dc.LogicalToDevice( wxPoint( x, y ) );
    wxSize sizeDevice = dc.LogicalToDeviceRel( wxSize( width, height ) );

    //Scale to client logical units
    dc.DrawRectangle( wxRect( posDevice, sizeDevice ) );
    //  dc.DrawRectangle( x * ScaleX, y * ScaleY, width * ScaleX, height * ScaleY );
};

wxImage GetImageFromFilename( wxString filename )
{

    wxFileName fn;
    wxImage image;
    bool fileOK = false;
    wxString  str = GetProject( )->GetImageFullPath( filename );

    fn.Assign( str );
    //wxString fullpath = fn.GetFullPath( );
    wxFileName fn3 = fn;
    //fn3.MakeAbsolute( );
    wxString str1 = fn3.GetFullPath( );
    if ( fn.FileExists( ) )
    {
        if ( image.CanRead( str ) )
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


// void RescaleImage( wxDC& dc, wxImage image, double x, double y, double w, double h )
// {
//     wxBitmap bitmap( image.Scale( w * ScaleX, h * ScaleY, wxIMAGE_QUALITY_HIGH ) );
//     dc.DrawBitmap( bitmap, x * ScaleX, y * ScaleY, false );
// }

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

        if ( w <= 10 || h <= 10 )
        {
            h = 10;
            w = 10;
        }
        dc.SetTextForeground( *wxBLACK );
        int xDevice = dc.LogicalToDeviceX( x );
        int yDevice = dc.LogicalToDeviceY( y );
        int widthDevice = dc.LogicalToDeviceXRel( w );
        int heightDevice = dc.LogicalToDeviceYRel( h );

        image.Rescale( widthDevice, heightDevice, wxIMAGE_QUALITY_HIGH );
        //image.Rescale( w * ScaleX, h * ScaleY, wxIMAGE_QUALITY_HIGH );
        wxBitmap bitmap( image );
        //Kluge( dc, image, x, y, w, h );

        dc.DrawBitmap( bitmap, xDevice, yDevice, false );
        // dc.DrawBitmap( bitmap, x * ScaleX, y * ScaleY, false );


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
    else
    {
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
