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

#include "design/Album.h"
#include "design/TitlePage.h"
#include "design/Page.h"
#include "odt/Document.h"
#include "odt/ODTDefs.h"
#include "utils/XMLUtilities.h"
#include "gui/DesignTreeCtrl.h"

namespace Design {

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


    bool Album::UpdateMinimumSize( )
    {

        //initialize properties before any pages regardless of the order in the layout xml
        // m_properties = (Properties*)FindFirstChild( "Properties" );
        // if ( m_properties )
        // {
        //     m_properties->UpdateMinimumSize();
        // }


        // TitlePage* titlePage = ( TitlePage* )FindFirstChild( "TitlePage" );
        // if ( titlePage )
        // {
        //     // set the layout parameters into the child
        //     titlePage->SetXPos( 0.0 );
        //     titlePage->SetYPos( 0.0 );
        //     titlePage->SetWidth( GetWidth( ) );
        //     titlePage->SetHeight( GetHeight( ) );
        //     titlePage->UpdateMinimumSize( );
        // }
        // set known child values
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);
        while ( childID.IsOk() )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl()->GetItemType( childID );
            switch ( type )
            {
                case AT_Page:
                {
                    // set the layout parameters into the child
                    Page* page = ( Page* )GetDesignTreeCtrl()->GetItemNode( childID );
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
            childID = GetDesignTreeCtrl()->GetNextChild(parentID, cookie);

        }
    }


    void Album::UpdateSizes( )
    {

        // go to the bottom of each child container object ( row, column, page)
        // and begin filling in position relative to the parent

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);
        while ( childID.IsOk() )
        {
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl()->GetItemNode( childID );

            //  call each childs Design function
            child->UpdateSizes(  );
            childID = GetDesignTreeCtrl()->GetNextChild(parentID, cookie);
        }

    }

    void Album::UpdatePositions( )
    {

        // go to the bottom of each child container object ( row, column, page)
        // and begin filling in position relative to the parent

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);
        while ( childID.IsOk() )
        {
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl()->GetItemNode( childID );

            child->UpdatePositions( ) ;
            childID = GetDesignTreeCtrl()->GetNextChild(parentID, cookie);
        }
    }

    wxXmlNode* Album::Write( wxXmlNode* parent )
    {

        // The text:p, i.e., content holder, for this Page
        wxXmlNode* thePage = 0;

        bool firstPage = true;

         wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);        while ( childID.IsOk() )
        {
            int childType  = ( AlbumBaseType )GetDesignTreeCtrl()->GetItemType( childID );
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
                    Page* page = ( Page* )GetDesignTreeCtrl()->GetItemNode( childID );
                    page->Write( thePage );
                    break;

                    childID = GetDesignTreeCtrl()->GetNextChild(parentID, cookie);

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

    NodeStatus Album::ValidateNode()
    {
        NodeStatus status = AT_OK;
        if ( GetPageHeight() <= 0.0)
        {
            std::cout << "Must define the page height.\n";
            status = AT_FATAL;
        }
        if ( GetPageWidth() <= 0.0)
        {
            std::cout << "Must define the page width.\n";
            status = AT_FATAL;
        }
        m_nodeValid = status;
        return status;
    }

    void Album::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_PageWidth );
        SetAttribute( xmlNode, AT_PageHeight );
        SetAttribute( xmlNode, AT_TopMargin );
        SetAttribute( xmlNode, AT_BottomMargin );
        SetAttribute( xmlNode, AT_RightMargin );
        SetAttribute( xmlNode, AT_LeftMargin );
        SetAttribute( xmlNode, AT_BorderFileName );
        SetAttribute( xmlNode, AT_BorderSize );
    }
    void Album::DumpLayout(   )
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);
        while ( childID.IsOk() )
        {
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl()->GetItemNode( childID );

            child->DumpLayout(  0, 0  );
            childID = GetDesignTreeCtrl()->GetNextChild(parentID, cookie);
        }
    }
}