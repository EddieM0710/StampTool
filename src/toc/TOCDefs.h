/**
 * @file TOCDefs.h
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
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
 * *
 */

#ifndef TOCDefs_h
#define TOCDefs_h

#include "wx/xml/xml.h"

namespace Utils {


    typedef enum
    {
        TOC_Section = 0,
        TOC_Volume,
        TOC_None,
        TOC_NbrTypes
    } TOCBaseType;

    TOCBaseType FindTOCBaseType( wxString name );
    TOCBaseType FindTOCBaseType( wxXmlNode* element );

    extern const wxString TOCBaseNames[ TOC_NbrTypes ];

}
#endif