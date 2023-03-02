/**
 * @file CatalogSectionData.cpp
 * @author Eddie Monroe ( )
 * @brief
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

 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <iostream>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/string.h>
#include "wx/xml/xml.h"
#include <wx/msgdlg.h>

#include "catalog/CatalogSectionData.h"

#include "Defs.h"

#include "catalog/CatalogDefs.h"
#include "catalog/Classification.h"
#include "catalog/Entry.h"

#include "utils/CSV.h"
#include "utils/Settings.h"
#include "utils/Project.h"
#include "utils/XMLUtilities.h"
#include "StampToolApp.h"
#include "gui/SectionDetailsDialog.h"

wxDECLARE_APP( StampToolApp );

namespace Catalog { 

    CatalogSectionData* NewCatalogSectionDataInstance( )
    { 
        return new CatalogSectionData( );
    }

    CatalogSectionData::CatalogSectionData( /* args */ )
    { 
        m_stampDoc = 0;
    }

    //*****

    CatalogSectionData::~CatalogSectionData( )
    { 
        delete m_stampDoc;
    }

    //*****

    bool CatalogSectionData::IsOK( )
    { 
        if ( m_stampDoc )
        { 
            return true;
        }
        return false;
    }

    //*****   

    void CatalogSectionData::SetDirty( bool state )
    { 
        m_dirty = state;
        if ( m_dirty )
        { 
            GetToolData( )->SetDirty( true );
        }
    }
    //*****

    wxXmlDocument* CatalogSectionData::NewDocument( )
    { 
        delete m_stampDoc;
        m_stampDoc = new wxXmlDocument( );
        return m_stampDoc;
    };

    //*****

    wxXmlDocument* CatalogSectionData::ReplaceDocument( wxXmlDocument* doc )
    { 
        delete m_stampDoc;
        m_stampDoc = doc;
        return m_stampDoc;
    };

    //*****

    void CatalogSectionData::Save( )
    { 
        wxString filename = m_sectionFilename;
        if ( wxFileExists( filename ) )
        { 
            wxFileName bakFile( filename );
            bakFile.SetExt( "bak" );
            wxRenameFile( filename, bakFile.GetFullName( ), true );
        }
        m_stampDoc->Save( filename );
        SetDirty( false );
    }

    //*****catalogData

    void CatalogSectionData::NewCatalog( )
    { 
        m_stampDoc = NewDocument( );
        wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, "Catalog" );
        m_stampDoc->SetRoot( root );
    }
    wxString CatalogSectionData::GetCatalogSectionImagePath( )
    { 
        wxString filename = "";
        if ( m_stampDoc && m_stampDoc->IsOk( ) )
        { 
            wxXmlNode* root = m_stampDoc->GetRoot( );
            if ( root )
            { 
                filename = Utils::GetAttrStr( root, "ImagePath" );

                return filename;
            }
        }
        return filename;
    };

    void CatalogSectionData::SetImagePath( wxString str )
    { 
        if ( m_stampDoc && m_stampDoc->IsOk( ) )
        { 
            wxXmlNode* root = m_stampDoc->GetRoot( );
            if ( root )
            { 
                Utils::SetAttrStr( root, "ImagePath", str );
            }
        }
    }
    //*****

    void CatalogSectionData::LoadXML( )
    { 

        bool ok = false;
        if ( m_sectionFilename.length( ) > 0 )
        { 
            if ( !m_stampDoc )
            { 
                m_stampDoc = NewDocument( );
            }

            wxString cwd = wxGetCwd( );
            //ok = m_stampDoc->Load( filename );
            wxFileInputStream stream( m_sectionFilename );
            if ( !stream.IsOk( ) )
            { 
                wxString txt = wxString::Format( "%s Stream Create Failed.\n\n", m_sectionFilename );
                wxMessageDialog* dlg = new wxMessageDialog( 
                    wxGetApp( ).GetFrame( ), txt, 
                    wxT( "Warning! Stream Create Failed.\n" ), 
                    wxOK | wxCANCEL | wxCENTER );
                int rsp = dlg->ShowModal( );
                return;
            }
            if ( !m_stampDoc->Load( stream ) )
            { 
                wxString txt = wxString::Format( "\n%s Stream  Failed. Error: %s.\n\n", m_sectionFilename, stream.GetLastError( ) );
                wxMessageDialog* dlg = new wxMessageDialog( 
                    wxGetApp( ).GetFrame( ), txt, 
                    wxT( "Warning! Stream Load Failed.\n" ), 
                    wxOK | wxCANCEL | wxCENTER );
                int rsp = dlg->ShowModal( );
                return;
            }
        }
        else
        { 
            // this creates an empty document
            if ( !m_stampDoc )
            { 
                m_stampDoc = NewDocument( );
            }
            wxXmlNode* catalogSectionData = m_stampDoc->GetRoot( );
            if ( catalogSectionData )
            { 
                wxString name = catalogSectionData->GetName( );

                if ( name.Length( ) == 0 )
                { 
                    catalogSectionData->SetName( m_sectionFilename );
                }
            }
        }

        SetDirty( false );
    }

    //*****

    bool CatalogSectionData::LoadCSV( wxString filename )
    { 
        if ( !m_stampDoc )
        { 
            NewDocument( );
        }

        Utils::CSVData* csv = new Utils::CSVData( );
        wxXmlNode* docRoot = m_stampDoc->GetRoot( );
        if ( !docRoot )
        { 
            docRoot = Utils::NewNode( m_stampDoc, CatalogBaseNames[ NT_Catalog ] );
        }
        wxFileName name( filename );
        Utils::SetAttrStr( docRoot, "Name", name.GetName( ) );
        // name.MakeRelativeTo( "." );
        Utils::SetAttrStr( docRoot, "ImagePath", "" );//name.GetPath( ) );

        bool status = false;
        status = csv->DoLoad( filename, m_stampDoc->GetRoot( ) );
        SetDirty( );
        delete csv;
        return status;
    }


    //*****

    wxXmlNode* CatalogSectionData::FindNodeWithPropertyAndValue( wxString property, wxString value )
    { 
        return FindNodeWithPropertyAndValue( m_stampDoc->GetRoot( ), property, value );
    }

    //*****

    wxXmlNode* CatalogSectionData::FindNodeWithPropertyAndValue( wxXmlNode* element, wxString property, wxString value )
    { 
        wxString   	attr;
        wxXmlNode* child = element->GetChildren( );
        while ( child )
        { 
            if ( child->GetAttribute( property, &attr ) )
            { 
                if ( !value.Cmp( attr ) )
                { 
                    return child;
                }
            }
            wxXmlNode* foundChild = FindNodeWithPropertyAndValue( child, property, value );
            if ( foundChild )
            { 
                return foundChild;
            }
            child = ( wxXmlNode* )child->GetNext( );
        }
        return ( wxXmlNode* )0;
    }

    // resort the tree with the new sort order data.
    // Probably doint this because the sort order was changed.
    void CatalogSectionData::ReSortTree( )
    { 
        wxXmlDocument* newDoc = new wxXmlDocument( );
        wxXmlNode* newRoot = newDoc->GetRoot( );
        if ( !newRoot )
        { 
            newRoot = Utils::NewNode( newDoc, Catalog::CatalogBaseNames[ Catalog::NT_Catalog ] );
        }

        wxXmlDocument* doc = m_stampDoc;
        wxXmlNode* root = doc->GetRoot( );

        wxXmlAttribute* attr = Utils::GetAttribute( root, Catalog::DT_DataNames[ Catalog::DT_Name ] );
        if ( attr ) { 
            wxString name = attr->GetName( );
            wxString value = attr->GetValue( );
            Utils::SetAttrStr( newRoot, name, value );
        }
        else
        { 
            Utils::SetAttrStr( newRoot, Catalog::DT_DataNames[ Catalog::DT_Name ], "" );
        }

        attr = Utils::GetAttribute( root, "ImagePath" );
        if ( attr ) { 
            wxString name = attr->GetName( );
            wxString value = attr->GetValue( );
            Utils::SetAttrStr( newRoot, name, value );
        }
        else
        { 
            Utils::SetAttrStr( newRoot, "ImagePath", "" );
        }

        Catalog::SortData( newRoot, root );

        ReplaceDocument( newDoc );
        // Utils::XMLDump( newDoc );

    }

    //*****
    // this makes a list of the children entry elements that can have childrem
    Utils::wxXmlNodeArray* CatalogSectionData::MakeParentList( Catalog::FormatType parentType )
    { 
        //Catalog::Entry parentEntry;
        wxXmlNode* node = m_stampDoc->GetRoot( );

        Utils::wxXmlNodeArray* parentList = new  Utils::wxXmlNodeArray( );
        wxXmlNode* child = node->GetChildren( );
        while ( child )
        { 
            Catalog::Entry parentEntry( child );
            if ( parentEntry.GetFormat( ) == Catalog::FT_FormatStrings[ parentType ] )
            { 
 //   std::cout << parentEntry.GetFormat( ) << " " << parentEntry.GetID( ) << "\n";
                parentList->push_back( child );
            }
            child = child->GetNext( );
        }
        return parentList;
    }


    //*****
    // this is an attempt to group the entrys;
    // i.e., an item of type entry can be a child of an item SeTenent type.
    void CatalogSectionData::ReGroupMultiples( )
    { 
        StructureCatalogSectionData( Catalog::FT_Se_tenant, Catalog::FT_Stamp );
        StructureCatalogSectionData( Catalog::FT_Gutter_Pair, Catalog::FT_Stamp );
        StructureCatalogSectionData( Catalog::FT_Booklet_Pane, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
        StructureCatalogSectionData( Catalog::FT_Mini_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
        StructureCatalogSectionData( Catalog::FT_Souvenir_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
        StructureCatalogSectionData( Catalog::FT_Mini_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
        StructureCatalogSectionData( Catalog::FT_Booklet, Catalog::FT_Stamp, Catalog::FT_Booklet_Pane );

    }

    //*****
    // this looks through the xml tree and makes related entries of childType a child of the parent type
    void CatalogSectionData::StructureCatalogSectionData( Catalog::FormatType parentType, 
        Catalog::FormatType childType, 
        Catalog::FormatType secondChildType )
    { 
        // Make a list of all nodes that are of parentType
        wxXmlNode* node = m_stampDoc->GetRoot( );
        Utils::wxXmlNodeArray* parentList = MakeParentList( parentType );

        // now find all the entrys that go into each parent by comparing the issue date, series and face value
        for ( int i = 0; i < parentList->size( ); i++ )
        { 
            wxXmlNode* parentNode = ( wxXmlNode* )parentList->at( i );
            Catalog::Entry* parentEntry = new Catalog::Entry( parentNode );
            wxString parentIssue = parentEntry->GetIssuedDate( );
            wxString parentSeries = parentEntry->GetSeries( );
            wxString parentFace = parentEntry->GetFaceValue( );
            wxString id = parentEntry->GetID( );
            // std::cout << "Looking for children of " << id << " "<< parentIssue << "  series:"<<parentSeries<<"  face:" <<parentFace <<"\n";
            long nbrEntrys;
            parentFace.ToLong( &nbrEntrys );
            if ( nbrEntrys <= 0 )
            { 
                // if we can't figure out the face then assume a setenant is no bigger than 50 entrys
                nbrEntrys = 50;
            }
            long count = 0;
            long searchRange = 0;

            wxXmlNode* childNode = node->GetChildren( );

            while ( childNode && ( searchRange < 1005 ) && ( count < nbrEntrys ) )
            { 
                Catalog::Entry* childEntry = new Catalog::Entry( childNode );

                // figure out what the next sibling is because we may move childNode
                wxXmlNode* nextSibling = childNode->GetNext( );

                if ( parentNode != childNode )
                { 
                    // only search a reasonable distance after the first one is found
                    if ( count > 1 )
                    { 
                        searchRange++;
                    }
                    // only look at children of childType
                    wxString format = childEntry->GetFormat( );
                    if ( ( format == Catalog::FT_FormatStrings[ childType ] )
                        || ( secondChildType
                            && ( format == Catalog::FT_FormatStrings[ secondChildType ] ) ) )
                    { 
                        wxString issue = childEntry->GetIssuedDate( );
                        wxString series = childEntry->GetSeries( );
                        // if the issue date and the series match the parent assume
                        // that the childNode goes in the parent
                        if ( !issue.Cmp( parentIssue )
                            && !series.Cmp( parentSeries ) )
                        { 
                            count++;
                            wxXmlNode* currParent = childNode->GetParent( );
                            if ( currParent )
                            { 
                                currParent->RemoveChild( childNode );
                            }
                            //and add it to new place
                            parentNode->AddChild( childNode );
                        // std::cout << "Adding "<< childEntry->GetID( ) << " to" << parentEntry->GetID( ) <<"\n";                       
                        }
                    }
                }
                childNode = nextSibling;
            }
        }
    }
    void CatalogSectionData::EditDetailsDialog( wxWindow* parent )
    { 
        SectionDetailsDialog sectionDetailsDialog( parent, 12346, 
            _( "View Edit Catalog Details" ) );

        sectionDetailsDialog.SetImagePath( GetCatalogSectionImagePath( ) );
        sectionDetailsDialog.SetName( GetSectionName( ) );


        if ( sectionDetailsDialog.ShowModal( ) == wxID_CANCEL )
            return; // the user changed idea..

        if ( sectionDetailsDialog.IsNameModified( ) )
        { 
            SetImagePath( sectionDetailsDialog.GetImagePath( ) );
            SetSectionName( sectionDetailsDialog.GetName( ) );
        }
    }

}