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

    ///  @brief Construct a new Catalog Details Dialog object
    ///  
    CatalogDetailsDialog( );

    ///  @brief Construct a new Catalog Details Dialog object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param caption 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    CatalogDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_CATALOGDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_CATALOGDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_CATALOGDETAILSDIALOG_SIZE, long style = SYMBOL_CATALOGDETAILSDIALOG_STYLE );

    ///  @brief Destroy the Catalog Details Dialog object
    ///  
    ~CatalogDetailsDialog( );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param caption 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    ///  @return true 
    ///  @return false 
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_CATALOGDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_CATALOGDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_CATALOGDETAILSDIALOG_SIZE, long style = SYMBOL_CATALOGDETAILSDIALOG_STYLE );

    ///  @brief Create a Controls object
    ///  
    void CreateControls( );

    wxString GetCatalogPath( );


    ///  @brief Get the Name object
    ///  
    ///  @return wxString 
    wxString GetName( );

    ///  @brief Get the Image Path object
    ///  
    ///  @return wxString 
    wxString GetImagePath( );

    ///  @brief 
    ///  
    void Init( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsNameModified( );

    ///  @brief 
    ///  
    ///  @param event 
    void OnOkClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnCatDirClick( wxCommandEvent& event );
    // void OnImageDirClick( wxCommandEvent& event );

    void SetCatalogFilename( wxString filename );

    ///  @brief Set the Design Tree I D object
    ///  
    ///  @param id 
    void SetDesignTreeID( wxTreeItemId id );

    ///  @brief Set the Image Path object
    ///  
    ///  @param str 
    void SetImagePath( wxString str );

    ///  @brief Set the Name object
    ///  
    ///  @param str 
    void SetName( wxString str );

    ///  @brief Set the Name Modified object
    ///  
    ///  @param state 
    void SetNameModified( bool state );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    static bool ShowToolTips( );

private:

    wxTreeItemId m_designTreeID;
    wxTextCtrl* m_name;
    LabeledTextBox* m_catPath;

};

#endif
