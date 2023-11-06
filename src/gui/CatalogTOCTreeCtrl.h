/**
 * @file gui/CatalogCatalogTOCTreeCtrl.h
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
 */
#ifndef CatalogTOCTreeCtrl_H
#define CatalogTOCTreeCtrl_H

#include <wx/treectrl.h>
#include <wx/imaglist.h>
#include "gui/IconDefs.h"
#include "gui/GuiUtils.h"
#include "gui/TOCTreeCtrl.h"


class Stamp;

namespace Utils {
    class StampLink;
}


/**
 * @brief Class to manage a wxTreeCtrl for Stamp
 *
 */
class CatalogTOCTreeCtrl : public TOCTreeCtrl
{
    DECLARE_DYNAMIC_CLASS( CatalogTOCTreeCtrl )
    DECLARE_EVENT_TABLE( )

public:


    CatalogTOCTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );

    virtual ~CatalogTOCTreeCtrl( void ) { }


    void EditDetailsDialog( TOCTreeCtrl* parent );

    VolumePtr FindVolume( wxString str ){
        return ( VolumePtr ) GetCatalogData( )->GetCatalogList( )->FindVolume( str );
    };

    Catalog::CatalogVolume* GetCurrVolume( );

    wxXmlNode* GetCurrVolumeRoot( );

    CatalogTOCTreeCtrl* GetCatalogTOCTreeCtrl( ) {
        return GetCatalogData( )->GetCatalogTOCTreeCtrl( );
    };
    wxString GetVolumeName( VolumePtr catVolume ) {
        return ( ( Catalog::CatalogVolume* ) catVolume )->GetName( );
    };

    void LinkMenuItemToTreeItem( int id, wxTreeItemId treeId );

    void LoadTree( );

    void OnRightDClick( wxMouseEvent& event );

    void OnSelChanged( wxTreeEvent& event );

    void ReSortTree( );

};

#endif
