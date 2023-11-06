/**
 * @file Volume.h
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
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

#ifndef Volume_H
#define Volume_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <wx/treectrl.h>

#include <unordered_map>
#include <functional>

#include "Defs.h"
#include "utils/XMLUtilities.h"

 //namespace Utils { class ImageRepository; };

namespace Utils {

    class Volume;

    typedef std::unordered_map< std::string, Volume*  > VolumeArray;
    typedef std::unordered_map< int, wxTreeItemId > MenuIDArray;

    class Volume
    {
    public:

        Volume( wxString type );

        ~Volume( );

        bool  ContinueIfDirty( wxWindow* parent );

        bool operator>( Volume* rhs );

        bool operator<( Volume* rhs );

        wxString GetBaseName( );

        wxString GetFilename( ) {
            return m_filename;
        };

        wxXmlDocument* GetDoc( ) {
            return m_doc;
        };

        wxString GetName( );

        wxString GetPath( );

        bool IsDirty( ) {
            return m_dirty;
        };

        bool IsOK( );

        void Load( );

        void LoadXML( );

        wxXmlDocument* NewDocument( );

        wxXmlDocument* ReplaceDocument( wxXmlDocument* doc );

        virtual void Save( ) = 0;

        void SetDirty( bool state = true );

        void SetFilename( wxString name ) {
            m_filename = name;
        };

        void SetName( wxString str );

    private:
        wxString m_filename;
        wxXmlDocument* m_doc;
        wxString m_type;
        bool m_dirty;
    };

}
#endif