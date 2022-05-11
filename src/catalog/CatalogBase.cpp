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

#include "catalog/CatalogBase.h"
#include "utils/XMLUtilities.h"

namespace Catalog {

    wxString CatalogBase::GetNodeAttrStr( wxString name ){ return Utils::GetAttrStr( m_catXMLNode, name) ;};
    double CatalogBase::GetNodeAttrDbl( wxString name ){ return Utils::GetAttrDbl( m_catXMLNode, name );};
    void CatalogBase::SetNodeAttrStr( wxString name, wxString val ){ Utils::SetAttrStr( m_catXMLNode, name, val );};
    void CatalogBase::SetNodeAttrDbl( wxString name, double val){  Utils::SetAttrDbl( m_catXMLNode, name, val );};

}
  