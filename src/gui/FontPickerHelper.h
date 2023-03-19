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
/////////////////////////////////////////////////////////////////////////////


#ifndef _FONTPICKERHELPER_H_
#define _FONTPICKERHELPER_H_


/*
 * Includes
 */

#include "gui/DesignTreeCtrl.h"
#include <wx/fontpicker.h>
#include <wx/font.h>
#include <wx/clrpicker.h>
#include "gui/GuiDefs.h"


//Helper class to group repetitive control construction sequence
class FontPicker
{
public:
    // create static, font picker color picker and default button t=ctrls
    FontPicker( wxWindow* parent, wxBoxSizer* verticalSizer,
        wxString staticText, int idStatic,
        int idFontPicker, int idColorPicker,
        wxString buttonText, int idDefaultButton,        
        const wxFont &font = wxNullFont,
        const wxColour &color = *wxStockGDI::GetColour(wxStockGDI::COLOUR_BLACK) )
    {
        m_parent = parent;
        m_verticalSizer = verticalSizer;
        m_staticText = staticText;
        m_idStatic = idStatic;
        m_idFontPicker = idFontPicker;
        m_idColorPicker = idColorPicker;
        m_buttonText = buttonText;
        m_idDefaultButton = idDefaultButton;
        m_font = font;
        m_color = color;
        CreateCtrls( );
    }
    
    void CreateCtrls( )
    {
        m_horizontalSizer = new wxBoxSizer( wxHORIZONTAL );
        m_verticalSizer->Add( m_horizontalSizer, 0, wxGROW | wxALL, 5 );

        wxStaticText* FontStatic = new wxStaticText( m_parent, m_idStatic, m_staticText, wxDefaultPosition, wxDefaultSize, 0 );
        m_horizontalSizer->Add( FontStatic, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        m_fontPicker = new wxFontPickerCtrl( m_parent, m_idFontPicker,
            m_font, wxDefaultPosition,
            wxDefaultSize, wxFNTP_DEFAULT_STYLE );
        m_horizontalSizer->Add( m_fontPicker, 2, wxGROW | wxALL, 5 );

        m_colorPicker = new wxColourPickerCtrl( m_parent, m_idColorPicker,
            m_color, wxDefaultPosition,
            wxDefaultSize, wxCLRP_DEFAULT_STYLE );
        m_horizontalSizer->Add( m_colorPicker, 1, wxGROW | wxALL, 5 );

        m_defaultButton = new wxButton( m_parent, m_idDefaultButton, m_buttonText, wxDefaultPosition, wxDefaultSize, 0 );
        m_horizontalSizer->Add( m_defaultButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    }

    wxFontPickerCtrl* GetFontPickerCtrl() { return m_fontPicker; };
    wxColourPickerCtrl* GetColourPickerCtrl() { return m_colorPicker; };
    wxButton* GetDefaultButton() { return m_defaultButton; };
private:
    wxWindow* m_parent;

    wxFontPickerCtrl* m_fontPicker;
    wxColourPickerCtrl* m_colorPicker;
    wxButton* m_defaultButton;
    wxBoxSizer* m_horizontalSizer;
    wxBoxSizer* m_verticalSizer;
    wxString m_staticText;
    wxString m_buttonText;
    int m_idStatic;
    int m_idFontPicker;
    int m_idColorPicker;
    int m_idDefaultButton;
    wxFont m_font;
    wxColour m_color;

};

#endif
