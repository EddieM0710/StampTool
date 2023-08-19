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
#include "catalog/CatalogDefs.h"

class LabeledTextBox;
namespace Catalog { class Entry; }

#define SYMBOL_IDENTIFICATIONPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_IDENTIFICATIONPANEL_TITLE _( "IdentificationPanel" )
#define SYMBOL_IDENTIFICATIONPANEL_IDNAME ID_IDENTIFICATIONPANEL
#define SYMBOL_IDENTIFICATIONPANEL_SIZE wxDefaultSize
#define SYMBOL_IDENTIFICATIONPANEL_POSITION wxDefaultPosition

/**
  * @brief IdentificationPanel displays stamp data relative to the stamp identification
  */
class IdentificationPanel : public wxPanel
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
        ID_EDITCHECKBOX,
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



    /**
     * @brief Default Constructor a new IdentificationPanel object
     * @details Must be used in conjunction with Create.
     *
     */
    IdentificationPanel( );

    /**
     * @brief Construct a new IdentificationPanel object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     */
    IdentificationPanel( wxWindow* parent,
        wxWindowID id = SYMBOL_IDENTIFICATIONPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_IDENTIFICATIONPANEL_POSITION,
        const wxSize& size = SYMBOL_IDENTIFICATIONPANEL_SIZE,
        long style = SYMBOL_IDENTIFICATIONPANEL_STYLE );

    /**
     * @brief  Used for two-step panel construction.
     * Use with default constructor.
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @return bool
     *
     */
    bool Create( wxWindow* parent,
        wxWindowID id = SYMBOL_IDENTIFICATIONPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_IDENTIFICATIONPANEL_POSITION,
        const wxSize& size = SYMBOL_IDENTIFICATIONPANEL_SIZE,
        long style = SYMBOL_IDENTIFICATIONPANEL_STYLE );


    ~IdentificationPanel( );

    void Init( );

    /**
     * @brief Creates the controls and sizers
     *
     */
    void CreateControls( );

    /**
    * @brief   ID_STATUSCHOICE
    *
    * @param event   Contains information about command events
    */
    //void OnStatuschoiceSelected( wxCommandEvent& event );

    /**
     * @brief    ID_EMISSIONCHOICE
     *
     * @param event   Contains information about command events
     */
    void OnEmissionchoiceSelected( wxCommandEvent& event );

    /**
     * @brief   ID_FORMATCHOICE
     *
     * @param event   Contains information about command events
     */
    void OnFormatchoiceSelected( wxCommandEvent& event );

    void OnTextctrlTextUpdated( wxCommandEvent& event );
    void OnEditCheckBox( wxCommandEvent& event );
    void SetDataEditable( bool val = true );
    void OnColnectButtonClick( wxCommandEvent& event );;

    void OneBayButtonClick( wxCommandEvent& event );

    void OnNPMButtonClick( wxCommandEvent& event );
    void OnComboboxSelected( wxCommandEvent& event );
    void OnComboboxUpdated( wxCommandEvent& event );

    /**
     * @brief ShowToolTips
     *
     * @return bool
     */
    static bool ShowToolTips( );

    /**
     * @brief Set the Choice object
     *
     * @param ctrl  pointer to choice control to set
     * @param str   value to set the choice to.
     */
    void SetChoice( wxChoice* ctrl, wxString str );

    /**
     * @brief Set the Choice object
     *
     * @param ctrl  pointer to choice control to set
     * @param ndx  selection index of the choice
     */
    void SetChoice( wxChoice* ctrl, int ndx );

    /**
     * @brief Set the Stamp object
     *
     * @param stamp
     */
    void UpdatePanel( );//Catalog::Entry* stamp );
    void UpdateStampValue( Catalog::DataTypes dt, LabeledTextBox* textBox );

    /**
     * @brief
     *
     */
    void UpdateStatus( );





private:
    wxCheckBox* m_editCheckbox;
    //    LabeledTextBox* m_ID;        ///< ID display
        //    wxChoice* m_status;          ///< Stamp Status wxChoice
    LabeledTextBox* m_name;      ///< Stamp Name display
    wxChoice* m_emission;        ///<  Stamp Emission wxChoice
    wxChoice* m_format;          ///<  Stamp Format wxChoice
    LabeledTextBox* m_issueDate; ///< Stamp Issue date display
    LabeledTextBox* m_series;    ///< Stamp Series display
    LabeledTextBox* m_themes;    ///< Stamp Theme display
    LabeledTextBox* m_country;   ///< Stamp Country display
    LabeledTextBox* m_perforation;   ///< Stamp perforation display
    LabeledTextBox* m_printing;   ///< Stamp printng display
    LabeledTextBox* m_width;   ///< Stamp width display
    LabeledTextBox* m_height;   ///< Stamp height display
    wxTextCtrl* m_catCode;
    //LabeledTextBox* m_stampMount;
    wxComboBox* mountComboBox;

    LabeledTextBox* m_link;
    // LabeledTextBox* m_catCodes;
    LabeledTextBox* m_imageName;
};

#endif
