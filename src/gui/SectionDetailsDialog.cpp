/*
 * @file  SectionDetailsDialog.cpp
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

 
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "wx/imaglist.h"

#include "wx/notebook.h"

#include "gui/SectionDetailsDialog.h"
#include "gui/LabeledTextBox.h"
#include "gui/ToolData.h" 
#include "wx/filename.h"


/*
 * SectionDetailsDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( SectionDetailsDialog, wxDialog )


/*
 * SectionDetailsDialog event table definition
 */

    BEGIN_EVENT_TABLE( SectionDetailsDialog, wxDialog )

    // SectionDetailsDialog event table entries
    EVT_BUTTON( wxID_OK, SectionDetailsDialog::OnOkClick )
    // SectionDetailsDialog event table entries
    EVT_BUTTON( ID_DIRBUTTON, SectionDetailsDialog::OnDirClick )

    END_EVENT_TABLE( )
    ;

/*
 * SectionDetailsDialog constructors
 */

SectionDetailsDialog::SectionDetailsDialog( )
{ 
    Init( );
}

SectionDetailsDialog::SectionDetailsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{ 
    Init( );
    Create( parent, id, caption, pos, size, style );
}


/*
 * SectionDetailsDialog creator
 */

bool SectionDetailsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{ 
    // SectionDetailsDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    { 
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // SectionDetailsDialog creation
    return true;
}


/*
 * SectionDetailsDialog destructor
 */

SectionDetailsDialog::~SectionDetailsDialog( )
{ 
    // SectionDetailsDialog destruction
    // SectionDetailsDialog destruction
}


/*
 * Member initialisation
 */

void SectionDetailsDialog::Init( )
{ 
    // SectionDetailsDialog member initialisation
    m_name = NULL;
    m_imagePath = NULL;

    // SectionDetailsDialog member initialisation
}


/*
 * Control creation for SectionDetailsDialog
 */

void SectionDetailsDialog::CreateControls( )
{ 
    // SectionDetailsDialog content construction

    SectionDetailsDialog* theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    m_name = new LabeledTextBox( theDialog, ID_NAMELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_name->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    theDialogVerticalSizer->Add( m_name, 1, wxGROW | wxALL, 5 );

    //>> first section ctrls
   // wxBoxSizer* firstSectionHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
   // theDialogVerticalSizer->Add( firstSectionHorizontalSizer, 0, wxGROW | wxALL, 0 );

    wxBoxSizer* theDialogHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theDialogHorizontalSizer, 1, wxGROW | wxALL, 0 );

    m_imagePath = new LabeledTextBox( theDialog, ID_IMAGEPATHTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_imagePath->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    theDialogHorizontalSizer->Add( m_imagePath, 1, wxGROW | wxALL, 5 );

    wxButton* dirButton = new wxButton( theDialog, ID_DIRBUTTON, _( "Dir" ), wxDefaultPosition, wxDefaultSize, 0 );
    theDialogHorizontalSizer->Add( dirButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // wxBoxSizer* SecondSectionHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    // theDialogVerticalSizer->Add( SecondSectionHorizontalSizer, 0, wxGROW | wxALL, 5 );

    // wxStaticText* TitleFontStatic = new wxStaticText( theDialog, wxID_STATIC, _( "Title Font" ), wxDefaultPosition, wxDefaultSize, 0 );
    // SecondSectionHorizontalSizer->Add( TitleFontStatic, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // m_titleFontPicker = new wxFontPickerCtrl( theDialog, 12345, 
    //     *wxNORMAL_FONT, wxDefaultPosition, 
    //     wxDefaultSize, wxFNTP_DEFAULT_STYLE );
    // SecondSectionHorizontalSizer->Add( m_titleFontPicker, 5, wxGROW | wxALL, 5 );

    // m_titleColorPicker = new wxColourPickerCtrl( theDialog, 12346, 
    //     *wxBLACK, wxDefaultPosition, 
    //     wxDefaultSize, wxCLRP_DEFAULT_STYLE );
    // SecondSectionHorizontalSizer->Add( m_titleColorPicker, 1, wxGROW | wxALL, 5 );

    // wxButton* defaultButton = new wxButton( theDialog, ID_DEFAULTFONTBUTTON, _( "Default" ), wxDefaultPosition, wxDefaultSize, 0 );
    // SecondSectionHorizontalSizer->Add( defaultButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    // //>>error list ctrls

    // wxBoxSizer* errorListSizer = new wxBoxSizer( wxHORIZONTAL );
    // theDialogVerticalSizer->Add( errorListSizer, 2, wxGROW | wxALL, 5 );

    // m_statusList = new wxListCtrl( theDialog, ID_LISTCTRL, wxDefaultPosition, wxSize( 100, 100 ), wxLC_REPORT | wxLC_EDIT_LABELS | wxSIMPLE_BORDER );
    // errorListSizer->Add( m_statusList, 2, wxGROW | wxALL, 5 );
    // //<<error list ctrls

    //>>dialog Ctrl buttons
    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* cancelButton = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* okButton = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( okButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //>>dialog Ctrl buttons  
    m_name->SetLabel( "Name" );
    m_imagePath->SetLabel( "ImageName" );
}




bool SectionDetailsDialog::ShowToolTips( )
{ 
    return true;
}


/*
 *   wxID_OK
 */

void SectionDetailsDialog::OnOkClick( wxCommandEvent& event )
{ 
    event.Skip( );
 
}
void SectionDetailsDialog::OnDirClick( wxCommandEvent& event )
{ 
 wxDirDialog dirDialog( this, "Select the art directory", GetToolData( )->GetImagePath( ) );

         if ( dirDialog.ShowModal( ) == wxID_CANCEL )
            return;

        wxString filename = dirDialog.GetPath( );
        wxString sectFilename = GetCatalogSectionData( )->GetSectionFilename( );
        wxFileName vFn( sectFilename );
        vFn.ClearExt( );
        vFn.SetName( "" );
        wxFileName fn;
        fn.SetPath( filename );
        fn.ClearExt( );
        fn.SetName( "" );
        wxString str1 = vFn.GetPath( );
        wxString str2 = fn.GetPath( );
        fn.MakeRelativeTo( vFn.GetPath( ) );
        wxString str3 = fn.GetPath( );
        SetImagePath( fn.GetPath( ) );

}
void SectionDetailsDialog::SetNameModified( bool state ) { m_name->SetModified( state ); };
void SectionDetailsDialog::SetDesignTreeID( wxTreeItemId id ) { if ( id.IsOk( ) ) m_designTreeID = id; };
bool SectionDetailsDialog::IsNameModified( ) { return m_name->IsModified( ); };

wxString SectionDetailsDialog::GetName( ){ return m_name->GetValue( ); };
wxString SectionDetailsDialog::GetImagePath( ){ return m_imagePath->GetValue( ); };
void SectionDetailsDialog::SetName( wxString str )
{ 
    m_name->SetValue( str ); 
};
void SectionDetailsDialog::SetImagePath( wxString str )
{ 
    m_imagePath->SetValue( str ); 
};

// void SectionDetailsDialog::SetShowTitle( bool state ) { m_titleCheckbox->SetValue( state ); };
// void SectionDetailsDialog::SetShowFrame( bool state ) { m_frameCheckbox->SetValue( state ); };
// bool SectionDetailsDialog::GetShowTitle( ) { return m_titleCheckbox->IsChecked( ); };;
// bool SectionDetailsDialog::GetShowFrame( ) { return m_frameCheckbox->IsChecked( ); };
