

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "gui/PDFPrintout.h"
#include <wx/filesys.h>

// Global print data, to remember settings during the session
wxPrintData* g_printData = ( wxPrintData* ) NULL;

// Global page setup data
wxPageSetupDialogData* g_pageSetupData = ( wxPageSetupDialogData* ) NULL;





bool PDFPrintout::OnPrintPage( int page )
{
    wxDC* dc = GetDC( );
    if ( dc )
    {
        if ( page == 1 )
            DrawPageOne( );
        else if ( page == 2 )
            DrawPageTwo( );

        // Draw page numbers at top left corner of printable area, sized so that
        // screen size of text matches paper size.
        MapScreenSizeToPage( );
        wxStringCharType buf[ 200 ];
        wxSprintf( buf, wxS( "PAGE %d" ), page );
        dc->DrawText( buf, 0, 0 );

        return true;
    }
    else
        return false;
}

bool PDFPrintout::OnBeginDocument( int startPage, int endPage )
{
    if ( !wxPrintout::OnBeginDocument( startPage, endPage ) )
        return false;

    return true;
}

void PDFPrintout::GetPageInfo( int* minPage, int* maxPage, int* selPageFrom, int* selPageTo )
{
    *minPage = 1;
    *maxPage = 2;
    *selPageFrom = 1;
    *selPageTo = 2;
}

bool PDFPrintout::HasPage( int pageNum )
{
    return ( pageNum == 1 || pageNum == 2 );
}

// void PDFPrintout::DrawPageOne( )
// {
//     // You might use THIS code if you were scaling graphics of known size to fit
//     // on the page. The commented-out code illustrates different ways of scaling
//     // the graphics.

//     // We know the graphic is 230x350. If we didn't know this, we'd need to
//     // calculate it.
//     wxSize devicePPI = GetDC( )->GetPPI( );
//     wxCoord maxX = wxRound( 230.0 * ( double ) devicePPI.GetWidth( ) / 72.0 );
//     wxCoord maxY = wxRound( 350.0 * ( double ) devicePPI.GetHeight( ) / 72.0 );

//     // This sets the user scale and origin of the DC so that the image fits
//     // within the paper rectangle (but the edges could be cut off by printers
//     // that can't print to the edges of the paper -- which is most of them. Use
//     // this if your image already has its own pageMargins.
// //    FitThisSizeToPaper(wxSize(maxX, maxY));
// //    wxRect fitRect = GetLogicalPaperRect();

//     // This sets the user scale and origin of the DC so that the image fits
//     // within the page rectangle, which is the printable area on Mac and MSW
//     // and is the entire page on other platforms.
// //    FitThisSizeToPage(wxSize(maxX, maxY));
// //    wxRect fitRect = GetLogicalPageRect();

//     // This sets the user scale and origin of the DC so that the image fits
//     // within the page pageMargins as specified by g_PageSetupData, which you can
//     // change (on some platforms, at least) in the Page Setup dialog. Note that
//     // on Mac, the native Page Setup dialog doesn't let you change the pageMargins
//     // of a wxPageSetupDialogData object, so you'll have to write your own dialog or
//     // use the Mac-only wxMacPagePageMarginsDialog, as we do in this program.
//     FitThisSizeToPagePageMargins( wxSize( maxX, maxY ), *g_pageSetupData );
//     wxRect fitRect = GetLogicalPagePageMarginsRect( *g_pageSetupData );

//     // This sets the user scale and origin of the DC so that the image appears
//     // on the paper at the same size that it appears on screen (i.e., 10-point
//     // type on screen is 10-point on the printed page) and is positioned in the
//     // top left corner of the page rectangle (just as the screen image appears
//     // in the top left corner of the window).
// //    MapScreenSizeToPage();
// //    wxRect fitRect = GetLogicalPageRect();

//     // You could also map the screen image to the entire paper at the same size
//     // as it appears on screen.
// //    MapScreenSizeToPaper();
// //    wxRect fitRect = GetLogicalPaperRect();

//     // You might also wish to do you own scaling in order to draw objects at
//     // full native device resolution. In this case, you should do the following.
//     // Note that you can use the GetLogicalXXXRect() commands to obtain the
//     // appropriate rect to scale to.
// //    MapScreenSizeToDevice();
// //    wxRect fitRect = GetLogicalPageRect();

//     // Each of the preceding Fit or Map routines positions the origin so that
//     // the drawn image is positioned at the top left corner of the reference
//     // rectangle. You can easily center or right- or bottom-justify the image as
//     // follows.

//     // This offsets the image so that it is centered within the reference
//     // rectangle defined above.
//     wxCoord xoff = ( fitRect.width - maxX ) / 2;
//     wxCoord yoff = ( fitRect.height - maxY ) / 2;
//     OffsetLogicalOrigin( xoff, yoff );

//     // This offsets the image so that it is positioned at the bottom right of
//     // the reference rectangle defined above.
// //    wxCoord xoff = (fitRect.width - maxX);
// //    wxCoord yoff = (fitRect.height - maxY);
// //    OffsetLogicalOrigin(xoff, yoff);

//     frame->Draw( *GetDC( ) );
// }

// void PDFPrintout::DrawPageTwo( )
// {
//     // You might use THIS code to set the printer DC to ROUGHLY reflect
//     // the screen text size. This page also draws lines of actual length
//     // 5cm on the page.

//     // Compare this to DrawPageOne(), which uses the really convenient routines
//     // from wxPrintout to fit the screen image onto the printed page. This page
//     // illustrates how to do all the scaling calculations yourself, if you're so
//     // inclined.

//     wxDC* dc = GetDC( );

//     // Get the logical pixels per inch of screen and printer
//     int ppiScreenX, ppiScreenY;
//     GetPPIScreen( &ppiScreenX, &ppiScreenY );
//     int ppiPrinterX, ppiPrinterY;
//     GetPPIPrinter( &ppiPrinterX, &ppiPrinterY );

//     // This scales the DC so that the printout roughly represents the the screen
//     // scaling. The text point size _should_ be the right size but in fact is
//     // too small for some reason. This is a detail that will need to be
//     // addressed at some point but can be fudged for the moment.
//     float scale = ( float ) ( ( float ) ppiPrinterX / ( float ) ppiScreenX );

//     // Now we have to check in case our real page size is reduced (e.g. because
//     // we're drawing to a print preview memory DC)
//     int pageWidth, pageHeight;
//     int w, h;
//     dc->GetSize( &w, &h );
//     GetPageSizePixels( &pageWidth, &pageHeight );

//     // If printer pageWidth == current DC width, then this doesn't change. But w
//     // might be the preview bitmap width, so scale down.
//     float overallScale = scale * ( float ) ( w / ( float ) pageWidth );
//     dc->SetUserScale( overallScale, overallScale );

//     // Calculate conversion factor for converting millimetres into logical
//     // units. There are approx. 25.4 mm to the inch. There are ppi device units
//     // to the inch. Therefore 1 mm corresponds to ppi/25.4 device units. We also
//     // divide by the screen-to-printer scaling factor, because we need to
//     // unscale to pass logical units to DrawLine.

//     // Draw 50 mm by 50 mm L shape
//     float logUnitsFactor = ( float ) ( ppiPrinterX / ( scale * 25.4 ) );
//     float logUnits = ( float ) ( 50 * logUnitsFactor );
//     dc->SetPen( *wxBLACK_PEN );
//     dc->DrawLine( 50, 250, ( long ) ( 50.0 + logUnits ), 250 );
//     dc->DrawLine( 50, 250, 50, ( long ) ( 250.0 + logUnits ) );

//     dc->SetBackgroundMode( wxTRANSPARENT );
//     dc->SetBrush( *wxTRANSPARENT_BRUSH );

//     { // GetTextExtent demo:
//         wxString words[ 7 ] = { _T( "This " ), _T( "is " ), _T( "GetTextExtent " ), _T( "testing " ), _T( "string. " ), _T( "Enjoy " ), _T( "it!" ) };
//         wxCoord w, h;
//         wxCoord x = 200, y = 250;
//         wxFont fnt( 15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL );

//         dc->SetFont( fnt );

//         for ( int i = 0; i < 7; i++ )
//         {
//             wxString word = words[ i ];
//             word.Remove( word.Len( ) - 1, 1 );
//             dc->GetTextExtent( word, &w, &h );
//             dc->DrawRectangle( x, y, w, h );
//             dc->GetTextExtent( words[ i ], &w, &h );
//             dc->DrawText( words[ i ], x, y );
//             x += w;
//         }

//     }

//     dc->SetFont( wxGetApp( ).m_testFont );

//     dc->DrawText( _T( "Some test text" ), 200, 300 );

//     // TESTING

//     int leftPageMargin = 20;
//     int rightPageMargin = 20;
//     int topPageMargin = 20;
//     int bottomPageMargin = 20;

//     int pageWidthMM, pageHeightMM;
//     GetPageSizeMM( &pageWidthMM, &pageHeightMM );

//     float leftPageMarginLogical = ( float ) ( logUnitsFactor * leftPageMargin );
//     float topPageMarginLogical = ( float ) ( logUnitsFactor * topPageMargin );
//     float bottomPageMarginLogical = ( float ) ( logUnitsFactor * ( pageHeightMM - bottomPageMargin ) );
//     float rightPageMarginLogical = ( float ) ( logUnitsFactor * ( pageWidthMM - rightPageMargin ) );

//     dc->SetPen( *wxRED_PEN );
//     dc->DrawLine( ( long ) leftPageMarginLogical, ( long ) topPageMarginLogical,
//         ( long ) rightPageMarginLogical, ( long ) topPageMarginLogical );
//     dc->DrawLine( ( long ) leftPageMarginLogical, ( long ) bottomPageMarginLogical,
//         ( long ) rightPageMarginLogical, ( long ) bottomPageMarginLogical );

//     WritePageHeader( this, dc, _T( "A header" ), logUnitsFactor );
// }

void PDFPrintout::SetFile( const wxString& htmlfile )
{
    // wxFileSystem fs;
    // wxFSFile* ff;

    // if ( wxFileExists( htmlfile ) )
    //     ff = fs.OpenFile( wxFileSystem::FileNameToURL( htmlfile ) );
    // else
    //     ff = fs.OpenFile( htmlfile );

    // if ( ff == NULL )
    // {
    //     wxLogError( htmlfile + _( ": file does not exist!" ) );
    //     return;
    // }

    // bool done = false;
    // wxHtmlFilterHTML defaultFilter;
    // wxString doc;

    // for ( size_t n = 0; n < m_Filters.size( ); ++n )
    // {
    //     wxHtmlFilter* const h = m_Filters[ n ];
    //     if ( h->CanRead( *ff ) )
    //     {
    //         doc = h->ReadFile( *ff );
    //         done = true;
    //         break;
    //     }
    // }

    // if ( !done )
    //     doc = defaultFilter.ReadFile( *ff );

    // SetHtmlText( doc, htmlfile, false );
    // delete ff;
}



void PDFPrintout::SetPageMargins( float top, float bottom, float left, float right, float spaces )
{
    m_PageMarginTop = top;
    m_PageMarginBottom = bottom;
    m_PageMarginLeft = left;
    m_PageMarginRight = right;
    m_PageMarginSpace = spaces;
}

void PDFPrintout::SetPageMargins( const wxPageSetupDialogData& pageSetupData )
{
    SetPageMargins( pageSetupData.GetPageMarginTopLeft( ).y,
        pageSetupData.GetPageMarginBottomRight( ).y,
        pageSetupData.GetPageMarginTopLeft( ).x,
        pageSetupData.GetPageMarginBottomRight( ).x );
}

void PDFPrintout::SetFonts( const wxString& normal_face, const wxString& fixed_face,
    const int* sizes )
{
    //    m_Renderer.SetFonts( normal_face, fixed_face, sizes );
     //   m_RendererHdr.SetFonts( normal_face, fixed_face, sizes );
}

void PDFPrintout::SetStandardFonts( int size,
    const wxString& normal_face,
    const wxString& fixed_face )
{
    //    m_Renderer.SetStandardFonts( size, normal_face, fixed_face );
    //    m_RendererHdr.SetStandardFonts( size, normal_face, fixed_face );
}


