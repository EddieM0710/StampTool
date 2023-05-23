/*
 * @file         GenerateList.h
 *@brief
* @author      Eddie Monroe
* Modified by:
* @author     Thu 08 Dec 2022 20:20:21 CST
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
 ///////////////////////////////////////

#ifndef _GENERATELIST_H_
#define _GENERATELIST_H_

#include "wx/grid.h"

#include "Defs.h"
#include "gui/GuiDefs.h"

#include "catalog/Entry.h"
#include "utils/XMLUtilities.h"

class wxGrid;

class GenerateListSettings;

#define SYMBOL_GENERATELIST_STYLE wxTAB_TRAVERSAL
#define SYMBOL_GENERATELIST_TITLE _( "GenerateList" )
#define SYMBOL_GENERATELIST_IDNAME ID_GENERATELIST
#define SYMBOL_GENERATELIST_SIZE wxSize( 400, 500 )
#define SYMBOL_GENERATELIST_POSITION wxDefaultPosition


class GenerateList : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( GenerateList )
        DECLARE_EVENT_TABLE( )

public:
    enum GenerateListGuiDefs
    {
        ID_SETLISTPREFSBUTTON = ID_GENERATELIST + 1,
        ID_GRIDCTRL,
        ID_WRITEBUTTON,
        ID_FILENAMETEXTCTRL,
    };


    ///  @brief Construct a new Generate List object
    ///  
    GenerateList( );

    ///  @brief Construct a new Generate List object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    GenerateList( wxWindow* parent, wxWindowID id = SYMBOL_GENERATELIST_IDNAME, const wxPoint& pos = SYMBOL_GENERATELIST_POSITION, const wxSize& size = SYMBOL_GENERATELIST_SIZE, long style = SYMBOL_GENERATELIST_STYLE );

    ///  @brief Destroy the Generate List object
    ///  
    ~GenerateList( );


    bool AddEntry( Catalog::Entry* entry );
    void ClearList( );

    ///  @brief 
    ///  
    ///  @param entry 
    ///  @return true 
    ///  @return false 
    bool CheckEmission( Catalog::Entry* entry );

    ///  @brief 
    ///  
    ///  @param entry 
    ///  @return true 
    ///  @return false 
    bool CheckFormat( Catalog::Entry* entry );

    ///  @brief 
    ///  
    ///  @param entry 
    ///  @return true 
    ///  @return false 
    bool CheckStatus( Catalog::Entry* entry );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    ///  @return true 
    ///  @return false 
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_GENERATELIST_IDNAME, const wxPoint& pos = SYMBOL_GENERATELIST_POSITION, const wxSize& size = SYMBOL_GENERATELIST_SIZE, long style = SYMBOL_GENERATELIST_STYLE );

    ///  @brief Create a Controls object
    ///  
    void CreateControls( );

    ///  @brief 
    ///  
    void DoListPrefs( );

    ///  @brief Get the String Len object
    ///  
    ///  @param font 
    ///  @param text 
    ///  @return int 
    int GetStringLen( wxFont& font, wxString text );

    ///  @brief 
    ///  
    void Init( );

    ///  @brief 
    ///  
    ///  @param event 
    void OnFileNameTextUpdated( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnSetListPrefsButtonClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnWriteButtonClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param entry 
    ///  @param row 
    void ShowRow( Catalog::Entry* entry, int row );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    static bool ShowToolTips( );

    ///  @brief 
    ///  
    void UpdateGrid( );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param row 
    void WriteEntries( wxXmlNode* parent, int& row );

private:
    wxGrid* m_gridCtrl;
    wxButton* m_writeButton;
    wxTextCtrl* m_filename;

    GenerateListSettings* m_generateListSettings;

    int m_checkedStatusItems;
    int m_checkedFormatItems;
    int m_checkedEmissionItems;
    wxString m_fromYear;
    wxString m_toYear;
    int m_currRow;
};

#endif

