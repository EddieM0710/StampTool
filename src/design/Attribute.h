/**
 * @file layout/Attribute.h
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

#ifndef Attribute_H
#define Attribute_H
#include <cstring>
#include <vector>

namespace Design { 

 /**
  * @brief Container for a Name/Value pair.
  *
  **************************************************/
class Attribute
{ 
public:
    /**
     * @brief Construct a new Attribute object
     *
     **************************************************/
    Attribute( ) { };
    /**
     * @brief Construct a new Attribute object
     *
     * @param name
     * @param value
     **************************************************/
    Attribute( const char* name, const char* value ) { 
        SetName( name );
        SetValue( value );
    };
    
    ~Attribute( ) { 
        delete m_name;
        delete m_value; 
    };

    /**
     * @brief Set the attribute Name
     *
     * @param name
     **************************************************/
    inline void SetName( const char* name ) { 
        m_name = ( char* ) malloc( strlen( name )+1 );
        strcpy ( m_name, name ); 
        };
    /**
     * @brief Get the attributes Name
     *
     * @return wxString
     **************************************************/
    inline char* GetName( ) { return m_name; };

    /**
     * @brief Set the attributes Value
     *
     * @param value
     **************************************************/
    inline void SetValue( const char* value ) {    
        m_value = ( char* )malloc( strlen( value )+1 );
        strcpy( m_value, value );
     };

    /**
     * @brief Get the attributes Value
     *
     * @return wxString
     **************************************************/
    inline char* GetValue( ) { return m_value; };

private:
    char* m_name;
    char* m_value;
};

typedef std::vector<Attribute*> LayoutAttributeArray;
}
#endif