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
 **************************************************/

#ifndef Album_H
#define Album_H
#include <wx/font.h>

#include "design/AlbumBase.h"
#include "design/DesignDefs.h"
#include "utils/Project.h"
#include "utils/Settings.h"
#include "utils/FontList.h"

namespace Design {

    /**
     * @brief Album layout object; inherits from LayoutBase.
     * This is the top LayoutBase for holding all the objecs within the album
     *
     **************************************************/
    class Album: public AlbumBase
    {
    public:

        // Construct a new Album object. The top layout LayoutBase
        // for holding all the objecs within the album
        Album( wxXmlNode* node ): AlbumBase( node )
        {
            SetNodeType( AT_Album );
        };

        // Destroy the Album object
        ~Album( ) { };

        void MakeAlbum( );
        void MakePDFAlbum( );
        wxString DrawPDF( );

        /**
         * @brief init drills down to the lowest layout object with an actual size
         * and begins calculating the min size of its parents as it progresses
         * back up the heirarchy.
         * @return true
         * @return false
         **************************************************/
        bool UpdateMinimumSize( );

        void UpdateSizes( );

        /**
         * @brief  Does the layout for each child. Goes to the bottom
         * of each child container object ( row, column, page )
         * and begin filling in position relative to the parent
         *
         * @return true
         * @return false
         **************************************************/
        void UpdatePositions( );

        NodeStatus ValidateNode( );

        double GetWidth( );
        double GetPageWidth( );
        wxString GetPageWidthStr( );
        void SetPageWidth( wxString str );

        double GetHeight( );
        double GetPageHeight( );
        wxString GetPageHeightStr( );
        void SetPageHeight( wxString str );

        double GetTopMargin( );
        wxString GetTopMarginStr( );
        void SetTopMargin( wxString str );

        double GetBottomMargin( );
        wxString GetBottomMarginStr( );
        void SetBottomMargin( wxString str );

        double GetRightMargin( );
        wxString GetRightMarginStr( );
        void SetRightMargin( wxString str );

        double GetLeftMargin( );
        wxString GetLeftMarginStr( );
        void SetLeftMargin( wxString str );

        double GetBorderSize( );
        wxString GetBorderSizeStr( );
        void SetBorderSize( wxString str );
        wxString GetBorderFileName( );


        wxString GetDocName( );
        void SetDocName( wxString str );

        void GetPageParameters( wxString& width, wxString& height, wxString& topMargin,
            wxString& bottomMargin, wxString& rightMargin, wxString& leftMargin );
        void Save( wxXmlNode* xmlNode );
        void DumpLayout( );

        // int GetAppPrefTitleFontNdx( );
        // int GetAppPrefNbrFontNdx( );
        // int GetAppPrefTextFontNdx( );
        // int GetAppPrefNameFontNdx( );

        int GetFontNdxPreference( AT_FontUsageType fontType ) { return GetSettings( )->GetFontNdxPreference( fontType ); }

        bool GetShowTitle( ) { return String2Bool( GetAttrStr( AT_ShowTitle ) ); };
        void SetShowTitle( bool val ) { SetAttrStr( AT_ShowTitle, Bool2String( val ) ); };
        bool GetShowNbr( ) { return String2Bool( GetAttrStr( AT_CatNbr ) ); };
        void SetShowNbr( bool val ) { SetAttrStr( AT_CatNbr, Bool2String( val ) ); };
        void SetGrayScaleImages( bool val = true ) { SetAttrStr( AT_GrayScaleImages, Bool2String( val ) ); };
        bool GetGrayScaleImages( ) { return String2Bool( GetAttrStr( AT_GrayScaleImages ) ); };

    private:

    };
}
#endif