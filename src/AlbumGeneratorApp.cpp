/**
 * @file AlbumGeneratorApp.cpp
 * @author Eddie Monroe ()
 * @brief This is the main instantiation class for the application
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

/**
 * 
 * @todo Complete Documentation
 * 
 * @todo integrate GIT
 * 
 * 
 **************************************************/


 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Defs.h"
#include "Settings.h"
#include "AlbumGeneratorApp.h"

/*
 * Application instance implementation
 */

 // implement app
IMPLEMENT_APP( AlbumGeneratorApp )
// implement app

/*
 * AlbumGeneratorApp type definition
 */
    IMPLEMENT_CLASS( AlbumGeneratorApp, wxApp )
    ;
/*
 * AlbumGeneratorApp event table definition
 */

BEGIN_EVENT_TABLE( AlbumGeneratorApp, wxApp )

// AlbumGeneratorApp event table entries
// AlbumGeneratorApp event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter
;

/*
 * Constructor for AlbumGeneratorApp
 */

AlbumGeneratorApp::AlbumGeneratorApp( )
{
    Init( );
}

/*
 * Member initialisation
 */

void AlbumGeneratorApp::Init( )
{
    // AlbumGeneratorApp member initialisation
    // AlbumGeneratorApp member initialisation
}

/*
 * Initialisation for AlbumGeneratorApp
 */

bool AlbumGeneratorApp::OnInit( )
{
    // AlbumGeneratorApp initialisation
   // Remove the comment markers above and below this block
   // to make permanent changes to the code.

#if wxUSE_XPM
    wxImage::AddHandler( new wxXPMHandler );
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler( new wxPNGHandler );
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler( new wxJPEGHandler );
#endif
#if wxUSE_GIF
    wxImage::AddHandler( new wxGIFHandler );
#endif

    InitDefs( );

    m_frame = new AlbumGeneratorFrame( NULL );
    m_frame->SetupRecentMenu( );    
    m_frame->InitLoad( );

    m_frame->Show( true );
    // AlbumGeneratorApp initialisation

    return true;
}

/*
 * Cleanup for AlbumGeneratorApp
 */

int AlbumGeneratorApp::OnExit( )
{
    // AlbumGeneratorApp cleanup
    return wxApp::OnExit( );
    // AlbumGeneratorApp cleanup
}
