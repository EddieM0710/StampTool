/**
 * @file CatalogBase.h
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

#ifndef CatalogBase_h
#define CatalogBase_h


#include "catalog/CatalogDefs.h"
#include "wx/xml/xml.h"

namespace Catalog {
    /// @brief Base class for all catalog objects. The catalog objects are
    /// initialy loaded from the catalog XML or from a csv file.
    class CatalogBase
    {
    protected:

        CatalogBase( ) { };

    public:

        ///  @brief Construct a new Catalog Base object
        ///  
        ///  @param ele 
        CatalogBase( wxXmlNode* ele ) { SetXMLCatNode( ele ); };

        ///  @brief Destroy the Catalog Base object
        ///  
        ~CatalogBase( ) { SetXMLCatNode( ( wxXmlNode* ) 0 ); };

        ///  @brief Get the XML Node of the object
        ///  
        ///  @return wxXmlNode* 
        wxXmlNode* GetCatXMLNode( ) { return m_catXMLNode; };

        ///  @brief Get the First xml Child object of this node
        ///  
        ///  @return wxXmlNode* 
        wxXmlNode* GetFirstChild( ) { return m_catXMLNode->GetChildren( ); };

        ///  @brief Finds the attribute named name and returns its string value
        ///  
        ///  @param name 
        ///  @return wxString 
        wxString GetNodeAttrStr( wxString name );

        ///  @brief Finds the attribute named name and returns its double value
        ///  
        ///  @param name 
        ///  @return double 
        double GetNodeAttrDbl( wxString name );

        ///  @brief Get the node type object
        ///  
        ///  @param type 
        CatalogBaseType  GetNodeType( ) { return m_nodeType; };

        ///  @brief Sanity check on object instantiation
        ///  
        ///  @return true 
        ///  @return false 
        virtual bool IsOK( ) = 0;

        ///  @brief  The attribute named name with val
        ///  
        ///  @param name 
        ///  @param val 
        void SetNodeAttrStr( wxString name, wxString val );

        ///  @brief Set the Node Attr Dbl object
        ///  
        ///  @param name 
        ///  @param val 
        void SetNodeAttrDbl( wxString name, double val );

        ///  @brief Set the node type object
        ///  
        ///  @param type 
        void SetNodeType( CatalogBaseType type ) { m_nodeType = type; };

        ///  @brief Set the XML Node of the object
        ///  
        ///  @param node 
        void SetXMLCatNode( wxXmlNode* node ) { m_catXMLNode = node; };

    private:
        wxXmlNode* m_catXMLNode;
        CatalogBaseType m_nodeType;
    };
}
#endif