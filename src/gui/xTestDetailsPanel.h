/*
 * @file TestDetailsPanel.h
 * @brief
 * @author Eddie Monroe
 * Modified by:
 * @date Wed 23 Nov 2022 11:31:39 CST
 *
 * @copyright Copyright ( c ) 2024
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
 //
 // @copyright Copyright ( c ) 2022 
 // 
 // This file is part of StampTool.
 //
 // StampTool is free software: you can redistribute it and/or modify it under the 
 // terms of the GNU General Public License as published by the Free Software Foundation, 
 // either version 3 of the License, or any later version.
 //
 // StampTool is distributed in the hope that it will be useful, but WITHOUT ANY 
 // WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 // PARTICULAR PURPOSE. See the GNU General Public License for more details.
 //
 // You should have received a copy of the GNU General Public License along with 
 // StampTool. If not, see <https://www.gnu.org/licenses/>.
 ///////////////////////////////////////

#ifndef _TestDetailsPanel_H_
#define _TestDetailsPanel_H_


#include "gui/GuiDefs.h"

#include "gui/HelperPanel.h"

class LabeledTextBox;
class wxListCtrl;
namespace Design {
    class Album;
};

#define SYMBOL_TestDetailsPanel_STYLE  wxTAB_TRAVERSAL
#define SYMBOL_TestDetailsPanel_TITLE _( "TestDetailsPanel" )
#define SYMBOL_TestDetailsPanel_IDNAME ID_ALBUMDETAILSDIALOG
#define SYMBOL_TestDetailsPanel_SIZE wxSize( 400, 300 )
#define SYMBOL_TestDetailsPanel_POSITION wxDefaultPosition
class TestDetailsPanel;

/// @brief
/// 
class TestDetailsPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( TestDetailsPanel )
    DECLARE_EVENT_TABLE( )

public:

    enum AlbumDetailDialogDefs {
        ID_NAMELABELEDTEXTBOX = 65432 + 1,

        // ID_LastID
    };

    /// @brief Construct a new Album Details Dialog object
    /// 
    TestDetailsPanel( );

    /// @brief Construct a new Album Details Dialog object
    /// 
    /// @param parent 
    /// @param id 
    /// @param caption 
    /// @param pos 
    /// @param size 
    /// @param style 
    TestDetailsPanel( wxWindow* parent, wxWindowID id = SYMBOL_TestDetailsPanel_IDNAME, const wxString& caption = SYMBOL_TestDetailsPanel_TITLE, const wxPoint& pos = SYMBOL_TestDetailsPanel_POSITION, const wxSize& size = SYMBOL_TestDetailsPanel_SIZE, long style = SYMBOL_TestDetailsPanel_STYLE );

    /// @brief Destroy the Album Details Dialog object
    /// 
    ~TestDetailsPanel( );

    /// @brief 
    /// 
    /// @param parent 
    /// @param id 
    /// @param caption 
    /// @param pos 
    /// @param size 
    /// @param style 
    /// @return true 
    /// @return false 
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_TestDetailsPanel_IDNAME, const wxString& caption = SYMBOL_TestDetailsPanel_TITLE, const wxPoint& pos = SYMBOL_TestDetailsPanel_POSITION, const wxSize& size = SYMBOL_TestDetailsPanel_SIZE, long style = SYMBOL_TestDetailsPanel_STYLE );

    /// @brief Create a Controls object
    /// 
    void CreateControls( );

    /// @brief 
    /// 
    void Init( );
    void SetupDialog( );

    void OnText( wxCommandEvent& event );

private:

    TestDetailsPanel* theDialog;
    wxTextCtrl* text;
    wxPanel* panel;
};

#endif
