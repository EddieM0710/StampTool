/**
 * @file StampToolPanel.h
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
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
 *
 */

#ifndef _STAMPTOOLPANEL_H_
#define _STAMPTOOLPANEL_H_

#include "wx/notebook.h"
#include "wx/splitter.h"
#include "wx/treectrl.h"

#include "gui/GuiDefs.h"

#include "gui/AlbumPanel.h"

 //#include "gui/WebViewPanel.h"

class CatalogPanel;
class wxNotebook;
class wxFlexGridSizer;
class StampDescriptionPanel;
class GenerateList;
class ImageGalleryPanel;


#define SYMBOL_STAMPTOOLPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_STAMPTOOLPANEL_TITLE _( "StampToolPanel" )
#define SYMBOL_STAMPTOOLPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_STAMPTOOLPANEL_POSITION wxDefaultPosition


/**
 * @brief StampToolPanel is the main window class for the application,
 * It contains wxNotebook with the the StampDescriptionPanel and AlbumPanel as pages.
 * StampToolPanel inherits from wxPanel.
 */
class StampToolPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( StampToolPanel )
    DECLARE_EVENT_TABLE( )

public:

    enum StampToolPanelGuiDefs
    {
        ID_CATALOGSPLITTERWINDOW = ID_STAMPTOOLPANEL + 1,
        ID_CATALOGPAGE,
        ID_STAMPTREECTRL,
        ID_NOTEBOOK,
        ID_DESCRIPTIONPANELFOREIGN,
        ID_GALLERYSCROLLEDWINDOW,
        ID_TITLETEXTCTRL,
        ID_STAMPTOOL,
        ID_ALBUMSPLITTERWINDOWFOREIGN,
        ID_GENERTELISTFOREIGN,
        ID_IMAGEALLERYPANEL,
        ID_IMAGEALLERYPANEL1,
        ID_DESIGNPAGE,
        ID_DESIGNSPLITTERWINDOW
    };

    StampToolPanel( );

    StampToolPanel( wxWindow* parent,
        wxWindowID id = ID_STAMPTOOLPANEL,
        const wxPoint& pos = SYMBOL_STAMPTOOLPANEL_POSITION,
        const wxSize& size = SYMBOL_STAMPTOOLPANEL_SIZE,
        long style = SYMBOL_STAMPTOOLPANEL_STYLE );

    bool Create( wxWindow* parent,
        wxWindowID id = ID_STAMPTOOLPANEL,
        const wxPoint& pos = SYMBOL_STAMPTOOLPANEL_POSITION,
        const wxSize& size = SYMBOL_STAMPTOOLPANEL_SIZE,
        long style = SYMBOL_STAMPTOOLPANEL_STYLE );

    ~StampToolPanel( );

    void CreateControls( );

    AlbumPanel* GetAlbumPanel( ) {
        return m_albumAlbumPanel;
    };

    AlbumTreePanel* GetAlbumTreePanel( ) {
        return m_albumAlbumPanel->GetAlbumTreePanel( );
    };

    CatalogPanel* GetCatalogPagePanel( ) {
        return m_catalogPanel;
    };

    GenerateList* GetGenerateListPanel( ) {
        return m_generateListPanel;
    };

    wxWindow* GetPage( )
    {
        return m_notebook->GetPage( m_notebook->GetSelection( ) );
    }

    void Init( );

    bool ShouldShowStates( );

    static bool ShowToolTips( );

    void OnNotebookPageChanged( wxNotebookEvent& event );

    void OnPDF( wxString filename );

    void OnTitleTextUpdated( wxCommandEvent& event );

    void SetPage( int page )
    {
        m_notebook->SetSelection( page );
    }

    void UpdateStatus( );

private:

    wxNotebook* m_notebook;
    wxFlexGridSizer* m_sizer;
    CatalogPanel* m_catalogPanel;
    //CatalogPanel* xm_albumPageCatTreePanel;
    wxSplitterWindow* m_stampToolSplitter;
    //wxSplitterWindow* m_albumNotebookPage;
    wxTreeItemId m_draggedItem;
    wxTreeItemId m_currentItem;
    AlbumPanel* m_albumAlbumPanel;
    StampDescriptionPanel* m_stampDescriptionPanel;
    GenerateList* m_generateListPanel;
    ImageGalleryPanel* m_imageGalleryPanel;
    //    WebViewPanel* m_webViewPanel;
};

#endif

