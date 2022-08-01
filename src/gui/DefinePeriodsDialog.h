/* 
 * @file src/gui/DefinePeriodsDialog.h
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-11
 *
 * @copyright Copyright (c) 2021  
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _DEFINEPERIODSDIALOG_H_
#define _DEFINEPERIODSDIALOG_H_


/*!
 * Includes
 */

// includes
// includes

/*!
 * Forward declarations
 */

// forward declarations
// forward declarations

/*!
 * Control identifiers
 */

// control identifiers
#define ID_DEFINEPERIODS 10000
#define ID_ANTIQUE 10002
#define ID_ANTIQUEYEAR 10003
#define ID_CLASSIC 10005
#define ID_MODERN 10008
#define ID_MODERNYEAR 10009
#define SYMBOL_DEFINEPERIODSDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_DEFINEPERIODSDIALOG_TITLE _("DefinePeriods")
#define SYMBOL_DEFINEPERIODSDIALOG_IDNAME ID_DEFINEPERIODS
#define SYMBOL_DEFINEPERIODSDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_DEFINEPERIODSDIALOG_POSITION wxDefaultPosition
// control identifiers


/*!
 * DefinePeriodsDialog class declaration
 */

class DefinePeriodsDialog: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( DefinePeriodsDialog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    DefinePeriodsDialog();
    DefinePeriodsDialog( wxWindow* parent, wxWindowID id = SYMBOL_DEFINEPERIODSDIALOG_IDNAME, const wxString& caption = SYMBOL_DEFINEPERIODSDIALOG_TITLE, const wxPoint& pos = SYMBOL_DEFINEPERIODSDIALOG_POSITION, const wxSize& size = SYMBOL_DEFINEPERIODSDIALOG_SIZE, long style = SYMBOL_DEFINEPERIODSDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_DEFINEPERIODSDIALOG_IDNAME, const wxString& caption = SYMBOL_DEFINEPERIODSDIALOG_TITLE, const wxPoint& pos = SYMBOL_DEFINEPERIODSDIALOG_POSITION, const wxSize& size = SYMBOL_DEFINEPERIODSDIALOG_SIZE, long style = SYMBOL_DEFINEPERIODSDIALOG_STYLE );

    /// Destructor
    ~DefinePeriodsDialog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

// DefinePeriodsDialog event handler declarations

    /// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_ANTIQUE
    void OnAntiqueTextUpdated( wxCommandEvent& event );

    /// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_ANTIQUEYEAR
    void OnAntiqueYearTextUpdated( wxCommandEvent& event );

    /// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_CLASSIC
    void OnClassicTextUpdated( wxCommandEvent& event );

    /// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_MODERN
    void OnModernTextUpdated( wxCommandEvent& event );

    /// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_MODERNYEAR
    void OnModernYearTextUpdated( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
    void OnCancelClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

// DefinePeriodsDialog event handler declarations

// DefinePeriodsDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
// DefinePeriodsDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();
    bool IsDirty( ) { return m_dirty; };

// DefinePeriodsDialog member variables
    wxTextCtrl* m_antiqueTextBox;
    wxTextCtrl* m_AntiqueYear;
    wxTextCtrl* m_classicTextBox;
    wxTextCtrl* m_modernTextBox;
    wxTextCtrl* m_modernYear;
// DefinePeriodsDialog member variables
   bool m_dirty;
};

#endif
    // _DEFINEPERIODSDIALOG_H_
