/*
 * @file src/gui/CompEntry.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-19
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

#include "CompEntry.h"
#include "catalog/MergeList.h"

#include "art/back.xpm"
#include "art/redo.xpm"

IMPLEMENT_DYNAMIC_CLASS( CompEntry, wxPanel )

BEGIN_EVENT_TABLE( CompEntry, wxPanel )

EVT_TEXT( ID_TARGETENTRY, CompEntry::OnTargetEntryTextUpdated )
EVT_BUTTON( ID_COPYATTRIBUTE, CompEntry::OnCopyAttributeClick )
EVT_BUTTON( ID_UNDOATTRIBCOPY, CompEntry::OnUndoAttribCopyClick )
EVT_TEXT( ID_MERGEENTRY, CompEntry::OnMergeEntryTextUpdated )

END_EVENT_TABLE( )

CompEntry::CompEntry( )
{
    Init( );
}

CompEntry::CompEntry( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}


bool CompEntry::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}


CompEntry::~CompEntry( )
{

}

void CompEntry::Init( )
{
    m_typeName = NULL;
    m_targetVal = NULL;
    m_merge = NULL;
    m_undo = NULL;
    m_mergeVal = NULL;
}


void CompEntry::CreateControls( )
{

    CompEntry* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer1, 1, wxGROW | wxALL, 0 );

    m_typeName = new wxStaticText( itemPanel1, wxID_STATIC, _( "Static text" ), wxDefaultPosition, wxSize( 150, -1 ), wxALIGN_RIGHT );
    itemBoxSizer1->Add( m_typeName, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 2 );

    m_targetVal = new wxTextCtrl( itemPanel1, ID_TARGETENTRY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 2 );
    itemBoxSizer1->Add( m_targetVal, 6, wxGROW | wxALL, 2 );

    m_merge = new wxBitmapButton( itemPanel1, ID_COPYATTRIBUTE, wxBitmap( back_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxNO_BORDER );
    itemBoxSizer1->Add( m_merge, 1, wxALIGN_CENTER_VERTICAL | wxALL, 0 );

    m_undo = new wxBitmapButton( itemPanel1, ID_UNDOATTRIBCOPY, wxBitmap( redo_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer1->Add( m_undo, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0 );

    m_mergeVal = new wxTextCtrl( itemPanel1, ID_MERGEENTRY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 2 );
    itemBoxSizer1->Add( m_mergeVal, 6, wxGROW | wxALL, 2 );

}



void  CompEntry::SetBackground( )
{
    wxColour colour;
    if ( m_comparePanel->CompareEnabled( ( int ) m_type ) &&
        m_targetVal->GetValue( ).Cmp( m_mergeVal->GetValue( ) ) )
    {
        colour = *wxYELLOW;
    }
    else
    {
        colour = *wxWHITE;

    }

    m_targetVal->SetBackgroundColour( colour );
    m_mergeVal->SetBackgroundColour( colour );
};




void CompEntry::OnTargetEntryTextUpdated( wxCommandEvent& event )
{
    m_targetFileEntry->SetAttr( m_type, m_targetVal->GetValue( ) );
    SetBackground( );
    event.Skip( );
}

void CompEntry::CopyAttribute( )
{
    m_targetVal->ChangeValue( m_mergeVal->GetValue( ) );
    m_targetFileEntry->SetAttr( m_type, m_mergeVal->GetValue( ) );
    SetBackground( );
}

void CompEntry::OnCopyAttributeClick( wxCommandEvent& event )
{
    CopyAttribute( );
    event.Skip( );
}


void CompEntry::UndoAttribCopy( )
{
    m_targetVal->ChangeValue( m_undoVal );
    m_targetFileEntry->SetAttr( m_type, m_undoVal );
    SetBackground( );

}

void CompEntry::OnUndoAttribCopyClick( wxCommandEvent& event )
{
    UndoAttribCopy( );
    event.Skip( );
}



void CompEntry::OnMergeEntryTextUpdated( wxCommandEvent& event )
{
    event.Skip( );
}

void CompEntry::Update( Catalog::MergeEntry* mergeEntry, Catalog::DataTypes type )
{
    m_type = type;
    m_targetFileEntry = mergeEntry->GetTargetEntry( );
    m_mergeFileEntry = mergeEntry->GetMergeEntry( );
    if ( m_targetFileEntry )
    {
        SetTargetValue( m_targetFileEntry->GetAttr( m_type ) );
        m_merge->Enable( );
        m_undo->Enable( );
    }
    else
    {
        SetTargetValue( "" );
        m_merge->Disable( );
        m_undo->Disable( );
    }
    if ( m_mergeFileEntry )
    {
        SetMergeValue( m_mergeFileEntry->GetAttr( m_type ) );
        m_merge->Enable( );
        m_undo->Enable( );
    }
    else
    {
        SetMergeValue( "" );
        m_merge->Disable( );
        m_undo->Disable( );
    }

    SetBackground( );
}

