/**
 * @file IdentificationPanel.h
 * @author Eddie Monroe ( )
 * @brief IdentificationPanel displays stamp data relative to the stamp identification
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
#ifndef _IDENTIFICATIONPANEL_H_
#define _IDENTIFICATIONPANEL_H_

#include "Defs.h"
#include "gui/GuiDefs.h"
#include "gui/HelperPanel.h"
#include "catalog/CatalogDefs.h"

 //class wxTextCtrl;
namespace Catalog {
    class Entry;
}

#define SYMBOL_IDENTIFICATIONPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_IDENTIFICATIONPANEL_TITLE _( "IdentificationPanel" )
#define SYMBOL_IDENTIFICATIONPANEL_IDNAME ID_IDENTIFICATIONPANEL
#define SYMBOL_IDENTIFICATIONPANEL_SIZE wxDefaultSize
#define SYMBOL_IDENTIFICATIONPANEL_POSITION wxDefaultPosition

/**
  * @brief IdentificationPanel displays stamp data relative to the stamp identification
  */
class IdentificationPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( IdentificationPanel )
    DECLARE_EVENT_TABLE( )

public:
    enum IdentificationPanelGuiDefs
    {
        ID_IDLABELEDTEXTBOX = ID_IDENTIFICATIONPANEL + 1,
        ID_STATUSCHOICE,
        ID_NAMELABELEDTEXTBOX,
        ID_EMISSIONCHOICE,
        ID_FORMATCHOICE,
        ID_ISSUEDTEXTBOX,
        ID_SERIESTEXTBOX,
        ID_THEMETEXTBOX,
        ID_THEMETEXTBOXUP,
        ID_COUNTRYTEXTBOX,
        ID_PEFORATIONTEXTBOX,
        ID_PRINTINGTEXTBOX,
        ID_WIDTHLABELEDTEXTBOX,
        ID_HEIGHTLABELEDTEXTBOX,
        ID_LINKTEXTBOX,
        ID_COLNECTBUTTON,
        ID_SITETBUTTON,
        ID_EBAYBUTTON,
        ID_NPMBUTTON,
        ID_CATCODETEXTBOX,
        ID_STAMPMOUNTTEXTBOX,
        ID_IMAGENAMETEXTBOX
    };




    IdentificationPanel( );


    IdentificationPanel( wxWindow* parent,
        wxWindowID id = SYMBOL_IDENTIFICATIONPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_IDENTIFICATIONPANEL_POSITION,
        const wxSize& size = SYMBOL_IDENTIFICATIONPANEL_SIZE,
        long style = SYMBOL_IDENTIFICATIONPANEL_STYLE );


    void Clear( );

    bool Create( wxWindow* parent,
        wxWindowID id = SYMBOL_IDENTIFICATIONPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_IDENTIFICATIONPANEL_POSITION,
        const wxSize& size = SYMBOL_IDENTIFICATIONPANEL_SIZE,
        long style = SYMBOL_IDENTIFICATIONPANEL_STYLE );

    ~IdentificationPanel( );

    void Init( );

    void CreateControls( );

    void OnCatalogCodesChanged( wxCommandEvent& event );

    void OnColnectButtonClick( wxCommandEvent& event );

    void OnComboboxSelected( wxCommandEvent& event );

    void OnComboboxUpdated( wxCommandEvent& event );

    void OnCountryUpdated( wxCommandEvent& event );

    void OneBayButtonClick( wxCommandEvent& event );


    void OnEmissionchoiceSelected( wxCommandEvent& event );

    void OnFormatchoiceSelected( wxCommandEvent& event );

    void OnHeightUpdated( wxCommandEvent& event );

    void OnIDUpdated( wxCommandEvent& event );

    void OnImageUpdated( wxCommandEvent& event );

    void OnIssuedUpdated( wxCommandEvent& event );

    void OnLinkUpdated( wxCommandEvent& event );

    void OnNameUpdated( wxCommandEvent& event );

    void OnNPMButtonClick( wxCommandEvent& event );

    void OnPerforationUpdated( wxCommandEvent& event );

    void OnPrintingUpdated( wxCommandEvent& event );

    void OnSeriesUpdated( wxCommandEvent& event );

    void OnThemeUpdated( wxCommandEvent& event );

    void OnWidthUpdated( wxCommandEvent& event );

    static bool ShowToolTips( );

    void SetChoice( wxChoice* ctrl, wxString str );

    void SetChoice( wxChoice* ctrl, int ndx );

    void SetDataEditable( bool val = true );

    void UpdatePanel( );

    void UpdateStampValue( Catalog::DataTypes dt, wxTextCtrl* textBox );

    void UpdateStatus( );



private:

    wxTextCtrl* m_name;      ///< Stamp Name display
    wxChoice* m_emission;        ///<  Stamp Emission wxChoice
    wxChoice* m_format;          ///<  Stamp Format wxChoice
    wxTextCtrl* m_issueDate; ///< Stamp Issue date display
    wxTextCtrl* m_series;    ///< Stamp Series display
    wxTextCtrl* m_themes;    ///< Stamp Theme display
    wxTextCtrl* m_country;   ///< Stamp Country display
    wxTextCtrl* m_perforation;   ///< Stamp perforation display
    wxTextCtrl* m_printing;   ///< Stamp printng display
    wxTextCtrl* m_width;   ///< Stamp width display
    wxTextCtrl* m_height;   ///< Stamp height display
    wxTextCtrl* m_catCode;
    wxComboBox* mountComboBox;

    wxTextCtrl* m_link;
    wxTextCtrl* m_imageName;
};

#endif
