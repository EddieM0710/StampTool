/////////////////////////////////////////////////////////////////////////////
// Name:        CatalogUpdater.h
// Purpose:     
// Author:      Eddie Monroe
// Modified by: 
// Created:     Sat 17 Jun 2023 20:33:14 CDT
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), Sat 17 Jun 2023 20:33:14 CDT

#ifndef _CATALOGUPDATER_H_
#define _CATALOGUPDATER_H_

#include "wx/splitter.h"
#include "wx/listctrl.h"


#define ID_CATALOGUPDATER 10000
#define ID_PANEL 10004
#define ID_SPLITTERWINDOW 10001
#define ID_LISTBOX 10002
#define ID_LISTCTRL 10003
#define SYMBOL_CATALOGUPDATER_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CATALOGUPDATER_TITLE _("CatalogUpdater")
#define SYMBOL_CATALOGUPDATER_IDNAME ID_CATALOGUPDATER
#define SYMBOL_CATALOGUPDATER_SIZE wxSize(800, 600)
#define SYMBOL_CATALOGUPDATER_POSITION wxDefaultPosition

class CatalogUpdater : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CatalogUpdater )
    DECLARE_EVENT_TABLE( )

public:
    /// Constructors
    CatalogUpdater( );
    CatalogUpdater( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGUPDATER_IDNAME, const wxString& caption = SYMBOL_CATALOGUPDATER_TITLE, const wxPoint& pos = SYMBOL_CATALOGUPDATER_POSITION, const wxSize& size = SYMBOL_CATALOGUPDATER_SIZE, long style = SYMBOL_CATALOGUPDATER_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGUPDATER_IDNAME, const wxString& caption = SYMBOL_CATALOGUPDATER_TITLE, const wxPoint& pos = SYMBOL_CATALOGUPDATER_POSITION, const wxSize& size = SYMBOL_CATALOGUPDATER_SIZE, long style = SYMBOL_CATALOGUPDATER_STYLE );

    /// Destructor
    ~CatalogUpdater( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );


    void OnListboxSelected( wxCommandEvent& event );

    void OnListctrlSelected( wxListEvent& event );



    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    wxIcon GetIconResource( const wxString& name );

    /// Should we show tooltips?
    static bool ShowToolTips( );

};

#endif

