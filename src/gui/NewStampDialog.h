/*
 * @file NewStampDialog.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-06-03
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

#ifndef _NEWSTAMPDIALOG_H_
#define _NEWSTAMPDIALOG_H_


 /*!
  * Includes
  */

#include "catalog/Entry.h"
#include "gui/GuiDefs.h"

  /*!
   * Forward declarations
   */
class LabeledTextBox;

/*!
 * Control identifiers
 */

 // control identifiers
#define SYMBOL_NEWSTAMPDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_NEWSTAMPDIALOG_TITLE _( "New Stamp Dialog" )
#define SYMBOL_NEWSTAMPDIALOG_IDNAME ID_NEWSTAMPDIALOG
#define SYMBOL_NEWSTAMPDIALOG_SIZE wxSize( 400, 300 )
#define SYMBOL_NEWSTAMPDIALOG_POSITION wxDefaultPosition
// control identifiers


/*!
 * NewStampDialog class declaration
 */

class NewStampDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( NewStampDialog )
        DECLARE_EVENT_TABLE( )

public:
    enum NewStampDialogGuiDefs
    {
        ID_IDLABELEDTEXTBOX = ID_NEWSTAMPDIALOG + 1,
        ID_NAMELABELEDTEXTBOX,
        ID_EMISSIONCHOICE,
        ID_FORMATCHOICE,
        ID_ISSUEDTEXTBOX,
        ID_COUNTRYTEXTBOX,
        ID_CATALOGTEXTBOX,
        ID_CATNBRTEXTBOX,
        ID_WIDTHTEXTBOX,
        ID_HEIGHTTEXTBOX
    };
    /// Constructors
    NewStampDialog( );
    NewStampDialog( wxWindow* parent, wxWindowID id = SYMBOL_NEWSTAMPDIALOG_IDNAME, const wxString& caption = SYMBOL_NEWSTAMPDIALOG_TITLE, const wxPoint& pos = SYMBOL_NEWSTAMPDIALOG_POSITION, const wxSize& size = SYMBOL_NEWSTAMPDIALOG_SIZE, long style = SYMBOL_NEWSTAMPDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_NEWSTAMPDIALOG_IDNAME, const wxString& caption = SYMBOL_NEWSTAMPDIALOG_TITLE, const wxPoint& pos = SYMBOL_NEWSTAMPDIALOG_POSITION, const wxSize& size = SYMBOL_NEWSTAMPDIALOG_SIZE, long style = SYMBOL_NEWSTAMPDIALOG_STYLE );

    /// Destructor
    ~NewStampDialog( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );

    // NewStampDialog event handler declarations

        /// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_EMISSIONCHOICE
    void OnEmissionchoiceSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_FORMATCHOICE
    void OnFormatchoiceSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
    void OnCancelClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

    // NewStampDialog event handler declarations

    // NewStampDialog member function declarations

        /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
    // NewStampDialog member function declarations

        /// Should we show tooltips?
    static bool ShowToolTips( );

    void UpdateStamp( );
    void SetChoice( wxChoice* ctrl, wxString str );
    void SetStamp( Catalog::Entry* stamp );


    // NewStampDialog member variables
    LabeledTextBox* m_ID;
    LabeledTextBox* m_name;
    wxChoice* m_emission;
    wxChoice* m_format;
    LabeledTextBox* m_issueDate;
    LabeledTextBox* m_country;
    LabeledTextBox* m_catalog;
    LabeledTextBox* m_catNbr;
    LabeledTextBox* m_width;
    LabeledTextBox* m_height;
    Catalog::Entry* m_stamp;              ///< Pointer to currently displayed stamp

    // NewStampDialog member variables
};

#endif
// _NEWSTAMPDIALOG_H_
