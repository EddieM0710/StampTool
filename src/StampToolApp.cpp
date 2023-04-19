/**
 * @file StampToolApp.cpp
 * @author Eddie Monroe ( )
 * @brief This is the main instantiation class for the application
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

 /**
  *
  * @todo Complete Documentation
  *
  * @todo integrate GIT
  *
  *
  **************************************************/



#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include <iostream>
#include "Defs.h"
#include "gui/ToolData.h"
#include "StampToolApp.h"

#include <wx/log.h>


  /*
   * Application instance implementation
   */

   // implement app
IMPLEMENT_APP( StampToolApp )
// implement app

/*
 * StampToolApp type definition
 */
    IMPLEMENT_CLASS( StampToolApp, wxApp )
    ;
/*
 * StampToolApp event table definition
 */

BEGIN_EVENT_TABLE( StampToolApp, wxApp )

// StampToolApp event table entries
// StampToolApp event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter
;


/*
 * Constructor for StampToolApp
 */

StampToolApp::StampToolApp( )
{
    Init( );
}

/*
 * Member initialisation
 */

void StampToolApp::Init( )
{
    // StampToolApp member initialisation
    // StampToolApp member initialisation
}

/*
 * Initialisation for StampToolApp
 */

bool StampToolApp::OnInit( )
{
    // StampToolApp initialisation
   // Remove the comment markers above and below this block
   // to make permanent changes to the code.

    wxLog::EnableLogging( true );
    // wxLog* logger = new wxLogStream(&std::cout);
    // wxLog::SetActiveTarget(logger);

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

    m_toolData = new ToolData( );
    m_toolData->InitToolData( );

    m_frame = new StampToolFrame( NULL );
    //  m_frame->SetupRecentMenu( );    
    m_frame->InitLoad( );

    m_frame->Show( true );
    // StampToolApp initialisation

    return true;
}

/*
 * Cleanup for StampToolApp
 */

int StampToolApp::OnExit( )
{
    // StampToolApp cleanup
    return wxApp::OnExit( );
    // StampToolApp cleanup
}
