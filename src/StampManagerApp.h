/////////////////////////////////////////////////////////////////////////////
// Name:        StampManagerApp.h
// Purpose:     
// Author:      Eddie Monroe
// Modified by: 
// Created:     Fri 25 Mar 2022 16:20:59 CDT
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _STAMPMANAGERAPP_H_
#define _STAMPMANAGERAPP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
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
////@end control identifiers

/*!
 * StampManagerApp class declaration
 */

class StampManagerApp: public wxApp
{    
    DECLARE_CLASS( StampManagerApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    StampManagerApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin StampManagerApp event handler declarations
////@end StampManagerApp event handler declarations

////@begin StampManagerApp member function declarations
////@end StampManagerApp member function declarations

////@begin StampManagerApp member variables
////@end StampManagerApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(StampManagerApp)
////@end declare app

#endif
    // _STAMPMANAGERAPP_H_
