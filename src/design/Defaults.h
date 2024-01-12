/**
 * @file layout/PageDefaults.h
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

#ifndef Defaults_H
#define Defaults_H

#include "design/XMLBase.h"
#include "design/DesignDefs.h"


namespace Design {

    class Defaults : public XMLBase
    {
    public:
        Defaults( );

        Defaults( wxXmlNode* xmlNode );

        ~Defaults( );

        void SaveDefault( wxXmlNode* xmlNode, Design::AlbumAttrType type );

        void SetDefault( Design::AlbumAttrType type, wxString str );

        void SetDefaultDbl( Design::AlbumAttrType type, double str );

        void SetDefault( Design::AlbumAttrType type, bool val );

        wxString GetDefault( Design::AlbumAttrType type );

        double GetDefaultDbl( Design::AlbumAttrType type );

        bool GetDefaultBool( Design::AlbumAttrType type, bool defVal = false );

    protected:
        wxString ApplicationDefault[ AT_NbrAttrTypes ];

    };
};

#endif