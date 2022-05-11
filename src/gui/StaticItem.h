/////////////////////////////////////////////////////////////////////////////
// Name:        gui/StaticItem.h
// Purpose:     
// Author:      Eddie Monroe
// Modified by: 
// Created:     Fri 21 Jan 2022 11:02:57 CST
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), Fri 21 Jan 2022 11:02:57 CST

#ifndef _STATICITEM_H_
#define _STATICITEM_H_


/*!
 * Includes
 */

////@begin includes
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_STATICITEM 10000
#define wxID_TITLESTATIC 10030
#define wxID_COLONSTATIC 10031
#define wxID_VALSTATIC 10029
#define SYMBOL_STATICITEM_STYLE wxTAB_TRAVERSAL
#define SYMBOL_STATICITEM_TITLE _("StaticItem")
#define SYMBOL_STATICITEM_IDNAME ID_STATICITEM
#define SYMBOL_STATICITEM_SIZE wxSize(400, 300)
#define SYMBOL_STATICITEM_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * StaticItem class declaration
 */

class StaticItem: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( StaticItem )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    StaticItem();
    StaticItem( wxWindow* parent, wxWindowID id = SYMBOL_STATICITEM_IDNAME, const wxPoint& pos = SYMBOL_STATICITEM_POSITION, const wxSize& size = SYMBOL_STATICITEM_SIZE, long style = SYMBOL_STATICITEM_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_STATICITEM_IDNAME, const wxPoint& pos = SYMBOL_STATICITEM_POSITION, const wxSize& size = SYMBOL_STATICITEM_SIZE, long style = SYMBOL_STATICITEM_STYLE );

    /// Destructor
    ~StaticItem();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin StaticItem event handler declarations

    /// wxEVT_CONTEXT_MENU event handler for ID_STATICITEM
    void OnContextMenu( wxContextMenuEvent& event );

////@end StaticItem event handler declarations

////@begin StaticItem member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end StaticItem member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin StaticItem member variables
    wxStaticText* m_title;
    wxStaticText* m_data;
////@end StaticItem member variables
};

#endif
    // _STATICITEM_H_
