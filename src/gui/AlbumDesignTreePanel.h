/*
 * @file AlbumDesignTreePanel.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-22
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

#ifndef _ALBUMPANEL_H_
#define _ALBUMPANEL_H_


 /*
  * Includes
  */
#include <vector>
#include "wx/treectrl.h"

#include "Defs.h"
#include "gui/GuiDefs.h"

/*
 * Forward declarations
 */
class DesignTreeCtrl;
class ReadAlbumEasyFile;

/*
 * Control identifiers
 */

#define SYMBOL_ALBUMDESIGNTREE_STYLE wxTAB_TRAVERSAL
#define SYMBOL_ALBUMDESIGNTREE_TITLE _( "AlbumPanel" )
#define SYMBOL_ALBUMDESIGNTREE_IDNAME ID_ALBUMDESIGNTREEPANEL
#define SYMBOL_ALBUMDESIGNTREE_SIZE wxSize( 400, 300 )
#define SYMBOL_ALBUMDESIGNTREE_POSITION wxDefaultPosition

/*
 * AlbumDesignTreePanel class declaration
 */

class AlbumDesignTreePanel: public wxPanel
{
    DECLARE_DYNAMIC_CLASS( AlbumDesignTreePanel )
        DECLARE_EVENT_TABLE( )

public:

        
        AlbumDesignTreePanel( );
    AlbumDesignTreePanel( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDESIGNTREE_IDNAME, const wxPoint& pos = SYMBOL_ALBUMDESIGNTREE_POSITION, const wxSize& size = SYMBOL_ALBUMDESIGNTREE_SIZE, long style = SYMBOL_ALBUMDESIGNTREE_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDESIGNTREE_IDNAME, const wxPoint& pos = SYMBOL_ALBUMDESIGNTREE_POSITION, const wxSize& size = SYMBOL_ALBUMDESIGNTREE_SIZE, long style = SYMBOL_ALBUMDESIGNTREE_STYLE );

    ~AlbumDesignTreePanel( );
    
    void Init( );

    void CreateControls( );
     
    static bool ShowToolTips( );

    void LoadAlbumLayout( );

    DesignTreeCtrl* GetDesignTreeCtrl( ) { return m_designTreeCtrl; };

private:
    DesignTreeCtrl* m_designTreeCtrl;

    };

#endif
