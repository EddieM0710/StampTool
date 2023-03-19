/**
 * @file gui/LabeledTextBox.h
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
 **************************************************/


#ifndef _LABLEDTEXTBOX_H_
#define _LABLEDTEXTBOX_H_

 /*
  * Includes
  */

#include <wx/event.h> 

#include "gui/GuiDefs.h"

  /*
   * Forward declarations
   */
namespace Catalog { class Entry; };

/*
 * Control identifiers
 */
#define SYMBOL_LABELEDTEXTBOX_STYLE wxTAB_TRAVERSAL
#define SYMBOL_LABELEDTEXTBOX_TITLE _( "LabledTextBox" )
#define SYMBOL_LABELEDTEXTBOX_IDNAME ID_LABELEDTEXTBOX
#define SYMBOL_LABELEDTEXTBOX_SIZE wxDefaultSize
#define SYMBOL_LABELEDTEXTBOX_POSITION wxDefaultPosition

 /*
  * LabeledTextBox class declaration
  */
typedef void ( MyFunct )( wxCommandEvent& event );



class LabeledTextBox: public wxPanel
{
    DECLARE_DYNAMIC_CLASS( LabeledTextBox )
        DECLARE_EVENT_TABLE( )

public:
    enum LabeledTextBoxGuiDefs
    {
        ID_LABELEDTEXTBOX_TEXTCTRL = ID_LABELEDTEXTBOX + 1
    };

    
    /**
     * @brief Default Constructor a new LabeledTextBox object
     * @details Must be used in conjunction with Create.
     *
     **************************************************/
    LabeledTextBox( );

    /**typedefze	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     **************************************************/
    LabeledTextBox( wxWindow* parent,
        wxWindowID id = SYMBOL_LABELEDTEXTBOX_IDNAME,
        const wxPoint& pos = SYMBOL_LABELEDTEXTBOX_POSITION,
        const wxSize& size = SYMBOL_LABELEDTEXTBOX_SIZE,
        long style = SYMBOL_LABELEDTEXTBOX_STYLE );

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
     **************************************************/
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_LABELEDTEXTBOX_IDNAME,
        const wxPoint& pos = SYMBOL_LABELEDTEXTBOX_POSITION,
        const wxSize& size = SYMBOL_LABELEDTEXTBOX_SIZE,
        long style = SYMBOL_LABELEDTEXTBOX_STYLE );

    
    /**
     * @brief Destroy the Labeled Text Box object
     *
     **************************************************/
    ~LabeledTextBox( );

    /**
     * @brief   Initialises member variables
     *
     **************************************************/
    void Init( );

    /**
     * @brief Creates the controls and sizers
     *
     **************************************************/
    void CreateControls( );

    // LabeledTextBox event handler declarations


   //   ID_LABELEDTEXTBOX_TEXTCTRL
    void OnTextctrlTextUpdated( wxCommandEvent& event );

  

    /**
     * @brief 
     *
     * @return bool
     **************************************************/
    static bool ShowToolTips( );

    /**
     * @brief Set the Stamp object
     *
     * @param stamp
     * @param type
     **************************************************/
    void Setup( wxString label, wxString value );

    /**
     * @brief Get the value in the ctrl
     *
     * @return wxString
     **************************************************/
    wxString GetValue( );

    /**
     * @brief Set the Width object
     *
     * @param width
     **************************************************/
    void SetValue( wxString value )
    {
        m_value->SetValue( value );
        m_value->SetModified( true );
    };
    void ChangeValue( wxString value )
    {
        m_value->ChangeValue( value );
        m_value->SetModified( false );
    };
    bool IsModified( ) { return m_value->IsModified( ); };
    void SetModified( bool state = true ) { m_value->SetModified( state ); };
    inline void SetLabel( wxString label )
    {
        m_label->SetLabel( label );
    };

    void SetEditable( bool value );


private:

    wxStaticText* m_label; ///< 
    wxWindow* m_parent; ///< 
    wxWindowID m_id; ///< 
    wxTextCtrl* m_value; ///< 
    //  Catalog::DataTypes m_type; ///< 
};

#endif
// _LABLEDTEXTBOX_H_
