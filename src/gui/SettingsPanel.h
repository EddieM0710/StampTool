/* 
 * @file gui/SettingsPanel.h
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-12
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
 */

#ifndef _SETTINGSPANEL_H_
#define _SETTINGSPANEL_H_


/*!
 * Includes
 */

// includes
// includes

/*!
 * Forward declarations
 */

// forward declarations
class LabeledTextBox;
// forward declarations

/*!
 * Control identifiers
 */

// control identifiers
#define ID_SETTINGSPANEL 10000
#define ID_IMAGEDIRECTORTEXTBOX 11001
#define ID_COUNTRYTEXTBOX 11003
#define ID_CATALOGTEXTBOX 11004
#define ID_OPENLASTCHECKBOX 11005
#define SYMBOL_SETTINGSPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_SETTINGSPANEL_TITLE _( "SettingsPanel" )
#define SYMBOL_SETTINGSPANEL_IDNAME ID_SETTINGSPANEL
#define SYMBOL_SETTINGSPANEL_SIZE wxSize( 400, 200 )
#define SYMBOL_SETTINGSPANEL_POSITION wxDefaultPosition
// control identifiers


/*!
 * SettingsPanel class declaration
 */

class SettingsPanel: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( SettingsPanel )
    DECLARE_EVENT_TABLE( )

public:
    /// Constructors
    SettingsPanel( );
    SettingsPanel( wxWindow* parent, wxWindowID id = SYMBOL_SETTINGSPANEL_IDNAME, const wxPoint& pos = SYMBOL_SETTINGSPANEL_POSITION, const wxSize& size = SYMBOL_SETTINGSPANEL_SIZE, long style = SYMBOL_SETTINGSPANEL_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_SETTINGSPANEL_IDNAME, const wxPoint& pos = SYMBOL_SETTINGSPANEL_POSITION, const wxSize& size = SYMBOL_SETTINGSPANEL_SIZE, long style = SYMBOL_SETTINGSPANEL_STYLE );

    /// Destructor
    ~SettingsPanel( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );

// SettingsPanel event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
    void OnCancelClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

// SettingsPanel event handler declarations

// SettingsPanel member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
// SettingsPanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips( );

// SettingsPanel member variables
    LabeledTextBox* m_imageDirectory;
    LabeledTextBox* m_country;
    LabeledTextBox* m_catalog;
    wxCheckBox* m_loadLastFileAtStartUp;
// SettingsPanel member variables
};

#endif
    // _SETTINGSPANEL_H_
