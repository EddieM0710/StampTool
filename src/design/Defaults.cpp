/**
 * @file Defaults.cpp
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
 */


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "utils/XMLUtilities.h"
#include "design/Defaults.h"


namespace Design {

    Defaults::Defaults( ) : XMLBase( ( wxXmlNode* ) 0 )
    {
        //ApplicationDefault.Alloc( AT_NbrAttrTypes );
        //  ApplicationDefault.Clear( );
    };

    Defaults::Defaults( wxXmlNode* xmlNode ) : XMLBase( xmlNode )
    {
        //ApplicationDefault.Alloc( AT_NbrAttrTypes );
        //  ApplicationDefault.Clear( );
    };

    Defaults::~Defaults( ){};


    void Defaults::Save( wxXmlNode* xmlNode, Design::AlbumAttrType type )
    {
        // don't save it if it is equal to the App default
        if ( !ApplicationDefault[ type ].IsEmpty( ) && !IsEqual( type, ApplicationDefault[ type ] ) )
            SetAttribute( xmlNode, type );
    }

    void Defaults::Set( Design::AlbumAttrType type, wxString str )
    {
        if ( str.IsEmpty( ) || IsEqual( type, ApplicationDefault[ type ] ) )
        {
            DeleteAttribute( AttrNameStrings[ type ] );
        }
        else
        {
            SetAttrStr( type, str );
        }
    }
    void Defaults::SetDbl( Design::AlbumAttrType type, double val )
    {
        double defVal;
        bool isOK = ApplicationDefault[ type ].ToDouble( &defVal );
        if ( isOK && IsEqualDbl( type, defVal ) )
        {
            DeleteAttribute( AttrNameStrings[ type ] );
        }
        else
        {
            SetAttrDbl( type, val );
        }
    }

    wxString Defaults::Get( Design::AlbumAttrType type )
    {
        wxString str = GetAttrStr( type );
        if ( str.IsEmpty( ) )
        {
            return ApplicationDefault[ type ];
        }
        else
        {
            return str;
        }
    }

    double Defaults::GetDbl( Design::AlbumAttrType type )
    {
        wxString str = GetAttrStr( type );
        if ( str.IsEmpty( ) )
        {
            double defVal;
            bool isOK = ApplicationDefault[ type ].ToDouble( &defVal );
            if ( isOK )
            {
                return defVal;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return GetAttrDbl( type );
        }
    }
}