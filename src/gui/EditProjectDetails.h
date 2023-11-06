/*
 * @file gui/EditProjectDetails.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-12
 *
 * @copyright Copyright ( c ) 2022
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

#ifndef _EditProjectDetails_H_
#define _EditProjectDetails_H_


 /*
  * Includes
  */




#include "gui/GuiDefs.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>
  /*
   * Forward declarations
   */



class SortOrderPanel;
class DefinePeriodsPanel;
/*
 * Control identifiers
 */


#define SYMBOL_EDITPROJECTDETAILS_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_EDITPROJECTDETAILS_TITLE _( "EditProjectDetails" )
#define SYMBOL_EDITPROJECTDETAILS_IDNAME ID_EDITPROJECTDETAILS
#define SYMBOL_EDITPROJECTDETAILS_SIZE wxSize( 600, 300 )
#define SYMBOL_EDITPROJECTDETAILS_POSITION wxDefaultPosition



 /*
  * EditProjectDetails class declaration
  */

class EditProjectDetails : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( EditProjectDetails )
    DECLARE_EVENT_TABLE( )

public:
    enum EditProjectDetailsGuiDefs
    {
        ID_IMAGEDIRECTORTEXTBOX = ID_EDITPROJECTDETAILS + 1,
        ID_COUNTRYTEXTBOX,
        ID_CATALOGTEXTBOX,
        ID_TITLEDEFAULTFONTBUTTON,
        ID_TEXTDEFAULTFONTBUTTON,
        ID_NAMEDEFAULTFONTBUTTON,
        ID_LastID
    };


    EditProjectDetails( );
    EditProjectDetails( wxWindow* parent, wxWindowID id = SYMBOL_EDITPROJECTDETAILS_IDNAME, const wxString& caption = SYMBOL_EDITPROJECTDETAILS_TITLE, const wxPoint& pos = SYMBOL_EDITPROJECTDETAILS_POSITION, const wxSize& size = SYMBOL_EDITPROJECTDETAILS_SIZE, long style = SYMBOL_EDITPROJECTDETAILS_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_EDITPROJECTDETAILS_IDNAME, const wxString& caption = SYMBOL_EDITPROJECTDETAILS_TITLE, const wxPoint& pos = SYMBOL_EDITPROJECTDETAILS_POSITION, const wxSize& size = SYMBOL_EDITPROJECTDETAILS_SIZE, long style = SYMBOL_EDITPROJECTDETAILS_STYLE );

    ~EditProjectDetails( );

    void Init( );

    void CreateControls( );

    void OnOkClick( wxCommandEvent& event );

    void OnSelectDirectory( wxCommandEvent& event );

    void UpdateProject( );

private:

    wxTextCtrl* m_imageDirectory;
    wxTextCtrl* m_country;
    wxTextCtrl* m_catalog;

};

#endif
// _EditProjectDetails_H_
