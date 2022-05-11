#ifndef ODTDefs_h
#define ODTDefs_h
#include <wx/xml/xml.h>
#include "Defs.h"

namespace ODT {

    class Document;
    class Content;
    class Settings;
    class Styles;
    class Manifest;
    class Meta;


    extern  wxString Frame20Content;
    extern  wxString NormalTextStyle;
    extern  wxString Bold18PtTextStyle;
    extern  wxString Normal8PtTextStyle;
    extern  wxString Normal10PtTextStyle;
    extern  wxString FrameWithBorder;
    extern  wxString FrameNoBorder;
    extern  wxString FrameWithImage;
    extern  wxString FrameCenteredAtTopNoBorder;
    extern  wxString FrameCenteredFromTopNoBorder;
    extern  wxString TextAnchorParagraph;
    extern  wxString TextAnchorPage;

typedef struct
{
    wxString ext;
    wxString type;
} MimeTypeDef;

enum MimeTypes
{
    MT_Gif = 0,
    MT_Jpeg,
    MT_Jpg,
    MT_Png,
    MT_Svg,
    MT_Tif,
    MT_Tiff,
    MT_Ico,
    MT_Webp,
    NbrMimeTypes,
};

extern MimeTypeDef mimeTypes[NbrMimeTypes];

wxString GetMimeType( const wxString& str );

    wxXmlDocument* ContentXML( );
    wxXmlDocument* SettingsXML( );
    wxXmlDocument* StylesXML( );
    wxXmlDocument* ManifestXML( );
    wxXmlDocument* MetaXML( );

    Content* ContentDoc( );
    Settings* SettingsDoc( );
    Styles* StylesDoc( );
    Manifest* ManifestDoc( );
    Meta* MetaDoc( );
    Document* ODTDoc();
    void SetODTDocument( Document* doc );
}
#endif