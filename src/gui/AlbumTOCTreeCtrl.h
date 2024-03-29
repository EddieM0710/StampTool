/**
 * @file gui/CatalogAlbumTOCTreeCtrl.h
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
#ifndef AlbumTOCTreeCtrl_H
#define AlbumTOCTreeCtrl_H

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
class AlbumTOCTreeCtrl : public TOCTreeCtrl
{
    DECLARE_DYNAMIC_CLASS( AlbumTOCTreeCtrl )
    DECLARE_EVENT_TABLE( )

public:


    ///  @brief Construct a new Catalog Tree Ctrl object
    ///  
    AlbumTOCTreeCtrl( ) { }


    ///  @brief Construct a new Catalog Tree Ctrl object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    AlbumTOCTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );

    virtual ~AlbumTOCTreeCtrl( void ) { }

    VolumePtr FindVolume( wxString str );

    wxString GetVolumeName( VolumePtr catVolume );

    void LoadTree( );

    wxXmlNode* GetCurrVolumeRoot( );
    void OnSelChanged( wxTreeEvent& event );
    void LinkMenuItemToTreeItem( int id, wxTreeItemId treeId );
    void ReSortTree( ) {};
    void EditDetailsDialog( TOCTreeCtrl* parent );

};

#endif
