
#ifndef _RemoveVolume_H_
#define _RemoveVolume_H_

#include <wx/dialog.h>

#define ID_RemoveVolume 10000
#define ID_COMBOBOX 10001
#define ID_RADIOBUTTON 10002
#define ID_RADIOBUTTON1 10003
#define SYMBOL_REMOVEVOLUMEDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_REMOVEVOLUMEDIALOG_TITLE _("Remove Volume From Project")
#define SYMBOL_REMOVEVOLUMEDIALOG_IDNAME ID_RemoveVolume
#define SYMBOL_REMOVEVOLUMEDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_REMOVEVOLUMEDIALOG_POSITION wxDefaultPosition

class RemoveVolumeDialog : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( RemoveVolumeDialog )
        DECLARE_EVENT_TABLE( )

public:
    RemoveVolumeDialog( );
    RemoveVolumeDialog( wxWindow* parent,
        wxString caption,
        wxString dialogInstructionText,
        wxArrayString listComboBoxStrings );

    RemoveVolumeDialog( wxWindow* parent, wxWindowID id = SYMBOL_REMOVEVOLUMEDIALOG_IDNAME, const wxString& caption = SYMBOL_REMOVEVOLUMEDIALOG_TITLE, const wxPoint& pos = SYMBOL_REMOVEVOLUMEDIALOG_POSITION, const wxSize& size = SYMBOL_REMOVEVOLUMEDIALOG_SIZE, long style = SYMBOL_REMOVEVOLUMEDIALOG_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_REMOVEVOLUMEDIALOG_IDNAME, const wxString& caption = SYMBOL_REMOVEVOLUMEDIALOG_TITLE, const wxPoint& pos = SYMBOL_REMOVEVOLUMEDIALOG_POSITION, const wxSize& size = SYMBOL_REMOVEVOLUMEDIALOG_SIZE, long style = SYMBOL_REMOVEVOLUMEDIALOG_STYLE );

    ~RemoveVolumeDialog( );

    void Init( );

    void CreateControls( );

    static bool ShowToolTips( );

    wxString m_dialogInstructionText;
    wxString m_dialogTitle;
    wxArrayString m_listComboBoxStrings;
    wxRadioButton* m_removeRadioButton;
    wxRadioButton* m_deleteRadioButton;
};

#endif

