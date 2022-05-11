/**
 * @file Album.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#include "album/Album.h"
#include "album/TitlePage.h"
#include "album/Page.h"
#include "odt/Document.h"
#include "odt/ODTDefs.h"

namespace Layout {

void Album::UpdateMinimumSize()
{

    //initialize properties before any pages regardless of the order in the layout xml
    // m_properties = (Properties*)FindFirstChild( "Properties" );
    // if ( m_properties )
    // {
    //     m_properties->UpdateMinimumSize();
    // }


    TitlePage* titlePage = (TitlePage*)FindFirstChild( "TitlePage" );
    if ( titlePage )
    {
        // set the layout parameters into the child
        titlePage->SetXPos( 0.0 );
        titlePage->SetYPos( 0.0 );
        titlePage->SetWidth( GetWidth() );
        titlePage->SetHeight( GetHeight() );
        titlePage->UpdateMinimumSize();
    }
    // set known child values

    for ( int i = 0; i < ObjectArrayCount(); i++ )
    {
        wxString childType = ChildItem( i )->GetObjectName();
        if ( !childType.Cmp( "TitlePage" ) )
        {
        }

        else if ( !childType.Cmp( "Border" ) )
        {
        }

        else if ( !childType.Cmp( "Page" ) )
        {
            // set the layout parameters into the child
            Page* page = (Page*)ChildItem( i );
            //page->SetBorder( m_border );
            page->SetXPos( 0.0 );
            page->SetYPos( 0.0 );
            page->SetWidth( GetWidth() );
            page->SetHeight( GetHeight() );
            page->SetTopMargin( GetTopMargin() );
            page->SetBottomMargin( GetBottomMargin() );
            page->SetRightMargin( GetRightMargin() );
            page->SetLeftMargin( GetLeftMargin() );
            page->SetBorderSize( GetBorderSize() );
            page->UpdateMinimumSize();
        }

        else
        {
            // ignore anything We dont recognise
        }
    }
}

bool Album::UpdateSizes()
{

    // go to the bottom of each child container object ( row, column, page)
    // and begin filling in position relative to the parent
    for ( int i = 0; i < ObjectArrayCount(); i++ )
    {
        //  call each childs Layout function
        LayoutNode* childNode = (LayoutNode*)ChildItem( i );
        childNode->UpdateSizes();
    }

    return true;
}

bool Album::UpdatePositions()
{

    // go to the bottom of each child container object ( row, column, page)
    // and begin filling in position relative to the parent
    for ( int i = 0; i < ObjectArrayCount(); i++ )
    {
        //  call each childs Layout function
        LayoutNode* childNode = (LayoutNode*)ChildItem( i );
        if ( !childNode->UpdatePositions() )
        {
            // quit on failure

            // debug message

            return false;
        }
    }

    return true;
}

wxXmlNode* Album::Write( wxXmlNode* parent )
{

    // The text:p, i.e., content holder, for this Page
    wxXmlNode* thePage = 0;

    bool firstPage = true;

    for ( int i = 0; i < ObjectArrayCount(); i++ )
    {
        wxString childType = ChildItem( i )->GetObjectName();
        if ( !childType.Cmp( "Page" ) )
        {
            // add the Text:p for this Page
            thePage = 0;
            if ( firstPage )
            {
                thePage = ODT::ContentDoc()->FindFirstPage();
                if ( !thePage )
                {
                    thePage = ODT::ContentDoc()->AddNewPage();
                }
            }
            else
            {
                thePage = ODT::ContentDoc()->AddNewPage();
            }
            firstPage = false;
            // set the layout parameters into the child
            Page* page = (Page*)ChildItem( i );
            page->Write( thePage );


        }
        // else if ( !childType.Cmp( "TitlePage" ) )
        // {

        //    // add the Text:p for this Page
        //     thePage = 0;
        //     if ( firstPage )
        //     {
        //         thePage = ContentDoc()->FindFirstPage();
        //         if ( !thePage )
        //         {
        //             thePage = ContentDoc()->AddNewPage();
        //         }
        //     }
        //     else
        //     {
        //         thePage = ContentDoc()->AddNewPage();
        //     }

        //     // set the layout parameters into the child
        //     Page* page = (Page*)ChildItem( i );
        //     page->Write( thePage );
        // }
    }
}

void Album::GetPageParameters( wxString& width,
    wxString& height,
    wxString& topMargin,
    wxString& bottomMargin,
    wxString& rightMargin,
    wxString& leftMargin )
{

    width = GetAttrVal( "PageWidth" );
    height = GetAttrVal( "PageHeight" );
    topMargin = GetAttrVal( "TopMargin" );
    bottomMargin = GetAttrVal( "BottomMargin" );
    rightMargin = GetAttrVal( "RightMargin" );
    leftMargin = GetAttrVal( "LeftMargin" );
};

void Album::MakeAlbum()
{
    UpdateMinimumSize();
    UpdateSizes();
    UpdatePositions();
    Write( (wxXmlNode*)0 );
}
}