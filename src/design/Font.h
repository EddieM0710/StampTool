/**
 * @file layout/Font.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
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
 **************************************************/

#ifndef Font_H
#define Font_H

#include "design/DesignDefs.h"

namespace Design {

    /**
     * @brief Font layout object; In
     *
     **************************************************/
    class Font : public LayoutBase
    {
    public:

        // font frame constructor
        /**
         * @brief Construct a new Font frame object.
         *
         * @param parent
         **************************************************/
        Font( wxXmlNode* node ){ SetNodeType( AT_Font ); };

        /**
         * @brief Destroy the Font object
         *
         **************************************************/
        ~Font( ) {};



        // build the frame container for the font

        /**
         * @brief Decends into each child layout object performing its write to the content, styles, or images ODT XML
         *
         **************************************************/
        wxXmlNode* Write( wxXmlNode* parent );


        void Save( wxXmlNode* xmlNode );

    private:
        wxString m_type;
        wxString m_name;
        wxString m_family;
        wxString m_size;
        wxString m_weight;
        wxString m_color;
        wxString m_style,

    };
}

#endif