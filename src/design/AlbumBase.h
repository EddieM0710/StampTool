/**
 * @file layout/AlbumBase.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
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

#ifndef AlbumBase_h
#define AlbumBase_h

#include "design/XMLBase.h"
#include "utils/FontList.h"
#include "design/DesignData.h"
#include <wx/treectrl.h>


namespace Design {

    //   class AlbumBase;

           /**
            * @brief Base class for all layout objects. The layout objects are
            * initialy loaded from the layout XML.
            *
            **************************************************/
    class AlbumBase: public XMLBase
    {
    public:

        AlbumBase( ): XMLBase( ( wxXmlNode* ) 0 ) { };

        AlbumBase( wxXmlNode* ele ): XMLBase( ele )
        {

        }

        ~AlbumBase( );

        int GetNbrChildren( );

        AlbumBase* GetParent( );
        bool HasChildren( );

        wxTreeItemId GetTreeItemId( ) { return m_treeID; };
        void SetTreeItemId( wxTreeItemId id ) { m_treeID = id; };

        virtual NodeStatus ValidateNode( ) = 0;

        NodeStatus ValidateChildren( AlbumBase* node );
        NodeStatus GetNodeStatus( ) { return m_nodeValid; };
        bool IsStatusOK( ) { return ( m_nodeValid != AT_FATAL ); };
        void SetNodeStatus( NodeStatus status ) { m_nodeValid = status; };

        virtual void Save( wxXmlNode* xmlNode ) = 0;

        wxArrayString* GetErrorArray( ) { return &m_errorArray; };

        int GetTitleFontNdx( );
        int GetTextFontNdx( );
        int GetNameFontNdx( );
        int GetNbrFontNdx( );

        wxFont GetTitleFont( );
        wxFont GetTextFont( );
        wxFont GetNameFont( );
        wxFont GetNbrFont( );

        wxColour GetTitleColor( );
        wxColour GetTextColor( );
        wxColour GetNameColor( );
        wxColour GetNbrColor( );

        void SetTitleFont( wxFont font, wxColour color );
        void SetTextFont( wxFont font, wxColour color );
        void SetNameFont( wxFont font, wxColour color );
        void SetNbrFont( wxFont font, wxColour color );

        // resets the Catalog Nbr Font to the default CatNbr Font
        void DefaultCatNbrFont( ) { m_nbrFont.Default( ); };

        // resets the Title Font to the default Title Font
        void DefaultTitleFont( ) { m_titleFont.Default( ); };

        // resets the Text Font to the default Text Font
        void DefaultTextFont( ) { m_textFont.Default( ); };

        bool IsDefaultTitleFont( int ndx );
        bool IsDefaultTextFont( int ndx );
        bool IsDefaultNameFont( int ndx );
        bool IsDefaultNbrFont( int ndx );

        void LoadFonts( wxXmlNode* node );
        void SaveFonts( wxXmlNode* parent );
        void DumpFont( wxString Level );


    private:

        wxTreeItemId m_treeID;
        wxArrayString m_errorArray;

        // index of title font in FontMap
        Utils::FontNdx m_titleFont;
        // index of text font in FontMap
        Utils::FontNdx m_textFont;
        // index of catalog number font in FontMap
        Utils::FontNdx m_nbrFont;
        // index of name font in FontMap
        Utils::FontNdx m_nameFont;

    protected:

    };
}
#endif
