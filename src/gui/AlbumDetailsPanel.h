/*
 * @file AlbumDetailsPanel.h
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

#ifndef _ALBUMDETAILSPANEL_H_
#define _ALBUMDETAILSPANEL_H_

#include "wx/listctrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/GuiDefs.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/FontPickerHelper.h"
#include "gui/HelperPanel.h"

class LabeledTextBox;
class wxListCtrl;

class AlbumDetailsPanel;

class FontDefaultsPanel;
class PageDefaultsPanel;
class FrameDefaultsPanel;
class StampDefaultsPanel;

namespace Design {
    class Album;
};

#define SYMBOL_ALBUMDETAILSPANEL_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_ALBUMDETAILSPANEL_TITLE _( "AlbumDetailsPanel" )
#define SYMBOL_ALBUMDETAILSPANEL_IDNAME ID_ALBUMDETAILSDIALOG
#define SYMBOL_ALBUMDETAILSPANEL_SIZE wxSize( -1, -1)
#define SYMBOL_ALBUMDETAILSPANEL_POSITION wxDefaultPosition



/// @brief
/// 
class AlbumDetailsPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( AlbumDetailsPanel )
    DECLARE_EVENT_TABLE( )

public:

    enum AlbumDetailDialogDefs {
        ID_NAMELABELEDTEXTBOX = ID_ALBUMDETAILSDIALOG + 1
    };

    AlbumDetailsPanel( );

    AlbumDetailsPanel( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSPANEL_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSPANEL_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSPANEL_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSPANEL_SIZE, long style = SYMBOL_ALBUMDETAILSPANEL_STYLE );

    ~AlbumDetailsPanel( );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSPANEL_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSPANEL_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSPANEL_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSPANEL_SIZE, long style = SYMBOL_ALBUMDETAILSPANEL_STYLE );

    void CreateControls( );

    void Init( );

    wxString GetName( );

    void OnNameClick( wxCommandEvent& event );

    void SetAlbum( Design::Album* album ) {
        m_album = album;
    };

    void SetupDialog( Design::Album* album );

    static bool ShowToolTips( );

    void UpdateControls( );

private:
    FontDefaultsPanel* m_fontDetailsPanel;
    PageDefaultsPanel* m_pageDetailsPanel;
    FrameDefaultsPanel* m_frameDetailsPanel;
    StampDefaultsPanel* m_stampDetailsPanel;

    wxTextCtrl* m_name;

    wxButton* m_validate;

    AlbumDetailsPanel* theDialog;
    Design::Album* m_album;
};

#endif
