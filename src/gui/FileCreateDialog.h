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
 ///////////////////////////////////////

#ifndef _FILECREATEDIALOG_H_
#define _FILECREATEDIALOG_H_

#include "gui/GuiDefs.h"

#define SYMBOL_FILECREATEDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_FILECREATEDIALOG_TITLE _( "Select file and directory" )
#define SYMBOL_FILECREATEDIALOG_IDNAME ID_FILECREATEDIALOG
#define SYMBOL_FILECREATEDIALOG_SIZE wxSize( 600, 300 )
#define SYMBOL_FILECREATEDIALOG_POSITION wxDefaultPosition

class FileCreateDialog : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( FileCreateDialog )
        DECLARE_EVENT_TABLE( )

public:

    ///  @brief Construct a new File Create Dialog object
    ///  
    FileCreateDialog( );

    ///  @brief Construct a new File Create Dialog object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param caption 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    FileCreateDialog( wxWindow* parent, wxWindowID id = SYMBOL_FILECREATEDIALOG_IDNAME, const wxString& caption = SYMBOL_FILECREATEDIALOG_TITLE, const wxPoint& pos = SYMBOL_FILECREATEDIALOG_POSITION, const wxSize& size = SYMBOL_FILECREATEDIALOG_SIZE, long style = SYMBOL_FILECREATEDIALOG_STYLE );

    ///  @brief Destroy the File Create Dialog object
    ///  
    ~FileCreateDialog( );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param caption 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    ///  @return true 
    ///  @return false 
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_FILECREATEDIALOG_IDNAME, const wxString& caption = SYMBOL_FILECREATEDIALOG_TITLE, const wxPoint& pos = SYMBOL_FILECREATEDIALOG_POSITION, const wxSize& size = SYMBOL_FILECREATEDIALOG_SIZE, long style = SYMBOL_FILECREATEDIALOG_STYLE );

    ///  @brief Create a Controls object
    ///  
    void CreateControls( );

    ///  @brief Get the Path object
    ///  
    ///  @return wxString 
    wxString GetPath( );

    ///  @brief Get the File object
    ///  
    ///  @return wxString 
    wxString GetFile( );

    ///  @brief Get the Dir object
    ///  
    ///  @return wxString 
    wxString GetDir( );

    ///  @brief 
    ///  
    void Init( );

    ///  @brief 
    ///  
    ///  @param event 
    void OnCancelClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnOKClick( wxCommandEvent& event );

    ///  @brief Set the Default Directory object
    ///  
    ///  @param str 
    void SetDefaultDirectory( wxString str ) { m_defaultDirectory = str; m_fileCtrl->SetDirectory( str ); };

    ///  @brief Set the Default Filename object
    ///  
    ///  @param str 
    void SetDefaultFilename( wxString str ) { m_defaultFilename = str; m_fileCtrl->SetFilename( str ); };

    ///  @brief Set the Wild Card object
    ///  
    ///  @param str 
    void SetWildCard( wxString str ) { m_wildCard = str; m_fileCtrl->SetWildcard( str ); };

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    static bool ShowToolTips( );

private:
    wxString m_path;
    wxString m_file;
    wxString m_dir;
    wxString m_defaultDirectory;
    wxString m_defaultFilename;
    wxString m_wildCard;
    wxFileCtrl* m_fileCtrl;
};

#endif
// _FILECREATEDIALOG_H_
