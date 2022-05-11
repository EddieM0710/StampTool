/////////////////////////////////////////////////////////////////////////////
// Name:        StampManagerApp.cpp
// Purpose:     
// Author:      Eddie Monroe
// Modified by: 
// Created:     Fri 25 Mar 2022 16:20:59 CDT
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "StampManagerApp.h"

////@begin XPM images

////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( StampManagerApp )
////@end implement app


/*
 * StampManagerApp type definition
 */

IMPLEMENT_CLASS( StampManagerApp, wxApp )


/*
 * StampManagerApp event table definition
 */

BEGIN_EVENT_TABLE( StampManagerApp, wxApp )

////@begin StampManagerApp event table entries
////@end StampManagerApp event table entries

END_EVENT_TABLE()


/*
 * Constructor for StampManagerApp
 */

StampManagerApp::StampManagerApp()
{
    Init();
}


/*
 * Member initialisation
 */

void StampManagerApp::Init()
{
////@begin StampManagerApp member initialisation
////@end StampManagerApp member initialisation
}

/*
 * Initialisation for StampManagerApp
 */

bool StampManagerApp::OnInit()
{    
////@begin StampManagerApp initialisation
    // Remove the comment markers above and below this block
    // to make permanent changes to the code.

#if wxUSE_XPM
    wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
    wxImage::AddHandler(new wxGIFHandler);
#endif
////@end StampManagerApp initialisation

    return true;
}


/*
 * Cleanup for StampManagerApp
 */

int StampManagerApp::OnExit()
{    
////@begin StampManagerApp cleanup
    return wxApp::OnExit();
////@end StampManagerApp cleanup
}

