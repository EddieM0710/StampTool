/*
 * @file VolumeDetailsDialog.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
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

#ifndef _VOLUMEDETAILSDIALOG_H_
#define _VOLUMEDETAILSDIALOG_H_


 /*!
  * Includes
  */

  // includes
#include "wx/listctrl.h"
// includes

#include "gui/DesignTreeCtrl.h"
//#include <wx/fontpicker.h>
//#include <wx/clrpicker.h>


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
#define ID_VOLUMEDETAILSDIALOG 10000
#define ID_NAMELABELEDTEXTBOX 10009
#define ID_IMAGEPATHTEXTBOX 10023
#define ID_VOLUMETITLECHECKBOX 10004
#define ID_FRAMECHECKBOX 10006
#define ID_LISTCTRL 10006
#define ID_DEFAULTFONTBUTTON 10007
#define ID_VOLUMENAMEPANEL 10008
#define ID_VOLUMELAYOUTPANEL 10020
#define ID_VOLUMELAYOUTTEXTCTRL 10021
#define ID_VOLUMENOTEBOOK 10022
#define ID_DIRBUTTON 10024
#define SYMBOL_VOLUMEDETAILSDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_VOLUMEDETAILSDIALOG_TITLE _("Volume Details Dialog")
#define SYMBOL_VOLUMEDETAILSDIALOG_IDNAME ID_VOLUMEDETAILSDIALOG
#define SYMBOL_VOLUMEDETAILSDIALOG_SIZE wxSize(600, 400)
#define SYMBOL_VOLUMEDETAILSDIALOG_POSITION wxDefaultPosition
// control identifiers


/*!
 * VolumeDetailsDialog class declaration
 */

class VolumeDetailsDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( VolumeDetailsDialog )
        DECLARE_EVENT_TABLE( )

public:
    /// Constructors
    VolumeDetailsDialog( );
    VolumeDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_VOLUMEDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_VOLUMEDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_VOLUMEDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_VOLUMEDETAILSDIALOG_SIZE, long style = SYMBOL_VOLUMEDETAILSDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_VOLUMEDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_VOLUMEDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_VOLUMEDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_VOLUMEDETAILSDIALOG_SIZE, long style = SYMBOL_VOLUMEDETAILSDIALOG_STYLE );

    /// Destructor
    ~VolumeDetailsDialog( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );

    // VolumeDetailsDialog event handler declarations

        /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );
    void OnDirClick( wxCommandEvent& event );

    // VolumeDetailsDialog event handler declarations

    // VolumeDetailsDialog member function declarations

        /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
    // VolumeDetailsDialog member function declarations

        /// Should we show tooltips?
    static bool ShowToolTips( );
    void SetNameModified( bool state );
    void SetDesignTreeID( wxTreeItemId id );
    bool IsNameModified( );
    wxString GetName();
    wxString GetImagePath();
    void SetName(wxString str);
    void SetImagePath(wxString str);

    wxTreeItemId m_designTreeID;
    // VolumeDetailsDialog member variables
    LabeledTextBox* m_name;
    LabeledTextBox* m_imagePath;


    // VolumeDetailsDialog member variables

};

#endif
// _VOLUMEDETAILSDIALOG_H_
