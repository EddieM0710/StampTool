#ifndef PDFPrintout_h
#define PDFPrintout_h

#include <wx/print.h>

class PDFPrintout : public wxPrintout
{
public:
    PDFPrintout( const wxChar* title = _T( "My printout" ) ) :wxPrintout( title ) {}
    bool OnPrintPage( int page );
    bool HasPage( int page );
    bool OnBeginDocument( int startPage, int endPage );
    void GetPageInfo( int* minPage, int* maxPage, int* selPageFrom, int* selPageTo );

    void DrawPageOne( );

    void DrawPageTwo( );
    void SetPageMargins( float top, float bottom, float left, float right, float spaces = 3 );
    void SetPageMargins( const wxPageSetupDialogData& pageSetupData );
    void SetFonts( const wxString& normal_face, const wxString& fixed_face, const int* sizes );
    void SetStandardFonts( int size, const wxString& normal_face, const wxString& fixed_face );
    void SetFile( const wxString& htmlfile );

private:
    // this function is called by the base class OnPreparePrinting()
    // implementation and by default checks whether the document fits into
    // pageArea horizontally and warns the user if it does not and, if we're
    // going to print and not just to preview the document, giving him the
    // possibility to cancel printing
    //
    // you may override it to either suppress this check if truncation of the
    // HTML being printed is acceptable or, on the contrary, add more checks to
    // it, e.g. for the fit in the vertical direction if the document should
    // always appear on a single page
    //
    // return true if printing should go ahead or false to cancel it (the
    // return value is ignored when previewing)
    virtual bool CheckFit( const wxSize& pageArea, const wxSize& docArea ) const;

    void RenderPage( wxDC* dc, int page );
    // renders one page into dc
    wxString TranslateHeader( const wxString& instr, int page );
    // substitute @PAGENUM@ and @PAGESCNT@ by real values
    void CountPages( );
    // fills m_PageBreaks, which indirectly gives the number of pages


private:
    wxVector<int> m_PageBreaks;

    wxString m_Document, m_BasePath;
    bool m_BasePathIsDir;
    wxString m_Headers[ 2 ], m_Footers[ 2 ];

    int m_HeaderHeight, m_FooterHeight;
    // wxHtmlDCRenderer m_Renderer, m_RendererHdr;
    float m_PageMarginTop, m_PageMarginBottom, m_PageMarginLeft, m_PageMarginRight, m_PageMarginSpace;

    // list of HTML filters
   // static wxVector<wxHtmlFilter*> m_Filters;

  //  wxDECLARE_NO_COPY_CLASS( wxHtmlPrintout );
};

enum
{
    WXPRINT_QUIT = 100,
    WXPRINT_PRINT,
    WXPRINT_PDF,
    WXPRINT_PDF_TPL,
    WXPRINT_PAGE_SETUP,
    WXPRINT_PREVIEW,
    WXPRINT_PRINT_PS,
    WXPRINT_PAGE_SETUP_PS,
    WXPRINT_PREVIEW_PS,
    WXPRINT_ABOUT,
    WXPRINT_ANGLEUP,
    WXPRINT_ANGLEDOWN,
    WXPRINT_PAGE_MARGINS,
    WXPDFPRINT_PAGE_SETUP_ALL,
    WXPDFPRINT_PAGE_SETUP_MINIMAL,
    WXPDFPRINT_PRINT_DIALOG_ALL,
    WXPDFPRINT_PRINT_DIALOG_MINIMAL,
    WXPDFPRINT_RICHTEXT_PRINT,
    WXPDFPRINT_RICHTEXT_PREVIEW,
    WXPDFPRINT_HTML_PRINT,
    WXPDFPRINT_HTML_PREVIEW
};
#endif