
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "ExportDialog.h"


IMPLEMENT_DYNAMIC_CLASS( ExportDialog, wxDialog )

BEGIN_EVENT_TABLE( ExportDialog, wxDialog )

END_EVENT_TABLE( )


ExportDialog::ExportDialog( wxWindow* parent,
    wxString caption,
    wxString dialogInstructionText,
    wxArrayString listComboBoxStrings )
{

    Init( );
    wxWindowID id = SYMBOL_EXPORTDIALOG_IDNAME;
    Create( parent, id, caption );
}


ExportDialog::ExportDialog( )
{
    Init( );
}

ExportDialog::ExportDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{

    Init( );
    Create( parent, id, caption, pos, size, style );
}

bool ExportDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}


ExportDialog::~ExportDialog( )
{

}


void ExportDialog::Init( )
{

}

void ExportDialog::CreateControls( )
{
    ExportDialog* theDialog = this;

    wxBoxSizer* mainVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( mainVerticalSizer );

    wxBoxSizer* staticHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    mainVerticalSizer->Add( staticHorizontalSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxBoxSizer* okCancelSizer = new wxBoxSizer( wxHORIZONTAL );
    mainVerticalSizer->Add( okCancelSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* cancelButton = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    okCancelSizer->Add( cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    okCancelSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* okButton = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    okCancelSizer->Add( okButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


}

bool ExportDialog::ShowToolTips( )
{
    return true;
}

