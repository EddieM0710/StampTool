/////////////////////////////////////////////////////////////////////////////
// Name:        GenerateList.cpp
// Purpose:     
// Author:      Eddie Monroe
// Modified by: 
// Created:     Thu 08 Dec 2022 20:20:21 CST
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), Thu 08 Dec 2022 20:20:21 CST

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

#include "GenerateList.h"
#include "GenerateListSettings.h"
#include "catalog/CatalogDefs.h"
#include "catalog/CatalogData.h"
#include "catalog/Entry.h"
#include "Defs.h"
#include "utils/XMLUtilities.h"

////@begin XPM images
////@end XPM images


/*
 * GenerateList type definition
 */

IMPLEMENT_DYNAMIC_CLASS( GenerateList, wxPanel )


/*
 * GenerateList event table definition
 */

BEGIN_EVENT_TABLE( GenerateList, wxPanel )

////@begin GenerateList event table entries
    EVT_BUTTON( ID_SETLISTPREFSBUTTON, GenerateList::OnSetListPrefsButtonClick )
    EVT_BUTTON( ID_WRITEBUTTON, GenerateList::OnWriteButtonClick )
    EVT_TEXT( ID_FILENAMETEXTCTRL, GenerateList::OnFileNameTextUpdated )
////@end GenerateList event table entries

END_EVENT_TABLE()


/*
 * GenerateList constructors
 */

GenerateList::GenerateList()
{
    Init();
}

GenerateList::GenerateList( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * GenerateList creator
 */

bool GenerateList::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
////@begin GenerateList creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end GenerateList creation
    return true;
}


/*
 * GenerateList destructor
 */

GenerateList::~GenerateList()
{
////@begin GenerateList destruction
////@end GenerateList destruction
}


/*
 * Member initialisation
 */

void GenerateList::Init()
{
////@begin GenerateList member initialisation
    m_gridCtrl = NULL;
    m_writeButton = NULL;
    m_filename = NULL;
////@end GenerateList member initialisation
    m_checkedStatusItems = 0;    
    m_checkedFormatItems = 0;
    m_checkedEmissionItems = 0;
    m_fromYear = "";
    m_toYear = "";
}


/*
 * Control creation for GenerateList
 */

void GenerateList::CreateControls()
{    
////@begin GenerateList content construction
    // Generated by DialogBlocks, Fri 09 Dec 2022 16:37:56 CST (unregistered)

    GenerateList* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton1 = new wxButton( itemPanel1, ID_SETLISTPREFSBUTTON, _("Set List Preferences"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(itemButton1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_gridCtrl = new wxGrid( itemPanel1, ID_GRIDCTRL, wxDefaultPosition, wxSize(200, 150), wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL );
    m_gridCtrl->SetDefaultColSize(100);
    m_gridCtrl->SetDefaultRowSize(25);
    m_gridCtrl->SetColLabelSize(25);
    m_gridCtrl->SetRowLabelSize(50);
    m_gridCtrl->CreateGrid(0, 6, wxGrid::wxGridSelectCells);
    itemBoxSizer2->Add(m_gridCtrl, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer8, 0, wxGROW|wxALL, 5);

    m_writeButton = new wxButton( itemPanel1, ID_WRITEBUTTON, _("Write"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(m_writeButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText10 = new wxStaticText( itemPanel1, wxID_STATIC, _("file name"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_filename = new wxTextCtrl( itemPanel1, ID_FILENAMETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(m_filename, 1, wxGROW|wxALL, 5);

////@end GenerateList content construction
        m_gridCtrl->SetColLabelValue( 0, Catalog::DT_DataNames[ Catalog::DT_ID_Nbr ] );
        m_gridCtrl->SetColLabelValue( 1, Catalog::DT_DataNames[ Catalog::DT_InventoryStatus ] );
        m_gridCtrl->SetColLabelValue( 2, Catalog::DT_DataNames[ Catalog::DT_Name ] );
        m_gridCtrl->SetColLabelValue( 3, Catalog::DT_DataNames[ Catalog::DT_Issued_on ] );        
        m_gridCtrl->SetColLabelValue( 4, Catalog::DT_DataNames[ Catalog::DT_Emission ] );        
        m_gridCtrl->SetColLabelValue( 5, Catalog::DT_DataNames[ Catalog::DT_Format ] );
}


/*
 * Should we show tooltips?
 */

bool GenerateList::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap GenerateList::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin GenerateList bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end GenerateList bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon GenerateList::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin GenerateList icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end GenerateList icon retrieval
}



/*
 * wxEVT_COMMAND_LIST_ITEM_SELECTED event handler for ID_LISTCTRL
 */


bool GenerateList::CheckStatus(Catalog::Entry* entry)
{
    wxString emission = entry->GetInventoryStatus();
    int i = Catalog::FindStatusType( emission );
    if (i >= 0 )
    {
        int base = 1;
        base = base<<=i;
        return m_checkedStatusItems & base ; 
    }
    return true;
}

bool GenerateList::CheckFormat(Catalog::Entry* entry)
{
    wxString emission = entry->GetFormat();
    int i = Catalog::FindFormatType( emission );
    if (i >= 0 )
    {
        int base = 1;
        base = base<<=i;
        return m_checkedFormatItems & base ; 
    }
    return true;
}

bool GenerateList::CheckEmission(Catalog::Entry* entry)
{
    wxString emission = entry->GetEmission();
    int i = Catalog::FindEmissionType( emission );
    if (i >= 0 )
    {
        int base = 1;
        base = base<<=i;
        return m_checkedEmissionItems & base ; 
    }
    return true;
}
#include "wx/graphics.h"

int GenerateList::GetStringLen(wxFont& font,  wxString text)
{

    wxClientDC dc( this );// = this->GetDC();
    dc.SetMapMode( wxMM_METRIC );
    dc.SetFont( font );

    PrepareDC( dc );

    //SetUserScale( dc );

    text.Trim( );
    text.Trim( false );
    int len = text.length( );
    if ( len > 0 )
    {
        wxSize ext = dc.GetTextExtent( text );
        return ext.GetX();
    }
    return 25;
}
void GenerateList::ShowRow( Catalog::Entry* entry, int row )
{
    wxFont font = m_gridCtrl->GetCellFont(row, 2);

    m_gridCtrl->AppendRows(1);
        m_gridCtrl->SetCellValue( row, 0, entry->GetID());
        m_gridCtrl->SetCellValue( row, 1, entry->GetInventoryStatus());
        m_gridCtrl->SetCellValue( row, 2, entry->GetName());

        int size = GetStringLen( font, entry->GetName());
        int curr = m_gridCtrl->GetColSize(2);
        if ( size > curr )
        {
            m_gridCtrl->SetColSize(2,size);
        }

        m_gridCtrl->SetCellValue( row, 3, entry->GetIssuedDate());        
        m_gridCtrl->SetCellValue( row, 4, entry->GetEmission());  
        size = GetStringLen( font, entry->GetEmission());
        curr = m_gridCtrl->GetColSize(4);
        if ( size > curr )
        {
            m_gridCtrl->SetColSize(4,size);
        }              
        m_gridCtrl->SetCellValue( row, 5, entry->GetFormat());
}
void GenerateList::WriteEntries( wxXmlNode* parent, int& row )
{

        wxXmlNode* child = parent->GetChildren( );
        while ( child )
        {
            if ( !child->GetName().compare( "Entry" ) )
            {
                Catalog::Entry entry(child);
                if( CheckStatus(&entry) && CheckEmission(&entry) && CheckFormat(&entry) )
                {                 
                    ShowRow( &entry, row );
                    row++;
                }
                WriteEntries( child, row ) ;                
            }
            child = child->GetNext( );            
        }
}

void GenerateList::UpdateGrid()
{
    m_gridCtrl->ClearGrid();
    int nbrRows = m_gridCtrl->GetNumberRows();
    if ( nbrRows > 0 ) m_gridCtrl->DeleteRows( 0, nbrRows );
    int row = 0;
    Catalog::CatalogData* catalogData = GetCatalogData( );
    if ( catalogData )
    {
        wxXmlDocument* entryDoc = catalogData->GetDoc( );
        //   XMLDump( entryDoc );
        wxXmlNode* root = entryDoc->GetRoot( );

        //wxXmlNode* child = root->GetChildren( );

        if ( root )
        {
        WriteEntries( root, row )  ;       
        }
    }
}
/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_WRITEBUTTON
 */

void GenerateList::OnWriteButtonClick( wxCommandEvent& event )
{
    UpdateGrid();
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_WRITEBUTTON in GenerateList.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_WRITEBUTTON in GenerateList. 
}


/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_FILENAMETEXTCTRL
 */

void GenerateList::OnFileNameTextUpdated( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_TEXT_UPDATED event handler for ID_FILENAMETEXTCTRL in GenerateList.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_TEXT_UPDATED event handler for ID_FILENAMETEXTCTRL in GenerateList. 
}

int MakeBitPatern( wxArrayInt& array )
{
    int nbr = array.Count();
    int val = 0;
    for ( int i = 0; i < nbr; i++ )
    {
        int base = 1;
        base = base<<=array[i];
        val = val | base ;
    }
    return val;
}

void GenerateList::DoListPrefs()
{
    GenerateListSettings* settings = new GenerateListSettings(this, 12349,
        _( "Edit Report Settings" ) );

    settings->SetCheckedStatusItems( m_checkedStatusItems );
    settings->SetCheckedFormatItems( m_checkedFormatItems );
    settings->SetCheckedEmissionItems( m_checkedEmissionItems );
    settings->SetFromYear(m_fromYear );
    settings->SetToYear( m_toYear );

    if ( settings->ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    m_checkedStatusItems = settings->GetCheckedStatusItems(  );
    m_checkedFormatItems = settings->GetCheckedFormatItems(  );
    m_checkedEmissionItems = settings->GetCheckedEmissionItems(  );


    m_fromYear = settings->GetFromYear();
    m_toYear = settings->GetToYear( );
    
    UpdateGrid();

    return;
}
/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SETLISTPREFSBUTTON
 */

void GenerateList::OnSetListPrefsButtonClick( wxCommandEvent& event )
{
    DoListPrefs();

    // if ( GenerateListSettings.IsNameModified( ) )
    // {
    //     node->SetAttrStr( Design::AT_Name, GenerateListSettings.GetName( ) );
    // }

////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SETLISTPREFSBUTTON in GenerateList.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SETLISTPREFSBUTTON in GenerateList. 
}
