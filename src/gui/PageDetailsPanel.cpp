/*
 * @file  PageDetailsPanel.cpp
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

#include "gui/PageDetailsPanel.h"
#include "gui/LabeledTextBox.h"
#include "gui/FontPickerHelper.h"
#include "design/TitleFrame.h"
#include "design/Page.h"
#include "design/Album.h"
#include "design/DesignDefs.h"
#include "utils/FontList.h"
#include "utils/Settings.h"
#include "Defs.h"

 /*
  * PageDetailsPanel type definition
  */

IMPLEMENT_DYNAMIC_CLASS( PageDetailsPanel, HelperPanel )


/*
 * PageDetailsPanel event table definition
 */

    BEGIN_EVENT_TABLE( PageDetailsPanel, HelperPanel )
    // EVT_BUTTON( ID_TITLEDEFAULTBUTTON, PageDetailsPanel::OnTitleDefaultClick )
    EVT_CHOICE( ID_ORIENTATIONCHOICE, PageDetailsPanel::OnOrientationchoiceSelected )
    END_EVENT_TABLE( )

    ;

/*
 * PageDetailsPanel constructors
 */

PageDetailsPanel::PageDetailsPanel( )
{
    Init( );
}

PageDetailsPanel::PageDetailsPanel( wxWindow* parent, wxWindowID id,
    const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
    // SetMinClientSize( wxSize( 100, 100 ) );
}


/*
 * PageDetailsPanel creator
 */

bool PageDetailsPanel::Create( wxWindow* parent, wxWindowID id,
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

PageDetailsPanel::~PageDetailsPanel( )
{

}



void PageDetailsPanel::Init( )
{
    m_frameCheckbox = NULL;
    m_statusList = NULL;
}

void PageDetailsPanel::CreateControls( )
{

    PageDetailsPanel* theDialog = this;

    wxBoxSizer* detailsHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialog->SetSizer( detailsHorizontalSizer );



    int lastID = ID_LastID;

    wxNotebook* focusNotebook = new wxNotebook( theDialog, ++lastID,
        wxDefaultPosition, wxDefaultSize, wxBK_LEFT );
    focusNotebook->SetPadding( wxSize( 1, 1 ) );
    detailsHorizontalSizer->Add( focusNotebook, 1, wxGROW | wxALL, 5 );

    wxPanel* commonPanel = new wxPanel( focusNotebook, ++lastID, wxDefaultPosition,
        wxDefaultSize, wxTAB_TRAVERSAL );
    commonPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* commonHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    commonPanel->SetSizer( commonHorizontalSizer );


    wxBoxSizer* leftCommonVerticalSizer = new wxBoxSizer( wxVERTICAL );
    commonHorizontalSizer->Add( leftCommonVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* middleCommonVerticalSizer = new wxBoxSizer( wxVERTICAL );
    commonHorizontalSizer->Add( middleCommonVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* rightCommonVerticalSizer = new wxBoxSizer( wxVERTICAL );
    commonHorizontalSizer->Add( rightCommonVerticalSizer, 1, wxGROW | wxALL, 0 );


    focusNotebook->AddPage( commonPanel, _( "Basic" ) );



    wxPanel* advancedPanel = new wxPanel( focusNotebook, ++lastID, wxDefaultPosition,
        wxDefaultSize, wxTAB_TRAVERSAL );
    advancedPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* advancedHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    advancedPanel->SetSizer( advancedHorizontalSizer );


    wxBoxSizer* leftAdvancedVerticalSizer = new wxBoxSizer( wxVERTICAL );
    advancedHorizontalSizer->Add( leftAdvancedVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* middleAdvancedVerticalSizer = new wxBoxSizer( wxVERTICAL );
    advancedHorizontalSizer->Add( middleAdvancedVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* rightAdvancedVerticalSizer = new wxBoxSizer( wxVERTICAL );
    advancedHorizontalSizer->Add( rightAdvancedVerticalSizer, 1, wxGROW | wxALL, 0 );

    focusNotebook->AddPage( advancedPanel, _( "Special" ) );



    m_titleHelper = SetupTitleHelper( commonPanel, leftCommonVerticalSizer, lastID, DefaultTitleHelperStyle,
        wxCommandEventHandler( PageDetailsPanel::OnTitleCheckboxClick ),
        wxCommandEventHandler( PageDetailsPanel::OnTitleTextChanged ),
        wxCommandEventHandler( PageDetailsPanel::OnSubTitleCheckboxClick ),
        wxCommandEventHandler( PageDetailsPanel::OnSubTitleTextChanged ) );

    SetupFontPicker( advancedPanel, leftAdvancedVerticalSizer, lastID,
        _( "Title" ), _( "Default" ),
        m_titleFontPicker, m_titleColorPicker,
        wxFontPickerEventHandler( PageDetailsPanel::OnTitleFontPicker ),
        wxColourPickerEventHandler( PageDetailsPanel::OnTitleColorPicker ),
        wxCommandEventHandler( PageDetailsPanel::OnTitleDefaultClick ) );


    SetupFontPicker( advancedPanel, leftAdvancedVerticalSizer, lastID,
        _( "SubTitle" ), _( "Default" ),
        m_subTitleFontPicker, m_subTitleColorPicker,
        wxFontPickerEventHandler( PageDetailsPanel::OnSubTitleFontPicker ),
        wxColourPickerEventHandler( PageDetailsPanel::OnSubTitleColorPicker ),
        wxCommandEventHandler( PageDetailsPanel::OnSubTitleDefaultClick ) );


    wxArrayString m_orientationChoiceStrings( 2, Design::OrientationStrings );
    m_orientationChoice = SetupChoice( commonPanel, middleCommonVerticalSizer, ++lastID,
        _( "Orientation:" ), m_orientationChoiceStrings,
        wxCommandEventHandler( PageDetailsPanel::OnOrientationchoiceSelected ) );
    m_orientationChoice->SetSelection( Design::AT_Portrait );


    wxBoxSizer* marginBoxVSizer;
    wxStaticBox* marginBox = SetupBoxSizer( advancedPanel, middleAdvancedVerticalSizer,
        "Page Margin", lastID, marginBoxVSizer, wxVERTICAL );

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxHORIZONTAL );
    marginBoxVSizer->Add( itemBoxSizer7, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer7 );

    m_topPageMargin = SetupLabelText( marginBox, itemBoxSizer7, lastID,
        _( "Top" ), false, wxCommandEventHandler( PageDetailsPanel::OnTopPageMargin ) );
    m_topPageMargin->SetToolTip( _( "Page top margin in mm." ) );
    HorizontalSpacer( itemBoxSizer7 );

    m_bottomPageMargin = SetupLabelText( marginBox, itemBoxSizer7, lastID,
        _( "Bottom" ), false, wxCommandEventHandler( PageDetailsPanel::OnBottomPageMargin ) );
    m_bottomPageMargin->SetToolTip( _( "Page bottom margin in mm." ) );


    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer( wxHORIZONTAL );
    marginBoxVSizer->Add( itemBoxSizer10, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer10 );

    m_leftPageMargin = SetupLabelText( marginBox, itemBoxSizer10, lastID,
        _( "Left" ), false, wxCommandEventHandler( PageDetailsPanel::OnLeftPageMargin ) );
    m_leftPageMargin->SetToolTip( _( "Page left margin in mm." ) );

    HorizontalSpacer( itemBoxSizer10 );

    m_rightPageMargin = SetupLabelText( marginBox, itemBoxSizer10, lastID,
        _( "Right" ), false, wxCommandEventHandler( PageDetailsPanel::OnRightPageMargin ) );
    m_rightPageMargin->SetToolTip( _( "Page right margin in mm." ) );


    wxBoxSizer* borderboxVSizer;
    wxStaticBox* borderBox = SetupBoxSizer( advancedPanel, middleAdvancedVerticalSizer,
        "Border", lastID, borderboxVSizer, wxVERTICAL );

    wxBoxSizer* itemBorderBoxSizer = new wxBoxSizer( wxHORIZONTAL );
    borderboxVSizer->Add( itemBorderBoxSizer, 0, wxGROW | wxALL, 0 );

    m_showBorder = SetupCheckBox( borderBox, itemBorderBoxSizer, ++lastID,
        _( "Show Border" ), wxCommandEventHandler( PageDetailsPanel::OnShowBorderCheckBoxClick ) );
    m_showBorder->SetToolTip( _( "Show the page border." ) );

    m_borderSize = SetupLabelText( borderBox, itemBorderBoxSizer, lastID,
        _( "Size" ), false, wxCommandEventHandler( PageDetailsPanel::OnBorderSize ) );
    m_borderSize->SetToolTip( _( "width of the border to be added to the margin for layout in mm." ) );


    // wxStaticText* orientationStatic = new wxStaticText(
    //     theDialog, wxID_STATIC, _( "Orientation:" ), wxDefaultPosition, wxDefaultSize, 0 );
    // firstRowHorizontalSizer->Add( orientationStatic, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // wxArrayString m_orientationChoiceStrings( 2, Design::OrientationStrings );
    // m_orientationChoice = new wxChoice( theDialog, ID_ORIENTATIONCHOICE, wxDefaultPosition, wxDefaultSize, m_orientationChoiceStrings, 0 );
    // m_orientationChoice->SetSelection( Design::AT_Portrait );

    // firstRowHorizontalSizer->Add( m_orientationChoice, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    //>>error list ctrls
    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    rightCommonVerticalSizer->Add( itemBoxSizer3, 2, wxGROW | wxALL, 0 );

    wxArrayString m_statusListStrings;
    m_statusList = new wxListBox( commonPanel, ID_ERRORLISTCTRL, wxDefaultPosition, wxDefaultSize, m_statusListStrings, wxLB_SINGLE );
    //m_statusList = new wxListBox( theDialog, ID_ERRORLISTCTRL, wxDefaultPosition, wxSize( 100, 100 ), wxLC_REPORT | wxLC_EDIT_LABELS | wxSIMPLE_BORDER );
    itemBoxSizer3->Add( m_statusList, 2, wxGROW | wxALL, 0 );



    wxBoxSizer* contentMarginBoxVSizer;
    wxStaticBox* contentMarginBox = SetupBoxSizer( advancedPanel, rightAdvancedVerticalSizer,
        "Content Margin", lastID, contentMarginBoxVSizer, wxVERTICAL );

    wxBoxSizer* itemBoxSizer17 = new wxBoxSizer( wxHORIZONTAL );
    contentMarginBoxVSizer->Add( itemBoxSizer17, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer17 );

    m_topContentMargin = SetupLabelText( contentMarginBox, itemBoxSizer17, lastID,
        _( "Top" ), false, wxCommandEventHandler( PageDetailsPanel::OnTopContentMargin ) );
    m_topContentMargin->SetToolTip( _( "Content top margin in mm." ) );
    HorizontalSpacer( itemBoxSizer17 );

    m_bottomContentMargin = SetupLabelText( contentMarginBox, itemBoxSizer17, lastID,
        _( "Bottom" ), false, wxCommandEventHandler( PageDetailsPanel::OnBottomContentMargin ) );
    m_bottomContentMargin->SetToolTip( _( "Content bottom margin in mm." ) );


    wxBoxSizer* itemBoxSizer110 = new wxBoxSizer( wxHORIZONTAL );
    contentMarginBoxVSizer->Add( itemBoxSizer110, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer110 );

    m_leftContentMargin = SetupLabelText( contentMarginBox, itemBoxSizer110, lastID,
        _( "Left" ), false, wxCommandEventHandler( PageDetailsPanel::OnLeftContentMargin ) );
    m_leftContentMargin->SetToolTip( _( "Content left margin in mm." ) );

    HorizontalSpacer( itemBoxSizer110 );

    m_rightContentMargin = SetupLabelText( contentMarginBox, itemBoxSizer110, lastID,
        _( "Right" ), false, wxCommandEventHandler( PageDetailsPanel::OnRightContentMargin ) );
    m_topContentMargin->SetToolTip( _( "Content right margin in mm." ) );

    Layout( );
}


void PageDetailsPanel::UpdateControls( )
{
    SetTitle( m_page->GetAttrStr( Design::AT_Name ) );
    SetSubTitle( m_page->GetAttrStr( Design::AT_SubTitle ) );
    SetTitleFont( m_page->GetTitleFrame( )->GetHeadingFont( ) );
    SetTitleColor( m_page->GetTitleFrame( )->GetHeadingColor( ) );
    SetSubTitleFont( m_page->GetTitleFrame( )->GetSubHeadingFont( ) );
    SetSubTitleColor( m_page->GetTitleFrame( )->GetSubHeadingColor( ) );
    SetOrientation( m_page->Orientation( ) );
    SetShowTitle( m_page->GetShowTitle( ) );
    SetShowSubTitle( m_page->GetShowSubTitle( ) );
    SetShowBorder( m_page->GetShowBorder( ) );
    SetBorderSize( Design::AlbumPageDefaults( )->BorderSizeStr( ) );

    SetTopPageMargin( m_page->GetTopPageMarginStr( ) );
    SetBottomPageMargin( m_page->GetBottomPageMarginStr( ) );
    SetLeftPageMargin( m_page->GetLeftPageMarginStr( ) );
    SetRightPageMargin( m_page->GetRightPageMarginStr( ) );

    SetTopContentMargin( Design::AlbumPageDefaults( )->TopContentMarginStr( ) );
    SetBottomContentMargin( Design::AlbumPageDefaults( )->BottomContentMarginStr( ) );
    SetLeftContentMargin( Design::AlbumPageDefaults( )->LeftContentMarginStr( ) );
    SetRightContentMargin( Design::AlbumPageDefaults( )->RightContentMarginStr( ) );


    // m_dialogVerticalSizer->Layout( );

     //    wxListBox* m_statusList;


}


void PageDetailsPanel::SetupDialog( Design::Page* page )
{

    m_page = page;

    UpdateControls( );

    wxArrayString* errors = m_page->GetErrorArray( );
    if ( !errors->IsEmpty( ) )
    {
        m_statusList->InsertItems( *errors, 0 );
    }

};



bool PageDetailsPanel::ShowToolTips( )
{
    return true;
}



void PageDetailsPanel::SetTitleFont( wxFont font )
{
    m_titleFontPicker->SetSelectedFont( font );
}

void PageDetailsPanel::SetTitleColor( wxColour color )
{
    m_titleColorPicker->SetColour( color );
}


void PageDetailsPanel::SetSubTitleFont( wxFont font )
{
    if ( !font.IsOk( ) )
    {
        std::cout << "Font invalid\n";
    }
    m_subTitleFontPicker->SetSelectedFont( font );
}

void PageDetailsPanel::SetSubTitleColor( wxColour color )
{
    m_subTitleColorPicker->SetColour( color );
}

void PageDetailsPanel::SetTitle( wxString name )
{
    m_titleHelper->titleLabel->SetValue( name );
}

wxString PageDetailsPanel::GetTitle( )
{
    return m_titleHelper->titleLabel->GetValue( );
}
void PageDetailsPanel::SetSubTitle( wxString subTitle )
{
    m_titleHelper->subTitleLabel->SetValue( subTitle );
}
wxString PageDetailsPanel::GetSubTitle( )
{
    return m_titleHelper->subTitleLabel->GetValue( );
};

void PageDetailsPanel::SetNameModified( bool state )
{
    m_titleHelper->titleLabel->SetModified( state );
};


void PageDetailsPanel::SetShowTitle( bool state )
{
    m_titleHelper->titleCheckbox->SetValue( state );
    UpdateTitleState( m_titleHelper );
};

void PageDetailsPanel::SetShowSubTitle( bool state )
{
    m_titleHelper->subTitleCheckbox->SetValue( state );
    UpdateSubTitleState( m_titleHelper );
};

void PageDetailsPanel::SetShowBorder( bool state )
{
    m_showBorder->SetValue( state );
};

void PageDetailsPanel::SetTopPageMargin( wxString str )
{
    m_topPageMargin->ChangeValue( str );
}
void PageDetailsPanel::SetBottomPageMargin( wxString str )
{
    m_bottomPageMargin->ChangeValue( str );
}
void PageDetailsPanel::SetLeftPageMargin( wxString str )
{
    m_leftPageMargin->ChangeValue( str );
}
void PageDetailsPanel::SetRightPageMargin( wxString str )
{
    m_rightPageMargin->ChangeValue( str );
}



void PageDetailsPanel::SetShow( bool state )
{
    m_frameCheckbox->SetValue( state );
};

bool PageDetailsPanel::GetShowTitle( )
{
    return m_titleHelper->titleCheckbox->IsChecked( );
};;
bool PageDetailsPanel::GetShowSubTitle( )
{
    return m_titleHelper->subTitleCheckbox->IsChecked( );
};;

bool PageDetailsPanel::GetShow( )
{
    return m_frameCheckbox->IsChecked( );
};


//--------------

void PageDetailsPanel::SetTopContentMargin( wxString topContentMargin )
{
    m_topContentMargin->ChangeValue( topContentMargin );
}

//--------------

void PageDetailsPanel::SetBottomContentMargin( wxString bottomContentMargin )
{
    m_bottomContentMargin->ChangeValue( bottomContentMargin );
}

//--------------

void PageDetailsPanel::SetLeftContentMargin( wxString leftContentMargin )
{
    m_leftContentMargin->ChangeValue( leftContentMargin );
}

//--------------

void PageDetailsPanel::SetRightContentMargin( wxString rightPageMargin )
{
    m_rightContentMargin->ChangeValue( rightPageMargin );
}


void PageDetailsPanel::OnTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_TitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );
    //std::cout << "PageDetailsPanel::OnTitleDefaultClick " << font.GetNativeFontInfoDesc( ) << "\n";
    m_page->GetTitleFrame( )->SetHeadingFont( font, color );
    event.Skip( );
}


void PageDetailsPanel::OnOrientationchoiceSelected( wxCommandEvent& event )
{
    m_page->Orientation( Design::OrientationStrings[ m_orientationChoice->GetSelection( ) ] );
    ////@begin wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_ORIENTATIONCHOICE in PageDetailsPanel.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_ORIENTATIONCHOICE in PageDetailsPanel. 
}



void PageDetailsPanel::OnSubTitleCheckboxClick( wxCommandEvent& event )
{
    m_page->SetShowSubTitle( m_titleHelper->subTitleCheckbox->GetValue( ) );
    UpdateSubTitleState( m_titleHelper );
};


void PageDetailsPanel::OnSubTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_SubTitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_subTitleFontPicker->SetSelectedFont( font );
    m_subTitleColorPicker->SetColour( color );
    //std::cout << "PageDetailsPanel::OnSubTitleDefaultClick " << font.GetNativeFontInfoDesc( ) << "\n";
    m_page->GetTitleFrame( )->SetSubHeadingFont( font, color );

    event.Skip( );
}


void PageDetailsPanel::OnTitleCheckboxClick( wxCommandEvent& event )
{
    m_page->SetShowTitle( m_titleHelper->titleCheckbox->GetValue( ) );
    UpdateTitleState( m_titleHelper );
    GetAlbumTreeCtrl( )->GetCurrentTreeID( );
}

void PageDetailsPanel::OnTitleTextChanged( wxCommandEvent& event )
{
    wxString title = m_titleHelper->titleLabel->GetValue( );
    m_page->SetTitleString( title );
}
void PageDetailsPanel::OnSubTitleTextChanged( wxCommandEvent& event )
{
    wxString subTitle = m_titleHelper->subTitleLabel->GetValue( );
    m_page->SetSubTitleString( subTitle );
}

void PageDetailsPanel::OnTitleFontPicker( wxFontPickerEvent& event )
{
    m_page->GetTitleFrame( )->SetHeadingFont( m_titleFontPicker->GetSelectedFont( ), m_titleColorPicker->GetColour( ) );
}

void PageDetailsPanel::OnTitleColorPicker( wxColourPickerEvent& event )
{
    m_page->GetTitleFrame( )->SetHeadingFont( m_titleFontPicker->GetSelectedFont( ), m_titleColorPicker->GetColour( ) );
}

void PageDetailsPanel::OnSubTitleFontPicker( wxFontPickerEvent& event )
{
    m_page->GetTitleFrame( )->SetSubHeadingFont( m_subTitleFontPicker->GetSelectedFont( ), m_subTitleColorPicker->GetColour( ) );
}

void PageDetailsPanel::OnSubTitleColorPicker( wxColourPickerEvent& event )
{
    m_page->GetTitleFrame( )->SetSubHeadingFont( m_subTitleFontPicker->GetSelectedFont( ), m_subTitleColorPicker->GetColour( ) );
}

//--------------

void PageDetailsPanel::OnTopPageMargin( wxCommandEvent& event )
{
    double val;
    m_topPageMargin->GetValue( ).ToDouble( &val );
    m_page->SetTopPageMargin( val );
    event.Skip( );
}

//--------------

void PageDetailsPanel::OnBottomPageMargin( wxCommandEvent& event )
{
    double val;
    m_bottomPageMargin->GetValue( ).ToDouble( &val );
    m_page->SetBottomPageMargin( val );
    event.Skip( );
}

//--------------

void PageDetailsPanel::OnLeftPageMargin( wxCommandEvent& event )
{
    double val;
    m_leftPageMargin->GetValue( ).ToDouble( &val );
    m_page->SetLeftPageMargin( val );
    event.Skip( );

}

//--------------

void PageDetailsPanel::OnRightPageMargin( wxCommandEvent& event )
{
    double val;
    m_rightPageMargin->GetValue( ).ToDouble( &val );
    m_page->SetRightPageMargin( val );
    event.Skip( );
}

//--------------

void PageDetailsPanel::OnShowBorderCheckBoxClick( wxCommandEvent& event )
{
    m_page->SetShowBorder( m_showBorder->GetValue( ) );
    Refresh( );
    event.Skip( );
}

//-------

void PageDetailsPanel::SetStatusList( )
{
    m_statusList->Clear( );
    wxArrayString* errors = m_page->GetErrorArray( );
    if ( !errors->IsEmpty( ) )
    {
        m_statusList->InsertItems( *errors, 0 );
    }
}
//-------

void PageDetailsPanel::Update( )
{
    GetAlbumTreeCtrl( )->Update( );
    SetStatusList( );
}

//--------------

void PageDetailsPanel::OnTopContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->TopContentMargin( Design::AlbumPageDefaults( )->TopContentMarginStr( ) );
    Update( );
    event.Skip( );
}

//--------------

void PageDetailsPanel::OnBottomContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->BottomContentMargin( Design::AlbumPageDefaults( )->BottomContentMarginStr( ) );

    Update( );
    event.Skip( );
}

//--------------

void PageDetailsPanel::OnLeftContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->LeftContentMargin( Design::AlbumPageDefaults( )->LeftContentMarginStr( ) );
    Update( );
    event.Skip( );

}

//--------------

void PageDetailsPanel::OnRightContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->RightContentMargin( Design::AlbumPageDefaults( )->RightContentMarginStr( ) );

    Update( );
    event.Skip( );
}

//--------------

//--------------

void PageDetailsPanel::SetBorderSize( wxString borderSize )
{
    m_borderSize->ChangeValue( borderSize );
}

//--------------

wxString PageDetailsPanel::GetBorderSize( ) {
    return m_borderSize->GetValue( );
}

//--------------

void PageDetailsPanel::OnBorderSize( wxCommandEvent& event )
{
    m_page->SetBorderSize( GetBorderSize( ) );

    Update( );
    event.Skip( );
}
