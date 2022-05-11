/**
 * @file CSV.cpp
 * @author Eddie Monroe ()
 * @brief This file contains the class that reads .csv files
 * and loads them into an XML structure.
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
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

#include <wx/arrimpl.cpp>
#include "CatalogCode.h"
#include "Classification.h"
#include "CSV.h"
#include "Stamp.h"
#include <wx/tokenzr.h>
#include "CatalogData.h"
#include "XMLUtilities.h"

bool CSVData::ReadDataFile( wxString& filename )
{
    bool status = false;

    wxFileInputStream l_file( filename );

    if ( l_file.IsOk( ) )
    {
        wxTextInputStream text( l_file );
        // process Header
        wxString inLine = text.ReadLine( );
        m_lineCnt = 0;

        // find the line that begins with "Name"
        while ( !inLine.StartsWith( "Name" ) && !l_file.Eof( ) )
        {
            inLine = text.ReadLine( );
            m_lineCnt++;
        }
        if ( !l_file.Eof( ) )
        {
            // comma separated Variables on line; i, e, .csv file
            wxStringTokenizer tokenizer( inLine, "," );

            wxString colStr;
            while ( tokenizer.HasMoreTokens( ) )
            {
                colStr = tokenizer.GetNextToken( );
                wxString rest;
                if ( colStr.StartsWith( wxT( "\"" ), &rest ) )
                    colStr = rest;
                if ( colStr.EndsWith( wxT( "\"" ), &rest ) )
                    colStr = rest;
                m_csvColName.Add( colStr );
            }
        }

        // figure out how to map the csv file data to the stamp array
        MakeColMap( );

        if ( ReadTextInStream( l_file, text ) )
        {
            status = true;
        }
    }

    return status;
};

void CSVData::DoLoad( wxString& filename, wxXmlNode* catalogData )
{
    m_nodeData = catalogData;

    ReadDataFile( filename );
};


bool CSVData::GetIDNbr( wxString catCodes, wxString& id )
{
    wxStringTokenizer tokenizer( catCodes, "," );

    wxString valStr;
    wxString rest;
    while ( tokenizer.HasMoreTokens( ) )
    {
        valStr = tokenizer.GetNextToken( );
        if ( valStr.StartsWith( wxT( "\"" ), &rest ) )
            valStr = rest;
        if ( valStr.EndsWith( wxT( "\"" ), &rest ) )
            valStr = rest;

        // "Mi:US 1, Sn:US 1b, Yt:US 1, Sg:US 1, Un:US 1b"
        valStr.Trim( );
        valStr.Trim( false );
        
       wxString codePrefix = "Sn:US";//GetCatalogData( )->GetCatalogCodePrefix();
        if ( !codePrefix.Length() )
        {
            
            if ( valStr.StartsWith( codePrefix, &rest ) )
            {
                id = valStr.Mid( 6 );
                return true;
            }
                    
        }
    }
    return false;
}

void CSVData::MakeColMap( void )
{
    for ( int j = 0; j < MaxNbrCSVCols; j++ )
    {
        m_csvColMap[ j ] = ( DataTypes )-1;
    }
    for ( int j = 0; j < NbrColNames( ); j++ )
    {
        for ( int i = 0; i < DT_NbrTypes; i++ )
        {
            if ( !DT_DataNames[ i ].Cmp( GetColName( j ) ) )
            {
                m_csvColMap[ j ] = ( DataTypes )i;
                break;
            }
        }
    }
}
void CSVData::FixUpLine( wxString& line )
{
    int curr = 0;
    int last = line.length( );
    int firstQuote = 0;
    int nextQuote = 0;
    int comma = 0;
    while ( curr < last )
    {
        firstQuote = line.find( "\"", curr );
        if ( firstQuote < 0 )
        {
            return;
        }
        nextQuote = line.find_first_of( "\"", firstQuote + 1 );
        if ( nextQuote < 0 )
        {
            // unmatched parens
            // this means the csv is messed up
            int a = 1;
            while ( 1 )
            {
                a = 1;
            }
            return;
        }
        comma = line.find_first_of( ",", firstQuote );
        bool check_again = true;
        while ( check_again )
        {
            if ( ( comma > firstQuote ) && ( comma < nextQuote ) )
            {
                line = line.replace( comma, 1, "{" );
                comma = line.find_first_of( ",", firstQuote );
            }
            else
            {
                check_again = false;
            }
        }
        curr = nextQuote + 1;
    }
};

bool CSVData::ReadTextInStream( wxFileInputStream& file,
    wxTextInputStream& text )
{
    bool status = false;
    bool valFound = false;
    int csvCol;
    bool endOfData = false;
    wxXmlNode* docRoot = m_nodeData;

    if ( file.IsOk( ) )
    {
        while ( !file.Eof( ) && !endOfData )
        {
            // read a line and parse it
            //	wxString inLine = text.ReadLine ( );
            if ( !file.Eof( ) )
            {
                status = true;
                // read a line and parse it
                wxString line = text.ReadLine( );
                if (line.length() > 0)
                {
                    m_lineCnt++;
                    FixUpLine( line );
                    if ( !file.Eof( ) )
                    {
                        // comma separated Variables on line; i, e, .csv file
                        wxStringTokenizer tokenizer( line, "," );

                        wxXmlNode* stampElement = NewNode( docRoot,  NodeNameStrings.Item( NT_Stamp ) );

    //                    Stamp* stampNode = new Stamp( stampElement );
                        csvCol = 0;
                        valFound = false;
                        wxString valStr;
                        wxString rest;
                        while ( tokenizer.HasMoreTokens( ) )
                        {
                            // watch out for commas within quotes
                            valStr = tokenizer.GetNextToken( );
                            if ( valStr.StartsWith( wxT( "\"" ), &rest ) )
                                valStr = rest;
                            if ( valStr.EndsWith( wxT( "\"" ), &rest ) )
                                valStr = rest;
                            valStr.Replace( "{", ",", true );


                            DataTypes stampType = m_csvColMap[ csvCol ];
                            if ( stampType > 0 )
                            {
                                stampElement->AddAttribute(  DT_XMLDataNames[stampType], valStr );
                                // stampNode->SetVal( stampType, valStr );
                                // if ( stampType == DT_Catalog_Codes )
                                // {
                                //     stampNode->ProcessCatalogCodes( );
                                //     /**
                                //      * @todo the id is becoming unnecessary.  Need to figure out how to handle it
                                //      *
                                //      **************************************************/
                                //     wxString id;
                                //     if ( GetIDNbr( valStr, id ) )
                                //     {
                                //         stampNode->SetID( id );
                                //     }
                                //     stampNode->SetID( valStr );
                                // }
                                valFound = true;
                            }
                            csvCol++;
                        }

                        if ( valFound )//&& ( stampNode->GetID( ).Length( ) > 0 ) )
                        {
    //                        docRoot->AddChild( ( wxXmlNode* )stampElement );
                        }
                        else
                        {
        //                    delete stampNode;
                        }
                    }
                }
                else
                {
                    endOfData = true;
                }
            }
        }
        XMLDumpNode( ( wxXmlNode* )docRoot, "" );
    }
    return status;
};

