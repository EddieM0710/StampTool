/*
 * @file         FileCreateDialog.h
 * @brief      
 * @author       Eddie Monroe
 * Modified by: 
 * @date     Fri 20 Jan 2023 19:33:48 CST
 *     
 * @copyright Copyright ( c ) 2024  
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
 */    
/////////////////////////////////////////////////////////////////////////////

#ifndef _FILECREATEDIALOG_H_
#define _FILECREATEDIALOG_H_


/*
 * Includes
 */

#include "gui/GuiDefs.h"

//  includes
//  includes

/*
 * Forward declarations
 */

//  forward declarations
//  forward declarations

/*
 * Control identifiers
 */

//  control identifiers

#define SYMBOL_FILECREATEDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_FILECREATEDIALOG_TITLE _( "Select file and directory" )
#define SYMBOL_FILECREATEDIALOG_IDNAME ID_FILECREATEDIALOG
#define SYMBOL_FILECREATEDIALOG_SIZE wxSize( 600, 300 )
#define SYMBOL_FILECREATEDIALOG_POSITION wxDefaultPosition
//  control identifiers


/*
 * FileCreateDialog class declaration
 */

class FileCreateDialog: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( FileCreateDialog )
    DECLARE_EVENT_TABLE( )

public:

    // enum FileCreateDialogGuiDefs
    // {
    // };

    
    FileCreateDialog( );
    FileCreateDialog( wxWindow* parent, wxWindowID id = SYMBOL_FILECREATEDIALOG_IDNAME, const wxString& caption = SYMBOL_FILECREATEDIALOG_TITLE, const wxPoint& pos = SYMBOL_FILECREATEDIALOG_POSITION, const wxSize& size = SYMBOL_FILECREATEDIALOG_SIZE, long style = SYMBOL_FILECREATEDIALOG_STYLE );

    
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_FILECREATEDIALOG_IDNAME, const wxString& caption = SYMBOL_FILECREATEDIALOG_TITLE, const wxPoint& pos = SYMBOL_FILECREATEDIALOG_POSITION, const wxSize& size = SYMBOL_FILECREATEDIALOG_SIZE, long style = SYMBOL_FILECREATEDIALOG_STYLE );

    
    ~FileCreateDialog( );

    
    void Init( );

    
    void CreateControls( );

//  FileCreateDialog event handler declarations

    ///   wxID_CANCEL
    void OnCancelClick( wxCommandEvent& event );
    void OnOKClick( wxCommandEvent& event );


    
    static bool ShowToolTips( );
    wxString GetPath( );
    wxString GetFile( );
    wxString GetDir( );
    void SetDefaultDirectory( wxString str ) { m_defaultDirectory = str; m_fileCtrl->SetDirectory( str ); };
    void SetDefaultFilename( wxString str ) { m_defaultFilename = str; m_fileCtrl->SetFilename( str ); }; 
    void SetWildCard( wxString str ) { m_wildCard = str; m_fileCtrl->SetWildcard( str ); };

//  FileCreateDialog member variables
//  FileCreateDialog member variables
    wxString m_path ;
    wxString m_file ;
    wxString m_dir ;
    wxString m_defaultDirectory; 
    wxString m_defaultFilename; 
    wxString m_wildCard;
    wxFileCtrl* m_fileCtrl;
};

#endif
    // _FILECREATEDIALOG_H_
