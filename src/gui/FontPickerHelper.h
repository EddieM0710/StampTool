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


#ifndef _FONTPICKERHELPER_H_
#define _FONTPICKERHELPER_H_



#include "gui/AlbumTreeCtrl.h"
#include <wx/fontpicker.h>
#include <wx/font.h>
#include <wx/clrpicker.h>
#include "gui/GuiDefs.h"

 ///  @brief Helper class to group repetitive control construction sequence
 ///  
class FontPicker
{

public:

    ///  @brief create static, font picker color picker and default button t=ctrls
    ///  
    ///  @param parent 
    ///  @param verticalSizer 
    ///  @param staticText 
    ///  @param idStatic 
    ///  @param idFontPicker 
    ///  @param idColorPicker 
    ///  @param buttonText 
    ///  @param idDefaultButton 
    ///  @param font 
    ///  @param color 
    FontPicker( wxWindow* parent, wxBoxSizer* verticalSizer,
        wxString staticText, wxString buttonText, int& lastID,
        const wxFont& font = wxNullFont,
        const wxColour& color = *wxStockGDI::GetColour( wxStockGDI::COLOUR_BLACK ) )
    {

        m_font = font;
        m_color = color;

        m_horizontalSizer = new wxBoxSizer( wxHORIZONTAL );
        verticalSizer->Add( m_horizontalSizer, 0, wxGROW | wxALL, 5 );

        wxStaticText* FontStatic = new wxStaticText( parent, ++lastID, staticText, wxDefaultPosition, wxDefaultSize, 0 );
        m_horizontalSizer->Add( FontStatic, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        m_fontPicker = new wxFontPickerCtrl( parent, ++lastID,
            m_font, wxDefaultPosition,
            wxDefaultSize, wxFNTP_DEFAULT_STYLE );
        m_horizontalSizer->Add( m_fontPicker, 2, wxGROW | wxALL, 5 );

        m_colorPicker = new wxColourPickerCtrl( parent, ++lastID,
            m_color, wxDefaultPosition,
            wxDefaultSize, wxCLRP_DEFAULT_STYLE );
        m_horizontalSizer->Add( m_colorPicker, 1, wxGROW | wxALL, 5 );

        m_defaultButton = new wxButton( parent, ++lastID, buttonText, wxDefaultPosition, wxDefaultSize, 0 );
        m_horizontalSizer->Add( m_defaultButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    }

    ///  @brief Get the Font Picker Ctrl object
    ///  
    ///  @return wxFontPickerCtrl* 
    wxFontPickerCtrl* GetFontPickerCtrl( ) { return m_fontPicker; };

    ///  @brief Get the Colour Picker Ctrl object
    ///  
    ///  @return wxColourPickerCtrl* 
    wxColourPickerCtrl* GetColourPickerCtrl( ) { return m_colorPicker; };

    ///  @brief Get the Default Button object
    ///  
    ///  @return wxButton* 
    wxButton* GetDefaultButton( ) { return m_defaultButton; };
    void ShowFontPicker( bool show = true ) { m_horizontalSizer->Show( show ); }

private:

    wxFontPickerCtrl* m_fontPicker;
    wxColourPickerCtrl* m_colorPicker;
    wxButton* m_defaultButton;
    wxBoxSizer* m_horizontalSizer;
    wxFont m_font;
    wxColour m_color;

};

#endif
