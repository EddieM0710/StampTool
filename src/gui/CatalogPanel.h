/* 
 * @file src/gui/CatalogPanel.h
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-22
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

#ifndef _CATALOGSECTIONDATAPANEL_H_
#define _CATALOGSECTIONDATAPANEL_H_


/*!
 * Includes
 */

// includes
#include "wx/treectrl.h"
// includes
#include <wx/tglbtn.h>

#include "Defs.h"
#include "gui/GuiDefs.h"

#include "utils/Project.h"
#include "CatalogSectionData.h"
/*!
 * Forward declarations
 */

// forward declarations
class CatalogTreeCtrl;
// forward declarations

class Stamp;

/*!
 * Control identifiers
 */

// control identifiers
#define ID_CATALOGSECTIONDATAPANEL 10000
#define ID_TEXTCTRL 10007
#define ID_TREECTRL 10010
#define ID_NEXTBUTTON 11010
#define ID_CHECKLISTBOX 11011
#define ID_SEARCHSTRINGTEXTCTRL 11012
#define ID_TOGGLEBUTTON 11013
#define ID_SECTIONCHOICE 11014
#define SYMBOL_CATALOGSECTIONDATAPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_CATALOGSECTIONDATAPANEL_TITLE _( "CatalogPanel" )
#define SYMBOL_CATALOGSECTIONDATAPANEL_IDNAME ID_CATALOGSECTIONDATAPANEL
#define SYMBOL_CATALOGSECTIONDATAPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_CATALOGSECTIONDATAPANEL_POSITION wxDefaultPosition
// control identifiers


/*!
 * CatalogPanel class declaration
 */

class CatalogPanel: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( CatalogPanel )
    DECLARE_EVENT_TABLE( )

public:
    /// Constructors
    CatalogPanel( );
    CatalogPanel( wxWindow* parent, 
    wxWindowID id = SYMBOL_CATALOGSECTIONDATAPANEL_IDNAME, 
    const wxPoint& pos = SYMBOL_CATALOGSECTIONDATAPANEL_POSITION, 
    const wxSize& size = SYMBOL_CATALOGSECTIONDATAPANEL_SIZE, 
    long style = SYMBOL_CATALOGSECTIONDATAPANEL_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGSECTIONDATAPANEL_IDNAME, const wxPoint& pos = SYMBOL_CATALOGSECTIONDATAPANEL_POSITION, const wxSize& size = SYMBOL_CATALOGSECTIONDATAPANEL_SIZE, long style = SYMBOL_CATALOGSECTIONDATAPANEL_STYLE );

    /// Destructor
    ~CatalogPanel( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );

// CatalogPanel event handler declarations

    /// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL
    void OnTextctrlTextUpdated( wxCommandEvent& event );

    void OnTogglebuttonClick( wxCommandEvent& event );

    void OnSectionChoiceSelected( wxCommandEvent& event );

// CatalogPanel event handler declarations

// CatalogPanel member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
// CatalogPanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips( );

    void InitCatalogSectionData( );
    CatalogTreeCtrl* GetCatalogTree( ) { return m_catalogTreeCtrl; };

    void SetSectionListStrings( wxArrayString& choices )
    { 
        m_sectionListCtrl->Clear( );
        m_sectionListCtrl->Append( choices );
    };

    void SetSectionListSelection( int i )
    { 
        m_sectionListCtrl->SetSelection( i );
    };

   // wxTextCtrl* m_title;
    wxChoice* m_sectionListCtrl;
    CatalogTreeCtrl* m_catalogTreeCtrl;
  
    wxTreeItemId m_draggedItem;
    wxBoxSizer* m_searchSizer;
    wxBoxSizer* m_catPanelSizer;
    wxToggleButton* m_toggleButton;
};

#endif
    // _CATALOGSECTIONDATAPANEL_H_
