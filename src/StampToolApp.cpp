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
 */

 /**
  *
  * @todo Complete Documentation
  *
  * @todo integrate GIT
  *
  *
  */



#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include <iostream>
#include "Defs.h"
#include "gui/AppData.h"
#include "StampToolApp.h"
#include "gui/StampToolFrame.h"

#include <wx/log.h>


IMPLEMENT_APP( StampToolApp )

IMPLEMENT_CLASS( StampToolApp, wxApp )


BEGIN_EVENT_TABLE( StampToolApp, wxApp )

END_EVENT_TABLE( )



StampToolApp::StampToolApp( )
{
    Init( );
}


void StampToolApp::Init( )
{

}


bool StampToolApp::OnInit( )
{

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

    m_AppData = new AppData( );
    m_AppData->InitAppData( );

    m_frame = new StampToolFrame( NULL );
    //  m_frame->SetupRecentMenu( );    
    m_frame->InitLoad( );

    m_frame->Show( true );


    return true;
}

/*
 * Cleanup for StampToolApp
 */

int StampToolApp::OnExit( )
{

    return wxApp::OnExit( );

}
