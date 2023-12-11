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
#include <wx/choice.h>
#include "wx/notebook.h"

class wxSplitterWindow;
class wxTreeCtrl;
class wxWindow;

class AlbumTreeCtrl;
class AlbumTreePanel;
class AlbumImagePanel;
class AlbumDetailsPanel;
class PageDetailsPanel;
class ColDetailsPanel;
class RowDetailsPanel;
class StampDetailsPanel;
//class TestDetailsPanel;

namespace Design {
    class AlbumBase;
}
class AlbumTOCTreeCtrl;

#define SYMBOL_STAMPTOOLAlbumPanel_STYLE wxTAB_TRAVERSAL
#define SYMBOL_STAMPTOOLAlbumPanel_TITLE _( "StampToolPanel" )
#define SYMBOL_STAMPTOOLAlbumPanel_IDNAME ID_ALBUMAlbumPanel
#define SYMBOL_STAMPTOOLAlbumPanel_SIZE wxSize( -1, -1 )
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
        ID_ALBUMALBUMIMAGEPANEL,
        ID_ALBUMZOOMSLIDER,
        ID_LISTCHOICE,
        ID_MANAGEBUTTON,
        ID_NEWDESIGN,
        ID_OPENDESIGN,
        ID_REMOVEDESIGN,
        ID_GENERATEPDF,
        ID_DETAILSSCROLLEDWINDOW,
        ID_HORIZONTALALBUMSPLITTERWINDOW1,
        ID_ALBUMLAYOUTPANEL,
        ID_LastID
    };


    AlbumPanel( );

    AlbumPanel( wxWindow* parent, wxWindowID id = SYMBOL_STAMPTOOLAlbumPanel_IDNAME, const wxPoint& pos = SYMBOL_STAMPTOOLAlbumPanel_POSITION, const wxSize& size = SYMBOL_STAMPTOOLAlbumPanel_SIZE, long style = SYMBOL_STAMPTOOLAlbumPanel_STYLE );

    ~AlbumPanel( );

    void Clear( );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_STAMPTOOLAlbumPanel_IDNAME, const wxPoint& pos = SYMBOL_STAMPTOOLAlbumPanel_POSITION, const wxSize& size = SYMBOL_STAMPTOOLAlbumPanel_SIZE, long style = SYMBOL_STAMPTOOLAlbumPanel_STYLE );

    wxPanel* CreateAlbumImageLayoutPanel( wxWindow* parent );

    void CreateControls( );

    wxPanel* CreateDetailsScrolledWindow( wxWindow* parent );

    wxNotebook* CreateImageDetailsSplitterWindow( wxWindow* parent );

    AlbumTreePanel* GetAlbumTreePanel( ) {
        return m_albumTreePanel;
    };

    void Init( );

    void NewDesign( );

    void OnGeneratePDFClick( wxCommandEvent& event );

    void OnManageClick( wxCommandEvent& event );

    void OnSplitterwindowSashPosChanged( wxSplitterEvent& event );

    void OnZoomsliderUpdated( wxCommandEvent& event );

    void OpenDesign( );

    void SaveAsDesign( );

    void SetAlbumListSelection( int i )
    {
        m_albumListCtrl->SetSelection( i );
    };

    void SetSashPosition( int pos ) {
        m_albumVerticalSplitterWindow->SetSashPosition( pos );
    };

    void ShowDetails( Design::AlbumBase* albumBase );

    static bool ShowToolTips( );

private:
    wxSplitterWindow* m_albumVerticalSplitterWindow;
    AlbumImagePanel* m_albumImagePanel;
    wxSlider* m_zoomSlider; ///< Pointer to image soom slider
    AlbumTreePanel* m_albumTreePanel;
    AlbumTOCTreeCtrl* m_tocTreeCtrl;

    AlbumDetailsPanel* m_albumDetailsPanel;
    PageDetailsPanel* m_pageDetailsPanel;
    ColDetailsPanel* m_colDetailsPanel;
    RowDetailsPanel* m_rowDetailsPanel;
    StampDetailsPanel* m_stampDetailsPanel;
    //TestDetailsPanel* m_testDetailsPanel;
    wxChoice* m_albumListCtrl;

    wxNotebook* m_imageDetailsSplitterWindow;

    wxPanel* m_detailsScrolledWindow;
};

#endif

