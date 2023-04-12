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
#include "art/fleur_di_lis3.xpm"



void DrawLabelPDF( wxPdfDocument* doc, const wxString& text,
    RealPoint pos,
    RealSize size,
    int   	alignment,
    int  	border,
    bool fill )
{
    doc->SetXY( pos.x, pos.y );
    doc->Write( 2, text );
    //   doc->Cell(size.x, size.y, text, border, 0, alignment, fill );

}

void DrawLabel( wxDC& dc, const wxString& text,
    RealPoint pos,
    RealSize size,
    int  	alignment,
    int  	indexAccel )
{
    // wxSize devicePos = LogicalToDeviceRel( dc, pos.x, pos.y );
    // wxSize deviceSize = LogicalToDeviceRel( dc, size.x, size.y );
    // double tx = pos.x * Design::ScaleFactor.x;
    // double ty = pos.y * Design::ScaleFactor.y;

    //wxRect rect( devicePos.x, devicePos.y , deviceSize.x, deviceSize.y );
    wxRect rect( pos.x * Design::ScaleFactor.x, pos.y * Design::ScaleFactor.y, size.x * Design::ScaleFactor.x, size.y * Design::ScaleFactor.y );
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

void DrawRectanglePDF( wxPdfDocument* doc, double x, double y, double width, double height )
{
    doc->Rect( x, y, width, height, wxPDF_STYLE_DRAW );
}

void DrawRectangle( wxDC& dc, double x, double y, double width, double height )
{
    // wxBrush currBrush = dc.GetBrush( );
    // wxBrush brush( currBrush );
    // brush.SetStyle( wxBRUSHSTYLE_TRANSPARENT );
    // dc.SetBrush( brush );
    dc.DrawRectangle( x * Design::ScaleFactor.x, y * Design::ScaleFactor.y, width * Design::ScaleFactor.x, height * Design::ScaleFactor.y );
    // dc.SetBrush( currBrush );

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
        image = new wxImage( fleur_di_lis );
    }

    return image;
}

void DrawImagePDF( wxPdfDocument* doc, wxString fileName, double x, double y, double w, double h )
{

    wxImage* image = GetImageFromFilename( fileName );
    // Draw jpeg image
 //   doc->Image( fileName, x, y, w, h );
    doc->Image( fileName, *image, x, y, w, h );


}
void DrawImage( wxDC& dc, wxImage* image, double x, double y, double w, double h )
{
    if ( image && image->IsOk( ) )
    {
        //Draw the stamp image

        if ( w <= 0.01 || h <= 0.01 )
        {
            h = 10;
            w = 10;
        }

        image->Rescale( w * Design::ScaleFactor.x, h * Design::ScaleFactor.y );
        wxBitmap bitmap = *image;

        dc.DrawBitmap( bitmap, x * Design::ScaleFactor.x, y * Design::ScaleFactor.y, true );
        if ( image )
        {
            delete image;
        }
    }

};

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
