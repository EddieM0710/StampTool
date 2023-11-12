
#ifndef _Export_H_
#define _Export_H_

#include <wx/dialog.h>

#define ID_EXPORTDIALOG 10000
#define ID_COMBOBOX 10001
#define ID_RADIOBUTTON 10002
#define ID_RADIOBUTTON1 10003
#define SYMBOL_EXPORTDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_EXPORTDIALOG_TITLE _("Remove Volume From Project")
#define SYMBOL_EXPORTDIALOG_IDNAME ID_EXPORTDIALOG
#define SYMBOL_EXPORTDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_EXPORTDIALOG_POSITION wxDefaultPosition

class ExportDialog : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( ExportDialog )
    DECLARE_EVENT_TABLE( )

public:
    ExportDialog( );
    ExportDialog( wxWindow* parent,
        wxString caption,
        wxString dialogInstructionText,
        wxArrayString listComboBoxStrings );

    ExportDialog( wxWindow* parent, wxWindowID id = SYMBOL_EXPORTDIALOG_IDNAME, const wxString& caption = SYMBOL_EXPORTDIALOG_TITLE, const wxPoint& pos = SYMBOL_EXPORTDIALOG_POSITION, const wxSize& size = SYMBOL_EXPORTDIALOG_SIZE, long style = SYMBOL_EXPORTDIALOG_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_EXPORTDIALOG_IDNAME, const wxString& caption = SYMBOL_EXPORTDIALOG_TITLE, const wxPoint& pos = SYMBOL_EXPORTDIALOG_POSITION, const wxSize& size = SYMBOL_EXPORTDIALOG_SIZE, long style = SYMBOL_EXPORTDIALOG_STYLE );

    ~ExportDialog( );

    void Init( );

    void CreateControls( );

    static bool ShowToolTips( );


};

#endif

