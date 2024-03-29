/**
 * @file StampDescriptionPanel.h
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


#ifndef _DISCRIPTIONPANEL_H_
#define _DISCRIPTIONPANEL_H_


#include "wx/notebook.h"
#include "wx/splitter.h"
#include <wx/slider.h>

#include "Defs.h"
#include "catalog/Entry.h"
#include "gui/GuiDefs.h"

 //class CatalogCodePanel;
class CharacteristicsPanel;
class IdentificationPanel;
class ImagePanel;
class InventoryPanel;
class MiscellaneousDataPanel;

#define SYMBOL_DESCRIPTIONPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_DESCRIPTIONPANEL_TITLE _( "DescriptionPanel" )
#define SYMBOL_DESCRIPTIONPANEL_IDNAME ID_STAMPDESCRIPTIONPANEL
#define SYMBOL_DESCRIPTIONPANEL_SIZE wxDefaultSize
#define SYMBOL_DESCRIPTIONPANEL_POSITION wxDefaultPosition



/**
 * @brief StampDescriptionPanel class declaration.
 * @details This panel contains ImagePanel to display the stamp, An
 * IdentificationPanel to display the ID info and a wxNotebook that manages the
 * InventoryPanel, the CharacteristicsPanel, the MiscellaneousDataPanel and pages for
 * displaying discription and background info. This class inherits from wxPanel.
 *
 */
class StampDescriptionPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( StampDescriptionPanel )
    DECLARE_EVENT_TABLE( )

public:

    enum StampDescriptionPanelGuiDefs {
        ID_HORIZONTALLITTERWINDOW = ID_STAMPDESCRIPTIONPANEL + 1,
        ID_DESCRIPTIONSPLITTERWINDOW,
        ID_IDENTIFICATIONPANELFORIEGN,
        ID_HORIZONTALPLITTERWINDOW,
        ID_ZOOMSLIDER,
        ID_STAMPIMAGEPANEL,
        ID_DESCRIPTIONLNOTEBOOK,
        ID_INVENTORYFOREIGN,
        ID_CATALOGCODEFOREIGN,
        ID_CHARACTERISTICSWINDOW,
        ID_MISCELLANEOUSDATAFORIEGN,
        ID_DESCRIPTIONSCROLLEDWINDOW,
        ID_DESCRIPTIONTEXTCTRL,
        ID_BACKGROUNDPANEL1,
        ID_BKGNDSCROLLEDWINDOW,
        ID_BKGNDTEXTCTRL,
        ID_NOTEBOOPANEL
    };




    /**
     * @brief Default Constructor for a new Description Panel object
     *
     */
    StampDescriptionPanel( void );

    StampDescriptionPanel( wxWindow* parent,
        wxWindowID id = SYMBOL_DESCRIPTIONPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_DESCRIPTIONPANEL_POSITION,
        const wxSize& size = SYMBOL_DESCRIPTIONPANEL_SIZE,
        long style = SYMBOL_DESCRIPTIONPANEL_STYLE );


    bool Create( wxWindow* parent,
        wxWindowID id = SYMBOL_DESCRIPTIONPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_DESCRIPTIONPANEL_POSITION,
        const wxSize& size = SYMBOL_DESCRIPTIONPANEL_SIZE,
        long style = SYMBOL_DESCRIPTIONPANEL_STYLE );


    ~StampDescriptionPanel( void );

    void Clear( );

    void Init( void );

    void CreateControls( void );

    InventoryPanel* GetInventoryPanel( ) {
        return m_inventoryPanel;
    };
    void OnZoomsliderUpdated( wxCommandEvent& event );

    void OnDescriptionTextctrlTextUpdated( wxCommandEvent& event );

    void OnBkGndTextUpdated( wxCommandEvent& event );

    void OnBkgndtextctrlMaxLen( wxCommandEvent& event );

    void OnLeaveWindow( wxMouseEvent& event );

    void OnNotebooksplitterwindowSashPosChanged( wxSplitterEvent& event );

    void OnSplitterwindowSashPosChanged( wxSplitterEvent& event );

    void SetDataEditable( bool val );

    static bool ShowToolTips( void );

    void UpdatePanel( );

    void UpdateStatus( void );

private:
    IdentificationPanel* m_identificationPanel; ///< Pointer to IdentificationPanel
    wxSlider* m_zoomSlider; ///< Pointer to image soom slider
    ImagePanel* m_stampImage; ///< Pointer to stamp image
    InventoryPanel* m_inventoryPanel; ///< Pointer to InventoryPanel

};

#endif
