/*
 * @file AlbumSplitterWiindow.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-19
 *
 * @copyright Copyright ( c ) 2021
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

#ifndef _ALBUMSPLITTERWIINDOW_H_
#define _ALBUMSPLITTERWIINDOW_H_
#include "wx/splitter.h"
#include "wx/treectrl.h"
#include "gui/GuiDefs.h"
#include <wx/slider.h>

class wxSplitterWindow;
class wxTreeCtrl;
class wxWindow;

class AlbumTreeCtrl;
class AlbumTreePanel;
class AlbumImagePanel;

#define SYMBOL_STAMPTOOLAlbumPanel_STYLE wxTAB_TRAVERSAL
#define SYMBOL_STAMPTOOLAlbumPanel_TITLE _( "StampToolPanel" )
#define SYMBOL_STAMPTOOLAlbumPanel_IDNAME ID_ALBUMAlbumPanel
#define SYMBOL_STAMPTOOLAlbumPanel_SIZE wxSize( 400, 300 )
#define SYMBOL_STAMPTOOLAlbumPanel_POSITION wxDefaultPosition

/*
 * AlbumPanel class declaration
 */

class AlbumPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( AlbumPanel )
        DECLARE_EVENT_TABLE( )

public:
    enum AlbumAlbumPanelGuiDefs
    {
        ID_SECONDARYSPLITTERWINDOW = ID_ALBUMAlbumPanel * 1,
        ID_SCROLLEDWINDOW,
        ID_AECMDTREECTRL,
        ID_PANEL,
        ID_CDDATATEXTCTRL,
        ID_ALBUMALBUMIMAGEPANEL,
        ID_ALBUMZOOMSLIDER,
        ID_LISTCHOICE,
        ID_MANAGEBUTTON,
        ID_NEWDESIGN,
        ID_OPENDESIGN,
        ID_REMOVEDESIGN,
        ID_GENERATEPDF
    };

    ///  @brief Construct a new Album Design Panel object
    ///  
    AlbumPanel( );

    ///  @brief Construct a new Album Design Panel object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    AlbumPanel( wxWindow* parent, wxWindowID id = SYMBOL_STAMPTOOLAlbumPanel_IDNAME, const wxPoint& pos = SYMBOL_STAMPTOOLAlbumPanel_POSITION, const wxSize& size = SYMBOL_STAMPTOOLAlbumPanel_SIZE, long style = SYMBOL_STAMPTOOLAlbumPanel_STYLE );

    ///  @brief Destroy the Album Design Panel object
    ///  
    ~AlbumPanel( );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    ///  @return true 
    ///  @return false 
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_STAMPTOOLAlbumPanel_IDNAME, const wxPoint& pos = SYMBOL_STAMPTOOLAlbumPanel_POSITION, const wxSize& size = SYMBOL_STAMPTOOLAlbumPanel_SIZE, long style = SYMBOL_STAMPTOOLAlbumPanel_STYLE );

    ///  @brief Create a Controls object
    ///  
    void CreateControls( );

    ///  @brief 
    ///  
    void Init( );

    ///  @brief Get the Album Design Tree Panel object
    ///  
    ///  @return AlbumTreePanel* 
    AlbumTreePanel* GetAlbumTreePanel( ) { return m_albumTreePanel; };

    void NewDesign( );

    void OpenDesign( );

    void SaveAsDesign( );

    ///  @brief Set the Album List Selection object
    ///  
    ///  @param i 
    void SetAlbumListSelection( int i )
    {
        m_albumListCtrl->SetSelection( i );
    };

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    static bool ShowToolTips( );

    ///  @brief Set the Sash Position object
    ///  
    ///  @param pos 
    void SetSashPosition( int pos ) { m_secondarySplitterWindow->SetSashPosition( pos ); };

    ///  @brief Set the Album List Strings object
    ///  
    ///  @param choices 
    void SetAlbumListStrings( wxArrayString& choices )
    {
        m_albumListCtrl->Clear( );
        m_albumListCtrl->Append( choices );
    };

    ///  @brief 
    ///  
    ///  @param event 
    void OnZoomsliderUpdated( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnManageClick( wxCommandEvent& event );

private:
    wxSplitterWindow* m_secondarySplitterWindow;
    AlbumImagePanel* m_albumImagePanel;
    wxSlider* m_zoomSlider; ///< Pointer to image soom slider
    AlbumTreePanel* m_albumTreePanel;
    wxChoice* m_albumListCtrl;
};

#endif

