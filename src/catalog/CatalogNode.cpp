/**
 * @file Node.cpp
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-02-28
 * 
 * @copyright Copyright (c) 2022
 * 
 **************************************************/

 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "catalog/CatalogNode.h"
#include "utils/XMLUtilities.h"

namespace Catalog {

    wxString CatalogNode::GetNodeAttrStr( wxString name ){ return Utils::GetAttrStr( m_Element, name) ;};
    double CatalogNode::GetNodeAttrDbl( wxString name ){ return Utils::GetAttrDbl( m_Element, name );};
    void CatalogNode::SetNodeAttrStr( wxString name, wxString val ){ Utils::SetAttrStr( m_Element, name, val );};
    void CatalogNode::SetNodeAttrDbl( wxString name, double val){  Utils::SetAttrDbl( m_Element, name, val );};

}
  