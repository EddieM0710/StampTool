/*
 * @file         HelperPanel.cpp
 *@brief
* @author      Eddie Monroe
* Modified by:
* @author     Wed 23 Nov 2022 12:01:34 CST
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
 ///////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

//  includes
#include "wx/imaglist.h"
//  includes

#include "gui/HelperPanel.h"
//#include "gui/LabeledTextBox.h"

#include "design/DesignDefs.h"

#include "utils/Settings.h"

#include "Defs.h"


IMPLEMENT_DYNAMIC_CLASS( HelperPanel, wxPanel )

BEGIN_EVENT_TABLE( HelperPanel, wxPanel )

END_EVENT_TABLE( )

//--------------

HelperPanel::HelperPanel( )
{
    Init( );
}

//--------------

HelperPanel::HelperPanel( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

//--------------

HelperPanel::~HelperPanel( )
{
}

void HelperPanel::Init( )
{

}


//--------------

bool HelperPanel::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    //  wxDialog::Create( parent, id, caption, pos, size, style );
    wxPanel::Create( parent, id, pos, size, style );

    // //( notebook, ID_PAGEDETAILSPANEL, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    // SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );


    // CreateControls( );
    // if ( GetSizer( ) )
    // {
    //     GetSizer( )->SetSizeHints( this );
    // }
    // Centre( );
    return true;
}

//--------------
FontPicker* HelperPanel::SetupFontPicker(
    wxWindow* parent, wxBoxSizer* verticalSizer, int& lastID,
    wxString staticText, wxString buttonText,
    wxFontPickerCtrl*& fontCtrl,
    wxColourPickerCtrl*& colorCtrl,
    wxObjectEventFunction  fontPickerHandler,
    wxObjectEventFunction  colorPickerHandler,
    wxObjectEventFunction  defaultButtonHandler )
{

    FontPicker* fontPickerHelper = new FontPicker(
        parent, verticalSizer,
        staticText,
        buttonText, ++lastID,
        *wxNORMAL_FONT, *wxBLACK );
    fontCtrl = fontPickerHelper->GetFontPickerCtrl( );
    colorCtrl = fontPickerHelper->GetColourPickerCtrl( );
    Connect( fontCtrl->GetId( ), wxEVT_FONTPICKER_CHANGED, fontPickerHandler );
    Connect( colorCtrl->GetId( ), wxEVT_COLOURPICKER_CHANGED, colorPickerHandler );
    Connect( fontPickerHelper->GetDefaultButton( )->GetId( ), wxEVT_BUTTON, defaultButtonHandler );
    return fontPickerHelper;
}


wxTextCtrl* HelperPanel::SetupLabelText( wxWindow* parent, wxBoxSizer* inSizer, int& lastID, wxString label, bool grow,
    wxObjectEventFunction  eventHandler )
{
    wxBoxSizer* mySizer;
    if ( inSizer->IsVertical( ) )
    {
        wxBoxSizer* myHSizer = new wxBoxSizer( wxHORIZONTAL );
        inSizer->Add( myHSizer, 0, wxGROW | wxALL, 0 );
        mySizer = myHSizer;
    }
    else
    {
        mySizer = inSizer;

    }


    wxPanel* labelTextPanel = new wxPanel( parent, ++lastID, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    labelTextPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    mySizer->Add( labelTextPanel, 1, wxGROW | wxALL, 2 );

    wxBoxSizer* labelTextHSizer = new wxBoxSizer( wxHORIZONTAL );
    labelTextPanel->SetSizer( labelTextHSizer );

    wxStaticText* staticText = new wxStaticText( labelTextPanel, wxID_STATIC, label, wxDefaultPosition, wxDefaultSize, 0 );
    labelTextHSizer->Add( staticText, 0, wxALIGN_CENTER_VERTICAL, 0 );

    wxTextCtrl* value = new wxTextCtrl( labelTextPanel, ++lastID, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );

    if ( grow )
    {
        labelTextHSizer->Add( value, 1, wxGROW | wxALL, 0 );
    }
    else
    {
        labelTextHSizer->Add( value, 0, wxLEFT | wxALL, 0 );
    }
    Connect( value->GetId( ), wxEVT_TEXT, eventHandler );

    return value;
}


wxCheckBox* HelperPanel::SetupCheckBox( wxWindow* parent, wxBoxSizer* sizer, int& lastID, wxString label, wxObjectEventFunction  eventHandler )
{

    wxCheckBox* checkbox = new wxCheckBox( parent, ++lastID, label, wxDefaultPosition, wxDefaultSize, 0 );
    checkbox->SetValue( true );

    sizer->Add( checkbox, 0, wxALIGN_LEFT | wxALL, 5 );

    Connect( checkbox->GetId( ), wxEVT_CHECKBOX, eventHandler );

    return checkbox;
}

wxChoice* HelperPanel::SetupChoice( wxWindow* parent, wxBoxSizer* sizer, int& lastID, wxString label,
    wxArrayString choiceStrings, wxObjectEventFunction  eventHandler )
{
    wxBoxSizer* itemBoxSizer20 = new wxBoxSizer( wxHORIZONTAL );
    sizer->Add( itemBoxSizer20, 0, wxALIGN_LEFT | wxALL, 0 );

    wxStaticText* staticText = new wxStaticText(
        parent, wxID_STATIC, label, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer20->Add( staticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxChoice* choice = new wxChoice( parent, wxALIGN_CENTER_VERTICAL, wxDefaultPosition, wxDefaultSize, choiceStrings, 0 );

    itemBoxSizer20->Add( choice, 0, wxALIGN_LEFT | wxALL, 0 );
    return choice;

}


HelperPanel::TitleHelper* HelperPanel::SetupTitleHelper( wxWindow* parent, wxBoxSizer* inSizer, int& idLast,
    int style,
    wxObjectEventFunction titleCheckBoxEventHandler,
    wxObjectEventFunction titleEventHandler,
    wxObjectEventFunction subTitleCheckBoxEeventHandler,
    wxObjectEventFunction subTitleEventHandler )
{
    TitleHelper* titleHelper = new TitleHelper;

    wxBoxSizer* horizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    inSizer->Add( horizontalSizer, 0, wxGROW | wxALL, 5 );
    titleHelper->titleCheckbox = 0;
    titleHelper->subTitleCheckbox = 0;
    titleHelper->titleLabel = 0;
    titleHelper->subTitleLabel = 0;

    titleHelper->titleCheckbox = SetupCheckBox( parent, horizontalSizer, idLast, _( "Show Title" ), titleCheckBoxEventHandler );
    titleHelper->titleCheckbox->SetValue( false );
    if ( style & HasSubTitle )
    {
        titleHelper->subTitleCheckbox = SetupCheckBox( parent, horizontalSizer, idLast, _( "Show SubTitle" ), subTitleCheckBoxEeventHandler );
        titleHelper->subTitleCheckbox->SetValue( false );
    }
    if ( style & HasTextCtrl )
    {
        titleHelper->titleLabel = SetupLabelText( parent, inSizer, idLast, _( "Title" ), true, titleCheckBoxEventHandler );
        if ( style & HasSubTitle )
        {
            titleHelper->subTitleLabel = SetupLabelText( parent, inSizer, idLast, _( "Sub Title" ), true, subTitleCheckBoxEeventHandler );
        }
    }
    return titleHelper;
}

void HelperPanel::SetTitleCheckboxValue( HelperPanel::TitleHelper* titleHelper, bool state )
{
    titleHelper->titleCheckbox->SetValue( state );
    UpdateTitleState( titleHelper );
};

void HelperPanel::SetSubTitleCheckboxValue( HelperPanel::TitleHelper* titleHelper, bool state )
{

    titleHelper->subTitleCheckbox->SetValue( state );
    UpdateSubTitleState( titleHelper );
};

void HelperPanel::UpdateTitleState( HelperPanel::TitleHelper* titleHelper )
{
    bool state = titleHelper->titleCheckbox->GetValue( );
    titleHelper->titleCheckbox->Show( true );
    if ( state )
    {

        if ( titleHelper->titleLabel )
        {
            titleHelper->titleLabel->Enable( state );
        }
        if ( titleHelper->subTitleCheckbox )
        {
            titleHelper->subTitleCheckbox->Enable( );
        }
    }
    else
    {
        titleHelper->titleCheckbox->Show( true );
        if ( titleHelper->titleLabel )
        {
            titleHelper->titleLabel->Disable( );
        }
        if ( titleHelper->subTitleCheckbox )
        {
            titleHelper->subTitleCheckbox->Disable( );
        }
    }
    if ( titleHelper->subTitleLabel )
    {
        titleHelper->subTitleLabel->Show( );
    }
}
void HelperPanel::UpdateSubTitleState( HelperPanel::TitleHelper* titleHelper )
{
    if ( titleHelper->subTitleCheckbox )
    {
        bool state = titleHelper->subTitleCheckbox->GetValue( );
        if ( state )
        {
            titleHelper->subTitleCheckbox->Enable( );
            if ( titleHelper->subTitleLabel )
            {
                titleHelper->subTitleLabel->Enable( );
            }
        }
        else
        {
            titleHelper->subTitleCheckbox->Disable( );
            if ( titleHelper->subTitleLabel )
            {
                titleHelper->subTitleLabel->Disable( );
            }
        }
    }
}

wxStaticBox* HelperPanel::SetupStaticBox( wxWindow* parent, wxBoxSizer* inSizer, wxBoxSizer* outBoxSizer )
{
    wxStaticBox* staticBox = new wxStaticBox( parent, wxID_ANY, _( "Name Location" ) );
    outBoxSizer = new wxStaticBoxSizer( staticBox, wxVERTICAL );
    inSizer->Add( outBoxSizer, 0, wxGROW | wxALL, 5 );
    return staticBox;
}


void HelperPanel::CreateControls( )
{
    HelperPanel* theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    wxBoxSizer* notebookHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( notebookHorizontalSizer, 2, wxGROW | wxALL, 5 );

}

void HelperPanel::HorizontalSpacer( wxBoxSizer* inSizer )
{
    inSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
}
void HelperPanel::VerticalSpacer( wxBoxSizer* inSizer )
{
    inSizer->Add( 5, 5, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );
}