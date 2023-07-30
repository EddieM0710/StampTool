/**
 * @file GuiUtils.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-23
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
#ifndef GUIUTILS_H_
#define GUIUTILS_H_

 /*
  * Includes
  */
#include <wx/pdfdocument.h>
#include <wx/pdffont.h>

#include "Defs.h"
#include "gui/GuiDefs.h"

typedef enum {
    CompareInvalid,
    CompareEqual,
    CompareLess,
    CompareGreater
}ComparisonResultType;

extern wxPdfArrayDouble defaultDash;

extern double ScaleX;
extern double ScaleY;
extern RealPoint ScalePoint;

void InitScale( wxSize sizeMM, wxSize sizeClient );

void drawBorder( wxDC& dc,
    double x, double y,
    double width, double height );

void DrawRectangle( wxDC& dc,
    double x, double y,
    double width, double height );

void DrawRectanglePDF( wxPdfDocument* doc,
    double x, double y,
    double width, double height );

// get pen current style to return; sets parameters; returns unchanged current pen so original can be reset
wxPen DCLineStyle( wxDC& dc, wxColour colour = *wxBLACK, double  width = -1, wxPenStyle style = wxPENSTYLE_SOLID );

// get current line style to return; sets parameters; returns unchanged current line style so original can be reset
wxPdfLineStyle PDFLineStyle( wxPdfDocument* doc, wxColour colour = *wxBLACK, double  width = -1, const wxPdfArrayDouble& dash = wxPdfArrayDouble( ) );

wxSize LogicalToDeviceRel( wxDC& dc,
    double x, double y );

double GetHeightChars( double pt );

double GetMultiLineTextHeight( wxString text, wxFont* font, double width );

void DrawTitle( wxDC& dc, wxString title,
    RealPoint pos,
    RealSize size );

void DrawTitlePDF( wxPdfDocument* doc, wxString title,
    RealPoint pos,
    RealSize size );

void DrawLabel( wxDC& dc, const wxString& text,
    RealPoint pos,
    RealSize size,
    int  	alignment = wxALIGN_CENTER,
    int  	indexAccel = -1 );

void DrawLabelPDF( wxPdfDocument* doc, const wxString& text,
    RealPoint pos,
    RealSize size,
    int   	alignment = wxPDF_ALIGN_LEFT, // wxPDF_ALIGN_LEFT wxPdfAlignment
    int  	border = wxPDF_BORDER_NONE,
    bool fill = 0 ); //0=>no Fill default   1=>Fill

void DrawImagePDF( wxPdfDocument* doc, wxImage image,
    double x, double y,
    double w, double h );

void DrawImage( wxDC& dc, wxImage image,
    double x, double y,
    double w, double h );

wxImage GetImageFromFilename( wxString filename );
////wxImage GetImage( wxString filename );

ComparisonResultType CompareDates( wxString date1, wxString date2 );
int CompareID( wxString id1, wxString id2 );

#endif
