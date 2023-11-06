/*
 * @file CatalogDetailsDialog.h
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

#ifndef _CATALOGDETAILSDIALOG_H_
#define _CATALOGDETAILSDIALOG_H_

#include "wx/listctrl.h"

#include "gui/AlbumTreeCtrl.h"
#include "gui/GuiDefs.h"

class LabeledTextBox;
class wxListCtrl;

#define SYMBOL_CATALOGDETAILSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_CATALOGDETAILSDIALOG_TITLE _( "Import File Details Dialog" )
#define SYMBOL_CATALOGDETAILSDIALOG_IDNAME ID_CATALOGDETAILSDIALOG
#define SYMBOL_CATALOGDETAILSDIALOG_SIZE wxSize( 800, 400 )
#define SYMBOL_CATALOGDETAILSDIALOG_POSITION wxDefaultPosition

class CatalogDetailsDialog : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CatalogDetailsDialog )
    DECLARE_EVENT_TABLE( )

public:

    enum CatalogDetailsDialogGuiDefs
    {
        ID_NAMELABELEDTEXTBOX = ID_CATALOGDETAILSDIALOG + 1,
        ID_IMAGEPATHTEXTBOX,
        ID_VOLUMETITLECHECKBOX,
        ID_FRAMECHECKBOX,
        ID_DEFAULTFONTBUTTON,
        ID_VOLUMENAMEPANEL,
        ID_VOLUMELAYOUTPANEL,
        ID_VOLUMELAYOUTTEXTCTRL,
        ID_VOLUMENOTEBOOK,
        ID_CATDIRBUTTON,
        ID_IMAGEDIRBUTTON
    };


    CatalogDetailsDialog( );

    CatalogDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_CATALOGDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_CATALOGDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_CATALOGDETAILSDIALOG_SIZE, long style = SYMBOL_CATALOGDETAILSDIALOG_STYLE );

    ~CatalogDetailsDialog( );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_CATALOGDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_CATALOGDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_CATALOGDETAILSDIALOG_SIZE, long style = SYMBOL_CATALOGDETAILSDIALOG_STYLE );

    void CreateControls( );

    wxString GetCatalogPath( );

    wxString GetName( );

    wxString GetImagePath( );

    void Init( );

    bool IsNameModified( );

    void OnCatDirClick( wxCommandEvent& event );

    void OnOkClick( wxCommandEvent& event );

    void SetCatalogFilename( wxString filename );

    void SetDesignTreeID( wxTreeItemId id );

    void SetImagePath( wxString str );

    void SetName( wxString str );

    void SetNameModified( bool state );

    static bool ShowToolTips( );

private:

    wxTreeItemId m_designTreeID;
    wxTextCtrl* m_name;
    LabeledTextBox* m_catPath;

};

#endif
