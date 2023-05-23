/*
 * @file         GenerateListSettings.h
 *@brief
* @author      Eddie Monroe
* Modified by:
* @author     Fri 09 Dec 2022 14:55:49 CST
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


#ifndef _GENERATELISTSETTINGS_H_
#define _GENERATELISTSETTINGS_H_

#include "gui/GuiDefs.h"




#define SYMBOL_GENERATELISTSETTINGS_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_GENERATELISTSETTINGS_TITLE _( "GenerateListSettings" )
#define SYMBOL_GENERATELISTSETTINGS_IDNAME ID_GENERATELISTSETTINGS
#define SYMBOL_GENERATELISTSETTINGS_SIZE wxSize( 400, 500 )
#define SYMBOL_GENERATELISTSETTINGS_POSITION wxDefaultPosition



class GenerateListSettings : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( GenerateListSettings )
        DECLARE_EVENT_TABLE( )

public:
    enum GenerateListSettingsGuiDefs
    {
        ID_STATUSALLBUTTON = ID_GENERATELISTSETTINGS + 1,
        IDSTATUSCLEARBUTTON,
        ID_CHECKLISTBOX,
        ID_EMISSIONALLBUTTON,
        ID_EMISSIONCLEARBUTTON,
        ID_CHECKLISTBOX1,
        ID_FORMATALLBUTTON,
        ID_FORMATCLEARBUTTON,
        ID_CHECKLISTBOX2,
        ID_FROMYEARTEXTCTRL,
        ID_TOYEARTEXTCTRL,
        ID_CLEARYEARRANGEBUTTON
    };





    GenerateListSettings( );
    GenerateListSettings( wxWindow* parent, wxWindowID id = SYMBOL_GENERATELISTSETTINGS_IDNAME, const wxString& caption = SYMBOL_GENERATELISTSETTINGS_TITLE, const wxPoint& pos = SYMBOL_GENERATELISTSETTINGS_POSITION, const wxSize& size = SYMBOL_GENERATELISTSETTINGS_SIZE, long style = SYMBOL_GENERATELISTSETTINGS_STYLE );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_GENERATELISTSETTINGS_IDNAME, const wxString& caption = SYMBOL_GENERATELISTSETTINGS_TITLE, const wxPoint& pos = SYMBOL_GENERATELISTSETTINGS_POSITION, const wxSize& size = SYMBOL_GENERATELISTSETTINGS_SIZE, long style = SYMBOL_GENERATELISTSETTINGS_STYLE );


    ~GenerateListSettings( );


    void Init( );


    void CreateControls( );

    void OnStatusAllButtonClick( wxCommandEvent& event );

    void OnStatusClearButtonClick( wxCommandEvent& event );

    void OnEmissionAllButtonClick( wxCommandEvent& event );

    void OnFormatAllButtonClick( wxCommandEvent& event );

    void OnEmissionClearButtonClick( wxCommandEvent& event );

    void OnFormatClearButtonClick( wxCommandEvent& event );

    void OnClearYearRangeButtonClick( wxCommandEvent& event );

    void OnOkClick( wxCommandEvent& event );



    static bool ShowToolTips( );

    int MakeBitPatern( wxArrayInt& array );

    int GetCheckedStatusItems( );
    void SetCheckedStatusItems( int checkedStatusItems );
    int GetCheckedFormatItems( );
    void SetCheckedFormatItems( int checkedFormatItems );
    int GetCheckedEmissionItems( );
    void SetCheckedEmissionItems( int checkedEmissionItems );

    wxString GetFromYear( ) { return m_fromYear->GetValue( ); };
    void SetFromYear( wxString year ) { m_fromYear->SetValue( year ); };
    wxString GetToYear( ) { return m_toYear->GetValue( ); };
    void SetToYear( wxString year ) { m_toYear->SetValue( year ); };





    wxCheckListBox* m_statusListCtrl;
    wxArrayString m_statusListCtrlStrings;

    wxCheckListBox* m_emissionListCtrl;
    wxArrayString m_emissionListCtrlStrings;

    wxCheckListBox* m_formatListCtrl;
    wxArrayString m_formatListCtrlStrings;

    wxTextCtrl* m_fromYear;
    wxTextCtrl* m_toYear;


};

#endif
