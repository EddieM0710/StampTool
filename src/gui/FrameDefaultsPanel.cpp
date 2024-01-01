/*
 * @file  FrameDefaultsPanel.cpp
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

#include "gui/FrameDefaultsPanel.h"
#include "gui/LabeledTextBox.h"
#include "gui/FontPickerHelper.h"
#include "design/TitleFrame.h"
#include "design/Page.h"
#include "design/Album.h"
#include "design/DesignDefs.h"
#include "design/FrameDefaults.h"
#include "utils/FontList.h"
#include "utils/Settings.h"
#include "Defs.h"



IMPLEMENT_DYNAMIC_CLASS( FrameDefaultsPanel, HelperPanel )


BEGIN_EVENT_TABLE( FrameDefaultsPanel, HelperPanel )
END_EVENT_TABLE( )

//----------

FrameDefaultsPanel::FrameDefaultsPanel( )
{
    Init( );
}

//----------

FrameDefaultsPanel::FrameDefaultsPanel( wxWindow* parent, wxWindowID id,
    const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
    // SetMinClientSize( wxSize( 100, 100 ) );
}

//----------

bool FrameDefaultsPanel::Create( wxWindow* parent, wxWindowID id,
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

//----------

FrameDefaultsPanel::~FrameDefaultsPanel( )
{

}

//----------

void FrameDefaultsPanel::Init( )
{
    m_frameCheckbox = NULL;
}

//----------

void FrameDefaultsPanel::CreateControls( )
{

    FrameDefaultsPanel* thePanel = this;

    wxBoxSizer* rowColHorizontalSizer = new wxBoxSizer( wxVERTICAL );
    thePanel->SetSizer( rowColHorizontalSizer );


    int lastID = ID_LastID;

    wxNotebook* focusNotebook = new wxNotebook( thePanel, ++lastID,
        wxDefaultPosition, wxDefaultSize, wxBK_LEFT );
    focusNotebook->SetPadding( wxSize( 1, 1 ) );
    rowColHorizontalSizer->Add( focusNotebook, 1, wxGROW | wxALL, 5 );

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


    m_frameCheckbox = SetupCheckBox( commonPanel, leftCommonVerticalSizer, lastID,
        ( "Show Frame" ), wxCommandEventHandler( FrameDefaultsPanel::OnFrameCheckboxClick ) );
    m_frameCheckbox->SetValue( false );


    m_titleHelper = SetupTitleHelper( commonPanel, leftCommonVerticalSizer, lastID, HasSubTitle,
        wxCommandEventHandler( FrameDefaultsPanel::OnTitleCheckboxClick ),
        wxCommandEventHandler( FrameDefaultsPanel::OnSubTitleCheckboxClick ),
        wxCommandEventHandler( FrameDefaultsPanel::OnSubTitleCheckboxClick ) );



    wxBoxSizer* memberSpacingVSizer;
    wxStaticBox* memberSpacingStaticBox = SetupBoxSizer( commonPanel, middleCommonVerticalSizer,
        "Member Position", lastID, memberSpacingVSizer, wxHORIZONTAL );

    m_fixedSpacingCheckbox = SetupCheckBox( memberSpacingStaticBox, memberSpacingVSizer, lastID,
        ( "Fixed Spacing" ), wxCommandEventHandler( FrameDefaultsPanel::OnFixedClick ) );
    m_fixedSpacingCheckbox->SetToolTip( _( "Normally Calculated. Enable for Fixed Spacing." ) );

    m_fixedSpaceSize = new wxTextCtrl( memberSpacingStaticBox, ++lastID, _( "4" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_fixedSpaceSize->SetToolTip( _( "mm" ) );
    m_fixedSpaceSize->Enable( false );
    memberSpacingVSizer->Add( m_fixedSpaceSize, 0, wxALIGN_LEFT | wxALL, 5 );



    wxBoxSizer* alignmentModeVSizer;
    wxStaticBox* alignmentModeBox = SetupBoxSizer( commonPanel, rightCommonVerticalSizer, "Stamp Member Alignment Mode", lastID, alignmentModeVSizer, wxHORIZONTAL );

    m_alignTopButton = SetupRadioButton( alignmentModeBox, alignmentModeVSizer, lastID, _( "Top" ), false,
        wxCommandEventHandler( FrameDefaultsPanel::OnAlignmentModeButtonSelected ) );

    m_alignMiddleButton = SetupRadioButton( alignmentModeBox, alignmentModeVSizer, lastID, _( "Middle" ), false,
        wxCommandEventHandler( FrameDefaultsPanel::OnAlignmentModeButtonSelected ) );

    m_alignBottomButton = SetupRadioButton( alignmentModeBox, alignmentModeVSizer, lastID, _( "Bottom" ), false,
        wxCommandEventHandler( FrameDefaultsPanel::OnAlignmentModeButtonSelected ) );



    wxBoxSizer* contentMarginBoxVSizer;
    wxStaticBox* contenrMarginBox = SetupBoxSizer( advancedPanel, leftAdvancedVerticalSizer,
        "Content Margin", lastID, contentMarginBoxVSizer, wxVERTICAL );

    wxBoxSizer* contentMarginBoxHSizer = new wxBoxSizer( wxHORIZONTAL );
    contentMarginBoxVSizer->Add( contentMarginBoxHSizer, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( contentMarginBoxHSizer );

    m_topContentMargin = SetupLabelText( contenrMarginBox, contentMarginBoxHSizer, lastID,
        _( "Top" ), false, wxCommandEventHandler( FrameDefaultsPanel::OnTopContentMargin ) );
    m_topContentMargin->SetToolTip( _( "Content top margin in mm." ) );
    HorizontalSpacer( contentMarginBoxHSizer );

    m_bottomContentMargin = SetupLabelText( contenrMarginBox, contentMarginBoxHSizer, lastID,
        _( "Bottom" ), false, wxCommandEventHandler( FrameDefaultsPanel::OnBottomContentMargin ) );
    m_bottomContentMargin->SetToolTip( _( "Content bottom margin in mm." ) );


    wxBoxSizer* itemBoxSizer110 = new wxBoxSizer( wxHORIZONTAL );
    contentMarginBoxVSizer->Add( itemBoxSizer110, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer110 );

    m_leftContentMargin = SetupLabelText( contenrMarginBox, itemBoxSizer110, lastID,
        _( "Left" ), false, wxCommandEventHandler( FrameDefaultsPanel::OnLeftContentMargin ) );
    m_leftContentMargin->SetToolTip( _( "Content left margin in mm." ) );

    HorizontalSpacer( itemBoxSizer110 );

    m_rightContentMargin = SetupLabelText( contenrMarginBox, itemBoxSizer110, lastID,
        _( "Right" ), false, wxCommandEventHandler( FrameDefaultsPanel::OnRightContentMargin ) );
    m_rightContentMargin->SetToolTip( _( "Content right margin in mm." ) );


}

//--------------

void FrameDefaultsPanel::UpdateControls( )
{
    SetFixedSpacingSize( Design::AlbumFrameDefaults( )->FixedSpacingStr( ) );
    SetFixedSpacing( );
    SetTopContentMargin( Design::AlbumFrameDefaults( )->TopContentMarginStr( ) );
    SetBottomContentMargin( Design::AlbumFrameDefaults( )->BottomContentMarginStr( ) );
    SetLeftContentMargin( Design::AlbumFrameDefaults( )->LeftContentMarginStr( ) );
    SetRightContentMargin( Design::AlbumFrameDefaults( )->RightContentMarginStr( ) );
    m_titleHelper->subTitleCheckbox->SetValue( Design::AlbumPageDefaults( )->ShowSubTitle( ) );
    m_titleHelper->titleCheckbox->SetValue( Design::AlbumPageDefaults( )->ShowTitle( ) );

    //memberSpacing
     //   Stampalignment


}

//--------------

void FrameDefaultsPanel::SetupDialog( Design::Page* page )
{
    UpdateControls( );
};

//----------

bool FrameDefaultsPanel::ShowToolTips( )
{
    return true;
}

//----------

void FrameDefaultsPanel::OnSubTitleCheckboxClick( wxCommandEvent& event )
{
    Design::AlbumFrameDefaults( )->ShowSubTitle( m_titleHelper->subTitleCheckbox->GetValue( ) );
    UpdateSubTitleState( m_titleHelper );
    Update( );
    event.Skip( );
};

//----------

void FrameDefaultsPanel::OnTitleCheckboxClick( wxCommandEvent& event )
{
    Design::AlbumFrameDefaults( )->ShowTitle( m_titleHelper->titleCheckbox->GetValue( ) );
    UpdateTitleState( m_titleHelper );
    Update( );
    event.Skip( );
}

//----------

void FrameDefaultsPanel::SetFixedSpacing( )
{
    if ( Design::AlbumFrameDefaults( )->CalculateSpacing( ) )
    {
        m_fixedSpacingCheckbox->SetValue( false );
        m_fixedSpaceSize->Enable( false );
    }
    else
    {
        m_fixedSpacingCheckbox->SetValue( true );
        m_fixedSpaceSize->Enable( true );
    }
}


//----------

void FrameDefaultsPanel::OnFrameCheckboxClick( wxCommandEvent& event )
{
    Design::AlbumFrameDefaults( )->ShowFrame( m_frameCheckbox->GetValue( ) );
    Update( );
    event.Skip( );
}

//----------

void FrameDefaultsPanel::OnTopContentMargin( wxCommandEvent& event )
{
    wxString valAlbum = Design::AlbumFrameDefaults( )->TopContentMarginStr( );
    wxString valLocal = m_topContentMargin->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        Design::AlbumFrameDefaults( )->TopContentMargin( valLocal );
    }
    Update( );
    event.Skip( );
}

//----------

void FrameDefaultsPanel::OnBottomContentMargin( wxCommandEvent& event )
{
    wxString valAlbum = Design::AlbumFrameDefaults( )->BottomContentMarginStr( );
    wxString valLocal = m_bottomContentMargin->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        Design::AlbumFrameDefaults( )->BottomContentMargin( valLocal );
    }
    Update( );
    event.Skip( );
}

//----------

void FrameDefaultsPanel::OnLeftContentMargin( wxCommandEvent& event )
{
    wxString valAlbum = Design::AlbumFrameDefaults( )->LeftContentMarginStr( );
    wxString valLocal = m_leftContentMargin->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        Design::AlbumFrameDefaults( )->LeftContentMargin( valLocal );
    }
    Update( );
    event.Skip( );
}

//----------

void FrameDefaultsPanel::OnRightContentMargin( wxCommandEvent& event )
{
    wxString valAlbum = Design::AlbumFrameDefaults( )->RightContentMarginStr( );
    wxString valLocal = m_rightContentMargin->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        Design::AlbumFrameDefaults( )->RightContentMargin( valLocal );
    }
    Update( );
    event.Skip( );
}

// //----------

// void FrameDefaultsPanel::SetFixedSpacing( bool val )
// {
//     m_fixedSpacingCheckbox->SetValue( val );
//     if ( val )
//     {
//         m_fixedSpaceSize->Enable( false );
//     }
//     else
//     {
//         m_fixedSpaceSize->Enable( true );
//     }
// };

//----------

// void FrameDefaultsPanel::OnCalculatedClick( wxCommandEvent& event )
// {
//     m_fixedSpaceSize->Enable( false );
//     //    m_row->SetFixedSpacing( true );
//     event.Skip( );
// }
// //----------


void FrameDefaultsPanel::OnFixedClick( wxCommandEvent& event )
{
    m_fixedSpaceSize->Enable( true );
    if ( m_fixedSpacingCheckbox->IsChecked( ) )
    {
        Design::AlbumFrameDefaults( )->CalculateSpacing( false );
        m_fixedSpaceSize->Enable( true );

    }
    else
    {
        Design::AlbumFrameDefaults( )->CalculateSpacing( true );
        m_fixedSpaceSize->Enable( false );
    }

    Update( );
    event.Skip( );
}

//----------

void FrameDefaultsPanel::SetAlignmentMode( )
{
    Design::AlignmentModeType mode = Design::AlbumFrameDefaults( )->GetAlignmentModeType( );
    if ( mode == Design::AlignTop )
    {
        m_alignTopButton->SetValue( true );
    }
    else if ( mode == Design::AlignMiddle )
    {
        m_alignMiddleButton->SetValue( true );
    }
    else // if ( mode == Design::AlignBottom )
    {
        m_alignBottomButton->SetValue( true );
    }

}

//----------

void FrameDefaultsPanel::OnAlignmentModeButtonSelected( wxCommandEvent& event )
{
    if ( m_alignTopButton->GetValue( ) )
    {
        Design::AlbumFrameDefaults( )->SetAlignmentModeType( Design::AlignTop );
    }
    else if ( m_alignMiddleButton->GetValue( ) )
    {
        Design::AlbumFrameDefaults( )->SetAlignmentModeType( Design::AlignMiddle );
    }
    else if ( m_alignBottomButton->GetValue( ) )
    {
        Design::AlbumFrameDefaults( )->SetAlignmentModeType( Design::AlignBottom );
    }

    Update( );
    event.Skip( );
}


//--------------

void FrameDefaultsPanel::SetTopContentMargin( wxString topContentMargin )
{
    m_topContentMargin->ChangeValue( topContentMargin );
}

//--------------

void FrameDefaultsPanel::SetBottomContentMargin( wxString bottomContentMargin )
{
    m_bottomContentMargin->ChangeValue( bottomContentMargin );
}

//--------------

void FrameDefaultsPanel::SetLeftContentMargin( wxString leftContentMargin )
{
    m_leftContentMargin->ChangeValue( leftContentMargin );
}

//--------------

void FrameDefaultsPanel::SetRightContentMargin( wxString rightPageMargin )
{
    m_rightContentMargin->ChangeValue( rightPageMargin );
}
//-------

void FrameDefaultsPanel::Update( )
{
    GetAlbumTreeCtrl( )->Update( );
}