/**
 * @file CatalogVolume.cpp
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
 */


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

#include "catalog/CatalogVolume.h"

#include "Defs.h"

#include "catalog/CatalogData.h"
#include "catalog/CatalogDefs.h"
#include "catalog/StampMount.h"
#include "catalog/Entry.h"
#include "collection/CollectionList.h"

#include "utils/CSV.h"
#include "utils/Settings.h"
#include "utils/Project.h"
#include "utils/XMLUtilities.h"
#include "gui/AppData.h"
#include "gui/CatalogDetailsDialog.h"
#include "gui/StampToolFrame.h"
#include "gui/GenerateList.h"

namespace Catalog {
    CatalogVolume::CatalogVolume( )
    {
        m_stampDoc = 0;
    }

    CatalogVolume::~CatalogVolume( )
    {
        delete m_stampDoc;
    }

    void CatalogVolume::EditDetailsDialog( wxWindow* parent )
    {
        CatalogDetailsDialog catalogDetailsDialog( parent, 12346,
            _( "Catalog Import File Details" ) );

        catalogDetailsDialog.SetCatalogFilename( GetVolumeFilename( ) );
        catalogDetailsDialog.SetName( GetVolumeName( ) );


        if ( catalogDetailsDialog.ShowModal( ) == wxID_CANCEL )
            return; // the user changed idea..

        SetVolumeName( catalogDetailsDialog.GetName( ) );
        wxString cwd = wxGetCwd( );
        wxFileName volFile( catalogDetailsDialog.GetCatalogPath( ) );
        volFile.MakeRelativeTo( cwd );
        SetVolumeFilename( volFile.GetFullPath( ) );
    }
    wxXmlNode* CatalogVolume::FindNodeWithPropertyAndValue( wxString property, wxString value )
    {
        return FindNodeWithPropertyAndValue( m_stampDoc->GetRoot( ), property, value );
    }

    wxXmlNode* CatalogVolume::FindNodeWithPropertyAndValue( wxXmlNode* element, wxString property, wxString value )
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
            child = ( wxXmlNode* ) child->GetNext( );
        }
        return ( wxXmlNode* ) 0;
    }


    bool CatalogVolume::FixupInventoryStatus( )
    {

        wxXmlNode* root = m_stampDoc->GetRoot( );
        wxString nodeName = root->GetName( );

        wxXmlNode* child = root;
        while ( child )
        {
            FixupInventoryStatus( child, ( InventoryStatusType ) ST_Exclude );
            child = child->GetNext( );
        }
        return true;
    }

    bool CatalogVolume::FixupInventoryStatus( wxXmlNode* parent, InventoryStatusType parentStatus )
    {

        if ( parentStatus >= ST_None && parentStatus < ST_Exclude )
        {
            //make sure this status is in a specimen
            wxXmlNode* node = Utils::NewNode( parent, "Specimen" );
            wxString currCollection = GetCollectionList( )->GetCurrentName( );
            Utils::SetAttrStr( node, ItemDataNames[ IDT_Collection ], currCollection );
            Utils::SetAttrStr( node, ItemDataNames[ IDT_InventoryStatus ], InventoryStatusStrings[ parentStatus ] );
        }

        bool specimenFound = false;
        wxXmlNode* child = parent->GetChildren( );
        while ( child )
        {
            wxXmlNode* nextChild = child->GetNext( );
            wxString nodeName = child->GetName( );
            // for each entry
            if ( !nodeName.Cmp( "Entry" ) )
            {

                wxString statusStr = child->GetAttribute( XMLDataNames[ DT_InventoryStatus ] );
                InventoryStatusType status = ( InventoryStatusType ) ST_Exclude;
                if ( !statusStr.IsEmpty( ) )
                {
                    status = FindStatusType( statusStr );
                }
                wxString currCollection = GetCollectionList( )->GetCurrentName( );
                // find all specimen nodes

                FixupInventoryStatus( child, status );
                bool ok = child->DeleteAttribute( XMLDataNames[ DT_InventoryStatus ] );;

            }
            else  if ( !nodeName.Cmp( "Specimen" ) )
            {
                // use the status in the specimen in preference to the parent preference
                wxString statusStr = child->GetAttribute( ItemDataNames[ IDT_InventoryStatus ], "" );

                InventoryStatusType specimenStatus = ( InventoryStatusType ) ST_Exclude;
                if ( !statusStr.IsEmpty( ) )
                {
                    specimenStatus = FindStatusType( statusStr );
                }

                if ( specimenStatus >= ST_None && specimenStatus < ST_Exclude )
                {
                    parentStatus = specimenStatus;
                }

                specimenFound = true;
                wxString name = child->GetAttribute( "Collection", "" );
                // if this collection doesn't exist then add it.
                if ( !name.IsEmpty( ) )
                {
                    if ( parentStatus >= ST_None && parentStatus < ST_Exclude )
                    {
                        // if this name not in collection then add it
                        Inventory::Collection* collection = GetCollectionList( )->FindCollection( name );
                        if ( !collection )
                        {
                            GetCollectionList( )->AddCollection( name, "", "" );
                        }
                        Utils::SetAttrStr( child, ItemDataNames[ IDT_InventoryStatus ], InventoryStatusStrings[ parentStatus ] );
                    }
                }
                else
                {
                    // specimen has no collection
                    if ( parentStatus >= ST_None && parentStatus < ST_Exclude )
                    {
                        wxString currCollection = GetCollectionList( )->GetCurrentName( );
                        Utils::SetAttrStr( child, ItemDataNames[ IDT_Collection ], currCollection );
                        Utils::SetAttrStr( child, ItemDataNames[ IDT_InventoryStatus ], InventoryStatusStrings[ parentStatus ] );
                    }
                }
            }
            else  if ( !nodeName.Cmp( "CatalogCode" ) )
            {
                //clobber it... or just ignore it
                parent->RemoveChild( child );
            }
            else
            {

                // for all other node types just decend and keep looking
                FixupInventoryStatus( child, ( InventoryStatusType ) -1 );
            }
            child = nextChild; //child->GetNext( );
        }
        return true;
    }



    wxString CatalogVolume::GetCatalogPath( )
    {
        wxString filename = GetCatalogFilename( );
        wxFileName FN( filename );
        FN.MakeAbsolute( );
        return FN.GetPath( );
    }

    wxString CatalogVolume::GetCatalogBaseName( )
    {
        wxString filename = GetCatalogFilename( );
        wxFileName FN( filename );
        return FN.GetName( );
    }

    wxString CatalogVolume::GetZipFileName( )
    {
        wxString path = GetCatalogPath( );
        wxString name = GetCatalogBaseName( );
        name = name + "Cat.zip";
        wxFileName FN( path );
        FN.SetName( name );
        FN.SetExt( "zip" );
        return ( path + "/" + name );
    }
    wxString CatalogVolume::GetCatalogVolumeImagePath( )
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

    bool CatalogVolume::IsOK( )
    {
        if ( m_stampDoc )
        {
            return true;
        }
        return false;
    }

    bool CatalogVolume::LoadCSV( wxString filename )
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

        bool status = false;
        status = csv->DoLoad( filename, m_stampDoc->GetRoot( ) );

        SetDirty( );
        delete csv;
        return status;
    }

    void CatalogVolume::Load( )
    {
        LoadXML( );
        wxString name = GetVolumeName( );
        if ( !name.IsEmpty( ) )
        {
            name = GetVolumeFilename( );
            wxFileName fn( name );
            SetVolumeName( fn.GetName( ) );
        }
    }

    void CatalogVolume::LoadXML( )
    {

        bool ok = false;
        if ( m_volumeFilename.length( ) > 0 )
        {
            if ( !m_stampDoc )
            {
                m_stampDoc = NewDocument( );
            }
            wxString cwd = wxGetCwd( );
            wxFileInputStream stream( m_volumeFilename );
            if ( !stream.IsOk( ) )
            {
                wxString txt = wxString::Format( "%s Stream Create Failed.\n\n", m_volumeFilename );
                wxMessageDialog* dlg = new wxMessageDialog(
                    GetFrame( ), txt,
                    wxT( "Warning! Stream Create Failed.\n" ),
                    wxOK | wxCANCEL | wxCENTER );
                int rsp = dlg->ShowModal( );
                return;
            }

            if ( !m_stampDoc->Load( stream ) )
            {
                int err = stream.GetLastError( );
                wxString txt = wxString::Format( "\n%s Stream  Failed. Error: %d\n\n.", m_volumeFilename, err );
                wxMessageDialog* dlg = new wxMessageDialog(
                    GetFrame( ), txt,
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
            wxXmlNode* catalogVolume = m_stampDoc->GetRoot( );
            if ( catalogVolume )
            {
                wxString name = catalogVolume->GetName( );

                if ( name.Length( ) == 0 )
                {
                    catalogVolume->SetName( m_volumeFilename );
                }
            }
        }

        //        FixupInventoryStatus( );
        //        UpdateMount( );
        SetDirty( false );
    }

    bool CatalogVolume::UpdateMount( )
    {

        wxXmlNode* root = m_stampDoc->GetRoot( );
        wxString nodeName = root->GetName( );

        wxXmlNode* child = root;
        while ( child )
        {
            UpdateMount( child );
            child = child->GetNext( );
        }
        return true;
    }

    bool CatalogVolume::UpdateMount( wxXmlNode* parent )
    {
        wxXmlNode* child = parent->GetChildren( );
        while ( child )
        {
            wxString nodeName = child->GetName( );
            if ( !nodeName.Cmp( "Entry" ) )
            {
                wxString id = child->GetAttribute( "ID_Nbr" );
                wxString mountStr = GetStampMountData( )->Find( id );
                wxString status = child->GetAttribute( XMLDataNames[ DT_StampMount ] );
                if ( status.IsEmpty( ) && !mountStr.IsEmpty( ) )
                {
                    Utils::SetAttrStr( child, XMLDataNames[ DT_StampMount ], mountStr );
                }
            }
            else
            {
            }

            UpdateMount( child );
            child = child->GetNext( );
        }
        return true;
    }


    bool CatalogVolume::MakeCatalogList( wxArrayString& fileArray )
    {
        fileArray.Clear( );

        wxXmlNode* root = m_stampDoc->GetRoot( );
        wxString nodeName = root->GetName( );
        GetCatalogData( )->GetGenerateListPanel( )->ClearList( );
        wxXmlNode* child = root;
        while ( child )
        {
            MakeCatalogList( child, fileArray );
            child = child->GetNext( );
        }
        return true;
    }

    bool CatalogVolume::MakeCatalogList( wxXmlNode* parent, wxArrayString& fileArray )
    {
        wxXmlNode* child = parent->GetChildren( );
        while ( child )
        {
            wxString nodeName = child->GetName( );
            if ( !nodeName.Cmp( "Entry" ) )
            {
                wxString imageName = child->GetAttribute( "ID_Nbr" );

                wxString status = child->GetAttribute( XMLDataNames[ DT_InventoryStatus ], InventoryStatusStrings[ ST_Exclude ] );
                InventoryStatusType type = FindStatusType( status );
                if ( type < ST_None ) type = ST_Exclude;
                Catalog::Entry entry( child );
                GenerateList* genList = GetCatalogData( )->GetGenerateListPanel( );
                if ( genList->CheckStatus( &entry ) )
                {
                    genList->AddEntry( &entry );
                }
            }
            MakeCatalogList( child, fileArray );
            child = child->GetNext( );
        }
        return true;
    }

    void CatalogVolume::MakeParentList( Catalog::FormatType parentType, Utils::wxXmlNodeArray* parentList, wxXmlNode* node )
    {

        wxXmlNode* child = node->GetChildren( );
        while ( child )
        {
            Catalog::Entry parentEntry( child );
            if ( parentEntry.GetFormat( ) == Catalog::FormatStrings[ parentType ] )
            {
                parentList->push_back( child );
            }
            MakeParentList( parentType, parentList, child );
            child = child->GetNext( );
        }
    }


    /// this makes a list of the children entry elements that can have childrem
    Utils::wxXmlNodeArray* CatalogVolume::MakeParentList( Catalog::FormatType parentType )
    {

        //Catalog::Entry parentEntry;
        wxXmlNode* node = m_stampDoc->GetRoot( );

        Utils::wxXmlNodeArray* parentList = new  Utils::wxXmlNodeArray( );
        MakeParentList( parentType, parentList, node );

        return parentList;
    }


    void CatalogVolume::NewCatalog( )
    {
        m_stampDoc = NewDocument( );
        wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, "Catalog" );
        m_stampDoc->SetRoot( root );
    }

    CatalogVolume* NewCatalogVolumeInstance( )
    {
        return new CatalogVolume( );
    }

    wxXmlDocument* CatalogVolume::NewDocument( )
    {
        delete m_stampDoc;
        m_stampDoc = new wxXmlDocument( );
        return m_stampDoc;
    };

    wxXmlDocument* CatalogVolume::ReplaceDocument( wxXmlDocument* doc )
    {
        delete m_stampDoc;
        m_stampDoc = doc;
        return m_stampDoc;
    };

    void CatalogVolume::Save( )
    {
        wxString filename = m_volumeFilename;
        if ( wxFileExists( filename ) )
        {
            wxFileName bakFile( filename );
            bakFile.SetExt( "bak.cat" );
            wxRenameFile( filename, bakFile.GetFullPath( ), true );
        }
        m_stampDoc->Save( filename );
        SetDirty( false );
    }

    void CatalogVolume::SetDirty( bool state )
    {
        m_dirty = state;
        if ( m_dirty )
        {
            GetAppData( )->SetDirty( true );
        }
    }

    // resort the tree with the new sort order data.
    // Probably doint this because the sort order was changed.
    void CatalogVolume::ReSortTree( )
    {
        wxXmlDocument* newDoc = new wxXmlDocument( );
        wxXmlNode* newRoot = newDoc->GetRoot( );
        if ( !newRoot )
        {
            newRoot = Utils::NewNode( newDoc, Catalog::CatalogBaseNames[ Catalog::NT_Catalog ] );
        }

        wxXmlDocument* doc = m_stampDoc;
        wxXmlNode* root = doc->GetRoot( );

        wxXmlAttribute* attr = Utils::GetAttribute( root, Catalog::DataTypeNames[ Catalog::DT_Name ] );
        if ( attr ) {
            wxString name = attr->GetName( );
            wxString value = attr->GetValue( );
            Utils::SetAttrStr( newRoot, name, value );
        }
        else
        {
            Utils::SetAttrStr( newRoot, Catalog::DataTypeNames[ Catalog::DT_Name ], "" );
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
    }

    void CatalogVolume::SetImagePath( wxString str )
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

    // this is an attempt to group the entrys;
    // i.e., an item of type entry can be a child of an item SeTenent type.
    void CatalogVolume::ReGroupMultiples( )
    {
        StructureCatalogVolume( Catalog::FT_Se_tenant, Catalog::FT_Stamp );
        StructureCatalogVolume( Catalog::FT_Gutter_Pair, Catalog::FT_Stamp );
        StructureCatalogVolume( Catalog::FT_Booklet_Pane, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
        StructureCatalogVolume( Catalog::FT_Mini_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
        StructureCatalogVolume( Catalog::FT_Souvenir_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
        StructureCatalogVolume( Catalog::FT_Mini_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
        StructureCatalogVolume( Catalog::FT_Booklet, Catalog::FT_Stamp, Catalog::FT_Booklet_Pane );

    }

    //
    // this looks through the xml tree and makes related entries of childType a child of the parent type
    void CatalogVolume::StructureCatalogVolume( Catalog::FormatType parentType,
        Catalog::FormatType childType,
        Catalog::FormatType secondChildType )
    {
        // Make a list of all nodes that are of parentType
//        wxXmlNode* node = m_stampDoc->GetRoot( );
        Utils::wxXmlNodeArray* parentList = MakeParentList( parentType );

        // now find all the entrys that go into each parent by comparing the issue date, series and face value
        for ( int i = 0; i < parentList->size( ); i++ )
        {
            wxXmlNode* parentNode = ( wxXmlNode* ) parentList->at( i );
            Catalog::Entry parentEntry( parentNode );
            wxString parentIssue = parentEntry.GetIssuedDate( );
            wxString parentSeries = parentEntry.GetSeries( );
            wxString parentFace = parentEntry.GetFaceValue( );
            wxString id = parentEntry.GetID( );
            if ( !id.Cmp( "Sn:US 4690a" ) )
            {
                int a = 0;
            }
            long nbrEntrys;
            parentFace.ToLong( &nbrEntrys );
            if ( nbrEntrys <= 0 )
            {
                // if we can't figure out the face then assume a setenant is no bigger than 50 entrys
                nbrEntrys = 50;
            }
            long count = 0;
            long searchRange = 0;

            // we want to examine siblings of the parentNode
            wxXmlNode* childNode = parentNode->GetParent( )->GetChildren( );

            while ( childNode && ( searchRange < 1005 ) && ( count < nbrEntrys ) )
            {
                Catalog::Entry childEntry( childNode );

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
                    wxString format = childEntry.GetFormat( );
                    if ( ( format == Catalog::FormatStrings[ childType ] )
                        || ( secondChildType
                            && ( format == Catalog::FormatStrings[ secondChildType ] ) ) )
                    {
                        wxString issue = childEntry.GetIssuedDate( );
                        wxString series = childEntry.GetSeries( );
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
                        }
                    }
                }
                childNode = nextSibling;
            }
        }
    }


}