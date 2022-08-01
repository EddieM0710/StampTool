/* 
 * @file ODTDefs.h
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * This file is part of AlbumGenerator.
 * 
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 * 
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 * 
 */
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