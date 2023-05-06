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

#include "gui/GuiDefs.h"

#define SYMBOL_DEFINEPERIODSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_DEFINEPERIODSDIALOG_TITLE _( "DefinePeriods" )
#define SYMBOL_DEFINEPERIODSDIALOG_IDNAME ID_DEFINEPERIODSDIALOG
#define SYMBOL_DEFINEPERIODSDIALOG_SIZE wxSize( 400, 300 )
#define SYMBOL_DEFINEPERIODSDIALOG_POSITION wxDefaultPosition

class DefinePeriodsDialog : public wxDialog
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


    ///  @brief Construct a new Define Periods Dialog object
    ///  
    DefinePeriodsDialog( );

    ///  @brief Construct a new Define Periods Dialog object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param caption 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    DefinePeriodsDialog( wxWindow* parent, wxWindowID id = SYMBOL_DEFINEPERIODSDIALOG_IDNAME, const wxString& caption = SYMBOL_DEFINEPERIODSDIALOG_TITLE, const wxPoint& pos = SYMBOL_DEFINEPERIODSDIALOG_POSITION, const wxSize& size = SYMBOL_DEFINEPERIODSDIALOG_SIZE, long style = SYMBOL_DEFINEPERIODSDIALOG_STYLE );

    ///  @brief Destroy the Define Periods Dialog object
    ///  
    ~DefinePeriodsDialog( );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param caption 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    ///  @return true 
    ///  @return false 
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_DEFINEPERIODSDIALOG_IDNAME, const wxString& caption = SYMBOL_DEFINEPERIODSDIALOG_TITLE, const wxPoint& pos = SYMBOL_DEFINEPERIODSDIALOG_POSITION, const wxSize& size = SYMBOL_DEFINEPERIODSDIALOG_SIZE, long style = SYMBOL_DEFINEPERIODSDIALOG_STYLE );

    ///  @brief Create a Controls object
    ///  
    void CreateControls( );

    ///  @brief 
    ///  
    void Init( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsDirty( ) { return m_dirty; };

    ///  @brief 
    ///  
    ///  @param event 
    void OnAntiqueTextUpdated( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnAntiqueYearTextUpdated( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnCancelClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnClassicTextUpdated( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnModernTextUpdated( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnModernYearTextUpdated( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnOkClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    static bool ShowToolTips( );

private:

    wxTextCtrl* m_antiqueTextBox;
    wxTextCtrl* m_AntiqueYear;
    wxTextCtrl* m_classicTextBox;
    wxTextCtrl* m_modernTextBox;
    wxTextCtrl* m_modernYear;
    bool m_dirty;
};

#endif
