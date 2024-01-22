/*
 * @file src/gui/CompEntry.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-29
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

#ifndef _COMPENTRY_H_
#define _COMPENTRY_H_

#include "catalog/CatalogDefs.h"
#include "catalog/Entry.h"
#include "catalog/MergeList.h"
#include "gui/ComparePanel.h"

#define ID_COMPENTRY 10000
#define ID_TARGETENTRY 10015
#define ID_COPYATTRIBUTE 10017
#define ID_UNDOATTRIBCOPY 10001
#define ID_MERGEENTRY 10016
#define SYMBOL_COMPENTRY_STYLE wxTAB_TRAVERSAL
#define SYMBOL_COMPENTRY_TITLE _("CompEntry")
#define SYMBOL_COMPENTRY_IDNAME ID_COMPENTRY
#define SYMBOL_COMPENTRY_SIZE wxSize(600, 300)
#define SYMBOL_COMPENTRY_POSITION wxDefaultPosition

class MergeEntry;


class CompEntry : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( CompEntry )
    DECLARE_EVENT_TABLE( )

public:
    CompEntry( );
    CompEntry( wxWindow* parent, wxWindowID id = SYMBOL_COMPENTRY_IDNAME, const wxPoint& pos = SYMBOL_COMPENTRY_POSITION, const wxSize& size = SYMBOL_COMPENTRY_SIZE, long style = SYMBOL_COMPENTRY_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_COMPENTRY_IDNAME, const wxPoint& pos = SYMBOL_COMPENTRY_POSITION, const wxSize& size = SYMBOL_COMPENTRY_SIZE, long style = SYMBOL_COMPENTRY_STYLE );

    ~CompEntry( );

    void Init( );

    void CreateControls( );

    void CopyAttribute( );

    void UndoAttribCopy( );

    void OnTargetEntryTextUpdated( wxCommandEvent& event );

    void OnCopyAttributeClick( wxCommandEvent& event );

    void OnUndoAttribCopyClick( wxCommandEvent& event );

    void OnMergeEntryTextUpdated( wxCommandEvent& event );

    wxBitmap GetBitmapResource( const wxString& name );

    wxIcon GetIconResource( const wxString& name );

    static bool ShowToolTips( );

    void SetTargetValue( wxString str )
    {
        m_targetVal->ChangeValue( str );
        m_undoVal = str;
    };

    wxString GetTargetValue( )
    {
        return m_targetVal->GetValue( );
    };

    void  SetBackground( );

    void SetTypeName( wxString str )
    {
        m_typeName->SetLabel( str );
    };


    void SetMergeValue( wxString str )
    {
        m_mergeVal->ChangeValue( str );
    };

    wxString GetMergeValue( )
    {
        return m_mergeVal->GetValue( );;
    };

    void Update( Catalog::MergeData* mergeEntry, Catalog::DataTypes type );

    void SetComparePanel( ComparePanel* comparePanel ){
        m_comparePanel = comparePanel;
    }

    ComparePanel* m_comparePanel;
    wxStaticText* m_typeName;
    wxTextCtrl* m_targetVal;
    wxString m_undoVal;
    Catalog::DataTypes m_type;
    Catalog::Entry* m_targetFileEntry;
    Catalog::Entry* m_mergeFileEntry;
    wxBitmapButton* m_merge;
    wxBitmapButton* m_undo;
    wxTextCtrl* m_mergeVal;

};

#endif

