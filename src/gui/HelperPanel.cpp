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

//--------------

void HelperPanel::Init( )
{

}

//--------------

bool HelperPanel::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxPanel::Create( parent, id, pos, size, style );
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

//--------------

wxStaticBox* HelperPanel::SetupBoxSizer( wxWindow* parent, wxBoxSizer* inSizer, wxString name, int& lastID, wxBoxSizer*& boxSizer, wxOrientation orientation )
{
    wxStaticBox* box = new wxStaticBox( parent, ++lastID, name );

    boxSizer = new wxStaticBoxSizer( box, orientation );
    inSizer->Add( boxSizer, 0, wxGROW | wxALL, 5 );

    return box;
}

//--------------

wxTextCtrl* HelperPanel::SetupLabelText( wxWindow* parent, wxBoxSizer* inSizer, int& lastID, wxString label, bool grow,
    wxObjectEventFunction  eventHandler )
{
    wxStaticBox* itemStaticBoxSizerStatic = new wxStaticBox( parent, wxID_ANY, label );
    wxStaticBoxSizer* itemStaticBoxSizer = new wxStaticBoxSizer( itemStaticBoxSizerStatic, wxVERTICAL );
    inSizer->Add( itemStaticBoxSizer, 0, wxGROW | wxALL, 2 );

    wxTextCtrl* itemTextCtrl = new wxTextCtrl( itemStaticBoxSizer->GetStaticBox( ), ++lastID,
        wxEmptyString, wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
    itemStaticBoxSizer->Add( itemTextCtrl, 0, wxGROW | wxALL, 2 );

    Connect( itemTextCtrl->GetId( ), wxEVT_TEXT, eventHandler );

    return itemTextCtrl;
}

//--------------

wxTextCtrl* HelperPanel::SetupMultilineLabeledText( wxWindow* parent, wxBoxSizer* inSizer, int& lastID, wxString label, bool grow,
    wxObjectEventFunction  eventHandler )
{
    wxStaticBox* itemStaticBoxSizerStatic = new wxStaticBox( parent, wxID_ANY, label );
    wxStaticBoxSizer* itemStaticBoxSizer = new wxStaticBoxSizer( itemStaticBoxSizerStatic, wxHORIZONTAL );
    inSizer->Add( itemStaticBoxSizer, 0, wxGROW | wxALL, 2 );

    wxTextCtrl* itemTextCtrl = new wxTextCtrl( itemStaticBoxSizer->GetStaticBox( ), ++lastID,
        wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxNO_BORDER );
    itemStaticBoxSizer->Add( itemTextCtrl, 1, wxALL, 0 );

    Connect( itemTextCtrl->GetId( ), wxEVT_TEXT, eventHandler );

    return itemTextCtrl;
}

//--------------

wxRadioButton* HelperPanel::SetupRadioButton( wxWindow* parent, wxBoxSizer* sizer, int& lastID, wxString label, bool initValue, wxObjectEventFunction  eventHandler )
{
    wxRadioButton* radioButton = new wxRadioButton( parent, ++lastID, label, wxDefaultPosition, wxDefaultSize, 0 );
    radioButton->SetValue( initValue );
    sizer->Add( radioButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    Connect( radioButton->GetId( ), wxEVT_RADIOBUTTON, eventHandler );
    return radioButton;
}

//--------------

wxCheckBox* HelperPanel::SetupCheckBox( wxWindow* parent, wxBoxSizer* sizer, int& lastID, wxString label, wxObjectEventFunction  eventHandler )
{
    wxCheckBox* checkbox = new wxCheckBox( parent, ++lastID, label, wxDefaultPosition, wxDefaultSize, 0 );
    checkbox->SetValue( true );

    sizer->Add( checkbox, 0, wxALIGN_LEFT, 5 );

    Connect( checkbox->GetId( ), wxEVT_CHECKBOX, eventHandler );

    return checkbox;
}

//--------------

wxChoice* HelperPanel::SetupChoice( wxWindow* parent, wxBoxSizer* sizer, int& lastID, wxString label,
    wxArrayString choiceStrings, wxObjectEventFunction  eventHandler )
{
    wxStaticBox* itemStaticBoxSizerStatic = new wxStaticBox( parent, wxID_ANY, label );
    wxStaticBoxSizer* itemStaticBoxSizer = new wxStaticBoxSizer( itemStaticBoxSizerStatic, wxVERTICAL );
    sizer->Add( itemStaticBoxSizer, 0, wxGROW | wxALL, 0 );

    wxChoice* choice = new wxChoice( parent, ++lastID, wxDefaultPosition, wxDefaultSize, choiceStrings, 0 );

    itemStaticBoxSizer->Add( choice, 1, wxGROW | wxALL, 0 );

    Connect( choice->GetId( ), wxEVT_CHOICE, eventHandler );

    return choice;
}

//--------------

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
        titleHelper->titleLabel = SetupLabelText( parent, inSizer, idLast, _( "Title" ), true, titleEventHandler );
        if ( style & HasSubTitle )
        {
            titleHelper->subTitleLabel = SetupLabelText( parent, inSizer, idLast, _( "Sub Title" ), true, subTitleEventHandler );
        }
    }
    return titleHelper;
}

//--------------

void HelperPanel::SetTitleCheckboxValue( HelperPanel::TitleHelper* titleHelper, bool state )
{
    titleHelper->titleCheckbox->SetValue( state );
    UpdateTitleState( titleHelper );
};

//--------------

void HelperPanel::SetSubTitleCheckboxValue( HelperPanel::TitleHelper* titleHelper, bool state )
{

    titleHelper->subTitleCheckbox->SetValue( state );
    UpdateSubTitleState( titleHelper );
};

//--------------

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
        if ( titleHelper->titleLabel )
        {
            titleHelper->titleLabel->Disable( );
        }
        if ( titleHelper->subTitleCheckbox )
        {
            titleHelper->subTitleCheckbox->Disable( );
            titleHelper->subTitleCheckbox->SetValue( state );
            titleHelper->subTitleLabel->Disable( );
        }
    }
    if ( titleHelper->subTitleLabel )
    {
        titleHelper->subTitleLabel->Show( );
    }
}

//--------------

void HelperPanel::UpdateSubTitleState( HelperPanel::TitleHelper* titleHelper )
{
    if ( titleHelper->subTitleCheckbox )
    {
        bool state = titleHelper->subTitleCheckbox->GetValue( );
        if ( state )
        {
            //titleHelper->subTitleCheckbox->Enable( );
            if ( titleHelper->subTitleLabel )
            {
                titleHelper->subTitleLabel->Enable( );
            }
        }
        else
        {
            //titleHelper->subTitleCheckbox->Disable( );
            if ( titleHelper->subTitleLabel )
            {
                titleHelper->subTitleLabel->Disable( );
            }
        }
    }
}

//--------------

wxStaticBox* HelperPanel::SetupStaticBox( wxWindow* parent, wxBoxSizer* inSizer, wxBoxSizer* outBoxSizer )
{
    wxStaticBox* staticBox = new wxStaticBox( parent, wxID_ANY, _( "Name Location" ) );
    outBoxSizer = new wxStaticBoxSizer( staticBox, wxVERTICAL );
    inSizer->Add( outBoxSizer, 0, wxGROW | wxALL, 5 );
    return staticBox;
}

//--------------

void HelperPanel::CreateControls( )
{
    HelperPanel* theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    wxBoxSizer* notebookHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( notebookHorizontalSizer, 2, wxGROW | wxALL, 5 );

}

//--------------

void HelperPanel::HorizontalSpacer( wxBoxSizer* inSizer )
{
    inSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
}

//--------------


void HelperPanel::VerticalSpacer( wxBoxSizer* inSizer )
{
    inSizer->Add( 5, 5, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );
}

//--------------


wxCheckListBox* HelperPanel::SetupCheckListBox( wxWindow* parent, wxBoxSizer* inSizer, int& lastID,
    wxString label, wxArrayString& array,
    wxObjectEventFunction  allButtonEventHandler,
    wxObjectEventFunction  clearButtonEventHandler )
{
    wxStaticBox* itemStaticBoxSizerStatic = new wxStaticBox( parent, wxID_ANY, label );
    wxStaticBoxSizer* itemStaticBoxSizer = new wxStaticBoxSizer( itemStaticBoxSizerStatic, wxVERTICAL );
    inSizer->Add( itemStaticBoxSizer, 0, wxGROW | wxALL, 2 );

    wxBoxSizer* horizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    itemStaticBoxSizer->Add( horizontalSizer, 2, wxGROW | wxALL, 5 );

    wxButton* allButton = new wxButton( parent, lastID++, _( "All" ), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    horizontalSizer->Add( allButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    if ( allButtonEventHandler )
        Connect( allButton->GetId( ), wxEVT_CHOICE, allButtonEventHandler );

    wxButton* clearButton = new wxButton( parent, lastID++, _( "Clear" ), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    horizontalSizer->Add( clearButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    if ( clearButtonEventHandler )
        Connect( clearButton->GetId( ), wxEVT_CHOICE, clearButtonEventHandler );

    wxCheckListBox* listCtrl = new wxCheckListBox( parent, lastID++, wxDefaultPosition, wxSize( -1, 100 ), array, wxLB_MULTIPLE | wxLB_HSCROLL );
    itemStaticBoxSizer->Add( listCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    return listCtrl;
}
