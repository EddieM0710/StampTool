/*
 * @file src/gui/DefinePeriodsDialog.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-11
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

#ifndef _DEFINEPERIODSDIALOG_H_
#define _DEFINEPERIODSDIALOG_H_


 /*
 * Includes
 */

#include "gui/GuiDefs.h"


 /*
 * Forward declarations
 */




 /*
 * Control identifiers
 */



#define SYMBOL_DEFINEPERIODSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_DEFINEPERIODSDIALOG_TITLE _( "DefinePeriods" )
#define SYMBOL_DEFINEPERIODSDIALOG_IDNAME ID_DEFINEPERIODSDIALOG
#define SYMBOL_DEFINEPERIODSDIALOG_SIZE wxSize( 400, 300 )
#define SYMBOL_DEFINEPERIODSDIALOG_POSITION wxDefaultPosition



 /*
 * DefinePeriodsDialog class declaration
 */

class DefinePeriodsDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( DefinePeriodsDialog )
        DECLARE_EVENT_TABLE( )

public:
    enum DefinePeriodsDialogGuiDefs
    {
        ID_DEFINEPERIODS = ID_DEFINEPERIODSDIALOG + 1,
        ID_ANTIQUE,
        ID_ANTIQUEYEAR,
        ID_CLASSIC,
        ID_MODERN,
        ID_MODERNYEAR
    };


    DefinePeriodsDialog( );
    DefinePeriodsDialog( wxWindow* parent, wxWindowID id = SYMBOL_DEFINEPERIODSDIALOG_IDNAME, const wxString& caption = SYMBOL_DEFINEPERIODSDIALOG_TITLE, const wxPoint& pos = SYMBOL_DEFINEPERIODSDIALOG_POSITION, const wxSize& size = SYMBOL_DEFINEPERIODSDIALOG_SIZE, long style = SYMBOL_DEFINEPERIODSDIALOG_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_DEFINEPERIODSDIALOG_IDNAME, const wxString& caption = SYMBOL_DEFINEPERIODSDIALOG_TITLE, const wxPoint& pos = SYMBOL_DEFINEPERIODSDIALOG_POSITION, const wxSize& size = SYMBOL_DEFINEPERIODSDIALOG_SIZE, long style = SYMBOL_DEFINEPERIODSDIALOG_STYLE );

    ~DefinePeriodsDialog( );

    void Init( );

    void CreateControls( );

    void OnAntiqueTextUpdated( wxCommandEvent& event );
    void OnAntiqueYearTextUpdated( wxCommandEvent& event );
    void OnClassicTextUpdated( wxCommandEvent& event );
    void OnModernTextUpdated( wxCommandEvent& event );
    void OnModernYearTextUpdated( wxCommandEvent& event );
    void OnCancelClick( wxCommandEvent& event );
    void OnOkClick( wxCommandEvent& event );


    static bool ShowToolTips( );
    bool IsDirty( ) { return m_dirty; };

    wxTextCtrl* m_antiqueTextBox;
    wxTextCtrl* m_AntiqueYear;
    wxTextCtrl* m_classicTextBox;
    wxTextCtrl* m_modernTextBox;
    wxTextCtrl* m_modernYear;
    bool m_dirty;
};

#endif
// _DEFINEPERIODSDIALOG_H_
