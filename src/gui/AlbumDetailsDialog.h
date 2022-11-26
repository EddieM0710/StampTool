/////////////////////////////////////////////////////////////////////////////
// Name:        AlbumDetailsDialog.h
// Purpose:     
// Author:      Eddie Monroe
// Modified by: 
// Created:     Wed 23 Nov 2022 11:31:39 CST
// RCS-ID:      
// Copyright:   
// Licence:     
//
// @copyright Copyright (c) 2022  
// 
// This file is part of AlbumGenerator.
//
// AlbumGenerator is free software: you can redistribute it and/or modify it under the 
// terms of the GNU General Public License as published by the Free Software Foundation, 
// either version 3 of the License, or any later version.
//
// AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
// PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with 
// AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////////

#ifndef _ALBUMDETAILSDIALOG_H_
#define _ALBUMDETAILSDIALOG_H_

// includes
#include "wx/listctrl.h"
// includes

#include "gui/DesignTreeCtrl.h"

/*!
 * Forward declarations
 */

// forward declarations
class LabeledTextBox;
class wxListCtrl;
// forward declarations



//// control identifiers
#define ID_ALBUMDETAILSDIALOG 10000
#define ID_NAMELABELEDTEXTBOX 10009
#define ID_HEIGHTLABELEDTEXTBOX 10001
#define ID_WIDTHLABELEDTEXTBOX 10002
#define ID_TOPMARGINLABELEDTEXTBOX 10007
#define ID_BOTTOMMARGINLABELEDTEXTBOX 10010
#define ID_RIGHTMARGINLABELEDTEXTBOX 10003
#define ID_LEFTMARGINLABELEDTEXTBOX 10004
#define ID_BORDERSIZELABELEDTEXTBOX 10011
#define ID_REFRESHBUTTON 10005
#define ID_VALIDATEBUTTON 10008
#define ID_LISTCTRL 10006
#define ID_CATNBRDEFAULTCHECKBOX 10012
#define ID_STAMPTITLEDEFAULTCHECKBOX 10013
#define ID_ROWCOLTITLEDEFAULTCHECKBOX 10014
#define ID_FRAMEDEFAULTCHECKBOX 10015
#define SYMBOL_ALBUMDETAILSDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_ALBUMDETAILSDIALOG_TITLE _("AlbumDetailsDialog")
#define SYMBOL_ALBUMDETAILSDIALOG_IDNAME ID_ALBUMDETAILSDIALOG
#define SYMBOL_ALBUMDETAILSDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_ALBUMDETAILSDIALOG_POSITION wxDefaultPosition
//// control identifiers


//
// AlbumDetailsDialog class declaration
//

class AlbumDetailsDialog: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( AlbumDetailsDialog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    AlbumDetailsDialog();
    AlbumDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSDIALOG_SIZE, long style = SYMBOL_ALBUMDETAILSDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSDIALOG_SIZE, long style = SYMBOL_ALBUMDETAILSDIALOG_STYLE );

    /// Destructor
    ~AlbumDetailsDialog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

//// AlbumDetailsDialog event handler declarations

//// AlbumDetailsDialog event handler declarations

//// AlbumDetailsDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
//// AlbumDetailsDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();
void SetName( wxString name );
void SetPageHeight( wxString height );
void SetPageWidth( wxString width );
void SetTopMargin( wxString margin );
void SetBottomMargin( wxString margin );
void SetLeftMargin( wxString margin );
void SetRightMargin( wxString margin );
void SetBorderSize( wxString size );
void SetShowCatNbr( bool state);
void SetShowStampTitle( bool state);

wxString GetName( );
wxString GetPageHeight( ) ;
wxString GetPageWidth(   );
wxString GetTopMargin( );
wxString GetBottomMargin( );
wxString GetLeftMargin(  );
wxString GetRightMargin( );
wxString GetBorderSize( );
bool GetShowCatNbr( );
bool GetShowStampTitle( );

bool IsNameModified( );
bool IsPageHeightModified( ) ;
bool IsPageWidthModified(   );
bool IsTopMarginModified( );
bool IsBottomMarginModified( );
bool IsLeftMarginModified(  );
bool IsRightMarginModified( );
bool IsBorderSizeModified( );
//bool IsShowCatNbrModified( );
//bool IsShowStampTitleModified( );



void SetNameModified( bool state ) ;
void SetPageHeightModified( bool state ) ;
void SetPageWidthModified( bool state );
void SetTopMarginModified( bool state );
void SetBottomMarginModified( bool state );
void SetLeftMarginModified( bool state );
void SetRightMarginModified( bool state );
void SetBorderSizeModified( bool state );
//void SetShowCatNbrModified( bool state );
//void SetShowStampTitleModified( bool state );

void OnOkClick( wxCommandEvent& event );
void OnCancelClick( wxCommandEvent& event );


//// AlbumDetailsDialog member variables
    LabeledTextBox* m_name;
    LabeledTextBox* m_height;
    LabeledTextBox* m_width;
    LabeledTextBox* m_topMargin;
    LabeledTextBox* m_bottomMargin;
    LabeledTextBox* m_rightMargin;
    LabeledTextBox* m_leftMargin;
    LabeledTextBox* m_borderSize;

wxCheckBox* m_catNbrCheckbox;
wxCheckBox* m_stampTitleCheckbox;
   
wxButton* m_validate;
    wxListCtrl* m_statusList;
//// AlbumDetailsDialog member variables
};

#endif
    // _ALBUMDETAILSDIALOG_H_
