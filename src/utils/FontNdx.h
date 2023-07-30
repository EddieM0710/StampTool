/**
 * @file utils/FontNdX.h
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

#ifndef FontNdX_H
#define FontNdX_H

#include "design/DesignDefs.h"
#include "design/XMLBase.h"

 //#include <vector>



namespace Utils {

    class FontList;
    class Font;

    class FontNdx
    {
    public:


        FontNdx( );

        int Get( );

        void Set( int ndx );

        void MakeDefault( );
        bool IsOk( ) { return ( m_ndx >= 0 ); };
        Utils::Font* GetFont( );
    private:
        FontList* m_fontList;
        int m_ndx;
    };

}
#endif