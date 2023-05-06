/**
 * @file LabeledTextBox.cpp
 * @author Eddie Monroe ( )
 * @brief 
 * @version 0.1
 * @date 2021-02-25
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
 * 
 */



#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "gui/LabeledTextBox.h"
 
#include "Defs.h"
#include "catalog/Entry.h"

/*
 * LabeledTextBox type definition
 */

IMPLEMENT_DYNAMIC_CLASS( LabeledTextBox, wxPanel )
; // silly business; The above macro screws up the formatter

/*
 * LabeledTextBox event table definition
 */

BEGIN_EVENT_TABLE( LabeledTextBox, wxPanel )

EVT_TEXT( ID_LABELEDTEXTBOX_TEXTCTRL, LabeledTextBox::OnTextctrlTextUpdated )

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

/*
 *
 * LabeledTextBox constructors
 *
 */
LabeledTextBox::LabeledTextBox( )
{ 
    Init( );
}

/*
 *
 * LabeledTextBox constructors
 *
 */
LabeledTextBox::LabeledTextBox( wxWindow *parent, wxWindowID id, 
                                const wxPoint &pos, const wxSize &size, 
                                long style )
{ 
    m_parent = parent;
    m_id = id;
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 *
 *  LabledTextBox creator
 *
 */
bool LabeledTextBox::Create( wxWindow *parent, wxWindowID id, 
                             const wxPoint &pos, const wxSize &size, 
                             long style )
{ 
     // LabeledTextBox creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    { 
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
     // LabeledTextBox creation
    return true;
}

/*
 *
 * LabeledTextBox destructor
 *
 */
LabeledTextBox::~LabeledTextBox( )
{ 
     // LabeledTextBox destruction
     // LabeledTextBox destruction
}

/*
 *
 * Member initialisation
 *
 */
void LabeledTextBox::Init( )
{ 
     // LabeledTextBox member initialisation
    m_label = NULL;
    m_value = NULL;
    // LabeledTextBox member initialisation
}

/*
 *
 * Control creation for LabledTextBox
 *
  */
void LabeledTextBox::CreateControls( )
{ 
     // LabeledTextBox content construction

    LabeledTextBox *itemPanel1 = this;

    wxBoxSizer *itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    m_label = new wxStaticText( itemPanel1, wxID_STATIC, _( "Static text" ), 
                                  wxDefaultPosition, wxDefaultSize, 0 );

    itemBoxSizer1->Add( m_label, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 0 );

    m_value = new wxTextCtrl( itemPanel1, ID_LABELEDTEXTBOX_TEXTCTRL, wxEmptyString, 
                               wxDefaultPosition, wxSize( -1, 26 ), 0 );

    m_value->SetEditable( false );

    itemBoxSizer1->Add( m_value, 1, wxGROW | wxLEFT | wxRIGHT, 4 );

    // LabeledTextBox content construction

    SetEditable( true );

}


/*
 *
 * 
 *
 */
bool LabeledTextBox::ShowToolTips( )
{ 
    return true;
}


void LabeledTextBox::SetEditable( bool value )
{ 
       m_value->SetEditable( value );
}
/*
 *
 * Setup( wxString label, wxString value )
 * 
 */

void LabeledTextBox::Setup( wxString label, wxString value )
{ 
    m_label->SetLabelText( label );
    m_value->SetValue( value );
    m_value->SetModified( false );
}

/**
 * GetValue( )
 * 
 */

wxString LabeledTextBox::GetValue( )
{ 
    return m_value->GetValue( );
};

/*
 *
 *   ID_LABELEDTEXTBOX_TEXTCTRL
 *
 */

void LabeledTextBox::OnTextctrlTextUpdated( wxCommandEvent &event )
{ 
    event.SetClientData( ( void* )this );
    if ( m_value->IsModified( ) )
    { 
       // m_value->GetBackgroundColour( );
       // m_value->SetBackgroundColour( );
        SetDirty( );
//        m_stamp->SetAttr( m_type, m_idText->GetValue( ) );
        m_value->SetModified( true );
    }

    event.Skip( );

}
