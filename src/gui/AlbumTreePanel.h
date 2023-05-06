/*
 * @file AlbumTreePanel.h
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
class AlbumTreeCtrl;
class ReadAlbumEasyFile;

/*
 * Control identifiers
 */

#define SYMBOL_ALBUMDESIGNTREE_STYLE wxTAB_TRAVERSAL
#define SYMBOL_ALBUMDESIGNTREE_TITLE _( "AlbumPanel" )
#define SYMBOL_ALBUMDESIGNTREE_IDNAME ID_albumTreePanel
#define SYMBOL_ALBUMDESIGNTREE_SIZE wxSize( 400, 300 )
#define SYMBOL_ALBUMDESIGNTREE_POSITION wxDefaultPosition

 /*
  * AlbumTreePanel class declaration
  */

class AlbumTreePanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( AlbumTreePanel )
        DECLARE_EVENT_TABLE( )

public:

    ///  @brief Construct a new Album Design Tree Panel object
    ///  
    AlbumTreePanel( );

    ///  @brief Construct a new Album Design Tree Panel object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    AlbumTreePanel( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDESIGNTREE_IDNAME, const wxPoint& pos = SYMBOL_ALBUMDESIGNTREE_POSITION, const wxSize& size = SYMBOL_ALBUMDESIGNTREE_SIZE, long style = SYMBOL_ALBUMDESIGNTREE_STYLE );

    ///  @brief Destroy the Album Design Tree Panel object
    ///  
    ~AlbumTreePanel( );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    ///  @return true 
    ///  @return false 
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDESIGNTREE_IDNAME, const wxPoint& pos = SYMBOL_ALBUMDESIGNTREE_POSITION, const wxSize& size = SYMBOL_ALBUMDESIGNTREE_SIZE, long style = SYMBOL_ALBUMDESIGNTREE_STYLE );

    ///  @brief Create a Controls object
    ///  
    void CreateControls( );

    ///  @brief Get the Design Tree Ctrl object
    ///  
    ///  @return AlbumTreeCtrl* 
    AlbumTreeCtrl* GetAlbumTreeCtrl( ) { return m_albumTreeCtrl; };

    ///  @brief 
    ///  
    void Init( );

    ///  @brief 
    ///  
    void LoadAlbumLayout( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    static bool ShowToolTips( );





private:
    AlbumTreeCtrl* m_albumTreeCtrl;

};

#endif
