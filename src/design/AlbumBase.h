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
#include "design/FontInfo.h"
#include "design/DesignData.h"
#include <wx/treectrl.h>


namespace Design { 

    //   class AlbumBase;

       //typedef std::vector<AlbumBase*> ChildList;

           /**
            * @brief Base class for all layout objects. The layout objects are
            * initialy loaded from the layout XML.
            *
            **************************************************/
    class AlbumBase: public XMLBase
    { 
    public:
        /**
         * @brief Unused; Construct a new Album Design Object object
         *
         **************************************************/
        AlbumBase( ) : XMLBase( (wxXmlNode*) 0 )
        { 
            m_titleFont = -1;
            m_textFont = -1;
            m_catNbrFont = -1;
        };

        /**
         * @brief Construct a new Album Design Object
         *
         * @param name
         **************************************************/
        AlbumBase( wxXmlNode* ele ) : XMLBase( ele )
        { 
            m_titleFont = -1;
            m_textFont = -1;
            m_catNbrFont = -1;
            LoadFonts( ele );
        }

        ~AlbumBase( );

        int GetNbrChildren( );

//        virtual wxXmlNode* Write( wxXmlNode* parent ) = 0;

        void DeleteChild( AlbumBase* node );

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

        wxArrayString* GetErrorArray( ){ return &m_errorArray; };

        wxFont* GetTitleFont();

        wxFont* GetTextFont();

        wxFont* GetCatNbrFont();

    void LoadFonts( wxXmlNode* node );
  

    private:

        wxTreeItemId m_treeID;
        wxArrayString m_errorArray;
         
        // index of title font in FontArray
        int m_titleFont;
        // index of text font in FontArray
        int m_textFont;
        // index of catalog number font in FontArray
        int m_catNbrFont;

    protected:

    };
}
#endif
