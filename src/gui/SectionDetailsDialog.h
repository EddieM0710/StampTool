/*
 * @file SectionDetailsDialog.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-04-29
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

#ifndef _SECTIONDETAILSDIALOG_H_
#define _SECTIONDETAILSDIALOG_H_


 /*!
  * Includes
  */

#include "wx/listctrl.h"

#include "gui/DesignTreeCtrl.h"
#include "gui/GuiDefs.h"


  /*!
   * Forward declarations
   */

   // forward declarations
class LabeledTextBox;
class wxListCtrl;
// forward declarations

/*!
 * Control identifiers
 */

 // control identifiers

#define SYMBOL_SECTIONDETAILSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_SECTIONDETAILSDIALOG_TITLE _( "Section Details Dialog" )
#define SYMBOL_SECTIONDETAILSDIALOG_IDNAME ID_SECTIONDETAILSDIALOG
#define SYMBOL_SECTIONDETAILSDIALOG_SIZE wxSize( 600, 400 )
#define SYMBOL_SECTIONDETAILSDIALOG_POSITION wxDefaultPosition
// control identifiers


/*!
 * SectionDetailsDialog class declaration
 */

class SectionDetailsDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( SectionDetailsDialog )
        DECLARE_EVENT_TABLE( )

public:

    enum SectionDetailsDialogGuiDefs
    {

        ID_NAMELABELEDTEXTBOX = ID_SECTIONDETAILSDIALOG + 1,
        ID_IMAGEPATHTEXTBOX,
        ID_SECTIONTITLECHECKBOX,
        ID_FRAMECHECKBOX,
        ID_DEFAULTFONTBUTTON,
        ID_SECTIONNAMEPANEL,
        ID_SECTIONLAYOUTPANEL,
        ID_SECTIONLAYOUTTEXTCTRL,
        ID_SECTIONNOTEBOOK,
        ID_DIRBUTTON
    };
    /// Constructors
    SectionDetailsDialog( );
    SectionDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_SECTIONDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_SECTIONDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_SECTIONDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_SECTIONDETAILSDIALOG_SIZE, long style = SYMBOL_SECTIONDETAILSDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_SECTIONDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_SECTIONDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_SECTIONDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_SECTIONDETAILSDIALOG_SIZE, long style = SYMBOL_SECTIONDETAILSDIALOG_STYLE );

    /// Destructor
    ~SectionDetailsDialog( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );

    // SectionDetailsDialog event handler declarations

        /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );
    void OnDirClick( wxCommandEvent& event );

    // SectionDetailsDialog event handler declarations

    // SectionDetailsDialog member function declarations

        /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
    // SectionDetailsDialog member function declarations

        /// Should we show tooltips?
    static bool ShowToolTips( );
    void SetNameModified( bool state );
    void SetDesignTreeID( wxTreeItemId id );
    bool IsNameModified( );
    wxString GetName( );
    wxString GetImagePath( );
    void SetName( wxString str );
    void SetImagePath( wxString str );

    wxTreeItemId m_designTreeID;
    // SectionDetailsDialog member variables
    LabeledTextBox* m_name;
    LabeledTextBox* m_imagePath;


    // SectionDetailsDialog member variables

};

#endif
// _SECTIONDETAILSDIALOG_H_
