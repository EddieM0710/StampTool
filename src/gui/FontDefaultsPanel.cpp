/*
 * @file  FontDefaultsPanel.cpp
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
#include <wx/arrstr.h>

#include "wx/notebook.h"

#include "gui/FontDefaultsPanel.h"

#include "gui/LabeledTextBox.h"
#include "gui/FontPickerHelper.h"
#include "design/TitleFrame.h"
#include "design/Page.h"
#include "design/Album.h"
#include "design/DesignDefs.h"
#include "utils/FontList.h"
#include "utils/Settings.h"
#include "Defs.h"


IMPLEMENT_DYNAMIC_CLASS( FontDefaultsPanel, HelperPanel )



BEGIN_EVENT_TABLE( FontDefaultsPanel, HelperPanel )

END_EVENT_TABLE( )


//--------------

FontDefaultsPanel::FontDefaultsPanel( )
{
    Init( );
}

//--------------

FontDefaultsPanel::FontDefaultsPanel( wxWindow* parent, wxWindowID id,
    const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

//--------------

bool FontDefaultsPanel::Create( wxWindow* parent, wxWindowID id,
    const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}

//--------------

FontDefaultsPanel::~FontDefaultsPanel( )
{

}

//--------------

void FontDefaultsPanel::Init( )
{
}

//--------------

void FontDefaultsPanel::CreateControls( )
{
    FontDefaultsPanel* thePanel = this;
    int lastID = ID_LastID;

    wxBoxSizer* detailsHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    thePanel->SetSizer( detailsHorizontalSizer );

    wxBoxSizer* leftColumnVerticalSizer = new wxBoxSizer( wxVERTICAL );
    detailsHorizontalSizer->Add( leftColumnVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* middleColumnVerticalSizer = new wxBoxSizer( wxVERTICAL );
    detailsHorizontalSizer->Add( middleColumnVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* rightColumnVerticalSizer = new wxBoxSizer( wxVERTICAL );
    detailsHorizontalSizer->Add( rightColumnVerticalSizer, 1, wxGROW | wxALL, 0 );

    SetupFontPicker( thePanel, leftColumnVerticalSizer, lastID,
        _( "Title Font" ), _( "Default" ),
        m_titleFontPicker, m_titleColorPicker,
        wxFontPickerEventHandler( FontDefaultsPanel::OnTitleFontPicker ),
        wxColourPickerEventHandler( FontDefaultsPanel::OnTitleColorPicker ),
        wxCommandEventHandler( FontDefaultsPanel::OnTitleDefaultClick ) );

    SetupFontPicker( thePanel, leftColumnVerticalSizer, lastID,
        _( "SubTitle Font" ), _( "Default" ),
        m_subTitleFontPicker, m_subTitleColorPicker,
        wxFontPickerEventHandler( FontDefaultsPanel::OnSubTitleFontPicker ),
        wxColourPickerEventHandler( FontDefaultsPanel::OnSubTitleColorPicker ),
        wxCommandEventHandler( FontDefaultsPanel::OnSubTitleDefaultClick ) );

    SetupFontPicker( thePanel, middleColumnVerticalSizer, lastID,
        _( "Text Font" ), _( "Default" ),
        m_textFontPicker, m_textColorPicker,
        wxFontPickerEventHandler( FontDefaultsPanel::OnTextFontPicker ),
        wxColourPickerEventHandler( FontDefaultsPanel::OnTextColorPicker ),
        wxCommandEventHandler( FontDefaultsPanel::OnTextDefaultClick ) );

    SetupFontPicker( thePanel, middleColumnVerticalSizer, lastID,
        _( "Default Catalog Nbr Font" ), _( "Default" ),
        m_nbrFontPicker, m_nbrColorPicker,
        wxFontPickerEventHandler( FontDefaultsPanel::OnNbrFontPicker ),
        wxColourPickerEventHandler( FontDefaultsPanel::OnNbrColorPicker ),
        wxCommandEventHandler( FontDefaultsPanel::OnNbrDefaultClick ) );

    SetupFontPicker( thePanel, rightColumnVerticalSizer, lastID,
        _( "Default Name Font" ), _( "Default" ),
        m_nameFontPicker, m_nameColorPicker,
        wxFontPickerEventHandler( FontDefaultsPanel::OnNameFontPicker ),
        wxColourPickerEventHandler( FontDefaultsPanel::OnNameColorPicker ),
        wxCommandEventHandler( FontDefaultsPanel::OnNameDefaultClick ) );
}

//--------------

wxFont FontDefaultsPanel::GetSubTitleFont( ) {
    return m_subTitleFontPicker->GetSelectedFont( );
}

//--------------

wxColour FontDefaultsPanel::GetSubTitleColor( ) {
    return m_subTitleColorPicker->GetColour( );
}

//--------------

wxColour FontDefaultsPanel::GetTextColor( ) {
    return m_textColorPicker->GetColour( );
}

//--------------

wxFont FontDefaultsPanel::GetTextFont( ) {
    return m_textFontPicker->GetSelectedFont( );
}

//--------------

wxFont FontDefaultsPanel::GetTitleFont( ) {
    return m_titleFontPicker->GetSelectedFont( );
}

//--------------

wxColour FontDefaultsPanel::GetTitleColor( ) {
    return m_titleColorPicker->GetColour( );
}

//--------------

void FontDefaultsPanel::UpdateControls( )
{

    SetTitleFont( Design::GetAlbum( )->GetFont( Design::AT_TitleFontType ) );
    SetTitleColor( Design::GetAlbum( )->GetColor( Design::AT_TitleFontType ) );
    SetSubTitleFont( Design::GetAlbum( )->GetFont( Design::AT_SubTitleFontType ) );
    SetSubTitleColor( Design::GetAlbum( )->GetColor( Design::AT_SubTitleFontType ) );
    SetTextFont( Design::GetAlbum( )->GetFont( Design::AT_TextFontType ) );
    SetTextColor( Design::GetAlbum( )->GetColor( Design::AT_TextFontType ) );
    SetNbrFont( Design::GetAlbum( )->GetFont( Design::AT_NbrFontType ) );
    SetNbrColor( Design::GetAlbum( )->GetColor( Design::AT_NbrFontType ) );
    SetNameFont( Design::GetAlbum( )->GetFont( Design::AT_NameFontType ) );
    SetNameColor( Design::GetAlbum( )->GetColor( Design::AT_NameFontType ) );
}

//--------------

void FontDefaultsPanel::SetupDialog( Design::Page* page )
{
    UpdateControls( );
};

//--------------

bool FontDefaultsPanel::ShowToolTips( )
{
    return true;
}

//--------------

void FontDefaultsPanel::OnTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_TitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );

    Design::GetAlbum( )->SetFont( Design::AT_TitleFontType, font, color );

    event.Skip( );
}

//--------------

void FontDefaultsPanel::OnSubTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_SubTitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_subTitleFontPicker->SetSelectedFont( font );
    m_subTitleColorPicker->SetColour( color );

    Design::GetAlbum( )->SetFont( Design::AT_SubTitleFontType, font, color );

    event.Skip( );
}

//--------------

void FontDefaultsPanel::OnTitleFontPicker( wxFontPickerEvent& event )
{
    Design::GetAlbum( )->SetFont( Design::AT_TitleFontType, GetTitleFont( ), GetTitleColor( ) );
}

//--------------

void FontDefaultsPanel::OnTitleColorPicker( wxColourPickerEvent& event )
{
    Design::GetAlbum( )->SetFont( Design::AT_TitleFontType, GetTitleFont( ), GetTitleColor( ) );
}

//--------------

void FontDefaultsPanel::OnSubTitleFontPicker( wxFontPickerEvent& event )
{
    Design::GetAlbum( )->SetFont( Design::AT_SubTitleFontType, GetSubTitleFont( ), GetSubTitleColor( ) );
}

//--------------

void FontDefaultsPanel::OnSubTitleColorPicker( wxColourPickerEvent& event )
{
    Design::GetAlbum( )->SetFont( Design::AT_SubTitleFontType, GetSubTitleFont( ), GetSubTitleColor( ) );
}

//--------------

void FontDefaultsPanel::OnTextFontPicker( wxFontPickerEvent& event )
{
    Design::GetAlbum( )->SetFont( Design::AT_TextFontType, GetTextFont( ), GetTextColor( ) );
    event.Skip( );
}

//--------------

void FontDefaultsPanel::OnTextColorPicker( wxColourPickerEvent& event )
{
    Design::GetAlbum( )->SetFont( Design::AT_TextFontType, GetTextFont( ), GetTextColor( ) );
    event.Skip( );
}

//--------------

void FontDefaultsPanel::OnTextDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_TextFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_textFontPicker->SetSelectedFont( font );
    m_textColorPicker->SetColour( color );
    Design::GetAlbum( )->SetFont( Design::AT_TextFontType, font, color );
    event.Skip( );
}

//--------------

void FontDefaultsPanel::SetTextFont( wxFont font ) {
    m_textFontPicker->SetSelectedFont( font );
}

//--------------

void FontDefaultsPanel::SetTitleFont( wxFont font ) {
    m_titleFontPicker->SetSelectedFont( font );
}

//--------------

void FontDefaultsPanel::SetNameFont( wxFont font ) {
    m_nameFontPicker->SetSelectedFont( font );
}

void FontDefaultsPanel::SetSubTitleFont( wxFont font ) {
    m_subTitleFontPicker->SetSelectedFont( font );
}

//--------------

void FontDefaultsPanel::SetNameColor( wxColour color ) {
    m_nbrColorPicker->SetColour( color );
}

//--------------

void FontDefaultsPanel::SetTextColor( wxColour color ) {
    m_textColorPicker->SetColour( color );
}

//--------------

void FontDefaultsPanel::SetTitleColor( wxColour color ) {
    m_titleColorPicker->SetColour( color );
}

void FontDefaultsPanel::SetSubTitleColor( wxColour color ) {
    m_subTitleColorPicker->SetColour( color );
}

//--------------

wxFont FontDefaultsPanel::GetNbrFont( ) {
    return m_nbrFontPicker->GetSelectedFont( );
}

//--------------

wxFont FontDefaultsPanel::GetNameFont( ) {
    return m_nameFontPicker->GetSelectedFont( );
}

//--------------

wxColour FontDefaultsPanel::GetNameColor( ) {
    return m_nameColorPicker->GetColour( );
}

//--------------

wxColour FontDefaultsPanel::GetNbrColor( ) {
    return m_nbrColorPicker->GetColour( );
}

//--------------

void FontDefaultsPanel::SetNbrFont( wxFont font ) {
    m_nbrFontPicker->SetSelectedFont( font );
}

//--------------

void FontDefaultsPanel::SetNbrColor( wxColour color ) {
    m_nbrColorPicker->SetColour( color );
}

//--------------

void FontDefaultsPanel::OnNbrDefaultClick( wxCommandEvent& event )
{

    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_NbrFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nbrFontPicker->SetSelectedFont( font );
    m_nbrColorPicker->SetColour( color );
    Design::GetAlbum( )->SetFont( Design::AT_NbrFontType, font, color );
    event.Skip( );
}

//--------------

void FontDefaultsPanel::OnNameDefaultClick( wxCommandEvent& event )
{

    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_NbrFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nameFontPicker->SetSelectedFont( font );
    m_nameColorPicker->SetColour( color );
    Design::GetAlbum( )->SetFont( Design::AT_NameFontType, font, color );

    event.Skip( );
}

//--------------

void FontDefaultsPanel::OnNbrFontPicker( wxFontPickerEvent& event )
{
    Design::GetAlbum( )->SetFont( Design::AT_NbrFontType, GetNbrFont( ), GetNbrColor( ) );
    event.Skip( );
}

//--------------

void FontDefaultsPanel::OnNameColorPicker( wxColourPickerEvent& event )
{
    Design::GetAlbum( )->SetFont( Design::AT_NameFontType, GetNameFont( ), GetNameColor( ) );
    event.Skip( );
}

//--------------

void FontDefaultsPanel::OnNbrColorPicker( wxColourPickerEvent& event )
{
    Design::GetAlbum( )->SetFont( Design::AT_NbrFontType, GetNbrFont( ), GetNbrColor( ) );
    event.Skip( );
}

//--------------

void FontDefaultsPanel::OnNameFontPicker( wxFontPickerEvent& event )
{
    Design::GetAlbum( )->SetFont( Design::AT_NameFontType, GetNameFont( ), GetNameColor( ) );
    event.Skip( );

}

//--------------
