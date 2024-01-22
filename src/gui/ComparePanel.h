/*
 * @file src/gui/ComparePanel.h
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
#ifndef _ComparePanel_H_
#define _ComparePanel_H_

#include "wx/listctrl.h"
#include "wx/splitter.h"

#include "catalog/CatalogDefs.h"

#include "catalog/MergeList.h"



#define ID_COMPAREPANEL 10000
#define ID_TARGETFILE 10001
#define ID_MERGEFILE 10002
#define ID_NEXTENTRY 10003
#define ID_PREVENTRY 10004
#define ID_SHOWDIFFSONLY 10005
#define ID_SHOWALL 10006
#define ID_COPYALL 10009
#define ID_UNDOCOPYALL 10008
#define ID_SCROLLEDWINDOW 10010
#define ID_TARGETFILEPICKER 10015
#define ID_MERGEFILEPICKER 10017
#define ID_LISTCTRL 10018
#define ID_SPLITTERWINDOW 10019
#define ID_SCROLLEDWINDOW2 10020
#define ID_PANEL 10021
#define wxID_UPDATETAEGET 10022
#define wxID_UPDATEMERGE 10023
#define ID_DEEPRADIOBUTTON 10024
#define ID_SELECTEDRADIOBUTTON 10025
#define ID_CHECKLISTBOX 10026
#define SYMBOL_COMPAREPANEL_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_COMPAREPANEL_TITLE _("ComparePanel")
#define SYMBOL_COMPAREPANEL_IDNAME ID_COMPAREPANEL
#define SYMBOL_COMPAREPANEL_SIZE wxSize(900, 800)
#define SYMBOL_COMPAREPANEL_POSITION wxDefaultPosition

class CompEntry;
class CompareTreeCtrl;

class ComparePanel : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( ComparePanel )
    DECLARE_EVENT_TABLE( )

public:
    ComparePanel( );
    ComparePanel( wxWindow* parent,
        wxWindowID id = SYMBOL_COMPAREPANEL_IDNAME,
        const wxString& caption = SYMBOL_COMPAREPANEL_TITLE,
        const wxPoint& pos = SYMBOL_COMPAREPANEL_POSITION,
        const wxSize& size = SYMBOL_COMPAREPANEL_SIZE,
        long style = SYMBOL_COMPAREPANEL_STYLE );

    bool Create( wxWindow* parent,
        wxWindowID id = SYMBOL_COMPAREPANEL_IDNAME,
        const wxString& caption = SYMBOL_COMPAREPANEL_TITLE,
        const wxPoint& pos = SYMBOL_COMPAREPANEL_POSITION,
        const wxSize& size = SYMBOL_COMPAREPANEL_SIZE,
        long style = SYMBOL_COMPAREPANEL_STYLE );

    ~ComparePanel( );

    void Init( );

    void CreateControls( );

    void OnTargetFileTextUpdated( wxCommandEvent& event );

    void LoadListBox( );

    void OnMergeFileTextUpdated( wxCommandEvent& event );

    void SetBackground( );

    void OnNextentryClick( wxCommandEvent& event );

    void OnPrevEntryClick( wxCommandEvent& event );

    void OnShowDiffsOnlySelected( wxCommandEvent& event );

    void OnShowallSelected( wxCommandEvent& event );

    void OnCopyAllClick( wxCommandEvent& event );

    void OnUndoCopyAllClick( wxCommandEvent& event );

    void OnOkClick( wxCommandEvent& event );

    void OnCancelClick( wxCommandEvent& event );

    void OnUpdateTarget( wxCommandEvent& event );

    void OnUpdateMerge( wxCommandEvent& event );

    void OnClear( wxCommandEvent& event );

    /// wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_DEEPRADIOBUTTON
    void OnDeepRadioButton( wxCommandEvent& event );

    /// wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_SELECTEDRADIOBUTTON
    void OnSelectedRadioButton( wxCommandEvent& event );

    /// wxEVT_COMMAND_LISTBOX_DOUBLECLICKED event handler for ID_CHECKLISTBOX
    void OnChecklistboxDoubleClicked( wxCommandEvent& event );

    /// wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_CHECKLISTBOX
    void OnChecklistboxSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHECKLISTBOX_TOGGLED event handler for ID_CHECKLISTBOX
    void OnCheckListBoxToggled( wxCommandEvent& event );

    wxArrayInt GetCheckedItems( );

    bool CompareEnabled( int i );

    wxString SelectFile( wxString caption );

    wxBitmap GetBitmapResource( const wxString& name );

    wxIcon GetIconResource( const wxString& name );

    static bool ShowToolTips( );

    void UpdateCompEntryTable( Catalog::MergeData* mergeEntry );
    void OnListCtrlSelected( wxListEvent& event );

    wxChoice* m_targetFile;
    wxChoice* m_mergeFile;
    wxStaticText* m_typeName;
    wxTextCtrl* m_targetVal;
    wxBitmapButton* m_merge;
    wxBitmapButton* m_undo;
    wxTextCtrl* m_mergeVal;
    // wxListView* m_listBox;
    wxBitmapButton* m_copyAllButton;

    wxRadioButton* m_deepCompare;
    wxRadioButton* m_SelectedCompare;
    wxCheckListBox* m_CompareCheckBox;
    wxArrayInt m_checkedItems;
    wxArrayString m_catalogListCtrlStrings;
    Utils::Volume* m_targetVolume;
    Utils::Volume* m_mergeVolume;
    Catalog::MergeList* m_mergeList;
    CompEntry* m_compEntry[ Catalog::DT_NbrTypes ];
    CompareTreeCtrl* m_compareTreeCtrl;

};

#endif
