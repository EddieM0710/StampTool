/* 
 * @file Settings.h
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-08-01
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
#ifndef Settings_h
#define Settings_h


#include "odt/ODTDefs.h"
#include <wx/xml/xml.h>

namespace ODT { 

    class Settings
    { 
    public:

        Settings( );
        ~Settings( ) { };
        bool Save( );

        wxXmlDocument* SettingsXML( ) { return m_settings; };
    private:
        wxXmlDocument* m_settings;
    };
}
#endif
