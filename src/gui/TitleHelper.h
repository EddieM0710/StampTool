/*
 * @file         FontPickerHelper.h
 *@brief
 * @author      Eddie Monroe
 * Modified by:
 * @author     Mon 02 Jan 2023 08:34:03 CST
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


#ifndef _TITLEHELPER_H_
#define _TITLEHELPER_H_



#include "gui/AlbumTreeCtrl.h"
#include <gui/FontPickerHelper.h>
//#include <gui/TitleHelper.h>

#include "gui/GuiDefs.h"

 ///  @brief Helper class to group repetitive control construction sequence
 ///  

#define HasTextCtrl 0x01
#define HasSubTitle  0x2
#define NoHideTextCtrl 0x4
#define DefaultTitleHelperStyle HasTextCtrl | HasSubTitle
class TitleHelper
{

public:

    ///  @brief create static, font picker color picker and default button t=ctrls
    ///  

    TitleHelper( wxWindow* parent, wxBoxSizer* verticalSizer,
        int& idLast, int style = 0 )
    {
        m_style = style;
        //  parent = parent;
        m_verticalSizer = verticalSizer;
        m_titleLabel = 0;
        m_subTitleLabel = 0;

        m_horizontalSizer = new wxBoxSizer( wxHORIZONTAL );
        m_verticalSizer->Add( m_horizontalSizer, 0, wxGROW | wxALL, 5 );

        m_titleCheckbox = new wxCheckBox( parent, ++idLast, _( "Show Title" ), wxDefaultPosition, wxDefaultSize, 0 );
        m_titleCheckbox->SetValue( false );
        m_horizontalSizer->Add( m_titleCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        m_subTitleCheckbox = new wxCheckBox( parent, ++idLast, _( "Show SubTitle" ), wxDefaultPosition, wxDefaultSize, 0 );
        m_subTitleCheckbox->SetValue( false );
        m_horizontalSizer->Add( m_subTitleCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        if ( m_style & HasLabels )
        {
            m_titleLabel = new LabeledTextBox( parent, ++idLast, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
            m_titleLabel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
            m_verticalSizer->Add( m_titleLabel, 0, wxGROW | wxALL, 5 );
        }
        m_titleFontPickerHelper = new FontPicker(
            parent, m_verticalSizer,
            _( "Title Font" ), _( "Default" ), ++idLast,
            *wxNORMAL_FONT, *wxBLACK );

        if ( m_style & HasLabels )
        {
            m_subTitleLabel = new LabeledTextBox( parent, ++idLast, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
            m_subTitleLabel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
            m_verticalSizer->Add( m_subTitleLabel, 0, wxGROW | wxALL, 5 );
        }
        m_subTitleFontPickerHelper = new FontPicker(
            parent, m_verticalSizer,
            _( "SubTitle Font" ), _( "Default" ), ++idLast,
            *wxNORMAL_FONT, *wxBLACK );

    }

    ///  @brief Get the Font Picker Ctrl object
    ///  
    ///  @return wxFontPickerCtrl* 
    wxFontPickerCtrl* GetTitleFontPickerCtrl( ) {
        return m_titleFontPickerHelper->GetFontPickerCtrl( );
    };
    wxFontPickerCtrl* GetSubTitleFontPickerCtrl( ) {
        return m_subTitleFontPickerHelper->GetFontPickerCtrl( );
    };

    ///  @brief Get the Colour Picker Ctrl object
    ///  
    ///  @return wxColourPickerCtrl* 
    wxColourPickerCtrl* GetTitleColourPickerCtrl( ) {
        return m_titleFontPickerHelper->GetColourPickerCtrl( );
    };
    wxColourPickerCtrl* GetSubTitleColourPickerCtrl( ) {
        return m_subTitleFontPickerHelper->GetColourPickerCtrl( );
    };

    void ShowTitleFontPicker( bool show = true )
    {
        m_titleFontPickerHelper->ShowFontPicker( show );
        m_verticalSizer->Layout( );
    };

    void ShowTitleLabel( bool show = true )
    {
        if ( m_titleLabel )
        {
            if ( !( m_style & NoHideTitle ) )
            {
                m_titleLabel->Show( show );
            }
            else
            {
                m_titleLabel->Show( true );
            }
            m_verticalSizer->Layout( );
        }
    };

    void ShowSubTitleFontPicker( bool show = true )
    {
        m_subTitleFontPickerHelper->ShowFontPicker( show );
        m_verticalSizer->Layout( );
    };

    void ShowSubTitleLabel( bool show = true )
    {
        if ( m_subTitleLabel )
        {
            m_subTitleLabel->Show( show );
            m_verticalSizer->Layout( );
        }
    };

    wxCheckBox* GetTitleCheckbox( ) {
        return m_titleCheckbox;
    };
    wxCheckBox* GetSubTitleCheckbox( ) {
        return m_subTitleCheckbox;
    };

    bool GetTitleCheckboxValue( ) {
        return m_titleCheckbox->GetValue( );
    };
    bool GetSubTitleCheckboxValue( ) {
        return m_subTitleCheckbox->GetValue( );
    };
    void SetTitleCheckboxValue( bool state )
    {
        m_titleCheckbox->SetValue( state );
        UpdateTitleState( );
    };
    void SetSubTitleCheckboxValue( bool state )
    {
        m_subTitleCheckbox->SetValue( state );
        UpdateSubTitleState( );
    };

    wxButton* GetTitleDefaultButton( ) {
        return m_titleFontPickerHelper->GetDefaultButton( );
    };
    wxButton* GetSubTitleDefaultButton( ) {
        return m_subTitleFontPickerHelper->GetDefaultButton( );
    };
    LabeledTextBox* GetTitleLabel( ) {
        return m_titleLabel;
    };
    LabeledTextBox* GetSubTitleLabel( ) {
        return m_subTitleLabel;
    };
    void UpdateTitleState( )
    {
        bool state = GetTitleCheckboxValue( );
        ShowTitleLabel( state );

        ShowTitleFontPicker( state );
        if ( !( m_style & NoHideTitle ) )
        {
            m_titleLabel->Show( state );
        }
        else
        {
            m_titleLabel->Show( true );
        }
        if ( !state )
        {
            SetSubTitleCheckboxValue( state );
            ShowSubTitleFontPicker( state );
            m_subTitleLabel->Show( state );
            GetSubTitleCheckbox( )->Disable( );
        }
        else
        {
            GetSubTitleCheckbox( )->Enable( );
        }
    }
    void UpdateSubTitleState( )
    {
        bool state = GetSubTitleCheckbox( )->GetValue( );
        ShowSubTitleFontPicker( state );
        ShowSubTitleLabel( state );
    }
private:
    int m_style;
    FontPicker* m_subTitleFontPickerHelper;
    FontPicker* m_titleFontPickerHelper;
    wxCheckBox* m_titleCheckbox;
    wxCheckBox* m_subTitleCheckbox;
    wxBoxSizer* m_horizontalSizer;
    wxBoxSizer* m_verticalSizer;

    LabeledTextBox* m_subTitleLabel;
    LabeledTextBox* m_titleLabel;
};

#endif
