/*
 * @file src/gui/DefinePeriodsPanel.h
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

#ifndef _DEFINEPERIODSPANEL_H_
#define _DEFINEPERIODSPANEL_H_

#include "gui/GuiDefs.h"

#define SYMBOL_DEFINEPERIODSPANEL_STYLE  wxTAB_TRAVERSAL
#define SYMBOL_DEFINEPERIODSPANEL_TITLE _( "DefinePeriods" )
#define SYMBOL_DEFINEPERIODSPANEL_IDNAME ID_DEFINEPERIODSPANEL
#define SYMBOL_DEFINEPERIODSPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_DEFINEPERIODSPANEL_POSITION wxDefaultPosition

class DefinePeriodsPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( DefinePeriodsPanel )
        DECLARE_EVENT_TABLE( )

public:
    enum DefinePeriodsPanelGuiDefs
    {
        ID_DEFINEPERIODS = ID_DEFINEPERIODSPANEL + 1,
        ID_ANTIQUE,
        ID_ANTIQUEYEAR,
        ID_CLASSIC,
        ID_MODERN,
        ID_MODERNYEAR
    };

    ///  @brief Construct a new Define Periods Panel object
    ///  
    DefinePeriodsPanel( );

    ///  @brief Construct a new Define Periods Panel object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    DefinePeriodsPanel( wxWindow* parent, wxWindowID id = SYMBOL_DEFINEPERIODSPANEL_IDNAME, const wxPoint& pos = SYMBOL_DEFINEPERIODSPANEL_POSITION, const wxSize& size = SYMBOL_DEFINEPERIODSPANEL_SIZE, long style = SYMBOL_DEFINEPERIODSPANEL_STYLE );

    ///  @brief Destroy the Define Periods Panel object
    ///  
    ~DefinePeriodsPanel( );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    ///  @return true 
    ///  @return false 
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_DEFINEPERIODSPANEL_IDNAME, const wxPoint& pos = SYMBOL_DEFINEPERIODSPANEL_POSITION, const wxSize& size = SYMBOL_DEFINEPERIODSPANEL_SIZE, long style = SYMBOL_DEFINEPERIODSPANEL_STYLE );

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
    void OnOkClick( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    static bool ShowToolTips( );

private:
    // DefinePeriodsPanel member variables
    wxTextCtrl* m_antiqueTextBox;
    wxTextCtrl* m_AntiqueYear;
    wxTextCtrl* m_classicTextBox;
    wxTextCtrl* m_modernTextBox;
    wxTextCtrl* m_modernYear;
    // DefinePeriodsPanel member variables
    bool m_dirty;
};

#endif
// _DEFINEPERIODSPANEL_H_
