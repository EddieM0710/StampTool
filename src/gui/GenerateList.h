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
 /////////////////////////////////////////////////////////////////////////////

#ifndef _GENERATELIST_H_
#define _GENERATELIST_H_


/*
 * Includes
 */

#include "wx/grid.h"

#include "Defs.h"
#include "gui/GuiDefs.h"

#include "catalog/Entry.h"
#include "utils/XMLUtilities.h"

 /*
  * Forward declarations
  */

  //
class wxGrid;
//
class GenerateListSettings;
/*
 * Control identifiers
 */

 //

#define SYMBOL_GENERATELIST_STYLE wxTAB_TRAVERSAL
#define SYMBOL_GENERATELIST_TITLE _( "GenerateList" )
#define SYMBOL_GENERATELIST_IDNAME ID_GENERATELIST
#define SYMBOL_GENERATELIST_SIZE wxSize( 400, 500 )
#define SYMBOL_GENERATELIST_POSITION wxDefaultPosition
//


/*
 * GenerateList class declaration
 */

class GenerateList: public wxPanel
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


    GenerateList( );
    GenerateList( wxWindow* parent, wxWindowID id = SYMBOL_GENERATELIST_IDNAME, const wxPoint& pos = SYMBOL_GENERATELIST_POSITION, const wxSize& size = SYMBOL_GENERATELIST_SIZE, long style = SYMBOL_GENERATELIST_STYLE );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_GENERATELIST_IDNAME, const wxPoint& pos = SYMBOL_GENERATELIST_POSITION, const wxSize& size = SYMBOL_GENERATELIST_SIZE, long style = SYMBOL_GENERATELIST_STYLE );


    ~GenerateList( );


    void Init( );


    void CreateControls( );

    //// GenerateList event handler declarations

    ////   ID_SETLISTPREFSBUTTON
    void OnSetListPrefsButtonClick( wxCommandEvent& event );

    bool CheckEmission( Catalog::Entry* entry );
    bool CheckFormat( Catalog::Entry* entry );
    bool CheckStatus( Catalog::Entry* entry );
    void WriteEntries( wxXmlNode* parent, int& row );
    void UpdateGrid( );
    void ShowRow( Catalog::Entry* entry, int row );
    int GetStringLen( wxFont& font, wxString text );


    ///   ID_WRITEBUTTON
    void OnWriteButtonClick( wxCommandEvent& event );

    ///   ID_FILENAMETEXTCTRL
    void OnFileNameTextUpdated( wxCommandEvent& event );

    //// GenerateList event handler declarations

    //// GenerateList member function declarations



    static bool ShowToolTips( );

    void DoListPrefs( );

    //// GenerateList member variables
    wxGrid* m_gridCtrl;
    wxButton* m_writeButton;
    wxTextCtrl* m_filename;
    //// GenerateList member variables
    GenerateListSettings* m_generateListSettings;

    int m_checkedStatusItems;
    int m_checkedFormatItems;
    int m_checkedEmissionItems;
    wxString m_fromYear;
    wxString m_toYear;
};

#endif
// _GENERATELIST_H_
