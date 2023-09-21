
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "RemoveVolumeDialog.h"


IMPLEMENT_DYNAMIC_CLASS( RemoveVolumeDialog, wxDialog )

BEGIN_EVENT_TABLE( RemoveVolumeDialog, wxDialog )

END_EVENT_TABLE( )


RemoveVolumeDialog::RemoveVolumeDialog( wxWindow* parent,
    wxString caption,
    wxString dialogInstructionText,
    wxArrayString listComboBoxStrings )
{
    m_listComboBoxStrings = listComboBoxStrings;
    m_dialogInstructionText = m_dialogInstructionText;
    Init( );
    wxWindowID id = SYMBOL_REMOVEVOLUMEDIALOG_IDNAME;
    Create( parent, id, caption );
}


RemoveVolumeDialog::RemoveVolumeDialog( )
{
    Init( );
}

RemoveVolumeDialog::RemoveVolumeDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    //  m_listComboBoxStrings = new wxArrayString( );

    Init( );
    Create( parent, id, caption, pos, size, style );
}

bool RemoveVolumeDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
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


RemoveVolumeDialog::~RemoveVolumeDialog( )
{

}


void RemoveVolumeDialog::Init( )
{

}

void RemoveVolumeDialog::CreateControls( )
{
    RemoveVolumeDialog* theDialog = this;

    wxBoxSizer* mainVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( mainVerticalSizer );

    wxBoxSizer* staticHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    mainVerticalSizer->Add( staticHorizontalSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxStaticText* diaogInstructionText = new wxStaticText( theDialog, wxID_STATIC, _( "Select the catalog to remove from project" ), wxDefaultPosition, wxDefaultSize, 0 );
    staticHorizontalSizer->Add( diaogInstructionText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0 );

    wxBoxSizer* listHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    mainVerticalSizer->Add( listHorizontalSizer, 0, wxGROW | wxALL, 5 );


    wxComboBox* listComboBox = new wxComboBox( theDialog, ID_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_listComboBoxStrings, wxCB_DROPDOWN );
    listHorizontalSizer->Add( listComboBox, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* radioButtonHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    mainVerticalSizer->Add( radioButtonHorizontalSizer, 0, wxGROW | wxALL, 5 );

    wxStaticBox* radioButtonStaticSizer = new wxStaticBox( theDialog, wxID_ANY, _( "Disposition" ) );
    wxStaticBoxSizer* radioButtonverticalSizer = new wxStaticBoxSizer( radioButtonStaticSizer, wxVERTICAL );
    radioButtonHorizontalSizer->Add( radioButtonverticalSizer, 1, wxGROW | wxALL, 5 );

    m_removeRadioButton = new wxRadioButton( radioButtonverticalSizer->GetStaticBox( ), ID_RADIOBUTTON, _( "Remove from Project" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_removeRadioButton->SetValue( false );
    radioButtonverticalSizer->Add( m_removeRadioButton, 0, wxALIGN_LEFT | wxALL, 5 );

    m_deleteRadioButton = new wxRadioButton( radioButtonverticalSizer->GetStaticBox( ), ID_RADIOBUTTON1, _( "Remove and Delete the file" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_deleteRadioButton->SetValue( false );
    radioButtonverticalSizer->Add( m_deleteRadioButton, 0, wxALIGN_LEFT | wxALL, 5 );

    wxBoxSizer* okCancelSizer = new wxBoxSizer( wxHORIZONTAL );
    mainVerticalSizer->Add( okCancelSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* cancelButton = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    okCancelSizer->Add( cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    okCancelSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* okButton = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    okCancelSizer->Add( okButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


}

bool RemoveVolumeDialog::ShowToolTips( )
{
    return true;
}

