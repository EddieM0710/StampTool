/**
 * @file layout/Album.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-02
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

#ifndef Album_H
#define Album_H
#include <wx/font.h>

#include "design/AlbumBase.h"
#include "design/DesignDefs.h"
 //#include "utils/Project.h"
#include "design/PageDefaults.h"
#include "design/FrameDefaults.h"
#include "design/StampDefaults.h"
#include <wx/pdfdc.h>


namespace Design {


    /**
     * @brief Album layout object; inherits from LayoutBase.
     *
     */
    class Album : public AlbumBase
    {

    public:

        Album( wxXmlNode* node );

        ~Album( ) { };

        void InitParameters( );

        void SetHardDefaults( );

        // double GetAlbumAttributeDbl( Design::AlbumAttrType type );

        // wxString GetAlbumAttributeStr( Design::AlbumAttrType type );

        // bool GetAlbumAttributeBool( Design::AlbumAttrType type );

        // void SetAlbumAttributeBool( Design::AlbumAttrType type, bool val );

        // void SetAlbumAttributeDbl( Design::AlbumAttrType type, double val );

        // void SetAlbumAttributeStr( Design::AlbumAttrType type, wxString val );

        // bool IsDefaultVal( AlbumAttrType type );

        // bool IsDefaultVal( AlbumAttrType type, wxString val );

        wxString DrawPDF( );

        wxString GetCatalog( );

        wxColour GetColor( FontUsageType fontType );

        wxString GetDocName( );

        wxFont GetFont( FontUsageType fontType );

        int GetFontNdx( FontUsageType fontType );

        int GetFontNdxPreference( FontUsageType fontType );

        bool IsDefaultFont( FontUsageType fontType, int ndx );

        void LoadFonts( wxXmlNode* node );

        void LoadDefaults( wxXmlNode* node );

        void MakeAlbum( );

        void MakeDefaultFont( FontUsageType fontType );

        void MakePDFAlbum( );

        void Save( wxXmlNode* xmlNode );

        void SaveDefaults( wxXmlNode* parent );

        void SaveFonts( wxXmlNode* parent );

        void SetCatalog( wxString str );

        void SetDocName( wxString str );

        void SetFont( FontUsageType fontType, wxFont font, wxColour color );

        void SetFontNdx( FontUsageType fontType, int ndx );


        /**
         * @brief UpdateMinimumSize drills down to the lowest layout object with an actual size
         * and begins calculating the min size of its parents as it progresses
         * back up the heirarchy.
         */
        bool UpdateMinimumSize( );

        /**
         * @brief  Does the layout for each child. Goes to the bottom
         * of each child container object ( row, column, page )
         * and begin filling in position relative to the parent
         */
        void UpdatePositions( );

        void UpdateSizes( );

        NodeStatus ValidateNode( );

        PageDefaults* AlbumPageDefaults( ) {
            return &m_pageDefaults;
        };

        FrameDefaults* AlbumFrameDefaults( ) {
            return &m_frameDefaults;
        };

        StampDefaults* AlbumStampDefaults( ) {
            return &m_stampDefaults;
        };

        void FixupNode( );

    private:
        int DefaultFonts[ AT_NbrFontUsageTypes ];

        const double m_defaultSelvageHeight = 0;
        const double m_defaultSelvageWidth = 0;
        const double m_defaultMountAllowanceHeight = 5;
        const double m_defaultMountAllowanceWidth = 4;

        PageDefaults m_pageDefaults;
        FrameDefaults m_frameDefaults;
        StampDefaults m_stampDefaults;
    };
}
#endif