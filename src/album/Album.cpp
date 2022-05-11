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
#include "utils/XMLUtilities.h"

namespace Layout {

    double Album::GetWidth( )
    {
        return GetAttrDbl( AT_PageWidth  );
    };

    double Album::GetHeight( )
    {
        return GetAttrDbl(  AT_PageHeight  );
    };



    double Album::GetPageWidth( )
    {
        return GetAttrDbl(  AT_PageWidth );
    };


    double Album::GetPageHeight( )
    {
        return GetAttrDbl( AT_PageHeight  );
    };


    double Album::GetTopMargin( )
    {
        return GetAttrDbl( AT_TopMargin  );
    };


    double Album::GetBottomMargin( )
    {
        return GetAttrDbl(  AT_BottomMargin  );
    };


    double Album::GetRightMargin( )
    {
        return GetAttrDbl(  AT_RightMargin  );
    };


    double Album::GetLeftMargin( )
    {
        return GetAttrDbl( AT_LeftMargin );
    };


    double Album::GetBorderSize( )
    {
        return GetAttrDbl(  AT_BorderSize );
    };

    wxString  Album::GetBorderFileName( )
    {
        return GetAttrStr( AT_BorderFileName );
    };



    wxString Album::GetDocName( )
    {
        return  GetAttrStr( "Name" );
    };


    void Album::UpdateMinimumSize( )
    {

        //initialize properties before any pages regardless of the order in the layout xml
        // m_properties = (Properties*)FindFirstChild( "Properties" );
        // if ( m_properties )
        // {
        //     m_properties->UpdateMinimumSize();
        // }


        TitlePage* titlePage = ( TitlePage* )FindFirstChild( "TitlePage" );
        if ( titlePage )
        {
            // set the layout parameters into the child
            titlePage->SetXPos( 0.0 );
            titlePage->SetYPos( 0.0 );
            titlePage->SetWidth( GetWidth( ) );
            titlePage->SetHeight( GetHeight( ) );
            titlePage->UpdateMinimumSize( );
        }
        // set known child values


        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            AlbumNodeType type = ( AlbumNodeType )( *it )->GetNodeType( );
            switch ( type )
            {
                case AT_Page:
                {
                    // set the layout parameters into the child
                    Page* page = ( Page* )( *it );
                    //page->SetBorder( m_border );
                    page->SetXPos( 0.0 );
                    page->SetYPos( 0.0 );
                    page->SetWidth( GetWidth( ) );
                    page->SetHeight( GetHeight( ) );
                    page->SetTopMargin( GetTopMargin( ) );
                    page->SetBottomMargin( GetBottomMargin( ) );
                    page->SetRightMargin( GetRightMargin( ) );
                    page->SetLeftMargin( GetLeftMargin( ) );
                    page->SetBorderSize( GetBorderSize( ) );
                    page->UpdateMinimumSize( );
                    break;
                }
                default:
                    break;
            }

        }
    }


    void Album::UpdateSizes( )
    {

        // go to the bottom of each child container object ( row, column, page)
        // and begin filling in position relative to the parent

        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );

            //  call each childs Layout function
            child->UpdateSizes(  );
        }

    }

    void Album::UpdatePositions( )
    {

        // go to the bottom of each child container object ( row, column, page)
        // and begin filling in position relative to the parent
        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );

            child->UpdatePositions( ) ;
        }
    }

    wxXmlNode* Album::Write( wxXmlNode* parent )
    {

        // The text:p, i.e., content holder, for this Page
        wxXmlNode* thePage = 0;

        bool firstPage = true;

        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );
            int childType = child->GetNodeType( );
            switch ( childType )
            {
                case AT_Page:
                {
                    // add the Text:p for this Page
                    thePage = 0;
                    if ( firstPage )
                    {
                        thePage = ODT::ContentDoc( )->FindFirstPage( );
                        if ( !thePage )
                        {
                            thePage = ODT::ContentDoc( )->AddNewPage( );
                        }
                    }
                    else
                    {
                        thePage = ODT::ContentDoc( )->AddNewPage( );
                    }
                    firstPage = false;
                    // set the layout parameters into the child
                    Page* page = ( Page* )child;
                    page->Write( thePage );
                    break;

                }
            
                default:
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
                break;
            }
        }
    }

    void Album::GetPageParameters( wxString& width,
        wxString& height,
        wxString& topMargin,
        wxString& bottomMargin,
        wxString& rightMargin,
        wxString& leftMargin )
    {
        width = GetAttrStr( AT_PageWidth );
        height = GetAttrStr( AT_PageHeight );
        topMargin = GetAttrStr( AT_TopMargin );
        bottomMargin = GetAttrStr( AT_BottomMargin );
        rightMargin = GetAttrStr( AT_RightMargin );
        leftMargin = GetAttrStr( AT_LeftMargin );
    };

    void Album::MakeAlbum( )
    {
        UpdateMinimumSize( );
        UpdateSizes( );
        UpdatePositions( );
        Write( ( wxXmlNode* )0 );
    }
}